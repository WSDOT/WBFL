///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// BoxBeam.h : Declaration of the CBoxBeam

#include "resource.h"       // main symbols
#include <GeomModel/BoxBeam.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CBoxBeam
class ATL_NO_VTABLE CBoxBeam : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBoxBeam, &CLSID_BoxBeam>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CBoxBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IBoxBeam,
   public IShapeXYPositionImpl<CBoxBeam, WBFL::Geometry::BoxBeam>
{
public:
	CBoxBeam()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetShape(const WBFL::Geometry::BoxBeam& shape);
   virtual WBFL::Geometry::BoxBeam& GetShape() override { return m_Beam; }

DECLARE_REGISTRY_RESOURCEID(IDR_BOXBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBoxBeam)
	COM_INTERFACE_ENTRY(IBoxBeam)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::BoxBeam m_Beam;
   CComPtr<IPoint2d> m_HookPoint;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IBoxBeam
public:
   STDMETHOD(get_W1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_W1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_W2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_W2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_W3)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_W3)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_W4)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_W4)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H3)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H3)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H4)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H4)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H5)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H5)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H6)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H6)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H7)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H7)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_F1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_F1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_F2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_F2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_C1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_C1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(put_VoidCount)(/*[in]*/CollectionIndexType nv) override;
   STDMETHOD(get_VoidCount)(/*[out,retval]*/CollectionIndexType* nv) override;
   STDMETHOD(get_HookPoint)(/*[out,retval]*/ IPoint2d** hookPnt) override;
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;
   STDMETHOD(get_WebWidth)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_BottomFlangeWidth)(/*[out]*/Float64* pLeft, /*[out]*/Float64* pRight) override;
   STDMETHOD(get_TopFlangeWidth)(/*[out]*/Float64* pLeft, /*[out]*/Float64* pRight) override;
   STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
   STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
   STDMETHOD(put_LeftBlockOut)(/*[in]*/VARIANT_BOOL bLeftBlockOut) override;
   STDMETHOD(get_LeftBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbLeftBlockOut) override;
   STDMETHOD(put_RightBlockOut)(/*[in]*/VARIANT_BOOL bRightBlockOut) override;
   STDMETHOD(get_RightBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbRightBlockOut) override;
   STDMETHOD(get_Width)(/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(get_Height)(/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(GetBoundaryPoints)(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppRightTop, IPoint2d** ppRightBottom) override;
   STDMETHOD(GetBoxShape)(/*[out]*/IShape** ppShape) override;
   STDMETHOD(GetVoidShape)(/*[in]*/IndexType idx, /*[out]*/IShape** ppShape) override;
};
