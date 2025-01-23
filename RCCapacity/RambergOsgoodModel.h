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

// RambergOsgoodModel.h : Declaration of the CRambergOsgoodModel

#pragma once

#include "resource.h"       // main symbols
#include <Materials/RambergOsgoodModel.h>

/////////////////////////////////////////////////////////////////////////////
// CRambergOsgoodModel
class ATL_NO_VTABLE CRambergOsgoodModel :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRambergOsgoodModel, &CLSID_RambergOsgoodModel>,
	public ISupportErrorInfo,
   public IRambergOsgoodModel,
	public IStressStrain
{
public:
   CRambergOsgoodModel() :
      m_Model(_T("Strand"))
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_RAMBERGOSGOODMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRambergOsgoodModel)
   COM_INTERFACE_ENTRY(IRambergOsgoodModel)
	COM_INTERFACE_ENTRY(IStressStrain)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

   WBFL::Materials::RambergOsgoodModel m_Model;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IRambergOsgoodModel
public:
   STDMETHOD(Init)(Float64 A, Float64 B, Float64 C, Float64 Eps, Float64 fpu, Float64 minStrain, Float64 maxStrain) override;


// IStressStrain
public:
   STDMETHOD(put_Name)(/*[in]*/BSTR name) override;
	STDMETHOD(get_Name)(/*[out,retval]*/BSTR *name) override;
   STDMETHOD(ComputeStress)(/*[in]*/ Float64 strain,/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(StrainLimits)(/*[out]*/Float64* minStrain,/*[out]*/Float64* maxStrain) override;
   STDMETHOD(get_YieldStrain)(/*[out,retval]*/Float64* pey) override;
   STDMETHOD(get_ModulusOfElasticity)(/*[out,retval]*/Float64* pE) override;
   STDMETHOD(get_StrainAtPeakStress)(/*[out,retval]*/Float64* strain) override;
};

