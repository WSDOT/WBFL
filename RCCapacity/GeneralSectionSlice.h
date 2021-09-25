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

// GeneralSectionSlice.h : Declaration of the CGeneralSectionSlice

#ifndef __GeneralSectionSlice_H_
#define __GeneralSectionSlice_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CGeneralSectionSlice
class ATL_NO_VTABLE CGeneralSectionSlice : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGeneralSectionSlice, &CLSID_GeneralSectionSlice>,
	public ISupportErrorInfo,
	public IGeneralSectionSlice
{
public:
	CGeneralSectionSlice()
	{
      m_ShapeIdx = INVALID_INDEX;
      m_Area = 0;
      m_InitialStrain = 0;
      m_IncrementalStrain = 0;
      m_TotalStrain = 0;
      m_cgX = 0;
      m_cgY = 0;
      m_fgStress = 0;
      m_bgStress = 0;
      m_vbExceededStrainLimit = VARIANT_FALSE;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_GENERALSECTIONSLICE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGeneralSectionSlice)
	COM_INTERFACE_ENTRY(IGeneralSectionSlice)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


private:
   IndexType m_ShapeIdx;
   CComPtr<IShape> m_Shape;
   CComPtr<IStressStrain> m_fgMaterial;
   CComPtr<IStressStrain> m_bgMaterial;
   Float64 m_Area;
   Float64 m_cgX, m_cgY;
   Float64 m_InitialStrain;
   Float64 m_IncrementalStrain;
   Float64 m_TotalStrain;
   Float64 m_fgStress;
   Float64 m_bgStress;
   VARIANT_BOOL m_vbExceededStrainLimit;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IGeneralSectionSlice
public:
   STDMETHOD(InitSlice)(/*[in]*/IndexType shapeIdx,/*[in]*/IShape* pShape,/*[in]*/Float64 A,/*[in]*/Float64 cgX,/*[in]*/Float64 cgY,/*[in]*/Float64 initialStrain,/*[in]*/Float64 deltaStrain,/*[in]*/Float64 totalStrain,/*[in]*/Float64 fgStress,/*[in]*/Float64 bgStress,/*[in]*/IStressStrain* pfgMaterial,/*[in]*/IStressStrain* pbgMaterial, /*[in]*/VARIANT_BOOL vbExceededStrainLimit) override;
   STDMETHOD(get_Area)(/*[out,retval]*/Float64* pArea) override;
	STDMETHOD(get_CG)(/*[out,retval]*/IPoint2d** pCG) override;
   STDMETHOD(get_InitialStrain)(/*[out,retval]*/Float64* pStrain) override;
   STDMETHOD(get_IncrementalStrain)(/*[out,retval]*/Float64* pStrain) override;
   STDMETHOD(get_TotalStrain)(/*[out,retval]*/Float64* pStrain) override;
   STDMETHOD(get_ForegroundStress)(/*[out,retval]*/Float64* pfgStress) override;
	STDMETHOD(get_BackgroundStress)(/*[out,retval]*/Float64* pbgStress) override;
   STDMETHOD(get_ForegroundMaterial)(/*[out,retval]*/IStressStrain** pMaterial) override;
   STDMETHOD(get_BackgroundMaterial)(/*[out,retval]*/IStressStrain** pMaterial) override;
   STDMETHOD(get_Shape)(/*[out,retval]*/IShape** pShape) override;
   STDMETHOD(get_ShapeIndex)(/*[out, retval]*/IndexType* pShapeIdx) override;
   STDMETHOD(ExceededStrainLimit)(/*[out, retval]*/VARIANT_BOOL* pvbExceededStrainLimit) override;
};

#endif //__GeneralSectionSlice_H_
