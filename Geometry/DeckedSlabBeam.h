///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// DeckedSlabBeam.h : Declaration of the CDeckedSlabBeam
#include "resource.h"       // main symbols
#include <GeomModel/DeckedSlabBEam.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CDeckedSlabBeam
class ATL_NO_VTABLE CDeckedSlabBeam : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDeckedSlabBeam, &CLSID_DeckedSlabBeam>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CDeckedSlabBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IDeckedSlabBeam,
   public IShapeXYPositionImpl<CDeckedSlabBeam, WBFL::Geometry::DeckedSlabBeam>
{
public:
	CDeckedSlabBeam()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetShape(const WBFL::Geometry::DeckedSlabBeam& shape);
   virtual WBFL::Geometry::DeckedSlabBeam& GetShape() override { return m_Beam; }

DECLARE_REGISTRY_RESOURCEID(IDR_DECKEDSLABBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDeckedSlabBeam)
	COM_INTERFACE_ENTRY(IDeckedSlabBeam)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::DeckedSlabBeam m_Beam;
   CComPtr<IPoint2d> m_HookPoint;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IDeckedSlabBeam
public:
   STDMETHOD(put_A)(/*[in]*/Float64 a) override;
   STDMETHOD(get_A)(/*[out,retval]*/Float64* a) override;
   STDMETHOD(put_B)(/*[in]*/Float64 b) override;
   STDMETHOD(get_B)(/*[out,retval]*/Float64* b) override;
   STDMETHOD(put_C)(/*[in]*/Float64 c) override;
   STDMETHOD(get_C)(/*[out,retval]*/Float64* c) override;
   STDMETHOD(put_W)(/*[in]*/Float64 w) override;
   STDMETHOD(get_W)(/*[out,retval]*/Float64* w) override;
   STDMETHOD(put_Tt)(/*[in]*/Float64 Tt) override;
   STDMETHOD(get_Tt)(/*[out,retval]*/Float64* Tt) override;
   STDMETHOD(put_Tb)(/*[in]*/Float64 Tb) override;
   STDMETHOD(get_Tb)(/*[out,retval]*/Float64* Tb) override;
   STDMETHOD(put_F)(/*[in]*/Float64 f) override;
   STDMETHOD(get_F)(/*[out,retval]*/Float64* f) override;
   STDMETHOD(put_LeftBlockOut)(/*[in]*/VARIANT_BOOL bLeftBlockOut) override;
   STDMETHOD(get_LeftBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbLeftBlockOut) override;
   STDMETHOD(put_RightBlockOut)(/*[in]*/VARIANT_BOOL bRightBlockOut) override;
   STDMETHOD(get_RightBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbRightBlockOut) override;
   STDMETHOD(put_VoidCount)(/*[in]*/IndexType nv) override;
   STDMETHOD(get_VoidCount)(/*[out,retval]*/IndexType* nv) override;
   STDMETHOD(get_Height)(/*[out, retval]*/Float64* pVal) override;
   STDMETHOD(get_HookPoint)(/*[out,retval]*/IPoint2d** hookPnt) override;
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;
   STDMETHOD(GetSlabShape)(/*[out]*/IShape** ppShape) override;
   STDMETHOD(GetVoidShape)(/*[in]*/IndexType idx, /*[out]*/IShape** ppShape) override;
   STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
   STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
};
