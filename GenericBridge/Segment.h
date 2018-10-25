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

// Segment.h : Declaration of the CSegment

#ifndef __SEGMENT_H_
#define __SEGMENT_H_

#include "resource.h"       // main symbols
#include "ItemDataManager.h"

/////////////////////////////////////////////////////////////////////////////
// CSegment
class ATL_NO_VTABLE CSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSegment, &CLSID_PrismaticSegment>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IPrismaticSegment,
   public IItemData,
   public IStructuredStorage2
{
   friend CSegment; // for easy cloning
public:
   CSegment()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_SEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSegment)
	COM_INTERFACE_ENTRY(IPrismaticSegment)
	COM_INTERFACE_ENTRY(ISegment)
	COM_INTERFACE_ENTRY(IItemData)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   ISegment* m_pPrevSegment; // weak reference to previous segment
   ISegment* m_pNextSegment; // weak reference to next segment

   Float64 m_Orientation; // orientation of girder... plumb = 0... rotated CW is +... radians

   struct ShapeData
   {
      CComPtr<IShape> Shape;
      CComPtr<IMaterial> FGMaterial;
      CComPtr<IMaterial> BGMaterial;
   };
   std::vector<ShapeData> m_Shapes;

   CItemDataManager m_ItemDataMgr;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISegment
public:
   STDMETHOD(putref_PrevSegment)(ISegment* segment) override;
   STDMETHOD(get_PrevSegment)(ISegment** segment) override;
   STDMETHOD(putref_NextSegment)(ISegment* segment) override;
   STDMETHOD(get_NextSegment)(ISegment** segment) override;
	STDMETHOD(get_Section)(StageIndexType stageIdx,Float64 Xs,SectionBias sectionBias,ISection** ppSection) override;
   STDMETHOD(get_PrimaryShape)(Float64 Xs, SectionBias sectionBias,IShape** ppShape) override;
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override;

// IPrismaticSegment
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
};

#endif //__SEGMENT_H_
