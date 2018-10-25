///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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

#pragma once

#include <Math\MathExp.h>

/*****************************************************************************
CLASS 
   mathCDRatio

   Utility class for evaluating capacity/demand ratios
*****************************************************************************/

class MATHCLASS mathCDRatio
{
public:
   // Sense of capacity being measured. (e.g., tension positive, compression negative)
   // This is necessary because both capacities being compared could be zero.
   enum cdSense {cdPositive, cdNegative};

   static Float64 CDRatio(Float64 capacity,Float64 demand);

   // Returns true if C/D 1 is less than C/D 2
   static bool IsCDRatioLess(cdSense sense, Float64 capacity1, Float64 demand1, Float64 capacity2, Float64 demand2);

   // returns the index of the minimum CD ratio
   static int MinCDRatio(cdSense sense, Float64 capacity1, Float64 demand1, Float64 capacity2, Float64 demand2, Float64 capacity3, Float64 demand3, Float64 capacity4, Float64 demand4,Float64* pCD);
};
