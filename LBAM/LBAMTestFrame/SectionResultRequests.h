// SectionResultRequests.h : Declaration of the CSectionResultRequests

#ifndef __SECTIONRESULTREQUESTS_H_
#define __SECTIONRESULTREQUESTS_H_

#include "resource.h"       // main symbols

#include "SectionResultRequest.h"
#include <WBFLComCollections.h>
#include "LBAMUtils.h"

class CSectionResultRequests;

typedef CComVectorCollection<ISectionResultRequests, ISectionResultRequest, IEnumSectionResultRequest, &IID_IEnumSectionResultRequest, &LIBID_WBFLLBAMAnalysis> SFRVectorImpl;
typedef CPersistentCollection<CSectionResultRequests, SFRVectorImpl, 1.0,&LIBID_WBFLLBAMAnalysis> PersistentSFRCollImpl;


/////////////////////////////////////////////////////////////////////////////
// CSectionResultRequests
class ATL_NO_VTABLE CSectionResultRequests : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSectionResultRequests, &CLSID_SectionResultRequests>,
	public ISupportErrorInfo,
   public PersistentSFRCollImpl
{
public:
	CSectionResultRequests() 
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SECTIONRESULTREQUESTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSectionResultRequests)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY2(IDispatch,ISectionResultRequests)
   COM_INTERFACE_ENTRY_CHAIN(PersistentSFRCollImpl)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISectionResultRequests
public:


	STDMETHOD(Clone)(/*[out, retval]*/ ISectionResultRequests** clone)
   {
      // implement to appease template. should never be called
      ATLASSERT(0);
      return E_FAIL;
   }


   virtual HRESULT OnBeforeAdd ( SFRVectorImpl::StoredType* pVal)
   {
      CHECK_IN(pVal);
      return S_OK;
   }

   virtual HRESULT OnBeforeRemove ( SFRVectorImpl::StoredType* pVal, long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterRemove ( long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterAdd ( SFRVectorImpl::ItemType* pVal, long id)
   {
      return S_OK;
   }


};

#endif //__SectionResultRequestS_H_
