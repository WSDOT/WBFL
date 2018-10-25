///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// UGirderSection2.cpp : Implementation of CUGirderSection2
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "UGirderSection2.h"
#include <MathEx.h>
#include <xutility> // for _cpp_min

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUGirderSection2
HRESULT CUGirderSection2::FinalConstruct()
{
   m_Beam.CoCreateInstance(CLSID_UBeam2);
   m_Beam.QueryInterface(&m_Shape);
   m_Beam.QueryInterface(&m_Position);

   return S_OK;
}

void CUGirderSection2::FinalRelease()
{
}

STDMETHODIMP CUGirderSection2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUGirderSection2,
      &IID_IGirderSection,
      &IID_IShape,
      &IID_IXYPosition,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CUGirderSection2::GetSplittingZone(Float64* pH,SplittingDirection* pSD)
{
   Float64 h,w1,w2;
   m_Beam->get_D1(&h);
   m_Beam->get_W1(&w1);
   m_Beam->get_W2(&w2);

   long idx = Min3Index(h,w1,w2);
   if ( idx == 0 )
   {
      *pH = h;
      *pSD = sdVertical;
   }
   else if ( idx == 1 )
   {
      *pH = w1;
      *pSD = sdHorizontal;
   }
   else
   {
      *pH = w2;
      *pSD = sdHorizontal;
   }
}

////////////////////////////////////////////////////////////////////////
// IUGirderSection2 implementation
STDMETHODIMP CUGirderSection2::put_Beam(IUBeam2* beam)
{
   CHECK_IN(beam);

   CComQIPtr<IShape> shape(beam);
   CHECK_IN(shape);

   CComPtr<IShape> clone;
   HRESULT hr = shape->Clone(&clone);
   ATLASSERT(SUCCEEDED(hr));

   m_Beam.Release();
   clone.QueryInterface(&m_Beam);

   m_Shape = clone;

   m_Position.Release();
   m_Shape.QueryInterface(&m_Position);

   return S_OK;
}

STDMETHODIMP CUGirderSection2::get_Beam(IUBeam2** beam)
{
   CHECK_RETOBJ(beam);
   (*beam) = m_Beam;
   (*beam)->AddRef();
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IPrecastGirderSection implementation
#define NWEBS 2
STDMETHODIMP CUGirderSection2::get_WebCount(WebIndexType* nWebs)
{
   CHECK_RETVAL(nWebs);
   *nWebs = NWEBS;
   return S_OK;
}

STDMETHODIMP CUGirderSection2::get_WebLocation(WebIndexType idx,Float64* location)
{
   if ( idx < 0 || NWEBS <= idx )
      return E_INVALIDARG;

   CHECK_RETVAL(location);

   return m_Beam->get_WebLocation(idx,location);
}

STDMETHODIMP CUGirderSection2::get_WebSpacing(WebIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   CHECK_RETVAL(spacing);

   return m_Beam->get_WebSpacing(spacing);
}

STDMETHODIMP CUGirderSection2::get_WebThickness(WebIndexType idx,Float64* tWeb)
{
   if ( idx < 0 || NWEBS <= idx )
      return E_INVALIDARG;

   CHECK_RETVAL(tWeb);

   Float64 web;
   m_Beam->get_T(&web);

   Float64 slope;
   m_Beam->get_Slope(idx,&slope);
   slope = fabs(slope);

   (*tWeb) = web*sqrt(slope*slope+1)/slope;

   return S_OK;
}

STDMETHODIMP CUGirderSection2::get_MinWebThickness(Float64* tWeb)
{
   return get_WebThickness(0,tWeb);
}

STDMETHODIMP CUGirderSection2::get_EffectiveWebThickness(Float64* tWeb)
{
   return get_MinWebThickness(tWeb);
}

STDMETHODIMP CUGirderSection2::get_MatingSurfaceCount(MatingSurfaceIndexType* nMatingSurfaces)
{
   return get_TopFlangeCount(nMatingSurfaces);
}

STDMETHODIMP CUGirderSection2::get_MatingSurfaceLocation(MatingSurfaceIndexType idx,Float64* location)
{
   return get_TopFlangeLocation(idx,location);
}

STDMETHODIMP CUGirderSection2::get_MatingSurfaceWidth(MatingSurfaceIndexType idx,Float64* wMatingSurface)
{
   return get_TopFlangeWidth(idx,wMatingSurface);
}

STDMETHODIMP CUGirderSection2::get_TopFlangeCount(FlangeIndexType* nTopFlanges)
{
   CHECK_RETVAL(nTopFlanges);
   *nTopFlanges = NWEBS;
   return S_OK;
}

STDMETHODIMP CUGirderSection2::get_TopFlangeLocation(FlangeIndexType idx,Float64* location)
{
   if ( idx < 0 || NWEBS < idx )
      return E_INVALIDARG;

   Float64 W2;
   m_Beam->get_W2(&W2);

   Float64 top_flange_width;
   get_TopFlangeWidth(idx,&top_flange_width);

   *location = (W2 - top_flange_width)/2;

   if ( idx == 0 )
      (*location) *= -1;  // left of CL beam so make it negative

   return S_OK;
}

STDMETHODIMP CUGirderSection2::get_TopFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx < 0 || NWEBS < idx )
      return E_INVALIDARG;

   return m_Beam->get_TopFlangeWidth(width);
}

STDMETHODIMP CUGirderSection2::get_TopFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx < 0 || NWEBS < idx )
      return E_INVALIDARG;

   return m_Beam->get_D5(tFlange);
}

STDMETHODIMP CUGirderSection2::get_TopFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   CHECK_RETVAL(spacing);

   return m_Beam->get_WebSpacing(spacing);
}

STDMETHODIMP CUGirderSection2::get_BottomFlangeCount(FlangeIndexType* nBottomFlanges)
{
   CHECK_RETVAL(nBottomFlanges);
   *nBottomFlanges = 1;
   return S_OK;
}

STDMETHODIMP CUGirderSection2::get_BottomFlangeLocation(FlangeIndexType idx,Float64* location)
{
   if ( idx != 0 ) 
      return E_INVALIDARG;

   *location = 0;
   return S_OK;
}

STDMETHODIMP CUGirderSection2::get_BottomFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   return m_Beam->get_W1(width);
}

STDMETHODIMP CUGirderSection2::get_BottomFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   return m_Beam->get_W2(tFlange);
}

STDMETHODIMP CUGirderSection2::get_BottomFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   CHECK_RETVAL(spacing);

   *spacing = 0;
   return S_OK;
}

STDMETHODIMP CUGirderSection2::get_GirderHeight(Float64* height)
{
   return m_Beam->get_Height(height);
}

STDMETHODIMP CUGirderSection2::get_TopWidth(Float64* width)
{
   return m_Beam->get_TopWidth(width);
}

STDMETHODIMP CUGirderSection2::get_BottomWidth(Float64* width)
{
   return m_Beam->get_W1(width);
}

STDMETHODIMP CUGirderSection2::get_ShearWidth(Float64* shearwidth)
{
   CHECK_RETVAL(shearwidth);
   Float64 width = 0;
   for ( long i = 0; i < NWEBS; i++ )
   {
      Float64 t;
      get_WebThickness(i,&t);
      width += t;
   }

   *shearwidth = width;

   return S_OK;
}

STDMETHODIMP CUGirderSection2::get_MinTopFlangeThickness(Float64* tf)
{
   CHECK_RETVAL(tf);
   Float64 d5;
   m_Beam->get_D5(&d5);

   *tf = d5;
   return S_OK;
}

STDMETHODIMP CUGirderSection2::get_MinBottomFlangeThickness(Float64* tf)
{
   return m_Beam->get_D2(tf);
}

STDMETHODIMP CUGirderSection2::get_CL2ExteriorWebDistance(DirectionType side, Float64* wd)
{
   HRESULT hr;
   CHECK_RETVAL(*wd);

   Float64 spacing;
   hr = m_Beam->get_WebSpacing(&spacing);
   *wd = spacing/2.0;

   return hr;
}

STDMETHODIMP CUGirderSection2::get_SplittingZoneDimension(Float64* pSZD)
{
   CHECK_RETVAL(pSZD);
   SplittingDirection sd;
   GetSplittingZone(pSZD,&sd);
   return S_OK;
}

STDMETHODIMP CUGirderSection2::get_SplittingDirection(SplittingDirection* pSD)
{
   CHECK_RETVAL(pSD);
   Float64 h;
   GetSplittingZone(&h,pSD);
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IShape implementation
STDMETHODIMP CUGirderSection2::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   return m_Shape->FurthestDistance(line,pVal);
}

STDMETHODIMP CUGirderSection2::get_Perimeter(Float64 *pVal)
{
   return m_Shape->get_Perimeter(pVal);
}

STDMETHODIMP CUGirderSection2::get_ShapeProperties(IShapeProperties* *pVal)
{
   return m_Shape->get_ShapeProperties(pVal);
}

STDMETHODIMP CUGirderSection2::get_BoundingBox(IRect2d* *pVal)
{
   return m_Shape->get_BoundingBox(pVal);
}

STDMETHODIMP CUGirderSection2::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   return m_Shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CUGirderSection2::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   return m_Shape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CUGirderSection2::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CUGirderSection2>* clone;
   CComObject<CUGirderSection2>::CreateInstance(&clone);

   CComPtr<IUGirderSection2> flanged_beam = clone;

   flanged_beam->put_Beam(m_Beam);

   CComQIPtr<IShape> shape(flanged_beam);
   (*pClone) = shape;
   (*pClone)->AddRef();

   return S_OK;
}

STDMETHODIMP CUGirderSection2::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   return m_Shape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CUGirderSection2::ClipIn(IRect2d* pRect,IShape** pShape)
{
   return m_Shape->ClipIn(pRect,pShape);
}

STDMETHODIMP CUGirderSection2::Offset(Float64 dx,Float64 dy)
{
   return m_Position->Offset(dx,dy);
}

STDMETHODIMP CUGirderSection2::OffsetEx(ISize2d* pSize)
{
   return m_Position->OffsetEx(pSize);
}

STDMETHODIMP CUGirderSection2::get_LocatorPoint(LocatorPointType lp,IPoint2d** point)
{
   return m_Position->get_LocatorPoint(lp,point);
}

STDMETHODIMP CUGirderSection2::put_LocatorPoint(LocatorPointType lp,IPoint2d* point)
{
   return m_Position->put_LocatorPoint(lp,point);
}

STDMETHODIMP CUGirderSection2::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   return m_Position->MoveEx(pFrom,pTo);
}

STDMETHODIMP CUGirderSection2::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   return m_Position->RotateEx(pPoint,angle);
}

STDMETHODIMP CUGirderSection2::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   return m_Position->Rotate(cx,cy,angle);
}
