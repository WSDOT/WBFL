///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2019  Washington State Department of Transportation
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
   AnalysisPointIndex = INVALID_INDEX;

   Mg = 0;
   Mw = 0;

   memset((void*)fps, 0, sizeof(fps));
   memset((void*)fcable, 0, sizeof(fcable));
   memset((void*)fg, 0, sizeof(fg));
   memset((void*)fw, 0, sizeof(fw));

   memset((void*)fDirect, 0, sizeof(fDirect));
   memset((void*)fTilt, 0, sizeof(fTilt));
   memset((void*)f, 0, sizeof(f));

   memset((void*)fMinDirect, 0, sizeof(fMinDirect));
   memset((void*)MinDirectStressImpactDirection, 0, sizeof(MinDirectStressImpactDirection));
   memset((void*)MinDirectStressWindDirection, 0, sizeof(MinDirectStressWindDirection));
   memset((void*)MinDirectStressCorner, 0, sizeof(MinDirectStressCorner));

   memset((void*)fMaxDirect, 0, sizeof(fMaxDirect));
   memset((void*)MaxDirectStressImpactDirection, 0, sizeof(MaxDirectStressImpactDirection));
   memset((void*)MaxDirectStressWindDirection, 0, sizeof(MaxDirectStressWindDirection));
   memset((void*)MaxDirectStressCorner, 0, sizeof(MaxDirectStressCorner));

   memset((void*)fMin, 0, sizeof(fMin));
   MinStressImpactDirection[stbTypes::Top]    = stbTypes::NoImpact;
   MinStressWindDirection[stbTypes::Top]      = stbTypes::Left;
   MinStressCorner[stbTypes::Top]             = stbTypes::TopLeft;
   MinStressImpactDirection[stbTypes::Bottom] = stbTypes::NoImpact;
   MinStressWindDirection[stbTypes::Bottom]   = stbTypes::Left;
   MinStressCorner[stbTypes::Bottom]          = stbTypes::BottomRight;

   memset((void*)fMax, 0, sizeof(fMax));
   MaxStressImpactDirection[stbTypes::Top]    = stbTypes::NoImpact;
   MaxStressWindDirection[stbTypes::Top]      = stbTypes::Left;
   MaxStressCorner[stbTypes::Top]             = stbTypes::TopLeft;
   MaxStressImpactDirection[stbTypes::Bottom] = stbTypes::NoImpact;
   MaxStressWindDirection[stbTypes::Bottom]   = stbTypes::Left;
   MaxStressCorner[stbTypes::Bottom]          = stbTypes::BottomRight;

   memset((void*)Mcr, 0, sizeof(Mcr));
   memset((void*)ThetaCrack, 0, sizeof(ThetaCrack));

      for (int i = 0; i < 3; i++)
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         stbTypes::WindDirection wind = (stbTypes::WindDirection)w;

         MinFScr[impact][wind] = Float64_Max;
         MinFScrCorner[impact][wind] = stbTypes::TopLeft;

         for (int c = 0; c < 4; c++)
         {
            stbTypes::Corner corner = (stbTypes::Corner)c;
            FScr[impact][wind][corner] = Float64_Max;
         }
      }
   }

   FScrMin = Float64_Max;
   FScrMinImpactDirection = stbTypes::NoImpact;
   FScrMinWindDirection = stbTypes::Left;
   FScrMinCorner = stbTypes::TopLeft;

   Float64 OffsetFactor = 0;
   memset((void*)eh, 0, sizeof(eh));
   memset((void*)Mh, 0, sizeof(Mh));

   fMin[stbTypes::Top] = Float64_Max;
   fMin[stbTypes::Bottom] = Float64_Max;
   fMax[stbTypes::Top] = -Float64_Max;
   fMax[stbTypes::Bottom] = -Float64_Max;

   fMinDirect[stbTypes::Top] = Float64_Max;
   fMinDirect[stbTypes::Bottom] = Float64_Max;
   fMaxDirect[stbTypes::Top] = -Float64_Max;
   fMaxDirect[stbTypes::Bottom] = -Float64_Max;
}

/////////////////////////////////////

stbLiftingResults::stbLiftingResults()
{
   Pcrit = 0;
   Plift = 0;
   memset((void*)emag,0,sizeof(emag));
   dLift = 0;

   memset((void*)ThetaEq, 0, sizeof(ThetaEq));

   MaxDirectStress = -Float64_Max;
   MaxDirectStressAnalysisPointIndex = 0;
   MaxDirectStressImpactDirection    = stbTypes::NoImpact;
   MaxDirectStressWindDirection      = stbTypes::Left;
   MaxDirectStressCorner             = stbTypes::TopLeft;

   MinDirectStress = Float64_Max;
   MinDirectStressAnalysisPointIndex = 0;
   MinDirectStressImpactDirection    = stbTypes::NoImpact;
   MinDirectStressWindDirection      = stbTypes::Left;
   MinDirectStressCorner             = stbTypes::TopLeft;

   MaxStress = -Float64_Max;
   MaxStressAnalysisPointIndex = 0;
   MaxStressImpactDirection    = stbTypes::NoImpact;
   MaxStressWindDirection      = stbTypes::Left;
   MaxStressCorner             = stbTypes::TopLeft;

   MinStress = Float64_Max;
   MinStressAnalysisPointIndex = 0;
   MinStressImpactDirection    = stbTypes::NoImpact;
   MinStressWindDirection      = stbTypes::Left;
   MinStressCorner             = stbTypes::TopLeft;

   memset((void*)FScrAnalysisPointIndex, 0, sizeof(FScrAnalysisPointIndex));
   memset((void*)FScrCorner, 0, sizeof(FScrCorner));

   FScrMin = Float64_Max;
   FScrMinAnalysisPointIndex = 0;
   FScrMinImpactDirection    = stbTypes::NoImpact;
   FScrMinWindDirection      = stbTypes::Left;
   FScrMinCorner = stbTypes::TopLeft;

   for (int i = 0; i < 3; i++)
   {
      stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
         MinFScr[impact][wind] = Float64_Max;
         FsFailure[impact][wind] = Float64_Max;
         AdjFsFailure[impact][wind] = Float64_Max;

         bIsStable[impact][wind] = true;
      }
   }


   memset((void*)(ThetaMax),0,sizeof(ThetaMax));

   MinFsFailure = Float64_Max;
   MinAdjFsFailure = Float64_Max;
   FSfImpactDirection = stbTypes::NoImpact;
   FSfWindDirection   = stbTypes::Left;
}