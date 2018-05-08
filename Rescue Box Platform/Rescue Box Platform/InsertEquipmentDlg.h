#pragma once

#include "AccessOperation.h"
#include "afxcmn.h"
#include "resource.h"

// CInsertEquipmentDlg �Ի���

class CInsertEquipmentDlg : public CDialog
{
	DECLARE_DYNAMIC(CInsertEquipmentDlg)

public:
	CInsertEquipmentDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInsertEquipmentDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_INSERTEQUIPMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()	

protected:
	AccessOperation m_accessMag;
	virtual BOOL OnInitDialog();
public:
	CTreeCtrl m_treeCtrlLib;
	CListCtrl m_listCtrlProp;
	afx_msg void OnTvnSelchangedTreeLib(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listEquipment;
	afx_msg void OnLvnItemchangedListEquipment(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnItemexpandingTreeLib(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonCancer();

	int m_ID;
};
