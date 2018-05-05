
// Equipment Library ManagerDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CEquipmentLibraryManagerDlg 对话框




CEquipmentLibraryManagerDlg::CEquipmentLibraryManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEquipmentLibraryManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_libPath.Format(_T("E:\\课题学习\\2-模块化设计学习动态-李乔\\3-软件开发例程\\6-器材库管理\\Library\\Equipment\\Default"));
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


// CEquipmentLibraryManagerDlg 消息处理程序

BOOL CEquipmentLibraryManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	
	// 初始化数据库连接
	m_accessMag.OnInitADOConn();

	// 填充TreeControl控件
	HTREEITEM root = m_treeCtrlLib.InsertItem(_T("器材库"),TVI_ROOT,TVI_SORT);	
	m_treeCtrlLib.SetItemData(root, 0);
	
	_RecordsetPtr res = m_accessMag.GetRecordSet("SELECT * FROM Menu WHERE ParentID = 0");	
	while(!res->adoEOF)
	{
		CString name = (_bstr_t)res->GetFields()->GetItem("NodeName")->Value;
		HTREEITEM node = m_treeCtrlLib.InsertItem(name, root, TVI_SORT);
		m_treeCtrlLib.SetItemData(node, _ttoi((LPCTSTR)(_bstr_t)res->GetFields()->GetItem("NodeID")->Value));
		res->MoveNext();
	}
	
	m_treeCtrlLib.Expand(root,TVE_TOGGLE);  //树状结构第一层用程序展开
	

	// 填充器材属性控件
	m_listCtrlProp.InsertColumn(0,_T("属性"),LVCFMT_LEFT,100,0);
	m_listCtrlProp.InsertColumn(1,_T("值"),LVCFMT_LEFT,200,0);



	//m_accessMag.ExitConnect();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEquipmentLibraryManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEquipmentLibraryManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEquipmentLibraryManagerDlg::OnTvnSelchangedTreeLib(NMHDR *pNMHDR, LRESULT *pResult)  //器材类别
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码	

	HTREEITEM node = m_treeCtrlLib.GetSelectedItem();
	CString sql;
    //_T()的作用是让你的程序支持Unicode（双字节方式）编码(lq)
	sql.Format(_T("SELECT * FROM Equipment WHERE NodeID = %d"), m_treeCtrlLib.GetItemData(node));  //SQL语句
	_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);  //执行查询操作(lq)
	
	m_listEquipment.DeleteAllItems();
	m_listCtrlProp.DeleteAllItems();

	int i = 0;
	while(!res->adoEOF)  //adoEOF实际就是EOF（END OF FILE），表示无更多资料可取(lq)
	{
		CString name = (_bstr_t)res->GetFields()->GetItem("EquipmentName")->Value;  //取得EquipmentName字段的值(lq)
		m_listEquipment.InsertItem(i++,name);  //在列表控件里面插入一个新行
		m_listEquipment.SetItemData(i-1,_ttoi((LPCTSTR)(_bstr_t)res->GetFields()->GetItem("ID")->Value));  //各项的序号和需要的内容相关联（lq）
		res->MoveNext();  //进入下一条记录
	}

	*pResult = 0;

}

void CEquipmentLibraryManagerDlg::OnLvnItemchangedListEquipment(NMHDR *pNMHDR, LRESULT *pResult)  //器材列表（中）
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	POSITION posi = m_listEquipment.GetFirstSelectedItemPosition();  //在列表视图控件中获取第一个选择的列表视图项的位置(lq)
	if(posi != NULL)
	{
		int index = m_listEquipment.GetNextSelectedItem(posi);  //为重复而获取下一个选择的列表视图(lq)
		int id = m_listEquipment.GetItemData(index);

		CString sql;
		sql.Format(_T("SELECT * FROM Equipment WHERE ID = %d"), id);
		_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);

		m_listCtrlProp.DeleteAllItems();
		//CStatic* pStatic = (CStatic*)GetDlgItem(IDC_LIST_PIC);
		//pStatic->SetBitmap(NULL);  （图片刷新的尝试）
		int i = 0;
		if(!res->adoEOF)
		{
			CString name = (_bstr_t)res->GetFields()->GetItem("Path")->Value;
			
			// 读取器材的属性
			CString path;
			path.Format(_T("%s\\Model\\%s\\Property\\Basic.xml"),m_libPath,name);
			
			XMLProc xmlProc;
			IXMLDOMDocumentPtr xmlDoc = xmlProc.Read((LPTSTR)(LPCTSTR)path);  //读取指定路径下的XML文件（lq）
			IXMLDOMElement *rootEle = xmlProc.GetReadRoot();  //XML文档的根节点(lq)
			IXMLDOMNodeList *propNodeList;
			xmlProc.GetChildList(&propNodeList,rootEle);

			IXMLDOMNode* temp;			
			while(propNodeList->nextNode(&temp) == S_OK)
			{				
				BSTR attrName,attrValue;
				xmlProc.GetNodeAttribute(temp,"Tag",&attrName);  //读取指定节点的属性（lq）
				xmlProc.GetText(temp,&attrValue);  //获得节点值(lq)
				
				m_listCtrlProp.InsertItem(m_listCtrlProp.GetItemCount(),attrName);
				m_listCtrlProp.SetItemText(m_listCtrlProp.GetItemCount()-1,1,attrValue);
			}	

			// 读取预览图
			CString picPath;
			picPath.Format(_T("%s\\Model\\%s\\demo.bmp"),m_libPath,name);


			//CStatic *pStatic=(CStatic *)GetDlgItem(IDC_LIST_PIC);  
			//HBITMAP hBitmap=::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_LIST_PIC5 (Picture Control)));  
			///*设置静态控件的样式，使其可以使用位图，并试位标显示使居中  */
			///*pStatic->ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE); */ 
			///*设置静态控件显示位图*/  
			//pStatic->SetBitmap(hBitmap); 


			//显示图片
			int cx, cy;
			CImage	image;
			CRect	rect;
			image.Load(picPath);//根据路径载入图片
			cx	= image.GetWidth();//获取图片的宽 高度
			cy	= image.GetHeight();
			GetDlgItem(IDC_LIST_PIC)->GetWindowRect(&rect);//获取Picture Control控件的大小
			ScreenToClient(&rect);//将客户区选中到控件表示的矩形区域内
			GetDlgItem(IDC_LIST_PIC)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);//窗口移动到控件表示的区域
			CWnd *pWnd = NULL;
			pWnd	= GetDlgItem(IDC_LIST_PIC);//获取控件句柄
			pWnd->GetClientRect(&rect);//获取句柄指向控件区域的大小
			CDC *pDc = NULL;
			pDc	= pWnd->GetDC();//获取picture的DC（画布）
			image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内
			ReleaseDC(pDc);
		}
	}

	*pResult = 0;

}

void CEquipmentLibraryManagerDlg::OnTvnItemexpandingTreeLib(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码	

	HTREEITEM node = pNMTreeView->itemNew.hItem;

	// 删除选中节点下的所有子节点的所有子节点, 重新插入新节点
	HTREEITEM subNode = m_treeCtrlLib.GetChildItem(node);
	while(subNode)
	{
		HTREEITEM tempNode = subNode;
		subNode = m_treeCtrlLib.GetNextItem(subNode,TVGN_NEXT);

		// 删除节点
		HTREEITEM subSubNode = m_treeCtrlLib.GetChildItem(tempNode);
		while(subSubNode)
		{
			HTREEITEM tempSubNode = subSubNode;
			subSubNode = m_treeCtrlLib.GetNextItem(subSubNode,TVGN_NEXT);
			m_treeCtrlLib.DeleteItem(tempSubNode);
		}
		// 重新插入节点
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

void CEquipmentLibraryManagerDlg::OnLvnItemchangedListProp(NMHDR *pNMHDR, LRESULT *pResult)  //器材列表（右）
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

}

void CEquipmentLibraryManagerDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CEquipmentLibraryManagerDlg::OnBnClickedInsertbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sql;
	CEquipmentInsertDialog EquipmentInsertDialog;
	EquipmentInsertDialog.DoModal();  //*::DoModal()返回值只有俩个
	sql.Format(_T("INSERT INTO Equipment ( EquipmentName, Path, NodeID, SortOrder )\
		values (\"%s\",\"%s\",\"%s\",\"%s\")")
		,m_mEquipmentName, m_mPath, m_mNodeID, m_mSortOrder); //SQL语句
	_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);  //执行ACCESS操作(lq)
	//判断机制
	if (m_mEquipmentName.IsEmpty()||m_mPath.IsEmpty()||m_mNodeID.IsEmpty()
		||m_mSortOrder.IsEmpty())
	{
		AfxMessageBox(_T("请将插入器材信息填写完整！"));
	}
	else
		AfxMessageBox(_T("添加新器材成功"));
}

void CEquipmentLibraryManagerDlg::OnBnClickedRefreshbutton() 
{
	// TODO: 在此添加控件通知处理程序代码
	CString sql;
	CEquipmentRefreshDialog EquipmentRefreshDialog;
	EquipmentRefreshDialog.DoModal();
	sql.Format(_T("UPDATE Equipment SET EquipmentName = \"%s\" WHERE EquipmentName = \"%s\"")
		,m_mNewEquipmentName,m_mOldEquipmentName);
	_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);  //执行ACCESS操作(lq)
	//判断机制
	if (m_mNewEquipmentName.IsEmpty()&&m_mOldEquipmentName.IsEmpty())
	{
		AfxMessageBox(_T("请输入新器材名和旧器材名！"));
	}
	else if (m_mNewEquipmentName.IsEmpty())
	{
		AfxMessageBox(_T("请输入新器材名！"));
	}
	else if (m_mOldEquipmentName.IsEmpty())
		{
			AfxMessageBox(_T("请输入旧器材名！"));
		}
	else
			AfxMessageBox(_T("名称更新成功"));
}

void CEquipmentLibraryManagerDlg::OnBnClickedDeletebutton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sql;
	CEquipmentDeleteDialog EquipmentDeleteDialog;
	EquipmentDeleteDialog.DoModal();
	sql.Format(_T("DELETE FROM Equipment WHERE EquipmentName = \"%s\"")
		,m_mEquipmentName);
	_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);  //执行ACCESS操作(lq)
	//判断机制
	if (m_mEquipmentName.IsEmpty())
	{
		AfxMessageBox(_T("请选择想要删除的器材！"));
	}
	else
	AfxMessageBox(_T("删除器材成功"));
}
