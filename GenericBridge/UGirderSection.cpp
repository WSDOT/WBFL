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

// UGirderSection.cpp : Implementation of CUGirderSection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "UGirderSection.h"
#include <MathEx.h>
#include <xutility> // for Min

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUGirderSection
HRESULT CUGirderSection::FinalConstruct()
{
   m_CompositeShape.CoCreateInstance(CLSID_CompositeShape);
   m_Beam.CoCreateInstance(CLSID_UBeam);

   CComQIPtr<IShape> beamShape(m_Beam);
   ATLASSERT(beamShape != nullptr); // must implement IShape interface

   m_CompositeShape->AddShape(beamShape,VARIANT_FALSE); // solid

   m_CompositeShape.QueryInterface(&m_Shape);
   m_CompositeShape.QueryInterface(&m_Position);

   m_Rotation = 0;
 
   return S_OK;
}

void CUGirderSection::FinalRelease()
{
}

STDMETHODIMP CUGirderSection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUGirderSection,
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

void CUGirderSection::GetSplittingZone(Float64* pH,SplittingDirection* pSD)
{
   Float64 h,w1,w2;
   m_Beam->get_D1(&h);
   m_Beam->get_W1(&w1);
   m_Beam->get_W2(&w2);

   IndexType idx = MinIndex(h,w1,w2);
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
// IUGirderSection implementation
STDMETHODIMP CUGirderSection::put_Beam(IUBeam* beam)
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

STDMETHODIMP CUGirderSection::get_Beam(IUBeam** beam)
{
   CHECK_RETOBJ(beam);
   (*beam) = m_Beam;
   (*beam)->AddRef();
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IPrecastGirderSection implementation
STDMETHODIMP CUGirderSection::get_WorkPoint(IPoint2d** ppWorkPoint)
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


#define NWEBS 2
STDMETHODIMP CUGirderSection::get_WebCount(WebIndexType* nWebs)
{
   CHECK_RETVAL(nWebs);
   *nWebs = NWEBS;
   return S_OK;
}

STDMETHODIMP CUGirderSection::get_WebLocation(WebIndexType idx,Float64* location)
{
   if ( idx < 0 || NWEBS <= idx )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(location);

   return m_Beam->get_WebLocation(idx,location);
}

STDMETHODIMP CUGirderSection::get_WebSpacing(WebIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(spacing);

   return m_Beam->get_WebSpacing(spacing);
}

STDMETHODIMP CUGirderSection::get_WebThickness(WebIndexType idx,Float64* tWeb)
{
   if ( idx < 0 || NWEBS <= idx )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(tWeb);

   Float64 web;
   m_Beam->get_T(&web);

   Float64 slope;
   m_Beam->get_Slope(idx,&slope);
   slope = fabs(slope);

   (*tWeb) = web*sqrt(slope*slope+1)/slope;

   return S_OK;
}

STDMETHODIMP CUGirderSection::get_MinWebThickness(Float64* tWeb)
{
   return get_WebThickness(0,tWeb);
}

STDMETHODIMP CUGirderSection::get_WebPlane(WebIndexType idx,IPlane3d** ppPlane)
{
   CHECK_RETOBJ(ppPlane);
   
   HRESULT hr = S_OK;

   Float64 slope;
   hr = m_Beam->get_Slope(idx,&slope);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 sign = (idx == 0 ? -1.0 : 1.0);

   Float64 tWeb;
   this->get_WebThickness(idx,&tWeb);

   Float64 x;
   this->get_WebLocation(idx,&x);

   Float64 w, wl, wr;
   this->get_BottomWidth(&wl,&wr);
   w = wl + wr;

   Float64 h;
   this->get_OverallHeight(&h);

   CComPtr<IPoint3d> p1;
   p1.CoCreateInstance(CLSID_Point3d);
   p1->Move(x,0,0);

   CComPtr<IPoint3d> p2;
   p2.CoCreateInstance(CLSID_Point3d);
   p2->Move( sign*(w-tWeb)/2, -h, 0);

   CComPtr<IPoint3d> p3;
   p3.CoCreateInstance(CLSID_Point3d);
   p3->Move(x,0,100);

   CComPtr<IPlane3d> plane;
   plane.CoCreateInstance(CLSID_Plane3d);
   plane->ThroughPoints(p1,p2,p3);

   return plane.CopyTo(ppPlane);
}

STDMETHODIMP CUGirderSection::get_EffectiveWebThickness(Float64* tWeb)
{
   return get_MinWebThickness(tWeb);
}

STDMETHODIMP CUGirderSection::get_MatingSurfaceCount(MatingSurfaceIndexType* nMatingSurfaces)
{
   return get_TopFlangeCount(nMatingSurfaces);
}

STDMETHODIMP CUGirderSection::get_MatingSurfaceLocation(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* location)
{
   return get_TopFlangeLocation(idx,location);
}

STDMETHODIMP CUGirderSection::get_MatingSurfaceWidth(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* wMatingSurface)
{
   return get_TopFlangeWidth(idx,wMatingSurface);
}

STDMETHODIMP CUGirderSection::get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile)
{
   return E_NOTIMPL;
}

STDMETHODIMP CUGirderSection::get_TopFlangeCount(FlangeIndexType* nTopFlanges)
{
   CHECK_RETVAL(nTopFlanges);
   *nTopFlanges = NWEBS;
   return S_OK;
}

STDMETHODIMP CUGirderSection::get_TopFlangeLocation(FlangeIndexType idx,Float64* location)
{
   if ( idx < 0 || NWEBS < idx )
   {
      return E_INVALIDARG;
   }

   Float64 W2;
   m_Beam->get_W2(&W2);

   Float64 top_flange_width;
   get_TopFlangeWidth(idx,&top_flange_width);

   *location = (W2 - top_flange_width)/2;

   if ( idx == 0 )
   {
      (*location) *= -1;  // left of CL beam so make it negative
   }

   return S_OK;
}

STDMETHODIMP CUGirderSection::get_TopFlangeWidth(FlangeIndexType idx,Float64* wFlange)
{
   if ( idx < 0 || NWEBS < idx )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_TopFlangeWidth(wFlange);
}

STDMETHODIMP CUGirderSection::get_TopFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx < 0 || NWEBS < idx )
   {
      return E_INVALIDARG;
   }

   Float64 D4, D6;
   m_Beam->get_D4(&D4);
   m_Beam->get_D6(&D6);

   *tFlange = Min(D4,D6);
   return S_OK;
}

STDMETHODIMP CUGirderSection::get_TopFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(spacing);

   return m_Beam->get_WebSpacing(spacing);
}

STDMETHODIMP CUGirderSection::get_BottomFlangeCount(FlangeIndexType* nBottomFlanges)
{
   CHECK_RETVAL(nBottomFlanges);
   *nBottomFlanges = 1;
   return S_OK;
}

STDMETHODIMP CUGirderSection::get_BottomFlangeLocation(FlangeIndexType idx,Float64* location)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   *location = 0;
   return S_OK;
}

STDMETHODIMP CUGirderSection::get_BottomFlangeWidth(FlangeIndexType idx,Float64* wFlange)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_W1(wFlange);
}

STDMETHODIMP CUGirderSection::get_BottomFlangeThickness(FlangeIndexType idx,Float64* tFlange)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   return m_Beam->get_D2(tFlange);
}

STDMETHODIMP CUGirderSection::get_BottomFlangeSpacing(FlangeIndexType idx,Float64* spacing)
{
   if ( idx != 0 )
   {
      return E_INVALIDARG;
   }

   CHECK_RETVAL(spacing);

   *spacing = 0;
   return S_OK;
}

STDMETHODIMP CUGirderSection::get_OverallHeight(Float64* height)
{
   return get_NominalHeight(height);
}

STDMETHODIMP CUGirderSection::get_NominalHeight(Float64* height)
{
   return m_Beam->get_Height(height);
}

STDMETHODIMP CUGirderSection::get_TopWidth(Float64* pLeft, Float64* pRight)
{
   Float64 width;
   m_Beam->get_TopWidth(&width);

   width /= 2.0;

   *pLeft = width;
   *pRight = width;

   return S_OK;
}

STDMETHODIMP CUGirderSection::get_BottomWidth(Float64* pLeft, Float64* pRight)
{
   Float64 width;
   m_Beam->get_W1(&width);

   width /= 2.0;

   *pLeft = width;
   *pRight = width;

   return S_OK;
}

STDMETHODIMP CUGirderSection::get_ShearWidth(Float64* shearwidth)
{
   CHECK_RETVAL(shearwidth);
   Float64 width = 0;
   for ( WebIndexType i = 0; i < NWEBS; i++ )
   {
      Float64 t;
      get_WebThickness(i,&t);
      width += t;
   }

   *shearwidth = width;

   return S_OK;
}

STDMETHODIMP CUGirderSection::get_MinTopFlangeThickness(Float64* tf)
{
   CHECK_RETVAL(tf);
   Float64 d4, d6;
   m_Beam->get_D4(&d4);
   m_Beam->get_D6(&d6);

   *tf = Min(d4,d6);
   return S_OK;
}

STDMETHODIMP CUGirderSection::get_MinBottomFlangeThickness(Float64* tf)
{
   return m_Beam->get_D2(tf);
}

STDMETHODIMP CUGirderSection::get_CL2ExteriorWebDistance(DirectionType side, Float64* wd)
{
   HRESULT hr;
   CHECK_RETVAL(wd);

   Float64 spacing;
   hr = m_Beam->get_WebSpacing(&spacing);
   *wd = spacing/2.0;

   return hr;
}


STDMETHODIMP CUGirderSection::RemoveSacrificalDepth(Float64 sacDepth)
{
   Float64 D4;
   m_Beam->get_D4(&D4);
   ATLASSERT(sacDepth < D4);
   D4 -= sacDepth;
   m_Beam->put_D4(D4);
   return S_OK;
}

STDMETHODIMP CUGirderSection::get_SplittingZoneDimension(Float64* pSZD)
{
   CHECK_RETVAL(pSZD);
   SplittingDirection sd;
   GetSplittingZone(pSZD,&sd);
   return S_OK;
}

STDMETHODIMP CUGirderSection::get_SplittingDirection(SplittingDirection* pSD)
{
   CHECK_RETVAL(pSD);
   Float64 h;
   GetSplittingZone(&h,pSD);
   return S_OK;
}

STDMETHODIMP CUGirderSection::GetWebSections(IDblArray** ppY, IDblArray** ppW, IBstrArray** ppDesc)
{
   Float64 D1, D2, D3, D4, D5, D6, D7;
   m_Beam->get_D1(&D1);
   m_Beam->get_D2(&D2);
   m_Beam->get_D3(&D3);
   m_Beam->get_D4(&D4);
   m_Beam->get_D5(&D5);
   m_Beam->get_D6(&D6);
   m_Beam->get_D7(&D7);

   Float64 t_web;
   get_WebThickness(0,&t_web);

   CComPtr<IDblArray> y;
   y.CoCreateInstance(CLSID_DblArray);
   y.CopyTo(ppY);

   CComPtr<IDblArray> w;
   w.CoCreateInstance(CLSID_DblArray);
   w.CopyTo(ppW);

   CComPtr<IBstrArray> desc;
   desc.CoCreateInstance(CLSID_BstrArray);
   desc.CopyTo(ppDesc);

   Float64 H1 = D4 + D5;
   Float64 H2 = D6 + D7;
   Float64 H = Max(H1, H2);
   (*ppY)->Add(-H);
   (*ppW)->Add(2 * t_web);
   if (IsZero(H))
   {
      (*ppDesc)->Add(_T("Top Girder"));
   }
   else
   {
      (*ppDesc)->Add(_T("Top Flange - Web"));
   }

   (*ppY)->Add(-D1 + D2 + D3);
   (*ppW)->Add(2 * t_web);
   (*ppDesc)->Add(CComBSTR(_T("Bottom Flange - Web")));

   return S_OK;
}

STDMETHODIMP CUGirderSection::GetWebWidthProjectionsForDebonding(IUnkArray** ppArray)
{
   CHECK_RETOBJ(ppArray);

   Float64 D1, D2, D3, W1;
   m_Beam->get_D1(&D1);
   m_Beam->get_D2(&D2);
   m_Beam->get_D3(&D3);
   m_Beam->get_W1(&W1);

   Float64 t_web;
   get_WebThickness(0, &t_web);


   CComPtr<IUnkArray> array;
   array.CoCreateInstance(CLSID_UnkArray);

   CComPtr<IRect2d> rect1;
   rect1.CoCreateInstance(CLSID_Rect2d);
   rect1->SetBounds(-W1 / 2, -W1/2 + t_web, -D1, -D1 + D2 + 0.5*D3);
   array->Add(rect1);

   CComPtr<IRect2d> rect2;
   rect2.CoCreateInstance(CLSID_Rect2d);
   rect2->SetBounds(W1 / 2 - t_web, W1 / 2, -D1, -D1 + D2 + 0.5*D3);
   array->Add(rect2);

   array.CopyTo(ppArray);
   return S_OK;
}

////////////////////////////////////////////////////////////////////////
// IShape implementation
STDMETHODIMP CUGirderSection::FurthestDistance(ILine2d* line,Float64 *pVal)
{
   return m_Shape->FurthestDistance(line,pVal);
}

STDMETHODIMP CUGirderSection::get_Perimeter(Float64 *pVal)
{
   return m_Shape->get_Perimeter(pVal);
}

STDMETHODIMP CUGirderSection::get_ShapeProperties(IShapeProperties* *pVal)
{
   return m_Shape->get_ShapeProperties(pVal);
}

STDMETHODIMP CUGirderSection::get_BoundingBox(IRect2d* *pVal)
{
   return m_Shape->get_BoundingBox(pVal);
}

STDMETHODIMP CUGirderSection::get_PolyPoints(IPoint2dCollection** ppPolyPoints)
{
   return m_Shape->get_PolyPoints(ppPolyPoints);
}

STDMETHODIMP CUGirderSection::PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
{
   return m_Shape->PointInShape(pPoint,pbResult);
}

STDMETHODIMP CUGirderSection::Clone(IShape** pClone)
{
   CHECK_RETOBJ(pClone);

   CComObject<CUGirderSection>* clone;
   CComObject<CUGirderSection>::CreateInstance(&clone);

   CComPtr<IUGirderSection> section = clone;

   clone->m_Rotation += m_Rotation;

   section->put_Beam(m_Beam); // beam is cloned when it is put in the section

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

STDMETHODIMP CUGirderSection::ClipWithLine(ILine2d* pLine,IShape** pShape)
{
   return m_Shape->ClipWithLine(pLine,pShape);
}

STDMETHODIMP CUGirderSection::ClipIn(IRect2d* pRect,IShape** pShape)
{
   return m_Shape->ClipIn(pRect,pShape);
}

////////////////////////////////////////////////////////////////////////
// IXYPosition implementation

STDMETHODIMP CUGirderSection::Offset(Float64 dx,Float64 dy)
{
   return m_Position->Offset(dx,dy);
}

STDMETHODIMP CUGirderSection::OffsetEx(ISize2d* pSize)
{
   return m_Position->OffsetEx(pSize);
}

STDMETHODIMP CUGirderSection::get_LocatorPoint(LocatorPointType lp,IPoint2d** point)
{
   return m_Position->get_LocatorPoint(lp,point);
}

STDMETHODIMP CUGirderSection::put_LocatorPoint(LocatorPointType lp,IPoint2d* point)
{
   return m_Position->put_LocatorPoint(lp,point);
}

STDMETHODIMP CUGirderSection::MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
{
   return m_Position->MoveEx(pFrom,pTo);
}

STDMETHODIMP CUGirderSection::RotateEx(IPoint2d* pPoint,Float64 angle)
{
   m_Rotation += angle;
   return m_Position->RotateEx(pPoint,angle);
}

STDMETHODIMP CUGirderSection::Rotate(Float64 cx,Float64 cy,Float64 angle)
{
   m_Rotation += angle;
   return m_Position->Rotate(cx,cy,angle);
}

////////////////////////////////////////////////////////////////////////
// ICompositeShape implementation
STDMETHODIMP CUGirderSection::get__NewEnum(IUnknown* *pVal)
{
   return m_CompositeShape->get__NewEnum(pVal);
}

STDMETHODIMP CUGirderSection::get_Item(CollectionIndexType idx, ICompositeShapeItem* *pVal)
{
   return m_CompositeShape->get_Item(idx,pVal);
}

STDMETHODIMP CUGirderSection::ReplaceEx(CollectionIndexType idx,ICompositeShapeItem* pShapeItem)
{
   return m_CompositeShape->ReplaceEx(idx,pShapeItem);
}

STDMETHODIMP CUGirderSection::Replace(CollectionIndexType idx,IShape* pShape)
{
   return m_CompositeShape->Replace(idx,pShape);
}

STDMETHODIMP CUGirderSection::AddShape(IShape* shape,VARIANT_BOOL bVoid)
{
   return m_CompositeShape->AddShape(shape,bVoid);
}

STDMETHODIMP CUGirderSection::AddShapeEx(ICompositeShapeItem* shapeItem)
{
   return m_CompositeShape->AddShapeEx(shapeItem);
}

STDMETHODIMP CUGirderSection::Remove(CollectionIndexType idx)
{
   return m_CompositeShape->Remove(idx);
}

STDMETHODIMP CUGirderSection::Clear()
{
   return m_CompositeShape->Clear();
}

STDMETHODIMP CUGirderSection::get_Count(CollectionIndexType *pVal)
{
   return m_CompositeShape->get_Count(pVal);
}

STDMETHODIMP CUGirderSection::get_Shape(IShape* *pVal)
{
   return m_CompositeShape->get_Shape(pVal);
}

STDMETHODIMP CUGirderSection::get_XYPosition(IXYPosition **pVal)
{
   CHECK_RETOBJ(pVal);
   return m_CompositeShape->get_XYPosition(pVal);
}

STDMETHODIMP CUGirderSection::get_StructuredStorage(IStructuredStorage2* *pStrStg)
{
   return m_CompositeShape->get_StructuredStorage(pStrStg);
}
