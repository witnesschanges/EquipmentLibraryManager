#pragma once
#include "afxwin.h"


// CEquipmentDeleteDialog �Ի���

class CEquipmentDeleteDialog : public CDialog
{
	DECLARE_DYNAMIC(CEquipmentDeleteDialog)

public:
	CEquipmentDeleteDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEquipmentDeleteDialog();

// �Ի�������
	enum { IDD = IDD_EQUIPMENTDELETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_EquipmentName;
	afx_msg void OnBnClickedOk();
	CString m_DeletePath;
};
