///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#pragma once

#include <Lrfd\LrfdExp.h>
#include <System\Flags.h>

namespace WBFL
{
   namespace LRFD
   {
      // possible methods for calculating df's
      constexpr int SPEC_EQN                          = 0x0001;
      constexpr int LEVER_RULE                        = 0x0002;
      constexpr int RIGID_METHOD                      = 0x0004;
      constexpr int LANES_DIV_BEAMS                   = 0x0008; // number of lanes divided by number of beams
      constexpr int SPECIAL_OVERRIDE                  = 0x0010; // special override for method in question 
      constexpr int INTERIOR_OVERRIDE                 = 0x0020; // happens if interior factor is larger than exterior. this is always OR'ed
      constexpr int MOMENT_OVERRIDE                   = 0x0040; // happens if shear factor is overriden by moment. this is always OR'ed
      constexpr int E_OVERRIDE                        = 0x0080; // happens if e factor is used as multiplier with interior g for exterior
      constexpr int S_OVER_D_METHOD                   = 0x0100; // factor was computed using S/D. Always combines with SPEC_EQN.
      constexpr int LANES_BEAMS_OVERRIDE              = 0x0200; // Lanes beams method was used because factor was smaller than lanes beams
      constexpr int OVERRIDE_USING_MULTILANE_FACTOR   = 0x0400; // TxDOT has a case for U Beams where the multi-lane factor is always used (no enveloping required)
      constexpr int MOMENT_SKEW_CORRECTION_APPLIED    = 0x1000;
      constexpr int SHEAR_SKEW_CORRECTION_APPLIED     = 0x2000;

      /// @brief Indicates what to do with range of applicability:
      enum class RangeOfApplicabilityAction 
      { 
         Enforce,            ///< Computation fails if any parameter outside of ROA
         Ignore,             ///< Ignore ROA and compute abiding by any parameters in range
         IgnoreUseLeverRule  ///< Compute g using lever rule if any parameters outside of ROA
      };


      /// @brief Standard interface for all live load distribution factor calculators.
      class LRFDCLASS ILiveLoadDistributionFactor
      {
      public:

         /// @brief Simple class to indicate whether an equation method was used
         /// Previous version or'd all data into Method data member - this put too much strain on reporting classes to determine what actually happened
         struct WasUsed
         {
            bool bWasUsed;

            WasUsed() : bWasUsed(false)
            {;}
         };

         /// @brief Results of distribution factors computed by the LRFD equations
         struct EqnMethod : public WasUsed
         {
            Float64 mg; // Result for basic equation
            Float64 e; // Correction factor for exterior girders (1.0 if interior girder)
            Float64 C;  // C value used in S/D comp. Ignore for other equation methods
            Float64 K;  // K ""             ""                 ""                 ""
            Float64 D;  // D ""             ""                 ""                 "" 
            Float64 m; // multiple presence factor

            EqnMethod() : e(1.0), mg(0.0), C(0.0), K(0.0), D(0.0), m(-1)
            {;}
         };

         /// @brief Results of distribution factors computed by the lever rule
         struct LeverRuleMethod : public WasUsed
         {
            Float64 mg;
            std::vector<Float64> AxleLocations;
            Float64 Sleft; // Girder spacing to left/right of girder
            Float64 Sright;
            Float64 m; // multiple presence factor
            Float64 de; // Used only for exterior girders
            IndexType nLanesUsed; // number of live load lanes actually used
            GirderIndexType Nb; // number of beams (girders)
            bool  bWasExterior; // true if an exterior beam was analyzed

            LeverRuleMethod(): mg(-1.0), Sleft(0.0), Sright(0.0), m(-1), de(0.0), nLanesUsed(-1), Nb(0), bWasExterior(false)
            {;}
         };

         /// @brief Results of distribution factors computed by the rigid method
         struct RigidMethod : public WasUsed
         {
            Float64 mg;
            Float64 Nl;
            Float64 Nb;
            Float64 Xext;
            std::vector<Float64> e;
            std::vector<Float64> x;
            Float64 m; // multiple presence factor

            RigidMethod(): mg(-1.0), Nl(0), Nb(0), Xext(0.0), m(-1)
            {;}
         };

         /// @brief Results of distribution factors computed by the number of lanes and beams method
         struct LanesBeamsMethod : public WasUsed
         {
            Float64 mg;
            IndexType Nl;
            GirderIndexType Nb;
            Float64 m; // multiple presence factor

            LanesBeamsMethod(): mg(-1.0), Nl(0), Nb(0), m(-1)
            {;}
         };

         /// @brief Detailed results from distribution factor calculation
         struct DFResult
         {
            Float64 mg;                    // the answer
            Float64 SkewCorrectionFactor; 
            Int16 ControllingMethod;     // how was it calc'd? (Bitwise OR value)
            EqnMethod       EqnData;
            LeverRuleMethod LeverRuleData;
            RigidMethod     RigidData;
            LanesBeamsMethod LanesBeamsData;

            DFResult(): mg(-1.0), SkewCorrectionFactor(1.0), ControllingMethod(0)
            {;}

            Float64 GetMultiplePresenceFactor() const
            {
               Float64 m;
               if (WBFL::System::Flags<Int16>::IsSet(ControllingMethod, SPEC_EQN))
               {
                  m = EqnData.m;
               }
               else if (WBFL::System::Flags<Int16>::IsSet(ControllingMethod, LEVER_RULE))
               {
                  m = LeverRuleData.m;
               }
               else if (WBFL::System::Flags<Int16>::IsSet(ControllingMethod, RIGID_METHOD))
               {
                  m = RigidData.m;
               }
               else if (WBFL::System::Flags<Int16>::IsSet(ControllingMethod, LANES_DIV_BEAMS))
               {
                  m = LanesBeamsData.m;
               }
               else
               {
                  CHECK(false);
                  m = -1;
               }
               CHECK(0 < m);
               return m;
            }
         };

         enum class Location {IntGirder,ExtGirder};
         enum class DfSide {LeftSide, RightSide}; // side looking up station
         enum class NumLoadedLanes {One,TwoOrMore};
         enum class DeckType {Concrete,SteelGrid,FilledGrid,WoodPlank,
                        StressLaminated,SpikeLaminated,GlueLaminated};

         virtual ~ILiveLoadDistributionFactor() = default;

         virtual Float64 MomentDF(Location loc,NumLoadedLanes numLanes,LimitState ls) const = 0;
         virtual Float64 ShearDF(Location loc,NumLoadedLanes numLanes,LimitState ls) const = 0;
         virtual Float64 ReactionDF(Location loc,NumLoadedLanes numLanes,LimitState ls) const = 0;

         virtual DFResult MomentDFEx(Location loc,NumLoadedLanes numLanes,LimitState ls) const = 0;
         virtual DFResult ShearDFEx(Location loc,NumLoadedLanes numLanes,LimitState ls) const = 0;
         virtual DFResult ReactionDFEx(Location loc,NumLoadedLanes numLanes,LimitState ls) const = 0;

         // ------- use these when overriding equations to get lever rule results with correct skew factors
         virtual ILiveLoadDistributionFactor::DFResult DistributeMomentByLeverRule(Location loc,NumLoadedLanes numLanes,bool applyMpf) const = 0;
         virtual ILiveLoadDistributionFactor::DFResult DistributeShearByLeverRule(Location loc,NumLoadedLanes numLanes, bool applyMpf) const = 0;
         virtual ILiveLoadDistributionFactor::DFResult DistributeReactionByLeverRule(Location loc,NumLoadedLanes numLanes, bool applyMpf) const = 0;
      };
   };
};
