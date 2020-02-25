///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

// DeckedSlabBeamSection.cpp : Implementation of CDeckedSlabBeamSection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "DeckedSlabBeamSection.h"
#include <math.h>
#include <xutility> // for Min

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeckedSlabBeamSection
HRESULT CDeckedSlabBeamSection::FinalConstruct()
{
   m_CompositeShape.CoCreateInstance(CLSID_CompositeShape);
   m_CompositeShape.QueryInterface(&m_Shape);
   m_CompositeShape.QueryInterface(&m_Position);

   m_Beam.CoCreateInstance(CLSID_DeckedSlabBeam);
   CComQIPtr<IShape> shape(m_Beam);
   m_CompositeShape->AddShape(shape,VARIANT_FALSE);

   m_Rotation = 0;

   return S_OK;
}

void CDeckedSlabBeamSection::FinalRelease()
{
}

STDMETHODIMP CDeckedSlabBeamSection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDeckedSlabBeamSection,
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


////////////////////////////////////////////////////////////////////////
// IDeckedSlabBeamSection implementation
STDMETHODIMP CDeckedSlabBeamSection::put_Beam(IDeckedSlabBeam* beam)
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

STDMETHODIMP CDeckedSlabBeamSection::get_Beam(IDeckedSlabBeam** beam)
{
   CHECK_RETOBJ(beam);
   (*beam) = m_Beam;
   (*beam)->AddRef();
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IPrecastGirderSection implementation
STDMETHODIMP CDeckedSlabBeamSection::get_WorkPoint(IPoint2d** ppWorkPoint)
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

STDMETHODIMP CDeckedSlabBeamSection::get_WebCount(WebIndexType* nWebs)
{
   CHECK_RETVAL(nWebs);

   *nWebs = 2;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_WebLocation(WebIndexType idx,Float64* location)
{
   CHECK_RETVAL(location);

   Float64 A, B, W;
   m_Beam->get_A(&A);
   m_Beam->get_B(&B);
   m_Beam->get_W(&W);

   Float64 tWeb;
   get_WebThickness(idx,&tWeb);
   Float64 x = (A - 2*B - 2*W)/2 + tWeb/2;

   if (idx==0)
   {
      *location = -x;
   }
   else if (idx==1)
   {
      *location = x;
   }
   else
   {
      return E_INVALIDARG;
   }

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_WebSpacing(WebIndexType idx,Float64* spacing)
{
   Float64 A, B, W;
   m_Beam->get_A(&A);
   m_Beam->get_B(&B);
   m_Beam->get_W(&W);

  if (idx==0)
   {
      *spacing = A - 2*B - W;
      return S_OK;
   }
   else
   {
      return E_INVALIDARG;
   }
}

STDMETHODIMP CDeckedSlabBeamSection::get_WebThickness(WebIndexType idx,Float64* tWeb)
{

   CHECK_RETVAL(tWeb);

   if (idx==0 || idx==1)
   {
      return m_Beam->get_W(tWeb);
   }
   else
   {
      return E_INVALIDARG;
   }
}

STDMETHODIMP CDeckedSlabBeamSection::get_WebPlane(WebIndexType idx,IPlane3d** ppPlane)
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

STDMETHODIMP CDeckedSlabBeamSection::get_MinWebThickness(Float64* tWeb)
{
   CHECK_RETVAL(tWeb);

   return m_Beam->get_W(tWeb);
}

STDMETHODIMP CDeckedSlabBeamSection::get_EffectiveWebThickness(Float64* tWeb)
{
   return m_Beam->get_W(tWeb);
}

STDMETHODIMP CDeckedSlabBeamSection::get_MatingSurfaceCount(MatingSurfaceIndexType* nMatingSurfaces)
{
   CHECK_RETVAL(nMatingSurfaces);
   *nMatingSurfaces = 1;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_MatingSurfaceLocation(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* location)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   *location = 0;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_MatingSurfaceWidth(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* wMatingSurface)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return get_TopWidth(wMatingSurface);
}

STDMETHODIMP CDeckedSlabBeamSection::get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile)
{
   return E_NOTIMPL;
}

STDMETHODIMP CDeckedSlabBeamSection::get_TopFlangeCount(FlangeIndexType* nTopFlanges)
{
   CHECK_RETVAL(nTopFlanges);
   *nTopFlanges = 1;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_TopFlangeLocation(FlangeIndexType idx,Float64* location)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   *location = 0;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_TopFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return get_TopWidth(width);
}

STDMETHODIMP CDeckedSlabBeamSection::get_TopFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_Tt(tFlange);
}

STDMETHODIMP CDeckedSlabBeamSection::get_TopFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(spacing);

   (*spacing) = 0;

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_BottomFlangeCount(FlangeIndexType* nBottomFlanges)
{
   CHECK_RETVAL(nBottomFlanges);
   *nBottomFlanges = 1;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_BottomFlangeLocation(FlangeIndexType idx,Float64* location)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   *location = 0;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_BottomFlangeWidth(FlangeIndexType idx,Float64* width)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return get_BottomWidth(width);
}

STDMETHODIMP CDeckedSlabBeamSection::get_BottomFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_Tb(tFlange);
}

STDMETHODIMP CDeckedSlabBeamSection::get_BottomFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(spacing);

   (*spacing) = 0;
   
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_OverallHeight(Float64* height)
{
   return get_NominalHeight(height);
}

STDMETHODIMP CDeckedSlabBeamSection::get_NominalHeight(Float64* height)
{
   Float64 C, Tt;
   m_Beam->get_C(&C);
   m_Beam->get_Tt(&Tt);
   *height = C + Tt;

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_TopWidth(Float64* width)
{
   // Don't account for shear key
   return m_Beam->get_A(width);
}

STDMETHODIMP CDeckedSlabBeamSection::get_BottomWidth(Float64* width)
{
   Float64 A, B;
   m_Beam->get_A(&A);
   m_Beam->get_B(&B);
   *width = A - 2*B;

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_ShearWidth(Float64* shearwidth)
{
   CHECK_RETVAL(shearwidth);

   Float64 W;
   m_Beam->get_W(&W);
   *shearwidth = 2*W;

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_MinTopFlangeThickness(Float64* tf)
{
   return get_TopFlangeThickness(0,tf);
}

STDMETHODIMP CDeckedSlabBeamSection::get_MinBottomFlangeThickness(Float64* tf)
{
   CHECK_RETVAL(tf);
   *tf = 0;
   return S_OK;

}

STDMETHODIMP CDeckedSlabBeamSection::get_CL2ExteriorWebDistance( DirectionType side, Float64* wd)
{
   CHECK_RETVAL(wd);

   Float64 A, B, W;
   m_Beam->get_A(&A);
   m_Beam->get_B(&B);
   m_Beam->get_W(&W);

   *wd = (A - 2*B - W)/2.0;

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::RemoveSacrificalDepth(Float64 sacDepth)
{
   Float64 Tt;
   m_Beam->get_Tt(&Tt);
   ATLASSERT(sacDepth < Tt);
   Tt -= sacDepth;
   m_Beam->put_Tt(Tt);
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_SplittingZoneDimension(Float64* pSZD)
{
   CHECK_RETVAL(pSZD);

   Float64 A, B;
   m_Beam->get_A(&A);
   m_Beam->get_B(&B);

   *pSZD = A - 2*B;

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_SplittingDirection(SplittingDirection* pSD)
{
   CHECK_RETVAL(pSD);
   *pSD = sdHorizontal;
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IShape implementation
STDMETHODIMP CDeckedSlabBeamSection::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   return m_Shape->FurthestDistance(line,pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get_Perimeter(Float64 *pVal)
{
   return m_Shape->get_Perimeter(pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get_ShapeProperties(IShapeProperties* *pVal)
{
   return m_Shape->get_ShapeProperties(pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get_BoundingBox(IRect2d* *pVal)
{
   return m_Shape->get_BoundingBox(pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   return m_Shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CDeckedSlabBeamSection::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   return m_Shape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CDeckedSlabBeamSection::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CDeckedSlabBeamSection>* clone;
   CComObject<CDeckedSlabBeamSection>::CreateInstance(&clone);

   clone->m_Rotation = m_Rotation;

   CComPtr<IDeckedSlabBeamSection> section = clone;
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

STDMETHODIMP CDeckedSlabBeamSection::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   return m_Shape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CDeckedSlabBeamSection::ClipIn(IRect2d* pRect,IShape** pShape)
{
   return m_Shape->ClipIn(pRect,pShape);
}

/////////////////////////////////////////////////////////////////////////////
// ICompositeShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CDeckedSlabBeamSection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   return m_CompositeShape->get_StructuredStorage(pStg);
}

STDMETHODIMP CDeckedSlabBeamSection::get_Shape(IShape* *pVal)
{
   return m_CompositeShape->get_Shape(pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get_Item(CollectionIndexType idx,ICompositeShapeItem* *pVal)
{
   return m_CompositeShape->get_Item(idx,pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get__NewEnum(IUnknown* *pVal)
{
   return m_CompositeShape->get__NewEnum(pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get_Count(CollectionIndexType *pVal)
{
   return m_CompositeShape->get_Count(pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::Remove(CollectionIndexType idx)
{
   return m_CompositeShape->Remove(idx);
}

STDMETHODIMP CDeckedSlabBeamSection::Clear()
{
   return m_CompositeShape->Clear();
}

STDMETHODIMP CDeckedSlabBeamSection::ReplaceEx(CollectionIndexType idx,ICompositeShapeItem* pShapeItem)
{
   return m_CompositeShape->ReplaceEx(idx,pShapeItem);
}

STDMETHODIMP CDeckedSlabBeamSection::Replace(CollectionIndexType idx,IShape* pShape)
{
   return m_CompositeShape->Replace(idx,pShape);
}

STDMETHODIMP CDeckedSlabBeamSection::AddShapeEx(ICompositeShapeItem* ShapeItem)
{
   return m_CompositeShape->AddShapeEx(ShapeItem);
}

STDMETHODIMP CDeckedSlabBeamSection::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   return m_CompositeShape->AddShape(shape,bVoid);
}

// XYPosition
STDMETHODIMP CDeckedSlabBeamSection::Offset(Float64 dx,Float64 dy)
{
   return m_Position->Offset(dx,dy);
}

STDMETHODIMP CDeckedSlabBeamSection::OffsetEx(ISize2d* pSize)
{
   return m_Position->OffsetEx(pSize);
}

STDMETHODIMP CDeckedSlabBeamSection::get_LocatorPoint(LocatorPointType lp,IPoint2d** point)
{
   return m_Position->get_LocatorPoint(lp,point);
}

STDMETHODIMP CDeckedSlabBeamSection::put_LocatorPoint(LocatorPointType lp,IPoint2d* point)
{
   return m_Position->put_LocatorPoint(lp,point);
}

STDMETHODIMP CDeckedSlabBeamSection::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   return m_Position->MoveEx(pFrom,pTo);
}

STDMETHODIMP CDeckedSlabBeamSection::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   m_Rotation += angle;
   return m_Position->RotateEx(pPoint,angle);
}

STDMETHODIMP CDeckedSlabBeamSection::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_Rotation += angle;
   return m_Position->Rotate(cx,cy,angle);
}
