///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2015  Washington State Department of Transportation
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

// StressResult.h : Declaration of the CStressResult

#ifndef __STRESSRESULT_H_
#define __STRESSRESULT_H_

#include "resource.h"       // main symbols
#include <vector>
#include "HpStressResult.h"
#include "LBAMUtils.h"

/////////////////////////////////////////////////////////////////////////////
// CStressResult
class ATL_NO_VTABLE CStressResult : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStressResult, &CLSID_StressResult>,
	public ISupportErrorInfo,
	public IStressResult,
   public IHpStressResult,
   public IPersistImpl<CStressResult>,
   public IObjectSafetyImpl<CStressResult,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2
{
public:
	CStressResult()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STRESSRESULT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStressResult)
	COM_INTERFACE_ENTRY(IStressResult)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY_IID(IID_IHpStressResult, IHpStressResult)
	COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

// IStressResult
	STDMETHOD(get_Count)(/*[out,retval]*/ CollectionIndexType *pVal);
	STDMETHOD(AddResult)(/*[in]*/ Float64 newVal);
	STDMETHOD(SetResult)(/*[in]*/CollectionIndexType index, /*[in]*/ Float64 newVal);
	STDMETHOD(GetResult)(/*[in]*/CollectionIndexType index, /*[out,retval]*/ Float64 *pVal);
	STDMETHOD(Clone)(/*[out,retval]*/ IStressResult* *pClone);

// IHpStressResult
	STDMETHOD(HpSumResults)(/*[in]*/CollectionIndexType num, /*[in]*/Float64* Vals);
	STDMETHOD(HpSetResults)(/*[in]*/CollectionIndexType num, /*[in]*/Float64* Vals);

public:
	STDMETHOD(FactorAndSum)(IStressResult* incRes, Float64 factor);
   typedef std::vector<Float64> Float64Vec;
   typedef Float64Vec::iterator Float64Iterator;
   Float64Vec m_Results;
};

#endif //__STRESSRESULT_H_
