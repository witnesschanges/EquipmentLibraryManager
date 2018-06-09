#pragma once
#include "afxwin.h"


// CEquipmentDeleteDialog 对话框

class CEquipmentDeleteDialog : public CDialog
{
	DECLARE_DYNAMIC(CEquipmentDeleteDialog)

public:
	CEquipmentDeleteDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEquipmentDeleteDialog();

// 对话框数据
	enum { IDD = IDD_EQUIPMENTDELETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_EquipmentName;
	afx_msg void OnBnClickedOk();
	CString m_DeletePath;
};
