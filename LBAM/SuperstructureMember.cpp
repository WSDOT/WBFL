///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2015  Washington State Department of Transportation
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

// SuperstructureMember.cpp : Implementation of CSuperstructureMember
#include "stdafx.h"
#include "WBFLLBAM.h"
#include <WBFLComCollections.h>
#include "SuperstructureMember.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperstructureMember

STDMETHODIMP CSuperstructureMember::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISuperstructureMember
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CSuperstructureMember::CSuperstructureMember() :
m_pSegments(0)
{
   Init();
}

HRESULT CSuperstructureMember::FinalConstruct()
{
   m_pSegments = new CSegments(this);
   return S_OK;
}

void CSuperstructureMember::FinalRelease()
{
   // destroy segments while we are still alive
   delete m_pSegments;
   m_pSegments = 0;
}

STDMETHODIMP CSuperstructureMember::get_Length(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

	*pVal = m_Length;

	return S_OK;
}

STDMETHODIMP CSuperstructureMember::put_Length(Float64 newVal)
{
	if (newVal<=0.0)
      return E_INVALIDARG;

   if (newVal!=m_Length)
   {
      m_Length = newVal;
      Fire_OnSuperstructureMemberChanged(this, CComBSTR("*"), cgtStiffness);
   } 

	return S_OK;
}

STDMETHODIMP CSuperstructureMember::get_IsSymmetrical(VARIANT_BOOL *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_IsSymmetrical;
	return S_OK;
}

STDMETHODIMP CSuperstructureMember::put_IsSymmetrical(VARIANT_BOOL newVal)
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

   Fire_OnSuperstructureMemberChanged(this, CComBSTR("*"), cgtStiffness);

	return S_OK;
}

STDMETHODIMP CSuperstructureMember::GetEndRelease(Side side, BSTR* pRemovalStage, MemberReleaseType *pVal)
{
   CHECK_RETVAL(pVal);
   CHECK_RETSTRING(pRemovalStage);

	if (side==ssLeft)
   {
      *pVal = m_LeftRelease;
      *pRemovalStage = m_LeftReleaseRemovalStage.Copy();
   }
   else if (side==ssRight)
   {
      *pVal = m_RightRelease;
      *pRemovalStage = m_RightReleaseRemovalStage.Copy();
   }
   else
      return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CSuperstructureMember::SetEndRelease(Side side, BSTR removalStage, MemberReleaseType newVal)
{
   CHECK_IN(removalStage);

   bool dofire=false;

   // be on the lookout for nefarious values
   if (newVal != mrtNone && newVal != mrtPinned)
      return E_INVALIDARG;

	if (side==ssLeft)
   {
      if (newVal != m_LeftRelease || m_LeftReleaseRemovalStage != removalStage)
      {
         m_LeftRelease = newVal;
         m_LeftReleaseRemovalStage = removalStage;
         dofire = true;
      }
   }
   else if (side==ssRight)
   {
      if (newVal != m_RightRelease || m_RightReleaseRemovalStage != removalStage)
      {
         m_RightRelease = newVal;
         m_RightReleaseRemovalStage = removalStage;
         dofire = true;
      }
   }
   else
      return E_INVALIDARG;

   if (dofire)
      Fire_OnSuperstructureMemberChanged(this, CComBSTR("*"), cgtStiffness);

	return S_OK;
}

STDMETHODIMP CSuperstructureMember::get_SegmentLength(BSTR stage, Float64 *pVal)
{
   CHECK_IN(stage);
   CHECK_RETVAL(pVal);

   try
   {
	   return m_pSegments->get_Length(stage, m_Length, pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::get_SegmentCount(BSTR stage, SegmentIndexType *pVal)
{
   CHECK_IN(stage);
   CHECK_RETVAL(pVal);

   try
   {
   	return m_pSegments->get_Count(stage, pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::get_Segment(BSTR stage, SegmentIndexType relPosition, ISegment **pVal)
{
   CHECK_IN(stage);
   CHECK_RETOBJ(pVal);

   try
   {
   	return m_pSegments->get_Segment(stage, relPosition, pVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::putref_Segment(BSTR stage, SegmentIndexType relPosition, ISegment *newVal)
{
   CHECK_IN(stage);
   CHECK_IN(newVal);

   try
   {
   	return m_pSegments->put_Segment(stage, relPosition, newVal);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::AddSegment(BSTR stage, ISegment * pSeg)
{
   CHECK_IN(stage);
   CHECK_IN(pSeg);

   try
   {
      return m_pSegments->Add(stage, pSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::InsertSegment(BSTR stage, SegmentIndexType relPosition, ISegment * pSeg)
{
   CHECK_IN(stage);
   CHECK_IN(pSeg);

   try
   {
   	return m_pSegments->Insert(relPosition, stage, pSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::MoveSegmentTo(BSTR stage, SegmentIndexType fromRelPosition, SegmentIndexType toRelPosition)
{
   CHECK_IN(stage);

   try
   {
   	return m_pSegments->MoveTo(stage, fromRelPosition, toRelPosition);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::CopySegmentTo(BSTR stage, SegmentIndexType fromRelPosition, SegmentIndexType toRelPosition)
{
   CHECK_IN(stage);

   try
   {
	   return m_pSegments->CopyTo(stage, fromRelPosition, toRelPosition);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::RemoveSegment(BSTR stage, SegmentIndexType relPosition)
{
   CHECK_IN(stage);

   try
   {
	   return m_pSegments->Remove(stage, relPosition);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::ReverseSegments(BSTR stage)
{
   CHECK_IN(stage);

   try
   {
	   return m_pSegments->Reverse(stage);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::GetSegmentForMemberLocation(BSTR stage, Float64 location, ISegmentItem** ppLeftSegi, ISegmentItem** ppRightSegi)
{
   CHECK_IN(stage);
   CHECK_RETOBJ(ppLeftSegi);
   CHECK_RETOBJ(ppRightSegi);

   try
   {
   	return m_pSegments->GetSegmentForMemberLocation(stage, m_Length, m_IsSymmetrical, location, ppLeftSegi, ppRightSegi);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::GetSegmentsForStage(BSTR stage, IFilteredSegmentCollection **ppSeg)
{
   CHECK_IN(stage);
   CHECK_RETOBJ(ppSeg);
   try
   {
   	return m_pSegments->GetSegmentsForStage(stage, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::GetMemberSegments(BSTR stage, IFilteredSegmentCollection **ppSeg)
{
   CHECK_IN(stage);
   CHECK_RETOBJ(ppSeg);
   try
   {
   	return m_pSegments->GetMemberSegments(stage, m_Length, m_IsSymmetrical, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

STDMETHODIMP CSuperstructureMember::get__EnumElements(IEnumSegmentItem* *retval)
{
   CHECK_RETOBJ(retval);

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

STDMETHODIMP CSuperstructureMember::get__NewEnum(IUnknown** retval)
{
   CHECK_RETOBJ(retval);

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

STDMETHODIMP CSuperstructureMember::OnSegmentItemChanged(/*[in]*/ISegmentItem* SegmentItem, BSTR stage, /*[in]*/ChangeType type)
{
   Fire_OnSuperstructureMemberChanged(this, stage, type);
   return S_OK;
}

// IStructuredStorage2
static const Float64 MY_VER=1.0;
STDMETHODIMP CSuperstructureMember::Load(IStructuredLoad2 * pload)
{
   CHECK_IN(pload);

   HRESULT hr;

   hr = pload->BeginUnit(CComBSTR("SuperstructureMember"));
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


      hr = pload->get_Property(CComBSTR("LeftRelease"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t rel (var);
      var.Clear();
      if (rel == _bstr_t("Pinned"))
      {
         m_LeftRelease=mrtPinned;
      }
      else if  (rel == _bstr_t("None"))
      {
         m_LeftRelease=mrtNone;
      }
      else
         return STRLOAD_E_INVALIDFORMAT;

      var.Clear();
      hr = pload->get_Property(CComBSTR("LeftReleaseRemovalStage"),&var);
      if (FAILED(hr))
         return hr;

      _bstr_t name(var);
      m_LeftReleaseRemovalStage = (LPCTSTR)name;

      var.Clear();
      hr = pload->get_Property(CComBSTR("RightRelease"),&var);
      if (FAILED(hr))
         return hr;

      rel = var;
      var.Clear();
      if (rel == _bstr_t("Pinned"))
      {
         m_RightRelease=mrtPinned;
      }
      else if  (rel == _bstr_t("None"))
      {
         m_RightRelease=mrtNone;
      }
      else
         return STRLOAD_E_INVALIDFORMAT;

      var.Clear();
      hr = pload->get_Property(CComBSTR("RightReleaseRemovalStage"),&var);
      if (FAILED(hr))
         return hr;

      name = var;
      m_RightReleaseRemovalStage = (LPCTSTR)name;

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


STDMETHODIMP CSuperstructureMember::Save(IStructuredSave2 * psave)
{
   CHECK_IN(psave);
   CHRException hr;
   try
   {
      hr = psave->BeginUnit(CComBSTR("SuperstructureMember"), MY_VER);
      hr = psave->put_Property(CComBSTR("Length"),_variant_t(m_Length));
      hr = psave->put_Property(CComBSTR("IsSymmetrical"),_variant_t(m_IsSymmetrical));

      _variant_t var = (m_LeftRelease==mrtPinned)?"Pinned":"None";
      hr = psave->put_Property(CComBSTR("LeftRelease"),var);

      hr = psave->put_Property(CComBSTR("LeftReleaseRemovalStage"),_variant_t(m_LeftReleaseRemovalStage));

      var = (m_RightRelease==mrtPinned)?"Pinned":"None";
      hr = psave->put_Property(CComBSTR("RightRelease"),var);

      hr = psave->put_Property(CComBSTR("RightReleaseRemovalStage"),_variant_t(m_RightReleaseRemovalStage));

      m_pSegments->Save(psave);

      hr = psave->EndUnit();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }

   return S_OK;
}

// callback functions for segments member
HRESULT CSuperstructureMember::SetUpConnection(ISegmentItem* pCp, DWORD* pcookie)
{
   HRESULT hr = CrAdvise(pCp, this, IID_ISegmentItemEvents, pcookie);
   return hr;
}

void CSuperstructureMember::BreakConnection(ISegmentItem* pCp, DWORD cookie)
{
   CrUnadvise(pCp, this, IID_ISegmentItemEvents, cookie);
}

void CSuperstructureMember::OnSegmentsChanged(CSegments* psegments, BSTR stage, ChangeType change)
{
   Fire_OnSuperstructureMemberChanged(this, stage, change);
}


STDMETHODIMP CSuperstructureMember::Clone(ISuperstructureMember **clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CSuperstructureMember>* pnew;
   HRESULT hr = CComObject<CSuperstructureMember>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ISuperstructureMember> spsm(pnew);

   pnew->m_Length                   = m_Length;
   pnew->m_IsSymmetrical            = m_IsSymmetrical;
   pnew->m_LeftRelease              = m_LeftRelease;
   pnew->m_LeftReleaseRemovalStage  = m_LeftReleaseRemovalStage;
   pnew->m_RightRelease             = m_RightRelease;
   pnew->m_RightReleaseRemovalStage = m_RightReleaseRemovalStage;
   
   hr = m_pSegments->Copy( pnew->m_pSegments );
   if (FAILED(hr))
      return hr;

   return spsm.CopyTo(clone);
}


STDMETHODIMP CSuperstructureMember::RemoveStage(BSTR stage)
{
   // release removal stages
   if (m_LeftReleaseRemovalStage==stage)
      m_LeftReleaseRemovalStage.Empty();

   if (m_RightReleaseRemovalStage==stage)
      m_RightReleaseRemovalStage.Empty();

   // segments are stage-dependent
   try
   {
	   return m_pSegments->RemoveStage(stage);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ISuperstructureMember);
   }
}

void CSuperstructureMember::Init()
{
   m_Length = 0.0;
   m_IsSymmetrical = VARIANT_FALSE;
   m_LeftRelease = mrtNone;
   m_RightRelease = mrtNone;
}

