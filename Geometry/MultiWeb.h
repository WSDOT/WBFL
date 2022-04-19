///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
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
#pragma once

// MultiWeb.h : Declaration of the CMultiWeb

#include "resource.h"       // main symbols
#include <GeomModel/MultiWeb.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiWeb
class ATL_NO_VTABLE CMultiWeb : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMultiWeb, &CLSID_MultiWeb>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CMultiWeb,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IMultiWeb,
	public IShapeXYPositionImpl<CMultiWeb, WBFL::Geometry::MultiWeb>
{
public:
	CMultiWeb()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

	void SetShape(const WBFL::Geometry::MultiWeb& shape);
	virtual WBFL::Geometry::MultiWeb& GetShape() override { return m_Beam; }

DECLARE_REGISTRY_RESOURCEID(IDR_MULTIWEB)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMultiWeb)
	COM_INTERFACE_ENTRY(IMultiWeb)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
	WBFL::Geometry::MultiWeb m_Beam;
	CComPtr<IPoint2d> m_HookPoint;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IMultiWeb
public:
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(get_TopFlangeWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_AvgWebWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_HookPoint)(/*[out,retval]*/ IPoint2d** hookPnt) override;
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;
	STDMETHOD(get_WebLocation)(/*[in]*/WebIndexType webIdx,/*[out,retval]*/Float64* location) override;
   STDMETHOD(get_WebCount)(/*[out, retval]*/ WebIndexType *pVal) override;
	STDMETHOD(put_WebCount)(/*[in]*/ WebIndexType newVal) override;
	STDMETHOD(get_T2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_T2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_T1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_T1)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D1)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_W2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_W1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W1)(/*[in]*/ Float64 newVal) override;
};
