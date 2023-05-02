///////////////////////////////////////////////////////////////////////
// COGOTest - Test Driver for Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// TestAlignment1.cpp: implementation of the CTestAlignment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestAlignment1.h"
#include <WBFLCogo\CogoHelpers.h>
#include <CoordGeom/Utilities.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void AlignmentDump(IAlignment* pAlignment, std::ostream& os)
{
   std::vector<Float64> vStations = linspace(0.00, 700.0, 50);

   for (const auto& station : vStations)
   {
      CComPtr<IPoint2d> pnt;
      pAlignment->LocatePoint(CComVariant(station), omtAlongDirection, 0.0, CComVariant(0), &pnt);
      Float64 x, y;
      pnt->Location(&x, &y);
      os << x << ", " << y << std::endl;
   }
}

void CommonAlignmentTest(IAlignment* alignment,Float64 xSign,Float64 ySign)
{
   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   Float64 alignment_offset = (ySign / xSign) * 10;
   CComPtr<IDirection> dir;
   Float64 dirVal;
   CComPtr<IPoint2d> pnt;
   Float64 x, y;
   CComPtr<IStation> station;
   Float64 offset;
   Float64 stationVal;

   auto AlignmentDirection = [&xSign, &ySign](Float64 dir) {return WBFL::COGO::Utilities::NormalizeAngle(atan2(ySign * tan(dir), xSign)); };

   // Sta 0+00
   Float64 alignment_direction = AlignmentDirection(0.0);
   TRY_TEST(alignment->GetBearing(CComVariant(0.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, alignment_direction), true);

   dir.Release();
   TRY_TEST(alignment->GetNormal(CComVariant(0.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, WBFL::COGO::Utilities::NormalizeAngle(alignment_direction + 3 * PI_OVER_2)), true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(0.00), omtAlongDirection, alignment_offset, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, xSign*-100.0), true);
   TRY_TEST(IsEqual(y, ySign*-10.0), true);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(pnt, &station, &offset), S_OK);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 0.00), true);
   TRY_TEST(IsEqual(offset, alignment_offset), true);

   CComPtr<IPoint2d> newPnt;
   station.Release();
   VARIANT_BOOL vbOnProjection;
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &station, &vbOnProjection), S_OK);
   newPnt->get_X(&x);
   newPnt->get_Y(&y);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 0.00), true);
   TRY_TEST(IsEqual(x, xSign * -100.0), true);
   TRY_TEST(IsEqual(y, ySign * 0.0), true);
   TRY_TEST(vbOnProjection, VARIANT_TRUE);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 0.00), true);


   // Sta 1+00
   alignment_direction = AlignmentDirection(0.0);
   dir.Release();
   TRY_TEST(alignment->GetBearing(CComVariant(100.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, alignment_direction), true);

   dir.Release();
   TRY_TEST(alignment->GetNormal(CComVariant(100.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, WBFL::COGO::Utilities::NormalizeAngle(alignment_direction + 3 * PI_OVER_2)), true);
   pnt.Release();

   TRY_TEST(alignment->LocatePoint(CComVariant(100.00), omtAlongDirection, alignment_offset, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, xSign*0.0), true);
   TRY_TEST(IsEqual(y, ySign*-10.0), true);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, alignment_offset), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 100.00), true);

   newPnt.Release();
   station.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &station, &vbOnProjection), S_OK);
   newPnt->get_X(&x);
   newPnt->get_Y(&y);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 100.00), true);
   TRY_TEST(IsEqual(x, xSign * 0.0), true);
   TRY_TEST(IsEqual(y, ySign * 0.0), true);
   TRY_TEST(vbOnProjection, VARIANT_FALSE);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 100.00), true);

   // Sta 1+25
   alignment_direction = AlignmentDirection(0.0);
   dir.Release();
   TRY_TEST(alignment->GetBearing(CComVariant(125.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, alignment_direction), true);

   dir.Release();
   TRY_TEST(alignment->GetNormal(CComVariant(125.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, WBFL::COGO::Utilities::NormalizeAngle(alignment_direction + 3 * PI_OVER_2)), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(125.00), omtAlongDirection, alignment_offset, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, xSign*25.0), true);
   TRY_TEST(IsEqual(y, ySign*-10.0), true);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, alignment_offset), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 125.00), true);

   newPnt.Release();
   station.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &station, &vbOnProjection), S_OK);
   newPnt->get_X(&x);
   newPnt->get_Y(&y);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 125.00), true);
   TRY_TEST(IsEqual(x, xSign * 25.0), true);
   TRY_TEST(IsEqual(y, ySign * 0.0), true);
   TRY_TEST(vbOnProjection, VARIANT_FALSE);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 125.00), true);

   // Sta 2+00
   dir.Release();
   alignment_direction = AlignmentDirection(M_PI/4);
   TRY_TEST(alignment->GetBearing(CComVariant(200.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, alignment_direction), true);

   dir.Release();
   TRY_TEST(alignment->GetNormal(CComVariant(200.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, WBFL::COGO::Utilities::NormalizeAngle(alignment_direction + 3 * PI_OVER_2)), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(200.00), omtAlongDirection, alignment_offset, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, xSign*107.0710678), true);
   TRY_TEST(IsEqual(y, ySign*-7.0710678), true);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, alignment_offset), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 200.00), true);

   newPnt.Release();
   station.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &station, &vbOnProjection), S_OK);
   newPnt->get_X(&x);
   newPnt->get_Y(&y);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 200.00), true);
   TRY_TEST(IsEqual(x, xSign * 100.0), true);
   TRY_TEST(IsEqual(y, ySign * 0.0), true);
   TRY_TEST(vbOnProjection, VARIANT_FALSE);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 200.00), true);

   // Sta 2+50
   alignment_direction = AlignmentDirection(M_PI / 4);
   dir.Release();
   TRY_TEST(alignment->GetBearing(CComVariant(250.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, alignment_direction), true);

   dir.Release();
   TRY_TEST(alignment->GetNormal(CComVariant(250.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, WBFL::COGO::Utilities::NormalizeAngle(alignment_direction + 3 * PI_OVER_2)), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(250.00), omtAlongDirection, alignment_offset, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, xSign*142.4264, 0.001), true);
   TRY_TEST(IsEqual(y, ySign*28.2843, 0.001), true);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, alignment_offset), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 250.00), true);

   newPnt.Release();
   station.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &station, &vbOnProjection), S_OK);
   newPnt->get_X(&x);
   newPnt->get_Y(&y);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 250.0), true);
   TRY_TEST(IsEqual(x, xSign * 135.35533905932738), true);
   TRY_TEST(IsEqual(y, ySign * 35.355339059327392), true);
   TRY_TEST(vbOnProjection, VARIANT_FALSE);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 250.00), true);

   // Sta 3+00
   alignment_direction = AlignmentDirection(5.8195376981787801);
   dir.Release();
   TRY_TEST(alignment->GetBearing(CComVariant(300.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, alignment_direction), true);

   dir.Release();
   TRY_TEST(alignment->GetNormal(CComVariant(300.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, WBFL::COGO::Utilities::NormalizeAngle(alignment_direction + 3* PI_OVER_2)), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(300.00), omtAlongDirection, alignment_offset, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, xSign*171.7250, 0.001), true);
   TRY_TEST(IsEqual(y, ySign*27.9571, 0.001), true);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, alignment_offset), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 300.00), true);

   newPnt.Release();
   station.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &station, &vbOnProjection), S_OK);
   newPnt->get_X(&x);
   newPnt->get_Y(&y);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 300.0), true);
   TRY_TEST(IsEqual(x, xSign * 176.19716589662397), true);
   TRY_TEST(IsEqual(y, ySign * 36.901417051688000), true);
   TRY_TEST(vbOnProjection, VARIANT_FALSE);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 300.00), true);

   // Sta 4+90
   alignment_direction = AlignmentDirection(0.0084083531428916);
   dir.Release();
   TRY_TEST(alignment->GetBearing(CComVariant(490.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, alignment_direction), true);

   dir.Release();
   TRY_TEST(alignment->GetNormal(CComVariant(490.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, WBFL::COGO::Utilities::NormalizeAngle(alignment_direction + 3 * PI_OVER_2)), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(490.00), omtAlongDirection, alignment_offset, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, xSign*357.5699, 0.001), true);
   TRY_TEST(IsEqual(y, ySign*-9.9882, 0.001), true);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, alignment_offset), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 490.00), true);

   newPnt.Release();
   station.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &station, &vbOnProjection), S_OK);
   newPnt->get_X(&x);
   newPnt->get_Y(&y);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 490.), true);
   TRY_TEST(IsEqual(x, xSign * 357.48589488932885), true);
   TRY_TEST(IsEqual(y, ySign * 0.011493657282799078), true);
   TRY_TEST(vbOnProjection, VARIANT_FALSE);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 490.00), true);

   // Sta 5+30
   alignment_direction = AlignmentDirection(0.39101);
   dir.Release();
   TRY_TEST(alignment->GetBearing(CComVariant(530.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, alignment_direction), true);

   dir.Release();
   TRY_TEST(alignment->GetNormal(CComVariant(530.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, WBFL::COGO::Utilities::NormalizeAngle(alignment_direction + 3 * PI_OVER_2)), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(530.00), omtAlongDirection, alignment_offset, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, xSign*400.3079, 0.001), true);
   TRY_TEST(IsEqual(y, ySign*-1.65612, 0.001), true);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, alignment_offset), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 530.00), true);

   newPnt.Release();
   station.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &station, &vbOnProjection), S_OK);
   newPnt->get_X(&x);
   newPnt->get_Y(&y);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 530.), true);
   TRY_TEST(IsEqual(x, xSign * 396.49675804330548), true);
   TRY_TEST(IsEqual(y, ySign * 7.5891337029933084), true);
   TRY_TEST(vbOnProjection, VARIANT_FALSE);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 530.00), true);

   // Sta 5+65
   alignment_direction = AlignmentDirection(0.73327699338782193);
   dir.Release();
   TRY_TEST(alignment->GetBearing(CComVariant(565.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, alignment_direction), true);

   dir.Release();
   TRY_TEST(alignment->GetNormal(CComVariant(565.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, WBFL::COGO::Utilities::NormalizeAngle(alignment_direction + 3 * PI_OVER_2)), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(565.00), omtAlongDirection, alignment_offset, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, xSign*432.5904, 0.001), true);
   TRY_TEST(IsEqual(y, ySign*18.8222, 0.001), true);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, alignment_offset), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 565.00), true);

   newPnt.Release();
   station.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &station, &vbOnProjection), S_OK);
   newPnt->get_X(&x);
   newPnt->get_Y(&y);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 565.0), true);
   TRY_TEST(IsEqual(x, xSign * 425.89739504565671), true);
   TRY_TEST(IsEqual(y, ySign * 26.252094830906742), true);
   TRY_TEST(vbOnProjection, VARIANT_FALSE);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 565.00), true);

   // Sta 6+00
   alignment_direction = AlignmentDirection(M_PI/4);
   dir.Release();
   TRY_TEST(alignment->GetBearing(CComVariant(600.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, alignment_direction), true);

   dir.Release();
   TRY_TEST(alignment->GetNormal(CComVariant(600.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, WBFL::COGO::Utilities::NormalizeAngle(alignment_direction + 3 * PI_OVER_2)), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(600.00), omtAlongDirection, alignment_offset, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, xSign*457.8918, 0.001), true);
   TRY_TEST(IsEqual(y, ySign*43.7496, 0.001), true);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, alignment_offset), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 600.00), true);

   newPnt.Release();
   station.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &station, &vbOnProjection), S_OK);
   newPnt->get_X(&x);
   newPnt->get_Y(&y);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 600.), true);
   TRY_TEST(IsEqual(x, xSign * 450.82071075337751), true);
   TRY_TEST(IsEqual(y, ySign * 50.820710753377611), true);
   TRY_TEST(vbOnProjection, VARIANT_TRUE);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 600.00), true);

   // Sta 7+00
   alignment_direction = AlignmentDirection(M_PI / 4);
   dir.Release();
   TRY_TEST(alignment->GetBearing(CComVariant(700.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, alignment_direction), true);

   dir.Release();
   TRY_TEST(alignment->GetNormal(CComVariant(700.00), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, WBFL::COGO::Utilities::NormalizeAngle(alignment_direction + 3 * PI_OVER_2)), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(700.00), omtAlongDirection, alignment_offset, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, xSign*528.6024, 0.001), true);
   TRY_TEST(IsEqual(y, ySign*114.4603, 0.001), true);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, alignment_offset), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 700.00), true);

   newPnt.Release();
   station.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &station, &vbOnProjection), S_OK);
   newPnt->get_X(&x);
   newPnt->get_Y(&y);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 700.), true);
   TRY_TEST(IsEqual(x, xSign * 521.53138887203227), true);
   TRY_TEST(IsEqual(y, ySign * 121.531388872032281), true);
   TRY_TEST(vbOnProjection, VARIANT_TRUE);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->get_Value(&stationVal);
   TRY_TEST(IsEqual(stationVal, 700.00), true);


   // Add a station equation
   alignment->AddStationEquation(650, 800);

   CComPtr<IStation> objStation;
   alignment->ConvertFromNormalizedStation(700, &objStation);

   ZoneIndexType idx;
   objStation->GetStation(&idx, &stationVal);
   TRY_TEST(idx, 1);
   TRY_TEST(IsEqual(stationVal, 850.0), true);

   // Sta 8+50 (station range 1)
   alignment_direction = AlignmentDirection(M_PI / 4);
   dir.Release();
   TRY_TEST(alignment->GetBearing(CComVariant(objStation), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, alignment_direction), true);

   dir.Release();
   TRY_TEST(alignment->GetNormal(CComVariant(objStation), &dir), S_OK);
   dir->get_Value(&dirVal);
   TRY_TEST(IsEqual(dirVal, WBFL::COGO::Utilities::NormalizeAngle(alignment_direction + 3 * PI_OVER_2)), true);

   pnt.Release();
   TRY_TEST(alignment->LocatePoint(CComVariant(objStation), omtAlongDirection, alignment_offset, CComVariant(dirVal), &pnt), S_OK);
   pnt->get_X(&x);
   pnt->get_Y(&y);
   TRY_TEST(IsEqual(x, xSign*528.6024, 0.001), true);
   TRY_TEST(IsEqual(y, ySign*114.4603, 0.001), true);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(pnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, alignment_offset), true);
   station->GetStation(&idx, &stationVal);
   TRY_TEST(idx, 1);
   TRY_TEST(IsEqual(stationVal, 850.0), true);

   newPnt.Release();
   station.Release();
   TRY_TEST(alignment->ProjectPoint(pnt, &newPnt, &station, &vbOnProjection), S_OK);
   newPnt->get_X(&x);
   newPnt->get_Y(&y);
   station->GetStation(&idx, &stationVal);
   TRY_TEST(idx, 1);
   TRY_TEST(IsEqual(stationVal, 850.0), true);
   TRY_TEST(IsEqual(x, xSign * 521.53138887203227), true);
   TRY_TEST(IsEqual(y, ySign * 121.531388872032281), true);
   TRY_TEST(vbOnProjection, VARIANT_TRUE);

   station.Release();
   TRY_TEST(alignment->StationAndOffset(newPnt, &station, &offset), S_OK);
   TRY_TEST(IsEqual(offset, 0.0), true);
   station->GetStation(&idx, &stationVal);
   TRY_TEST(idx, 1);
   TRY_TEST(IsEqual(stationVal, 850.0), true);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestAlignment1::CTestAlignment1()
{

}

void CTestAlignment1::Test()
{
   Test1();
   Test1a();
   Test2();
   Test2a();
   Test3();
   Test3a();
   Test4();
   Test4a();
}

void CTestAlignment1::Test1()
{
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0,0);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(100,0);

   CComPtr<IPathSegment> segment;
   segment.CoCreateInstance(CLSID_PathSegment);
   segment->ThroughPoints(p1, p2);
   CComQIPtr<IPathElement> element(segment);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(150,50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(250,0);

   CComPtr<IPathSegment> ls;
   ls.CoCreateInstance(CLSID_PathSegment);
   ls->ThroughPoints(start,end);
   element.Release();
   ls->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> pbt;
   pbt.CoCreateInstance(CLSID_Point2d);
   pbt->Move(300,0);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(400,0);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(500,100);

   CComPtr<ICompoundCurve> hc;
   hc.CoCreateInstance(CLSID_CompoundCurve);
   hc->put_PBT(pbt);
   hc->put_PI(pi);
   hc->put_PFT(pft);
   hc->put_Radius(100);
   hc->put_SpiralLength(spEntry,10);
   hc->put_SpiralLength(spExit,20);
   element.Release();
   hc->QueryInterface(&element);
   alignment->AddPathElement(element);

   //AlignmentDump(alignment, std::cout);

   //////////////
   // Bearing, Normal, LocatePoint, Station, and Offset
   CComPtr<IDirection> dir;
   CComPtr<IPoint2d> pnt;
   CComPtr<IStation> station;
   Float64 offset;

   TRY_TEST(alignment->GetBearing(CComVariant(0.00),nullptr),E_POINTER);
   TRY_TEST(alignment->GetNormal(CComVariant(0.00),nullptr),E_POINTER);
   TRY_TEST(alignment->LocatePoint(CComVariant(125),omtAlongDirection, 10,CComVariant(PI_OVER_2),nullptr),E_POINTER);
   TRY_TEST(alignment->StationAndOffset(end,&station,nullptr),E_POINTER);
   TRY_TEST(alignment->StationAndOffset(end,nullptr,&offset),E_POINTER);
   TRY_TEST(alignment->StationAndOffset(nullptr,&station,&offset),E_INVALIDARG);
   TRY_TEST(alignment->ProjectPoint(end,nullptr,nullptr,nullptr),E_POINTER);
   start.Release();
   TRY_TEST(alignment->ProjectPoint(nullptr,&start,nullptr,nullptr),E_INVALIDARG);

   CommonAlignmentTest(alignment, 1.0, 1.0);
}

void CTestAlignment1::Test1a()
{
   // this test is the same as Test1 except we use a transition curve, circular curve, transition curve instead of a compound curve
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0, 0);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(100, 0);

   CComPtr<IPathSegment> segment;
   segment.CoCreateInstance(CLSID_PathSegment);
   segment->ThroughPoints(p1, p2);
   CComQIPtr<IPathElement> element(segment);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(150, 50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(250, 0);

   CComPtr<IPathSegment> ls;
   ls.CoCreateInstance(CLSID_PathSegment);
   ls->ThroughPoints(start, end);
   element.Release();
   ls->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> start_entry_spiral;
   start_entry_spiral.CoCreateInstance(CLSID_Point2d);
   start_entry_spiral->Move(353.385105248, 0);

   CComPtr<IDirection> start_entry_spiral_direction;
   start_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_entry_spiral_direction->put_Value(0.0);

   CComPtr<IPoint2d> end_entry_spiral;
   end_entry_spiral.CoCreateInstance(CLSID_Point2d);
   end_entry_spiral->Move(363.3826055,0.1666369);

   CComPtr<IDirection> end_entry_spiral_direction;
   end_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_entry_spiral_direction->put_Value(0.05);



   CComPtr<IPoint2d> start_exit_spiral;
   start_exit_spiral.CoCreateInstance(CLSID_Point2d);
   start_exit_spiral->Move(421.682819278,22.624955);

   CComPtr<IDirection> start_exit_spiral_direction;
   start_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_exit_spiral_direction->put_Value(0.685398116);

   CComPtr<IPoint2d> end_exit_spiral;
   end_exit_spiral.CoCreateInstance(CLSID_Point2d);
   end_exit_spiral->Move(436.2818872224,36.2818872224);

   CComPtr<IDirection> end_exit_spiral_direction;
   end_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_exit_spiral_direction->put_Value(M_PI/4);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(396.225283748,1.8101406324);

   CComPtr<ITransitionCurve> entry_transition;
   entry_transition.CoCreateInstance(CLSID_TransitionCurve);
   entry_transition->Init(start_entry_spiral,CComVariant(start_entry_spiral_direction),0.0,100.0,10, Clothoid);
   element.Release();
   entry_transition->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<ICircularCurve> curve;
   curve.CoCreateInstance(CLSID_CircularCurve);
   curve->put_PBT(end_entry_spiral);
   curve->put_PI(pi);
   curve->put_PFT(start_exit_spiral);
   curve->put_Radius(100);
   element.Release();
   curve->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<ITransitionCurve> exit_transition;
   exit_transition.CoCreateInstance(CLSID_TransitionCurve);
   exit_transition->Init(start_exit_spiral, CComVariant(start_exit_spiral_direction), 100.0, 0.0, 20, Clothoid);
   element.Release();
   exit_transition->QueryInterface(&element);
   alignment->AddPathElement(element);


   //AlignmentDump(alignment, std::cout);


   CommonAlignmentTest(alignment, 1.0, 1.0);
}

void CTestAlignment1::Test2()
{
   // Mirror Test1 about X axis
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0, 0);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(100, 0);

   CComPtr<IPathSegment> segment;
   segment.CoCreateInstance(CLSID_PathSegment);
   segment->ThroughPoints(p1, p2);
   CComQIPtr<IPathElement> element(segment);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(150, -50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(250, 0);

   CComPtr<IPathSegment> ls;
   ls.CoCreateInstance(CLSID_PathSegment);
   ls->ThroughPoints(start, end);
   element.Release();
   ls->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> pbt;
   pbt.CoCreateInstance(CLSID_Point2d);
   pbt->Move(300,0);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(400,0);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(500,-100);

   CComPtr<ICompoundCurve> hc;
   hc.CoCreateInstance(CLSID_CompoundCurve);
   hc->put_PBT(pbt);
   hc->put_PI(pi);
   hc->put_PFT(pft);
   hc->put_Radius(100);
   hc->put_SpiralLength(spEntry,10);
   hc->put_SpiralLength(spExit,20);
   element.Release();
   hc->QueryInterface(&element);
   alignment->AddPathElement(element);

   //AlignmentDump(alignment, std::cout);

   CommonAlignmentTest(alignment, 1.0, -1.0);
}

void CTestAlignment1::Test2a()
{
   // Mirror Test1a about X axis
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0, 0);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(100, 0);

   CComPtr<IPathSegment> segment;
   segment.CoCreateInstance(CLSID_PathSegment);
   segment->ThroughPoints(p1, p2);
   CComQIPtr<IPathElement> element(segment);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(150, -50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(250, 0);

   CComPtr<IPathSegment> ls;
   ls.CoCreateInstance(CLSID_PathSegment);
   ls->ThroughPoints(start, end);
   element.Release();
   ls->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> start_entry_spiral;
   start_entry_spiral.CoCreateInstance(CLSID_Point2d);
   start_entry_spiral->Move(353.385105248, 0);

   CComPtr<IDirection> start_entry_spiral_direction;
   start_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_entry_spiral_direction->put_Value(0.0);

   CComPtr<IPoint2d> end_entry_spiral;
   end_entry_spiral.CoCreateInstance(CLSID_Point2d);
   end_entry_spiral->Move(363.3826055, -0.1666369);

   CComPtr<IDirection> end_entry_spiral_direction;
   end_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_entry_spiral_direction->put_Value(TWO_PI - 0.05);



   CComPtr<IPoint2d> start_exit_spiral;
   start_exit_spiral.CoCreateInstance(CLSID_Point2d);
   start_exit_spiral->Move(421.682819278, -22.624955);

   CComPtr<IDirection> start_exit_spiral_direction;
   start_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_exit_spiral_direction->put_Value(TWO_PI - 0.685398116);

   CComPtr<IPoint2d> end_exit_spiral;
   end_exit_spiral.CoCreateInstance(CLSID_Point2d);
   end_exit_spiral->Move(436.2818872224, -36.2818872224);

   CComPtr<IDirection> end_exit_spiral_direction;
   end_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_exit_spiral_direction->put_Value(TWO_PI - M_PI / 4);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(396.225283748, -1.8101406324);

   CComPtr<ITransitionCurve> entry_transition;
   entry_transition.CoCreateInstance(CLSID_TransitionCurve);
   entry_transition->Init(start_entry_spiral, CComVariant(start_entry_spiral_direction), 0.0, -100.0, 10, Clothoid);
   element.Release();
   entry_transition->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<ICircularCurve> curve;
   curve.CoCreateInstance(CLSID_CircularCurve);
   curve->put_PBT(end_entry_spiral);
   curve->put_PI(pi);
   curve->put_PFT(start_exit_spiral);
   curve->put_Radius(100);
   element.Release();
   curve->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<ITransitionCurve> exit_transition;
   exit_transition.CoCreateInstance(CLSID_TransitionCurve);
   exit_transition->Init(start_exit_spiral, CComVariant(start_exit_spiral_direction), -100.0, 0.0, 20, Clothoid);
   element.Release();
   exit_transition->QueryInterface(&element);
   alignment->AddPathElement(element);

   //CComPtr<IPoint2d> pft;
   //pft.CoCreateInstance(CLSID_Point2d);
   //pft->Move(500, -100);

   //alignment->AddEx(pft);

   //AlignmentDump(alignment, std::cout);
   CommonAlignmentTest(alignment, 1.0, -1.0);
}

void CTestAlignment1::Test3()
{
   // Mirror Test1 about Y axis
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0,0);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(-100,0);

   CComPtr<IPathSegment> segment;
   segment.CoCreateInstance(CLSID_PathSegment);
   segment->ThroughPoints(p1, p2);
   CComQIPtr<IPathElement> element(segment);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(-150,50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(-250,0);

   CComPtr<IPathSegment> ls;
   ls.CoCreateInstance(CLSID_PathSegment);
   ls->ThroughPoints(start, end);
   element.Release();
   ls->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> pbt;
   pbt.CoCreateInstance(CLSID_Point2d);
   pbt->Move(-300,0);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(-400,0);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(-500,100);

   CComPtr<ICompoundCurve> hc;
   hc.CoCreateInstance(CLSID_CompoundCurve);
   hc->put_PBT(pbt);
   hc->put_PI(pi);
   hc->put_PFT(pft);
   hc->put_Radius(100);
   hc->put_SpiralLength(spEntry,10);
   hc->put_SpiralLength(spExit,20);
   element.Release();
   hc->QueryInterface(&element);
   alignment->AddPathElement(element);

   CommonAlignmentTest(alignment, -1.0, 1.0);
}

void CTestAlignment1::Test3a()
{
   // Mirror Test1 about Y axis
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0, 0);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(-100, 0);

   CComPtr<IPathSegment> segment;
   segment.CoCreateInstance(CLSID_PathSegment);
   segment->ThroughPoints(p1, p2);
   CComQIPtr<IPathElement> element(segment);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(-150, 50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(-250, 0);

   CComPtr<IPathSegment> ls;
   ls.CoCreateInstance(CLSID_PathSegment);
   ls->ThroughPoints(start, end);
   element.Release();
   ls->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> start_entry_spiral;
   start_entry_spiral.CoCreateInstance(CLSID_Point2d);
   start_entry_spiral->Move(-353.385105248, 0);

   CComPtr<IDirection> start_entry_spiral_direction;
   start_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_entry_spiral_direction->put_Value(M_PI);

   CComPtr<IPoint2d> end_entry_spiral;
   end_entry_spiral.CoCreateInstance(CLSID_Point2d);
   end_entry_spiral->Move(-363.3826055, 0.1666369);

   CComPtr<IDirection> end_entry_spiral_direction;
   end_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_entry_spiral_direction->put_Value(M_PI - 0.05);



   CComPtr<IPoint2d> start_exit_spiral;
   start_exit_spiral.CoCreateInstance(CLSID_Point2d);
   start_exit_spiral->Move(-421.682819278, 22.624955);

   CComPtr<IDirection> start_exit_spiral_direction;
   start_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_exit_spiral_direction->put_Value(M_PI - 0.685398116);

   CComPtr<IPoint2d> end_exit_spiral;
   end_exit_spiral.CoCreateInstance(CLSID_Point2d);
   end_exit_spiral->Move(-436.2818872224, 36.2818872224);

   CComPtr<IDirection> end_exit_spiral_direction;
   end_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_exit_spiral_direction->put_Value(M_PI - M_PI / 4);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(-396.225283748, 1.8101406324);

   CComPtr<ITransitionCurve> entry_transition;
   entry_transition.CoCreateInstance(CLSID_TransitionCurve);
   entry_transition->Init(start_entry_spiral, CComVariant(start_entry_spiral_direction), 0.0, -100.0, 10, Clothoid);
   element.Release();
   entry_transition->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<ICircularCurve> curve;
   curve.CoCreateInstance(CLSID_CircularCurve);
   curve->put_PBT(end_entry_spiral);
   curve->put_PI(pi);
   curve->put_PFT(start_exit_spiral);
   curve->put_Radius(100);
   element.Release();
   curve->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<ITransitionCurve> exit_transition;
   exit_transition.CoCreateInstance(CLSID_TransitionCurve);
   exit_transition->Init(start_exit_spiral, CComVariant(start_exit_spiral_direction), -100.0, 0.0, 20, Clothoid);
   element.Release();
   exit_transition->QueryInterface(&element);
   alignment->AddPathElement(element);

   //CComPtr<IPoint2d> pft;
   //pft.CoCreateInstance(CLSID_Point2d);
   //pft->Move(-500, 100);

   //alignment->AddEx(pft);

   CommonAlignmentTest(alignment, -1.0, 1.0);
}

void CTestAlignment1::Test4()
{
   // Mirror Test1 about both X and Y axis
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0,0);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(-100,0);

   CComPtr<IPathSegment> segment;
   segment.CoCreateInstance(CLSID_PathSegment);
   segment->ThroughPoints(p1, p2);
   CComQIPtr<IPathElement> element(segment);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(-150,-50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(-250,0);

   CComPtr<IPathSegment> ls;
   ls.CoCreateInstance(CLSID_PathSegment);
   ls->ThroughPoints(start, end);
   element.Release();
   ls->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> pbt;
   pbt.CoCreateInstance(CLSID_Point2d);
   pbt->Move(-300,0);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(-400,0);

   CComPtr<IPoint2d> pft;
   pft.CoCreateInstance(CLSID_Point2d);
   pft->Move(-500,-100);

   CComPtr<ICompoundCurve> hc;
   hc.CoCreateInstance(CLSID_CompoundCurve);
   hc->put_PBT(pbt);
   hc->put_PI(pi);
   hc->put_PFT(pft);
   hc->put_Radius(100);
   hc->put_SpiralLength(spEntry,10);
   hc->put_SpiralLength(spExit,20);
   element.Release();
   hc->QueryInterface(&element);
   alignment->AddPathElement(element);

   CommonAlignmentTest(alignment, -1.0, -1.0);
}

void CTestAlignment1::Test4a()
{
   // Mirror Test1 about both X and Y axis
   CComPtr<IAlignment> alignment;
   alignment.CoCreateInstance(CLSID_Alignment);

   alignment->put_RefStation(CComVariant(100.00));

   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance(CLSID_Point2d);
   p1->Move(0, 0);

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance(CLSID_Point2d);
   p2->Move(-100, 0);

   CComPtr<IPathSegment> segment;
   segment.CoCreateInstance(CLSID_PathSegment);
   segment->ThroughPoints(p1, p2);
   CComQIPtr<IPathElement> element(segment);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> start;
   start.CoCreateInstance(CLSID_Point2d);
   start->Move(-150, -50);

   CComPtr<IPoint2d> end;
   end.CoCreateInstance(CLSID_Point2d);
   end->Move(-250, 0);

   CComPtr<IPathSegment> ls;
   ls.CoCreateInstance(CLSID_PathSegment);
   ls->ThroughPoints(start, end);
   element.Release();
   ls->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<IPoint2d> start_entry_spiral;
   start_entry_spiral.CoCreateInstance(CLSID_Point2d);
   start_entry_spiral->Move(-353.385105248, 0);

   CComPtr<IDirection> start_entry_spiral_direction;
   start_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_entry_spiral_direction->put_Value(M_PI);

   CComPtr<IPoint2d> end_entry_spiral;
   end_entry_spiral.CoCreateInstance(CLSID_Point2d);
   end_entry_spiral->Move(-363.3826055, -0.1666369);

   CComPtr<IDirection> end_entry_spiral_direction;
   end_entry_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_entry_spiral_direction->put_Value(M_PI + 0.05);



   CComPtr<IPoint2d> start_exit_spiral;
   start_exit_spiral.CoCreateInstance(CLSID_Point2d);
   start_exit_spiral->Move(-421.682819278, -22.624955);

   CComPtr<IDirection> start_exit_spiral_direction;
   start_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   start_exit_spiral_direction->put_Value(M_PI + 0.685398116);

   CComPtr<IPoint2d> end_exit_spiral;
   end_exit_spiral.CoCreateInstance(CLSID_Point2d);
   end_exit_spiral->Move(-436.2818872224, -36.2818872224);

   CComPtr<IDirection> end_exit_spiral_direction;
   end_exit_spiral_direction.CoCreateInstance(CLSID_Direction);
   end_exit_spiral_direction->put_Value(M_PI + M_PI / 4);

   CComPtr<IPoint2d> pi;
   pi.CoCreateInstance(CLSID_Point2d);
   pi->Move(-396.225283748, -1.8101406324);

   CComPtr<ITransitionCurve> entry_transition;
   entry_transition.CoCreateInstance(CLSID_TransitionCurve);
   entry_transition->Init(start_entry_spiral, CComVariant(start_entry_spiral_direction), 0.0, 100.0, 10, Clothoid);
   element.Release();
   entry_transition->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<ICircularCurve> curve;
   curve.CoCreateInstance(CLSID_CircularCurve);
   curve->put_PBT(end_entry_spiral);
   curve->put_PI(pi);
   curve->put_PFT(start_exit_spiral);
   curve->put_Radius(100);
   element.Release();
   curve->QueryInterface(&element);
   alignment->AddPathElement(element);

   CComPtr<ITransitionCurve> exit_transition;
   exit_transition.CoCreateInstance(CLSID_TransitionCurve);
   exit_transition->Init(start_exit_spiral, CComVariant(start_exit_spiral_direction), 100.0, 0.0, 20, Clothoid);
   element.Release();
   exit_transition->QueryInterface(&element);
   alignment->AddPathElement(element);

   //CComPtr<IPoint2d> pft;
   //pft.CoCreateInstance(CLSID_Point2d);
   //pft->Move(-500, -100);

   //alignment->AddEx(pft);

   CommonAlignmentTest(alignment, -1.0, -1.0);
}
