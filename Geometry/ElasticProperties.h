///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// ElasticProperties.h : Declaration of the CElasticProperties

#ifndef __ELASTICPROPERTIES_H_
#define __ELASTICPROPERTIES_H_

#include "resource.h"       // main symbols
#include <GeomModel/ElasticProperties.h>

/////////////////////////////////////////////////////////////////////////////
// CElasticProperties
class ATL_NO_VTABLE CElasticProperties : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CElasticProperties, &CLSID_ElasticProperties>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CElasticProperties,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IElasticProperties
{
public:
	CElasticProperties()
	{
	}

   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_ELASTICPROPERTIES)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CElasticProperties)
	COM_INTERFACE_ENTRY(IElasticProperties)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IElasticProperties
public:
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
	STDMETHOD(get_EIxy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EIxy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EIyy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EIyy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EIxx)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EIxx)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_EI12Min)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_EI12Max)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_EI22)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_EI11)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Centroid)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(put_Centroid)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_EA)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EA)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(AddProperties)(/*[in]*/ IElasticProperties* props) override;
	STDMETHOD(TransformProperties)(/*[in]*/ Float64 E,/*[out,retval]*/ IShapeProperties** props) override;

private:
	WBFL::Geometry::ElasticProperties m_Props;
};

#endif //__ELASTICPROPERTIES_H_
