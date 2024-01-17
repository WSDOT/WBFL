///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// Rect2d.cpp : Implementation of CRect2d
#include "stdafx.h"
#include "WBFLGeometry.h"
#include "Helper.h"
#include "Rect2d.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRect2d

STDMETHODIMP CRect2d::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRect2d
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CRect2d::get_Left(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Rect.Left();

	return S_OK;
}

STDMETHODIMP CRect2d::put_Left(Float64 newVal)
{
   m_Rect.Left() = newVal;

	return S_OK;
}

STDMETHODIMP CRect2d::get_Right(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Rect.Right();

	return S_OK;
}

STDMETHODIMP CRect2d::put_Right(Float64 newVal)
{
   m_Rect.Right() = newVal;

	return S_OK;
}

STDMETHODIMP CRect2d::get_Top(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Rect.Top();

	return S_OK;
}

STDMETHODIMP CRect2d::put_Top(Float64 newVal)
{
   m_Rect.Top() = newVal;

	return S_OK;
}

STDMETHODIMP CRect2d::get_Bottom(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Rect.Bottom();

	return S_OK;
}

STDMETHODIMP CRect2d::put_Bottom(Float64 newVal)
{
   m_Rect.Bottom() = newVal;

	return S_OK;
}

STDMETHODIMP CRect2d::SetBounds(/*[in]*/ Float64 Left, /*[in]*/ Float64 Right, /*[in]*/ Float64 Bottom, /*[in]*/ Float64 Top)
{
   ATLASSERT(Left<=Right);
   ATLASSERT(Bottom<=Top);

   m_Rect.Set(Left, Bottom, Right, Top);

	return S_OK;
}

STDMETHODIMP CRect2d::GetBounds(/*[out, retval]*/ Float64* pLeft, /*[out, retval]*/ Float64* pRight, /*[out, retval]*/ Float64* pBottom, /*[out, retval]*/ Float64* pTop)
{
   *pLeft    = m_Rect.Left();
   *pRight  = m_Rect.Right();
   *pBottom = m_Rect.Bottom();
   *pTop     = m_Rect.Top();

	return S_OK;
}


STDMETHODIMP CRect2d::get_Area(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Rect.Area();
	return S_OK;
}

STDMETHODIMP CRect2d::get_BottomLeft(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Rect.BottomLeft(), pVal);
}

STDMETHODIMP CRect2d::get_BottomCenter(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Rect.BottomCenter(), pVal);
}

STDMETHODIMP CRect2d::get_BottomRight(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Rect.BottomRight(), pVal);
}

STDMETHODIMP CRect2d::get_CenterCenter(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Rect.Center(), pVal);
}

STDMETHODIMP CRect2d::get_CenterLeft(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Rect.LeftCenter(), pVal);
}

STDMETHODIMP CRect2d::get_CenterRight(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Rect.RightCenter(), pVal);
}

STDMETHODIMP CRect2d::get_TopLeft(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Rect.TopLeft(), pVal);
}

STDMETHODIMP CRect2d::get_TopCenter(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Rect.TopCenter(), pVal);
}

STDMETHODIMP CRect2d::get_TopRight(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);
   return CreatePoint(m_Rect.TopRight(), pVal);
}

STDMETHODIMP CRect2d::BoundPoint(Float64 x, Float64 y)
{
   // Rectangle must be normalized
   VARIANT_BOOL bIsNormalized;
   IsNormalized(&bIsNormalized);
   if (bIsNormalized == VARIANT_FALSE)
      return Error(IDS_E_NOTNORMALIZED, IID_IRect2d, GEOMETRY_E_NOTNORMALIZED);

   m_Rect.BoundPoint(WBFL::Geometry::Point2d(x, y));

	return S_OK;
}

STDMETHODIMP CRect2d::BoundPointEx(IPoint2d *pPoint)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   pPoint->Location(&x,&y);

   return BoundPoint(x,y);
}

STDMETHODIMP CRect2d::get_Width(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Rect.Width();
	return S_OK;
}

STDMETHODIMP CRect2d::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Rect.Height();
	return S_OK;
}

STDMETHODIMP CRect2d::Inflate(Float64 dx, Float64 dy)
{
   m_Rect.Inflate(dx, dy);
	return S_OK;
}

STDMETHODIMP CRect2d::InflateEx(ISize2d *pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);

   return Inflate(dx,dy);
}

STDMETHODIMP CRect2d::Normalize()
{
   m_Rect.Normalize();
   return S_OK;
}

STDMETHODIMP CRect2d::Offset(Float64 dx, Float64 dy)
{
   m_Rect.Offset(dx, dy);
	return S_OK;
}

STDMETHODIMP CRect2d::OffsetEx(ISize2d *pSize)
{
   CHECK_IN(pSize);

   Float64 dx,dy;
   pSize->get_Dx(&dx);
   pSize->get_Dy(&dy);

   return Offset(dx,dy);
}

STDMETHODIMP CRect2d::Intersect(IRect2d *pRect, IRect2d **ppIntersection)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(ppIntersection);

   VARIANT_BOOL bIsNormalized;
   VARIANT_BOOL bIsOtherNormalized;
   IsNormalized( &bIsNormalized );
   pRect->IsNormalized( &bIsOtherNormalized );
   if ( bIsNormalized == VARIANT_FALSE || bIsOtherNormalized == VARIANT_FALSE )
      return Error( IDS_E_NOTNORMALIZED, IID_IRect2d, GEOMETRY_E_NOTNORMALIZED );

   WBFL::Geometry::Rect2d other;
   pRect->GetBounds(&other.Left(), &other.Right(), &other.Bottom(), &other.Top());
   return CreateRect(m_Rect.IntersectionBy(other), ppIntersection);
   return S_OK;
}

STDMETHODIMP CRect2d::UnionBy(IRect2d *pRect, IRect2d **ppUnion)
{
   CHECK_IN(pRect);
   CHECK_RETOBJ(ppUnion);

   VARIANT_BOOL bIsNormalized;
   VARIANT_BOOL bIsOtherNormalized;
   IsNormalized( &bIsNormalized );
   pRect->IsNormalized( &bIsOtherNormalized );
   if ( bIsNormalized == VARIANT_FALSE || bIsOtherNormalized == VARIANT_FALSE )
      return Error( IDS_E_NOTNORMALIZED, IID_IRect2d, GEOMETRY_E_NOTNORMALIZED );

   WBFL::Geometry::Rect2d other;
   pRect->GetBounds(&other.Left(), &other.Right(), &other.Bottom(), &other.Top());
   return CreateRect(m_Rect.UnionBy(other),ppUnion);
}

STDMETHODIMP CRect2d::Union(IRect2d *pRect)
{
   CHECK_IN(pRect);

   VARIANT_BOOL bIsNormalized;
   VARIANT_BOOL bIsOtherNormalized;
   IsNormalized( &bIsNormalized );
   pRect->IsNormalized( &bIsOtherNormalized );
   if ( bIsNormalized == VARIANT_FALSE || bIsOtherNormalized == VARIANT_FALSE )
      return Error( IDS_E_NOTNORMALIZED, IID_IRect2d, GEOMETRY_E_NOTNORMALIZED );

   WBFL::Geometry::Rect2d other;
   pRect->GetBounds(&other.Left(), &other.Right(), &other.Bottom(), &other.Top());
   m_Rect.Union(other);

   return S_OK;
}

STDMETHODIMP CRect2d::Size(ISize2d **ppSize)
{
   CHECK_RETOBJ(ppSize);

   return CreateSize( m_Rect.Size(), ppSize );
}

STDMETHODIMP CRect2d::SetEmpty()
{
   return SetNull();
}

STDMETHODIMP CRect2d::SetNull()
{
   m_Rect.SetNull();
	return S_OK;
}

STDMETHODIMP CRect2d::ContainsPoint(IPoint2d *pPoint, VARIANT_BOOL *pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   Float64 x,y;
   pPoint->Location(&x, &y);
   *pbResult = m_Rect.Contains(WBFL::Geometry::Point2d(x, y)) ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CRect2d::ContainsRect(IRect2d *pRect, VARIANT_BOOL *pbResult)
{
   CHECK_IN(pRect);
   CHECK_RETVAL(pbResult);

   Float64 left, right, top, bottom;
   pRect->get_Left(&left);
   pRect->get_Top(&top);
   pRect->get_Bottom(&bottom);
   pRect->get_Right(&right);

   *pbResult = m_Rect.Contains(WBFL::Geometry::Rect2d(left,bottom,right,top)) ? VARIANT_TRUE : VARIANT_FALSE;

   return S_OK;
}

STDMETHODIMP CRect2d::Touches(IRect2d* pRect, VARIANT_BOOL* pbResult)
{
   CHECK_IN(pRect);
   CHECK_RETVAL(pbResult);

   Float64 left, right, top, bottom;
   pRect->get_Left( &left );
   pRect->get_Top( &top );
   pRect->get_Right( &right );
   pRect->get_Bottom( &bottom );

   *pbResult = m_Rect.Touches(WBFL::Geometry::Rect2d(left, bottom, right, top)) ? VARIANT_TRUE : VARIANT_FALSE;

   return S_OK;
}

STDMETHODIMP CRect2d::IsNull(VARIANT_BOOL *pbResult)
{
   CHECK_RETVAL(pbResult);

   *pbResult = m_Rect.IsNull() ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CRect2d::Clone(IRect2d** clone)
{
   CHECK_RETOBJ(clone);
   CComObject<CRect2d>* pClone;
   CComObject<CRect2d>::CreateInstance(&pClone);
   pClone->m_Rect = m_Rect;
   (*clone) = pClone;
   (*clone)->AddRef();
   return S_OK;
}

STDMETHODIMP CRect2d::IsNormalized(VARIANT_BOOL *pbResult)
{
   CHECK_RETVAL(pbResult);

   *pbResult = m_Rect.IsNormalized() ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}
