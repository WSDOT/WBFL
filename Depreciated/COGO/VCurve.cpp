///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <Cogo\CogoLib.h>

/****************************************************************************
CLASS
   cogoVCurve
****************************************************************************/

#include <Cogo\VCurve.h>
#include <MathEx.h>

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
cogoVCurve::cogoVCurve()
{
}

cogoVCurve::cogoVCurve(const gpPoint2d& bvc,const gpPoint2d& pvi,const gpPoint2d& evc)
{
   m_BVC = bvc;
   m_PVI = pvi;
   m_EVC = evc;
}

cogoVCurve::cogoVCurve(const cogoVCurve& rOther)
{
   MakeCopy(rOther);
}

cogoVCurve::~cogoVCurve()
{
}

//======================== OPERATORS  =======================================
cogoVCurve& cogoVCurve::operator= (const cogoVCurve& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
void cogoVCurve::SetBVC(const gpPoint2d& bvc)
{
   m_BVC = bvc;
}

gpPoint2d cogoVCurve::GetBVC() const
{
   return m_BVC;
}

void cogoVCurve::SetPVI(const gpPoint2d& pvi)
{
   m_PVI = pvi;
}

gpPoint2d cogoVCurve::GetPVI() const
{
   return m_PVI;
}

void cogoVCurve::SetEVC(const gpPoint2d& evc)
{
   m_EVC = evc;
}

gpPoint2d cogoVCurve::GetEVC() const
{
   return m_EVC;
}

Float64 cogoVCurve::GetLength() const
{
   return m_EVC.X() - m_BVC.X();
}

Float64 cogoVCurve::GetG1() const
{
   Float64 g;
   g = (m_PVI.Y() - m_BVC.Y())/(m_PVI.X() - m_BVC.X());
   return g;
}

Float64 cogoVCurve::GetG2() const
{
   Float64 g;
   g = (m_EVC.Y() - m_PVI.Y())/(m_EVC.X() - m_PVI.X());
   return g;
}

Float64 cogoVCurve::GetGrade(Float64 station) const
{
   Float64 g1 = GetG1();
   Float64 g2 = GetG2();
   Float64 A = g2 - g1;
   Float64 L = GetLength();
   Float64 g = g1 + A*(station - m_BVC.X())/L;
   return g;
}

gpPoint2d cogoVCurve::GetHighPoint() const
{
   gpPoint2d exp = MinMaxPoint();

   // Test end points
   if ( exp.Y() > m_BVC.Y() && exp.Y() > m_EVC.Y() )
      return exp; // computed point is truly the high point

   // At least one end is higher than the computed point.
   // Return higher end point.

   if ( m_BVC.Y() > m_EVC.Y() )
      return m_BVC;

   return m_EVC;
}

gpPoint2d cogoVCurve::GetLowPoint() const
{
   gpPoint2d exp = MinMaxPoint();

   // Test end points
   if ( exp.Y() < m_BVC.Y() && exp.Y() < m_EVC.Y() )
      return exp; // computed point is truly the low point

   // At least one end is lower than the computed point.
   // Return lower end point.

   if ( m_BVC.Y() < m_EVC.Y() )
      return m_BVC;

   return m_EVC;
}

Float64 cogoVCurve::GetElevation(Float64 station) const
{
   Float64 g1 = GetG1();
   Float64 g2 = GetG2();
   Float64 A = g2 - g1;
   Float64 L = GetLength();
   Float64 x = station - m_BVC.X();
   Float64 ha = m_BVC.Y();

   Float64 y = A*x*x/(2*L) + g1*x + ha;

   return y;
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void cogoVCurve::MakeCopy(const cogoVCurve& rOther)
{
   m_BVC = rOther.m_BVC;
   m_PVI = rOther.m_PVI;
   m_EVC = rOther.m_EVC;
}

void cogoVCurve::MakeAssignment(const cogoVCurve& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
gpPoint2d cogoVCurve::MinMaxPoint() const
{
   Float64 g1 = GetG1();
   Float64 g2 = GetG2();
   Float64 A = g2 - g1;
   Float64 L = GetLength();
   Float64 x = g1*L/A;
   Float64 y = GetElevation(m_BVC.X() + x );
   return gpPoint2d(x,y);
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool cogoVCurve::AssertValid() const
{
   return true;
}

void cogoVCurve::Dump(dbgDumpContext& os) const
{
   os << "Dump for cogoVCurve - Not Implemented" << endl;
   os << "BVC" << endl;
   m_BVC.Dump(os);
   os << "PVI" << endl;
   m_PVI.Dump(os);
   os << "EVC" << endl;
   m_EVC.Dump(os);
}
#endif // _DEBUG

#if defined _UNITTEST
bool cogoVCurve::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("cogoVCurve");
#pragma Reminder("Implement Unit Tests")
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for cogoVCurve");
   TESTME_EPILOG("cogoVCurve");
}
#endif