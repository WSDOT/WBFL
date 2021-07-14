///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2021  Washington State Department of Transportation
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

using namespace WBFL::Stability;

LiftingSectionResult::LiftingSectionResult()
{
   AnalysisPointIndex = INVALID_INDEX;

   Mg = 0;
   Mw = 0;

   fps.fill(0);
   fcable.fill(0);
   fg.fill(0);
   fw.fill(0);

   memset((void*)fDirect, 0, sizeof(fDirect));
   memset((void*)fTilt, 0, sizeof(fTilt));
   memset((void*)f, 0, sizeof(f));

   fMinDirect.fill(0);
   MinDirectStressImpactDirection.fill(NoImpact);
   MinDirectStressCorner.fill(TopLeft);

   fMaxDirect.fill(0);
   MaxDirectStressImpactDirection.fill(NoImpact);
   MaxDirectStressCorner.fill(TopLeft);

   fMin.fill(0);
   MinStressImpactDirection[Top]    = NoImpact;
   MinStressWindDirection[Top]      = Left;
   MinStressCorner[Top]             = TopLeft;
   MinStressImpactDirection[Bottom] = NoImpact;
   MinStressWindDirection[Bottom]   = Left;
   MinStressCorner[Bottom]          = BottomRight;

   fMax.fill(0);
   MaxStressImpactDirection[Top]    = NoImpact;
   MaxStressWindDirection[Top]      = Left;
   MaxStressCorner[Top]             = TopLeft;
   MaxStressImpactDirection[Bottom] = NoImpact;
   MaxStressWindDirection[Bottom]   = Left;
   MaxStressCorner[Bottom]          = BottomRight;

   memset((void*)Mcr, 0, sizeof(Mcr));
   memset((void*)ThetaCrack, 0, sizeof(ThetaCrack));

      for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;

         MinFScr[impact][wind] = Float64_Max;
         MinFScrCorner[impact][wind] = TopLeft;

         for (int c = 0; c < 4; c++)
         {
            Corner corner = (Corner)c;
            FScr[impact][wind][corner] = Float64_Max;
         }
      }
   }

   FScrMin = Float64_Max;
   FScrMinImpactDirection = NoImpact;
   FScrMinWindDirection = Left;
   FScrMinCorner = TopLeft;

   Float64 OffsetFactor = 0;
   memset((void*)eh, 0, sizeof(eh));
   memset((void*)Mh, 0, sizeof(Mh));

   fMin[Top] = Float64_Max;
   fMin[Bottom] = Float64_Max;
   fMax[Top] = -Float64_Max;
   fMax[Bottom] = -Float64_Max;

   fMinDirect[Top] = Float64_Max;
   fMinDirect[Bottom] = Float64_Max;
   fMaxDirect[Top] = -Float64_Max;
   fMaxDirect[Bottom] = -Float64_Max;
}

/////////////////////////////////////

LiftingResults::LiftingResults()
{
   Pcrit = 0;
   Plift = 0;
   emag.fill(0);
   //dLift = 0;

   memset((void*)ThetaEq, 0, sizeof(ThetaEq));

   MaxDirectStress = -Float64_Max;
   MaxDirectStressAnalysisPointIndex = 0;
   MaxDirectStressImpactDirection    = NoImpact;
   MaxDirectStressCorner             = TopLeft;

   MinDirectStress = Float64_Max;
   MinDirectStressAnalysisPointIndex = 0;
   MinDirectStressImpactDirection    = NoImpact;
   MinDirectStressCorner             = TopLeft;

   MaxStress = -Float64_Max;
   MaxStressAnalysisPointIndex = 0;
   MaxStressImpactDirection    = NoImpact;
   MaxStressWindDirection      = Left;
   MaxStressCorner             = TopLeft;

   MinStress = Float64_Max;
   MinStressAnalysisPointIndex = 0;
   MinStressImpactDirection    = NoImpact;
   MinStressWindDirection      = Left;
   MinStressCorner             = TopLeft;

   memset((void*)FScrAnalysisPointIndex, 0, sizeof(FScrAnalysisPointIndex));
   memset((void*)FScrCorner, 0, sizeof(FScrCorner));

   FScrMin = Float64_Max;
   FScrMinAnalysisPointIndex = 0;
   FScrMinImpactDirection    = NoImpact;
   FScrMinWindDirection      = Left;
   FScrMinCorner = TopLeft;

   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;
         MinFScr[impact][wind] = Float64_Max;
         FsFailure[impact][wind] = Float64_Max;
         AdjFsFailure[impact][wind] = Float64_Max;

         bIsStable[impact][wind] = true;
      }
   }


   memset((void*)(ThetaMax),0,sizeof(ThetaMax));

   MinFsFailure = Float64_Max;
   MinAdjFsFailure = Float64_Max;
   FSfImpactDirection = NoImpact;
   FSfWindDirection   = Left;

   AssumedTiltDirection = Left;
}