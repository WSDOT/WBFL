///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/StationEquation.h>

using namespace WBFL::COGO;

StationEquation::StationEquation(Float64 back, Float64 ahead, Float64 normalizedStation) :
   m_Back(back), m_Ahead(ahead), m_NormalizedStation(normalizedStation)
{
}

std::tuple<Float64,Float64,Float64> StationEquation::GetEquationParameters() const
{
   return std::make_tuple(m_Back, m_Ahead, m_NormalizedStation);
}

Float64 StationEquation::GetBack() const
{
   return m_Back;
}

Float64 StationEquation::GetAhead() const
{
   return m_Ahead;
}

Float64 StationEquation::GetNormalizedStation() const
{
   return m_NormalizedStation;
}
