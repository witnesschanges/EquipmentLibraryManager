#include "stdafx.h"
#include "global.h"

#include <fstream>

#include <ProMenuBar.h>
#include <ProAsmcomp.h>
#include <ProModelitem.h>
#include <ProSolid.h>
#include "ProUtil.h"
#include <ProParameter.h>
#include <ProFeatType.h>
#include <ProMode.h>

#include "XMLProc.h"

#include "InsertMechanismDlg.h"



ProError filter_action(ProFeature *p_feature, ProAppData app_data)
{
	ProFeattype p_type;
	ProFeatureTypeGet(p_feature, &p_type);
	if(p_type != PRO_FEAT_COMPONENT)
	{
		return PRO_TK_CONTINUE;
	}
	return PRO_TK_NO_ERROR;
}

ProError visit_action(ProFeature *p_feature, ProError status, ProAppData app_data)
{
	ProMdlType type;
	ProMdl mdl;
	ProAsmcompMdlGet((ProAsmcomp *)p_feature, &mdl);
	ProMdlTypeGet(mdl, &type);
	if(type == PRO_MDL_ASSEMBLY)
	{
		ProSolidFeatVisit((ProSolid)mdl, (ProFeatureVisitAction)visit_action, (ProFeatureFilterAction)filter_action, NULL);
	}
	if(type == PRO_MDL_PART)
	{
		CString id;
		id.Format(_T("P%04d%04d%04d%04d%04d%04d%04d"),rand()%9999,rand()%9999,rand()%9999,rand()%9999,rand()%9999,rand()%9999,rand()%9999);		
		ProMdlRename(mdl, (wchar_t *)(_bstr_t)id);
	}
	return PRO_TK_NO_ERROR;
}


// 欢迎命令的响应函数
int InsertMechanism(uiCmdCmdId  command, uiCmdValue *p_value, void *p_push_command_data)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// 当前模型是否有对应的文件
	ProAssembly asm_model;	
	ProMdlCurrentGet((ProMdl*)&asm_model);
	ProMdldata asm_data;
	ProMdlDataGet(asm_model, &asm_data);
	CString asm_path;
	asm_path.Format(_T("%s:%s%s.%s.%d"),asm_data.device, asm_data.path, asm_data.name, asm_data.type, asm_data.version);
	std::ifstream fin(asm_path);
	if(!fin)
	{
		AfxMessageBox(_T("当前的模型未指定路径，请保存后使用此命令。"));
		return 0;
	}
	
	InsertMechanismDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{		
		AccessOperation accessMag((_bstr_t)m_mechLibPath);	
		accessMag.OnInitADOConn();

		CString sql;
		sql.Format(_T("SELECT * FROM Mechanism WHERE ID = %d"), dlg.m_ID);
		_RecordsetPtr res = accessMag.GetRecordSet((_bstr_t)sql);	
		if(!res->adoEOF)
		{
			CString name = (_bstr_t)res->GetFields()->GetItem("Path")->Value;
			CString path;
			path.Format(_T("%s\\Model\\%s\\Model.asm.1"),m_mechLibPath,name);

			
			ProSolid comp_model;

			ProMatrix identity_matrix = {{1.0,0.0,0.0,0.0},
			{0.0,1.0,0.0,0.0},
			{0.0,0.0,1.0,0.0},
			{0.0,0.0,0.0,1.0}};
			ProAsmcomp asmcomp;


			// 在目录中载入组件
			ProMdlLoad(path.GetBuffer(),PRO_MDL_ASSEMBLY,PRO_B_FALSE,(ProMdl*)&comp_model);

			// 修改组立中所有元素的名称
			srand((unsigned)time(NULL)); 
			ProSolidFeatVisit(comp_model,(ProFeatureVisitAction)visit_action, (ProFeatureFilterAction)filter_action, NULL);

			CString id;
			id.Format(_T("A%04d%04d%04d%04d%04d%04d%04d"),rand()%9999,rand()%9998,rand()%9997,rand()%9996,rand()%9995,rand()%9994,rand()%9993);
			ProMdlRename(comp_model, (wchar_t *)(_bstr_t)id);
			
			CString comp_path;
			comp_path.Format(_T("%s:%s"), asm_data.device, asm_data.path);
			ProMdldata comp_data;
			wcscpy(comp_data.path, comp_path);
			ProMdlBackup(comp_model,&comp_data);


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

			path.Format(_T("%s\\Model\\%s\\Property\\Basic.xml"),m_mechLibPath,name);
			
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

// 欢迎命令的菜单权限函数
uiCmdAccessState InsertMechanismAccess(uiCmdAccessMode access_mode)
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