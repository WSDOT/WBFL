///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2010  Washington State Department of Transportation
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

// CrackedSectionSolution.h : Declaration of the CCrackedSectionSolution

#ifndef __CrackedSectionSolution_H_
#define __CrackedSectionSolution_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CCrackedSectionSolution
class ATL_NO_VTABLE CCrackedSectionSolution : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCrackedSectionSolution, &CLSID_CrackedSectionSolution>,
	public ISupportErrorInfo,
	public ICrackedSectionSolution
{
public:
	CCrackedSectionSolution()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_CRACKEDSECTIONSOLUTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCrackedSectionSolution)
	COM_INTERFACE_ENTRY(ICrackedSectionSolution)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


private:
   CComPtr<IPoint2d> m_pntCG;
   CComPtr<IUnkArray> m_Slices;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ICrackedSectionSolution
public:
   STDMETHOD(InitSolution)(/*[in]*/IPoint2d* pntCG,/*[in]*/IUnkArray* slices) override;
   STDMETHOD(get_CG)(/*[out,retval]*/IPoint2d** pntCG) override;
   STDMETHOD(get_SliceCount)(/*[out,retval]*/CollectionIndexType* nSlices) override;
	STDMETHOD(get_Slice)(/*[in]*/ CollectionIndexType sliceIdx,/*[out,retval]*/ICrackedSectionSlice** pSlice) override;
   STDMETHOD(get_ElasticProperties)(/*[out,retval]*/IElasticProperties** ppProps) override;
};

#endif //__CrackedSectionSolution_H_
