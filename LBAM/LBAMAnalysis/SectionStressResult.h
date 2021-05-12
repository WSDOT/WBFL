///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2021  Washington State Department of Transportation
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

// SectionStressResult.h : Declaration of the CSectionStressResult

#ifndef __SECTIONSTRESSRESULT_H_
#define __SECTIONSTRESSRESULT_H_

#include "resource.h"       // main symbols
#include <vector>
#include "HpStressResult.h"
#include "LBAMUtils.h"

/////////////////////////////////////////////////////////////////////////////
// CSectionStressResult
class ATL_NO_VTABLE CSectionStressResult : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSectionStressResult, &CLSID_SectionStressResult>,
	public ISupportErrorInfo,
	public ISectionStressResult,
   public IHpSectionStressResult,
   public IPersistImpl<CSectionStressResult>,
   public IObjectSafetyImpl<CSectionStressResult,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2

{
public:
	CSectionStressResult()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SECTIONSTRESSRESULT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSectionStressResult)
	COM_INTERFACE_ENTRY(ISectionStressResult)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY_IID(IID_IHpSectionStressResult, IHpSectionStressResult)
	COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// ISectionStressResult
	STDMETHOD(get_LeftCount)(/*[out,retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(AddLeftResult)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(SetLeftResult)(/*[in]*/CollectionIndexType index, /*[in]*/ Float64 newVal) override;
	STDMETHOD(GetLeftResult)(/*[in]*/CollectionIndexType index, /*[out,retval]*/ Float64 *pVal) override;
	STDMETHOD(get_RightCount)(/*[out,retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(AddRightResult)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(SetRightResult)(/*[in]*/CollectionIndexType index, /*[in]*/ Float64 newVal) override;
	STDMETHOD(GetRightResult)(/*[in]*/CollectionIndexType index, /*[out,retval]*/ Float64 *pVal) override;
	STDMETHOD(Clone)(/*[out,retval]*/ ISectionStressResult* *pClone) override;
	STDMETHOD(CreateLeftStressResult)(/*[out,retval]*/IStressResult* *result) override;
	STDMETHOD(CreateRightStressResult)(/*[out,retval]*/IStressResult* *result) override;
	STDMETHOD(FactorAndSum)(/*[in]*/ISectionStressResult* incRes, /*[in]*/Float64 leftFactor,/*[in]*/Float64 rightFactor) override;

// IHpStressResult
	STDMETHOD(HpSumResults)(/*[in]*/CollectionIndexType numLeft, /*[in]*/Float64* leftVals, /*[in]*/CollectionIndexType numRight, /*[in]*/Float64* rightVals) override;
	STDMETHOD(HpSetResults)(/*[in]*/CollectionIndexType numLeft, /*[in]*/Float64* leftVals, /*[in]*/CollectionIndexType numRight, /*[in]*/Float64* rightVals) override;

public:
   typedef std::vector<Float64> Float64Vec;
   typedef Float64Vec::iterator Float64Iterator;
   Float64Vec m_LeftResults;
   Float64Vec m_RightResults;
};

#endif //__SECTIONSTRESSRESULT_H_
