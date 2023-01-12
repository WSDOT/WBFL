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

// TrafficBarrier.h : Declaration of the CTrafficBarrier

#include "resource.h"       // main symbols
#include <GeomModel/TrafficBarrier.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CTrafficBarrier
class ATL_NO_VTABLE CTrafficBarrier : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTrafficBarrier, &CLSID_TrafficBarrier>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CTrafficBarrier,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public ITrafficBarrier,
	public IShapeXYPositionImpl<CTrafficBarrier, WBFL::Geometry::TrafficBarrier>
{
public:
	CTrafficBarrier()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

	void SetShape(const WBFL::Geometry::TrafficBarrier& shape);
	virtual WBFL::Geometry::TrafficBarrier& GetShape() override { return m_Barrier; }

DECLARE_REGISTRY_RESOURCEID(IDR_TRAFFICBARRIER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTrafficBarrier)
	COM_INTERFACE_ENTRY(ITrafficBarrier)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
	WBFL::Geometry::TrafficBarrier m_Barrier;
	CComPtr<IPoint2d> m_HookPoint;

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ITrafficBarrier
public:
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(get_Orientation)(/*[out, retval]*/ TrafficBarrierOrientation *pVal) override;
	STDMETHOD(put_Orientation)(/*[in]*/ TrafficBarrierOrientation newVal) override;
	STDMETHOD(get_HookPoint)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_Y4)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y4)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Y3)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y3)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Y2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Y1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Y1)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X5)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X5)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X4)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X4)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X3)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X3)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X2)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X2)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_X1)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_X1)(/*[in]*/ Float64 newVal) override;
};
