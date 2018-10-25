///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright � 1999-2015  Washington State Department of Transportation
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

   Float64 m_HaunchDepth[2];
   
   CItemDataManager m_ItemDataMgr;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISegment
public:
   STDMETHOD(putref_SuperstructureMember)(ISuperstructureMember* ssMbr);
   STDMETHOD(get_SuperstructureMember)(ISuperstructureMember** ssMbr);
   STDMETHOD(putref_GirderLine)(IGirderLine* girderLine);
   STDMETHOD(get_GirderLine)(IGirderLine** girderLine);
   STDMETHOD(putref_PrevSegment)(ISegment* segment);
   STDMETHOD(get_PrevSegment)(ISegment** segment);
   STDMETHOD(putref_NextSegment)(ISegment* segment);
   STDMETHOD(get_NextSegment)(ISegment** segment);
	STDMETHOD(get_Section)(StageIndexType stageIdx,Float64 distAlongSegment,ISection** ppSection);
   STDMETHOD(get_PrimaryShape)(Float64 distAlongSegment,IShape** ppShape);
   STDMETHOD(get_Profile)(VARIANT_BOOL bIncludeClosure,IShape** ppShape);
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_LayoutLength)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(put_Orientation)(/*[in]*/Float64 orientation);
	STDMETHOD(get_Orientation)(/*[out,retval]*/Float64* orientation);
   STDMETHOD(get_HaunchDepth)(EndType endType,Float64* pVal);
   STDMETHOD(put_HaunchDepth)(EndType endType,Float64 val);
   STDMETHOD(GetHaunchDepth)(Float64 distAlongSegment,Float64 *pVal);

// IPrismaticSuperstructureMemberSegment
public:
	STDMETHOD(AddShape)(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial);
   STDMETHOD(get_ShapeCount)(IndexType* nShapes);
   STDMETHOD(get_ForegroundMaterial)(IndexType index,IMaterial* *material);
   STDMETHOD(get_BackgroundMaterial)(IndexType index,IMaterial* *material);


// IItemData
public:
   STDMETHOD(AddItemData)(/*[in]*/BSTR name,/*[in]*/IUnknown* data);
   STDMETHOD(GetItemData)(/*[in]*/BSTR name,/*[out,retval]*/IUnknown** data);
   STDMETHOD(RemoveItemData)(/*[in]*/BSTR name);
   STDMETHOD(GetItemDataCount)(/*[out,retval]*/CollectionIndexType* count);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);

private:
   Float64 GetSuperstructureMemberLength();
};