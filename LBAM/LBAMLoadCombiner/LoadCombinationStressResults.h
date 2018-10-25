///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright (C) 2009  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// LoadCombinationStressResults.h : Declaration of the CLoadCombinationStressResults

#ifndef __LOADCOMBINATIONSTRESSRESULTS_H_
#define __LOADCOMBINATIONSTRESSRESULTS_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CLoadCombinationStressResults
class ATL_NO_VTABLE CLoadCombinationStressResults : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLoadCombinationStressResults, &CLSID_LoadCombinationStressResults>,
	public ISupportErrorInfo,
	public ILoadCombinationStressResults,
   public IPersistImpl<CLoadCombinationStressResults>,
   public IObjectSafetyImpl<CLoadCombinationStressResults,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2
{
public:
	CLoadCombinationStressResults()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOADCOMBINATIONSTRESSRESULTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCombinationStressResults)
	COM_INTERFACE_ENTRY(ILoadCombinationStressResults)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILoadCombinationStressResults
public:
	STDMETHOD(GetResult)(/*[in]*/CollectionIndexType index, /*[out]*/IStressResult** leftResult, /*[out]*/ILoadCombinationResultConfiguration** leftConfig, /*[out]*/IStressResult** rightResult, /*[out]*/ILoadCombinationResultConfiguration** rightConfig);
	STDMETHOD(SetResult)(/*[in]*/CollectionIndexType index, /*[in]*/IStressResult* leftResult, /*[in]*/ILoadCombinationResultConfiguration* leftConfig, /*[in]*/IStressResult* rightResult, /*[in]*/ILoadCombinationResultConfiguration* rightConfig);
	STDMETHOD(Add)(/*[in]*/IStressResult* leftResult, /*[in]*/ILoadCombinationResultConfiguration* leftConfig, /*[in]*/IStressResult* rightResult, /*[in]*/ILoadCombinationResultConfiguration* rightConfig);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(Reserve)(/*[in]*/CollectionIndexType size);
	STDMETHOD(Clear)();

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

private:
   struct ComboRes
   {
      ComboRes()
      {;}
      ComboRes(IStressResult* leftResult, IStressResult* rightResult, ILoadCombinationResultConfiguration* leftConfig, ILoadCombinationResultConfiguration* rightConfig):
      m_LeftResult(leftResult),
      m_RightResult(rightResult),
      m_LeftConfig(leftConfig),
      m_RightConfig(rightConfig)
      {;}

      CComPtr<IStressResult>                       m_LeftResult;
      CComPtr<IStressResult>                       m_RightResult;
      CComPtr<ILoadCombinationResultConfiguration> m_LeftConfig;
      CComPtr<ILoadCombinationResultConfiguration> m_RightConfig;
   };

   typedef std::vector<ComboRes>  ComboResList;
   typedef ComboResList::iterator ComboResIterator;

   ComboResList m_ComboResults;
};

// LoadCombinationStressResults.h : Declaration of the CLoadCombinationStressResults

#endif //__LOADCOMBINATIONSTRESSRESULTS_H_
