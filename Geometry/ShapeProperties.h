///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

// ShapeProperties.h : Declaration of the CShapeProperties

#ifndef __SHAPEPROPERTIES_H_
#define __SHAPEPROPERTIES_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CShapeProperties
class ATL_NO_VTABLE CShapeProperties : 
	public CComObjectRootEx<CComSingleThreadModel>,
   public ISupportErrorInfo,
	public CComCoClass<CShapeProperties, &CLSID_ShapeProperties>,
   public IObjectSafetyImpl<CShapeProperties,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IShapeProperties,
   public IStructuredStorage2,
   public IPersist
{
public:
	CShapeProperties()
	{
	}

   HRESULT FinalConstruct();


DECLARE_REGISTRY_RESOURCEID(IDR_SHAPEPROPERTIES)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CShapeProperties)
   COM_INTERFACE_ENTRY(IShapeProperties)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

private:
   // properties about centroidal axis
   Float64   m_Area;
   CComPtr<IPoint2d> m_pCentroid;
   Float64   m_Ixx;
   Float64   m_Iyy;
   Float64   m_Ixy;
   Float64   m_Xleft;   // Distance from centroid to left edge
   Float64   m_Xright;  // Distance from centroid to right edge
   Float64   m_Ytop;    // Distance from centroid to top edge
   Float64   m_Ybottom; // Distance from centroid to bottom edge

   // Current coordinate system
   CoordinateSystemType m_CoordType;
   CComPtr<IPoint2d> m_pOrigin;
   Float64         m_Orientation;

   // properties transformed into current coord sys
   CComPtr<IPoint2d> m_pCurrCentroid;
   Float64   m_CurrIxx;
   Float64   m_CurrIyy;
   Float64   m_CurrIxy;

   void UpdateOrientation();

// ISupportErrorInfo
public:
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IShapeProperties
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(AddProperties)(/*[in]*/ IShapeProperties* props);
	STDMETHOD(get_PrincipleDirection)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_CoordinateSystem)(/*[out, retval]*/ CoordinateSystemType *pVal);
	STDMETHOD(put_CoordinateSystem)(/*[in]*/ CoordinateSystemType newVal);
	STDMETHOD(get_Orientation)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Orientation)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Origin)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(put_Origin)(/*[in]*/ IPoint2d* newVal);
	STDMETHOD(get_Ybottom)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Ybottom)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Ytop)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Ytop)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Xright)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Xright)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Xleft)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Xleft)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Ixy)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Ixy)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Iyy)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Iyy)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Ixx)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Ixx)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_I12Min)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_I12Max)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_I22)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_I11)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Centroid)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(put_Centroid)(/*[in]*/ IPoint2d* newVal);
	STDMETHOD(get_Area)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Area)(/*[in]*/ Float64 newVal);

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);
};

#endif //__SHAPEPROPERTIES_H_
