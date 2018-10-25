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

#include <Stability\StabilityLib.h>
#include <Stability\LiftingResults.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

stbLiftingSectionResult::stbLiftingSectionResult()
{
   memset((void*)this,0,sizeof(stbLiftingSectionResult));
   bSectionHasRebar[TOP]    = false;
   bSectionHasRebar[BOTTOM] = false;
}

/////////////////////////////////////

stbLiftingResults::stbLiftingResults()
{
   bIsStable[IMPACT_NONE] = true;
   bIsStable[IMPACT_UP]   = true;
   bIsStable[IMPACT_DOWN] = true;

   Pcrit = 0;
   Plift = 0;
   memset((void*)emag,0,sizeof(emag));
   dLift = 0;

   MaxStress = 0;
   MaxStressAnalysisPointIndex = INVALID_INDEX;
   MaxStressImpactDirection    = INVALID_INDEX;
   MaxStressWindDirection      = INVALID_INDEX;
   MaxStressCorner             = INVALID_INDEX;

   MinStress = 0;
   MinStressAnalysisPointIndex = INVALID_INDEX;
   MinStressImpactDirection    = INVALID_INDEX;
   MinStressWindDirection      = INVALID_INDEX;
   MinStressCorner             = INVALID_INDEX;

   MinFScr = 0;
   FScrAnalysisPointIndex = INVALID_INDEX;
   FScrImpactDirection    = INVALID_INDEX;
   FScrWindDirection      = INVALID_INDEX;

   memset((void*)(ThetaMax),0,sizeof(ThetaMax));
   memset((void*)(FsFailure),0,sizeof(FsFailure));
   memset((void*)(AdjFsFailure),0,sizeof(AdjFsFailure));

   FSfImpactDirection = INVALID_INDEX;
   FSfWindDirection   = INVALID_INDEX;
   MinFsFailure    = 0;
   MinAdjFsFailure = 0;
}