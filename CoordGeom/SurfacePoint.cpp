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
#include <CoordGeom/SurfacePoint.h>
#include <CoordGeom/Surface.h>
#include <CoordGeom/Profile.h>
#include <CoordGeom/Alignment.h>

using namespace WBFL::COGO;

SurfacePoint::SurfacePoint(const Station& station, Float64 normalOffset, Float64 cutlineOffset, Float64 elevation, const WBFL::Geometry::Point2d& location) :
   m_Station(station), m_NormalOffset(normalOffset), m_CutlineOffset(cutlineOffset), m_Elevation(elevation), m_Location(location)
{
}

void SurfacePoint::SetSurface(std::weak_ptr<const Surface> surface)
{
   m_Surface = surface;
}

std::shared_ptr<SurfacePoint> SurfacePoint::Create()
{
   return std::shared_ptr<SurfacePoint>(new SurfacePoint);
}

std::shared_ptr<SurfacePoint> SurfacePoint::Create(const Station& station, Float64 normalOffset, Float64 cutlineOffset, Float64 elevation, const WBFL::Geometry::Point2d& location)
{
   return std::shared_ptr<SurfacePoint>(new SurfacePoint(station, normalOffset, cutlineOffset, elevation, location));
}

std::shared_ptr<const Surface> SurfacePoint::GetSurface() const
{
   return m_Surface.lock();
}

void SurfacePoint::SetStation(const Station& station)
{
   m_Station = station;
}

const Station& SurfacePoint::GetStation() const
{
   return m_Station;
}

void SurfacePoint::SetNormalOffset(Float64 offset)
{
   m_NormalOffset = offset;
}

Float64 SurfacePoint::GetNormalOffset() const
{
   return m_NormalOffset;
}

void SurfacePoint::SetCutlineOffset(Float64 offset)
{
   m_CutlineOffset = offset;
}

Float64 SurfacePoint::GetCutlineOffset() const
{
   return m_CutlineOffset;
}

void SurfacePoint::SetElevation(Float64 elevation)
{
   m_Elevation = elevation;
}

Float64 SurfacePoint::GetElevation() const
{
   return m_Elevation;
}

void SurfacePoint::SetLocation(const WBFL::Geometry::Point2d& location)
{
   m_Location = location;
}

const WBFL::Geometry::Point2d& SurfacePoint::GetLocation() const
{
   return m_Location;
}

WBFL::Geometry::Point3d SurfacePoint::GetPoint() const
{
   return WBFL::Geometry::Point3d(m_Location, m_Elevation);
}
