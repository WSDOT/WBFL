///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////
// POICollection.cpp : Implementation of CPOICollection
#include "stdafx.h"
#include "POICollection.h"
#include "POI.h"
#include "ModelEvents.h"
#include <MathEx.h>


/////////////////////////////////////////////////////////////////////////////
// CPOICollection

STDMETHODIMP CPOICollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_IFem2dPOICollection
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CPOICollection::OnCreate(IFem2dModel* pParent, ModelEvents* pEvents, WBFL::FEA2D::Model* pCoreModel)
{
   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent,pEvents,pCoreModel);  // to get at C++ event handlers
}

void CPOICollection::AdoptCore(WBFL::FEA2D::POI* pCore)
{
   ATLASSERT(pCore!=0);

   CComObject<CPOI>* ppoi;
   HRESULT hr = CComObject<CPOI>::CreateInstance( &ppoi );
   ATLASSERT(SUCCEEDED(hr));

   CComPtr<IFem2dPOI> item(ppoi);

   ppoi->OnCreate(m_pModel, m_pEvents, pCore);

   std::pair<ContainerIteratorType,bool> st( m_coll.insert(ContainerValueType(pCore->GetID(), item )) );
   ATLASSERT(st.second);
}

STDMETHODIMP CPOICollection::Create(PoiIDType id, MemberIDType memberID, Float64 loc, IFem2dPOI **ppPOI)
{
   CHECK_RETOBJ(ppPOI);

   WBFL::FEA2D::POI* pCore;
   try
   {
      pCore = &m_pCoreModel->CreatePOI(id, memberID, loc);
   }
   catch (const WBFL::FEA2D::XFEA2D& ex)
   {
      return ReportFem2dError(ex, CLSID_Fem2dPOICollection, IID_IFem2dPOI);
   }

   // create the COM wrapper
   CComObject<CPOI>* ppoi;
   HRESULT hr = CComObject<CPOI>::CreateInstance( &ppoi );
   if (FAILED(hr))
      return hr;

   *ppPOI = ppoi;
   (*ppPOI)->AddRef(); // for client

   ppoi->OnCreate(m_pModel, m_pEvents, pCore);

   // insert new poi
   std::pair<ContainerIteratorType,bool> st( m_coll.insert(ContainerValueType(id, *ppPOI )) );
   if (!st.second)
   {
      ATLASSERT(false); // insert failed - better check why
      return E_FAIL;
   }

   m_pEvents->OnPOIAdded(id);

	return S_OK;
}

STDMETHODIMP CPOICollection::Remove(IndexType IDorIndex, Fem2dAccessType AccessMethod, PoiIDType* pid)
{
   HRESULT hr = POICollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
      m_pCoreModel->RemovePOI(*pid);

      // send event up the pipe
      m_pEvents->OnPOIRemoved(*pid);
   }

   return hr;
}

STDMETHODIMP CPOICollection::Clear()
{
   if (!m_coll.empty())
   {
      HRESULT hr = POICollImpl::Clear();
      if (SUCCEEDED(hr))
      {
         m_pCoreModel->ClearPOIs();

         // send event up the pipe
         m_pEvents->OnPOIsCleared();
      }
      return hr;
   }

   return S_OK;
}
