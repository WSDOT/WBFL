///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/SurfaceTemplate.h>
#include <CoordGeom/Surface.h>
#include <CoordGeom/Profile.h>
#include "SurfaceTemplateImpl.h"

using namespace WBFL::COGO;

std::shared_ptr<SurfaceTemplate> SurfaceTemplate::Create(const Station& station)
{
   return std::shared_ptr<SurfaceTemplate>(new SurfaceTemplate(station));
}

std::shared_ptr<SurfaceTemplate> SurfaceTemplate::Create(const SurfaceTemplate& surfaceTemplate)
{
   return std::shared_ptr<SurfaceTemplate>(new SurfaceTemplate(surfaceTemplate));
}

SurfaceTemplate::SurfaceTemplate(const Station& station)
{
   m_pImpl = std::make_unique<SurfaceTemplateImpl>(station);
}

SurfaceTemplate::SurfaceTemplate(const SurfaceTemplate& surfaceTemplate)
{
   m_pImpl = std::make_unique<SurfaceTemplateImpl>(*surfaceTemplate.m_pImpl);

   // The default constructor of the implementation class copies the surface data member.
   // A newly created surface template object should not be associated with a surface,
   // so set the surface to nullptr
   m_pImpl->SetSurface(std::shared_ptr<Surface>(nullptr));
}

SurfaceTemplate::~SurfaceTemplate() = default;

void SurfaceTemplate::SetSurface(std::weak_ptr<const Surface> surface)
{
   m_pImpl->SetSurface(surface);
}

std::shared_ptr<const Surface> SurfaceTemplate::GetSurface() const
{
   return m_pImpl->GetSurface();
}

const Station& SurfaceTemplate::GetStation() const
{
   return m_pImpl->GetStation();
}

std::tuple<Float64, Float64, SurfaceTemplateSegment::SlopeType> SurfaceTemplate::GetSegmentParameters(IndexType segmentIdx)
{
   return m_pImpl->GetSegmentParameters(segmentIdx);
}

void SurfaceTemplate::UpdateSegmentParameters(IndexType segmentIdx, Float64 width, Float64 slope, SurfaceTemplateSegment::SlopeType slopeType)
{
   m_pImpl->UpdateSegmentParameters(segmentIdx, width, slope, slopeType);
}

IndexType SurfaceTemplate::GetCount() const
{
   return m_pImpl->GetCount();
}

SurfaceTemplateSegment& SurfaceTemplate::GetSegment(IndexType idx)
{
   return m_pImpl->GetSegment(idx);
}

const SurfaceTemplateSegment& SurfaceTemplate::GetSegment(IndexType idx) const
{
   return m_pImpl->GetSegment(idx);
}

void SurfaceTemplate::Clear()
{
   m_pImpl->Clear();
}

Float64 SurfaceTemplate::GetRidgePointElevationChange(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   return m_pImpl->GetRidgePointElevationChange(ridgePoint1Idx, ridgePoint2Idx);
}

Float64 SurfaceTemplate::GetElevationChange(IndexType ridgePointIdx, Float64 offset) const
{
   return m_pImpl->GetElevationChange(ridgePointIdx, offset);
}

Float64 SurfaceTemplate::GetSlope(IndexType ridgePointIdx, Float64 offset) const
{
   return m_pImpl->GetSlope(ridgePointIdx, offset);
}

Float64 SurfaceTemplate::GetSegmentSlope(IndexType idx) const
{
   return m_pImpl->GetSegmentSlope(idx);
}

Float64 SurfaceTemplate::GetRidgePointOffset(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   return m_pImpl->GetRidgePointOffset(ridgePoint1Idx, ridgePoint2Idx);
}

Float64 SurfaceTemplate::GetRidgePointElevation(IndexType ridgePointIdx) const
{
   return m_pImpl->GetRidgePointElevation(ridgePointIdx);
}

std::pair<Float64,Float64> SurfaceTemplate::GetRidgePointOffsetAndElevation(IndexType ridgePoint1Idx, IndexType ridgePoint2Idx) const
{
   return m_pImpl->GetRidgePointOffsetAndElevation(ridgePoint1Idx, ridgePoint2Idx);
}
