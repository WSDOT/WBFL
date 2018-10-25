///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2014  Washington State Department of Transportation
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

// ILiveLoadModelSectionResults.h : Declaration of the CLiveLoadModelSectionResults

#ifndef __ILiveLoadModelSectionResults_H_
#define __ILiveLoadModelSectionResults_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadModelSectionResults
class ATL_NO_VTABLE CLiveLoadModelSectionResults : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLiveLoadModelSectionResults, &CLSID_LiveLoadModelSectionResults>,
	public ISupportErrorInfo,
	public ILiveLoadModelSectionResults,
   public IPersistImpl<CLiveLoadModelSectionResults>,
   public IObjectSafetyImpl<CLiveLoadModelSectionResults,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2
{
public:
	CLiveLoadModelSectionResults()
	{
	}

	~CLiveLoadModelSectionResults()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LIVELOADMODELSECTIONRESULTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLiveLoadModelSectionResults)
	COM_INTERFACE_ENTRY(ILiveLoadModelSectionResults)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

// IILiveLoadModelSectionResults
public:
	STDMETHOD(GetResult)(/*[in]*/CollectionIndexType index, /*[out]*/Float64* leftResult, /*[out]*/ILiveLoadConfiguration* *leftConfig, /*[out]*/Float64* rightResult, /*[out]*/ILiveLoadConfiguration* *rightConfig);
	STDMETHOD(SetResult)(/*[in]*/CollectionIndexType index, /*[in]*/Float64 leftResult, /*[in]*/ILiveLoadConfiguration* leftConfig, /*[in]*/Float64 rightResult, /*[in]*/ILiveLoadConfiguration* rightConfig);
	STDMETHOD(Add)(/*[in]*/Float64 leftResult, /*[in]*/ILiveLoadConfiguration* leftConfig, /*[in]*/Float64 rightResult, /*[in]*/ILiveLoadConfiguration* rightConfig);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(Reserve)(/*[in]*/CollectionIndexType size);
	STDMETHOD(Clear)();

private:
   struct LlmResults
   {
      LlmResults()
      {;}

      LlmResults(Float64 leftResult, ILiveLoadConfiguration* leftConfig,
         Float64 rightResult, ILiveLoadConfiguration* rightConfig):
      m_LeftResult(leftResult),
      m_LeftConfig(leftConfig),
      m_RightResult(rightResult),
      m_RightConfig(rightConfig)
      {;}

      ~LlmResults()
      {
      }

      Float64                           m_LeftResult;
      CComPtr<ILiveLoadConfiguration>  m_LeftConfig;
      Float64                           m_RightResult;
      CComPtr<ILiveLoadConfiguration>  m_RightConfig;
   };

   std::vector<LlmResults> m_Results;

};

#endif //__ILiveLoadModelSectionResults_H_
