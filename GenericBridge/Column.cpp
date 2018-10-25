///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

// Column.cpp : Implementation of CColumn
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "Column.h"
#include "Segment.h"
#include <ComException.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColumn
HRESULT CColumn::FinalConstruct()
{
   m_bFractional  = VARIANT_FALSE;
   m_bSymmetrical = VARIANT_FALSE;;

   m_Height     = 0.0;
   m_BaseOffset = 0.0;


   m_pSegments = new CSegments(this);

   return S_OK;
}

void CColumn::FinalRelease()
{
   delete m_pSegments;
   m_pSegments = NULL;
}

STDMETHODIMP CColumn::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IColumn,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CColumn::Clone(IColumn* *clone)
{
   CComObject<CColumn>* pClone;
   HRESULT hr = CComObject<CColumn>::CreateInstance(&pClone);
   if (FAILED(hr))
      return hr;

   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->SetBridge(m_pBridge);

   pClone->put_Symmetrical(m_bSymmetrical);
   pClone->put_Fractional(m_bFractional);
   pClone->put_Height(m_Height);
   pClone->put_BaseOffset(m_BaseOffset);
   
   hr = m_pSegments->Copy( pClone->GetSegments() );
   if (FAILED(hr))
      return hr;

	return S_OK;
}


////////////////////////////////////////////////////////////////////////
// CSegmentsOwner implementation
HRESULT CColumn::SetUpConnection(ISegmentItem* pCp, unsigned long* pcookie)
{
   HRESULT hr = AdviseSegmentItem(pCp,pcookie);
   return S_OK;
}

void CColumn::BreakConnection(ISegmentItem* pCp, unsigned long cookie)
{
   UnadviseSegmentItem(pCp,cookie);
}

void CColumn::OnSegmentsChanged(CSegments* psegments)
{
   Fire_OnColumnChanged(this);
}

Float64 CColumn::Length()
{
   Float64 length;
   get_Length(&length);
   return length;
}

HRESULT CColumn::AdviseSegmentItem(ISegmentItem* segItem,DWORD* pdwCookie)
{
   CComPtr<ISegmentItem> item(segItem);
   HRESULT hr = item.Advise(GetUnknown(),IID_ISegmentItemEvents,pdwCookie);
   ATLASSERT(SUCCEEDED(hr));

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CColumn::UnadviseSegmentItem(ISegmentItem* segItem,DWORD dwCookie)
{
   InternalAddRef(); // conteract InternalRelease() in advise
   CComQIPtr<IConnectionPointContainer> pCPC(segItem);
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint(IID_ISegmentItemEvents,&pCP);

   HRESULT hr = pCP->Unadvise(dwCookie);
   ATLASSERT( SUCCEEDED(hr) );

   return hr;
}

//////////////////////////////////////////////////////
// ISegmentMeasure
STDMETHODIMP CColumn::IsFractional()
{
   VARIANT_BOOL bFractional;
   get_Fractional(&bFractional);
   return (bFractional == VARIANT_TRUE ? S_OK : S_FALSE);
}

//////////////////////////////////////////////////////
// IColumn
STDMETHODIMP CColumn::get_Height(Float64* height)
{
   CHECK_RETVAL(height);
   (*height) = m_Height;
   return S_OK;
}

STDMETHODIMP CColumn::put_Height(Float64 height)
{
   if ( height < 0 )
      return E_INVALIDARG;

   if ( IsEqual(m_Height,height) )
      return S_OK;

   m_Height = height;
   Fire_OnColumnChanged(this);
   return S_OK;
}

STDMETHODIMP CColumn::get_BaseOffset(Float64* offset)
{
   CHECK_RETVAL(offset);
   (*offset) = m_BaseOffset;;
   return S_OK;
}

STDMETHODIMP CColumn::put_BaseOffset(Float64 offset)
{
   if ( IsEqual(m_BaseOffset,offset) )
      return S_OK;

   m_BaseOffset = offset;
   Fire_OnColumnChanged(this);
   return S_OK;
}

STDMETHODIMP CColumn::get_Length(Float64* length)
{
   CHECK_RETVAL(length);
   (*length) = sqrt(m_Height*m_Height + m_BaseOffset*m_BaseOffset);
   return S_OK;
}

STDMETHODIMP CColumn::AddSegment(ISegment* segment)
{
   try
   {
      segment->putref_SegmentMeasure(this);
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
      return DealWithExceptions(this, IID_IColumn);
   }
}

STDMETHODIMP CColumn::InsertSegment(CollectionIndexType idx,ISegment* segment)
{
   try
   {
      segment->putref_SegmentMeasure(this);
      HRESULT hr = m_pSegments->Insert(idx,segment);
      if ( FAILED(hr) )
         return hr;
      
      CComPtr<ISegment> s;
      m_pSegments->get_Segment(idx,&s);

      return S_OK;
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IColumn);
   }
}

STDMETHODIMP CColumn::RemoveSegment(CollectionIndexType idx)
{
   try
   {
	   return m_pSegments->Remove(idx);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IColumn);
   }
}

STDMETHODIMP CColumn::RemoveSegments()
{
   try
   {
      return m_pSegments->RemoveSegments();
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IColumn);
   }
}

STDMETHODIMP CColumn::get_Segment(CollectionIndexType idx, ISegment* *segment)
{
   try
   {
   	return m_pSegments->get_Segment(idx, segment);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IColumn);
   }
}

STDMETHODIMP CColumn::get_SegmentCount(CollectionIndexType* count)
{
   try
   {
      return m_pSegments->get_Count(count);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IColumn);
   }
}

STDMETHODIMP CColumn::get_SegmentLength(Float64* length)
{
   try
   {
	   return m_pSegments->get_Length(length);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IColumn);
   }
}

STDMETHODIMP CColumn::CopySegmentTo(CollectionIndexType fromIdx,CollectionIndexType toIdx)
{
   try
   {
   	return m_pSegments->CopyTo(fromIdx,toIdx);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IColumn);
   }
}

STDMETHODIMP CColumn::MoveSegmentTo(CollectionIndexType fromIdx,CollectionIndexType toIdx)
{
   try
   {
   	return m_pSegments->MoveTo(fromIdx,toIdx);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IColumn);
   }
}

STDMETHODIMP CColumn::ReverseSegments()
{
   return m_pSegments->Reverse();
}

STDMETHODIMP CColumn::get_Fractional(VARIANT_BOOL* bFractional)
{
   CHECK_RETVAL(bFractional);

   (*bFractional) = m_bFractional;

	return S_OK;
}

STDMETHODIMP CColumn::put_Fractional(VARIANT_BOOL bFractional)
{
   if ( m_bFractional ==  bFractional )
      return S_OK; // Do nothing, no change

   m_bFractional = bFractional;

   m_bIgnoreSegmentEvents = true;

   if ( m_bFractional == VARIANT_TRUE )
      m_pSegments->MakeFractional();
   else
      m_pSegments->MakeAbsolute();

   m_bIgnoreSegmentEvents = false;

   Fire_OnColumnChanged(this);
   return S_OK;
}

STDMETHODIMP CColumn::get_Symmetrical(VARIANT_BOOL* bSymmetrical)
{
   CHECK_RETVAL(bSymmetrical);
   (*bSymmetrical) = m_bSymmetrical;
	return S_OK;
}

STDMETHODIMP CColumn::put_Symmetrical(VARIANT_BOOL bSymmetrical)
{
   if ( m_bSymmetrical == bSymmetrical )
      return S_OK;

   m_bSymmetrical = bSymmetrical;
   Fire_OnColumnChanged(this);
   return S_OK;
}

STDMETHODIMP CColumn::GetMemberSegments(IFilteredSegmentCollection **ppSeg)
{
   try
   {
   	return m_pSegments->GetMemberSegments(Length(), m_bSymmetrical, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IColumn);
   }
}

STDMETHODIMP CColumn::GetSegmentForMemberLocation(Float64 location, Float64* dist,ISegmentItem **ppSeg)
{
   try
   {
   	return m_pSegments->GetSegmentForMemberLocation(Length(), m_bSymmetrical, location, dist, ppSeg);
   }
   catch(...)
   {
      return DealWithExceptions(this, IID_IColumn);
   }
}

////////////////////////////////////////////////////////////////////
// IStructuredStorage2 implementation
STDMETHODIMP CColumn::Load(IStructuredLoad2* load)
{
   load->BeginUnit(CComBSTR("Column"));

   CComVariant var;
   load->get_Property(CComBSTR("Height"),&var);
   m_Height = var.dblVal;

   load->get_Property(CComBSTR("BaseOffset"),&var);
   m_BaseOffset = var.dblVal;

   load->get_Property(CComBSTR("Fractional"),&var);
   m_bFractional = var.boolVal;

   load->get_Property(CComBSTR("Symmetrical"),&var);
   m_bSymmetrical = var.boolVal;

   m_pSegments->Load(load);

   VARIANT_BOOL bEnd;
   load->EndUnit(&bEnd);
   return S_OK;
}

STDMETHODIMP CColumn::Save(IStructuredSave2* save)
{
   save->BeginUnit(CComBSTR("Column"),1.0);

   save->put_Property(CComBSTR("Height"),CComVariant(m_Height));
   save->put_Property(CComBSTR("BaseOffset"),CComVariant(m_BaseOffset));
   save->put_Property(CComBSTR("Fractional"),CComVariant(m_bFractional));
   save->put_Property(CComBSTR("Symmetrical"),CComVariant(m_bSymmetrical));

   m_pSegments->Save(save);

   save->EndUnit();
   return S_OK;
}