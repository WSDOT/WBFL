///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2021  Washington State Department of Transportation
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

// LoadCombinationSectionResults.h : Declaration of the CLoadCombinationSectionResults

#ifndef __LoadCombinationSectionResults_H_
#define __LoadCombinationSectionResults_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CLoadCombinationSectionResults
class ATL_NO_VTABLE CLoadCombinationSectionResults : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLoadCombinationSectionResults, &CLSID_LoadCombinationSectionResults>,
	public ISupportErrorInfo,
	public ILoadCombinationSectionResults,
   public IPersistImpl<CLoadCombinationSectionResults>,
   public IObjectSafetyImpl<CLoadCombinationSectionResults,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2
{
public:
	CLoadCombinationSectionResults()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOADCOMBINATIONSECTIONRESULTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCombinationSectionResults)
	COM_INTERFACE_ENTRY(ILoadCombinationSectionResults)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// ILoadCombinationSectionResults
public:
	STDMETHOD(GetResult)(/*[in]*/CollectionIndexType index, /*[out]*/Float64* leftResult, /*[out]*/ILoadCombinationResultConfiguration** leftConfig, /*[out]*/Float64* rightResult, /*[out]*/ILoadCombinationResultConfiguration** rightConfig) override;
	STDMETHOD(SetResult)(/*[in]*/CollectionIndexType index, /*[in]*/Float64 leftResult, /*[in]*/ILoadCombinationResultConfiguration* leftConfig, /*[in]*/Float64 rightResult, /*[in]*/ILoadCombinationResultConfiguration* rightConfig) override;
	STDMETHOD(Add)(/*[in]*/Float64 leftResult, /*[in]*/ILoadCombinationResultConfiguration* leftConfig, /*[in]*/Float64 rightResult, /*[in]*/ILoadCombinationResultConfiguration* rightConfig) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(Reserve)(/*[in]*/CollectionIndexType size) override;
	STDMETHOD(Clear)() override;

// functions available to non-com pals
public:
   HRESULT AllocateResults(CollectionIndexType size, bool createConfig, ResultsSummationType summ);
   HRESULT SumResultNoConfig(CollectionIndexType index, Float64 leftResult, Float64 rightResult);
	HRESULT SumResult(CollectionIndexType index, BSTR loadCase, Float64 leftResult, Float64 leftFactor, Float64 rightResult, Float64 rightFactor);
	HRESULT SumLLResult(CollectionIndexType index, Float64 leftResult, ILiveLoadConfiguration* leftConfig, Float64 rightResult, ILiveLoadConfiguration* rightConfig, Float64 Factor);

private:
   struct ComboRes
   {
      ComboRes()
      {;}
      ComboRes(Float64 leftResult, Float64 rightResult, ILoadCombinationResultConfiguration* leftConfig, ILoadCombinationResultConfiguration* rightConfig):
      m_LeftResult(leftResult),
      m_RightResult(rightResult),
      m_LeftConfig(leftConfig),
      m_RightConfig(rightConfig)
      {;}

      Float64                                       m_LeftResult;
      Float64                                       m_RightResult;
      CComPtr<ILoadCombinationResultConfiguration> m_LeftConfig;
      CComPtr<ILoadCombinationResultConfiguration> m_RightConfig;
   };

   typedef std::vector<ComboRes>  ComboResList;
   typedef ComboResList::iterator ComboResIterator;

   ComboResList m_ComboResults;
};

#endif //__LoadCombinationSectionResults_H_
