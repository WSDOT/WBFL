///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TensionStressPlaneModel.h : Declaration of the CTensionStressPlaneModel

#include "resource.h"       // main symbols
#include "WBFLRCCapacity.h"

// {C76A3B9E-3743-4B8A-B6F9-F996DE29D8AC}
DEFINE_GUID(CLSID_TensionStressPlaneModel,
   0xc76a3b9e, 0x3743, 0x4b8a, 0xb6, 0xf9, 0xf9, 0x96, 0xde, 0x29, 0xd8, 0xac);

/////////////////////////////////////////////////////////////////////////////
// CTensionStressPlaneModel
class ATL_NO_VTABLE CTensionStressPlaneModel :
   public CComObjectRootEx<CComSingleThreadModel>,
   public CComCoClass<CTensionStressPlaneModel, &CLSID_TensionStressPlaneModel>,
   public ISupportErrorInfo,
   public IStressStrain
{
public:
   CTensionStressPlaneModel() :
      m_bstrName("Tension Stress Plane Model")
   {
   }

   //DECLARE_REGISTRY_RESOURCEID(IDR_STRAINHARDENEDREBARMODEL)

   DECLARE_PROTECT_FINAL_CONSTRUCT()

   BEGIN_COM_MAP(CTensionStressPlaneModel)
      COM_INTERFACE_ENTRY(IStressStrain)
      COM_INTERFACE_ENTRY(ISupportErrorInfo)
   END_COM_MAP()

   CComBSTR m_bstrName;

   // ISupportsErrorInfo
public:
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

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
