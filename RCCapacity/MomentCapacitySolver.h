///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
//                   Bridge and Structures Office
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
      m_bFurthestPointUpdated = false;
      m_XFurthest = -999999;
      m_YFurthest = -999999;

      m_bUpdateTensionLimit = true;
      m_bUpdateCompressionLimit = true;
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
   CComPtr<IPlane3d> m_StrainPlane;
   CComPtr<IPoint3d> m_P1, m_P2, m_P3;
   Float64 m_AxialTolerance;
   long m_MaxIter;
   bool m_bFurthestPointUpdated;
   Float64 m_XFurthest, m_YFurthest;

   bool m_bUpdateTensionLimit;
   Float64 m_FzTensionLimit, m_MxTensionLimit, m_MyTensionLimit, m_eoTensionLimit;

   bool m_bUpdateCompressionLimit;
   Float64 m_FzCompressionLimit, m_MxCompressionLimit, m_MyCompressionLimit, m_eoCompressionLimit;

   void UpdateStrainPlane(Float64 angle,Float64 k_or_ec,Float64 eo,SolutionMethod solutionMethod);
   void UpdateFurthestPoint(Float64 angle);
   Float64 GetCurvature(CollectionIndexType idx);
   HRESULT GetNeutralAxisParameterRange(Float64 k_or_ec,SolutionMethod solutionMethod,Float64 angle,Float64 Fz,Float64* peo_lower,Float64* peo_upper,Float64* pFz_lower,Float64* pFz_upper);
   HRESULT AnalyzeSection(Float64 Fz,Float64 angle,Float64 k_or_ec,SolutionMethod solutionMethod,IMomentCapacitySolution** solution);
   HRESULT ZeroCapacitySolution(IMomentCapacitySolution** solution);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMomentCapacitySolver
public:
   STDMETHOD(put_AxialTolerance)(/*[in]*/Float64 tolerance);
   STDMETHOD(get_AxialTolerance)(/*[out,retval]*/Float64* tolerance);
   STDMETHOD(put_MaxIterations)(/*[in]*/long maxIter);
   STDMETHOD(get_MaxIterations)(/*[out,retval]*/long* maxIter);
   STDMETHOD(put_Slices)(/*[in]*/long nSlices);
	STDMETHOD(get_Slices)(/*[out,retval]*/long* nSlices);
   STDMETHOD(put_SliceGrowthFactor)(/*[in]*/Float64 sliceGrowthFactor);
	STDMETHOD(get_SliceGrowthFactor)(/*[out,retval]*/Float64* sliceGrowthFactor);
   STDMETHOD(putref_Section)(/*[in]*/IGeneralSection* pSection);
	STDMETHOD(get_Section)(/*[out,retval]*/IGeneralSection** pSection);
   STDMETHOD(Solve)(/*[in]*/Float64 Fz,/*[in]*/ Float64 angle,/*[in]*/ Float64 k_or_ec,/*[in]*/SolutionMethod solutionMethod,/*[out,retval]*/IMomentCapacitySolution** solution);
   STDMETHOD(CompressionLimit)(/*[out]*/Float64* Fz,/*[out]*/Float64* Mx,/*[out]*/Float64* My,/*[out]*/Float64* eo);
   STDMETHOD(TensionLimit)(/*[out]*/Float64* Fz,/*[out]*/Float64* Mx,/*[out]*/Float64* My,/*[out]*/Float64* eo);
   STDMETHOD(get_PlasticCentroid)(/*[out,retval]*/ IPoint2d** pcg);
};

#endif //__MomentCapacitySolver_H_
