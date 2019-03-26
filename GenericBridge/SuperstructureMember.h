///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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

// SuperstructureMember.h : Declaration of the CSuperstructureMember

#ifndef __SUPERSTRUCTUREMEMBER_H_
#define __SUPERSTRUCTUREMEMBER_H_

#include "resource.h"       // main symbols
#include "ItemDataManager.h"

/////////////////////////////////////////////////////////////////////////////
// CSuperstructureMember
class ATL_NO_VTABLE CSuperstructureMember : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSuperstructureMember,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSuperstructureMember, &CLSID_SuperstructureMember>,
	public ISupportErrorInfo,
   public ISuperstructureMember,
   public IItemData,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CSuperstructureMember,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CSuperstructureMember()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void Init(GirderIDType id,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,IGenericBridge* pBridge);


DECLARE_REGISTRY_RESOURCEID(IDR_SUPERSTRUCTUREMEMBER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSuperstructureMember)
	COM_INTERFACE_ENTRY(ISuperstructureMember)
	COM_INTERFACE_ENTRY(IItemData)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   GirderIDType m_ID;
   GirderIDType m_LeftSSMbrID, m_RightSSMbrID;
   IGenericBridge* m_pBridge; // weak referece to bridge

   typedef std::pair<EndType,std::pair<CComBSTR,ReleaseType> > MemberReleaseDataType;

   std::vector<CComPtr<ISuperstructureMemberSegment>> m_Segments;

   ReleaseType m_Release[2];
   StageIndexType m_ReleaseStageIndex[2];

   CItemDataManager m_ItemDataMgr;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISuperstructureMember
public:
   STDMETHOD(get_ID)(GirderIDType* pID) override;
	STDMETHOD(AddSegment)(/*[in]*/ ISuperstructureMemberSegment* segment) override;
	STDMETHOD(get_Segment)(/*[in]*/ SegmentIndexType idx, /*[out, retval]*/ ISuperstructureMemberSegment* *pVal) override;
   STDMETHOD(GetDistanceFromStartOfSegment)(Float64 Xg,Float64* pXs,SegmentIndexType* pSegIdx,ISuperstructureMemberSegment** ppSeg) override;
   STDMETHOD(GetDistanceFromStart)(SegmentIndexType segIdx,Float64 Xs,Float64* pXg) override;
	STDMETHOD(get_SegmentCount)(/*[out, retval]*/ SegmentIndexType *pVal) override;
	STDMETHOD(GetEndRelease)(/*[in]*/ EndType end,/*[out]*/ StageIndexType* pStageIdx,/*[out]*/ ReleaseType* release) override;
	STDMETHOD(SetEndRelease)(/*[in]*/ EndType end,/*[in]*/ StageIndexType stageIdx,/*[in]*/ ReleaseType release) override;
   STDMETHOD(GetPlanAngle)(/*[in]*/Float64 distFromStartOfSSMbr,/*[out,retval]*/IAngle** ppAngle) override;
   STDMETHOD(get_LocationType)(LocationType* pVal) override;
   STDMETHOD(get_LeftSSMbrID)(/*[out, retval]*/ GirderIDType* pID) override;
   STDMETHOD(get_RightSSMbrID)(/*[out, retval]*/ GirderIDType* pID) override;
   STDMETHOD(get_Bridge)(IGenericBridge** ppBridge) override;

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

#endif //__SUPERSTRUCTUREMEMBER_H_
