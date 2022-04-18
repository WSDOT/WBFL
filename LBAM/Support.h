///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2022  Washington State Department of Transportation
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

// Support.h : Declaration of the CSupport

#ifndef __SUPPORT_H_
#define __SUPPORT_H_

#include "resource.h"       // main symbols
#include "Segments.h"
#include "SupportCP.h"
#include "LoadModifierHelper.h"

/////////////////////////////////////////////////////////////////////////////
// CSupport
class ATL_NO_VTABLE CSupport : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSupport,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSupport, &CLSID_Support>,
	public ISupportErrorInfo,
   public IPersistImpl<CSupport>,
	public IStructuredStorage2,
	public IConnectionPointContainerImpl<CSupport>,
   public CSegmentsOwner,
	public ISupport,
	public CProxyDSupportEvents< CSupport >,
	public ISegmentItemEvents,
   public IObjectSafetyImpl<CSupport,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IDistributionFactorEvents
{
public:
	CSupport();

DECLARE_REGISTRY_RESOURCEID(IDR_SUPPORT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSupport)
	COM_INTERFACE_ENTRY(ISupport)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ISegmentItemEvents)
   COM_INTERFACE_ENTRY(IDistributionFactorEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSupport)
CONNECTION_POINT_ENTRY(IID_ISupportEvents)
END_CONNECTION_POINT_MAP()


// SupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISupport
public:
	STDMETHOD(AddAssociatedSupport)(/*[in]*/SupportIDType id) override;
   STDMETHOD(GetAssociatedSupportCount)(/*[out,retval]*/SupportIndexType* pCount) override;
   STDMETHOD(GetAssociatedSupportID)(/*[in]*/IndexType index,/*[out,retval]*/SupportIDType* pID) override;
   STDMETHOD(get_TopRelease)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_TopRelease)(/*[in]*/ VARIANT_BOOL newVal) override;
	STDMETHOD(get_DistributionFactor)(/*[out, retval]*/ IDistributionFactor* *pVal) override;
	STDMETHOD(putref_DistributionFactor)(/*[in]*/ IDistributionFactor* newVal) override;
	STDMETHOD(GetLoadModifier)(/*[in]*/ LoadCombinationType type, /*[out]*/ Float64 *minVal, /*[out]*/ Float64 *maxVal) override;
	STDMETHOD(SetLoadModifier)(/*[in]*/ LoadCombinationType type, /*[in]*/ Float64 minVal, /*[in]*/ Float64 maxVal) override;
	STDMETHOD(RemoveStage)(/*[in]*/BSTR stage) override;
	STDMETHOD(get_IsSymmetrical)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_IsSymmetrical)(/*[in]*/ VARIANT_BOOL newVal) override;
	STDMETHOD(Clone)(/*[out,retval]*/ISupport** clone) override;
	STDMETHOD(GetMemberSegments)(/*[in]*/BSTR stage, /*[out,retval]*/IFilteredSegmentCollection** segments) override;
	STDMETHOD(GetSegmentsForStage)(/*[in]*/BSTR stage, /*[out,retval]*/IFilteredSegmentCollection** segments) override;
	STDMETHOD(GetSegmentForMemberLocation)(/*[in]*/BSTR stage, /*[in]*/Float64 location, ISegmentItem** ppLeftSegi, ISegmentItem** ppRightSegi) override;
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
	STDMETHOD(get_BoundaryCondition)(/*[out, retval]*/ BoundaryConditionType *pVal) override;
	STDMETHOD(put_BoundaryCondition)(/*[in]*/ BoundaryConditionType newVal) override;
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Length)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_BottomOffset)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_BottomOffset)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get__EnumElements)(/*[out, retval]*/ IEnumSegmentItem* *pVal) override;

   // CSegmentsOwner
   virtual HRESULT SetUpConnection(ISegmentItem* pCp, DWORD* pcookie) override;
   virtual void BreakConnection(ISegmentItem* pCp, DWORD cookie) override;
   virtual void OnSegmentsChanged(CSegments* psegments, BSTR stage, ChangeType change) override;

   Float64 Length() { return m_Length;}

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

   // _ISegmentItemEvents
   STDMETHOD(OnSegmentItemChanged)(/*[in]*/ISegmentItem* SegmentItem, BSTR stage, /*[in]*/ChangeType type) override;

   // IDistributionFactorEvents
   STDMETHOD(OnDistributionFactorChanged)(IDistributionFactor* factor) override;

   // implementation
   HRESULT FinalConstruct();
   void FinalRelease();

   CSegments* m_pSegments;
   Float64 m_Length;
   Float64 m_BottomOffset;
   VARIANT_BOOL m_IsSymmetrical;
   BoundaryConditionType m_BoundaryCondition;
   VARIANT_BOOL m_TopRelease;

   CLoadModifierHelper m_LoadModifierHelper;

   CComPtr<IDistributionFactor>     m_DistributionFactor;
   DWORD                            m_DistributionFactorCookie;

   std::vector<SupportIDType> m_AssociatedSupportIDs;
};

#endif //__Support_H_
