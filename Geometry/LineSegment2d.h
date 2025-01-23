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

// LineSegment2d.h : Declaration of the CLineSegment2d

#include "resource.h"       // main symbols
#include <GeomModel/LineSegment2d.h>

/////////////////////////////////////////////////////////////////////////////
// CLineSegment2d
class ATL_NO_VTABLE CLineSegment2d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLineSegment2d, &CLSID_LineSegment2d>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CLineSegment2d,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
   public ILineSegment2d
{
public:
	CLineSegment2d()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetLineSegment(const WBFL::Geometry::LineSegment2d& ls);

DECLARE_REGISTRY_RESOURCEID(IDR_LINESEGMENT2D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLineSegment2d)
	COM_INTERFACE_ENTRY(ILineSegment2d)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   WBFL::Geometry::LineSegment2d m_LineSegment;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILineSegment2d
public:
   STDMETHOD(Clone)(/*[out,retval]*/ILineSegment2d** ppClone) override;
   STDMETHOD(ContainsPoint)(/*[in]*/IPoint2d* pPoint, /*[in]*/Float64 tolerance, /*[out]*/VARIANT_BOOL* pbResult) override;
   STDMETHOD(Divide)(/*[in]*/IndexType nSpaces, /*[out]*/IPoint2dCollection** ppPoints) override;
   STDMETHOD(ThroughPoints)(/*[in]*/ IPoint2d* p1, /*[in]*/ IPoint2d* p2) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize) override;
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy) override;
   STDMETHOD(Offset2)(/*[in]*/ Float64 distance) override;
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pCenter,/*[in]*/ Float64 angle) override;
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx, /*[in]*/ Float64 cy, /*[in]*/ Float64 angle) override;
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_EndPoint)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(put_EndPoint)(/*[in]*/ IPoint2d* newVal) override;
	STDMETHOD(get_StartPoint)(/*[out, retval]*/ IPoint2d* *pVal) override;
	STDMETHOD(put_StartPoint)(/*[in]*/ IPoint2d* newVal) override;
};
