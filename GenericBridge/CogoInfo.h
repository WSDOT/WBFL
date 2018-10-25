///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// CogoInfo.h : Declaration of the CCogoInfo

#ifndef __COGOINFO_H_
#define __COGOINFO_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCogoInfo
class ATL_NO_VTABLE CCogoInfo : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCogoInfo, &CLSID_CogoInfo>,
	public ISupportErrorInfo,
	public ICogoInfo,
   public IObjectSafetyImpl<CCogoInfo,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CCogoInfo()
	{
	}

   void SetBridge(IGenericBridge* pBridge)
   {
      m_pBridge = pBridge;
   }

DECLARE_REGISTRY_RESOURCEID(IDR_COGOINFO)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCogoInfo)
	COM_INTERFACE_ENTRY(ICogoInfo)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   IGenericBridge* m_pBridge;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICogoInfo
public:
   STDMETHOD(get_CLBridgeKey)(/*[out,retval]*/ CogoElementKey* clBridgeKey);
   STDMETHOD(get_AlignmentKey)(/*[out,retval]*/ CogoElementKey* alignmentKey);
	STDMETHOD(get_PierPointID)(/*[in]*/ PierIndexType pierIdx,/*[in]*/ PierPointType pointType, /*[out, retval]*/ CogoElementKey *pVal);
   STDMETHOD(get_GirderLineID)(/*[in]*/ SpanIndexType spanIdx,/*[in]*/ GirderIndexType gdrIdx,/*[out, retval]*/ CogoElementKey *pVal);
   STDMETHOD(get_PierGirderIntersectionPointID)(/*[in]*/ PierIndexType pierIdx,/*[in]*/ GirderIndexType gdrIdx,/*[in]*/ PositionType posType, /*[out, retval]*/ CogoElementKey *pVal);
	STDMETHOD(get_BearingGirderIntersectionPointID)(/*[in]*/ PierIndexType pierIdx,/*[in]*/ GirderIndexType gdrIdx,/*[in]*/ PositionType posType, /*[out, retval]*/ CogoElementKey *pVal);
   STDMETHOD(get_GirderEndPointID)(/*[in]*/SpanIndexType spanIdx,/*[in]*/ GirderIndexType gdrIdx,/*[in]*/EndType endType,/*[out,retval]*/CogoElementKey* pVal);
};

#endif //__COGOINFO_H_
