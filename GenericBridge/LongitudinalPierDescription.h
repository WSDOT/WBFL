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

// LongitudinalPierDescription.h : Declaration of the CLongitudinalPierDescription

#ifndef __LONGITUDINALPIERDESCRIPTION_H_
#define __LONGITUDINALPIERDESCRIPTION_H_

#include "resource.h"       // main symbols
#include "TxnMgrImpl.h"
#include "Segments.h"
#include "GenericBridgeCP.h"

/////////////////////////////////////////////////////////////////////////////
// CLongitudinalPierDescription
class ATL_NO_VTABLE CLongitudinalPierDescription : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLongitudinalPierDescription, &CLSID_LongitudinalPierDescription>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CLongitudinalPierDescription,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ISupportTransactionsImpl,
	public IConnectionPointContainerImpl<CLongitudinalPierDescription>,
   public ILongitudinalPierDescription,
   public IStructuredStorage2,
   public ISegmentItemEvents,
   public ISegmentMeasure,
   public CProxyDLongitudinalPierDescriptionEvents< CLongitudinalPierDescription >,
   public CSegmentsOwner
{
public:
   friend CLongitudinalPierDescription; // Friend of self for easy cloning

	CLongitudinalPierDescription()
	{
      m_Connectivity = ctPinned;
      m_Height = 1.0;
      m_BaseOffset = 0.0;
      m_bstrStage = "Stage 1";
      m_bFractional = VARIANT_FALSE;
      m_bSymmetrical = VARIANT_FALSE;
      m_bIgnoreSegmentEvents = false;

      m_pPier = NULL;
	}
 
   HRESULT FinalConstruct();
   void FinalRelease();

   void SetPier(IPier* pier)
   {
      m_pPier = pier;
   }

   void SetBridge(IGenericBridge* pBridge)
   {
      m_pBridge = pBridge;
      m_pSegments->SetBridge(pBridge);
   }

   CSegments* GetSegments() { return m_pSegments; }

   // Implemented privately for new... can easily move to the COM interface
   STDMETHOD(Clone)(ILongitudinalPierDescription* *clone);

   void RenameStageReferences(BSTR bstrOldName,BSTR bstrNewName);
   void AddDataForStage(BSTR bstrName);
   void RemoveDataForStage(BSTR bstrName);

#if defined _DEBUG
   void AssertValid() const;
#endif // _DEBUG

DECLARE_REGISTRY_RESOURCEID(IDR_LONGITUDINALPIERDESCRIPTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLongitudinalPierDescription)
   COM_INTERFACE_ENTRY(ILongitudinalPierDescription)

	COM_INTERFACE_ENTRY(ISupportErrorInfo)

   COM_INTERFACE_ENTRY(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ISupportTransactions)

   COM_INTERFACE_ENTRY(ISegmentItemEvents)
   COM_INTERFACE_ENTRY(ISegmentMeasure)

   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IObjectSafety)

	COM_INTERFACE_ENTRY(IStructuredStorage2)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLongitudinalPierDescription)
CONNECTION_POINT_ENTRY(IID_ILongitudinalPierDescriptionEvents)
END_CONNECTION_POINT_MAP()

public:
   struct REMOVESEGMENT
   {
      CComBSTR bstrStage;
      SegmentIndexType idx;
      CComPtr<ISegment> segment;
   };

   struct REMOVESEGMENTS
   {
      CComBSTR bstrStage;
      CComPtr<IFilteredSegmentCollection> segments;
   };

   static HRESULT PutConnectivity(CLongitudinalPierDescription* pThis,ConnectivityType newVal);
   static HRESULT PutHeight(CLongitudinalPierDescription* pThis,Float64 newVal);
   static HRESULT PutBaseOffset(CLongitudinalPierDescription* pThis,Float64 newVal);
   static HRESULT PutContinuityStage(CLongitudinalPierDescription* pThis,CComBSTR newVal);
   static HRESULT PutFractional(CLongitudinalPierDescription* pThis,VARIANT_BOOL bFractional);
   static HRESULT PutSymmetrical(CLongitudinalPierDescription* pThis,VARIANT_BOOL bSymmetrical);
   static HRESULT DoAddSegment(CLongitudinalPierDescription* pThis,CComPtr<ISegment>& segment);
   static HRESULT UndoAddSegment(CLongitudinalPierDescription* pThis,CComPtr<ISegment>& segment);
   static HRESULT DoInsertSegment(CLongitudinalPierDescription* pThis,CollectionIndexType& idx,CComPtr<ISegment>& segment);
   static HRESULT UndoInsertSegment(CLongitudinalPierDescription* pThis,CollectionIndexType& idx,CComPtr<ISegment>& segment);
   static HRESULT DoMoveSegment(CLongitudinalPierDescription* pThis,CollectionIndexType& fromIdx,CollectionIndexType& toIdx);
   static HRESULT UndoMoveSegment(CLongitudinalPierDescription* pThis,CollectionIndexType& fromIdx,CollectionIndexType& toIdx);
   static HRESULT DoRemoveSegment(CLongitudinalPierDescription* pThis,REMOVESEGMENT& value);
   static HRESULT UndoRemoveSegment(CLongitudinalPierDescription* pThis,REMOVESEGMENT& value);
   static HRESULT DoRemoveSegments(CLongitudinalPierDescription* pThis,REMOVESEGMENTS& value);
   static HRESULT UndoRemoveSegments(CLongitudinalPierDescription* pThis,REMOVESEGMENTS& value);
   static HRESULT DoCopySegment(CLongitudinalPierDescription* pThis,CollectionIndexType& fromIdx,CollectionIndexType& toIdx);
   static HRESULT UndoCopySegment(CLongitudinalPierDescription* pThis,CollectionIndexType& fromIdx,CollectionIndexType& toIdx);
   static HRESULT DoReverseSegments(CLongitudinalPierDescription* pThis);

private:
   ConnectivityType m_Connectivity;
   Float64 m_Height;
   Float64 m_BaseOffset;
   CComBSTR m_bstrStage;
   VARIANT_BOOL m_bFractional;
   VARIANT_BOOL m_bSymmetrical;
   bool m_bIgnoreSegmentEvents;
   IPier* m_pPier; // This is a weak reference to avoid a circular reference
   IGenericBridge* m_pBridge; // This is a weak referenece to avoid a circular referece

   HRESULT AdviseSegmentItem(ISegmentItem* segItem,DWORD* pdwCookie);
   HRESULT UnadviseSegmentItem(ISegmentItem* segItem,DWORD dwCookie);

   CSegments* m_pSegments;

public:

// virtual methods for CSegmentsOwner
   virtual HRESULT SetUpConnection(ISegmentItem* pCp, DWORD* pcookie);
   virtual void BreakConnection(ISegmentItem* pCp, DWORD cookie);
   virtual void OnSegmentsChanged(CSegments* psegments);
   virtual Float64 Length();


// ISupportsErrorInfo
public:
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISupportTransactions
public:
   STDMETHOD(putref_TransactionMgr)(ITransactionMgr* txnMgr);

// ISegmentMeasure
public:
   STDMETHOD(IsFractional)();

// ILongitudinalPierDescription
public:
   STDMETHOD(get_Pier)(/*[out,retval]*/IPier* *pier);
   STDMETHOD(get_Fractional)(/*[out,retval]*/ VARIANT_BOOL* bFractional);
	STDMETHOD(get_Symmetrical)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Symmetrical)(/*[in]*/ VARIANT_BOOL newVal);
   STDMETHOD(put_Fractional)(/*[in]*/ VARIANT_BOOL bFractional);
	STDMETHOD(get_Connectivity)(/*[out, retval]*/ ConnectivityType *pVal);
	STDMETHOD(put_Connectivity)(/*[in]*/ ConnectivityType newVal);
   STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Height)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_BaseOffset)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_BaseOffset)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_Length)(/*[out,retval]*/ Float64* value);
   STDMETHOD(get_ContinuityStage)(/*[out,retval]*/ BSTR* stage);
   STDMETHOD(put_ContinuityStage)(/*[in]*/ BSTR stage);

   STDMETHOD(AddSegment)(/*[in]*/ISegment* segment);
   STDMETHOD(InsertSegment)(/*[in]*/ SegmentIndexType idx,/*[in]*/ISegment* segment);
	STDMETHOD(MoveSegmentTo)(/*[in]*/ SegmentIndexType fromIdx,/*[in]*/ SegmentIndexType toIdx);
	STDMETHOD(CopySegmentTo)(/*[in]*/ SegmentIndexType fromIdx, /*[in]*/ SegmentIndexType toIdx);
	STDMETHOD(RemoveSegment)(/*[in]*/ SegmentIndexType idx);
	STDMETHOD(RemoveSegments)();
	STDMETHOD(GetMemberSegments)(/*[out,retval]*/ IFilteredSegmentCollection **ppSeg);
	STDMETHOD(GetSegmentForMemberLocation)(/*[in]*/ Float64 Location,/*[out]*/Float64* dist,/*[out]*/ ISegmentItem **ppSeg);
	STDMETHOD(ReverseSegments)();
   STDMETHOD(get_SegmentCount)(/*[out,retval]*/ SegmentIndexType* count);
   STDMETHOD(get_SegmentLength)(/*[out,retval]*/ Float64* value);
   STDMETHOD(get_Segment)(/*[in]*/ SegmentIndexType idx,/*[out,retval]*/ ISegment* *segment);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);

// ISegmentItemEvents
public:
	STDMETHOD(OnSegmentItemChanged)(ISegmentItem * segItem)
	{
      if ( m_bIgnoreSegmentEvents )
         return S_OK;

      Fire_OnChanged();
		return S_OK;
	}
};

#endif //__LONGITUDINALPIERDESCRIPTION_H_
