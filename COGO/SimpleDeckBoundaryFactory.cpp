///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// DeckBoundary.cpp : Implementation of CDiaphragm

#include "stdafx.h"
#include "WBFLCogo.h"
#include "SimpleDeckBoundaryFactory.h"
#include <WBFLCogo\CogoHelpers.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

STDMETHODIMP CSimpleDeckBoundaryFactory::put_TransverseEdgeID(EndType end, IDType ID)
{
   m_Factory->SetTransverseEdgeID(WBFL::COGO::EndType(end), ID);
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_TransverseEdgeID(EndType end, IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetTransverseEdgeID(WBFL::COGO::EndType(end));
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_TransverseEdgeType(EndType end, DeckBoundaryEdgeType edgeType)
{
   m_Factory->SetTransverseEdgeType(WBFL::COGO::EndType(end), WBFL::COGO::TransverseEdgeType(edgeType));
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_TransverseEdgeType(EndType end, DeckBoundaryEdgeType* edgeType)
{
   CHECK_RETVAL(edgeType);
   *edgeType = DeckBoundaryEdgeType(m_Factory->GetTransverseEdgeType(WBFL::COGO::EndType(end)));
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_EdgeID(SideType side, IDType ID)
{
   m_Factory->SetEdgeID(WBFL::COGO::SideType(side), ID);
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_EdgeID(SideType side, IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetEdgeID(WBFL::COGO::SideType(side));
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_EdgeBreakID(SideType side, IDType ID)
{
   m_Factory->SetEdgeBreakID(WBFL::COGO::SideType(side), ID);
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_EdgeBreakID(SideType side, IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_Factory->GetEdgeBreakID(WBFL::COGO::SideType(side));
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::put_BreakEdge(EndType end, SideType side, VARIANT_BOOL bBreak)
{
   m_Factory->SetBreakEdge(WBFL::COGO::EndType(end), WBFL::COGO::SideType(side), bBreak == VARIANT_TRUE);
   return S_OK;
}

STDMETHODIMP CSimpleDeckBoundaryFactory::get_BreakEdge(EndType end, SideType side, VARIANT_BOOL* bBreak)
{
   CHECK_RETVAL(bBreak);
   *bBreak = m_Factory->GetBreakEdge(WBFL::COGO::EndType(end), WBFL::COGO::SideType(side)) ? VARIANT_TRUE : VARIANT_FALSE;
   return S_OK;
}


