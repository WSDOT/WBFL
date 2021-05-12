///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
// Copyright © 1999-2021  Washington State Department of Transportation
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

#include <Roark\RoarkLib.h>
#include <Roark\Roark.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

rkComposite::rkComposite() :
rkRoarkBeam(0,0,0)
{
}

rkComposite::rkComposite(const rkComposite& rOther) :
rkRoarkBeam(rOther)
{
   BeamContainer::const_iterator i;
   for ( i = rOther.m_Beams.begin(); i < rOther.m_Beams.end(); i++ )
   {
      m_Beams.push_back(std::shared_ptr<rkRoarkBeam>( (*i)->CreateClone() ) );
   }
}

void rkComposite::AddBeam(const rkRoarkBeam& beam)
{
   m_Beams.push_back(std::shared_ptr<rkRoarkBeam>( beam.CreateClone() ) );
   L = beam.GetL();
   EI = beam.GetEI();
}

CollectionIndexType rkComposite::GetBeamCount() const
{
   return m_Beams.size();
}

const rkRoarkBeam* rkComposite::GetBeam(CollectionIndexType index) const
{
   return m_Beams[index].get();
}

void rkComposite::RemoveAllBeams()
{
   m_Beams.clear();
}

rkRoarkBeam* rkComposite::CreateClone() const
{
   return new rkComposite( *this );
}

void rkComposite::GetReactions(Float64 *pRa,Float64* pRb) const
{
   *pRa = 0;
   *pRb = 0;
   BeamContainer::const_iterator i;
   for ( i = m_Beams.begin(); i < m_Beams.end(); i++ )
   {
      Float64 Ra, Rb;
      (*i)->GetReactions( &Ra, &Rb );
      *pRa += Ra;
      *pRb += Rb;
   }
}

void rkComposite::GetMoments(Float64* pMa,Float64* pMb) const
{
   *pMa = 0;
   *pMb = 0;
   BeamContainer::const_iterator i;
   for ( i = m_Beams.begin(); i < m_Beams.end(); i++ )
   {
      Float64 Ma, Mb;
      (*i)->GetMoments( &Ma, &Mb );
      *pMa += Ma;
      *pMb += Mb;
   }
}

void rkComposite::GetRotations(Float64* pra,Float64* prb) const
{
   *pra = 0;
   *prb = 0;
   BeamContainer::const_iterator i;
   for ( i = m_Beams.begin(); i < m_Beams.end(); i++ )
   {
      Float64 ra, rb;
      (*i)->GetRotations( &ra, &rb );
      *pra += ra;
      *prb += rb;
   }
}

void rkComposite::GetDeflections(Float64* pYa,Float64* pYb) const
{
   *pYa = 0;
   *pYb = 0;
   BeamContainer::const_iterator i;
   for ( i = m_Beams.begin(); i < m_Beams.end(); i++ )
   {
      Float64 Ya, Yb;
      (*i)->GetDeflections( &Ya, &Yb );
      *pYa += Ya;
      *pYb += Yb;
   }
}

sysSectionValue rkComposite::ComputeShear(Float64 x) const
{
   sysSectionValue V(0);
   BeamContainer::const_iterator i;
   for ( i = m_Beams.begin(); i < m_Beams.end(); i++ )
   {
      V += (*i)->ComputeShear(x);
   }

   return V;
}

sysSectionValue rkComposite::ComputeMoment(Float64 x) const
{
   sysSectionValue M(0);
   BeamContainer::const_iterator i;
   for ( i = m_Beams.begin(); i < m_Beams.end(); i++ )
   {
      M += (*i)->ComputeMoment(x);
   }
   
   return M;
}

Float64 rkComposite::ComputeRotation(Float64 x) const
{
   Float64 r = 0;
   BeamContainer::const_iterator i;
   for ( i = m_Beams.begin(); i < m_Beams.end(); i++ )
   {
      r += (*i)->ComputeRotation(x);
   }

   return r;
}

Float64 rkComposite::ComputeDeflection(Float64 x) const
{
   Float64 y = 0;
   BeamContainer::const_iterator i;
   for ( i = m_Beams.begin(); i < m_Beams.end(); i++ )
   {
      y += (*i)->ComputeDeflection(x);
   }

   return y;
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool rkComposite::AssertValid() const
{
   BeamContainer::const_iterator i;
   for ( i = m_Beams.begin(); i < m_Beams.end(); i++ )
   {
      if ( (*i)->AssertValid() == false )
         return false;
   }

   return true;
}

void rkComposite::Dump(dbgDumpContext& os) const
{
   os << "Dump for rkComposite" << endl;
   BeamContainer::const_iterator i;
   for ( i = m_Beams.begin(); i < m_Beams.end(); i++ )
   {
      (*i)->Dump(os);
      os << endl;
   }
}
#endif // _DEBUG

#if defined _UNITTEST
bool rkComposite::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("rkComposite");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for rkComposite");

   TESTME_EPILOG("Composite");
}
#endif // _UNITTEST
