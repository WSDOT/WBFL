///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include "pch.h"
#include <DManip/ToolImpl.h>
#include <DManip/DragData.h>

using namespace WBFL::DManip;

CLIPFORMAT Tool::ms_cfFormat = ::RegisterClipboardFormat(_T("WBFLDManip.Tool"));

Tool::~Tool()
{
   if (m_Icon)
      ::DestroyIcon(m_Icon);
}

void Tool::SetID(UINT id)
{
   m_ID = id;
}

UINT Tool::GetID() const
{
   return m_ID;
}

void Tool::SetToolTipText(LPCTSTR lpszToolTipText)
{
   m_strToolTipText = lpszToolTipText;
}

std::_tstring Tool::GetToolTipText() const
{
   return m_strToolTipText;
}

void Tool::SetDragData(std::shared_ptr<iDragData> dd)
{
   m_pDragData = dd;
}

std::shared_ptr<iDragData> Tool::GetDragData()
{
   return m_pDragData;
}

UINT Tool::Format()
{
   if ( m_pDragData )
      return m_pDragData->Format();
   else
      return ms_cfFormat;
}

void Tool::PrepareDrag(std::shared_ptr<iDragDataSink> pSink)
{
   // Save away tool specific data
   pSink->CreateFormat(ms_cfFormat);
   pSink->Write(ms_cfFormat,(void*)&m_ID,sizeof(m_ID));
   pSink->Write(ms_cfFormat,(void*)&m_hIconInstance,sizeof(m_hIconInstance));
   pSink->Write(ms_cfFormat,(void*)&m_IconResId,sizeof(m_IconResId));

   if ( m_pDragData )
      m_pDragData->PrepareForDrag(nullptr,pSink);
}

void Tool::OnDrop(std::shared_ptr<iDragDataSource> pSource)
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
      m_pDragData->OnDrop(nullptr,pSource);
}

void Tool::OnDragMoved(const WBFL::Geometry::Size2d& offset)
{
}

void Tool::OnMoved()
{
}

void Tool::OnCopied()
{
}

void Tool::DrawDragImage(CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint)
{
   const int SZ(42); // The icon size is 32, but windows 10 can stretch it and cause the BitBlt calls not to fully mask the icon 
                     // leaving trails per mantis 784. Soon we will need to deal with High DPI monitors but not yet.

   CSize offset(-SZ/2,-SZ);

   if (m_Icon != nullptr)
   {
      // move icon so bottom center is at point
      CPoint newPoint(dragPoint);
      newPoint.Offset( offset );

      if (m_First)
      {
         // first time through - create memory dc/bitmap and save off portion of screen under our icon
         m_MemDC.CreateCompatibleDC(pDC);
         m_Bitmap.CreateCompatibleBitmap(pDC, SZ, SZ);
         m_MemDC.SelectObject(m_Bitmap);

         BOOL st = m_MemDC.BitBlt(0,0,SZ,SZ,pDC,newPoint.x, newPoint.y,SRCCOPY);
         ATLASSERT(st);
         m_First = false;
      }
      else
      {
         // draw saved location
         BOOL st =pDC->BitBlt(m_OldPoint.x, m_OldPoint.y, SZ, SZ, &m_MemDC, 0,0, SRCCOPY);
         ATLASSERT(st);

         // save new location
         st = m_MemDC.BitBlt(0,0,SZ,SZ,pDC,newPoint.x, newPoint.y,SRCCOPY);
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

HRESULT Tool::SetIcon(HINSTANCE hInstance, WORD iconResId)
{
   m_hIconInstance = hInstance;
   m_IconResId     = iconResId;

   this->LoadIcon();

   if (m_Icon != nullptr)
      return S_OK;
   else
      return E_FAIL;
}

void Tool::LoadIcon()
{
   // load the 16x16 version
   m_Icon = (HICON) ::LoadImage(m_hIconInstance, MAKEINTRESOURCE(m_IconResId),IMAGE_ICON,32,32,LR_DEFAULTCOLOR);
}