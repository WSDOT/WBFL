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

////////////////////////////////////////////////////////////////////////
// CSegmentsOwner implementation
Float64 CLongitudinalPierDescription::Length()
{
   Float64 length;
   get_Length(&length);
   return length;
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
   if ( m_bFractional ==  bFractional )
      return S_OK; // Do nothing, no change

   m_bFractional = bFractional;

   if ( m_bFractional == VARIANT_TRUE )
      m_pSegments->MakeFractional();
   else
      m_pSegments->MakeAbsolute();

   return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::get_Symmetrical(VARIANT_BOOL* bSymmetrical)
{
   CHECK_RETVAL(bSymmetrical);
   *bSymmetrical = m_bSymmetrical;

	return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::put_Symmetrical(VARIANT_BOOL bSymmetrical)
{
   m_bSymmetrical = bSymmetrical;
   return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::get_Connectivity(ConnectivityType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Connectivity;

	return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::put_Connectivity(ConnectivityType newVal)
{
   m_Connectivity = newVal;
   return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::get_Height(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_Height;

	return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::put_Height(Float64 newVal)
{
   if ( newVal < 0 )
      return E_INVALIDARG;

   m_Height = newVal;
   return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::get_BaseOffset(Float64 *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_BaseOffset;

	return S_OK;
}

STDMETHODIMP CLongitudinalPierDescription::put_BaseOffset(Float64 newVal)
{
   m_BaseOffset = newVal;
   return S_OK;
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

//STDMETHODIMP CLongitudinalPierDescription::get_ContinuityStage(StageIndexType* pStageIdx)
//{
//   CHECK_RETVAL(pStageIdx);
//   
//   *pStageIdx = m_ContinuityStageIdx;
//
//   return S_OK;
//}
//
//STDMETHODIMP CLongitudinalPierDescription::put_ContinuityStage(StageIndexType stageIdx)
//{
//   if ( m_ContinuityStageIdx == stageIdx )
//      return S_OK;
//
//   //// Verify the stage actually exists
//   //CComPtr<IStageCollection> stages;
//   //m_pBridge->get_Stages(&stages);
//
//   //CComPtr<IStage> stage;
//   //stages->Find(newVal,&stage);
//
//   //if ( stage == NULL )
//   //   return Error(IDS_E_STAGE_NOT_FOUND,IID_ILongitudinalPierDescription,GB_E_STAGE_NOT_FOUND);
//
//   m_ContinuityStageIdx = stageIdx;
//
//   return S_OK;
//}

STDMETHODIMP CLongitudinalPierDescription::AddSegment(ISegment* segment)
{
   try
   {
      HRESULT hr = m_pSegments->Add(segment);
      if ( FAILED(hr) )
         return hr;

      CollectionIndexType count;
      m_pSegments->get_Count(&count);

      CComPtr<ISegment> s;
      m_pSegments->get_Segment(count-1,&s);

      return S_OK;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILongitudinalPierDescription);
   }
}


STDMETHODIMP CLongitudinalPierDescription::InsertSegment(CollectionIndexType idx,ISegment* segment)
{
   try
   {
      return m_pSegments->Insert(idx,segment);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILongitudinalPierDescription);
   }
}

STDMETHODIMP CLongitudinalPierDescription::MoveSegmentTo(CollectionIndexType fromIdx, CollectionIndexType toIdx)
{
   try
   {
   	return m_pSegments->MoveTo(fromIdx,toIdx);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILongitudinalPierDescription);
   }
}

STDMETHODIMP CLongitudinalPierDescription::CopySegmentTo(CollectionIndexType fromIdx, CollectionIndexType toIdx)
{
   try
   {
   	return m_pSegments->CopyTo(fromIdx,toIdx);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILongitudinalPierDescription);
   }
}

STDMETHODIMP CLongitudinalPierDescription::RemoveSegment(CollectionIndexType idx)
{
   try
   {
      return m_pSegments->Remove(idx);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILongitudinalPierDescription);
   }
}

STDMETHODIMP CLongitudinalPierDescription::RemoveSegments()
{
   try
   {
      return m_pSegments->RemoveSegments();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILongitudinalPierDescription);
   }
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

STDMETHODIMP CLongitudinalPierDescription::GetDistanceFromStartOfSegment(Float64 location, Float64* dist,ISegmentItem **ppSeg)
{
   try
   {
   	return m_pSegments->GetDistanceFromStartOfSegment(Length(), m_bSymmetrical, location, dist, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_ILongitudinalPierDescription);
   }
}

STDMETHODIMP CLongitudinalPierDescription::ReverseSegments()
{
   return m_pSegments->Reverse();
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

   //load->get_Property(CComBSTR("ContinuityStage"),&var);
   //m_ContinuityStageIdx = var.llVal;

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
   //save->put_Property(CComBSTR("ContinuityStage"),CComVariant(m_ContinuityStageIdx));

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