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

#pragma once

#include <Stability\StabilityExp.h>

/*****************************************************************************
CLASS 
   stbCriteria

DESCRIPTION
   Encapsulates the criteria for analysis
*****************************************************************************/

class STABILITYCLASS stbHaulingCriteria
{
public:
   stbHaulingCriteria();

   Float64 Lambda;

   Float64 CompressionCoefficient_GlobalStress;
   Float64 CompressionCoefficient_PeakStress;
   Float64 TensionCoefficient[2];
   bool bMaxTension[2];
   Float64 MaxTension[2];
   Float64 TensionCoefficientWithRebar[2];

   Float64 MinFScr; // minimum factor of safety against cracking
   Float64 MinFSf;  // minimum factor of safety against failure

   Float64 AllowableCompression_GlobalStress; // allowable compression stress
   Float64 AllowableCompression_PeakStress; // allowable compression stress
   Float64 AllowableTension[2]; // allowable tension stress (array index is stbTypes::HaulingSlope)
   Float64 AllowableTensionWithRebar[2]; // allowable tension stress if there is adequate rebar (array index is stbTypes::HaulingSlope)

   Float64 MaxClearSpan;
   Float64 MaxLeadingOverhang;
   Float64 MaxGirderWeight;
};
