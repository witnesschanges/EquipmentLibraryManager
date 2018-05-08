
// Equipment Library ManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "AccessOperation.h"
#include "afxwin.h"

// CEquipmentLibraryManagerDlg �Ի���
class CEquipmentLibraryManagerDlg : public CDialog
{
// ����
public:
	CEquipmentLibraryManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EQUIPMENTLIBRARYMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_treeCtrlLib;
private:
	AccessOperation m_accessMag;
	CString m_libPath;
public:
	afx_msg void OnTvnSelchangedTreeLib(NMHDR *pNMHDR, LRESULT *pResult);
	// �����б�ؼ�
	CListCtrl m_listEquipment;
	afx_msg void OnLvnItemchangedListEquipment(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listCtrlProp;
	afx_msg void OnTvnItemexpandingTreeLib(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListProp(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeEdit1();
	afx_msg void OnStnClickedListPic();
	//�����ɾ���������贫�ݱ������ǿؼ���������������lq��
	CString m_mEquipmentName;  //�����m����main�����Ի���
	CString m_mPath;
	CString m_mNodeID;
	CString m_mSortOrder;

	//�����������贫�ݱ������ǿؼ���������������lq��
	CString m_mOldEquipmentName;
	CString m_mNewEquipmentName;

	//ͼ���б����
	CImageList m_imageList;

	//��ť�ؼ�
	afx_msg void OnBnClickedInsertbutton();
	afx_msg void OnBnClickedRefreshbutton();
	afx_msg void OnBnClickedDeletebutton();
};
