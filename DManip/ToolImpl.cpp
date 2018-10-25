///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

#include "stdafx.h"
#include <WBFLDManip.h>
#include <DManip\DManip.h>
#include "ToolImpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLIPFORMAT CToolImpl::ms_cfFormat = ::RegisterClipboardFormat(_T("WBFLDManip.Tool"));

CToolImpl::CToolImpl() :
m_ID(-1), 
m_strToolTipText(""),
m_hIconInstance(0),
m_IconResId(0),
m_Icon(NULL),
m_First(true),
m_bDrawIcon(true)
{
   m_pDragData = NULL;
}

CToolImpl::~CToolImpl()
{
   if (m_Icon)
      ::DestroyIcon(m_Icon);
}

STDMETHODIMP_(void) CToolImpl::SetID(UINT id)
{
   m_ID = id;
}

UINT CToolImpl::GetID()
{
   return m_ID;
}

STDMETHODIMP_(void) CToolImpl::SetToolTipText(LPCTSTR lpszToolTipText)
{
   m_strToolTipText = lpszToolTipText;
}

STDMETHODIMP_(CString) CToolImpl::GetToolTipText()
{
   return m_strToolTipText;
}

STDMETHODIMP_(void) CToolImpl::SetDragData(iDragData* dd)
{
   m_pDragData = dd;
}

STDMETHODIMP_(void) CToolImpl::GetDragData(iDragData** dd)
{
   (*dd) = m_pDragData;
   (*dd)->AddRef();
}

STDMETHODIMP_(UINT) CToolImpl::Format()
{
   if ( m_pDragData )
      return m_pDragData->Format();
   else
      return ms_cfFormat;
}

STDMETHODIMP_(void) CToolImpl::PrepareDrag(iDragDataSink* pSink)
{
   // Save away tool specific data
   pSink->CreateFormat(ms_cfFormat);
   pSink->Write(ms_cfFormat,(void*)&m_ID,sizeof(m_ID));
   pSink->Write(ms_cfFormat,(void*)&m_hIconInstance,sizeof(m_hIconInstance));
   pSink->Write(ms_cfFormat,(void*)&m_IconResId,sizeof(m_IconResId));

   if ( m_pDragData )
      m_pDragData->PrepareForDrag(NULL,pSink);
}

STDMETHODIMP_(void) CToolImpl::OnDrop(iDragDataSource* pSource)
{
   pSource->PrepareFormat(ms_cfFormat);
   pSource->Read(ms_cfFormat,(void*)&m_ID,sizeof(m_ID));
   pSource->Read(ms_cfFormat,(void*)&m_hIconInstance,sizeof(m_hIconInstance));
   pSource->Read(ms_cfFormat,(void*)&m_IconResId,sizeof(m_IconResId));

   if (m_IconResId != 0)
   {
      this->LoadIcon();
   }

   if ( m_pDragData )
      m_pDragData->OnDrop(NULL,pSource);
}

STDMETHODIMP_(void) CToolImpl::OnDragMoved(ISize2d* offset)
{
}

STDMETHODIMP_(void) CToolImpl::OnMoved()
{
}

STDMETHODIMP_(void) CToolImpl::OnCopied()
{
}

STDMETHODIMP_(void) CToolImpl::DrawDragImage(CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint)
{
   CSize offset(-16,-32);


   if (m_Icon != NULL)
   {
      // move icon so bottom center is at point
      CPoint newPoint(dragPoint);
      newPoint.Offset( offset );

      if (m_First)
      {
         // first time through - create memory dc/bitmap and save off portion of screen under our icon
         m_MemDC.CreateCompatibleDC(pDC);
         m_Bitmap.CreateCompatibleBitmap(pDC, 32, 32);
         m_MemDC.SelectObject(m_Bitmap);

         BOOL st = m_MemDC.BitBlt(0,0,32,32,pDC,newPoint.x, newPoint.y,SRCCOPY);
         ATLASSERT(st);
         m_First = false;
      }
      else
      {
         // draw saved location
         BOOL st =pDC->BitBlt(m_OldPoint.x, m_OldPoint.y, 32, 32, &m_MemDC, 0,0, SRCCOPY);
         ATLASSERT(st);

         // save new location
         st = m_MemDC.BitBlt(0,0,32,32,pDC,newPoint.x, newPoint.y,SRCCOPY);
         ATLASSERT(st);
      }

      m_OldPoint = newPoint;

      if ( m_bDrawIcon )
      {
         pDC->DrawIcon(newPoint, m_Icon);
         m_bDrawIcon = false;
      }
      else
      {
         m_bDrawIcon = true;
      }


   }
}

STDMETHODIMP_(HRESULT) CToolImpl::SetIcon(HINSTANCE hInstance, WORD iconResId)
{
   m_hIconInstance = hInstance;
   m_IconResId     = iconResId;

   this->LoadIcon();

   if (m_Icon != NULL)
      return S_OK;
   else
      return E_FAIL;
}

void CToolImpl::LoadIcon()
{
   // load the 16x16 version
   m_Icon = (HICON) ::LoadImage(m_hIconInstance, MAKEINTRESOURCE(m_IconResId),IMAGE_ICON,32,32,LR_DEFAULTCOLOR);
}