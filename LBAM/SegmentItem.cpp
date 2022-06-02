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

// SegmentItem.cpp : Implementation of CSegmentItem
#include "stdafx.h"
#include "WBFLLBAM.h"
#include "SegmentItem.h"
#include "LBAMUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSegmentItem

STDMETHODIMP CSegmentItem::InterfaceSupportsErrorInfo(REFIID riid)
{

	static const IID* arr[] = 
	{
		&IID_ISegmentItem
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CSegmentItem::FinalRelease()
{
   HRESULT hr;
   if (!!m_Segment)
   {
      hr = CrUnadvise(m_Segment, this, IID_ISegmentEvents, m_SegmentCookie);
      ATLASSERT(SUCCEEDED(hr));
   }
}


STDMETHODIMP CSegmentItem::get_Stage(BSTR* pVal)
{

   CHECK_RETSTRING(pVal);

   *pVal = m_Stage.Copy();

	return S_OK;
}

STDMETHODIMP CSegmentItem::get_RelPosition(SegmentIndexType *pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = m_RelPosition;

	return S_OK;
}

STDMETHODIMP CSegmentItem::get_Segment(ISegment **pVal)
{
   CHECK_RETOBJ(pVal);

	return m_Segment.CopyTo(pVal);
}

HRESULT CSegmentItem::PutSegment(ISegment *newVal)
{
	CHECK_IN(newVal);

   // don't bother if someone is assigning same segment
   if ( m_Segment.IsEqualObject(newVal) )
      return S_OK;

   CrAssignPointer(m_Segment,newVal,this,IID_ISegmentEvents,&m_SegmentCookie);

   // tell the world we've changed
   Fire_OnSegmentItemChanged(this, m_Stage, cgtStiffness);

	return S_OK;
}

STDMETHODIMP CSegmentItem::OnSegmentChanged(/*[in]*/ISegment* segment, /*[in]*/ChangeType type)
{
   Fire_OnSegmentItemChanged(this, m_Stage, type);
   return S_OK;
}

HRESULT CSegmentItem::Clone(ISegmentItem** pclone)
{
   CHECK_RETOBJ(pclone);

   CComObject<CSegmentItem>* pnew;
   HRESULT hr = CComObject<CSegmentItem>::CreateInstance(&pnew);
   if (FAILED(hr))
      return hr;

   CComPtr<ISegmentItem> spsegi(pnew); // memory leak avoidance

   pnew->m_Stage = m_Stage;
   pnew->m_RelPosition = m_RelPosition;

   // deep clone
   CComPtr<ISegment> spseg;
   m_Segment->Clone(&spseg);

   pnew->PutSegment(spseg);

   return spsegi.CopyTo(pclone);
}
