///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

// CompoundDrawPointStrategyImpl.cpp: implementation of the CCompoundDrawPointStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "CompoundDrawPointStrategyImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompoundDrawPointStrategyImpl::CCompoundDrawPointStrategyImpl()
{
}

CCompoundDrawPointStrategyImpl::~CCompoundDrawPointStrategyImpl()
{
}

HRESULT CCompoundDrawPointStrategyImpl::FinalConstruct()
{
   return S_OK;
}

/////////////////////////////////////////////////////////
// iPointDrawStrategy Implementation

STDMETHODIMP_(void) CCompoundDrawPointStrategyImpl::Draw(iPointDisplayObject* pDO,CDC* pDC)
{
   Strategies::iterator iter;
   for ( iter = m_Strategies.begin(); iter != m_Strategies.end(); iter++ )
   {
      CComPtr<iDrawPointStrategy> strategy(*iter);
      strategy->Draw(pDO,pDC);
   }
}

STDMETHODIMP_(void) CCompoundDrawPointStrategyImpl::DrawDragImage(iPointDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint)
{
   Strategies::iterator iter;
   for ( iter = m_Strategies.begin(); iter != m_Strategies.end(); iter++ )
   {
      CComPtr<iDrawPointStrategy> strategy(*iter);
      strategy->DrawDragImage(pDO,pDC,map,dragStart,dragPoint);
   }
}

STDMETHODIMP_(void) CCompoundDrawPointStrategyImpl::DrawHighlite(iPointDisplayObject* pDO,CDC* pDC,BOOL bHighlite)
{
   Strategies::iterator iter;
   for ( iter = m_Strategies.begin(); iter != m_Strategies.end(); iter++ )
   {
      CComPtr<iDrawPointStrategy> strategy(*iter);
      strategy->DrawHighlite(pDO,pDC,bHighlite);
   }
}

STDMETHODIMP_(void) CCompoundDrawPointStrategyImpl::GetBoundingBox(iPointDisplayObject* pDO,IRect2d** box)
{
   CComPtr<IRect2d> bounding_box;
   bounding_box.CoCreateInstance(CLSID_Rect2d);

   Strategies::iterator iter;
   for ( iter = m_Strategies.begin(); iter != m_Strategies.end(); iter++ )
   {
      CComPtr<IRect2d> rect;
      CComPtr<iDrawPointStrategy> strategy(*iter);

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
// iSimplePointDrawStrategy Implementation
STDMETHODIMP_(void) CCompoundDrawPointStrategyImpl::AddStrategy(iDrawPointStrategy* pStrategy)
{
   m_Strategies.push_back(CComPtr<iDrawPointStrategy>(pStrategy));
}

STDMETHODIMP_(void) CCompoundDrawPointStrategyImpl::RemoveStrategy(CollectionIndexType index)
{
   m_Strategies.erase(m_Strategies.begin() + index);
}

STDMETHODIMP_(void) CCompoundDrawPointStrategyImpl::GetStrategy(CollectionIndexType index, iDrawPointStrategy** ppStrategy)
{
   m_Strategies[index].CopyTo(ppStrategy);
}

STDMETHODIMP_(CollectionIndexType) CCompoundDrawPointStrategyImpl::Count()
{
   return m_Strategies.size();
}
