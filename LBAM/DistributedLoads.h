///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2012  Washington State Department of Transportation
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
#include "LoadCP.h"
#include "LBAMUtils.h"

typedef CLoadItem<IDistributedLoadItem, IDistributedLoad, &IID_IDistributedLoadItem> CDistributedLoadItem;
class CDistributedLoads;
typedef CLoadCollection<IDistributedLoads, &IID_IDistributedLoads, CDistributedLoads, 
                        IDistributedLoad, IDistributedLoadItem, CDistributedLoadItem, 
                        IEnumDistributedLoad, &IID_IEnumDistributedLoad> DistributedLoadColl_Impl;
/////////////////////////////////////////////////////////////////////////////
// CDistributedLoads
class ATL_NO_VTABLE CDistributedLoads : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDistributedLoads, &CLSID_DistributedLoads>,
	public ISupportErrorInfo,
   public DistributedLoadColl_Impl,
	public IConnectionPointContainerImpl<CDistributedLoads>,
	public CProxyDDistributedLoadsEvents< CDistributedLoads >,
   public IObjectSafetyImpl<CDistributedLoads,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IDistributedLoadEvents
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
   COM_INTERFACE_ENTRY(IDistributedLoadEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDistributedLoads)
CONNECTION_POINT_ENTRY(IID_IDistributedLoadsEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IDistributedLoadEvents
   STDMETHOD(OnDistributedLoadChanged)(/*[in]*/IDistributedLoad* DistributedLoad)
   {
      // Load can be in more than one item
      iterator i(begin());
      iterator iend(end());
      for (; i!=iend; i++)
      {
         CComPtr<IDistributedLoad> pl;
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

// IDistributedLoads
public:

   // virtual duties
   // would like to have all of these functions in the template collection, but
   // inheritance via atl won't allow it.
   void FireAfterAdd(IDistributedLoadItem* pitem)
   {
      Fire_OnDistributedLoadsAdded(pitem);
   }

   void FireBeforeRemove(IDistributedLoadItem* pitem)
   {
      Fire_OnDistributedLoadsBeforeRemove(pitem);
   }

   void FireOnChanged(IDistributedLoadItem* pitem)
   {
      Fire_OnDistributedLoadsChanged(pitem);
   }

   virtual HRESULT MakeConnection(CDistributedLoadItem* pitem)
   {
      return CrAdvise(pitem->m_Load, this, IID_IDistributedLoadEvents, &(pitem->m_LoadCookie));
   }

   virtual HRESULT BreakConnection(CDistributedLoadItem* pitem)
   {
      return CrUnadvise(pitem->m_Load, this, IID_IDistributedLoadEvents, pitem->m_LoadCookie);
   }

   STDMETHOD(FinalRelease)()
   {
      iterator i( begin() );
      iterator iend( end() );
      for (; i!=iend; i++)
      {
         OnBeforeRemove(*i);
      }
      return S_OK;
   }

};

#endif //__DISTRIBUTEDLOADS_H_
