///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2019  Washington State Department of Transportation
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

// SimpleDeckBoundaryFactory.cpp : Implementation of CSimpleDeckBoundaryFactory

#include "stdafx.h"
#include "SimpleDeckBoundaryFactory.h"
#include "DeckBoundary.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CSimpleDeckBoundaryFactory
STDMETHODIMP CSimpleDeckBoundaryFactory::put_TransverseEdgeID(EndType end,LineIDType ID)
{
   m_TransverseEdgeID[end] = ID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_TransverseEdgeID(EndType end,LineIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_TransverseEdgeID[end];
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_TransverseEdgeType(EndType end,DeckBoundaryEdgeType edgeType)
{
   m_TransverseEdgeType[end] = edgeType;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_TransverseEdgeType(EndType end,DeckBoundaryEdgeType* edgeType)
{
   CHECK_RETVAL(edgeType);
   *edgeType = m_TransverseEdgeType[end];
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_EdgeID(SideType side, PathIDType ID)
{
   m_EdgeID[side] = ID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_EdgeID(SideType side,PathIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_EdgeID[side];
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_EdgeBreakID(SideType side,PathIDType ID)
{
   m_EdgeBreakID[side] = ID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_EdgeBreakID(SideType side,PathIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_EdgeBreakID[side];
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_BreakEdge(EndType end,SideType side,VARIANT_BOOL bBreak)
{
   m_vbBreakEdge[end][side] = bBreak;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_BreakEdge(EndType end,SideType side,VARIANT_BOOL* bBreak)
{
   CHECK_RETVAL(bBreak);
   *bBreak = m_vbBreakEdge[end][side];
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::Create(IBridgeGeometry* pBridge,IDeckBoundary** ppDeckBoundary)
{
   CHECK_IN(pBridge);
   CHECK_RETOBJ(ppDeckBoundary);

   CComObject<CDeckBoundary>* pDeckBoundary;
   CComObject<CDeckBoundary>::CreateInstance(&pDeckBoundary);
   (*ppDeckBoundary) = pDeckBoundary;
   (*ppDeckBoundary)->AddRef();

   pDeckBoundary->m_pBridge = pBridge;

   // validate creation parameters
   for ( int i = 0; i < 2; i++ )
   {
      EndType end = (EndType)i;
      
      ATLASSERT(m_TransverseEdgeID[end] != INVALID_ID);
      if ( m_TransverseEdgeID[end] == INVALID_ID )
      {
         return E_INVALIDARG;
      }
#if defined _DEBUG
      else
      {
         // Check to see if reference line is defined. It is ok if it is not defined as long as it
         // gets defined before the overall bridge geometry is updated. These asserts are just a 
         // heads-up warning for the developer
         if ( m_TransverseEdgeType[end] == setPier )
         {
            CComPtr<IPierLine> pier;
            ATLASSERT( SUCCEEDED(pBridge->FindPierLine(m_TransverseEdgeID[end],&pier)) );
         }
         else
         {
            CComPtr<IPath> path;
            ATLASSERT( SUCCEEDED(pBridge->FindLayoutLine(m_TransverseEdgeID[end],&path)) );
         }
      }
#endif

      SideType side = (SideType)i;
      ATLASSERT( m_EdgeID[side] != INVALID_INDEX );
      if ( m_EdgeID[side] == INVALID_INDEX )
      {
         return E_INVALIDARG;
      }
#if defined _DEBUG
      else
      {
         // Check to see if reference line is defined. It is ok if it is not defined as long as it
         // gets defined before the overall bridge geometry is updated. These asserts are just a 
         // heads-up warning for the developer
         CComPtr<IPath> path;
         ATLASSERT( SUCCEEDED(pBridge->FindLayoutLine(m_EdgeID[side],&path)) );
      }
#endif

      if ( (m_vbBreakEdge[etStart][side] == VARIANT_TRUE || m_vbBreakEdge[etEnd][side] == VARIANT_TRUE) )
      {
         if ( m_EdgeBreakID[side] == INVALID_INDEX )
         {
            ATLASSERT(false);
            return E_INVALIDARG;
         }
#if defined _DEBUG
         else
         {
            // Check to see if reference line is defined. It is ok if it is not defined as long as it
            // gets defined before the overall bridge geometry is updated. These asserts are just a 
            // heads-up warning for the developer
            CComPtr<IPath> path;
            ATLASSERT( SUCCEEDED(pBridge->FindLayoutLine(m_EdgeBreakID[side],&path)) );
         }
#endif
      }

      pDeckBoundary->m_TransverseEdgeID[end]   = m_TransverseEdgeID[end];
      pDeckBoundary->m_TransverseEdgeType[end] = m_TransverseEdgeType[end];

      pDeckBoundary->m_EdgeID[side]       = m_EdgeID[side];
      pDeckBoundary->m_EdgeBreakID[side]  = m_EdgeBreakID[side];

      pDeckBoundary->m_vbBreakEdge[etStart][side] = m_vbBreakEdge[etStart][side];
      pDeckBoundary->m_vbBreakEdge[etEnd][side]   = m_vbBreakEdge[etEnd][side];
   }

   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::Reset()
{
   for ( int i = 0; i < 2; i++ )
   {
      EndType end = (EndType)i;

      m_TransverseEdgeID[end]   = INVALID_INDEX;
      m_TransverseEdgeType[end] = setLayout;

      m_EdgeID[end]       = INVALID_INDEX;
      m_EdgeBreakID[end]  = INVALID_INDEX;

      m_vbBreakEdge[end][stLeft]  = VARIANT_FALSE;
      m_vbBreakEdge[end][stRight] = VARIANT_FALSE;
   }

   return S_OK;
}
