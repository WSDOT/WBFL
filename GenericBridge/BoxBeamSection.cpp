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

// BoxBeamSection.cpp : Implementation of CBoxBeamSection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "BoxBeamSection.h"
#include <math.h>
#include <xutility> // for _cpp_min

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoxBeamSection
HRESULT CBoxBeamSection::FinalConstruct()
{
   m_Beam.CoCreateInstance(CLSID_BoxBeam);
   m_Beam.QueryInterface(&m_Shape);
   m_Beam.QueryInterface(&m_Position);
   m_Beam.QueryInterface(&m_Composite);

   return S_OK;
}

void CBoxBeamSection::FinalRelease()
{
}

STDMETHODIMP CBoxBeamSection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBoxBeamSection,
      &IID_IGirderSection,
      &IID_IShape,
      &IID_ICompositeShape,
      &IID_IXYPosition,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

bool CBoxBeamSection::ValidateWebIndex(WebIndexType idx)
{
   WebIndexType nWebs;
   get_WebCount(&nWebs);

   return ( 0 <= idx && idx < nWebs );
}


////////////////////////////////////////////////////////////////////////
// IBoxBeamSection implementation
STDMETHODIMP CBoxBeamSection::put_Beam(IBoxBeam* beam)
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

   m_Composite.Release();
   m_Shape.QueryInterface(&m_Composite);

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_Beam(IBoxBeam** beam)
{
   CHECK_RETOBJ(beam);
   (*beam) = m_Beam;
   (*beam)->AddRef();
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IPrecastGirderSection implementation
STDMETHODIMP CBoxBeamSection::get_WebCount(WebIndexType* nWebs)
{
   CHECK_RETVAL(nWebs);

   *nWebs = 2;
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_WebLocation(WebIndexType idx,Float64* location)
{
   if ( !ValidateWebIndex(idx) )
      return E_INVALIDARG;

   CHECK_RETVAL(location);

   Float64 tWeb;
   get_WebThickness(idx,&tWeb);

   Float64 w3;
   m_Beam->get_W3(&w3);

   if ( idx == 0 )
      *location = -(w3+tWeb)/2;
   else
      *location =  (w3+tWeb)/2;

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_WebSpacing(WebIndexType idx,Float64* spacing)
{
   if ( !ValidateWebIndex(idx) )
      return E_INVALIDARG;

   CHECK_RETVAL(spacing);

   Float64 w3;
   m_Beam->get_W3(&w3);

   Float64 tWeb;
   get_WebThickness(idx,&tWeb);

   *spacing = w3 + tWeb;

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_WebThickness(WebIndexType idx,Float64* tWeb)
{
   if ( !ValidateWebIndex(idx) )
      return E_INVALIDARG;

   CHECK_RETVAL(tWeb);

   Float64 W1,W2,W4,H1,H2,H3,H4,H7,F1,F2;
   m_Beam->get_W1(&W1);
   m_Beam->get_W2(&W2);
   m_Beam->get_W4(&W4);
   m_Beam->get_H1(&H1);
   m_Beam->get_H2(&H2);
   m_Beam->get_H3(&H3);
   m_Beam->get_H4(&H4);
   m_Beam->get_H7(&H7);
   m_Beam->get_F1(&F1);
   m_Beam->get_F2(&F2);

   bool bSmallShearKey    = (W1 < W2/2 || W4 < W2/2)       ? true : false;
   bool bShearKeyAtTop    = (H4 < H1 && H2+H3-F1 < H7) ? true : false;
   bool bShearKeyAtBottom = (H7 < H3 && H1+H2-F2 < H4) ? true : false;

   if ( bSmallShearKey && bShearKeyAtTop )
      *tWeb = W2 + W4;
   else if ( bSmallShearKey && bShearKeyAtBottom )
      *tWeb = W1 + W2;
   else
      *tWeb = W2;

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_MinWebThickness(Float64* tWeb)
{
   CHECK_RETVAL(tWeb);
   return get_WebThickness(0,tWeb);
}

STDMETHODIMP CBoxBeamSection::get_EffectiveWebThickness(Float64* tWeb)
{
   CHECK_RETVAL(tWeb);
   
   Float64 W3, W2;
   m_Beam->get_W2(&W2);
   m_Beam->get_W3(&W3);

   // Web thickness for effective flange width computations - for box beams in pre-2008 lrfd::4.6.2.2.1
   // Quote: "In calculating the effective flange width for closed steel and precast concrete boxes, the distance between the
   // outside of webs at their tops will be used in lieu of the web thickness"
   *tWeb = W3 + 2*W2;

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_MatingSurfaceCount(MatingSurfaceIndexType* nMatingSurfaces)
{
   return get_TopFlangeCount(nMatingSurfaces);
}

STDMETHODIMP CBoxBeamSection::get_MatingSurfaceLocation(MatingSurfaceIndexType idx,Float64* location)
{
   return get_TopFlangeLocation(idx,location);
}

STDMETHODIMP CBoxBeamSection::get_MatingSurfaceWidth(MatingSurfaceIndexType idx,Float64* wMatingSurface)
{
   return get_TopFlangeWidth(idx,wMatingSurface);
}

STDMETHODIMP CBoxBeamSection::get_TopFlangeCount(FlangeIndexType* nTopFlanges)
{
   CHECK_RETVAL(nTopFlanges);
   *nTopFlanges = 1;
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_TopFlangeLocation(FlangeIndexType idx,Float64* location)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   *location = 0;
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_TopFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   return get_TopWidth(width);
}

STDMETHODIMP CBoxBeamSection::get_TopFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   return m_Beam->get_H1(tFlange);
}

STDMETHODIMP CBoxBeamSection::get_TopFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   CHECK_RETVAL(spacing);

   (*spacing) = 0;
   
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_BottomFlangeCount(FlangeIndexType* nBottomFlanges)
{
   CHECK_RETVAL(nBottomFlanges);
   *nBottomFlanges = 1;
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_BottomFlangeLocation(FlangeIndexType idx,Float64* location)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   *location = 0;
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_BottomFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   return get_BottomWidth(width);
}

STDMETHODIMP CBoxBeamSection::get_BottomFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   return m_Beam->get_H3(tFlange);
}

STDMETHODIMP CBoxBeamSection::get_BottomFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
      return E_INVALIDARG;

   CHECK_RETVAL(spacing);

   (*spacing) = 0;
   
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_GirderHeight(Float64* height)
{
   Float64 h1,h2,h3;
   m_Beam->get_H1(&h1);
   m_Beam->get_H2(&h2);
   m_Beam->get_H3(&h3);

   *height = h1+h2+h3;
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_TopWidth(Float64* width)
{
   return m_Beam->get_TopFlangeWidth(width);
}

STDMETHODIMP CBoxBeamSection::get_BottomWidth(Float64* width)
{
   return m_Beam->get_BottomFlangeWidth(width);
}

STDMETHODIMP CBoxBeamSection::get_ShearWidth(Float64* shearwidth)
{
   return m_Beam->get_WebWidth(shearwidth);
}

STDMETHODIMP CBoxBeamSection::get_MinTopFlangeThickness(Float64* tf)
{
   CHECK_RETVAL(*tf);
   return m_Beam->get_H1(tf);
}

STDMETHODIMP CBoxBeamSection::get_MinBottomFlangeThickness(Float64* tf)
{
   CHECK_RETVAL(*tf);
   return m_Beam->get_H3(tf);
}

STDMETHODIMP CBoxBeamSection::get_CL2ExteriorWebDistance(DirectionType side, Float64* wd)
{
   CHECK_RETVAL(*wd);

   Float64 spacing;
   HRESULT hr = get_WebSpacing(0, &spacing);
   
   *wd = spacing/2.0;

   return hr;
}

STDMETHODIMP CBoxBeamSection::get_SplittingZoneDimension(Float64* pSZD)
{
   CHECK_RETVAL(pSZD);
   SplittingDirection sd;
   GetSplittingZone(pSZD,&sd);
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_SplittingDirection(SplittingDirection* pSD)
{
   CHECK_RETVAL(pSD);
   Float64 h;
   GetSplittingZone(&h,pSD);
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IShape implementation
STDMETHODIMP CBoxBeamSection::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   return m_Shape->FurthestDistance(line,pVal);
}

STDMETHODIMP CBoxBeamSection::get_Perimeter(Float64 *pVal)
{
   return m_Shape->get_Perimeter(pVal);
}

STDMETHODIMP CBoxBeamSection::get_ShapeProperties(IShapeProperties* *pVal)
{
   return m_Shape->get_ShapeProperties(pVal);
}

STDMETHODIMP CBoxBeamSection::get_BoundingBox(IRect2d* *pVal)
{
   return m_Shape->get_BoundingBox(pVal);
}

STDMETHODIMP CBoxBeamSection::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   return m_Shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CBoxBeamSection::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   return m_Shape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CBoxBeamSection::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CBoxBeamSection>* clone;
   CComObject<CBoxBeamSection>::CreateInstance(&clone);

   CComPtr<IBoxBeamSection> flanged_beam = clone;

   flanged_beam->put_Beam(m_Beam);

   CComQIPtr<IShape> shape(flanged_beam);
   (*pClone) = shape;
   (*pClone)->AddRef();

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   return m_Shape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CBoxBeamSection::ClipIn(IRect2d* pRect,IShape** pShape)
{
   return m_Shape->ClipIn(pRect,pShape);
}

/////////////////////////////////////////////////////////////////////////////
// ICompositeShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CBoxBeamSection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   return m_Composite->get_StructuredStorage(pStg);
}

STDMETHODIMP CBoxBeamSection::get_Shape(IShape* *pVal)
{
   return m_Composite->get_Shape(pVal);
}

STDMETHODIMP CBoxBeamSection::get_Item(CollectionIndexType idx,ICompositeShapeItem* *pVal)
{
   return m_Composite->get_Item(idx,pVal);
}

STDMETHODIMP CBoxBeamSection::get__NewEnum(IUnknown* *pVal)
{
   return m_Composite->get__NewEnum(pVal);
}

STDMETHODIMP CBoxBeamSection::get_Count(CollectionIndexType *pVal)
{
   return m_Composite->get_Count(pVal);
}

STDMETHODIMP CBoxBeamSection::Remove(CollectionIndexType idx)
{
   return m_Composite->Remove(idx);
}

STDMETHODIMP CBoxBeamSection::Clear()
{
   return m_Composite->Clear();
}

STDMETHODIMP CBoxBeamSection::AddShapeEx(ICompositeShapeItem* ShapeItem)
{
   return m_Composite->AddShapeEx(ShapeItem);
}

STDMETHODIMP CBoxBeamSection::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   return m_Composite->AddShape(shape,bVoid);
}

// XYPosition
STDMETHODIMP CBoxBeamSection::Offset(Float64 dx,Float64 dy)
{
   return m_Position->Offset(dx,dy);
}

STDMETHODIMP CBoxBeamSection::OffsetEx(ISize2d* pSize)
{
   return m_Position->OffsetEx(pSize);
}

STDMETHODIMP CBoxBeamSection::get_LocatorPoint(LocatorPointType lp,IPoint2d** point)
{
   return m_Position->get_LocatorPoint(lp,point);
}

STDMETHODIMP CBoxBeamSection::put_LocatorPoint(LocatorPointType lp,IPoint2d* point)
{
   return m_Position->put_LocatorPoint(lp,point);
}

STDMETHODIMP CBoxBeamSection::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   return m_Position->MoveEx(pFrom,pTo);
}

STDMETHODIMP CBoxBeamSection::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   return m_Position->RotateEx(pPoint,angle);
}

STDMETHODIMP CBoxBeamSection::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   return m_Position->Rotate(cx,cy,angle);
}

void CBoxBeamSection::GetSplittingZone(Float64* pH,SplittingDirection* pSD)
{
   Float64 h1,h2,h3,w2,w3;
   m_Beam->get_H1(&h1);
   m_Beam->get_H2(&h2);
   m_Beam->get_H3(&h3);

   m_Beam->get_W2(&w2);
   m_Beam->get_W3(&w3);

   Float64 h = h1+h2+h3;
   Float64 w = 2*w2+w3;

   if ( h < w )
   {
      *pH = h;
      *pSD = sdVertical;
   }
   else
   {
      *pH = w;
      *pSD = sdHorizontal;
   }
}
