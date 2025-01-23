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
#pragma once

// NUBeam.h : Declaration of the CNUBeam

#include "resource.h"       // main symbols
#include <GeomModel/NUBeam.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CNUBeam
class ATL_NO_VTABLE CNUBeam : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CNUBeam, &CLSID_NUBeam>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CNUBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public INUBeam,
	public IShapeXYPositionImpl<CNUBeam, WBFL::Geometry::NUBeam>
{
public:
	CNUBeam()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

	void SetShape(const WBFL::Geometry::NUBeam& shape);
	virtual WBFL::Geometry::NUBeam& GetShape() override { return m_Beam; }

DECLARE_REGISTRY_RESOURCEID(IDR_NUBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNUBeam)
	COM_INTERFACE_ENTRY(INUBeam)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
	WBFL::Geometry::NUBeam m_Beam;
	CComPtr<IPoint2d> m_HookPoint;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// INUBeam
public:
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(get_TopFlangeWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_BottomFlangeWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_AvgWebWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_HookPoint)(/*[out,retval]*/ IPoint2d** hookPnt) override;
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;
	STDMETHOD(get_R4)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_R4)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_R3)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_R3)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_R2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_R2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_R1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_R1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_EndBlock)(/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(put_EndBlock)(/*[in]*/Float64 newVal) override;
	STDMETHOD(get_T)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_T)(/*[in]*/ Float64 newVal) override;
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
	STDMETHOD(get_W2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_W1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_W1)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_C1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_C1)(/*[in]*/ Float64 newVal) override;
};
