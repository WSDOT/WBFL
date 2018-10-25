///////////////////////////////////////////////////////////////////////
// LBAM Analysis Utility - Longitindal Bridge Analysis Model
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

// LoadCombinationResponseAgg.h : Declaration of the CLoadCombinationResponseAgg

#ifndef __LoadCombinationResponseAGG_H_
#define __LoadCombinationResponseAGG_H_

#include "resource.h"       // main symbols
#include "LBAMModelEnveloper.h"

/////////////////////////////////////////////////////////////////////////////
// CLoadCombinationResponseAgg
class ATL_NO_VTABLE CLoadCombinationResponseAgg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfo,
	public ILoadCombinationResponse,
   public IConcurrentLoadCombinationResponse
{
public:
   friend CLBAMModelEnveloper;

	CLoadCombinationResponseAgg()
	{
	}

	~CLoadCombinationResponseAgg()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCombinationResponseAgg)
	COM_INTERFACE_ENTRY(ILoadCombinationResponse)
   COM_INTERFACE_ENTRY(IConcurrentLoadCombinationResponse)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadCombinationResponseAgg)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILoadCombinationResponse
public:
   STDMETHOD(ComputeForces)(/*[in]*/BSTR LoadCombination, /*[in]*/ILongArray* POIs, /*[in]*/BSTR Stage, /*[in]*/ResultsOrientation orientation, 
                            /*[in]*/ResultsSummationType summ, /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization, 
                            /*[in]*/VARIANT_BOOL includeLiveLoad, /*[in]*/VARIANT_BOOL includeImpact, /*[in]*/VARIANT_BOOL computeConfig,
                            /*[out,retval]*/ILoadCombinationSectionResults** results);

   STDMETHOD(ComputeDeflections)(/*[in]*/BSTR LoadCombination, /*[in]*/ILongArray* POIs, /*[in]*/BSTR Stage,
                                 /*[in]*/ResultsSummationType summ, /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization, 
                                 /*[in]*/VARIANT_BOOL includeLiveLoad, /*[in]*/VARIANT_BOOL includeImpact, /*[in]*/VARIANT_BOOL computeConfig,
                                 /*[out,retval]*/ILoadCombinationSectionResults** results);

   STDMETHOD(ComputeReactions)(/*[in]*/BSTR LoadCombination, /*[in]*/ILongArray* POIs, /*[in]*/BSTR Stage,
                               /*[in]*/ResultsSummationType summ, /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization, 
                               /*[in]*/VARIANT_BOOL includeLiveLoad, /*[in]*/VARIANT_BOOL includeImpact, /*[in]*/VARIANT_BOOL computeConfig,
                               /*[out,retval]*/ILoadCombinationResults** results);

   STDMETHOD(ComputeSupportDeflections)(/*[in]*/BSTR LoadCombination, /*[in]*/ILongArray* POIs, /*[in]*/BSTR Stage,
                                        /*[in]*/ResultsSummationType summ, /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization, 
                                        /*[in]*/VARIANT_BOOL includeLiveLoad, /*[in]*/VARIANT_BOOL includeImpact, /*[in]*/VARIANT_BOOL computeConfig,
                                        /*[out,retval]*/ILoadCombinationResults** results);

   STDMETHOD(ComputeStresses)(/*[in]*/BSTR LoadCombination, /*[in]*/ILongArray* POIs, /*[in]*/BSTR Stage,
                              /*[in]*/ResultsSummationType summ, /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization, 
                              /*[in]*/VARIANT_BOOL includeLiveLoad, /*[in]*/VARIANT_BOOL includeImpact, /*[in]*/VARIANT_BOOL computeConfig,
                              /*[out,retval]*/ILoadCombinationStressResults** results);

// IConcurrentLoadCombinationResponse
public:
   STDMETHOD(ComputeForces)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage, /*[in]*/ResultsOrientation orientation, /*[in]*/ILoadCombinationResultConfiguration* config, /*[out,retval]*/ISectionResult3Ds* *results);
   STDMETHOD(ComputeDeflections)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage, /*[in]*/ILoadCombinationResultConfiguration* config, /*[out,retval]*/ISectionResult3Ds* *results);
   STDMETHOD(ComputeReactions)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage, /*[in]*/ILoadCombinationResultConfiguration* config, /*[out,retval]*/IResult3Ds* *results);
   STDMETHOD(ComputeSupportDeflections)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage, /*[in]*/ILoadCombinationResultConfiguration* config, /*[out,retval]*/IResult3Ds* *results);
   STDMETHOD(ComputeStresses)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage, /*[in]*/ILoadCombinationResultConfiguration* config, /*[out,retval]*/ISectionStressResults* *results);

private:
   // internal implementation
   void EnvelopeLoadCombinationResults(ILoadCombinationResults* res1, ILoadCombinationResults* res2,
                                       VARIANT_BOOL computeConfig, OptimizationType optimization,long engineID);

void EnvelopeLoadCombinationSectionResults(ILoadCombinationSectionResults* res1, ILoadCombinationSectionResults* res2,
                                           VARIANT_BOOL computeConfig, OptimizationType optimization, bool doFlip, long EngineNo);


   CLBAMModelEnveloper*  m_pEnveloper;

   // vector containing engine number of controlling result for left and right sections
   // this is used in order to determine the controlling model when computing stresses
   // and concurrent section results
   struct LRPair
   {
      long Left;
      long Right;

      LRPair():
      Left(0),
      Right(0)
      {;}
   };

   std::vector<LRPair> m_ControllingEngine;

   // engine id for controlling engine for reactions
   std::vector<long> m_ControllingEngineReactions;

};

#endif //__LoadCombinationResponseAgg_H_
