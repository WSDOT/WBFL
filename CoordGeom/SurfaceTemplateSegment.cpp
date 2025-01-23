///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <CoordGeom/SurfaceTemplateSegment.h>

using namespace WBFL::COGO;

SurfaceTemplateSegment::SurfaceTemplateSegment(Float64 width, Float64 slope, SlopeType slopeType)
{
   SetParameters(width, slope, slopeType);
}

void SurfaceTemplateSegment::SetParameters(Float64 width, Float64 slope, SlopeType slopeType)
{
   m_Width = width;
   m_Slope = slope;
   m_SlopeType = slopeType;
}

std::tuple<Float64, Float64, SurfaceTemplateSegment::SlopeType> SurfaceTemplateSegment::GetParameters() const
{
   return std::make_tuple(m_Width, m_Slope, m_SlopeType);
}

void SurfaceTemplateSegment::SetWidth(Float64 width)
{
   m_Width = width;
}

Float64 SurfaceTemplateSegment::SurfaceTemplateSegment::GetWidth() const
{
   return m_Width;
}

void SurfaceTemplateSegment::SetSlope(Float64 slope)
{
   m_Slope = slope;
}

Float64 SurfaceTemplateSegment::GetSlope() const
{
   return m_Slope;
}

void SurfaceTemplateSegment::SetSlopeType(SlopeType slopeType)
{
   m_SlopeType = slopeType;
}

SurfaceTemplateSegment::SlopeType SurfaceTemplateSegment::GetSlopeType() const
{
   return m_SlopeType;
}
