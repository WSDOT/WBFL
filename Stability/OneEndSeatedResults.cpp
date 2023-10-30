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

#include <Stability\StabilityLib.h>
#include <Stability\OneEndSeatedResults.h>

using namespace WBFL::Stability;

OneEndSeatedSectionResult::OneEndSeatedSectionResult()
{
   AnalysisPointIndex = INVALID_INDEX;

   Mg = 0;
   Mw = 0;
   Mcf = 0;

   fps.fill(0);
   fg.fill(0);
   fw.fill(0);
   fcf.fill(0);

   memset((void*)fDirect, 0, sizeof(fDirect));
   memset((void*)fTilt, 0, sizeof(fTilt));
   memset((void*)f, 0, sizeof(f));

   memset((void*)fMinDirect, 0, sizeof(fMinDirect));
   memset((void*)MinDirectStressImpactDirection, 0, sizeof(MinDirectStressImpactDirection));
   memset((void*)MinDirectStressCorner, 0, sizeof(MinDirectStressCorner));

   memset((void*)fMaxDirect, 0, sizeof(fMaxDirect));
   memset((void*)MaxDirectStressImpactDirection, 0, sizeof(MaxDirectStressImpactDirection));
   memset((void*)MaxDirectStressCorner, 0, sizeof(MaxDirectStressCorner));

   memset((void*)fMin, 0, sizeof(fMin));
   memset((void*)MinStressImpactDirection, 0, sizeof(MinStressImpactDirection));
   memset((void*)MinStressWindDirection, 0, sizeof(MinStressWindDirection));
   memset((void*)MinStressCorner, 0, sizeof(MinStressCorner));

   memset((void*)fMax, 0, sizeof(fMax));
   memset((void*)MaxStressImpactDirection, 0, sizeof(MaxStressImpactDirection));
   memset((void*)MaxStressWindDirection, 0, sizeof(MaxStressWindDirection));
   memset((void*)MaxStressCorner, 0, sizeof(MaxStressCorner));

   memset((void*)Mcr, 0, sizeof(Mcr));
   memset((void*)ThetaCrack, 0, sizeof(ThetaCrack));

   memset((void*)FScr, 0, sizeof(FScr));

   FScrMin = 0;
   FScrImpactDirection = ImpactDirection::NoImpact;
   FScrWindDirection = WindDirection::Left;
   FScrCorner = Corner::BottomLeft;


   fMinDirect[+GirderFace::Top] = Float64_Max;
   fMinDirect[+GirderFace::Bottom] = Float64_Max;
   fMaxDirect[+GirderFace::Top] = -Float64_Max;
   fMaxDirect[+GirderFace::Bottom] = -Float64_Max;

   fMin[+GirderFace::Top] = Float64_Max;
   fMin[+GirderFace::Bottom] = Float64_Max;
   fMax[+GirderFace::Top] = -Float64_Max;
   fMax[+GirderFace::Bottom] = -Float64_Max;

   FScrMin = Float64_Max;

}

//////////////////////////////////////////

OneEndSeatedResults::OneEndSeatedResults()
{
   MaxDirectStress = -Float64_Max;
   MaxDirectStressAnalysisPointIndex = 0;
   MaxDirectStressImpactDirection = ImpactDirection::NoImpact;
   MaxDirectStressCorner = Corner::TopLeft;

   MinDirectStress = Float64_Max;
   MinDirectStressAnalysisPointIndex = 0;
   MinDirectStressImpactDirection = ImpactDirection::NoImpact;
   MinDirectStressCorner = Corner::TopLeft;

   MaxStress = -Float64_Max;
   MaxStressAnalysisPointIndex = 0;
   MaxStressImpactDirection = ImpactDirection::NoImpact;
   MaxStressWindDirection = WindDirection::Left;
   MaxStressCorner = Corner::TopLeft;

   MinStress = Float64_Max;
   MinStressAnalysisPointIndex = 0;
   MinStressImpactDirection = ImpactDirection::NoImpact;
   MinStressWindDirection = WindDirection::Left;
   MinStressCorner = Corner::TopLeft;

   MinFScr = Float64_Max;
   FScrAnalysisPointIndex = 0;
   FScrImpactDirection = ImpactDirection::NoImpact;
   FScrWindDirection = WindDirection::Left;
   FScrCorner = Corner::TopLeft;

   FSfImpactDirection = ImpactDirection::NoImpact;
   FSfWindDirection = WindDirection::Left;
   MinFsFailure = Float64_Max;
   MinAdjFsFailure = Float64_Max;

   FSroImpactDirection = ImpactDirection::NoImpact;
   FSroWindDirection = WindDirection::Left;
   MinFsRollover = Float64_Max;

   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;
         bRotationalStability[+impact][+wind] = true;
         bRolloverStability[+impact][+wind] = true;
      }
   }


   memset((void*)ThetaMax, 0, sizeof(ThetaMax));
   memset((void*)FsFailure, 0, sizeof(FsFailure));
   memset((void*)AdjFsFailure, 0, sizeof(AdjFsFailure));

   memset((void*)ThetaRollover, 0, sizeof(ThetaRollover));
   memset((void*)FsRollover,0,sizeof(FsRollover));

   AssumedTiltDirection = GirderSide::Left;
}

bool OneEndSeatedResults::HasRotationalStablity() const
{
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;
         if (!bRotationalStability[+impact][+wind])
         {
            // only one has to be false
            return false;
         }
      }
   }
   return true;
}

bool OneEndSeatedResults::HasRolloverStability() const
{
   for (int i = 0; i < 3; i++)
   {
      ImpactDirection impact = (ImpactDirection)i;
      for (int w = 0; w < 2; w++)
      {
         WindDirection wind = (WindDirection)w;
         if (!bRolloverStability[+impact][+wind])
         {
            // only one has to be false
            return false;
         }
      }
   }

   return true;
}

bool OneEndSeatedResults::IsStable() const
{
   return HasRotationalStablity() && HasRolloverStability();
}
