///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

// PrismaticSuperstructureMemberSegment.h : Declaration of the CPrismaticSuperstructureMemberSegment

#pragma once

#include "resource.h"       // main symbols
#include "ItemDataManager.h"

/////////////////////////////////////////////////////////////////////////////
// CPrismaticSuperstructureMemberSegment
class ATL_NO_VTABLE CPrismaticSuperstructureMemberSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPrismaticSuperstructureMemberSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPrismaticSuperstructureMemberSegment, &CLSID_PrismaticSuperstructureMemberSegment>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPrismaticSuperstructureMemberSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IPrismaticSuperstructureMemberSegment,
   public IItemData,
   public IStructuredStorage2
{
   friend CPrismaticSuperstructureMemberSegment; // for easy cloning
public:
   CPrismaticSuperstructureMemberSegment()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_PRISMATICSUPERSTRUCTUREMEMBERSEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPrismaticSuperstructureMemberSegment)
	COM_INTERFACE_ENTRY(IPrismaticSuperstructureMemberSegment)
   COM_INTERFACE_ENTRY(ISuperstructureMemberSegment)
	COM_INTERFACE_ENTRY(ISegment)
	COM_INTERFACE_ENTRY(IItemData)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   IGirderLine* m_pGirderLine; // weak reference to the girder line in the geometry model that provies the geometry for this segment

   ISuperstructureMember* m_pSSMbr; // weak reference to parent superstructure member
   ISuperstructureMemberSegment* m_pPrevSegment; // weak reference to previous segment
   ISuperstructureMemberSegment* m_pNextSegment; // weak reference to next segment

   Float64 m_Orientation; // orientation of girder... plumb = 0... rotated CW is +... radians

   struct ShapeData
   {
      CComPtr<IShape> Shape;
      CComPtr<IMaterial> FGMaterial;
      CComPtr<IMaterial> BGMaterial;
   };
   std::vector<ShapeData> m_Shapes;

   Float64 m_HaunchDepth[3];
   Float64 m_Fillet;
   
   CItemDataManager m_ItemDataMgr;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISegment
public:
   STDMETHOD(putref_SuperstructureMember)(ISuperstructureMember* ssMbr) override;
   STDMETHOD(get_SuperstructureMember)(ISuperstructureMember** ssMbr) override;
   STDMETHOD(putref_GirderLine)(IGirderLine* girderLine) override;
   STDMETHOD(get_GirderLine)(IGirderLine** girderLine) override;
   STDMETHOD(putref_PrevSegment)(ISegment* segment) override;
   STDMETHOD(get_PrevSegment)(ISegment** segment) override;
   STDMETHOD(putref_NextSegment)(ISegment* segment) override;
   STDMETHOD(get_NextSegment)(ISegment** segment) override;
	STDMETHOD(get_Section)(StageIndexType stageIdx,Float64 distAlongSegment,ISection** ppSection) override;
   STDMETHOD(get_PrimaryShape)(Float64 distAlongSegment,IShape** ppShape) override;
   STDMETHOD(get_Profile)(VARIANT_BOOL bIncludeClosure,IShape** ppShape) override;
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_LayoutLength)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(put_Orientation)(/*[in]*/Float64 orientation) override;
	STDMETHOD(get_Orientation)(/*[out,retval]*/Float64* orientation) override;
   STDMETHOD(GetHaunchDepth)(Float64* pStartVal,Float64* pMidVal,Float64* pEndVal) override;
   STDMETHOD(SetHaunchDepth)(Float64 startVal,Float64 midVal,Float64 endVal) override;
   STDMETHOD(ComputeHaunchDepth)(Float64 distAlongSegment,Float64* pVal) override;
   STDMETHOD(put_Fillet)(/*[in]*/Float64 Fillet) override;
	STDMETHOD(get_Fillet)(/*[out,retval]*/Float64* Fillet) override;

// IPrismaticSuperstructureMemberSegment
public:
	STDMETHOD(AddShape)(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial) override;
   STDMETHOD(get_ShapeCount)(IndexType* nShapes) override;
   STDMETHOD(get_ForegroundMaterial)(IndexType index,IMaterial* *material) override;
   STDMETHOD(get_BackgroundMaterial)(IndexType index,IMaterial* *material) override;


// IItemData
public:
   STDMETHOD(AddItemData)(/*[in]*/BSTR name,/*[in]*/IUnknown* data) override;
   STDMETHOD(GetItemData)(/*[in]*/BSTR name,/*[out,retval]*/IUnknown** data) override;
   STDMETHOD(RemoveItemData)(/*[in]*/BSTR name) override;
   STDMETHOD(GetItemDataCount)(/*[out,retval]*/CollectionIndexType* count) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;

private:
   Float64 GetSuperstructureMemberLength();
};
