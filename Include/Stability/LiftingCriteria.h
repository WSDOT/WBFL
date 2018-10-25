///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2018  Washington State Department of Transportation
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
   stbLiftingCriteria

DESCRIPTION
   Encapsulates the criteria for analysis
*****************************************************************************/

class STABILITYCLASS stbLiftingCriteria
{
public:
   stbLiftingCriteria();

   Float64 Lambda;

   Float64 CompressionCoefficient;
   Float64 TensionCoefficient;
   bool bMaxTension;
   Float64 MaxTension;
   Float64 TensionCoefficientWithRebar;

   Float64 MinFScr; // minimum factor of safety against cracking
   Float64 MinFSf;  // minimum factor of safety against failure

   Float64 AllowableCompression; // allowable compression stress
   Float64 AllowableTension; // allowable tension stress
   Float64 AllowableTensionWithRebar; // allowable tension stress if there is adequate rebar
};
