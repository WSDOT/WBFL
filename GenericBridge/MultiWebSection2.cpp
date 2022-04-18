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

// MultiWebSection2.cpp : Implementation of CMultiWebSection2
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "MultiWebSection2.h"
#include <math.h>
#include <xutility> // for Min

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiWebSection2
HRESULT CMultiWebSection2::FinalConstruct()
{
   m_CompositeShape.CoCreateInstance(CLSID_CompositeShape);
   m_CompositeShape.QueryInterface(&m_Shape);
   m_CompositeShape.QueryInterface(&m_Position);

   m_Beam.CoCreateInstance(CLSID_MultiWeb2);
   CComQIPtr<IShape> beamShape(m_Beam);
   ATLASSERT(beamShape != nullptr); // must implement IShape interface
   m_CompositeShape->AddShape(beamShape,VARIANT_FALSE); // solid

   m_Rotation = 0;

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
   m_Shape = clone;

   m_CompositeShape->Replace(0,m_Shape);

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
STDMETHODIMP CMultiWebSection2::get_WorkPoint(IPoint2d** ppWorkPoint)
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

STDMETHODIMP CMultiWebSection2::get_WebCount(WebIndexType* nWebs)
{
   return m_Beam->get_WebCount(nWebs);
}

STDMETHODIMP CMultiWebSection2::get_WebLocation(WebIndexType idx,Float64* location)
{
   if ( !ValidateWebIndex(idx) )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(location);

   return m_Beam->get_WebLocation(idx,location);
}

STDMETHODIMP CMultiWebSection2::get_WebSpacing(WebIndexType idx,Float64* spacing)
{
   if ( !ValidateSpacingIndex(idx) )
   {
      return E_INVALIDARG;
   }

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
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_AvgWebWidth(idx,tWeb);
}

STDMETHODIMP CMultiWebSection2::get_MinWebThickness(Float64* tWeb)
{
   CHECK_RETVAL(tWeb);

   Float64 w1, w2;
   get_WebThickness(0,&w1);
   get_WebThickness(1,&w2);

   *tWeb = Min(w1,w2);

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_WebPlane(WebIndexType idx,IPlane3d** ppPlane)
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

STDMETHODIMP CMultiWebSection2::get_EffectiveWebThickness(Float64* tWeb)
{
   return get_MinWebThickness(tWeb);
}

STDMETHODIMP CMultiWebSection2::get_MatingSurfaceCount(MatingSurfaceIndexType* nMatingSurfaces)
{
   return get_TopFlangeCount(nMatingSurfaces);
}

STDMETHODIMP CMultiWebSection2::get_MatingSurfaceLocation(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* location)
{
   return get_TopFlangeLocation(idx,location);
}

STDMETHODIMP CMultiWebSection2::get_MatingSurfaceWidth(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* wMatingSurface)
{
   return get_TopFlangeWidth(idx,wMatingSurface);
}

STDMETHODIMP CMultiWebSection2::get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile)
{
   return E_NOTIMPL;
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
   {
      return E_INVALIDARG;
   }

   *location = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_TopFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   Float64 left, right;
   get_TopWidth(&left, &right);

   *width = left + right;
   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_TopFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_H3(tFlange);
}

STDMETHODIMP CMultiWebSection2::get_TopFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

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
   {
      return E_INVALIDARG;
   }

   *location = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_BottomFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   *width = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_BottomFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   *tFlange = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_BottomFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(spacing);

   (*spacing) = 0;

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_OverallHeight(Float64* height)
{
   return get_NominalHeight(height);
}

STDMETHODIMP CMultiWebSection2::get_NominalHeight(Float64* height)
{
   return m_Beam->get_Height(height);
}

STDMETHODIMP CMultiWebSection2::get_TopWidth(Float64* pLeft, Float64* pRight)
{
   Float64 width;
   m_Beam->get_TopFlangeWidth(&width);
   width /= 2.0;

   *pLeft = width;
   *pRight = width;

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::get_BottomWidth(Float64* pLeft, Float64* pRight)
{
   return get_TopWidth(pLeft, pRight);
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
   CHECK_RETVAL(wd);

   WebIndexType nwebs;
   hr = get_WebCount(&nwebs);
   if (FAILED(hr))
   {
      return hr;
   }

   if (nwebs==1)
   {
      *wd = 0.0;
   }
   else
   {
      // multiweb
      Float64 webwid = 0;

      for (WebIndexType is = 0; is<nwebs-1; is++)
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


STDMETHODIMP CMultiWebSection2::RemoveSacrificalDepth(Float64 sacDepth)
{
   Float64 H3;
   m_Beam->get_H3(&H3);
   ATLASSERT(sacDepth < H3);
   H3 -= sacDepth;
   m_Beam->put_H3(H3);
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

STDMETHODIMP CMultiWebSection2::GetWebSections(IDblArray** ppY, IDblArray** ppW,IBstrArray** ppDesc)
{
   Float64 H2, H3, F1, F2, T1, T2, T3, T4, T5;
   m_Beam->get_H2(&H2);
   m_Beam->get_H3(&H3);
   m_Beam->get_F1(&F1);
   m_Beam->get_F2(&F2);
   m_Beam->get_T1(&T1);
   m_Beam->get_T2(&T2);
   m_Beam->get_T3(&T3);
   m_Beam->get_T4(&T4);
   m_Beam->get_T5(&T5);

   WebIndexType nWebs;
   m_Beam->get_WebCount(&nWebs);

   CComPtr<IDblArray> y;
   y.CoCreateInstance(CLSID_DblArray);
   y.CopyTo(ppY);

   CComPtr<IDblArray> w;
   w.CoCreateInstance(CLSID_DblArray);
   w.CopyTo(ppW);

   CComPtr<IBstrArray> desc;
   desc.CoCreateInstance(CLSID_BstrArray);
   desc.CopyTo(ppDesc);

   if (0 < nWebs)
   {
      (*ppY)->Add(-(H2 + H3));
      if (1 <= nWebs && nWebs <= 2)
      {
         (*ppW)->Add(nWebs*(T1 + T2 + T3 + 2*F1));
      }
      else
      {
         ATLASSERT(2 < nWebs);
         (*ppW)->Add(2 * (T1 + T2 + T3 + 2*F2) + (nWebs - 2)*(2*T4 + T5 + 2*F2));
      }
      (*ppDesc)->Add(CComBSTR(_T("Top Flange - Fillet")));

      (*ppY)->Add(-(H2 + H3 + F1));
      if (1 <= nWebs && nWebs <= 2)
      {
         (*ppW)->Add(nWebs*(T1 + T2 + T3));
      }
      else
      {
         ATLASSERT(2 < nWebs);
         (*ppW)->Add(2 * (T1 + T2 + T3) + (nWebs - 2)*(2 * T4 + T5));
      }
      (*ppDesc)->Add(CComBSTR(_T("Top Fillet - Web")));
   }

   return S_OK;
}

STDMETHODIMP CMultiWebSection2::GetWebWidthProjectionsForDebonding(IUnkArray** ppArray)
{
   // web width projections for debonding don't apply to this type of section
   CHECK_RETOBJ(ppArray);
   return S_FALSE;
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

   clone->m_Rotation = m_Rotation;

   CComPtr<IMultiWebSection2> section = clone;

   section->put_Beam(m_Beam);

   IndexType nShapes;
   m_CompositeShape->get_Count(&nShapes);

   CComQIPtr<ICompositeShape> compShape(section);
   for ( IndexType shapeIdx = 1; shapeIdx < nShapes; shapeIdx++ )
   {
      CComPtr<ICompositeShapeItem> compShapeItem;
      m_CompositeShape->get_Item(shapeIdx,&compShapeItem);

      CComPtr<IShape> shapeItem;
      compShapeItem->get_Shape(&shapeItem);

      VARIANT_BOOL bVoid;
      compShapeItem->get_Void(&bVoid);

      CComPtr<IShape> shapeItemClone;
      shapeItem->Clone(&shapeItemClone);

      compShape->AddShape(shapeItemClone,bVoid);
   }

   CComQIPtr<IShape> shape(section);
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
   m_Rotation += angle;
   return m_Position->RotateEx(pPoint,angle);
}

STDMETHODIMP CMultiWebSection2::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_Rotation += angle;
   return m_Position->Rotate(cx,cy,angle);
}

////////////////////////////////////////////////////////////////////////
// ICompositeShape implementation
STDMETHODIMP CMultiWebSection2::get__NewEnum(IUnknown* *pVal)
{
   return m_CompositeShape->get__NewEnum(pVal);
}

STDMETHODIMP CMultiWebSection2::get_Item(CollectionIndexType idx, ICompositeShapeItem* *pVal)
{
   return m_CompositeShape->get_Item(idx,pVal);
}

STDMETHODIMP CMultiWebSection2::ReplaceEx(CollectionIndexType idx,ICompositeShapeItem* pShapeItem)
{
   return m_CompositeShape->ReplaceEx(idx,pShapeItem);
}

STDMETHODIMP CMultiWebSection2::Replace(CollectionIndexType idx,IShape* pShape)
{
   return m_CompositeShape->Replace(idx,pShape);
}

STDMETHODIMP CMultiWebSection2::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   return m_CompositeShape->AddShape(shape,bVoid);
}

STDMETHODIMP CMultiWebSection2::AddShapeEx(ICompositeShapeItem* shapeItem)
{
   return m_CompositeShape->AddShapeEx(shapeItem);
}

STDMETHODIMP CMultiWebSection2::Remove(CollectionIndexType idx)
{
   return m_CompositeShape->Remove(idx);
}

STDMETHODIMP CMultiWebSection2::Clear()
{
   return m_CompositeShape->Clear();
}

STDMETHODIMP CMultiWebSection2::get_Count(CollectionIndexType *pVal)
{
   return m_CompositeShape->get_Count(pVal);
}

STDMETHODIMP CMultiWebSection2::get_Shape(IShape* *pVal)
{
   return m_CompositeShape->get_Shape(pVal);
}

STDMETHODIMP CMultiWebSection2::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return m_CompositeShape->get_XYPosition(pVal);
}

STDMETHODIMP CMultiWebSection2::get_StructuredStorage(IStructuredStorage2* *pStrStg)
{
   return m_CompositeShape->get_StructuredStorage(pStrStg);
}
