///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2017  Washington State Department of Transportation
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
   memset((void*)bSectionHasRebar,false,sizeof(bSectionHasRebar));

   MaxStressImpactDirection[stbTypes::Top]    = stbTypes::NoImpact;
   MaxStressWindDirection[stbTypes::Top]      = stbTypes::Left;
   MaxStressCorner[stbTypes::Top]             = stbTypes::TopLeft;

   MinStressImpactDirection[stbTypes::Top]    = stbTypes::NoImpact;
   MinStressWindDirection[stbTypes::Top]      = stbTypes::Left;
   MinStressCorner[stbTypes::Top]             = stbTypes::TopLeft;


   MaxStressImpactDirection[stbTypes::Bottom]    = stbTypes::NoImpact;
   MaxStressWindDirection[stbTypes::Bottom]      = stbTypes::Left;
   MaxStressCorner[stbTypes::Bottom]             = stbTypes::BottomRight;

   MinStressImpactDirection[stbTypes::Bottom]    = stbTypes::NoImpact;
   MinStressWindDirection[stbTypes::Bottom]      = stbTypes::Left;
   MinStressCorner[stbTypes::Bottom]             = stbTypes::BottomRight;
}

/////////////////////////////////////

stbLiftingResults::stbLiftingResults()
{
   bIsStable[stbTypes::NoImpact] = true;
   bIsStable[stbTypes::ImpactUp]   = true;
   bIsStable[stbTypes::ImpactDown] = true;

   Pcrit = 0;
   Plift = 0;
   memset((void*)emag,0,sizeof(emag));
   dLift = 0;

   MaxDirectStress = 0;
   MaxDirectStressAnalysisPointIndex = INVALID_INDEX;
   MaxDirectStressImpactDirection    = stbTypes::NoImpact;
   MaxDirectStressWindDirection      = stbTypes::Left;
   MaxDirectStressCorner             = stbTypes::TopLeft;

   MinDirectStress = 0;
   MinDirectStressAnalysisPointIndex = INVALID_INDEX;
   MinDirectStressImpactDirection    = stbTypes::NoImpact;
   MinDirectStressWindDirection      = stbTypes::Left;
   MinDirectStressCorner             = stbTypes::TopLeft;

   MaxStress = 0;
   MaxStressAnalysisPointIndex = INVALID_INDEX;
   MaxStressImpactDirection    = stbTypes::NoImpact;
   MaxStressWindDirection      = stbTypes::Left;
   MaxStressCorner             = stbTypes::TopLeft;

   MinStress = 0;
   MinStressAnalysisPointIndex = INVALID_INDEX;
   MinStressImpactDirection    = stbTypes::NoImpact;
   MinStressWindDirection      = stbTypes::Left;
   MinStressCorner             = stbTypes::TopLeft;

   MinFScr = 0;
   FScrAnalysisPointIndex = INVALID_INDEX;
   FScrImpactDirection    = stbTypes::NoImpact;
   FScrWindDirection      = stbTypes::Left;

   memset((void*)(ThetaMax),0,sizeof(ThetaMax));
   memset((void*)(FsFailure),0,sizeof(FsFailure));
   memset((void*)(AdjFsFailure),0,sizeof(AdjFsFailure));

   FSfImpactDirection = stbTypes::NoImpact;
   FSfWindDirection   = stbTypes::Left;
   MinFsFailure    = 0;
   MinAdjFsFailure = 0;
}