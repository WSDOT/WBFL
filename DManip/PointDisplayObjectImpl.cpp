///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

// PointDisplayObject.cpp: implementation of the CPointDisplayObjectImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "PointDisplayObjectImpl.h"
#include "SimpleDrawPointStrategyImpl.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
UINT CPointDisplayObjectImpl::ms_cfFormat = ::RegisterClipboardFormat(_T("WBFLDManip.PointDisplayObject"));

CPointDisplayObjectImpl::CPointDisplayObjectImpl()
{
}

CPointDisplayObjectImpl::~CPointDisplayObjectImpl()
{
}

HRESULT CPointDisplayObjectImpl::FinalConstruct()
{
   HRESULT hr;

   SetDisplayObject(this); // Must be called from FinalConstruct and not c'tor

   CComObject<CSimpleDrawPointStrategyImpl>* pStrategy;
   hr = CComObject<CSimpleDrawPointStrategyImpl>::CreateInstance(&pStrategy);
   if ( FAILED(hr) )
      return hr;

   m_pDrawStrategy = pStrategy;

   m_pDragData = 0;

   hr = m_Position.CoCreateInstance(CLSID_Point2d);
   if ( FAILED(hr) )
      return hr;

   m_bAutoUpdate = FALSE;

   return S_OK;
}

void CPointDisplayObjectImpl::FinalRelease()
{
   CDisplayObjectDefaultImpl::Do_FinalRelease();
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::SetPosition(IPoint2d* pos,BOOL bRedraw,BOOL bFireEvent)
{
   if ( bRedraw )
   {
      // Erase the old graphic
      CComPtr<iDisplayList> pDL;
      GetDisplayList(&pDL);

      CComPtr<iDisplayMgr> pDispMgr;
      pDL->GetDisplayMgr(&pDispMgr);

      CRect box = GetBoundingBox();
      pDispMgr->InvalidateRect(box);
   }
   
   // Set the new position
   Float64 currX, currY;
   m_Position->get_X(&currX);
   m_Position->get_Y(&currY);
   m_Position =  pos;

   // Update the position of all the sockets
   SocketContainer::iterator iter;
   for ( iter = m_Sockets.begin(); iter != m_Sockets.end(); iter++ )
   {
      CComPtr<iSocket> pSocket = *iter;
      pSocket->SetPosition(m_Position);
   }

   if ( bRedraw )
   {
      CComPtr<iDisplayList> pDL;
      GetDisplayList(&pDL);

      CComPtr<iDisplayMgr> pDispMgr;
      pDL->GetDisplayMgr(&pDispMgr);

      CRect box = GetBoundingBox();
      pDispMgr->InvalidateRect(box);
   }

   if ( bFireEvent )
   {
      // Compute the amount moved
      Float64 x,y;
      m_Position->get_X(&x);
      m_Position->get_Y(&y);

      CComPtr<ISize2d> offset;
      offset.CoCreateInstance(CLSID_Size2d);
      offset->put_Dx(x - currX);
      offset->put_Dy(y - currY);

      Fire_OnDragMoved(offset);
   }
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::GetPosition(IPoint2d* *pos)
{
   (*pos) = m_Position;
   (*pos)->AddRef();
}

STDMETHODIMP_(CPoint) CPointDisplayObjectImpl::GetPosition()
{
   CComPtr<iDisplayList> pDL;
   GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> map;
   pDispMgr->GetCoordinateMap(&map);

   LONG lx,ly;
   map->WPtoLP(m_Position,&lx,&ly);

   CPoint p(lx,ly);

   return p;
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::Offset(ISize2d* offset,BOOL bRedraw,BOOL bFireEvent)
{
   m_Position->OffsetEx(offset);
   SetPosition(m_Position,bRedraw,bFireEvent);
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::SetDrawingStrategy(iDrawPointStrategy* pStrategy)
{
   m_pDrawStrategy = pStrategy;
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::GetDrawingStrategy(iDrawPointStrategy** pStrategy)
{
   (*pStrategy) = m_pDrawStrategy;
   (*pStrategy)->AddRef();
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::Draw(CDC* pDC)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   m_pDrawStrategy->Draw(this,pDC);
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::Highlite(CDC* pDC,BOOL bHighlite)
{
   if ( !IsVisible() ) // Don't draw if not visible
      return;

   m_pDrawStrategy->DrawHighlite(this,pDC,bHighlite);
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::GetBoundingBox(IRect2d** rect)
{
   m_pDrawStrategy->GetBoundingBox(this, rect);
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::SetDragData(iDragData* dd)
{
   m_pDragData = dd;
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::GetDragData(iDragData** dd)
{
   *dd = m_pDragData;
   (*dd)->AddRef();
}

STDMETHODIMP_(UINT) CPointDisplayObjectImpl::Format()
{
   return ( m_pDragData ) ? m_pDragData->Format() : 0;
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::PrepareDrag(iDragDataSink* pSink)
{
   pSink->CreateFormat(ms_cfFormat);
   Float64 x,y;
   UINT size = sizeof(Float64);

   m_Position->get_X(&x);
   m_Position->get_Y(&y);

   pSink->Write(ms_cfFormat,&x,size);
   pSink->Write(ms_cfFormat,&y,size);

   if ( m_pDragData )
   {
      m_pDragData->PrepareForDrag(this,pSink);
   }
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::OnDrop(iDragDataSource* pSource)
{
   Float64 x,y;
   UINT size = sizeof(Float64);

   pSource->Read(ms_cfFormat,&x,size);
   pSource->Read(ms_cfFormat,&y,size);

   m_Position->put_X(x);
   m_Position->put_Y(y);

  if ( m_pDragData )
     m_pDragData->OnDrop(this,pSource);
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::DrawDragImage(CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint)
{
   m_pDrawStrategy->DrawDragImage(this,pDC,map, dragStart,dragPoint);
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::OnDragMoved(ISize2d* offset)
{
   if (m_bAutoUpdate)
   {
      Offset(offset,TRUE,FALSE); // TRUE = Redraw
                                 // FALSE = don't fire event... We fire it below
   }

   Fire_OnDragMoved(offset);
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::OnMoved()
{
   // This display object got moved onto another drop target
   Fire_OnMoved();
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::OnCopied()
{
   // This display object got copied onto another drop target
   Fire_OnCopied();
}

STDMETHODIMP_(void) CPointDisplayObjectImpl::EnableAutoUpdate(BOOL bEnable)
{
   m_bAutoUpdate = bEnable;
}

STDMETHODIMP_(BOOL) CPointDisplayObjectImpl::IsAutoUpdateEnabled()
{
   return m_bAutoUpdate;
}
