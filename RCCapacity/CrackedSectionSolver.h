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

// CrackedSectionSolver.h : Declaration of the CCrackedSectionSolver

#ifndef __CrackedSectionSolver_H_
#define __CrackedSectionSolver_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CCrackedSectionSolver
class ATL_NO_VTABLE CCrackedSectionSolver : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCrackedSectionSolver, &CLSID_CrackedSectionSolver>,
	public ISupportErrorInfo,
	public ICrackedSectionSolver
{
public:
	CCrackedSectionSolver()
	{
      //m_bFurthestPointUpdated = false;
      //m_XFurthest = -999999;
      //m_YFurthest = -999999;

      //m_bUpdateTensionLimit = true;
      //m_bUpdateCompressionLimit = true;

      m_nSlices = 100;
      m_SliceGrowthFactor = 1.0; // all slices are equal height

      m_bDecomposed = false;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_CRACKEDSECTIONSOLVER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCrackedSectionSolver)
	COM_INTERFACE_ENTRY(ICrackedSectionSolver)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


private:
   //CComPtr<IGeneralSectionSolver> m_GeneralSolver;
   //CComPtr<IGeneralSectionSolution> m_GeneralSolution;
   //CComPtr<IPlane3d> m_StrainPlane;
   //CComPtr<IPoint3d> m_P1, m_P2, m_P3;
   Float64 m_CGTolerance;
   long m_MaxIter;
   //bool m_bFurthestPointUpdated;
   //Float64 m_XFurthest, m_YFurthest;

   //void UpdateStrainPlane(Float64 angle,Float64 k_or_ec,Float64 eo,SolutionMethod solutionMethod);
   //void UpdateFurthestPoint(Float64 angle);
   //Float64 GetCurvature(CollectionIndexType idx);
   //HRESULT GetNeutralAxisParameterRange(Float64 k_or_ec,SolutionMethod solutionMethod,Float64 angle,Float64 Fz,Float64* peo_lower,Float64* peo_upper,Float64* pFz_lower,Float64* pFz_upper);
   //HRESULT AnalyzeSection(Float64 Fz,Float64 angle,Float64 k_or_ec,SolutionMethod solutionMethod,IMomentCapacitySolution** solution);

   long m_nSlices;
   Float64 m_SliceGrowthFactor; // height of last slice is slice growth factor times the height of the first slice
   CComPtr<IGeneralSection> m_Section;

   bool m_bDecomposed;

   typedef struct SHAPEINFO
   {
      CComPtr<IShape> Shape;
      CComPtr<IStressStrain> FgMaterial;
      CComPtr<IStressStrain> BgMaterial;
   };

   typedef struct SLICEINFO
   {
      Float64 Area;
      Float64 Top;
      Float64 Bottom;
      Float64 Xcg;
      Float64 Ycg;
      CComPtr<IStressStrain> FgMaterial;
      CComPtr<IStressStrain> BgMaterial;
      CComPtr<IShape> SliceShape;

      bool operator<(const SLICEINFO& other) { return other.Ycg < Ycg; }
   } SLICEINFO;

   std::vector<SLICEINFO> m_SliceInfo;
   CComPtr<IRect2d> m_ClippingRect;

   Float64 m_Ybottom, m_Ytop; // top and bottom of section

   void DecomposeSection();
   HRESULT AnalyzeSection(Float64 Yguess,IUnkArray* slices,IPoint2d* pntCG);
   HRESULT AnalyzeSlice(Float64 Yguess,SLICEINFO& slice,Float64& EA,Float64& EAx,Float64& EAy,Float64& Efg,Float64& Ebg);
   HRESULT SliceShape(const SHAPEINFO& shapeInfo,Float64 sliceTop,Float64 sliceBottom,SLICEINFO& sliceInfo);

#if defined _DEBUG_LOGGING
   CComPtr<IWBFLErrorLog> m_Log;
   DWORD m_dwCookie;
#endif // _DEBUG_LOGGING

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICrackedSectionSolver
public:
   STDMETHOD(put_CGTolerance)(/*[in]*/Float64 tolerance);
   STDMETHOD(get_CGTolerance)(/*[out,retval]*/Float64* tolerance);
   STDMETHOD(put_MaxIterations)(/*[in]*/long maxIter);
   STDMETHOD(get_MaxIterations)(/*[out,retval]*/long* maxIter);
   STDMETHOD(put_Slices)(/*[in]*/long nSlices);
	STDMETHOD(get_Slices)(/*[out,retval]*/long* nSlices);
   STDMETHOD(put_SliceGrowthFactor)(/*[in]*/Float64 sliceGrowthFactor);
	STDMETHOD(get_SliceGrowthFactor)(/*[out,retval]*/Float64* sliceGrowthFactor);
   STDMETHOD(putref_Section)(/*[in]*/IGeneralSection* pSection);
	STDMETHOD(get_Section)(/*[out,retval]*/IGeneralSection** pSection);
   STDMETHOD(Solve)(/*[out,retval]*/ICrackedSectionSolution** solution);
};

#endif //__CrackedSectionSolver_H_
