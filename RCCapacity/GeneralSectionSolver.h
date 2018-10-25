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
      CComPtr<IShape> Shape;
      CComPtr<IStressStrain> FgMaterial;
      CComPtr<IStressStrain> BgMaterial;
      Float64 ei; // initial strain
   };

   typedef struct SLICEINFO
   {
      Float64 Area;
      Float64 Top;
      Float64 Bottom;
      Float64 Xcg;
      Float64 Ycg;
      Float64 ei; // initial strain
      CComPtr<IStressStrain> FgMaterial;
      CComPtr<IStressStrain> BgMaterial;
      CComPtr<IShape> SliceShape;

      bool operator<(const SLICEINFO& other) { return other.Ycg < Ycg; }
   } SLICEINFO;

   std::vector<SLICEINFO> m_Slices;

   long m_nSlices;
   Float64 m_SliceGrowthFactor; // height of last slice is slice growth factor times the height of the first slice

   HRESULT AnalyzeSlice(CGeneralSectionSolver::SLICEINFO& slice,IPlane3d* strainPlane,Float64& P,Float64& Mx,Float64& My,Float64& fg_stress,Float64& bg_stress,Float64& stress,Float64& strain,bool& bExceededStrainLimits);
   HRESULT SliceShape(const SHAPEINFO& shapeInfo,Float64 angle,Float64 sliceTop,Float64 sliceBottom,SLICEINFO& sliceInfo);
   Float64 GetNeutralAxisAngle();

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IGeneralSectionSolver
public:
   STDMETHOD(putref_Section)(/*[in]*/IGeneralSection* pSection);
   STDMETHOD(get_Section)(/*[out,retval]*/IGeneralSection** pSection);
   STDMETHOD(put_Slices)(/*[in]*/long nSlices);
   STDMETHOD(get_Slices)(/*[out,retval]*/long* nSlices);
   STDMETHOD(put_SliceGrowthFactor)(/*[in]*/Float64 sliceGrowthFactor);
   STDMETHOD(get_SliceGrowthFactor)(/*[out,retval]*/Float64* sliceGrowthFactor);
   STDMETHOD(Solve)(/*[in]*/ IPlane3d* strainPlane,/*[out,retval]*/IGeneralSectionSolution** solution);
};

#endif //__GeneralSectionSolver_H_
