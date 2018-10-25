///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// FlangedGirderEndBlockSegment.h : Declaration of the CSegment

#pragma once

#include "resource.h"       // main symbols
#include "ItemDataManager.h"

/////////////////////////////////////////////////////////////////////////////
// CFlangedGirderEndBlockSegment
class ATL_NO_VTABLE CFlangedGirderEndBlockSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CFlangedGirderEndBlockSegment, &CLSID_FlangedGirderEndBlockSegment>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CFlangedGirderEndBlockSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IFlangedGirderEndBlockSegment,
   public IItemData,
   public IStructuredStorage2
{
   friend CFlangedGirderEndBlockSegment; // for easy cloning
public:
   CFlangedGirderEndBlockSegment()
	{
      m_pSSMbr       = NULL;
      m_pPrevSegment = NULL;
      m_pNextSegment = NULL;
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_FLANGEDGIRDERENDBLOCKSEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFlangedGirderEndBlockSegment)
	COM_INTERFACE_ENTRY(IFlangedGirderEndBlockSegment)
	COM_INTERFACE_ENTRY(ISegment)
   COM_INTERFACE_ENTRY(ISuperstructureMemberSegment)
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

   CItemDataManager m_ItemDataMgr;

   Float64 m_HaunchDepth[3];
   Float64 m_Fillet;

   // index is EndType
   Float64 m_EndBlockLength[2]; // length of end block from end of girder to transitation
   Float64 m_EndBlockTransitionLength[2]; // length of transition
   Float64 m_EndBlockWidth[2]; // width of end block at end of girder... constant until transition
                               // then transitions to the section

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
   STDMETHOD(GetHaunchDepth)(Float64* pStartVal,Float64* pMidVal,Float64* pEndVal);
   STDMETHOD(SetHaunchDepth)(Float64 startVal,Float64 midVal,Float64 endVal);
   STDMETHOD(ComputeHaunchDepth)(Float64 distAlongSegment,Float64* pVal);
   STDMETHOD(put_Fillet)(/*[in]*/Float64 fillet);
	STDMETHOD(get_Fillet)(/*[out,retval]*/Float64* fillet);

// IFlangedGirderEndBlockSegment
public:
   STDMETHOD(AddShape)(IShape* pShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial);
   STDMETHOD(get_ShapeCount)(IndexType* nShapes);
   STDMETHOD(get_ForegroundMaterial)(IndexType index,IMaterial* *material);
   STDMETHOD(get_BackgroundMaterial)(IndexType index,IMaterial* *material);

   STDMETHOD(put_EndBlockLength)(/*[in]*/EndType endType,/*[in]*/ Float64 length);
   STDMETHOD(get_EndBlockLength)(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pLength);
   STDMETHOD(put_EndBlockTransitionLength)(/*[in]*/EndType endType,/*[in]*/ Float64 length);
   STDMETHOD(get_EndBlockTransitionLength)(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pLength);
   STDMETHOD(put_EndBlockWidth)(/*[in]*/EndType endType,/*[in]*/ Float64 width);
   STDMETHOD(get_EndBlockWidth)(/*[in]*/EndType endType,/*[out,retval]*/ Float64* pWidth);

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
   void GetEndBlockWidth(Float64 x,Float64* pWtop,Float64* pWbot);
   Float64 GetSuperstructureMemberLength();
};

