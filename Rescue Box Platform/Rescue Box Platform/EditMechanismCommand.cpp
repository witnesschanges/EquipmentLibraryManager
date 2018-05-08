#include "stdafx.h"
#include "global.h"

#include <ProMenuBar.h>
#include <ProAsmcomp.h>
#include <ProModelitem.h>
#include <ProSolid.h>
#include "ProUtil.h"
#include <ProParameter.h>
#include <ProMode.h>

#include "EditMechanismDlg.h"

// 命令的响应函数
int EditMechanism(uiCmdCmdId  command, uiCmdValue *p_value, void *p_push_command_data)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ProError status;
	int num = 0;
	ProSelection *sel;
	status = ProSelect("prt_or_asm",1,NULL,NULL,NULL,NULL,&sel,&num);
	if(status != PRO_TK_NO_ERROR || num <=0 )
	{
		return 0;
	}

	ProModelitem comp;
	status = ProSelectionModelitemGet(*sel, &comp);
	if(status == PRO_TK_NO_ERROR)
	{
		ProParameter param;
		ProName name;
		ProParamvalue value;

		ProParameterInit(&comp, _T("RBP_TYPE"), &param);
		ProParameterValueGet(&param, &value);
		if(value.type == PRO_PARAM_STRING && wcscmp(value.value.s_val,_T("MECHANISM")) == 0)
		{
			EditMechanismDlg dlg(&comp);
			INT_PTR nResponse = dlg.DoModal();
			if (nResponse == IDOK)
			{	
			}
			else
			{}
		}
	}

	return 0;
}

// 命令的菜单权限函数
uiCmdAccessState EditMechanismAccess(uiCmdAccessMode access_mode)
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