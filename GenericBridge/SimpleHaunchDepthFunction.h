///////////////////////////////////////////////////////////////////////
// GenericBridge - Tools for manipluating the Generic Bridge Modeling
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

// SimpleHaunchDepthFunction.h : Declaration of the CSimpleHaunchDepthFunction

#ifndef __SimpleHaunchDepthFunction_H_
#define __SimpleHaunchDepthFunction_H_

#include "resource.h"       // main symbols

class CSimpleHaunchDepthFunction;

/////////////////////////////////////////////////////////////////////////////
// CSimpleHaunchDepthFunction
class ATL_NO_VTABLE CSimpleHaunchDepthFunction : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleHaunchDepthFunction, &CLSID_SimpleHaunchDepthFunction>,
	public ISupportErrorInfo,
   public ISimpleHaunchDepthFunction,
   public IObjectSafetyImpl<CSimpleHaunchDepthFunction,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CSimpleHaunchDepthFunction():
      m_LayoutLength(Float64_Inf), // make things obvious if were're not initialized
      m_StartOffset(Float64_Inf)
	{
	}

   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SIMPLEHAUNCHDEPTHFUNCTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSimpleHaunchDepthFunction)
   COM_INTERFACE_ENTRY(ISimpleHaunchDepthFunction)
   COM_INTERFACE_ENTRY(IHaunchDepthFunction)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

protected:

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

public:
   // ISimpleHaunchDepthFunction
   STDMETHOD(Initialize)(/*[in]*/Float64 startOffset, /*[in]*/Float64 layoutLength, /*[in]*/IDblArray* haunchVals);

   // IHaunchDepthFunction
   STDMETHOD(GetHaunchDepth)(/*[in]*/Float64 location, /*[out, retval]*/Float64* pHaunchDepth);


private:
   Float64 m_StartOffset;
   Float64 m_LayoutLength;
   std::vector<Float64> m_HaunchDepths;
};

#endif //__SimpleHaunchDepthFunction_H_
