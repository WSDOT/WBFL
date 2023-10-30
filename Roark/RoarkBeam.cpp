///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam formula, patterned after Roark's formulas
//         for Stress and Strain
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

#include <Roark/RoarkLib.h>
#include <Roark/RoarkBeam.h>

using namespace WBFL::Beams;

RoarkBeam::RoarkBeam(Float64 l,Float64 ei)
{
   PRECONDITION(0 < l);
   PRECONDITION(0 < ei);
   L = l; // Length of beam
   EI = ei;
}

void RoarkBeam::SetL(Float64 l)
{
   PRECONDITION(0 < l);
   L = l;
}

Float64 RoarkBeam::GetL() const
{
   return L;
}

void RoarkBeam::SetEI(Float64 ei)
{
   PRECONDITION(0 < ei);
   EI = ei;
}

Float64 RoarkBeam::GetEI() const
{
   return EI;
}

std::pair<Float64,Float64> RoarkBeam::GetProperties() const
{
   return std::make_pair(L, EI);
}
