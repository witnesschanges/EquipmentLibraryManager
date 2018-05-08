#include "stdafx.h"
#include "XMLProc.h"

XMLProc::XMLProc()
{
	//CoInitialize(NULL);
	createFile = NULL;
	readFile = NULL;
	createRoot = NULL;
	readRoot = NULL;
	pPI = NULL;
}

XMLProc::~XMLProc()
{
	if (readRoot)
		readRoot.Release();
	if (readFile)
		readFile.Release();
	if (createRoot)
		createRoot.Release();
	if (pPI)
		pPI.Release();
	if (createFile)
		createFile.Release();
}


IXMLDOMDocumentPtr XMLProc::Create(char* rootTag)
{
	if (rootTag == NULL)
		return 0;
	hr = createFile.CreateInstance(__uuidof(DOMDocument));
	hr = createFile->createProcessingInstruction( _bstr_t(_T("xml")), _bstr_t(_T("version=\"1.0\" encoding=\"GBK\"")), &pPI );
	//hr = createFile->createProcessingInstruction( _bstr_t(_T("xml")), _bstr_t(_T("version=\"1.0\"")), &pPI );
	hr = createFile->appendChild(pPI, NULL);
	hr = createFile->createElement(_bstr_t(rootTag), &createRoot);
	hr = createFile->appendChild(createRoot, NULL);
	return createFile;
}

IXMLDOMDocumentPtr XMLProc::Read(wchar_t *sfile)
{
	VARIANT_BOOL dl;
	hr = readFile.CreateInstance(__uuidof(DOMDocument));
	hr = readFile->load(_variant_t(sfile), &dl);
	hr = readFile->get_documentElement(&readRoot);
	return readFile;
}

BOOL XMLProc::NewElement(char* tag, char* text, IXMLDOMElement** newNode)
{
	if (createFile == NULL || tag == NULL || text == NULL)
	{
		return FALSE;
	}
	hr = createFile->createElement(_bstr_t(tag), newNode);
	if (hr != S_OK)
		return FALSE;
	(*newNode)->put_text(_bstr_t(text));
	return TRUE;
}



BOOL XMLProc::NewElement(char* tag, IXMLDOMElement** newNode)
{
	if (createFile == NULL || tag == NULL)
	{
		return FALSE;
	}
	hr = createFile->createElement(_bstr_t(tag), newNode);
	if (hr != S_OK)
		return FALSE;
	return TRUE;
}



BOOL XMLProc::SelectElement(char *tag, IXMLDOMElement** node)
{
	char usetag[256 + 2] = "//";
	if (readFile == NULL || tag == NULL || strlen(tag) >= 256)
		return FALSE;
	strcat(usetag, tag);
	hr = readFile->selectSingleNode(_bstr_t(usetag), (IXMLDOMNode**)node);
	if (hr != S_OK)
		return FALSE;
	return TRUE;
}



BOOL XMLProc::GetText(IXMLDOMNode *node, BSTR *text)
{
	if (node == NULL || text == NULL)
		return FALSE;
	hr = node->get_text(text);
	if (hr != S_OK)
		return FALSE;
	else 
	{
		return TRUE;
	}
}



BOOL XMLProc::ChangeText(IXMLDOMElement *elem, char* text)
{
	if (elem == NULL)
		return FALSE;
	hr = elem->put_text(_bstr_t(text));
	if (hr != S_OK)
		return FALSE;
	else 
	{
		return TRUE;
	}
}



BOOL XMLProc::AddChild(IXMLDOMElement* childElem, IXMLDOMElement* parentElem)
{
	if (parentElem == NULL || childElem == NULL)
		return FALSE;
	hr = parentElem->appendChild((IXMLDOMNode*)childElem, NULL);
	if (hr != S_OK)
		return FALSE;
	else
		return TRUE;
}



BOOL XMLProc::GetParent(IXMLDOMElement* childElem, IXMLDOMElement** parentElem)
{
	if (childElem == NULL)
		return FALSE;
	hr = childElem->get_parentNode((IXMLDOMNode**)parentElem);
	if (hr != S_OK)
		return FALSE;
	else
		return TRUE;
}



BOOL XMLProc::GetChild(IXMLDOMElement** childElem, IXMLDOMElement* parentElem)
{
	if (parentElem == NULL)
		return FALSE;
	hr = parentElem->get_firstChild((IXMLDOMNode**)childElem);
	if (hr != S_OK)
		return FALSE;
	else
		return TRUE;
}

BOOL XMLProc::GetChildList(IXMLDOMNodeList** childList, IXMLDOMElement* parentElem)
{
	if (parentElem == NULL)
		return FALSE;
	hr = parentElem->get_childNodes(childList);
	if (hr != S_OK)
		return FALSE;
	else
		return TRUE;
}



BOOL XMLProc::SetAttribute(IXMLDOMElement* node, char* attr, char* value)
{
	if (node == NULL)
	{
		return FALSE;
	}
	hr = node->setAttribute(_bstr_t(attr), _variant_t(value));
	if (hr != S_OK)
		return FALSE;
	else
		return TRUE;
}

BOOL XMLProc::GetAttribute(IXMLDOMElement* node, char* attr, char* value, int *len)
{
	if (node == NULL || attr == NULL)
	{
		return FALSE;
	}

	_variant_t temp;	
	hr = node->getAttribute((_bstr_t)attr, &temp);

	if (hr != S_OK)
		return FALSE;
	else
	{
		BSTR str = (_bstr_t)temp;
		*len = (int)strlen((char *)(_bstr_t)str) > *len ? *len : (int)strlen((char *)(_bstr_t)str);
		strncpy(value,(char *)(_bstr_t)str,*len);
		return TRUE;
	}
}


BOOL XMLProc::GetNodeAttribute(IXMLDOMNode *node, char *attr, BSTR *value)
{
	IXMLDOMNamedNodeMap *nodeMap;
	hr = node-> get_attributes(&nodeMap);

	if(hr != S_OK)
		return FALSE;

	IXMLDOMNode *nodeAttr;
	hr = nodeMap->getNamedItem((_bstr_t)attr,&nodeAttr);
	
	if(hr != S_OK)
		return FALSE;

	hr = nodeAttr->get_text(value);
	
	if(hr != S_OK)
		return FALSE;
	else
	{
		return TRUE;
	}
}



BOOL XMLProc::RemoveChild(IXMLDOMElement* childElem, IXMLDOMElement* parentElem)
{
	if (parentElem == NULL || childElem == NULL)
		return FALSE;
	hr = parentElem->removeChild((IXMLDOMNode*)childElem, NULL);
	if (hr != S_OK)
		return FALSE;
	else
		return TRUE;
}



BOOL XMLProc::SaveCreateFile(char* dfile)
{
	if (createFile == NULL || dfile == NULL)
		return FALSE;
	hr = createFile->save(_variant_t(dfile));
	if (hr != S_OK)
	{
		return FALSE;
	}
	else
		return TRUE;
}



BOOL XMLProc::SaveReadFile(char* dfile)
{
	if (readFile == NULL || dfile == NULL)
		return FALSE;
	hr = readFile->save(_variant_t(dfile));
	if (hr != S_OK)
		return FALSE;
	else
		return TRUE;
}



IXMLDOMDocumentPtr XMLProc::GetCreateFile()
{
	return createFile;
}


IXMLDOMDocumentPtr XMLProc::GetReadFile()
{
	return readFile;
}



IXMLDOMElement* XMLProc::GetCreateRoot()
{
	return createRoot;
}



IXMLDOMElement* XMLProc::GetReadRoot()
{
	return readRoot;
}