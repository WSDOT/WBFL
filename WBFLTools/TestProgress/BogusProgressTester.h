// BogusProgressTester.h : Declaration of the CBogusProgressTester

#ifndef __BOGUSPROGRESSTESTER_H_
#define __BOGUSPROGRESSTESTER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBogusProgressTester
class ATL_NO_VTABLE CBogusProgressTester : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBogusProgressTester, &CLSID_BogusProgressTester>,
	public ISupportErrorInfo,
	public IDispatchImpl<ISupportProgressMonitor, &IID_ISupportProgressMonitor, &LIBID_TestProgressLib>,
	public IDispatchImpl<IBogusProgressTester, &IID_IBogusProgressTester, &LIBID_TestProgressLib>
{
public:
   CBogusProgressTester():
   m_Cookie(0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BOGUSPROGRESSTESTER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBogusProgressTester)
	COM_INTERFACE_ENTRY(ISupportProgressMonitor)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY2(IDispatch, ISupportProgressMonitor)
	COM_INTERFACE_ENTRY(IBogusProgressTester)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISupportProgressMonitor
public:
	STDMETHOD(InitializeProgressMonitor)(IProgressMonitor* newVal, long cookie);

// IBogusProgressTester
	STDMETHOD(RunTest)();

private:
   bool WasCancelled();

   CComPtr<IProgressMonitor> m_Pm;
   long                      m_Cookie;
};

#endif //__BOGUSPROGRESSTESTER_H_
