///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// PCISolution.h : Declaration of the CPCISolution

#ifndef __PCISOLUTION_H_
#define __PCISOLUTION_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPCISolution
class ATL_NO_VTABLE CPCISolution : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPCISolution, &CLSID_PCISolution>,
	public IRCSolution,
	public IPCISolution
{
public:
	CPCISolution()
	{
      m_AvgBeta1 = 0.0;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PCISOLUTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPCISolution)
	COM_INTERFACE_ENTRY(IPCISolution)
	COM_INTERFACE_ENTRY(IRCSolution)
END_COM_MAP()

   CComPtr<IRCSolution> m_Solution;
   Float64 m_AvgBeta1;

// IRCSolution
public:
	STDMETHOD(get_Yweb)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Yflange)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(get_T)(/*[out,retval]*/ Float64 *pVal);
	STDMETHOD(get_Cweb)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Cflange)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_IsOverReinforced)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(InitSolution)(/*[in]*/ Float64 Mn,/*[in]*/ Float64 c,/*[in]*/ Float64 fps,/*[in]*/ Float64 Cflange,/*[in]*/ Float64 Cweb,/*[in]*/ Float64 T,/*[in]*/ Float64 Yflange,/*[in]*/ Float64 Yweb,/*[in]*/ VARIANT_BOOL bOverReinforced);
	STDMETHOD(get_Mn)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(get_NeutralAxisDepth)(/*[out, retval]*/ Float64* pVal);
   STDMETHOD(get_fps)(/*[out,retval]*/ Float64* fps);

// IPCISolution
public:
	STDMETHOD(InitSolution)(/*[in]*/ Float64 Mn,/*[in]*/ Float64 c,/*[in]*/ Float64 fps,/*[in]*/ Float64 Cflange,/*[in]*/ Float64 Cweb,/*[in]*/ Float64 T,/*[in]*/ Float64 Yflange,/*[in]*/ Float64 Yweb,/*[in]*/ VARIANT_BOOL bOverReinforced,/*[in]*/ Float64 avgBeta1);
   STDMETHOD(get_AvgBeta1)(/*[out, retval]*/ Float64 *pVal);
};

#endif //__PCISOLUTION_H_
