#pragma once

#include "AccessOperation.h"
#include "afxcmn.h"
#include "resource.h"

// InsertMechanismDlg 对话框

class InsertMechanismDlg : public CDialog
{
	DECLARE_DYNAMIC(InsertMechanismDlg)

public:
	InsertMechanismDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InsertMechanismDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_INSERTMECHANISM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	AccessOperation m_accessMag;

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_treeCtrlType;
	CListCtrl m_listCtrlProp;

	int m_ID;
	afx_msg void OnTvnSelchangedTreeMechType(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listMechanism;
	afx_msg void OnLvnItemchangedListMechName(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnItemexpandingTreeMechType(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonMechInsert();
	afx_msg void OnBnClickedButtonMechCancer();
};
