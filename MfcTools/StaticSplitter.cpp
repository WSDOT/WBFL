///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2011  Washington State Department of Transportation
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

// StaticSplitter.cpp : implementation file
//

#include "stdafx.h"
#include <MfcTools\StaticSplitter.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDynamicSplitter, CSplitterWnd)

CDynamicSplitter::CDynamicSplitter() :
m_FirstPaneFraction(.50)
{
}

CDynamicSplitter::~CDynamicSplitter()
{
}

BEGIN_MESSAGE_MAP(CDynamicSplitter, CSplitterWnd)
	//{{AFX_MSG_MAP(CDynamicSplitter)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynamicSplitter message handlers
//

void CDynamicSplitter::SetFirstPaneFraction(Float64 frac)
{
   ASSERT(frac<=1.0); 
   ASSERT(frac>=0.0);
   m_FirstPaneFraction = frac;
}

Float64  CDynamicSplitter::GetFirstPaneFraction() const
{
   return m_FirstPaneFraction;
}

void CDynamicSplitter::OnSize(UINT nType, int cx, int cy)
{
   if ( cy > 0 )
   {
      int hPane1;
      int hPane2;
      int hPaneMin;

      GetRowInfo(0,hPane1,hPaneMin);
      GetRowInfo(1,hPane2,hPaneMin);

      int h = hPane1 + hPane2 + m_cySplitterGap + 2*m_cyBorder;

      hPane1 *= cy;
      hPane1 /= h;

      hPane2 *= cy;
      hPane2 /= h;

      if ( 0 < hPane1 && 0 < hPane2 )
      {
         SetRowInfo(0,hPane1,hPaneMin);
         SetRowInfo(1,hPane2,hPaneMin);
      }
   }

   CSplitterWnd::OnSize(nType, cx, cy);
}

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitter

IMPLEMENT_DYNCREATE(CStaticSplitter, CDynamicSplitter)

CStaticSplitter::CStaticSplitter()
{
}

CStaticSplitter::~CStaticSplitter()
{
}

BEGIN_MESSAGE_MAP(CStaticSplitter, CDynamicSplitter)
	//{{AFX_MSG_MAP(CStaticSplitter)
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitter message handlers
//
LRESULT CStaticSplitter::OnNcHitTest(CPoint point)
{
   return HTNOWHERE;
}

void CStaticSplitter::OnSize(UINT nType, int cx, int cy) 
{
   if ( cy > 0 )
   {
      int hPane1 = int(GetFirstPaneFraction() * cy);
      int hPane2 = cy - hPane1;
	
      SetRowInfo(0,hPane1,3*hPane1/8);   
      SetRowInfo(1,hPane2,3*hPane2/8);   

      // There is no need to call RecalcLayout() because the OnSize call below
      // will call it.
   }

   //CDynamicSplitter::OnSize(nType, cx, cy);
   CSplitterWnd::OnSize(nType, cx, cy);
}
