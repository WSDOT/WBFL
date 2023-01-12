///////////////////////////////////////////////////////////////////////
// Stability
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

#pragma once

#include <Stability/StabilityExp.h>
#include <Stability/Results.h>
#include <WBFLGenericBridgeTools/AlternativeTensileStressCalculator.h>
#include <array>

namespace WBFL
{
   namespace Stability
   {

      /// Hauling analysis results at a section
      class STABILITYCLASS HaulingSectionResult
      {
      public:
         HaulingSectionResult();

         IndexType AnalysisPointIndex; ///< index of the analysis point for these results

         Float64 Mg;  ///< moment due to girder weight
         Float64 Mw;  ///< transverse moment due to wind
         Float64 Mcf; ///< transverse moment due to CF

         std::array<Float64, 4> fps;   ///< corner stresses due to prestressing (array indices are [+corner])
         std::array<Float64, 4> fg;    ///< corner stresses due to girder weight without impact (array indices are [+corner])
         std::array<Float64, 4> fw;    ///< corner stresses due to wind towards the left (array indices are [+corner])
         std::array<Float64, 4> fcf;   ///< corner stresses due to centrifugal towards the left (array indices are [+corner])

         Float64 fDirect[2][3][4]; ///< stress due to direct loads (girder self weight and ps). Array indices are [HaulingSlope][ImpactDirection][+corner]

         Float64 fTilt[2][3][2][4];   ///< stress due to equilibrium rotation of girder caused by girder self weight. Array indices are [HaulingSlope][ImpactDirection][WindDirection][+corner]
         Float64 f[2][3][2][4];       ///< stress at a corner (fDirect + fTilt + fWind + fCF). Array indices are [HaulingSlope][ImpactDirection][WindDirection][+corner]

         Float64 fMinDirect[2][2];    ///< min direct stress. Array indices are [HaulingSlope][GirderFace]
         ImpactDirection MinDirectStressImpactDirection[2][2];    ///< impact direction associated with the minimum girder stress. Array indices are [HaulingSlope][GirderFace]
         Corner MinDirectStressCorner[2][2];             ///< corner where the minimum girder stress occurs. Array indices are [HaulingSlope][GirderFace]

         Float64 fMaxDirect[2][2];    ///< max direction stress. Array indices are [HaulingSlope][GirderFace]
         ImpactDirection MaxDirectStressImpactDirection[2][2];    ///< impact direction associated with the maximum girder stress. Array indices are [HaulingSlope][GirderFace]
         Corner MaxDirectStressCorner[2][2];             ///< corner where the maximum girder stress occurs. Array indices are [HaulingSlope][GirderFace]

         Float64 fMin[2][2];    ///< min stress. Array indices are [HaulingSlope][GirderFace]
         ImpactDirection MinStressImpactDirection[2][2];    ///< impact direction associated with the minimum girder stress. Array indices are [HaulingSlope][GirderFace]
         WindDirection MinStressWindDirection[2][2];      ///< wind direction associated with the minimum girder stress. Array indices are [HaulingSlope][GirderFace]
         Corner MinStressCorner[2][2];             ///< corner where the minimum girder stress occurs. Array indices are [HaulingSlope][GirderFace]

         Float64 fMax[2][2];    ///< max stress. Array indices are [HaulingSlope][GirderFace]
         ImpactDirection MaxStressImpactDirection[2][2];    ///< impact direction associated with the maximum girder stress. Array indices are [HaulingSlope][GirderFace]
         WindDirection MaxStressWindDirection[2][2];      ///< wind direction associated with the maximum girder stress. Array indices are [HaulingSlope][GirderFace]
         Corner MaxStressCorner[2][2];             ///< corner where the maximum girder stress occurs. Array indices are [HaulingSlope][GirderFace]

         Float64 Mcr[2][3][2][4];        ///< cracking moment. Array indices are [HaulingSlope][ImpactDirection][WindDirection][+corner]
         Float64 ThetaCrack[2][3][2][4]; ///< rotation angle causing cracking. Array indices are [HaulingSlope][ImpactDirection][WindDirection][+corner]
         Float64 FScr[2][3][2][4]; ///< factor of safety against cracking. Array indices are [HaulingSlope][ImpactDirection][WindDirection][+corner]

         std::array<Float64, 2> FScrMin; ///< controlling FScr. The least of all FScr[HaulingSlope][ImpactDirection][WindDirection][+corner]. Array indices are [HaulingSlope]
         std::array<ImpactDirection, 2> FScrImpactDirection; ///< impact direction for FScrMin. Array indices are [HaulingSlope]
         std::array<WindDirection, 2> FScrWindDirection; ///< wind direction for FScrMin. Array indices are [HaulingSlope]
         std::array<Corner, 2> FScrCorner; ///< corner for FScrMin. Array indices are [HaulingSlope]

#if defined REBAR_FOR_DIRECT_TENSION
         gbtAlternativeTensileStressRequirements altTensionRequirements[2][3]; ///< details of the auxiliary tension reinforcement requirements. Array indices are [HaulingSlope][ImpactDirection] 
#else
   // use if lateral loads are considered
         gbtAlternativeTensileStressRequirements altTensionRequirements[2][3][2]; ///< details of the auxiliary tension reinforcement requirements. Array indices are [HaulingSlope][ImpactDirection][WindDirection]
#endif
      };


      /// Analysis results for hauling stability analysis
      class STABILITYCLASS HaulingResults : public Results
      {
      public:
         HaulingResults();

         GirderSide AssumedTiltDirection; ///< Direction in which girder is assumed to tilt

         bool bRotationalStability[2][3][2]; ///< if true, the girder is not stable for hauling... it will just roll over (Ktheta is too small so ThetaEq is too big). Array indices are [HaulingSlope][ImpactDirection][WindDirection]

         bool HasRotationalStablity() const; ///< returns true if girder has rotational stability
         bool HasRolloverStability() const; ///< returns true if girder has rollover stability
         bool IsStable() const; ///< returns true only if all cases are stable, otherwise false

         Float64 MotWind; ///< lateral overturning moment due to wind

         Float64 Wcf;   ///< total centrifugal force (applied at Dra)
         Float64 MotCF; ///< lateral overturning moment due to centrifugal force

         Float64 ZoCF;   ///< lateral deflection of center of gravity for for centrifugal force applied laterally

         std::vector<HaulingSectionResult> vSectionResults; ///< analysis results for each analysis point in the stability problem object.

         Float64 ThetaEq[2][3][2]; ///< roll angle at equilibrium. Array indices are [HaulingSlope][ImpactDirection][WindDirection].

         std::array<Float64, 2> MaxDirectStress;                     ///< maximum stress in plumb girder (most tensile value). Array indices are [HaulingSlope].
         std::array<IndexType, 2> MaxDirectStressAnalysisPointIndex; ///< analysis point index associated with the maximum girder stress. Array indices are [HaulingSlope].
         std::array<ImpactDirection, 2> MaxDirectStressImpactDirection;    ///< impact direction associated with the maximum girder stress. Array indices are [HaulingSlope].
         std::array<Corner, 2> MaxDirectStressCorner;             ///< corner where the maximum girder stress occurs. Array indices are [HaulingSlope].

         std::array<Float64, 2> MinDirectStress;                     ///< minimum stress in plumb girder (most compressive value). Array indices are [HaulingSlope].
         std::array<IndexType, 2> MinDirectStressAnalysisPointIndex; ///< analysis point index associated with the minimum girder stress. Array indices are [HaulingSlope].
         std::array<ImpactDirection, 2> MinDirectStressImpactDirection;    ///< impact direction associated with the minimum girder stress. Array indices are [HaulingSlope].
         std::array<Corner, 2> MinDirectStressCorner;             ///< corner where the minimum girder stress occurs. Array indices are [HaulingSlope].

         std::array<Float64, 2> MaxStress; ///< maximum stress (most tensile value). Array indices are [HaulingSlope].
         std::array<IndexType, 2> MaxStressAnalysisPointIndex; ///< analysis point index associated with the maximum girder stress. Array indices are [HaulingSlope].
         std::array<ImpactDirection, 2> MaxStressImpactDirection;    ///< impact direction associated with the maximum girder stress. Array indices are [HaulingSlope].
         std::array<WindDirection, 2> MaxStressWindDirection;      ///< wind direction associated with the maximum girder stress. Array indices are [HaulingSlope].
         std::array<Corner, 2> MaxStressCorner;             ///< corner where the maximum girder stress occurs. Array indices are [HaulingSlope].

         std::array<Float64, 2> MinStress;                     ///< minimum stress (most compressive value). Array indices are [HaulingSlope].
         std::array<IndexType, 2> MinStressAnalysisPointIndex; ///< analysis point index associated with the minimum girder stress. Array indices are [HaulingSlope].
         std::array<ImpactDirection, 2> MinStressImpactDirection;    ///< impact direction associated with the minimum girder stress. Array indices are [HaulingSlope].
         std::array<WindDirection, 2> MinStressWindDirection;      ///< wind direction associated with the minimum girder stress. Array indices are [HaulingSlope].
         std::array<Corner, 2> MinStressCorner;             ///< corner where the minimum girder stress occurs. Array indices are [HaulingSlope].

         std::array<Float64, 2> MinFScr; ///< minimum factor of safety against cracking. Array indices are [HaulingSlope].
         std::array<IndexType, 2> FScrAnalysisPointIndex;  ///< analysis point index associated with the minimum factor of safety against cracking. Array indices are [HaulingSlope].
         std::array<ImpactDirection, 2> FScrImpactDirection; ///< impact direction associated with the minimum factor of safety against cracking. Array indices are [HaulingSlope].
         std::array<WindDirection, 2> FScrWindDirection;   ///< wind direction associated with the minimum factor of safety against cracking. Array indices are [HaulingSlope].
         std::array<Corner, 2> FScrCorner; ///< corner associated with the minimum factor of safety against cracking. Array indices are [HaulingSlope].

         Float64 ThetaMax[2][3][2];    ///< maximum tilt angle of the cracked section. Array indices are [HaulingSlope][ImpactDirection][WindDirection].
         Float64 FsFailure[2][3][2];   ///< factor of safety against failure. Array indices are [HaulingSlope][ImpactDirection][WindDirection].
         Float64 AdjFsFailure[2][3][2]; ///< adjusted FS against failure (if FSfailure < FScr then FSfailure = FScr). Array indices are [HaulingSlope][ImpactDirection][WindDirection].
         std::array<ImpactDirection, 2> FSfImpactDirection; ///< impact direction associated with the minimum factor of safety against failure. Array indices are [HaulingSlope].
         std::array<WindDirection, 2> FSfWindDirection;   ///< wind direction associated with the minimum factor of safety against failure. Array indices are [HaulingSlope].
         std::array<Float64, 2> MinFsFailure; ///< minimum factor of safety against failure. Array indices are [HaulingSlope].
         std::array<Float64, 2> MinAdjFsFailure; ///< corresponding adjusted minimum factor of safety against failure. Array indices are [HaulingSlope].

         bool bRolloverStability[2][3][2]; ///< there is a rollover instability. Array indices are [HaulingSlope][ImpactDirection][WindDirection].
         Float64 ThetaRollover[2][3][2]; ///< minimum tilt angle that causes roll over (> 0 girder tilts CCW, < 0 girder tilts CW. Array indices are [HaulingSlope][ImpactDirection][WindDirection].
         Float64 FsRollover[2][3][2];    ///< factor of safety against roll over. Array indices are [HaulingSlope][ImpactDirection][WindDirection].
         std::array<ImpactDirection, 2> FSroImpactDirection;  ///< impact direction direction associated with the minimum factor of safety against rollover. Array indices are [HaulingSlope].
         std::array<WindDirection, 2> FSroWindDirection;    ///< wind direction direction associated with the minimum factor of safety against rollover. Array indices are [HaulingSlope].
         std::array<Float64, 2> MinFsRollover;          ///< minimum factor of safety against roll over. Array indices are [HaulingSlope].
      };
   }
}