///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright � 1999-2025  Washington State Department of Transportation
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

// DistributedLoads.h : Declaration of the CDistributedLoads

#ifndef __DISTRIBUTEDLOADS_H_
#define __DISTRIBUTEDLOADS_H_

#include "resource.h"       // main symbols
#include "LoadCollection.h"
#include "LoadingCP.h"
#include "LoadingUtils.h"

using CDistributedLoadItem = CLoadItem<ldIDistributedLoadItem, ldIDistributedLoad, &IID_ldIDistributedLoadItem>;
class CDistributedLoads;
using DistributedLoadColl_Impl = CLoadCollection<ldIDistributedLoads, &IID_ldIDistributedLoads, CDistributedLoads,
                        ldIDistributedLoad, ldIDistributedLoadItem, CDistributedLoadItem, 
                        ldIEnumDistributedLoad, &IID_ldIEnumDistributedLoad>;
/////////////////////////////////////////////////////////////////////////////
// CDistributedLoads
class ATL_NO_VTABLE CDistributedLoads : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDistributedLoads, &CLSID_ldDistributedLoads>,
	public ISupportErrorInfo,
   public DistributedLoadColl_Impl,
	public IConnectionPointContainerImpl<CDistributedLoads>,
	public CProxyDDistributedLoadsEvents< CDistributedLoads >,
   public IObjectSafetyImpl<CDistributedLoads,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ldIDistributedLoadEvents
{
public:
	CDistributedLoads()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DISTRIBUTEDLOADS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDistributedLoads)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(DistributedLoadColl_Impl)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ldIDistributedLoadEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDistributedLoads)
CONNECTION_POINT_ENTRY(IID_ldIDistributedLoadsEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ldIDistributedLoadEvents
   STDMETHOD(OnDistributedLoadChanged)(/*[in]*/ldIDistributedLoad* DistributedLoad) override
   {
      // Load can be in more than one item
      for (iterator i=begin(); i!=end(); i++)
      {
         CComPtr<ldIDistributedLoad> pl;
         HRESULT hr = i->get_Load(&pl);
         if (FAILED(hr))
            return hr;

         // it's one of ours, so we should be able to get away with direct Distributeder compare
         if (pl == DistributedLoad)
         {
            Fire_OnDistributedLoadsChanged(*i);
         }
      }

      return S_OK;
   }

// ldIDistributedLoads
public:

   // virtual duties
   // would like to have all of these functions in the template collection, but
   // inheritance via atl won't allow it.
   void FireAfterAdd(ldIDistributedLoadItem* pitem)
   {
      Fire_OnDistributedLoadsAdded(pitem);
   }

   void FireBeforeRemove(ldIDistributedLoadItem* pitem)
   {
      Fire_OnDistributedLoadsBeforeRemove(pitem);
   }

   void FireOnChanged(ldIDistributedLoadItem* pitem)
   {
      Fire_OnDistributedLoadsChanged(pitem);
   }

   virtual HRESULT MakeConnection(CDistributedLoadItem* pitem) override
   {
      return CrAdvise(pitem->m_Load, this, IID_ldIDistributedLoadEvents, &(pitem->m_LoadCookie));
   } 

   virtual HRESULT BreakConnection(CDistributedLoadItem* pitem) override
   {
      return CrUnadvise(pitem->m_Load, this, IID_ldIDistributedLoadEvents, pitem->m_LoadCookie);
   } 

   void FinalRelease()
   {
      for (iterator i=begin(); i!=end(); i++)
      {
         OnBeforeRemove(*i);
      }
   }

};

#endif //__DISTRIBUTEDLOADS_H_
