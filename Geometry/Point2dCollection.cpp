///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2025  Washington State Department of Transportation
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


/////////////////////////////////////////////////////////////////////////////
// CPoint2dCollection

STDMETHODIMP CPoint2dCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPoint2dCollection
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
      {
			return S_OK;
      }
	}
	return S_FALSE;
}

void CPoint2dCollection::FinalRelease()
{
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

STDMETHODIMP CPoint2dCollection::Clear()
{
   m_coll.clear();
	return S_OK;
}

STDMETHODIMP CPoint2dCollection::Offset(Float64 dx,Float64 dy)
{
   for (iterator it= begin(); it != end(); it++)
   {
      CComPtr<IPoint2d> p = it->second;
      p->Offset(dx,dy);
   }

   return S_OK;
}

STDMETHODIMP CPoint2dCollection::RemoveDuplicatePoints()
{
   if ( m_coll.size() < 2 )
   {
      return S_OK;
   }

   ContainerIteratorType iter = m_coll.begin();
   CComPtr<IPoint2d> prevPoint(iter->second);
   iter++;
   while ( iter != m_coll.end() )
   {
      CComPtr<IPoint2d> currPoint(iter->second);
      if ( prevPoint->SameLocation(currPoint) == S_OK )
      {
         IndexType idx = std::distance(m_coll.begin(),iter);
         iter = m_coll.erase(iter);
      }
      else
      {
         iter++;
         prevPoint = currPoint;
      }
   }

   return S_OK;
}


STDMETHODIMP CPoint2dCollection::OffsetEx(ISize2d* size)
{
   CHECK_IN(size);
   Float64 dx,dy;
   size->Dimensions(&dx,&dy);
   return Offset(dx,dy);
}
