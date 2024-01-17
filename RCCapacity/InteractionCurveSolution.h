///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// InteractionCurveSolution.h : Declaration of the CInteractionCurveSolution

#ifndef __InteractionCurveSolution_H_
#define __InteractionCurveSolution_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CInteractionCurveSolution
class ATL_NO_VTABLE CInteractionCurveSolution : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CInteractionCurveSolution, &CLSID_InteractionCurveSolution>,
	public ISupportErrorInfo,
	public IInteractionCurveSolution
{
public:
	CInteractionCurveSolution()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_INTERACTIONCURVESOLUTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CInteractionCurveSolution)
	COM_INTERFACE_ENTRY(IInteractionCurveSolution)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   struct CURVATUREINFO
   {
      Float64 NeutralAxis;
      CComPtr<IMomentCurvatureSolution> Curvature;

      bool operator<(const CURVATUREINFO& other) const { return NeutralAxis < other.NeutralAxis; }
   };

   std::vector<CURVATUREINFO> m_CurvatureInfo;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IInteractionCurveSolution
public:
   STDMETHOD(get_NeutralAxisDirection)(/*[in]*/IndexType index,/*[out,retval]*/Float64* angle) override;
	STDMETHOD(get_MomentCurvatureSolution)(/*[in]*/IndexType index,/*[out,retval]*/IMomentCurvatureSolution** solution) override;
	STDMETHOD(AddSolutionPoint)(/*[in]*/Float64 angle,/*[in]*/IMomentCurvatureSolution* solution) override;
	STDMETHOD(get_SolutionPointCount)(/*[out,retval]*/IndexType* nPoints) override;
};

#endif //__InteractionCurveSolution_H_
