///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// CapacityReductionFactor.h : Declaration of the CCapacityReductionFactor

#ifndef __CapacityReductionFactor_H_
#define __CapacityReductionFactor_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CCapacityReductionFactor
class ATL_NO_VTABLE CCapacityReductionFactor : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCapacityReductionFactor, &CLSID_CapacityReductionFactor>,
	public ISupportErrorInfo,
	public ICapacityReductionFactor
{
public:
	CCapacityReductionFactor()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_CAPACITYREDUCTIONFACTOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCapacityReductionFactor)
	COM_INTERFACE_ENTRY(ICapacityReductionFactor)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   HRESULT ComputeC(IUnkArray* pConcShapes,ILine2d* neutralAxis,Float64* c);
   HRESULT ComputeDt(IUnkArray* pReinfShapes,ILine2d* neutralAxis,Float64* c,Float64* dt);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICapacityReductionFactor
public:
   STDMETHOD(Compute)(/*[in]*/IGeneralSection* section,/*[in]*/IndexType nConcShapes,/*[in]*/ILine2d* neutralAxis,/*[in]*/Float64 ppr,/*[out]*/Float64* c,/*[out]*/Float64* dt,/*[out]*/Float64* phi) override;
	STDMETHOD(ComputeEx)(/*[in]*/IUnkArray* pConcShapes,/*[in]*/IUnkArray* pReinfShapes,/*[in]*/ILine2d* neutralAxis,/*[in]*/Float64 ppr,/*[out]*/Float64* c,/*[out]*/Float64* dt,/*[out]*/Float64* phi) override;
};

#endif //__CapacityReductionFactor_H_
