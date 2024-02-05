///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include "helpers.h"

void DrawArrowHead(CDC* pDC,WBFL::DManip::ArrowHeadStyleType style,CPoint left,CPoint tip,CPoint right)
{
   CPoint p[3];
   p[0] = tip;
   p[1] = left;
   p[2] = right;

   switch(style)
   {
   case WBFL::DManip::ArrowHeadStyleType::Lines:
      pDC->MoveTo(p[1]);
      pDC->LineTo(p[0]);
      pDC->LineTo(p[2]);
      break;

   case WBFL::DManip::ArrowHeadStyleType::Open:
      {
         CBrush brush;
         brush.CreateSysColorBrush(COLOR_WINDOW);
         CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&brush);
         pDC->Polygon(p,3);
         pDC->SelectObject(pOldBrush);
      }
      break;

   case WBFL::DManip::ArrowHeadStyleType::Filled:
      // *** DROP THROUGH ***   break;
   default:
      {
         CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(BLACK_BRUSH);
         pDC->Polygon(p,3);
         pDC->SelectObject(pOldBrush);
      }
   };
}

void DrawPointSymbol(CDC* pDC, const RECT& rect, WBFL::DManip::PointType type)
{
   switch (type)
   {
   case WBFL::DManip::PointType::None:
      break; // do nothing

   case WBFL::DManip::PointType::Circle:
   case WBFL::DManip::PointType::Dot:
      pDC->Ellipse(&rect);
      break;

   case WBFL::DManip::PointType::Square:
      pDC->Rectangle(&rect);
      break;

   case WBFL::DManip::PointType::CrossHair:
      pDC->MoveTo(rect.left, (rect.top + rect.bottom)/2);
      pDC->LineTo(rect.right, (rect.top + rect.bottom)/2);
      pDC->MoveTo((rect.left + rect.right)/2, rect.bottom);
      pDC->LineTo((rect.left + rect.right)/2, rect.top);
      break;

   default:
      CHECK(false); // is there a new type?
   }
}

void CreatePen(WBFL::DManip::LineStyleType style, UINT width, COLORREF color,CPen& pen)
{
   DWORD centerStyle[] = { 20, 2, 3, 2 };
   LOGBRUSH lb;
   lb.lbStyle = BS_SOLID;
   lb.lbColor = color;
   lb.lbHatch = 0;
   switch (style)
   {
   case WBFL::DManip::LineStyleType::Null:
      pen.CreatePen(PS_NULL, width, color);
      break;

   case WBFL::DManip::LineStyleType::Solid:
      pen.CreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_JOIN_BEVEL, width, &lb);
      break;

   case WBFL::DManip::LineStyleType::Dot:
      pen.CreatePen(PS_DOT, width, color);
      break;

   case WBFL::DManip::LineStyleType::Dash:
      pen.CreatePen(PS_DASH, width, color);
      break;

   case WBFL::DManip::LineStyleType::Centerline:
      pen.CreatePen(PS_USERSTYLE | PS_GEOMETRIC, width, &lb, sizeof(centerStyle) / sizeof(DWORD), centerStyle);
      break;

   default:
      CHECK(false);
      pen.CreatePen(PS_NULL, width, color);
      break;
   }
}


#if defined _DEBUG
#include <DManip/DisplayObject.h>
#include <DManip/DisplayList.h>
#include <DManip/DisplayMgr.h>

using namespace WBFL::DManip;

Uint64 ObjectRecord::count = 0;
std::vector<ObjectRecord> CircularRefDebugger::ObjectRecords;

iDisplayObject::iDisplayObject()
{
   CircularRefDebugger::Add(ObjectType::DO, this);
}

iDisplayObject::~iDisplayObject()
{
   CircularRefDebugger::Remove(this);
}

iDisplayList::iDisplayList()
{
   CircularRefDebugger::Add(ObjectType::DL, this);
}

iDisplayList::~iDisplayList()
{
   CircularRefDebugger::Remove(this);
}

iDisplayMgr::iDisplayMgr()
{
   CircularRefDebugger::Add(ObjectType::DM, this);
}

iDisplayMgr::~iDisplayMgr()
{
   CircularRefDebugger::Remove(this);
}
#endif