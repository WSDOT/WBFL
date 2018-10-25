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
#include "helpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void DrawArrowHead(CDC* pDC,DManip::ArrowHeadStyleType style,CPoint left,CPoint tip,CPoint right)
{
   CPoint p[3];
   p[0] = tip;
   p[1] = left;
   p[2] = right;

   switch(style)
   {
   case DManip::ahsLines:
      pDC->MoveTo(p[1]);
      pDC->LineTo(p[0]);
      pDC->LineTo(p[2]);
      break;

   case DManip::ahsOpen:
      {
         CBrush brush;
         brush.CreateSysColorBrush(COLOR_WINDOW);
         CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&brush);
         pDC->Polygon(p,3);
         pDC->SelectObject(pOldBrush);
      }
      break;

   case DManip::ahsFilled:
      // *** DROP THROUGH ***   break;
   default:
      {
         CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(BLACK_BRUSH);
         pDC->Polygon(p,3);
         pDC->SelectObject(pOldBrush);
      }
   };
}
