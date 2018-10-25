///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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

// SpanCollection.cpp : Implementation of CSpanCollection
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "SpanCollection.h"
#include "Span.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpanCollection
void CSpanCollection::FinalRelease()
{
   SpanColl::Clear(); // Forces all of the span objects to be unadvised
}

void CSpanCollection::SetBridge(IGenericBridge* bridge)
{
   m_pBridge = bridge;

   CComPtr<IEnumSpans> enumSpans;
   get__EnumSpans(&enumSpans);
   CComPtr<ISpan> span;
   while ( enumSpans->Next(1,&span,NULL) != S_FALSE )
   {
      dynamic_cast<CSpan*>(span.p)->SetBridge(bridge);
      span.Release();
   };
}

STDMETHODIMP CSpanCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISpanCollection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSpanCollection::Clone(ISpanCollection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CSpanCollection>* pClone;
   CComObject<CSpanCollection>::CreateInstance(&pClone);
   (*clone) = pClone;
   (*clone)->AddRef();

   iterator iter;
   for ( iter = begin(); iter != end(); iter++ )
   {
      StoredType* st = *iter;

      // Casting because Clone is current not on the COM interface
      CSpan* pSpan = dynamic_cast<CSpan*>(st->second.m_T.p);
      
      CComPtr<ISpan> spanClone;
      pSpan->Clone(&spanClone);

      pClone->Add(spanClone);
   }

   return S_OK;
}

SpanIndexType CSpanCollection::GetSpanIndex(ISpan* span)
{
   SpanIndexType idx = 0;
   iterator iter;
   for ( iter = begin(); iter != end(); iter++ )
   {
      StoredType* st = *iter;
      if ( st->second.m_T.IsEqualObject(span) )
         return idx;

      idx++;
   }

   ATLASSERT( iter != end() ); // Span wasn't found
   return ALL_SPANS;
}

HRESULT CSpanCollection::OnBeforeAdd( StoredType* pVal)
{
   return S_OK;
}

HRESULT CSpanCollection::OnAfterAdd(StoredType* pVal, SpanIndexType spanIndex)
{
   // Set up event sink
   DWORD dwCookie;
   HRESULT hr = Advise(pVal->second.m_T,&dwCookie);
   ATLASSERT(SUCCEEDED(hr));

   pVal->first = dwCookie;

   // hook up parent
   CSpan* pSpan = dynamic_cast<CSpan*>((pVal->second.m_T).p);
   pSpan->SetBridge(m_pBridge);

   return S_OK;
}

HRESULT CSpanCollection::OnBeforeRemove( StoredType* pVal, SpanIndexType spanIndex)
{
   DWORD dwCookie = pVal->first;
   CComPtr<ISpan> span(pVal->second.m_T);
   HRESULT hr = Unadvise(span,dwCookie);
   ATLASSERT(SUCCEEDED(hr));

   CSpan* pSpan = dynamic_cast<CSpan*>((pVal->second.m_T).p);
   pSpan->SetBridge(NULL);

   return S_OK;
}

HRESULT CSpanCollection::Advise(ISpan* span,DWORD* pdwCookie)
{
   CComPtr<ISpan> pCP(span);
   HRESULT hr = pCP.Advise(GetUnknown(), IID_ISpanEvents, pdwCookie );
   if ( FAILED(hr) )
   {
      ATLTRACE("Failed to establish connection point with Span object\n");
      return hr;
   }

   InternalRelease(); // Break circular reference

   return hr;
}

HRESULT CSpanCollection::Unadvise(ISpan* span,DWORD dwCookie)
{
   ATLASSERT(span != 0);

   //
   // Disconnection from connection point
   //

   InternalAddRef(); // Counteract InternalRelease() in Advise

   // Find the connection point and disconnection
   CComQIPtr<IConnectionPointContainer> pCPC( span );
   CComPtr<IConnectionPoint> pCP;
   pCPC->FindConnectionPoint( IID_ISpanEvents, &pCP );
   HRESULT hr = pCP->Unadvise( dwCookie );
   ATLASSERT(SUCCEEDED(hr));
   return hr;
}

STDMETHODIMP CSpanCollection::get_SpanIndex(ISpan* span,SpanIndexType* index)
{
   CHECK_IN(span);
   CHECK_RETVAL(index);

   (*index) = GetSpanIndex(span);
   return ( (*index) == ALL_SPANS ) ? S_FALSE : S_OK;
}

STDMETHODIMP CSpanCollection::get__EnumSpans(IEnumSpans* *enumSpans)
{
   return get__EnumElements(enumSpans);
}

/////////////////////////////////////////////////////////////////
HRESULT CSpanCollection::DoSaveItem(IStructuredSave2* save,ISpan* item)
{
   CComQIPtr<IStructuredStorage2> ssSpan(item);
   return ssSpan->Save(save);
}

HRESULT CSpanCollection::DoLoadItem(IStructuredLoad2* load,ISpan* *ppItem)
{
   // Create a new span object
   CComObject<CSpan>* pSpan;
   CComObject<CSpan>::CreateInstance(&pSpan);
   CComPtr<ISpan> newSpan = pSpan;

   ATLASSERT(m_pBridge != NULL);
   pSpan->SetBridge(m_pBridge);

   CComQIPtr<IStructuredStorage2> ssSpan(newSpan);
   HRESULT hr = ssSpan->Load(load);
   if ( FAILED(hr) )
      return hr;

   (*ppItem) = newSpan;
   (*ppItem)->AddRef();

   return S_OK;
}
