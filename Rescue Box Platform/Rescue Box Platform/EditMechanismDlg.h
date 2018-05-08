#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

// EditMechanismDlg 对话框

class EditMechanismDlg : public CDialog
{
	DECLARE_DYNAMIC(EditMechanismDlg)

public:
	EditMechanismDlg(ProModelitem *comp, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~EditMechanismDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_EDITMECHANISM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_listCtrlParam;
	ProModelitem *m_pComp;
	ProArray p_data;
	CEdit m_paramName;
	CEdit m_paramValue;
	CEdit m_paramDesc;
	afx_msg void OnLvnItemchangedListParam(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonUpdate();
};
