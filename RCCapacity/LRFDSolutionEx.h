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

// LRFDSolutionEx.h : Declaration of the CLRFDSolutionEx

#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRCSolutionEx
class ATL_NO_VTABLE CLRFDSolutionEx : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLRFDSolutionEx, &CLSID_LRFDSolutionEx>,
	public ISupportErrorInfo,
	public ILRFDSolutionEx
{
public:
	CLRFDSolutionEx()
	{
      m_Alpha1  = 0;
      m_Beta1   = 0;
      m_Mn      = 0;
      m_c       = 0;
      m_Cflange = 0;
      m_Cweb    = 0;
      m_T       = 0;
      m_Yflange = 0;
      m_Yweb    = 0;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_LRFDSOLUTIONEX)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLRFDSolutionEx)
	COM_INTERFACE_ENTRY(IRCSolutionEx)
   COM_INTERFACE_ENTRY(ILRFDSolutionEx)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


private:
   Float64 m_Alpha1;
   Float64 m_Beta1;
   Float64 m_Mn;
   Float64 m_c;
   CComPtr<IDblArray> m_fs;
   CComPtr<IDblArray> m_fps;
   Float64 m_Cflange;
   Float64 m_Cweb;
   Float64 m_Yflange;
   Float64 m_Yweb;
   Float64 m_T;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

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

// ILRFDSolutionEx
public:
   STDMETHOD(InitLRFDSolution)(/*[in]*/ Float64 alpha1,/*[in]*/ Float64 beta1,/*[in]*/ Float64 Mn,/*[in]*/ Float64 c,/*[in]*/ IDblArray* fs,/*[in]*/ IDblArray* fps,/*[in]*/ Float64 Cflange,/*[in]*/ Float64 Cweb,/*[in]*/ Float64 T,/*[in]*/ Float64 Yflange,/*[in]*/ Float64 Yweb) override;
   STDMETHOD(get_Alpha1)(/*[out,retval]*/Float64* pAlpha1) override;
   STDMETHOD(get_Beta1)(/*[out,retval]*/Float64* pBeta1) override;
};
