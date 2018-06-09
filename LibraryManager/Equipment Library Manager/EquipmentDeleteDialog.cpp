// EquipmentDeleteDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Equipment Library Manager.h"
#include "EquipmentDeleteDialog.h"
#include "Equipment Library ManagerDlg.h"
#include "global.h"

// CEquipmentDeleteDialog 对话框

IMPLEMENT_DYNAMIC(CEquipmentDeleteDialog, CDialog)

CEquipmentDeleteDialog::CEquipmentDeleteDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEquipmentDeleteDialog::IDD, pParent)
	, m_EquipmentName(_T(""))
	, m_DeletePath(_T(""))
{
}

CEquipmentDeleteDialog::~CEquipmentDeleteDialog()
{
}

void CEquipmentDeleteDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EquipmentNameEDIT, TransEquipmentName);
	//键盘输入需要删除的器材名
	//DDX_Text(pDX, IDC_EquipmentNameEDIT, m_EquipmentName);
	DDX_Text(pDX, IDC_DELETPATHEDIT, m_DeletePath);
}


BEGIN_MESSAGE_MAP(CEquipmentDeleteDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CEquipmentDeleteDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CEquipmentDeleteDialog 消息处理程序

void CEquipmentDeleteDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	/*UpdateData(TRUE);*/
	//键盘输入需要删除的器材名
	//((CEquipmentLibraryManagerDlg*)GetParent())->m_mEquipmentName = m_EquipmentName;
    //((CEquipmentLibraryManagerDlg*)GetParent())->m_mEquipmentName = TransEquipmentName;

	//删除Property文件夹及其里面的文件
	//CString Path;
	//m_DeletePath = TransPath;
	//Path.Format(_T("E:\\课题学习\\2-模块化设计学习动态-李乔\\3-软件开发例程\\6-器材库管理\\Library\\Equipment\\Default\\Model\\%s\\Property"),m_DeletePath);
	//CFileFind fileFinder;
	//BOOL bFind = fileFinder.FindFile(Path + _T("\\*.*"));
	//while (bFind)
	//{
	//	bFind = fileFinder.FindNextFile();
	//	if (fileFinder.IsDirectory()) //这里可以使用递归进行子文件夹的删除
	//		continue;

	//	CString strFilePath = fileFinder.GetFilePath();
	//	DeleteFile(strFilePath);
	//}
	//::RemoveDirectory(Path);

	//删除器材名对应路径文件夹其里面的文件（注1：暂时无法删除该文件夹；注2：可以考虑用函数来实现这俩个删除文件的步骤）
	//CString Path2;
	//Path2.Format(_T("E:\\课题学习\\2-模块化设计学习动态-李乔\\3-软件开发例程\\6-器材库管理\\Library\\Equipment\\Default\\Model\\%s"),m_DeletePath);
	//CFileFind fileFinder2;
	//BOOL bFind2 = fileFinder2.FindFile(Path2 + _T("\\*.*"));
	//while (bFind2)
	//{
	//	bFind2 = fileFinder2.FindNextFile();
	//	if (fileFinder.IsDirectory()) //这里可以使用递归进行子文件夹的删除
	//		continue;
	//	CString strFilePath = fileFinder2.GetFilePath();
	//	DeleteFile(strFilePath);
	//}
	//::RemoveDirectory(Path2);

	//OnOK();
}
