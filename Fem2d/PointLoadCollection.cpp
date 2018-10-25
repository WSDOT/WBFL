///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2012  Washington State Department of Transportation
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
// PointLoadCollection.cpp : Implementation of CPointLoadCollection
#include "stdafx.h"
#include "PointLoadCollection.h"
#include "PointLoad.h"
#include "ModelEvents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointLoadCollection

STDMETHODIMP CPointLoadCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dPointLoadCollection
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CPointLoadCollection::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading)
{
   ATLASSERT(pLoading!=0);

   InitParent(pParent); // CCircularChild implementation
   InitCollection(pParent, pEvents, pLoading);  // for C++ event handlers
}

STDMETHODIMP CPointLoadCollection::Create(/*[in]*/LoadIDType id, /*[in]*/MemberIDType memberID, /*[in]*/Float64 location, /*[in]*/Float64 Fx, /*[in]*/Float64 Fy, /*[in]*/Float64 Mz, Fem2dLoadOrientation orientation, /*[out, retval]*/ IFem2dPointLoad** ppPointLoad)
{
   CHECK_RETOBJ(ppPointLoad);
   HRESULT hr = E_FAIL;

   // see if a Point load with our id already exists
   ContainerIteratorType it( m_coll.find(id) );
   if (it != m_coll.end())
   {
      // exists - return error
      return CComCoClass<CPointLoadCollection, &CLSID_Fem2dPointLoadCollection>::Error(IDS_E_POINT_LOAD_WITH_ID_ALREADY_EXISTS, IDH_E_POINT_LOAD_WITH_ID_ALREADY_EXISTS, GetHelpFile(), IID_IFem2dPointLoadCollection, FEM2D_E_POINT_LOAD_WITH_ID_ALREADY_EXISTS);
   }
   else
   {
      // create a new Point load
      CComObject<CPointLoad>* ppl;
      hr = CComObject<CPointLoad>::CreateInstance( &ppl );
      if (FAILED(hr))
         return hr;

      *ppPointLoad = ppl;
      (*ppPointLoad)->AddRef(); // for client

      ppl->Init(m_pModel, m_pEvents, m_pLoading, id, memberID, location, Fx, Fy, Mz, orientation);

      // insert new Point
      std::pair<ContainerIteratorType,bool> st( m_coll.insert(ContainerValueType(id, CComVariant(*ppPointLoad) )) );
      if (!st.second)
      {
         ATLASSERT(0); // insert failed - better check why
         return E_FAIL;
      }

      LoadCaseIDType loadingID;
      m_pLoading->get_ID(&loadingID);
      m_pEvents->OnPointLoadAdded(id,loadingID);
   }

	return hr;
}

STDMETHODIMP CPointLoadCollection::Remove(CollectionIndexType IDorIndex, Fem2dAccessType AccessMethod, LoadIDType* pid)
{
   HRESULT hr = PointLoadCollImpl::Remove(IDorIndex, AccessMethod, pid);
   if (SUCCEEDED(hr))
   {
      // send event up the pipe
      LoadCaseIDType loadingID;
      m_pLoading->get_ID(&loadingID);
      m_pEvents->OnPointLoadRemoved(*pid, loadingID);
   }

   return hr;
}

STDMETHODIMP CPointLoadCollection::Clear()
{
   if (!m_coll.empty())
   {
      HRESULT hr = PointLoadCollImpl::Clear();
      if (SUCCEEDED(hr))
      {
         // send event up the pipe
         LoadCaseIDType loadingID;
         m_pLoading->get_ID(&loadingID);
         m_pEvents->OnPointLoadsCleared(loadingID);
      }
      return hr;
   }
   else
      return S_OK;
}