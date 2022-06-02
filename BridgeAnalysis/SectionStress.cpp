///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
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

#include <BridgeAnalysis\BridgeAnalysisLib.h>
/****************************************************************************
CLASS
   bamSectionStress
****************************************************************************/

#include <BridgeAnalysis\SectionStress.h>        // class implementation

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bamSectionStressKey::bamSectionStressKey()
{
}

bamSectionStressKey::bamSectionStressKey(PoiIDType poi,CollectionIndexType idx,IDType loadingId) :
m_LoadingId( loadingId ),
m_StressPointIdx( idx ),
m_Poi( poi )
{
}

bamSectionStressKey::bamSectionStressKey(const bamSectionStressKey& rOther)
{
   MakeCopy(rOther);
}

bamSectionStressKey::~bamSectionStressKey()
{
}

//======================== OPERATORS  =======================================
bamSectionStressKey& bamSectionStressKey::operator= (const bamSectionStressKey& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

bool bamSectionStressKey::operator< (const bamSectionStressKey& rOther) const
{
   if ( m_LoadingId < rOther.m_LoadingId )
      return true;

   if ( m_LoadingId > rOther.m_LoadingId )
      return false;

   if ( m_Poi < rOther.m_Poi )
      return true;

   if ( m_Poi > rOther.m_Poi )
      return false;

   if ( m_StressPointIdx < rOther.m_StressPointIdx )
      return true;

   return false;
}

bool bamSectionStressKey::operator==(const bamSectionStressKey& rOther) const
{
   return (m_LoadingId == rOther.m_LoadingId) && (m_Poi == rOther.m_Poi) && (m_StressPointIdx == rOther.m_StressPointIdx);
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void bamSectionStressKey::LoadingId(IDType loadingId)
{
   m_LoadingId = loadingId;
}

IDType bamSectionStressKey::LoadingId() const
{
   return m_LoadingId;
}

void bamSectionStressKey::StressPointIdx(IndexType idx)
{
   m_StressPointIdx = idx;
}

IndexType bamSectionStressKey::StressPointIdx() const
{
   return m_StressPointIdx;
}

void bamSectionStressKey::PointOfInterest(IDType poi)
{
   m_Poi = poi;
}

IDType bamSectionStressKey::PointOfInterest() const
{
   return m_Poi;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamSectionStressKey::MakeCopy(const bamSectionStressKey& rOther)
{
   m_LoadingId = rOther.m_LoadingId;
   m_Poi = rOther.m_Poi;
   m_StressPointIdx = rOther.m_StressPointIdx;
}

void bamSectionStressKey::MakeAssignment(const bamSectionStressKey& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////// PUBLIC     ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//======================== LIFECYCLE  =======================================
bamSectionStress::bamSectionStress()
{
}

bamSectionStress::bamSectionStress(const sysSectionValue& f) :
m_f( f )
{
}

bamSectionStress::bamSectionStress(const bamSectionStress& rOther)
{
   MakeCopy(rOther);
}

bamSectionStress::~bamSectionStress()
{
}

//======================== OPERATORS  =======================================
bamSectionStress& bamSectionStress::operator= (const bamSectionStress& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

bamSectionStress& bamSectionStress::operator+=(const bamSectionStress& rOther)
{
   m_f += rOther.m_f;

   return *this;
}

bamSectionStress& bamSectionStress::operator-=(const bamSectionStress& rOther)
{
   m_f -= rOther.m_f;

   return *this;
}

bamSectionStress  bamSectionStress::operator-()
{
   return bamSectionStress( -m_f );
}

bamSectionStress& bamSectionStress::operator*=(Float64 d)
{
   m_f *= d;

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
const sysSectionValue& bamSectionStress::F() const
{
   return m_f;
}

sysSectionValue& bamSectionStress::F()
{
   return m_f;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamSectionStress::MakeCopy(const bamSectionStress& rOther)
{
   m_f = rOther.m_f;
}

void bamSectionStress::MakeAssignment(const bamSectionStress& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

bamSectionStress operator+(const bamSectionStress& a,const bamSectionStress& b)
{
   return bamSectionStress( a.F() + b.F() );
}

bamSectionStress operator-(const bamSectionStress& a,const bamSectionStress& b)
{
   return bamSectionStress( a.F() - b.F() );
}

bamSectionStress operator*(Float64 d,const bamSectionStress& rhs)
{
   return bamSectionStress( sysSectionValue(d * rhs.F().Left(), d * rhs.F().Right() ) );
}

bamSectionStress operator*(const bamSectionStress& lhs,Float64 d)
{
   return d * lhs;
}

bamSectionStress operator*(const sysSectionValue& lhs,const bamSectionStress& rhs)
{
   return bamSectionStress( lhs * rhs.F() );
}

bamSectionStress operator*(const bamSectionStress& lhs,const sysSectionValue& rhs)
{
   return rhs * lhs;
}