///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// BridgeFramingGeometry.cpp : Implementation of CBridgeGeometry

#include "stdafx.h"
#include "WBFLCogo.h"
#include "BridgeGeometry.h"
#include <WBFLCogo\CogoHelpers.h>

// CBridgeGeometry

STDMETHODIMP CBridgeGeometry::AddAlignment(IDType ID,IAlignment* pAlignment)
{
   CHECK_IN(pAlignment);
   m_Alignments.insert(std::make_pair(ID,pAlignment));

   auto alignment = cogoUtil::GetInnerAlignment(pAlignment);
   m_Bridge->AddAlignment(ID, alignment);

   return S_OK;
}


STDMETHODIMP CBridgeGeometry::GetAlignment(IDType ID,IAlignment** pAlignment)
{
   CHECK_RETOBJ(pAlignment);
   AlignmentCollection::iterator found = m_Alignments.find(ID);
   if ( found == m_Alignments.end() )
   {
      return E_INVALIDARG;
   }

   return found->second.CopyTo(pAlignment);
}

STDMETHODIMP CBridgeGeometry::put_BridgeAlignmentID(IDType ID)
{
   m_Bridge->SetBridgeAlignmentID(ID);
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::get_BridgeAlignmentID(IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Bridge->GetBridgeAlignmentID();
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::get_BridgeAlignment(IAlignment** alignment)
{
   CHECK_RETOBJ(alignment);
   return GetAlignment(m_Bridge->GetBridgeAlignmentID(), alignment);
}

STDMETHODIMP CBridgeGeometry::put_ProfileID(IDType profileID)
{
   m_Bridge->SetProfileID(profileID);
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::get_ProfileID(IDType* pProfileID)
{
   CHECK_RETVAL(pProfileID);
   *pProfileID = m_Bridge->GetProfileID();
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::put_SurfaceID(IDType surfaceID)
{
   m_Bridge->SetSurfaceID(surfaceID);
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::get_SurfaceID(IDType* pSurfaceID)
{
   CHECK_RETVAL(pSurfaceID);
   *pSurfaceID = m_Bridge->GetSurfaceID();
   return S_OK;
}


STDMETHODIMP CBridgeGeometry::put_BridgeLineOffset(Float64 offset)
{
   m_Bridge->SetBridgeLineOffset(offset);
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::get_BridgeLineOffset(Float64* offset)
{
   CHECK_RETVAL(offset);
   *offset = m_Bridge->GetBridgeLineOffset();
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::get_BridgeLine(IPath** path)
{
   CHECK_RETOBJ(path);
   auto bridge_line = m_Bridge->GetBridgeLine();
   auto clone = WBFL::COGO::Path::Create(*bridge_line);
   return cogoUtil::CreatePath(clone, path);
}

STDMETHODIMP CBridgeGeometry::AddPierLineFactory(IPierLineFactory* pFactory)
{
   CHECK_IN(pFactory);
   auto factory = cogoUtil::GetInnerFactory(pFactory);
   m_Bridge->AddPierLineFactory(factory);
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::GetPierLine(PierIndexType idx, IPierLine** ppPierLine)
{
   CHECK_RETOBJ(ppPierLine);
   auto pier_line = m_Bridge->GetPierLine(idx);
   return cogoUtil::CreatePierLine(WBFL::COGO::PierLine::Create(*pier_line), ppPierLine);
}

STDMETHODIMP CBridgeGeometry::FindPierLine(PierIDType ID, IPierLine** ppPierLine)
{
   CHECK_RETOBJ(ppPierLine);
   auto pier_line = m_Bridge->FindPierLine(ID);
   if (pier_line == nullptr) return E_INVALIDARG;
   return cogoUtil::CreatePierLine(WBFL::COGO::PierLine::Create(*pier_line), ppPierLine);
}

STDMETHODIMP CBridgeGeometry::get_PierLineCount(PierIndexType* pVal)
{
   CHECK_RETOBJ(pVal);
   *pVal = m_Bridge->GetPierLineCount();
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::AddLayoutLineFactory(ILayoutLineFactory* pFactory)
{
   CHECK_IN(pFactory);
   auto factory = cogoUtil::GetInnerFactory(pFactory);
   m_Bridge->AddLayoutLineFactory(factory);
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::GetLayoutLine(IndexType idx, IPath** ppPath)
{
   CHECK_RETOBJ(ppPath);
   auto path = m_Bridge->GetLayoutLine(idx);
   return cogoUtil::CreatePath(WBFL::COGO::Path::Create(*path), ppPath);
}

STDMETHODIMP CBridgeGeometry::FindLayoutLine(IDType ID,IPath** ppPath)
{
   CHECK_RETVAL(ppPath);
   auto path = m_Bridge->FindLayoutLine(ID);
   if (path == nullptr) return E_INVALIDARG;
   return cogoUtil::CreatePath(WBFL::COGO::Path::Create(*path), ppPath);
}

STDMETHODIMP CBridgeGeometry::get_LayoutLineCount(IndexType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Bridge->GetLayoutLineCount();
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::AddGirderLineFactory(IGirderLineFactory* pFactory)
{
   CHECK_IN(pFactory);
   m_Bridge->AddGirderLineFactory(cogoUtil::GetInnerFactory(pFactory));
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::GetGirderLine(IndexType idx, IGirderLine** ppGirderLine)
{
   CHECK_RETOBJ(ppGirderLine);
   auto girder_line = m_Bridge->GetGirderLine(idx);
   return cogoUtil::CreateGirderLine(WBFL::COGO::GirderLine::Create(*girder_line), ppGirderLine);
}

STDMETHODIMP CBridgeGeometry::FindGirderLine(IDType ID, IGirderLine** ppGirderLine)
{
   CHECK_RETOBJ(ppGirderLine);
   auto girder_line = m_Bridge->FindGirderLine(ID);
   if (girder_line == nullptr) return E_INVALIDARG;
   return cogoUtil::CreateGirderLine(WBFL::COGO::GirderLine::Create(*girder_line), ppGirderLine);
}

STDMETHODIMP CBridgeGeometry::get_GirderLineCount(IndexType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Bridge->GetGirderLineCount();
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::AddDiaphragmLineFactory(IDiaphragmLineFactory* pFactory)
{
   CHECK_IN(pFactory);
   auto factory = cogoUtil::GetInnerFactory(pFactory);
   m_Bridge->AddDiaphragmLineFactory(factory);
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::GetDiaphragmLine(IndexType idx, IDiaphragmLine** ppDiaphragmLine)
{
   CHECK_RETOBJ(ppDiaphragmLine);
   auto diaphragm_line = m_Bridge->GetDiaphragmLine(idx);
   return cogoUtil::CreateDiaphragmLine(WBFL::COGO::DiaphragmLine::Create(*diaphragm_line), ppDiaphragmLine);
}

STDMETHODIMP CBridgeGeometry::FindDiaphragmLine(IDType ID, IDiaphragmLine** ppDiaphragmLine)
{
   CHECK_RETOBJ(ppDiaphragmLine);
   auto diaphragm_line = m_Bridge->FindDiaphragmLine(ID);
   if (diaphragm_line == nullptr) return E_INVALIDARG;
   return cogoUtil::CreateDiaphragmLine(WBFL::COGO::DiaphragmLine::Create(*diaphragm_line), ppDiaphragmLine);
}

STDMETHODIMP CBridgeGeometry::get_DiaphragmLineCount(IndexType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Bridge->GetDiaphragmLineCount();
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::AddDeckBoundaryFactory(IDeckBoundaryFactory* pFactory)
{
   CHECK_IN(pFactory);
   auto factory = cogoUtil::GetInnerFactory(pFactory);
   m_Bridge->SetDeckBoundaryFactory(factory);
   return S_OK;
}

STDMETHODIMP CBridgeGeometry::get_DeckBoundary(IDeckBoundary** ppDeckBoundary)
{
   CHECK_RETOBJ(ppDeckBoundary);
   auto deck_boundary = m_Bridge->GetDeckBoundary();
   return cogoUtil::CreateDeckBoundary(WBFL::COGO::DeckBoundary::Create(*deck_boundary), ppDeckBoundary);
}


//
//STDMETHODIMP CBridgeGeometry::CreateGirderLines(IGirderLineFactory* pFactory)
//{
//   CHECK_IN(pFactory);
//
//   CComPtr<IUnkArray> arrUnks;
//   HRESULT hr = pFactory->Create(this,&arrUnks);
//   if ( FAILED(hr) )
//   {
//      return hr;
//   }
//
//   IndexType nItems;
//   arrUnks->get_Count(&nItems);
//
//   for (IndexType idx = 0; idx < nItems; idx++ )
//   {
//      CComPtr<IUnknown> pUnk;
//      arrUnks->get_Item(idx,&pUnk);
//
//      CComQIPtr<IGirderLine> girderLine(pUnk);
//      ATLASSERT( girderLine != nullptr );
//
//      GirderIDType ID;
//      girderLine->get_ID(&ID);
//
//      std::pair<GirderLineCollection::iterator,bool> insert_result( m_GirderLines.insert( std::make_pair(ID,girderLine) ) );
//      if ( insert_result.second == false )
//      {
//         ATLASSERT(false); // container already has a girder line with ID
//         m_GirderLines.erase(insert_result.first); // remove the previously defined girder line
//         insert_result = m_GirderLines.insert( std::make_pair(ID,girderLine) );
//         ATLASSERT(insert_result.second == true); // WTF happened
//         if ( insert_result.second == false )
//         {
//            return E_FAIL;
//         }
//      }
//   }
//
//   return S_OK;
//}
//
//STDMETHODIMP CBridgeGeometry::FindGirderLine(GirderIDType ID,IGirderLine** ppGirderLine)
//{
//   CHECK_RETOBJ(ppGirderLine);
//   GirderLineCollection::iterator found = m_GirderLines.find(ID);
//   if ( found == m_GirderLines.end() )
//   {
//      return E_FAIL;
//   }
//
//   return found->second.CopyTo(ppGirderLine);
//}
//
//STDMETHODIMP CBridgeGeometry::get_GirderLineCount(IndexType* pVal)
//{
//   CHECK_RETVAL(pVal);
//   *pVal = m_GirderLines.size();
//   return S_OK;
//}
//
//STDMETHODIMP CBridgeGeometry::CreateDiaphragmLines(IDiaphragmLineFactory* pFactory)
//{
//   CHECK_IN(pFactory);
//
//   CComPtr<IUnkArray> arrUnks;
//   HRESULT hr = pFactory->Create(this,&arrUnks);
//   if ( FAILED(hr) )
//   {
//      return hr;
//   }
//
//   IndexType nItems;
//   arrUnks->get_Count(&nItems);
//
//   for (IndexType idx = 0; idx < nItems; idx++ )
//   {
//      CComPtr<IUnknown> pUnk;
//      arrUnks->get_Item(idx,&pUnk);
//
//      CComQIPtr<IDiaphragmLine> diaphragmLine(pUnk);
//      ATLASSERT( diaphragmLine != nullptr );
//
//      LineIDType ID;
//      diaphragmLine->get_ID(&ID);
//
//      std::pair<DiaphragmLineCollection::iterator,bool> insert_result = m_DiaphragmLines.insert( std::make_pair(ID,diaphragmLine) );
//      if ( insert_result.second == false )
//      {
//         ATLASSERT(false); // container already has a girder line with ID
//         m_DiaphragmLines.erase(insert_result.first); // remove the previously defined girder line
//         insert_result = m_DiaphragmLines.insert( std::make_pair(ID,diaphragmLine) );
//         ATLASSERT(insert_result.second == true); // WTF happened
//         if ( insert_result.second == false )
//         {
//            return E_FAIL;
//         }
//      }
//   }
//
//   return S_OK;
//}
//
//STDMETHODIMP CBridgeGeometry::FindDiaphragmLine(LineIDType ID,IDiaphragmLine** ppDiaphragmLine)
//{
//   CHECK_RETOBJ(ppDiaphragmLine);
//   DiaphragmLineCollection::iterator found = m_DiaphragmLines.find(ID);
//   if ( found == m_DiaphragmLines.end() )
//   {
//      return E_FAIL;
//   }
//
//   return found->second.CopyTo(ppDiaphragmLine);
//}
//
//STDMETHODIMP CBridgeGeometry::get_DiaphragmLineCount(IndexType* pVal)
//{
//   CHECK_RETVAL(pVal);
//   *pVal = m_DiaphragmLines.size();
//   return S_OK;
//}
//
//STDMETHODIMP CBridgeGeometry::CreateDeckBoundary(IDeckBoundaryFactory* pFactory)
//{
//   CHECK_IN(pFactory);
//   m_DeckBoundary.Release();
//   HRESULT hr = pFactory->Create(this,&m_DeckBoundary);
//   if ( FAILED(hr) )
//   {
//      return hr;
//   }
//
//   return S_OK;
//}
//
//STDMETHODIMP CBridgeGeometry::get_DeckBoundary(IDeckBoundary** ppDeckBoundary)
//{
//   CHECK_RETOBJ(ppDeckBoundary);
//   m_DeckBoundary.CopyTo(ppDeckBoundary);
//   return S_OK;
//}
//
//STDMETHODIMP CBridgeGeometry::UpdateGeometry(long flag)
//{
//   ASSERTVALID;
//
//   HRESULT hr = S_OK;
//   
//   if (flag & GF_BRIDGELINE)
//   {
//      hr = UpdateBridgeLine();
//      if (FAILED(hr))
//      {
//         return hr;
//      }
//   }
//
//   if (flag & GF_PIERS)
//   {
//      hr = UpdatePierGeometry();
//      if (FAILED(hr))
//      {
//         return hr;
//      }
//   }
//
//   if (flag & GF_GIRDERS)
//   {
//      hr = UpdateGirderGeometry();
//      if (FAILED(hr))
//      {
//         return hr;
//      }
//   }
//
//   if (flag & GF_DIAPHRAGMS)
//   {
//      hr = UpdateDiaphragmGeometry();
//      if (FAILED(hr))
//      {
//         return hr;
//      }
//   }
//
//   if (flag & GF_DECK)
//   {
//      hr = UpdateDeckBoundaryGeometry();
//      if (FAILED(hr))
//      {
//         return hr;
//      }
//   }
//
//   return S_OK;
//}
//
//
///////////////////////////////////////
//
//HRESULT CBridgeGeometry::UpdateBridgeLine()
//{
//   CComPtr<IAlignment> alignment;
//   HRESULT hr = get_BridgeAlignment(&alignment);
//   if ( FAILED(hr) )
//   {
//      return hr;
//   }
//
//   m_BridgeLine.Release();
//   return alignment->CreateOffsetPath(m_AlignmentOffset,&m_BridgeLine);
//}
//
//HRESULT CBridgeGeometry::UpdatePierGeometry()
//{
//   HRESULT hr = S_OK;
//
//   CComPtr<IEnumPierLines> pEnum;
//   m_PierLines->get__EnumPiers(&pEnum);
//   CComPtr<IPierLine> pier;
//   while( pEnum->Next(1,&pier,nullptr) != S_FALSE )
//   {
//      CPierLine* pPier = (CPierLine*)pier.p;
//      hr = pPier->UpdateGeometry();
//      if ( FAILED(hr) )
//      {
//         return hr;
//      }
//
//      pier.Release();
//   }
//
//   return S_OK;
//}
//
//HRESULT CBridgeGeometry::UpdateGirderGeometry()
//{
//   for( const auto& gdrLineEntry : m_GirderLines)
//   {
//      CComPtr<IGirderLine> girderLine( gdrLineEntry.second );
//      CGirderLine* pGirderLine = (CGirderLine*)girderLine.p;
//      HRESULT hr = pGirderLine->UpdateGeometry();
//      if ( FAILED(hr) )
//      {
//         return hr;
//      }
//   }
//
//   return S_OK;
//}
//
//HRESULT CBridgeGeometry::UpdateDiaphragmGeometry()
//{
//   for( const auto& diaphragmLineEntry : m_DiaphragmLines)
//   {
//      CComPtr<IDiaphragmLine> DiaphragmLine( diaphragmLineEntry.second );
//      CDiaphragmLine* pDiaphragmLine = (CDiaphragmLine*)DiaphragmLine.p;
//      HRESULT hr = pDiaphragmLine->UpdateGeometry();
//      if ( FAILED(hr) )
//      {
//         return hr;
//      }
//   }
//
//   return S_OK;
//}
//
//HRESULT CBridgeGeometry::UpdateDeckBoundaryGeometry()
//{
//   if ( m_DeckBoundary )
//   {
//      CDeckBoundary* pDeckBoundary = (CDeckBoundary*)m_DeckBoundary.p;
//      return pDeckBoundary->UpdateGeometry();
//   }
//
//   return S_OK;
//}
//
//#if defined _DEBUG
//void CBridgeGeometry::AssertValid()
//{
//   PierIndexType nPiers;
//   m_PierLines->get_Count(&nPiers);
//   ATLASSERT(1 < nPiers); // must be 2 or more piers
//}
//#endif