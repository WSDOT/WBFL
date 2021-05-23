///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

// Stress-strain curve taken from PCI BDM Figure 2.11-1
// If you plug the numbers into the PCI equations there is a discontinuity at the yield strain.
// This is because of rounding in the published equations.
// We get around the discontinuity by computing the yield strain and using that as the limit between the linear and curved portions of the equation
//
// Constants for Grade 2070 (Grade 300) are published. We assumed A to be 300 ksi, B = 0.04 to match 250 and 270. C is computed from
// 0.9fu = fu - 0.04/(0.9fu/E - C), note that fy = 0.9fu
// C = ((0.1fu)(0.9fu/E) - 0.04)/(0.1fu) = ((0.1*300)(0.9*300/28500) - 0.04)/(0.1*300) = 0.0081
void get_constants( matPsStrand::Grade grade, Float64 *pA, Float64* pB, Float64* pC)
{
   switch (grade)
   {
   case matPsStrand::Gr1725: *pA = 250; *pB = 0.04; *pC = 0.0064; break;
   case matPsStrand::Gr1860: *pA = 270; *pB = 0.04; *pC = 0.0070; break;
   case matPsStrand::Gr2070: *pA = 300; *pB = 0.04; *pC = 0.0081; break;
   default: ATLASSERT(false); // is there a new strand grade
   }
}

////////////////////////// PUBLIC     ///////////////////////////////////////
static const Float64 g_28500_KSI = ::ConvertToSysUnits( 28500., unitMeasure::KSI );

//======================== LIFECYCLE  =======================================
matPsStrandCurve::matPsStrandCurve(const matPsStrand& strand) :
matYieldStressStrainCurve( strand.GetName(), 1,1,-1,1,1,-1,-1,1,1,-1,-1 )
{
   m_StrandGrade = strand.GetGrade();

   Float64 E   = g_28500_KSI;
   Float64 fpu;
   switch (m_StrandGrade)
   {
   case matPsStrand::Gr1725: fpu = 249.; break;
   case matPsStrand::Gr1860: fpu = 269.; break;
   case matPsStrand::Gr2070: fpu = 299.; break;
   default: ATLASSERT(false); // is there a new strand grade?
   }
   Float64 fu  = ::ConvertToSysUnits( fpu, unitMeasure::KSI );
   Float64 fy = strand.GetYieldStrength();

   Float64 a,b,c;
   get_constants( m_StrandGrade, &a, &b, &c );
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

   // Don't pass in a nullptr pointer
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
      get_constants( m_StrandGrade, &a, &b, &c );
      Float64 fps = a - b/(strain - c); // KSI
      fps = ::ConvertToSysUnits( fps, unitMeasure::KSI );

      *pStress = fps;
      state = matStressStrainCurve::TensPlastic;
   }

   return state;
}

matStressStrainCurve::StrainState matPsStrandCurve::GetStrain(Float64 stress,Float64* pStrain) const
{
   // Don't pass in a nullptr pointer
   PRECONDITION( pStrain != 0 );
   ASSERTVALID;

   if ( stress < 0 )
   {
      *pStrain = 0;
      return matStressStrainCurve::Crushed;
   }

   Float64 a, b, c;
   get_constants(m_StrandGrade, &a, &b, &c );

   *pStrain = (b/(a-stress) + c);

   Float64 eps = GetTensYieldStrain();

   if ( *pStrain <= eps )
   {
      // The above equation is only for strains that are more than +/-eps
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
bool matPsStrandCurve::AssertValid() const
{
   Float64 eps = GetTensYieldStrain();
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
   m_StrandGrade = rOther.m_StrandGrade;
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
   target_stress = ::ConvertToSysUnits(248.30508474576271, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::TensPlastic && IsEqual( stress, target_stress ) );

   state = Gr1725_curve.GetStress( 0.0076, &stress );
   target_stress = ::ConvertToSysUnits( 216.6, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::Elastic && IsEqual( stress, target_stress ) );

   state = Gr1725_curve.GetStress( s6, &stress );
   target_stress = ::ConvertToSysUnits( 85.5, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::Elastic && IsEqual( stress, target_stress ) );

   state = Gr1725_curve.GetStress( s8, &stress );
   target_stress = ::ConvertToSysUnits(245.34883720930233, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::TensPlastic && IsEqual( stress, target_stress ) );

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
   target_stress = ::ConvertToSysUnits(268.26086956521738, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::TensPlastic && IsEqual( stress, target_stress ) );

   state = Gr1860_curve.GetStress( 0.0086, &stress );
   target_stress = ::ConvertToSysUnits( 245.0, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::TensPlastic && IsEqual( stress, target_stress ) );

   state = Gr1860_curve.GetStress( s6, &stress );
   target_stress = ::ConvertToSysUnits( 85.5, unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::Elastic && IsEqual( stress, target_stress ) );

   state = Gr1860_curve.GetStress( s8, &stress );
   target_stress = ::ConvertToSysUnits( 265., unitMeasure::KSI );
   TRY_TESTME ( state == matStressStrainCurve::TensPlastic && IsEqual( stress, target_stress ) );

   state = Gr1860_curve.GetStress( s10, &stress );
   TRY_TESTME ( state == matStressStrainCurve::Fractured );

   TESTME_EPILOG("matPsStrandCurve");
}
#endif // _UNITTEST


