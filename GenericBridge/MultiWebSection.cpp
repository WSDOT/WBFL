///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2023  Washington State Department of Transportation
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

// MultiWebSection.cpp : Implementation of CMultiWebSection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "MultiWebSection.h"
#include <math.h>
#include <xutility> // for Min

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiWebSection
HRESULT CMultiWebSection::FinalConstruct()
{
   m_CompositeShape.CoCreateInstance(CLSID_CompositeShape);
   m_CompositeShape.QueryInterface(&m_Shape);
   m_CompositeShape.QueryInterface(&m_Position);

   m_Beam.CoCreateInstance(CLSID_MultiWeb);
   CComQIPtr<IShape> beamShape(m_Beam);
   ATLASSERT(beamShape != nullptr); // must implement IShape interface
   m_CompositeShape->AddShape(beamShape,VARIANT_FALSE); // solid

   m_Rotation = 0;

   return S_OK;
}

void CMultiWebSection::FinalRelease()
{
}

STDMETHODIMP CMultiWebSection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMultiWebSection,
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

bool CMultiWebSection::ValidateWebIndex(WebIndexType idx)
{
   WebIndexType nWebs;
   get_WebCount(&nWebs);

   return ( 0 <= idx && idx < nWebs );
}

////////////////////////////////////////////////////////////////////////
// IMultiWebSection implementation
STDMETHODIMP CMultiWebSection::put_Beam(IMultiWeb* beam)
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

STDMETHODIMP CMultiWebSection::get_Beam(IMultiWeb** beam)
{
   CHECK_RETOBJ(beam);
   (*beam) = m_Beam;
   (*beam)->AddRef();
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IPrecastGirderSection implementation
STDMETHODIMP CMultiWebSection::get_WorkPoint(IPoint2d** ppWorkPoint)
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

      // the hook point is at the top center of the shape
      pntHookPoint->Clone(ppWorkPoint);

      // apply the rotation to the work point
      (*ppWorkPoint)->RotateEx(pntHookPoint, m_Rotation);
   }

   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_WebCount(WebIndexType* nWebs)
{
   return m_Beam->get_WebCount(nWebs);
}

STDMETHODIMP CMultiWebSection::get_WebLocation(WebIndexType idx,Float64* location)
{
   if ( !ValidateWebIndex(idx) )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(location);

   return m_Beam->get_WebLocation(idx,location);
}

STDMETHODIMP CMultiWebSection::get_WebSpacing(WebIndexType idx,Float64* spacing)
{
   if ( !ValidateWebIndex(idx) )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(spacing);

   Float64 t1,w2;
   m_Beam->get_T1(&t1);
   m_Beam->get_W2(&w2);
   (*spacing) = t1 + w2; // 0.5*t1 + w2 + 0.5*t1

   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_WebThickness(WebIndexType idx,Float64* tWeb)
{
   CHECK_RETVAL(tWeb);

   if ( !ValidateWebIndex(idx) )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_T2(tWeb);
}

STDMETHODIMP CMultiWebSection::get_MinWebThickness(Float64* tWeb)
{
   return get_WebThickness(0,tWeb);
}

STDMETHODIMP CMultiWebSection::get_WebPlane(WebIndexType idx,IPlane3d** ppPlane)
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

STDMETHODIMP CMultiWebSection::get_EffectiveWebThickness(Float64* tWeb)
{
   return get_MinWebThickness(tWeb);
}

STDMETHODIMP CMultiWebSection::get_MatingSurfaceCount(MatingSurfaceIndexType* nMatingSurfaces)
{
   return get_TopFlangeCount(nMatingSurfaces);
}

STDMETHODIMP CMultiWebSection::get_MatingSurfaceLocation(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* location)
{
   return get_TopFlangeLocation(idx,location);
}

STDMETHODIMP CMultiWebSection::get_MatingSurfaceWidth(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* wMatingSurface)
{
   return get_TopFlangeWidth(idx,wMatingSurface);
}

STDMETHODIMP CMultiWebSection::get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile)
{
   return E_NOTIMPL;
}

STDMETHODIMP CMultiWebSection::get_TopFlangeCount(FlangeIndexType* nTopFlanges)
{
   CHECK_RETVAL(nTopFlanges);
   *nTopFlanges = 1;
   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_TopFlangeLocation(FlangeIndexType idx,Float64* location)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   *location = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_TopFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   Float64 left, right;
   get_TopWidth(&left,&right);

   *width = left + right;
   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_TopFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_D1(tFlange);
}

STDMETHODIMP CMultiWebSection::get_TopFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(spacing);

   (*spacing) = 0;

   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_BottomFlangeCount(FlangeIndexType* nBottomFlanges)
{
   CHECK_RETVAL(nBottomFlanges);
   *nBottomFlanges = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_BottomFlangeLocation(FlangeIndexType idx,Float64* location)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   *location = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_BottomFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   *width = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_BottomFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   *tFlange = 0;
   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_BottomFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(spacing);

   (*spacing) = 0;

   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_OverallHeight(Float64* height)
{
   return get_NominalHeight(height);
}

STDMETHODIMP CMultiWebSection::get_NominalHeight(Float64* height)
{
   return m_Beam->get_Height(height);
}

STDMETHODIMP CMultiWebSection::get_TopWidth(Float64* pLeft, Float64* pRight)
{
   Float64 width;
   m_Beam->get_TopFlangeWidth(&width);

   width /= 2.0;

   *pLeft = width;
   *pRight = width;

   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_BottomWidth(Float64* pLeft, Float64* pRight)
{
   CHECK_RETVAL(pLeft);
   CHECK_RETVAL(pRight);

   WebIndexType nWebs;
   get_WebCount(&nWebs);

   Float64 t1, t2, w2;
   m_Beam->get_T1(&t1);
   m_Beam->get_T2(&t2);
   m_Beam->get_W2(&w2);

   Float64 width = nWebs*t1 + (nWebs-1)*w2 - (t1-t2);
   width /= 2.0;

   *pLeft = width;
   *pRight = width;

   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_ShearWidth(Float64* shearwidth)
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

STDMETHODIMP CMultiWebSection::get_MinTopFlangeThickness(Float64* tf)
{
   return m_Beam->get_D1(tf);
}

STDMETHODIMP CMultiWebSection::get_MinBottomFlangeThickness(Float64* tf)
{
   CHECK_IN(tf);

   *tf = 0;

   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_CL2ExteriorWebDistance(DirectionType side, Float64* wd)
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


STDMETHODIMP CMultiWebSection::RemoveSacrificalDepth(Float64 sacDepth)
{
   Float64 D1;
   m_Beam->get_D1(&D1);
   ATLASSERT(sacDepth < D1);
   D1 -= sacDepth;
   m_Beam->put_D1(D1);
   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_SplittingZoneDimension(Float64* pSZD)
{
   CHECK_RETVAL(pSZD);

   Float64 h;
   m_Beam->get_Height(&h);

   *pSZD = h;

   return S_OK;
}

STDMETHODIMP CMultiWebSection::get_SplittingDirection(SplittingDirection* pSD)
{
   CHECK_RETVAL(pSD);
   *pSD = sdVertical;
   return S_OK;
}

STDMETHODIMP CMultiWebSection::GetWebSections(IDblArray** ppY, IDblArray** ppW, IBstrArray** ppDesc)
{
   Float64 D1, T1;
   m_Beam->get_D1(&D1);
   m_Beam->get_T1(&T1);

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
      (*ppY)->Add(-D1);
      (*ppW)->Add(nWebs * T1);
      (*ppDesc)->Add(CComBSTR(_T("Top Flange - Web")));
   }

   return S_OK;
}

STDMETHODIMP CMultiWebSection::GetWebWidthProjectionsForDebonding(IUnkArray** ppArray)
{
   // web width projections for debonding don't apply to this type of section
   CHECK_RETOBJ(ppArray);
   return S_FALSE;
}

////////////////////////////////////////////////////////////////////////
// IShape implementation
STDMETHODIMP CMultiWebSection::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   return m_Shape->FurthestDistance(line,pVal);
}

STDMETHODIMP CMultiWebSection::get_Perimeter(Float64 *pVal)
{
   return m_Shape->get_Perimeter(pVal);
}

STDMETHODIMP CMultiWebSection::get_ShapeProperties(IShapeProperties* *pVal)
{
   return m_Shape->get_ShapeProperties(pVal);
}

STDMETHODIMP CMultiWebSection::get_BoundingBox(IRect2d* *pVal)
{
   return m_Shape->get_BoundingBox(pVal);
}

STDMETHODIMP CMultiWebSection::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   return m_Shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CMultiWebSection::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   return m_Shape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CMultiWebSection::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CMultiWebSection>* clone;
   CComObject<CMultiWebSection>::CreateInstance(&clone);

   clone->m_Rotation = m_Rotation;

   CComPtr<IMultiWebSection> section = clone;

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

STDMETHODIMP CMultiWebSection::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   return m_Shape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CMultiWebSection::ClipIn(IRect2d* pRect,IShape** pShape)
{
   return m_Shape->ClipIn(pRect,pShape);
}

STDMETHODIMP CMultiWebSection::Offset(Float64 dx,Float64 dy)
{
   return m_Position->Offset(dx,dy);
}

STDMETHODIMP CMultiWebSection::OffsetEx(ISize2d* pSize)
{
   return m_Position->OffsetEx(pSize);
}

STDMETHODIMP CMultiWebSection::get_LocatorPoint(LocatorPointType lp,IPoint2d** point)
{
   return m_Position->get_LocatorPoint(lp,point);
}

STDMETHODIMP CMultiWebSection::put_LocatorPoint(LocatorPointType lp,IPoint2d* point)
{
   return m_Position->put_LocatorPoint(lp,point);
}

STDMETHODIMP CMultiWebSection::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   return m_Position->MoveEx(pFrom,pTo);
}

STDMETHODIMP CMultiWebSection::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   m_Rotation += angle;
   return m_Position->RotateEx(pPoint,angle);
}

STDMETHODIMP CMultiWebSection::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_Rotation += angle;
   return m_Position->Rotate(cx,cy,angle);
}

////////////////////////////////////////////////////////////////////////
// ICompositeShape implementation
STDMETHODIMP CMultiWebSection::get__NewEnum(IUnknown* *pVal)
{
   return m_CompositeShape->get__NewEnum(pVal);
}

STDMETHODIMP CMultiWebSection::get_Item(CollectionIndexType idx, ICompositeShapeItem* *pVal)
{
   return m_CompositeShape->get_Item(idx,pVal);
}

STDMETHODIMP CMultiWebSection::ReplaceEx(CollectionIndexType idx,ICompositeShapeItem* pShapeItem)
{
   return m_CompositeShape->ReplaceEx(idx,pShapeItem);
}

STDMETHODIMP CMultiWebSection::Replace(CollectionIndexType idx,IShape* pShape)
{
   return m_CompositeShape->Replace(idx,pShape);
}

STDMETHODIMP CMultiWebSection::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   return m_CompositeShape->AddShape(shape,bVoid);
}

STDMETHODIMP CMultiWebSection::AddShapeEx(ICompositeShapeItem* shapeItem)
{
   return m_CompositeShape->AddShapeEx(shapeItem);
}

STDMETHODIMP CMultiWebSection::Remove(CollectionIndexType idx)
{
   return m_CompositeShape->Remove(idx);
}

STDMETHODIMP CMultiWebSection::Clear()
{
   return m_CompositeShape->Clear();
}

STDMETHODIMP CMultiWebSection::get_Count(CollectionIndexType *pVal)
{
   return m_CompositeShape->get_Count(pVal);
}

STDMETHODIMP CMultiWebSection::get_Shape(IShape* *pVal)
{
   return m_CompositeShape->get_Shape(pVal);
}

STDMETHODIMP CMultiWebSection::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return m_CompositeShape->get_XYPosition(pVal);
}

STDMETHODIMP CMultiWebSection::get_StructuredStorage(IStructuredStorage2* *pStrStg)
{
   return m_CompositeShape->get_StructuredStorage(pStrStg);
}
