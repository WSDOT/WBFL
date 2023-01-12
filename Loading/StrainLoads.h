///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
// Copyright © 1999-2023  Washington State Department of Transportation
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

// StrainLoads.h : Declaration of the CStrainLoads

#ifndef __STRAINLOADS_H_
#define __STRAINLOADS_H_

#include "resource.h"       // main symbols
#include "LoadingCP.h"
#include "LoadCollection.h"
#include "LoadingUtils.h"

typedef CLoadItem<ldIStrainLoadItem, ldIStrainLoad, &IID_ldIStrainLoadItem> CStrainLoadItem;
class CStrainLoads;
typedef CLoadCollection<ldIStrainLoads, &IID_ldIStrainLoads, CStrainLoads, ldIStrainLoad, 
                        ldIStrainLoadItem, CStrainLoadItem, 
                        ldIEnumStrainLoad, &IID_ldIEnumStrainLoad> StrainLoadColl_Impl;

/////////////////////////////////////////////////////////////////////////////
// CStrainLoads
class ATL_NO_VTABLE CStrainLoads : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStrainLoads, &CLSID_ldStrainLoads>,
	public ISupportErrorInfo,
   public StrainLoadColl_Impl,
	public IConnectionPointContainerImpl<CStrainLoads>,
	public CProxyDStrainLoadsEvents< CStrainLoads >,
   public IObjectSafetyImpl<CStrainLoads,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ldIStrainLoadEvents
{
public:
	CStrainLoads()
	{
	}

	~CStrainLoads()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STRAINLOADS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStrainLoads)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(StrainLoadColl_Impl)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ldIStrainLoadEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CStrainLoads)
CONNECTION_POINT_ENTRY(IID_ldIStrainLoadsEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ldIStrainLoadEvents
   STDMETHOD(OnStrainLoadChanged)(/*[in]*/ldIStrainLoad* StrainLoad) override
   {
      // Load can be in more than one item
      for (iterator i=begin(); i!=end(); i++)
      {
         CComPtr<ldIStrainLoad> pl;
         HRESULT hr = i->get_Load(&pl);
         if (FAILED(hr))
            return hr;

         // it's one of ours, so we should be able to get away with direct Strainer compare
         if (pl == StrainLoad)
         {
            Fire_OnStrainLoadsChanged(*i);
         }
      }

      return S_OK;
   }


// ldIStrainLoads
public:

   // virtual duties
   // would like to have all of these functions in the template collection, but
   // inheritance via atl won't allow it.
   void FireAfterAdd(ldIStrainLoadItem* pitem)
   {
      Fire_OnStrainLoadsAdded(pitem);
   }

   void FireBeforeRemove(ldIStrainLoadItem* pitem)
   {
      Fire_OnStrainLoadsBeforeRemove(pitem);
   }

   void FireOnChanged(ldIStrainLoadItem* pitem)
   {
      Fire_OnStrainLoadsChanged(pitem);
   }

   virtual HRESULT MakeConnection(CStrainLoadItem* pitem) override
   {
      return CrAdvise(pitem->m_Load, this, IID_ldIStrainLoadEvents, &(pitem->m_LoadCookie));
   }

   virtual HRESULT BreakConnection(CStrainLoadItem* pitem) override
   {
      return CrUnadvise(pitem->m_Load, this, IID_ldIStrainLoadEvents, pitem->m_LoadCookie);
   }

   void FinalRelease()
   {
      for (iterator i=begin(); i!=end(); i++)
      {
         OnBeforeRemove(*i);
      }
   }

};

#endif //__STRAINLOADS_H_
