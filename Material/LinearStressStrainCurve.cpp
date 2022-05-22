///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#include <Material\MatLib.h>
#include <Material\LinearStressStrainCurve.h>
#include <Material\Metal.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matLinearStressStrainCurve
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
matLinearStressStrainCurve::matLinearStressStrainCurve() :
matYieldStressStrainCurve()
{
}

matLinearStressStrainCurve::matLinearStressStrainCurve(const std::_tstring& name,
                                                       Float64 E,
                                                       Float64 tensYieldStress,
                                                       Float64 compYieldStress,
                                                       Float64 tensUltStrain,
                                                       Float64 tensUltStress,
                                                       Float64 compUltStrain,
                                                       Float64 compUltStress,
                                                       Float64 fractureStrain,
                                                       Float64 fractureStress,
                                                       Float64 crushingStrain,
                                                       Float64 crushingStress) :
matYieldStressStrainCurve(name,
                          E,
                          tensYieldStress,
                          compYieldStress,
                          tensUltStrain,
                          tensUltStress,
                          compUltStrain,
                          compUltStress,
                          fractureStrain,
                          fractureStress,
                          crushingStrain,
                          crushingStress)
{
}


matLinearStressStrainCurve::matLinearStressStrainCurve(const std::_tstring& name,
                                                       Float64 E,
                                                       Float64 tensYieldStress,
                                                       Float64 tensUltStrain,
                                                       Float64 tensUltStress,
                                                       Float64 fractureStrain,
                                                       Float64 fractureStress ) :
matYieldStressStrainCurve(name,
                          E,
                          tensYieldStress,
                          -tensYieldStress,
                          tensUltStrain,
                          tensUltStress,
                          -tensUltStrain,
                          -tensUltStress,
                          fractureStrain,
                          fractureStress,
                          -fractureStrain,
                          -fractureStress)
{
}

matLinearStressStrainCurve::matLinearStressStrainCurve(const matMetal& metal) :
matYieldStressStrainCurve( metal.GetName(),
                           metal.GetE(),
                           metal.GetYieldStress(),
                           -metal.GetYieldStress(),
                           metal.GetUltStrain(),
                           metal.GetUltStress(),
                           -metal.GetUltStrain(),
                           -metal.GetUltStress(),
                           metal.GetRuptureStrain(),
                           metal.GetRuptureStress(),
                           -metal.GetRuptureStrain(),
                           -metal.GetRuptureStress() )
{
}

matLinearStressStrainCurve::matLinearStressStrainCurve(const matLinearStressStrainCurve& rOther) :
matYieldStressStrainCurve(rOther)
{
   MakeCopy(rOther);
}

matLinearStressStrainCurve::~matLinearStressStrainCurve()
{
}

//======================== OPERATORS  =======================================
matLinearStressStrainCurve& matLinearStressStrainCurve::operator= (const matLinearStressStrainCurve& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

matStressStrainCurve* matLinearStressStrainCurve::CreateClone() const
{
   return new matLinearStressStrainCurve(*this);
}


matStressStrainCurve::StrainState matLinearStressStrainCurve::GetStress(Float64 strain,Float64* pStress) const
{
   ASSERTVALID;

   if ( InRange( GetCrushingStrain(), strain, GetCompUltStrain() ) )
   {
      *pStress = LinInterp(strain-GetCrushingStrain(),
                           GetCrushingStress(),
                           GetCompUltStress(),
                           GetCompUltStrain()-GetCrushingStrain());
      return matStressStrainCurve::CompUltimate;
   }
   else if ( InRange( GetCompUltStrain(), strain, GetCompYieldStrain() ) )
   {
      *pStress = LinInterp(strain-GetCompUltStrain(),
                           GetCompUltStress(),
                           GetCompYieldStress(),
                           GetCompYieldStrain()-GetCompUltStrain());
      return matStressStrainCurve::CompPlastic;
   }
   else if ( InRange( GetCompYieldStrain(), strain, GetTensYieldStrain() ) )
   {
      *pStress = GetE() * strain;
      return matStressStrainCurve::Elastic;
   }
   else if ( InRange( GetTensYieldStrain(), strain, GetTensUltStrain() ) )
   {
      *pStress = LinInterp(strain-GetTensYieldStrain(),
                           GetTensYieldStress(),
                           GetTensUltStress(),
                           GetTensUltStrain()-GetTensYieldStrain());
      return matStressStrainCurve::TensPlastic;
   }
   else if ( InRange( GetTensUltStrain(), strain, GetFractureStrain() ) )
   {
      *pStress = LinInterp(strain-GetTensUltStrain(),
                           GetTensUltStress(),
                           GetFractureStress(),
                           GetFractureStrain()-GetTensUltStrain());
      return matStressStrainCurve::TensUltimate;
   }
   else
   {
      if ( strain < 0 )
      {
         *pStress = GetCrushingStress();
         return matStressStrainCurve::Crushed;
      }
      else
      {
         *pStress = GetFractureStress();
         return matStressStrainCurve::Fractured;
      }
   }

   return matStressStrainCurve::Crushed;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
#include <Units\System.h>

bool matLinearStressStrainCurve::AssertValid() const
{
   return matYieldStressStrainCurve::AssertValid();
}

void matLinearStressStrainCurve::Dump(WBFL::Debug::LogContext& os) const
{
   matYieldStressStrainCurve::Dump( os );
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void matLinearStressStrainCurve::MakeCopy(const matLinearStressStrainCurve& rOther)
{
   // Add copy code here...
}

void matLinearStressStrainCurve::MakeAssignment(const matLinearStressStrainCurve& rOther)
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
#include <Units\AutoSystem.h>
#include <Units\System.h>

bool matLinearStressStrainCurve::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("matLinearStressStrainCurve");

   WBFL::Units::AutoSystem au; // automatically rolls back changes

   // We want to work in slug, inch, second, C, rad
   WBFL::Units::System::SetMassUnit( WBFL::Units::Measure::Slug );
   WBFL::Units::System::SetLengthUnit( WBFL::Units::Measure::Feet );
   WBFL::Units::System::SetTimeUnit( WBFL::Units::Measure::Second );
   WBFL::Units::System::SetTemperatureUnit( WBFL::Units::Measure::Celcius );
   WBFL::Units::System::SetAngleUnit( WBFL::Units::Measure::Radian );

   matLinearStressStrainCurve curve(_T(""),50000000.,60000.,0.003,65000.,0.006,62000.);
   Float64 s1 = -0.006;
   Float64 s2 =  0.006;
   Float64 s3 = -0.003;
   Float64 s4 =  0.003;
   Float64 s5 = -0.001;
   Float64 s6 =  0.001;
   Float64 s7 = -0.004;
   Float64 s8 =  0.004;
   Float64 s9 = -0.0015;
   Float64 s10 = 0.0015;
   Float64 s11 = -0.008;
   Float64 s12 =  0.008;
   Float64 stress;
   Float64 target_stress;
   matStressStrainCurve::StrainState state;

   state = curve.GetStress( s1, &stress );
   target_stress = -62000.;
   TRY_TESTME ( state == matStressStrainCurve::CompUltimate || IsZero( stress, target_stress ) );

   state = curve.GetStress( s2, &stress );
   target_stress = 62000.;
   TRY_TESTME ( state == matStressStrainCurve::TensUltimate || IsZero( stress, target_stress ) );

   state = curve.GetStress( s3, &stress );
   target_stress = -65000.;
   TRY_TESTME ( state == matStressStrainCurve::CompUltimate || IsZero( stress, target_stress ) );

   state = curve.GetStress( s4, &stress );
   target_stress = 65000.;
   TRY_TESTME ( state == matStressStrainCurve::TensUltimate || IsZero( stress, target_stress ) );

   state = curve.GetStress( s5, &stress );
   target_stress = -50000.;
   TRY_TESTME ( state == matStressStrainCurve::Elastic || IsZero( stress, target_stress ) );
   
   state = curve.GetStress( s6, &stress );
   target_stress = 50000.;
   TRY_TESTME ( state == matStressStrainCurve::Elastic || IsZero( stress, target_stress ) );

   state = curve.GetStress( s7, &stress );
   target_stress = -64000.;
   TRY_TESTME ( state == matStressStrainCurve::CompUltimate || IsZero( stress, target_stress ) );

   state = curve.GetStress( s8, &stress );
   target_stress = 64000.;
   TRY_TESTME ( state == matStressStrainCurve::TensUltimate || IsZero( stress, target_stress ) );

   state = curve.GetStress( s9, &stress );
   target_stress = -60833.333333333333333;
   TRY_TESTME ( state == matStressStrainCurve::CompPlastic || IsZero( stress, target_stress ) );

   state = curve.GetStress( s10, &stress );
   target_stress = 60833.333333333333333;
   TRY_TESTME ( state == matStressStrainCurve::TensPlastic || IsZero( stress, target_stress ) );

   state = curve.GetStress( s11, &stress );
   TRY_TESTME ( state == matStressStrainCurve::Crushed );

   state = curve.GetStress( s12, &stress );
   TRY_TESTME ( state == matStressStrainCurve::Fractured );
   
   TESTME_EPILOG("matLinearStressStrainCurve");
}
#endif // _UNITTEST


