// EquipmentRefreshDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Equipment Library Manager.h"
#include "EquipmentRefreshDialog.h"
#include "Equipment Library ManagerDlg.h"


// CEquipmentRefreshDialog 对话框

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


// CEquipmentRefreshDialog 消息处理程序

void CEquipmentRefreshDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	((CEquipmentLibraryManagerDlg*)GetParent())->m_mOldEquipmentName = m_OldEquipmentName;
	((CEquipmentLibraryManagerDlg*)GetParent())->m_mNewEquipmentName = m_NewEquipmentName;
	OnOK();
}
