///////////////////////////////////////////////////////////////////////
// LBAM Analysis Utility - Longitindal Bridge Analysis Model
// Copyright © 1999-2013  Washington State Department of Transportation
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

// LiveLoadResponseAgg.h : Declaration of the CLiveLoadResponseAgg

#ifndef __LiveLoadResponseAgg_H_
#define __LiveLoadResponseAgg_H_

#include "resource.h"       // main symbols
#include "LBAMModelEnveloper.h"

/////////////////////////////////////////////////////////////////////////////
// CLiveLoadResponseAgg
class ATL_NO_VTABLE CLiveLoadResponseAgg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfo,
	public ILiveLoadModelResponse
{
public:
   friend CLBAMModelEnveloper;

	CLiveLoadResponseAgg()
	{
	}

	~CLiveLoadResponseAgg()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLiveLoadResponseAgg)
	COM_INTERFACE_ENTRY(ILiveLoadModelResponse)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLiveLoadResponseAgg)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILiveLoadModelResponse
public:
	STDMETHOD(ComputeForces)( /*[in]*/IIDArray* pois, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                             /*[in]*/ResultsOrientation orientation, /*[in]*/ForceEffectType effect, 
                             /*[in]*/OptimizationType optimization, 
                             /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                             /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                             /*[in]*/VARIANT_BOOL computePlacement, /*[out,retval]*/ILiveLoadModelSectionResults** results);

	STDMETHOD(ComputeDeflections)( /*[in]*/IIDArray* pois, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                             /*[in]*/ForceEffectType effect, 
                             /*[in]*/OptimizationType optimization, 
                             /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                             /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                             /*[in]*/VARIANT_BOOL computePlacement, /*[out,retval]*/ILiveLoadModelSectionResults** results);

	STDMETHOD(ComputeReactions)( /*[in]*/IIDArray* supports, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                                /*[in]*/ForceEffectType effect, 
                                /*[in]*/OptimizationType optimization, 
                                /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                                /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                                /*[in]*/VARIANT_BOOL computePlacement, /*[out,retval]*/ILiveLoadModelResults** results);

	STDMETHOD(ComputeSupportDeflections)( /*[in]*/IIDArray* supports, /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                                         /*[in]*/ForceEffectType effect, 
                                         /*[in]*/OptimizationType optimization, 
                                         /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                                         /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                                         /*[in]*/VARIANT_BOOL computePlacement, /*[out,retval]*/ILiveLoadModelResults** results);

	STDMETHOD(ComputeStresses)( /*[in]*/IIDArray* pois , /*[in]*/BSTR stage, /*[in]*/LiveLoadModelType type, 
                               /*[in]*/ForceEffectType effect, /*[in]*/OptimizationType optimization, 
                               /*[in]*/VehicularLoadConfigurationType vehConfiguration, 
                               /*[in]*/VARIANT_BOOL applyImpact, /*[in]*/VARIANT_BOOL applyDistribution,
                               /*[in]*/VARIANT_BOOL computePlacement, /*[out,retval]*/ILiveLoadModelStressResults** results);
private:
   // internal implementation
   void EnvelopeLiveLoadResults(ILiveLoadModelResults* res1, ILiveLoadModelResults* res2,
                                       VARIANT_BOOL computeConfig, OptimizationType optimization);

   void EnvelopeLiveLoadSectionResults(ILiveLoadModelSectionResults* res1, ILiveLoadModelSectionResults* res2,
                                           VARIANT_BOOL computeConfig, OptimizationType optimization, bool doFlip, CollectionIndexType engineIdx);


   CLBAMModelEnveloper*  m_pEnveloper;

   // vector containing engine number of controlling result for left and right sections
   // this is used in order to determine the controlling model when computing stresses
   struct LRPair
   {
      CollectionIndexType Left;
      CollectionIndexType Right;

      LRPair():
      Left(0),
      Right(0)
      {;}
   };

   std::vector<LRPair> m_ControllingEngine;

};

#endif //__LiveLoadResponseAgg_H_
