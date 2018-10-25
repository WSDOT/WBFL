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

// LoadCombinationResults.h : Declaration of the CLoadCombinationResults

#ifndef __LOADCOMBINATIONRESULTS_H_
#define __LOADCOMBINATIONRESULTS_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CLoadCombinationResults
class ATL_NO_VTABLE CLoadCombinationResults : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLoadCombinationResults, &CLSID_LoadCombinationResults>,
	public ISupportErrorInfo,
	public ILoadCombinationResults,
   public IPersistImpl<CLoadCombinationResults>,
   public IObjectSafetyImpl<CLoadCombinationResults,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2
{
public:
	CLoadCombinationResults()
	{;}

	~CLoadCombinationResults()
	{;}

DECLARE_REGISTRY_RESOURCEID(IDR_LOADCOMBINATIONRESULTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCombinationResults)
	COM_INTERFACE_ENTRY(ILoadCombinationResults)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILoadCombinationResults
public:
	STDMETHOD(GetResult)(/*[in]*/CollectionIndexType index, /*[out]*/Float64* Result, /*[out]*/ILoadCombinationResultConfiguration** Config);
	STDMETHOD(SetResult)(/*[in]*/CollectionIndexType index, /*[in]*/Float64 Result, /*[in]*/ILoadCombinationResultConfiguration* Config);
	STDMETHOD(Add)(/*[in]*/Float64 Result, /*[in]*/ILoadCombinationResultConfiguration* Config);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(Reserve)(/*[in]*/CollectionIndexType size);
	STDMETHOD(Clear)();

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

// functions available to non-com pals
public:
   HRESULT AllocateResults(CollectionIndexType size, bool createConfig, ResultsSummationType summ);
   HRESULT SumResultNoConfig(CollectionIndexType index, Float64 Result);
	HRESULT SumResult(CollectionIndexType index, BSTR loadCase, Float64 Result, Float64 Factor);
	HRESULT SumLLResult(CollectionIndexType index, Float64 Result, ILiveLoadConfiguration* Config, Float64 Factor);

private:
   struct ComboRes
   {
      ComboRes()
      {;}
      ComboRes(Float64 Result, ILoadCombinationResultConfiguration* Config):
      m_Result(Result),
      m_Config(Config)
      {;}

      Float64                                       m_Result;
      CComPtr<ILoadCombinationResultConfiguration> m_Config;
   };

   typedef std::vector<ComboRes>  ComboResList;
   typedef ComboResList::iterator ComboResIterator;

   ComboResList m_ComboResults;
};

#endif //__LOADCOMBINATIONRESULTS_H_
