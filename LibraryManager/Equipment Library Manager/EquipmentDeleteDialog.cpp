// EquipmentDeleteDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Equipment Library Manager.h"
#include "EquipmentDeleteDialog.h"
#include "Equipment Library ManagerDlg.h"
#include "global.h"

// CEquipmentDeleteDialog �Ի���

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
	//����������Ҫɾ����������
	//DDX_Text(pDX, IDC_EquipmentNameEDIT, m_EquipmentName);
	DDX_Text(pDX, IDC_DELETPATHEDIT, m_DeletePath);
}


BEGIN_MESSAGE_MAP(CEquipmentDeleteDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CEquipmentDeleteDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CEquipmentDeleteDialog ��Ϣ�������

void CEquipmentDeleteDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*UpdateData(TRUE);*/
	//����������Ҫɾ����������
	//((CEquipmentLibraryManagerDlg*)GetParent())->m_mEquipmentName = m_EquipmentName;
    //((CEquipmentLibraryManagerDlg*)GetParent())->m_mEquipmentName = TransEquipmentName;

	//ɾ��Property�ļ��м���������ļ�
	//CString Path;
	//m_DeletePath = TransPath;
	//Path.Format(_T("E:\\����ѧϰ\\2-ģ�黯���ѧϰ��̬-����\\3-�����������\\6-���Ŀ����\\Library\\Equipment\\Default\\Model\\%s\\Property"),m_DeletePath);
	//CFileFind fileFinder;
	//BOOL bFind = fileFinder.FindFile(Path + _T("\\*.*"));
	//while (bFind)
	//{
	//	bFind = fileFinder.FindNextFile();
	//	if (fileFinder.IsDirectory()) //�������ʹ�õݹ�������ļ��е�ɾ��
	//		continue;

	//	CString strFilePath = fileFinder.GetFilePath();
	//	DeleteFile(strFilePath);
	//}
	//::RemoveDirectory(Path);

	//ɾ����������Ӧ·���ļ�����������ļ���ע1����ʱ�޷�ɾ�����ļ��У�ע2�����Կ����ú�����ʵ��������ɾ���ļ��Ĳ��裩
	//CString Path2;
	//Path2.Format(_T("E:\\����ѧϰ\\2-ģ�黯���ѧϰ��̬-����\\3-�����������\\6-���Ŀ����\\Library\\Equipment\\Default\\Model\\%s"),m_DeletePath);
	//CFileFind fileFinder2;
	//BOOL bFind2 = fileFinder2.FindFile(Path2 + _T("\\*.*"));
	//while (bFind2)
	//{
	//	bFind2 = fileFinder2.FindNextFile();
	//	if (fileFinder.IsDirectory()) //�������ʹ�õݹ�������ļ��е�ɾ��
	//		continue;
	//	CString strFilePath = fileFinder2.GetFilePath();
	//	DeleteFile(strFilePath);
	//}
	//::RemoveDirectory(Path2);

	//OnOK();
}
