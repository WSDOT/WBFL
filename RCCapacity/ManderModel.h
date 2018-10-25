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

// ManderModel.h : Declaration of the CManderModel

#ifndef __ManderModel_H_
#define __ManderModel_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>

/////////////////////////////////////////////////////////////////////////////
// CManderModel
class ATL_NO_VTABLE CManderModel : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CManderModel, &CLSID_ManderModel>,
	public ISupportErrorInfo,
	public IManderModel,
	public IStressStrain,
	public ISupportUnitServer
{
public:
   CManderModel() :
      m_bstrName("Confined Concrete")
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_MANDERMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CManderModel)
	COM_INTERFACE_ENTRY(IManderModel)
	COM_INTERFACE_ENTRY(IStressStrain)
   COM_INTERFACE_ENTRY(ISupportUnitServer)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

   Float64 m_Fco; // psi
   Float64 m_eco;
   Float64 m_R;
   CComPtr<IManderModelSection> m_Section;
   CComPtr<IUnitServer> m_UnitServer;
   CComBSTR m_bstrName;

   Float64 GetEc();
   void GetConcreteParameters(Float64& fr,Float64& fcc,Float64& ecc);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IManderModel
public:
   STDMETHOD(putref_Section)(/*[in]*/IManderModelSection* section) override;
	STDMETHOD(get_Section)(/*[out,retval]*/IManderModelSection** section) override;
	STDMETHOD(put_fco)(/*[in]*/Float64 fco) override;
	STDMETHOD(get_fco)(/*[out,retval]*/Float64* fco) override;
	STDMETHOD(put_eco)(/*[in]*/Float64 eco) override;
	STDMETHOD(get_eco)(/*[out,retval]*/Float64* eco) override;
	STDMETHOD(put_R)(/*[in]*/Float64 r) override;
	STDMETHOD(get_R)(/*[out,retval]*/Float64* r) override;
   STDMETHOD(GetConcreteParameters)(Float64* pfr, Float64* pfcc, Float64* pecc);

// IStressStrain
public:
   STDMETHOD(put_Name)(/*[in]*/BSTR name) override;
	STDMETHOD(get_Name)(/*[out,retval]*/BSTR *name) override;
   STDMETHOD(ComputeStress)(/*[in]*/ Float64 strain,/*[out,retval]*/Float64* pVal) override;
   STDMETHOD(StrainLimits)(/*[out]*/Float64* minStrain,/*[out]*/Float64* maxStrain) override;
   STDMETHOD(get_YieldStrain)(/*[out,retval]*/Float64* pey) override;
   STDMETHOD(get_ModulusOfElasticity)(/*[out,retval]*/Float64* pE) override;
   STDMETHOD(get_StrainAtPeakStress)(/*[out,retval]*/Float64* strain) override;

// ISupportUnitServer
public:
	STDMETHOD(get_UnitServer)(/*[out,retval]*/ IUnitServer** ppVal ) override;
	STDMETHOD(putref_UnitServer)(/*[in]*/ IUnitServer* pNewVal ) override;
};

#endif //__ManderModel_H_
