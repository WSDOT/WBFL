///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2021  Washington State Department of Transportation
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
#include "Rect2d.h"
#include <MathEx.h>
#include "Helper.h"
#include <xutility>

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
		&IID_IRect2d,
      &IID_IStructuredStorage2
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

   *pVal = m_Left;

	return S_OK;
}

STDMETHODIMP CRect2d::put_Left(Float64 newVal)
{
   m_Left = newVal;

	return S_OK;
}

STDMETHODIMP CRect2d::get_Right(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Right;

	return S_OK;
}

STDMETHODIMP CRect2d::put_Right(Float64 newVal)
{
   m_Right = newVal;

	return S_OK;
}

STDMETHODIMP CRect2d::get_Top(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Top;

	return S_OK;
}

STDMETHODIMP CRect2d::put_Top(Float64 newVal)
{
   m_Top = newVal;

	return S_OK;
}

STDMETHODIMP CRect2d::get_Bottom(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Bottom;

	return S_OK;
}

STDMETHODIMP CRect2d::put_Bottom(Float64 newVal)
{
   m_Bottom = newVal;

	return S_OK;
}

STDMETHODIMP CRect2d::SetBounds(/*[in]*/ Float64 Left, /*[in]*/ Float64 Right, /*[in]*/ Float64 Bottom, /*[in]*/ Float64 Top)
{
   ATLASSERT(Left<=Right);
   ATLASSERT(Bottom<=Top);

   m_Left   = Left;
   m_Right  = Right;
   m_Bottom = Bottom;
   m_Top    = Top;

	return S_OK;
}

STDMETHODIMP CRect2d::GetBounds(/*[out, retval]*/ Float64* pLeft, /*[out, retval]*/ Float64* pRight, /*[out, retval]*/ Float64* pBottom, /*[out, retval]*/ Float64* pTop)
{
   *pLeft    = m_Left;
   *pRight  = m_Right;
   *pBottom = m_Bottom;
   *pTop     = m_Top;

	return S_OK;
}


STDMETHODIMP CRect2d::get_Area(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = (m_Top - m_Bottom)*(m_Right - m_Left);

	return S_OK;
}

STDMETHODIMP CRect2d::get_BottomLeft(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   return CreatePoint(m_Left,m_Bottom,nullptr,pVal);
}

STDMETHODIMP CRect2d::get_BottomCenter(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 cx = (m_Left + m_Right)/2.0;
   return CreatePoint(cx,m_Bottom,nullptr,pVal);
}

STDMETHODIMP CRect2d::get_BottomRight(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   return CreatePoint(m_Right,m_Bottom,nullptr,pVal);
}

STDMETHODIMP CRect2d::get_CenterCenter(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 cx = (m_Left + m_Right)/2.0;
   Float64 cy = (m_Top + m_Bottom)/2.0;
   return CreatePoint(cx,cy,nullptr,pVal);
}

STDMETHODIMP CRect2d::get_CenterLeft(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 cy = (m_Top + m_Bottom)/2.0;
   return CreatePoint(m_Left,cy,nullptr,pVal);
}

STDMETHODIMP CRect2d::get_CenterRight(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 cy = (m_Top + m_Bottom)/2.0;
   return CreatePoint(m_Right,cy,nullptr,pVal);
}

STDMETHODIMP CRect2d::get_TopLeft(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   return CreatePoint(m_Left,m_Top,nullptr,pVal);
}

STDMETHODIMP CRect2d::get_TopCenter(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   Float64 cx = (m_Left + m_Right)/2.0;
   return CreatePoint(cx,m_Top,nullptr,pVal);
}

STDMETHODIMP CRect2d::get_TopRight(IPoint2d **pVal)
{
   CHECK_RETOBJ(pVal);

   return CreatePoint(m_Right,m_Top,nullptr,pVal);
}

STDMETHODIMP CRect2d::BoundPoint(Float64 x, Float64 y)
{
   // Rectangle must be normalized
   VARIANT_BOOL bIsNormalized;
   IsNormalized( &bIsNormalized );
   if ( bIsNormalized == VARIANT_FALSE )
      return Error(IDS_E_NOTNORMALIZED,IID_IRect2d,GEOMETRY_E_NOTNORMALIZED);

   m_Left   = Min(x,  m_Left);
   m_Bottom = Min(y,  m_Bottom);
   m_Right  = Max(x,  m_Right);
   m_Top    = Max(y,  m_Top);

	return S_OK;
}

STDMETHODIMP CRect2d::BoundPointEx(IPoint2d *pPoint)
{
   CHECK_IN(pPoint);

   Float64 x,y;
   pPoint->get_X(&x);
   pPoint->get_Y(&y);

   return BoundPoint(x,y);
}

STDMETHODIMP CRect2d::get_Width(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Right - m_Left;

	return S_OK;
}

STDMETHODIMP CRect2d::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   
   *pVal = m_Top - m_Bottom;

	return S_OK;
}

STDMETHODIMP CRect2d::Inflate(Float64 dx, Float64 dy)
{
   m_Left   -= dx;
   m_Right  += dx;
   m_Top    += dy;
   m_Bottom -= dy;

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
   Float64 temp;
   if ( m_Left > m_Right )
   {
      temp = m_Right;
      m_Right = m_Left;
      m_Left = temp;
   }

   if ( m_Top < m_Bottom )
   {
      temp = m_Bottom;
      m_Bottom = m_Top;
      m_Top = temp;
   }

   return S_OK;
}

STDMETHODIMP CRect2d::Offset(Float64 dx, Float64 dy)
{
   m_Left   += dx;
   m_Right  += dx;
   m_Top    += dy;
   m_Bottom += dy;

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

   Float64 left, right, top, bottom;
   pRect->get_Left(&left);
   pRect->get_Top(&top);
   pRect->get_Right(&right);
   pRect->get_Bottom(&bottom);
 
   CComPtr<IRect2d> pIntersection;
   HRESULT hr = CreateRect(0,0,0,0,&pIntersection);
   if ( FAILED(hr) )
      return hr;

   VARIANT_BOOL bTouches;
   Touches(pRect,&bTouches);
   if ( bTouches == VARIANT_TRUE )
   {
      pIntersection->put_Left(   Max(left,   m_Left) );
      pIntersection->put_Bottom( Max(bottom, m_Bottom) );
      pIntersection->put_Right(  Min(right,  m_Right) );
      pIntersection->put_Top(    Min(top,    m_Top) );
   }
   else
   {
      // Set all sides to zero, but since we did that
      // when the rectangle was created, we don't have to do it again.
//      pIntersection->put_Left( 0 );
//      pIntersection->put_Bottom( 0 );
//      pIntersection->put_Right( 0 );
//      pIntersection->put_Top( 0 );
   }

   if (*ppIntersection)
      (*ppIntersection)->Release();

   pIntersection->QueryInterface(ppIntersection);

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

   Float64 left, right, top, bottom;
   pRect->get_Left(&left);
   pRect->get_Top(&top);
   pRect->get_Right(&right);
   pRect->get_Bottom(&bottom);

   CComPtr<IRect2d> pUnion;
   CreateRect(0,0,0,0,&pUnion);

   pUnion->put_Left(   Min(left,   m_Left) );
   pUnion->put_Bottom( Min(bottom, m_Bottom) );
   pUnion->put_Right(  Max(right,  m_Right) );
   pUnion->put_Top(    Max(top,    m_Top) );

   if ( *ppUnion )
      (*ppUnion)->Release();

   pUnion->QueryInterface(ppUnion);

   return S_OK;
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

   Float64 left, right, top, bottom;
   pRect->get_Left(&left);
   pRect->get_Top(&top);
   pRect->get_Right(&right);
   pRect->get_Bottom(&bottom);

   m_Left   = Min(left,   m_Left);
   m_Bottom = Min(bottom, m_Bottom);
   m_Right  = Max(right,  m_Right);
   m_Top    = Max(top,    m_Top);

   return S_OK;
}

STDMETHODIMP CRect2d::Size(ISize2d **ppSize)
{
   CHECK_RETOBJ(ppSize);

   Float64 dx = m_Right - m_Left;
   Float64 dy = m_Top - m_Bottom;

   return CreateSize( dx, dy, ppSize );
}

STDMETHODIMP CRect2d::SetEmpty()
{
   return SetNull();
}

STDMETHODIMP CRect2d::SetNull()
{
   m_Left = m_Right = m_Top = m_Bottom = 0.00;
	return S_OK;
}

STDMETHODIMP CRect2d::ContainsPoint(IPoint2d *pPoint, VARIANT_BOOL *pbResult)
{
   CHECK_IN(pPoint);
   CHECK_RETVAL(pbResult);

   Float64 x,y;
   pPoint->get_X(&x);
   pPoint->get_Y(&y);

   *pbResult = ( (m_Left   <= x && x < m_Right) &&
                 (m_Bottom <= y && y < m_Top) ) ? VARIANT_TRUE : VARIANT_FALSE;

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

   *pbResult = ( (m_Left   <= left   && right <= m_Right) &&
                 (m_Bottom <= bottom && top   <= m_Top) ) ? VARIANT_TRUE : VARIANT_FALSE;

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
   *pbResult = ( (m_Left   < right && left   < m_Right) &&
               (m_Bottom < top   && bottom < m_Top) ) ? VARIANT_TRUE : VARIANT_FALSE;

   return S_OK;
}

STDMETHODIMP CRect2d::IsNull(VARIANT_BOOL *pbResult)
{
   CHECK_RETVAL(pbResult);

   *pbResult = IsZero( m_Left )  &&
               IsZero( m_Right ) && 
               IsZero( m_Top )   &&
               IsZero( m_Bottom ) ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CRect2d::Clone(IRect2d** clone)
{
   CHECK_RETOBJ(clone);
   CComObject<CRect2d>* pClone;
   CComObject<CRect2d>::CreateInstance(&pClone);
   pClone->m_Left   = m_Left;
   pClone->m_Right  = m_Right;
   pClone->m_Top    = m_Top;
   pClone->m_Bottom = m_Bottom;
   (*clone) = pClone;
   (*clone)->AddRef();
   return S_OK;
}

STDMETHODIMP CRect2d::IsNormalized(VARIANT_BOOL *pbResult)
{
   CHECK_RETVAL(pbResult);

   *pbResult = ( IsGE(m_Left,m_Right) && IsGE(m_Bottom, m_Top) ) ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CRect2d::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IPersist
STDMETHODIMP CRect2d::GetClassID(CLSID* pClassID)
{
   CHECK_IN(pClassID);

   *pClassID = GetObjectCLSID();
   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CRect2d::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("Rect2d"),1.0);
   pSave->put_Property(CComBSTR("Left"),CComVariant(m_Left));
   pSave->put_Property(CComBSTR("Top"),CComVariant(m_Top));
   pSave->put_Property(CComBSTR("Right"),CComVariant(m_Right));
   pSave->put_Property(CComBSTR("Bottom"),CComVariant(m_Bottom));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CRect2d::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Rect2d"));
   
   pLoad->get_Property(CComBSTR("Left"),&var);
   m_Left = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Top"),&var);
   m_Top = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Right"),&var);
   m_Right = var.dblVal;
   
   pLoad->get_Property(CComBSTR("Bottom"),&var);
   m_Bottom = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
