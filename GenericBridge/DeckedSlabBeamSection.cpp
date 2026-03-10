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

// DeckedSlabBeamSection.cpp : Implementation of CDeckedSlabBeamSection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "DeckedSlabBeamSection.h"
#include <math.h>
#include <xutility> // for Min


/////////////////////////////////////////////////////////////////////////////
// CDeckedSlabBeamSection
HRESULT CDeckedSlabBeamSection::FinalConstruct()
{
   m_Beam.CoCreateInstance(CLSID_DeckedSlabBeam);
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
STDMETHODIMP CDeckedSlabBeamSection::get_GirderShape(IShape** ppShape)
{
   return m_Beam->GetSlabShape(ppShape);
}

STDMETHODIMP CDeckedSlabBeamSection::get_VoidCount(/*[out, retval]*/IndexType* pnVoids)
{
   return m_Beam->get_VoidCount(pnVoids);
}

STDMETHODIMP CDeckedSlabBeamSection::get_VoidShape(/*[in]*/IndexType voidIdx, /*[out, retval]*/IShape** ppShape)
{
   return m_Beam->GetVoidShape(voidIdx, ppShape);
}

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

   Float64 left, right;
   get_TopWidth(&left, &right);

   *wMatingSurface = left + right;

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile)
{
   //ATLASSERT(false); It is valid to not have a mating surface profile... top of girder becomes the profile
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

   Float64 left, right;
   get_TopWidth(&left, &right);

   *width = left + right;

   return S_OK;
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

   Float64 left, right;
   get_BottomWidth(&left, &right);

   *width = left + right;

   return S_OK;
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

STDMETHODIMP CDeckedSlabBeamSection::get_TopWidth(Float64* pLeft, Float64* pRight)
{
   // Don't account for shear key
   Float64 width;
   m_Beam->get_A(&width);
   width /= 2.0;

   *pLeft = width;
   *pRight = width;

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get_BottomWidth(Float64* pLeft, Float64* pRight)
{
   Float64 A, B;
   m_Beam->get_A(&A);
   m_Beam->get_B(&B);
   Float64 width = A - 2*B;
   width /= 2.0;

   *pLeft = width;
   *pRight = width;

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

STDMETHODIMP CDeckedSlabBeamSection::GetWebSections(IDblArray** ppY, IDblArray** ppW,IBstrArray** ppDesc)
{
   Float64 C, Tt, Tb, W;
   m_Beam->get_C(&C);
   m_Beam->get_Tt(&Tt);
   m_Beam->get_Tb(&Tb);
   m_Beam->get_W(&W);

   Float64 H = C + Tt;

   CComPtr<IDblArray> y;
   y.CoCreateInstance(CLSID_DblArray);
   y.CopyTo(ppY);

   CComPtr<IDblArray> w;
   w.CoCreateInstance(CLSID_DblArray);
   w.CopyTo(ppW);

   CComPtr<IBstrArray> desc;
   desc.CoCreateInstance(CLSID_BstrArray);
   desc.CopyTo(ppDesc);

   (*ppY)->Add(-Tt);
   (*ppW)->Add(2 * W);
   (*ppDesc)->Add(CComBSTR(_T("Top Flange - Web")));

   (*ppY)->Add(-H + Tb);
   (*ppW)->Add(2 * W);
   (*ppDesc)->Add(CComBSTR(_T("Bottom Flange - Web")));

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::GetWebWidthProjectionsForDebonding(IUnkArray** ppArray)
{
   CHECK_RETOBJ(ppArray);

   Float64 A, B, C, Tt, Tb, W;
   m_Beam->get_A(&A);
   m_Beam->get_B(&B);
   m_Beam->get_C(&C);
   m_Beam->get_Tt(&Tt);
   m_Beam->get_Tb(&Tb);
   m_Beam->get_W(&W);

   Float64 H = C + Tt;

   Float64 edge = A / 2 - B;

   CComPtr<IUnkArray> array;
   array.CoCreateInstance(CLSID_UnkArray);

   CComPtr<IRect2d> rect1;
   rect1.CoCreateInstance(CLSID_Rect2d);
   rect1->SetBounds(-edge, -edge + W, -H, -H + Tb);
   array->Add(rect1);

   CComPtr<IRect2d> rect2;
   rect2.CoCreateInstance(CLSID_Rect2d);
   rect2->SetBounds(edge - W, edge, -H, -H + Tb);
   array->Add(rect2);

   array.CopyTo(ppArray);

   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IShape implementation
STDMETHODIMP CDeckedSlabBeamSection::FurthestPoint(ILine2d* line, IPoint2d** ppPoint, Float64* dist)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->FurthestPoint(line, ppPoint, dist);
}

STDMETHODIMP CDeckedSlabBeamSection::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->FurthestDistance(line, pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get_Perimeter(Float64 *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_Perimeter(pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get_ShapeProperties(IShapeProperties* *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_ShapeProperties(pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get_BoundingBox(IRect2d* *pVal)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_BoundingBox(pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CDeckedSlabBeamSection::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->PointInShape(pPoint, pbResult);
}

STDMETHODIMP CDeckedSlabBeamSection::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CDeckedSlabBeamSection>* clone;
   CComObject<CDeckedSlabBeamSection>::CreateInstance(&clone);

   clone->m_Rotation = m_Rotation;

   CComPtr<IDeckedSlabBeamSection> section = clone;

   CComQIPtr<IShape> beam_shape(m_Beam);
   CComPtr<IShape> clone_beam;
   beam_shape->Clone(&clone_beam);
   CComQIPtr<IDeckedSlabBeam> new_beam(clone_beam);
   section->put_Beam(new_beam);

   CComQIPtr<IShape> shape(section);
   (*pClone) = shape;
   (*pClone)->AddRef();

   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->ClipWithLine(pLine, pShape);
}

STDMETHODIMP CDeckedSlabBeamSection::ClipIn(IRect2d* pRect,IShape** pShape)
{
   CComQIPtr<IShape> shape(m_Beam);
   return shape->ClipIn(pRect, pShape);
}

/////////////////////////////////////////////////////////////////////////////
// ICompositeShape
/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CDeckedSlabBeamSection::get_Shape(IShape* *pVal)
{
   CHECK_RETOBJ(pVal);
   return this->QueryInterface(IID_IShape, (void**)pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return this->QueryInterface(IID_IXYPosition, (void**)pVal);
}

STDMETHODIMP CDeckedSlabBeamSection::get_Item(IndexType idx,ICompositeShapeItem* *pVal)
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
      m_Beam->GetVoidShape(idx - 1,&shape);
      compShape->AddShape(shape, VARIANT_TRUE);
   }

   compShape->get_Item(0, pVal);
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::get__NewEnum(IUnknown* *pVal)
{
   ATLASSERT(false);
   return E_INVALIDARG;
}

STDMETHODIMP CDeckedSlabBeamSection::get_Count(IndexType *pVal)
{
   CHECK_RETVAL(pVal);
   m_Beam->get_VoidCount(pVal);
   *pVal += 1;
   return S_OK;
}

STDMETHODIMP CDeckedSlabBeamSection::Remove(IndexType idx)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CDeckedSlabBeamSection::Clear()
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CDeckedSlabBeamSection::ReplaceEx(IndexType idx,ICompositeShapeItem* pShapeItem)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CDeckedSlabBeamSection::Replace(IndexType idx,IShape* pShape)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CDeckedSlabBeamSection::AddShapeEx(ICompositeShapeItem* ShapeItem)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

STDMETHODIMP CDeckedSlabBeamSection::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   ATLASSERT(false); // can't add a shape
   return E_INVALIDARG;
}

// XYPosition
STDMETHODIMP CDeckedSlabBeamSection::Offset(Float64 dx,Float64 dy)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->Offset(dx, dy);
}

STDMETHODIMP CDeckedSlabBeamSection::OffsetEx(ISize2d* pSize)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->OffsetEx(pSize);
}

STDMETHODIMP CDeckedSlabBeamSection::get_LocatorPoint(LocatorPointType lp,IPoint2d** point)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->get_LocatorPoint(lp, point);
}

STDMETHODIMP CDeckedSlabBeamSection::put_LocatorPoint(LocatorPointType lp,IPoint2d* point)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->put_LocatorPoint(lp, point);
}

STDMETHODIMP CDeckedSlabBeamSection::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->MoveEx(pFrom, pTo);
}

STDMETHODIMP CDeckedSlabBeamSection::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   m_Rotation += angle;
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->RotateEx(pPoint, angle);
}

STDMETHODIMP CDeckedSlabBeamSection::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_Rotation += angle;
   CComQIPtr<IXYPosition> position(m_Beam);
   return position->Rotate(cx, cy, angle);
}
