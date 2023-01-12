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

// VoidedSlab.h : Declaration of the CVoidedSlab

#include "resource.h"       // main symbols
#include <GeomModel/VoidedSlab.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CVoidedSlab
class ATL_NO_VTABLE CVoidedSlab : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVoidedSlab, &CLSID_VoidedSlab>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CVoidedSlab,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IVoidedSlab,
   public IShapeXYPositionImpl<CVoidedSlab, WBFL::Geometry::VoidedSlab>
{
public:
	CVoidedSlab()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetShape(const WBFL::Geometry::VoidedSlab& shape);
   virtual WBFL::Geometry::VoidedSlab& GetShape() override { return m_Beam; }

DECLARE_REGISTRY_RESOURCEID(IDR_VOIDEDSLAB)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVoidedSlab)
	COM_INTERFACE_ENTRY(IVoidedSlab)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::VoidedSlab m_Beam;
   CComPtr<IPoint2d> m_HookPoint;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IVoidedSlab
public:
   STDMETHOD(put_Height)(/*[in]*/Float64 h) override;
   STDMETHOD(get_Height)(/*[out,retval]*/Float64* h) override;
   STDMETHOD(put_Width)(/*[in]*/Float64 w) override;
   STDMETHOD(get_Width)(/*[out,retval]*/Float64* w) override;
   STDMETHOD(put_VoidDiameter)(/*[in]*/Float64 d) override;
   STDMETHOD(get_VoidDiameter)(/*[out,retval]*/Float64* d) override;
   STDMETHOD(put_VoidSpacing)(/*[in]*/Float64 s) override;
   STDMETHOD(get_VoidSpacing)(/*[out,retval]*/Float64* s) override;
   STDMETHOD(put_VoidCount)(/*[in]*/CollectionIndexType nv) override;
   STDMETHOD(get_VoidCount)(/*[out,retval]*/CollectionIndexType* nv) override;
   STDMETHOD(GetSlabShape)(/*[out]*/IShape** ppShape) override;
   STDMETHOD(GetVoidShape)(/*[in]*/IndexType idx, /*[out]*/IShape** ppShape) override;
   STDMETHOD(get_HookPoint)(/*[out,retval]*/IPoint2d** hookPnt) override;
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;
   STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
   STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
};
