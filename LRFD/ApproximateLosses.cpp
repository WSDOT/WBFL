///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\ApproximateLosses.h>
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
   lrfdApproximateLosses
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdApproximateLosses::lrfdApproximateLosses()
{
}

lrfdApproximateLosses::lrfdApproximateLosses(BeamType beamType,
                         Float64 shipping,
                         Float64 ppr,
                         Float64 x, // location along girder where losses are computed
                         Float64 Lg,    // girder length
                         lrfdLosses::SectionPropertiesType sectionProperties,
                         matPsStrand::Grade gradePerm, // strand grade
                         matPsStrand::Type typePerm, // strand type
                         matPsStrand::Coating coatingPerm, // strand coating (none, epoxy)
                         matPsStrand::Grade gradeTemp, // strand grade
                         matPsStrand::Type typeTemp, // strand type
                         matPsStrand::Coating coatingTemp, // strand coating (none, epoxy)
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

                         lrfdConcreteUtil::DensityType concreteType,
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

                         Float64 rh,      // relative humidity
                         Float64 ti,   // Time until prestress transfer
                         bool bIgnoreInitialRelaxation,
                         bool bValidateLosses
                         ) :
lrfdLosses(x,Lg,sectionProperties,gradePerm,typePerm,coatingPerm,gradeTemp,typeTemp,coatingTemp,fpjPerm,fpjTemp,ApsPerm,ApsTemp,aps,epermRelease,epermFinal,etemp,usage,anchorSet,wobble,friction,angleChange,Fc,Fci,FcSlab,Ec,Eci,Ecd,Mdlg,Madlg,Msidl,Mllim,Ag,Ig,Ybg,Ac,Ic,Ybc,An,In,Ybn,Acn,Icn,Ybcn,rh,ti,bIgnoreInitialRelaxation,bValidateLosses)

{
   m_ConcreteType = concreteType;
   m_Shipping = shipping;
   m_PPR = ppr;
   m_BeamType = beamType;
}

lrfdApproximateLosses::lrfdApproximateLosses(const lrfdApproximateLosses& rOther)
{
   MakeCopy( rOther );
}

lrfdApproximateLosses::~lrfdApproximateLosses()
{
}

//======================== OPERATORS  =======================================
lrfdApproximateLosses& lrfdApproximateLosses::operator=(const lrfdApproximateLosses& rOther)
{
   if ( this != &rOther )
   {
      MakeAssignment( rOther );
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 lrfdApproximateLosses::TemporaryStrand_TimeDependentLossesAtShipping() const
{
   return PermanentStrand_TimeDependentLossesAtShipping();
}

Float64 lrfdApproximateLosses::PermanentStrand_TimeDependentLossesAtShipping() const
{
   if ( m_Shipping < 0 )
   {
      // shipping loss is percentage of final losses
      // make sure long term losses are computed
      UpdateLongTermLosses();
      return -m_Shipping*TimeDependentLosses();
   }
   else
   {
      return m_Shipping;
   }
}

Float64 lrfdApproximateLosses::TimeDependentLossesBeforeDeck() const
{
   return TimeDependentLosses();
}

Float64 lrfdApproximateLosses::TimeDependentLossesAfterDeck() const
{
   return 0;
}

Float64 lrfdApproximateLosses::TimeDependentLosses() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   return m_dfpLT;
}

Float64 lrfdApproximateLosses::PermanentStrand_Final() const
{
   // need to over ride this method because shipping losses could be a lump sum and it
   // doesn't have to be consistent with the other losses

   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AfterTransfer() // initial relaxation
                + TimeDependentLosses(); // total lump sum time dependent losses

   return loss;
}

Float64 lrfdApproximateLosses::PermanentStrand_BeforeTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_AtShipping();
   return loss;
}

Float64 lrfdApproximateLosses::PermanentStrand_AfterTemporaryStrandRemoval() const
{
   if ( m_IsDirty )
   {
      UpdateLosses();
   }

   Float64 loss = PermanentStrand_BeforeTemporaryStrandRemoval();
   return loss;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdApproximateLosses::MakeAssignment( const lrfdApproximateLosses& rOther )
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void lrfdApproximateLosses::MakeCopy( const lrfdApproximateLosses& rOther )
{
   lrfdLosses::MakeCopy(rOther);
   m_BeamType = rOther.m_BeamType;
   m_PPR      = rOther.m_PPR;
   m_dfpLT    = rOther.m_dfpLT;
   m_Shipping = rOther.m_Shipping;
   m_ConcreteType = rOther.m_ConcreteType;
}

void lrfdApproximateLosses::ValidateParameters() const
{
}

void lrfdApproximateLosses::UpdateLongTermLosses() const
{
   if ( IsZero( m_FpjPerm ) )
   {
      // If the strands aren't jacked, then there can't be losses.
      m_dfpLT = 0.0;
   }
   else
   {
      // approximate loss method was removed from LRFD 5th Edition, 2010
      ASSERT( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FifthEdition2010 );

      Float64 losses;
      const unitStress* p_unit;

      bool is_si = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI);

      if ( is_si )
      {
         p_unit = &unitMeasure::MPa;
      }
      else
      {
         p_unit = &unitMeasure::KSI;
      }

      Float64 lowRelaxReduction = 0.0;
      if ( m_BeamType == IBeam )
      {
         Float64 A,B; // Coefficients in the loss equation
         A = is_si ? 230. : 33.;
         B = is_si ?  41. :  6.;

         lowRelaxReduction = is_si ? 41. : 6.;

         Float64 fc = ::ConvertFromSysUnits( m_Fc, *p_unit );

         losses = A*(1.0 - 0.15*(fc - B)/B) + B*m_PPR;
      }
      else if ( m_BeamType == UBeam )
      {
         losses = (is_si ? 145. + 28*m_PPR : 21.0 + 4.0*m_PPR);

         lowRelaxReduction = is_si ? 28.0 : 4.0;
      }
      else if ( m_BeamType == SolidSlab )
      {
         losses = (is_si ? 180. + 28.*m_PPR : 26.0 + 4.0*m_PPR);

         lowRelaxReduction = is_si ? 41.0 : 6.0;
      }
      else if ( m_BeamType == BoxBeam )
      {
         losses = (is_si ? 130. + 28*m_PPR : 19.0 + 4.0*m_PPR);

         lowRelaxReduction = is_si ? 28.0 : 4.0;
      }
      else if ( m_BeamType == SingleT )
      {
         Float64 A,B; // Coefficients in the loss equation
         A = is_si ? 230. : 33.;
         B = is_si ?  41. :  6.;

         lowRelaxReduction = is_si ? 55. : 8.;

         Float64 fc = ::ConvertFromSysUnits( m_Fc, *p_unit );

         losses = A*(1.0 - 0.15*(fc - B)/B) + B*m_PPR;
      }


      if ( m_TypePerm == matPsStrand::LowRelaxation )
      {
         losses -= lowRelaxReduction;
      }

      if ( m_ConcreteType != lrfdConcreteUtil::NormalDensity )
      {
         losses += (is_si ? ::ConvertToSysUnits(35.,unitMeasure::MPa) : ::ConvertToSysUnits(5.0,unitMeasure::KSI));
      }

      m_dfpLT = ::ConvertToSysUnits( losses, *p_unit );
   }

   m_DeltaFcd1 = -1*(m_Madlg*m_epermFinal/m_Ig + m_Msidl*( m_Ybc - m_Ybg + m_epermFinal )/m_Ic);
}

void lrfdApproximateLosses::UpdateHaulingLosses() const
{
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

#if defined _UNITTEST
#include <Units\SysUnitsMgr.h>
#include <Lrfd\AutoVersion.h>
bool lrfdApproximateLosses::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdApproximateLosses");

//   lrfdAutoVersion av;
//
//   Float64 Fpj   = ::ConvertToSysUnits( 0.80*1860, unitMeasure::MPa );
//   Float64 Ag    = ::ConvertToSysUnits( 486051, unitMeasure::Millimeter2 );
//   Float64 Ig    = ::ConvertToSysUnits( 126011e6, unitMeasure::Millimeter4 );
//   Float64 Ybg   = ::ConvertToSysUnits( 608, unitMeasure::Millimeter );
//   Float64 e     = ::ConvertToSysUnits( 489, unitMeasure::Millimeter );
//   Float64 Aps   = ::ConvertToSysUnits( 5133, unitMeasure::Millimeter2 );
//   Float64 Mdlg  = ::ConvertToSysUnits( 1328, unitMeasure::KilonewtonMeter );
//   Float64 Eci   = ::ConvertToSysUnits( 30360, unitMeasure::MPa );
//   Float64 Fc    = ::ConvertToSysUnits( 48, unitMeasure::MPa );
//   Float64 t     = ::ConvertToSysUnits( 4.0, unitMeasure::Day );
//   Float64 PPR   = 1.0;
//
//   lrfdApproximateLosses loss( matPsStrand::Gr1860,
//                               matPsStrand::LowRelaxation,
//                               lrfdApproximateLosses::IBeam,
//                               Fpj, 0, Ag, Ig, Ybg, e, e, e, Aps, 0, Mdlg, 1.0, Eci, Fc, PPR, t );
//
//   lrfdVersionMgr::RegisterListener( &loss );
//
//   lrfdVersionMgr::SetVersion( lrfdVersionMgr::FirstEdition );
//   Float64 loss1 = loss.ImmediatelyAfterXferLosses();
//   TRY_TEST (  IsEqual( ::ConvertFromSysUnits(loss1,unitMeasure::MPa),165.7,0.1) );
//
//   Float64 loss2 = loss.FinalLosses();
//   TRY_TEST (  IsEqual(::ConvertFromSysUnits(loss2,unitMeasure::MPa),339.8,0.1) );
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
//
   TESTME_EPILOG("lrfdApproximateLosses");
}

#endif // _UNITTEST


