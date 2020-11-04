///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2020  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

std::array<Float64, 4> ResolveFractionalDistance(const std::array<Float64, 4>& X, Float64 L)
{
   std::array<Float64, 4> result;
   for (int i = 0; i < 4; i++)
   {
      if (X[i] < 0)
      {
         result[i] = -X[i] * L;
      }
      else
      {
         result[i] = X[i];
      }
   }

   return result;
}

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
      d1 = 0;
      d2 = 0;
      d3 = 0;
      d7 += D1 + D2 + D3;
      t1 = Wt;
   }
   else if (W2 + T1 / 2 < Wt / 2)
   {
      // end block extends beyond top fillet
      w2 = 0;
      w1 = W1 + W2 + T1 / 2 - Wt / 2;
      w1 = (IsZero(w1) ? 0 : w1); // eliminate noise
      d2 = (D2 / W1)*w1;
      d3 = D3 + (D2 - d2);
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
      d4 = 0;
      d5 = 0;
      d6 = 0;
      d7 += D4 + D5 + D6;
      t2 = Wb;
   }
   else if (W4 + T2 / 2 < Wb / 2)
   {
      // end block extends beyond bottom fillet
      w4 = 0;
      w3 = W3 + W4 + T2 / 2 - Wb / 2;
      w3 = (IsZero(w3) ? 0 : w3); // eliminate noise
      d5 = (D5 / W3)*w3;
      d6 = D6 + (D5 - d5);
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

   // near top flange
   if (2 * (W1 + W2 + W3) + T1 < Wt)
   {
      // end block is wider than the top flange
      w1 = 0;
      w2 = 0;
      w3 = 0;
      d1 = 0;
      d2 = 0;
      d3 = 0;
      t1 = Wt;
   }
   else if (W3 + T1 / 2 < Wt / 2)
   {
      // end block extends beyond top fillet
      w3 = 0;
      w2 = W1 + W2 + W3 + T1 / 2 - Wt / 2;
      w2 = (IsZero(w2) ? 0 : w2); // eliminate noise
      d2 = (D2 / W1)*w1;
      d3 = D3 + (D2 - d2);
      t1 = Wt;
   }
   else if (T1 / 2 < Wt / 2)
   {
      // end block intersects top fillet
      w3 = W3 + T1 / 2 - Wt / 2;
      d3 = (D3 / W3)*w3;
      t1 = Wt;
   }

   // near bottom flange
   if (2 * (W4 + W5) + T2 < Wb)
   {
      // end block is wider than the bottom flange
      w4 = 0;
      w5 = 0;
      d4 = 0;
      d5 = 0;
      d6 = 0;
      t2 = Wb;
   }
   else if (W5 + T2 / 2 < Wb / 2)
   {
      // end block extends beyond bottom fillet
      w5 = 0;
      w4 = W4 + W5 + T2 / 2 - Wb / 2;
      w4 = (IsZero(w4) ? 0 : w3); // eliminate noise
      d5 = (D5 / W4)*w4;
      d6 = D6 + (D5 - d5);
      t2 = Wb;
   }
   else if (T2 / 2 < Wb / 2)
   {
      // end block intersects bottom fillet
      w5 = W5 + T2 / 2 - Wb / 2;
      d6 = (D6 / W5)*w5;
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
