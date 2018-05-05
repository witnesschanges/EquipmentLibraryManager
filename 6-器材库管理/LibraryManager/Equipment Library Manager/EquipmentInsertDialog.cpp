// EquipmentInsertDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Equipment Library Manager.h"
#include "EquipmentInsertDialog.h"
#include "Equipment Library ManagerDlg.h"

// CEquipmentInsertDialog �Ի���

IMPLEMENT_DYNAMIC(CEquipmentInsertDialog, CDialog)

CEquipmentInsertDialog::CEquipmentInsertDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEquipmentInsertDialog::IDD, pParent)
	, m_EquipmentName(_T(""))
	, m_Path(_T(""))
	, m_NodeID(_T(""))
	, m_SortOrder(_T(""))
{

}

CEquipmentInsertDialog::~CEquipmentInsertDialog()
{
}

void CEquipmentInsertDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EquipmentNameEDIT, m_EquipmentName);
	DDX_Text(pDX, IDC_PathEDIT, m_Path);
	DDX_Text(pDX, IDC_NodeIDEDIT, m_NodeID);
	DDX_Text(pDX, IDC_SortOderEDIT, m_SortOrder);
}


BEGIN_MESSAGE_MAP(CEquipmentInsertDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CEquipmentInsertDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CEquipmentInsertDialog ��Ϣ�������


void CEquipmentInsertDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);  
    ((CEquipmentLibraryManagerDlg*)GetParent())->m_mEquipmentName = m_EquipmentName;
	((CEquipmentLibraryManagerDlg*)GetParent())->m_mPath = m_Path;  
	((CEquipmentLibraryManagerDlg*)GetParent())->m_mNodeID = m_NodeID;  
	((CEquipmentLibraryManagerDlg*)GetParent())->m_mSortOrder = m_SortOrder;  
	OnOK();
}
