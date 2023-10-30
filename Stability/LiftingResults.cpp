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

#include <Stability/StabilityLib.h>
#include <Stability/LiftingResults.h>

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
   MinDirectStressImpactDirection.fill(ImpactDirection::NoImpact);
   MinDirectStressCorner.fill(Corner::TopLeft);

   fMaxDirect.fill(0);
   MaxDirectStressImpactDirection.fill(ImpactDirection::NoImpact);
   MaxDirectStressCorner.fill(Corner::TopLeft);

   fMin.fill(0);
   MinStressImpactDirection[+GirderFace::Top]    = ImpactDirection::NoImpact;
   MinStressWindDirection[+GirderFace::Top]      = WindDirection::Left;
   MinStressCorner[+GirderFace::Top]             = Corner::TopLeft;
   MinStressImpactDirection[+GirderFace::Bottom] = ImpactDirection::NoImpact;
   MinStressWindDirection[+GirderFace::Bottom]   = WindDirection::Left;
   MinStressCorner[+GirderFace::Bottom]          = Corner::BottomRight;

   fMax.fill(0);
   MaxStressImpactDirection[+GirderFace::Top]    = ImpactDirection::NoImpact;
   MaxStressWindDirection[+GirderFace::Top]      = WindDirection::Left;
   MaxStressCorner[+GirderFace::Top]             = Corner::TopLeft;
   MaxStressImpactDirection[+GirderFace::Bottom] = ImpactDirection::NoImpact;
   MaxStressWindDirection[+GirderFace::Bottom]   = WindDirection::Left;
   MaxStressCorner[+GirderFace::Bottom]          = Corner::BottomRight;

   memset((void*)Mcr, 0, sizeof(Mcr));
   memset((void*)ThetaCrack, 0, sizeof(ThetaCrack));

      for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;

         MinFScr[+impact][+wind] = Float64_Max;
         MinFScrCorner[+impact][+wind] = Corner::TopLeft;

         for (int c = 0; c < 4; c++)
         {
            Corner corner = (Corner)c;
            FScr[+impact][+wind][+corner] = Float64_Max;
         }
      }
   }

   FScrMin = Float64_Max;
   FScrMinImpactDirection = ImpactDirection::NoImpact;
   FScrMinWindDirection = WindDirection::Left;
   FScrMinCorner = Corner::TopLeft;

   Float64 OffsetFactor = 0;
   memset((void*)eh, 0, sizeof(eh));
   memset((void*)Mh, 0, sizeof(Mh));

   fMin[+GirderFace::Top] = Float64_Max;
   fMin[+GirderFace::Bottom] = Float64_Max;
   fMax[+GirderFace::Top] = -Float64_Max;
   fMax[+GirderFace::Bottom] = -Float64_Max;

   fMinDirect[+GirderFace::Top] = Float64_Max;
   fMinDirect[+GirderFace::Bottom] = Float64_Max;
   fMaxDirect[+GirderFace::Top] = -Float64_Max;
   fMaxDirect[+GirderFace::Bottom] = -Float64_Max;
}

/////////////////////////////////////

LiftingResults::LiftingResults()
{
   Pcrit = 0;
   Plift = 0;
   emag.fill(0);
   //dLift = 0;

   MaxDirectStress = -Float64_Max;
   MaxDirectStressAnalysisPointIndex = 0;
   MaxDirectStressImpactDirection    = ImpactDirection::NoImpact;
   MaxDirectStressCorner             = Corner::TopLeft;

   MinDirectStress = Float64_Max;
   MinDirectStressAnalysisPointIndex = 0;
   MinDirectStressImpactDirection    = ImpactDirection::NoImpact;
   MinDirectStressCorner             = Corner::TopLeft;

   MaxStress = -Float64_Max;
   MaxStressAnalysisPointIndex = 0;
   MaxStressImpactDirection    = ImpactDirection::NoImpact;
   MaxStressWindDirection      = WindDirection::Left;
   MaxStressCorner             = Corner::TopLeft;

   MinStress = Float64_Max;
   MinStressAnalysisPointIndex = 0;
   MinStressImpactDirection    = ImpactDirection::NoImpact;
   MinStressWindDirection      = WindDirection::Left;
   MinStressCorner             = Corner::TopLeft;

   FScrMin = Float64_Max;
   FScrMinAnalysisPointIndex = 0;
   FScrMinImpactDirection    = ImpactDirection::NoImpact;
   FScrMinWindDirection      = WindDirection::Left;
   FScrMinCorner             = Corner::TopLeft;

   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;
         ThetaEq[+impact][+wind] = 0.0;
         ThetaMax[+impact][+wind] = 0.0;
         FScrAnalysisPointIndex[+impact][+wind] = 0;
         FScrCorner[+impact][+wind] = (Corner)0;

         MinFScr[+impact][+wind] = Float64_Max;
         FsFailure[+impact][+wind] = Float64_Max;
         AdjFsFailure[+impact][+wind] = Float64_Max;

         bIsStable[+impact][+wind] = true;
      }
   }

   MinFsFailure = Float64_Max;
   MinAdjFsFailure = Float64_Max;
   FSfImpactDirection = ImpactDirection::NoImpact;
   FSfWindDirection   = WindDirection::Left;

   AssumedTiltDirection = GirderSide::Left;
}