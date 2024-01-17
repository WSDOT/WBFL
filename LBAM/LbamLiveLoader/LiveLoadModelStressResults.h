///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2024  Washington State Department of Transportation
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

// LiveLoadModelStressResults.h : Declaration of the CLiveLoadModelStressResults

#ifndef __LIVELOADMODELSTRESSRESULTS_H_
#define __LIVELOADMODELSTRESSRESULTS_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadModelStressResults
class ATL_NO_VTABLE CLiveLoadModelStressResults : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLiveLoadModelStressResults, &CLSID_LiveLoadModelStressResults>,
	public ISupportErrorInfo,
	public ILiveLoadModelStressResults,
   public IPersistImpl<CLiveLoadModelStressResults>,
   public IObjectSafetyImpl<CLiveLoadModelStressResults,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2
{
public:
	CLiveLoadModelStressResults()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LIVELOADMODELSTRESSRESULTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLiveLoadModelStressResults)
	COM_INTERFACE_ENTRY(ILiveLoadModelStressResults)
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

// ILiveLoadModelStressResults
public:
	STDMETHOD(GetResult)(/*[in]*/IndexType index, /*[out]*/IStressResult* *leftResult, /*[out]*/ILiveLoadConfiguration* *leftConfig, /*[out]*/IStressResult* *rightResult, /*[out]*/ILiveLoadConfiguration* *rightConfig) override;
	STDMETHOD(SetResult)(/*[in]*/IndexType index, /*[in]*/IStressResult* leftResult, /*[in]*/ILiveLoadConfiguration* leftConfig, /*[in]*/IStressResult* rightResult, /*[in]*/ILiveLoadConfiguration* rightConfig) override;
	STDMETHOD(Add)(/*[in]*/IStressResult* leftResult, /*[in]*/ILiveLoadConfiguration* leftConfig, /*[in]*/IStressResult* rightResult, /*[in]*/ILiveLoadConfiguration* rightConfig) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ IndexType *pVal) override;
	STDMETHOD(Reserve)(/*[in]*/IndexType size) override;
	STDMETHOD(Clear)() override;

private:
   struct LlmResults
   {
      LlmResults()
      {;}

      LlmResults(IStressResult* leftResult, ILiveLoadConfiguration* leftConfig,
         IStressResult* rightResult, ILiveLoadConfiguration* rightConfig):
      m_LeftResult(leftResult),
      m_LeftConfig(leftConfig),
      m_RightResult(rightResult),
      m_RightConfig(rightConfig)
      {;}

      ~LlmResults()
      {
      }

      CComPtr<IStressResult>           m_LeftResult;
      CComPtr<ILiveLoadConfiguration>  m_LeftConfig;
      CComPtr<IStressResult>           m_RightResult;
      CComPtr<ILiveLoadConfiguration>  m_RightConfig;
   };

   std::vector<LlmResults> m_Results;

};

#endif //__LIVELOADMODELSTRESSRESULTS_H_
