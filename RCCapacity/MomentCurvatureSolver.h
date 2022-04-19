///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

// MomentCurvatureSolver.h : Declaration of the CMomentCurvatureSolver

#ifndef __MomentCurvatureSolver_H_
#define __MomentCurvatureSolver_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>
#include <vector>

class CMomentCurvatureSolution;

/////////////////////////////////////////////////////////////////////////////
// CMomentCurvatureSolver
class ATL_NO_VTABLE CMomentCurvatureSolver : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMomentCurvatureSolver, &CLSID_MomentCurvatureSolver>,
	public ISupportErrorInfo,
	public IMomentCurvatureSolver
{
public:
	CMomentCurvatureSolver()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_MOMENTCURVATURESOLVER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMomentCurvatureSolver)
	COM_INTERFACE_ENTRY(IMomentCurvatureSolver)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


private:
   Float64 m_kInitialStep;
   CComPtr<IMomentCapacitySolver>   m_CapacitySolver;

   Float64 GetCurvatureIncrement(Uint32 nFail);
   HRESULT AnalyzeSection(Float64 Fz,Float64 angle,Float64 k,CMomentCurvatureSolution* solution);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IMomentCurvatureSolver
public:
   STDMETHOD(putref_Section)(/*[in]*/IGeneralSection* pSection) override;
	STDMETHOD(get_Section)(/*[out,retval]*/IGeneralSection** pSection) override;
   STDMETHOD(put_Slices)(/*[in]*/long nSlices) override;
	STDMETHOD(get_Slices)(/*[out,retval]*/long* nSlices) override;
   STDMETHOD(put_SliceGrowthFactor)(/*[in]*/Float64 sliceGrowthFactor) override;
   STDMETHOD(get_SliceGrowthFactor)(/*[out,retval]*/Float64* sliceGrowthFactor) override;
   STDMETHOD(put_AxialTolerance)(/*[in]*/Float64 tolerance) override;
	STDMETHOD(get_AxialTolerance)(/*[out,retval]*/Float64* tolerance) override;
	STDMETHOD(put_MaxIterations)(/*[in]*/long maxIter) override;
	STDMETHOD(get_MaxIterations)(/*[out,retval]*/long* maxIter) override;
   STDMETHOD(put_InitialCurvatureStep)(/*[in]*/Float64 k) override;
	STDMETHOD(get_InitialCurvatureStep)(/*[out,retval]*/Float64* k) override;
   STDMETHOD(Solve)(/*[in]*/ Float64 Fz,/*[in]*/ Float64 angle,/*[out,retval]*/IMomentCurvatureSolution** solution) override;
};

#endif //__MomentCurvatureSolver_H_
