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

// MomentCapacitySolver.h : Declaration of the CMomentCapacitySolver

#ifndef __MomentCapacitySolver_H_
#define __MomentCapacitySolver_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CMomentCapacitySolver
class ATL_NO_VTABLE CMomentCapacitySolver : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMomentCapacitySolver, &CLSID_MomentCapacitySolver>,
	public ISupportErrorInfo,
	public IMomentCapacitySolver
{
public:
	CMomentCapacitySolver()
	{
      m_bAnalysisPointUpdated = false;
      m_bUpdateLimits = true;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_MOMENTCAPACITYSOLVER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMomentCapacitySolver)
	COM_INTERFACE_ENTRY(IMomentCapacitySolver)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


private:
   CComPtr<IGeneralSectionSolver> m_GeneralSolver;
   CComPtr<IGeneralSectionSolution> m_GeneralSolution;
   CComPtr<IGeneralSectionSolution> m_TensionSolution;
   CComPtr<IGeneralSectionSolution> m_CompressionSolution;
   CComPtr<IPlane3d> m_IncrementalStrainPlane;
   CComPtr<IPoint3d> m_P1, m_P2, m_P3;
   Float64 m_AxialTolerance;
   long m_MaxIter;
   bool m_bAnalysisPointUpdated;
   CComPtr<IPoint2d> m_ExtremeCompressionPoint; // this is compression side point furthest from the neutral axis
   CComPtr<IPoint2d> m_ExtremeTensionPoint; // this is the tension side point furthest from the neutral axis
   CComPtr<IPoint2d> m_ControlPoint; // this point is varied in the Z direction to manipulate the strain plane
   CComPtr<IPoint2d> m_FixedPoint; // this point is the fixed control point (like the point of -0.003 compression strain at the top of a section)

   bool m_bUpdateLimits;
   Float64 m_FzTensionLimit, m_MxTensionLimit, m_MyTensionLimit, m_eoTensionLimit;
   Float64 m_FzCompressionLimit, m_MxCompressionLimit, m_MyCompressionLimit, m_eoCompressionLimit;
   HRESULT UpdateLimits();

   void UpdateStrainPlane(Float64 angle,Float64 k_or_ec,Float64 strainLocation,SolutionMethod solutionMethod,Float64 eo);
   void UpdateAnalysisPoints(Float64 angle, SolutionMethod solutionMethod,Float64 strainLocation);
   void UpdateControlPoints(Float64 angle, SolutionMethod solutionMethod, Float64 strainLocation);
   HRESULT GetNeutralAxisParameterRange(Float64 k_or_ec,Float64 strainLocation,SolutionMethod solutionMethod,Float64 angle,Float64 Fz,Float64* peo_lower,Float64* peo_upper,Float64* pFz_lower,Float64* pFz_upper);
   HRESULT AnalyzeSection(Float64 Fz,Float64 angle,Float64 k_or_ec,SolutionMethod solutionMethod, Float64 strainLocation,IMomentCapacitySolution** solution);
   HRESULT ZeroCapacitySolution(IMomentCapacitySolution** solution);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IMomentCapacitySolver
public:
   STDMETHOD(put_AxialTolerance)(/*[in]*/Float64 tolerance) override;
   STDMETHOD(get_AxialTolerance)(/*[out,retval]*/Float64* tolerance) override;
   STDMETHOD(put_MaxIterations)(/*[in]*/long maxIter) override;
   STDMETHOD(get_MaxIterations)(/*[out,retval]*/long* maxIter) override;
   STDMETHOD(put_Slices)(/*[in]*/long nSlices) override;
	STDMETHOD(get_Slices)(/*[out,retval]*/long* nSlices) override;
   STDMETHOD(put_SliceGrowthFactor)(/*[in]*/Float64 sliceGrowthFactor) override;
	STDMETHOD(get_SliceGrowthFactor)(/*[out,retval]*/Float64* sliceGrowthFactor) override;
   STDMETHOD(putref_Section)(/*[in]*/IGeneralSection* pSection) override;
	STDMETHOD(get_Section)(/*[out,retval]*/IGeneralSection** pSection) override;
   STDMETHOD(Solve)(/*[in]*/Float64 Fz,/*[in]*/ Float64 angle,/*[in]*/ Float64 k_or_ec,/*[in]*/Float64 strainLocation,/*[in]*/SolutionMethod solutionMethod,/*[out,retval]*/IMomentCapacitySolution** solution) override;
   STDMETHOD(CompressionLimit)(/*[out]*/Float64* Fz,/*[out]*/Float64* Mx,/*[out]*/Float64* My,/*[out]*/Float64* eo) override;
   STDMETHOD(TensionLimit)(/*[out]*/Float64* Fz,/*[out]*/Float64* Mx,/*[out]*/Float64* My,/*[out]*/Float64* eo) override;
   STDMETHOD(get_PlasticCentroid)(/*[out,retval]*/ IPoint2d** pcg) override;
};

#endif //__MomentCapacitySolver_H_
