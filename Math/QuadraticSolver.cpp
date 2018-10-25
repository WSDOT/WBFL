///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2017  Washington State Department of Transportation
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
#include <Math\QuadraticSolver.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   mathQuadraticSolver
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mathQuadraticSolver::mathQuadraticSolver(Float64 a,Float64 b,Float64 c)
{
   m_A = a;
   m_B = b;
   m_C = c;
}

mathQuadraticSolver::mathQuadraticSolver(const mathQuadraticSolver& rOther)
{
   MakeCopy(rOther);
}

mathQuadraticSolver::~mathQuadraticSolver()
{
}

//======================== OPERATORS  =======================================
mathQuadraticSolver& mathQuadraticSolver::operator= (const mathQuadraticSolver& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
int mathQuadraticSolver::Solve(Float64* x1, Float64* x2) const
{
   Float64 a = m_A;
   Float64 b = m_B;
   Float64 c = m_C;

   if ( IsZero( a ) )
   {
      // the function is linear
      if ( IsZero(b) )
      {
         // the function is a horizontal line
         return 0; // no roots
      }
      else
      {
         // the function is a sloped line
         *x1 = -c/b;
         return 1; // 1 root
      }
   }

   Float64 K = b*b - 4.0*a*c;
   
   if ( K < 0 )
      return 0;

   K = sqrt( K );

   *x1 = (-b + K) / (2*a);
   *x2 = (-b - K) / (2*a);

   return 2;
}

//======================== ACCESS     =======================================
void mathQuadraticSolver::SetA(Float64 a)
{
   m_A = a;
}

Float64 mathQuadraticSolver::GetA() const
{
   return m_A;
}

void mathQuadraticSolver::SetB(Float64 b)
{
   m_B = b;
}

Float64 mathQuadraticSolver::GetB() const
{
   return m_B;
}

void mathQuadraticSolver::SetC(Float64 c)
{
   m_C = c;
}

Float64 mathQuadraticSolver::GetC() const
{
   return m_C;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void mathQuadraticSolver::MakeCopy(const mathQuadraticSolver& rOther)
{
   m_A = rOther.m_A;
   m_B = rOther.m_B;
   m_C = rOther.m_C;
}

void mathQuadraticSolver::MakeAssignment(const mathQuadraticSolver& rOther)
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
bool mathQuadraticSolver::AssertValid() const
{
   // Objects of this class are always valid
   return true;
}

void mathQuadraticSolver::Dump(dbgDumpContext& os) const
{
   os << "Dump for mathQuadraticSolver" << endl;
   os << "m_A = " << m_A << endl;
   os << "m_B = " << m_B << endl;
   os << "m_C = " << m_C << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool mathQuadraticSolver::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("mathQuadraticSolver");

   mathQuadraticSolver solver( 10, 10, 10 );
   Float64 x1, x2;

   TRY_TESTME( solver.Solve( &x1, &x2 ) == 0 );

   solver.SetA( 1.0 );
   solver.SetB( 9.0 );
   solver.SetC( -2.0 );
   TRY_TESTME( solver.Solve( &x1, &x2 ) == 2 );
   TRY_TESTME( IsEqual( x1,  0.21699056605 ) );
   TRY_TESTME( IsEqual( x2, -9.21699056605 ) );

   solver.SetA( 1.0 );
   solver.SetB( 0 );
   solver.SetC( -25 );
   TRY_TESTME( solver.Solve( &x1, &x2 ) == 2 );
   TRY_TESTME( IsEqual( x1,  5.0 ) );
   TRY_TESTME( IsEqual( x2, -5.0 ) );

   solver.SetA( 0 );
   solver.SetB( 10 );
   solver.SetC( -25 );
   TRY_TESTME( solver.Solve( &x1, &x2 ) == 1 );
   TRY_TESTME( IsEqual( x1, 2.5 ) );

   TESTME_EPILOG("mathQuadraticSolver");
}
#endif // _UNITTEST
