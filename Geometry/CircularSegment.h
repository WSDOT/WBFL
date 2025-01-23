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

// CircularSegment.h : Declaration of the CCircularSegment

#include "resource.h"       // main symbols
#include <GeomModel/CircularSegment.h>
#include "IShapeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CCircularSegment
class ATL_NO_VTABLE CCircularSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCircularSegment, &CLSID_CircularSegment>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCircularSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public ICircularSegment,
	public IShapeXYPositionImpl<CCircularSegment,WBFL::Geometry::CircularSegment>
{
public:
	CCircularSegment()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

	void SetShape(const WBFL::Geometry::CircularSegment& shape);
	virtual WBFL::Geometry::CircularSegment& GetShape() override { return m_CircularSegment; }

DECLARE_REGISTRY_RESOURCEID(IDR_CIRCULARSEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCircularSegment)
	COM_INTERFACE_ENTRY(ICircularSegment)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IShape)
	COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
	WBFL::Geometry::CircularSegment m_CircularSegment;
	CComPtr<IPoint2d> m_HookPoint;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICircularSegment
public:
	STDMETHOD(get_Rotation)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Rotation)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_InteriorAngle)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_InteriorAngle)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_MidOrdinate)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_MidOrdinate)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Chord)(/*[out, retval]*/ILineSegment2d** ppChord) override;
	STDMETHOD(get_Center)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(put_Center)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_Radius)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Radius)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_HookPoint)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
};
