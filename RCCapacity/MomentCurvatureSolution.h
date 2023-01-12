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

// MomentCurvatureSolution.h : Declaration of the CMomentCurvatureSolution

#ifndef __MomentCurvatureSolution_H_
#define __MomentCurvatureSolution_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CMomentCurvatureSolution
class ATL_NO_VTABLE CMomentCurvatureSolution : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMomentCurvatureSolution, &CLSID_MomentCurvatureSolution>,
	public ISupportErrorInfo,
	public IMomentCurvatureSolution
{
public:
	CMomentCurvatureSolution()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void AddCurvaturePoint(Float64 M,Float64 k,IMomentCapacitySolution* pSolution);


DECLARE_REGISTRY_RESOURCEID(IDR_MOMENTCURVATURESOLUTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMomentCurvatureSolution)
	COM_INTERFACE_ENTRY(IMomentCurvatureSolution)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   struct CurvaturePoint
   {
      Float64 M;
      Float64 k;
      CComPtr<IMomentCapacitySolution> Solution;

      bool operator<(const CurvaturePoint& other) const { return k < other.k; }
   };
   std::vector<CurvaturePoint> m_CurvaturePoints;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IMomentCurvatureSolution
public:
   STDMETHOD(get_MaxMoment)(/*[out,retval]*/Float64* Mmax) override;
   STDMETHOD(get_MaxMomentCurvature)(/*[out,retval]*/Float64* k) override;
   STDMETHOD(PeakCapacity)(/*[out]*/Float64* Mmax,/*[out]*/Float64* k) override;
   STDMETHOD(get_Moment)(/*[in]*/CollectionIndexType idx,/*[out,retval]*/Float64* Mmax) override;
	STDMETHOD(get_Curvature)(/*[in]*/CollectionIndexType idx,/*[out,retval]*/Float64* k) override;
	STDMETHOD(get_StrainPlane)(/*[in]*/CollectionIndexType idx,/*[out,retval]*/IPlane3d** strainPlane) override;
   STDMETHOD(get_CapacitySolution)(/*[in]*/CollectionIndexType idx,/*[out,retval]*/IMomentCapacitySolution** solution) override;
   STDMETHOD(get_PointCount)(/*[out,retval]*/CollectionIndexType* nPoints) override;
};

#endif //__MomentCurvatureSolution_H_
