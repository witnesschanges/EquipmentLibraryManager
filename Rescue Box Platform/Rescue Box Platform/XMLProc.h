#pragma once

#import <msxml6.dll>

class AFX_EXT_CLASS XMLProc 
{
public:
	IXMLDOMDocumentPtr createFile;
	IXMLDOMDocumentPtr readFile;
	IXMLDOMElementPtr createRoot;
	IXMLDOMElementPtr readRoot;
	IXMLDOMProcessingInstructionPtr pPI;
	HRESULT hr;
public:
	XMLProc();
	~XMLProc();
	IXMLDOMDocumentPtr Create(char* rootTag);
	BOOL NewElement(char* tag, char* text, IXMLDOMElement** newNode);
	BOOL NewElement(char* tag, IXMLDOMElement** newNode);
	BOOL AddChild(IXMLDOMElement* childElem, IXMLDOMElement* parentElem);
	BOOL SaveCreateFile(char* dfile);
	IXMLDOMDocumentPtr Read(wchar_t* sfile);
	BOOL SelectElement(char* tag, IXMLDOMElement** node);
	BOOL GetText(IXMLDOMNode *node, BSTR *text);
	BOOL SaveReadFile(char* dfile);
	BOOL ChangeText(IXMLDOMElement* elem, char* text);
	BOOL GetParent(IXMLDOMElement* childElem, IXMLDOMElement** parentElem);
	BOOL GetChild(IXMLDOMElement** childElem, IXMLDOMElement* parentElem);
	BOOL GetChildList(IXMLDOMNodeList** childList, IXMLDOMElement* parentElem);
	BOOL RemoveChild(IXMLDOMElement* childElem, IXMLDOMElement* parentElem);
	BOOL SetAttribute(IXMLDOMElement* node, char* attr, char* value);
	BOOL GetAttribute(IXMLDOMElement* node, char* attr, char* value, int *len);
	BOOL GetNodeAttribute(IXMLDOMNode *node, char *attr, BSTR *value);
	IXMLDOMDocumentPtr GetCreateFile();
	IXMLDOMDocumentPtr GetReadFile();
	IXMLDOMElement* GetCreateRoot();
	IXMLDOMElement* GetReadRoot();
};