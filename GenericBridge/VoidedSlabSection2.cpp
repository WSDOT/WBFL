///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2022  Washington State Department of Transportation
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

// VoidedSlabSection2.cpp : Implementation of CVoidedSlabSection2
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "VoidedSlabSection2.h"
#include <math.h>
#include <xutility> // for Min

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVoidedSlabSection2
HRESULT CVoidedSlabSection2::FinalConstruct()
{
   m_Beam.CoCreateInstance(CLSID_VoidedSlab2);
   return S_OK;
}

void CVoidedSlabSection2::FinalRelease()
{
}

STDMETHODIMP CVoidedSlabSection2::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVoidedSlabSection2,
      &IID_IGirderSection,
      &IID_IShape,
      &IID_ICompositeShape,
      &IID_IXYPosition,
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

bool CVoidedSlabSection2::ValidateWebIndex(WebIndexType idx)
{
   WebIndexType nWebs;
   m_Beam->get_VoidCount(&nWebs);
   nWebs++; // there is one more "web" than voids

   return ( 0 <= idx && idx < nWebs );
}

void CVoidedSlabSection2::GetWebs(Float64* pIntWeb,Float64* pExtWeb)
{
   // pIntWeb = width of one interior web
   // pExtWeb = width of one exterior web

   Float64 Si, Se, Di, De, W, C1;
   CollectionIndexType N;
   m_Beam->get_InteriorVoidSpacing(&Si);
   m_Beam->get_InteriorVoidDiameter(&Di);
   m_Beam->get_ExteriorVoidSpacing(&Se);
   m_Beam->get_ExteriorVoidDiameter(&De);
   m_Beam->get_C1(&C1);
   m_Beam->get_Width(&W);
   m_Beam->get_VoidCount(&N);

   if ( N == 0 )
   {
      *pExtWeb = (W-2*C1)/2;
      *pIntWeb = 0;
   }
   else if ( N == 1 )
   {
      *pExtWeb = (W-2*C1-De)/2;
      *pIntWeb = 0;
   }
   else if ( N == 2 )
   {
      *pIntWeb = Se - De;
      *pExtWeb = (W - 2*C1 - Se - De)/2;
   }
   else if ( N == 3 )
   {
      *pIntWeb = Se - Di/2 - De/2;
      *pExtWeb = (W - 2*C1 - 2*Se - De)/2;
   }
   else
   {
      *pIntWeb = Si - Di;
      *pExtWeb = (W - 2*C1 - 2*Se - (N-3)*Si - De)/2;
   }
}


////////////////////////////////////////////////////////////////////////
// IVoidedSlabSection2 implementation
STDMETHODIMP CVoidedSlabSection2::put_Beam(IVoidedSlab2* beam)
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

STDMETHODIMP CVoidedSlabSection2::get_Beam(IVoidedSlab2** beam)
{
   CHECK_RETOBJ(beam);
   (*beam) = m_Beam;
   (*beam)->AddRef();
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IPrecastGirderSection implementation
STDMETHODIMP CVoidedSlabSection2::get_GirderShape(IShape** ppShape)
{
   return m_Beam->GetSlabShape(ppShape);
}

STDMETHODIMP CVoidedSlabSection2::get_VoidCount(/*[out, retval]*/IndexType* pnVoids)
{
   return m_Beam->get_VoidCount(pnVoids);
}

STDMETHODIMP CVoidedSlabSection2::get_VoidShape(/*[in]*/IndexType voidIdx, /*[out, retval]*/IShape** ppShape)
{
   return m_Beam->GetVoidShape(voidIdx, ppShape);
}

STDMETHODIMP CVoidedSlabSection2::get_WorkPoint(IPoint2d** ppWorkPoint)
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

STDMETHODIMP CVoidedSlabSection2::get_WebCount(WebIndexType* nWebs)
{
   CHECK_RETVAL(nWebs);

   *nWebs = 0;
   return S_OK;

   // a voided slab doesn't have webs like and I-beam or a U-beam has webs
   // the correct web count is 0.

   //WebIndexType nVoids;
   //m_Beam->get_VoidCount(&nVoids);

   //*nWebs = nVoids + 1;
   //return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_WebLocation(WebIndexType idx,Float64* location)
{
   if (!ValidateWebIndex(idx))
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(location);

   Float64 S1, S2, D1, D2, W;
   CollectionIndexType N;
   m_Beam->get_ExteriorVoidSpacing(&S1);
   m_Beam->get_InteriorVoidSpacing(&S2);
   m_Beam->get_ExteriorVoidDiameter(&D1);
   m_Beam->get_InteriorVoidDiameter(&D2);
   m_Beam->get_Width(&W);
   m_Beam->get_VoidCount(&N);

   CollectionIndexType nWebs = N + 1;

   Float64 edge_width, between_ext_int_void_width, between_int_void_width;
   if (3 <= N)
   {
      edge_width = (W - (N - 3)*S2 - 2 * S1 - D1) / 2;
      between_ext_int_void_width = S1 - D1 / 2 - D2 / 2;
      between_int_void_width = S2 - D2;
   }
   else
   {
      if (N == 0)
      {
         edge_width = W / 2;
         between_ext_int_void_width = 0;
         between_int_void_width = 0;
      }
      else if (N == 1)
      {
         edge_width = W / 2 - D1 / 2;
         between_ext_int_void_width = 0;
         between_int_void_width = 0;
      }
      else
      {
         edge_width = W / 2 - D1 / 2 - S1 / 2;
         between_ext_int_void_width = S1 - D1;
         between_int_void_width = 0;
      }
   }

   // location measured from left edge
   if (idx == 0)
   {
      // left exterior web
      *location = -W / 2 + edge_width / 2;
   }
   else if (1 == idx)
   {
      // first interior web between exterior and interior void
      *location = -W / 2 + edge_width + D1 + between_ext_int_void_width / 2;
   }
   else if (2 <= idx && idx <= nWebs - 3)
   {
      // between interior voids
      *location = -W / 2 + edge_width + D1 + between_ext_int_void_width + (idx - 2)*(D2 + between_int_void_width) + D2 + between_int_void_width / 2;
   }
   else if (idx == nWebs - 2)
   {
      // last exterior web between exterior and interior void
      *location = W / 2 - (edge_width + D1 + between_ext_int_void_width / 2);
   }
   else if (idx == nWebs - 1)
   {
      // right exterior web
      *location = W / 2 - edge_width / 2;
   }

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_WebSpacing(WebIndexType idx,Float64* spacing)
{
   if ( !ValidateWebIndex(idx) )
   {
      return E_INVALIDARG;
   }

   CollectionIndexType N;
   m_Beam->get_VoidCount(&N);

   if ( idx == 0 || idx == 1 || idx == N || idx == N-1 )
   {
      return m_Beam->get_ExteriorVoidSpacing(spacing);
   }
   else
   {
      return m_Beam->get_InteriorVoidSpacing(spacing);
   }
}

STDMETHODIMP CVoidedSlabSection2::get_WebThickness(WebIndexType idx,Float64* tWeb)
{
   if ( !ValidateWebIndex(idx) )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(tWeb);

   CollectionIndexType nVoids;
   m_Beam->get_VoidCount(&nVoids);

   if ( nVoids == 0 )
   {
      m_Beam->get_Width(tWeb);
   }
   else
   {
      Float64 end_webs, int_webs;
      GetWebs(&int_webs,&end_webs);

      if ( idx == 0 || idx == nVoids)
      {
         *tWeb = end_webs;
      }
      else
      {
         *tWeb = int_webs;
      }
   }

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_MinWebThickness(Float64* tWeb)
{
   CHECK_RETVAL(tWeb);

   CollectionIndexType nVoids;
   m_Beam->get_VoidCount(&nVoids);

   if ( nVoids == 0 )
   {
      m_Beam->get_Width(tWeb);
   }
   else
   {
      Float64 end_webs, int_webs;
      GetWebs(&int_webs,&end_webs);

      *tWeb = Min(int_webs,end_webs);
   }

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_EffectiveWebThickness(Float64* tWeb)
{
   return get_MinWebThickness(tWeb);
}

STDMETHODIMP CVoidedSlabSection2::get_WebPlane(WebIndexType idx,IPlane3d** ppPlane)
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

STDMETHODIMP CVoidedSlabSection2::get_MatingSurfaceCount(MatingSurfaceIndexType* nMatingSurfaces)
{
   CHECK_RETVAL(nMatingSurfaces);
   *nMatingSurfaces = 1;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_MatingSurfaceLocation(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* location)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   *location = 0;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_MatingSurfaceWidth(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* wMatingSurface)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_Width(wMatingSurface);
}

STDMETHODIMP CVoidedSlabSection2::get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile)
{
   return E_NOTIMPL;
}

STDMETHODIMP CVoidedSlabSection2::get_TopFlangeCount(FlangeIndexType* nTopFlanges)
{
   CHECK_RETVAL(nTopFlanges);
   *nTopFlanges = 0;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_TopFlangeLocation(FlangeIndexType idx,Float64* location)
{
   ATLASSERT(false); // there is no top flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::get_TopFlangeWidth(FlangeIndexType idx,Float64* width)
{
   ATLASSERT(false); // there is no top flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::get_TopFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   ATLASSERT(false); // there is no top flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::get_TopFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   ATLASSERT(false); // there is no top flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::get_BottomFlangeCount(FlangeIndexType* nBottomFlanges)
{
   CHECK_RETVAL(nBottomFlanges);
   *nBottomFlanges = 0;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_BottomFlangeLocation(FlangeIndexType idx,Float64* location)
{
   ATLASSERT(false); // there is no Bottom flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::get_BottomFlangeWidth(FlangeIndexType idx,Float64* width)
{
   ATLASSERT(false); // there is no Bottom flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::get_BottomFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   ATLASSERT(false); // there is no Bottom flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::get_BottomFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   ATLASSERT(false); // there is no Bottom flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::get_OverallHeight(Float64* height)
{
   return get_NominalHeight(height);
}

STDMETHODIMP CVoidedSlabSection2::get_NominalHeight(Float64* height)
{
   return m_Beam->get_Height(height);
}

STDMETHODIMP CVoidedSlabSection2::get_TopWidth(Float64* pLeft, Float64* pRight)
{
   Float64 width;
   m_Beam->get_Width(&width);
   width /= 2.0;

   *pLeft = width;
   *pRight = width;

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_BottomWidth(Float64* pLeft, Float64* pRight)
{
   return get_TopWidth(pLeft, pRight);
}

STDMETHODIMP CVoidedSlabSection2::get_ShearWidth(Float64* shearwidth)
{
   CHECK_RETVAL(shearwidth);

   CollectionIndexType nVoids;
   m_Beam->get_VoidCount(&nVoids);

   if ( nVoids == 0 )
   {
      m_Beam->get_Width(shearwidth);
   }
   else
   {
      Float64 end_webs, int_webs;
      GetWebs(&int_webs,&end_webs);

      *shearwidth = 2*end_webs + (nVoids-1)*int_webs;
   }

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_MinTopFlangeThickness(Float64* tf)
{
   CHECK_RETVAL(tf);
   // There aren't any top flanges for a voided slab. However this parameter
   // is used to determine the deck overhang dimensions when the overhang
   // "tapers to the bottom of the top flange".... Just use the clear distance
   // from the top of the slab to the voids
   Float64 H, D1, H1, D2, H2;
   m_Beam->get_Height(&H);
   m_Beam->get_ExteriorVoidDiameter(&D1);
   m_Beam->get_ExteriorVoidElevation(&H1);
   m_Beam->get_InteriorVoidDiameter(&D2);
   m_Beam->get_InteriorVoidElevation(&H2);

   Float64 extTF = H - (H1+D1/2);
   Float64 intTF = H - (H2+D2/2);
   *tf = Min(extTF,intTF);
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_MinBottomFlangeThickness(Float64* tf)
{
   CHECK_RETVAL(tf);
   // There aren't any bottom flanges for a voided slab. 
   // Just use the clear distance from the bottom of the slab to the voids
   Float64 D1, H1, D2, H2;
   m_Beam->get_ExteriorVoidDiameter(&D1);
   m_Beam->get_ExteriorVoidElevation(&H1);
   m_Beam->get_InteriorVoidDiameter(&D2);
   m_Beam->get_InteriorVoidElevation(&H2);

   Float64 extBF = H1-D1/2;
   Float64 intBF = H2-D2/2;
   *tf = Min(extBF,intBF);
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_CL2ExteriorWebDistance( DirectionType side, Float64* wd)
{
   HRESULT hr;
   CHECK_RETVAL(wd);

   WebIndexType nWebs;
   WebIndexType nVoids;
   hr = m_Beam->get_VoidCount(&nVoids);
   if (FAILED(hr))
   {
      return hr;
   }

   nWebs = nVoids + 1;


   if (nWebs == 1)
   {
      *wd = 0.0;
   }
   else
   {
      // multiweb
      Float64 webwid = 0;

      for (WebIndexType is = 0; is < nWebs-1; is++)
      {
         Float64 spacing;

         hr = get_WebSpacing(is, &spacing);
         if (FAILED(hr))
         {
            return hr;
         }

         webwid += spacing;
      }

      *wd = webwid/2.0;
   }

   return S_OK;
}


STDMETHODIMP CVoidedSlabSection2::RemoveSacrificalDepth(Float64 sacDepth)
{
   Float64 H, C2;
   m_Beam->get_Height(&H);
   m_Beam->get_C2(&C2);
   ATLASSERT(sacDepth < H);
   H -= sacDepth;
   C2 -= sacDepth;
   if (C2 < 0)
   {
      C2 = 0;
   }
   m_Beam->put_Height(H);
   m_Beam->put_C2(C2);
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_SplittingZoneDimension(Float64* pSZD)
{
   CHECK_RETVAL(pSZD);

   Float64 w;
   m_Beam->get_Width(&w);

   *pSZD = w;

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::get_SplittingDirection(SplittingDirection* pSD)
{
   CHECK_RETVAL(pSD);
   *pSD = sdHorizontal;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::GetWebSections(IDblArray** ppY, IDblArray** ppW,IBstrArray** ppDesc)
{
   CComPtr<IDblArray> y;
   y.CoCreateInstance(CLSID_DblArray);
   y.CopyTo(ppY);

   CComPtr<IDblArray> w;
   w.CoCreateInstance(CLSID_DblArray);
   w.CopyTo(ppW);

   CComPtr<IBstrArray> desc;
   desc.CoCreateInstance(CLSID_BstrArray);
   desc.CopyTo(ppDesc);
   
   IndexType nVoids;
   m_Beam->get_VoidCount(&nVoids);
   if (0 < nVoids)
   {
      Float64 W, H, D1, H1, D2, H2;
      m_Beam->get_Width(&W);
      m_Beam->get_Height(&H);
      m_Beam->get_ExteriorVoidDiameter(&D1);
      m_Beam->get_ExteriorVoidElevation(&H1);
      m_Beam->get_InteriorVoidDiameter(&D2);
      m_Beam->get_InteriorVoidElevation(&H2);

      Float64 y1 = -(H - H1 - D1 / 2);
      Float64 y2 = -(H - H2 - D2 / 2);
      Float64 y3 = -(H - H1 + D1 / 2);
      Float64 y4 = -(H - H2 + D2 / 2);

      (*ppY)->Add(Max(y1, y2));
      (*ppW)->Add(W);
      (*ppDesc)->Add(CComBSTR(_T("Top of Voids")));

      (*ppY)->Add(Min(y3, y4));
      (*ppW)->Add(W);
      (*ppDesc)->Add(CComBSTR(_T("Bottom of Voids")));
   }

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::GetWebWidthProjectionsForDebonding(IUnkArray** ppArray)
{
   CHECK_RETOBJ(ppArray);

   IndexType nVoids;
   m_Beam->get_VoidCount(&nVoids);

   if (0 < nVoids)
   {
      Float64 W, H, H1, H2, S1, S2, D1, D2;
      m_Beam->get_Width(&W);
      m_Beam->get_Height(&H);
      m_Beam->get_ExteriorVoidDiameter(&D1);
      m_Beam->get_ExteriorVoidElevation(&H1);
      m_Beam->get_InteriorVoidDiameter(&D2);
      m_Beam->get_InteriorVoidElevation(&H2);
      m_Beam->get_ExteriorVoidSpacing(&S1);
      m_Beam->get_InteriorVoidSpacing(&S2);

      IndexType nExtVoids = (nVoids == 1 ? 1 : 2);
      IndexType nIntVoids = nVoids - nExtVoids;

      // distance from exterior void to edge of slab
      Float64 edge;
      if (nExtVoids == 1)
      {
         edge = (W - D1) / 2.0;
      }
      else if (nExtVoids == 2 && nIntVoids == 0)
      {
         edge = (W - (nExtVoids - 1)*(S1 + D1)) / 2.0;
      }
      else
      {
         edge = (W - nExtVoids*S1 - (nIntVoids - 1)*S2 - D1) / 2.0;
      }

      // distance from bottom of void to bottom of slab
      Float64 bottom = Min(H1 - D1 / 2, H1 - D2 / 2);

      CComPtr<IUnkArray> array;
      array.CoCreateInstance(CLSID_UnkArray);

      // Left edge of slab
      CComPtr<IRect2d> rect;
      rect.CoCreateInstance(CLSID_Rect2d);
      rect->SetBounds(-W / 2, -W / 2 + edge, -H, -H + bottom);
      array->Add(rect);

      WebIndexType nWebs = nVoids + 1;
      for (auto webIdx = 1; webIdx < nWebs - 1; webIdx++)
      {
         Float64 x;
         get_WebLocation(webIdx, &x);

         Float64 web_width;
         if (nVoids == 2)
         {
            web_width = S1 - D1;
         }
         else
         {
            web_width = (webIdx == 1 || webIdx == nWebs - 2) ? (S1 - (D1 + D2) / 2) : S2 - D2;
         }

         rect.Release();
         rect.CoCreateInstance(CLSID_Rect2d);
         rect->SetBounds(x - web_width / 2, x + web_width / 2, -H, -H + bottom);
         array->Add(rect);
      }

      // Right edge of slab
      rect.Release();
      rect.CoCreateInstance(CLSID_Rect2d);
      rect->SetBounds(W / 2 - edge, W / 2, -H, -H + bottom);
      array->Add(rect);

      array.CopyTo(ppArray);
   }

   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IShape implementation
STDMETHODIMP CVoidedSlabSection2::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->FurthestDistance(line, pVal);
}

STDMETHODIMP CVoidedSlabSection2::get_Perimeter(Float64 *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_Perimeter(pVal);
}

STDMETHODIMP CVoidedSlabSection2::get_ShapeProperties(IShapeProperties* *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_ShapeProperties(pVal);
}

STDMETHODIMP CVoidedSlabSection2::get_BoundingBox(IRect2d* *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_BoundingBox(pVal);
}

STDMETHODIMP CVoidedSlabSection2::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CVoidedSlabSection2::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->PointInShape(pPoint, pbResult);
}

STDMETHODIMP CVoidedSlabSection2::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CVoidedSlabSection2>* clone;
   CComObject<CVoidedSlabSection2>::CreateInstance(&clone);

   clone->m_Rotation = m_Rotation;

   CComPtr<IVoidedSlabSection2> section = clone;

   CComQIPtr<IShape> beam_shape(m_Beam);
   CComPtr<IShape> clone_beam;
   beam_shape->Clone(&clone_beam);
   CComQIPtr<IVoidedSlab2> new_beam(clone_beam);
   section->put_Beam(new_beam);

   CComQIPtr<IShape> shape(section);
   (*pClone) = shape;
   (*pClone)->AddRef();

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->ClipWithLine(pLine, pShape);
}

STDMETHODIMP CVoidedSlabSection2::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->ClipIn(pRect, pShape);
}

/////////////////////////////////////////////////////////////////////////////
// ICompositeShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CVoidedSlabSection2::get_Shape(IShape* *pVal)
{
   CHECK_RETOBJ(pVal);
   return this->QueryInterface(IID_IShape, (void**)pVal);
}

STDMETHODIMP CVoidedSlabSection2::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return this->QueryInterface(IID_IXYPosition, (void**)pVal);
}

STDMETHODIMP CVoidedSlabSection2::get_Item(CollectionIndexType idx,ICompositeShapeItem* *pVal)
{
   CComPtr<ICompositeShape> compShape;
   compShape.CoCreateInstance(CLSID_CompositeShape);

   if (idx == 0)
   {
      CComPtr<IShape> shape;
      m_Beam->GetSlabShape(&shape);
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

STDMETHODIMP CVoidedSlabSection2::get__NewEnum(IUnknown* *pVal)
{
   ATLASSERT(false);
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::get_Count(CollectionIndexType *pVal)
{
   CHECK_RETVAL(pVal);
   IndexType nVoids;
   m_Beam->get_VoidCount(&nVoids);
   *pVal = nVoids + 1;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection2::Remove(CollectionIndexType idx)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::Clear()
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::ReplaceEx(CollectionIndexType idx,ICompositeShapeItem* pShapeItem)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::Replace(CollectionIndexType idx,IShape* pShape)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::AddShapeEx(ICompositeShapeItem* ShapeItem)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection2::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

// XYPosition
STDMETHODIMP CVoidedSlabSection2::Offset(Float64 dx,Float64 dy)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->Offset(dx, dy);
}

STDMETHODIMP CVoidedSlabSection2::OffsetEx(ISize2d* pSize)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->OffsetEx(pSize);
}

STDMETHODIMP CVoidedSlabSection2::get_LocatorPoint(LocatorPointType lp,IPoint2d** point)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->get_LocatorPoint(lp, point);
}

STDMETHODIMP CVoidedSlabSection2::put_LocatorPoint(LocatorPointType lp,IPoint2d* point)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->put_LocatorPoint(lp, point);
}

STDMETHODIMP CVoidedSlabSection2::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->MoveEx(pFrom, pTo);
}

STDMETHODIMP CVoidedSlabSection2::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   m_Rotation += angle;
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->RotateEx(pPoint, angle);
}

STDMETHODIMP CVoidedSlabSection2::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_Rotation += angle;
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->Rotate(cx, cy, angle);
}
