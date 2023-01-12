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

// MultiWeb2.h : Declaration of the CMultiWeb2

#include "resource.h"       // main symbols
#include <GeomModel/MultiWeb2.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiWeb2
class ATL_NO_VTABLE CMultiWeb2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMultiWeb2, &CLSID_MultiWeb2>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CMultiWeb2,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IMultiWeb2,
   public IShapeXYPositionImpl<CMultiWeb2, WBFL::Geometry::MultiWeb2>
{
public:
	CMultiWeb2()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetShape(const WBFL::Geometry::MultiWeb2& shape);
   virtual WBFL::Geometry::MultiWeb2& GetShape() override { return m_Beam; }

DECLARE_REGISTRY_RESOURCEID(IDR_MULTIWEB2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMultiWeb2)
	COM_INTERFACE_ENTRY(IMultiWeb2)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::MultiWeb2 m_Beam;
   CComPtr<IPoint2d> m_HookPoint;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IMultiWeb2
public:
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(get_AvgWebWidth)(/*[in]*/ WebIndexType webIdx,/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_TopFlangeWidth)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_HookPoint)(/*[out,retval]*/ IPoint2d** hookPnt) override;
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;
	STDMETHOD(get_WebLocation)(/*[in]*/WebIndexType webIdx,/*[out,retval]*/Float64* location) override;
   STDMETHOD(get_WebCount)(/*[out, retval]*/ WebIndexType *pVal) override;
	STDMETHOD(put_WebCount)(/*[in]*/ WebIndexType newVal) override;
   STDMETHOD(get_W1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_W1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_W2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_W2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_H3)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_H3)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_T1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_T1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_T2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_T2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_T3)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_T3)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_T4)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_T4)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_T5)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_T5)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_F1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_F1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_F2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_F2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_C1)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_C1)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_C2)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_C2)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(put_LeftBlockOut)(/*[in]*/VARIANT_BOOL bLeftBlockOut) override;
   STDMETHOD(get_LeftBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbLeftBlockOut) override;
   STDMETHOD(put_RightBlockOut)(/*[in]*/VARIANT_BOOL bRightBlockOut) override;
   STDMETHOD(get_RightBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbRightBlockOut) override;
};
