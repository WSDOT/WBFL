///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// PrimitiveFactory.cpp : Implementation of CPrimitiveFactory
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "PrimitiveFactory.h"
#include "Point2d.h"
#include "Point3d.h"
#include "Line2d.h"
#include "LineSegment2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrimitiveFactory

STDMETHODIMP CPrimitiveFactory::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPoint2dFactory,
		&IID_IPoint3dFactory,
      &IID_ILine2dFactory,
      &IID_ILineSegment2dFactory,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPrimitiveFactory::CreatePoint(IPoint2d **ppPoint)
{
   CHECK_RETOBJ(ppPoint);

   HRESULT hr = S_OK;
   typedef CComObject<CPoint2d> PointType;
   PointType* pPoint;
   hr = PointType::CreateInstance(&pPoint);
   if ( FAILED(hr) )
      return hr;

   return pPoint->QueryInterface( ppPoint );
}

STDMETHODIMP CPrimitiveFactory::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

STDMETHODIMP CPrimitiveFactory::CreatePoint(IPoint3d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);

   HRESULT hr = S_OK;
   typedef CComObject<CPoint3d> PointType;
   PointType* pPoint;
   hr = PointType::CreateInstance(&pPoint);
   if ( FAILED(hr) )
      return hr;

   return pPoint->QueryInterface( ppPoint );
}

STDMETHODIMP CPrimitiveFactory::CreateLine(ILine2d **ppLine)
{
   CHECK_RETOBJ(ppLine);

   HRESULT hr = S_OK;
   typedef CComObject<CLine2d> LineType;
   LineType* pLine;
   hr = LineType::CreateInstance(&pLine);
   if ( FAILED(hr) )
      return hr;

   return pLine->QueryInterface( ppLine );
}

STDMETHODIMP CPrimitiveFactory::CreateLineSegment(ILineSegment2d **ppLineSeg)
{
   CHECK_RETOBJ(ppLineSeg);

   HRESULT hr = S_OK;
   typedef CComObject<CLineSegment2d> LineSegType;
   LineSegType* pLineSeg;
   hr = LineSegType::CreateInstance(&pLineSeg);
   if ( FAILED(hr) )
      return hr;

   return pLineSeg->QueryInterface( ppLineSeg );
}


// IStructuredStorage2
STDMETHODIMP CPrimitiveFactory::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("PrimitiveFactory"),1.0);
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CPrimitiveFactory::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("PrimitiveFactory"));


   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
