///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2013  Washington State Department of Transportation
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
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISuperstructureMember
public:
	STDMETHOD(RemoveStage)(/*[in]*/BSTR stage);
	STDMETHOD(get_IsSymmetrical)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsSymmetrical)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(Clone)(/*[out,retval]*/ISuperstructureMember** clone);
	STDMETHOD(GetMemberSegments)(/*[in]*/BSTR stage, /*[out,retval]*/IFilteredSegmentCollection** segments);
	STDMETHOD(GetSegmentsForStage)(/*[in]*/BSTR stage, /*[out,retval]*/IFilteredSegmentCollection** segments);
	STDMETHOD(GetSegmentForMemberLocation)(/*[in]*/BSTR stage, /*[in]*/Float64 location, /*[out]*/ ISegmentItem** ppLeftSegi, ISegmentItem** ppRightSegi);
	STDMETHOD(ReverseSegments)(/*[in]*/BSTR stage);
	STDMETHOD(RemoveSegment)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition);
	STDMETHOD(CopySegmentTo)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType fromRelPosition, /*[in]*/SegmentIndexType toRelPosition);
	STDMETHOD(MoveSegmentTo)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType fromRelPosition, /*[in]*/SegmentIndexType toRelPosition);
	STDMETHOD(InsertSegment)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition, /*[in]*/ISegment*);
	STDMETHOD(AddSegment)(/*[in]*/BSTR stage, /*[in]*/ISegment*);
	STDMETHOD(get_Segment)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition, /*[out, retval]*/ ISegment* *pVal);
	STDMETHOD(putref_Segment)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition, /*[in]*/ ISegment* newVal);
	STDMETHOD(get_SegmentCount)(/*[in]*/BSTR stage, /*[out, retval]*/ SegmentIndexType *pVal);
	STDMETHOD(get_SegmentLength)(/*[in]*/BSTR stage, /*[out, retval]*/ Float64 *pVal);
	STDMETHOD(GetEndRelease)(/*[in]*/Side side, /*[out]*/ BSTR* removalStage,/*[out, retval]*/ MemberReleaseType *pVal);
	STDMETHOD(SetEndRelease)(/*[in]*/Side side,  /*[in]*/ BSTR removalStage, /*[in]*/ MemberReleaseType newVal);
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Length)(/*[in]*/ Float64 newVal);
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);  
	STDMETHOD(get__EnumElements)(/*[out, retval]*/ IEnumSegmentItem* *pVal);

   // CSegmentsOwner
   virtual HRESULT SetUpConnection(ISegmentItem* pCp, DWORD* pcookie);
   virtual void BreakConnection(ISegmentItem* pCp, DWORD cookie);
   virtual void OnSegmentsChanged(CSegments* psegments, BSTR stage, ChangeType change);
   virtual Float64 Length() { return m_Length;}

// _ISegmentItemEvents
   STDMETHOD(OnSegmentItemChanged)(/*[in]*/ISegmentItem* SegmentItem, BSTR Stage, /*[in]*/ChangeType type);

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

   // implementation
   HRESULT FinalConstruct();
   void FinalRelease();

private:
   void Init();

protected:
   CSegments* m_pSegments;
   Float64 m_Length;
   VARIANT_BOOL m_IsSymmetrical;
   MemberReleaseType m_LeftRelease;
   CComBSTR          m_LeftReleaseRemovalStage;
   MemberReleaseType m_RightRelease;
   CComBSTR          m_RightReleaseRemovalStage;

};

#endif //__SUPERSTRUCTUREMEMBER_H_
