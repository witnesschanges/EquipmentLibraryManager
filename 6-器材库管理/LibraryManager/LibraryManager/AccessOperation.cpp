#include "stdafx.h"
#include "AccessOperation.h"

AccessOperation::AccessOperation(void)
{
	TCHAR pFileName[256]; 
	int a = GetCurrentDirectory(256,pFileName);
	m_connString.Format(_T("Provider = Microsoft.ACE.OLEDB.12.0;Data Source= %s\\Library\\Equipment\\Default\\MenuData\\MenuData.mdb"),pFileName);
}

AccessOperation::AccessOperation(wchar_t *path)
{
	m_connString.Format(_T("Provider = Microsoft.ACE.OLEDB.12.0;Data Source= %s\\MenuData\\MenuData.mdb"),path);
}

AccessOperation::~AccessOperation(void)
{}

void AccessOperation::OnInitADOConn()
{
	try
	{
		m_pConnection.CreateInstance(_T("ADODB.Connection"));		
		m_pConnection->Open((_bstr_t)m_connString,"","",adModeUnknown);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
}

void AccessOperation::ExitConnect()
{
	if(m_pRecordset!= NULL)
	{
		m_pRecordset->Close();
	}
	m_pConnection->Close();
}

_RecordsetPtr AccessOperation::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		if(m_pConnection ==NULL)
			OnInitADOConn();
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic, adCmdText);
	}
	catch(_com_error e)
	{
		e.Description();
	}
	return m_pRecordset;
}

BOOL AccessOperation::ExecuteSQL(_bstr_t bstrSQL)
{
	_variant_t RecordsAffected;
	try
	{
		if(m_pConnection ==NULL)
			OnInitADOConn();
		m_pConnection->Execute(bstrSQL,NULL,adCmdText);
		return true;
	}
	catch(_com_error e)
	{
		e.Description();
		return false;
	}
}

