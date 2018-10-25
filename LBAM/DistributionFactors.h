///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// DistributionFactors.h : Declaration of the CDistributionFactors

#ifndef __DISTRIBUTIONFACTORS_H_
#define __DISTRIBUTIONFACTORS_H_

#include "resource.h"       // main symbols
#include <WBFLComCollections.h>
#include "LBAMUtils.h"
#include "LBAMCP.h"

#include "FilteredDfSegmentCollection.h"

class CDistributionFactors;
typedef CComSegmentCollection< IDistributionFactors, IDistributionFactorSegment, IEnumDistributionFactorSegment, &IID_IEnumDistributionFactorSegment,CollectionIndexType > DistributionFactorCollImpl;
typedef CPersistentCollection<CDistributionFactors, DistributionFactorCollImpl,CollectionIndexType> PersistentDistributionFactorCollImpl;
/////////////////////////////////////////////////////////////////////////////
// CDistributionFactors
class ATL_NO_VTABLE CDistributionFactors : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDistributionFactors, &CLSID_DistributionFactors>,
	public ISupportErrorInfo,
   public PersistentDistributionFactorCollImpl,
	public IConnectionPointContainerImpl<CDistributionFactors>,
	public IDistributionFactorSegmentEvents,
   public IObjectSafetyImpl<CDistributionFactors,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDDistributionFactorsEvents< CDistributionFactors >

{
public:
   CDistributionFactors():
   m_IsSymmetrical(VARIANT_FALSE)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DISTRIBUTIONFACTORS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDistributionFactors)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentDistributionFactorCollImpl)
   COM_INTERFACE_ENTRY(IDistributionFactorSegmentEvents)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDistributionFactors)
CONNECTION_POINT_ENTRY(IID_IDistributionFactorsEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IDistributionFactorSegmentEvents
	STDMETHOD(OnDistributionFactorSegmentChanged)();

// IDistributionFactors
   STDMETHOD(get_Length)(/*[in]*/Float64 superstructureLength, /*[out,retval]*/ Float64 *pVal);
   STDMETHOD(GetFactorForLocation)(/*[in]*/Float64 location, /*[in]*/Float64 superstructureLength, /*[out]*/IDistributionFactor** leftLLDF, /*[out]*/IDistributionFactor** rightLLDF);
   STDMETHOD(GetSegmentForLocation)(/*[in]*/Float64 location, /*[in]*/Float64 superstructureLength, /*[out]*/IDistributionFactorSegment** leftSegment, /*[out]*/IDistributionFactorSegment** rightSegment);
   STDMETHOD(GetMemberSegments)(/*[in]*/Float64 superstructureLength, /*[out,retval]*/IFilteredDfSegmentCollection** segments);
   STDMETHOD(Clone)(/*[out,retval]*/IDistributionFactors** clone);
   STDMETHOD(get_IsSymmetrical)(/*[out,retval]*/ VARIANT_BOOL *pVal);
   STDMETHOD(put_IsSymmetrical)(/*[in]*/ VARIANT_BOOL newVal);

public:
   // implementations of virtual functions for collection
   virtual HRESULT OnBeforeAdd( StoredType* pVal)
   {
      CHECK_IN(pVal);
      try
      {
         // set up connection point
         HRESULT hr;
         hr = CrAdvise(pVal->second.m_T, this, IID_IDistributionFactorSegmentEvents, &(pVal->first));
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(0);
         return E_FAIL;
      }
      return S_OK;
   }

   virtual HRESULT OnAfterAdd( StoredType* pVal, CollectionIndexType idx)
   {
      Fire_OnDistributionFactorsAdded(pVal->second.m_T, idx);
      return S_OK;
   }

   virtual HRESULT OnBeforeRemove( StoredType* pVal, CollectionIndexType idx)
   {
      try
      {
         // release connection point
         HRESULT hr;
         hr = CrUnadvise(pVal->second.m_T, this, IID_IDistributionFactorSegmentEvents, pVal->first);
         if (FAILED(hr))
            return hr;
      }
      catch(...)
      {
         ATLASSERT(0);
         return E_FAIL;
      }

      Fire_OnDistributionFactorsBeforeRemove(pVal->second.m_T, idx);

      return S_OK;
   }

   virtual HRESULT OnAfterRemove( CollectionIndexType idx)
   {
      return S_OK; 
   }

   virtual HRESULT OnAfterMoveTo( CollectionIndexType from, CollectionIndexType to)
   {
      Fire_OnDistributionFactorsMoveTo (from, to);
      return S_OK;
   }
   virtual HRESULT OnAfterCopyTo( CollectionIndexType from, CollectionIndexType to)
   {
      Fire_OnDistributionFactorsCopyTo(from, to);
      return S_OK;
   }
   virtual HRESULT OnAfterReverse()
   {
      Fire_OnDistributionFactorsReverse();
      return S_OK;
   }

public:
   virtual void FinalRelease();
   virtual HRESULT FinalConstruct();


   // virtual functions to allow saving properties along with collection
   HRESULT SaveAdditionalProperties(IStructuredSave2 *save)
   {
      HRESULT hr = save->put_Property(CComBSTR("IsSymmetrical"), _variant_t((long)m_IsSymmetrical));
      if (FAILED(hr))
         return hr;

      return S_OK;
   }

   HRESULT LoadAdditionalProperties(IStructuredLoad2 *load)
   {
      _variant_t var;;
      HRESULT hr = load->get_Property(_bstr_t("IsSymmetrical"),&var);
      if (FAILED(hr))
         return hr;

      VARIANT_BOOL vbl = var;
      if (vbl==VARIANT_FALSE)
         m_IsSymmetrical = VARIANT_FALSE;
      else 
         m_IsSymmetrical = VARIANT_TRUE;

      return S_OK;
   }


protected:
   VARIANT_BOOL m_IsSymmetrical;
   STDMETHOD(GetMemberSegments)(Float64 superstructureLength, VARIANT_BOOL isSymmetrical, IFilteredDfSegmentCollection** segments);
   HRESULT LayoutSegments(Float64 layoutLength, Float64 totalLength, CFilteredDfSegmentCollection* pnew_coll);

private:
   // default factor - only create if needed
   CComPtr<IDistributionFactorSegment> m_DefaultFactorSeg;

};

#endif //__DISTRIBUTIONFACTORS_H_
