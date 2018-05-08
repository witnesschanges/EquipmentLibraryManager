// InsertEquipmentDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "global.h"

#include "AccessOperation.h"
#include "XMLProc.h"

#include "Rescue Box Platform.h"
#include "InsertEquipmentDlg.h"


// CInsertEquipmentDlg 对话框

IMPLEMENT_DYNAMIC(CInsertEquipmentDlg, CDialog)

CInsertEquipmentDlg::CInsertEquipmentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertEquipmentDlg::IDD, pParent)
{
	m_accessMag = AccessOperation((_bstr_t)m_equLibPath);
}

CInsertEquipmentDlg::~CInsertEquipmentDlg()
{
}

void CInsertEquipmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_LIB, m_treeCtrlLib);
	DDX_Control(pDX, IDC_LIST_PROP, m_listCtrlProp);
	DDX_Control(pDX, IDC_LIST_EQUIPMENT, m_listEquipment);
}


BEGIN_MESSAGE_MAP(CInsertEquipmentDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_LIB, &CInsertEquipmentDlg::OnTvnSelchangedTreeLib)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EQUIPMENT, &CInsertEquipmentDlg::OnLvnItemchangedListEquipment)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE_LIB, &CInsertEquipmentDlg::OnTvnItemexpandingTreeLib)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CInsertEquipmentDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_CANCER, &CInsertEquipmentDlg::OnBnClickedButtonCancer)
END_MESSAGE_MAP()


// CInsertEquipmentDlg 消息处理程序

BOOL CInsertEquipmentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
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
	
	m_treeCtrlLib.Expand(root,TVE_TOGGLE);
	

	// 填充器材属性控件
	m_listCtrlProp.InsertColumn(0,_T("属性"),LVCFMT_LEFT,80,0);
	m_listCtrlProp.InsertColumn(1,_T("值"),LVCFMT_LEFT,150,0);

	return TRUE;
}

void CInsertEquipmentDlg::OnTvnSelchangedTreeLib(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码	

	HTREEITEM node = m_treeCtrlLib.GetSelectedItem();
	CString sql;
	sql.Format(_T("SELECT * FROM Equipment WHERE NodeID = %d"), m_treeCtrlLib.GetItemData(node));
	_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);
	
	m_listEquipment.DeleteAllItems();
	m_listCtrlProp.DeleteAllItems();
	int i = 0;
	while(!res->adoEOF)
	{
		CString name = (_bstr_t)res->GetFields()->GetItem("EquipmentName")->Value;
		m_listEquipment.InsertItem(i++,name);
		m_listEquipment.SetItemData(i-1,_ttoi((LPCTSTR)(_bstr_t)res->GetFields()->GetItem("ID")->Value));
		res->MoveNext();
	}

	*pResult = 0;
}

void CInsertEquipmentDlg::OnLvnItemchangedListEquipment(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	POSITION posi = m_listEquipment.GetFirstSelectedItemPosition();
	if(posi != NULL)
	{
		int index = m_listEquipment.GetNextSelectedItem(posi);
		int id = m_listEquipment.GetItemData(index);

		CString sql;
		sql.Format(_T("SELECT * FROM Equipment WHERE ID = %d"), id);
		_RecordsetPtr res = m_accessMag.GetRecordSet((_bstr_t)sql);

		m_listCtrlProp.DeleteAllItems();
		int i = 0;
		if(!res->adoEOF)
		{
			CString name = (_bstr_t)res->GetFields()->GetItem("Path")->Value;
			
			// 读取器材的属性
			CString path;
			path.Format(_T("%s\\Model\\%s\\Property\\Basic.xml"),m_equLibPath,name);
			
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
			picPath.Format(_T("%s\\Model\\%s\\model.png"),m_equLibPath,name);
			
			
		}
		
	}

	*pResult = 0;
}

void CInsertEquipmentDlg::OnTvnItemexpandingTreeLib(NMHDR *pNMHDR, LRESULT *pResult)
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
		sql.Format(_T("SELECT * FROM Menu WHERE ParentID = %d"), m_treeCtrlLib.GetItemData(tempNode));
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

void CInsertEquipmentDlg::OnBnClickedButtonInsert()
{
	// TODO: 在此添加控件通知处理程序代码
	
	POSITION posi = m_listEquipment.GetFirstSelectedItemPosition();
	if(posi != NULL)
	{
		int index = m_listEquipment.GetNextSelectedItem(posi);
		m_ID = m_listEquipment.GetItemData(index);		
		
		m_accessMag.ExitConnect();
		CDialog::OnOK();
	}
	else 
	{
		m_accessMag.ExitConnect();
		CDialog::OnCancel();
	}
}

void CInsertEquipmentDlg::OnBnClickedButtonCancer()
{
	// TODO: 在此添加控件通知处理程序代码
	m_accessMag.ExitConnect();
	CDialog::OnCancel();	
}
