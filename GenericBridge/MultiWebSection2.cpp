///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

// MultiWebSection2.cpp : Implementation of CMultiWebSection2
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "MultiWebSection2.h"
#include <math.h>
#include <xutility> // for _cpp_min

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiWebSection2
HRESULT CMultiWebSection2::FinalConstruct()
{
   m_Beam.CoCreateInstance(CLSID_MultiWeb2);
   m_Beam.QueryInterface(&m_Shape);
   m_Beam.QueryInterface(&m_Position);

   return S_OK;
}

void CMultiWebSection2::FinalRelease()
{
}

STDMETHODIMP CMultiWebSection2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMultiWebSection2,
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

bool CMultiWebSection2::ValidateWebIndex(WebIndexType idx)
{
   WebIndexType nWebs;
   get_WebCount(&nWebs);

   return ( 0 <= idx && idx < nWebs );
}

bool CMultiWebSection2::ValidateSpacingIndex(SpacingIndexType idx)
{
   WebIndexType nWebs;
   get_WebCount(&nWebs);

   return ( 0 <= idx && idx < nWebs-1 );
}

////////////////////////////////////////////////////////////////////////
// IMultiWebSection2 implementation
STDMETHODIMP CMultiWebSection2::put_Beam(IMultiWeb2* beam)
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

STDMETHODIMP CMultiWebSection2::get_Beam(IMultiWeb2** beam)
{
   CHECK_RETOBJ(beam);
   (*beam) = m_Beam;
   (*beam)->AddRef();
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IPrecastGirderSection implementation
STDMETHODIMP CMultiWebSection2::get_WebCount(WebIndexType* nWebs)
{
   return m_Beam->get_WebCount(nWebs);
}

STDMETHODIMP CMultiWebSection2::get_WebLocation(WebIndexType idx,Float64* location)
{
   if ( !ValidateWebIndex(idx) )
      return E_INVALIDARG;

   CHECK_RETVAL(location);

   return m_Beam->get_WebLocation(idx,location);
}

STDMETHODIMP CMultiWebSection2::get_WebSpacing(WebIndexType idx,Float64* spacing)
{
   if ( !ValidateSpacingIndex(idx) )
      return E_INVALIDARG;

   CHECK_RETVAL(spacing);

   WebIndexType nWebs;
   get_WebCount(&nWebs);

   if ( idx == 0 || idx == nWebs-2 )
   {
      // Exterior web
      Float64 t2, t3, t4, t5, w2;
      m_Beam->get_T2(&t2);
      m_Beam->get_T3(&t3);
      m_Beam->get_T4(&t4);
      m_Beam->get_T5(&t5);
      m_Beam->get_W2(&w2);

      *spacing = t2/2 + t3 + w2 + t4 + t5/2;
   }
   else
   {
      // interior web
      Float64 w2, t4, t5;
      m_Beam->get_T4(&t4);
      m_Beam->get_T5(&t5);
      m_Beam->get_W2(&w2);

      *spacing = 2*t4 + w2 + t5;
   }

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_WebThickness(WebIndexType idx,Float64* tWeb)
{
   CHECK_RETVAL(tWeb);

   if ( !ValidateWebIndex(idx) )
      return E_INVALIDARG;

   return m_Beam->get_AvgWebWidth(idx,tWeb);
}

STDMETHODIMP CMultiWebSection2::get_MinWebThickness(Float64* tWeb)
{
   CHECK_RETVAL(tWeb);

   Float64 w1, w2;
   get_WebThickness(0,&w1);
   get_WebThickness(1,&w2);

   *tWeb = _cpp_min(w1,w2);

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_EffectiveWebThickness(Float64* tWeb)
{
   return get_MinWebThickness(tWeb);
}

STDMETHODIMP CMultiWebSection2::get_MatingSurfaceCount(MatingSurfaceIndexType* nMatingSurfaces)
{
   return get_TopFlangeCount(nMatingSurfaces);
}

STDMETHODIMP CMultiWebSection2::get_MatingSurfaceLocation(MatingSurfaceIndexType idx,Float64* location)
{
   return get_TopFlangeLocation(idx,location);
}

STDMETHODIMP CMultiWebSection2::get_MatingSurfaceWidth(MatingSurfaceIndexType idx,Float64* wMatingSurface)
{
   return get_TopFlangeWidth(idx,wMatingSurface);
}

STDMETHODIMP CMultiWebSection2::get_TopFlangeCount(FlangeIndexType* nTopFlanges)
{
   CHECK_RETVAL(nTopFlanges);
   *nTopFlanges = 1;
   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_TopFlangeLocation(FlangeIndexType idx,Float64* location)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   *location = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_TopFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   return get_TopWidth(width);
}

STDMETHODIMP CMultiWebSection2::get_TopFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   return m_Beam->get_H3(tFlange);
}

STDMETHODIMP CMultiWebSection2::get_TopFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   CHECK_RETVAL(spacing);

   (*spacing) = 0;

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_BottomFlangeCount(FlangeIndexType* nBottomFlanges)
{
   CHECK_RETVAL(nBottomFlanges);
   *nBottomFlanges = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_BottomFlangeLocation(FlangeIndexType idx,Float64* location)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   *location = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_BottomFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   *width = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_BottomFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   *tFlange = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_BottomFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   CHECK_RETVAL(spacing);

   (*spacing) = 0;

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_GirderHeight(Float64* height)
{
   return m_Beam->get_Height(height);
}

STDMETHODIMP CMultiWebSection2::get_TopWidth(Float64* width)
{
   return m_Beam->get_TopFlangeWidth(width);
}

STDMETHODIMP CMultiWebSection2::get_BottomWidth(Float64* width)
{
   return get_TopWidth(width);
}

STDMETHODIMP CMultiWebSection2::get_ShearWidth(Float64* shearwidth)
{
   CHECK_RETVAL(shearwidth);

   WebIndexType nWebs;
   get_WebCount(&nWebs);

   Float64 width = 0;
   for ( WebIndexType i = 0; i < nWebs; i++ )
   {
      Float64 t;
      get_WebThickness(i,&t);
      width += t;
   }

   *shearwidth = width;

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_MinTopFlangeThickness(Float64* tf)
{
   return m_Beam->get_H3(tf);
}

STDMETHODIMP CMultiWebSection2::get_MinBottomFlangeThickness(Float64* tf)
{
   CHECK_IN(tf);

   *tf = 0;

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_CL2ExteriorWebDistance(DirectionType side, Float64* wd)
{
   HRESULT hr;
   CHECK_RETVAL(*wd);

   WebIndexType nwebs;
   hr = get_WebCount(&nwebs);
   if (FAILED(hr))
      return hr;

   if (nwebs==1)
   {
      *wd = 0.0;
   }
   else
   {
      // multiweb
      Float64 webwid = 0;

      for (WebIndexType is=0; is<nwebs-1; is++)
      {
         Float64 spacing;

         hr = get_WebSpacing(is, &spacing);
         if (FAILED(hr))
            return hr;

         webwid += spacing;
      }

      *wd = webwid/2.0;
   }

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_SplittingZoneDimension(Float64* pSZD)
{
   CHECK_RETVAL(pSZD);

   Float64 h;
   m_Beam->get_Height(&h);

   *pSZD = h;

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_SplittingDirection(SplittingDirection* pSD)
{
   CHECK_RETVAL(pSD);
   *pSD = sdVertical;
   return S_OK;
}


////////////////////////////////////////////////////////////////////////
// IShape implementation
STDMETHODIMP CMultiWebSection2::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   return m_Shape->FurthestDistance(line,pVal);
}

STDMETHODIMP CMultiWebSection2::get_Perimeter(Float64 *pVal)
{
   return m_Shape->get_Perimeter(pVal);
}

STDMETHODIMP CMultiWebSection2::get_ShapeProperties(IShapeProperties* *pVal)
{
   return m_Shape->get_ShapeProperties(pVal);
}

STDMETHODIMP CMultiWebSection2::get_BoundingBox(IRect2d* *pVal)
{
   return m_Shape->get_BoundingBox(pVal);
}

STDMETHODIMP CMultiWebSection2::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   return m_Shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CMultiWebSection2::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   return m_Shape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CMultiWebSection2::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CMultiWebSection2>* clone;
   CComObject<CMultiWebSection2>::CreateInstance(&clone);

   CComPtr<IMultiWebSection2> flanged_beam = clone;

   flanged_beam->put_Beam(m_Beam);

   CComQIPtr<IShape> shape(flanged_beam);
   (*pClone) = shape;
   (*pClone)->AddRef();

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   return m_Shape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CMultiWebSection2::ClipIn(IRect2d* pRect,IShape** pShape)
{
   return m_Shape->ClipIn(pRect,pShape);
}

STDMETHODIMP CMultiWebSection2::Offset(Float64 dx,Float64 dy)
{
   return m_Position->Offset(dx,dy);
}

STDMETHODIMP CMultiWebSection2::OffsetEx(ISize2d* pSize)
{
   return m_Position->OffsetEx(pSize);
}

STDMETHODIMP CMultiWebSection2::get_LocatorPoint(LocatorPointType lp,IPoint2d** point)
{
   return m_Position->get_LocatorPoint(lp,point);
}

STDMETHODIMP CMultiWebSection2::put_LocatorPoint(LocatorPointType lp,IPoint2d* point)
{
   return m_Position->put_LocatorPoint(lp,point);
}

STDMETHODIMP CMultiWebSection2::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   return m_Position->MoveEx(pFrom,pTo);
}

STDMETHODIMP CMultiWebSection2::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   return m_Position->RotateEx(pPoint,angle);
}

STDMETHODIMP CMultiWebSection2::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   return m_Position->Rotate(cx,cy,angle);
}
