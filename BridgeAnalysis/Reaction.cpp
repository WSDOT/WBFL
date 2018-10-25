///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2015  Washington State Department of Transportation
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
   bamReaction
****************************************************************************/

#include <BridgeAnalysis\Reaction.h>        // class implementation

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//======================== LIFECYCLE  =======================================
bamReactionKey::bamReactionKey()
{
   m_SupportId = -1;
   m_LoadingId = -1;
}

bamReactionKey::bamReactionKey(SupportIDType supportId,IDType loadingId) :
m_SupportId(supportId),m_LoadingId(loadingId)
{
}

bamReactionKey::bamReactionKey(const bamReactionKey& rOther)
{
   MakeCopy(rOther);
}

bamReactionKey::~bamReactionKey()
{
}

//======================== OPERATORS  =======================================
bamReactionKey& bamReactionKey::operator= (const bamReactionKey& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

bool bamReactionKey::operator< (const bamReactionKey& rOther) const
{
   if ( m_SupportId < rOther.SupportId() )
      return true;

   if ( m_SupportId > rOther.SupportId() )
      return false;

   if ( m_LoadingId < rOther.LoadingId() )
      return true;

   return false;
}

bool bamReactionKey::operator==(const bamReactionKey& rOther) const
{
   return (m_SupportId == rOther.SupportId()) && (m_LoadingId == rOther.LoadingId() );
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
void bamReactionKey::SupportId(SupportIDType supportId)
{
   m_SupportId = supportId;
}

SupportIDType bamReactionKey::SupportId() const
{
   return m_SupportId;
}

void bamReactionKey::LoadingId(IDType loadingId)
{
   m_LoadingId = loadingId;
}

IDType bamReactionKey::LoadingId() const
{
   return m_LoadingId;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamReactionKey::MakeCopy(const bamReactionKey& rOther)
{
   m_SupportId = rOther.SupportId();
   m_LoadingId = rOther.LoadingId();
}

void bamReactionKey::MakeAssignment(const bamReactionKey& rOther)
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
bamReaction::bamReaction() :
m_Fx(0),m_Fy(0),m_Mz(0),m_Dx(0),m_Dy(0),m_Rz(0)
{
}

bamReaction::bamReaction(Float64 fx,Float64 fy,Float64 mz,Float64 dx,Float64 dy,Float64 rz) :
m_Fx(fx),m_Fy(fy),m_Mz(mz),m_Dx(dx),m_Dy(dy),m_Rz(rz)
{
}

bamReaction::bamReaction(const bamReaction& rOther)
{
   MakeCopy(rOther);
}

bamReaction::~bamReaction()
{
}

//======================== OPERATORS  =======================================
bamReaction& bamReaction::operator= (const bamReaction& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

bamReaction& bamReaction::operator+= (const bamReaction& rOther)
{
   m_Fx += rOther.Fx();
   m_Fy += rOther.Fy();
   m_Mz += rOther.Mz();
   m_Dx += rOther.Dx();
   m_Dy += rOther.Dy();
   m_Rz += rOther.Rz();

   return *this;
}

bamReaction& bamReaction::operator-= (const bamReaction& rOther)
{
   m_Fx -= rOther.Fx();
   m_Fy -= rOther.Fy();
   m_Mz -= rOther.Mz();
   m_Dx -= rOther.Dx();
   m_Dy -= rOther.Dy();
   m_Rz -= rOther.Rz();

   return *this;
} 

bamReaction& bamReaction::operator*= (Float64 d)
{
   m_Fx *= d;
   m_Fy *= d;
   m_Mz *= d;
   m_Dx *= d;
   m_Dy *= d;
   m_Rz *= d;

   return *this;
}

bamReaction& bamReaction::operator/= (Float64 d)
{
   m_Fx /= d;
   m_Fy /= d;
   m_Mz /= d;
   m_Dx /= d;
   m_Dy /= d;
   m_Rz /= d;

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
const Float64& bamReaction::Fx() const
{
   return m_Fx;
}

Float64& bamReaction::Fx()
{
   return m_Fx;
}

const Float64& bamReaction::Fy() const
{
   return m_Fy;
}

Float64& bamReaction::Fy()
{
   return m_Fy;
}

const Float64& bamReaction::Mz() const
{
   return m_Mz;
}

Float64& bamReaction::Mz()
{
   return m_Mz;
}

const Float64& bamReaction::Dx() const
{
   return m_Dx;
}

Float64& bamReaction::Dx()
{
   return m_Dx;
}

const Float64& bamReaction::Dy() const
{
   return m_Dy;
}

Float64& bamReaction::Dy()
{
   return m_Dy;
}

const Float64& bamReaction::Rz() const
{
   return m_Rz;
}

Float64& bamReaction::Rz()
{
   return m_Rz;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bamReaction::MakeCopy(const bamReaction& rOther)
{
   m_Fx = rOther.m_Fx;
   m_Fy = rOther.m_Fy;
   m_Mz = rOther.m_Mz;
   m_Dx = rOther.m_Dx;
   m_Dy = rOther.m_Dy;
   m_Rz = rOther.m_Rz;
}

void bamReaction::MakeAssignment(const bamReaction& rOther)
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

bamReaction operator+(const bamReaction& lhs,const bamReaction& rhs)
{
   return bamReaction( lhs.Fx() + rhs.Fx(),
                      lhs.Fy() + rhs.Fy(),
                      lhs.Mz() + rhs.Mz(),
                      lhs.Dx() + rhs.Dx(),
                      lhs.Dy() + rhs.Dy(),
                      lhs.Rz() + rhs.Rz() );
}

bamReaction operator-(const bamReaction& lhs,const bamReaction& rhs)
{
   return bamReaction( lhs.Fx() - rhs.Fx(),
                      lhs.Fy() - rhs.Fy(),
                      lhs.Mz() - rhs.Mz(),
                      lhs.Dx() - rhs.Dx(),
                      lhs.Dy() - rhs.Dy(),
                      lhs.Rz() - rhs.Rz() );
}

bamReaction operator*(const bamReaction& lhs,Float64 d)
{
   return bamReaction( lhs.Fx() * d,
                      lhs.Fy() * d,
                      lhs.Mz() * d,
                      lhs.Dx() * d,
                      lhs.Dy() * d,
                      lhs.Rz() * d );
}

bamReaction operator*(Float64 d,const bamReaction& rhs)
{
   return rhs * d;
}
