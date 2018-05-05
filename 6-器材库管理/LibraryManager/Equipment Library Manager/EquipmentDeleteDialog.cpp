// EquipmentDeleteDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Equipment Library Manager.h"
#include "EquipmentDeleteDialog.h"
#include "Equipment Library ManagerDlg.h"

// CEquipmentDeleteDialog 对话框

IMPLEMENT_DYNAMIC(CEquipmentDeleteDialog, CDialog)

CEquipmentDeleteDialog::CEquipmentDeleteDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEquipmentDeleteDialog::IDD, pParent)
	, m_EquipmentName(_T(""))
{

}

CEquipmentDeleteDialog::~CEquipmentDeleteDialog()
{
}

void CEquipmentDeleteDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EquipmentNameEDIT, m_EquipmentName);
}


BEGIN_MESSAGE_MAP(CEquipmentDeleteDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CEquipmentDeleteDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CEquipmentDeleteDialog 消息处理程序

void CEquipmentDeleteDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);  
    ((CEquipmentLibraryManagerDlg*)GetParent())->m_mEquipmentName = m_EquipmentName;
	OnOK();
}
