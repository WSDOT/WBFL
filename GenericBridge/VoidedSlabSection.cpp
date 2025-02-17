///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright � 1999-2025  Washington State Department of Transportation
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

// VoidedSlabSection.cpp : Implementation of CVoidedSlabSection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "VoidedSlabSection.h"
#include <math.h>
#include <xutility> // for Min

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVoidedSlabSection
HRESULT CVoidedSlabSection::FinalConstruct()
{
   m_Beam.CoCreateInstance(CLSID_VoidedSlab);
   return S_OK;
}

void CVoidedSlabSection::FinalRelease()
{
}

STDMETHODIMP CVoidedSlabSection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVoidedSlabSection,
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

bool CVoidedSlabSection::ValidateWebIndex(WebIndexType idx)
{
   WebIndexType nWebs;
   m_Beam->get_VoidCount(&nWebs);
   nWebs++; // there is one more "web" than voids

   return ( 0 <= idx && idx < nWebs );
}

void CVoidedSlabSection::GetWebs(Float64* pIntWeb,Float64* pExtWeb)
{
   Float64 S, D, W;
   IndexType N;
   m_Beam->get_VoidSpacing(&S);
   m_Beam->get_VoidDiameter(&D);
   m_Beam->get_Width(&W);
   m_Beam->get_VoidCount(&N);

   *pExtWeb = (W - D - (N-1)*S)/2;
   *pIntWeb = S - D;
}


////////////////////////////////////////////////////////////////////////
// IVoidedSlabSection implementation
STDMETHODIMP CVoidedSlabSection::put_Beam(IVoidedSlab* beam)
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

STDMETHODIMP CVoidedSlabSection::get_Beam(IVoidedSlab** beam)
{
   CHECK_RETOBJ(beam);
   (*beam) = m_Beam;
   (*beam)->AddRef();
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IPrecastGirderSection implementation
STDMETHODIMP CVoidedSlabSection::get_GirderShape(IShape** ppShape)
{
   return m_Beam->GetSlabShape(ppShape);
}

STDMETHODIMP CVoidedSlabSection::get_VoidCount(/*[out, retval]*/IndexType* pnVoids)
{
   return m_Beam->get_VoidCount(pnVoids);
}

STDMETHODIMP CVoidedSlabSection::get_VoidShape(/*[in]*/IndexType voidIdx, /*[out, retval]*/IShape** ppShape)
{
   return m_Beam->GetVoidShape(voidIdx, ppShape);
}

STDMETHODIMP CVoidedSlabSection::get_WorkPoint(IPoint2d** ppWorkPoint)
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

STDMETHODIMP CVoidedSlabSection::get_WebCount(WebIndexType* nWebs)
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

STDMETHODIMP CVoidedSlabSection::get_WebLocation(WebIndexType idx,Float64* location)
{
   if ( !ValidateWebIndex(idx) )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(location);

   Float64 S, D, W;
   IndexType N;
   m_Beam->get_VoidSpacing(&S);
   m_Beam->get_VoidDiameter(&D);
   m_Beam->get_Width(&W);
   m_Beam->get_VoidCount(&N);

   Float64 end_web_width, int_web_width;
   end_web_width = 0.5*(W - D - (N-1)*S);
   int_web_width = S - D;

   // location measured from left edge
   if ( idx == 0 )
   {
      *location = end_web_width /2;
   }
   else if ( 0 < idx && idx < N )
   {
      *location = end_web_width + (idx-1)*int_web_width + idx*D + int_web_width /2;
   }
   else
   {
      *location = W - end_web_width/2;
   }

   // location measured from CL of section
   *location -= W/2;

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_WebSpacing(WebIndexType idx,Float64* spacing)
{
   if ( !ValidateWebIndex(idx) )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_VoidSpacing(spacing);
}

STDMETHODIMP CVoidedSlabSection::get_WebThickness(WebIndexType idx,Float64* tWeb)
{
   if ( !ValidateWebIndex(idx) )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(tWeb);

   IndexType nVoids;
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

STDMETHODIMP CVoidedSlabSection::get_MinWebThickness(Float64* tWeb)
{
   CHECK_RETVAL(tWeb);

   IndexType nVoids;
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

STDMETHODIMP CVoidedSlabSection::get_EffectiveWebThickness(Float64* tWeb)
{
   return get_MinWebThickness(tWeb);
}

STDMETHODIMP CVoidedSlabSection::get_WebPlane(WebIndexType idx,IPlane3d** ppPlane)
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

STDMETHODIMP CVoidedSlabSection::get_MatingSurfaceCount(MatingSurfaceIndexType* nMatingSurfaces)
{
   CHECK_RETVAL(nMatingSurfaces);
   *nMatingSurfaces = 1;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_MatingSurfaceLocation(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* location)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   *location = 0;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_MatingSurfaceWidth(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* wMatingSurface)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_Width(wMatingSurface);
}

STDMETHODIMP CVoidedSlabSection::get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile)
{
   return E_NOTIMPL;
}

STDMETHODIMP CVoidedSlabSection::get_TopFlangeCount(FlangeIndexType* nTopFlanges)
{
   CHECK_RETVAL(nTopFlanges);
   *nTopFlanges = 0;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_TopFlangeLocation(FlangeIndexType idx,Float64* location)
{
   ATLASSERT(false); // there is no top flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_TopFlangeWidth(FlangeIndexType idx,Float64* width)
{
   ATLASSERT(false); // there is no top flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_TopFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   ATLASSERT(false); // there is no top flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_TopFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   ATLASSERT(false); // there is no top flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_BottomFlangeCount(FlangeIndexType* nBottomFlanges)
{
   CHECK_RETVAL(nBottomFlanges);
   *nBottomFlanges = 0;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_BottomFlangeLocation(FlangeIndexType idx,Float64* location)
{
   ATLASSERT(false); // there is no Bottom flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_BottomFlangeWidth(FlangeIndexType idx,Float64* width)
{
   ATLASSERT(false); // there is no Bottom flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_BottomFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   ATLASSERT(false); // there is no Bottom flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_BottomFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   ATLASSERT(false); // there is no Bottom flange!!!
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_OverallHeight(Float64* height)
{
   return get_NominalHeight(height);
}

STDMETHODIMP CVoidedSlabSection::get_NominalHeight(Float64* height)
{
   return m_Beam->get_Height(height);
}

STDMETHODIMP CVoidedSlabSection::get_TopWidth(Float64* pLeft, Float64* pRight)
{
   Float64 width;
   m_Beam->get_Width(&width);
   width /= 2.0;

   *pLeft = width;
   *pRight = width;

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_BottomWidth(Float64* pLeft, Float64* pRight)
{
   return get_TopWidth(pLeft, pRight);
}

STDMETHODIMP CVoidedSlabSection::get_ShearWidth(Float64* shearwidth)
{
   CHECK_RETVAL(shearwidth);

   IndexType nVoids;
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

STDMETHODIMP CVoidedSlabSection::get_MinTopFlangeThickness(Float64* tf)
{
   CHECK_RETVAL(tf);
   // There aren't any top flanges for a voided slab. However this parameter
   // is used to determine the deck overhang dimensions when the overhang
   // "tapers to the bottom of the top flange".... Just use the clear distance
   // from the top of the slab to the voids
   Float64 H, D;
   m_Beam->get_Height(&H);
   m_Beam->get_VoidDiameter(&D);
   *tf = (H-D)/2;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_MinBottomFlangeThickness(Float64* tf)
{
   CHECK_RETVAL(tf);
   // There aren't any bottom flanges for a voided slab. 
   // Just use the clear distance from the bottom of the slab to the voids
   Float64 H, D;
   m_Beam->get_Height(&H);
   m_Beam->get_VoidDiameter(&D);
   *tf = (H-D)/2;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_CL2ExteriorWebDistance( DirectionType side, Float64* wd)
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


STDMETHODIMP CVoidedSlabSection::RemoveSacrificalDepth(Float64 sacDepth)
{
   // voids are always centered on beam height. if we reduce
   // the beam height, we move the voids. We don't want to do this.
   // Since the top of the slab is always flat, we can do nothing
   // here and let the external tools use the clipping method
   return S_FALSE;
}

STDMETHODIMP CVoidedSlabSection::get_SplittingZoneDimension(Float64* pSZD)
{
   CHECK_RETVAL(pSZD);

   Float64 w;
   m_Beam->get_Width(&w);

   *pSZD = w;

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::get_SplittingDirection(SplittingDirection* pSD)
{
   CHECK_RETVAL(pSD);
   *pSD = sdHorizontal;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::GetWebSections(IDblArray** ppY, IDblArray** ppW,IBstrArray** ppDesc)
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
      Float64 W, H, D;
      m_Beam->get_Width(&W);
      m_Beam->get_Height(&H);
      m_Beam->get_VoidDiameter(&D);

      Float64 gap = (H - D) / 2;

      (*ppY)->Add(-gap);
      (*ppW)->Add(W);
      (*ppDesc)->Add(CComBSTR(_T("Top of Voids")));

      (*ppY)->Add(-H + gap);
      (*ppW)->Add(W);
      (*ppDesc)->Add(CComBSTR(_T("Bottom of Voids")));
   }

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::GetWebWidthProjectionsForDebonding(IUnkArray** ppArray)
{
   CHECK_RETOBJ(ppArray);

   IndexType nVoids;
   m_Beam->get_VoidCount(&nVoids);

   if (0 < nVoids)
   {
      Float64 W, H, D, S;
      m_Beam->get_Width(&W);
      m_Beam->get_Height(&H);
      m_Beam->get_VoidDiameter(&D);
      m_Beam->get_VoidSpacing(&S);

      Float64 ext_web_width, int_web_width;
      ext_web_width = (W - D - (nVoids-1)*S)/2;
      int_web_width = S - D;

      Float64 bottom = (H - D) / 2;


      CComPtr<IUnkArray> array;
      array.CoCreateInstance(CLSID_UnkArray);

      // Left edge of slab
      CComPtr<IRect2d> rect;
      rect.CoCreateInstance(CLSID_Rect2d);
      rect->SetBounds(-W / 2, -W / 2 + ext_web_width, -H, -H + bottom);
      array->Add(rect);

      // Between interior voids
      WebIndexType nWebs = nVoids + 1;
      for (auto webIdx = 1; webIdx < nWebs - 1; webIdx++)
      {
         Float64 x;
         get_WebLocation(webIdx, &x);

         rect.Release();
         rect.CoCreateInstance(CLSID_Rect2d);
         rect->SetBounds(x - int_web_width / 2, x + int_web_width / 2, -H, -H + bottom);
         array->Add(rect);
      }

      // Right edge of slab
      rect.Release();
      rect.CoCreateInstance(CLSID_Rect2d);
      rect->SetBounds(W / 2 - ext_web_width, W / 2, -H, -H + bottom);
      array->Add(rect);

      array.CopyTo(ppArray);
   }

   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IShape implementation
STDMETHODIMP CVoidedSlabSection::FurthestPoint(ILine2d* line, IPoint2d** ppPoint, Float64* dist)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->FurthestPoint(line, ppPoint, dist);
}

STDMETHODIMP CVoidedSlabSection::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->FurthestDistance(line, pVal);
}

STDMETHODIMP CVoidedSlabSection::get_Perimeter(Float64 *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_Perimeter(pVal);
}

STDMETHODIMP CVoidedSlabSection::get_ShapeProperties(IShapeProperties* *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_ShapeProperties(pVal);
}

STDMETHODIMP CVoidedSlabSection::get_BoundingBox(IRect2d* *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_BoundingBox(pVal);
}

STDMETHODIMP CVoidedSlabSection::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CVoidedSlabSection::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->PointInShape(pPoint, pbResult);
}

STDMETHODIMP CVoidedSlabSection::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CVoidedSlabSection>* clone;
   CComObject<CVoidedSlabSection>::CreateInstance(&clone);

   clone->m_Rotation = m_Rotation;

   CComPtr<IVoidedSlabSection> section = clone;

   CComQIPtr<IShape> beam_shape(m_Beam);
   CComPtr<IShape> clone_beam;
   beam_shape->Clone(&clone_beam);
   CComQIPtr<IVoidedSlab> new_beam(clone_beam);
   section->put_Beam(new_beam);

   CComQIPtr<IShape> shape(section);
   (*pClone) = shape;
   (*pClone)->AddRef();

   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->ClipWithLine(pLine, pShape);
}

STDMETHODIMP CVoidedSlabSection::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->ClipIn(pRect, pShape);
}

/////////////////////////////////////////////////////////////////////////////
// ICompositeShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CVoidedSlabSection::get_Shape(IShape* *pVal)
{
   CHECK_RETOBJ(pVal);
   return this->QueryInterface(IID_IShape, (void**)pVal);
}

STDMETHODIMP CVoidedSlabSection::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return this->QueryInterface(IID_IXYPosition, (void**)pVal);
}

STDMETHODIMP CVoidedSlabSection::get_Item(IndexType idx,ICompositeShapeItem* *pVal)
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

STDMETHODIMP CVoidedSlabSection::get__NewEnum(IUnknown* *pVal)
{
   ATLASSERT(false);
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::get_Count(IndexType *pVal)
{
   CHECK_RETVAL(pVal);
   IndexType nVoids;
   m_Beam->get_VoidCount(&nVoids);
   *pVal = nVoids + 1;
   return S_OK;
}

STDMETHODIMP CVoidedSlabSection::Remove(IndexType idx)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::Clear()
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::ReplaceEx(IndexType idx,ICompositeShapeItem* pShapeItem)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::Replace(IndexType idx,IShape* pShape)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::AddShapeEx(ICompositeShapeItem* ShapeItem)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CVoidedSlabSection::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

// XYPosition
STDMETHODIMP CVoidedSlabSection::Offset(Float64 dx,Float64 dy)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->Offset(dx, dy);
}

STDMETHODIMP CVoidedSlabSection::OffsetEx(ISize2d* pSize)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->OffsetEx(pSize);
}

STDMETHODIMP CVoidedSlabSection::get_LocatorPoint(LocatorPointType lp,IPoint2d** point)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->get_LocatorPoint(lp, point);
}

STDMETHODIMP CVoidedSlabSection::put_LocatorPoint(LocatorPointType lp,IPoint2d* point)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->put_LocatorPoint(lp, point);
}

STDMETHODIMP CVoidedSlabSection::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->MoveEx(pFrom, pTo);
}

STDMETHODIMP CVoidedSlabSection::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   m_Rotation += angle;
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->RotateEx(pPoint, angle);
}

STDMETHODIMP CVoidedSlabSection::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_Rotation += angle;
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->Rotate(cx, cy, angle);
}
