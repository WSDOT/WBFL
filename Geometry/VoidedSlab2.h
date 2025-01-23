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

// VoidedSlab2.h : Declaration of the CVoidedSlab2
#include "resource.h"       // main symbols
#include <GeomModel/VoidedSlab2.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CVoidedSlab2
class ATL_NO_VTABLE CVoidedSlab2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVoidedSlab2, &CLSID_VoidedSlab2>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CVoidedSlab2,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IVoidedSlab2,
   public IShapeXYPositionImpl<CVoidedSlab2, WBFL::Geometry::VoidedSlab2>
{
public:
	CVoidedSlab2()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetShape(const WBFL::Geometry::VoidedSlab2& shape);
   virtual WBFL::Geometry::VoidedSlab2& GetShape() override { return m_Beam; }

DECLARE_REGISTRY_RESOURCEID(IDR_VOIDEDSLAB2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVoidedSlab2)
	COM_INTERFACE_ENTRY(IVoidedSlab2)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::VoidedSlab2 m_Beam;
   CComPtr<IPoint2d> m_HookPoint;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IVoidedSlab2
public:
   STDMETHOD(put_Height)(/*[in]*/Float64 h) override;
   STDMETHOD(get_Height)(/*[out,retval]*/Float64* h) override;
   STDMETHOD(put_Width)(/*[in]*/Float64 w) override;
   STDMETHOD(get_Width)(/*[out,retval]*/Float64* w) override;
   STDMETHOD(put_C1)(/*[in]*/Float64 c1) override;
   STDMETHOD(get_C1)(/*[out,retval]*/Float64* c1) override;
   STDMETHOD(put_C2)(/*[in]*/Float64 c2) override;
   STDMETHOD(get_C2)(/*[out,retval]*/Float64* c2) override;
   STDMETHOD(put_C3)(/*[in]*/Float64 c3) override;
   STDMETHOD(get_C3)(/*[out,retval]*/Float64* c3) override;
   STDMETHOD(put_LeftBlockOut)(/*[in]*/VARIANT_BOOL bLeftBlockOut) override;
   STDMETHOD(get_LeftBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbLeftBlockOut) override;
   STDMETHOD(put_RightBlockOut)(/*[in]*/VARIANT_BOOL bRightBlockOut) override;
   STDMETHOD(get_RightBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbRightBlockOut) override;
   STDMETHOD(put_ExteriorVoidDiameter)(/*[in]*/Float64 d) override;
   STDMETHOD(get_ExteriorVoidDiameter)(/*[out,retval]*/Float64* d) override;
   STDMETHOD(put_InteriorVoidDiameter)(/*[in]*/Float64 d) override;
   STDMETHOD(get_InteriorVoidDiameter)(/*[out,retval]*/Float64* d) override;
   STDMETHOD(put_ExteriorVoidSpacing)(/*[in]*/Float64 s) override;
   STDMETHOD(get_ExteriorVoidSpacing)(/*[out,retval]*/Float64* s) override;
   STDMETHOD(put_InteriorVoidSpacing)(/*[in]*/Float64 s) override;
   STDMETHOD(get_InteriorVoidSpacing)(/*[out,retval]*/Float64* s) override;
   STDMETHOD(put_ExteriorVoidElevation)(/*[in]*/Float64 h1) override;
   STDMETHOD(get_ExteriorVoidElevation)(/*[out,retval]*/Float64* h1) override;
   STDMETHOD(put_InteriorVoidElevation)(/*[in]*/Float64 h2) override;
   STDMETHOD(get_InteriorVoidElevation)(/*[out,retval]*/Float64* h2) override;
   STDMETHOD(put_VoidCount)(/*[in]*/IndexType nv) override;
   STDMETHOD(get_VoidCount)(/*[out,retval]*/IndexType* nv) override;
   STDMETHOD(GetSlabShape)(/*[out]*/IShape** ppShape) override;
   STDMETHOD(GetVoidShape)(/*[in]*/IndexType idx, /*[out]*/IShape** ppShape) override;
   STDMETHOD(get_HookPoint)(/*[out,retval]*/IPoint2d** hookPnt) override;
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;
   STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
   STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
};
