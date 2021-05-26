///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2021  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// DiaphragmLine.cpp : Implementation of CDiaphragmLine

#include "stdafx.h"
#include "DiaphragmLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



// CDiaphragmLine
STDMETHODIMP CDiaphragmLine::get_Point(GirderIDType gdrLineID,EndType endType,IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);

   // gdrLineID identifies the girder bay where the diaphragm is located.
   // gdrLineID identifies the girder line on the left hand side of the bay.

   EndPointContainer::iterator found = m_EndPoints.find(gdrLineID);
   if ( found == m_EndPoints.end() )
      return E_INVALIDARG;

   if ( endType == etStart )
      found->second.pntLeft->Clone(ppPoint);
   else
      found->second.pntRight->Clone(ppPoint);

   return S_OK;
}

STDMETHODIMP CDiaphragmLine::get_Length(GirderIDType gdrLineID,Float64* pLength)
{
   CHECK_RETVAL(pLength);

   EndPointContainer::iterator found = m_EndPoints.find(gdrLineID);
   if ( found == m_EndPoints.end() )
      return E_INVALIDARG;

   CComPtr<IPoint2d> p1, p2;
   p1 = found->second.pntLeft;
   p2 = found->second.pntRight;

   return p1->DistanceEx(p2,pLength);
}

STDMETHODIMP CDiaphragmLine::get_ID(LineIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_ID;

   return S_OK;
}

HRESULT CDiaphragmLine::UpdateGeometry()
{
   // clear all the girder line geometry before proceeding
   m_Point[etStart].Release();
   m_Point[etEnd].Release();

   m_EndPoints.clear();

   LocatePoints();
   return S_OK;
}

HRESULT CDiaphragmLine::LocatePoints()
{
   CComPtr<ICogoModel> cogoModel;
   m_pBridge->get_CogoModel(&cogoModel);
   CComPtr<ICogoEngine> cogoEngine;
   cogoModel->get_Engine(&cogoEngine);
   CComQIPtr<ILocate2> locate(cogoEngine);
   CComQIPtr<IMeasure2> measure(cogoEngine);
   CComQIPtr<IIntersect2> intersect(cogoEngine);

   //
   // Locate intersection of diaphragm reference line and the left and right girder lines
   //

   CComPtr<IGirderLine> leftGirderLine, rightGirderLine;
   m_pBridge->FindGirderLine(m_LeftGirderID, &leftGirderLine);
   m_pBridge->FindGirderLine(m_RightGirderID,&rightGirderLine);

   CComPtr<IPath> leftPath, rightPath;
   leftGirderLine->get_Path(&leftPath);
   rightGirderLine->get_Path(&rightPath);

   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> v;
   m_Line->GetExplicit(&p,&v);

   leftPath->Intersect( m_Line,p,&m_Point[etStart]);
   rightPath->Intersect(m_Line,p,&m_Point[etEnd]);

   ATLASSERT(m_Point[etStart] != nullptr);
   ATLASSERT(m_Point[etEnd]   != nullptr);

   if ( m_Point[etStart] == nullptr || m_Point[etEnd] == nullptr )
      return E_FAIL;

   //
   // Find the start and end points of the diaphragm in the girder bays
   //
   CComPtr<IPoint2d> pntLeft = m_Point[etStart];

   for ( GirderIDType gdrID = m_LeftGirderID; gdrID < m_RightGirderID; gdrID++ )
   {
      CComPtr<IGirderLine> girderLine;
      m_pBridge->FindGirderLine(gdrID+1,&girderLine);
      CComPtr<IPath> rightPath;
      girderLine->get_Path(&rightPath);

      CComPtr<IPoint2d> pntRight;
      rightPath->Intersect(m_Line,p,&pntRight);

      EndPoints endPoints;
      endPoints.pntLeft  = pntLeft;
      endPoints.pntRight = pntRight;

      if ( m_bStaggered )
      {
         // find mid-point between pntLeft and pntRight. This is the point the staggered diaphram
         // passes through in the center of the girder bay
         Float64 xl,yl,xr,yr;
         pntLeft->Location(&xl,&yl);
         pntRight->Location(&xr,&yr);
         Float64 cx = (xl+xr)/2;
         Float64 cy = (yl+yr)/2;
         CComPtr<IPoint2d> pntC;
         pntC.CoCreateInstance(CLSID_Point2d);
         pntC->Move(cx,cy);

         // Find the point on the left girder line where the normal passes through (cx,cy)
         endPoints.pntLeft.Release();
         Float64 distFromStart;
         VARIANT_BOOL vbOnProjection;
         leftPath->ProjectPoint(pntC,&endPoints.pntLeft, &distFromStart, &vbOnProjection);

         // Create a line from this point through point (cx,cy)
         CComPtr<ILine2d> staggeredLine;
         staggeredLine.CoCreateInstance(CLSID_Line2d);
         staggeredLine->ThroughPoints(endPoints.pntLeft,pntC);
   
         // Intersect staggered line with the right girder line
         endPoints.pntRight.Release();
         rightPath->Intersect(staggeredLine,pntC,&endPoints.pntRight);
      }

      m_EndPoints.insert( std::make_pair(gdrID,endPoints) );

      pntLeft = pntRight;
      leftPath = rightPath;
   }

   return S_OK;
}
