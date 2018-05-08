#include "stdafx.h"
#include "global.h"

#include <ProMenuBar.h>
#include <ProAsmcomp.h>
#include <ProModelitem.h>
#include <ProSolid.h>
#include "ProUtil.h"
#include <ProParameter.h>
#include <ProMode.h>

#include "XMLProc.h"

#include "InsertEquipmentDlg.h"

// 命令的响应函数
int InsertEquipment(uiCmdCmdId  command, uiCmdValue *p_value, void *p_push_command_data)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CInsertEquipmentDlg dlg;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{		
		AccessOperation accessMag((_bstr_t)m_equLibPath);	
		accessMag.OnInitADOConn();

		CString sql;
		sql.Format(_T("SELECT * FROM Equipment WHERE ID = %d"), dlg.m_ID);
		_RecordsetPtr res = accessMag.GetRecordSet((_bstr_t)sql);	
		if(!res->adoEOF)
		{
			CString name = (_bstr_t)res->GetFields()->GetItem("Path")->Value;
			CString path;
			path.Format(_T("%s\\Model\\%s\\Model.prt.1"),m_equLibPath,name);

			ProAssembly asm_model;
			ProSolid comp_model;

			ProMatrix identity_matrix = {{1.0,0.0,0.0,0.0},
			{0.0,1.0,0.0,0.0},
			{0.0,0.0,1.0,0.0},
			{0.0,0.0,0.0,1.0}};
			ProAsmcomp asmcomp;

			// 获得当前打开的组件对象
			ProMdlCurrentGet((ProMdl*)&asm_model);
			// 在目录中载入零件
			ProMdlLoad(path.GetBuffer(),PRO_MDL_PART,PRO_B_FALSE,(ProMdl*)&comp_model);
			
			srand((unsigned)time(NULL)); 
			CString id;
			id.Format(_T("P%04d%04d%04d%04d%04d%04d%04d"),rand()%9999,rand()%9998,rand()%9997,rand()%9996,rand()%9995,rand()%9994,rand()%9993);
			ProMdlRename(comp_model, (wchar_t *)(_bstr_t)id);

			// 得到组件和零件的最大外形尺寸
			Pro3dPnt compOutline[3],asmOutline[3];
			ProSolidOutlineGet(comp_model,compOutline);
			ProSolidOutlineGet(asm_model,asmOutline);

			identity_matrix[3][0] = asmOutline[1][0] + compOutline[1][0] - compOutline[0][0];
			identity_matrix[3][1] = asmOutline[1][1] + compOutline[1][1] - compOutline[0][1];
			identity_matrix[3][2] = asmOutline[1][2] + compOutline[1][2] - compOutline[0][2];

			// 将零件插入到组件中
			ProAsmcompAssemble(asm_model,comp_model,identity_matrix,&asmcomp);
			ProSolidRegenerate((ProSolid)asmcomp.owner,PRO_REGEN_CAN_FIX);			
			ProAsmcompConstrRedefUI(&asmcomp);	


			// 修改元件的属性
			ProModelitem comp_modelitem;
			ProMdlToModelitem(comp_model,&comp_modelitem);	

			path.Format(_T("%s\\Model\\%s\\Property\\Basic.xml"),m_equLibPath,name);
			
			XMLProc xmlProc;
			IXMLDOMDocumentPtr xmlDoc = xmlProc.Read((LPTSTR)(LPCTSTR)path);
			IXMLDOMElement *rootEle = xmlProc.GetReadRoot();
			IXMLDOMNodeList *propNodeList;
			xmlProc.GetChildList(&propNodeList,rootEle);

			IXMLDOMNode* temp;			
			while(propNodeList->nextNode(&temp) == S_OK)
			{				
				BSTR attrTag, attrType, attrDesc, attrValueType, attrValue;
				
				xmlProc.GetNodeAttribute(temp,"Tag",&attrTag);
				xmlProc.GetNodeAttribute(temp,"Type",&attrType);
				xmlProc.GetNodeAttribute(temp,"Desc",&attrDesc);
				xmlProc.GetNodeAttribute(temp,"ValueType",&attrValueType);				
				xmlProc.GetText(temp,&attrValue);

				ProName paraName;
				wcscpy(paraName,(wchar_t *)(_bstr_t)attrTag);

				if( wcscmp((wchar_t *)(_bstr_t)attrValueType,_T("string")) == 0 )
				{
					ProParameter param;
					ProParamvalue proval;			
					proval.type = PRO_PARAM_STRING;
					wcscpy(proval.value.s_val, (wchar_t *)(_bstr_t)attrValue);					
					ProParameterCreate(&comp_modelitem,paraName, &proval, &param);	
				}
				else if(  wcscmp((wchar_t *)(_bstr_t)attrValueType,_T("float")) == 0  )
				{
					ProParameter param;
					ProParamvalue proval;			
					proval.type = PRO_PARAM_DOUBLE;
					
					double value = 0;
					sscanf((char *)(_bstr_t)attrValue, "%lf", &value);
					proval.value.d_val = value;					
					ProParameterCreate(&comp_modelitem,paraName, &proval, &param);	
				}
			}

		}

		accessMag.ExitConnect();
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

    return 0;
}

// 命令的菜单权限函数
uiCmdAccessState InsertEquipmentAccess(uiCmdAccessMode access_mode)
{
    ProMode mode;
	ProError res = ProModeCurrentGet(&mode);
	if(mode != PRO_MODE_ASSEMBLY)
	{
		return ACCESS_UNAVAILABLE;
	}
	else
	{
		return ACCESS_AVAILABLE;
	}
}