#pragma once


// CEquipmentRefreshDialog 对话框

class CEquipmentRefreshDialog : public CDialog
{
	DECLARE_DYNAMIC(CEquipmentRefreshDialog)

public:
	CEquipmentRefreshDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEquipmentRefreshDialog();

// 对话框数据
	enum { IDD = IDD_EQUIPMENTREFRESH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_OldEquipmentName;
	CString m_NewEquipmentName;
	afx_msg void OnBnClickedOk();
};
