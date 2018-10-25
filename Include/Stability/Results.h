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

/*****************************************************************************
CLASS 
   stbResults

DESCRIPTION
   Encapsulates the analysis results


COPYRIGHT
   Copyright © 1997-2016
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

#define TOP    0
#define BOTTOM 1

#define TOP_LEFT     0
#define TOP_RIGHT    1
#define BOTTOM_LEFT  2
#define BOTTOM_RIGHT 3

#define IMPACT_NONE 0
#define IMPACT_UP   1
#define IMPACT_DOWN 2

class STABILITYCLASS stbResults
{
public:
   stbResults();

   Float64 Ls; // span length between supports

   Float64 Yr;  // location from the center of gravity from the roll axis in girder section coordinates (positive means roll center is above CG)
   Float64 Dra[3]; // distance from the center of gravity to the roll axis, adjusted for camber

   Float64 OffsetFactor; // cg offset factor
   Float64 CamberOffsetFactor; // factor used to multiple with Yr to adjust for camber (this is the Bob Mast "increase by 2% to account for camber") method
   Float64 LateralSweep; // lateral sweep due to imperfections (SweepTolerance*Lg + SupportOffset)
   Float64 EccLateralSweep[3]; // eccentricty of CG due to lateral sweep (OffsetFactor*LateralSweep + SupportPlacementTolerance)*emag[impact]

   Float64 Ywind[3];   // distance between roll center and resultant wind force (mid-height of girder) (array index is IMPACT_xxx)
   Float64 EccWind[3]; // Vertical eccentricty of the girder self-weight load with respect to the roll axis (array index is IMPACT_xxx)
   Float64 Wwind;   // total wind force (applied at EccWind)
   Float64 MotWind; // lateral overturning moment due to wind
   Float64 MroWind; // lateral roll over moemnt due to wind

   Float64 Wcf;   // total centrifugal force (applied at Dra)
   Float64 MotCF; // lateral overturning moment due to centrifugal force
   Float64 MroCF; // lateral roll over moemnt due to centrifugal force

   Float64 Zo[3];  // lateral deflection of center of gravity for full dead load applied laterally (array index is IMPACT_xxx)
   Float64 ZoWind[3]; // lateral deflection of center of gravity for full wind applied laterally
   Float64 ZoCF;   // lateral deflection of center of gravity for for centrifugal force applied laterally
};
