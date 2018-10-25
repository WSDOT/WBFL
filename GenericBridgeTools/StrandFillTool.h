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

// StrandFillTool.h : Declaration of the CStrandFillTool
#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CStrandFillTool
class ATL_NO_VTABLE CStrandFillTool : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStrandFillTool, &CLSID_StrandFillTool>,
	public ISupportErrorInfo,
	public IStrandFillTool,
   public IObjectSafetyImpl<CStrandFillTool,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CStrandFillTool()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_STRANDFILLTOOL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStrandFillTool)
	COM_INTERFACE_ENTRY(IStrandFillTool)
	COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStrandFillTool
public:
   STDMETHOD(ComputeHarpedStrandMaxFill)(IStrandGridFiller* pEndGridFiller,IStrandGridFiller* pHPGridFiller,StrandIndexType* pMaxStrandCount,IIndexArray** ppStrandFill);
};
