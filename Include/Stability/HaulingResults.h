///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2018  Washington State Department of Transportation
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

/*****************************************************************************
CLASS 
   stbHaulingSectionResults

DESCRIPTION
   Encapsulates the hauling analysis results at a section
*****************************************************************************/

class STABILITYCLASS stbHaulingSectionResult
{
public:
   stbHaulingSectionResult();

   IndexType AnalysisPointIndex; // index of the analysis point for these results

   Float64 Mg;  // moment due to girder weight
   Float64 Mw;  // transverse moment due to wind
   Float64 Mcf; // transverse moment due to CF

   Float64 fps[2];   // top/bottom stress due to prestressing
   Float64 fg[2];    // top/bottom stress due to girder weight without impact
   Float64 fw[4];    // corner stresses due to wind towards the left
   Float64 fcf[4];   // corner stresses due to CF towards the left

   // Array indicies are [HaulingSlope enum][ImpactDirection enum][Direction enum (Wind)][Corner enum]
   Float64 fDirect[2][3][2][4]; // stress due to direct loads (girder self weight, wind, CF, and ps)
   Float64 fTilt[2][3][2][4];   // stress due to equilibrium rotation of girder caused by girder self weight
   Float64 f[2][3][2][4];       // stress at a corner (fDirect + fTilt)

   // Array indicies are [HaulingSlope enum][Face enum]
   Float64 fMinDirect[2][2];    // min stress
   stbTypes::ImpactDirection MinDirectStressImpactDirection[2][2];    // impact direction associated with the minimum girder stress
   stbTypes::WindDirection MinDirectStressWindDirection[2][2];      // wind direction associated with the minimum girder stress
   stbTypes::Corner MinDirectStressCorner[2][2];             // corner where the minimum girder stress occurs

   Float64 fMaxDirect[2][2];    // max stress
   stbTypes::ImpactDirection MaxDirectStressImpactDirection[2][2];    // impact direction associated with the maximum girder stress
   stbTypes::WindDirection MaxDirectStressWindDirection[2][2];      // wind direction associated with the maximum girder stress
   stbTypes::Corner MaxDirectStressCorner[2][2];             // corner where the maximum girder stress occurs

   Float64 fMin[2][2];    // min stress
   stbTypes::ImpactDirection MinStressImpactDirection[2][2];    // impact direction associated with the minimum girder stress
   stbTypes::WindDirection MinStressWindDirection[2][2];      // wind direction associated with the minimum girder stress
   stbTypes::Corner MinStressCorner[2][2];             // corner where the minimum girder stress occurs

   Float64 fMax[2][2];    // max stress
   stbTypes::ImpactDirection MaxStressImpactDirection[2][2];    // impact direction associated with the maximum girder stress
   stbTypes::WindDirection MaxStressWindDirection[2][2];      // wind direction associated with the maximum girder stress
   stbTypes::Corner MaxStressCorner[2][2];             // corner where the maximum girder stress occurs

   // Array indicies are [HaulingSlope enum][ImpactDirection enum][Direction enum (Wind)][Corner enum]
   Float64 Mcr[2][3][2][4];        // cracking moment
   Float64 ThetaCrack[2][3][2][4]; // rotation angle causing cracking

   // Array indices are [HaulingSlope num][ImpactDirection enum][Direction enum (Wind)]
   stbTypes::Corner CrackedFlange[2][3][2]; // indicates the flange and corner that is cracked (TOP_LEFT, etc)
   Float64 FScr[2][3][2]; // factor of safety against cracking

   // Array indicies are [HaulingSlope enum]
   Float64 FScrMin[2];
   stbTypes::ImpactDirection FScrImpactDirection[2];
   stbTypes::WindDirection FScrWindDirection[2];
   stbTypes::Corner FScrCorner[2];

   // Array indicies are [HaulingSlope enum][Impact][Wind Direction]
   bool bSectionHasRebar[2][3][2]; // true if there is sufficient bonded reinforcement at this section to use the higher allowable tension limit
   Float64 Yna[2][3][2];
   Float64 NAslope[2][3][2];
   Float64 AreaTension[2][3][2];
   Float64 T[2][3][2];
   Float64 AsProvided[2][3][2];
   Float64 AsRequired[2][3][2];
};


/*****************************************************************************
CLASS 
   stbHaulingResults

DESCRIPTION
   Encapsulates the analysis results for hauling stability analysis
*****************************************************************************/

class STABILITYCLASS stbHaulingResults : public stbResults
{
public:
   stbHaulingResults();

   Float64 MotWind; // lateral overturning moment due to wind
   Float64 MroWind; // lateral roll over moemnt due to wind

   Float64 Wcf;   // total centrifugal force (applied at Dra)
   Float64 MotCF; // lateral overturning moment due to centrifugal force
   Float64 MroCF; // lateral roll over moemnt due to centrifugal force

   Float64 ZoCF;   // lateral deflection of center of gravity for for centrifugal force applied laterally

   std::vector<stbHaulingSectionResult> vSectionResults; // analysis results for each analysis point in the stability problem object

   // Array indicies are [HaulingSlope enum][Impact][Wind]
   Float64 ThetaEq[2][3][2];    // roll angle at equilibrium (slope, impact, wind]

   // Array indicies are [HaulingSlope enum]
   Float64 MaxDirectStress[2];                     // maximum stress in plumb girder(most tensile value)
   IndexType MaxDirectStressAnalysisPointIndex[2]; // analysis poiint index associated with the maximum girder stress
   stbTypes::ImpactDirection MaxDirectStressImpactDirection[2];    // impact direction associated with the maximum girder stress
   stbTypes::WindDirection MaxDirectStressWindDirection[2];      // wind direction associated with the maximum girder stress
   stbTypes::Corner MaxDirectStressCorner[2];             // corner where the maximum girder stress occurs

   Float64 MinDirectStress[2];                     // minimum stress in plumb girder (most compressive value)
   IndexType MinDirectStressAnalysisPointIndex[2]; // analysis poiint index associated with the minimum girder stress
   stbTypes::ImpactDirection MinDirectStressImpactDirection[2];    // impact direction associated with the minimum girder stress
   stbTypes::WindDirection MinDirectStressWindDirection[2];      // wind direction associated with the minimum girder stress
   stbTypes::Corner MinDirectStressCorner[2];             // corner where the minimum girder stress occurs

   Float64 MaxStress[2];                     // maximum stress (most tensile value)
   IndexType MaxStressAnalysisPointIndex[2]; // analysis poiint index associated with the maximum girder stress
   stbTypes::ImpactDirection MaxStressImpactDirection[2];    // impact direction associated with the maximum girder stress
   stbTypes::WindDirection MaxStressWindDirection[2];      // wind direction associated with the maximum girder stress
   stbTypes::Corner MaxStressCorner[2];             // corner where the maximum girder stress occurs

   Float64 MinStress[2];                     // minimum stress (most compressive value)
   IndexType MinStressAnalysisPointIndex[2]; // analysis poiint index associated with the minimum girder stress
   stbTypes::ImpactDirection MinStressImpactDirection[2];    // impact direction associated with the minimum girder stress
   stbTypes::WindDirection MinStressWindDirection[2];      // wind direction associated with the minimum girder stress
   stbTypes::Corner MinStressCorner[2];             // corner where the minimum girder stress occurs

   Float64 MinFScr[2];               // minimum factor of safety against cracking
   IndexType FScrAnalysisPointIndex[2];  // analysis point index associated with the minimum factor of safety against cracking
   stbTypes::ImpactDirection FScrImpactDirection[2]; // impact direction associated with the minimum factor of safety against cracking
   stbTypes::WindDirection FScrWindDirection[2];   // wind direction associated with the minimum factor of safety against cracking

   // Array indicies [HaulingSlope enum][ImpactDirection enum][Side Enum (wind)]
   Float64 ThetaMax[2][3][2];    // maximum tilt angle of the cracked section
   Float64 FsFailure[2][3][2];   // factor of safety against failure
   Float64 AdjFsFailure[2][3][2];// adjusted FS against failure (if FSfailure < FScr then FSfailure = FScr)
   stbTypes::ImpactDirection FSfImpactDirection[2]; // impact direction associated with the minimum factor of safety against failure
   stbTypes::WindDirection FSfWindDirection[2];   // wind direction associated with the minimum factor of safety against failure
   Float64 MinFsFailure[2];         // minimum factor of safety against failure
   Float64 MinAdjFsFailure[2];      // corrosponding adjusted minimum factor of safety against failure

   Float64 ThetaRollover[2][3][2]; // tilt angle that causes roll over
   Float64 FsRollover[2][3][2];    // factor of safety against roll over
   stbTypes::ImpactDirection FSroImpactDirection[2];  // impact direction direction associated with the minimum factor of safety against rollover
   stbTypes::WindDirection FSroWindDirection[2];    // wind direction direction associated with the minimum factor of safety against rollover
   Float64 MinFsRollover[2];          // minimum factor of safety agains roll over
};
