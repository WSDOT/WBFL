///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2018  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// SuperstructureMember.h : Declaration of the CSuperstructureMember

#ifndef __SUPERSTRUCTUREMEMBER_H_
#define __SUPERSTRUCTUREMEMBER_H_

#include "resource.h"       // main symbols
#include "Segments.h"
#include "SuperstructureMemberCP.h"

/////////////////////////////////////////////////////////////////////////////
// CSuperstructureMember
class ATL_NO_VTABLE CSuperstructureMember : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSuperstructureMember,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSuperstructureMember, &CLSID_SuperstructureMember>,
	public ISupportErrorInfo,
   public IPersistImpl<CSuperstructureMember>,
	public IStructuredStorage2,
	public IConnectionPointContainerImpl<CSuperstructureMember>,
	public ISuperstructureMember,
   public CSegmentsOwner,
   public CProxyDSuperstructureMemberEvents< CSuperstructureMember >,
   public IObjectSafetyImpl<CSuperstructureMember,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISegmentItemEvents
{
public:
   CSuperstructureMember();

   ~CSuperstructureMember()
   {;}

DECLARE_REGISTRY_RESOURCEID(IDR_SUPERSTRUCTUREMEMBER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSuperstructureMember)
	COM_INTERFACE_ENTRY(ISuperstructureMember)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ISegmentItemEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSuperstructureMember)
CONNECTION_POINT_ENTRY(IID_ISuperstructureMemberEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISuperstructureMember
public:
   STDMETHOD(get_LinkMember)(/*[out,retval]*/VARIANT_BOOL* pbIsLinkMember) override;
   STDMETHOD(put_LinkMember)(/*[in]*/VARIANT_BOOL bIsLinkMember) override;
   STDMETHOD(RemoveStage)(/*[in]*/BSTR stage) override;
	STDMETHOD(get_IsSymmetrical)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_IsSymmetrical)(/*[in]*/ VARIANT_BOOL newVal) override;
	STDMETHOD(Clone)(/*[out,retval]*/ISuperstructureMember** clone) override;
	STDMETHOD(GetMemberSegments)(/*[in]*/BSTR stage, /*[out,retval]*/IFilteredSegmentCollection** segments) override;
	STDMETHOD(GetSegmentsForStage)(/*[in]*/BSTR stage, /*[out,retval]*/IFilteredSegmentCollection** segments) override;
	STDMETHOD(GetSegmentForMemberLocation)(/*[in]*/BSTR stage, /*[in]*/Float64 location, /*[out]*/ ISegmentItem** ppLeftSegi, ISegmentItem** ppRightSegi) override;
	STDMETHOD(ReverseSegments)(/*[in]*/BSTR stage) override;
	STDMETHOD(RemoveSegment)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition) override;
	STDMETHOD(CopySegmentTo)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType fromRelPosition, /*[in]*/SegmentIndexType toRelPosition) override;
	STDMETHOD(MoveSegmentTo)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType fromRelPosition, /*[in]*/SegmentIndexType toRelPosition) override;
	STDMETHOD(InsertSegment)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition, /*[in]*/ISegment*) override;
	STDMETHOD(AddSegment)(/*[in]*/BSTR stage, /*[in]*/ISegment*) override;
	STDMETHOD(get_Segment)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition, /*[out, retval]*/ ISegment* *pVal) override;
	STDMETHOD(putref_Segment)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition, /*[in]*/ ISegment* newVal) override;
	STDMETHOD(get_SegmentCount)(/*[in]*/BSTR stage, /*[out, retval]*/ SegmentIndexType *pVal) override;
	STDMETHOD(get_SegmentLength)(/*[in]*/BSTR stage, /*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(IsEndReleased)(/*[in]*/Side side, /*[in]*/ MemberReleaseType releaseType,/*[out,retval]*/VARIANT_BOOL* pvbIsReleased) override;
	STDMETHOD(SetEndRelease)(/*[in]*/Side side, /*[in]*/ MemberReleaseType newVal) override;
	STDMETHOD(GetEndReleaseRemovalStage)(/*[in]*/Side side, /*[out]*/ BSTR* removalStage) override;
	STDMETHOD(SetEndReleaseRemovalStage)(/*[in]*/Side side,  /*[in]*/ BSTR removalStage) override;
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Length)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get__EnumElements)(/*[out, retval]*/ IEnumSegmentItem* *pVal) override;

   // CSegmentsOwner
   virtual HRESULT SetUpConnection(ISegmentItem* pCp, DWORD* pcookie) override;
   virtual void BreakConnection(ISegmentItem* pCp, DWORD cookie) override;
   virtual void OnSegmentsChanged(CSegments* psegments, BSTR stage, ChangeType change) override;

   Float64 Length() { return m_Length;}

// _ISegmentItemEvents
   STDMETHOD(OnSegmentItemChanged)(/*[in]*/ISegmentItem* SegmentItem, BSTR Stage, /*[in]*/ChangeType type) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

   // implementation
   HRESULT FinalConstruct();
   void FinalRelease();

private:
   void Init();

protected:
   CSegments* m_pSegments;
   Float64 m_Length;
   VARIANT_BOOL m_IsSymmetrical;
   long m_LeftRelease;
   CComBSTR          m_LeftReleaseRemovalStage;
   long m_RightRelease;
   CComBSTR          m_RightReleaseRemovalStage;
   VARIANT_BOOL m_bIsLinkMember; // if VARIANT_TRUE, this superstructure member is used as a link
                                 // member between distinct parts of the superstructure. This would occur
                                 // if you were modeling two simple spans with a gap between the spans
                                 // such as would occur in a precast-prestressed girder bridge.
                                 // The link members are needed to keep the LBAM and FEM models stable
                                 // but they aren't part of the real structure so they don't get loaded.
};

#endif //__SUPERSTRUCTUREMEMBER_H_
