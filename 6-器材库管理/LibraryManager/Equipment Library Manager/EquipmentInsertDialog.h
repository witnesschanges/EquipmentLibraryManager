#pragma once


// CEquipmentInsertDialog �Ի���

class CEquipmentInsertDialog : public CDialog
{
	DECLARE_DYNAMIC(CEquipmentInsertDialog)

public:
	CEquipmentInsertDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEquipmentInsertDialog();

// �Ի�������
	enum { IDD = IDD_EQUIPMENTINSERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_EquipmentName;
	CString m_Path;
	CString m_NodeID;
	CString m_SortOrder;
	afx_msg void OnBnClickedOk();
};
