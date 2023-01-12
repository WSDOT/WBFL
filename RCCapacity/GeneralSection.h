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

// GeneralSection.h : Declaration of the CGeneralSection

#ifndef __GeneralSection_H_
#define __GeneralSection_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CGeneralSection
class ATL_NO_VTABLE CGeneralSection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGeneralSection, &CLSID_GeneralSection>,
	public ISupportErrorInfo,
	public IGeneralSection,
   public IStructuredStorage2
{
public:
	CGeneralSection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_GENERALSECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGeneralSection)
	COM_INTERFACE_ENTRY(IGeneralSection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
END_COM_MAP()


private:
   struct SectionItem
   {
      CComBSTR bstrName;
      CComPtr<IShape> shape;
      CComPtr<IStressStrain> fgMaterial;
      CComPtr<IStressStrain> bgMaterial;
      CComPtr<IPlane3d> initialStrain;
      Float64 Le; // elongation length
      SectionItem() : Le(1.0)
      {}
      SectionItem(CComBSTR bstrName,IShape* pShape,IStressStrain* pFG,IStressStrain* pBG,IPlane3d* initialStrain,Float64 le) : bstrName(bstrName), shape(pShape), fgMaterial(pFG), bgMaterial(pBG), initialStrain(initialStrain), Le(le)
      {}
   };

   std::vector<SectionItem> m_SectionItems;
   IndexType m_PrimaryShapeIdx;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IGeneralSection
public:
   STDMETHOD(AddShape)(/*[in]*/BSTR bstrName,/*[in]*/IShape* pShape,/*[in]*/IStressStrain* pfgMaterial,/*[in]*/IStressStrain* pbgMaterial,/*[in]*/IPlane3d* initialStrain,/*[in]*/Float64 Le,/*[in]*/VARIANT_BOOL vbPrimaryShape) override;
   STDMETHOD(get_ShapeCount)(/*[out,retval]*/CollectionIndexType* nShapes) override;
   STDMETHOD(put_PrimaryShape)(/*[in]*/IndexType shapeIdx) override;
   STDMETHOD(get_PrimaryShape)(/*[out, retval]*/IndexType* pShapeIdx) override;
   STDMETHOD(put_Name)(/*[in]*/CollectionIndexType shapeIdx, /*[in]*/BSTR bstrName) override;
   STDMETHOD(get_Name)(/*[in]*/CollectionIndexType shapeIdx, /*[out, retval]*/BSTR* pbstrName) override;
   STDMETHOD(get_Shape)(/*[in]*/CollectionIndexType shapeIdx,/*[out,retval]*/IShape** pShape) override;
   STDMETHOD(putref_Shape)(/*[in]*/CollectionIndexType shapeIdx,/*[in]*/IShape* pShape) override;
   STDMETHOD(get_ForegroundMaterial)(/*[in]*/CollectionIndexType shapeIdx,/*[out,retval]*/IStressStrain** pMaterial) override;
   STDMETHOD(putref_ForegroundMaterial)(/*[in]*/CollectionIndexType shapeIdx,/*[in]*/IStressStrain* pMaterial) override;
   STDMETHOD(get_BackgroundMaterial)(/*[in]*/CollectionIndexType shapeIdx,/*[out,retval]*/IStressStrain** pMaterial) override;
   STDMETHOD(putref_BackgroundMaterial)(/*[in]*/CollectionIndexType shapeIdx,/*[in]*/IStressStrain* pMaterial) override;
   STDMETHOD(get_InitialStrain)(/*[in]*/CollectionIndexType shapeIdx,/*[out,retval]*/IPlane3d** pStrainPlane) override;
   STDMETHOD(putref_InitialStrain)(/*[in]*/CollectionIndexType shapeIdx,/*[in]*/IPlane3d* strandPlane) override;
   STDMETHOD(get_ElongationLength)(/*[in]*/CollectionIndexType shapeIdx, /*[out, retval]*/Float64* Le);
   STDMETHOD(put_ElongationLength)(/*[in]*/CollectionIndexType shapeIdx, /*[in]*/Float64 Le);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;
};

#endif //__GeneralSection_H_
