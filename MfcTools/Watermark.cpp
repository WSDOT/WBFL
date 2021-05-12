///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
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

// Watermark.cpp : implementation file
//

#include "stdafx.h"
#include <MFCTools\Watermark.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWatermark

CWatermark::CWatermark()
{
}

CWatermark::~CWatermark()
{
}

int CWatermark::MarkIt( UINT nIDResource, HWND hwnd )
{
   if ( !m_Bitmap.LoadBitmap( nIDResource ) )
      return -1;

   return Subclass( hwnd );
}

int CWatermark::MarkIt( LPCTSTR lpszResourceName, HWND hwnd )
{
   if ( !m_Bitmap.LoadBitmap( lpszResourceName ) )
      return -1;

   return Subclass( hwnd );
}

int CWatermark::Subclass(HWND hwnd)
{
  if ( !SubclassWindow(hwnd) )
   {
      TRACE0("Failed to subclass window\n");
      return -1;
   }

  return 0;
}

BEGIN_MESSAGE_MAP(CWatermark, CWnd)
	//{{AFX_MSG_MAP(CWatermark)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWatermark message handlers

int CWatermark::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

BOOL CWatermark::OnEraseBkgnd(CDC* pDC) 
{
   // If we don't have a valid bitmap, then there is nothing to draw
   // Just use the default behavior
   if ( m_Bitmap.GetSafeHandle() == nullptr )
   {
      return CWnd::OnEraseBkgnd( pDC );
   }


   // Fill the background in gray
   CRect client;
   GetClientRect( &client );
   pDC->FillSolidRect( client, RGB(192,192,192) );

   // Get some info about the bitmap
   BITMAP bm;
   m_Bitmap.GetBitmap( &bm );
   CSize bmp_size( bm.bmWidth, bm.bmHeight );

   // Draw the bitmap
   CDC memdc;
   memdc.CreateCompatibleDC( pDC );
   memdc.SelectObject( m_Bitmap );

   if ( bmp_size.cx > client.Width() ||
        bmp_size.cy > client.Height() )
       {
      // Bitmap is bigger that screen, shrink it to fit
       int edge = min( client.Height(), client.Width());
       CPoint p(client.Width()/2 - edge/2,client.Height()/2 - edge/2);
       pDC->StretchBlt(p.x,p.y,edge,edge,&memdc,0,0,bmp_size.cx,bmp_size.cy,SRCCOPY);
       }
    else
       {
       // bitmap fits just fine.  Center it.
       int x = (client.Width()/2)  - (bmp_size.cx/2);
       int y = (client.Height()/2) - (bmp_size.cy/2);

       pDC->BitBlt(x,y,bmp_size.cx,bmp_size.cy,&memdc,0,0,SRCCOPY);
       }

    return TRUE;
}

void CWatermark::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
   Invalidate();
	
}
