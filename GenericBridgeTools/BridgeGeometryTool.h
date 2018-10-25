///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2014  Washington State Department of Transportation
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

// BridgeGeometryTool.h : Declaration of the CBridgeGeometryTool

#ifndef __BridgeGeometryTool_H_
#define __BridgeGeometryTool_H_

#include "resource.h"       // main symbols
#include <vector>
#include <set>
#include <MathEx.h>

/////////////////////////////////////////////////////////////////////////////
// CBridgeGeometryTool
class ATL_NO_VTABLE CBridgeGeometryTool : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBridgeGeometryTool, &CLSID_BridgeGeometryTool>,
	public ISupportErrorInfo,
	public IBridgeGeometryTool,
   public IObjectSafetyImpl<CBridgeGeometryTool,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CBridgeGeometryTool()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_BRIDGEGEOMETRYTOOL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBridgeGeometryTool)
	COM_INTERFACE_ENTRY(IBridgeGeometryTool)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   CComPtr<ICogoEngine> m_CogoEngine;

   HRESULT GetDeckEdgePath(IGenericBridge* bridge,DirectionType side,IPath** ppPath);
   HRESULT GetPierLine(IGenericBridge* bridge,PierIndexType pierIdx,ILine2d** ppLine);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IBridgeGeometryTool
public:
	STDMETHOD(Point)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ SpanIndexType spanIdx,/*[in]*/ GirderIndexType gdrIdx, /*[in]*/ Float64 distFromStartOfGirder,/*[out]*/ IPoint2d** point);
	STDMETHOD(StationAndOffset)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ SpanIndexType spanIdx,/*[in]*/ GirderIndexType gdrIdx, /*[in]*/ Float64 distFromStartOfGirder,/*[out]*/ IStation** station, /*[out]*/ Float64* offset);
	STDMETHOD(GirderPathOffset)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ SpanIndexType spanIdx,/*[in]*/ GirderIndexType gdrIdx, /*[in]*/ VARIANT varStation, /*[out,retval]*/ Float64* offset);
   STDMETHOD(GirderLineBearing)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ SpanIndexType spanIdx,/*[in]*/ GirderIndexType gdrIdx, /*[out,retval]*/ IDirection** direction);
	STDMETHOD(GirderLinePoint)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ Float64 distFromStartOfBridge,/*[in]*/ GirderIndexType gdrIdx, /*[out]*/ SpanIndexType* spanIdx, /*[out]*/ Float64* distFromStartOfSpan);
   STDMETHOD(DeckEdgePoint)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ IDirection* direction,/*[in]*/ DirectionType side,/*[out,retval]*/ IPoint2d** point);
	STDMETHOD(DeckEdgePoints)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ DirectionType side,/*[in]*/ CollectionIndexType nPoints,/*[out,retval]*/ IPoint2dCollection** points);
   STDMETHOD(DeckOffset)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ IDirection* direction,/*[in]*/ DirectionType side,/*[out,retval]*/ Float64* pOffset);
   STDMETHOD(CurbOffset)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ IDirection* direction,/*[in]*/ DirectionType side,/*[out,retval]*/ Float64* pOffset);
	STDMETHOD(DeckOverhang)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ IDirection* direction,/*[in]*/ DirectionType side,/*[out,retval]*/ Float64* pOverhang);
	STDMETHOD(DeckOverhangFromGirder)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ SpanIndexType spanIdx,/*[in]*/ GirderIndexType gdrIdx, /*[in]*/ Float64 distFromStartOfGirder,/*[in]*/ DirectionType side,/*[out]*/ Float64* pOverhang);
   STDMETHOD(InteriorCurbOffset)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ IDirection* direction,/*[in]*/ DirectionType side,/*[out,retval]*/ Float64* pOffset);
};

#endif //__BridgeGeometryTool_H_
