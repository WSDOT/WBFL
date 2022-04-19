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

// UBeam.h : Declaration of the CUBeam

#include "resource.h"       // main symbols
#include <GeomModel/UBeam.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CUBeam
class ATL_NO_VTABLE CUBeam : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUBeam, &CLSID_UBeam>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CUBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IUBeam,
	public IShapeXYPositionImpl<CUBeam, WBFL::Geometry::UBeam>
{
public:
	CUBeam()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

	void SetShape(const WBFL::Geometry::UBeam& shape);
	virtual WBFL::Geometry::UBeam& GetShape() override { return m_Beam; }

DECLARE_REGISTRY_RESOURCEID(IDR_UBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUBeam)
	COM_INTERFACE_ENTRY(IUBeam)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IUBeam
public:
	STDMETHOD(get_T)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_T)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D7)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D7)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D6)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D6)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D5)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D5)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D4)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D4)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D3)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D3)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_D1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_D1)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_W5)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W5)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_W4)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W4)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_W3)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W3)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_W2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_W1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_Slope)(/*[in]*/WebIndexType webIdx,/*[out,retval]*/Float64* slope) override;
	STDMETHOD(get_TopWidth)(/*[out,retval]*/Float64* width) override;
	STDMETHOD(get_TopFlangeWidth)(/*[out,retval]*/Float64* width) override;
	STDMETHOD(get_WebLocation)(/*[in]*/WebIndexType webIdx,/*[out,retval]*/Float64* location) override;
	STDMETHOD(get_WebSpacing)(/*[out,retval]*/Float64* spacing) override;
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64* pVal) override;
	STDMETHOD(get_HookPoint)(/*[out, retval]*/ IPoint2d** pVal) override;
	STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape** pVal) override;
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition** pVal) override;

private:
	WBFL::Geometry::UBeam m_Beam;
	CComPtr<IPoint2d> m_HookPoint;
};
