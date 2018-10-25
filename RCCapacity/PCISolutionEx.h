///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
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

// PCISolutionEx.h : Declaration of the CPCISolutionEx

#ifndef __PCISOLUTIONEX_H_
#define __PCISOLUTIONEX_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPCISolutionEx
class ATL_NO_VTABLE CPCISolutionEx : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPCISolutionEx, &CLSID_PCISolutionEx>,
	public IRCSolutionEx,
	public IPCISolutionEx
{
public:
	CPCISolutionEx()
	{
      m_AvgBeta1 = 0.0;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PCISOLUTIONEX)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPCISolutionEx)
	COM_INTERFACE_ENTRY(IPCISolutionEx)
	COM_INTERFACE_ENTRY(IRCSolutionEx)
END_COM_MAP()

   CComPtr<IRCSolutionEx> m_Solution;
   Float64 m_AvgBeta1;

// IRCSolutionEx
public:
	STDMETHOD(get_Yweb)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Yflange)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_T)(/*[out,retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Cweb)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Cflange)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(InitSolution)(/*[in]*/ Float64 Mn,/*[in]*/ Float64 c,/*[in]*/ IDblArray* fs,/*[in]*/ IDblArray* fps,/*[in]*/ Float64 Cflange,/*[in]*/ Float64 Cweb,/*[in]*/ Float64 T,/*[in]*/ Float64 Yflange,/*[in]*/ Float64 Yweb) override;
	STDMETHOD(get_Mn)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_NeutralAxisDepth)(/*[out, retval]*/ Float64* pVal) override;
   STDMETHOD(get_fps)(/*[out,retval]*/ IDblArray** fps) override;
   STDMETHOD(get_fs)(/*[out,retval]*/ IDblArray** fs) override;

// IPCISolutionEx
public:
	STDMETHOD(InitSolution)(/*[in]*/ Float64 Mn,/*[in]*/ Float64 c,/*[in]*/ IDblArray* fs,/*[in]*/ IDblArray* fps,/*[in]*/ Float64 Cflange,/*[in]*/ Float64 Cweb,/*[in]*/ Float64 T,/*[in]*/ Float64 Yflange,/*[in]*/ Float64 Yweb,/*[in]*/ Float64 avgBeta1) override;
   STDMETHOD(get_AvgBeta1)(/*[out, retval]*/ Float64 *pVal) override;
};

#endif //__PCISOLUTIONEX_H_
