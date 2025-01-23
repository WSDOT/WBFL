///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
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

// LRFDSolution.h : Declaration of the CLRFDSolution

#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLRFDSolution
class ATL_NO_VTABLE CLRFDSolution : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLRFDSolution, &CLSID_LRFDSolution>,
	public ISupportErrorInfo,
	public ILRFDSolution
{
public:
	CLRFDSolution()
	{
      m_Alpha1  = 0;
      m_Beta1   = 0;
      m_Mn      = 0;
      m_c       = 0;
      m_fps     = 0;
      m_Cflange = 0;
      m_Cweb    = 0;
      m_T       = 0;
      m_Yflange = 0;
      m_Yweb    = 0;
      m_bIsOverReinforced = VARIANT_FALSE;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LRFDSOLUTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLRFDSolution)
   COM_INTERFACE_ENTRY(IRCSolution)
   COM_INTERFACE_ENTRY(ILRFDSolution)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   Float64 m_Alpha1;
   Float64 m_Beta1;
   Float64 m_Mn;
   Float64 m_c;
   Float64 m_fps;
   Float64 m_Cflange;
   Float64 m_Cweb;
   Float64 m_Yflange;
   Float64 m_Yweb;
   Float64 m_T;
   VARIANT_BOOL m_bIsOverReinforced;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IRCSolution
public:
	STDMETHOD(get_Yweb)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Yflange)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_T)(/*[out,retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Cweb)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Cflange)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_IsOverReinforced)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(InitSolution)(/*[in]*/ Float64 Mn,/*[in]*/ Float64 c,/*[in]*/ Float64 fps,/*[in]*/ Float64 Cflange,/*[in]*/ Float64 Cweb,/*[in]*/ Float64 T,/*[in]*/ Float64 Yflange,/*[in]*/ Float64 Yweb,/*[in]*/ VARIANT_BOOL bOverReinforced) override;
	STDMETHOD(get_Mn)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_NeutralAxisDepth)(/*[out, retval]*/ Float64* pVal) override;
   STDMETHOD(get_fps)(/*[out,retval]*/ Float64* fps) override;

// ILRFDSolution
public:
   STDMETHOD(InitLRFDSolution)(/*[in]*/ Float64 alpha1,/*[in]*/ Float64 beta1,/*[in]*/ Float64 Mn,/*[in]*/ Float64 c,/*[in]*/ Float64 fps,/*[in]*/ Float64 Cflange,/*[in]*/ Float64 Cweb,/*[in]*/ Float64 T,/*[in]*/ Float64 Yflange,/*[in]*/ Float64 Yweb,/*[in]*/ VARIANT_BOOL bOverReinforced) override;
   STDMETHOD(get_Alpha1)(/*[out,retval]*/Float64* pAlpha1) override;
   STDMETHOD(get_Beta1)(/*[out,retval]*/Float64* pBeta1) override;
};
