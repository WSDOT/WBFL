///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2020  Washington State Department of Transportation
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

#include <Math\MathLib.h>
#include <Math\1dRange.h>
#include <limits>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   math1dRange
****************************************************************************/


math1dRange::BoundType intersect_bounds(math1dRange::BoundType b1, math1dRange::BoundType b2)
{
   return (b1!=b2)? math1dRange::Limit : b1;
}
math1dRange::BoundType union_bounds(math1dRange::BoundType b1, math1dRange::BoundType b2)
{
   return (b1!=b2)? math1dRange::Bound : b1;
}

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
math1dRange::math1dRange():
m_LeftLocation(0.0),
m_LeftBound(Limit),
m_RightLocation(0.0),
m_RightBound(Limit)
{
}

math1dRange::math1dRange(Float64 leftLocation, BoundType leftBound, Float64 rightLocation, BoundType rightBound):
m_LeftLocation(leftLocation),
m_LeftBound(leftBound),
m_RightLocation(rightLocation),
m_RightBound(rightBound)
{
}

math1dRange::math1dRange(const math1dRange& rOther)
{
   MakeCopy(rOther);
}

math1dRange::~math1dRange()
{
}

//======================== OPERATORS  =======================================
math1dRange& math1dRange::operator= (const math1dRange& rOther)
{
   ASSERTVALID;
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
bool math1dRange::IsInRange(Float64 value) const
{
   ASSERTVALID;
   if(value>m_LeftLocation && value<m_RightLocation)
      return true;

   if(value==m_LeftLocation && m_LeftBound==Bound)
      return true;

   if(value==m_RightLocation && m_RightBound==Bound)
      return true;

   return false;
}

bool math1dRange::IsNull() const
{
   ASSERTVALID;
   return m_LeftLocation==m_RightLocation &&
          m_LeftBound ==Limit &&
          m_RightBound==Limit;
}

void math1dRange::SetNull()
{
   m_LeftLocation=0.0;
   m_RightLocation=0.0;
   m_LeftBound=Limit;
   m_RightBound=Limit;
}

bool math1dRange::IsIntersection(const math1dRange& rOther) const
{
   ASSERTVALID;
   if (!(IsNull() || rOther.IsNull()))
      return m_LeftLocation        <= rOther.m_RightLocation && 
             rOther.m_LeftLocation <= m_RightLocation;
   else
      return false;
}

math1dRange math1dRange::Intersection(const math1dRange& rOther) const
{
   ASSERTVALID;
   math1dRange range;
   if (IsIntersection(rOther))
   {
      // left bound
      if (m_LeftLocation > rOther.m_LeftLocation)
      {
         range.m_LeftLocation  = m_LeftLocation;
         range.m_LeftBound     = m_LeftBound;
      }
      else if(m_LeftLocation<rOther.m_LeftLocation)
      {
         range.m_LeftLocation = rOther.m_LeftLocation;
         range.m_LeftBound    = rOther.m_LeftBound;
      }
      else
      {
         // edges match - Limit wins in a contention
         range.m_LeftLocation = rOther.m_LeftLocation;
         range.m_LeftBound    = intersect_bounds(m_LeftBound,rOther.m_LeftBound);
      }

      // Right bound
      if (m_RightLocation < rOther.m_RightLocation)
      {
         range.m_RightLocation  = m_RightLocation;
         range.m_RightBound     = m_RightBound;
      }
      else if(m_RightLocation > rOther.m_RightLocation)
      {
         range.m_RightLocation = rOther.m_RightLocation;
         range.m_RightBound    = rOther.m_RightBound;
      }
      else
      {
         range.m_RightLocation = rOther.m_RightLocation;
         range.m_RightBound    = intersect_bounds(m_RightBound,rOther.m_RightBound);
      }
   }

   return range;
}

math1dRange math1dRange::Union(const math1dRange& rOther) const
{
   ASSERTVALID;
   math1dRange range;
   // left bound
   if (m_LeftLocation < rOther.m_LeftLocation)
   {
      range.m_LeftLocation  = m_LeftLocation;
      range.m_LeftBound     = m_LeftBound;
   }
   else if (m_LeftLocation > rOther.m_LeftLocation)
   {
      range.m_LeftLocation = rOther.m_LeftLocation;
      range.m_LeftBound    = rOther.m_LeftBound;
   }
   else
   {
      // edges match - Limit wins in a contention
      range.m_LeftLocation = rOther.m_LeftLocation;
      range.m_LeftBound    = union_bounds(m_LeftBound,rOther.m_LeftBound);
   }

   // right bound
   if (m_RightLocation > rOther.m_RightLocation)
   {
      range.m_RightLocation  = m_RightLocation;
      range.m_RightBound     = m_RightBound;
   }
   else if (m_RightLocation < rOther.m_RightLocation)
   {
      range.m_RightLocation = rOther.m_RightLocation;
      range.m_RightBound    = rOther.m_RightBound;
   }
   else
   {
      // edges match - Limit wins in a contention
      range.m_RightLocation = rOther.m_RightLocation;
      range.m_RightBound    = union_bounds(m_RightBound,rOther.m_RightBound);
   }

   return range;
}

void math1dRange::Set(Float64 leftLocation, BoundType leftBound, Float64 rightLocation, BoundType rightBound)
{
   m_LeftLocation  = leftLocation;
   m_LeftBound     = leftBound;
   m_RightLocation = rightLocation;
   m_RightBound    = rightBound;
   ASSERTVALID;
}

Float64 math1dRange::GetLeftBoundLocation() const
{
   ASSERTVALID;
   return m_LeftLocation;
}

void math1dRange::SetLeftBoundLocation(Float64 bound)
{
   m_LeftLocation = bound;
}

math1dRange::BoundType math1dRange::GetLeftBoundType() const
{
   ASSERTVALID;
   return m_LeftBound;
}

void math1dRange::SetLeftBoundType(math1dRange::BoundType type)
{
   m_LeftBound = type;
}

Float64 math1dRange::GetRightBoundLocation() const
{
   ASSERTVALID;
   return m_RightLocation;
}

void math1dRange::SetRightBoundLocation(Float64 bound)
{
   m_RightLocation = bound;
}

math1dRange::BoundType math1dRange::GetRightBoundType() const
{
   ASSERTVALID;
   return m_RightBound;
}

void math1dRange::SetRightBoundType(math1dRange::BoundType type)
{
   m_RightBound = type;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void math1dRange::MakeCopy(const math1dRange& rOther)
{
   m_LeftLocation  = rOther.m_LeftLocation;
   m_LeftBound     = rOther.m_LeftBound;
   m_RightLocation = rOther.m_RightLocation;
   m_RightBound    = rOther.m_RightBound;
}

void math1dRange::MakeAssignment(const math1dRange& rOther)
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

//======================== DEBUG      =======================================
#if defined _DEBUG
bool math1dRange::AssertValid() const
{
   if (m_LeftLocation>m_RightLocation)
      return false;

   return true;
}

void math1dRange::Dump(dbgDumpContext& os) const
{
   os << "Dump for math1dRange" << endl;
   os << "m_LeftLocation:  " << m_LeftLocation << endl;
   os << "m_LeftBound:     " <<m_LeftBound << endl;
   os << "m_RightLocation: " <<m_RightLocation << endl;
   os << "m_RightBound:    " <<m_RightBound << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool math1dRange::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("math1dRange");
   math1dRange r1;
   TRY_TESTME(r1.IsNull());
   r1.Set(10,math1dRange::Bound, 150, math1dRange::Bound);
   math1dRange r2(-220,math1dRange::Bound, 100, math1dRange::Limit);
   math1dRange r3 = r1.Intersection(r2);
   math1dRange r4 = r2.Intersection(r1);
   TRY_TESTME(r3==r4);
   math1dRange r5;
   r5.SetLeftBoundLocation(10);
   r5.SetRightBoundLocation(100);
   r5.SetLeftBoundType(math1dRange::Bound);
   r5.SetRightBoundType(math1dRange::Limit);
   TRY_TESTME(r5==r4);
   r4 = r2.Union(r1);
   r5.SetLeftBoundLocation(-220);
   r5.SetRightBoundLocation(150);
   r5.SetLeftBoundType(math1dRange::Bound);
   r5.SetRightBoundType(math1dRange::Bound);
   TRY_TESTME(r5==r4);
   TRY_TESTME(r5.GetLeftBoundLocation()==-220);
   TRY_TESTME(r5.GetRightBoundLocation()==150);
   TRY_TESTME(r5.GetLeftBoundType()==math1dRange::Bound);
   TRY_TESTME(r5.GetRightBoundType()==math1dRange::Bound);
   r5.SetNull();
   TRY_TESTME(r5.IsNull());

   TESTME_EPILOG("1dRange");
}
#endif // _UNITTEST

bool operator==(const math1dRange& lhs, const math1dRange& rhs)
{
   return lhs.m_LeftLocation  == rhs.m_LeftLocation &&
          lhs.m_LeftBound     == rhs.m_LeftBound &&
          lhs.m_RightLocation == rhs.m_RightLocation &&
          lhs.m_RightBound    == rhs.m_RightBound;
}

