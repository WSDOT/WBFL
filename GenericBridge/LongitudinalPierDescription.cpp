///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

// LongitudinalPierDescription.cpp : Implementation of CLongitudinalPierDescription
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "LongitudinalPierDescription.h"
#include "Segment.h"
#include <ComException.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLongitudinalPierDescription
HRESULT CLongitudinalPierDescription::FinalConstruct()
{
   m_pSegments = new CSegments(this);
   return S_OK;
}

void CLongitudinalPierDescription::FinalRelease()
{
   putref_TransactionMgr(NULL);

   // destroy segments while we are still alive
   m_pSegments->Clear();
   delete m_pSegments;
   m_pSegments = 0;
}

STDMETHODIMP CLongitudinalPierDescription::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILongitudinalPierDescription,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CLongitudinalPierDescription::Clone(ILongitudinalPierDescription* *clone)
{
   CHECK_RETOBJ(clone);
   
   CComObject<CLongitudinalPierDescription>* pClone;
   CComObject<CLongitudinalPierDescription>::CreateInstance(&pClone);
   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->SetBridge(m_pBridge);

   pClone->m_Connectivity = m_Connectivity;
   pClone->m_Height = m_Height;
   pClone->m_BaseOffset = m_BaseOffset;
   pClone->m_bFractional = m_bFractional;
   pClone->m_bstrStage = m_bstrStage;

   m_pSegments->Copy( pClone->GetSegments() );

   // Linkage isn't cloned here. Linkage has to be cloned at the Pier Collection level

   return S_OK;
}

void CLongitudinalPierDescription::RenameStageReferences(BSTR bstrOldName,BSTR bstrNewName)
{
   if (m_bstrStage == bstrOldName )
      m_bstrStage = bstrNewName;
}

void CLongitudinalPierDescription::AddDataForStage(BSTR bstrName)
{
}

void CLongitudinalPierDescription::RemoveDataForStage(BSTR bstrName)
{
}

////////////////////////////////////////////////////////////////////////
// CSegmentsOwner implementation
HRESULT CLongitudinalPierDescription::SetUpConnection(ISegmentItem* pCp, DWORD* pcookie)
{
   HRESULT hr = AdviseSegmentItem(pCp,pcookie);
   return S_OK;
}

void CLongitudinalPierDescription::BreakConnection(ISegmentItem* pCp, DWORD cookie)
{
   UnadviseSegmentItem(pCp,cookie);
}

void CLongitudinalPierDescription::OnSegmentsChanged(CSegments* psegments)
{
   Fire_OnChanged();
}

Float64 CLongitudinalPierDescription::Length()
{
   Float64 length;
   get_Length(&length);
   return length;
}

HRESULT CLongitudinalPierDescription::AdviseSegmentItem(ISegmentItem* segItem,DWORD* pdwCookie)
{
   CComPtr<ISegmentItem> pCP(segItem);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_ISegmentItemEvents, pdwCookie );
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point with Segment Item object\n");
      return hr;
   }

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CLongitudinalPierDescription::UnadviseSegmentItem(ISegmentItem* segItem,DWORD dwCookie)
{
   ATLASSERT(segItem != 0);

   //
   // Disconnection from connection point
   //

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( segItem );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_ISegmentItemEvents, &pCP );
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));
   return hr;
}

HRESULT CLongitudinalPierDescription::PutConnectivity(CLongitudinalPierDescription* pThis,ConnectivityType newVal)
{
   if ( pThis->m_Connectivity == newVal )
      return S_OK;

   pThis->m_Connectivity = newVal;
   pThis->Fire_OnChanged();
   return S_OK;
}

HRESULT CLongitudinalPierDescription::PutHeight(CLongitudinalPierDescription*pThis,Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   if ( IsEqual(pThis->m_Height,newVal) )
      return S_OK;

   pThis->m_Height = newVal;
   pThis->Fire_OnChanged();
   return S_OK;
}

HRESULT CLongitudinalPierDescription::PutBaseOffset(CLongitudinalPierDescription*pThis,Float64 newVal)
{
   if ( IsEqual(pThis->m_BaseOffset,newVal) )
      return S_OK;

   pThis->m_BaseOffset = newVal;
   pThis->Fire_OnChanged();
   return S_OK;
}

HRESULT CLongitudinalPierDescription::PutContinuityStage(CLongitudinalPierDescription* pThis,CComBSTR newVal)
{
   if ( pThis->m_bstrStage == newVal )
      return S_OK;

   // Verify the stage actually exists
   CComPtr<IStageCollection> stages;
   pThis->m_pBridge->get_Stages(&stages);

   CComPtr<IStage> stage;
   stages->Find(newVal,&stage);

   if ( stage == NULL )
      return Error(IDS_E_STAGE_NOT_FOUND,IID_ILongitudinalPierDescription,GB_E_STAGE_NOT_FOUND);

   pThis->m_bstrStage = newVal;

   pThis->Fire_OnChanged();
   return S_OK;
}

HRESULT CLongitudinalPierDescription::PutFractional(CLongitudinalPierDescription* pThis,VARIANT_BOOL bFractional)
{
   if ( pThis->m_bFractional ==  bFractional )
      return S_OK; // Do nothing, no change

   pThis->m_bFractional = bFractional;

   pThis->m_bIgnoreSegmentEvents = true;

   if ( pThis->m_bFractional == VARIANT_TRUE )
      pThis->m_pSegments->MakeFractional();
   else
      pThis->m_pSegments->MakeAbsolute();

   pThis->m_bIgnoreSegmentEvents = false;

   pThis->Fire_OnChanged();
   return S_OK;
}

HRESULT CLongitudinalPierDescription::PutSymmetrical(CLongitudinalPierDescription* pThis,VARIANT_BOOL bSymmetrical)
{
   if ( pThis->m_bSymmetrical ==  bSymmetrical )
      return S_OK; // Do nothing, no change

   pThis->m_bSymmetrical = bSymmetrical;

   pThis->Fire_OnChanged();
   return S_OK;
}

HRESULT CLongitudinalPierDescription::DoAddSegment(CLongitudinalPierDescription* pThis,CComPtr<ISegment>& segment)
{
   try
   {
      segment->putref_SegmentMeasure(pThis);
      HRESULT hr = pThis->m_pSegments->Add(segment);
      if ( FAILED(hr) )
         return hr;

      CollectionIndexType count;
      pThis->m_pSegments->get_Count(&count);

      CComPtr<ISegment> s;
      pThis->m_pSegments->get_Segment(count-1,&s);

      CComQIPtr<ISupportTransactions> supTxn(s);
      if ( supTxn )
         supTxn->putref_TransactionMgr(pThis->m_TxnMgr);

      return S_OK;
   }
   catch(...)
   {
      return DealWithExceptions(pThis, IID_ILongitudinalPierDescription);
   }
}

HRESULT CLongitudinalPierDescription::UndoAddSegment(CLongitudinalPierDescription* pThis,CComPtr<ISegment>& segment)
{
   CollectionIndexType nSegments;
   pThis->m_pSegments->get_Count(&nSegments);
   try
   {
      CComPtr<ISegment> seg;
      pThis->m_pSegments->get_Segment(nSegments-1,&seg);
      seg->putref_SegmentMeasure(NULL);
      return pThis->m_pSegments->Remove(nSegments-1);
   }
   catch(...)
   {
      return DealWithExceptions(pThis, IID_ILongitudinalPierDescription);
   }
}

HRESULT CLongitudinalPierDescription::DoInsertSegment(CLongitudinalPierDescription* pThis,CollectionIndexType& idx,CComPtr<ISegment>& segment)
{
   try
   {
      segment->putref_SegmentMeasure(pThis);
      return pThis->m_pSegments->Insert(idx,segment);
   }
   catch(...)
   {
      return DealWithExceptions(pThis, IID_ILongitudinalPierDescription);
   }
}

HRESULT CLongitudinalPierDescription::UndoInsertSegment(CLongitudinalPierDescription* pThis,CollectionIndexType& idx,CComPtr<ISegment>& segment)
{
   try
   {
      CComPtr<ISegment> seg;
      pThis->m_pSegments->get_Segment(idx,&seg);
      seg->putref_SegmentMeasure(NULL);
      return pThis->m_pSegments->Remove(idx);
   }
   catch(...)
   {
      return DealWithExceptions(pThis, IID_ILongitudinalPierDescription);
   }
}

HRESULT CLongitudinalPierDescription::DoMoveSegment(CLongitudinalPierDescription* pThis,CollectionIndexType& fromIdx,CollectionIndexType& toIdx)
{
   try
   {
   	return pThis->m_pSegments->MoveTo(fromIdx,toIdx);
   }
   catch(...)
   {
      return DealWithExceptions(pThis, IID_ILongitudinalPierDescription);
   }
}

HRESULT CLongitudinalPierDescription::UndoMoveSegment(CLongitudinalPierDescription* pThis,CollectionIndexType& fromIdx,CollectionIndexType& toIdx)
{
   try
   {
   	return pThis->m_pSegments->MoveTo(toIdx,fromIdx);
   }
   catch(...)
   {
      return DealWithExceptions(pThis, IID_ILongitudinalPierDescription);
   }
}

HRESULT CLongitudinalPierDescription::DoCopySegment(CLongitudinalPierDescription* pThis,CollectionIndexType& fromIdx,CollectionIndexType& toIdx)
{
   try
   {
   	return pThis->m_pSegments->CopyTo(fromIdx,toIdx);
   }
   catch(...)
   {
      return DealWithExceptions(pThis, IID_ILongitudinalPierDescription);
   }
}

HRESULT CLongitudinalPierDescription::UndoCopySegment(CLongitudinalPierDescription* pThis,CollectionIndexType& fromIdx,CollectionIndexType& toIdx)
{
   try
   {
   	return pThis->m_pSegments->Remove(toIdx);
   }
   catch(...)
   {
      return DealWithExceptions(pThis, IID_ILongitudinalPierDescription);
   }
}

HRESULT CLongitudinalPierDescription::DoRemoveSegment(CLongitudinalPierDescription* pThis,REMOVESEGMENT& value)
{
   try
   {
      // Save the segment that is about to be removed for Undo
      pThis->m_pSegments->get_Segment(value.idx,&value.segment);

      CComQIPtr<ISupportTransactions> supTxn(value.segment);
      if ( supTxn )
         supTxn->putref_TransactionMgr(NULL);

	   return pThis->m_pSegments->Remove(value.idx);
   }
   catch(...)
   {
      return DealWithExceptions(pThis, IID_ILongitudinalPierDescription);
   }
}

HRESULT CLongitudinalPierDescription::UndoRemoveSegment(CLongitudinalPierDescription* pThis,REMOVESEGMENT& value)
{
   try
   {
	   return pThis->m_pSegments->Insert(value.idx,value.segment);
   }
   catch(...)
   {
      return DealWithExceptions(pThis, IID_ILongitudinalPierDescription);
   }
}

HRESULT CLongitudinalPierDescription::DoRemoveSegments(CLongitudinalPierDescription* pThis,REMOVESEGMENTS& data)
{
   try
   {
      // Save segments for a later undo
      HRESULT hr = pThis->m_pSegments->GetSegments(&data.segments);
      if ( FAILED(hr) )
         return hr;

      CComPtr<IEnumSegment> enumSegments;
      data.segments->get__EnumElements(&enumSegments);
      CComPtr<ISegment> segment;
      while ( enumSegments->Next(1,&segment,0) != S_FALSE )
      {
         CComQIPtr<ISupportTransactions> supTxn(segment);
         if ( supTxn )
            supTxn->putref_TransactionMgr(NULL);

         segment.Release();
      }

      return pThis->m_pSegments->RemoveSegments();
   }
   catch(...)
   {
      return DealWithExceptions(pThis, IID_ILongitudinalPierDescription);
   }
}

HRESULT CLongitudinalPierDescription::UndoRemoveSegments(CLongitudinalPierDescription* pThis,REMOVESEGMENTS& data)
{
   CComPtr<IEnumSegment> enumSegment;
   data.segments->get__EnumElements(&enumSegment);
   CComPtr<ISegment> segment;
   while( enumSegment->Next(1,&segment,NULL) != S_FALSE )
   {
      pThis->m_pSegments->Add(segment);

      CollectionIndexType nSeg;
      pThis->m_pSegments->get_Count(&nSeg);

      CComPtr<ISegment> s;
      pThis->m_pSegments->get_Segment(nSeg-1,&s);

      CComQIPtr<ISupportTransactions> supTxn(s);
      if ( supTxn )
         supTxn->putref_TransactionMgr(pThis->m_TxnMgr);

      segment.Release();
   }

   return S_OK;
}

HRESULT CLongitudinalPierDescription::DoReverseSegments(CLongitudinalPierDescription* pThis)
{
   return pThis->m_pSegments->Reverse();
}

//////////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CLongitudinalPierDescription::putref_TransactionMgr(ITransactionMgr* txnMgr)
{
   // When the transaction server is set, set it on all of the segments
   CSegments::iterator iter;
   for ( iter = m_pSegments->begin(); iter != m_pSegments->end(); iter++ )
   {
      CComPtr<ISegmentItem> item = *iter;
      CComPtr<ISegment> seg;
      item->get_Segment(&seg);

      CComQIPtr<ISupportTransactions> supTxn(seg);
      if ( supTxn )
         supTxn->putref_TransactionMgr(txnMgr);
   }

   return ISupportTransactionsImpl::putref_TransactionMgr(txnMgr);
}

//////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CLongitudinalPierDescription::IsFractional()
{
   VARIANT_BOOL bFractional;
   get_Fractional(&bFractional);
   return ( bFractional == VARIANT_TRUE ? S_OK : S_FALSE );
}

//////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CLongitudinalPierDescription::get_Pier(IPier* *pier)
{
   CHECK_RETOBJ(pier);

   (*pier) = m_pPier;
   (*pier)->AddRef();

   return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::get_Fractional(VARIANT_BOOL* bFractional)
{
   CHECK_RETVAL(bFractional);
   *bFractional = m_bFractional;
	return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::put_Fractional(VARIANT_BOOL bFractional)
{
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CLongitudinalPierDescription,VARIANT_BOOL,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditFractionalTxn;
      CComObject<CEditFractionalTxn>* pTxn;
      CComObject<CEditFractionalTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Fractional Measure"),&PutFractional,m_bFractional,bFractional);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutFractional(this,bFractional);
   }

   ATLASSERT(FALSE); // Should never get here!!!!
   return E_FAIL;
}

STDMETHODIMP CLongitudinalPierDescription::get_Symmetrical(VARIANT_BOOL* bSymmetrical)
{
   CHECK_RETVAL(bSymmetrical);
   *bSymmetrical = m_bSymmetrical;

	return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::put_Symmetrical(VARIANT_BOOL bSymmetrical)
{
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CLongitudinalPierDescription,VARIANT_BOOL,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditSymmetricalTxn;
      CComObject<CEditSymmetricalTxn>* pTxn;
      CComObject<CEditSymmetricalTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Symmetrical Segments"),&PutSymmetrical,m_bSymmetrical,bSymmetrical);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutSymmetrical(this,bSymmetrical);
   }

   ATLASSERT(FALSE); // Should never get here!!!!
   return E_FAIL;
}

STDMETHODIMP CLongitudinalPierDescription::get_Connectivity(ConnectivityType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Connectivity;

	return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::put_Connectivity(ConnectivityType newVal)
{
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CLongitudinalPierDescription,ConnectivityType,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditConnectivityTxn;
      CComObject<CEditConnectivityTxn>* pTxn;
      CComObject<CEditConnectivityTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Change connectivity"),&PutConnectivity,m_Connectivity,newVal);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutConnectivity(this,newVal);
   }

   ATLASSERT(FALSE); // Should never get here!!!!
   return E_FAIL;
}

STDMETHODIMP CLongitudinalPierDescription::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Height;

	return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::put_Height(Float64 newVal)
{
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CLongitudinalPierDescription,Float64,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditHeightTxn;
      CComObject<CEditHeightTxn>* pTxn;
      CComObject<CEditHeightTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Change Height"),&PutHeight,m_Height,newVal);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutHeight(this,newVal);
   }

   ATLASSERT(FALSE); // Should never get here!!!!
   return E_FAIL;
}

STDMETHODIMP CLongitudinalPierDescription::get_BaseOffset(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_BaseOffset;

	return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::put_BaseOffset(Float64 newVal)
{
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CLongitudinalPierDescription,Float64,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditBaseOffsetTxn;
      CComObject<CEditBaseOffsetTxn>* pTxn;
      CComObject<CEditBaseOffsetTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Change BaseOffset"),&PutBaseOffset,m_BaseOffset,newVal);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutBaseOffset(this,newVal);
   }

   ATLASSERT(FALSE); // Should never get here!!!!
   return E_FAIL;
}

STDMETHODIMP CLongitudinalPierDescription::get_Length(Float64* value)
{
   CHECK_RETVAL(value);

   if ( m_Connectivity == ctRoller || m_Connectivity == ctPinned )
      *value = 0.0;
   else
      *value = sqrt(m_Height*m_Height + m_BaseOffset*m_BaseOffset);

   return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::get_ContinuityStage(BSTR* stage)
{
   CHECK_RETSTRING(stage);
   
   *stage = m_bstrStage.Copy();

   return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::put_ContinuityStage(BSTR stage)
{
   if ( m_TxnMgr )
   {
      typedef CEditValueTransaction<CLongitudinalPierDescription,CComBSTR,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CEditContinuityStageTxn;
      CComObject<CEditContinuityStageTxn>* pTxn;
      CComObject<CEditContinuityStageTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Change Continuity Stage"),&PutContinuityStage,m_bstrStage,stage);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return PutContinuityStage(this,stage);
   }

   ATLASSERT(FALSE); // Should never get here!!!!
   return E_FAIL;
}

STDMETHODIMP CLongitudinalPierDescription::AddSegment(ISegment* segment)
{
   if ( m_TxnMgr )
   {
      typedef CActionTransaction1<CLongitudinalPierDescription,CComPtr<ISegment>,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CAddSegmentTxn;
      CComObject<CAddSegmentTxn>* pTxn;
      CComObject<CAddSegmentTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Add Segment"),&DoAddSegment,&UndoAddSegment,CComPtr<ISegment>(segment));

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return DoAddSegment(this,CComPtr<ISegment>(segment));
   }

   return E_FAIL;
}


STDMETHODIMP CLongitudinalPierDescription::InsertSegment(CollectionIndexType idx,ISegment* segment)
{
   if ( m_TxnMgr )
   {
      typedef CActionTransaction2<CLongitudinalPierDescription,CollectionIndexType,CComPtr<ISegment>,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CInsertSegmentTxn;
      CComObject<CInsertSegmentTxn>* pTxn;
      CComObject<CInsertSegmentTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Insert Segment"),&DoInsertSegment,&UndoInsertSegment,idx,CComPtr<ISegment>(segment));

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return DoInsertSegment(this,idx,CComPtr<ISegment>(segment));
   }

   return E_FAIL;
}

STDMETHODIMP CLongitudinalPierDescription::MoveSegmentTo(CollectionIndexType fromIdx, CollectionIndexType toIdx)
{
   if ( m_TxnMgr )
   {
      typedef CActionTransaction2<CLongitudinalPierDescription,CollectionIndexType,CollectionIndexType,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CMoveSegmentTxn;
      CComObject<CMoveSegmentTxn>* pTxn;
      CComObject<CMoveSegmentTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Move Segment"),&DoMoveSegment,&UndoMoveSegment,fromIdx,toIdx);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return DoMoveSegment(this,fromIdx,toIdx);
   }

   return E_FAIL;
}

STDMETHODIMP CLongitudinalPierDescription::CopySegmentTo(CollectionIndexType fromIdx, CollectionIndexType toIdx)
{
   if ( m_TxnMgr )
   {
      typedef CActionTransaction2<CLongitudinalPierDescription,CollectionIndexType,CollectionIndexType,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CCopySegmentTxn;
      CComObject<CCopySegmentTxn>* pTxn;
      CComObject<CCopySegmentTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Copy Segment"),&DoCopySegment,&UndoCopySegment,fromIdx,toIdx);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return DoCopySegment(this,fromIdx,toIdx);
   }

   return E_FAIL;
}

STDMETHODIMP CLongitudinalPierDescription::RemoveSegment(CollectionIndexType idx)
{
   REMOVESEGMENT data;
   data.idx = idx;

   if ( m_TxnMgr )
   {
      typedef CActionTransaction1<CLongitudinalPierDescription,REMOVESEGMENT,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CRemoveSegmentTxn;
      CComObject<CRemoveSegmentTxn>* pTxn;
      CComObject<CRemoveSegmentTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Remove Segment"),&DoRemoveSegment,&UndoRemoveSegment,data);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return DoRemoveSegment(this,data);
   }

   return E_FAIL;
}

STDMETHODIMP CLongitudinalPierDescription::RemoveSegments()
{
   REMOVESEGMENTS data;

   if ( m_TxnMgr )
   {
      typedef CActionTransaction1<CLongitudinalPierDescription,REMOVESEGMENTS,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CRemoveSegmentsTxn;
      CComObject<CRemoveSegmentsTxn>* pTxn;
      CComObject<CRemoveSegmentsTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Remove Segments"),&DoRemoveSegments,&UndoRemoveSegments,data);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return DoRemoveSegments(this,data);
   }

   return E_FAIL;
}

STDMETHODIMP CLongitudinalPierDescription::GetMemberSegments(IFilteredSegmentCollection **ppSeg)
{
   try
   {
   	return m_pSegments->GetMemberSegments(Length(), m_bSymmetrical, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILongitudinalPierDescription);
   }
}

STDMETHODIMP CLongitudinalPierDescription::GetSegmentForMemberLocation(Float64 location, Float64* dist,ISegmentItem **ppSeg)
{
   try
   {
   	return m_pSegments->GetSegmentForMemberLocation(Length(), m_bSymmetrical, location, dist, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILongitudinalPierDescription);
   }
}

STDMETHODIMP CLongitudinalPierDescription::ReverseSegments()
{
   if ( m_TxnMgr )
   {
      typedef CActionTransaction<CLongitudinalPierDescription,VARIANT_TRUE,VARIANT_FALSE,&LIBID_WBFLGenericBridge> CReverseSegmentsTxn;
      CComObject<CReverseSegmentsTxn>* pTxn;
      CComObject<CReverseSegmentsTxn>::CreateInstance(&pTxn);
      pTxn->Init(this,_T("Reverse Segment"),&DoReverseSegments,&DoReverseSegments);

      return m_TxnMgr->Execute(pTxn);
   }
   else
   {
      return DoReverseSegments(this);
   }

   return E_FAIL;
}

STDMETHODIMP CLongitudinalPierDescription::get_SegmentLength(Float64 *pVal)
{
   try
   {
	   return m_pSegments->get_Length(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILongitudinalPierDescription);
   }
}

STDMETHODIMP CLongitudinalPierDescription::get_SegmentCount(CollectionIndexType *pVal)
{
   try
   {
      return m_pSegments->get_Count(pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILongitudinalPierDescription);
   }
}

STDMETHODIMP CLongitudinalPierDescription::get_Segment(CollectionIndexType idx, ISegment **pVal)
{
   try
   {
   	return m_pSegments->get_Segment(idx, pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILongitudinalPierDescription);
   }
}


////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CLongitudinalPierDescription::Load(IStructuredLoad2* load)
{
   CComVariant var;
   load->BeginUnit(CComBSTR("LongitudinalPierDescription"));

   load->get_Property(CComBSTR("BaseOffset"),&var);
   m_BaseOffset = var.dblVal;

   load->get_Property(CComBSTR("Height"),&var);
   m_Height = var.dblVal;

   load->get_Property(CComBSTR("Fractional"),&var);
   m_bFractional = var.boolVal;

   load->get_Property(CComBSTR("Symmetrical"),&var);
   m_bSymmetrical = var.boolVal;

   load->get_Property(CComBSTR("Connectivity"),&var);
   m_Connectivity = (ConnectivityType)var.lVal;

   load->get_Property(CComBSTR("ContinuityStage"),&var);
   m_bstrStage = var.bstrVal;

   m_pSegments->Load(load);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("LongitudinalPierDescription"),1.0);

   save->put_Property(CComBSTR("BaseOffset"),CComVariant(m_BaseOffset));
   save->put_Property(CComBSTR("Height"),CComVariant(m_Height));
   save->put_Property(CComBSTR("Fractional"),CComVariant(m_bFractional));
   save->put_Property(CComBSTR("Symmetrical"),CComVariant(m_bSymmetrical));
   save->put_Property(CComBSTR("Connectivity"),CComVariant(m_Connectivity));
   save->put_Property(CComBSTR("ContinuityStage"),CComVariant(m_bstrStage));

   m_pSegments->Save(save);

   save->EndUnit();
   return S_OK;
}


#if defined _DEBUG
void CLongitudinalPierDescription::AssertValid() const
{
   ATLASSERT(m_pPier != NULL);
}
#endif // _DEBUG