///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2021  Washington State Department of Transportation
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

// PointLoads.h : Declaration of the CPointLoads

#ifndef __POINTLOADS_H_
#define __POINTLOADS_H_

#include "resource.h"       // main symbols
#include "LoadCollection.h"
#include "LoadCP.h"
#include "LBAMUtils.h"

typedef CLoadItem<IPointLoadItem, IPointLoad, &IID_IPointLoadItem> CPointLoadItem;
class CPointLoads;
typedef CLoadCollection<IPointLoads, &IID_IPointLoads, CPointLoads, IPointLoad, 
                        IPointLoadItem, CPointLoadItem, 
                        IEnumPointLoad, &IID_IEnumPointLoad> PointLoadColl_Impl;


/////////////////////////////////////////////////////////////////////////////
// CPointLoads
class ATL_NO_VTABLE CPointLoads : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPointLoads, &CLSID_PointLoads>,
	public ISupportErrorInfo,
   public PointLoadColl_Impl,
	public IConnectionPointContainerImpl<CPointLoads>,
	public CProxyDPointLoadsEvents< CPointLoads >,
   public IObjectSafetyImpl<CPointLoads,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IPointLoadEvents
{
public:
   CPointLoads()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_POINTLOADS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPointLoads)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PointLoadColl_Impl)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPointLoadEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPointLoads)
CONNECTION_POINT_ENTRY(IID_IPointLoadsEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IPointLoadEvents
   STDMETHOD(OnPointLoadChanged)(/*[in]*/IPointLoad* PointLoad)
   {
      // Load can be in more than one item
      for (iterator i=begin(); i!=end(); i++)
      {
         CComPtr<IPointLoad> pl;
         HRESULT hr = i->get_Load(&pl);
         if (FAILED(hr))
            return hr;

         // it's one of ours, so we should be able to get away with direct pointer compare
         if (pl == PointLoad)
         {
            Fire_OnPointLoadsChanged(*i);
         }
      }

      return S_OK;
   }


// IPointLoads
public:

   // virtual duties
   // would like to have all of these functions in the template collection, but
   // inheritance via atl won't allow it.
   void FireAfterAdd(IPointLoadItem* pitem)
   {
      Fire_OnPointLoadsAdded(pitem);
   }

   void FireBeforeRemove(IPointLoadItem* pitem)
   {
      Fire_OnPointLoadsBeforeRemove(pitem);
   }

   void FireOnChanged(IPointLoadItem* pitem)
   {
      Fire_OnPointLoadsChanged(pitem);
   }


   virtual HRESULT MakeConnection(CPointLoadItem* pitem)
   {
      return CrAdvise(pitem->m_Load, this, IID_IPointLoadEvents, &(pitem->m_LoadCookie));
   }

   virtual HRESULT BreakConnection(CPointLoadItem* pitem)
   {
      return CrUnadvise(pitem->m_Load, this, IID_IPointLoadEvents, pitem->m_LoadCookie);
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

#endif //__POINTLOADS_H_
