///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <Lrfd/BDSManager.h>
#include <Lrfd\Utility.h>

using namespace WBFL::LRFD;

LldfTypeHIJ::LldfTypeHIJ(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                                 Uint32 Nl, Float64 wLane,
                                 Float64 L,Float64 W,Float64 I,Float64 J,Float64 PoissonRatio,
                                 Float64 leftDe,Float64 rightDe,
                                 Float64 skewAngle1, Float64 skewAngle2,
                                 bool bMomentSkew, bool bShearSkew) :
LiveLoadDistributionFactorBase(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane,bMomentSkew,bShearSkew)
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

bool LldfTypeHIJ::TestRangeOfApplicability(Location loc) const
{
   if (!DoCheckApplicablity())
      return true;

   bool bSISpec = (BDSManager::GetUnits() == BDSManager::Units::SI );
   bool doThrow=true;

   if (!InteriorMomentEquationRule(bSISpec, true))
      return false;

   if (!IsZero(m_SkewAngle1) || !IsZero(m_SkewAngle2))
   {
      // NOTE: In LRFD 7th Edition, 2014 Table 4.6.2.2.2e-1 was expanded to include type i and j if connected to prevent vertical displacements
      // however, Table 4.6.2.2.3c was not updated and therefore skew is still not applicable to this type of girder.
      if (BDSManager::GetEdition() < BDSManager::Edition::SeventhEdition2014)
      {
         THROW_DF(XRangeOfApplicability, SkewAngle, _T("Skew corrections are not defined for this girder type. See 4.6.2.2.2e"));
      }
      else
      {
         THROW_DF(XRangeOfApplicability, SkewAngle, _T("Skew corrections are not defined for this girder type. See 4.6.2.2.3c"));
      }
   }

   // This is not an out of range of applicability case... skew adjustment simply isn't applied in this case
   //Float64 skew_delta_max = WBFL::Units::ConvertToSysUnits( 10.0, WBFL::Units::Measure::Degree );
   //if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
   //   THROW_DF( XRangeOfApplicability, SkewAngleDiff, "Excessive difference in skew angles. See Article 4.6.2.2.2e");

   return true;
}

bool LldfTypeHIJ::InteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   if ( 6 < m_Nl )
      THROW_DF( XRangeOfApplicability, NumLanes, _T("Excessive number of lanes. See Table 4.6.2.2.2b-1"));

   Float64 skew_max = WBFL::Units::ConvertToSysUnits( 45.0, WBFL::Units::Measure::Degree );
   if ( !IsLE(m_SkewAngle1,skew_max) || !IsLE(m_SkewAngle2,skew_max) )
      THROW_DF( XRangeOfApplicability, SkewAngle, _T("Excessive skew angle. See Table 4.6.2.2.2b-1"));

   if ( GetNb() < 4 )
      THROW_DF( XRangeOfApplicability, NumGirders, _T("Number of girders is out of range. Must be >=4, see 4.6.2.2.1"));

   return true;
}


ILiveLoadDistributionFactor::DFResult LldfTypeHIJ::GetMomentDF_Int_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;
   bool bSISpec = BDSManager::GetUnits() == BDSManager::Units::SI;

   if( m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore || InteriorMomentEquationRule(bSISpec, false) )
   {
      Float64 J, I, W, S, L;
      Float64 f;
      bool bSI = BDSManager::GetUnits() == BDSManager::Units::SI;
      if ( bSI )
      {
         J = WBFL::Units::ConvertFromSysUnits(m_J,WBFL::Units::Measure::Millimeter4);
         I = WBFL::Units::ConvertFromSysUnits(m_I,WBFL::Units::Measure::Millimeter4);
         W = WBFL::Units::ConvertFromSysUnits(m_W,WBFL::Units::Measure::Millimeter);
         S = WBFL::Units::ConvertFromSysUnits(m_Savg,WBFL::Units::Measure::Millimeter);
         L = WBFL::Units::ConvertFromSysUnits(m_L,WBFL::Units::Measure::Millimeter);
         f = 300;
      }
      else
      {
         J = WBFL::Units::ConvertFromSysUnits(m_J,WBFL::Units::Measure::Inch4);
         I = WBFL::Units::ConvertFromSysUnits(m_I,WBFL::Units::Measure::Inch4);
         W = WBFL::Units::ConvertFromSysUnits(m_W,WBFL::Units::Measure::Feet);
         S = WBFL::Units::ConvertFromSysUnits(m_Savg,WBFL::Units::Measure::Feet);
         L = WBFL::Units::ConvertFromSysUnits(m_L,WBFL::Units::Measure::Feet);
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
      g.EqnData.D = WBFL::Units::ConvertToSysUnits(D,bSI? WBFL::Units::Measure::Millimeter : WBFL::Units::Measure::Feet);;
      g.EqnData.C = C;
      g.EqnData.K = K;
      g.EqnData.e = 1.0;
      g.EqnData.m = Utility::GetMultiplePresenceFactor(1);
      g.EqnData.mg = S/D;
      g.mg = g.EqnData.mg;
   }
   else
   {
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::IntGirder, NumLoadedLanes::One, true);
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

ILiveLoadDistributionFactor::DFResult LldfTypeHIJ::GetMomentDF_Int_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g = GetMomentDF_Int_1_Strength();

   if (g.ControllingMethod & LEVER_RULE)
   {
      // needs to be multiple lane
      g.LeverRuleData = DistributeByLeverRuleEx(Location::IntGirder, NumLoadedLanes::TwoOrMore, true);
      g.mg = g.LeverRuleData.mg * g.SkewCorrectionFactor;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult LldfTypeHIJ::GetMomentDF_Ext_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::One, true);
   Float64 skew = MomentSkewCorrectionFactor();
   if ( m_bSkewMoment )
   {
      g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.LeverRuleData.mg;

   return g;
}

ILiveLoadDistributionFactor::DFResult LldfTypeHIJ::GetMomentDF_Ext_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::TwoOrMore, true);

   Float64 skew = MomentSkewCorrectionFactor();
   if ( m_bSkewMoment )
   {
      g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.LeverRuleData.mg;
   return g;
}

ILiveLoadDistributionFactor::DFResult LldfTypeHIJ::GetShearDF_Int_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;


   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(Location::IntGirder, NumLoadedLanes::One, true);

   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.LeverRuleData.mg;

   return g;
}

ILiveLoadDistributionFactor::DFResult  LldfTypeHIJ::GetShearDF_Int_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(Location::IntGirder, NumLoadedLanes::TwoOrMore, true);

   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.LeverRuleData.mg;
   return g;
}

ILiveLoadDistributionFactor::DFResult LldfTypeHIJ::GetShearDF_Ext_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::One, true);

   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.LeverRuleData.mg;

   return g;
}

ILiveLoadDistributionFactor::DFResult LldfTypeHIJ::GetShearDF_Ext_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::TwoOrMore, true);

   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.LeverRuleData.mg;
   return g;
}

Float64 LldfTypeHIJ::MomentSkewCorrectionFactor() const
{
   if ( !m_bSkewMoment )
   {
      return 1.0;
   }

   Float64 skew = 1.0;  // no skew correction given in AASHTO, before 7th edition

   if ( BDSManager::Edition::SeventhEdition2014 <= BDSManager::GetEdition() )
   {
      // LRFD 7th Edition 2014 added skew correction for moment for type h,i,j sections
      
      // 4.6.2.2.2e - don't reduce moment if difference in skew is > 10 degree
      Float64 skew_delta_max = WBFL::Units::ConvertToSysUnits( 10.0, WBFL::Units::Measure::Degree );
      if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
      {
         return 1.0;
      }

      Float64 avg_skew_angle = fabs(m_SkewAngle1 + m_SkewAngle2)/2.;

      Float64 deg60 = WBFL::Units::ConvertToSysUnits(60.,WBFL::Units::Measure::Degree);
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

Float64 LldfTypeHIJ::ShearSkewCorrectionFactor() const
{
   return 1.0; // no skew correction given in AASHTO
}
