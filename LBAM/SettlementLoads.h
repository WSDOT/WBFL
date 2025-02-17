///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
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

// SettlementLoads.h : Declaration of the CSettlementLoads

#ifndef __SETTLEMENTLOADS_H_
#define __SETTLEMENTLOADS_H_

#include "resource.h"       // main symbols
#include "LoadCP.h"
#include "LoadCollection.h"
#include "LBAMUtils.h"

using CSettlementLoadItem = CLoadItem<ISettlementLoadItem, ISettlementLoad, &IID_ISettlementLoadItem>;
class CSettlementLoads;
using SettlementLoadColl_Impl = CLoadCollection<ISettlementLoads, &IID_ISettlementLoads, CSettlementLoads, ISettlementLoad,
                        ISettlementLoadItem, CSettlementLoadItem, 
                        IEnumSettlementLoad, &IID_IEnumSettlementLoad>;

/////////////////////////////////////////////////////////////////////////////
// CSettlementLoads
class ATL_NO_VTABLE CSettlementLoads : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSettlementLoads, &CLSID_SettlementLoads>,
	public ISupportErrorInfo,
   public SettlementLoadColl_Impl,
	public IConnectionPointContainerImpl<CSettlementLoads>,
	public CProxyDSettlementLoadsEvents< CSettlementLoads >,
   public IObjectSafetyImpl<CSettlementLoads,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISettlementLoadEvents
{
public:
	CSettlementLoads()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SETTLEMENTLOADS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSettlementLoads)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(SettlementLoadColl_Impl)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ISettlementLoadEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSettlementLoads)
CONNECTION_POINT_ENTRY(IID_ISettlementLoadsEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISettlementLoadEvents
   STDMETHOD(OnSettlementLoadChanged)(/*[in]*/ISettlementLoad* SettlementLoad)
   {
      // Load can be in more than one item
      for (iterator i=begin(); i!=end(); i++)
      {
         CComPtr<ISettlementLoad> pl;
         HRESULT hr = i->get_Load(&pl);
         if (FAILED(hr))
            return hr;

         // it's one of ours, so we should be able to get away with direct Settlementer compare
         if (pl == SettlementLoad)
         {
            Fire_OnSettlementLoadsChanged(*i);
         }
      }

      return S_OK;
   }


// ISettlementLoads
public:

   // virtual duties
   // would like to have all of these functions in the template collection, but
   // inheritance via atl won't allow it.
   void FireAfterAdd(ISettlementLoadItem* pitem)
   {
      Fire_OnSettlementLoadsAdded(pitem);
   }

   void FireBeforeRemove(ISettlementLoadItem* pitem)
   {
      Fire_OnSettlementLoadsBeforeRemove(pitem);
   }

   void FireOnChanged(ISettlementLoadItem* pitem)
   {
      Fire_OnSettlementLoadsChanged(pitem);
   }

   virtual HRESULT MakeConnection(CSettlementLoadItem* pitem)
   {
      return CrAdvise(pitem->m_Load, this, IID_ISettlementLoadEvents, &(pitem->m_LoadCookie));
   }

   virtual HRESULT BreakConnection(CSettlementLoadItem* pitem)
   {
      return CrUnadvise(pitem->m_Load, this, IID_ISettlementLoadEvents, pitem->m_LoadCookie);
   }

   STDMETHOD(FinalRelease)()
   {
      for (iterator i=begin(); i!=end(); i++)
      {
         OnBeforeRemove(*i);
      }
      return S_OK;
   }
};

#endif //__SETTLEMENTLOADS_H_
