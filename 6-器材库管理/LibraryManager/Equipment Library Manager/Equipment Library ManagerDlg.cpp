
// Equipment Library ManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Equipment Library Manager.h"
#include "Equipment Library ManagerDlg.h"
#include "XMLProc.h"
#include "EquipmentInsertDialog.h"
#include "EquipmentDeleteDialog.h"
#include "EquipmentRefreshDialog.h"
 
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
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PROP, &CEquipmentLibraryManagerDlg::OnLvnItemchangedListProp)
	ON_BN_CLICKED(IDC_INSERTBUTTON, &CEquipmentLibraryManagerDlg::OnBnClickedInsertbutton)
	ON_BN_CLICKED(IDC_REFRESHBUTTON, &CEquipmentLibraryManagerDlg::OnBnClickedRefreshbutton)
	ON_BN_CLICKED(IDC_DELETEBUTTON, &CEquipmentLibraryManagerDlg::OnBnClickedDeletebutton)
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

	
	// ��ʼ�����ݿ�����
	m_accessMag.OnInitADOConn();

	// ���TreeControl�ؼ�
	HTREEITEM root = m_treeCtrlLib.InsertItem(_T("���Ŀ�"),TVI_ROOT,TVI_SORT);	
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



	//m_accessMag.ExitConnect();

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

	*pResult = 0;

}

void CEquipmentLibraryManagerDlg::OnLvnItemchangedListEquipment(NMHDR *pNMHDR, LRESULT *pResult)  //�����б��У�
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	POSITION posi = m_listEquipment.GetFirstSelectedItemPosition();  //���б���ͼ�ؼ��л�ȡ��һ��ѡ����б���ͼ���λ��(lq)
	if(posi != NULL)
	{
		int index = m_listEquipment.GetNextSelectedItem(posi);  //Ϊ�ظ�����ȡ��һ��ѡ����б���ͼ(lq)
		int id = m_listEquipment.GetItemData(index);

		CString sql;
		sql.Format(_T("SELECT * FROM Equipment WHERE ID = %d"), id);
		_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);

		m_listCtrlProp.DeleteAllItems();
		//CStatic* pStatic = (CStatic*)GetDlgItem(IDC_LIST_PIC);
		//pStatic->SetBitmap(NULL);  ��ͼƬˢ�µĳ��ԣ�
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


			//CStatic *pStatic=(CStatic *)GetDlgItem(IDC_LIST_PIC);  
			//HBITMAP hBitmap=::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_LIST_PIC5 (Picture Control)));  
			///*���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ������λ����ʾʹ����  */
			///*pStatic->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE); */ 
			///*���þ�̬�ؼ���ʾλͼ*/  
			//pStatic->SetBitmap(hBitmap); 


			//��ʾͼƬ
			int cx, cy;
			CImage	image;
			CRect	rect;
			image.Load(picPath);//����·������ͼƬ
			cx	= image.GetWidth();//��ȡͼƬ�Ŀ� �߶�
			cy	= image.GetHeight();
			GetDlgItem(IDC_LIST_PIC)->GetWindowRect(&rect);//��ȡPicture Control�ؼ��Ĵ�С
			ScreenToClient(&rect);//���ͻ���ѡ�е��ؼ���ʾ�ľ���������
			GetDlgItem(IDC_LIST_PIC)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);//�����ƶ����ؼ���ʾ������
			CWnd *pWnd = NULL;
			pWnd	= GetDlgItem(IDC_LIST_PIC);//��ȡ�ؼ����
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

void CEquipmentLibraryManagerDlg::OnLvnItemchangedListProp(NMHDR *pNMHDR, LRESULT *pResult)  //�����б��ң�
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

}

void CEquipmentLibraryManagerDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
}

void CEquipmentLibraryManagerDlg::OnBnClickedDeletebutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sql;
	CEquipmentDeleteDialog EquipmentDeleteDialog;
	EquipmentDeleteDialog.DoModal();
	sql.Format(_T("DELETE FROM Equipment WHERE EquipmentName = \"%s\"")
		,m_mEquipmentName);
	_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);  //ִ��ACCESS����(lq)
	//�жϻ���
	if (m_mEquipmentName.IsEmpty())
	{
		AfxMessageBox(_T("��ѡ����Ҫɾ�������ģ�"));
	}
	else
	AfxMessageBox(_T("ɾ�����ĳɹ�"));
}
