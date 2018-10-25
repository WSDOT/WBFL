///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2016  Washington State Department of Transportation
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


COPYRIGHT
   Copyright © 1997-2016
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class STABILITYCLASS stbHaulingSectionResult
{
public:
   Float64 X;   // location of section
   Float64 Mg;  // moment due to girder weight
   Float64 Mw;  // transverse moment due to wind
   Float64 Mcf; // transverse moment due to CF

   Float64 fps[2];   // top/bottom stress due to prestressing
   Float64 fg[2];    // top/bottom stress due to girder weight without impact
   Float64 fw[4];    // corner stresses due to wind towards the left
   Float64 fcf[4];   // corner stresses due to CF towards the left

   // Array indicies are [IMPACT_xxx][wind direction LEFT/RIGHT][CF direction LEFT/RIGHT][corner TOP_LEFT,TOP_RIGHT,BOTTOM_LEFT,BOTTOM_RIGHT]
   Float64 fDirect[3][2][2][4]; // stress due to direct loads (girder self weight, wind, CF, and ps)
   Float64 fTilt[3][2][2][4];   // stress due to equilibrium rotation of girder caused by girder self weight
   Float64 f[3][2][2][4];       // stress at a corner (fDirect + fTilt)
   Float64 Mcr[3][2][2];        // cracking moment
   int     CrackedFlange[3][2][2]; // indicates the flange and corner that is cracked (TOP_LEFT, etc)
   Float64 ThetaCrack[3][2][2]; // rotation angle causing cracking

   Float64 FScr[3][2][2]; // factor of safety against cracking
};


/*****************************************************************************
CLASS 
   stbHaulingResults

DESCRIPTION
   Encapsulates the analysis results for hauling stability analysis


COPYRIGHT
   Copyright © 1997-2016
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class STABILITYCLASS stbHaulingResults : public stbResults
{
public:
   stbHaulingResults();

   std::vector<stbHaulingSectionResult> vSectionResults; // analysis results for each analysis point in the stability problem object

   Float64 ThetaEq[3][2][2];    // roll angle at equilibrium

   Float64 MaxDirectStress;                     // maximum stress in plumb girder(most tensile value)
   IndexType MaxDirectStressAnalysisPointIndex; // analysis poiint index associated with the maximum girder stress
   IndexType MaxDirectStressImpactDirection;    // impact direction associated with the maximum girder stress
   IndexType MaxDirectStressWindDirection;      // wind direction associated with the maximum girder stress
   IndexType MaxDirectStressCFDirection;        // centrifugal force direction associated with the maximum girder stress
   IndexType MaxDirectStressCorner;             // corner where the maximum girder stress occurs

   Float64 MinDirectStress;                     // minimum stress in plumb girder (most compressive value)
   IndexType MinDirectStressAnalysisPointIndex; // analysis poiint index associated with the minimum girder stress
   IndexType MinDirectStressImpactDirection;    // impact direction associated with the minimum girder stress
   IndexType MinDirectStressWindDirection;      // wind direction associated with the minimum girder stress
   IndexType MinDirectStressCFDirection;        // centrifugal force direction associated with the minimum girder stress
   IndexType MinDirectStressCorner;             // corner where the minimum girder stress occurs

   Float64 MaxStress;                     // maximum stress (most tensile value)
   IndexType MaxStressAnalysisPointIndex; // analysis poiint index associated with the maximum girder stress
   IndexType MaxStressImpactDirection;    // impact direction associated with the maximum girder stress
   IndexType MaxStressWindDirection;      // wind direction associated with the maximum girder stress
   IndexType MaxStressCFDirection;        // centrifugal force direction associated with the maximum girder stress
   IndexType MaxStressCorner;             // corner where the maximum girder stress occurs

   Float64 MinStress;                     // minimum stress (most compressive value)
   IndexType MinStressAnalysisPointIndex; // analysis poiint index associated with the minimum girder stress
   IndexType MinStressImpactDirection;    // impact direction associated with the minimum girder stress
   IndexType MinStressWindDirection;      // wind direction associated with the minimum girder stress
   IndexType MinStressCFDirection;        // centrifugal force direction associated with the minimum girder stress
   IndexType MinStressCorner;             // corner where the minimum girder stress occurs

   Float64 MinFScr;               // minimum factor of safety against cracking
   IndexType FScrAnalysisPointIndex;  // analysis point index associated with the minimum factor of safety against cracking
   IndexType FScrImpactDirection; // impact direction associated with the minimum factor of safety against cracking
   IndexType FScrWindDirection;   // wind direction associated with the minimum factor of safety against cracking
   IndexType FScrCFDirection;     // centrifugal direction associated with the minimum factor of safety against cracking

   // Array indicies [IMPACT_xxx][wind direction, LEFT/RIGHT][centrifugal force direction, LEFT/RIGHT]
   Float64 ThetaMax[3][2][2];    // maximum tilt angle of the cracked section
   Float64 FsFailure[3][2][2];   // factor of safety against failure
   IndexType FSfImpactDirection; // impact direction associated with the minimum factor of safety against failure
   IndexType FSfWindDirection;   // wind direction associated with the minimum factor of safety against failure
   IndexType FSfCFDirection;     // centrifugal force direction associated with the minimum factor of safety against failure
   Float64 MinFsFailure;         // minimum factor of safety against failure

   Float64 ThetaRollover[3][2][2]; // tilt angle that causes roll over
   Float64 FsRollover[3][2][2];    // factor of safety against roll over
   IndexType FSroImpactDirection;  // impact direction direction associated with the minimum factor of safety against rollover
   IndexType FSroWindDirection;    // wind direction direction associated with the minimum factor of safety against rollover
   IndexType FSroCFDirection;      // centrifugal force direction associated with the minimum factor of safety against rollover
   Float64 MinFsRollover;          // minimum factor of safety agains roll over
};
