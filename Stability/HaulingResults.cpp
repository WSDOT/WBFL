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
#include <Stability\HaulingResults.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

stbHaulingSectionResult::stbHaulingSectionResult()
{
   AnalysisPointIndex = INVALID_INDEX;

   Mg = 0;
   Mw = 0;
   Mcf = 0;

   memset((void*)fps, 0, sizeof(fps));
   memset((void*)fg, 0, sizeof(fg));
   memset((void*)fw, 0, sizeof(fw));
   memset((void*)fcf, 0, sizeof(fcf));

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

   memset((void*)FScrMin, 0, sizeof(FScrMin));
   memset((void*)FScrImpactDirection, 0, sizeof(FScrImpactDirection));
   memset((void*)FScrWindDirection, 0, sizeof(FScrWindDirection));
   memset((void*)FScrCorner, 0, sizeof(FScrCorner));


   for (int s = 0; s < 2; s++)
   {
      stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;
      fMinDirect[slope][stbTypes::Top] = Float64_Max;
      fMinDirect[slope][stbTypes::Bottom] = Float64_Max;
      fMaxDirect[slope][stbTypes::Top] = -Float64_Max;
      fMaxDirect[slope][stbTypes::Bottom] = -Float64_Max;

      fMin[slope][stbTypes::Top] = Float64_Max;
      fMin[slope][stbTypes::Bottom] = Float64_Max;
      fMax[slope][stbTypes::Top] = -Float64_Max;
      fMax[slope][stbTypes::Bottom] = -Float64_Max;

      FScrMin[slope] = Float64_Max;
   }

}

//////////////////////////////////////////

stbHaulingResults::stbHaulingResults()
{
   for ( int s = 0; s < 2; s++ )
   {
      stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;

      MaxDirectStress[slope] = -Float64_Max;
      MaxDirectStressAnalysisPointIndex[slope] = 0;
      MaxDirectStressImpactDirection[slope] = stbTypes::NoImpact;
      MaxDirectStressCorner[slope] = stbTypes::TopLeft;

      MinDirectStress[slope] = Float64_Max;
      MinDirectStressAnalysisPointIndex[slope] = 0;
      MinDirectStressImpactDirection[slope] = stbTypes::NoImpact;
      MinDirectStressCorner[slope] = stbTypes::TopLeft;

      MaxStress[slope] = -Float64_Max;
      MaxStressAnalysisPointIndex[slope] = 0;
      MaxStressImpactDirection[slope] = stbTypes::NoImpact;
      MaxStressWindDirection[slope] = stbTypes::Left;
      MaxStressCorner[slope] = stbTypes::TopLeft;

      MinStress[slope] = Float64_Max;
      MinStressAnalysisPointIndex[slope] = 0;
      MinStressImpactDirection[slope] = stbTypes::NoImpact;
      MinStressWindDirection[slope] = stbTypes::Left;
      MinStressCorner[slope] = stbTypes::TopLeft;

      MinFScr[slope] = Float64_Max;
      FScrAnalysisPointIndex[slope] = 0;
      FScrImpactDirection[slope] = stbTypes::NoImpact;
      FScrWindDirection[slope] = stbTypes::Left;
      FScrCorner[slope] = stbTypes::TopLeft;

      FSfImpactDirection[slope] = stbTypes::NoImpact;
      FSfWindDirection[slope] = stbTypes::Left;
      MinFsFailure[slope] = Float64_Max;
      MinAdjFsFailure[slope] = Float64_Max;

      FSroImpactDirection[slope] = stbTypes::NoImpact;
      FSroWindDirection[slope] = stbTypes::Left;
      MinFsRollover[slope] = Float64_Max;

      for (int i = 0; i < 3; i++)
      {
         stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
         for (int w = 0; w < 2; w++)
         {
            stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
            bRotationalStability[slope][impact][wind] = true;
            bRolloverStability[slope][impact][wind] = true;
         }
      }
   }


   memset((void*)ThetaMax, 0, sizeof(ThetaMax));
   memset((void*)FsFailure, 0, sizeof(FsFailure));
   memset((void*)AdjFsFailure, 0, sizeof(AdjFsFailure));

   memset((void*)ThetaRollover, 0, sizeof(ThetaRollover));
   memset((void*)FsRollover,0,sizeof(FsRollover));
}

bool stbHaulingResults::HasRotationalStablity() const
{
   for (int s = 0; s < 2; s++)
   {
      stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;
      for (int i = 0; i < 3; i++)
      {
         stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
         for (int w = 0; w < 2; w++)
         {
            stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
            if (!bRotationalStability[slope][impact][wind])
            {
               // only one has to be false
               return false;
            }
         }
      }
   }
   return true;
}

bool stbHaulingResults::HasRolloverStability() const
{
   for (int s = 0; s < 2; s++)
   {
      stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;
      for (int i = 0; i < 3; i++)
      {
         stbTypes::ImpactDirection impact = (stbTypes::ImpactDirection)i;
         for (int w = 0; w < 2; w++)
         {
            stbTypes::WindDirection wind = (stbTypes::WindDirection)w;
            if (!bRolloverStability[slope][impact][wind])
            {
               // only one has to be false
               return false;
            }
         }
      }
   }

   return true;
}

bool stbHaulingResults::IsStable() const
{
   return HasRotationalStablity() && HasRolloverStability();
}