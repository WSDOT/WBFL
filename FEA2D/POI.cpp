///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
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

#include <FEA2D\FEA2DLib.h>
#include <FEA2D\POI.h>
#include <FEA2D\Model.h>
#include <FEA2D\XFEA2D.h>

using namespace WBFL::FEA2D;

POI::POI(Model* pModel, PoiIDType id, MemberIDType memberID, Float64 location) :
   m_pModel(pModel), m_ID(id), m_MemberID(memberID), m_Location(location)
{
   if (location < -1.0)
   {
      THROW_FEA2D(ReasonCode::InvalidPoiLocation);
   }
}

PoiIDType POI::GetID() const noexcept
{
   return m_ID;
}

MemberIDType POI::GetMemberID() const noexcept
{
   return m_MemberID;
}

bool POI::SetMemberID(MemberIDType id) noexcept
{
   if (m_MemberID != id) { m_MemberID = id; m_pModel->InvalidatePOI(m_ID); return true; }
   return false;
}

Float64 POI::GetLocation() const noexcept
{
   return m_Location;
}

bool POI::SetLocation(Float64 location)
{
   if (location < -1.0)
   {
      THROW_FEA2D(ReasonCode::InvalidPoiLocation);
   }
   if (m_Location != location) { m_Location = location; m_pModel->InvalidatePOI(m_ID); return true; }
   return false;
}
