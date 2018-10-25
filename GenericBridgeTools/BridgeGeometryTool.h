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
   CComPtr<ILine2d> m_Line1;
   CComPtr<ILine2d> m_Line2;
   CComPtr<ILineSegment2d> m_LineSegment1;
   CComPtr<ILineSegment2d> m_LineSegment2;
   CComPtr<IGeomUtil2d> m_GeomUtil;

   HRESULT GetDeckEdgePath(IGenericBridge* bridge,DirectionType side,IPath** ppPath);


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IBridgeGeometryTool
public:
	STDMETHOD(PointBySSMbr)(IGenericBridge* bridge,GirderIDType ssMbrID, Float64 distFromStartOfSSMbr,IPoint2d** point);
   STDMETHOD(PointBySegment)(IGenericBridge* bridge,GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 distFromStartOfSegment,IPoint2d** point);
	STDMETHOD(StationAndOffsetBySSMbr)(IGenericBridge* bridge,GirderIDType ssMbrID, Float64 distFromStartOfSSMbr, IStation** station, Float64* offset);
   STDMETHOD(StationAndOffsetBySegment)(IGenericBridge* bridge,GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 distFromStartOfSegment, IStation** station, Float64* offset);
	STDMETHOD(GirderPathOffset)(IGenericBridge* bridge,GirderIDType ssMbrID, SegmentIndexType segIdx, VARIANT varStation, Float64* offset);
 //  STDMETHOD(GirderLineBearing)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ SpanIndexType spanIdx,/*[in]*/ GirderIndexType gdrIdx, /*[out,retval]*/ IDirection** direction);
	//STDMETHOD(GirderLinePoint)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ Float64 distFromStartOfBridge,/*[in]*/ GirderIndexType gdrIdx, /*[out]*/ SpanIndexType* spanIdx, /*[out]*/ Float64* distFromStartOfSpan);
   STDMETHOD(DeckEdgePoint)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ IDirection* direction,/*[in]*/ DirectionType side,/*[out,retval]*/ IPoint2d** point);
   STDMETHOD(DeckEdgePoints)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ DirectionType side,/*[in]*/ CollectionIndexType nPoints,/*[out,retval]*/ IPoint2dCollection** points);
   STDMETHOD(DeckOffset)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ IDirection* direction,/*[in]*/ DirectionType side,/*[out,retval]*/ Float64* pOffset);
   STDMETHOD(CurbOffset)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ IDirection* direction,/*[in]*/ DirectionType side,/*[out,retval]*/ Float64* pOffset);
   STDMETHOD(DeckOverhang)(IGenericBridge* bridge,Float64 station,GirderIDType ssMbrID,IDirection* direction,DirectionType side,Float64* pOverhang);
   STDMETHOD(DeckOverhangBySSMbr)(IGenericBridge* bridge,GirderIDType ssMbrID, Float64 distFromStartOfSSMbr,IDirection* direction,DirectionType side,Float64* pOverhang);
   STDMETHOD(DeckOverhangBySegment)(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,IDirection* direction,DirectionType side,Float64* pOverhang);
   STDMETHOD(GirderSpacingBySSMbr)(IGenericBridge* bridge,GirderIDType ssMbrID, Float64 distFromStartOfSSMbr,GirderIDType otherSSMbrID,Float64* pSpacing);
   STDMETHOD(GirderSpacingBySegment)(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 distFromStartOfSegment,GirderIDType otherSSMbrID,Float64* pSpacing);
   STDMETHOD(InteriorCurbOffset)(/*[in]*/ IGenericBridge* bridge,/*[in]*/ Float64 station,/*[in]*/ IDirection* direction,/*[in]*/ DirectionType side,/*[out,retval]*/ Float64* pOffset);
};

#endif //__BridgeGeometryTool_H_
