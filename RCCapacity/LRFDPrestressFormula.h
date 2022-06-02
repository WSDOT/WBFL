///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// LRFDPrestressFormula.h : Declaration of the CLRFDPrestressFormula

#ifndef __LRFDPrestressFormula_H_
#define __LRFDPrestressFormula_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>

// Computes stress in prestressing using LRFD Equation 5.7.3.1.1-1

/////////////////////////////////////////////////////////////////////////////
// CLRFDPrestressFormula
class ATL_NO_VTABLE CLRFDPrestressFormula : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLRFDPrestressFormula, &CLSID_LRFDPrestressFormula>,
	public ISupportErrorInfo,
   public ILRFDPrestressFormula,
	public IStressStrain,
   public IStructuredStorage2,
   public IPersist
{
public:
   CLRFDPrestressFormula() :
      m_bstrName("Strand")
	{
      m_ProductionMethod = pmtLowRelaxation;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_LRFDPRESTRESSFORMULA)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLRFDPrestressFormula)
   COM_INTERFACE_ENTRY(ILRFDPrestressFormula)
	COM_INTERFACE_ENTRY(IStressStrain)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

   void ClearUnits();
   void SetupUnits();

   ProductionMethodType m_ProductionMethod;

   Float64 m_Fpu;
   Float64 m_Eps;

   CComBSTR m_bstrName;

   Float64 m_MinStrain;
   Float64 m_MaxStrain;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILRFDPrestressFormula
public:
   STDMETHOD(put_Fpu)(/*[in]*/Float64 fpu) override;
   STDMETHOD(get_Fpu)(/*[out,retval]*/Float64* pFpu) override;
   STDMETHOD(put_Eps)(/*[in]*/Float64 Eps) override;
   STDMETHOD(get_ProductionMethod)(/*[out,retval]*/ProductionMethodType* type) override;
	STDMETHOD(put_ProductionMethod)(/*[in]*/ProductionMethodType type) override;

// IStressStrain
public:
   STDMETHOD(put_Name)(/*[in]*/BSTR name) override;
	STDMETHOD(get_Name)(/*[out,retval]*/BSTR *name) override;
   STDMETHOD(ComputeStress)(/*[in]*/ Float64 strain,/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(StrainLimits)(/*[out]*/Float64* minStrain,/*[out]*/Float64* maxStrain) override;
   STDMETHOD(get_YieldStrain)(/*[out,retval]*/Float64* pey) override;
   STDMETHOD(get_ModulusOfElasticity)(/*[out,retval]*/Float64* pE) override;
   STDMETHOD(get_StrainAtPeakStress)(/*[out,retval]*/Float64* strain) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID) override;
};

#endif //__LRFDPrestressFormula_H_
