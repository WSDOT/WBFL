///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2014  Washington State Department of Transportation
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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\RefinedLosses.h>
#include <Lrfd\ElasticShortening.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\XPsLosses.h>
#include <Units\SysUnits.h>
#include <System\XProgrammingError.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdRefinedLosses
****************************************************************************/


Float64 shrinkage_losses(Float64 h);
Float64 creep_losses(Float64 fcgp, Float64 dfcdp);
Float64 relaxation_after_transfer(matPsStrand::Type type,Float64 es,Float64 sr,Float64 cr);

bool IsSI() 
{
   return (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI);
}

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdRefinedLosses::lrfdRefinedLosses()
{
}

lrfdRefinedLosses::lrfdRefinedLosses(Float64 x, // location along girder where losses are computed
                         Float64 Lg,    // girder length
                         lrfdLosses::SectionPropertiesType sectionProperties,
                         matPsStrand::Grade gr,
                         matPsStrand::Type type,
                         Float64 fpjPerm, // fpj permanent strands
                         Float64 fpjTemp, // fpj of temporary strands
                         Float64 ApsPerm,  // area of permanent strand
                         Float64 ApsTemp,  // area of TTS 
                         Float64 aps,      // area of one strand
                         Float64 epermRelease, // eccentricty of permanent ps strands with respect to CG of girder
                         Float64 epermFinal,
                         Float64 etemp, // eccentricty of temporary strands with respect to CG of girder
                         TempStrandUsage usage,
                         Float64 anchorSet,
                         Float64 wobble,
                         Float64 friction,
                         Float64 angleChange,

                         Float64 Fc,   // 28 day strength of girder concrete
                         Float64 Fci,  // Release strength
                         Float64 FcSlab,   
                         Float64 Ec,   // Modulus of elasticity of girder
                         Float64 Eci,  // Modulus of elasticity of girder at transfer
                         Float64 Ecd,  // Modulus of elasticity of deck

                         Float64 Mdlg,  // Dead load moment of girder only
                         Float64 Madlg,  // Additional dead load on girder section
                         Float64 Msidl, // Superimposed dead loads
                         Float64 Mllim, // live load

                         Float64 Ag,    // Area of girder
                         Float64 Ig,    // Moment of inertia of girder
                         Float64 Ybg,   // Centroid of girder measured from bottom
                         Float64 Ac,    // Area of the composite girder and deck
                         Float64 Ic,    // Moment of inertia of composite
                         Float64 Ybc,   // Centroid of composite measured from bottom

                         Float64 An,    // Area of girder
                         Float64 In,    // Moment of inertia of girder
                         Float64 Ybn,   // Centroid of girder measured from bottom
                         Float64 Acn,    // Area of the composite girder and deck
                         Float64 Icn,    // Moment of inertia of composite
                         Float64 Ybcn,   // Centroid of composite measured from bottom

                         Float64 rh, // relative humidity

                         Float64 ti,   // Time until prestress transfer
                         Float64 shipping,
                         bool bValidateParameters
                         ) :
lrfdLosses(x,Lg,sectionProperties,gr,type,fpjPerm,fpjTemp,ApsPerm,ApsTemp,aps,epermRelease,epermFinal,etemp,usage,anchorSet,wobble,friction,angleChange,Fc,Fci,FcSlab,Ec,Eci,Ecd,Mdlg,Madlg,Msidl,Mllim,Ag,Ig,Ybg,Ac,Ic,Ybc,An,In,Ybn,Acn,Icn,Ybcn,rh,ti,false,bValidateParameters)
{
   m_Shipping = shipping;
}

lrfdRefinedLosses::lrfdRefinedLosses(const lrfdRefinedLosses& rOther)
{
   MakeCopy( rOther );
}

lrfdRefinedLosses::~lrfdRefinedLosses()
{
}

//======================== OPERATORS  =======================================
lrfdRefinedLosses& lrfdRefinedLosses::operator=(const lrfdRefinedLosses& rOther)
{
   if ( this != &rOther )
   {
      MakeAssignment( rOther );
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 lrfdRefinedLosses::TemporaryStrand_TimeDependentLossesAtShipping() const
{
   return PermanentStrand_TimeDependentLossesAtShipping();
}

Float64 lrfdRefinedLosses::PermanentStrand_TimeDependentLossesAtShipping() const
{
   if ( m_Shipping < 0 )
   {
      return -m_Shipping*TimeDependentLosses();
   }
   else
   {
      return m_Shipping;
   }
}

Float64 lrfdRefinedLosses::TimeDependentLossesBeforeDeck() const
{
   return TimeDependentLosses();
}

Float64 lrfdRefinedLosses::TimeDependentLossesAfterDeck() const
{
   return 0;
}

Float64 lrfdRefinedLosses::TimeDependentLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpSR + m_dfpCR + m_dfpR2;
}

Float64 lrfdRefinedLosses::ShrinkageLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpSR;
}

Float64 lrfdRefinedLosses::CreepLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpCR;
}

Float64 lrfdRefinedLosses::TemporaryStrand_RelaxationLossesAtXfer() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[0];
}

Float64 lrfdRefinedLosses::PermanentStrand_RelaxationLossesAtXfer() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[1];
}

Float64 lrfdRefinedLosses::RelaxationLossesAfterXfer() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR2;
}

Float64 lrfdRefinedLosses::TemporaryStrand_ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[0];
}

Float64 lrfdRefinedLosses::PermanentStrand_ImmediatelyBeforeXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpR0[1];
}

Float64 lrfdRefinedLosses::TemporaryStrand_ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[0] + m_dfpR0[0];
}

Float64 lrfdRefinedLosses::PermanentStrand_ImmediatelyAfterXferLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpES[1] + m_dfpR0[1];
}

void lrfdRefinedLosses::ValidateParameters() const
{
}

void lrfdRefinedLosses::UpdateLongTermLosses() const
{
   if ( IsZero( m_FpjPerm ) )
   {
      // If the strands aren't jacked, then there can't be losses.
      m_dfpSR = 0.0;
      m_dfpCR = 0.0;
      m_dfpR2 = 0.0;
   }
   else
   {
      m_dfpSR = shrinkage_losses( m_H );

      m_DeltaFcd1 = -1*(m_Madlg*m_epermFinal/m_Ig + m_Msidl*( m_Ybc - m_Ybg + m_epermFinal )/m_Ic);

      m_dfpCR = creep_losses( m_ElasticShortening.PermanentStrand_Fcgp()/* + m_DeltaFcgp*/, m_DeltaFcd1 );

      m_dfpR2 = relaxation_after_transfer( m_Type, m_dfpES[1] + m_dfpp, m_dfpSR, m_dfpCR );
   }
}

void lrfdRefinedLosses::UpdateHaulingLosses() const
{
   UpdateLongTermLosses();
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdRefinedLosses::MakeAssignment( const lrfdRefinedLosses& rOther )
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void lrfdRefinedLosses::MakeCopy( const lrfdRefinedLosses& rOther )
{
   lrfdLosses::MakeCopy(rOther);

   m_dfpSR = rOther.m_dfpSR;
   m_dfpCR = rOther.m_dfpCR;
   m_dfpR2 = rOther.m_dfpR2;

   m_Shipping = rOther.m_Shipping;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


Float64 shrinkage_losses(Float64 h)
{
   CHECK( InRange(0.,h,100.) );

   Float64 losses;
   Float64 A,B; // Coefficients in the loss equation
   const unitStress* p_unit;

   bool is_si = IsSI();

   if ( is_si )
   {
      p_unit = &unitMeasure::MPa;
   }
   else
   {
      p_unit = &unitMeasure::KSI;
   }

   A = is_si ? 117. : 17.;
   B = is_si ? 1.03 : 0.150;

   losses = A - B*h;

   losses = ::ConvertToSysUnits(losses, *p_unit );
   CHECK( losses >= 0. );

   return losses;
}

Float64 creep_losses(Float64 fcgp, Float64 dfcdp)
{
   Float64 loss = 12.0* fcgp + 7.0*dfcdp;
   loss = (loss < 0 ) ? 0 : loss;
   return loss;
}

Float64 relaxation_after_transfer(matPsStrand::Type type,Float64 es,Float64 sr,Float64 cr)
{
   bool is_si = IsSI();
   const unitStress* p_unit;
   Float64 A;

   if ( is_si )
   {
      p_unit = &unitMeasure::MPa;
      A = 138.;
   }
   else
   {
      p_unit = &unitMeasure::KSI;
      A = 20.;
   }

   // Convert input values from system units to code units
   es = ::ConvertFromSysUnits(es,*p_unit);
   sr = ::ConvertFromSysUnits(sr,*p_unit);
   cr = ::ConvertFromSysUnits(cr,*p_unit);

   Float64 losses;
   losses = A - 0.4*es - 0.2*(sr+cr);

   if ( type == matPsStrand::LowRelaxation )
   {
      losses *= 0.3;
   }

   losses = ::ConvertToSysUnits(losses,*p_unit);

   if ( losses < 0 )
   {
      WATCH(_T("Losses less than zero. Setting them to zero"));
      losses = 0; // Per Bijan Khaleghi 12/18/98
   }

   return losses;
}

#if defined _UNITTEST
#include <Units\SysUnitsMgr.h>
#include <Lrfd\AutoVersion.h>
bool lrfdRefinedLosses::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdRefinedLosses");
//
//   lrfdAutoVersion av;
//
//   Float64 Fpj   = ::ConvertToSysUnits( 0.80*1860, unitMeasure::MPa );
//   Float64 Ag    = ::ConvertToSysUnits( 486051, unitMeasure::Millimeter2 );
//   Float64 Ig    = ::ConvertToSysUnits( 126011e6, unitMeasure::Millimeter4 );
//   Float64 Ybg   = ::ConvertToSysUnits( 608, unitMeasure::Millimeter );
//   Float64 Ic    = ::ConvertToSysUnits( 283.7e9, unitMeasure::Millimeter4 );
//   Float64 Ybc   = ::ConvertToSysUnits( 977, unitMeasure::Millimeter );
//   Float64 e     = ::ConvertToSysUnits( 489, unitMeasure::Millimeter );
//   Float64 Aps   = ::ConvertToSysUnits( 5133, unitMeasure::Millimeter2 );
//   Float64 Mdlg  = ::ConvertToSysUnits( 1328, unitMeasure::KilonewtonMeter );
//   Float64 Madlg = ::ConvertToSysUnits( 2900-1328, unitMeasure::KilonewtonMeter );
//   Float64 Msidl = ::ConvertToSysUnits( 540+353, unitMeasure::KilonewtonMeter );
//   Float64 Rh    = 70.;
//   Float64 Eci   = ::ConvertToSysUnits( 30360, unitMeasure::MPa );
//   Float64 t     = ::ConvertToSysUnits( 4.0, unitMeasure::Day );
//
//   lrfdRefinedLosses loss( matPsStrand::Gr1860,
//                      matPsStrand::LowRelaxation,
//                      Fpj, 0, Ag, Ig, Ybg, Ic, Ybc, e, e, e, Aps, 0, Mdlg, Madlg, Msidl, 1.0,
//                      Rh, Eci, t );
//
//   lrfdVersionMgr::RegisterListener( &loss );
//
//   lrfdVersionMgr::SetVersion( lrfdVersionMgr::FirstEdition );
//   Float64 loss1 = loss.ImmediatelyAfterXferLosses();
//   TRY_TEST (  IsEqual( ::ConvertFromSysUnits(loss1,unitMeasure::MPa),165.7,0.1) );
//
//   Float64 loss2 = loss.FinalLosses();
//   TRY_TEST (  IsEqual(::ConvertFromSysUnits(loss2,unitMeasure::MPa),394.2,0.1) );
//
//   loss.SetFpj(1);
//   bool bDidCatch = false;
//   try
//   {
//      Float64 loss3 = loss.FinalLosses();
//   }
//   catch( const lrfdXPsLosses& e )
//   {
//      bDidCatch = true;
//      TRY_TEST( bDidCatch );
//      TRY_TEST( e.GetReasonCode() == lrfdXPsLosses::fpjOutOfRange );
//   }
//   TRY_TEST( bDidCatch );
//
//   lrfdVersionMgr::UnregisterListener( &loss );

   TESTME_EPILOG("lrfdRefinedLosses");
}

#endif // _UNITTEST


