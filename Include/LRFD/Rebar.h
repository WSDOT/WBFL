///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#pragma once

#include <Lrfd\LrfdExp.h>
#include <Materials/Rebar.h>
#include <Materials/SimpleConcrete.h>
#include <Lrfd\Details.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Encapsulates constants and equations associated with rebar
      class LRFDCLASS Rebar
      {
      public:
         enum class Usage {
            Longitudinal, // 5.10.2.1
            Transverse,   // 5.10.2.1
            Seismic       // 5.10.2.2
         };

         enum class Hook
         {
            hookNone,
            hook90,
            hook135,
            hook180
         };

         Rebar() = delete;
         Rebar(const Rebar&) = delete;
         ~Rebar() = delete;

         Rebar& operator=(const Rebar&) = delete;

         // Calculates the maximum stress in the bursting zone per 5.10.10.1
         static Float64 GetMaxBurstingStress(Float64 fyRebar);

         //------------------------------------------------------------------------
         // Returns the distance from the ends of the girder within which the bursting
         // stress requirements must be checked. 5.10.10.1
         static Float64 GetBurstingZoneLength( Float64 girderHeight );

         //------------------------------------------------------------------------
         // Returns the minimum bar size in the confinement zone per 5.10.10.2
         // Bar size correlates to lrfdRebarPool
         static WBFL::Materials::Rebar::Size GetMinConfinementBarSize();

         //------------------------------------------------------------------------
         // Returns the minimum bar area in the confinement zone per 5.10.10.2
         static Float64 GetMaxConfinementBarSpacing();

         //------------------------------------------------------------------------
         // Returns the minimum Av/S in the confinement zone per 5.10.10.2
         static Float64 GetMinConfinementAvS();

         //------------------------------------------------------------------------
         // Returns the minimum av/s for detailing per 5.8.2.5
         static Float64 GetAvOverSMin(Float64 fc, Float64 bv, Float64 fy);

         //------------------------------------------------------------------------
         // Returns max bar spacing for Vu over and under limits per 5.8.2.7
         static void GetMaxStirrupSpacing(Float64* sUnderLimit, Float64* sOverLimit);

         //------------------------------------------------------------------------
         // Returns max development length of a rebar in tension per 5.11.2.1.1
         // modification factors are not applied
         static Float64 GetTensileDevelopmentLength(const WBFL::Materials::Rebar& rebar, Float64 fc);

         //------------------------------------------------------------------------
         // Returns the hook extension at the free end of the bar per LRFD 5.10.2.1 and 5.10.2.2
         static Float64 GetHookExtension(WBFL::Materials::Rebar::Size size,Float64 db,Usage usage,Hook hook);

         //------------------------------------------------------------------------
         // Returns the minimum inside bend diameter (LRFD 5.10.2.3)
         // if fractional is true, returns the number of bar diameters
         // otherwise returns the actual bend diameter
         static Float64 GetBendDiameter(WBFL::Materials::Rebar::Size size,Float64 db,Usage usage,bool bFractional);

         //------------------------------------------------------------------------
         // Returns the compression controlled strain limit (LRFD 5.7.2.1)
         static Float64 GetCompressionControlledStrainLimit(WBFL::Materials::Rebar::Grade grade);

         //------------------------------------------------------------------------
         // Returns the tension controlled strain limit (LRFD 5.7.2.1)
         static Float64 GetTensionControlledStrainLimit(WBFL::Materials::Rebar::Grade grade);

         //------------------------------------------------------------------------
         // Returns rebar development length
         static REBARDEVLENGTHDETAILS GetRebarDevelopmentLengthDetails(WBFL::Materials::Rebar::Size size, Float64 Ab, Float64 db, Float64 fy, const WBFL::Materials::SimpleConcrete& concrete,Float64 distFromBottom,bool bEpoxyCoated,bool bMeetsCoverRequirements);
         static REBARDEVLENGTHDETAILS GetRebarDevelopmentLengthDetails(WBFL::Materials::Rebar::Size size, Float64 Ab, Float64 db, Float64 fy, WBFL::Materials::ConcreteType type, Float64 fc, bool isFct, Float64 Fct,Float64 density, Float64 distFromBottom, bool bEpoxyCoated, bool bMeetsCoverRequirements);
      };
   };
};
