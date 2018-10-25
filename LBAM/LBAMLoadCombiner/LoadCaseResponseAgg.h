///////////////////////////////////////////////////////////////////////
// LBAM Load Combiner - Longitindal Bridge Analysis Model
// Copyright © 1999-2017  Washington State Department of Transportation
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

// LoadCaseResponseAgg.h : Declaration of the CLoadCaseResponseAgg

#ifndef __LoadCaseResponseAGG_H_
#define __LoadCaseResponseAGG_H_

#include "resource.h"       // main symbols
#include "LoadCombiner.h"

class CLoadCombiner;
/////////////////////////////////////////////////////////////////////////////
// CLoadCaseResponseAgg
class ATL_NO_VTABLE CLoadCaseResponseAgg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISupportErrorInfo,
	public ILoadCaseResponse
{
public:
   friend CLoadCombiner;

   CLoadCaseResponseAgg()
	{
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
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILoadCaseResponse
public:
	STDMETHOD(ComputeForces)(/*[in]*/BSTR LoadCase, /*[in]*/IIDArray* POIs, /*[in]*/BSTR Stage, /*[in]*/ResultsOrientation orientation, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionResult3Ds** results) override;
	STDMETHOD(ComputeDeflections)(/*[in]*/BSTR LoadCase, /*[in]*/IIDArray* POIs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionResult3Ds** results) override;
	STDMETHOD(ComputeReactions)(/*[in]*/BSTR LoadCase, /*[in]*/IIDArray* POIs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/IResult3Ds** results) override;
	STDMETHOD(ComputeSupportDeflections)(/*[in]*/BSTR LoadCase, /*[in]*/IIDArray* POIs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/IResult3Ds** results) override;
	STDMETHOD(ComputeStresses)(/*[in]*/BSTR LoadCase, /*[in]*/IIDArray* POIs, /*[in]*/BSTR Stage, /*[in]*/ResultsSummationType summ, /*[out,retval]*/ISectionStressResults** results) override;

private:
   // internal implementation
   CLoadCombiner*  m_pCombiner;


};

#endif //__LoadCaseResponseAgg_H_
