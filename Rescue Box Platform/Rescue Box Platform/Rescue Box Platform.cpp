// Rescue Box Platform.cpp : ���� DLL �ĳ�ʼ�����̡�
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
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CRescueBoxPlatformApp

BEGIN_MESSAGE_MAP(CRescueBoxPlatformApp, CWinApp)
END_MESSAGE_MAP()


// CRescueBoxPlatformApp ����

CRescueBoxPlatformApp::CRescueBoxPlatformApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CRescueBoxPlatformApp ����

CRescueBoxPlatformApp theApp;

// CRescueBoxPlatformApp ��ʼ��

BOOL CRescueBoxPlatformApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


// Pro/TOOLKIT����ں���
extern "C" int user_initialize()
{	
	ProError err;
	
	// ������ʼ��
	m_equLibPath.Format(_T("E:\\��������\\1-ģ�黯���\\4-����ʦ������\\3-���Դ����2��\\Library\\Equipment\\Default"));
	m_mechLibPath.Format(_T("E:\\��������\\1-ģ�黯���\\4-����ʦ������\\3-���Դ����2��\\Library\\Mechanism\\Default"));


    // ��Ϣ�ļ�����
    ProFamilyName MsgFile;
    ProStringToWstring(MsgFile, "Menu_Msg.txt");

    // ��Ӳ˵�:Menu
    err = ProMenubarMenuAdd("MenuMain", "Menu", "Help", PRO_B_TRUE, MsgFile);

    // ��Ӳ�����������
    uiCmdCmdId cmd_id1;
    err = ProCmdActionAdd("CmdInsert", InsertEquipment, uiCmdPrioDefault, InsertEquipmentAccess,PRO_B_FALSE, PRO_B_FALSE, &cmd_id1);
	err = ProMenubarmenuPushbuttonAdd("MenuMain", "ButtonInsert", "InsertEquipment", "InsertEquipmentHelp",NULL, PRO_B_TRUE, cmd_id1, MsgFile);
    
	// ��Ӳ����������
    uiCmdCmdId cmd_id2;
    err = ProCmdActionAdd("CmdInsertMechanism", InsertMechanism, uiCmdPrioDefault, InsertMechanismAccess,PRO_B_FALSE, PRO_B_FALSE, &cmd_id2);
	err = ProMenubarmenuPushbuttonAdd("MenuMain", "ButtonInsertMechanism", "InsertMechanism", "InsertMechanismHelp",NULL, PRO_B_TRUE, cmd_id2, MsgFile);

	// ��ӱ༭��������
    uiCmdCmdId cmd_id3;
    err = ProCmdActionAdd("CmdEditMechanism", EditMechanism, uiCmdPrioDefault, EditMechanismAccess,PRO_B_FALSE, PRO_B_FALSE, &cmd_id3);
	err = ProMenubarmenuPushbuttonAdd("MenuMain", "ButtonEditMechanism", "EditMechanism", "EditMechanismHelp",NULL, PRO_B_TRUE, cmd_id3, MsgFile);

	
	return 0;
}

// Pro/TOOLKIT����ʱ���õĺ���
extern "C" void user_terminate()
{}

