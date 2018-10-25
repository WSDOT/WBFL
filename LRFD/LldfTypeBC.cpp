///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2011  Washington State Department of Transportation
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
#include <Lrfd\LldfTypeBC.h>
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
   lrfdLldfTypeBC
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdLldfTypeBC::lrfdLldfTypeBC(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                  Uint32 Nl, Float64 wLane,
                  Float64 d,Float64 L,
                  Float64 leftDe,Float64 rightDe,
                  Float64 skewAngle1, Float64 skewAngle2) :
lrfdLiveLoadDistributionFactorBase(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane)
{
   m_d           = d;
   m_L           = L;
   m_LeftDe      = leftDe;
   m_RightDe     = rightDe;
   m_SkewAngle1  = skewAngle1;
   m_SkewAngle2  = skewAngle2;
}

lrfdLldfTypeBC::lrfdLldfTypeBC(const lrfdLldfTypeBC& rOther) :
lrfdLiveLoadDistributionFactorBase(rOther)
{
   MakeCopy(rOther);
}

lrfdLldfTypeBC::~lrfdLldfTypeBC()
{
}

//======================== OPERATORS  =======================================
lrfdLldfTypeBC& lrfdLldfTypeBC::operator= (const lrfdLldfTypeBC& rOther)
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
void lrfdLldfTypeBC::MakeCopy(const lrfdLldfTypeBC& rOther)
{
   m_LeftDe      = rOther.m_LeftDe;
   m_RightDe     = rOther.m_RightDe;
   m_d           = rOther.m_d;
   m_L           = rOther.m_L;
   m_SkewAngle1  = rOther.m_SkewAngle1;
   m_SkewAngle2  = rOther.m_SkewAngle2;
}

void lrfdLldfTypeBC::MakeAssignment(const lrfdLldfTypeBC& rOther)
{
   lrfdLiveLoadDistributionFactorBase::MakeAssignment( rOther );
   MakeCopy( rOther );
}

bool lrfdLldfTypeBC::TestRangeOfApplicability(Location loc) const
{
   if (!DoCheckApplicablity())
      return true;

   bool doThrow=true;
   bool bSISpec = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );

   // if S exceeds 16' use lever rule and don't check other params
   if ( !SpacingTriggersLeverRule(bSISpec) )
   {
      if (loc==ExtGirder)
      {
         if (!ExteriorMomentEquationRule(bSISpec,doThrow))
            return false;
      }
      else
      {
         if (!InteriorMomentEquationRule(bSISpec,doThrow))
            return false;
      }
   }

   if ( DoApplySkew() )
   {
      // This is not an out of range of applicability case... skew adjustment simply isn't applied in this case
      //Float64 skew_delta_max = ::ConvertToSysUnits( 10.0, unitMeasure::Degree );
      //if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
      //   THROW_DF( lrfdXRangeOfApplicability, SkewAngleDiff, "Excessive difference in skew angles. See Article 4.6.2.2.2e");

      Float64 skew_max = ::ConvertToSysUnits( 60.0, unitMeasure::Degree );
      if ( !IsLE(m_SkewAngle1,skew_max) || !IsLE(m_SkewAngle2,skew_max) )
         THROW_DF( lrfdXRangeOfApplicability, SkewAngle, _T("Excessive skew angle. See Table 4.6.2.2.2e-1"));

      Float64 smax = DBL_MAX;
      if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FirstEditionWith1997Interims )
      {
         smax =  ::ConvertToSysUnits( bSISpec ? 3500. : 11.5, bSISpec ? unitMeasure::Millimeter : unitMeasure::Feet);
      }
      else
      {
         // after 1997 there is no upper limit because lever rule is used... UNLESS THERE IS A SKEW
         // max with skew
         if ( DoApplySkew()  )
            smax =  ::ConvertToSysUnits( bSISpec ? 3500. : 11.5, bSISpec ? unitMeasure::Millimeter : unitMeasure::Feet);
      }

      if ( smax < m_Savg )
         THROW_DF(lrfdXRangeOfApplicability, Spacing, _T("Beam spacing is out of range (too large). See Table 4.6.2.2.3c-1"));
   }

   return true;
}

bool lrfdLldfTypeBC::InteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   if ( GetNb() < 3 )
      THROW_DF( lrfdXRangeOfApplicability, NumGirders, _T("Number of girders is out of range. See Table 4.6.2.2.2b-1"));

   Float64 smin = ::ConvertToSysUnits( bSISpec ? 1800. : 6.0, bSISpec ? unitMeasure::Millimeter : unitMeasure::Feet);
   if ( m_Savg<=smin-1.0e-05)
      THROW_DF(lrfdXRangeOfApplicability, Spacing, _T("Beam spacing is out of range (too small). See Table 4.6.2.2.2b-1"));

   Float64 lmin = ::ConvertToSysUnits( bSISpec ? 6000. : 20., bSISpec ? unitMeasure::Millimeter : unitMeasure::Feet);
   Float64 lmax = ::ConvertToSysUnits( bSISpec ? 43000. : 140., bSISpec ? unitMeasure::Millimeter : unitMeasure::Feet);
   if ( !InRange( lmin, m_L, lmax ) )
      THROW_DF( lrfdXRangeOfApplicability,SpanLength, _T("Span length is out of range. See Table 4.6.2.2.2b-1"));

   Float64 dmin = ::ConvertToSysUnits( bSISpec ? 450. : 18., bSISpec ? unitMeasure::Millimeter : unitMeasure::Inch);
   Float64 dmax = ::ConvertToSysUnits( bSISpec ? 1700. : 65., bSISpec ? unitMeasure::Millimeter : unitMeasure::Inch);
   if ( !InRange( dmin, m_d, dmax ) )
      THROW_DF( lrfdXRangeOfApplicability,GirderDepth, _T("Girder depth is out of range. See Table 4.6.2.2.2b-1"));

   return true;
}

bool lrfdLldfTypeBC::ExteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   if ( InteriorMomentEquationRule(bSISpec, doThrow) )
   {
      if ( GetNb() < 3 ) // one could argue that this should be 4
         THROW_DF( lrfdXRangeOfApplicability, NumGirders, _T("Number of girders is out of range. Must be >=4, see 4.6.2.2.1"));

      //  check de for exterior girders - it's not applicable for interior
      Float64 demin = 0.0;
      Float64 demax = ::ConvertToSysUnits( bSISpec ?  1400. : 4.5, bSISpec ? unitMeasure::Millimeter : unitMeasure::Feet);

      Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;
      if ( !InRange( demin, de_raw, demax ) )
         THROW_DF( lrfdXRangeOfApplicability, CurbLineOffset, _T("Curb offset (de) is out of range. See Table 4.6.2.2.2d-1"));
   }
   else
   {
      return false;
   }

   return true;
}

bool lrfdLldfTypeBC::SpacingTriggersLeverRule(bool bSISpec) const
{
   // lever rule for any case of spacing over limit, shear had different requirement
   if (bSISpec)
   {
      Float64 S     = ::ConvertFromSysUnits( m_Savg,     unitMeasure::Millimeter );
      Float64 Slimit= lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SecondEditionWith2002Interims ? 3500. : 5500.;
      if ( S>Slimit && lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FirstEditionWith1997Interims )
      {
         // lever rule introduced in 97, otherwise roa is exceeded
         return false;
      }
      else 
      {
         return S > Slimit;
      }
   }
   else
   {
      Float64 S     = ::ConvertFromSysUnits( m_Savg, unitMeasure::Feet );
      Float64 Slimit= lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SecondEditionWith2002Interims ? 11.5 : 18.0;
      if ( S>Slimit && lrfdVersionMgr::GetVersion() < lrfdVersionMgr::FirstEditionWith1997Interims )
      {
         // lever rule introduced in 97, otherwise roa is exceeded
         return false;
      }
      else 
      {
         return S > Slimit;
      }
   }
}


lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeBC::GetMomentDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   // use lever rule for any case of spacing over limit
   bool do_lever = SpacingTriggersLeverRule(bSISpec);

   if(!do_lever && (m_RangeOfApplicabilityAction==roaIgnore || InteriorMomentEquationRule(bSISpec, false)) )
   {
      g.ControllingMethod = SPEC_EQN;
      g.EqnData.bWasUsed = true;
      g.EqnData.e = 1.0;

      if (bSISpec)
      {
         Float64 S     = ::ConvertFromSysUnits( m_Savg,  unitMeasure::Millimeter );
         Float64 L     = ::ConvertFromSysUnits( m_L,     unitMeasure::Millimeter );
         Float64 d     = ::ConvertFromSysUnits( m_d,     unitMeasure::Millimeter );

         g.EqnData.mg = pow( (S/910.), 0.35) * pow((S*d/pow(L,2)),0.25);
         g.mg = g.EqnData.mg;
      }
      else
      {
         Float64 S     = ::ConvertFromSysUnits( m_Savg,  unitMeasure::Feet );
         Float64 L     = ::ConvertFromSysUnits( m_L,     unitMeasure::Feet );
         Float64 d     = ::ConvertFromSysUnits( m_d,     unitMeasure::Inch );

         g.EqnData.mg = pow((S/3.0),0.35) * pow((S*d/(12.0*pow(L,2))),0.25);
         g.mg = g.EqnData.mg;
      }
   }
   else
   {
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, OneLoadedLane);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = MomentSkewCorrectionFactor();

   g.SkewCorrectionFactor = skew;
   g.mg *= skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeBC::GetMomentDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   // lever rule for any case of spacing over limit
   bool do_lever = SpacingTriggersLeverRule(bSISpec);

   if(!do_lever &&  ( m_RangeOfApplicabilityAction==roaIgnore || InteriorMomentEquationRule(bSISpec, false)) )
   {
      g.ControllingMethod = SPEC_EQN;
      g.EqnData.bWasUsed = true;
      g.EqnData.e = 1.0;

      Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;
      if ( bSISpec )
      {
         Float64 S     = ::ConvertFromSysUnits( m_Savg,  unitMeasure::Millimeter );
         Float64 L     = ::ConvertFromSysUnits( m_L,     unitMeasure::Millimeter );
         Float64 d     = ::ConvertFromSysUnits( m_d,     unitMeasure::Millimeter );
         Float64 de    = ::ConvertFromSysUnits( de_raw,  unitMeasure::Millimeter );

         g.EqnData.mg = pow((S/1900),0.6) * pow((S*d/pow(L,2)),0.125);
         g.mg = g.EqnData.mg;
      }
      else
      {
         Float64 S     = ::ConvertFromSysUnits( m_Savg,  unitMeasure::Feet );
         Float64 L     = ::ConvertFromSysUnits( m_L,     unitMeasure::Feet );
         Float64 d     = ::ConvertFromSysUnits( m_d,     unitMeasure::Inch );
         Float64 de    = ::ConvertFromSysUnits( de_raw,  unitMeasure::Feet );

         g.EqnData.mg = pow((S/6.3),0.6) * pow((S*d/(12.0*pow(L,2))),0.125);
         g.mg = g.EqnData.mg;
      }
   }
   else
   {
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, TwoOrMoreLoadedLanes);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = MomentSkewCorrectionFactor();

   g.SkewCorrectionFactor = skew;
   g.mg *= skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeBC::GetMomentDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
   g.mg = g.LeverRuleData.mg;

   Float64 skew = MomentSkewCorrectionFactor();
   g.mg *= skew;
   g.SkewCorrectionFactor = skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeBC::GetMomentDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   // lever rule for any case of spacing over limit
   bool do_lever = SpacingTriggersLeverRule(bSISpec);

   if(!do_lever && (m_RangeOfApplicabilityAction==roaIgnore || ExteriorMomentEquationRule(bSISpec, false)) )
   {
      g = GetMomentDF_Int_2_Strength();
      assert(g.ControllingMethod & SPEC_EQN);

      Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         Float64 de = ::ConvertFromSysUnits( de_raw, unitMeasure::Millimeter );
         Float64 e = 0.97 + de/8700.;

         g.EqnData.e = e;
         g.mg *= e;
         g.ControllingMethod |= E_OVERRIDE;
      }
      else
      {
         Float64 de = ::ConvertFromSysUnits( de_raw, unitMeasure::Feet );
         Float64 e = 0.97 + de/28.5;

         g.EqnData.e = e;
         g.mg *= e;
         g.ControllingMethod |= E_OVERRIDE;
      }
   }
   else
   {
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, TwoOrMoreLoadedLanes);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = MomentSkewCorrectionFactor();
      g.mg *= skew;
      g.SkewCorrectionFactor = skew;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeBC::GetShearDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   // shear ROA same as moment
   if(!SpacingTriggersLeverRule(bSISpec) &&  InteriorMomentEquationRule(bSISpec, false) )
   {
      if ( bSISpec )
      {
         Float64 S = ::ConvertFromSysUnits( m_Savg, unitMeasure::Millimeter );
         Float64 d = ::ConvertFromSysUnits( m_d,    unitMeasure::Millimeter );
         Float64 L = ::ConvertFromSysUnits( m_L,    unitMeasure::Millimeter );

         g.ControllingMethod = SPEC_EQN;
         g.EqnData.bWasUsed = true;
         g.EqnData.e = 1.0;
         g.EqnData.mg = pow((S/3050),0.6) * pow((d/L),0.1);
         g.mg = g.EqnData.mg;
      }
      else
      {
         Float64 S = ::ConvertFromSysUnits( m_Savg, unitMeasure::Feet );
         Float64 d = ::ConvertFromSysUnits( m_d,    unitMeasure::Inch );
         Float64 L = ::ConvertFromSysUnits( m_L,    unitMeasure::Feet );

         g.ControllingMethod = SPEC_EQN;
         g.EqnData.bWasUsed = true;
         g.EqnData.e = 1.0;
         g.EqnData.mg = pow((S/10.0),0.6) * pow((d/(12.0*L)),0.1);
         g.mg = g.EqnData.mg;
      }
   }
   else
   {
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, OneLoadedLane);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = ShearSkewCorrectionFactor();

   g.mg *= skew;
   g.SkewCorrectionFactor = skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult  lrfdLldfTypeBC::GetShearDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   // lever rule for any case of spacing over limit
   bool do_lever = this->SpacingTriggersLeverRule(bSISpec);

   // otherwise, roa for shear is same as moment
   if(!do_lever && InteriorMomentEquationRule(bSISpec, false) )
   {
      g.ControllingMethod = SPEC_EQN;
      g.EqnData.bWasUsed = true;
      g.EqnData.e = 1.0;

      if ( bSISpec )
      {
         Float64 S = ::ConvertFromSysUnits( m_Savg, unitMeasure::Millimeter );
         Float64 d = ::ConvertFromSysUnits( m_d,    unitMeasure::Millimeter );
         Float64 L = ::ConvertFromSysUnits( m_L,    unitMeasure::Millimeter );

         g.EqnData.mg = pow((S/2250),0.8) * pow((d/L),0.1);
         g.mg = g.EqnData.mg;
      }
      else
      {
         Float64 S = ::ConvertFromSysUnits( m_Savg, unitMeasure::Feet );
         Float64 d = ::ConvertFromSysUnits( m_d,    unitMeasure::Inch );
         Float64 L = ::ConvertFromSysUnits( m_L,    unitMeasure::Feet );

         g.EqnData.mg = pow((S/7.4),0.8) * pow((d/(12.0*L)),0.1);
         g.mg = g.EqnData.mg;
      }
   }
   else
   {
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, TwoOrMoreLoadedLanes);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = ShearSkewCorrectionFactor();

   g.mg *= skew;
   g.SkewCorrectionFactor = skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeBC::GetShearDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
   g.mg = g.LeverRuleData.mg;

   Float64 skew = ShearSkewCorrectionFactor();

   g.mg *= skew;
   g.SkewCorrectionFactor = skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeBC::GetShearDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   // lever rule for any case of spacing over limit
   bool do_lever = SpacingTriggersLeverRule(bSISpec);

   if(!do_lever && ExteriorMomentEquationRule(bSISpec, false) ) // shear roa same as moment
   {
      Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         g = GetShearDF_Int_2_Strength();

         Float64 de = ::ConvertFromSysUnits( de_raw, unitMeasure::Millimeter );
         Float64 e = 0.8 + de/3050.;

         g.EqnData.e = e;
         g.mg *= e;
         g.ControllingMethod |= E_OVERRIDE;
      }
      else
      {
         g = GetShearDF_Int_2_Strength();

         Float64 de = ::ConvertFromSysUnits( de_raw, unitMeasure::Feet );
         Float64 e = 0.8 + de/10.0;

         g.EqnData.e = e;
         g.mg *= e;
         g.ControllingMethod |= E_OVERRIDE;
      }
   }
   else
   {
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, TwoOrMoreLoadedLanes);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = ShearSkewCorrectionFactor();
      g.mg *= skew;
      g.SkewCorrectionFactor = skew;
   }

   return g;
}

bool lrfdLldfTypeBC::DoApplySkew() const
{
   return  !IsZero(m_SkewAngle1) || !IsZero(m_SkewAngle2);
}


Float64 lrfdLldfTypeBC::MomentSkewCorrectionFactor() const
{
   Float64 skew;

   if (!DoApplySkew())
      return 1.0;

   // 4.6.2.2.2e - don't reduce moment if difference in skew is > 10 degree
   Float64 skew_delta_max = ::ConvertToSysUnits( 10.0, unitMeasure::Degree );
   if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
      return 1.0;

   Float64 avg_skew_angle = fabs(m_SkewAngle1 + m_SkewAngle2)/2.;

   // Skew angle is limited to 60 deg.
   if ( 60.0 < ::ConvertFromSysUnits(avg_skew_angle, unitMeasure::Degree) )
      avg_skew_angle = ::ConvertToSysUnits(60.0,unitMeasure::Degree);

   skew = 1.05 - 0.25*tan(::ConvertFromSysUnits(avg_skew_angle,unitMeasure::Radian));

   if ( skew > 1.0 )
      skew = 1.0;

   return skew;
}

Float64 lrfdLldfTypeBC::ShearSkewCorrectionFactor() const
{
   Float64 skew;

   if (!DoApplySkew())
      return 1.0;

   Float64 avg_skew_angle = fabs(m_SkewAngle1 + m_SkewAngle2)/2.;

// Table Table 4.6.2.2.3c-1 does not cap values for shear as for moment. Hence the commented code below.

//   // Skew angle is limited to 60 deg.
//   if ( 60.0 < ::ConvertFromSysUnits(avg_skew_angle, unitMeasure::Degree) )
//      avg_skew_angle = ::ConvertToSysUnits(60.0,unitMeasure::Degree);

   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      Float64 L = ::ConvertFromSysUnits( m_L,    unitMeasure::Millimeter );
      Float64 d = ::ConvertFromSysUnits( m_d,    unitMeasure::Millimeter );
      Float64 S = ::ConvertFromSysUnits( m_Savg, unitMeasure::Millimeter );
      skew = 1.0 + sqrt(L*d)*tan(::ConvertFromSysUnits(avg_skew_angle,unitMeasure::Radian))/(6*S);
   }
   else
   {
      Float64 L = ::ConvertFromSysUnits( m_L,    unitMeasure::Feet );
      Float64 d = ::ConvertFromSysUnits( m_d,    unitMeasure::Inch );
      Float64 S = ::ConvertFromSysUnits( m_Savg, unitMeasure::Feet );
      skew = 1.0 + sqrt(L*d/12.0)*tan(::ConvertFromSysUnits(avg_skew_angle,unitMeasure::Radian))/(6*S);
   }

   return skew;
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
bool lrfdLldfTypeBC::AssertValid() const
{
   return lrfdLiveLoadDistributionFactorBase::AssertValid();
}

void lrfdLldfTypeBC::Dump(dbgDumpContext& os) const
{
   lrfdLiveLoadDistributionFactorBase::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdLldfTypeBC::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdLldfTypeBC");

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);

   Float64 S = ::ConvertToSysUnits( 8.57, unitMeasure::Feet );
   Float64 de = ::ConvertToSysUnits( 2.574, unitMeasure::Feet );
   Float64 oh = ::ConvertToSysUnits( 5.145, unitMeasure::Feet );
   Float64 wLane = ::ConvertToSysUnits( 12.0, unitMeasure::Feet );
   Float64 L = ::ConvertToSysUnits( 114., unitMeasure::Feet );
   Float64 d = ::ConvertToSysUnits( 48., unitMeasure::Inch );
   Int16 Nb = 5;
   std::vector<Float64> spacings;
   spacings.assign(Nb-1,S);
   Int16 Nl = Int16( (2*de + wLane*(Nb-1))/::ConvertToSysUnits(10., unitMeasure::Feet) );
   Float64 skew = ::ConvertToSysUnits(20.0,unitMeasure::Degree);

   lrfdLldfTypeBC df(1,S,spacings,oh,oh,
                     Nl,wLane,d,L,
                     de,de,
                     skew,skew);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.31382, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.54911, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 1.17, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.582, 0.001) );
   
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.7506, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.9261, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 1.404, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.9792, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.2615, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.9752, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.6255, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 1.1706, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.2615, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.9752, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.6255, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 1.1706, 0.001) );

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);

   TESTME_EPILOG("lrfdLldfTypeBC");
}
#endif // _UNITTEST



/****************************************************************************
CLASS
   lrfdWsdotLldfTypeBC
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdWsdotLldfTypeBC::lrfdWsdotLldfTypeBC(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,
                                         Float64 leftOverhang,Float64 rightOverhang,
                                         Uint32 Nl, Float64 wLane,
                                         Float64 d,Float64 L,
                                         Float64 leftDe,Float64 rightDe,
                                         Float64 leftSlabOverhang,Float64 rightSlabOverhang,
                                         Float64 skewAngle1, Float64 skewAngle2):
lrfdLldfTypeBC(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,
               Nl, wLane, d, L, leftDe, rightDe,
               skewAngle1, skewAngle2),
m_LeftSlabOverhang(leftSlabOverhang),
m_RightSlabOverhang(rightSlabOverhang)
{
   // For U Beams, WSDOT applies a MPF of 1.0 for exterior girders using the lever rule where one lane controls
   this->IgnoreMpfLeverRule(true);
}

lrfdWsdotLldfTypeBC::lrfdWsdotLldfTypeBC(const lrfdWsdotLldfTypeBC& rOther) :
lrfdLldfTypeBC(rOther)
{
   MakeCopy(rOther);
}

lrfdWsdotLldfTypeBC::~lrfdWsdotLldfTypeBC()
{
}

//======================== OPERATORS  =======================================
lrfdWsdotLldfTypeBC& lrfdWsdotLldfTypeBC::operator= (const lrfdWsdotLldfTypeBC& rOther)
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

lrfdILiveLoadDistributionFactor::DFResult lrfdWsdotLldfTypeBC::GetMomentDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult gint;

   // need for both overhang cases
   gint = lrfdLldfTypeBC::GetMomentDF_Int_1_Strength();

   Float64 soh_raw = m_Side==LeftSide ? m_LeftSlabOverhang : m_RightSlabOverhang;

   if ( IsGT(soh_raw, m_Savg/2) )
   {
      // apply lever rule with mpf=1
      lrfdILiveLoadDistributionFactor::DFResult gext;
      gext.ControllingMethod = LEVER_RULE;
      gext.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
      gext.mg = gext.LeverRuleData.mg;

      Float64 skew = MomentSkewCorrectionFactor();
      gext.mg *= skew;
      gext.SkewCorrectionFactor = skew;

      // external must be >= internal
      if (gext.mg >= gint.mg)
      {
         gint = gext;
      }
      else
      {
         gint.ControllingMethod |= INTERIOR_OVERRIDE;
      }
   }

   return gint;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdWsdotLldfTypeBC::GetMomentDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   // we need to compute interior g in all cases
   g = lrfdLldfTypeBC::GetMomentDF_Int_2_Strength();

   Float64 soh_raw = m_Side==LeftSide ? m_LeftSlabOverhang : m_RightSlabOverhang;

   if ( IsGT(soh_raw, m_Savg/2) )
   {
      lrfdILiveLoadDistributionFactor::DFResult gext;
      gext = lrfdLldfTypeBC::GetMomentDF_Ext_2_Strength();

      if (gext.mg >= g.mg)
      {
         g = gext;
      }
      else
      {
         // interior controlled
         g.ControllingMethod |= INTERIOR_OVERRIDE;
      }
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdWsdotLldfTypeBC::GetShearDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult gint;

   gint = lrfdLldfTypeBC::GetShearDF_Int_1_Strength();

   Float64 soh_raw = m_Side==LeftSide ? m_LeftSlabOverhang : m_RightSlabOverhang;

   if ( IsGT(soh_raw, m_Savg/2) )
   {
      // apply lever rule with mpf=1
      lrfdILiveLoadDistributionFactor::DFResult gext;
      gext.ControllingMethod = LEVER_RULE;
      gext.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
      gext.mg = gext.LeverRuleData.mg;

      Float64 skew = ShearSkewCorrectionFactor();
      gext.mg *= skew;
      gext.SkewCorrectionFactor = skew;

      if (gext.mg >= gint.mg)
      {
         gint = gext;
      }
      else
      {
         gint.ControllingMethod |= INTERIOR_OVERRIDE;
      }
   }

   return gint;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdWsdotLldfTypeBC::GetShearDF_Ext_2_Strength() const
{
   // need interior comp for both overhang widths
   lrfdILiveLoadDistributionFactor::DFResult g;
   g = lrfdLldfTypeBC::GetShearDF_Int_2_Strength();

   Float64 soh_raw = m_Side==LeftSide ? m_LeftSlabOverhang : m_RightSlabOverhang;

   if ( IsGT(soh_raw, m_Savg/2) )
   {
      lrfdILiveLoadDistributionFactor::DFResult gext =  lrfdLldfTypeBC::GetShearDF_Ext_2_Strength();

      if (gext.mg >= g.mg)
      {
         g = gext;
      }
      else
      {
         // interior controlled
         g.ControllingMethod |= INTERIOR_OVERRIDE;
      }
   }

   return g;
}

void lrfdWsdotLldfTypeBC::MakeCopy(const lrfdWsdotLldfTypeBC& rOther)
{
   m_LeftSlabOverhang  = rOther.m_LeftSlabOverhang;
   m_RightSlabOverhang = rOther.m_RightSlabOverhang;
}

void lrfdWsdotLldfTypeBC::MakeAssignment(const lrfdWsdotLldfTypeBC& rOther)
{
   lrfdLldfTypeBC::MakeAssignment( rOther );
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
bool lrfdWsdotLldfTypeBC::AssertValid() const
{
   return lrfdLldfTypeBC::AssertValid();
}

void lrfdWsdotLldfTypeBC::Dump(dbgDumpContext& os) const
{
   lrfdLldfTypeBC::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdWsdotLldfTypeBC::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdWsdotLldfTypeBC");

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);

   Float64 S = ::ConvertToSysUnits( 8.57, unitMeasure::Feet );
   Float64 de = ::ConvertToSysUnits( 2.574, unitMeasure::Feet );
   Float64 oh = ::ConvertToSysUnits( 5.145, unitMeasure::Feet );
   Float64 ohs = ::ConvertToSysUnits( 6.145, unitMeasure::Feet );
   Float64 wLane = ::ConvertToSysUnits( 12.0, unitMeasure::Feet );
   Float64 L = ::ConvertToSysUnits( 114., unitMeasure::Feet );
   Float64 d = ::ConvertToSysUnits( 48., unitMeasure::Inch );
   Int16 Nb = 5;
   std::vector<Float64> spacings;
   spacings.assign(Nb-1,S);
   Int16 Nl = Int16( (2*de + wLane*(Nb-1))/::ConvertToSysUnits(10., unitMeasure::Feet) );
   Float64 skew = ::ConvertToSysUnits(20.0,unitMeasure::Degree);

   lrfdWsdotLldfTypeBC df(1,S,spacings,oh,oh,
                          Nl,wLane,d,L,
                          de,de,
                          ohs,ohs,
                          skew,skew);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.31382, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.54911, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.975, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.582, 0.001) );
   
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.7506, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.9261, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 1.171, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.9792, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.2615, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.9752, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.6255, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 1.1706, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.2615, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.9752, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.6255, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 1.1706, 0.001) );

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);

   TESTME_EPILOG("lrfdWsdotLldfTypeBC");
}
#endif // _UNITTEST




/****************************************************************************
CLASS
   lrfdTxDotLldfTypeBC
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdTxDotLldfTypeBC::lrfdTxDotLldfTypeBC(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                                         Uint32 Nl, Float64 wLane,
                                         Float64 d,Float64 L,
                                         Float64 leftDe,Float64 rightDe,
                                         Float64 roadwayWidth,
                                         Float64 skewAngle1, Float64 skewAngle2):
lrfdLldfTypeBC(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,
               Nl, wLane, d, L, leftDe, rightDe,
               skewAngle1, skewAngle2),
m_RoadwayWidth(roadwayWidth)
{
   // For U Beams, TxDOT applies a MPF of 1.0 for exterior girders using the lever rule where one lane controls
   this->IgnoreMpfLeverRule(true);
}

lrfdTxDotLldfTypeBC::lrfdTxDotLldfTypeBC(const lrfdTxDotLldfTypeBC& rOther) :
lrfdLldfTypeBC(rOther)
{
   MakeCopy(rOther);
}

lrfdTxDotLldfTypeBC::~lrfdTxDotLldfTypeBC()
{
}

//======================== OPERATORS  =======================================
lrfdTxDotLldfTypeBC& lrfdTxDotLldfTypeBC::operator= (const lrfdTxDotLldfTypeBC& rOther)
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

lrfdILiveLoadDistributionFactor::LeverRuleMethod lrfdTxDotLldfTypeBC::DistributeByLeverRule(GirderIndexType beamNum,const std::vector<Float64>& Spacings, Float64 leftOverhang, Float64 rightOverhang,Float64 wLane,IndexType Nl) const
{
   lrfdILiveLoadDistributionFactor::LeverRuleMethod lrData(lrfdLldfTypeBC::DistributeByLeverRule(beamNum,Spacings,leftOverhang,rightOverhang,wLane,Nl));

   if (beamNum==0 || beamNum==Spacings.size() )
   {
      // for all exterior girders, apply a factor of 0.9
      lrData.mg *= 0.9;
   }

   return lrData;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxDotLldfTypeBC::GetMomentDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   GirderIndexType nb = GetNb();
   if (nb >= 3)
   {
      g = lrfdLldfTypeBC::GetMomentDF_Int_1_Strength();
   }
   else
   {
      g = GetLanesBeamsMethod(1,nb);
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxDotLldfTypeBC::GetMomentDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   GirderIndexType nb = GetNb();
   if (nb>=3)
   {
      g = lrfdLldfTypeBC::GetMomentDF_Int_2_Strength();
   }
   else
   {
      g = GetLanesBeamsMethod(m_Nl,nb);
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxDotLldfTypeBC::GetMomentDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;
   Float64 w20 = ::ConvertToSysUnits(20.0, unitMeasure::Feet); // txdot doesn't care about metric

   GirderIndexType nb = GetNb();
   if ( nb<3 )
   {
      g = GetLanesBeamsMethod(1,nb);
   }
   else if (m_RoadwayWidth >= w20)
   {
      g = GetMomentDF_Ext_2_Strength();
   }
   else
   {
      g.ControllingMethod = LEVER_RULE;
      // txdot 0.9 factor applied within and use mpf=1.0
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = MomentSkewCorrectionFactor();
      g.mg *= skew;
      g.SkewCorrectionFactor = skew;
   }

   // exterior cannot be less than interior
   if (nb>2) // no use computing twice for nb<3 case
   {
      lrfdILiveLoadDistributionFactor::DFResult gint = GetMomentDF_Int_1_Strength();
      if (g.mg < gint.mg)
      {
         g = gint;
         g.ControllingMethod |= INTERIOR_OVERRIDE;
      }
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxDotLldfTypeBC::GetMomentDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   GirderIndexType nb = GetNb();
   if ( nb < 3 )
   {
      g = GetLanesBeamsMethod(m_Nl,nb);
   }
   else 
   {
      bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;
      // ROA for TxDOT moment is more like shear: all outside of equation goes to lever rule
      // lever rule for any case of spacing over limit
      bool do_lever = SpacingTriggersLeverRule(bSISpec);

      if(!do_lever && ExteriorMomentEquationRule(bSISpec, false)) 
      {
         g = lrfdLldfTypeBC::GetMomentDF_Ext_2_Strength();

         assert(g.ControllingMethod & SPEC_EQN); // always should use equation
      }
      else
      {
         g.ControllingMethod = LEVER_RULE;
         g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, TwoOrMoreLoadedLanes);
         g.mg = g.LeverRuleData.mg;

         Float64 skew = MomentSkewCorrectionFactor();
         g.mg *= skew;
         g.SkewCorrectionFactor = skew;
      }
   }

   // exterior cannot be less than interior
   if (nb>2)
   {
      lrfdILiveLoadDistributionFactor::DFResult gint = GetMomentDF_Int_2_Strength();
      if (g.mg < gint.mg)
      {
         g = gint;
         g.ControllingMethod |= INTERIOR_OVERRIDE;
      }
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxDotLldfTypeBC::GetShearDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   GirderIndexType nb = GetNb();
   if (nb>=3)
   {
      g = lrfdLldfTypeBC::GetShearDF_Int_1_Strength();
   }
   else
   {
      g = GetLanesBeamsMethod(1,nb);
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxDotLldfTypeBC::GetShearDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   GirderIndexType nb = GetNb();
   if (nb>=3)
   {
      g = lrfdLldfTypeBC::GetShearDF_Int_2_Strength();
   }
   else
   {
      g = GetLanesBeamsMethod(m_Nl,nb);
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxDotLldfTypeBC::GetShearDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;
   Float64 w20 = ::ConvertToSysUnits(20.0, unitMeasure::Feet);

   GirderIndexType nb = GetNb();
   if ( nb<3 )
   {
      g = GetLanesBeamsMethod(1,nb);
   }
   else if (m_RoadwayWidth >= w20)
   {
      g = GetShearDF_Ext_2_Strength();
   }
   else
   {
      g.ControllingMethod = LEVER_RULE;
      // txdot mpf=1.0 and 0.9 factor applied within:
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = ShearSkewCorrectionFactor();
      g.mg *= skew;
      g.SkewCorrectionFactor = skew;
   }

   // exterior cannot be less than interior
   if (nb>2)
   {
      lrfdILiveLoadDistributionFactor::DFResult gint = GetShearDF_Int_1_Strength();
      if (g.mg < gint.mg)
      {
         g = gint;
         g.ControllingMethod |= INTERIOR_OVERRIDE;
      }
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxDotLldfTypeBC::GetShearDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   GirderIndexType nb = GetNb();
   if ( nb<3 )
   {
      g = GetLanesBeamsMethod(m_Nl,nb);
   }
   else 
   {
      g = lrfdLldfTypeBC::GetShearDF_Ext_2_Strength();
   }

   // exterior cannot be less than interior
   if (nb>2)
   {
      lrfdILiveLoadDistributionFactor::DFResult gint = GetShearDF_Int_2_Strength();
      if (g.mg < gint.mg)
      {
         g = gint;
         g.ControllingMethod |= INTERIOR_OVERRIDE;
      }
   }

   return g;
}

void lrfdTxDotLldfTypeBC::MakeCopy(const lrfdTxDotLldfTypeBC& rOther)
{
   m_RoadwayWidth   = rOther.m_RoadwayWidth;
}

void lrfdTxDotLldfTypeBC::MakeAssignment(const lrfdTxDotLldfTypeBC& rOther)
{
   lrfdLldfTypeBC::MakeAssignment( rOther );
   MakeCopy( rOther );
}

// only difference between txdot and aashto is txdot allows Nb<3
bool lrfdTxDotLldfTypeBC::TestRangeOfApplicability(Location loc) const
{
   if (!DoCheckApplicablity())
      return true;

   GirderIndexType nb = GetNb();
   if ( nb<3)
   {
      return true;
   }
   else
   {
      return lrfdLldfTypeBC::TestRangeOfApplicability(loc);
   }

   return true;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================
bool lrfdTxDotLldfTypeBC::DoApplySkew() const
{
   GirderIndexType nb = GetNb();
   if (nb>=3)
   {
      return lrfdLldfTypeBC::DoApplySkew();
   }
   else
   {
      return false;
   }
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdTxDotLldfTypeBC::AssertValid() const
{
   return lrfdLldfTypeBC::AssertValid();
}

void lrfdTxDotLldfTypeBC::Dump(dbgDumpContext& os) const
{
   lrfdLldfTypeBC::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdTxDotLldfTypeBC::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdTxDotLldfTypeBC");

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);

   Float64 S = ::ConvertToSysUnits( 8.57, unitMeasure::Feet );
   Float64 de = ::ConvertToSysUnits( 2.574, unitMeasure::Feet );
   Float64 oh = ::ConvertToSysUnits( 5.145, unitMeasure::Feet );
   Float64 wLane = ::ConvertToSysUnits( 12.0, unitMeasure::Feet );
   Float64 L = ::ConvertToSysUnits( 114., unitMeasure::Feet );
   Float64 d = ::ConvertToSysUnits( 48., unitMeasure::Inch );
   Int16 Nb = 5;
   std::vector<Float64> spacings;
   spacings.assign(Nb-1,S);
   Int16 Nl = Int16( (2*de + wLane*(Nb-1))/::ConvertToSysUnits(10., unitMeasure::Feet) );
   Float64 skew = ::ConvertToSysUnits(20.0,unitMeasure::Degree);

   lrfdLldfTypeBC df(1,S,spacings,oh,oh,
                     Nl,wLane,d,L,
                     de,de,
                     skew,skew);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.31382, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.54911, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 1.17, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.582, 0.001) );
   
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.7506, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.9261, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 1.404, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.9792, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.2615, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.9752, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.6255, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 1.1706, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.2615, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.9752, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.6255, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 1.1706, 0.001) );

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);

   TESTME_EPILOG("lrfdTxDotLldfTypeBC");
}
#endif // _UNITTEST
