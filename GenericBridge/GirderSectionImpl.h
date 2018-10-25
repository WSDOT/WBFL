///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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
// CFlangedBeam
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
      m_Beam.CoCreateInstance(*pbeamclsid);

      CComQIPtr<IShape> beamShape(m_Beam);
      ATLASSERT(beamShape != NULL); // must implement IShape interface

      m_CompositeShape->AddShape(beamShape,VARIANT_FALSE); // solid

      m_CompositeShape.QueryInterface(&m_Shape);
      m_CompositeShape.QueryInterface(&m_Position);

      return S_OK;
   }


//DECLARE_REGISTRY_RESOURCEID(IDR_FLANGEDBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(C)
	COM_INTERFACE_ENTRY(_ISECTION_)
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
	   for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	   {
		   if (InlineIsEqualGUID(*arr[i],riid))
			   return S_OK;
	   }
	   return S_FALSE;
   }

   ////////////////////////////////////////////////////////////////////////
   // IFlangedBeam implementation
   STDMETHODIMP put_Beam(_IBEAM_* beam)
   {
      CHECK_IN(beam);

      CComQIPtr<IShape> shape(beam);
      CHECK_IN(shape);

      CComPtr<IShape> clone;
      HRESULT hr = shape->Clone(&clone);
      ATLASSERT(SUCCEEDED(hr));

      m_Beam.Release();
      clone.QueryInterface(&m_Beam);

      m_CompositeShape->Replace(0,clone);

      return S_OK;
   }

   STDMETHODIMP get_Beam(_IBEAM_** beam)
   {
      CHECK_RETOBJ(beam);
      (*beam) = m_Beam;
      (*beam)->AddRef();
      return S_OK;
   }

   ////////////////////////////////////////////////////////////////////////
   // IGirderSection implementation
   STDMETHODIMP get_WebCount(WebIndexType* nWebs)
   {
      CHECK_RETVAL(nWebs);
      *nWebs = 1;
      return S_OK;
   }

   STDMETHODIMP get_WebLocation(WebIndexType idx,Float64* location)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      CHECK_RETVAL(location);

      (*location) = 0;
      return S_OK;
   }

   STDMETHODIMP get_WebSpacing(WebIndexType idx,Float64* spacing)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      CHECK_RETVAL(spacing);

      (*spacing) = 0;
      return S_OK;
   }

   STDMETHODIMP get_WebThickness(WebIndexType idx,Float64* tWeb)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      CHECK_RETVAL(tWeb);

      Float64 web;
      m_Beam->get_AvgWebWidth(&web);
      (*tWeb) = web;
      return S_OK;
   }

   STDMETHODIMP get_WebPlane(WebIndexType idx,IPlane3d** ppPlane)
   {
      CHECK_RETOBJ(ppPlane);

      Float64 x;
      HRESULT hr = get_WebLocation(idx,&x);
      if ( FAILED(hr) )
         return hr;

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

   STDMETHODIMP get_MatingSurfaceCount(MatingSurfaceIndexType* nMatingSurfaces)
   {
      return get_TopFlangeCount(nMatingSurfaces);
   }

   STDMETHODIMP get_MatingSurfaceLocation(MatingSurfaceIndexType idx,Float64* location)
   {
      return get_TopFlangeLocation(idx,location);
   }

	STDMETHODIMP get_MatingSurfaceWidth(MatingSurfaceIndexType idx,Float64* wMatingSurface)
   {
      return get_TopFlangeWidth(idx,wMatingSurface);
   }

   STDMETHODIMP get_TopFlangeCount(FlangeIndexType* nTopFlanges)
   {
      CHECK_RETVAL(nTopFlanges);
      *nTopFlanges = 1;
      return S_OK;
   }

   STDMETHODIMP get_TopFlangeLocation(FlangeIndexType idx,Float64* location)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      *location = 0;
      return S_OK;
   }

   STDMETHODIMP get_TopFlangeWidth(FlangeIndexType idx,Float64* wFlange)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_TopFlangeWidth(wFlange);
   }

   STDMETHODIMP get_TopFlangeSpacing(FlangeIndexType idx,Float64* spacing)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      CHECK_RETVAL(spacing);

      (*spacing) = 0;
      return S_OK;
   }

   STDMETHODIMP get_BottomFlangeCount(FlangeIndexType* nBottomFlanges)
   {
      CHECK_RETVAL(nBottomFlanges);
      *nBottomFlanges = 1;
      return S_OK;
   }

   STDMETHODIMP get_BottomFlangeLocation(FlangeIndexType idx,Float64* location)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      *location = 0;
      return S_OK;
   }

   STDMETHODIMP get_BottomFlangeWidth(FlangeIndexType idx,Float64* wFlange)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_BottomFlangeWidth(wFlange);
   }

   STDMETHODIMP get_BottomFlangeSpacing(FlangeIndexType idx,Float64* spacing)
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      CHECK_RETVAL(spacing);

      (*spacing) = 0;
      return S_OK;
   }

   STDMETHODIMP get_GirderHeight(Float64* height)
   {
      return m_Beam->get_Height(height);
   }

	STDMETHODIMP get_TopWidth(Float64* width)
   {
      return m_Beam->get_TopFlangeWidth(width);
   }

	STDMETHODIMP get_BottomWidth(Float64* width)
   {
      return m_Beam->get_BottomFlangeWidth(width);
   }

   STDMETHODIMP get_ShearWidth(Float64* shearwidth)
   {
      return m_Beam->get_AvgWebWidth(shearwidth);
   }

   STDMETHODIMP get_MinTopFlangeThickness(Float64* tf)
   {
      return m_Beam->get_D1(tf);
   }

   STDMETHODIMP get_CL2ExteriorWebDistance(DirectionType side, Float64* wd)
   {
      HRESULT hr = S_OK;
      CHECK_RETVAL(*wd);

      *wd = 0.0;

      return hr;
   }

   ////////////////////////////////////////////////////////////////////////
   // IShape implementation
   STDMETHODIMP FurthestDistance(ILine2d* line,Float64 *pVal)
   {
      return m_Shape->FurthestDistance(line,pVal);
   }

   STDMETHODIMP get_Perimeter(Float64 *pVal)
   {
      return m_Shape->get_Perimeter(pVal);
   }

   STDMETHODIMP get_ShapeProperties(IShapeProperties* *pVal)
   {
      return m_Shape->get_ShapeProperties(pVal);
   }

   STDMETHODIMP get_BoundingBox(IRect2d* *pVal)
   {
      return m_Shape->get_BoundingBox(pVal);
   }

   STDMETHODIMP get_PolyPoints(IPoint2dCollection** ppPolyPoints)
   {
      return m_Shape->get_PolyPoints(ppPolyPoints);
   }

   STDMETHODIMP PointInShape(IPoint2d* pPoint,VARIANT_BOOL* pbResult)
   {
      return m_Shape->PointInShape(pPoint,pbResult);
   }

   STDMETHODIMP Clone(IShape** pClone)
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


      (*pClone) = clone;
      (*pClone)->AddRef();

      return S_OK;
   }

   STDMETHODIMP ClipWithLine(ILine2d* pLine,IShape** pShape)
   {
      return m_Shape->ClipWithLine(pLine,pShape);
   }

   STDMETHODIMP ClipIn(IRect2d* pRect,IShape** pShape)
   {
      return m_Shape->ClipIn(pRect,pShape);
   }

   STDMETHODIMP Offset(Float64 dx,Float64 dy)
   {
      return m_Position->Offset(dx,dy);
   }

   STDMETHODIMP OffsetEx(ISize2d* pSize)
   {
      return m_Position->OffsetEx(pSize);
   }

   STDMETHODIMP get_LocatorPoint(LocatorPointType lp,IPoint2d** point)
   {
      return m_Position->get_LocatorPoint(lp,point);
   }

   STDMETHODIMP put_LocatorPoint(LocatorPointType lp,IPoint2d* point)
   {
      return m_Position->put_LocatorPoint(lp,point);
   }

   STDMETHODIMP MoveEx(IPoint2d* pFrom,IPoint2d* pTo)
   {
      return m_Position->MoveEx(pFrom,pTo);
   }

   STDMETHODIMP RotateEx(IPoint2d* pPoint,Float64 angle)
   {
      return m_Position->RotateEx(pPoint,angle);
   }

   STDMETHODIMP Rotate(Float64 cx,Float64 cy,Float64 angle)
   {
      return m_Position->Rotate(cx,cy,angle);
   }

   // ICompositeSection
   STDMETHODIMP get__NewEnum(IUnknown* *pVal)
   {
      return m_CompositeShape->get__NewEnum(pVal);
   }

   STDMETHODIMP get_Item(CollectionIndexType idx, ICompositeShapeItem* *pVal)
   {
      return m_CompositeShape->get_Item(idx,pVal);
   }

   STDMETHODIMP ReplaceEx(CollectionIndexType idx,ICompositeShapeItem* pShapeItem)
   {
      return m_CompositeShape->ReplaceEx(idx,pShapeItem);
   }

   STDMETHODIMP Replace(CollectionIndexType idx,IShape* pShape)
   {
      return m_CompositeShape->Replace(idx,pShape);
   }

   STDMETHODIMP AddShape(IShape* shape,VARIANT_BOOL bVoid)
   {
      return m_CompositeShape->AddShape(shape,bVoid);
   }

	STDMETHODIMP AddShapeEx(ICompositeShapeItem* shapeItem)
   {
      return m_CompositeShape->AddShapeEx(shapeItem);
   }

	STDMETHODIMP Remove(CollectionIndexType idx)
   {
      return m_CompositeShape->Remove(idx);
   }

	STDMETHODIMP Clear()
   {
      return m_CompositeShape->Clear();
   }

   STDMETHODIMP get_Count(CollectionIndexType *pVal)
   {
      return m_CompositeShape->get_Count(pVal);
   }

	STDMETHODIMP get_Shape(IShape* *pVal)
   {
      return m_CompositeShape->get_Shape(pVal);
   }

   STDMETHODIMP get_StructuredStorage(IStructuredStorage2* *pStrStg)
   {
      return m_CompositeShape->get_StructuredStorage(pStrStg);
   }
};

#endif //__GIRDERSECTIONIMPL_H_
