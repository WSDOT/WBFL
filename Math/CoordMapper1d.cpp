///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2012  Washington State Department of Transportation
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
#include <Math\CoordMapper1d.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   mathCoordMapper1d
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mathCoordMapper1d::mathCoordMapper1d()
{
   // no scale difference, no offset
   m_c = 1;
   m_d = 0;
}

mathCoordMapper1d::mathCoordMapper1d(Float64 d, bool IsSameDirection)
{
  SetMapSameScale(d, IsSameDirection);
}

mathCoordMapper1d::mathCoordMapper1d(Float64 a1, Float64 b1, Float64 a2, Float64 b2)
{
  SetCoordinateMap(a1, b1, a2, b2);
}

mathCoordMapper1d::mathCoordMapper1d(const mathCoordMapper1d& rOther)
{
   MakeCopy(rOther);
}

mathCoordMapper1d::~mathCoordMapper1d()
{
}

//======================== OPERATORS  =======================================
mathCoordMapper1d& mathCoordMapper1d::operator= (const mathCoordMapper1d& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

Float64 mathCoordMapper1d::GetA( Float64 B) const
{
   return B * m_c + m_d;
}

Float64 mathCoordMapper1d::GetB( Float64 A) const
{
   return (A-m_d)/m_c;
}

void mathCoordMapper1d::SetCoordinateMap(Float64 a1, Float64 b1, Float64 a2, Float64 b2)
{
   PRECONDITIONX( !IsEqual(a1,a2,1.0e-16), _T("a1 cannot equal a2") );

   // set up mapping equation: A = B * m_c + m_d

   // Don't allow divide by zero no matter what
   if (!IsEqual(b1,b2,1.0e-16))
   {
      m_c = (a2 - a1) / (b2 - b1);
   }
   else
   {
      PRECONDITIONX( false, _T("b1 cannot equal b2") );
      m_c = 1; // same default as in constructor
   }

   m_d = a1 - b1 * m_c;
}

void mathCoordMapper1d::SetMapSameScale(Float64 d, bool bIsSameDirection)
{
   // logic is bizarre here, but it works

   m_d = d;

   if (bIsSameDirection)
      m_c = 1;
   else
      m_c = -1;
}



//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void mathCoordMapper1d::MakeCopy(const mathCoordMapper1d& rOther)
{
   m_c = rOther.m_c;
   m_d = rOther.m_d;
}

void mathCoordMapper1d::MakeAssignment(const mathCoordMapper1d& rOther)
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

#if defined _DEBUG
bool mathCoordMapper1d::AssertValid() const
{
   return true;
}

void mathCoordMapper1d::Dump(dbgDumpContext& os) const
{
   os << _T("Dump for mathCoordMapper1d not implemented") << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool mathCoordMapper1d::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("mathCoordMapper1d");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for mathCoordMapper1d");
   TESTME_EPILOG("mathCoordMapper1d");
}
#endif
