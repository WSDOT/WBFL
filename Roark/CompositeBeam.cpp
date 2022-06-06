///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Beams;

CompositeBeam::CompositeBeam() :
RoarkBeam(1,1)
{
}

void CompositeBeam::AddBeam(const RoarkBeam& beam)
{
   AddBeam(beam.CreateClone());
}

void CompositeBeam::AddBeam(std::unique_ptr<RoarkBeam>&& beam)
{
   PRECONDITION(IsEqual(GetL(), beam->GetL()));
   PRECONDITION(IsEqual(GetEI(), beam->GetEI()));
   m_Beams.emplace_back(std::move(beam));
}

CollectionIndexType CompositeBeam::GetBeamCount() const
{
   return m_Beams.size();
}

const std::unique_ptr<RoarkBeam>& CompositeBeam::GetBeam(CollectionIndexType index) const
{
   return m_Beams[index];
}

void CompositeBeam::RemoveAllBeams()
{
   m_Beams.clear();
}

std::unique_ptr<RoarkBeam> CompositeBeam::CreateClone() const
{
   std::unique_ptr<CompositeBeam> clone(std::make_unique<CompositeBeam>());
   clone->SetL(GetL());
   clone->SetEI(GetEI());
   for (auto& beam : m_Beams)
   {
      clone->AddBeam(beam->CreateClone());
   }
   return clone;
}

void CompositeBeam::GetReactions(Float64 *pRa,Float64* pRb) const
{
   *pRa = 0;
   *pRb = 0;
   for(const auto& beam : m_Beams)
   {
      Float64 Ra, Rb;
      beam->GetReactions( &Ra, &Rb );
      *pRa += Ra;
      *pRb += Rb;
   }
}

void CompositeBeam::GetMoments(Float64* pMa,Float64* pMb) const
{
   *pMa = 0;
   *pMb = 0;
   for(const auto& beam : m_Beams)
   {
      Float64 Ma, Mb;
      beam->GetMoments( &Ma, &Mb );
      *pMa += Ma;
      *pMb += Mb;
   }
}

void CompositeBeam::GetRotations(Float64* pra,Float64* prb) const
{
   *pra = 0;
   *prb = 0;
   for(const auto& beam : m_Beams)
   {
      Float64 ra, rb;
      beam->GetRotations( &ra, &rb );
      *pra += ra;
      *prb += rb;
   }
}

void CompositeBeam::GetDeflections(Float64* pYa,Float64* pYb) const
{
   *pYa = 0;
   *pYb = 0;
   for(const auto& beam : m_Beams)
   {
      Float64 Ya, Yb;
      beam->GetDeflections( &Ya, &Yb );
      *pYa += Ya;
      *pYb += Yb;
   }
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
   for(const auto& beam : m_Beams)
   {
      y += beam->ComputeDeflection(x);
   }

   return y;
}

#if defined _DEBUG
bool CompositeBeam::AssertValid() const
{
   for(const auto& beam : m_Beams)
   {
      if ( beam->AssertValid() == false )
         return false;
   }

   return true;
}

void CompositeBeam::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for CompositeBeam" << WBFL::Debug::endl;
   for(const auto& beam : m_Beams)
   {
      beam->Dump(os);
      os << WBFL::Debug::endl;
   }
}
#endif // _DEBUG

#if defined _UNITTEST
bool CompositeBeam::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompositeBeam");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for CompositeBeam");

   TESTME_EPILOG("Composite");
}
#endif // _UNITTEST
