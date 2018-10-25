///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2016  Washington State Department of Transportation
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
#include <Math\CubicSolver.h>
#include <Math\QuadraticSolver.h>
#include <algorithm>
#include <functional>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   mathCubicSolver
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mathCubicSolver::mathCubicSolver(Float64 a,Float64 b,Float64 c,Float64 d)
{
   m_A = a;
   m_B = b;
   m_C = c;
   m_D = d;
}

mathCubicSolver::mathCubicSolver(const mathCubicSolver& rOther)
{
   MakeCopy(rOther);
}

mathCubicSolver::~mathCubicSolver()
{
}

//======================== OPERATORS  =======================================
mathCubicSolver& mathCubicSolver::operator= (const mathCubicSolver& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
int mathCubicSolver::Solve(Float64* pX1, Float64* pX2,Float64* pX3) const
{
   Float64 a = m_A;
   Float64 b = m_B;
   Float64 c = m_C;
   Float64 d = m_D;

   Float64 X[3];
   X[0] = DBL_MAX;
   X[1] = DBL_MAX;
   X[2] = DBL_MAX;

   int nRoots = 0;

   if ( a == 0 )
   {
      // function is a quadratic
      mathQuadraticSolver solver(b,c,d);
      nRoots = solver.Solve(&X[0],&X[1]);
   }
   else  if ( d == 0 )
   {
      // one of the roots is zero. divide through by x and solve the quadratic
      mathQuadraticSolver solver(a,b,c);

      nRoots = solver.Solve(&X[0],&X[1]);
      X[nRoots++] = 0;
   }
   else
   {
      // I don't have a very good reference for this algorithm. It was 
      // taken from http://www.1728.com/cubic2.htm
      Float64 f = (3*c/a - (b*b)/(a*a))/3;
      Float64 g = (2*b*b*b/(a*a*a) - (9*b*c/(a*a)) + (27*d/a))/27;
      Float64 h = g*g/4 + f*f*f/27;

      if ( IsZero(h) || h < 0 )
      {
         if ( IsZero(h) && IsZero(f) && IsZero(g) )
         {
            // all roots are real and equal
            X[0] = -(d/a < 0 ? -pow(-d/a,1./3.) : pow(d/a,1./3.));
            X[1] = X[0];
            X[2] = X[0];
            nRoots = 1; // only one unique root
         }
         else
         {
            // roots are real
            Float64 i = sqrt( (g*g)/4 - h );
            Float64 j = pow(i,1./3.);
            Float64 k = acos( -(g/(2*i)) );
            Float64 l = -j;
            Float64 m = cos(k/3);
            Float64 n = sqrt(3.)*sin(k/3);
            Float64 p = -b/(3*a);
            X[0] = 2*j*cos(k/3) + p;
            X[1] = l*(m+n) + p;
            X[2] = l*(m-n) + p;

            // if h = 0, then two of the roots are the same
            if ( IsZero(h) )
            {
               // 2 roots are the same, eliminate the redundant root
               if ( IsEqual(X[0],X[1]) )
               {
                  X[1] = X[2];
                  X[2] = DBL_MAX;
               }
               else if ( IsEqual(X[1],X[2]) )
               {
                  X[2] = DBL_MAX;
               }
               nRoots = 2;
            }
            else
            {
               nRoots = 3;
            }
         }
      }
      else /*if ( 0 < h )*/
      {
         // only 1 real root
         assert(0 < h);
         Float64 r = -g/2 + sqrt(h);
         Float64 s = (r < 0 ? -pow(-r,1./3.) : pow(r,1./3.));
         Float64 t = -g/2 - sqrt(h);
         Float64 u = (t < 0 ? -pow(-t,1./3.) : pow(t,1./3.));
         X[0] = (s+u) - b/(3*a);
         nRoots = 1;
      }
   }

   std::sort(&X[0],&X[3]);

   *pX1 = X[0];
   *pX2 = X[1];
   *pX3 = X[2];

   return nRoots;
}

//======================== ACCESS     =======================================
void mathCubicSolver::SetA(Float64 a)
{
   m_A = a;
}

Float64 mathCubicSolver::GetA() const
{
   return m_A;
}

void mathCubicSolver::SetB(Float64 b)
{
   m_B = b;
}

Float64 mathCubicSolver::GetB() const
{
   return m_B;
}

void mathCubicSolver::SetC(Float64 c)
{
   m_C = c;
}

Float64 mathCubicSolver::GetC() const
{
   return m_C;
}

void mathCubicSolver::SetD(Float64 d)
{
   m_D = d;
}

Float64 mathCubicSolver::GetD() const
{
   return m_D;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void mathCubicSolver::MakeCopy(const mathCubicSolver& rOther)
{
   m_A = rOther.m_A;
   m_B = rOther.m_B;
   m_C = rOther.m_C;
   m_D = rOther.m_D;
}

void mathCubicSolver::MakeAssignment(const mathCubicSolver& rOther)
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
bool mathCubicSolver::AssertValid() const
{
   // Objects of this class are always valid
   return true;
}

void mathCubicSolver::Dump(dbgDumpContext& os) const
{
   os << "Dump for mathCubicSolver" << endl;
   os << "m_A = " << m_A << endl;
   os << "m_B = " << m_B << endl;
   os << "m_C = " << m_C << endl;
   os << "m_D = " << m_D << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool mathCubicSolver::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("mathCubicSolver");

   mathCubicSolver solver( 1, 6, -4, -24 );
   Float64 x1, x2, x3;

   // 3 real roots
   TRY_TESTME( solver.Solve( &x1, &x2, &x3 ) == 3 );
   TRY_TESTME( IsEqual( x1, -6.0 ) );
   TRY_TESTME( IsEqual( x2, -2.0 ) );
   TRY_TESTME( IsEqual( x3,  2.0 ) );

   // one real root (two complex)
   solver.SetA( 1.0 );
   solver.SetB( -11 );
   solver.SetC(  49 );
   solver.SetD( -75 );
   TRY_TESTME( solver.Solve( &x1, &x2, &x3 ) == 1 );
   TRY_TESTME( IsEqual( x1,  3.0 ) );

   // 3 real roots
   solver.SetA( 2.0 );
   solver.SetB( -4 );
   solver.SetC( -22 );
   solver.SetD(  24 );
   TRY_TESTME( solver.Solve( &x1, &x2, &x3 ) == 3 );
   TRY_TESTME( IsEqual( x1, -3.0 ) );
   TRY_TESTME( IsEqual( x2,  1.0 ) );
   TRY_TESTME( IsEqual( x3,  4.0 ) );

   // one real root (two complex)
   solver.SetA( 3.0 );
   solver.SetB( -10 );
   solver.SetC(  14 );
   solver.SetD(  27 );
   TRY_TESTME( solver.Solve( &x1, &x2, &x3 ) == 1 );
   TRY_TESTME( IsEqual( x1,  -1.0 ) );

   // 3 real, with all roots equal
   solver.SetA( 1.0 );
   solver.SetB(  6 );
   solver.SetC( 12 );
   solver.SetD(  8 );
   TRY_TESTME( solver.Solve( &x1, &x2, &x3 ) == 1 );
   TRY_TESTME( IsEqual( x1,  -2.0 ) );


   // 3 real, with 2 equal roots
   solver.SetA( 1.0 );
   solver.SetB( -12 );
   solver.SetC( 45 );
   solver.SetD( -50 );
   TRY_TESTME( solver.Solve( &x1, &x2, &x3 ) == 2 );
   TRY_TESTME( IsEqual( x1, 2.0 ) );
   TRY_TESTME( IsEqual( x2, 5.0 ) );


   // 3 real, with 2 equal roots
   solver.SetA( 1.0 );
   solver.SetB( -9 );
   solver.SetC( 24 );
   solver.SetD( -20 );
   TRY_TESTME( solver.Solve( &x1, &x2, &x3 ) == 2 );
   TRY_TESTME( IsEqual( x1, 2.0 ) );
   TRY_TESTME( IsEqual( x2, 5.0 ) );

   // 3 real roots, one root is 0
   solver.SetA( 1 );
   solver.SetB( 3 );
   solver.SetC( -28 );
   solver.SetD( 0 );
   TRY_TESTME( solver.Solve( &x1, &x2, &x3 ) == 3 );
   TRY_TESTME( IsEqual( x1, -7.0 ) );
   TRY_TESTME( IsEqual( x2,  0.0 ) );
   TRY_TESTME( IsEqual( x3,  4.0 ) );

   // this is actually a quadratic with 2 roots
   solver.SetA( 0 );
   solver.SetB( 1 );
   solver.SetC( 3 );
   solver.SetD( -28 );
   TRY_TESTME( solver.Solve( &x1, &x2, &x3 ) == 2 );
   TRY_TESTME( IsEqual( x1, -7.0 ) );
   TRY_TESTME( IsEqual( x2,  4.0 ) );

   TESTME_EPILOG("mathCubicSolver");
}
#endif // _UNITTEST
