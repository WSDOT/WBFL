///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#include <GeomModel/GeomModelLib.h>
#include <GeomModel/MassProperties.h>

using namespace WBFL::Geometry;

MassProperties::MassProperties(Float64 mpl):
m_Mpl(mpl)
{
}

MassProperties MassProperties::operator+(const MassProperties& other)
{
   return MassProperties(m_Mpl + other.m_Mpl);
}

MassProperties MassProperties::operator-(const MassProperties& other)
{
   return MassProperties(m_Mpl - other.m_Mpl);
}

MassProperties& MassProperties::operator+=(const MassProperties& other)
{
   m_Mpl += other.m_Mpl;
   return *this;
}

MassProperties& MassProperties::operator-=(const MassProperties& other)
{
   m_Mpl -= other.m_Mpl;
   return *this;
}

void MassProperties::SetMassPerLength(Float64 mpl)
{
   m_Mpl = mpl;
}

Float64 MassProperties::GetMassPerLength() const
{
   return m_Mpl;
}
