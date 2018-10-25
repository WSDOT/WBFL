///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\LldfTypeHIJ.h>
#include <Lrfd\XRangeOfApplicability.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\Utility.h>
#include <Units\SysUnits.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdLldfTypeHIJ
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdLldfTypeHIJ::lrfdLldfTypeHIJ(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                                 Uint32 Nl, Float64 wLane,
                                 Float64 L,Float64 W,Float64 I,Float64 J,Float64 PoissonRatio,
                                 Float64 leftDe,Float64 rightDe,
                                 Float64 skewAngle1, Float64 skewAngle2,
                                 bool bMomentSkew, bool bShearSkew) :
lrfdLiveLoadDistributionFactorBase(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane,bMomentSkew,bShearSkew)
{
   m_L           = L;
   m_W           = W;
   m_I           = I;
   m_J           = J;
   m_LeftDe      = leftDe;
   m_RightDe     = rightDe;
   m_PoissonRatio = PoissonRatio;
   m_SkewAngle1  = skewAngle1;
   m_SkewAngle2  = skewAngle2;
}

lrfdLldfTypeHIJ::lrfdLldfTypeHIJ(const lrfdLldfTypeHIJ& rOther) :
lrfdLiveLoadDistributionFactorBase(rOther)
{
   MakeCopy(rOther);
}

lrfdLldfTypeHIJ::~lrfdLldfTypeHIJ()
{
}

//======================== OPERATORS  =======================================
lrfdLldfTypeHIJ& lrfdLldfTypeHIJ::operator= (const lrfdLldfTypeHIJ& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdLldfTypeHIJ::MakeCopy(const lrfdLldfTypeHIJ& rOther)
{
   m_L           = rOther.m_L;
   m_W           = rOther.m_W;
   m_I           = rOther.m_I;
   m_J           = rOther.m_J;
   m_LeftDe      = rOther.m_LeftDe;
   m_RightDe     = rOther.m_RightDe;
   m_PoissonRatio = rOther.m_PoissonRatio;
   m_SkewAngle1  = rOther.m_SkewAngle1;
   m_SkewAngle2  = rOther.m_SkewAngle2;
}

void lrfdLldfTypeHIJ::MakeAssignment(const lrfdLldfTypeHIJ& rOther)
{
   lrfdLiveLoadDistributionFactorBase::MakeAssignment( rOther );
   MakeCopy( rOther );
}

bool lrfdLldfTypeHIJ::TestRangeOfApplicability(Location loc) const
{
   if (!DoCheckApplicablity())
      return true;

   bool bSISpec = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
   bool doThrow=true;

   if (!InteriorMomentEquationRule(bSISpec, true))
      return false;

   if ( !IsZero(m_SkewAngle1) || !IsZero(m_SkewAngle2) )
      THROW_DF( lrfdXRangeOfApplicability, SkewAngle, _T("Skew corrections are not defined for this girder type. See 4.6.2.2.2e"));

   // This is not an out of range of applicability case... skew adjustment simply isn't applied in this case
   //Float64 skew_delta_max = ::ConvertToSysUnits( 10.0, unitMeasure::Degree );
   //if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
   //   THROW_DF( lrfdXRangeOfApplicability, SkewAngleDiff, "Excessive difference in skew angles. See Article 4.6.2.2.2e");

   return true;
}

bool lrfdLldfTypeHIJ::InteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   if ( 6 < m_Nl )
      THROW_DF( lrfdXRangeOfApplicability, NumLanes, _T("Excessive number of lanes. See Table 4.6.2.2.2b-1"));

   Float64 skew_max = ::ConvertToSysUnits( 45.0, unitMeasure::Degree );
   if ( !IsLE(m_SkewAngle1,skew_max) || !IsLE(m_SkewAngle2,skew_max) )
      THROW_DF( lrfdXRangeOfApplicability, SkewAngle, _T("Excessive skew angle. See Table 4.6.2.2.2b-1"));

   if ( GetNb() < 4 )
      THROW_DF( lrfdXRangeOfApplicability, NumGirders, _T("Number of girders is out of range. Must be >=4, see 4.6.2.2.1"));

   return true;
}


lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeHIJ::GetMomentDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;
   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   if( m_RangeOfApplicabilityAction==roaIgnore || InteriorMomentEquationRule(bSISpec, false) )
   {
      Float64 J, I, W, S, L;
      Float64 f;
      bool bSI = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;
      if ( bSI )
      {
         J = ::ConvertFromSysUnits(m_J,unitMeasure::Millimeter4);
         I = ::ConvertFromSysUnits(m_I,unitMeasure::Millimeter4);
         W = ::ConvertFromSysUnits(m_W,unitMeasure::Millimeter);
         S = ::ConvertFromSysUnits(m_Savg,unitMeasure::Millimeter);
         L = ::ConvertFromSysUnits(m_L,unitMeasure::Millimeter);
         f = 300;
      }
      else
      {
         J = ::ConvertFromSysUnits(m_J,unitMeasure::Inch4);
         I = ::ConvertFromSysUnits(m_I,unitMeasure::Inch4);
         W = ::ConvertFromSysUnits(m_W,unitMeasure::Feet);
         S = ::ConvertFromSysUnits(m_Savg,unitMeasure::Feet);
         L = ::ConvertFromSysUnits(m_L,unitMeasure::Feet);
         f = 1;
      }

      Float64 K = sqrt( (1+m_PoissonRatio)*I/J );
      Float64 C = K*(W/L);
      if ( K < C )
         C = K;

      Float64 D;
      if ( 5 < C )
      {
         D = f*(11.5 - m_Nl);
      }
      else
      {
         D = f*(11.5 - m_Nl + 1.4*m_Nl*pow(1-0.2*C,2));
      }

      g.ControllingMethod = SPEC_EQN | S_OVER_D_METHOD;
      g.EqnData.bWasUsed = true;
      g.EqnData.D = ::ConvertToSysUnits(D,bSI? unitMeasure::Millimeter : unitMeasure::Feet);;
      g.EqnData.C = C;
      g.EqnData.K = K;
      g.EqnData.e = 1.0;
      g.EqnData.mg = S/D;
      g.mg = g.EqnData.mg;
   }
   else
   {
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, OneLoadedLane);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = MomentSkewCorrectionFactor();
   if ( m_bSkewMoment )
   {
      g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg *= skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeHIJ::GetMomentDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g = GetMomentDF_Int_1_Strength();

   if (g.ControllingMethod & LEVER_RULE)
   {
      // needs to be multiple lane
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, TwoOrMoreLoadedLanes);
      g.mg = g.LeverRuleData.mg * g.SkewCorrectionFactor;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeHIJ::GetMomentDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
   Float64 skew = MomentSkewCorrectionFactor();
   if ( m_bSkewMoment )
   {
      g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.LeverRuleData.mg;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeHIJ::GetMomentDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, TwoOrMoreLoadedLanes);

   Float64 skew = MomentSkewCorrectionFactor();
   if ( m_bSkewMoment )
   {
      g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.LeverRuleData.mg;
   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeHIJ::GetShearDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;


   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, OneLoadedLane);

   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.LeverRuleData.mg;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult  lrfdLldfTypeHIJ::GetShearDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, TwoOrMoreLoadedLanes);

   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.LeverRuleData.mg;
   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeHIJ::GetShearDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);

   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.LeverRuleData.mg;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeHIJ::GetShearDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, TwoOrMoreLoadedLanes);

   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.LeverRuleData.mg;
   return g;
}



Float64 lrfdLldfTypeHIJ::MomentSkewCorrectionFactor() const
{
   if ( !m_bSkewMoment )
   {
      return 1.0;
   }

   Float64 skew = 1.0;  // no skew correction given in AASHTO, before 7th edition

   if ( lrfdVersionMgr::SeventhEdition2014 <= lrfdVersionMgr::GetVersion() )
   {
      // LRFD 7th Edition 2014 added skew correction for moment for type h,i,j sections
      
      // 4.6.2.2.2e - don't reduce moment if difference in skew is > 10 degree
      Float64 skew_delta_max = ::ConvertToSysUnits( 10.0, unitMeasure::Degree );
      if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
      {
         return 1.0;
      }

      Float64 avg_skew_angle = fabs(m_SkewAngle1 + m_SkewAngle2)/2.;

      Float64 deg60 = ::ConvertToSysUnits(60.,unitMeasure::Degree);
      if ( deg60 < avg_skew_angle )
      {
         avg_skew_angle = deg60;
      }

      skew = 1.05 - 0.25*tan(avg_skew_angle);
      if ( 1.0 < skew )
      {
         skew = 1.0;
      }
   }

   return skew;
}

Float64 lrfdLldfTypeHIJ::ShearSkewCorrectionFactor() const
{
   return 1.0; // no skew correction given in AASHTO
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
bool lrfdLldfTypeHIJ::AssertValid() const
{
   return lrfdLiveLoadDistributionFactorBase::AssertValid();
}

void lrfdLldfTypeHIJ::Dump(dbgDumpContext& os) const
{
   lrfdLiveLoadDistributionFactorBase::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdLldfTypeHIJ::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdLldfTypeHIJ");

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);

   Int16 Nb = 5;
   Float64 S = ::ConvertToSysUnits( 6, unitMeasure::Feet );
   std::vector<Float64> spacings;
   spacings.assign(Nb-1,S);
   Float64 L = ::ConvertToSysUnits( 120.25, unitMeasure::Feet );
   Float64 W = S*Nb;
   Float64 I = ::ConvertToSysUnits(559367.214,unitMeasure::Inch4);
   Float64 J = ::ConvertToSysUnits( 33064.695,unitMeasure::Inch4);
   Float64 wLane = ::ConvertToSysUnits( 12.0, unitMeasure::Feet );
   Int16 Nl = Int16((wLane*(Nb-1))/::ConvertToSysUnits(10., unitMeasure::Feet) );
   Float64 de = S/2.0;

   lrfdLldfTypeHIJ df(1,S,spacings,de,de,Nl,wLane,
                      L,W,I,J,0.2,de,de,
                      0.0,0.0,true,true);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.55226, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.55226, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.800, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.8, 0.001) );
   
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.6, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.6667, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.8, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.8, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.460188, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.6667, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.5, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.6667, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.460188, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.6667, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.5, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.6667, 0.001) );

   
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);

   TESTME_EPILOG("lrfdLldfTypeHIJ");
}
#endif // _UNITTEST



