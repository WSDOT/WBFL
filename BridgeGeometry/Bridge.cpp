///////////////////////////////////////////////////////////////////////
// BridgeGeometry
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

// Bridge.cpp : Implementation of CBridge

#include "stdafx.h"
#include "Bridge.h"
#include "PierLine.h"
#include "GirderLine.h"
#include "DiaphragmLine.h"
#include "DeckBoundary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CBridge

STDMETHODIMP CBridge::putref_CogoModel(ICogoModel* pCogoModel)
{
   if ( m_CogoModel )
   {
      return Error(IDS_E_INITIALIZATION,IID_IBridgeGeometry,BRIDGEGEOMETRY_E_INITIALIZATION);
   }

   CHECK_IN(pCogoModel);
   m_CogoModel = pCogoModel;
   return S_OK;
}

STDMETHODIMP CBridge::get_CogoModel(ICogoModel** pCogoModel)
{
   CHECK_RETOBJ(pCogoModel);
   return m_CogoModel.CopyTo(pCogoModel);
}

STDMETHODIMP CBridge::putref_Alignment(CogoObjectID ID,IAlignment* pAlignment)
{
   CHECK_IN(pAlignment);
   m_Alignments.insert(std::make_pair(ID,pAlignment));
   return S_OK;
}


STDMETHODIMP CBridge::get_Alignment(CogoObjectID ID,IAlignment** pAlignment)
{
   CHECK_RETOBJ(pAlignment);
   AlignmentCollection::iterator found = m_Alignments.find(ID);
   if ( found == m_Alignments.end() )
   {
      return Error(IDS_E_ID,IID_IBridgeGeometry,BRIDGEGEOMETRY_E_ID);
   }

   return found->second.CopyTo(pAlignment);
}

STDMETHODIMP CBridge::put_BridgeAlignmentID(CogoObjectID ID)
{
   m_BridgeAlignmentID = ID;
   return S_OK;
}

STDMETHODIMP CBridge::get_BridgeAlignmentID(CogoObjectID* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_BridgeAlignmentID;
   return S_OK;
}

STDMETHODIMP CBridge::get_BridgeAlignment(IAlignment** alignment)
{
   CHECK_RETOBJ(alignment);
   return get_Alignment(m_BridgeAlignmentID,alignment);
}

STDMETHODIMP CBridge::put_ProfileID(IDType profileID)
{
   m_ProfileID = profileID;
   return S_OK;
}

STDMETHODIMP CBridge::get_ProfileID(IDType* pProfileID)
{
   CHECK_RETVAL(pProfileID);
   *pProfileID = m_ProfileID;
   return S_OK;
}

STDMETHODIMP CBridge::put_SurfaceID(IDType surfaceID)
{
   m_SurfaceID = surfaceID;
   return S_OK;
}

STDMETHODIMP CBridge::get_SurfaceID(IDType* pSurfaceID)
{
   CHECK_RETVAL(pSurfaceID);
   *pSurfaceID = m_SurfaceID;
   return S_OK;
}


STDMETHODIMP CBridge::put_AlignmentOffset(Float64 offset)
{
   m_AlignmentOffset = offset;
   return S_OK;
}

STDMETHODIMP CBridge::get_AlignmentOffset(Float64* offset)
{
   CHECK_RETVAL(offset);
   *offset = m_AlignmentOffset;
   return S_OK;
}

STDMETHODIMP CBridge::get_BridgeLine(IPath** path)
{
   CHECK_RETOBJ(path);
   return m_BridgeLine.CopyTo(path);
}

STDMETHODIMP CBridge::CreateLayoutLines(ILayoutLineFactory* pFactory)
{
   CHECK_IN(pFactory);

   HRESULT hr = pFactory->Create(this,m_LayoutLines);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return S_OK;
}

STDMETHODIMP CBridge::FindLayoutLine(CogoObjectID ID,IPath** ppPath)
{
   CHECK_RETVAL(ppPath);
   CComPtr<IPath> path;
   HRESULT hr = m_LayoutLines->get_Item(ID,&path);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return path->Clone(ppPath);
}

STDMETHODIMP CBridge::get_LayoutLineCount(CollectionIndexType* pVal)
{
   CHECK_RETVAL(pVal);
   return m_LayoutLines->get_Count(pVal);
}

STDMETHODIMP CBridge::CreatePierLine(PierIDType ID, CogoObjectID alignmentID,VARIANT station, BSTR orientation, Float64 width, Float64 offset,IPierLine** ppPierLine)
{
   CHECK_RETOBJ(ppPierLine);

   // see if a pier with this ID already exists
   CComPtr<IPierLine> otherPierLine;
   m_PierLines->FindPierLine(ID,&otherPierLine);
   if ( otherPierLine != nullptr )
   {
      return Error(IDS_E_ID,IID_IBridgeGeometry,BRIDGEGEOMETRY_E_ID);
   }

   // create pier object
   CComObject<CPierLine>* pPierLine;
   CComObject<CPierLine>::CreateInstance(&pPierLine);
   CComPtr<IPierLine> pierLine = pPierLine;

   // initialize it
   pPierLine->m_pBridge = this;
   pPierLine->m_ID = ID;
   pPierLine->m_AlignmentID = alignmentID;
   HRESULT hr = pPierLine->m_Station->FromVariant(station);
   if ( FAILED(hr) )
   {
      return Error(IDS_E_INVALIDSTATION,IID_IBridgeGeometry,BRIDGEGEOMETRY_E_INVALIDSTATION);
   }

   pPierLine->m_bstrOrientation = orientation;

   pPierLine->m_Width = width;
   pPierLine->m_Offset = offset;

   // save it in the collection
   ((CPierLineCollection*)m_PierLines.p)->Add(pierLine);

   pierLine.CopyTo(ppPierLine);

   return S_OK;
}

STDMETHODIMP CBridge::GetPierLine(PierIndexType idx, IPierLine** ppPierLine)
{
   CHECK_RETOBJ(ppPierLine);
   return m_PierLines->get_PierLine(idx,ppPierLine);
}

STDMETHODIMP CBridge::FindPierLine(PierIDType ID, IPierLine** ppPierLine)
{
   CHECK_RETOBJ(ppPierLine);
   return m_PierLines->FindPierLine(ID,ppPierLine);
}

STDMETHODIMP CBridge::get_PierLineCount(PierIndexType* pVal)
{
   CHECK_RETOBJ(pVal);
   return m_PierLines->get_Count(pVal);
}

STDMETHODIMP CBridge::CreateGirderLines(IGirderLineFactory* pFactory)
{
   CHECK_IN(pFactory);

   CComPtr<IUnkArray> arrUnks;
   HRESULT hr = pFactory->Create(this,&arrUnks);
   if ( FAILED(hr) )
   {
      return hr;
   }

   CollectionIndexType nItems;
   arrUnks->get_Count(&nItems);

   for (CollectionIndexType idx = 0; idx < nItems; idx++ )
   {
      CComPtr<IUnknown> pUnk;
      arrUnks->get_Item(idx,&pUnk);

      CComQIPtr<IGirderLine> girderLine(pUnk);
      ATLASSERT( girderLine != nullptr );

      GirderIDType ID;
      girderLine->get_ID(&ID);

      std::pair<GirderLineCollection::iterator,bool> insert_result( m_GirderLines.insert( std::make_pair(ID,girderLine) ) );
      if ( insert_result.second == false )
      {
         ATLASSERT(false); // container already has a girder line with ID
         m_GirderLines.erase(insert_result.first); // remove the previously defined girder line
         insert_result = m_GirderLines.insert( std::make_pair(ID,girderLine) );
         ATLASSERT(insert_result.second == true); // WTF happened
         if ( insert_result.second == false )
         {
            return E_FAIL;
         }
      }
   }

   return S_OK;
}

STDMETHODIMP CBridge::FindGirderLine(GirderIDType ID,IGirderLine** ppGirderLine)
{
   CHECK_RETOBJ(ppGirderLine);
   GirderLineCollection::iterator found = m_GirderLines.find(ID);
   if ( found == m_GirderLines.end() )
   {
      return E_FAIL;
   }

   return found->second.CopyTo(ppGirderLine);
}

STDMETHODIMP CBridge::get_GirderLineCount(CollectionIndexType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_GirderLines.size();
   return S_OK;
}

STDMETHODIMP CBridge::CreateDiaphragmLines(IDiaphragmLineFactory* pFactory)
{
   CHECK_IN(pFactory);

   CComPtr<IUnkArray> arrUnks;
   HRESULT hr = pFactory->Create(this,&arrUnks);
   if ( FAILED(hr) )
   {
      return hr;
   }

   CollectionIndexType nItems;
   arrUnks->get_Count(&nItems);

   for (CollectionIndexType idx = 0; idx < nItems; idx++ )
   {
      CComPtr<IUnknown> pUnk;
      arrUnks->get_Item(idx,&pUnk);

      CComQIPtr<IDiaphragmLine> diaphragmLine(pUnk);
      ATLASSERT( diaphragmLine != nullptr );

      LineIDType ID;
      diaphragmLine->get_ID(&ID);

      std::pair<DiaphragmLineCollection::iterator,bool> insert_result = m_DiaphragmLines.insert( std::make_pair(ID,diaphragmLine) );
      if ( insert_result.second == false )
      {
         ATLASSERT(false); // container already has a girder line with ID
         m_DiaphragmLines.erase(insert_result.first); // remove the previously defined girder line
         insert_result = m_DiaphragmLines.insert( std::make_pair(ID,diaphragmLine) );
         ATLASSERT(insert_result.second == true); // WTF happened
         if ( insert_result.second == false )
         {
            return E_FAIL;
         }
      }
   }

   return S_OK;
}

STDMETHODIMP CBridge::FindDiaphragmLine(LineIDType ID,IDiaphragmLine** ppDiaphragmLine)
{
   CHECK_RETOBJ(ppDiaphragmLine);
   DiaphragmLineCollection::iterator found = m_DiaphragmLines.find(ID);
   if ( found == m_DiaphragmLines.end() )
   {
      return E_FAIL;
   }

   return found->second.CopyTo(ppDiaphragmLine);
}

STDMETHODIMP CBridge::get_DiaphragmLineCount(CollectionIndexType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_DiaphragmLines.size();
   return S_OK;
}

STDMETHODIMP CBridge::CreateDeckBoundary(IDeckBoundaryFactory* pFactory)
{
   CHECK_IN(pFactory);
   m_DeckBoundary.Release();
   HRESULT hr = pFactory->Create(this,&m_DeckBoundary);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return S_OK;
}

STDMETHODIMP CBridge::get_DeckBoundary(IDeckBoundary** ppDeckBoundary)
{
   CHECK_RETOBJ(ppDeckBoundary);
   m_DeckBoundary.CopyTo(ppDeckBoundary);
   return S_OK;
}

STDMETHODIMP CBridge::UpdateGeometry(long flag)
{
   ASSERTVALID;

   HRESULT hr = S_OK;
   
   if (flag & GF_BRIDGELINE)
   {
      hr = UpdateBridgeLine();
      if (FAILED(hr))
      {
         return hr;
      }
   }

   if (flag & GF_PIERS)
   {
      hr = UpdatePierGeometry();
      if (FAILED(hr))
      {
         return hr;
      }
   }

   if (flag & GF_GIRDERS)
   {
      hr = UpdateGirderGeometry();
      if (FAILED(hr))
      {
         return hr;
      }
   }

   if (flag & GF_DIAPHRAGMS)
   {
      hr = UpdateDiaphragmGeometry();
      if (FAILED(hr))
      {
         return hr;
      }
   }

   if (flag & GF_DECK)
   {
      hr = UpdateDeckBoundaryGeometry();
      if (FAILED(hr))
      {
         return hr;
      }
   }

   return S_OK;
}


/////////////////////////////////////

HRESULT CBridge::UpdateBridgeLine()
{
   CComPtr<IAlignment> alignment;
   HRESULT hr = get_BridgeAlignment(&alignment);
   if ( FAILED(hr) )
   {
      return hr;
   }

   m_BridgeLine.Release();
   return alignment->CreateOffsetPath(m_AlignmentOffset,&m_BridgeLine);
}

HRESULT CBridge::UpdatePierGeometry()
{
   HRESULT hr = S_OK;

   CComPtr<IEnumPierLines> pEnum;
   m_PierLines->get__EnumPiers(&pEnum);
   CComPtr<IPierLine> pier;
   while( pEnum->Next(1,&pier,nullptr) != S_FALSE )
   {
      CPierLine* pPier = (CPierLine*)pier.p;
      hr = pPier->UpdateGeometry();
      if ( FAILED(hr) )
      {
         return hr;
      }

      pier.Release();
   }

   return S_OK;
}

HRESULT CBridge::UpdateGirderGeometry()
{
   for( const auto& gdrLineEntry : m_GirderLines)
   {
      CComPtr<IGirderLine> girderLine( gdrLineEntry.second );
      CGirderLine* pGirderLine = (CGirderLine*)girderLine.p;
      HRESULT hr = pGirderLine->UpdateGeometry();
      if ( FAILED(hr) )
      {
         return hr;
      }
   }

   return S_OK;
}

HRESULT CBridge::UpdateDiaphragmGeometry()
{
   for( const auto& diaphragmLineEntry : m_DiaphragmLines)
   {
      CComPtr<IDiaphragmLine> DiaphragmLine( diaphragmLineEntry.second );
      CDiaphragmLine* pDiaphragmLine = (CDiaphragmLine*)DiaphragmLine.p;
      HRESULT hr = pDiaphragmLine->UpdateGeometry();
      if ( FAILED(hr) )
      {
         return hr;
      }
   }

   return S_OK;
}

HRESULT CBridge::UpdateDeckBoundaryGeometry()
{
   if ( m_DeckBoundary )
   {
      CDeckBoundary* pDeckBoundary = (CDeckBoundary*)m_DeckBoundary.p;
      return pDeckBoundary->UpdateGeometry();
   }

   return S_OK;
}

#if defined _DEBUG
void CBridge::AssertValid()
{
   PierIndexType nPiers;
   m_PierLines->get_Count(&nPiers);
   ATLASSERT(1 < nPiers); // must be 2 or more piers
}
#endif