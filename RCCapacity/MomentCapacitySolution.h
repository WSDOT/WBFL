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

// MomentCapacitySolution.h : Declaration of the CMomentCapacitySolution

#ifndef __MomentCapacitySolution_H_
#define __MomentCapacitySolution_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CMomentCapacitySolution
class ATL_NO_VTABLE CMomentCapacitySolution : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMomentCapacitySolution, &CLSID_MomentCapacitySolution>,
	public ISupportErrorInfo,
	public IMomentCapacitySolution
{
public:
	CMomentCapacitySolution()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_MOMENTCAPACITYSOLUTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMomentCapacitySolution)
	COM_INTERFACE_ENTRY(IMomentCapacitySolution)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   Float64 m_Fz;
   Float64 m_Mx;
   Float64 m_My;
   CComPtr<IPlane3d> m_StrainPlane;
   CComPtr<ILine2d> m_NeutralAxis;
   Float64 m_C;
   Float64 m_T;
   CComPtr<IPoint2d> m_cgC;
   CComPtr<IPoint2d> m_cgT;
   CComPtr<IGeneralSectionSolution> m_Solution;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IMomentCapacitySolution
public:
   STDMETHOD(InitSolution)(/*[in]*/Float64 fz,/*[in]*/Float64 mx,/*[in]*/Float64 my,/*[in]*/IPlane3d* strainPlane,/*[in]*/ILine2d* neutralAxis,/*[in]*/IPoint2d* cgC,/*[in]*/Float64 C,/*[in]*/IPoint2d* cgT,/*[in]*/Float64 T,/*[in]*/IGeneralSectionSolution* solution) override;
	STDMETHOD(get_Fz)(/*[out,retval]*/Float64* fz) override;
	STDMETHOD(get_Mx)(/*[out,retval]*/Float64* mx) override;
	STDMETHOD(get_My)(/*[out,retval]*/Float64* my) override;
   STDMETHOD(get_StrainPlane)(/*[out,retval]*/IPlane3d** strainPlane) override;
   STDMETHOD(get_NeutralAxis)(/*[out,retval]*/ILine2d** neutralAxis) override;
   STDMETHOD(get_NeutralAxisDirection)(/*[out,retval]*/Float64* angle) override;
   STDMETHOD(get_CompressionResultant)(/*[out,retval]*/Float64* c) override;
	STDMETHOD(get_TensionResultant)(/*[out,retval]*/Float64* t) override;
   STDMETHOD(get_CompressionResultantLocation)(/*[out,retval]*/IPoint2d** cgC) override;
   STDMETHOD(get_TensionResultantLocation)(/*[out,retval]*/IPoint2d** cgT) override;
   STDMETHOD(get_GeneralSectionSolution)(/*[out,retval]*/IGeneralSectionSolution** solution) override;
};

#endif //__MomentCapacitySolution_H_
