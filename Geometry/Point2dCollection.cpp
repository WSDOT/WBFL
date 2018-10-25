///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// Point2dCollection.cpp : Implementation of CPoint2dCollection
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Point2dCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPoint2dCollection

STDMETHODIMP CPoint2dCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPoint2dCollection,
      &IID_IStructuredStorage2
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CPoint2dCollection::FinalRelease()
{
   UnadviseAll();
}


HRESULT CPoint2dCollection::OnBeforeAdd ( Point2dVectorImpl::StoredType* pVal)
{
   CHECK_IN(pVal);
   try
   {
      // set up connection point
      HRESULT hr;
      hr = CrAdvise(pVal->second.m_T, this, IID_IPoint2dEvents, &(pVal->first));
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

HRESULT CPoint2dCollection::OnAfterAdd ( Point2dVectorImpl::StoredType* pVal, CollectionIndexType idx)
{
   if ( m_bEventsEnabled )
      Fire_OnPointAdded(idx, pVal->second.m_T);
   return S_OK;
}

HRESULT CPoint2dCollection::OnBeforeRemove ( Point2dVectorImpl::StoredType* pVal, CollectionIndexType idx)
{
   try
   {
      // release connection point
      HRESULT hr;
      hr = CrUnadvise(pVal->second.m_T, this, IID_IPoint2dEvents, pVal->first);
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

HRESULT CPoint2dCollection::OnAfterRemove ( CollectionIndexType idx)
{
   if ( m_bEventsEnabled )
      Fire_OnPointRemoved(idx);
   return S_OK;
}

void CPoint2dCollection::UnadviseAll()
{
   // free up all of our connectionpoints on destruct
   CollectionIndexType cnt=0;
   for (iterator it= begin(); it != end(); it++)
   {
      OnBeforeRemove(*it, cnt++);
   }
}

STDMETHODIMP CPoint2dCollection::get__Enum(IEnumPoint2d** ppenum)
{
   return get__EnumElements(ppenum);
}

STDMETHODIMP CPoint2dCollection::Clone(IPoint2dCollection** clone)
{
   CHECK_RETOBJ(clone);
   CComObject<CPoint2dCollection>* pClone;
   CComObject<CPoint2dCollection>::CreateInstance(&pClone);

   for (iterator it= begin(); it != end(); it++)
   {
      CComPtr<IPoint2d> p = it->second;
      CComPtr<IPoint2d> pntClone;
      p->Clone(&pntClone);
      pClone->Add(pntClone);
   }
   (*clone) = pClone;
   (*clone)->AddRef();
   return S_OK;
}

STDMETHODIMP CPoint2dCollection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

STDMETHODIMP CPoint2dCollection::Clear()
{
   UnadviseAll();
   m_coll.clear();
   if ( m_bEventsEnabled )
      Fire_OnPointsCleared();
	return S_OK;
}

STDMETHODIMP CPoint2dCollection::OnPointChanged(IPoint2d* point)
{
   if ( m_bEventsEnabled )
      Fire_OnPointChanged(point);

   return S_OK;
}
