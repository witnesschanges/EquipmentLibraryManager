#pragma once


// CEquipmentInsertDialog 对话框

class CEquipmentInsertDialog : public CDialog
{
	DECLARE_DYNAMIC(CEquipmentInsertDialog)

public:
	CEquipmentInsertDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEquipmentInsertDialog();

// 对话框数据
	enum { IDD = IDD_EQUIPMENTINSERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_EquipmentName;
	CString m_Path;
	CString m_NodeID;
	CString m_SortOrder;
	afx_msg void OnBnClickedOk();
};
