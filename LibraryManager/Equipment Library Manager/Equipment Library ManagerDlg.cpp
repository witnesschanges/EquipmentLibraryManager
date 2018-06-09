
// Equipment Library ManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Equipment Library Manager.h"
#include "Equipment Library ManagerDlg.h"
#include "XMLProc.h"
#include "EquipmentInsertDialog.h"
#include "EquipmentDeleteDialog.h"
#include "EquipmentRefreshDialog.h"
#include "global.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CEquipmentLibraryManagerDlg �Ի���




CEquipmentLibraryManagerDlg::CEquipmentLibraryManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEquipmentLibraryManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_libPath.Format(_T("E:\\����ѧϰ\\2-ģ�黯���ѧϰ��̬-����\\3-�����������\\6-���Ŀ����\\Library\\Equipment\\Default"));
	m_accessMag = AccessOperation((_bstr_t)m_libPath);
}

void CEquipmentLibraryManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_LIB, m_treeCtrlLib);
	DDX_Control(pDX, IDC_LIST_EQUIPMENT, m_listEquipment);
	DDX_Control(pDX, IDC_LIST_PROP, m_listCtrlProp);
}

BEGIN_MESSAGE_MAP(CEquipmentLibraryManagerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_LIB, &CEquipmentLibraryManagerDlg::OnTvnSelchangedTreeLib)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EQUIPMENT, &CEquipmentLibraryManagerDlg::OnLvnItemchangedListEquipment)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE_LIB, &CEquipmentLibraryManagerDlg::OnTvnItemexpandingTreeLib)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PROP, &CEquipmentLibraryManagerDlg::OnLvnItemchangedListProp)
	ON_BN_CLICKED(IDC_INSERTBUTTON, &CEquipmentLibraryManagerDlg::OnBnClickedInsertbutton)
	ON_BN_CLICKED(IDC_REFRESHBUTTON, &CEquipmentLibraryManagerDlg::OnBnClickedRefreshbutton)
	ON_BN_CLICKED(IDC_DELETEBUTTON, &CEquipmentLibraryManagerDlg::OnBnClickedDeletebutton)
	ON_BN_CLICKED(IDC_REVISEPROPERTY, &CEquipmentLibraryManagerDlg::OnBnClickedReviseproperty)
	ON_BN_CLICKED(IDC_INSERTCATAGORY, &CEquipmentLibraryManagerDlg::OnBnClickedInsertcatagory)
	ON_BN_CLICKED(IDC_DELETECATAGORY, &CEquipmentLibraryManagerDlg::OnBnClickedDeletecatagory)
END_MESSAGE_MAP()


// CEquipmentLibraryManagerDlg ��Ϣ�������

BOOL CEquipmentLibraryManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//��ӽڵ�ǰ��ͼ��
	HICON hIcon[3];      // ͼ��������  
    hIcon[0] = theApp.LoadIcon(IDI_FIRSTNODE_ICON);// ��������ͼ�꣬�������ǵľ�����浽����     
    hIcon[1] = theApp.LoadIcon(IDI_SECONDNODE_ICON);   
    hIcon[2] = theApp.LoadIcon(IDI_THIRDNODE_ICON); 
    m_imageList.Create(32, 32, ILC_COLOR32, 3, 3);// ����ͼ������CImageList����      
    for (int i=0; i<3; i++)   // ������ͼ����ӵ�ͼ������
    {   
        m_imageList.Add(hIcon[i]);   
    }
	//�������
	CEquipmentLibraryManagerDlg::ContentFill();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CEquipmentLibraryManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEquipmentLibraryManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CEquipmentLibraryManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEquipmentLibraryManagerDlg::OnTvnSelchangedTreeLib(NMHDR *pNMHDR, LRESULT *pResult)  //�������
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������	

	//ѡ����������ˢ�������б����������
	CEquipmentLibraryManagerDlg::RefreshList();
	*pResult = 0;

}

void CEquipmentLibraryManagerDlg::OnLvnItemchangedListEquipment(NMHDR *pNMHDR, LRESULT *pResult)  //�����б��У�
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	POSITION posi = m_listEquipment.GetFirstSelectedItemPosition();  //���б���ͼ�ؼ��л�ȡ��һ��ѡ����б���ͼ���λ��(lq)
	if(posi != NULL)
	{
		//��ȡѡ���������ı�����ֵ�����ݱ���
		CString SelEquipmentName;    // ѡ�����Ե������ַ���   
		NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;   
		if (-1 != pNMListView->iItem)        // ���iItem����-1����˵�����б��ѡ��   
		{   
			// ��ȡ��ѡ���б����һ��������ı�   
			SelEquipmentName = m_listEquipment.GetItemText(pNMListView->iItem, 0);   
			// ����ȡ���ı���ֵ�����ݱ���   
			TransEquipmentName = SelEquipmentName;
		}

		int index = m_listEquipment.GetNextSelectedItem(posi);  //Ϊ�ظ�����ȡ��һ��ѡ����б���ͼ(lq)
		int id = m_listEquipment.GetItemData(index);

		CString sql;
		sql.Format(_T("SELECT * FROM Equipment WHERE ID = %d"), id);
		_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);

		m_listCtrlProp.DeleteAllItems();

		int i = 0;
		if(!res->adoEOF)
		{
			CString name = (_bstr_t)res->GetFields()->GetItem("Path")->Value;
			
			// ��ȡ���ĵ�����
			CString path;
			path.Format(_T("%s\\Model\\%s\\Property\\Basic.xml"),m_libPath,name);
		
			XMLProc xmlProc;
			IXMLDOMDocumentPtr xmlDoc = xmlProc.Read((LPTSTR)(LPCTSTR)path);  //��ȡָ��·���µ�XML�ļ���lq��
			IXMLDOMElement *rootEle = xmlProc.GetReadRoot();  //XML�ĵ��ĸ��ڵ�(lq)
			IXMLDOMNodeList *propNodeList;
			xmlProc.GetChildList(&propNodeList,rootEle);

			IXMLDOMNode* temp;			
			while(propNodeList->nextNode(&temp) == S_OK)
			{				
				BSTR attrName,attrValue;
				xmlProc.GetNodeAttribute(temp,"Tag",&attrName);  //��ȡָ���ڵ�����ԣ�lq��
				xmlProc.GetText(temp,&attrValue);  //��ýڵ�ֵ(lq)
				m_listCtrlProp.InsertItem(m_listCtrlProp.GetItemCount(),attrName);
				m_listCtrlProp.SetItemText(m_listCtrlProp.GetItemCount()-1,1,attrValue);
			}	

			// ��ȡԤ��ͼ
			CString picPath;
			picPath.Format(_T("%s\\Model\\%s\\demo.bmp"),m_libPath,name);
			//��ʾͼƬ
			int cx, cy;
			CImage image;
			CRect rect;
			image.Load(picPath);//����·������ͼƬ
			cx = image.GetWidth();//��ȡͼƬ�Ŀ� �߶�
			cy = image.GetHeight();
			GetDlgItem(IDC_LIST_PIC)->GetWindowRect(&rect);//��ȡPicture Control�ؼ��Ĵ�С
			ScreenToClient(&rect);//���ͻ���ѡ�е��ؼ���ʾ�ľ���������
			GetDlgItem(IDC_LIST_PIC)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);//�����ƶ����ؼ���ʾ������
			CWnd *pWnd = NULL;
			pWnd = GetDlgItem(IDC_LIST_PIC);//��ȡ�ؼ����
			pWnd->GetClientRect(&rect);//��ȡ���ָ��ؼ�����Ĵ�С
			CDC *pDc = NULL;
			pDc	= pWnd->GetDC();//��ȡpicture��DC��������
			image.Draw(pDc->m_hDC, rect);//��ͼƬ���Ƶ�picture��ʾ��������
			ReleaseDC(pDc);
		}
	}

	*pResult = 0;

}

void CEquipmentLibraryManagerDlg::OnTvnItemexpandingTreeLib(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������	

	HTREEITEM node = pNMTreeView->itemNew.hItem;

	// ɾ��ѡ�нڵ��µ������ӽڵ�������ӽڵ�, ���²����½ڵ�
	HTREEITEM subNode = m_treeCtrlLib.GetChildItem(node);
	while(subNode)
	{
		HTREEITEM tempNode = subNode;
		subNode = m_treeCtrlLib.GetNextItem(subNode,TVGN_NEXT);

		// ɾ���ڵ�
		HTREEITEM subSubNode = m_treeCtrlLib.GetChildItem(tempNode);
		while(subSubNode)
		{
			HTREEITEM tempSubNode = subSubNode;
			subSubNode = m_treeCtrlLib.GetNextItem(subSubNode,TVGN_NEXT);
			m_treeCtrlLib.DeleteItem(tempSubNode);
		}
		// ���²���ڵ�
		CString sql;
		sql.Format(_T("SELECT * FROM Menu WHERE ParentID = %d")
			, m_treeCtrlLib.GetItemData(tempNode));
		_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);	
		while(!res->adoEOF)
		{
			CString name = (_bstr_t)res->GetFields()->GetItem("NodeName")->Value;
			HTREEITEM node = m_treeCtrlLib.InsertItem(name, tempNode, TVI_SORT);
			m_treeCtrlLib.SetItemData(node, _ttoi((LPCTSTR)(_bstr_t)res->GetFields()->GetItem("NodeID")->Value));
			res->MoveNext();
		}
	}		


	*pResult = 0;
}

void CEquipmentLibraryManagerDlg::OnBnClickedInsertbutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sql;
	CEquipmentInsertDialog EquipmentInsertDialog;
	EquipmentInsertDialog.DoModal();  //*::DoModal()����ֵֻ������
	sql.Format(_T("INSERT INTO Equipment ( EquipmentName, Path, NodeID, SortOrder )\
		values (\"%s\",\"%s\",\"%s\",\"%s\")")
		,m_mEquipmentName, m_mPath, m_mNodeID, m_mSortOrder); //SQL���
	_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);  //ִ��ACCESS����(lq)
	//�жϻ���
	if (m_mEquipmentName.IsEmpty()||m_mPath.IsEmpty()||m_mNodeID.IsEmpty()
		||m_mSortOrder.IsEmpty())
	{
		AfxMessageBox(_T("�뽫����������Ϣ��д������"));
	}
	else
		AfxMessageBox(_T("��������ĳɹ�"));

	//�½���Ӧ����·�����ļ���
	CString DocStr;
	DocStr.Format(_T("%s\\Model\\%s"),m_libPath,m_mPath);
	CString PropertyDoc;
	PropertyDoc.Format(_T("%s\\Property"),DocStr);
	if (!PathIsDirectory(DocStr)&&!PathIsDirectory(DocStr)) 
	{
		::CreateDirectory(DocStr, NULL);
		::CreateDirectory(PropertyDoc, NULL);
	}
	else if (PathIsDirectory(DocStr)&&!PathIsDirectory(DocStr))
	{
		AfxMessageBox(_T("���и����ֵ�ģ�������ļ��У�������������"));
	}
	else 
		AfxMessageBox(_T("���и����ֵ������ļ��У�������������"));
	//�½�XML�ļ�
	CString XMLPath;
	XMLPath.Format(_T("%s"),PropertyDoc);
	CEquipmentLibraryManagerDlg::CreateXMLFile(XMLPath);
	//���Ԥ���ļ�demo.bmp��lq:�д����ƣ�
	CString SourcePath;
	CString DestinationPath;
	SourcePath.Format(_T("%s\\Model\\demo.bmp"),m_libPath);
	DestinationPath.Format(_T("%s\\demo.bmp"),DocStr);
	CopyFile(LPCWSTR(SourcePath),LPCWSTR(DestinationPath),TRUE);
	//�������֮�����ˢ��
	CEquipmentLibraryManagerDlg::RefreshList();
}

void CEquipmentLibraryManagerDlg::OnBnClickedRefreshbutton() 
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sql;
	CEquipmentRefreshDialog EquipmentRefreshDialog;
	EquipmentRefreshDialog.DoModal();
	sql.Format(_T("UPDATE Equipment SET EquipmentName = \"%s\" WHERE EquipmentName = \"%s\"")
		,m_mNewEquipmentName,m_mOldEquipmentName);
	_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);  //ִ��ACCESS����(lq)
	//�жϻ���
	if (m_mNewEquipmentName.IsEmpty()&&m_mOldEquipmentName.IsEmpty())
	{
		AfxMessageBox(_T("���������������;���������"));
	}
	else if (m_mNewEquipmentName.IsEmpty())
	{
		AfxMessageBox(_T("����������������"));
	}
	else if (m_mOldEquipmentName.IsEmpty())
		{
			AfxMessageBox(_T("���������������"));
		}
	else
			AfxMessageBox(_T("���Ƹ��³ɹ�"));
	//��������֮�����ˢ��
	CEquipmentLibraryManagerDlg::RefreshList();
}

void CEquipmentLibraryManagerDlg::OnBnClickedDeletebutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ѯ��������Ӧ��·��
	CString selsql;
	selsql.Format(_T("SELECT Path FROM Equipment WHERE (EquipmentName=\"%s\")"),TransEquipmentName);
	_RecordsetPtr res1 = m_accessMag.GetRecordSet((_bstr_t)selsql);
	CString Path = (_bstr_t)res1->GetFields()->GetItem("Path")->Value;
	
	//ɾ����������Ӧ������ļ�
	CString DeleteDirectory;
	DeleteDirectory.Format(_T("E:\\����ѧϰ\\2-ģ�黯���ѧϰ��̬-����\\3-�����������\\6-���Ŀ����\\Library\\Equipment\\Default\\Model\\%s"),Path);
	CEquipmentLibraryManagerDlg::DeleteDirectory(DeleteDirectory);
	RemoveDirectory(DeleteDirectory);
 
	//ɾ����������Ӧ��ACCESS���ݿ�����
	CString sql;
	sql.Format(_T("DELETE FROM Equipment WHERE EquipmentName = \"%s\"")
		,TransEquipmentName);
	_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);  //ִ��ACCESS����(lq)
	//�жϻ���
	if (TransEquipmentName.IsEmpty())
	{
		AfxMessageBox(_T("��ѡ����Ҫɾ�������ģ�"));
	}
	else
	AfxMessageBox(_T("ɾ�����ĳɹ�"));
	//ɾ������֮�����ˢ��
	CEquipmentLibraryManagerDlg::RefreshList();
}


//ɾ���ļ�����
void CEquipmentLibraryManagerDlg::DeleteDirectory(CString directory_path)   //ɾ��һ���ļ����µ���������
{   
	CFileFind finder;
	CString path;
	path.Format(_T("%s\\*.*"),directory_path);
	BOOL bWorking = finder.FindFile(path);
	while(bWorking)
	{
		bWorking = finder.FindNextFile();
		if(finder.IsDirectory() && !finder.IsDots())
		{//�����ļ���
			DeleteDirectory(finder.GetFilePath()); //�ݹ�ɾ���ļ���
			RemoveDirectory(finder.GetFilePath());
		}
		else
		{//�����ļ�
			DeleteFile(finder.GetFilePath());
		}
	}
}
//��ָ��·���´���.xml�ļ�(�д��Ľ�)
void CEquipmentLibraryManagerDlg::CreateXMLFile(CString directory_path)
{
	CString pszFileName;
	pszFileName.Format(_T("%s\\Basic.xml"),directory_path);
	CStdioFile myFile;
	CFileException fileException;
	if(myFile.Open(pszFileName,CFile::typeText|CFile::modeCreate|CFile::modeReadWrite|CFile::modeNoTruncate),&fileException)
	{
		CString strOrder;			//����ļ�������򿪣����򴴽�
		strOrder.Format(_T("<?xml version=\"1.0\" encoding=\"GBK\" ?> "));
		myFile.WriteString(strOrder);
		myFile.WriteString(_T("\r\n"));
		myFile.WriteString(_T("\r\n"));
		myFile.WriteString(_T("<Equipment name = \"aa\">"));
		myFile.WriteString(_T("\r\n"));
		myFile.WriteString(_T("	<Name Tag=\"Default\" Type=\"Var\" Desc=\"Default\" ValueType=\"string\">Default</Name>"));
		myFile.WriteString(_T("\r\n"));
		myFile.WriteString(_T("</Equipment>"));
		myFile.Close();
	}
	else
	{
		TRACE("Can't open file %s,error=%u\n",pszFileName,fileException.m_cause);	//�쳣����
	}
}

void CEquipmentLibraryManagerDlg::RefreshList(void)
{
	HTREEITEM node = m_treeCtrlLib.GetSelectedItem();
	CString sql;
    //_T()������������ĳ���֧��Unicode��˫�ֽڷ�ʽ������(lq)
	sql.Format(_T("SELECT * FROM Equipment WHERE NodeID = %d"), m_treeCtrlLib.GetItemData(node));  //SQL���
	_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);  //ִ�в�ѯ����(lq)
	
	m_listEquipment.DeleteAllItems();
	m_listCtrlProp.DeleteAllItems();
	int i = 0;
	while(!res->adoEOF)  //adoEOFʵ�ʾ���EOF��END OF FILE������ʾ�޸������Ͽ�ȡ(lq)
	{
		CString name = (_bstr_t)res->GetFields()->GetItem("EquipmentName")->Value;  //ȡ��EquipmentName�ֶε�ֵ(lq)
		m_listEquipment.InsertItem(i++,name);  //���б�ؼ��������һ������
		m_listEquipment.SetItemData(i-1,_ttoi((LPCTSTR)(_bstr_t)res->GetFields()->GetItem("ID")->Value));  //�������ź���Ҫ�������������lq��
		res->MoveNext();  //������һ����¼
	}
	//����ͼƬ
	CRect rect;
	GetDlgItem(IDC_LIST_PIC)->GetWindowRect(&rect);//��ȡPicture Control�ؼ��Ĵ�С
	InvalidateRect(NULL, true);
}
void CEquipmentLibraryManagerDlg::OnBnClickedReviseproperty()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString selsql;
	selsql.Format(_T("SELECT Path FROM Equipment WHERE (EquipmentName=\"%s\")"),TransEquipmentName);
	_RecordsetPtr res1 = m_accessMag.GetRecordSet((_bstr_t)selsql);
	CString Path = (_bstr_t)res1->GetFields()->GetItem("Path")->Value;
	CString XMLPath;
	XMLPath.Format(_T("%s\\Model\\%s\\Property\\Basic.xml"),m_libPath,Path);
	ShellExecute(NULL, _T("open"),XMLPath, NULL, NULL, SW_SHOW);
	CEquipmentLibraryManagerDlg::RefreshList();//����ø��º�Ч�����ӻ������ԣ�
}

void CEquipmentLibraryManagerDlg::OnBnClickedInsertcatagory()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sql;
	sql.Format(_T("INSERT INTO Menu (NodeID, NodeName, ParentID, SortOrder ) values (\"12\",\"8 ������\",\"0\",\"8\")")
	/*,m_mEquipmentName, m_mPath, m_mNodeID, m_mSortOrder*/);//��Ҫ��NodeID��Ϊ�ֶ�����
	_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);
	CEquipmentLibraryManagerDlg::ContentFill();
	AfxMessageBox(_T("�������ɹ���"));
}

void CEquipmentLibraryManagerDlg::OnBnClickedDeletecatagory()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CEquipmentLibraryManagerDlg::ContentFill(void)
{
	//��֮ǰ���е�����ɾ��
	m_treeCtrlLib.DeleteAllItems();
	m_listEquipment.DeleteAllItems();
	m_listCtrlProp.DeleteAllItems();
	//����ͼƬ
	CRect rect;
	GetDlgItem(IDC_LIST_PIC)->GetWindowRect(&rect);//��ȡPicture Control�ؼ��Ĵ�С
	InvalidateRect(NULL, true);
	m_treeCtrlLib.SetImageList(&m_imageList, TVSIL_NORMAL);// Ϊ���οؼ�����ͼ������
    // ��ʼ�����ݿ�����
	m_accessMag.OnInitADOConn();
	// ���TreeControl�ؼ�
	HTREEITEM root = m_treeCtrlLib.InsertItem(_T("���Ŀ�"),2,2,TVI_ROOT,TVI_SORT);	
	m_treeCtrlLib.SetItemData(root, 0);
	
	_RecordsetPtr res = m_accessMag.GetRecordSet("SELECT * FROM Menu WHERE ParentID = 0");	
	while(!res->adoEOF)
	{
		CString name = (_bstr_t)res->GetFields()->GetItem("NodeName")->Value;
		HTREEITEM node = m_treeCtrlLib.InsertItem(name, root, TVI_SORT);
		m_treeCtrlLib.SetItemData(node, _ttoi((LPCTSTR)(_bstr_t)res->GetFields()->GetItem("NodeID")->Value));
		res->MoveNext();
	}
	m_treeCtrlLib.Expand(root,TVE_TOGGLE);  //��״�ṹ��һ���ó���չ��
	// ����������Կؼ�
	m_listCtrlProp.InsertColumn(0,_T("����"),LVCFMT_LEFT,100,0);
	m_listCtrlProp.InsertColumn(1,_T("ֵ"),LVCFMT_LEFT,200,0);
}

