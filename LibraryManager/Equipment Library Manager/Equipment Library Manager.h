
// Equipment Library Manager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEquipmentLibraryManagerApp:
// �йش����ʵ�֣������ Equipment Library Manager.cpp
//

class CEquipmentLibraryManagerApp : public CWinAppEx
{
public:
	CEquipmentLibraryManagerApp();

// ��д
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEquipmentLibraryManagerApp theApp;