///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#include <Material\MatLib.h>
#include <Material\PsStrandCurve.h>
#include <Units\SysUnits.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matPsStrandCurve
****************************************************************************/

void get_constants( bool bGr1725, Float64 *pA, Float64* pB, Float64* pC)
{
   *pA = ( bGr1725 ? 250.   : 270.  );
   *pB = ( bGr1725 ? 0.04   : 0.04  );
   *pC = ( bGr1725 ? 0.0064 : 0.007 ); 
}

////////////////////////// PUBLIC     ///////////////////////////////////////
static const Float64 g_28500_KSI = ::ConvertToSysUnits( 28500., unitMeasure::KSI );

//======================== LIFECYCLE  =======================================
matPsStrandCurve::matPsStrandCurve(const matPsStrand& strand) :
matYieldStressStrainCurve( strand.GetName(), 1,1,-1,1,1,-1,-1,1,1,-1,-1 )
{
   m_bIsGr1725 = ( strand.GetGrade() ==  matPsStrand::Gr1725 );

   Float64 E   = g_28500_KSI;
   Float64 fpu = ( m_bIsGr1725 ? 249. : 269. );
   Float64 fu  = ::ConvertToSysUnits( fpu, unitMeasure::KSI );
   Float64 fy  = E * ( m_bIsGr1725 ? 0.00764091 : 0.00859219);

   Float64 a,b,c;
   get_constants( m_bIsGr1725, &a, &b, &c );
   Float64 eu = b + c;  // This is the strain that will cause the equation to
                        // be equal to fu.

   SetE( E );
   SetCompUltStrain( 0 );
   SetCompUltStress( 0 );
   SetTensUltStrain( eu );
   SetTensUltStress( fu );
   SetCrushingStrain( 0 );
   SetCrushingStress( 0 );
   SetFractureStrain( eu );
   SetFractureStress( fu );
   SetCompYieldStress( 0 );
   SetTensYieldStress( fy );

   ASSERTVALID;
}

matPsStrandCurve::matPsStrandCurve(const matPsStrandCurve& rOther) :
matYieldStressStrainCurve( rOther )
{
   MakeCopy(rOther);

   ASSERTVALID;
}

matPsStrandCurve::~matPsStrandCurve()
{
}

//======================== OPERATORS  =======================================
matPsStrandCurve& matPsStrandCurve::operator= (const matPsStrandCurve& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);

      ASSERTVALID;
   }

   return *this;
}

//======================== OPERATIONS =======================================

matStressStrainCurve* matPsStrandCurve::CreateClone() const
{
   return new matPsStrandCurve(*this);
}


matStressStrainCurve::StrainState matPsStrandCurve::GetStress(Float64 strain,Float64* pStress) const
{
   // :NOTE: Stress-strain curve taken from PCI Bridge Design Manual, Section 2.11
   matStressStrainCurve::StrainState state;

   // Don't pass in a NULL pointer
   PRECONDITION( pStress != 0 );
   ASSERTVALID;

   // Prestressing strands don't have a material curve for compression
   // (This is an assumption of this class)
   if ( strain < 0 )
   {
      *pStress = 0;
      return matStressStrainCurve::Elastic;
   }

   if ( strain <= GetTensYieldStrain() )
   {
      // Strain is between yield points
      *pStress = GetE() * strain;
      state = matStressStrainCurve::Elastic;
   }
   else if ( GetFractureStrain() < strain )
   {
      // Strain is beyond ultimate

      // :NOTE: The documented behavior is that *pStress is undefined
      // for this case, but lets assign it the fracture/crushing stress
      // anyway
      *pStress = GetFractureStress();
      state = matStressStrainCurve::Fractured;
   }
   else
   {
      // Strain is between yield and ultimate
      Float64 a, b, c;
      get_constants( m_bIsGr1725, &a, &b, &c );
      Float64 fps = a - b/(strain - c); // KSI
      fps = ::ConvertToSysUnits( fps, unitMeasure::KSI );

      *pStress = fps;
      state = matStressStrainCurve::TensPlastic;
   }

   return state;
}

matStressStrainCurve::StrainState matPsStrandCurve::GetStrain(Float64 stress,Float64* pStrain) const
{
   // Don't pass in a NULL pointer
   PRECONDITION( pStrain != 0 );
   ASSERTVALID;

   if ( stress < 0 )
   {
      *pStrain = 0;
      return matStressStrainCurve::Crushed;
   }

   Float64 a, b, c;
   get_constants( m_bIsGr1725, &a, &b, &c );

   *pStrain = (b/(a-stress) + c);

   Float64 eps = (m_bIsGr1725 ? 0.0076 : 0.0086 );

   if ( *pStrain <= eps )
   {
      // The above equation is only for strains that are more than +/-0.008
      *pStrain = stress/GetE();
   }

   Float64 dummy_stress;
   StrainState stage = GetStress( *pStrain, &dummy_stress );

   return stage;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
#include <iostream>
bool matPsStrandCurve::AssertValid() const
{
   Float64 eps = (m_bIsGr1725 ? 0.0076 : 0.0086 );
   return matYieldStressStrainCurve::AssertValid() &&
          IsZero( GetCompYieldStrain() )   &&
          IsZero( GetTensYieldStrain() -  eps, 0.0001 );
}

void matPsStrandCurve::Dump(dbgDumpContext& os) const
{
   matYieldStressStrainCurve::Dump( os );
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void matPsStrandCurve::MakeCopy(const matPsStrandCurve& rOther)
{
   m_bIsGr1725 = rOther.m_bIsGr1725;
}

void matPsStrandCurve::MakeAssignment(const matPsStrandCurve& rOther)
{
   matYieldStressStrainCurve::MakeAssignment( rOther );
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
#if defined _UNITTEST
bool matPsStrandCurve::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("matPsStrandCurve");
   Float64 s2 =  0.030;
   Float64 s4 =  0.0086;
   Float64 s6 =  0.003;
   Float64 s8 =  0.015;
   Float64 s10 = 1.000;
   Float64 stress;
   Float64 target_stress;
   matStressStrainCurve::StrainState state;

   // Test a grade 250 strand
   matPsStrand Gr1725(_T(""),
                     matPsStrand::Gr1725,
                     matPsStrand::LowRelaxation,
                     matPsStrand::None,
                     matPsStrand::D1270,
                     ::ConvertToSysUnits(250.,unitMeasure::KSI),
                     ::ConvertToSysUnits(0.90*250.,unitMeasure::KSI),
                     ::ConvertToSysUnits(28500., unitMeasure::KSI),
                     ::ConvertToSysUnits(0.50,unitMeasure::Inch),
                     ::ConvertToSysUnits(0.144,unitMeasure::Inch2));
   matPsStrandCurve Gr1725_curve( Gr1725 );

   state = Gr1725_curve.GetStress( s2, &stress );
   target_stress = ::ConvertToSysUnits( 245, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::TensPlastic || IsEqual( stress, target_stress ) );

   state = Gr1725_curve.GetStress( 0.0076, &stress );
   target_stress = ::ConvertToSysUnits( 216.6, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::Elastic || IsEqual( stress, target_stress ) );

   state = Gr1725_curve.GetStress( s6, &stress );
   target_stress = ::ConvertToSysUnits( 84., unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::Elastic || IsEqual( stress, target_stress ) );

   state = Gr1725_curve.GetStress( s8, &stress );
   target_stress = ::ConvertToSysUnits( 241.5555555555, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::TensPlastic || IsEqual( stress, target_stress ) );

   state = Gr1725_curve.GetStress( s10, &stress );
   TRY_TESTME ( state == matStressStrainCurve::Fractured );

   //
   // Test a grade 270 strand
   //
   matPsStrand Gr1860(_T(""),
                     matPsStrand::Gr1860,
                     matPsStrand::LowRelaxation,
                     matPsStrand::None,
                     matPsStrand::D1270,
                     ::ConvertToSysUnits(250.,unitMeasure::KSI),
                     ::ConvertToSysUnits(0.90*250.,unitMeasure::KSI),
                     ::ConvertToSysUnits(28500., unitMeasure::KSI),
                     ::ConvertToSysUnits(0.50,unitMeasure::Inch),
                     ::ConvertToSysUnits(0.144,unitMeasure::Inch2));
   matPsStrandCurve Gr1860_curve( Gr1860 );

   state = Gr1860_curve.GetStress( s2, &stress );
   target_stress = ::ConvertToSysUnits( 264.6, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::TensPlastic || IsEqual( stress, target_stress ) );

   state = Gr1860_curve.GetStress( 0.0086, &stress );
   target_stress = ::ConvertToSysUnits( 245.0, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::Elastic || IsEqual( stress, target_stress ) );

   state = Gr1860_curve.GetStress( s6, &stress );
   target_stress = ::ConvertToSysUnits( 84., unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::Elastic || IsEqual( stress, target_stress ) );

   state = Gr1860_curve.GetStress( s8, &stress );
   target_stress = ::ConvertToSysUnits( 259.176470588, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::TensPlastic || IsEqual( stress, target_stress ) );

   state = Gr1860_curve.GetStress( s10, &stress );
   TRY_TESTME ( state == matStressStrainCurve::Fractured );

   TESTME_EPILOG("matPsStrandCurve");
}
#endif // _UNITTEST


