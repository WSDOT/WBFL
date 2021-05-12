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
#include <Stability\HaulingCriteria.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

stbHaulingCriteria::stbHaulingCriteria()
{
   Lambda = 0.0;

   CompressionCoefficient_GlobalStress = 0;
   CompressionCoefficient_PeakStress = 0;
   AllowableCompression_GlobalStress = 0;
   AllowableCompression_PeakStress = 0;

   MinFScr = Float64_Max;
   MinFSf  = Float64_Max;

   for ( int s = 0; s < 2; s++ )
   {
      stbTypes::HaulingSlope slope = (stbTypes::HaulingSlope)s;
      TensionCoefficient[slope] = 0;
      bMaxTension[slope] = false;
      MaxTension[slope] = 0;
      TensionCoefficientWithRebar[slope] = 0;
      AllowableTension[slope]          = 0;
      AllowableTensionWithRebar[slope] = 0;
   }
}