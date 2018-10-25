///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
   bamSectionResults
****************************************************************************/

#include <BridgeAnalysis\SectionResults.h>        // class implementation

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bamSectionResultsKey::bamSectionResultsKey()
{
}

bamSectionResultsKey::bamSectionResultsKey(Int32 poi,Int32 loadingId) :
m_LoadingId( loadingId ),
m_Poi( poi )
{
}

bamSectionResultsKey::bamSectionResultsKey(const bamSectionResultsKey& rOther)
{
   MakeCopy(rOther);
}

bamSectionResultsKey::~bamSectionResultsKey()
{
}

//======================== OPERATORS  =======================================
bamSectionResultsKey& bamSectionResultsKey::operator= (const bamSectionResultsKey& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

bool bamSectionResultsKey::operator< (const bamSectionResultsKey& rOther) const
{
   if ( m_LoadingId < rOther.m_LoadingId )
      return true;

   if ( m_LoadingId > rOther.m_LoadingId )
      return false;

   if ( m_Poi < rOther.m_Poi )
      return true;

   return false;
}

bool bamSectionResultsKey::operator==(const bamSectionResultsKey& rOther) const
{
   return (m_LoadingId == rOther.m_LoadingId) && (m_Poi == rOther.m_Poi);
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void bamSectionResultsKey::LoadingId(Int32 loadingId)
{
   m_LoadingId = loadingId;
}

Int32 bamSectionResultsKey::LoadingId() const
{
   return m_LoadingId;
}

void bamSectionResultsKey::PointOfInterest(Int32 poi)
{
   m_Poi = poi;
}

Int32 bamSectionResultsKey::PointOfInterest() const
{
   return m_Poi;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamSectionResultsKey::MakeCopy(const bamSectionResultsKey& rOther)
{
   m_LoadingId = rOther.m_LoadingId;
   m_Poi = rOther.m_Poi;
}

void bamSectionResultsKey::MakeAssignment(const bamSectionResultsKey& rOther)
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
//bamSectionResults::bamSectionResults()
//{
//}
//
//bamSectionResults::bamSectionResults(const sysSectionValue& fx,
//                                   const sysSectionValue& fy,
//                                   const sysSectionValue& mz,
//                                   const sysSectionValue& dx,
//                                   const sysSectionValue& dy,
//                                   const sysSectionValue& rz) :
//m_Fx( fx ),
//m_Fy( fy ),
//m_Mz( mz ),
//m_Dx( dx ),
//m_Dy( dy ),
//m_Rz( rz )
//{
//}
//
//bamSectionResults::bamSectionResults(const bamSectionResults& rOther)
//{
//   MakeCopy(rOther);
//}
//
//bamSectionResults::~bamSectionResults()
//{
//}
//
////======================== OPERATORS  =======================================
//bamSectionResults& bamSectionResults::operator= (const bamSectionResults& rOther)
//{
//   if( this != &rOther )
//   {
//      MakeAssignment(rOther);
//   }
//
//   return *this;
//}
//
//bamSectionResults& bamSectionResults::operator+=(const bamSectionResults& rOther)
//{
//   m_Fx += rOther.m_Fx;
//   m_Fy += rOther.m_Fy;
//   m_Mz += rOther.m_Mz;
//   m_Dx += rOther.m_Dx;
//   m_Dy += rOther.m_Dy;
//   m_Rz += rOther.m_Rz;
//
//   return *this;
//}
//
//bamSectionResults& bamSectionResults::operator-=(const bamSectionResults& rOther)
//{
//   m_Fx -= rOther.m_Fx;
//   m_Fy -= rOther.m_Fy;
//   m_Mz -= rOther.m_Mz;
//   m_Dx -= rOther.m_Dx;
//   m_Dy -= rOther.m_Dy;
//   m_Rz -= rOther.m_Rz;
//
//   return *this;
//}
//
//bamSectionResults  bamSectionResults::operator-()
//{
//   return bamSectionResults( -m_Fx, -m_Fy, -m_Mz, -m_Dx, -m_Dy, -m_Rz );
//}
//
//bamSectionResults& bamSectionResults::operator*=(Float64 d)
//{
//   m_Fx *= d;
//   m_Fy *= d;
//   m_Mz *= d;
//   m_Dx *= d;
//   m_Dy *= d;
//   m_Rz *= d;
//
//   return *this;
//}
//
////======================== OPERATIONS =======================================
////======================== ACCESS     =======================================
//const sysSectionValue& bamSectionResults::Fx() const
//{
//   return m_Fx;
//}
//
//sysSectionValue& bamSectionResults::Fx()
//{
//   return m_Fx;
//}
//
//const sysSectionValue& bamSectionResults::Fy() const
//{
//   return m_Fy;
//}
//
//sysSectionValue& bamSectionResults::Fy()
//{
//   return m_Fy;
//}
//
//const sysSectionValue& bamSectionResults::Mz() const
//{
//   return m_Mz;
//}
//
//sysSectionValue& bamSectionResults::Mz()
//{
//   return m_Mz;
//}
//
//const sysSectionValue& bamSectionResults::Dx() const
//{
//   return m_Dx;
//}
//
//sysSectionValue& bamSectionResults::Dx()
//{
//   return m_Dx;
//}
//
//const sysSectionValue& bamSectionResults::Dy() const
//{
//   return m_Dy;
//}
//
//sysSectionValue& bamSectionResults::Dy()
//{
//   return m_Dy;
//}
//
//const sysSectionValue& bamSectionResults::Rz() const
//{
//   return m_Rz;
//}
//
//sysSectionValue& bamSectionResults::Rz()
//{
//   return m_Rz;
//}
//
////======================== INQUIRY    =======================================
//
//////////////////////////// PROTECTED  ///////////////////////////////////////
//
////======================== LIFECYCLE  =======================================
////======================== OPERATORS  =======================================
////======================== OPERATIONS =======================================
//void bamSectionResults::MakeCopy(const bamSectionResults& rOther)
//{
//   m_Fx = rOther.m_Fx;
//   m_Fy = rOther.m_Fy;
//   m_Mz = rOther.m_Mz;
//   m_Dx = rOther.m_Dx;
//   m_Dy = rOther.m_Dy;
//   m_Rz = rOther.m_Rz;
//}
//
//void bamSectionResults::MakeAssignment(const bamSectionResults& rOther)
//{
//   MakeCopy( rOther );
//}
//
////======================== ACCESS     =======================================
////======================== INQUIRY    =======================================
//
//////////////////////////// PRIVATE    ///////////////////////////////////////
//
////======================== LIFECYCLE  =======================================
////======================== OPERATORS  =======================================
////======================== OPERATIONS =======================================
////======================== ACCESS     =======================================
////======================== INQUERY    =======================================
//
//bamSectionResults operator+(const bamSectionResults& a,const bamSectionResults& b)
//{
//   return bamSectionResults( a.Fx() + b.Fx(),
//                            a.Fy() + b.Fy(),
//                            a.Mz() + b.Mz(),
//                            a.Dx() + b.Dx(),
//                            a.Dy() + b.Dy(),
//                            a.Rz() + b.Rz() );
//}
//
//bamSectionResults operator-(const bamSectionResults& a,const bamSectionResults& b)
//{
//   return bamSectionResults( a.Fx() - b.Fx(),
//                            a.Fy() - b.Fy(),
//                            a.Mz() - b.Mz(),
//                            a.Dx() - b.Dx(),
//                            a.Dy() - b.Dy(),
//                            a.Rz() - b.Rz() );
//}
//
//bamSectionResults operator*(Float64 d,const bamSectionResults& rhs)
//{
//   return bamSectionResults( d * rhs.Fx(),
//                            d * rhs.Fy(),
//                            d * rhs.Mz(),
//                            d * rhs.Dx(),
//                            d * rhs.Dy(),
//                            d * rhs.Rz());
//}
//
//bamSectionResults operator*(const bamSectionResults& lhs,Float64 d)
//{
//   return d * lhs;
//}
//
//bamSectionResults operator*(const sysSectionValue& lhs,const bamSectionResults& rhs)
//{
//   return bamSectionResults( lhs * rhs.Fx(),
//                            lhs * rhs.Fy(),
//                            lhs * rhs.Mz(),
//                            lhs * rhs.Dx(),
//                            lhs * rhs.Dy(),
//                            lhs * rhs.Rz());
//}
//
//bamSectionResults operator*(const bamSectionResults& lhs,const sysSectionValue& rhs)
//{
//   return rhs * lhs;
//}