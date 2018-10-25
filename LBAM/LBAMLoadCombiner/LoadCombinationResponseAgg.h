///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
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

// LoadCombinationResponseAgg.h : Declaration of the CLoadCombinationResponseAgg

#ifndef __LoadCombinationResponseAGG_H_
#define __LoadCombinationResponseAGG_H_

#include "resource.h"       // main symbols
#include "LoadCombiner.h"

class CLoadCombiner;
/////////////////////////////////////////////////////////////////////////////
// CLoadCombinationResponseAgg
class ATL_NO_VTABLE CLoadCombinationResponseAgg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfo,
	public ILoadCombinationResponse
{
public:
   friend CLoadCombiner;

	CLoadCombinationResponseAgg()
	{
	}

	~CLoadCombinationResponseAgg()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCombinationResponseAgg)
	COM_INTERFACE_ENTRY(ILoadCombinationResponse)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadCombinationResponseAgg)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILoadCombinationResponse
public:
   STDMETHOD(ComputeForces)(/*[in]*/BSTR LoadCombination, /*[in]*/IIDArray* POIs, /*[in]*/BSTR Stage, /*[in]*/ResultsOrientation orientation, 
                            /*[in]*/ResultsSummationType summ, /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization, 
                            /*[in]*/VARIANT_BOOL includeLiveLoad, /*[in]*/VARIANT_BOOL includeImpact, /*[in]*/VARIANT_BOOL computeConfig,
                            /*[out,retval]*/ILoadCombinationSectionResults** results);

   STDMETHOD(ComputeDeflections)(/*[in]*/BSTR LoadCombination, /*[in]*/IIDArray* POIs, /*[in]*/BSTR Stage,
                                 /*[in]*/ResultsSummationType summ, /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization, 
                                 /*[in]*/VARIANT_BOOL includeLiveLoad, /*[in]*/VARIANT_BOOL includeImpact, /*[in]*/VARIANT_BOOL computeConfig,
                                 /*[out,retval]*/ILoadCombinationSectionResults** results);

   STDMETHOD(ComputeReactions)(/*[in]*/BSTR LoadCombination, /*[in]*/IIDArray* POIs, /*[in]*/BSTR Stage,
                               /*[in]*/ResultsSummationType summ, /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization, 
                               /*[in]*/VARIANT_BOOL includeLiveLoad, /*[in]*/VARIANT_BOOL includeImpact, /*[in]*/VARIANT_BOOL computeConfig,
                               /*[out,retval]*/ILoadCombinationResults** results);

   STDMETHOD(ComputeSupportDeflections)(/*[in]*/BSTR LoadCombination, /*[in]*/IIDArray* POIs, /*[in]*/BSTR Stage,
                                        /*[in]*/ResultsSummationType summ, /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization, 
                                        /*[in]*/VARIANT_BOOL includeLiveLoad, /*[in]*/VARIANT_BOOL includeImpact, /*[in]*/VARIANT_BOOL computeConfig,
                                        /*[out,retval]*/ILoadCombinationResults** results);

   STDMETHOD(ComputeStresses)(/*[in]*/BSTR LoadCombination, /*[in]*/IIDArray* POIs, /*[in]*/BSTR Stage,
                              /*[in]*/ResultsSummationType summ, /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization, 
                              /*[in]*/VARIANT_BOOL includeLiveLoad, /*[in]*/VARIANT_BOOL includeImpact, /*[in]*/VARIANT_BOOL computeConfig,
                              /*[out,retval]*/ILoadCombinationStressResults** results);
private:
   // internal implementation
   CLoadCombiner*  m_pCombiner;
};

#endif //__LoadCombinationResponseAgg_H_
