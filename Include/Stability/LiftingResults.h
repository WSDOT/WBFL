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
#include <WBFLGenericBridgeTools\AlternativeTensileStressCalculator.h>

/*****************************************************************************
CLASS 
   stbLiftingSectionResults

DESCRIPTION
   Encapsulates the lifting analysis results at a section
*****************************************************************************/

class STABILITYCLASS stbLiftingSectionResult
{
public:
   stbLiftingSectionResult();

   IndexType AnalysisPointIndex; // index of the analysis point for these results

   Float64 Mg;  // moment due to girder weight
   Float64 Mw;  // transverse moment due to wind

   // array index is stbTypes::Corner
   Float64 fps[4]; // stress due to prestressing
   Float64 fcable[4]; // stress due to inclined lift cable without impact
   Float64 fg[4]; // stress due to girder weight without impact
   Float64 fw[4]; // stress due to wind towards the left (multiply by -1 to get stress due to wind towards the right)

   // Array indicies are [ImpactDirection enum][Side enum (wind)][Corner enum]
   Float64 fDirect[3][2][4]; // stress due to direct loads (girder self weight, wind, CF, and ps)
   Float64 fTilt[3][2][4];   // stress due to equilibrium rotation of girder caused by girder self weight
   Float64 f[3][2][4];       // stress at a corner (fDirect + fTilt)

   Float64 fMinDirect[2];    // min stress
   stbTypes::ImpactDirection MinDirectStressImpactDirection[2];    // impact direction associated with the minimum girder stress
   stbTypes::WindDirection MinDirectStressWindDirection[2];      // wind direction associated with the minimum girder stress
   stbTypes::Corner MinDirectStressCorner[2];      // corner where the minimum direct girder stress occurs

   Float64 fMaxDirect[2];    // max stress
   stbTypes::ImpactDirection MaxDirectStressImpactDirection[2];    // impact direction associated with the maximum girder stress
   stbTypes::WindDirection MaxDirectStressWindDirection[2];      // wind direction associated with the maximum girder stress
   stbTypes::Corner MaxDirectStressCorner[2];      // corner where the maximum direct girder stress occurs

   Float64 fMin[2];    // min stress
   stbTypes::ImpactDirection MinStressImpactDirection[2];    // impact direction associated with the minimum girder stress
   stbTypes::WindDirection MinStressWindDirection[2];      // wind direction associated with the minimum girder stress
   stbTypes::Corner MinStressCorner[2];             // corner where the minimum girder stress occurs

   Float64 fMax[2];    // max stress
   stbTypes::ImpactDirection MaxStressImpactDirection[2];    // impact direction associated with the maximum girder stress
   stbTypes::WindDirection MaxStressWindDirection[2];      // wind direction associated with the maximum girder stress
   stbTypes::Corner MaxStressCorner[2];             // corner where the maximum girder stress occurs

   // FScr computation values at each corner for each impact and wind
   Float64 Mcr[3][2][4];        // cracking moment
   Float64 ThetaCrack[3][2][4]; // rotation angle causing cracking
   Float64 FScr[3][2][4]; // factor of safety against cracking
   
   // Governing FScr and corner where it occurs for each impact and wind
   Float64 MinFScr[3][2]; // same as FScr[impact][wind][MinFScrCorner[impact][wind]]
   stbTypes::Corner MinFScrCorner[3][2]; // corner for MinFScr

   // Governing FScr at this section for all load cases
   Float64 FScrMin;
   stbTypes::ImpactDirection FScrMinImpactDirection;
   stbTypes::WindDirection FScrMinWindDirection;
   stbTypes::Corner FScrMinCorner;

   // parameters related to laterial moment due to axial force of inclined cables
   Float64 OffsetFactor; // cg offset factor at this section
   Float64 eh[3][2]; // eccentricity of axial force of inclined cables from roll axis at this location
   Float64 Mh[3][2]; // lateral moment due to axial force of inclined cables

   gbtAlternativeTensileStressRequirements altTensionRequirements[3][2];
};

/*****************************************************************************
CLASS 
   stbLiftingResults

DESCRIPTION
   Encapsulates the analysis results for lifting stability analysis
*****************************************************************************/

class STABILITYCLASS stbLiftingResults : public stbResults
{
public:
   stbLiftingResults();

   bool bIsStable[3][2]; // if false, the girder is not stable for lifting... it will just roll over. 
                      // if the girder is not stable, the analysis results below are not valid
                      // (array index in one of the stbTypes::Impact enum values)

   Float64 Pcrit; // critical compression load
   Float64 Plift; // axial force due to inclination of lift cables for the no-impact case
   Float64 dLift; // deflection due to lifting cable force for the no-impact case
   Float64 emag[3];  // lateral deflection magnification factor (array index in one of the stbTypes::Impact enum values)

   Float64 ThetaEq[3][2];    // tilt angle at equilibrium (array index is [impact][wind])

   std::vector<stbLiftingSectionResult> vSectionResults; // analysis results for each analysis point in the stability problem object

   Float64 MaxDirectStress;                     // maximum stress (most tensile value)
   IndexType MaxDirectStressAnalysisPointIndex; // analysis poiint index associated with the maximum girder stress
   stbTypes::ImpactDirection MaxDirectStressImpactDirection;    // impact direction associated with the maximum girder stress
   stbTypes::WindDirection MaxDirectStressWindDirection;      // wind direction associated with the maximum girder stress
   stbTypes::Corner MaxDirectStressCorner;             // corner where the maximum girder stress occurs

   Float64 MinDirectStress;                     // minimum stress (most compressive value)
   IndexType MinDirectStressAnalysisPointIndex; // analysis poiint index associated with the minimum girder stress
   stbTypes::ImpactDirection MinDirectStressImpactDirection;    // impact direction associated with the minimum girder stress
   stbTypes::WindDirection MinDirectStressWindDirection;      // wind direction associated with the minimum girder stress
   stbTypes::Corner MinDirectStressCorner;             // corner where the minimum girder stress occurs

   Float64 MaxStress;                     // maximum stress (most tensile value)
   IndexType MaxStressAnalysisPointIndex; // analysis poiint index associated with the maximum girder stress
   stbTypes::ImpactDirection MaxStressImpactDirection;    // impact direction associated with the maximum girder stress
   stbTypes::WindDirection MaxStressWindDirection;      // wind direction associated with the maximum girder stress
   stbTypes::Corner MaxStressCorner;             // corner where the maximum girder stress occurs

   Float64 MinStress;                     // minimum stress (most compressive value)
   IndexType MinStressAnalysisPointIndex; // analysis poiint index associated with the minimum girder stress
   stbTypes::ImpactDirection MinStressImpactDirection;    // impact direction associated with the minimum girder stress
   stbTypes::WindDirection MinStressWindDirection;      // wind direction associated with the minimum girder stress
   stbTypes::Corner MinStressCorner;             // corner where the minimum girder stress occurs

   // controlling FScr for a load case [impact][wind]
   Float64 MinFScr[3][2];                  // minimum factor of safety against cracking
   IndexType FScrAnalysisPointIndex[3][2]; // analysis point index associated with the minimum factor of safety against cracking
   stbTypes::Corner FScrCorner[3][2];             // corner associated with the minimum factor of safety against cracking

   // overall controlling FScr
   Float64 FScrMin;                  // minimum factor of safety against cracking
   IndexType FScrMinAnalysisPointIndex; // analysis point index associated with the minimum factor of safety against cracking
   stbTypes::ImpactDirection FScrMinImpactDirection;    // impact direction associated with the minimum factor of safety against cracking
   stbTypes::WindDirection FScrMinWindDirection;      // wind direction associated with the minimum factor of safety against cracking
   stbTypes::Corner FScrMinCorner;             // corner associated with the minimum factor of safety against cracking

   // Array indicies [Impact Direction][Side enum (wind direction)]
   Float64 ThetaMax[3][2];     // maximum tilt angle of the cracked section
   Float64 FsFailure[3][2];    // factor of safety against failure computed using direct equation
   Float64 AdjFsFailure[3][2]; // adjusted FS against failure (if FSfailure < FScr then FSfailure = FScr)

   Float64 MinFsFailure;         // minimum factor of safety against failure
   Float64 MinAdjFsFailure;      // corrosponding adjusted minimum factor of safety against failure
   stbTypes::ImpactDirection FSfImpactDirection; // impact direction associated with the minimum factor of safety against cracking
   stbTypes::WindDirection FSfWindDirection;   // wind direction associated with the minimum factor of safety against cracking
};
