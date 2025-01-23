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
#include <CoordGeom/Widening.h>

#include <CoordGeom/Surface.h>
#include <CoordGeom/Profile.h>
#include <CoordGeom/Alignment.h>
#include <CoordGeom/COGO.h>
#include <CoordGeom/XCoordGeom.h>

using namespace WBFL::COGO;

std::shared_ptr<Widening> Widening::Create()
{
   std::shared_ptr<Widening> w(new Widening());
   return w;
}

std::shared_ptr<Widening> Widening::Create(const Widening& widening)
{
   std::shared_ptr<Widening> w(new Widening(widening));
   return w;
}

std::shared_ptr<Widening> Widening::Create(const Station& beginTrasitionStation, const Station& beginFullWidening, const Station& endFullWidening, const Station& endTrasitionStation, Float64 widening, IndexType segment1, IndexType segment2)
{
   std::shared_ptr<Widening> widen(new Widening());
   widen->Init(beginTrasitionStation, beginFullWidening, endFullWidening, endTrasitionStation, widening, segment1, segment2);
   return widen;
}

void Widening::SetSurface(std::weak_ptr<const Surface> surface)
{
   m_Surface = surface;
}

std::shared_ptr<const Surface> Widening::GetSurface() const
{
   return m_Surface.lock();
}

void Widening::Init(const Station& beginTrasitionStation, const Station& beginFullWidening, const Station& endFullWidening, const Station& endTransitionStation, Float64 widening, IndexType segment1, IndexType segment2)
{
   m_BeginTransition = beginTrasitionStation;
   m_BeginFullWidening = beginFullWidening;
   m_EndFullWidening = endFullWidening;
   m_EndTransition = endTransitionStation;
   m_Widening = widening;
   SetSegment(0, segment1);
   SetSegment(1, segment2);
}

void Widening::SetBeginTransition(const Station& beginTrasitionStation)
{
   m_BeginTransition = beginTrasitionStation;
}

const Station& Widening::GetBeginTransition() const
{
   return m_BeginTransition;
}

void Widening::SetBeginFullWidening(const Station& beginFullWidening)
{
   m_BeginFullWidening = beginFullWidening;
}

const Station& Widening::GetBeginFullWidening() const
{
   return m_BeginFullWidening;
}

void Widening::SetEndFullWidening(const Station& endFullWidening)
{
   m_EndFullWidening = endFullWidening;
}

const Station& Widening::GetEndFullWidening() const
{
   return m_EndFullWidening;
}

void Widening::SetEndTransition(const Station& endTransitionStation)
{
   m_EndTransition = endTransitionStation;
}

const Station& Widening::GetEndTransition() const
{
   return m_EndTransition;
}

void Widening::SetWidening(Float64 widening)
{
   m_Widening = widening;
}

Float64 Widening::GetWidening() const
{
   return m_Widening;
}

void Widening::SetSegment(IndexType pntIdx, IndexType segmentIdx)
{
   PRECONDITION(pntIdx < 2);
   m_SegmentIndex[pntIdx] = segmentIdx;
}

IndexType Widening::GetSegment(IndexType pntIdx) const
{
   PRECONDITION(pntIdx < 2);
   return m_SegmentIndex[pntIdx];
}

Float64 Widening::GetWidening(const Station& station, IndexType surfaceTemplateSegmentIndex) const
{
   if (m_SegmentIndex[0] != surfaceTemplateSegmentIndex && m_SegmentIndex[1] != surfaceTemplateSegmentIndex)
   {
      // the specified segment is not widened
      return 0.0;
   }

   auto alignment = GetAlignment();

   Float64 widening = 0;
   if (0 < COGO::CompareStations(alignment,station, m_BeginTransition) ||
      0 < COGO::CompareStations(alignment,m_EndTransition, station))
   {
      // station is not in the widening area
   }
   else if (0 <= COGO::CompareStations(alignment, m_BeginTransition, station) &&
       0 <= COGO::CompareStations(alignment, station, m_BeginFullWidening))
   {
      // In begin transition
      Float64 sta = COGO::ConvertToNormalizedStation(alignment,station);
      Float64 begin = COGO::ConvertToNormalizedStation(alignment, m_BeginTransition);
      Float64 full = COGO::ConvertToNormalizedStation(alignment, m_BeginFullWidening);
      if (IsEqual(begin, full))
      {
         widening = m_Widening;
      }
      else
      {
         widening  = ::LinInterp(sta - begin, 0.0, m_Widening, full - begin);
      }
   }
   else if (0 <= COGO::CompareStations(alignment, m_EndFullWidening, station) &&
            0 <= COGO::CompareStations(alignment, station, m_EndTransition))
   {
      // In end transition
      Float64 sta  = COGO::ConvertToNormalizedStation(alignment, station);
      Float64 full = COGO::ConvertToNormalizedStation(alignment, m_EndFullWidening);
      Float64 end  = COGO::ConvertToNormalizedStation(alignment, m_EndTransition);
      if (IsEqual(full, end))
      {
         widening = m_Widening;
      }
      else
      {
         widening = ::LinInterp(sta - full, m_Widening, 0.0, end - full);
      }
   }
   else
   {
      // In full widening
      widening = m_Widening;
   }

   return widening;
}

std::shared_ptr<const Alignment> Widening::GetAlignment() const
{
   auto surface = GetSurface();
   auto profile = (surface ? surface->GetProfile() : nullptr);
   auto alignment = (profile ? profile->GetAlignment() : nullptr);
   return alignment;
}
