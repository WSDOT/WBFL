///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2011  Washington State Department of Transportation
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

// LoadCombiner.h : Declaration of the CLoadCombiner

#ifndef __LOADCOMBINER_H_
#define __LOADCOMBINER_H_

#include "resource.h"       // main symbols

#include <vector>
#include <map>

class CLoadCaseResponseAgg;
class CLoadCombinationResponseAgg;
class CConcurrentLoadCombinationResponseAgg;

// handle dealing with cancel from progress monitor
#define CMB_HANDLE_CANCEL_PROGRESS() if (m_pCombiner->CheckForCancel()) throw S_FALSE;

/////////////////////////////////////////////////////////////////////////////
// CLoadCombiner
class ATL_NO_VTABLE CLoadCombiner : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CLoadCombiner,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CLoadCombiner, &CLSID_LoadCombiner>,
	public ISupportErrorInfo,
	public IGetActiveLoadCases,
	public IDependOnLoadCombinationAnalysisContext,
	public ILoadCombinationAnalysisContextEvents,
   public IObjectSafetyImpl<CLoadCombiner,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportProgressMonitor
{
public:
   // our aggregates know us well
   friend CLoadCaseResponseAgg;
   friend CLoadCombinationResponseAgg;
   friend CConcurrentLoadCombinationResponseAgg;

   CLoadCombiner():
   m_ContextCookie(0),
   m_ProgressCookie(0),
   m_IsValidated(false)
	{
	}

   ~CLoadCombiner()
	{
	}


DECLARE_REGISTRY_RESOURCEID(IDR_LOADCOMBINER)

DECLARE_PROTECT_FINAL_CONSTRUCT()
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CLoadCombiner)
	COM_INTERFACE_ENTRY(IDependOnLoadCombinationAnalysisContext)
   COM_INTERFACE_ENTRY(ILoadCombinationAnalysisContextEvents)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_AGGREGATE(IID_ILoadCaseResponse, m_pLoadCaseResponseAgg.p)
   COM_INTERFACE_ENTRY_AGGREGATE(IID_ILoadCombinationResponse, m_pLoadCombinationResponseAgg.p)
   COM_INTERFACE_ENTRY_AGGREGATE(IID_IConcurrentLoadCombinationResponse, m_pConcurrentLoadCombinationResponseAgg.p)
   COM_INTERFACE_ENTRY(ISupportProgressMonitor)
   COM_INTERFACE_ENTRY(IGetActiveLoadCases)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

   void FinalRelease();
   HRESULT FinalConstruct();


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


// IDependOnLoadCombinationAnalysisContext
	STDMETHOD(Initialize)(/*[in]*/IUnknown* context);

// ILoadCombinationAnalysisContextEvents 
   STDMETHOD(OnCombinationChanged)(/*[in]*/ComboType ctype, /*[in]*/ BSTR combination);
   STDMETHOD(OnResultsChanged)();

// ISupportProgressMonitor
	STDMETHOD(InitializeProgressMonitor)(IProgressMonitor * newVal, LONG cookie);

// IGetActiveLoadCases
	STDMETHOD(GetActiveLoadCases)(/*[out,retval]*/IBstrArray* *loadCases);

private:
   void AssertValid();

   CComPtr<IUnknown>                        m_Context;
   DWORD                                    m_ContextCookie;

   // progress monitoring
   bool CheckForCancel()
   {
      if (m_pProgressMonitor)
      {
         VARIANT_BOOL cncl = VARIANT_FALSE;
         HRESULT hr = m_pProgressMonitor->get_WasCancelled(&cncl);
         ATLASSERT(SUCCEEDED(hr));
         return cncl!=VARIANT_FALSE;
      }
      else
         return false;
   }

   CComPtr<IProgressMonitor>                m_pProgressMonitor;
   long                                     m_ProgressCookie;

   // cache some interfaces so we don't have to QI the context each time to get them
   CComPtr<ILoadGroupResponse>       m_pLoadGroupResponse;
   CComPtr<ILiveLoadModelResponse>   m_pLiveLoadModelResponse;
   CComPtr<IBasicVehicularResponse>  m_pBasicVehicularResponse;
   CComPtr<IGetCombinationFactors>   m_pGetCombinationFactors;
   CComPtr<IGetStressPoints>         m_pGetStressPoints;

   // our aggregates
   CComPtr<IUnknown>                 m_pLoadCaseResponseAgg;
   CComPtr<IUnknown>                 m_pLoadCombinationResponseAgg;
   CComPtr<IUnknown>                 m_pConcurrentLoadCombinationResponseAgg;

   // keep around a QI'd pointer to our aggregate for performance
   ILoadCaseResponse*                  m_pLoadCaseResponse;
   IConcurrentLoadCombinationResponse* m_pConcurrentLoadCombinationResponse;

   // get stress points in a predictable manner
   HRESULT GetStressPoints(long poiID, BSTR stage, IStressPoints* *leftSps, IStressPoints* *rightSps);

   // For performance, we cache the active loadgroups in each loadcase
   // and only those loadcases and factors that are active for each loadcombination.
   void Invalidate();
   void Validate();
   void ValidateLoadCases();
   void ValidateLoadCombinations();
   bool m_IsValidated;

   // cache of ACTIVE load group names for each defined loadcase
   typedef CAdapt<CComBSTR> NameHolder;
   typedef std::vector< CComBSTR > NameVec;
   typedef std::map< NameHolder, NameVec> LoadCaseList;
   typedef LoadCaseList::iterator      LoadCaseIterator;

   LoadCaseList  m_LoadCases;

   struct ComboData
   {
      Float64              m_LiveLoadFactor;
      std::vector<LiveLoadModelType> m_LiveLoadModels;

      LoadCombinationType m_LoadCombinationType;

      struct LoadCaseFactors
      {
         LoadCaseFactors(BSTR name, Float64 minFactor, Float64 maxFactor):
         m_LoadCaseName(name),
         m_MinFactor(minFactor),
         m_MaxFactor(maxFactor)
         {;}

         CComBSTR m_LoadCaseName;
         Float64   m_MinFactor;
         Float64   m_MaxFactor;
      };
      typedef std::vector<LoadCaseFactors> LoadCaseFactorVec;
      typedef LoadCaseFactorVec::iterator  LoadCaseFactorIterator;
      LoadCaseFactorVec m_LoadCaseFactors;
   };

   typedef std::map< NameHolder, ComboData > LoadCombinationList;
   typedef LoadCombinationList::iterator     LoadCombinationIterator;

   LoadCombinationList m_LoadCombinations;

};

#endif //__LOADCOMBINER_H_
