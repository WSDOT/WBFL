///////////////////////////////////////////////////////////////////////
// Stability
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

#pragma once

#include <Stability\StabilityExp.h>
#include <Stability\Results.h>
#include <WBFLGenericBridgeTools\AlternativeTensileStressCalculator.h>
#include <array>

namespace WBFL
{
   namespace Stability
   {

      /// One end seated analysis results at a section
      class STABILITYCLASS OneEndSeatedSectionResult
      {
      public:
         OneEndSeatedSectionResult();

         IndexType AnalysisPointIndex; ///< index of the analysis point for these results

         Float64 Mg;  ///< moment due to girder weight
         Float64 Mw;  ///< transverse moment due to wind
         Float64 Mcf; ///< transverse moment due to CF

         std::array<Float64, 4> fps;   ///< corner stresses due to prestressing (array indices are [+corner])
         std::array<Float64, 4> fg;    ///< corner stresses due to girder weight without impact (array indices are [+corner])
         std::array<Float64, 4> fw;    ///< corner stresses due to wind towards the left (array indices are [+corner])
         std::array<Float64, 4> fcf;   ///< corner stresses due to centrifugal towards the left (array indices are [+corner])

         Float64 fDirect[3][4]; ///< stress due to direct loads (girder self weight and ps). Array indices are [ImpactDirection][+corner]

         Float64 fTilt[3][2][4];   ///< stress due to equilibrium rotation of girder caused by girder self weight. Array indices are [ImpactDirection][WindDirection][+corner]
         Float64 f[3][2][4];       ///< stress at a corner (fDirect + fTilt + fWind + fCF). Array indices are [ImpactDirection][WindDirection][+corner]

         Float64 fMinDirect[2];    ///< min direct stress. Array indices are [GirderFace]
         ImpactDirection MinDirectStressImpactDirection[2];    ///< impact direction associated with the minimum girder stress. Array indices are [GirderFace]
         Corner MinDirectStressCorner[2];             ///< corner where the minimum girder stress occurs. Array indices are [GirderFace]

         Float64 fMaxDirect[2];    ///< max direction stress. Array indices are [GirderFace]
         ImpactDirection MaxDirectStressImpactDirection[2];    ///< impact direction associated with the maximum girder stress. Array indices are [GirderFace]
         Corner MaxDirectStressCorner[2];             ///< corner where the maximum girder stress occurs. Array indices are [GirderFace]

         Float64 fMin[2];    ///< min stress. Array indices are [GirderFace]
         ImpactDirection MinStressImpactDirection[2];    ///< impact direction associated with the minimum girder stress. Array indices are [GirderFace]
         WindDirection MinStressWindDirection[2];      ///< wind direction associated with the minimum girder stress. Array indices are [GirderFace]
         Corner MinStressCorner[2];             ///< corner where the minimum girder stress occurs. Array indices are [GirderFace]

         Float64 fMax[2];    ///< max stress. Array indices are [GirderFace]
         ImpactDirection MaxStressImpactDirection[2];    ///< impact direction associated with the maximum girder stress. Array indices are [GirderFace]
         WindDirection MaxStressWindDirection[2];      ///< wind direction associated with the maximum girder stress. Array indices are [GirderFace]
         Corner MaxStressCorner[2];             ///< corner where the maximum girder stress occurs. Array indices are [GirderFace]

         Float64 Mcr[3][2][4];        ///< cracking moment. Array indices are [ImpactDirection][WindDirection][+corner]
         Float64 ThetaCrack[3][2][4]; ///< rotation angle causing cracking. Array indices are [ImpactDirection][WindDirection][+corner]
         Float64 FScr[3][2][4]; ///< factor of safety against cracking. Array indices are [ImpactDirection][WindDirection][+corner]

         Float64 FScrMin; ///< controlling FScr. The least of all FScr[ImpactDirection][WindDirection][+corner].
         ImpactDirection FScrImpactDirection; ///< impact direction for FScrMin.
         WindDirection FScrWindDirection; ///< wind direction for FScrMin.
         Corner FScrCorner; ///< corner for FScrMin.

#if defined REBAR_FOR_DIRECT_TENSION
         gbtAlternativeTensileStressRequirements altTensionRequirements[3]; ///< details of the auxiliary tension reinforcement requirements. Array indices are [ImpactDirection] 
#else
   // use if lateral loads are considered
         gbtAlternativeTensileStressRequirements altTensionRequirements[3][2]; ///< details of the auxiliary tension reinforcement requirements. Array indices are [ImpactDirection][WindDirection]
#endif
      };


      /// Analysis results for one-end seated stability analysis
      class STABILITYCLASS OneEndSeatedResults : public Results
      {
      public:
         OneEndSeatedResults();

         GirderSide AssumedTiltDirection; ///< Direction in which girder is assumed to tilt

         bool bRotationalStability[3][2]; ///< if true, the girder is not stable for hauling... it will just roll over (Ktheta is too small so ThetaEq is too big). Array indices are [ImpactDirection][WindDirection]

         bool HasRotationalStablity() const; ///< returns true if girder has rotational stability
         bool HasRolloverStability() const; ///< returns true if girder has rollover stability
         bool IsStable() const; ///< returns true only if all cases are stable, otherwise false

         Float64 MotWind; ///< lateral overturning moment due to wind

         std::vector<OneEndSeatedSectionResult> vSectionResults; ///< analysis results for each analysis point in the stability problem object.

         Float64 ThetaEq[3][2]; ///< roll angle at equilibrium. Array indices are [ImpactDirection][WindDirection].

         Float64 MaxDirectStress;                     ///< maximum stress in plumb girder (most tensile value).
         IndexType MaxDirectStressAnalysisPointIndex; ///< analysis point index associated with the maximum girder stress.
         ImpactDirection MaxDirectStressImpactDirection;    ///< impact direction associated with the maximum girder stress.
         Corner MaxDirectStressCorner;             ///< corner where the maximum girder stress occurs.

         Float64 MinDirectStress;                     ///< minimum stress in plumb girder (most compressive value).
         IndexType MinDirectStressAnalysisPointIndex; ///< analysis point index associated with the minimum girder stress.
         ImpactDirection MinDirectStressImpactDirection;    ///< impact direction associated with the minimum girder stress.
         Corner MinDirectStressCorner;             ///< corner where the minimum girder stress occurs.

         Float64 MaxStress; ///< maximum stress (most tensile value).
         IndexType MaxStressAnalysisPointIndex; ///< analysis point index associated with the maximum girder stress.
         ImpactDirection MaxStressImpactDirection;    ///< impact direction associated with the maximum girder stress.
         WindDirection MaxStressWindDirection;      ///< wind direction associated with the maximum girder stress.
         Corner MaxStressCorner;             ///< corner where the maximum girder stress occurs.

         Float64 MinStress;                     ///< minimum stress (most compressive value).
         IndexType MinStressAnalysisPointIndex; ///< analysis point index associated with the minimum girder stress.
         ImpactDirection MinStressImpactDirection;    ///< impact direction associated with the minimum girder stress.
         WindDirection MinStressWindDirection;      ///< wind direction associated with the minimum girder stress.
         Corner MinStressCorner;             ///< corner where the minimum girder stress occurs.

         Float64 MinFScr; ///< minimum factor of safety against cracking.
         IndexType FScrAnalysisPointIndex;  ///< analysis point index associated with the minimum factor of safety against cracking.
         ImpactDirection FScrImpactDirection; ///< impact direction associated with the minimum factor of safety against cracking.
         WindDirection FScrWindDirection;   ///< wind direction associated with the minimum factor of safety against cracking.
         Corner  FScrCorner; ///< corner associated with the minimum factor of safety against cracking.

         Float64 ThetaMax[3][2];    ///< maximum tilt angle of the cracked section. Array indices are [ImpactDirection][WindDirection].
         Float64 FsFailure[3][2];   ///< factor of safety against failure. Array indices are [ImpactDirection][WindDirection].
         Float64 AdjFsFailure[3][2]; ///< adjusted FS against failure (if FSfailure < FScr then FSfailure = FScr). Array indices are [ImpactDirection][WindDirection].
         ImpactDirection FSfImpactDirection; ///< impact direction associated with the minimum factor of safety against failure.
         WindDirection FSfWindDirection;   ///< wind direction associated with the minimum factor of safety against failure.
         Float64 MinFsFailure; ///< minimum factor of safety against failure.
         Float64 MinAdjFsFailure; ///< corresponding adjusted minimum factor of safety against failure.

         bool bRolloverStability[3][2]; ///< there is a rollover instability. Array indices are [ImpactDirection][WindDirection].
         Float64 ThetaRollover[3][2]; ///< minimum tilt angle that causes roll over (> 0 girder tilts CCW, < 0 girder tilts CW. Array indices are [ImpactDirection][WindDirection].
         Float64 FsRollover[3][2];    ///< factor of safety against roll over. Array indices are [ImpactDirection][WindDirection].
         ImpactDirection FSroImpactDirection;  ///< impact direction direction associated with the minimum factor of safety against rollover.
         WindDirection FSroWindDirection;    ///< wind direction direction associated with the minimum factor of safety against rollover.
         Float64 MinFsRollover;          ///< minimum factor of safety against roll over.
      };
   }
}