// POIsAgg.h : Declaration of the CPOIsAgg

#ifndef __POISAGG_H_
#define __POISAGG_H_

#include "resource.h"       // main symbols
#include "LBAM.h"

/////////////////////////////////////////////////////////////////////////////
// CPOIsAgg
class ATL_NO_VTABLE CPOIsAgg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfo,
	public IPOIs
{
public:

	CPOIsAgg()
	{
	}

	~CPOIsAgg()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPOIsAgg)
	COM_INTERFACE_ENTRY(IPOIs)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPOIsAgg)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPOIsAgg
public:
// IPOIs
   STDMETHOD(get_Item)(/*[in]*/long index, /*[out,retval]*/ IPOI* *pVal);
   STDMETHOD(get__NewEnum)(/*[out,retval]*/ IUnknown** retval);  
   STDMETHOD(get_Count)(/*[out,retval]*/ long *pVal);
   STDMETHOD(get__EnumElements)(/*[out,retval]*/ IEnumPOI* *pVal);
   STDMETHOD(Find)(/*[in]*/long id, /*[out,retval]*/IPOI**);
   STDMETHOD(Add)(/*[in]*/IPOI*);
   STDMETHOD(RemoveByID)(/*[in]*/long id);
   STDMETHOD(RemoveByIndex)(/*[in]*/long index, /*[out,retval]*/long* id);
   STDMETHOD(Clone)(/*[out,retval]*/IPOIs**);
   STDMETHOD(Clear)();

   // internal implementation
   CComPtr<IPOIs> m_POIs;
};

#endif //__POIsAgg_H_
