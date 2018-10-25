///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

// NUSplicedGirderSegment.cpp : Implementation of CNUSplicedGirderSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "NUSplicedGirderSegment.h"
#include <MathEx.h>
#include <algorithm>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNUSplicedGirderSegment
HRESULT CNUSplicedGirderSegment::FinalConstruct()
{
   return S_OK;
}

void CNUSplicedGirderSegment::FinalRelease()
{
}

////////////////////////////////////////////////////////////////////
// ISplicedGirderSegment implementation
//

HRESULT CNUSplicedGirderSegment::GetPrimaryShape(Float64 Xs,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   if (m_Shapes.size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   CComQIPtr<INUGirderSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is nullptr... how did it get in the system????

   // This object reprsents a prismatic shape... all sections are the same
   HRESULT hr = S_OK;
   CComPtr<INUBeam> pcBeam;
   beam->get_Beam(&pcBeam);

   Float64 D1,D2,D3,D4,D5;
   Float64 R1,R2,R3,R4;
   Float64 T;
   Float64 W1,W2;
   Float64 C1;


   pcBeam->get_W1(&W1);
   pcBeam->get_W2(&W2);

   pcBeam->get_D1(&D1);
   pcBeam->get_D2(&D2);
   pcBeam->get_D3(&D3);
   pcBeam->get_D4(&D4);
   pcBeam->get_D5(&D5);

   pcBeam->get_R1(&R1);
   pcBeam->get_R2(&R2);
   pcBeam->get_R3(&R3);
   pcBeam->get_R4(&R4);

   pcBeam->get_T(&T);

   pcBeam->get_C1(&C1);

   Float64 w1 = W1;
   Float64 w2 = W2;
   Float64 d1 = D1;
   Float64 d2 = D2;
   Float64 d3 = D3;
   Float64 d4 = D4;
   Float64 d5 = D5;
   Float64 r1 = R1;
   Float64 r2 = R2;
   Float64 r3 = R3;
   Float64 r4 = R4;
   Float64 t  = T;
   Float64 c1 = C1;

   // Get the end block dimensions
   Float64 Web;
   GetEndBlockWidth(Xs,&Web);

   //
   // Adjust D5 based on the bottom flange height
   // If bottom flange height is zero then don't make any adjustments (take zero to be don't change bottom flange)
   //
   Float64 bottom_flange_height = GetBottomFlangeHeight(Xs);
   if ( !IsZero(bottom_flange_height) )
   {
      d5 = bottom_flange_height;
   }

   if ( d5 < 0 )
   {
      // there really isn't a bottom flange if d5 < 0
      d5 = 0;
   }

   //
   // Adjust D3 based on the spliced girder profile
   //
   Float64 section_height = GetSectionDepth(Xs);
   d3 = section_height - (d1 + d2 + d4 + d5);
   ATLASSERT( 0 <= d3 );

   // create a new shape that is a clone of the original
   CComQIPtr<IShape> shape(beam);
   CComPtr<IShape> newShape;
   hr = shape->Clone(&newShape);

   // set the dimensions
   CComQIPtr<INUGirderSection> newFlangedBeam(newShape);
   CComPtr<INUBeam> newBeam;
   newFlangedBeam->get_Beam(&newBeam);
   newBeam->put_C1(c1);
   newBeam->put_D1(d1);
   newBeam->put_D2(d2);
   newBeam->put_D3(d3);
   newBeam->put_D4(d4);
   newBeam->put_D5(d5);
   newBeam->put_R1(r1);
   newBeam->put_R2(r2);
   newBeam->put_R3(r3);
   newBeam->put_R4(r4);
   newBeam->put_W1(w1);
   newBeam->put_W2(w2);
   newBeam->put_T(t);
   newBeam->put_EndBlock(Web);

   // position the shape
   CComPtr<IPoint2d> pntTopCenter;
   GB_GetSectionLocation(this,Xs,&pntTopCenter);

   CComQIPtr<IXYPosition> position(newFlangedBeam);
   position->put_LocatorPoint(lpTopCenter,pntTopCenter);

   *ppShape = newShape;
   (*ppShape)->AddRef();
   return S_OK;
}

void CNUSplicedGirderSegment::GetEndBlockWidth(Float64 distAlongSegment,Float64* pWendBlock)
{
   Float64 segLength;
   get_Length(&segLength);

   CComQIPtr<INUGirderSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is nullptr... how did it get in the system????

   CComPtr<INUBeam> pcBeam;
   beam->get_Beam(&pcBeam);

   EndType endType;
   if ( distAlongSegment < segLength/2 )
   {
      // at the start end...
      endType = etStart;
   }
   else
   {
      endType = etEnd;
      distAlongSegment = segLength - distAlongSegment; // distAlongSegment is now measured from the left end
   }

   Float64 ebWidth       = m_EndBlockWidth[endType];
   Float64 ebLength      = m_EndBlockLength[endType];
   Float64 ebTransLength = m_EndBlockTransitionLength[endType];

   if ( distAlongSegment < ebLength )
   {
      // in the end block
      *pWendBlock = ebWidth;
   }
   else if ( ::InRange(ebLength,distAlongSegment,ebLength+ebTransLength) )
   {
      // in the end block transition
      Float64 t;
      pcBeam->get_T(&t);
      *pWendBlock = ::LinInterp(distAlongSegment-ebLength,ebWidth,t,ebTransLength);
   }
   else
   {
      // after the end block
      Float64 t;
      pcBeam->get_T(&t);
      *pWendBlock = t;
   }
}
