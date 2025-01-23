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

// GirderSectionImpl.h : Declaration of the IGirderSectionImpl

#ifndef __GIRDERSECTIONIMPL_H_
#define __GIRDERSECTIONIMPL_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGirderSectionImpl
template <class C,const CLSID* pclsid,class _ISECTION_,const IID* piid,class _IBEAM_,const CLSID* pbeamclsid>
class ATL_NO_VTABLE CGirderSectionImpl :
   public CComObjectRootEx<CComSingleThreadModel>,
   public CComCoClass<C, pclsid>,
   public ISupportErrorInfo,
   public _ISECTION_,
   public IPrestressedGirderSection,
   public IShape,
   public ICompositeShape,
   public IXYPosition
{
public:
   CGirderSectionImpl()
   {
   }

   HRESULT FinalConstruct()
   {
      m_CompositeShape.CoCreateInstance(CLSID_CompositeShape);
      HRESULT hr = m_Beam.CoCreateInstance(*pbeamclsid);
      if (FAILED(hr))
      {
         CreateBeam(&m_Beam);
      }

      CComQIPtr<IShape> beamShape(m_Beam);
      ATLASSERT(beamShape != nullptr); // must implement IShape interface

      m_CompositeShape->AddShape(beamShape, VARIANT_FALSE); // solid

      m_CompositeShape.QueryInterface(&m_Shape);
      m_CompositeShape.QueryInterface(&m_Position);

      m_Rotation = 0;

      return S_OK;
   }

   virtual HRESULT CreateBeam(_IBEAM_** ppBeam)
   {
      return E_FAIL;
   }


   DECLARE_PROTECT_FINAL_CONSTRUCT()

   BEGIN_COM_MAP(C)
      COM_INTERFACE_ENTRY_IID(*piid,_ISECTION_)
      COM_INTERFACE_ENTRY(IGirderSection)
      COM_INTERFACE_ENTRY(IPrestressedGirderSection)
      COM_INTERFACE_ENTRY(IShape)
      COM_INTERFACE_ENTRY(ICompositeShape)
      COM_INTERFACE_ENTRY(IXYPosition)
      COM_INTERFACE_ENTRY(ISupportErrorInfo)
   END_COM_MAP()

protected:
   CComPtr<_IBEAM_> m_Beam;
   CComPtr<ICompositeShape> m_CompositeShape;
   CComPtr<IShape> m_Shape;
   CComPtr<IXYPosition> m_Position;
   Float64 m_Rotation;

public:
   STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid)
   {
      static const IID* arr[] =
      {
         piid,
         &IID_IGirderSection,
         &IID_IShape,
         &IID_ICompositeShape,
         &IID_IXYPosition,
      };
      for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
      {
         if (InlineIsEqualGUID(*arr[i], riid))
            return S_OK;
      }
      return S_FALSE;
   }

   ////////////////////////////////////////////////////////////////////////
   // IFlangedBeam implementation
   STDMETHODIMP put_Beam(_IBEAM_* beam) override
   {
      CHECK_IN(beam);

      CComQIPtr<IShape> shape(beam);
      CHECK_IN(shape);

      CComPtr<IShape> clone;
      HRESULT hr = shape->Clone(&clone);
      ATLASSERT(SUCCEEDED(hr));

      m_Beam.Release();
      clone.QueryInterface(&m_Beam);

      m_CompositeShape->Replace(0, clone);

      return S_OK;
   }

   STDMETHODIMP get_Beam(_IBEAM_** beam) override
   {
      CHECK_RETOBJ(beam);
      (*beam) = m_Beam;
      (*beam)->AddRef();
      return S_OK;
   }

   ////////////////////////////////////////////////////////////////////////
   // IGirderSection implementation
   STDMETHODIMP get_GirderShape(IShape** ppShape)
   {
      return m_Beam->get_Shape(ppShape);
   }

   STDMETHODIMP get_VoidCount(/*[out, retval]*/IndexType* pnVoids)
   {
      CHECK_RETVAL(pnVoids);
      *pnVoids = 0;
      return S_OK;
   }

   STDMETHODIMP get_VoidShape(/*[in]*/IndexType voidIdx, /*[out, retval]*/IShape** ppShape)
   {
      CHECK_RETOBJ(ppShape);
      ATLASSERT(false);
      *ppShape = nullptr;
      return E_INVALIDARG;
   }

   STDMETHODIMP get_WorkPoint(IPoint2d** ppWorkPoint) override
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

   STDMETHODIMP get_WebCount(WebIndexType* nWebs) override
   {
      CHECK_RETVAL(nWebs);
      *nWebs = 1;
      return S_OK;
   }

   STDMETHODIMP get_WebLocation(WebIndexType idx, Float64* location) override
   {
      if (idx != 0)
         return E_INVALIDARG;

      CHECK_RETVAL(location);

      (*location) = 0;
      return S_OK;
   }

   STDMETHODIMP get_WebSpacing(WebIndexType idx, Float64* spacing) override
   {
      if (idx != 0)
         return E_INVALIDARG;

      CHECK_RETVAL(spacing);

      (*spacing) = 0;
      return S_OK;
   }

   STDMETHODIMP get_WebThickness(WebIndexType idx, Float64* tWeb) override
   {
      if (idx != 0)
         return E_INVALIDARG;

      CHECK_RETVAL(tWeb);

      Float64 web;
      m_Beam->get_AvgWebWidth(&web);
      (*tWeb) = web;
      return S_OK;
   }

   STDMETHODIMP get_WebPlane(WebIndexType idx, IPlane3d** ppPlane) override
   {
      CHECK_RETOBJ(ppPlane);

      Float64 x;
      HRESULT hr = get_WebLocation(idx, &x);
      if (FAILED(hr))
         return hr;

      CComPtr<IPoint3d> p1;
      p1.CoCreateInstance(CLSID_Point3d);
      p1->Move(x, 0, 0);

      CComPtr<IPoint3d> p2;
      p2.CoCreateInstance(CLSID_Point3d);
      p2->Move(x, 100, 0);

      CComPtr<IPoint3d> p3;
      p3.CoCreateInstance(CLSID_Point3d);
      p3->Move(x, 0, 100);

      CComPtr<IPlane3d> plane;
      plane.CoCreateInstance(CLSID_Plane3d);
      plane->ThroughPoints(p1, p2, p3);

      return plane.CopyTo(ppPlane);
   }

   STDMETHODIMP get_MatingSurfaceCount(MatingSurfaceIndexType* nMatingSurfaces) override
   {
      return get_TopFlangeCount(nMatingSurfaces);
   }

   STDMETHODIMP get_MatingSurfaceLocation(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, Float64* location) override
   {
      return get_TopFlangeLocation(idx, location);
   }

   STDMETHODIMP get_MatingSurfaceWidth(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, Float64* wMatingSurface) override
   {
      return get_TopFlangeWidth(idx, wMatingSurface);
   }

   STDMETHODIMP get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile) override
   {
      return E_NOTIMPL;
   }

   STDMETHODIMP get_TopFlangeCount(FlangeIndexType* nTopFlanges) override
   {
      CHECK_RETVAL(nTopFlanges);
      *nTopFlanges = 1;
      return S_OK;
   }

   STDMETHODIMP get_TopFlangeLocation(FlangeIndexType idx, Float64* location) override
   {
      if (idx != 0)
         return E_INVALIDARG;

      *location = 0;
      return S_OK;
   }

   STDMETHODIMP get_TopFlangeWidth(FlangeIndexType idx, Float64* wFlange) override
   {
      if (idx != 0)
         return E_INVALIDARG;

      return m_Beam->get_TopFlangeWidth(wFlange);
   }

   STDMETHODIMP get_TopFlangeSpacing(FlangeIndexType idx, Float64* spacing) override
   {
      if (idx != 0)
         return E_INVALIDARG;

      CHECK_RETVAL(spacing);

      (*spacing) = 0;
      return S_OK;
   }

   STDMETHODIMP get_BottomFlangeCount(FlangeIndexType* nBottomFlanges) override
   {
      CHECK_RETVAL(nBottomFlanges);
      *nBottomFlanges = 1;
      return S_OK;
   }

   STDMETHODIMP get_BottomFlangeLocation(FlangeIndexType idx, Float64* location) override
   {
      if (idx != 0)
         return E_INVALIDARG;

      *location = 0;
      return S_OK;
   }

   STDMETHODIMP get_BottomFlangeWidth(FlangeIndexType idx, Float64* wFlange) override
   {
      if (idx != 0)
         return E_INVALIDARG;

      return m_Beam->get_BottomFlangeWidth(wFlange);
   }

   STDMETHODIMP get_BottomFlangeSpacing(FlangeIndexType idx, Float64* spacing) override
   {
      if (idx != 0)
         return E_INVALIDARG;

      CHECK_RETVAL(spacing);

      (*spacing) = 0;
      return S_OK;
   }

   STDMETHODIMP get_OverallHeight(Float64* height) override
   {
      return get_NominalHeight(height);
   }

   STDMETHODIMP get_NominalHeight(Float64* height) override
   {
      return m_Beam->get_Height(height);
   }

   STDMETHODIMP get_TopWidth(Float64* pLeft, Float64* pRight) override
   {
      CHECK_RETVAL(pLeft);
      CHECK_RETVAL(pRight);

      Float64 width;
      m_Beam->get_TopFlangeWidth(&width);
      width /= 2.0;

      *pLeft = width;
      *pRight = width;

      return S_OK;
   }

   STDMETHODIMP get_BottomWidth(Float64* pLeft, Float64* pRight) override
   {
      CHECK_RETVAL(pLeft);
      CHECK_RETVAL(pRight);

      Float64 width;
      m_Beam->get_BottomFlangeWidth(&width);
      width /= 2.0;

      *pLeft = width;
      *pRight = width;

      return S_OK;
   }

   STDMETHODIMP get_ShearWidth(Float64* shearwidth) override
   {
      return m_Beam->get_AvgWebWidth(shearwidth);
   }

   STDMETHODIMP get_MinTopFlangeThickness(Float64* tf) override
   {
      return m_Beam->get_D1(tf);
   }

   STDMETHODIMP get_CL2ExteriorWebDistance(DirectionType side, Float64* wd) override
   {
      HRESULT hr = S_OK;
      CHECK_RETVAL(wd);

      *wd = 0.0;

      return hr;
   }

   ////////////////////////////////////////////////////////////////////////
   // IShape implementation
   STDMETHODIMP FurthestPoint(ILine2d* line, IPoint2d** ppPoint, Float64* dist) override
   {
      return m_Shape->FurthestPoint(line, ppPoint, dist);
   }

   STDMETHODIMP FurthestDistance(ILine2d* line,Float64 *pVal) override
   { 
      return m_Shape->FurthestDistance(line,pVal);
   }

   STDMETHODIMP get_Perimeter(Float64 *pVal) override
   {
      return m_Shape->get_Perimeter(pVal);
   }

   STDMETHODIMP get_ShapeProperties(IShapeProperties* *pVal) override
   {
      return m_Shape->get_ShapeProperties(pVal);
   }

   STDMETHODIMP get_BoundingBox(IRect2d* *pVal) override
   { 
      return m_Shape->get_BoundingBox(pVal);
   }

   STDMETHODIMP get_PolyPoints(IPoint2dCollection** ppPolyPoints) override
   {
      return m_Shape->get_PolyPoints(ppPolyPoints);
   }

   STDMETHODIMP PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult) override
   {
      return m_Shape->PointInShape(pPoint,pbResult);
   }

   STDMETHODIMP Clone(IShape** pClone) override
   {
      CHECK_RETOBJ(pClone);

      CComObject<C>* clone;
      CComObject<C>::CreateInstance(&clone);
      clone->m_CompositeShape.Release();
      clone->m_Shape.Release();
      clone->m_Position.Release();
      clone->m_Beam.Release();

      m_Shape->Clone(&clone->m_Shape);
      clone->m_Shape->QueryInterface(&clone->m_CompositeShape);
      clone->m_Shape->QueryInterface(&clone->m_Position);

      // first item is the beam
      CComPtr<ICompositeShapeItem> item;
      clone->m_CompositeShape->get_Item(0,&item);

      CComPtr<IShape> s;
      item->get_Shape(&s);

      CComQIPtr<_IBEAM_> beam(s);
      clone->m_Beam = beam;

      clone->m_Rotation = m_Rotation;


      (*pClone) = clone;
      (*pClone)->AddRef();

      return S_OK;
   }

   STDMETHODIMP ClipWithLine(ILine2d* pLine,IShape** pShape) override
   {
      CHECK_IN(pLine);
      CHECK_RETOBJ(pShape);
      return m_Shape->ClipWithLine(pLine, pShape);
   }

   STDMETHODIMP ClipIn(IRect2d* pRect,IShape** pShape) override
   {
      CHECK_IN(pRect);
      CHECK_RETOBJ(pShape);

      return m_Shape->ClipIn(pRect, pShape);
   }

   STDMETHODIMP Offset(Float64 dx,Float64 dy) override
   {
      return m_Position->Offset(dx,dy);
   }

   STDMETHODIMP OffsetEx(ISize2d* pSize) override
   {
      return m_Position->OffsetEx(pSize);
   }

   STDMETHODIMP get_LocatorPoint(LocatorPointType lp,IPoint2d** point) override
   {
      return m_Position->get_LocatorPoint(lp,point);
   }

   STDMETHODIMP put_LocatorPoint(LocatorPointType lp,IPoint2d* point) override
   {
      return m_Position->put_LocatorPoint(lp,point);
   }

   STDMETHODIMP MoveEx(IPoint2d* pFrom,IPoint2d* pTo) override
   {
      return m_Position->MoveEx(pFrom,pTo);
   }

   STDMETHODIMP RotateEx(IPoint2d* pPoint,Float64 angle) override
   {
      m_Rotation += angle;
      return m_Position->RotateEx(pPoint,angle);
   }

   STDMETHODIMP Rotate(Float64 cx,Float64 cy,Float64 angle) override
   {
      m_Rotation += angle;
      return m_Position->Rotate(cx,cy,angle);
   }

   // ICompositeSection
   STDMETHODIMP get__NewEnum(IUnknown* *pVal) override
   {
      return m_CompositeShape->get__NewEnum(pVal);
   }

   STDMETHODIMP get_Item(IndexType idx, ICompositeShapeItem* *pVal) override
   {
      return m_CompositeShape->get_Item(idx,pVal);
   }

   STDMETHODIMP ReplaceEx(IndexType idx,ICompositeShapeItem* pShapeItem) override
   {
      return m_CompositeShape->ReplaceEx(idx,pShapeItem);
   }

   STDMETHODIMP Replace(IndexType idx,IShape* pShape) override
   {
      return m_CompositeShape->Replace(idx,pShape);
   }

   STDMETHODIMP AddShape(IShape* shape,VARIANT_BOOL bVoid) override
   {
      return m_CompositeShape->AddShape(shape,bVoid);
   }

	STDMETHODIMP AddShapeEx(ICompositeShapeItem* shapeItem) override
   {
      return m_CompositeShape->AddShapeEx(shapeItem);
   }

	STDMETHODIMP Remove(IndexType idx) override
   {
      return m_CompositeShape->Remove(idx);
   }

	STDMETHODIMP Clear() override
   {
      return m_CompositeShape->Clear();
   }

   STDMETHODIMP get_Count(IndexType *pVal) override
   {
      return m_CompositeShape->get_Count(pVal);
   }

	STDMETHODIMP get_Shape(IShape* *pVal) override
   {
      return m_CompositeShape->get_Shape(pVal);
   }

   STDMETHODIMP get_XYPosition(IXYPosition* *pVal) override
   {
      return m_CompositeShape->get_XYPosition(pVal);
   }
};

#endif //__GIRDERSECTIONIMPL_H_
