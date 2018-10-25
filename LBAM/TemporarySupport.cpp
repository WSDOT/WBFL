///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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

// TemporarySupport.cpp : Implementation of CTemporarySupport
#include "stdafx.h"
#include "WBFLLBAM.h"
#include <WBFLComCollections.h>
#include "TemporarySupport.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemporarySupport

STDMETHODIMP CTemporarySupport::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITemporarySupport
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CTemporarySupport::CTemporarySupport():
m_Length(0.0),
m_BottomOffset(0.0),
m_Location(0.0),
m_ID(0),
m_IsSymmetrical(VARIANT_FALSE),
m_BoundaryCondition(bcFixed),
m_TopRelease(VARIANT_FALSE),
m_bOmitReaction(VARIANT_FALSE)
{
}


STDMETHODIMP CTemporarySupport::get_Location(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Location;

	return S_OK;
}

STDMETHODIMP CTemporarySupport::put_Location(Float64 newVal)
{
	if (newVal<-1.0)
      return E_INVALIDARG;

   if (newVal!=m_Location)
   {
      m_Location = newVal;
      Fire_OnTemporarySupportChanged(this, CComBSTR("*"), cgtStiffness);
   } 

	return S_OK;
}

STDMETHODIMP CTemporarySupport::get_StageRemoved(BSTR *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_StageRemoved.Copy();
	return S_OK;
}

STDMETHODIMP CTemporarySupport::put_StageRemoved(BSTR newVal)
{
   if (newVal!=m_StageRemoved)
   {
      m_StageRemoved = newVal;
      Fire_OnTemporarySupportChanged(this, CComBSTR("*"), cgtStiffness);
   }	

	return S_OK;
}


HRESULT CTemporarySupport::FinalConstruct()
{
   // segments
   m_pSegments = new CSegments(this);

   // distribution factors
   HRESULT hr = m_DistributionFactor.CoCreateInstance(CLSID_DistributionFactor);
   if (FAILED(hr))
      return hr;

   hr = CrAdvise(m_DistributionFactor, this, IID_IDistributionFactorEvents, &m_DistributionFactorCookie);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

void CTemporarySupport::FinalRelease()
{
   // destroy segments while we are still alive
   delete m_pSegments;
   m_pSegments = 0;

   // say goodbye to our df's
   ATLASSERT(!!m_DistributionFactor);
   HRESULT hr = CrUnadvise(m_DistributionFactor, this, IID_IDistributionFactorEvents, m_DistributionFactorCookie);
   ATLASSERT(SUCCEEDED(hr));

}

STDMETHODIMP CTemporarySupport::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Length;

	return S_OK;
}

STDMETHODIMP CTemporarySupport::put_Length(Float64 newVal)
{
	if (newVal<0.0)
      return E_INVALIDARG;

   if (newVal!=m_Length)
   {
      m_Length = newVal;
      Fire_OnTemporarySupportChanged(this, CComBSTR("*"), cgtStiffness);
   } 

	return S_OK;
}

STDMETHODIMP CTemporarySupport::get_BottomOffset(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_BottomOffset;

	return S_OK;
}

STDMETHODIMP CTemporarySupport::put_BottomOffset(Float64 newVal)
{
   if (newVal!=m_BottomOffset)
   {
      m_BottomOffset = newVal;
      Fire_OnTemporarySupportChanged(this, CComBSTR("*"), cgtStiffness);
   } 

	return S_OK;
}


STDMETHODIMP CTemporarySupport::get_IsSymmetrical(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_IsSymmetrical;
	return S_OK;
}

STDMETHODIMP CTemporarySupport::put_IsSymmetrical(VARIANT_BOOL newVal)
{
   if (newVal==m_IsSymmetrical)
      return S_OK;

   if (newVal==VARIANT_FALSE)
   {
      m_IsSymmetrical = newVal;
   }
   else
   {
      m_IsSymmetrical = VARIANT_TRUE;
   }

   Fire_OnTemporarySupportChanged(this, CComBSTR("*"), cgtStiffness);

	return S_OK;
}

STDMETHODIMP CTemporarySupport::get_BoundaryCondition(BoundaryConditionType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_BoundaryCondition;

	return S_OK;
}

STDMETHODIMP CTemporarySupport::put_BoundaryCondition(BoundaryConditionType newVal)
{
   bool dofire=false;

   // be on the lookout for nefarious values
   if (newVal != bcFixed && newVal != bcPinned && newVal != bcRoller)
      return E_INVALIDARG;

   if (newVal != m_BoundaryCondition)
   {
      m_BoundaryCondition = newVal;
      Fire_OnTemporarySupportChanged(this, CComBSTR("*"), cgtStiffness);
   }

	return S_OK;
}

STDMETHODIMP CTemporarySupport::get_TopRelease(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_TopRelease;

	return S_OK;
}

STDMETHODIMP CTemporarySupport::put_TopRelease(VARIANT_BOOL newVal)
{
   m_TopRelease = newVal;

   Fire_OnTemporarySupportChanged(this, CComBSTR("*"), cgtStiffness);


	return S_OK;
}

STDMETHODIMP CTemporarySupport::get_OmitReaction(VARIANT_BOOL* pbOmit)
{
   CHECK_RETVAL(pbOmit);
   *pbOmit = m_bOmitReaction;
   return S_OK;
}

STDMETHODIMP CTemporarySupport::put_OmitReaction(VARIANT_BOOL bOmit)
{
   m_bOmitReaction = bOmit;
   Fire_OnTemporarySupportChanged(this, CComBSTR("*"), cgtStiffness);
   return S_OK;
}

STDMETHODIMP CTemporarySupport::get_SegmentLength(BSTR stage, Float64 *pVal)
{
   CHECK_IN(stage);
   CHECK_RETVAL(pVal);
   try
   {
	   return m_pSegments->get_Length(stage, m_Length, pVal);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::get_DistributionFactor(IDistributionFactor **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_DistributionFactor.CopyTo(pVal);
}

STDMETHODIMP CTemporarySupport::putref_DistributionFactor(IDistributionFactor *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same object
   if ( m_DistributionFactor.IsEqualObject(newVal) )
      return S_OK;

   // first we must break our cp with old if we had one
   HRESULT hr;
   if (!!m_DistributionFactor)
   {
      hr = CrUnadvise(m_DistributionFactor, this, IID_IDistributionFactorEvents, m_DistributionFactorCookie);
      if (FAILED(hr))
         return hr;
   }

   // assign new 
   m_DistributionFactor = newVal;

   // establish cp with new 
   hr = CrAdvise(m_DistributionFactor, this, IID_IDistributionFactorEvents, &m_DistributionFactorCookie);
   if (FAILED(hr))
      return hr;

   // tell the world we've changed
   Fire_OnTemporarySupportChanged(this, CComBSTR("*"), cgtDistributionFactor);

	return S_OK;
}



STDMETHODIMP CTemporarySupport::get_SegmentCount(BSTR stage, SegmentIndexType *pVal)
{
   try
   {
   	return m_pSegments->get_Count(stage, pVal);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::get_Segment(BSTR stage, SegmentIndexType relPosition, ISegment **pVal)
{
   try
   {
   	return m_pSegments->get_Segment(stage, relPosition, pVal);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::putref_Segment(BSTR stage, SegmentIndexType relPosition, ISegment *newVal)
{
   try
   {
   	return m_pSegments->put_Segment(stage, relPosition, newVal);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::AddSegment(BSTR stage, ISegment * pSeg)
{
   try
   {
      return m_pSegments->Add(stage, pSeg);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::InsertSegment(BSTR stage, SegmentIndexType relPosition, ISegment * pSeg)
{
   try
   {
   	return m_pSegments->Insert(relPosition, stage, pSeg);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::MoveSegmentTo(BSTR stage, SegmentIndexType fromRelPosition, SegmentIndexType toRelPosition)
{
   try
   {
   	return m_pSegments->MoveTo(stage, fromRelPosition, toRelPosition);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::CopySegmentTo(BSTR stage, SegmentIndexType fromRelPosition, SegmentIndexType toRelPosition)
{
   try
   {
	   return m_pSegments->CopyTo(stage, fromRelPosition, toRelPosition);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::RemoveSegment(BSTR stage, SegmentIndexType relPosition)
{
   try
   {
	   return m_pSegments->Remove(stage, relPosition);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::ReverseSegments(BSTR stage)
{
   try
   {
	   return m_pSegments->Reverse(stage);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::GetSegmentForMemberLocation(BSTR stage, Float64 location, ISegmentItem** ppLeftSegi, ISegmentItem** ppRightSegi)
{
   try
   {
   	return m_pSegments->GetSegmentForMemberLocation(stage, m_Length, m_IsSymmetrical, location, ppLeftSegi, ppRightSegi);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::GetSegmentsForStage(BSTR stage, IFilteredSegmentCollection **ppSeg)
{
   try
   {
   	return m_pSegments->GetSegmentsForStage(stage, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::GetMemberSegments(BSTR stage, IFilteredSegmentCollection **ppSeg)
{
   try
   {
   	return m_pSegments->GetMemberSegments(stage, m_Length, m_IsSymmetrical, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptionsInContext(this, IID_ITemporarySupport);
   }
}

STDMETHODIMP CTemporarySupport::get__EnumElements(IEnumSegmentItem* *retval)
{
   typedef _CopyInterface<ISegmentItem> mycopy;
   typedef CComEnumOnSTL<IEnumSegmentItem, &IID_IEnumSegmentItem, ISegmentItem*, mycopy, CSegments> EnumType;

   CComObject<EnumType>* penum;
   HRESULT hr;
   hr = CComObject<EnumType>::CreateInstance(&penum);
   if (FAILED(hr))
      return hr;

   penum->Init(GetUnknown(), *m_pSegments);

   *retval = penum;
   (*retval)->AddRef();

   return S_OK;
}

STDMETHODIMP CTemporarySupport::get__NewEnum(IUnknown** retval)
{
   typedef _CopyInterfaceToVariant<CSegments::ItemType> mycopy;
   typedef CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, mycopy, CSegments> EnumType;

   CComObject<EnumType>* penum;
   HRESULT hr;
   hr = CComObject<EnumType>::CreateInstance(&penum);
   if (FAILED(hr))
      return hr;

   *retval = penum;
   (*retval)->AddRef();

   return S_OK;
}

STDMETHODIMP CTemporarySupport::OnSegmentItemChanged(/*[in]*/ISegmentItem* SegmentItem, BSTR stage, /*[in]*/ChangeType type)
{
   Fire_OnTemporarySupportChanged(this, stage, type);
   return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=2.0;
STDMETHODIMP CTemporarySupport::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("TemporarySupport"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      _variant_t var;
      hr = pload->get_Property(CComBSTR("Length"),&var);
      if (FAILED(hr))
         return hr;

      m_Length = var;
      var.Clear();

      hr = pload->get_Property(CComBSTR("Location"),&var);
      if (FAILED(hr))
         return hr;

      m_Location = var;
      var.Clear();

      hr = pload->get_Property(CComBSTR("ID"),&var);
      if (FAILED(hr))
         return hr;

      m_ID = var;
      var.Clear();

      hr = pload->get_Property(CComBSTR("StageRemoved"),&var);
      if (FAILED(hr))
         return hr;

      m_StageRemoved = var.bstrVal;
      var.Clear();

      hr = pload->get_Property(CComBSTR("BottomOffset"),&var);
      if (FAILED(hr))
         return hr;

      m_BottomOffset = var;
      var.Clear();

      long issym;
      hr = pload->get_Property(CComBSTR("IsSymmetrical"),&var);
      if (FAILED(hr))
         return hr;

      issym = var;
      var.Clear();
      if (issym==0)
         m_IsSymmetrical = VARIANT_FALSE;
      else
         m_IsSymmetrical = VARIANT_TRUE;

      hr = pload->get_Property(CComBSTR("BoundaryCondition"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t rel (var);
      var.Clear();
      if (rel == _bstr_t("Pinned"))
      {
         m_BoundaryCondition=bcPinned;
      }
      else if  (rel == _bstr_t("Fixed"))
      {
         m_BoundaryCondition=bcFixed;
      }
      else if  (rel == _bstr_t("Roller"))
      {
         m_BoundaryCondition=bcRoller;
      }
      else
         return STRLOAD_E_INVALIDFORMAT;
   

      var.Clear();
      hr = pload->get_Property(CComBSTR("TopRelease"),&var);
      if (FAILED(hr))
         return hr;

      m_TopRelease = var.boolVal;

      if ( ver < 2.0 )
      {
         var.Clear();
         hr = pload->get_Property(CComBSTR("OmitReaction"),&var);
         if (FAILED(hr))
            return hr;

         m_bOmitReaction = var.boolVal;
      }

      // LoadModifiers
      hr = m_LoadModifierHelper.Load(pload);
      if (FAILED(hr))
         return hr;

      // DistributionFactor
      var.Clear();
      hr = pload->get_Property(_bstr_t("DistributionFactor"),&var);
      if (FAILED(hr))
         return hr;

      // get variant into more convenient form
      CComPtr<IDistributionFactor> piDistributionFactor;
      hr = _CopyVariantToInterface<IDistributionFactor>::copy(&piDistributionFactor, &var);
      if (FAILED(hr))
         return STRLOAD_E_INVALIDFORMAT;

      hr = putref_DistributionFactor(piDistributionFactor);
      if (FAILED(hr))
         return hr;

      // segments
      m_pSegments->Load(pload);
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}


STDMETHODIMP CTemporarySupport::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("TemporarySupport"), MY_VER);

      hr = psave->put_Property(CComBSTR("Length"),_variant_t(m_Length));

      hr = psave->put_Property(CComBSTR("Location"),_variant_t(m_Location));

      hr = psave->put_Property(CComBSTR("ID"),_variant_t(m_ID));

      hr = psave->put_Property(CComBSTR("StageRemoved"),_variant_t(m_StageRemoved));

      hr = psave->put_Property(CComBSTR("BottomOffset"),_variant_t(m_BottomOffset));

      hr = psave->put_Property(CComBSTR("IsSymmetrical"),_variant_t(m_IsSymmetrical));

      _variant_t var;
      if (m_BoundaryCondition==bcFixed)
         var = "Fixed";
      else if (m_BoundaryCondition==bcPinned)
         var = "Pinned";
      else if (m_BoundaryCondition==bcRoller)
         var = "Roller";
      else
      {
         ATLASSERT(0);
         var = "Fixed";
      }

      hr = psave->put_Property(CComBSTR("BoundaryCondition"),var);

      hr = psave->put_Property(CComBSTR("TopRelease"),  _variant_t(m_TopRelease));
      hr = psave->put_Property(CComBSTR("OmitReaction"),_variant_t(m_bOmitReaction));

      // load modifiers
      hr = m_LoadModifierHelper.Save(psave);

      hr = psave->put_Property(CComBSTR("DistributionFactor"),_variant_t(m_DistributionFactor));

      m_pSegments->Save(psave);

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ITemporarySupport);
   }

   return S_OK;
}

// callback functions for segments member
HRESULT CTemporarySupport::SetUpConnection(ISegmentItem* pCp, DWORD* pcookie)
{
   HRESULT hr = CrAdvise(pCp, this, IID_ISegmentItemEvents, pcookie);
   return S_OK;
}

void CTemporarySupport::BreakConnection(ISegmentItem* pCp, DWORD cookie)
{
   CrUnadvise(pCp, this, IID_ISegmentItemEvents, cookie);
}

void CTemporarySupport::OnSegmentsChanged(CSegments* psegments, BSTR stage, ChangeType change)
{
   Fire_OnTemporarySupportChanged(this, stage, change);
}

STDMETHODIMP CTemporarySupport::OnDistributionFactorChanged(IDistributionFactor* factor)
{
   Fire_OnTemporarySupportChanged(this, CComBSTR("*"), cgtDistributionFactor);
   return S_OK;
}


STDMETHODIMP CTemporarySupport::Clone(ITemporarySupport **clone)
{

   // create a new stress point collection and fill it up
   CComObject<CTemporarySupport>* pnew;
   HRESULT hr = CComObject<CTemporarySupport>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ITemporarySupport> spsm(pnew);

   pnew->m_Length        = m_Length;
   pnew->m_Location      = m_Location;
   pnew->m_ID            = m_ID;
   pnew->m_IsSymmetrical = m_IsSymmetrical;
   pnew->m_BottomOffset  = m_BottomOffset;
   pnew->m_BoundaryCondition  = m_BoundaryCondition;
   pnew->m_StageRemoved  = m_StageRemoved;
   pnew->m_TopRelease    = m_TopRelease;
   pnew->m_bOmitReaction = m_bOmitReaction;

   pnew->m_LoadModifierHelper  = m_LoadModifierHelper;
   if (FAILED(hr))
      return hr;

   CComPtr<IDistributionFactor> new_df;
   hr = m_DistributionFactor->Clone(&new_df);
   if (FAILED(hr))
      return hr;

   hr = pnew->putref_DistributionFactor(new_df);
   if (FAILED(hr))
      return hr;
   
   hr = m_pSegments->Copy( pnew->m_pSegments );
   if (FAILED(hr))
      return hr;

   return spsm.CopyTo(clone);
}

STDMETHODIMP CTemporarySupport::RemoveStage(BSTR stage)
{
   try
   {
	   return m_pSegments->RemoveStage(stage);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CTemporarySupport::get_ID(SupportIDType *pVal)
{
	*pVal = m_ID;

	return S_OK;
}

STDMETHODIMP CTemporarySupport::put_ID(SupportIDType newVal)
{
   if (newVal!=m_ID)
   {
      m_ID = newVal;
      Fire_OnTemporarySupportChanged(this, CComBSTR("*"), cgtStiffness);
   } 

	return S_OK;
}

STDMETHODIMP CTemporarySupport::GetLoadModifier(LoadCombinationType type, Float64 *minVal, Float64 *maxVal)
{
	return m_LoadModifierHelper.GetLoadModifier(type, minVal, maxVal);
}

STDMETHODIMP CTemporarySupport::SetLoadModifier(LoadCombinationType type, Float64 minVal, Float64 maxVal)
{
   bool did_fire;
   HRESULT hr = m_LoadModifierHelper.SetLoadModifier(type, minVal, maxVal, &did_fire);
   if (FAILED(hr))
      return hr;

   if (did_fire)
      Fire_OnTemporarySupportChanged(this, CComBSTR("*"), cgtCombination);

	return S_OK;
}

