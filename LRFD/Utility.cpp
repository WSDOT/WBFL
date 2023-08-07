///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\Utility.h>
#include <Lrfd\VersionMgr.h>

using namespace WBFL::LRFD;

Float64 Utility::IbeamEffFlangeWidth(Float64 effSpanLength,
                                         Float64 leftSpacing,
                                         Float64 rightSpacing,
                                         Float64 tSlab,
                                         Float64 tWeb,
                                         Float64 wTopFlange,
                                         GirderPosition position)
{
   Float64 wEff;

   if ( position == GirderPosition::Interior)
   {
      //
      // Interior Girder
      //
      Float64 w1,w2,w3;

      w1 = 0.25*effSpanLength;
      w2 = 12.0*tSlab + max(tWeb,0.5*wTopFlange);
      w3 = (leftSpacing + rightSpacing) / 2;

      wEff = min(w1,min(w2,w3));
   }
   else
   {
      //
      // Exterior Girder
      //

      Float64 w1,w2,w3;
      Float64 wEff1, wEff2;

      // Effective width on inboard side
      w1 = 0.25*effSpanLength;
      w2 = 12.0*tSlab + max(tWeb,0.5*wTopFlange);
      w3 = (position == GirderPosition::LeftExterior) ? rightSpacing : leftSpacing;
      
      wEff1 = min(w1,min(w2,w3)) / 2;

      // Effective width on outboard side
      w1 = 0.125*effSpanLength;
      w2 = 6.0*tSlab + max(0.5*tWeb,0.25*wTopFlange);
      w3 = (position == GirderPosition::LeftExterior) ? leftSpacing : rightSpacing;

      wEff2 = min(w1,min(w2,w3));

      wEff = wEff1 + wEff2;
   }

   return wEff;
}

Float64 Utility::GetMultiplePresenceFactor(IndexType nLanesLoaded)
{
   if ( nLanesLoaded == 0 || nLanesLoaded == 1 )
      return 1.2;

   if ( nLanesLoaded == 2 )
      return 1.0;

   if ( nLanesLoaded == 3 )
      return 0.85;

   return 0.65;
}

std::tuple<Float64, Float64, Float64> get_lane_parameters()
{
   Float64 wStdLane; // Standard design lane width
   Float64 wCurbToCurbMin;
   Float64 wCurbToCurbMax;
   if (LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI)
   {
      wStdLane = WBFL::Units::ConvertToSysUnits(3600., WBFL::Units::Measure::Millimeter);
      wCurbToCurbMin = WBFL::Units::ConvertToSysUnits(6000., WBFL::Units::Measure::Millimeter);
      wCurbToCurbMax = WBFL::Units::ConvertToSysUnits(7200., WBFL::Units::Measure::Millimeter);
   }
   else
   {
      wStdLane = WBFL::Units::ConvertToSysUnits(12., WBFL::Units::Measure::Feet);
      wCurbToCurbMin = WBFL::Units::ConvertToSysUnits(20., WBFL::Units::Measure::Feet);
      wCurbToCurbMax = WBFL::Units::ConvertToSysUnits(24., WBFL::Units::Measure::Feet);
   }

   return std::make_tuple(wStdLane, wCurbToCurbMin, wCurbToCurbMax);
}

Float64 Utility::GetDesignLaneWidth(Float64 wCurbToCurb)
{
   auto [wStdLane, wCurbToCurbMin, wCurbToCurbMax] = get_lane_parameters();

   Uint16 nDesignLanes = (Uint16)floor(wCurbToCurb/wStdLane);

   Float64 wDesignLane;
   if ( InRange(wCurbToCurbMin, wCurbToCurb, wCurbToCurbMax) )
      wDesignLane = wCurbToCurb/2.;
   else if (nDesignLanes == 0)
      wDesignLane = wCurbToCurb;
   else
      wDesignLane = wStdLane;

   return wDesignLane;
}

Uint16 Utility::GetNumDesignLanes(Float64 wCurbToCurb)
{
   auto [wStdLane, wCurbToCurbMin, wCurbToCurbMax] = get_lane_parameters();

   Uint16 nDesignLanes = (Uint16)floor(wCurbToCurb/wStdLane);
   if (wCurbToCurb/wStdLane - nDesignLanes > 0.99999 )
      nDesignLanes++; // we are so close to the next number of design lanes, assume round off error and increment

   if ( InRange(wCurbToCurbMin, wCurbToCurb, wCurbToCurbMax) )
      nDesignLanes = 2;

   if ( wCurbToCurb < wCurbToCurbMin && nDesignLanes != 0 )
      nDesignLanes--;

   if ( nDesignLanes == 0 )
      nDesignLanes++;

   return nDesignLanes;
}
