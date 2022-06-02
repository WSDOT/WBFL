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

// GeneralSectionSolver.h : Declaration of the CGeneralSectionSolver

#ifndef __GeneralSectionSolver_H_
#define __GeneralSectionSolver_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CGeneralSectionSolver
class ATL_NO_VTABLE CGeneralSectionSolver : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGeneralSectionSolver, &CLSID_GeneralSectionSolver>,
	public ISupportErrorInfo,
	public IGeneralSectionSolver
{
public:
	CGeneralSectionSolver()
	{
      m_bDecomposed = false;
      m_nSlices = 100;
      m_SliceGrowthFactor = 1.0; // all slices are equal height
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_GENERALSECTIONSOLVER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGeneralSectionSolver)
	COM_INTERFACE_ENTRY(IGeneralSectionSolver)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


private:
   bool m_bDecomposed;
   CComPtr<ILine2d> m_NeutralAxis;
   CComPtr<ILine2d> m_TestLine;
   CComPtr<IGeomUtil2d> m_GeomUtil;
   CComPtr<IRect2d> m_ClippingRect;

   CComPtr<IGeneralSection> m_Section;
   void DecomposeSection(IPlane3d* strainPlane);
   bool IsNeutralAxisParallel(IPlane3d* strainPlane);
   void UpdateNeutralAxis(IPlane3d* strainPlane,ILine2d* line);

   typedef struct SHAPEINFO
   {
      IndexType ShapeIdx; // index of the shape in the general section model
      CComPtr<IShape> Shape;
      CComPtr<IStressStrain> FgMaterial;
      CComPtr<IStressStrain> BgMaterial;
      CComPtr<IPlane3d> InitialStrain;
      Float64 Le; // elongation length (typically 1 unit, but can be different for unbonded reinforcement elements)
      SHAPEINFO(IndexType shapeIdx, IShape* pShape, IStressStrain* pFG, IStressStrain* pBG, IPlane3d* pInitialStrain,Float64 Le) : ShapeIdx(shapeIdx), Shape(pShape), FgMaterial(pFG), BgMaterial(pBG), InitialStrain(pInitialStrain), Le(Le)
      {}
   } SHAPEINFO;

   typedef struct SLICEINFO
   {
      IndexType ShapeIdx; // index of the general section shape from which this slice is taken
      Float64 Area; // slice area
      Float64 Top; // top of slice elevation (may be off the section)
      Float64 Bottom; // bottom of slice elevation (may be off the sectino)
      CComPtr<IPoint2d> pntCG;
      Float64 ei; // initial strain at the centroid of this slice
      Float64 Le; // elongation length (typically 1 unit, but can be different for unbonded reinforcement elements)
      CComPtr<IStressStrain> FgMaterial;
      CComPtr<IStressStrain> BgMaterial;
      CComPtr<IShape> SliceShape;
   } SLICEINFO;

   std::vector<SLICEINFO> m_Slices;

   long m_nSlices;
   Float64 m_SliceGrowthFactor; // height of last slice is slice growth factor times the height of the first slice

   HRESULT AnalyzeSlice(CGeneralSectionSolver::SLICEINFO& slice,IPlane3d* incrementalStrainPlane,Float64& P,Float64& Mx,Float64& My,Float64& fg_stress,Float64& bg_stress,Float64& stress,Float64& incrementalStrain,Float64& totalStrain,bool& bExceededStrainLimits);
   HRESULT SliceShape(const SHAPEINFO& shapeInfo,Float64 angle,Float64 sliceTop,Float64 sliceBottom,SLICEINFO& sliceInfo);
   Float64 GetNeutralAxisAngle();

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IGeneralSectionSolver
public:
   STDMETHOD(putref_Section)(/*[in]*/IGeneralSection* pSection) override;
   STDMETHOD(get_Section)(/*[out,retval]*/IGeneralSection** pSection) override;
   STDMETHOD(put_Slices)(/*[in]*/long nSlices) override;
   STDMETHOD(get_Slices)(/*[out,retval]*/long* nSlices) override;
   STDMETHOD(put_SliceGrowthFactor)(/*[in]*/Float64 sliceGrowthFactor) override;
   STDMETHOD(get_SliceGrowthFactor)(/*[out,retval]*/Float64* sliceGrowthFactor) override;
   STDMETHOD(Solve)(/*[in]*/ IPlane3d* strainPlane,/*[out,retval]*/IGeneralSectionSolution** solution) override;
};

#endif //__GeneralSectionSolver_H_
