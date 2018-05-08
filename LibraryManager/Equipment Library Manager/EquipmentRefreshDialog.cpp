// EquipmentRefreshDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Equipment Library Manager.h"
#include "EquipmentRefreshDialog.h"
#include "Equipment Library ManagerDlg.h"


// CEquipmentRefreshDialog �Ի���

IMPLEMENT_DYNAMIC(CEquipmentRefreshDialog, CDialog)

CEquipmentRefreshDialog::CEquipmentRefreshDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEquipmentRefreshDialog::IDD, pParent)
	, m_OldEquipmentName(_T(""))
	, m_NewEquipmentName(_T(""))
{

}

CEquipmentRefreshDialog::~CEquipmentRefreshDialog()
{
}

void CEquipmentRefreshDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OldEquipmentNameEDIT, m_OldEquipmentName);
	DDX_Text(pDX, IDC_NewEquipmentNameEDIT, m_NewEquipmentName);
}


BEGIN_MESSAGE_MAP(CEquipmentRefreshDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CEquipmentRefreshDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CEquipmentRefreshDialog ��Ϣ�������

void CEquipmentRefreshDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE); 
	((CEquipmentLibraryManagerDlg*)GetParent())->m_mOldEquipmentName = m_OldEquipmentName;
	((CEquipmentLibraryManagerDlg*)GetParent())->m_mNewEquipmentName = m_NewEquipmentName;
	OnOK();
}
