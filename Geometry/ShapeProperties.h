///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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

// ShapeProperties.h : Declaration of the CShapeProperties

#ifndef __SHAPEPROPERTIES_H_
#define __SHAPEPROPERTIES_H_

#include "resource.h"       // main symbols
#include <GeomModel/ShapeProperties.h>

/////////////////////////////////////////////////////////////////////////////
// CShapeProperties
class ATL_NO_VTABLE CShapeProperties : 
	public CComObjectRootEx<CComSingleThreadModel>,
   public ISupportErrorInfo,
	public CComCoClass<CShapeProperties, &CLSID_ShapeProperties>,
   public IObjectSafetyImpl<CShapeProperties,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public IShapeProperties
{
public:
	CShapeProperties()
	{
	}

   HRESULT FinalConstruct();
	void SetProperties(const WBFL::Geometry::ShapeProperties& props) { m_Properties = props; }

DECLARE_REGISTRY_RESOURCEID(IDR_SHAPEPROPERTIES)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CShapeProperties)
   COM_INTERFACE_ENTRY(IShapeProperties)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::ShapeProperties m_Properties;

// ISupportErrorInfo
public:
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IShapeProperties
public:
   STDMETHOD(AddProperties)(/*[in]*/ IShapeProperties* props) override;
	STDMETHOD(get_PrincipleDirection)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_CoordinateSystem)(/*[out, retval]*/ CoordinateSystemType *pVal) override;
	STDMETHOD(put_CoordinateSystem)(/*[in]*/ CoordinateSystemType newVal) override;
	STDMETHOD(get_Orientation)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Orientation)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Origin)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(put_Origin)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_Ybottom)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Ybottom)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Ytop)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Ytop)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Xright)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Xright)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Xleft)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Xleft)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Ixy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Ixy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Iyy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Iyy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Ixx)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Ixx)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_I12Min)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_I12Max)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_I22)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_I11)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Centroid)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(put_Centroid)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_Area)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Area)(/*[in]*/ Float64 newVal) override;
};

#endif //__SHAPEPROPERTIES_H_
