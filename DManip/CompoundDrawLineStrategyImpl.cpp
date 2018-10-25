///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright (C) 2008  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// CompoundDrawLineStrategyImpl.cpp: implementation of the CCompoundDrawLineStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "CompoundDrawLineStrategyImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompoundDrawLineStrategyImpl::CCompoundDrawLineStrategyImpl()
{
}

CCompoundDrawLineStrategyImpl::~CCompoundDrawLineStrategyImpl()
{
}

HRESULT CCompoundDrawLineStrategyImpl::FinalConstruct()
{
   return S_OK;
}

/////////////////////////////////////////////////////////
// iLineDrawStrategy Implementation

STDMETHODIMP_(void) CCompoundDrawLineStrategyImpl::Draw(iLineDisplayObject* pDO,CDC* pDC)
{
   Strategies::iterator iter;
   for ( iter = m_Strategies.begin(); iter != m_Strategies.end(); iter++ )
   {
      CComPtr<iDrawLineStrategy> strategy(*iter);
      strategy->Draw(pDO,pDC);
   }
}

STDMETHODIMP_(void) CCompoundDrawLineStrategyImpl::DrawDragImage(iLineDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint)
{
   Strategies::iterator iter;
   for ( iter = m_Strategies.begin(); iter != m_Strategies.end(); iter++ )
   {
      CComPtr<iDrawLineStrategy> strategy(*iter);
      strategy->DrawDragImage(pDO,pDC,map,dragStart,dragPoint);
   }
}

STDMETHODIMP_(void) CCompoundDrawLineStrategyImpl::DrawHighlite(iLineDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   Strategies::iterator iter;
   for ( iter = m_Strategies.begin(); iter != m_Strategies.end(); iter++ )
   {
      CComPtr<iDrawLineStrategy> strategy(*iter);
      strategy->DrawHighlite(pDO,pDC,bHighlite);
   }
}

STDMETHODIMP_(void) CCompoundDrawLineStrategyImpl::GetBoundingBox(iLineDisplayObject* pDO,IRect2d** box)
{
   CComPtr<IRect2d> bounding_box;
   bounding_box.CoCreateInstance(CLSID_Rect2d);

   Strategies::iterator iter;
   for ( iter = m_Strategies.begin(); iter != m_Strategies.end(); iter++ )
   {
      CComPtr<IRect2d> rect;
      CComPtr<iDrawLineStrategy> strategy(*iter);

      if ( iter - m_Strategies.begin() == 0 )
      {
         CComPtr<IRect2d> bbox;
         strategy->GetBoundingBox(pDO,&bbox);

         Float64 l,r,t,b;
         bbox->get_Left(&l);
         bbox->get_Right(&r);
         bbox->get_Top(&t);
         bbox->get_Bottom(&b);

         bounding_box->put_Left(l);
         bounding_box->put_Right(r);
         bounding_box->put_Top(t);
         bounding_box->put_Bottom(b);
      }
      else
      {
         strategy->GetBoundingBox(pDO,&rect);
         bounding_box->Union(rect);
      }
   }

   (*box) = bounding_box;
   (*box)->AddRef();
}

/////////////////////////////////////////////////////////
// iSimpleLineDrawStrategy Implementation
STDMETHODIMP_(void) CCompoundDrawLineStrategyImpl::AddStrategy(iDrawLineStrategy* pStrategy)
{
   m_Strategies.push_back(CComPtr<iDrawLineStrategy>(pStrategy));
}

STDMETHODIMP_(void) CCompoundDrawLineStrategyImpl::RemoveStrategy(long index)
{
   m_Strategies.erase(m_Strategies.begin() + index);
}

STDMETHODIMP_(long) CCompoundDrawLineStrategyImpl::Count()
{
   return m_Strategies.size();
}
