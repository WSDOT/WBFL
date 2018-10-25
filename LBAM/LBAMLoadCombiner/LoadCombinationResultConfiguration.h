///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2017  Washington State Department of Transportation
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

// LoadCombinationResultConfiguration.h : Declaration of the CLoadCombinationResultConfiguration

#ifndef __LOADCOMBINATIONRESULTCONFIGURATION_H_
#define __LOADCOMBINATIONRESULTCONFIGURATION_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CLoadCombinationResultConfiguration
class ATL_NO_VTABLE CLoadCombinationResultConfiguration : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLoadCombinationResultConfiguration, &CLSID_LoadCombinationResultConfiguration>,
	public ISupportErrorInfo,
	public ILoadCombinationResultConfiguration,
   public IPersistImpl<CLoadCombinationResultConfiguration>,
   public IObjectSafetyImpl<CLoadCombinationResultConfiguration,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2
{
public:
   CLoadCombinationResultConfiguration():
   m_LiveLoadFactor(0),
   m_ResultsSummationType(rsIncremental)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOADCOMBINATIONRESULTCONFIGURATION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCombinationResultConfiguration)
	COM_INTERFACE_ENTRY(ILoadCombinationResultConfiguration)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILoadCombinationResultConfiguration
public:
	STDMETHOD(get_SummationType)(/*[out, retval]*/ ResultsSummationType *pVal) override;
	STDMETHOD(put_SummationType)(/*[in]*/ ResultsSummationType newVal) override;
	STDMETHOD(GetLiveLoadConfigurationCount)(/*[out,retval]*/CollectionIndexType* count) override;
	STDMETHOD(GetLiveLoadConfiguration)(/*[in]*/CollectionIndexType index,/*[out,retval]*/ILiveLoadConfiguration* *Config) override;
	STDMETHOD(AddLiveLoadConfiguration)(/*[in]*/ILiveLoadConfiguration* Config) override;
	STDMETHOD(get_LiveLoadFactor)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_LiveLoadFactor)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(AddLoadCaseFactor)( /*[in]*/BSTR loadCase, /*[in]*/Float64 factor) override;
	STDMETHOD(GetLoadCaseFactor)(/*[in]*/CollectionIndexType index, /*[out]*/BSTR* loadCase, /*[out]*/Float64* factor) override;
	STDMETHOD(get_LoadCaseFactorCount)(/*[out, retval]*/ CollectionIndexType *pVal) override;

// IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

protected:
   struct LoadCaseFactor
   {
      LoadCaseFactor()
      {;}

      LoadCaseFactor(BSTR name, Float64 factor):
      m_LoadCaseName(name),
      m_Factor(factor)
      {;}

      CComBSTR  m_LoadCaseName;
      Float64    m_Factor;
   };

   typedef std::vector<LoadCaseFactor> LcfContainer;
   typedef LcfContainer::iterator       LcfIterator;
   LcfContainer m_LoadCaseFactors;

   Float64                           m_LiveLoadFactor;
   std::vector<CComPtr<ILiveLoadConfiguration> >  m_LLConfig;

   ResultsSummationType             m_ResultsSummationType;
};

#endif //__LOADCOMBINATIONRESULTCONFIGURATION_H_
