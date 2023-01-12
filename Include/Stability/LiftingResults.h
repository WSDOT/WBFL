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
#include <WBFLGenericBridgeTools\AlternativeTensileStressCalculator.h>
#include <array>

namespace WBFL
{
   namespace Stability
   {

      /// Lifting analysis results at a section
      class STABILITYCLASS LiftingSectionResult
      {
      public:
         LiftingSectionResult();

         IndexType AnalysisPointIndex; ///< index of the analysis point for these results

         Float64 Mg;  ///< moment due to girder weight
         Float64 Mw;  ///< transverse moment due to wind

         std::array<Float64, 4> fps;   ///< corner stresses due to prestressing (array indices are [+corner])
         std::array<Float64, 4> fg;    ///< corner stresses due to girder weight without impact (array indices are [+corner])
         std::array<Float64, 4> fw;    ///< corner stresses due to wind towards the left (array indices are [+corner])
         std::array<Float64, 4> fcable; ///< corner stresses due to included lift cable without impact (array indices are [+corner])

         Float64 fDirect[3][4]; ///< stress due to direct loads (girder self weight and ps). Array indices are [ImpactDirection][+corner]

         Float64 fTilt[3][2][4];   ///< stress due to equilibrium rotation of girder caused by girder self weight. Array indices are [ImpactDirection][WindDirection][+corner]
         Float64 f[3][2][4];       ///< stress at a corner (fDirect + fTilt + fWind + fCF). Array indices are [ImpactDirection][WindDirection][+corner]

         std::array<Float64, 2> fMinDirect;    ///< min direct stress. Array indices are [GirderFace]
         std::array<ImpactDirection, 2> MinDirectStressImpactDirection;    ///< impact direction associated with the minimum girder stress. Array indices are [GirderFace]
         std::array<Corner, 2> MinDirectStressCorner;///< corner where the minimum girder stress occurs. Array indices are [GirderFace]

         std::array<Float64, 2> fMaxDirect;    ///< max direction stress. Array indices are [GirderFace]
         std::array<ImpactDirection, 2> MaxDirectStressImpactDirection;    ///< impact direction associated with the maximum girder stress. Array indices are [GirderFace]
         std::array<Corner, 2> MaxDirectStressCorner;   ///< corner where the maximum girder stress occurs. Array indices are [GirderFace]

         std::array<Float64, 2> fMin;    ///< min stress. Array indices are [GirderFace]
         std::array<ImpactDirection, 2> MinStressImpactDirection;    ///< impact direction associated with the minimum girder stress. Array indices are [GirderFace]
         std::array<WindDirection, 2> MinStressWindDirection;      ///< wind direction associated with the minimum girder stress. Array indices are [GirderFace]
         std::array<Corner, 2> MinStressCorner;             ///< corner where the minimum girder stress occurs. Array indices are [GirderFace]

         std::array<Float64, 2> fMax;    ///< max stress. Array indices are [GirderFace]
         std::array<ImpactDirection, 2> MaxStressImpactDirection;    ///< impact direction associated with the maximum girder stress. Array indices are [GirderFace]
         std::array<WindDirection, 2> MaxStressWindDirection;      ///< wind direction associated with the maximum girder stress. Array indices are [GirderFace]
         std::array<Corner, 2> MaxStressCorner;             ///< corner where the maximum girder stress occurs. Array indices are [GirderFace]

         // FScr computation values at each corner for each impact and wind
         Float64 Mcr[3][2][4];        ///< cracking moment. Array indices are [ImpactDirection][WindDirection][+corner]
         Float64 ThetaCrack[3][2][4]; ///< rotation angle causing cracking. Array indices are [ImpactDirection][WindDirection][+corner]
         Float64 FScr[3][2][4]; ///< factor of safety against cracking. Array indices are [ImpactDirection][WindDirection][+corner]

         // Governing FScr and corner where it occurs for each impact and wind
         Float64 MinFScr[3][2]; ///< same as FScr[ImpactDirection][WindDirection][MinFScrCorner[ImpactDirection][WindDirection]]. Array indices are [ImpactDirection][WindDirection].
         Corner MinFScrCorner[3][2]; ///< Corner where the governing factor of safety occurs. Array indices are [ImpactDirection][WindDirection].

         // Governing FScr at this section for all load cases
         Float64 FScrMin; ///< controlling FScr. The least of all FScr[ImpactDirection][WindDirection][+corner].
         ImpactDirection FScrMinImpactDirection; ///< impact direction for FScrMin.
         WindDirection FScrMinWindDirection; ///< wind direction for FScrMin.
         Corner FScrMinCorner; ///< corner for FScrMin. 

         // Parameters related to lateral moment due to axial force of inclined cables
         Float64 OffsetFactor; ///< CG offset factor at this section associated with lateral moment caused by inclined lift cables.
         Float64 eh[3][2]; ///< Eccentricity of axial force of inclined cables from roll axis at this location. Array indices are [ImpactDirection][WindDirection]
         Float64 Mh[3][2]; ///< Lateral moment due to axial force of inclined cables. Array indices are [ImpactDirection][WindDirection]

#if defined REBAR_FOR_DIRECT_TENSION
         std::array<gbtAlternativeTensileStressRequirements, 3> altTensionRequirements; ///< details of the auxiliary tension reinforcement requirements.
#else
         gbtAlternativeTensileStressRequirements altTensionRequirements[3][2];///< details of the auxiliary tension reinforcement requirements. Array indices are [ImpactDirection][WindDirection] 
#endif
      };

      ///  Analysis results for lifting stability analysis
      class STABILITYCLASS LiftingResults : public Results
      {
      public:
         LiftingResults();

         GirderSide AssumedTiltDirection; ///< Direction in which girder is assumed to tilt

         std::array<std::array<bool, 2>, 3> bIsStable;  ///< if true, the girder is not stable for lifting... it will just roll over. If the girder is not stable, the analysis results below are not valid. Array indices are [ImpactDirection][WindDirection]

         Float64 Pcrit; ///< critical buckling load
         Float64 Plift; ///< axial force due to inclination of lift cables for the no-impact case
         //Float64 dLift; ///< deflection due to lifting cable force for the no-impact case
         std::array<Float64, 3> emag;  ///< lateral deflection magnification factor. Array indices are [ImpactDirection].

         std::vector<LiftingSectionResult> vSectionResults; ///< analysis results for each analysis point in the stability problem object.

         std::array<std::array<Float64, 2>, 3> ThetaEq; ///< roll angle at equilibrium. Array indices are [ImpactDirection][WindDirection].

         Float64 MaxDirectStress; ///< maximum stress in plumb girder (most tensile value).
         IndexType MaxDirectStressAnalysisPointIndex; ///< analysis point index associated with the maximum girder stress.
         ImpactDirection MaxDirectStressImpactDirection; ///< impact direction associated with the maximum girder stress.
         Corner MaxDirectStressCorner; ///< corner where the maximum girder stress occurs. 

         Float64 MinDirectStress;                     ///< minimum stress in plumb girder (most compressive value). 
         IndexType MinDirectStressAnalysisPointIndex; ///< analysis point index associated with the minimum girder stress.
         ImpactDirection MinDirectStressImpactDirection; ///< impact direction associated with the minimum girder stress.
         Corner MinDirectStressCorner;             ///< corner where the minimum girder stress occurs.

         Float64 MaxStress;                    ///< maximum stress (most tensile value).
         IndexType MaxStressAnalysisPointIndex; ///< analysis point index associated with the maximum girder stress.
         ImpactDirection MaxStressImpactDirection;   ///< impact direction associated with the maximum girder stress.
         WindDirection MaxStressWindDirection;      ///< wind direction associated with the maximum girder stress.
         Corner MaxStressCorner;           ///< corner where the maximum girder stress occurs. 

         Float64 MinStress;                     ///< minimum stress (most compressive value).
         IndexType MinStressAnalysisPointIndex; ///< analysis point index associated with the minimum girder stress.
         ImpactDirection MinStressImpactDirection;    ///< impact direction associated with the minimum girder stress.
         WindDirection MinStressWindDirection;      ///< wind direction associated with the minimum girder stress.
         Corner MinStressCorner;            ///< corner where the minimum girder stress occurs.

         // controlling FScr for a load case
         std::array<std::array<Float64, 2>, 3> MinFScr;                  ///< minimum factor of safety against cracking. Array indices are [ImpactDirection][WindDirection].
         std::array<std::array<IndexType, 2>, 3> FScrAnalysisPointIndex; ///< analysis point index associated with the minimum factor of safety against cracking. Array indices are [ImpactDirection][WindDirection].
         std::array<std::array<Corner, 2>, 3> FScrCorner;   ///< corner associated with the minimum factor of safety against cracking. Array indices are [ImpactDirection][WindDirection].

         // overall controlling FScr
         Float64 FScrMin;                  ///< minimum factor of safety against cracking
         IndexType FScrMinAnalysisPointIndex; ///< analysis point index associated with the minimum factor of safety against cracking
         ImpactDirection FScrMinImpactDirection;    ///< impact direction associated with the minimum factor of safety against cracking
         WindDirection FScrMinWindDirection;      ///< wind direction associated with the minimum factor of safety against cracking
         Corner FScrMinCorner;             ///< corner associated with the minimum factor of safety against cracking

         std::array<std::array<Float64, 2>, 3> ThetaMax;     ///< maximum tilt angle of the cracked section. Array indices are [ImpactDirection][WindDirection].
         std::array<std::array<Float64, 2>, 3> FsFailure;    ///< factor of safety against failure. Array indices are [ImpactDirection][WindDirection].
         std::array<std::array<Float64, 2>, 3> AdjFsFailure; ///< adjusted FS against failure (if FSfailure < FScr then FSfailure = FScr). Array indices are [ImpactDirection][WindDirection].

         Float64 MinFsFailure;         ///< minimum factor of safety against failure
         Float64 MinAdjFsFailure;      ///< corresponding adjusted minimum factor of safety against failure
         ImpactDirection FSfImpactDirection; ///< impact direction associated with the minimum factor of safety against cracking
         WindDirection FSfWindDirection;   ///< wind direction associated with the minimum factor of safety against cracking
      };
   }
}