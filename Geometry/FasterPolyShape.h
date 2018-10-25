///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2014  Washington State Department of Transportation
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

// FasterPolyShape.h : Declaration of the CFasterPolyShape

#ifndef __FASTERPOLYSHAPE_H_
#define __FASTERPOLYSHAPE_H_

#include "resource.h"       // main symbols
#include "Helper.h"
#include <MathEx.h>
#include <GeometricPrimitives\Primitives.h>

class gpLine2d;

/////////////////////////////////////////////////////////////////////////////
// CFasterPolyShape
class ATL_NO_VTABLE CFasterPolyShape : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFasterPolyShape, &CLSID_FasterPolyShape>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CFasterPolyShape,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IFasterPolyShape,
   public IShape,
   public IXYPosition,
   public IStructuredStorage2,
   public IPersist
{
public:
	CFasterPolyShape()
	{
	}

	virtual ~CFasterPolyShape()
	{
	}


   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_FASTERPOLYSHAPE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFasterPolyShape)
   COM_INTERFACE_ENTRY(IFasterPolyShape)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFasterPolyShape
public:
   STDMETHOD(AddPoint)(/*[in]*/ Float64 x,/*[in]*/ Float64 y);
	STDMETHOD(AddPointEx)(/*[in]*/ IPoint2d* pPoint);
	STDMETHOD(AddPoints)(/*[in]*/ IPoint2dCollection* pPoints);
   STDMETHOD(ChangePoint)(/*[in]*/ CollectionIndexType index,/*[in]*/ Float64 x,/*[in]*/ Float64 y);
	STDMETHOD(RemovePoint)(/*[in]*/ CollectionIndexType index);
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal);
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal);
	STDMETHOD(get_NumPoints)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(GetPoint)(/*[in]*/ CollectionIndexType index, /*[out]*/ Float64* pX,/*[out]*/ Float64* pY);
	STDMETHOD(Clear)();
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);

// IShape
	STDMETHOD(FurthestDistance)(/*[in]*/ILine2d* line,/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Perimeter)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(get_ShapeProperties)(/*[out,retval]*/ IShapeProperties* *pVal);
	STDMETHOD(get_BoundingBox)(/*[out, retval]*/ IRect2d* *pVal);
	STDMETHOD(get_PolyPoints)(/*[out,retval]*/ IPoint2dCollection** ppPolyPoints);
	STDMETHOD(PointInShape)(/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ VARIANT_BOOL* pbResult);
	STDMETHOD(Clone)(/*[out,retval]*/ IShape** pClone);
	STDMETHOD(ClipWithLine)(/*[in]*/ ILine2d* pLine,/*[out,retval]*/ IShape** pShape);
	STDMETHOD(ClipIn)(/*[in]*/ IRect2d* pRect,/*[out,retval]*/ IShape** pShape);

// IXYPosition
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy);
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize);
	STDMETHOD(get_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[out,retval]*/ IPoint2d** point);
	STDMETHOD(put_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[in]*/ IPoint2d* point);
	STDMETHOD(MoveEx)(/*[in]*/ IPoint2d* pFrom,/*[in]*/ IPoint2d* pTo);
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pPoint,/*[in]*/ Float64 angle);
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 angle);

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

private:
   STDMETHOD(ClipWithgpLine)(gpLine2d& theLine,IShape** pShape);

   // Simple collection of points
   typedef std::vector<gpPoint2d> fpPointCollection;
   typedef fpPointCollection::iterator fpPointIterator;

   fpPointCollection m_Points;

   // Cache if we need it
   class GeomUtilHolder
   {
      CComPtr<IGeomUtil2d> m_GeomUtil;

   public:
      IGeomUtil2d* GetGeomUtil()
      {
         if (!m_GeomUtil)
         {
            HRESULT hr = m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
            ATLASSERT(SUCCEEDED(hr));
         }

         return m_GeomUtil.p;
      }
   } m_GeomUtilHolder;


   void GetLocatorPoint(LocatorPointType lp,Float64* x,Float64* y);

   // dirty flags to signal completion of different computations and cached properties
   bool m_DirtyBoundingBox;
   bool m_DirtyProperties;

   // cached shape properties
   struct ShapeProps
   {
      Float64 Area;
      Float64 Ixx;
      Float64 Iyy;
      Float64 Ixy;
      Float64 Xleft;
      Float64 Xright;
      Float64 Ytop;
      Float64 Ybottom;
      Float64 Cx;  // centriod coord's
      Float64 Cy;

      ShapeProps()
      {
         Init();
      }
      void Init();
      HRESULT CreateIShapeProperties(IShapeProperties ** props);

   } m_ShapeProps;


   // cached bounding rectangle
   gpRect2d m_BoundingRect;

   void MakeDirty() { m_DirtyBoundingBox = m_DirtyProperties = true;}
   void UpdateBoundingBox();
   void UpdateShapeProperties();

};

#endif //__FASTERPOLYSHAPE_H_
