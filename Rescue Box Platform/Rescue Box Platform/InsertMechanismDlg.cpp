// InsertMechanismDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "global.h"

#include "AccessOperation.h"
#include "XMLProc.h"

#include "Rescue Box Platform.h"
#include "InsertMechanismDlg.h"


// InsertMechanismDlg 对话框

IMPLEMENT_DYNAMIC(InsertMechanismDlg, CDialog)

InsertMechanismDlg::InsertMechanismDlg(CWnd* pParent /*=NULL*/)
	: CDialog(InsertMechanismDlg::IDD, pParent),
	  m_accessMag((_bstr_t)m_mechLibPath)
{

}

InsertMechanismDlg::~InsertMechanismDlg()
{
}

void InsertMechanismDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_MECH_TYPE, m_treeCtrlType);
	DDX_Control(pDX, IDC_LIST_MECH_PROP, m_listCtrlProp);
	DDX_Control(pDX, IDC_LIST_MECH_NAME, m_listMechanism);
}


BEGIN_MESSAGE_MAP(InsertMechanismDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_MECH_TYPE, &InsertMechanismDlg::OnTvnSelchangedTreeMechType)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MECH_NAME, &InsertMechanismDlg::OnLvnItemchangedListMechName)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE_MECH_TYPE, &InsertMechanismDlg::OnTvnItemexpandingTreeMechType)
	ON_BN_CLICKED(IDC_BUTTON_MECH_INSERT, &InsertMechanismDlg::OnBnClickedButtonMechInsert)
	ON_BN_CLICKED(IDC_BUTTON_MECH_CANCER, &InsertMechanismDlg::OnBnClickedButtonMechCancer)
END_MESSAGE_MAP()


// InsertMechanismDlg 消息处理程序
BOOL InsertMechanismDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 初始化数据库连接
	m_accessMag.OnInitADOConn();

	// 填充TreeControl控件
	HTREEITEM root = m_treeCtrlType.InsertItem(_T("机构库"),TVI_ROOT,TVI_SORT);	
	m_treeCtrlType.SetItemData(root, 0);
	
	_RecordsetPtr res = m_accessMag.GetRecordSet("SELECT * FROM Menu WHERE ParentID = 0");	
	while(!res->adoEOF)
	{
		CString name = (_bstr_t)res->GetFields()->GetItem("NodeName")->Value;
		HTREEITEM node = m_treeCtrlType.InsertItem(name, root, TVI_SORT);
		m_treeCtrlType.SetItemData(node, _ttoi((LPCTSTR)(_bstr_t)res->GetFields()->GetItem("NodeID")->Value));
		res->MoveNext();
	}
	
	m_treeCtrlType.Expand(root,TVE_TOGGLE);
	

	// 填充机构属性控件
	m_listCtrlProp.InsertColumn(0,_T("属性"),LVCFMT_LEFT,80,0);
	m_listCtrlProp.InsertColumn(1,_T("值"),LVCFMT_LEFT,150,0);

	return 0;
}
void InsertMechanismDlg::OnTvnSelchangedTreeMechType(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	HTREEITEM node = m_treeCtrlType.GetSelectedItem();
	CString sql;
	sql.Format(_T("SELECT * FROM Mechanism WHERE NodeID = %d"), m_treeCtrlType.GetItemData(node));
	_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);
	
	m_listMechanism.DeleteAllItems();
	m_listCtrlProp.DeleteAllItems();
	int i = 0;
	while(!res->adoEOF)
	{
		CString name = (_bstr_t)res->GetFields()->GetItem("MechanismName")->Value;
		m_listMechanism.InsertItem(i++,name);
		m_listMechanism.SetItemData(i-1,_ttoi((LPCTSTR)(_bstr_t)res->GetFields()->GetItem("ID")->Value));
		res->MoveNext();
	}

	*pResult = 0;
}

void InsertMechanismDlg::OnLvnItemchangedListMechName(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	POSITION posi = m_listMechanism.GetFirstSelectedItemPosition();
	if(posi != NULL)
	{
		int index = m_listMechanism.GetNextSelectedItem(posi);
		int id = m_listMechanism.GetItemData(index);

		CString sql;
		sql.Format(_T("SELECT * FROM Mechanism WHERE ID = %d"), id);
		_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);

		m_listCtrlProp.DeleteAllItems();
		int i = 0;
		if(!res->adoEOF)
		{
			CString name = (_bstr_t)res->GetFields()->GetItem("Path")->Value;
			
			// 读取器材的属性
			CString path;
			path.Format(_T("%s\\Model\\%s\\Property\\Basic.xml"),m_mechLibPath,name);
			
			XMLProc xmlProc;
			IXMLDOMDocumentPtr xmlDoc = xmlProc.Read((LPTSTR)(LPCTSTR)path);
			IXMLDOMElement *rootEle = xmlProc.GetReadRoot();
			IXMLDOMNodeList *propNodeList;
			xmlProc.GetChildList(&propNodeList,rootEle);

			IXMLDOMNode* temp;			
			while(propNodeList->nextNode(&temp) == S_OK)
			{				
				BSTR attrName,attrValue;
				xmlProc.GetNodeAttribute(temp,"Tag",&attrName);
				xmlProc.GetText(temp,&attrValue);
				
				m_listCtrlProp.InsertItem(m_listCtrlProp.GetItemCount(),attrName);
				m_listCtrlProp.SetItemText(m_listCtrlProp.GetItemCount()-1,1,attrValue);
			}	

			// 读取预览图
			CString picPath;
			picPath.Format(_T("%s\\Model\\%s\\model.png"),m_mechLibPath,name);			
		}
		
	}

	*pResult = 0;
}

void InsertMechanismDlg::OnTvnItemexpandingTreeMechType(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	HTREEITEM node = pNMTreeView->itemNew.hItem;
	// 删除选中节点下的所有子节点的所有子节点, 重新插入新节点
	HTREEITEM subNode = m_treeCtrlType.GetChildItem(node);
	while(subNode)
	{
		HTREEITEM tempNode = subNode;
		subNode = m_treeCtrlType.GetNextItem(subNode,TVGN_NEXT);

		// 删除节点
		HTREEITEM subSubNode = m_treeCtrlType.GetChildItem(tempNode);
		while(subSubNode)
		{
			HTREEITEM tempSubNode = subSubNode;
			subSubNode = m_treeCtrlType.GetNextItem(subSubNode,TVGN_NEXT);
			m_treeCtrlType.DeleteItem(tempSubNode);
		}
		// 重新插入节点
		CString sql;
		sql.Format(_T("SELECT * FROM Menu WHERE ParentID = %d"), m_treeCtrlType.GetItemData(tempNode));
		_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);	
		while(!res->adoEOF)
		{
			CString name = (_bstr_t)res->GetFields()->GetItem("NodeName")->Value;
			HTREEITEM node = m_treeCtrlType.InsertItem(name, tempNode, TVI_SORT);
			m_treeCtrlType.SetItemData(node, _ttoi((LPCTSTR)(_bstr_t)res->GetFields()->GetItem("NodeID")->Value));
			res->MoveNext();
		}
	}		

	*pResult = 0;
}

void InsertMechanismDlg::OnBnClickedButtonMechInsert()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION posi = m_listMechanism.GetFirstSelectedItemPosition();
	if(posi != NULL)
	{
		int index = m_listMechanism.GetNextSelectedItem(posi);
		m_ID = m_listMechanism.GetItemData(index);		
		
		m_accessMag.ExitConnect();
		CDialog::OnOK();
	}
	else 
	{
		m_accessMag.ExitConnect();
		CDialog::OnCancel();
	}
}

void InsertMechanismDlg::OnBnClickedButtonMechCancer()
{
	// TODO: 在此添加控件通知处理程序代码
	m_accessMag.ExitConnect();
	CDialog::OnCancel();	
}
