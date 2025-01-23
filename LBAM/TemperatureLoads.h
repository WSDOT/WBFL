///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2025  Washington State Department of Transportation
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

// TemperatureLoads.h : Declaration of the CTemperatureLoads

#ifndef __TEMPERATURELOADS_H_
#define __TEMPERATURELOADS_H_

#include "resource.h"       // main symbols
#include "LoadCP.h"
#include "LoadCollection.h"
#include "LBAMUtils.h"

using CTemperatureLoadItem = CLoadItem<ITemperatureLoadItem, ITemperatureLoad, &IID_ITemperatureLoadItem>;
class CTemperatureLoads;
using TemperatureLoadColl_Impl = CLoadCollection<ITemperatureLoads, &IID_ITemperatureLoads, CTemperatureLoads, ITemperatureLoad,
                        ITemperatureLoadItem, CTemperatureLoadItem, 
                        IEnumTemperatureLoad, &IID_IEnumTemperatureLoad>;

/////////////////////////////////////////////////////////////////////////////
// CTemperatureLoads
class ATL_NO_VTABLE CTemperatureLoads : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTemperatureLoads, &CLSID_TemperatureLoads>,
	public ISupportErrorInfo,
   public TemperatureLoadColl_Impl,
	public IConnectionPointContainerImpl<CTemperatureLoads>,
	public CProxyDTemperatureLoadsEvents< CTemperatureLoads >,
   public IObjectSafetyImpl<CTemperatureLoads,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ITemperatureLoadEvents
{
public:
	CTemperatureLoads()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TEMPERATURELOADS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTemperatureLoads)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(TemperatureLoadColl_Impl)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ITemperatureLoadEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTemperatureLoads)
CONNECTION_POINT_ENTRY(IID_ITemperatureLoadsEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ITemperatureLoadEvents
   STDMETHOD(OnTemperatureLoadChanged)(/*[in]*/ITemperatureLoad* TemperatureLoad)
   {
      // Load can be in more than one item
      for (iterator i=begin(); i!=end(); i++)
      {
         CComPtr<ITemperatureLoad> pl;
         HRESULT hr = i->get_Load(&pl);
         if (FAILED(hr))
            return hr;

         // it's one of ours, so we should be able to get away with direct Temperatureer compare
         if (pl == TemperatureLoad)
         {
            Fire_OnTemperatureLoadsChanged(*i);
         }
      }

      return S_OK;
   }


// ITemperatureLoads
public:

   // virtual duties
   // would like to have all of these functions in the template collection, but
   // inheritance via atl won't allow it.
   void FireAfterAdd(ITemperatureLoadItem* pitem)
   {
      Fire_OnTemperatureLoadsAdded(pitem);
   }

   void FireBeforeRemove(ITemperatureLoadItem* pitem)
   {
      Fire_OnTemperatureLoadsBeforeRemove(pitem);
   }

   void FireOnChanged(ITemperatureLoadItem* pitem)
   {
      Fire_OnTemperatureLoadsChanged(pitem);
   }

   virtual HRESULT MakeConnection(CTemperatureLoadItem* pitem)
   {
      return CrAdvise(pitem->m_Load, this, IID_ITemperatureLoadEvents, &(pitem->m_LoadCookie));
   }

   virtual HRESULT BreakConnection(CTemperatureLoadItem* pitem)
   {
      return CrUnadvise(pitem->m_Load, this, IID_ITemperatureLoadEvents, pitem->m_LoadCookie);
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

#endif //__TEMPERATURELOADS_H_
