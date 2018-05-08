// Rescue Box Platform.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "global.h"
#include "Rescue Box Platform.h"
#include "InsertEquipmentDlg.h"

#include <ProMenuBar.h>
#include <ProAsmcomp.h>
#include <ProModelitem.h>
#include <ProSolid.h>
#include "ProUtil.h"

#define PRO_USE_VAR_ARGS 1

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern uiCmdAccessState InsertEquipmentAccess(uiCmdAccessMode access_mode);
extern int InsertEquipment(uiCmdCmdId  command, uiCmdValue *p_value, void *p_push_command_data);

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CRescueBoxPlatformApp

BEGIN_MESSAGE_MAP(CRescueBoxPlatformApp, CWinApp)
END_MESSAGE_MAP()


// CRescueBoxPlatformApp 构造

CRescueBoxPlatformApp::CRescueBoxPlatformApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CRescueBoxPlatformApp 对象

CRescueBoxPlatformApp theApp;

// CRescueBoxPlatformApp 初始化

BOOL CRescueBoxPlatformApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


// Pro/TOOLKIT的入口函数
extern "C" int user_initialize()
{	
	ProError err;
	
	// 变量初始化
	m_equLibPath.Format(_T("E:\\文献资料\\1-模块化设计\\4-苏炎师兄资料\\3-软件源代码2版\\Library\\Equipment\\Default"));
	m_mechLibPath.Format(_T("E:\\文献资料\\1-模块化设计\\4-苏炎师兄资料\\3-软件源代码2版\\Library\\Mechanism\\Default"));


    // 信息文件名称
    ProFamilyName MsgFile;
    ProStringToWstring(MsgFile, "Menu_Msg.txt");

    // 添加菜单:Menu
    err = ProMenubarMenuAdd("MenuMain", "Menu", "Help", PRO_B_TRUE, MsgFile);

    // 添加插入器材命令
    uiCmdCmdId cmd_id1;
    err = ProCmdActionAdd("CmdInsert", InsertEquipment, uiCmdPrioDefault, InsertEquipmentAccess,PRO_B_FALSE, PRO_B_FALSE, &cmd_id1);
	err = ProMenubarmenuPushbuttonAdd("MenuMain", "ButtonInsert", "InsertEquipment", "InsertEquipmentHelp",NULL, PRO_B_TRUE, cmd_id1, MsgFile);
    
	// 添加插入机构命令
    uiCmdCmdId cmd_id2;
    err = ProCmdActionAdd("CmdInsertMechanism", InsertMechanism, uiCmdPrioDefault, InsertMechanismAccess,PRO_B_FALSE, PRO_B_FALSE, &cmd_id2);
	err = ProMenubarmenuPushbuttonAdd("MenuMain", "ButtonInsertMechanism", "InsertMechanism", "InsertMechanismHelp",NULL, PRO_B_TRUE, cmd_id2, MsgFile);

	// 添加编辑机构命令
    uiCmdCmdId cmd_id3;
    err = ProCmdActionAdd("CmdEditMechanism", EditMechanism, uiCmdPrioDefault, EditMechanismAccess,PRO_B_FALSE, PRO_B_FALSE, &cmd_id3);
	err = ProMenubarmenuPushbuttonAdd("MenuMain", "ButtonEditMechanism", "EditMechanism", "EditMechanismHelp",NULL, PRO_B_TRUE, cmd_id3, MsgFile);

	
	return 0;
}

// Pro/TOOLKIT结束时调用的函数
extern "C" void user_terminate()
{}

