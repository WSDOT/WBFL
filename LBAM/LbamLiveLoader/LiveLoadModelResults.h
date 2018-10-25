///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2012  Washington State Department of Transportation
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

// LiveLoadModelResults.h : Declaration of the CLiveLoadModelResults

#ifndef __LIVELOADMODELRESULTS_H_
#define __LIVELOADMODELRESULTS_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadModelResults
class ATL_NO_VTABLE CLiveLoadModelResults : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLiveLoadModelResults, &CLSID_LiveLoadModelResults>,
	public ISupportErrorInfo,
	public ILiveLoadModelResults,
   public IPersistImpl<CLiveLoadModelResults>,
   public IObjectSafetyImpl<CLiveLoadModelResults,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2
{
public:
	CLiveLoadModelResults()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LIVELOADMODELRESULTS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLiveLoadModelResults)
	COM_INTERFACE_ENTRY(ILiveLoadModelResults)
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

// ILiveLoadModelResults
public:
	STDMETHOD(GetResult)(/*[in]*/CollectionIndexType index, /*[out]*/Float64* result, /*[out]*/ILiveLoadConfiguration* *Config);
	STDMETHOD(SetResult)(/*[in]*/CollectionIndexType index, /*[in]*/Float64 result, /*[in]*/ILiveLoadConfiguration* Config);
	STDMETHOD(Add)(/*[in]*/Float64 result, /*[in]*/ILiveLoadConfiguration* Config);
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(Reserve)(/*[in]*/CollectionIndexType size);
	STDMETHOD(Clear)();

private:
   struct LlmResults
   {
      LlmResults()
      {;}

      LlmResults(Float64 result, ILiveLoadConfiguration* config):
      m_Result(result),
      m_Config(config)
      {;}

      ~LlmResults()
      {
      }

      Float64                           m_Result;
      CComPtr<ILiveLoadConfiguration>  m_Config;
   };

   std::vector<LlmResults> m_Results;

};

#endif //__LIVELOADMODELRESULTS_H_
