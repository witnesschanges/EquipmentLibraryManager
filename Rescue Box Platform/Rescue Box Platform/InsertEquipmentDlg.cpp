// InsertEquipmentDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "global.h"

#include "AccessOperation.h"
#include "XMLProc.h"

#include "Rescue Box Platform.h"
#include "InsertEquipmentDlg.h"


// CInsertEquipmentDlg �Ի���

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


// CInsertEquipmentDlg ��Ϣ�������

BOOL CInsertEquipmentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
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
	
	m_treeCtrlLib.Expand(root,TVE_TOGGLE);
	

	// ����������Կؼ�
	m_listCtrlProp.InsertColumn(0,_T("����"),LVCFMT_LEFT,80,0);
	m_listCtrlProp.InsertColumn(1,_T("ֵ"),LVCFMT_LEFT,150,0);

	return TRUE;
}

void CInsertEquipmentDlg::OnTvnSelchangedTreeLib(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������	

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
			
			// ��ȡ���ĵ�����
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

			// ��ȡԤ��ͼ
			CString picPath;
			picPath.Format(_T("%s\\Model\\%s\\model.png"),m_equLibPath,name);
			
			
		}
		
	}

	*pResult = 0;
}

void CInsertEquipmentDlg::OnTvnItemexpandingTreeLib(NMHDR *pNMHDR, LRESULT *pResult)
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_accessMag.ExitConnect();
	CDialog::OnCancel();	
}
