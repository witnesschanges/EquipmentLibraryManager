#pragma once


// CEquipmentRefreshDialog �Ի���

class CEquipmentRefreshDialog : public CDialog
{
	DECLARE_DYNAMIC(CEquipmentRefreshDialog)

public:
	CEquipmentRefreshDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEquipmentRefreshDialog();

// �Ի�������
	enum { IDD = IDD_EQUIPMENTREFRESH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_OldEquipmentName;
	CString m_NewEquipmentName;
	afx_msg void OnBnClickedOk();
};
