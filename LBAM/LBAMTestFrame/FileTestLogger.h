// FileTestLogger.h : Declaration of the CFileTestLogger

#ifndef __FILETESTLOGGER_H_
#define __FILETESTLOGGER_H_

#include "resource.h"       // main symbols
#include <fstream>
/////////////////////////////////////////////////////////////////////////////
// CFileTestLogger
class ATL_NO_VTABLE CFileTestLogger : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFileTestLogger, &CLSID_FileTestLogger>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CFileTestLogger>,
	public IDispatchImpl<IFileTestLogger, &IID_IFileTestLogger, &LIBID_WBFLLBAMTESTFRAMELib>
{
public:
   CFileTestLogger():
   m_TotalTests(0),
   m_FailedTests(0) 
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FILETESTLOGGER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFileTestLogger)
	COM_INTERFACE_ENTRY(IFileTestLogger)
	COM_INTERFACE_ENTRY2(IDispatch,IFileTestLogger)
	COM_INTERFACE_ENTRY(ITestLogger)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CFileTestLogger)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFileTestLogger
public:
	STDMETHOD(Close)();
	STDMETHOD(Open)(/*[in]*/BSTR FileName);
	STDMETHOD(get_FileName)(/*[out, retval]*/ BSTR *pVal);

// ITestLogger
	STDMETHOD(get_TotalTests)(/*[out, retval]*/ long *pVal);
   STDMETHOD(get_TotalFails)(/*[out, retval]*/ long *pVal);
	STDMETHOD(AddTestEntry)(/*[in]*/TestResult result, /*[in]*/BSTR message);
	STDMETHOD(AddDescriptionEntry)(/*[in]*/BSTR description);

private:
   CComBSTR m_FileName;
   long     m_TotalTests;
   long     m_FailedTests;

   std::ofstream m_Stream;

};

#endif //__FILETESTLOGGER_H_
