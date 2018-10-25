///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// EffectiveFlangeWidthTool.h : Declaration of the CEffectiveFlangeWidthTool

#ifndef __EFFECTIVEFLANGEWIDTHTOOL_H_
#define __EFFECTIVEFLANGEWIDTHTOOL_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CEffectiveFlangeWidthTool
class ATL_NO_VTABLE CEffectiveFlangeWidthTool : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEffectiveFlangeWidthTool, &CLSID_EffectiveFlangeWidthTool>,
	public ISupportErrorInfo,
	public IEffectiveFlangeWidthTool,
   public IObjectSafetyImpl<CEffectiveFlangeWidthTool,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CEffectiveFlangeWidthTool()
	{
	}

   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_EFFECTIVEFLANGEWIDTHTOOL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEffectiveFlangeWidthTool)
	COM_INTERFACE_ENTRY(IEffectiveFlangeWidthTool)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   CComPtr<IBridgeGeometryTool> m_BridgeGeometryTool;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IEffectiveFlangeWidthTool
public:
	STDMETHOD(TributaryFlangeWidth)(/*[in]*/IGenericBridge* bridge,/*[in]*/SpanIndexType span,/*[in]*/GirderIndexType gdr,/*[in]*/Float64 location, /*[out,retval]*/Float64 *tribFlangeWidth);
   STDMETHOD(TributaryFlangeWidthEx)(/*[in]*/IGenericBridge* bridge,/*[in]*/SpanIndexType span,/*[in]*/GirderIndexType gdr,/*[in]*/Float64 location, /*[out]*/ Float64* twLeft,/*[out]*/Float64* twRight,/*[out]*/Float64 *tribFlangeWidth);
	STDMETHOD(EffectiveFlangeWidth)(/*[in]*/IGenericBridge* bridge,/*[in]*/SpanIndexType span,/*[in]*/GirderIndexType gdr,/*[in]*/Float64 location, /*[out,retval]*/Float64 *effFlangeWidth);
   STDMETHOD(EffectiveFlangeWidthEx)(/*[in]*/IGenericBridge* bridge,/*[in]*/SpanIndexType span,/*[in]*/GirderIndexType gdr,/*[in]*/Float64 location, /*[out,retval]*/IEffectiveFlangeWidthDetails** details);
};

#endif //__EFFECTIVEFLANGEWIDTHTOOL_H_
