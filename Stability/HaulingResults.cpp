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
#include <Stability\HaulingResults.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

stbHaulingSectionResult::stbHaulingSectionResult()
{
   memset((void*)this,0,sizeof(stbHaulingSectionResult));
   memset((void*)bSectionHasRebar,false,sizeof(bSectionHasRebar));
}

//////////////////////////////////////////

stbHaulingResults::stbHaulingResults()
{

   for ( int s = 0; s < 2; s++ )
   {
      stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;

      MaxDirectStress[slope] = 0;
      MaxDirectStressAnalysisPointIndex[slope] = INVALID_INDEX;
      MaxDirectStressImpactDirection[slope] = stbTypes::NoImpact;
      MaxDirectStressWindDirection[slope] = stbTypes::Left;
      MaxDirectStressCorner[slope] = stbTypes::TopLeft;

      MinDirectStress[slope] = 0;
      MinDirectStressAnalysisPointIndex[slope] = INVALID_INDEX;
      MinDirectStressImpactDirection[slope] = stbTypes::NoImpact;
      MinDirectStressWindDirection[slope] = stbTypes::Left;
      MinDirectStressCorner[slope] = stbTypes::TopLeft;

      MaxStress[slope] = 0;
      MaxStressAnalysisPointIndex[slope] = INVALID_INDEX;
      MaxStressImpactDirection[slope] = stbTypes::NoImpact;
      MaxStressWindDirection[slope] = stbTypes::Left;
      MaxStressCorner[slope] = stbTypes::TopLeft;

      MinStress[slope] = 0;
      MinStressAnalysisPointIndex[slope] = INVALID_INDEX;
      MinStressImpactDirection[slope] = stbTypes::NoImpact;
      MinStressWindDirection[slope] = stbTypes::Left;
      MinStressCorner[slope] = stbTypes::TopLeft;

      MinFScr[slope] = 0;
      FScrAnalysisPointIndex[slope] = INVALID_INDEX;
      FScrImpactDirection[slope] = stbTypes::NoImpact;
      FScrWindDirection[slope] = stbTypes::Left;

      FSfImpactDirection[slope] = stbTypes::NoImpact;
      FSfWindDirection[slope] = stbTypes::Left;
      MinFsFailure[slope] = 0;

      FSroImpactDirection[slope] = stbTypes::NoImpact;
      FSroWindDirection[slope] = stbTypes::Left;
      MinFsRollover[slope] = 0;
   }

   memset((void*)ThetaMax,0,sizeof(ThetaMax));
   memset((void*)FsFailure,0,sizeof(FsFailure));
   memset((void*)ThetaRollover,0,sizeof(ThetaRollover));
   memset((void*)FsRollover,0,sizeof(FsRollover));
}