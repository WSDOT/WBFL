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
#include <Lrfd\LldfTypeAEKIJ.h>
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
   lrfdLldfTypeAEKIJ
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdLldfTypeAEKIJ::lrfdLldfTypeAEKIJ(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                     Uint32 Nl, Float64 wLane,
                     Float64 deLeft,Float64 deRight,Float64 L,Float64 ts,Float64 n,
                     Float64 I, Float64 A, Float64 eg,
                     Float64 skewAngle1, Float64 skewAngle2,
                     bool bSkewMoment,
                     bool bSkewShear) :
lrfdLiveLoadDistributionFactorBase(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane,bSkewMoment,bSkewShear), 
m_bIgnoreDe(false)
{
   m_LeftDe       = deLeft;
   m_RightDe      = deRight;
   m_L           = L;
   m_ts          = ts;
   m_n           = n;
   m_I           = I;
   m_A           = A;
   m_eg          = eg;
   m_SkewAngle1  = skewAngle1;
   m_SkewAngle2  = skewAngle2;

   m_Kg = n*(I + A * eg * eg );
}

lrfdLldfTypeAEKIJ::lrfdLldfTypeAEKIJ(const lrfdLldfTypeAEKIJ& rOther) :
lrfdLiveLoadDistributionFactorBase(rOther)
{
   MakeCopy(rOther);
}

lrfdLldfTypeAEKIJ::~lrfdLldfTypeAEKIJ()
{
}

//======================== OPERATORS  =======================================
lrfdLldfTypeAEKIJ& lrfdLldfTypeAEKIJ::operator= (const lrfdLldfTypeAEKIJ& rOther)
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
void lrfdLldfTypeAEKIJ::MakeCopy(const lrfdLldfTypeAEKIJ& rOther)
{
   lrfdLiveLoadDistributionFactorBase::MakeCopy(rOther);

   m_LeftDe      = rOther.m_LeftDe;
   m_RightDe     = rOther.m_RightDe;
   m_L           = rOther.m_L;
   m_ts          = rOther.m_ts;
   m_n           = rOther.m_n;
   m_A           = rOther.m_A;
   m_I           = rOther.m_I;
   m_eg          = rOther.m_eg;
   m_SkewAngle1  = rOther.m_SkewAngle1;
   m_SkewAngle2  = rOther.m_SkewAngle2;
   m_Kg          = rOther.m_Kg;
   m_bIgnoreDe   = rOther.m_bIgnoreDe;
}

void lrfdLldfTypeAEKIJ::MakeAssignment(const lrfdLldfTypeAEKIJ& rOther)
{
   lrfdLiveLoadDistributionFactorBase::MakeAssignment( rOther );
   MakeCopy( rOther );
}

bool lrfdLldfTypeAEKIJ::TestRangeOfApplicability(Location loc) const
{
   if (!DoCheckApplicablity())
   {
      return true;
   }

   bool doThrow=true;
   bool bSISpec = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );

   // if S exceeds 16' use lever rule and don't check other params
   if ( !SpGreaterThan16_Rule(bSISpec) )
   {
      if (loc==ExtGirder)
      {
         ExteriorMomentEquationRule(bSISpec,true);

         if ( GetNb() < 3 )
         {
            THROW_DF( lrfdXRangeOfApplicability, NumGirders, _T("Number of girders is out of range. See Table 4.6.2.2.2d-1"));
         }
      }
      else
      {
         InteriorMomentEquationRule(bSISpec,true);

         GirderIndexType nb = GetNb();

         if ( lrfdVersionMgr::GetVersion() == lrfdVersionMgr::FirstEdition1994 ||
              lrfdVersionMgr::GetVersion() == lrfdVersionMgr::FirstEditionWith1996Interims )
         {
            if ( nb < 4 )
            {
               THROW_DF( lrfdXRangeOfApplicability, NumGirders, _T("Number of girders is out of range. See Table 4.6.2.2.2b-1"));
            }
         }
         else
         {
            if ( nb < 3 )
            {
               THROW_DF( lrfdXRangeOfApplicability, NumGirders, _T("Number of girders is out of range. See Table 4.6.2.2.2b-1"));
            }

            // Skew corrections only apply for Nb >= 4.  We can't use this method to
            // compute distribution factors if we have 3 beams and skews.
            if ( nb == 3 && (m_bSkewMoment || m_bSkewShear) )
            {
               THROW_DF( lrfdXRangeOfApplicability, NumGirders, _T("Number of girders is out of range. See Table 4.6.2.2.2e-1"));
            }
         }
      }
   }

   // This is not an out of range of applicability case... skew adjustment simply isn't applied in this case
   //Float64 skew_delta_max = ::ConvertToSysUnits( 10.0, unitMeasure::Degree );
   //if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
   //   THROW_DF( lrfdXRangeOfApplicability, SkewAngleDiff, "Excessive difference in skew angles. See Article 4.6.2.2.2e");

   Float64 skew_max = ::ConvertToSysUnits( 60.0, unitMeasure::Degree );
   if ( !IsLE(m_SkewAngle1,skew_max) || !IsLE(m_SkewAngle2,skew_max) )
   {
      THROW_DF( lrfdXRangeOfApplicability, SkewAngle, _T("Excessive skew angle. See Table 4.6.2.2.2e-1"));
   }

   return true;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeAEKIJ::GetMomentDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   if ( SpGreaterThan16_Rule(bSISpec) )
   {
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, OneLoadedLane);
      g.mg = g.LeverRuleData.mg;
   }
   else if( m_RangeOfApplicabilityAction==roaIgnore || InteriorMomentEquationRule(bSISpec, false) )
   {
      // use equation
      if ( bSISpec)
      {
         Float64 S     = ::ConvertFromSysUnits( m_Savg,  unitMeasure::Millimeter );
         Float64 L     = ::ConvertFromSysUnits( m_L,     unitMeasure::Millimeter );
         Float64 ts    = ::ConvertFromSysUnits( m_ts,    unitMeasure::Millimeter );
         Float64 Kg    = ::ConvertFromSysUnits( m_Kg,    unitMeasure::Millimeter4 );

         g.ControllingMethod = SPEC_EQN;
         g.EqnData.bWasUsed = true;
         g.EqnData.mg = 0.06 + pow(S/4300.,0.4)*pow(S/L,0.3)*pow(Kg/(L*pow(ts,3)),0.1);
         g.EqnData.e = 1.0;
         g.mg = g.EqnData.mg;

      }
      else
      {
         Float64 S     = ::ConvertFromSysUnits( m_Savg,  unitMeasure::Feet );
         Float64 L     = ::ConvertFromSysUnits( m_L,     unitMeasure::Feet );
         Float64 ts    = ::ConvertFromSysUnits( m_ts,    unitMeasure::Inch );
         Float64 Kg    = ::ConvertFromSysUnits( m_Kg,    unitMeasure::Inch4 );

         g.ControllingMethod = SPEC_EQN;
         g.EqnData.bWasUsed = true;
         g.EqnData.mg = 0.06 + pow(S/14.,0.4)*pow(S/L,0.3)*pow(Kg/(12.0*L*pow(ts,3)),0.1);
         g.EqnData.e = 1.0;
         g.mg = g.EqnData.mg;
      }

      g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(1);

      GirderIndexType nb = GetNb();
      if ( lrfdVersionMgr::FirstEditionWith1997Interims <= lrfdVersionMgr::GetVersion() && nb == 3 )
      {
         g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, OneLoadedLane);
         // controlling g is minimum of equation and lever rule
         if (g.LeverRuleData.mg < g.EqnData.mg)
         {
            g.ControllingMethod = LEVER_RULE;
            g.mg = g.LeverRuleData.mg;
         }
      }
   }
   else
   {
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
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

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeAEKIJ::GetMomentDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   if ( SpGreaterThan16_Rule(bSISpec) )
   {
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, TwoOrMoreLoadedLanes);
      g.mg = g.LeverRuleData.mg;
   }
   else if( m_RangeOfApplicabilityAction==roaIgnore || InteriorMomentEquationRule(bSISpec, false) )
   {
      // using equation
      Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;

      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         Float64 S     = ::ConvertFromSysUnits( m_Savg,  unitMeasure::Millimeter );
         Float64 L     = ::ConvertFromSysUnits( m_L,     unitMeasure::Millimeter );
         Float64 ts    = ::ConvertFromSysUnits( m_ts,    unitMeasure::Millimeter );
         Float64 Kg    = ::ConvertFromSysUnits( m_Kg,    unitMeasure::Millimeter4 );
         Float64 de    = ::ConvertFromSysUnits( de_raw,  unitMeasure::Millimeter );
         Float64 wLane = ::ConvertFromSysUnits( m_wLane, unitMeasure::Millimeter );

         g.ControllingMethod = SPEC_EQN;
         g.EqnData.bWasUsed = true;
         g.EqnData.mg = 0.075 + pow(S/2900.,0.6)*pow(S/L,0.2)*pow(Kg/(L*pow(ts,3)),0.1);
         g.EqnData.e = 1.0;
         g.mg = g.EqnData.mg;
      }
      else
      {
         Float64 S     = ::ConvertFromSysUnits( m_Savg,  unitMeasure::Feet );
         Float64 L     = ::ConvertFromSysUnits( m_L,     unitMeasure::Feet );
         Float64 ts    = ::ConvertFromSysUnits( m_ts,    unitMeasure::Inch );
         Float64 Kg    = ::ConvertFromSysUnits( m_Kg,    unitMeasure::Inch4 );
         Float64 de    = ::ConvertFromSysUnits( de_raw,  unitMeasure::Feet );
         Float64 wLane = ::ConvertFromSysUnits( m_wLane, unitMeasure::Feet );

         g.ControllingMethod = SPEC_EQN;
         g.EqnData.bWasUsed = true;
         g.EqnData.mg = 0.075 + pow(S/9.5,0.6)*pow(S/L,0.2)*pow(Kg/(12.0*L*pow(ts,3)),0.1);
         g.EqnData.e = 1.0;
         g.mg = g.EqnData.mg;
      }

      g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(1);

      GirderIndexType nb = GetNb();
      if ( lrfdVersionMgr::FirstEditionWith1997Interims <= lrfdVersionMgr::GetVersion() && nb == 3 )
      {
         g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, TwoOrMoreLoadedLanes);

         if (g.LeverRuleData.mg < g.EqnData.mg)
         {
            g.ControllingMethod = LEVER_RULE;
            g.mg = g.LeverRuleData.mg;
         }
      }
   }
   else
   {
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, TwoOrMoreLoadedLanes);
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

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeAEKIJ::GetMomentDF_Ext_1_Strength() const
{
   Float64 skew;
   lrfdILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
   g.mg = g.LeverRuleData.mg;

   skew = MomentSkewCorrectionFactor();
   if ( m_bSkewMoment )
   {
      g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
   }
   g.mg *= skew;
   g.SkewCorrectionFactor = skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeAEKIJ::GetMomentDF_Ext_2_Strength() const
{
   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   // Skew correction factor is included int GetMomentDF_Int_2_Strength
   // Because this are virtual methods, it is important that we call the
   // GetMomentDF_Int_2_Strength() for this class and not an overriden one.
   // Hence the scoping qualifier.
   lrfdILiveLoadDistributionFactor::DFResult g;
   g = lrfdLldfTypeAEKIJ::GetMomentDF_Int_2_Strength();
   if (g.ControllingMethod & SPEC_EQN && (m_RangeOfApplicabilityAction==roaIgnore || DeRule(bSISpec,false) ) )
   {
      // only apply e factor if equation was used for interior
      Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;
      Float64 e;
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         Float64 de = ::ConvertFromSysUnits( de_raw, unitMeasure::Millimeter );

         ATLASSERT( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::SeventhEdition2014 );

         if ( lrfdVersionMgr::FirstEdition1994 < lrfdVersionMgr::GetVersion()  )
         {
            e = 0.77 + de/2800.;
         }
         else
         {
            e = max( 0.77 + de/2800., 1.0);
         }
      }
      else
      {
         Float64 de = ::ConvertFromSysUnits( de_raw, unitMeasure::Feet );

         if ( lrfdVersionMgr::SeventhEdition2014 <= lrfdVersionMgr::GetVersion() )
         {
            if ( de < -1.0 )
            {
               de = -1.0;
            }
         }

         if ( lrfdVersionMgr::FirstEdition1994 < lrfdVersionMgr::GetVersion()  )
         {
            e = 0.77 + de/9.1;
         }
         else
         {
            e = max( 0.77 + de/9.1, 1.0);
         }
      }

      g.EqnData.e = e;
      g.mg *= e;
      g.ControllingMethod |= E_OVERRIDE;

      if (GetNb() <= 3)
      {
         g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, TwoOrMoreLoadedLanes);

         Float64 skew = MomentSkewCorrectionFactor();

         if (g.LeverRuleData.mg*skew < g.mg) // use lesser of lever rule and equation
         {
            g.ControllingMethod = LEVER_RULE;
            if ( m_bSkewMoment )
            {
               g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
            }
            g.SkewCorrectionFactor = skew;
            g.mg = g.LeverRuleData.mg * skew;
         }
      }
   }
   else
   {
      // lever rule was used for interior - override using exterior lever rule
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, TwoOrMoreLoadedLanes);

      Float64 skew = MomentSkewCorrectionFactor();
      if ( m_bSkewMoment )
      {
         g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
      }
      g.SkewCorrectionFactor = skew;
      g.mg = g.LeverRuleData.mg * skew;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeAEKIJ::GetShearDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   if( (InteriorShearEquationRule(bSISpec, false)) && 3 < GetNb() )
   {
      // using spec equation
      g.ControllingMethod = SPEC_EQN;
      g.EqnData.e = 1.0;
      g.EqnData.bWasUsed = true;

      if ( bSISpec )
      {
         Float64 S     = ::ConvertFromSysUnits( m_Savg,     unitMeasure::Millimeter );
         g.EqnData.mg = 0.36 + S/7600.;
         g.mg = g.EqnData.mg;
      }
      else
      {
         Float64 S     = ::ConvertFromSysUnits( m_Savg,     unitMeasure::Feet );
         g.EqnData.mg = 0.36 + S/25.;
         g.mg = g.EqnData.mg;
      }

      g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(1);
   }
   else
   {
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, OneLoadedLane);
      g.mg = g.LeverRuleData.mg;
   }


   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.mg *= skew;
   g.SkewCorrectionFactor = skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult  lrfdLldfTypeAEKIJ::GetShearDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   if( ( InteriorShearEquationRule(bSISpec, false)) && 3 < GetNb() )
   {
      // using spec equation
      g.ControllingMethod = SPEC_EQN;
      g.EqnData.e = 1.0;
      g.EqnData.bWasUsed = true;

      if ( bSISpec )
      {
         Float64 S     = ::ConvertFromSysUnits( m_Savg,     unitMeasure::Millimeter );
         g.EqnData.mg = 0.2 + S/3600. - pow(S/10700.,2.0);
         g.EqnData.e = 1.0;
         g.mg = g.EqnData.mg;
      }
      else
      {
         Float64 S     = ::ConvertFromSysUnits( m_Savg,     unitMeasure::Feet );
         g.EqnData.mg = 0.2 + S/12. - pow(S/35.,2.0);
         g.mg = g.EqnData.mg;
      }

      g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(2);
   }
   else
   {
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, TwoOrMoreLoadedLanes);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.mg *= skew;
   g.SkewCorrectionFactor = skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeAEKIJ::GetShearDF_Ext_1_Strength() const
{
   Float64 skew;
   lrfdILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
   g.mg = g.LeverRuleData.mg;

   skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.mg *= skew;
   g.SkewCorrectionFactor = skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeAEKIJ::GetShearDF_Ext_2_Strength() const
{
   bool bSISpec = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
   // Skew correction factor is included in GetShearDF_Int_2_Strength
   // Because this are virtual methods,  it is important that we call the
   // GetShearDF_Int_2_Strength() for this class and not an overriden one.
   // Hence the scoping qualifier.
   lrfdILiveLoadDistributionFactor::DFResult g;
   g = lrfdLldfTypeAEKIJ::GetShearDF_Int_2_Strength();

   // Only apply e factor if equation was used for interior, and de and nb are in range
   if (g.ControllingMethod & SPEC_EQN && DeRule(bSISpec,false) && 3 < GetNb() )
   {
      Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;
      Float64 e;
      if ( bSISpec )
      {
         Float64 de = ::ConvertFromSysUnits( de_raw, unitMeasure::Millimeter );
         e = 0.6 + de/3000.;
      }
      else
      {
         Float64 de = ::ConvertFromSysUnits( de_raw, unitMeasure::Feet );
         e = 0.6 + de/10.;
      }

      g.EqnData.e = e;
      g.mg  *= e;
      g.ControllingMethod |= E_OVERRIDE;
   }
   else
   {
      g = DistributeShearByLeverRule(ExtGirder, TwoOrMoreLoadedLanes);
   }

   return g;
}

Float64 lrfdLldfTypeAEKIJ::MomentSkewCorrectionFactor() const
{
   Float64 c1;
   Float64 skew;

   if (!m_bSkewMoment)
   {
      return 1.0;
   }

   // 4.6.2.2.2e - don't reduce moment if difference in skew is > 10 degree
   Float64 skew_delta_max = ::ConvertToSysUnits( 10.0, unitMeasure::Degree );
   if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
   {
      return 1.0;
   }

   Float64 avg_skew_angle = fabs(m_SkewAngle1 + m_SkewAngle2)/2.;

   Float64 deg30 = ::ConvertToSysUnits(30.,unitMeasure::Degree);
   if ( avg_skew_angle + 1.0e-14 < deg30  ) // need a fudge factor here because 30 degrees was showing true
   {
      c1 = 0;
   }
   else
   {
      if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
      {
         Float64 L  = ::ConvertFromSysUnits( m_L,  unitMeasure::Millimeter );
         Float64 Kg = ::ConvertFromSysUnits( m_Kg, unitMeasure::Millimeter4 );
         Float64 ts = ::ConvertFromSysUnits( m_ts, unitMeasure::Millimeter );
         Float64 S  = ::ConvertFromSysUnits( m_Savg,  unitMeasure::Millimeter );

         c1 = 0.25*pow(Kg/(L*pow(ts,3)),0.25)*pow((S/L),0.5);
      }
      else
      {
         Float64 L  = ::ConvertFromSysUnits( m_L,  unitMeasure::Feet );
         Float64 Kg = ::ConvertFromSysUnits( m_Kg, unitMeasure::Inch4 );
         Float64 ts = ::ConvertFromSysUnits( m_ts, unitMeasure::Inch );
         Float64 S  = ::ConvertFromSysUnits( m_Savg,  unitMeasure::Feet );

         c1 = 0.25*pow(Kg/(12.0*L*pow(ts,3)),0.25)*pow((S/L),0.5);
      }
   }

   // Skew angle is limited to 60 deg.
   if ( 60.0 < ::ConvertFromSysUnits(avg_skew_angle, unitMeasure::Degree) )
   {
      avg_skew_angle = ::ConvertToSysUnits(60.0,unitMeasure::Degree);
   }

   skew = 1. - c1*pow( tan(::ConvertFromSysUnits(avg_skew_angle,unitMeasure::Radian)), 1.5);

   return skew;
}

Float64 lrfdLldfTypeAEKIJ::ShearSkewCorrectionFactor() const
{
   Float64 skew;

   if (!m_bSkewShear)
   {
      return 1.0;
   }

   Float64 avg_skew_angle = fabs(m_SkewAngle1 + m_SkewAngle2)/2.;

// Table Table 4.6.2.2.3c-1 does not cap values for shear as for moment. Hence the commented code below.

//   // Skew angle is limited to 60 deg.
//   if ( 60.0 < ::ConvertFromSysUnits(avg_skew_angle, unitMeasure::Degree) )
//      avg_skew_angle = ::ConvertToSysUnits(60.0,unitMeasure::Degree);

   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      Float64 L  = ::ConvertFromSysUnits( m_L,  unitMeasure::Millimeter );
      Float64 Kg = ::ConvertFromSysUnits( m_Kg, unitMeasure::Millimeter4 );
      Float64 ts = ::ConvertFromSysUnits( m_ts, unitMeasure::Millimeter );

      skew = 1.0 + 0.20*pow(L*pow(ts,3)/Kg,0.3)*tan( ::ConvertFromSysUnits(avg_skew_angle,unitMeasure::Radian) );
   }
   else
   {
      Float64 L  = ::ConvertFromSysUnits( m_L,  unitMeasure::Feet );
      Float64 Kg = ::ConvertFromSysUnits( m_Kg, unitMeasure::Inch4 );
      Float64 ts = ::ConvertFromSysUnits( m_ts, unitMeasure::Inch );

      skew = 1.0 + 0.20*pow(12.*L*pow(ts,3)/Kg,0.3)*tan( ::ConvertFromSysUnits(avg_skew_angle,unitMeasure::Radian) );
   }

   return skew;
}

Float64 lrfdLldfTypeAEKIJ::GetKg() const
{
   return m_Kg;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
// Rules
bool lrfdLldfTypeAEKIJ::SpGreaterThan16_Rule(bool bSISpec) const
{
   Float64 smax = ::ConvertToSysUnits( bSISpec ? 4900. : 16.0, bSISpec ? unitMeasure::Millimeter : unitMeasure::Feet);

   return smax < m_Savg;
}


bool lrfdLldfTypeAEKIJ::InteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   // same as for shear and more
   if ( InteriorShearEquationRule(bSISpec,doThrow) )
   {
      if ( lrfdVersionMgr::SecondEditionWith2001Interims <= lrfdVersionMgr::GetVersion() ) // 2001 or later
      {
         Float64 Kgmin = ::ConvertToSysUnits( bSISpec ? 4e9 : 10000., bSISpec ? unitMeasure::Millimeter4 : unitMeasure::Inch4);
         Float64 Kgmax = ::ConvertToSysUnits( bSISpec ? 3e12 : 7000000., bSISpec ? unitMeasure::Millimeter4 : unitMeasure::Inch4);
         if ( !InRange( Kgmin, m_Kg, Kgmax ) )
         {
            THROW_DF( lrfdXRangeOfApplicability, LongStiffness, _T("Longitudinal Stiffness Parameter (Kg) is out of range. See Table 4.6.2.2.2b-1"));
         }
      }
   }
   else
   {
      return false;
   }

   return true;
}

bool lrfdLldfTypeAEKIJ::InteriorShearEquationRule(bool bSISpec, bool doThrow) const
{
   if (SpGreaterThan16_Rule(bSISpec))
   {
      assert(!doThrow); // max spacing should be checked before here - we should never throw
      THROW_DF(lrfdXRangeOfApplicability, Spacing, _T("Beam spacing is out of range -too large. See Table 4.6.2.2.2b-1"));
   }

   Float64 smin = ::ConvertToSysUnits( bSISpec ? 1100. : 3.5, bSISpec ? unitMeasure::Millimeter : unitMeasure::Feet);
   if ( m_Savg < smin )
   {
      THROW_DF(lrfdXRangeOfApplicability, Spacing, _T("Beam spacing is out of range -too small. See Table 4.6.2.2.2b-1"));
   }

   Float64 tsmin = ::ConvertToSysUnits( bSISpec ? 100. : 4.5, bSISpec ? unitMeasure::Millimeter : unitMeasure::Inch);
   Float64 tsmax = ::ConvertToSysUnits( bSISpec ? 300. : 12., bSISpec ? unitMeasure::Millimeter : unitMeasure::Inch);
   if ( !InRange( tsmin, m_ts, tsmax ) )
   {
      THROW_DF(lrfdXRangeOfApplicability,SlabDepth, _T("Slab depth is out of range. See Table 4.6.2.2.2b-1"));
   }

   Float64 lmin = ::ConvertToSysUnits( bSISpec ? 6000. : 20., bSISpec ? unitMeasure::Millimeter : unitMeasure::Feet);
   Float64 lmax = ::ConvertToSysUnits( bSISpec ? 73000. : 240., bSISpec ? unitMeasure::Millimeter : unitMeasure::Feet);
   if ( !InRange( lmin, m_L, lmax ) )
   {
      THROW_DF( lrfdXRangeOfApplicability,SpanLength, _T("Span length is out of range. See Table 4.6.2.2.2b-1"));
   }


   return true;
}

bool lrfdLldfTypeAEKIJ::ExteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   // same as for interior moment+
   if ( InteriorMomentEquationRule(bSISpec,doThrow) )
   {
      return DeRule(bSISpec,doThrow);
   }
   else
   {
      return false;
   }

   return true;
}

bool lrfdLldfTypeAEKIJ::DeRule(bool bSISpec, bool doThrow) const
{
   Float64 demin = ::ConvertToSysUnits( bSISpec ? -300. : -1.0, bSISpec ? unitMeasure::Millimeter : unitMeasure::Feet);
   Float64 demax = ::ConvertToSysUnits( bSISpec ? 1700. : 5.5, bSISpec ? unitMeasure::Millimeter : unitMeasure::Feet);

   Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;

   bool bBad_de = false;
   if ( lrfdVersionMgr::SeventhEdition2014 <= lrfdVersionMgr::GetVersion() )
   {
      // begining with LRFD 7th Edition, 2014 de can be less than -1 feet (-300 mm) so only
      // check the upper bound on the value.
      //
      // Note that if de < -1 feet, use -1 feet (see LRFD 4.6.2.2.2d)... also, do the mapping in the calling function
      bBad_de = (demax < de_raw ? true : false);
   }
   else
   {
      bBad_de = InRange(demin,de_raw,demax) ? false : true;
   }

   if ( bBad_de )
   {
      THROW_DF( lrfdXRangeOfApplicability, CurbLineOffset, _T("Curb offset (de) is out of range. See Table 4.6.2.2.2d-1"));
   }
   else
   {
      return true;
   }
}


//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdLldfTypeAEKIJ::AssertValid() const
{
   return lrfdLiveLoadDistributionFactorBase::AssertValid();
}

void lrfdLldfTypeAEKIJ::Dump(dbgDumpContext& os) const
{
   lrfdLiveLoadDistributionFactorBase::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
#include <LRFD\AutoVersion.h>
bool lrfdLldfTypeAEKIJ::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdLldfTypeAEKIJ");

   lrfdAutoVersion av;
   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);

//   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for lrfdLldfTypeAEKIJ");

   Float64 S = ::ConvertToSysUnits( 2000., unitMeasure::Millimeter );
   Float64 de = ::ConvertToSysUnits( 910., unitMeasure::Millimeter );
   Float64 ro = de;
   Float64 wLane = ::ConvertToSysUnits( 3600., unitMeasure::Millimeter );
   Float64 L = ::ConvertToSysUnits( 20000., unitMeasure::Millimeter );
   Float64 ts = ::ConvertToSysUnits( 240., unitMeasure::Millimeter );
   Float64 n = 1.32;
   Float64 I = ::ConvertToSysUnits( 216.9e9, unitMeasure::Millimeter4 );
   Float64 A = ::ConvertToSysUnits( 653587., unitMeasure::Millimeter2 );
   Float64 eg = ::ConvertToSysUnits( 908., unitMeasure::Millimeter );
   Int16 Nb = 5;
   std::vector<Float64> spacings;
   spacings.assign(Nb-1,S);
   Int16 Nl = Int16( (2*de + wLane*(Nb-1))/::ConvertToSysUnits(3000., unitMeasure::Millimeter) );

   lrfdLldfTypeAEKIJ df(1,S,spacings,de,de,Nl,wLane,
                        de,de,L,ts,n,I,A,eg,
                        0.0,0.0,false,false);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.480, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.649, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.846, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.711, 0.001) );
   
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.623, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.721, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.846, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.651, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.3996, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.7050, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI),  0.5193, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI),  0.7050, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.3996, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.7050, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII),  0.5193, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII),  0.7050, 0.001) );

   TESTME_EPILOG("LldfTypeAEKIJ");
}
#endif // _UNITTEST
