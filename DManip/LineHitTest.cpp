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

#include "stdafx.h"
#include <DManip\DManip.h>
#include "LineHitTest.h"
#include <Math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CLineHitTest::HitTest(iDisplayObject* pDO,IPoint2d* pStart,IPoint2d* pEnd,CPoint point)
{
   CRect box = GetHitRect(pDO, pStart, pEnd);

   return box.PtInRect(point);
}

CRect CLineHitTest::GetHitRect(iDisplayObject* pDO, IPoint2d* pStart, IPoint2d* pEnd)
{
   CComPtr<iDisplayList> pDL;
   pDO->GetDisplayList(&pDL);

   CComPtr<iDisplayMgr> pDispMgr;
   pDL->GetDisplayMgr(&pDispMgr);

   CComPtr<iCoordinateMap> pMap;
   pDispMgr->GetCoordinateMap(&pMap);

   // convert start and end in to logical space
   Float64 startWX, startWY, endWX, endWY;
   pMap->MPtoWP(pStart, &startWX, &startWY);
   pMap->MPtoWP(pEnd, &endWX, &endWY);

   CPoint start, end;
   pMap->WPtoLP(startWX, startWY, &start.x, &start.y);
   pMap->WPtoLP(endWX, endWY, &end.x, &end.y);

   CRect box(start, end);
   box.InflateRect(4, 4);

   return box;
}
