// LibraryManager.h : LibraryManager DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLibraryManagerApp
// �йش���ʵ�ֵ���Ϣ������� LibraryManager.cpp
//

class CLibraryManagerApp : public CWinApp
{
public:
	CLibraryManagerApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
