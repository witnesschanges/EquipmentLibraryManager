#pragma once

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

class AFX_EXT_CLASS AccessOperation
{
public:
	AccessOperation(void);
	AccessOperation(wchar_t *path);
	~AccessOperation(void);

	BOOL ExecuteSQL(_bstr_t bstrSQL);
	_RecordsetPtr GetRecordSet(_bstr_t bstrSQL);
	void ExitConnect();
	void OnInitADOConn();
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
protected:
	CString m_connString;
};
