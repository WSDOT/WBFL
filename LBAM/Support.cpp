///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2019  Washington State Department of Transportation
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

// ISupport.cpp : Implementation of CISupport
#include "stdafx.h"
#include "WBFLLBAM.h"
#include <WBFLComCollections.h>
#include "Support.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CISupport

STDMETHODIMP CSupport::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISupport
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
} 

CSupport::CSupport():
m_Length(0.0),
m_BottomOffset(0.0),
m_IsSymmetrical(VARIANT_FALSE),
m_BoundaryCondition(bcPinned),
m_TopRelease(VARIANT_FALSE)
{
}

HRESULT CSupport::FinalConstruct()
{
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

void CSupport::FinalRelease()
{
   // destroy segments while we are still alive
   delete m_pSegments;
   m_pSegments = 0;

   // say goodbye to our df's
   ATLASSERT(!!m_DistributionFactor);
   HRESULT hr = CrUnadvise(m_DistributionFactor, this, IID_IDistributionFactorEvents, m_DistributionFactorCookie);
   ATLASSERT(SUCCEEDED(hr));

}

STDMETHODIMP CSupport::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

	*pVal = m_Length;

	return S_OK;
}

STDMETHODIMP CSupport::put_Length(Float64 newVal)
{
	if (newVal<0.0)
      return E_INVALIDARG;

   if (newVal!=m_Length)
   {
      m_Length = newVal;
      Fire_OnSupportChanged(this, CComBSTR("*"), cgtStiffness);
   } 

	return S_OK;
}

STDMETHODIMP CSupport::get_BottomOffset(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_BottomOffset;

	return S_OK;
}

STDMETHODIMP CSupport::put_BottomOffset(Float64 newVal)
{
   if (newVal!=m_BottomOffset)
   {
      m_BottomOffset = newVal;
      Fire_OnSupportChanged(this, CComBSTR("*"), cgtStiffness);
   } 

	return S_OK;
}


STDMETHODIMP CSupport::get_IsSymmetrical(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_IsSymmetrical;
	return S_OK;
}

STDMETHODIMP CSupport::put_IsSymmetrical(VARIANT_BOOL newVal)
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

   Fire_OnSupportChanged(this, CComBSTR("*"), cgtStiffness);

	return S_OK;
}

STDMETHODIMP CSupport::get_BoundaryCondition(BoundaryConditionType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_BoundaryCondition;

	return S_OK;
}

STDMETHODIMP CSupport::put_BoundaryCondition(BoundaryConditionType newVal)
{
   bool dofire=false;

   // be on the lookout for nefarious values
   if (newVal != bcFixed && newVal != bcPinned && newVal != bcRoller)
      return E_INVALIDARG;

   if (newVal != m_BoundaryCondition)
   {
      m_BoundaryCondition = newVal;
      Fire_OnSupportChanged(this, CComBSTR("*"), cgtStiffness);
   }

	return S_OK;
}


STDMETHODIMP CSupport::get_DistributionFactor(IDistributionFactor **pVal)
{
   CHECK_RETOBJ(pVal);
	return m_DistributionFactor.CopyTo(pVal);
}

STDMETHODIMP CSupport::putref_DistributionFactor(IDistributionFactor *newVal)
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
   Fire_OnSupportChanged(this, CComBSTR("*"), cgtDistributionFactor);

	return S_OK;
}

STDMETHODIMP CSupport::AddAssociatedSupport(/*[in]*/SupportIDType id)
{
   m_AssociatedSupportIDs.push_back(id);
   return S_OK;
}

STDMETHODIMP CSupport::GetAssociatedSupportCount(/*[out,retval]*/SupportIndexType* pCount)
{
   CHECK_RETVAL(pCount);
   *pCount = m_AssociatedSupportIDs.size();
   return S_OK;
}

STDMETHODIMP CSupport::GetAssociatedSupportID(/*[in]*/IndexType index,/*[out,retval]*/SupportIDType* pID)
{
   CHECK_RETVAL(pID);
   if ( index == INVALID_INDEX || m_AssociatedSupportIDs.size() <= index )
      return E_INVALIDARG;

   *pID = m_AssociatedSupportIDs[index];
   return S_OK;
}

STDMETHODIMP CSupport::get_TopRelease(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_TopRelease;

	return S_OK;
}

STDMETHODIMP CSupport::put_TopRelease(VARIANT_BOOL newVal)
{
   m_TopRelease = newVal;

   Fire_OnSupportChanged(this, CComBSTR("*"), cgtStiffness);

	return S_OK;
}

STDMETHODIMP CSupport::get_SegmentLength(BSTR stage, Float64 *pVal)
{
   try
   {
	   return m_pSegments->get_Length(stage, m_Length, pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::get_SegmentCount(BSTR stage, SegmentIndexType *pVal)
{
   try
   {
   	return m_pSegments->get_Count(stage, pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::get_Segment(BSTR stage, SegmentIndexType relPosition, ISegment **pVal)
{
   try
   {
   	return m_pSegments->get_Segment(stage, relPosition, pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::putref_Segment(BSTR stage, SegmentIndexType relPosition, ISegment *newVal)
{
   try
   {
   	return m_pSegments->put_Segment(stage, relPosition, newVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::AddSegment(BSTR stage, ISegment * pSeg)
{
   try
   {
      return m_pSegments->Add(stage, pSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::InsertSegment(BSTR stage, SegmentIndexType relPosition, ISegment * pSeg)
{
   try
   {
   	return m_pSegments->Insert(relPosition, stage, pSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::MoveSegmentTo(BSTR stage, SegmentIndexType fromRelPosition, SegmentIndexType toRelPosition)
{
   try
   {
   	return m_pSegments->MoveTo(stage, fromRelPosition, toRelPosition);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::CopySegmentTo(BSTR stage, SegmentIndexType fromRelPosition, SegmentIndexType toRelPosition)
{
   try
   {
	   return m_pSegments->CopyTo(stage, fromRelPosition, toRelPosition);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::RemoveSegment(BSTR stage, SegmentIndexType relPosition)
{
   try
   {
	   return m_pSegments->Remove(stage, relPosition);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::ReverseSegments(BSTR stage)
{
   try
   {
	   return m_pSegments->Reverse(stage);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::GetSegmentForMemberLocation(BSTR stage, Float64 location, ISegmentItem** ppLeftSegi, ISegmentItem** ppRightSegi)
{
   try
   {
   	return m_pSegments->GetSegmentForMemberLocation(stage, m_Length, m_IsSymmetrical, location, ppLeftSegi, ppRightSegi);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::GetSegmentsForStage(BSTR stage, IFilteredSegmentCollection **ppSeg)
{
   try
   {
   	return m_pSegments->GetSegmentsForStage(stage, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::GetMemberSegments(BSTR stage, IFilteredSegmentCollection **ppSeg)
{
   try
   {
   	return m_pSegments->GetMemberSegments(stage, m_Length, m_IsSymmetrical, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }
}

STDMETHODIMP CSupport::get__EnumElements(IEnumSegmentItem* *retval)
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

STDMETHODIMP CSupport::OnSegmentItemChanged(/*[in]*/ISegmentItem* SegmentItem, BSTR stage, /*[in]*/ChangeType type)
{
   Fire_OnSupportChanged(this, stage, type);
   return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CSupport::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("Support"));
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

      m_pSegments->Load(pload);


      hr = pload->BeginUnit(_T("AssociatedSupports"));
      var.Clear();
      hr = pload->get_Property(_T("Count"),&var);
      if ( FAILED(hr) )
         return hr;
      
      IndexType count = VARIANT2INDEX(var);
      m_AssociatedSupportIDs.clear();
      for ( IndexType i = 0; i < count; i++ )
      {
         var.Clear();
         hr = pload->get_Property(_T("SupportID"),&var);
         if ( FAILED(hr) )
            return hr;

         m_AssociatedSupportIDs.push_back(VARIANT2ID(var));
      }
      VARIANT_BOOL eb;
      hr = pload->EndUnit(&eb); // Associated Supports
      if (FAILED(hr))
         return hr;

      if (eb!=VARIANT_TRUE)
         return STRLOAD_E_INVALIDFORMAT;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}


STDMETHODIMP CSupport::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("Support"), MY_VER);
      hr = psave->put_Property(CComBSTR("Length"),_variant_t(m_Length));
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
         ATLASSERT(false);
         var = "Fixed";
      }

      hr = psave->put_Property(CComBSTR("BoundaryCondition"),var);
      hr = psave->put_Property(CComBSTR("TopRelease"),_variant_t(m_TopRelease));
      hr = m_LoadModifierHelper.Save(psave);
      hr = psave->put_Property(CComBSTR("DistributionFactor"),_variant_t(m_DistributionFactor));
      
      m_pSegments->Save(psave);

      hr = psave->BeginUnit(_T("AssociatedSupports"),1.0);
      hr = psave->put_Property(_T("Count"),_variant_t(m_AssociatedSupportIDs.size()));
      std::vector<SupportIDType>::iterator iter(m_AssociatedSupportIDs.begin());
      std::vector<SupportIDType>::iterator end(m_AssociatedSupportIDs.end());
      for ( ; iter != end; iter++ )
      {
         hr = psave->put_Property(_T("SupportID"),_variant_t(*iter));
      }
      hr = psave->EndUnit(); // Associated Supports

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISupport);
   }

   return S_OK;
}

// callback functions for segments member
HRESULT CSupport::SetUpConnection(ISegmentItem* pCp, DWORD* pcookie)
{
   HRESULT hr = CrAdvise(pCp, this, IID_ISegmentItemEvents, pcookie);
   return S_OK;
}

void CSupport::BreakConnection(ISegmentItem* pCp, DWORD cookie)
{
   CrUnadvise(pCp, this, IID_ISegmentItemEvents, cookie);
}

void CSupport::OnSegmentsChanged(CSegments* psegments, BSTR stage, ChangeType change)
{
   Fire_OnSupportChanged(this, stage, change);
}

STDMETHODIMP CSupport::OnDistributionFactorChanged(IDistributionFactor* factor)
{
   Fire_OnSupportChanged(this, CComBSTR("*"), cgtDistributionFactor);
   return S_OK;
}

 
STDMETHODIMP CSupport::Clone(ISupport **clone)
{
   CHECK_RETOBJ(clone);

   // create a new stress point collection and fill it up
   CComObject<CSupport>* pnew;
   HRESULT hr = CComObject<CSupport>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ISupport> spsm(pnew);

   pnew->m_Length        = m_Length;
   pnew->m_IsSymmetrical = m_IsSymmetrical;
   pnew->m_BottomOffset  = m_BottomOffset;
   pnew->m_BoundaryCondition  = m_BoundaryCondition;
   pnew->m_TopRelease    = m_TopRelease;

   pnew->m_LoadModifierHelper  = m_LoadModifierHelper;
   
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

   pnew->m_AssociatedSupportIDs = m_AssociatedSupportIDs;

   return spsm.CopyTo(clone);
}


STDMETHODIMP CSupport::RemoveStage(BSTR stage)
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

STDMETHODIMP CSupport::GetLoadModifier(LoadCombinationType type, Float64 *minVal, Float64 *maxVal)
{
	return m_LoadModifierHelper.GetLoadModifier(type, minVal, maxVal);
}

STDMETHODIMP CSupport::SetLoadModifier(LoadCombinationType type, Float64 minVal, Float64 maxVal)
{
   bool did_fire;
   HRESULT hr = m_LoadModifierHelper.SetLoadModifier(type, minVal, maxVal, &did_fire);
   if (FAILED(hr))
      return hr;

   if (did_fire)
      Fire_OnSupportChanged(this, CComBSTR("*"), cgtCombination);

	return S_OK;
}
 

