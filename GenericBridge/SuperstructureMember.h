///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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
#include "Segments.h"
#include "GenericBridgeCP.h"
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
   public ISegmentItemEvents,
   public ISegmentMeasure,
   public IStructuredStorage2,
   public CProxyDSuperstructureMemberEvents< CSuperstructureMember >,
   public IConnectionPointContainerImpl<CSuperstructureMember>,
   public IObjectSafetyImpl<CSuperstructureMember,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public CSegmentsOwner
{
public:
   CSuperstructureMember()
	{
      m_bIgnoreSegmentEvents = false;
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetBridge(IGenericBridge* pBridge);

   void RenameStageReferences(BSTR bstrOldName,BSTR bstrNewName);
   void AddDataForStage(BSTR bstrName);
   void RemoveDataForStage(BSTR bstrName);

   CSegments* GetSegments() { return m_pSegments; }

   // Sets the length of the member without creating a transaction or event
   void SetLengthSilent(Float64 length) { m_Length = length; }


DECLARE_REGISTRY_RESOURCEID(IDR_SUPERSTRUCTUREMEMBER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSuperstructureMember)
	COM_INTERFACE_ENTRY(ISuperstructureMember)
	COM_INTERFACE_ENTRY(IItemData)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(ISegmentItemEvents)
   COM_INTERFACE_ENTRY(ISegmentMeasure)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSuperstructureMember)
   CONNECTION_POINT_ENTRY(IID_ISuperstructureMemberEvents)
END_CONNECTION_POINT_MAP()

private:
   IGenericBridge* m_pBridge; // weak referece to bridge

   typedef std::pair<EndType,std::pair<CComBSTR,ReleaseType> > MemberReleaseDataType;

   CSegments* m_pSegments;
   bool m_bIgnoreSegmentEvents;

   Float64 m_Length;
   ReleaseType m_Release[2];
   CComBSTR m_bstrReleaseStage[2];
   VARIANT_BOOL m_bAreSegmentsSymmetrical; 
   VARIANT_BOOL m_bAreSegmentLengthsFractional;

   CItemDataManager m_ItemDataMgr;

// virtual methods for CSegmentsOwner
   virtual HRESULT SetUpConnection(ISegmentItem* pCp, unsigned long* pcookie);
   virtual void BreakConnection(ISegmentItem* pCp, unsigned long cookie);
   virtual void OnSegmentsChanged(CSegments* psegments);
   virtual Float64 Length();

   HRESULT AdviseSegmentItem(ISegmentItem* segItem,DWORD* pdwCookie);
   HRESULT UnadviseSegmentItem(ISegmentItem* segItem,DWORD dwCookie);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISegmentMeasure
public:
	STDMETHOD(IsFractional)();

// ISuperstructureMember
public:
	STDMETHOD(ReverseSegments)();
	STDMETHOD(GetSegmentForMemberLocation)(/*[in]*/ Float64 Location,/*[out]*/Float64* dist,/*[out]*/ ISegmentItem **ppSeg);
	STDMETHOD(GetMemberSegments)(/*[out,retval]*/ IFilteredSegmentCollection **ppSeg);
	STDMETHOD(RemoveSegments)();
	STDMETHOD(RemoveSegment)(/*[in]*/ CollectionIndexType idx);
	STDMETHOD(CopySegmentTo)(/*[in]*/ CollectionIndexType fromIdx, /*[in]*/ CollectionIndexType toIdx);
	STDMETHOD(MoveSegmentTo)(/*[in]*/ CollectionIndexType fromIdx,/*[in]*/ CollectionIndexType toIdx);
	STDMETHOD(InsertSegment)(/*[in]*/ CollectionIndexType idx,/*[in]*/ ISegment* segment);
	STDMETHOD(AddSegment)(/*[in]*/ ISegment* segment);
	STDMETHOD(get_AreSegmentLengthsFractional)(/*[out, retval]*/ VARIANT_BOOL *pVal);
   STDMETHOD(put_AreSegmentLengthsFractional)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_AreSegmentsSymmetrical)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_AreSegmentsSymmetrical)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Segment)(/*[in]*/ CollectionIndexType idx, /*[out, retval]*/ ISegment* *pVal);
	STDMETHOD(get_SegmentCount)(/*[out, retval]*/ CollectionIndexType *pVal);
	STDMETHOD(get_SegmentLength)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(GetEndRelease)(/*[in]*/ EndType end,/*[out]*/ BSTR* strReleaseStage,/*[out]*/ ReleaseType* release);
	STDMETHOD(SetEndRelease)(/*[in]*/ EndType end,/*[in]*/ BSTR strRemoveStage,/*[in]*/ ReleaseType release);
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Length)(/*[in]*/ Float64 newVal);
   STDMETHOD(Clone)(/*[out,retval]*/ISuperstructureMember** ppSSM);

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

// ISegmentItemEvents
public:
	STDMETHOD(OnSegmentItemChanged)(ISegmentItem* item)
	{
      if ( m_bIgnoreSegmentEvents )
         return S_OK;

      Fire_OnSuperstructureMemberChanged(this);
      return S_OK;
	}
};

#endif //__SUPERSTRUCTUREMEMBER_H_
