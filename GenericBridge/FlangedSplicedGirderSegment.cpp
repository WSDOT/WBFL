///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// FlangedSplicedGirderSegment.cpp : Implementation of CFlangedSplicedGirderSegment
#include "stdafx.h"
#include "WBFLGenericBridge.h"
#include "FlangedSplicedGirderSegment.h"
#include <MathEx.h>
#include <algorithm>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlangedSplicedGirderSegment
HRESULT CFlangedSplicedGirderSegment::FinalConstruct()
{
   return S_OK;
}

void CFlangedSplicedGirderSegment::FinalRelease()
{
}

////////////////////////////////////////////////////////////////////
// ISplicedGirderSegment implementation
//

HRESULT CFlangedSplicedGirderSegment::GetPrimaryShape(Float64 Xs,IShape** ppShape)
{
   CHECK_RETOBJ(ppShape);

   if (m_Shapes.size() == 0 )
   {
      *ppShape = 0;
      return S_OK;
   }

   CComQIPtr<IFlangedGirderSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is NULL... how did it get in the system????

   // This object reprsents a prismatic shape... all sections are the same
   HRESULT hr = S_OK;
   CComPtr<IPrecastBeam> pcBeam;
   beam->get_Beam(&pcBeam);

   Float64 W1, W2, W3, W4;
   Float64 D1, D2, D3, D4, D5, D6, D7;
   Float64 T1, T2;
   Float64 C1;

   pcBeam->get_W1(&W1);
   pcBeam->get_W2(&W2);
   pcBeam->get_W3(&W3);
   pcBeam->get_W4(&W4);

   pcBeam->get_D1(&D1);
   pcBeam->get_D2(&D2);
   pcBeam->get_D3(&D3);
   pcBeam->get_D4(&D4);
   pcBeam->get_D5(&D5);
   pcBeam->get_D6(&D6);
   pcBeam->get_D7(&D7);

   pcBeam->get_T1(&T1);
   pcBeam->get_T2(&T2);

   pcBeam->get_C1(&C1);

   Float64 w1 = W1;
   Float64 w2 = W2;
   Float64 w3 = W3;
   Float64 w4 = W4;
   Float64 d1 = D1;
   Float64 d2 = D2;
   Float64 d3 = D3;
   Float64 d4 = D4;
   Float64 d5 = D5;
   Float64 d6 = D6;
   Float64 d7 = D7;
   Float64 t1 = T1;
   Float64 t2 = T2;
   Float64 c1 = C1;

   // Get the end block dimensions
   Float64 Wt, Wb;
   GetEndBlockWidth(Xs,&Wt,&Wb);

   // adjust dimensions based on end block size

   // near top flange
   if ( 2*(W1+W2) + T1 < Wt )
   {
      // end block is wider than the top flange
      w1 = 0;
      w2 = 0;
      d1 = 0;
      d2 = 0;
      d3 = 0;
      d7 += D1 + D2 + D3;
      t1 = Wt;
   }
   else if ( W2 + T1/2 < Wt/2)
   {
      // end block extends beyond top fillet
      w2 = 0;
      w1 = W1 + W2 + T1/2 - Wt/2;
      w1 = (IsZero(w1) ? 0 : w1); // eliminate noise
      d2 = (D2/W1)*w1;
      d3 = D3 + (D2 - d2);
      t1 = Wt;
   }
   else if ( T1/2 < Wt/2)
   {
      // end block intersects top fillet
      w2 = W2 + T1/2 - Wt/2;
      d3 = (D3/W2)*w2;
      d7 += (D3 - d3);
      t1 = Wt;
   }

   // near bottom flange
   if ( 2*(W3+W4) + T2 < Wb )
   {
      // end block is wider than the bottom flange
      w3 = 0;
      w4 = 0;
      d4 = 0;
      d5 = 0;
      d6 = 0;
      d7 += D4 + D5 + D6;
      t2 = Wb;
   }
   else if ( W4 + T2/2 < Wb/2 )
   {
      // end block extends beyond bottom fillet
      w4 = 0;
      w3 = W3 + W4 + T2/2 - Wb/2;
      w3 = (IsZero(w3) ? 0 : w3); // eliminate noise
      d5 = (D5/W3)*w3;
      d6 = D6 + (D5 - d5);
      t2 = Wb;
   }
   else if ( T2/2 < Wb/2)
   {
      // end block intersects bottom fillet
      w4 = W4 + T2/2 - Wb/2;
      d6 = (D6/W4)*w4;
      d7 += D6 - d6;
      t2 = Wb;
   }

   // verify girder height is unchanged
   ATLASSERT(IsEqual(d1+d2+d3+d4+d5+d6+d7,D1+D2+D3+D4+D5+D6+D7));
   ATLASSERT(IsEqual(2*(w1+w2)+t1,2*(W1+W2)+T1) || IsEqual(2*(w1+w2)+t1,Wt));
   ATLASSERT(IsEqual(2*(w3+w4)+t2,2*(W3+W4)+T2) || IsEqual(2*(w3+w4)+t2,Wb));

   //
   // Adjust D4 based on the bottom flange height
   // If bottom flange height is zero then don't make any adjustments (take zero to be don't change bottom flange)
   //
   Float64 bottom_flange_height = GetBottomFlangeHeight(Xs);
   if ( !IsZero(bottom_flange_height) )
   {
      d4 = bottom_flange_height;
   }

   if ( d4 < 0 )
   {
      // there really isn't a bottom flange if d4 < 0
      d4 = 0;
      d5 = 0;
      d6 = 0;
      w3 = 0;
      w4 = 0;
   }

   //
   // Adjust D7 based on the spliced girder profile
   //
   Float64 section_height = GetSectionDepth(Xs);
   d7 = section_height - (d1 + d2 + d3 + d4 + d5 + d6);
   ATLASSERT( 0 <= d7 );

   // create a new shape that is a clone of the original
   CComQIPtr<IShape> shape(beam);
   CComPtr<IShape> newShape;
   hr = shape->Clone(&newShape);

   // set the dimensions
   CComQIPtr<IFlangedGirderSection> newFlangedBeam(newShape);
   CComPtr<IPrecastBeam> newBeam;
   newFlangedBeam->get_Beam(&newBeam);
   newBeam->put_C1(c1);
   newBeam->put_D1(d1);
   newBeam->put_D2(d2);
   newBeam->put_D3(d3);
   newBeam->put_D4(d4);
   newBeam->put_D5(d5);
   newBeam->put_D6(d6);
   newBeam->put_D7(d7);
   newBeam->put_W1(w1);
   newBeam->put_W2(w2);
   newBeam->put_W3(w3);
   newBeam->put_W4(w4);
   newBeam->put_T1(t1);
   newBeam->put_T2(t2);

   // position the shape
   CComPtr<IPoint2d> pntTopCenter;
   GB_GetSectionLocation(this,Xs,&pntTopCenter);

   CComQIPtr<IXYPosition> position(newFlangedBeam);
   position->put_LocatorPoint(lpTopCenter,pntTopCenter);

   *ppShape = newShape;
   (*ppShape)->AddRef();
   return S_OK;
}

void CFlangedSplicedGirderSegment::GetEndBlockWidth(Float64 distAlongSegment,Float64* pWtop,Float64* pWbot)
{
   Float64 segLength;
   get_Length(&segLength);

   CComQIPtr<IFlangedGirderSection> beam(m_Shapes.front().Shape);
   ATLASSERT(beam); // if this is NULL... how did it get in the system????

   CComPtr<IPrecastBeam> pcBeam;
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
      *pWtop = ebWidth;
      *pWbot = ebWidth;
   }
   else if ( ::InRange(ebLength,distAlongSegment,ebLength+ebTransLength) )
   {
      // in the end block transition
      Float64 t1, t2;
      pcBeam->get_T1(&t1);
      pcBeam->get_T2(&t2);
      *pWtop = ::LinInterp(distAlongSegment-ebLength,ebWidth,t1,ebTransLength);
      *pWbot = ::LinInterp(distAlongSegment-ebLength,ebWidth,t2,ebTransLength);
   }
   else
   {
      // after the end block
      Float64 t1, t2;
      pcBeam->get_T1(&t1);
      pcBeam->get_T2(&t2);
      *pWtop = t1;
      *pWbot = t2;
   }
}
