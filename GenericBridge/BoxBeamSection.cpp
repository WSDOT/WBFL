///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// BoxBeamSection.cpp : Implementation of CBoxBeamSection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "BoxBeamSection.h"
#include <math.h>
#include <xutility> // for Min
#include <algorithm>
#include <functional>


/////////////////////////////////////////////////////////////////////////////
// CBoxBeamSection
HRESULT CBoxBeamSection::FinalConstruct()
{
   m_Beam.CoCreateInstance(CLSID_BoxBeam);
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
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
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

   // getting the bounding box and shape properties
   // causes these to be computed and cached in beam
   // when we clone, these will be cloned. that way
   // they don't have to be computed later when needed.
   CComPtr<IShapeProperties> shapeProps;
   shape->get_ShapeProperties(&shapeProps);
   CComPtr<IRect2d> box;
   shape->get_BoundingBox(&box);

   CComPtr<IShape> clone;
   HRESULT hr = shape->Clone(&clone);
   ATLASSERT(SUCCEEDED(hr));

   m_Beam.Release();
   clone.QueryInterface(&m_Beam);


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
STDMETHODIMP CBoxBeamSection::get_GirderShape(IShape** ppShape)
{
   return m_Beam->GetBoxShape(ppShape);
}

STDMETHODIMP CBoxBeamSection::get_VoidCount(/*[out, retval]*/IndexType* pnVoids)
{
   return m_Beam->get_VoidCount(pnVoids);
}

STDMETHODIMP CBoxBeamSection::get_VoidShape(/*[in]*/IndexType voidIdx, /*[out, retval]*/IShape** ppShape)
{
   return m_Beam->GetVoidShape(voidIdx, ppShape);
}

STDMETHODIMP CBoxBeamSection::get_WorkPoint(IPoint2d** ppWorkPoint)
{
   // work point is at top center
   // if the section has been rotated, the top center locator point is
   // the top center of the bounding box of the rotated shape. this is
   // not the work point
   if (IsZero(m_Rotation))
   {
      // don't do extra work if there isn't rotation
      get_LocatorPoint(lpTopCenter, ppWorkPoint);
   }
   else
   {
      CComQIPtr<IXYPosition> position(m_Beam);
      CComPtr<IPoint2d> pntHookPoint; // hook point is at bottom center of shape (not bottom center of bounding box)
      position->get_LocatorPoint(lpHookPoint, &pntHookPoint);

      // compute the location of the top center point without rotation
      // this is just the hook point offset vertically by the height of the beam shape
      Float64 H;
      get_NominalHeight(&H);
      CComPtr<IPoint2d> pntUnRotatedTopCenter;
      pntHookPoint->Clone(&pntUnRotatedTopCenter);
      pntUnRotatedTopCenter->Offset(0, H);

      // the unrotated top center is also the unrotated work point
      pntUnRotatedTopCenter->Clone(ppWorkPoint);

      // apply the rotation to the work point
      (*ppWorkPoint)->RotateEx(pntHookPoint, m_Rotation);
   }

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_WebCount(WebIndexType* nWebs)
{
   CHECK_RETVAL(nWebs);

   *nWebs = 2;
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_WebLocation(WebIndexType idx,Float64* location)
{
   if ( !ValidateWebIndex(idx) )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(location);

   Float64 tWeb;
   get_WebThickness(idx,&tWeb);

   Float64 w3;
   m_Beam->get_W3(&w3);

   if ( idx == 0 )
   {
      *location = -(w3+tWeb)/2;
   }
   else
   {
      *location =  (w3+tWeb)/2;
   }

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_WebSpacing(WebIndexType idx,Float64* spacing)
{
   if ( !ValidateWebIndex(idx) )
   {
      return E_INVALIDARG;
   }

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
   {
      return E_INVALIDARG;
   }

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
   {
      *tWeb = W2 + W4;
   }
   else if ( bSmallShearKey && bShearKeyAtBottom )
   {
      *tWeb = W1 + W2;
   }
   else
   {
      *tWeb = W2;
   }

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_MinWebThickness(Float64* tWeb)
{
   CHECK_RETVAL(tWeb);
   return get_WebThickness(0,tWeb);
}

STDMETHODIMP CBoxBeamSection::get_WebPlane(WebIndexType idx,IPlane3d** ppPlane)
{
   CHECK_RETOBJ(ppPlane);

   Float64 x;
   HRESULT hr = get_WebLocation(idx,&x);
   if ( FAILED(hr) )
   {
      return hr;
   }

   CComPtr<IPoint3d> p1;
   p1.CoCreateInstance(CLSID_Point3d);
   p1->Move(x,0,0);

   CComPtr<IPoint3d> p2;
   p2.CoCreateInstance(CLSID_Point3d);
   p2->Move(x,100,0);

   CComPtr<IPoint3d> p3;
   p3.CoCreateInstance(CLSID_Point3d);
   p3->Move(x,0,100);

   CComPtr<IPlane3d> plane;
   plane.CoCreateInstance(CLSID_Plane3d);
   plane->ThroughPoints(p1,p2,p3);

   return plane.CopyTo(ppPlane);
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

STDMETHODIMP CBoxBeamSection::get_MatingSurfaceLocation(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* location)
{
   return get_TopFlangeLocation(idx,location);
}

STDMETHODIMP CBoxBeamSection::get_MatingSurfaceWidth(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* wMatingSurface)
{
   return get_TopFlangeWidth(idx,wMatingSurface);
}

STDMETHODIMP CBoxBeamSection::get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile)
{
   return E_NOTIMPL;
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
   {
      return E_INVALIDARG;
   }

   // flange can be offset if unequal left and right
   Float64 left, right;
   m_Beam->get_TopFlangeWidth(&left, &right);

   *location = (right - left) / 2.0;
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_TopFlangeWidth(FlangeIndexType idx,Float64* width)
{
   CHECK_RETVAL(width);

   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   Float64 left, right;
   m_Beam->get_TopFlangeWidth(&left, &right);

   *width = left + right;

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_TopFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_H1(tFlange);
}

STDMETHODIMP CBoxBeamSection::get_TopFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

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
   {
      return E_INVALIDARG;
   }

   *location = 0;
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_BottomFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   Float64 left, right;
   m_Beam->get_BottomFlangeWidth(&left, &right);

   *width = left + right;

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_BottomFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_H3(tFlange);
}

STDMETHODIMP CBoxBeamSection::get_BottomFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(spacing);

   (*spacing) = 0;
   
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_OverallHeight(Float64* height)
{
   return get_NominalHeight(height);
}

STDMETHODIMP CBoxBeamSection::get_NominalHeight(Float64* height)
{
   Float64 h1,h2,h3;
   m_Beam->get_H1(&h1);
   m_Beam->get_H2(&h2);
   m_Beam->get_H3(&h3);

   *height = h1+h2+h3;
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get_TopWidth(Float64* wLeft,Float64* wRight)
{
   return m_Beam->get_TopFlangeWidth(wLeft, wRight);
}

STDMETHODIMP CBoxBeamSection::get_BottomWidth(Float64* wLeft,Float64* wRight)
{
   return m_Beam->get_BottomFlangeWidth(wLeft, wRight);
}

STDMETHODIMP CBoxBeamSection::get_ShearWidth(Float64* shearwidth)
{
   return m_Beam->get_WebWidth(shearwidth);
}

STDMETHODIMP CBoxBeamSection::get_MinTopFlangeThickness(Float64* tf)
{
   CHECK_RETVAL(tf);
   return m_Beam->get_H1(tf);
}

STDMETHODIMP CBoxBeamSection::get_MinBottomFlangeThickness(Float64* tf)
{
   CHECK_RETVAL(tf);
   return m_Beam->get_H3(tf);
}

STDMETHODIMP CBoxBeamSection::get_CL2ExteriorWebDistance(DirectionType side, Float64* wd)
{
   CHECK_RETVAL(wd);

   Float64 spacing;
   HRESULT hr = get_WebSpacing(0, &spacing);
   
   *wd = spacing/2.0;

   return hr;
}

STDMETHODIMP CBoxBeamSection::RemoveSacrificalDepth(Float64 sacDepth)
{
   Float64 H1, H4;
   m_Beam->get_H1(&H1);
   m_Beam->get_H4(&H4);
   ATLASSERT(sacDepth < H1);
   ATLASSERT(sacDepth < H4);
   H1 -= sacDepth;
   H4 -= sacDepth;
   m_Beam->put_H1(H1);
   m_Beam->put_H4(H4);
   return S_OK;
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

STDMETHODIMP CBoxBeamSection::GetWebSections(IDblArray** ppY, IDblArray** ppW, IBstrArray** ppDesc)
{
   Float64 W1, W2, W3, W4, H1, H2, H3, H4, H5, H6, H7, F1, F2;
   m_Beam->get_W1(&W1);
   m_Beam->get_W2(&W2);
   m_Beam->get_W3(&W3);
   m_Beam->get_W4(&W4);
   m_Beam->get_H1(&H1);
   m_Beam->get_H2(&H2);
   m_Beam->get_H3(&H3);
   m_Beam->get_H4(&H4);
   m_Beam->get_H5(&H5);
   m_Beam->get_H6(&H6);
   m_Beam->get_H7(&H7);
   m_Beam->get_F1(&F1);
   m_Beam->get_F2(&F2);

   Float64 H = H1 + H2 + H3;

   bool bSmallShearKey = (W1 < W2 / 2 || W4 < W2 / 2) ? true : false;

   CComPtr<IDblArray> y;
   y.CoCreateInstance(CLSID_DblArray);
   y.CopyTo(ppY);

   CComPtr<IDblArray> w;
   w.CoCreateInstance(CLSID_DblArray);
   w.CopyTo(ppW);

   CComPtr<IBstrArray> desc;
   desc.CoCreateInstance(CLSID_BstrArray);
   desc.CopyTo(ppDesc);

   // put values in a vector, then we can sort and eliminate duplicate values
   std::vector<std::tuple<Float64, Float64, CComBSTR>> vWebSections;

   Float64 bw;

   // Working down from the top of the box on the inside void, add web sections at H1, H1+F1, H-H3-F2, and H-H3

   // H1
   if (H1 < H4)
   {
      bw = 2 * (W2 + F1 + W1);
   }
   else if (H1 < H4+H5)
   {
      bw = 2 * (W2 + F1 + (W1 / H5)*(H4 + H5 - H1));
   }
   else
   {
      bw = 2 * (W2 + F1);
   }
   vWebSections.emplace_back(-H1, bw, CComBSTR(_T("Top slab at top of interior fillet")));

   // H1+F1
   if (H1 + F1 < H4)
   {
      bw = 2 * (W2 + W1);
   }
   else if (H1 + F1 < H4 + H5)
   {
      bw = 2 * (W2 + (W1 / H5)*(H4 + H5 - H1 - F1));
   }
   else
   {
      bw = 2 * W2;
   }
   vWebSections.emplace_back(-(H1 + F1), bw, CComBSTR(_T("Top slab at bottom of interior fillet")));

   // H3+F2
   if (H3 + F2 < H7)
   {
      bw = 2*(W2 + W4);
   }
   else if (H3 + F2 < H6 + H7) 
   {
      bw = 2 * (W2 + (W4 / H6)*(H6 + H7 - H3 - F2));
   }
   else
   {
      bw = 2 * W2;
   }
   vWebSections.emplace_back(H3 + F2 - H, bw, CComBSTR(_T("Bottom slab at top of interior fillet")));

   // H3
   if (H3 < H7)
   {
      bw = 2 * (W2 + F2 + W4);
   }
   else if (H3 < H6 + H7)
   {
      bw = 2 * (W2 + F2 + (W4 / H6)*(H6 + H7 - H3 - F2));
   }
   else
   {
      bw = 2 * (W2 + F2);
   }
   vWebSections.emplace_back(H3 - H, bw, CComBSTR(_T("Bottom slab at bottom of interior fillet")));


   // Working down from the top of the box on the exterior edge, add web sections at H4, H4+H5, H-H6-H7, and H-H7

   if (!bSmallShearKey)
   {
      // H4
      if (H1 < H4)
      {
         if (H4 < H1 + F1)
         {
            bw = 2 * (W2 + W1 + (H1 + F1 - H4));
         }
         else
         {
            // H1 + F1 <= H4
            ATLASSERT(::IsLE(H1 + F1, H4));
            bw = 2 * (W2 + W1);
         }
         vWebSections.emplace_back(-H4, bw, CComBSTR(_T("Top exterior flange")));
      }
#if defined _DEBUG
      else
      {
         ATLASSERT(::IsLE(H4, H1)); // H4 <= H1... we don't want this case because bw is fill width of box
      }
#endif

      // H4+H5
      if (H1 < H4 + H5)
      {
         if (H4 + H5 < H1 + F1)
         {
            bw = 2 * (W2 + H1 + F1 - H4 - H5);
         }
         else
         {
            // H1 + F1 <= H4 + H5
            ATLASSERT(::IsLE(H1 + F1, H4 + H5));
            bw = 2 * W2;
         }
         vWebSections.emplace_back(-(H4 + H5), bw, CComBSTR(_T("Top flange at web")));
      }
#if defined _DEBUG
      else
      {
         ATLASSERT(::IsLE(H4 + H5, H1)); // H4+H5 <= H1... we don't want this case because bw is fill width of box
      }
#endif

      // H6+H7
      if (H3 < H6 + H7)
      {
         if (H6 + H7 < H3 + F2)
         {
            bw = 2 * (W2 + (H6 + H7 - H3));
         }
         else
         {
            // H3 + F2 <= H6 + H7
            ATLASSERT(::IsLE(H3 + F2, H6 + H7));
            bw = 2 * W2;
         }
         vWebSections.emplace_back(H6 + H7 - H, bw, CComBSTR(_T("Bottom flange at web")));
      }
#if defined _DEBUG
      else
      {
         ATLASSERT(::IsLE(H6 + H7, H3)); // H6+H7 <= H3... we don't want this case because bw is fill width of box
      }
#endif

      // H7
      if (H3 < H7)
      {
         if (H7 < H3 + F2)
         {
            bw = 2 * (W2 + W4 + (H3 + F2 - H7));
         }
         else
         {
            // H3+F2 <= H7
            ATLASSERT(::IsLE(H3 + F2, H7));
            bw = 2 * (W2 + W4);
         }
         vWebSections.emplace_back(H7 - H, bw, CComBSTR(_T("Bottom exterior flange")));
      }
#if defined _DEBUG
      else
      {
         ATLASSERT(::IsLE(H7, H3)); // H7 <= H3... we don't want this case because bw is fill width of box
      }
#endif
   }

   // sort and remove duplicates at same elevation
   std::sort(std::begin(vWebSections), std::end(vWebSections), std::greater<>());
   auto new_end_iter = std::unique(std::begin(vWebSections), std::end(vWebSections), [](const auto& a, const auto& b) {return ::IsEqual(std::get<0>(a), std::get<0>(b)) && ::IsEqual(std::get<1>(a), std::get<1>(b)); });
   vWebSections.erase(new_end_iter, std::end(vWebSections));

   for (auto& webSection : vWebSections)
   {
      (*ppY)->Add(std::get<0>(webSection));
      (*ppW)->Add(std::get<1>(webSection));
      (*ppDesc)->Add(std::get<2>(webSection));
   }

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::GetWebWidthProjectionsForDebonding(IUnkArray** ppArray)
{
   CHECK_RETOBJ(ppArray);

   Float64 W1, W2, W3, W4, H1, H2, H3, H4, H5, H6, H7, F1, F2;
   m_Beam->get_W1(&W1);
   m_Beam->get_W2(&W2);
   m_Beam->get_W3(&W3);
   m_Beam->get_W4(&W4);
   m_Beam->get_H1(&H1);
   m_Beam->get_H2(&H2);
   m_Beam->get_H3(&H3);
   m_Beam->get_H4(&H4);
   m_Beam->get_H5(&H5);
   m_Beam->get_H6(&H6);
   m_Beam->get_H7(&H7);
   m_Beam->get_F1(&F1);
   m_Beam->get_F2(&F2);

   Float64 H = H1 + H2 + H3;

   CComPtr<IUnkArray> array;
   array.CoCreateInstance(CLSID_UnkArray);

   CComPtr<IRect2d> rect1;
   rect1.CoCreateInstance(CLSID_Rect2d);
   rect1->SetBounds(-W3/2-W2, -W3/2, -H, -H+H3+F2/2);
   array->Add(rect1);

   CComPtr<IRect2d> rect2;
   rect2.CoCreateInstance(CLSID_Rect2d);
   rect2->SetBounds(W3 / 2, W3 / 2 + W2, -H, -H + H3 + F2 / 2);
   array->Add(rect2);

   array.CopyTo(ppArray);

   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IShape implementation
STDMETHODIMP CBoxBeamSection::FurthestPoint(ILine2d* line, IPoint2d** ppPoint, Float64* dist)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->FurthestPoint(line, ppPoint, dist);
}

STDMETHODIMP CBoxBeamSection::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->FurthestDistance(line, pVal);
}

STDMETHODIMP CBoxBeamSection::get_Perimeter(Float64 *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_Perimeter(pVal);
}

STDMETHODIMP CBoxBeamSection::get_ShapeProperties(IShapeProperties* *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_ShapeProperties(pVal);
}

STDMETHODIMP CBoxBeamSection::get_BoundingBox(IRect2d* *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_BoundingBox(pVal);
}

STDMETHODIMP CBoxBeamSection::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CBoxBeamSection::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CBoxBeamSection::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CBoxBeamSection>* clone;
   CComObject<CBoxBeamSection>::CreateInstance(&clone);

   CComPtr<IBoxBeamSection> section = clone;

   CComQIPtr<IShape> beam_shape(m_Beam);
   CComPtr<IShape> clone_beam;
   beam_shape->Clone(&clone_beam);
   CComQIPtr<IBoxBeam> new_beam(clone_beam);
   section->put_Beam(new_beam);

   CComQIPtr<IShape> shape(section);
   (*pClone) = shape;
   (*pClone)->AddRef();

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CBoxBeamSection::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->ClipIn(pRect,pShape);
}

/////////////////////////////////////////////////////////////////////////////
// ICompositeShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CBoxBeamSection::get_Shape(IShape* *pVal)
{
   CHECK_RETOBJ(pVal);
   return this->QueryInterface(IID_IShape, (void**)pVal);
}

STDMETHODIMP CBoxBeamSection::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return this->QueryInterface(IID_IXYPosition, (void**)pVal);
}

STDMETHODIMP CBoxBeamSection::get_Item(IndexType idx,ICompositeShapeItem* *pVal)
{
   CComPtr<ICompositeShape> compShape;
   compShape.CoCreateInstance(CLSID_CompositeShape);

   if (idx == 0)
   {
      CComPtr<IShape> shape;
      m_Beam->GetBoxShape(&shape);
      compShape->AddShape(shape, VARIANT_FALSE);
   }
   else
   {
      CComPtr<IShape> shape;
      m_Beam->GetVoidShape(idx - 1, &shape);
      compShape->AddShape(shape, VARIANT_TRUE);
   }

   compShape->get_Item(0, pVal);
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::get__NewEnum(IUnknown* *pVal)
{
   ATLASSERT(false);
   return E_INVALIDARG;
}

STDMETHODIMP CBoxBeamSection::get_Count(IndexType *pVal)
{
   CHECK_RETVAL(pVal);
   IndexType nVoids;
   m_Beam->get_VoidCount(&nVoids);
   *pVal = nVoids + 1;
   return S_OK;
}

STDMETHODIMP CBoxBeamSection::Remove(IndexType idx)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CBoxBeamSection::Clear()
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CBoxBeamSection::ReplaceEx(IndexType idx,ICompositeShapeItem* pShapeItem)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CBoxBeamSection::Replace(IndexType idx,IShape* pShape)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CBoxBeamSection::AddShapeEx(ICompositeShapeItem* ShapeItem)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CBoxBeamSection::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

// XYPosition
STDMETHODIMP CBoxBeamSection::Offset(Float64 dx,Float64 dy)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->Offset(dx,dy);
}

STDMETHODIMP CBoxBeamSection::OffsetEx(ISize2d* pSize)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->OffsetEx(pSize);
}

STDMETHODIMP CBoxBeamSection::get_LocatorPoint(LocatorPointType lp,IPoint2d** point)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->get_LocatorPoint(lp,point);
}

STDMETHODIMP CBoxBeamSection::put_LocatorPoint(LocatorPointType lp,IPoint2d* point)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->put_LocatorPoint(lp,point);
}

STDMETHODIMP CBoxBeamSection::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->MoveEx(pFrom, pTo);
}

STDMETHODIMP CBoxBeamSection::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   m_Rotation += angle;
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->RotateEx(pPoint, angle);
}

STDMETHODIMP CBoxBeamSection::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_Rotation += angle;
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->Rotate(cx, cy, angle);
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

STDMETHODIMP CBoxBeamSection::GetTopWidth(Float64* pLeft, Float64* pRight)
{
   CHECK_RETOBJ(pLeft);
   CHECK_RETOBJ(pRight);

   return m_Beam->get_TopFlangeWidth(pLeft, pRight);

}

STDMETHODIMP CBoxBeamSection::GetHeight(Float64* pHmin, Float64* pHcl, Float64* pHmax)
{
   Float64 H;
   get_NominalHeight(&H);

   *pHmin = H;
   *pHcl  = H;
   *pHmax = H;

   return S_OK;
}

STDMETHODIMP CBoxBeamSection::GetStressPoints(StressPointType spType, IPoint2dCollection** ppPoints)
{
   CHECK_RETOBJ(ppPoints);
   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   // get boundary points from shape
   CComPtr<IPoint2d> leftTop, leftBottom, rightTop, rightBottom;
   m_Beam->GetBoundaryPoints(&leftTop, &leftBottom, &rightTop, &rightBottom);

   if (spType == spTop)
   {
      points->Add(leftTop);
      points->Add(rightTop);
   }
   else
   {
      points->Add(leftBottom);
      points->Add(rightBottom);
   }

   return points.CopyTo(ppPoints);
}
