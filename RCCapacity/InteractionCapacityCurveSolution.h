///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
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

// InteractionCapacityCurveSolution.h : Declaration of the CInteractionCapacityCurveSolution

#ifndef __InteractionCapacityCurveSolution_H_
#define __InteractionCapacityCurveSolution_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CInteractionCapacityCurveSolution
class ATL_NO_VTABLE CInteractionCapacityCurveSolution : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CInteractionCapacityCurveSolution, &CLSID_InteractionCapacityCurveSolution>,
	public ISupportErrorInfo,
	public IInteractionCapacityCurveSolution
{
public:
	CInteractionCapacityCurveSolution()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_INTERACTIONCAPACITYCURVESOLUTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CInteractionCapacityCurveSolution)
	COM_INTERFACE_ENTRY(IInteractionCapacityCurveSolution)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   struct CAPACITYINFO
   {
      Float64 Fz;
      CComPtr<IMomentCapacitySolution> Capacity;

      bool operator<(const CAPACITYINFO& other) const { return Fz < other.Fz; }
   };

   std::vector<CAPACITYINFO> m_CapacityInfo;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IInteractionCapacityCurveSolution
public:
	STDMETHOD(get_MomentCapacitySolution)(/*[in]*/CollectionIndexType index,/*[out,retval]*/IMomentCapacitySolution** solution) override;
	STDMETHOD(AddSolutionPoint)(/*[in]*/IMomentCapacitySolution* solution) override;
	STDMETHOD(get_SolutionPointCount)(/*[out,retval]*/CollectionIndexType* nPoints) override;
};

#endif //__InteractionCapacityCurveSolution_H_
