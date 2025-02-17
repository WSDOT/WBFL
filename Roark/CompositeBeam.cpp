///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam formula, patterned after Roark's formulas
//         for Stress and Strain
// Copyright � 1999-2025  Washington State Department of Transportation
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
#include <Roark/CompositeBeam.h>

using namespace WBFL::Beams;

CompositeBeam::CompositeBeam(Float64 length, Float64 ei) :
RoarkBeam(length,ei)
{
}

void CompositeBeam::AddBeam(const RoarkBeam& beam)
{
   AddBeam(beam.CreateClone());
}

void CompositeBeam::AddBeam(std::shared_ptr<RoarkBeam> beam)
{
   PRECONDITION(IsEqual(GetL(), beam->GetL()));
   PRECONDITION(IsEqual(GetEI(), beam->GetEI()));
   m_Beams.emplace_back(beam);
}

IndexType CompositeBeam::GetBeamCount() const
{
   return m_Beams.size();
}

std::shared_ptr<const RoarkBeam> CompositeBeam::GetBeam(IndexType index) const
{
   return m_Beams[index];
}

void CompositeBeam::RemoveAllBeams()
{
   m_Beams.clear();
}

std::shared_ptr<RoarkBeam> CompositeBeam::CreateClone() const
{
   std::shared_ptr<CompositeBeam> clone(std::make_shared<CompositeBeam>(GetL(),GetEI()));
   for (auto& beam : m_Beams)
   {
      clone->AddBeam(beam->CreateClone());
   }
   return clone;
}

std::pair<Float64, Float64> CompositeBeam::GetReactions() const
{
   Float64 Ra = 0;
   Float64 Rb = 0;
   for(const auto& beam : m_Beams)
   {
      auto [ra,rb] = beam->GetReactions();
      Ra += ra;
      Rb += rb;
   }
   return std::make_pair(Ra, Rb);
}


std::pair<Float64, Float64> CompositeBeam::GetMoments() const
{
   Float64 Ma = 0;
   Float64 Mb = 0;
   for(const auto& beam : m_Beams)
   {
      auto [ma,mb] = beam->GetMoments();
      Ma += ma;
      Mb += mb;
   }
   return std::make_pair(Ma, Mb);
}

std::pair<Float64, Float64> CompositeBeam::GetRotations() const
{
   Float64 ra = 0;
   Float64 rb = 0;
   for(const auto& beam : m_Beams)
   {
      auto [_ra,_rb] = beam->GetRotations();
      ra += _ra;
      rb += _rb;
   }
   return std::make_pair(ra, rb);
}

std::pair<Float64, Float64> CompositeBeam::GetDeflections() const
{
   Float64 Ya = 0;
   Float64 Yb = 0;
   for(const auto& beam : m_Beams)
   {
      auto [ya,yb] = beam->GetDeflections();
      Ya += ya;
      Yb += yb;
   }
   return std::make_pair(Ya, Yb);
}

WBFL::System::SectionValue CompositeBeam::ComputeShear(Float64 x) const
{
   WBFL::System::SectionValue V(0);
   for(const auto& beam : m_Beams)
   {
      V += beam->ComputeShear(x);
   }

   return V;
}

WBFL::System::SectionValue CompositeBeam::ComputeMoment(Float64 x) const
{
   WBFL::System::SectionValue M(0);
   for(const auto& beam : m_Beams)
   {
      M += beam->ComputeMoment(x);
   }
   
   return M;
}

Float64 CompositeBeam::ComputeRotation(Float64 x) const
{
   Float64 r = 0;
   for(const auto& beam : m_Beams)
   {
      r += beam->ComputeRotation(x);
   }

   return r;
}

Float64 CompositeBeam::ComputeDeflection(Float64 x) const
{
   Float64 y = 0;
   for (const auto& beam : m_Beams)
   {
      y += beam->ComputeDeflection(x);
   }

   return y;
}