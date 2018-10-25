// InfluenceResultRequests.h : Declaration of the CInfluenceResultRequests

#ifndef __INFLUENCERESULTREQUESTS_H_
#define __INFLUENCERESULTREQUESTS_H_

#include "resource.h"       // main symbols

#include "InfluenceResultRequest.h"
#include "ComCollections.h"
#include "LBAMUtils.h"

class CInfluenceResultRequests;

typedef CComVectorCollection<IInfluenceResultRequests, IInfluenceResultRequest, IEnumInfluenceResultRequest, &IID_IEnumInfluenceResultRequest, &LIBID_WBFLLBAMAnalysis> IFRVectorImpl;
typedef CPersistentCollection<CInfluenceResultRequests, IFRVectorImpl, 1.0,&LIBID_WBFLLBAMAnalysis> PersistentIFRCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CInfluenceResultRequests
class ATL_NO_VTABLE CInfluenceResultRequests : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CInfluenceResultRequests, &CLSID_InfluenceResultRequests>,
	public ISupportErrorInfo,
   public PersistentIFRCollImpl
{
public:
	CInfluenceResultRequests()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_INFLUENCERESULTREQUESTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CInfluenceResultRequests)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY2(IDispatch,IInfluenceResultRequest)
   COM_INTERFACE_ENTRY_CHAIN(PersistentIFRCollImpl)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IInfluenceResultRequests
public:
	STDMETHOD(Clone)(/*[out, retval]*/ ISectionResultRequests** clone)
   {
      // implement to appease template. should never be called
      ATLASSERT(0);
      return E_FAIL;
   }

   virtual HRESULT OnBeforeAdd ( IFRVectorImpl::StoredType* pVal)
   {
      CHECK_IN(pVal);
      return S_OK;
   }

   virtual HRESULT OnBeforeRemove ( IFRVectorImpl::StoredType* pVal, long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterRemove ( long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterAdd ( IFRVectorImpl::ItemType* pVal, long id)
   {
      return S_OK;
   }
};

#endif //__INFLUENCERESULTREQUESTS_H_
