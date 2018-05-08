#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

// EditMechanismDlg �Ի���

class EditMechanismDlg : public CDialog
{
	DECLARE_DYNAMIC(EditMechanismDlg)

public:
	EditMechanismDlg(ProModelitem *comp, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~EditMechanismDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_EDITMECHANISM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
