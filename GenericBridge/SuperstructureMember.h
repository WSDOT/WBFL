///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

   void Init(GirderIDType id,LocationType locationType,IGenericBridge* pBridge);


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
   IGenericBridge* m_pBridge; // weak referece to bridge

   typedef std::pair<EndType,std::pair<CComBSTR,ReleaseType> > MemberReleaseDataType;

   std::vector<CComPtr<ISuperstructureMemberSegment>> m_Segments;

   ReleaseType m_Release[2];
   StageIndexType m_ReleaseStageIndex[2];

   LocationType m_LocationType;

   CItemDataManager m_ItemDataMgr;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISuperstructureMember
public:
   STDMETHOD(get_ID)(GirderIDType* pID);
	STDMETHOD(AddSegment)(/*[in]*/ ISuperstructureMemberSegment* segment);
	STDMETHOD(get_Segment)(/*[in]*/ SegmentIndexType idx, /*[out, retval]*/ ISuperstructureMemberSegment* *pVal);
   STDMETHOD(GetDistanceFromStartOfSegment)(Float64 Xg,Float64* pXs,SegmentIndexType* pSegIdx,ISuperstructureMemberSegment** ppSeg);
   STDMETHOD(GetDistanceFromStart)(SegmentIndexType segIdx,Float64 Xs,Float64* pXg);
	STDMETHOD(get_SegmentCount)(/*[out, retval]*/ SegmentIndexType *pVal);
	STDMETHOD(GetEndRelease)(/*[in]*/ EndType end,/*[out]*/ StageIndexType* pStageIdx,/*[out]*/ ReleaseType* release);
	STDMETHOD(SetEndRelease)(/*[in]*/ EndType end,/*[in]*/ StageIndexType stageIdx,/*[in]*/ ReleaseType release);
   STDMETHOD(GetPlanAngle)(/*[in]*/Float64 distFromStartOfSSMbr,/*[out,retval]*/IAngle** ppAngle);
   STDMETHOD(get_LocationType)(LocationType* pVal);
   STDMETHOD(get_Bridge)(IGenericBridge** ppBridge);

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
};

#endif //__SUPERSTRUCTUREMEMBER_H_
