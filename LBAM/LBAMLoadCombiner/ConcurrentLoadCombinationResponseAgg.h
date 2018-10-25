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

// ConcurrentLoadCombinationResponseAgg.h : Declaration of the CConcurrentLoadCombinationResponseAgg

#ifndef __CONCURRENTLOADCOMBINATIONRESPONSEAGG_H_
#define __CONCURRENTLOADCOMBINATIONRESPONSEAGG_H_

#include "resource.h"       // main symbols
#include "LoadCombiner.h"

/////////////////////////////////////////////////////////////////////////////
// CConcurrentLoadCombinationResponseAgg
class ATL_NO_VTABLE CConcurrentLoadCombinationResponseAgg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfo,
	public IConcurrentLoadCombinationResponse
{
public:
   friend CLoadCombiner;

	CConcurrentLoadCombinationResponseAgg()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CConcurrentLoadCombinationResponseAgg)
	COM_INTERFACE_ENTRY(IConcurrentLoadCombinationResponse)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IConcurrentLoadCombinationResponseAgg
public:
	STDMETHOD(ComputeForces)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage, /*[in]*/ResultsOrientation orientation, /*[in]*/ILoadCombinationResultConfiguration* config, /*[out,retval]*/ISectionResult3Ds* *results);
	STDMETHOD(ComputeDeflections)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage, /*[in]*/ILoadCombinationResultConfiguration* config, /*[out,retval]*/ISectionResult3Ds* *results);
	STDMETHOD(ComputeReactions)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage, /*[in]*/ILoadCombinationResultConfiguration* config, /*[out,retval]*/IResult3Ds* *results);
	STDMETHOD(ComputeSupportDeflections)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage, /*[in]*/ILoadCombinationResultConfiguration* config, /*[out,retval]*/IResult3Ds* *results);
	STDMETHOD(ComputeStresses)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage, /*[in]*/ILoadCombinationResultConfiguration* config, /*[out,retval]*/ISectionStressResults* *results);

private:
   // internal implementation
   CLoadCombiner*  m_pCombiner;
};

#endif //__ConcurrentLoadCombinationResponseAgg_H_
