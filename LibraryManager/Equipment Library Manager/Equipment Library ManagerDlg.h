
// Equipment Library ManagerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "AccessOperation.h"
#include "afxwin.h"

// CEquipmentLibraryManagerDlg 对话框
class CEquipmentLibraryManagerDlg : public CDialog
{
// 构造
public:
	CEquipmentLibraryManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EQUIPMENTLIBRARYMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 器材列表控件
	CListCtrl m_listEquipment;
	afx_msg void OnLvnItemchangedListEquipment(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listCtrlProp;
	afx_msg void OnTvnItemexpandingTreeLib(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListProp(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeEdit1();
	afx_msg void OnStnClickedListPic();
	//插入或删除器材所需传递变量（非控件变量）的声明（lq）
	CString m_mEquipmentName;  //多出的m代表main（主对话框）
	CString m_mPath;
	CString m_mNodeID;
	CString m_mSortOrder;

	//更新器材所需传递变量（非控件变量）的声明（lq）
	CString m_mOldEquipmentName;
	CString m_mNewEquipmentName;

	//图像列表变量
	CImageList m_imageList;

	//按钮控件
	afx_msg void OnBnClickedInsertbutton();
	afx_msg void OnBnClickedRefreshbutton();
	afx_msg void OnBnClickedDeletebutton();
};
