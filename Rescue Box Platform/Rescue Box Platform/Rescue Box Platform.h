// Rescue Box Platform.h : Rescue Box Platform DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRescueBoxPlatformApp
// �йش���ʵ�ֵ���Ϣ������� Rescue Box Platform.cpp
//

class CRescueBoxPlatformApp : public CWinApp
{
public:
	CRescueBoxPlatformApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
