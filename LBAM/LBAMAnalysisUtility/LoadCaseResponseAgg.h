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

// LoadCaseResponseAgg.h : Declaration of the CLoadCaseResponseAgg

#ifndef __LoadCaseResponseAGG_H_
#define __LoadCaseResponseAGG_H_

#include "resource.h"       // main symbols
#include "LBAMModelEnveloper.h"

/////////////////////////////////////////////////////////////////////////////
// CLoadCaseResponseAgg
class ATL_NO_VTABLE CLoadCaseResponseAgg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfo,
	public ILoadCaseResponse
{
public:
   friend CLBAMModelEnveloper;

	CLoadCaseResponseAgg()
	{
      m_Optimization = optMaximize;
      m_ForceEffect  = fetMz;
	}

	~CLoadCaseResponseAgg()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCaseResponseAgg)
	COM_INTERFACE_ENTRY(ILoadCaseResponse)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadCaseResponseAgg)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILoadCaseResponse
public:
// ILoadCaseResponse
public:
	STDMETHOD(ComputeForces)(/*[in]*/BSTR LoadCase, /*[in]*/ILongArray* POIs, /*[in]*/BSTR Stage, /*[in]*/ResultsOrientation orientation, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionResult3Ds** results);
	STDMETHOD(ComputeDeflections)(/*[in]*/BSTR LoadCase, /*[in]*/ILongArray* POIs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionResult3Ds** results);
	STDMETHOD(ComputeReactions)(/*[in]*/BSTR LoadCase, /*[in]*/ILongArray* POIs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/IResult3Ds** results);
	STDMETHOD(ComputeSupportDeflections)(/*[in]*/BSTR LoadCase, /*[in]*/ILongArray* POIs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/IResult3Ds** results);
	STDMETHOD(ComputeStresses)(/*[in]*/BSTR LoadCase, /*[in]*/ILongArray* POIs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionStressResults** results);

private:
   // internal implementation
   void EnvelopeLoadCaseResults(IResult3Ds* res1, IResult3Ds* res2);
   void EnvelopeLoadCaseSectionResults(ISectionResult3Ds* res1, ISectionResult3Ds* res2,bool doFlip,long EngineNo);
   void EnvelopeLoadCaseSectionStressResults(ISectionStressResults* res1, ISectionStressResults* res2);


   OptimizationType m_Optimization;
   ForceEffectType m_ForceEffect;

   CLBAMModelEnveloper*  m_pEnveloper;

   // vector containing engine number of controlling result for left and right sections
   // this is used in order to determine the controlling model when computing stresses
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

};

#endif //__LoadCaseResponseAgg_H_
