///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

#include "Stdafx.h"
#include <GenericBridge\Helpers.h>
#include <MathEx.h>
#include <array>
#include <memory>
#include <numeric>

#include <Math\LinearFunction.h>
#include <Math\MathUtils.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TransitionType TransitionTypeFromZone(ZoneType zone,Float64 Yl, Float64 Yr, bool bParabolas)
{
   TransitionType transition = TransitionType::Linear;
   switch (zone)
   {
   case ZoneType::LeftStraight:
      transition = TransitionType::Linear;
      break;

   case ZoneType::LeftSlope:
      transition = (bParabolas ? (Yl < Yr ? TransitionType::RightParabola : TransitionType::LeftParabola) : TransitionType::Linear);
      break;

   case ZoneType::MidStraight:
      transition = TransitionType::Linear;
      break;

   case ZoneType::RightSlope:
      transition = (bParabolas ? (Yl < Yr ? TransitionType::RightParabola : TransitionType::LeftParabola) : TransitionType::Linear);
      break;

   case ZoneType::RightStraight:
      transition = TransitionType::Linear;
      break;

   default:
      ATLASSERT(false); // should never get nere
   }
   return transition;
}

Float64 GetSectionDepth(Float64 X, Float64 X1, Float64 H1, Float64 X2, Float64 H2, TransitionType transition)
{
   Float64 H = -99999;
   Float64 LX = X2 - X1;
   Float64 DX = X - X1;
   switch (transition)
   {
   case TransitionType::Linear:
      H = IsZero(LX) ? H1 : ::LinInterp(DX, H1, H2, LX);
      break;

   case TransitionType::RightParabola:
      H = IsZero(LX) ? H1 : H1 + (H2 - H1)*DX*DX / (LX*LX);
      break;

   case TransitionType::LeftParabola:
      DX = X2 - X;
      H = IsZero(LX) ? H2 : H2 - (H2 - H1)*DX*DX / (LX*LX);
      break;

   default:
      ATLASSERT(false); // should never get here
   }

   return H;
}

ZoneType GetZone(Float64 Xs, const std::array<Float64, 4>& X)
{
   ZoneType zone;
   if (Xs < X[ZoneBreakType::Start])
   {
      zone = ZoneType::LeftStraight;
   }
   else if (X[ZoneBreakType::Start] <= Xs && Xs <= X[ZoneBreakType::LeftBreak])
   {
      zone = ZoneType::LeftSlope;
   }
   else if (X[ZoneBreakType::LeftBreak] < Xs && Xs < X[ZoneBreakType::RightBreak])
   {
      zone = ZoneType::MidStraight;
   }
   else if (X[ZoneBreakType::RightBreak] <= Xs && Xs <= X[ZoneBreakType::End])
   {
      zone = ZoneType::RightSlope;
   }
   else
   {
      zone = ZoneType::RightStraight;
   }

   return zone;
}

ZoneType GetControlPoints(Float64 Xs, Float64 Ls, const std::array<Float64, 4>& X, const std::array<Float64, 4>& Y, Float64* pXl, Float64* pYl, Float64* pXr, Float64* pYr)
{
   ZoneType zone;
   if (Xs < X[ZoneBreakType::Start])
   {
      zone = ZoneType::LeftStraight;
      *pXl = 0.0;
      *pYl = Y[ZoneBreakType::Start];
      *pXr = X[ZoneBreakType::Start];
      *pYr = Y[ZoneBreakType::Start];
   }
   else if (X[ZoneBreakType::Start] <= Xs && Xs <= X[ZoneBreakType::LeftBreak])
   {
      zone = ZoneType::LeftSlope;
      *pXl = X[ZoneBreakType::Start];
      *pYl = Y[ZoneBreakType::Start];
      *pXr = X[ZoneBreakType::LeftBreak];
      if (Y[ZoneBreakType::LeftBreak] == 0)
      {
         if (Y[ZoneBreakType::RightBreak] == 0)
         {
            *pXr = X[ZoneBreakType::End];
            *pYr = Y[ZoneBreakType::End];
         }
         else
         {
            *pXr = X[ZoneBreakType::Start];
            *pYr = Y[ZoneBreakType::Start];
         }
      }
      else
      {
         *pYr = Y[ZoneBreakType::LeftBreak];
      }
   }
   else if (X[ZoneBreakType::LeftBreak] < Xs && Xs < X[ZoneBreakType::RightBreak])
   {
      zone = ZoneType::MidStraight;
      *pXl = X[ZoneBreakType::LeftBreak];
      *pYl = (Y[ZoneBreakType::LeftBreak] == 0 ? Y[ZoneBreakType::Start] : Y[ZoneBreakType::LeftBreak]);
      *pXr = X[ZoneBreakType::RightBreak];
      *pYr = (Y[ZoneBreakType::RightBreak] == 0? Y[ZoneBreakType::End] : Y[ZoneBreakType::RightBreak]);
   }
   else if (X[ZoneBreakType::RightBreak] <= Xs && Xs <= X[ZoneBreakType::End])
   {
      zone = ZoneType::RightSlope;
      *pXl = X[ZoneBreakType::RightBreak];
      if (Y[ZoneBreakType::RightBreak] == 0)
      {
         if (Y[ZoneBreakType::LeftBreak] == 0)
         {
            *pXl = X[ZoneBreakType::Start];
            *pYl = Y[ZoneBreakType::Start];
         }
         else
         {
            *pXl = X[ZoneBreakType::End];
            *pYl = Y[ZoneBreakType::End];
         }
      }
      else
      {
         *pYl = Y[ZoneBreakType::RightBreak];
      }

      *pXr = X[ZoneBreakType::End];
      *pYr = Y[ZoneBreakType::End];
   }
   else
   {
      zone = ZoneType::RightStraight;
      *pXl = X[ZoneBreakType::End];
      *pYl = Y[ZoneBreakType::End];
      *pXr = Ls;
      *pYr = Y[ZoneBreakType::End];
   }

#if defined _DEBUG
   ATLASSERT(zone == GetZone(Xs, X));
#endif

   return zone;
}

void AdjustForEndBlocks(IPrecastBeam* pBeam, Float64 Wt, Float64 Wb)
{
   Float64 W1, W2, W3, W4;
   Float64 D1, D2, D3, D4, D5, D6, D7;
   Float64 T1, T2;

   pBeam->get_W1(&W1);
   pBeam->get_W2(&W2);
   pBeam->get_W3(&W3);
   pBeam->get_W4(&W4);

   pBeam->get_D1(&D1);
   pBeam->get_D2(&D2);
   pBeam->get_D3(&D3);
   pBeam->get_D4(&D4);
   pBeam->get_D5(&D5);
   pBeam->get_D6(&D6);
   pBeam->get_D7(&D7);

   pBeam->get_T1(&T1);
   pBeam->get_T2(&T2);

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

   // near top flange
   if (2 * (W1 + W2) + T1 < Wt)
   {
      // end block is wider than the top flange
      w1 = 0;
      w2 = 0;
      d7 += D1 + D2 + D3;
      t1 = Wt;
   }
   else if (W2 + T1 / 2 < Wt / 2)
   {
      // end block extends beyond top fillet
      w2 = 0;
      w1 = W1 + W2 + T1 / 2 - Wt / 2;
      if (IsZero(w1))
      {
         w1 = 0.0; // eliminate noise
      }
      else
      {
         d2 = (D2 / W1) * w1;
         d3 = D3 + (D2 - d2);
      }
      t1 = Wt;
   }
   else if (T1 / 2 < Wt / 2)
   {
      // end block intersects top fillet
      w2 = W2 + T1 / 2 - Wt / 2;
      d3 = (D3 / W2)*w2;
      d7 += (D3 - d3);
      t1 = Wt;
   }

   // near bottom flange
   if (2 * (W3 + W4) + T2 < Wb)
   {
      // end block is wider than the bottom flange
      w3 = 0;
      w4 = 0;
      d7 += D4 + D5 + D6;
      t2 = Wb;
   }
   else if (W4 + T2 / 2 < Wb / 2)
   {
      // end block extends beyond bottom fillet
      w4 = 0;
      w3 = W3 + W4 + T2 / 2 - Wb / 2;
      if (IsZero(w3))
      {
         w3 = 0.0; // eliminate noise
      }
      else
      {
         d5 = (D5 / W3) * w3;
         d6 = D6 + (D5 - d5);
      }
      t2 = Wb;
   }
   else if (T2 / 2 < Wb / 2)
   {
      // end block intersects bottom fillet
      w4 = W4 + T2 / 2 - Wb / 2;
      d6 = (D6 / W4)*w4;
      d7 += D6 - d6;
      t2 = Wb;
   }

   // verify girder height is unchanged
   ATLASSERT(IsEqual(d1 + d2 + d3 + d4 + d5 + d6 + d7, D1 + D2 + D3 + D4 + D5 + D6 + D7));
   ATLASSERT(IsEqual(2 * (w1 + w2) + t1, 2 * (W1 + W2) + T1) || IsEqual(2 * (w1 + w2) + t1, Wt));
   ATLASSERT(IsEqual(2 * (w3 + w4) + t2, 2 * (W3 + W4) + T2) || IsEqual(2 * (w3 + w4) + t2, Wb));

   pBeam->put_D1(d1);
   pBeam->put_D2(d2);
   pBeam->put_D3(d3);
   pBeam->put_D4(d4);
   pBeam->put_D5(d5);
   pBeam->put_D6(d6);
   pBeam->put_D7(d7);
   pBeam->put_W1(w1);
   pBeam->put_W2(w2);
   pBeam->put_W3(w3);
   pBeam->put_W4(w4);
   pBeam->put_T1(t1);
   pBeam->put_T2(t2);
}

void GetEndBlockWidth(Float64 Xs, Float64 Ls, SectionBias sectionBias, IPrecastBeam* pBeam, const std::array<Float64, 2>& ebWidth, const std::array<Float64, 2>& ebLength, const std::array<Float64, 2>& ebTransLength, Float64* pWtop, Float64* pWbot)
{
   EndType endType;
   if (Xs < Ls / 2)
   {
      // at the start end...
      endType = etStart;
   }
   else
   {
      endType = etEnd;
      Xs = Ls - Xs; // Xs is now measured from the right end
   }

   if ( Xs < ebLength[endType] || (IsEqual(Xs,ebLength[endType]) && sectionBias == (endType == etStart ? sbLeft : sbRight)))
   {
      // in the end block
      *pWtop = ebWidth[endType];
      *pWbot = ebWidth[endType];
   }
   else if (!::IsZero(ebTransLength[endType]) && ::InRange(ebLength[endType], Xs, ebLength[endType] + ebTransLength[endType]))
   {
      // in the end block transition
      Float64 t1, t2;
      pBeam->get_T1(&t1);
      pBeam->get_T2(&t2);
      *pWtop = ::LinInterp(Xs - ebLength[endType], ebWidth[endType], t1, ebTransLength[endType]);
      *pWbot = ::LinInterp(Xs - ebLength[endType], ebWidth[endType], t2, ebTransLength[endType]);
   }
   else
   {
      // after the end block
      Float64 t1, t2;
      pBeam->get_T1(&t1);
      pBeam->get_T2(&t2);
      *pWtop = t1;
      *pWbot = t2;
   }
}

void AdjustForVariableDepth(IPrecastBeam* pBeam, Float64 Hg, Float64 Hbf)
{
   Float64 d1, d2, d3, d4, d5, d6, d7;

   pBeam->get_D1(&d1);
   pBeam->get_D2(&d2);
   pBeam->get_D3(&d3);
   pBeam->get_D4(&d4);
   pBeam->get_D5(&d5);
   pBeam->get_D6(&d6);
   pBeam->get_D7(&d7);

   // Adjust d4 based on the bottom flange height
   // If bottom flange height is zero then don't make any adjustments (take zero to be don't change bottom flange)
   if (0 < Hbf)
   {
      d4 = Hbf;
   }

   if (d4 < 0)
   {
      // there really isn't a bottom flange
      d4 = 0;
      d5 = 0; 
      d6 = 0;
      pBeam->put_D4(d4);
      pBeam->put_D5(d5);
      pBeam->put_D6(d6);
      pBeam->put_W3(0);
      pBeam->put_W4(0);
   }
   else
   {
      pBeam->put_D4(d4);
   }

   // Adjust d7 based on the overall girder height
   if (0 < Hg)
   {
      d7 = Hg - (d1 + d2 + d3 + d4 + d5 + d6);
      pBeam->put_D7(d7);
   }
}





void AdjustForEndBlocks(IPrecastBeam2* pBeam, Float64 Wt, Float64 Wb)
{
   Float64 W1, W2, W3, W4, W5;
   Float64 D1, D2, D3, D4, D5, D6, H;
   Float64 T1, T2;

   pBeam->get_W1(&W1);
   pBeam->get_W2(&W2);
   pBeam->get_W3(&W3);
   pBeam->get_W4(&W4);
   pBeam->get_W5(&W5);

   pBeam->get_D1(&D1);
   pBeam->get_D2(&D2);
   pBeam->get_D3(&D3);
   pBeam->get_D4(&D4);
   pBeam->get_D5(&D5);
   pBeam->get_D6(&D6);
   pBeam->get_H(&H);

   pBeam->get_T1(&T1);
   pBeam->get_T2(&T2);

   Float64 w1 = W1;
   Float64 w2 = W2;
   Float64 w3 = W3;
   Float64 w4 = W4;
   Float64 w5 = W5;
   Float64 d1 = D1;
   Float64 d2 = D2;
   Float64 d3 = D3;
   Float64 d4 = D4;
   Float64 d5 = D5;
   Float64 d6 = D6;
   Float64 h = H;
   Float64 t1 = T1;
   Float64 t2 = T2;

   // adjust dimensions based on end block size

   // near top flange
   if (2 * (W1 + W2 + W3) + T1 < Wt)
   {
      // end block is wider than the top flange
      w1 = 0;
      w2 = 0;
      w3 = 0;
      t1 = Wt;
   }
   else if (2 * (W2 + W3) + T1 < Wt)
   {
      // end block is wider than the sloped portion of the top flange
      w1 = (W1 + W2 + W3 + T1 / 2) - Wt / 2;
      w2 = 0;
      w3 = 0;
      t1 = Wt;
   }
   else if (W3 + T1 / 2 < Wt / 2)
   {
      // end block extends beyond top fillet
      w3 = 0;
      w2 = W2 + W3 + T1 / 2 - Wt / 2;
      if (IsZero(w2))
      {
         w2 = 0.0; // eliminate noise
      }
      else
      {
         d2 = (D2 / W2) * w2;
      }
      t1 = Wt;
   }
   else if (T1 / 2 < Wt / 2)
   {
      // end block intersects top fillet
      w3 = W3 + T1 / 2 - Wt / 2;
      d3 = (D3 / W3) * w3;
      t1 = Wt;
   }

   // near bottom flange
   if (2 * (W4 + W5) + T2 < Wb)
   {
      // end block is wider than the bottom flange
      w4 = 0;
      w5 = 0;
      t2 = Wb;
   }
   else if (W4 + T2 / 2 < Wb / 2)
   {
      // end block extends beyond bottom fillet
      w4 = 0;
      w5 = W4 + W5 + T2 / 2 - Wb / 2;
      if (IsZero(w5))
      {
         w5 = 0.0; // eliminate noise
      }
      else
      {
         d4 = D4 + (D5 - d5);
         d5 = (D5 / W5) * w5;
      }
      t2 = Wb;
   }
   else if (T2 / 2 < Wb / 2)
   {
      // end block intersects bottom fillet
      w4 = W4 + T2 / 2 - Wb / 2;
      d4 = (D4 / W4) * w4;
      t2 = Wb;
   }

   // verify girder height is unchanged
   ATLASSERT(IsEqual(2 * (w1 + w2 + w3) + t1, 2 * (W1 + W2 + W3) + T1) || IsEqual(2 * (w1 + w2 + w3) + t1, Wt));
   ATLASSERT(IsEqual(2 * (w4 + w5) + t2, 2 * (W4 + W5) + T2) || IsEqual(2 * (w4 + w5) + t2, Wb));

   pBeam->put_D1(d1);
   pBeam->put_D2(d2);
   pBeam->put_D3(d3);
   pBeam->put_D4(d4);
   pBeam->put_D5(d5);
   pBeam->put_D6(d6);
   pBeam->put_H(H);
   pBeam->put_W1(w1);
   pBeam->put_W2(w2);
   pBeam->put_W3(w3);
   pBeam->put_W4(w4);
   pBeam->put_W5(w5);
   pBeam->put_T1(t1);
   pBeam->put_T2(t2);
}

void GetEndBlockWidth(Float64 Xs, Float64 Ls, SectionBias sectionBias, IPrecastBeam2* pBeam, const std::array<Float64, 2>& ebWidth, const std::array<Float64, 2>& ebLength, const std::array<Float64, 2>& ebTransLength, Float64* pWtop, Float64* pWbot)
{
   EndType endType;
   if (Xs < Ls / 2)
   {
      // at the start end...
      endType = etStart;
   }
   else
   {
      endType = etEnd;
      Xs = Ls - Xs; // Xs is now measured from the right end
   }

   if (Xs < ebLength[endType] || (IsEqual(Xs, ebLength[endType]) && sectionBias == (endType == etStart ? sbLeft : sbRight)))
   {
      // in the end block
      *pWtop = ebWidth[endType];
      *pWbot = ebWidth[endType];
   }
   else if (!::IsZero(ebTransLength[endType]) && ::InRange(ebLength[endType], Xs, ebLength[endType] + ebTransLength[endType]))
   {
      // in the end block transition
      Float64 t1, t2;
      pBeam->get_T1(&t1);
      pBeam->get_T2(&t2);
      *pWtop = ::LinInterp(Xs - ebLength[endType], ebWidth[endType], t1, ebTransLength[endType]);
      *pWbot = ::LinInterp(Xs - ebLength[endType], ebWidth[endType], t2, ebTransLength[endType]);
   }
   else
   {
      // after the end block
      Float64 t1, t2;
      pBeam->get_T1(&t1);
      pBeam->get_T2(&t2);
      *pWtop = t1;
      *pWbot = t2;
   }
}

void AdjustForVariableDepth(IPrecastBeam2* pBeam, Float64 Hg, Float64 Hbf)
{
   Float64 d6, h;

   pBeam->get_D6(&d6);
   pBeam->get_H(&h);

   // Adjust d6 based on the bottom flange height
   // If bottom flange height is zero then don't make any adjustments (take zero to be don't change bottom flange)
   if (0 < Hbf)
   {
      d6 = Hbf;
   }

   if (d6 < 0)
   {
      // there really isn't a bottom flange
      pBeam->put_D4(0);
      pBeam->put_D5(0);
      pBeam->put_D6(0);
      pBeam->put_W4(0);
      pBeam->put_W5(0);
   }
   else
   {
      pBeam->put_D6(d6);
   }

   // Adjust H based on the overall girder height
   if (0 < Hg)
   {
      pBeam->put_H(Hg);
   }
}




void GetEndBlockWidth(Float64 Xs, Float64 Ls, SectionBias sectionBias, INUBeam* pBeam, const std::array<Float64, 2>& ebWidth, const std::array<Float64, 2>& ebLength, const std::array<Float64, 2>& ebTransLength, Float64* pWeb)
{
   EndType endType;
   if (Xs < Ls / 2)
   {
      // at the start end...
      endType = etStart;
   }
   else
   {
      endType = etEnd;
      Xs = Ls - Xs; // distAlongSegment is now measured from the left end
   }

   if (Xs < ebLength[endType])
   {
      // in the end block
      *pWeb = ebWidth[endType];
   }
   else if (::InRange(ebLength[endType], Xs, ebLength[endType] + ebTransLength[endType]))
   {
      // in the end block transition
      Float64 t;
      pBeam->get_T(&t);
      *pWeb = ::LinInterp(Xs - ebLength[endType], ebWidth[endType], t, ebTransLength[endType]);
   }
   else
   {
      // after the end block
      Float64 t;
      pBeam->get_T(&t);
      *pWeb = t;
   }
}

void AdjustForEndBlocks(INUBeam* pBeam, Float64 Web)
{
   pBeam->put_EndBlock(Web);
}

void AdjustForVariableDepth(INUBeam* pBeam, Float64 Hg, Float64 Hbf)
{
   Float64 d1, d2, d3, d4, d5;
   Float64 r1, r2, r3, r4;
   Float64 t;
   Float64 w1, w2;
   Float64 c1;

   pBeam->get_W1(&w1);
   pBeam->get_W2(&w2);

   pBeam->get_D1(&d1);
   pBeam->get_D2(&d2);
   pBeam->get_D3(&d3);
   pBeam->get_D4(&d4);
   pBeam->get_D5(&d5);

   pBeam->get_R1(&r1);
   pBeam->get_R2(&r2);
   pBeam->get_R3(&r3);
   pBeam->get_R4(&r4);

   pBeam->get_T(&t);

   pBeam->get_C1(&c1);

   //
   // Adjust d5 based on the bottom flange height
   // If bottom flange height is zero then don't make any adjustments (take zero to be don't change bottom flange)
   //
   if (0 < Hbf)
   {
      d5 = Hbf;
   }

   if (d5 < 0)
   {
      // there really isn't a bottom flange if d5 < 0
      d5 = 0;
      pBeam->put_D5(d5);
   }
   pBeam->put_D5(d5);


   // Adjust d3 based on the overall girder height
   if (0 < Hg)
   {
      d3 = Hg - (d1 + d2 + d4 + d5);
      ATLASSERT(0 <= d3);
      pBeam->put_D3(d3);
   }
}

Float64 ComputeTopFlangeThickening(Float64 Xs, Float64 Ls, ThickeningType thickeningType, Float64 tft)
{
   if (IsZero(tft))
   {
      return 0;
   }

   Float64 thickening;
   if (thickeningType == ttEnds)
   {
      thickening = 4 * tft*Xs*Xs / (Ls*Ls) - 4 * tft*Xs / Ls + tft;
   }
   else
   {
      thickening = -4 * tft*Xs*Xs / (Ls*Ls) + 4 * tft*Xs / Ls;
   }
   return thickening;
}

Float64 ComputePrecamber(Float64 Xs, Float64 Ls, Float64 precamber)
{
   if (IsZero(precamber))
   {
      return 0;
   }

   return (4 * precamber / Ls)*Xs*(1 - Xs / Ls);
}

Float64 WBFLGENERICBRIDGEFUNC ComputeHaunchDepthAlongSegment(Float64 distAlongSegment,Float64 segmentLength,const std::vector<Float64>& vHaunchDepths)
{
   // it's not unusual to ask for this value within closures, so the assert below is commented out
//   ATLASSERT(distAlongSegment >= 0.0 && distAlongSegment <= segmentLength);

   IndexType nVals = vHaunchDepths.size();

   Float64 haunchDepth;
   if (0 == nVals)
   {
      // called for non-composite sections among other cases
      haunchDepth = 0.0;
   }
   else if (1 == nVals)
   {
      // constant 
      haunchDepth = vHaunchDepths.front();
   }
   else if (3 == nVals)
   {
      // Parabolic distribution
      Float64 startHaunch(vHaunchDepths[0]),midHaunch(vHaunchDepths[1]),endHaunch(vHaunchDepths[2]);

      // Linear portion of haunch based on end values
      Float64 lin_haunch = ::LinInterp(distAlongSegment,startHaunch,endHaunch,segmentLength);

      // Compute height of bulge at location
      // Made an OPTIMIZATION here - this function is called many, many times.
      // Was using GenerateParabola() in MathUtils.h, but calls were costly. Refer to that derivation
      // for how we got here.
      Float64 mid_bulge = midHaunch - (startHaunch + endHaunch) / 2.0;
      Float64 Vx = (segmentLength) / 2.0;   // X ordinate of peak
                                             // y = Ax^2 + Bx + C
      Float64 A = -mid_bulge / (Vx * Vx);
      Float64 B = 2 * mid_bulge / Vx;
      Float64 para_haunch = A * distAlongSegment * distAlongSegment + B * distAlongSegment;

      haunchDepth = lin_haunch + para_haunch; // haunch is sum of linear part and parabolic sliver
   }
   else
   {
      // Haunch is piecewise linear based on evenly spaced segments
      // dist should always be within segment, but make assumptions to avoid a crash
      if (distAlongSegment <= 0.0)
      {
         haunchDepth = vHaunchDepths.front();
      }
      else if (distAlongSegment >= segmentLength)
      {
         haunchDepth = vHaunchDepths.back();
      }
      else
      {
         // Use fractional distance along segment to determine indexes of bracketing haunch values
         Float64 frac = distAlongSegment / segmentLength;
         Float64 fracIdx = frac * (nVals-1);
         int floorIdx = (int)floor(fracIdx);
         int ceilIdx = (int)ceil(fracIdx);
         if (floorIdx == ceilIdx)
         {
            haunchDepth = vHaunchDepths[floorIdx];
         }
         else
         {
            Float64 fracAlongSeg = fracIdx - floorIdx; // fractional distance along fractional segment
            Float64 lin_haunch = ::LinInterp(fracAlongSeg, vHaunchDepths[floorIdx], vHaunchDepths[ceilIdx],1.0);
            haunchDepth = lin_haunch;
         }
      }
   }

   return haunchDepth;
}


// GetGirderProfile, below, caches the profile function in the ItemData of a SuperstructureMember object. ItemData is stashed by an IUnknown
// pointer of a COM object. The profile function is not a COM object. We create a FunctionHolder object that is a COM object that
// holds the profile function object an can be stored in the ItemData of the SuperstructureMember object.
// {F427244C-4A03-4037-AB2A-6769AAF5CA0A}
#include <initguid.h>
DEFINE_GUID(CLSID_FunctionHolder, 0xf427244c, 0x4a03, 0x4037, 0xab, 0x2a, 0x67, 0x69, 0xaa, 0xf5, 0xca, 0xa);
// {D62A0D3A-8D99-4F82-8155-AF3E30BC175D}
DEFINE_GUID(IID_IFunctionHolder, 0xd62a0d3a, 0x8d99, 0x4f82, 0x81, 0x55, 0xaf, 0x3e, 0x30, 0xbc, 0x17, 0x5d);

MIDL_INTERFACE("D62A0D3A-8D99-4F82-8155-AF3E30BC175D")
IFunctionHolder : public IUnknown
{
   virtual void SetFunction(WBFL::Math::CompositeFunction* pFunction) = 0;
   virtual WBFL::Math::CompositeFunction* GetFunction() = 0;
};

class ATL_NO_VTABLE CFunctionHolder :
   public CComObjectRootEx<CComSingleThreadModel>,
   public CComCoClass<CFunctionHolder, &CLSID_FunctionHolder>,
   public IFunctionHolder
{
public:
   BEGIN_COM_MAP(CFunctionHolder)
      COM_INTERFACE_ENTRY_IID(IID_IFunctionHolder,IFunctionHolder)
   END_COM_MAP()

   virtual void SetFunction(WBFL::Math::CompositeFunction* pFunction) override
   {
      m_pFunction.reset(pFunction);
   }

   virtual WBFL::Math::CompositeFunction* GetFunction() override
   {
      return m_pFunction.get();
   }
protected:
   std::unique_ptr<WBFL::Math::CompositeFunction> m_pFunction;
};

void WBFLGENERICBRIDGEFUNC ClearGirderProfile(ISuperstructureMember* pSSMbr)
{
   CComQIPtr<IItemData> itemData(pSSMbr);
   itemData->RemoveItemData(CComBSTR("GirderProfileFunction"));
   itemData->RemoveItemData(CComBSTR("BottomFlangeFunction"));
}

WBFL::Math::CompositeFunction* GetGirderProfile(ISuperstructureMember* pSSMbr, bool bGirderProfile)
{
   // The profile function is cached as item data on the superstructure member object
   // Check the cache before proceeding
   CComBSTR bstrItemDataName(bGirderProfile ? _T("GirderProfileFunction") : _T("BottomFlangeFunction"));
   CComQIPtr<IItemData> itemData(pSSMbr);
   CComPtr<IUnknown> punk;
   if (SUCCEEDED(itemData->GetItemData(bstrItemDataName, &punk)))
   {
      // the function was cached, return it
      CComQIPtr<IFunctionHolder> pf(punk);
      return pf->GetFunction();
   }
   
   // The function isn't cached so create it and then add it to the cache
   std::unique_ptr<WBFL::Math::CompositeFunction> pCompositeFunction(std::make_unique<WBFL::Math::CompositeFunction>());

   SegmentIndexType nSegments;
   pSSMbr->get_SegmentCount(&nSegments);

   Float64 xSegmentStart = 0; // start of segment
   Float64 xStart = 0; // start of curve section
   Float64 xEnd = 0; // end of curve section

   bool bParabola = false;
   Float64 xParabolaStart, xParabolaEnd;
   Float64 yParabolaStart, yParabolaEnd;
   Float64 slopeParabola = 0;

   for (SegmentIndexType segIdx = 0; segIdx < nSegments; segIdx++)
   {
      CComPtr<ISuperstructureMemberSegment> ssmbrSegment;
      pSSMbr->get_Segment(segIdx, &ssmbrSegment);

      CComQIPtr<ISplicedGirderSegment> segment(ssmbrSegment);
      ATLASSERT(segment != nullptr);

      SegmentVariationType variation_type;
      segment->get_VariationType(&variation_type);

      Float64 segment_length;
      segment->get_LayoutLength(&segment_length);

      CComPtr<IGirderLine> girderLine;
      segment->get_GirderLine(&girderLine);

      if (segIdx == 0)
      {
         Float64 brgOffset;
         girderLine->get_BearingOffset(etStart, &brgOffset);
         Float64 endDist;
         girderLine->get_EndDistance(etStart, &endDist);
         Float64 offset_dist = brgOffset - endDist;
         offset_dist = IsZero(offset_dist) ? 0.0 : offset_dist;
         xSegmentStart = offset_dist;
         segment_length -= offset_dist;
      }


      if (segIdx == nSegments - 1)
      {
         Float64 brgOffset;
         girderLine->get_BearingOffset(etEnd, &brgOffset);
         Float64 endDist;
         girderLine->get_EndDistance(etEnd, &endDist);
         Float64 offset_dist = brgOffset - endDist;
         offset_dist = IsZero(offset_dist) ? 0.0 : offset_dist;
         segment_length -= offset_dist;
      }

      xStart = xSegmentStart;

      if (variation_type == svtNone)
      {
         Float64 l, h, b;
         segment->GetVariationParameters(sztLeftPrismatic, &l, &h, &b);
         Float64 h1 = (bGirderProfile ? h : b);
         Float64 h2 = h1;

         Float64 precamber;
         segment->get_Precamber(&precamber);

         xEnd = xStart + segment_length;
         if (!bGirderProfile || IsZero(precamber))
         {
            Float64 slope = (h2 - h1) / segment_length;
            WBFL::Math::LinearFunction func(slope, h1);
            pCompositeFunction->AddFunction(xStart, xEnd, func);
            slopeParabola = slope;
         }
         else
         {
            // NOTE: Tricky... using negative of precamber to make this parabola
            // the callers of this method use the negative of the value return
            // from the function to get the profile based on the top of the girder
            // being at zero. That negative cancels out the negative used here and we
            // get the profile we want
            WBFL::Math::PolynomialFunction func(WBFL::Math::GenerateParabola(xStart, xEnd, -precamber, h1));
            pCompositeFunction->AddFunction(xStart, xEnd, func);
            slopeParabola = 0;
         }
         xStart = xEnd;
      }
      else
      {
         std::array<Float64, 4> variation_length, variation_height, variation_bottom_flange;
         segment->GetVariationParameters(sztLeftPrismatic, &variation_length[sztLeftPrismatic], &variation_height[sztLeftPrismatic], &variation_bottom_flange[sztLeftPrismatic]);
         segment->GetVariationParameters(sztLeftTapered, &variation_length[sztLeftTapered], &variation_height[sztLeftTapered], &variation_bottom_flange[sztLeftTapered]);
         segment->GetVariationParameters(sztRightTapered, &variation_length[sztRightTapered], &variation_height[sztRightTapered], &variation_bottom_flange[sztRightTapered]);
         segment->GetVariationParameters(sztRightPrismatic, &variation_length[sztRightPrismatic], &variation_height[sztRightPrismatic], &variation_bottom_flange[sztRightPrismatic]);

         Float64 h1, h2, h3, h4;
         if (bGirderProfile)
         {
            // we are creating a girder profile
            h1 = variation_height[sztLeftPrismatic];
            h2 = variation_height[sztRightPrismatic];
            h3 = variation_height[sztLeftTapered];
            h4 = variation_height[sztRightTapered];
         }
         else
         {
            // we are creating a bottom flange profile
            h1 = variation_bottom_flange[sztLeftPrismatic];
            h2 = variation_bottom_flange[sztRightPrismatic];
            h3 = variation_bottom_flange[sztLeftTapered];
            h4 = variation_bottom_flange[sztRightTapered];
         }

         if (0 < variation_length[sztLeftPrismatic])
         {
            // create a prismatic segment
            WBFL::Math::LinearFunction func(0.0, h1);
            xEnd = xStart + (variation_type == svtNone ? segment_length / 2 : variation_length[sztLeftPrismatic]);
            pCompositeFunction->AddFunction(xStart, xEnd, func);
            slopeParabola = 0;
            xStart = xEnd;
         }

         if (variation_type == svtLinear)
         {
            // create a linear taper segment
            Float64 taper_length = segment_length - variation_length[sztLeftPrismatic] - variation_length[sztRightPrismatic];
            Float64 slope = (h2 - h1) / taper_length;
            Float64 b = h1 - slope*xStart;

            WBFL::Math::LinearFunction func(slope, b);
            xEnd = xStart + taper_length;
            pCompositeFunction->AddFunction(xStart, xEnd, func);
            xStart = xEnd;
            slopeParabola = slope;
         }
         else if (variation_type == svtDoubleLinear)
         {
            // create a linear taper for left side of segment
            Float64 slope = (h3 - h1) / variation_length[sztLeftTapered];
            Float64 b = h1 - slope*xStart;

            WBFL::Math::LinearFunction left_func(slope, b);
            xEnd = xStart + variation_length[sztLeftTapered];
            pCompositeFunction->AddFunction(xStart, xEnd, left_func);
            xStart = xEnd;

            // create a linear segment between left and right tapers
            Float64 taper_length = segment_length - std::accumulate(std::begin(variation_length), std::end(variation_length), 0.0);
            slope = (h4 - h3) / taper_length;
            b = h3 - slope*xStart;

            WBFL::Math::LinearFunction middle_func(slope, b);
            xEnd = xStart + taper_length;
            pCompositeFunction->AddFunction(xStart, xEnd, middle_func);
            xStart = xEnd;

            // create a linear taper for right side of segment
            slope = (h2 - h4) / variation_length[sztRightTapered];
            b = h4 - slope*xStart;

            WBFL::Math::LinearFunction right_func(slope, b);
            xEnd = xStart + variation_length[sztRightTapered];
            pCompositeFunction->AddFunction(xStart, xEnd, right_func);
            xStart = xEnd;
            slopeParabola = slope;
         }
         else if (variation_type == svtParabolic)
         {
            if (!bParabola)
            {
               // this is the start of a parabolic segment
               bParabola = true;
               xParabolaStart = xStart;
               yParabolaStart = h1;
            }

            // Parabola ends in this segment if
            // 1) this segment has a prismatic segment on the right end -OR-
            // 2) this is the last segment -OR-
            // 3) the next segment starts with a prismatic segment -OR-
            // 4) the next segment has a linear transition

            CComPtr<ISuperstructureMemberSegment> next_ssmbrSegment;
            if (segIdx < nSegments - 1)
            {
               pSSMbr->get_Segment(segIdx + 1, &next_ssmbrSegment);
            }
            CComQIPtr<ISplicedGirderSegment> next_segment(next_ssmbrSegment);


            Float64 next_segment_left_prismatic_length = 0;
            SegmentVariationType next_segment_variation_type = svtNone;

            if (next_segment)
            {
               Float64 h, b;
               next_segment->GetVariationParameters(sztLeftPrismatic, &next_segment_left_prismatic_length, &h, &b);

               next_segment->get_VariationType(&next_segment_variation_type);
            }

            if (
               0 < variation_length[sztRightPrismatic] || // parabola ends in this segment -OR-
               segIdx == nSegments - 1 || // this is the last segment (parabola ends here) -OR-
               0 < next_segment_left_prismatic_length || // next segment starts with prismatic section -OR-
               (next_segment_variation_type == svtNone || next_segment_variation_type == svtLinear || next_segment_variation_type == svtDoubleLinear) // next segment is linear 
               )
            {
               // parabola ends in this segment
               Float64 xParabolaEnd = xStart + segment_length - variation_length[sztRightPrismatic];
               Float64 yParabolaEnd = h2;

               if (yParabolaEnd < yParabolaStart)
               {
                  // slope at end is zero
                  WBFL::Math::PolynomialFunction func = WBFL::Math::GenerateParabola2(xParabolaStart, yParabolaStart, xParabolaEnd, yParabolaEnd, 0.0);
                  pCompositeFunction->AddFunction(xParabolaStart, xParabolaEnd, func);
               }
               else
               {
                  // slope at start is zero
                  WBFL::Math::PolynomialFunction func = WBFL::Math::GenerateParabola1(xParabolaStart, yParabolaStart, xParabolaEnd, yParabolaEnd, slopeParabola);
                  pCompositeFunction->AddFunction(xParabolaStart, xParabolaEnd, func);
               }

               bParabola = false;
               xStart = xParabolaEnd;
            }
            else
            {
               // parabola ends further down the girderline
               // do nothing???
            }
         }
         else if (variation_type == svtDoubleParabolic)
         {
            // left parabola ends in this segment
            if (!bParabola)
            {
               // not currently in a parabola, based the start point on this segment
               xParabolaStart = xSegmentStart + variation_length[sztLeftPrismatic];
               yParabolaStart = h1;
            }

#pragma Reminder("BUG: Assuming slope at start is zero, but it may not be if tangent to a linear segment")
            xParabolaEnd = xSegmentStart + variation_length[sztLeftPrismatic] + variation_length[sztLeftTapered];
            yParabolaEnd = h3;
            WBFL::Math::PolynomialFunction func_left_parabola;
            if (yParabolaEnd < yParabolaStart)
            {
               func_left_parabola = WBFL::Math::GenerateParabola2(xParabolaStart, yParabolaStart, xParabolaEnd, yParabolaEnd, 0.0);
            }
            else
            {
               func_left_parabola = WBFL::Math::GenerateParabola1(xParabolaStart, yParabolaStart, xParabolaEnd, yParabolaEnd, slopeParabola);
            }

            pCompositeFunction->AddFunction(xParabolaStart, xParabolaEnd, func_left_parabola);

            // parabola on right side of this segment starts here
            xParabolaStart = xSegmentStart + segment_length - variation_length[sztRightPrismatic] - variation_length[sztRightTapered];
            yParabolaStart = h4;
            bParabola = true;

            if (!IsZero(xParabolaStart - xParabolaEnd))
            {
               // create a line segment between parabolas
               Float64 taper_length = segment_length - std::accumulate(std::begin(variation_length), std::end(variation_length), 0.0);
               Float64 slope = -(h4 - h3) / taper_length;
               Float64 b = h3 - slope*xParabolaEnd;

               WBFL::Math::LinearFunction middle_func(slope, b);
               pCompositeFunction->AddFunction(xParabolaEnd, xParabolaStart, middle_func);
               slopeParabola = slope;
            }

            // parabola ends in this segment if
            // 1) this is the last segment
            // 2) right prismatic section length > 0
            // 3) next segment is not parabolic

            CComPtr<ISuperstructureMemberSegment> next_ssmbrSegment;
            if (segIdx < nSegments - 1)
            {
               pSSMbr->get_Segment(segIdx + 1, &next_ssmbrSegment);
            }
            CComQIPtr<ISplicedGirderSegment> next_segment(next_ssmbrSegment);


            SegmentVariationType next_segment_variation_type = svtNone;
            if (next_segment)
            {
               next_segment->get_VariationType(&next_segment_variation_type);
            }

            if (0 < variation_length[sztRightPrismatic] ||
               segIdx == nSegments - 1 ||
               (next_segment_variation_type == svtNone || next_segment_variation_type == svtLinear || next_segment_variation_type == svtDoubleLinear) // next segment is linear 
               )
            {
               bParabola = false;
               xParabolaEnd = xSegmentStart + segment_length - variation_length[sztRightPrismatic];
               yParabolaEnd = h2;


               WBFL::Math::PolynomialFunction func_right_parabola;
               if (yParabolaEnd < yParabolaStart)
               {
                  // compute slope at end of parabola
                  if (next_segment)
                  {
                     Float64 next_segment_length;
                     next_segment->get_LayoutLength(&next_segment_length);

                     std::array<Float64, 4> next_segment_variation_length, next_segment_variation_height, next_segment_variation_bottom_flange;
                     next_segment->GetVariationParameters(sztLeftPrismatic, &next_segment_variation_length[sztLeftPrismatic], &next_segment_variation_height[sztLeftPrismatic], &next_segment_variation_bottom_flange[sztLeftPrismatic]);
                     next_segment->GetVariationParameters(sztLeftTapered, &next_segment_variation_length[sztLeftTapered], &next_segment_variation_height[sztLeftTapered], &next_segment_variation_bottom_flange[sztLeftTapered]);
                     next_segment->GetVariationParameters(sztRightTapered, &next_segment_variation_length[sztRightTapered], &next_segment_variation_height[sztRightTapered], &next_segment_variation_bottom_flange[sztRightTapered]);
                     next_segment->GetVariationParameters(sztRightPrismatic, &next_segment_variation_length[sztRightPrismatic], &next_segment_variation_height[sztRightPrismatic], &next_segment_variation_bottom_flange[sztRightPrismatic]);

                     if (next_segment_variation_type == svtLinear)
                     {
                        // next segment is linear
                        if (IsZero(next_segment_variation_length[sztLeftPrismatic]))
                        {
                           Float64 dist = next_segment_length - next_segment_variation_length[sztLeftPrismatic] - next_segment_variation_length[sztRightPrismatic];
                           slopeParabola = (next_segment_variation_height[sztRightPrismatic] - next_segment_variation_height[sztLeftPrismatic]) / dist;
                        }
                     }
                     else if (next_segment_variation_type == svtDoubleLinear)
                     {
                        if (IsZero(next_segment_variation_length[sztLeftPrismatic]))
                        {
                           Float64 dist = next_segment_variation_length[sztLeftTapered];
                           slopeParabola = (next_segment_variation_height[sztLeftTapered] - next_segment_variation_height[sztLeftPrismatic]) / dist;
                        }
                     }
                  }
                  else
                  {
                     slopeParabola = 0;
                  }
                  func_right_parabola = WBFL::Math::GenerateParabola2(xParabolaStart, yParabolaStart, xParabolaEnd, yParabolaEnd, slopeParabola);
               }
               else
               {
                  func_right_parabola = WBFL::Math::GenerateParabola1(xParabolaStart, yParabolaStart, xParabolaEnd, yParabolaEnd, slopeParabola);
               }

               pCompositeFunction->AddFunction(xParabolaStart, xParabolaEnd, func_right_parabola);
            }
            else
            {
               // parabola ends further down the girderline
               bParabola = true;
            }

            xStart = xSegmentStart + segment_length - variation_length[sztRightPrismatic];
         }

         if (0 < variation_length[sztRightPrismatic])
         {
            // create a prismatic segment
            WBFL::Math::LinearFunction func(0.0, h2);
            xEnd = xStart + (variation_type == svtNone ? segment_length / 2 : variation_length[sztRightPrismatic]);
            pCompositeFunction->AddFunction(xStart, xEnd, func);
            slopeParabola = 0;
            xStart = xEnd;
         }
      }
      xSegmentStart += segment_length;
   } // next segment

   // Cache the function as item data on the superstructure member object.
   CComObject<CFunctionHolder>* pFuncHolder;
   CComObject<CFunctionHolder>::CreateInstance(&pFuncHolder);
   CComPtr<IFunctionHolder> func_holder(pFuncHolder);
   func_holder->SetFunction(pCompositeFunction.release());
   CComPtr<IUnknown> punk_func_holder;
   func_holder.QueryInterface(&punk_func_holder);
   HRESULT hr = itemData->AddItemData(bstrItemDataName, punk_func_holder);
   ATLASSERT(SUCCEEDED(hr));

   return func_holder->GetFunction();
}
