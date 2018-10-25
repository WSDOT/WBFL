// SimpleDeckBoundaryFactory.cpp : Implementation of CSimpleDeckBoundaryFactory

#include "stdafx.h"
#include "SimpleDeckBoundaryFactory.h"
#include "DeckBoundary.h"


// CSimpleDeckBoundaryFactory
STDMETHODIMP CSimpleDeckBoundaryFactory::put_BackEdgeID(LineIDType ID)
{
   m_BackEdgeID = ID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_BackEdgeID(LineIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_BackEdgeID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_BackEdgeType(DeckBoundaryEdgeType edgeType)
{
   m_BackEdgeType = edgeType;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_BackEdgeType(DeckBoundaryEdgeType* edgeType)
{
   CHECK_RETVAL(edgeType);
   *edgeType = m_BackEdgeType;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_ForwardEdgeID(LineIDType ID)
{
   m_ForwardEdgeID = ID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_ForwardEdgeID(LineIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_ForwardEdgeID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_ForwardEdgeType(DeckBoundaryEdgeType edgeType)
{
   m_ForwardEdgeType = edgeType;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_ForwardEdgeType(DeckBoundaryEdgeType* edgeType)
{
   CHECK_RETVAL(edgeType);
   *edgeType = m_ForwardEdgeType;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_LeftEdgeID(LineIDType ID)
{
   m_LeftEdgeID = ID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_LeftEdgeID(LineIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_LeftEdgeID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_RightEdgeID(LineIDType ID)
{
   m_RightEdgeID = ID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_RightEdgeID(LineIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_RightEdgeID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_LeftEdgeBreakID(LineIDType ID)
{
   m_LeftEdgeBreakID = ID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_LeftEdgeBreakID(LineIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_LeftEdgeBreakID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_RightEdgeBreakID(LineIDType ID)
{
   m_RightEdgeBreakID = ID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_RightEdgeBreakID(LineIDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_RightEdgeBreakID;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_BreakLeftEdge(EndType end,VARIANT_BOOL bBreak)
{
   m_vbBreakLeftEdge[end] = bBreak;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_BreakLeftEdge(EndType end,VARIANT_BOOL* bBreak)
{
   CHECK_RETVAL(bBreak);
   *bBreak = m_vbBreakLeftEdge[end];
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_BreakRightEdge(EndType end,VARIANT_BOOL bBreak)
{
   m_vbBreakRightEdge[end] = bBreak;
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_BreakRightEdge(EndType end,VARIANT_BOOL* bBreak)
{
   CHECK_RETVAL(bBreak);
   *bBreak = m_vbBreakRightEdge[end];
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

   // validate creation parameters
   ATLASSERT( m_BackEdgeID != INVALID_INDEX );
   if ( m_BackEdgeID == INVALID_INDEX )
   {
      return E_INVALIDARG;
   }
#if defined _DEBUG
   else
   {
      // Check to see if reference line is defined. It is ok if it is not defined as long as it
      // gets defined before the overall bridge geometry is updated. These asserts are just a 
      // heads-up warning for the developer
      if ( m_BackEdgeType == setPier )
      {
         CComPtr<IPierLine> pier;
         ATLASSERT( SUCCEEDED(pBridge->FindPierLine(m_BackEdgeID,&pier)) );
      }
      else
      {
         CComPtr<IPath> path;
         ATLASSERT( SUCCEEDED(pBridge->FindLayoutLine(m_BackEdgeID,&path)) );
      }
   }
#endif

   ATLASSERT( m_ForwardEdgeID != INVALID_INDEX );
   if ( m_ForwardEdgeID == INVALID_INDEX )
   {
      return E_INVALIDARG;
   }
#if defined _DEBUG
   else
   {
      // Check to see if reference line is defined. It is ok if it is not defined as long as it
      // gets defined before the overall bridge geometry is updated. These asserts are just a 
      // heads-up warning for the developer
      if ( m_ForwardEdgeType == setPier )
      {
         CComPtr<IPierLine> pier;
         ATLASSERT( SUCCEEDED(pBridge->FindPierLine(m_ForwardEdgeID,&pier)) );
      }
      else
      {
         CComPtr<IPath> path;
         ATLASSERT( SUCCEEDED(pBridge->FindLayoutLine(m_ForwardEdgeID,&path)) );
      }
   }
#endif

   ATLASSERT( m_LeftEdgeID != INVALID_INDEX );
   if ( m_LeftEdgeID == INVALID_INDEX )
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
      ATLASSERT( SUCCEEDED(pBridge->FindLayoutLine(m_LeftEdgeID,&path)) );
   }
#endif

   ATLASSERT( m_RightEdgeID != INVALID_INDEX );
   if ( m_RightEdgeID == INVALID_INDEX )
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
      ATLASSERT( SUCCEEDED(pBridge->FindLayoutLine(m_RightEdgeID,&path)) );
   }
#endif

   if ( (m_vbBreakLeftEdge[etStart] == VARIANT_TRUE || m_vbBreakLeftEdge[etEnd] == VARIANT_TRUE) )
   {
      if ( m_LeftEdgeBreakID == INVALID_INDEX )
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
         ATLASSERT( SUCCEEDED(pBridge->FindLayoutLine(m_LeftEdgeBreakID,&path)) );
      }
#endif
   }

   if ( (m_vbBreakRightEdge[etStart] == VARIANT_TRUE || m_vbBreakRightEdge[etEnd] == VARIANT_TRUE) )
   {
      if ( m_RightEdgeBreakID == INVALID_INDEX )
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
         ATLASSERT( SUCCEEDED(pBridge->FindLayoutLine(m_RightEdgeBreakID,&path)) );
      }
#endif
   }

   pDeckBoundary->m_pBridge = pBridge;

   pDeckBoundary->m_BackEdgeID   = m_BackEdgeID;
   pDeckBoundary->m_BackEdgeType = m_BackEdgeType;

   pDeckBoundary->m_ForwardEdgeID   = m_ForwardEdgeID;
   pDeckBoundary->m_ForwardEdgeType = m_ForwardEdgeType;

   pDeckBoundary->m_LeftEdgeID       = m_LeftEdgeID;
   pDeckBoundary->m_RightEdgeID      = m_RightEdgeID;
   pDeckBoundary->m_LeftEdgeBreakID  = m_LeftEdgeBreakID;
   pDeckBoundary->m_RightEdgeBreakID = m_RightEdgeBreakID;

   pDeckBoundary->m_vbBreakLeftEdge[etStart] = m_vbBreakLeftEdge[etStart];
   pDeckBoundary->m_vbBreakLeftEdge[etEnd]   = m_vbBreakLeftEdge[etEnd];
      
   pDeckBoundary->m_vbBreakRightEdge[etStart] = m_vbBreakRightEdge[etStart];
   pDeckBoundary->m_vbBreakRightEdge[etEnd]   = m_vbBreakRightEdge[etEnd];

   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::Reset()
{
#pragma Reminder("IMPLEMENT: CSimpleDeckBoundaryFactory::Reset")
   return S_OK;
}
