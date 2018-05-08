// EditMechanismDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include <ProMenuBar.h>
#include <ProAsmcomp.h>
#include <ProModelitem.h>
#include <ProSolid.h>
#include "ProUtil.h"
#include <ProParameter.h>

#include "Rescue Box Platform.h"
#include "EditMechanismDlg.h"


// EditMechanismDlg �Ի���

IMPLEMENT_DYNAMIC(EditMechanismDlg, CDialog)

EditMechanismDlg::EditMechanismDlg(ProModelitem *pComp, CWnd* pParent /*=NULL*/)
	: CDialog(EditMechanismDlg::IDD, pParent)
{
	this->m_pComp = pComp;
}

EditMechanismDlg::~EditMechanismDlg()
{
	ProArrayFree(&p_data);
}

void EditMechanismDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PARAM, m_listCtrlParam);
	DDX_Control(pDX, IDC_EDIT_PARAMNAME, m_paramName);
	DDX_Control(pDX, IDC_EDIT_PARAMVALUE, m_paramValue);
	DDX_Control(pDX, IDC_EDIT_PARAMDESC, m_paramDesc);
}


BEGIN_MESSAGE_MAP(EditMechanismDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PARAM, &EditMechanismDlg::OnLvnItemchangedListParam)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &EditMechanismDlg::OnBnClickedButtonUpdate)
END_MESSAGE_MAP()

// ��������
ProError ParamFilterFn(ProParameter *handle, ProAppData data)
{
	if(wcsncmp(handle->id, _T("RBP_E_"), 6) == 0 )
	{
		return PRO_TK_NO_ERROR;
	}
	else
	{
		return PRO_TK_CONTINUE;
	}
}

// ��������
ProError ParamActionFn(ProParameter *handle, ProError status, ProAppData data)
{
	ProArrayObjectAdd((ProArray *)data, PRO_VALUE_UNUSED, 1, handle);
	return PRO_TK_NO_ERROR;
}


// EditMechanismDlg ��Ϣ�������
BOOL EditMechanismDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ����б������
	m_listCtrlParam.SetExtendedStyle( LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES );
	m_listCtrlParam.InsertColumn(0,_T("���"),LVCFMT_LEFT,40,0);
	m_listCtrlParam.InsertColumn(1,_T("������"),LVCFMT_LEFT,80,0);
	m_listCtrlParam.InsertColumn(2,_T("����ֵ"),LVCFMT_LEFT,80,0);
	m_listCtrlParam.InsertColumn(3,_T("����"),LVCFMT_LEFT,120,0);
	
	ProError res = ProArrayAlloc(0,sizeof(ProParameter),1,&p_data);
	ProParameterVisit(m_pComp, (ProParameterFilter) ParamFilterFn, (ProParameterAction)ParamActionFn, (ProAppData)&p_data);
	
	ProError status;
	int num;
	ProArraySizeGet(p_data, &num);
	for(int i=0; i<num; i++)
	{
		ProParamvalue value;
		ProParameterValueGet(((ProParameter *)p_data)+i,&value);
		
		wchar_t a[32];
		swprintf(a,_T("%d"),i+1);
		m_listCtrlParam.InsertItem(i,a);
		m_listCtrlParam.SetItemText(i,1,((ProParameter *)p_data + i)->id);
		swprintf(a,_T("%.3f"),value.value.d_val);
		m_listCtrlParam.SetItemText(i,2,a);
	}	

	return 0;
}
void EditMechanismDlg::OnLvnItemchangedListParam(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION posi = m_listCtrlParam.GetFirstSelectedItemPosition();
	if(posi != NULL)
	{
		int index = m_listCtrlParam.GetNextSelectedItem(posi);

		ProParameter *paramName = (ProParameter *)p_data + index;
		ProParamvalue paramValue;
		ProParameterValueGet(paramName, &paramValue);
		
		// װ��Edit�ؼ���ֵ
		wchar_t a[32];
		swprintf(a,_T("%s"),paramName->id);
		m_paramName.SetWindowTextW(a);
		swprintf(a,_T("%.3f"),paramValue.value.d_val);
		m_paramValue.SetWindowTextW(a);
	}

	*pResult = 0;
}

void EditMechanismDlg::OnBnClickedButtonUpdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION posi = m_listCtrlParam.GetFirstSelectedItemPosition();
	if(posi != NULL)
	{
		int index = m_listCtrlParam.GetNextSelectedItem(posi);
		ProParameter *paramName = (ProParameter *)p_data + index;
		ProParamvalue paramValue;
		ProParameterValueGet(paramName, &paramValue);

		// �޸Ĳ���
		CString val;
		m_paramValue.GetWindowTextW(val);
		double temp;
		swscanf(val.GetBuffer(val.GetLength()),_T("%lf"),&temp);
		paramValue.value.d_val = temp;
		ProParameterValueSet(paramName, &paramValue);
		
		// �޸��б��ֵ
		wchar_t temp2[32];
		swprintf(temp2,_T("%.3f"),paramValue.value.d_val);
		m_listCtrlParam.SetItemText(index,2,temp2);

		// ����ģ��
		ProMdl mdl;
		ProMdlCurrentGet(&mdl);
		ProSolidRegenerate((ProSolid)mdl, PRO_REGEN_NO_FLAGS);
	}
}
