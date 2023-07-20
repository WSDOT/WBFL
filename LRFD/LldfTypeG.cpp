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

#include <Lrfd\LldfTypeG.h>
#include <Lrfd\XRangeOfApplicability.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\Utility.h>

using namespace WBFL::LRFD;

LldfTypeG::LldfTypeG(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                             Uint32 Nl, Float64 wLane,
                             Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                             Float64 leftDe,Float64 rightDe,
                             Float64 PossionRatio, 
                             Float64 skewAngle1, Float64 skewAngle2,
                             bool bMomentSkew, bool bShearSkew) :
LiveLoadDistributionFactorBase(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane,bMomentSkew,bShearSkew)
{
   m_L           = L;
   m_W           = W;
   m_I           = I;
   m_J           = J;
   m_b           = b;
   m_d           = d;
   m_LeftDe      = leftDe;
   m_RightDe     = rightDe;
   m_PoissonRatio = PossionRatio;
   m_SkewAngle1  = skewAngle1;
   m_SkewAngle2  = skewAngle2;
}

bool LldfTypeG::TestRangeOfApplicability(Location loc) const
{
   if (!DoCheckApplicablity())
      return true;

   bool doThrow=true;
   bool bSISpec = (LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );

   ExteriorMomentEquationRule(bSISpec, true);

   // This is not an out of range of applicability case... skew adjustment simply isn't applied in this case
   //Float64 skew_delta_max = WBFL::Units::ConvertToSysUnits( 10.0, WBFL::Units::Measure::Degree );
   //if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
   //   THROW_DF( XRangeOfApplicability, SkewAngleDiff, "Excessive difference in skew angles. See Article 4.6.2.2.2e");


   if ( (m_bSkewMoment || m_bSkewShear) && (!IsZero(m_SkewAngle1) || !IsZero(m_SkewAngle2)) )
   {
      // only check this if we have skew
      Float64 Lmin = bSISpec ?  6000 :  20;
      Float64 Lmax = bSISpec ? 37000 : 120;
      Float64 L = WBFL::Units::ConvertFromSysUnits(m_L,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Feet);
      if ( L < Lmin || Lmax < L )
         THROW_DF(XRangeOfApplicability, SpanLength, _T("Span Length (L) is out of range. See Table 4.6.2.2.3c-1"));

      Float64 dMin = bSISpec ?  430 : 17;
      Float64 dMax = bSISpec ? 1500 : 60;
      Float64 d = WBFL::Units::ConvertFromSysUnits(m_d,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Inch);
      if ( d < dMin || dMax < d )
         THROW_DF(XRangeOfApplicability, GirderDepth, _T("Depth (d) of beam is out of range. See Table 4.6.2.2.3c-1"));

      Float64 bMin = bSISpec ?  900 : 35;
      Float64 bMax = bSISpec ? 1500 : 60;
      Float64 b = WBFL::Units::ConvertFromSysUnits(m_b,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Inch);
      if ( b < bMin || bMax < b )
         THROW_DF(XRangeOfApplicability, BeamWidth, _T("Width (b), of beam is out of range. See Table 4.6.2.2.3c-1"));
   }

   return true;
}

bool LldfTypeG::InteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   if ( 6 < m_Nl )
      THROW_DF( XRangeOfApplicability, NumLanes, _T("Excessive number of lanes. See Table 4.6.2.2.2b-1"));

   if ( GetNb() < 4 )
      THROW_DF( XRangeOfApplicability, NumGirders, _T("Number of girders is out of range. Must be >=4, see 4.6.2.2.1"));

   Float64 skew_max = WBFL::Units::ConvertToSysUnits( 45.0, WBFL::Units::Measure::Degree );
   if ( m_bSkewMoment && (!IsLE(m_SkewAngle1,skew_max) || !IsLE(m_SkewAngle2,skew_max)) )
      THROW_DF( XRangeOfApplicability, SkewAngle, _T("Excessive skew angle. See Table 4.6.2.2.2b-1"));

   return true;
}

bool LldfTypeG::ExteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   if (!InteriorMomentEquationRule(bSISpec, doThrow))
      return false;

   Float64 de_max = bSISpec ? WBFL::Units::ConvertToSysUnits(600.,WBFL::Units::Measure::Millimeter) : WBFL::Units::ConvertToSysUnits(2.0,WBFL::Units::Measure::Feet);
   Float64 de_raw = m_Side == DfSide::LeftSide ? m_LeftDe : m_RightDe;

   if ( de_max+1.0e-06 < de_raw )
         THROW_DF( XRangeOfApplicability, CurbLineOffset, _T("Curb offset (de) is out of range. See Table 4.6.2.2.2d-1"));

   return true;
}

bool LldfTypeG::InteriorShearEquationRule(bool bSISpec) const
{
   Float64 bMin = bSISpec ?  900 : 35;
   Float64 bMax = bSISpec ? 1500 : 60;
   Float64 b = WBFL::Units::ConvertFromSysUnits(m_b,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Inch);
   if ( b < bMin || bMax < b )
   {
      return false;
   }

   Float64 Lmin = bSISpec ?  6000 :  20;
   Float64 Lmax = bSISpec ? 37000 : 120;
   Float64 L = WBFL::Units::ConvertFromSysUnits(m_L,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Feet);
   if ( L < Lmin || Lmax < L )
   {
      return false;
   }

   GirderIndexType nb = GetNb();
   if ( nb < 5 || 20 < nb )
   {
      return false;
   }

   return true;
}

bool LldfTypeG::ExteriorShearEquationRule(bool bSISpec) const
{
   if ( !InteriorShearEquationRule(bSISpec) )
      return false;

   Float64 de_max = bSISpec ? WBFL::Units::ConvertToSysUnits(600.,WBFL::Units::Measure::Millimeter) : WBFL::Units::ConvertToSysUnits(2.0,WBFL::Units::Measure::Feet);
   Float64 de_raw = m_Side == DfSide::LeftSide ? m_LeftDe : m_RightDe;

   if ( de_max < de_raw )
         return false;

   return true;
}

bool LldfTypeG::IandJOutOfRangeRule(bool bSISpec) const
{
   Float64 Jmin = bSISpec ? 1.0e10 : 25000;
   Float64 Jmax = bSISpec ? 2.5e11 : 610000;
   Float64 J = WBFL::Units::ConvertFromSysUnits(m_J,bSISpec?WBFL::Units::Measure::Millimeter4:WBFL::Units::Measure::Inch4);
   if ( J < Jmin || Jmax < J )
      return true;

   Float64 Imin = bSISpec ? 1.7e10 : 40000;
   Float64 Imax = bSISpec ? 2.5e11 : 610000;
   Float64 I = WBFL::Units::ConvertFromSysUnits(m_I,bSISpec?WBFL::Units::Measure::Millimeter4:WBFL::Units::Measure::Inch4);
   if ( I < Imin || Imax < I )
      return true;

   return false;
}

ILiveLoadDistributionFactor::DFResult LldfTypeG::GetMomentDF_Int_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI;

   if(m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore || InteriorMomentEquationRule(bSISpec, false) )
   {
      // S/D method
      Float64 J, I, W, S, L;
      Float64 f;
      if ( bSISpec )
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
      g.EqnData.e = 1.0;
      g.EqnData.D = WBFL::Units::ConvertToSysUnits(D, bSISpec? WBFL::Units::Measure::Millimeter : WBFL::Units::Measure::Feet);
      g.EqnData.C = C;
      g.EqnData.K = K;
      g.EqnData.mg = S/D;
      g.EqnData.m = Utility::GetMultiplePresenceFactor(1);
      g.mg = g.EqnData.mg;
   }
   else
   {
      // lever rule
      CHECK(m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::IntGirder, NumLoadedLanes::One,true);
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

ILiveLoadDistributionFactor::DFResult LldfTypeG::GetMomentDF_Int_2_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

ILiveLoadDistributionFactor::DFResult LldfTypeG::GetMomentDF_Ext_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );
   
   if(m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore || ExteriorMomentEquationRule(bSISpec, false) )
   {
      g = GetMomentDF_Int_1_Strength();

      Float64 A = (bSISpec ? 9100 : 30);
      Float64 de_raw = m_Side == DfSide::LeftSide ? m_LeftDe : m_RightDe;
      Float64 de = WBFL::Units::ConvertFromSysUnits(de_raw,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Feet);

      Float64 e = 1.125 + de/A;
      if ( e < 1.0 )
         e = 1.0;

      g.EqnData.e = e;
      g.mg *= e;
      g.ControllingMethod |= E_OVERRIDE;
   }
   else
   {
      // lever rule
      CHECK(m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::One,true);
      g.mg = g.LeverRuleData.mg;

      g.EqnData.e = 1.0;
      Float64 skew = MomentSkewCorrectionFactor();
      if ( m_bSkewMoment )
      {
         g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
      }
      g.SkewCorrectionFactor = skew;
      g.mg *= skew;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult LldfTypeG::GetMomentDF_Ext_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );
   
   if(m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore || ExteriorMomentEquationRule(bSISpec, false) )
   {
      g = GetMomentDF_Int_2_Strength();

      bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );
      Float64 A = (bSISpec ? 7600 : 25);

      Float64 de_raw = m_Side == DfSide::LeftSide ? m_LeftDe : m_RightDe;
      Float64 de = WBFL::Units::ConvertFromSysUnits(de_raw,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Feet);

      Float64 e = 1.04 + de/A;
      if ( e < 1.0 )
         e = 1.0;

      g.EqnData.e = e;
      g.mg *= e;
      g.ControllingMethod |= E_OVERRIDE;
   }
   else
   {
      // lever rule
      CHECK(m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::TwoOrMore,true);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = MomentSkewCorrectionFactor();
      if ( m_bSkewMoment )
      {
         g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
      }
      g.SkewCorrectionFactor = skew;
      g.mg *= skew;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult LldfTypeG::GetShearDF_Int_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );

   if ( InteriorShearEquationRule(bSISpec) )
   {
      if ( !IandJOutOfRangeRule(bSISpec) )
      {
         g.ControllingMethod = SPEC_EQN;
         g.EqnData.bWasUsed = true;

         Float64 b = WBFL::Units::ConvertFromSysUnits(m_b,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Inch);
         Float64 L = WBFL::Units::ConvertFromSysUnits(m_L,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Feet);
         Float64 I = WBFL::Units::ConvertFromSysUnits(m_I,bSISpec?WBFL::Units::Measure::Millimeter4:WBFL::Units::Measure::Inch4);
         Float64 J = WBFL::Units::ConvertFromSysUnits(m_J,bSISpec?WBFL::Units::Measure::Millimeter4:WBFL::Units::Measure::Inch4);

         Float64 K1 = (bSISpec ? 0.7 : 1.0);
         Float64 K2 = (bSISpec ? 1.0 : 130);

         g.EqnData.mg = K1*pow( b/(K2*L), 0.15) * pow( I/J, 0.05 );
         g.EqnData.e = 1.0;
         g.EqnData.m = Utility::GetMultiplePresenceFactor(1);
         g.mg = g.EqnData.mg;
      }
      else
      {
         g = GetMomentDF_Int_1_Strength();
         g.ControllingMethod |= MOMENT_OVERRIDE;

         // Need to remove moment skew factor and apply shear skew
         if (g.SkewCorrectionFactor != 1.0)
         {
            g.mg /= g.SkewCorrectionFactor;
            g.SkewCorrectionFactor = 1.0;
         }
      }
   }
   else
   {
      // default to lever rule
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::IntGirder, NumLoadedLanes::One, true);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg *= skew;

   return g;
}

ILiveLoadDistributionFactor::DFResult  LldfTypeG::GetShearDF_Int_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );

   if ( InteriorShearEquationRule(bSISpec) )
   {
      if ( !IandJOutOfRangeRule(bSISpec) )
      {
         g.ControllingMethod = SPEC_EQN;
         g.EqnData.bWasUsed = true;

         Float64 b = WBFL::Units::ConvertFromSysUnits(m_b,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Inch);
         Float64 L = WBFL::Units::ConvertFromSysUnits(m_L,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Feet);
         Float64 I = WBFL::Units::ConvertFromSysUnits(m_I,bSISpec?WBFL::Units::Measure::Millimeter4:WBFL::Units::Measure::Inch4);
         Float64 J = WBFL::Units::ConvertFromSysUnits(m_J,bSISpec?WBFL::Units::Measure::Millimeter4:WBFL::Units::Measure::Inch4);

         Float64 K1 = (bSISpec ? 4000 : 156);
         Float64 K2 = (bSISpec ? 1.0 : 12);
         Float64 K3 = (bSISpec ? 1200 : 48);

         Float64 K4 = b/K3;
         if ( K4 < 1.0 )
            K4 = 1.0;

         g.EqnData.mg = pow(b/K1,0.4) * pow(b/(K2*L),0.1) * pow(I/J,0.05) * K4;
         g.EqnData.e = 1.0;
         g.EqnData.m = Utility::GetMultiplePresenceFactor(2);
         g.mg = g.EqnData.mg;
      }
      else
      {
         g = GetMomentDF_Int_2_Strength();
         g.ControllingMethod |= MOMENT_OVERRIDE;

         // Need to remove moment skew factor and apply shear skew
         if (g.SkewCorrectionFactor != 1.0)
         {
            g.mg /= g.SkewCorrectionFactor;
            g.SkewCorrectionFactor = 1.0;
         }
      }
   }
   else
   {
      // default to lever rule
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::IntGirder, NumLoadedLanes::TwoOrMore, true);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }
   g.SkewCorrectionFactor = skew;
   g.mg *= skew;

   return g;
}

ILiveLoadDistributionFactor::DFResult LldfTypeG::GetShearDF_Ext_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;
   
   bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );

   if ( ExteriorShearEquationRule(bSISpec) )
   {
      g = GetShearDF_Int_1_Strength(); // will use the moment LLDF if I and J rule is violated

      if (g.ControllingMethod & SPEC_EQN)
      {
         // only apply e factor to equation method
         bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );
         Float64 de_raw = m_Side == DfSide::LeftSide ? m_LeftDe : m_RightDe;
         Float64 de = WBFL::Units::ConvertFromSysUnits(de_raw,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Feet);
         Float64 K = (bSISpec ? 6100 : 20);

         Float64 e = 1.25 + de/K;
         if ( e < 1 )
            e = 1.0;

         g.ControllingMethod |= E_OVERRIDE;
         g.EqnData.e = e;
         g.mg *= e;
      }
      else
      {
         CHECK(0); // should always be using equation unless rules are screwed up.
      }
   }
   else
   {
      // default to lever rule
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::One, true);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = ShearSkewCorrectionFactor();
      if ( m_bSkewShear )
      {
         g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
      }
      g.SkewCorrectionFactor = skew;
      g.mg *= skew;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult LldfTypeG::GetShearDF_Ext_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;
   
   bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );

   if ( ExteriorShearEquationRule(bSISpec) )
   {
      g = GetShearDF_Int_2_Strength(); // will use the moment LLDF if I and J rule is violated

      if (g.ControllingMethod & SPEC_EQN)
      {
         // only use e factor for equation methods
         bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );

         Float64 de_raw = m_Side == DfSide::LeftSide ? m_LeftDe : m_RightDe;
         Float64 de = WBFL::Units::ConvertFromSysUnits(de_raw,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Feet);

         Float64 b  = WBFL::Units::ConvertFromSysUnits(m_b, bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Inch);

         Float64 K1 = (bSISpec ?  1200 : 48);
         Float64 K2 = (bSISpec ?     1 : 12);
         Float64 K3 = (bSISpec ?   610 :  2);
         Float64 K4 = (bSISpec ? 12200 : 40);

         Float64 K5 = K1/b;
         if ( 1 < K5 )
            K5 = 1.0;

         Float64 K6 = (de + b/K2 - K3)/K4;

         if ( K6 < 0 )
            K6 = 0; // This isn't in AASHTO, but we don't want to take the square root of a negative number

         Float64 e = 1 + pow(K6,0.5);

         if ( e < 1 )
            e = 1.0;

         // HACK: put 48/b factor in e, although it's not technically part in spec
         g.EqnData.K = K5; // Need for reporting, this is awful, but don't see any better hacks
         e *= K5;

         g.EqnData.e = e;
         g.mg *= e;
         g.ControllingMethod |= E_OVERRIDE;
      }
      else
      {
         CHECK(0); // rules messed up?
      }
   }
   else
   {
      // default to lever rule
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::TwoOrMore, true);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = ShearSkewCorrectionFactor();
      if ( m_bSkewShear )
      {
         g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
      }
      g.SkewCorrectionFactor = skew;
      g.mg *= skew;
   }

   return g;
}

Float64 LldfTypeG::MomentSkewCorrectionFactor() const
{
   if ( !m_bSkewMoment )
   {
      return 1.0;
   }

   // 4.6.2.2.2e - don't reduce moment if difference in skew is > 10 degree
   Float64 skew_delta_max = WBFL::Units::ConvertToSysUnits( 10.0, WBFL::Units::Measure::Degree );
   if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
      return 1.0;

   Float64 avg_skew_angle = fabs(m_SkewAngle1 + m_SkewAngle2)/2.;

   if ( IsZero(avg_skew_angle) )
      return 1.0;

   if ( WBFL::Units::ConvertToSysUnits(60.,WBFL::Units::Measure::Degree) < avg_skew_angle)
      avg_skew_angle = WBFL::Units::ConvertToSysUnits(60.,WBFL::Units::Measure::Degree);


   Float64 skew = 1.05 - 0.25*tan(WBFL::Units::ConvertFromSysUnits(avg_skew_angle,WBFL::Units::Measure::Radian));

   return skew;
}

Float64 LldfTypeG::ShearSkewCorrectionFactor() const
{
   if ( !m_bSkewShear )
   {
      return 1.0;
   }

   Float64 avg_skew_angle = fabs(m_SkewAngle1 + m_SkewAngle2)/2.;

   if ( IsZero(avg_skew_angle) )
      return 1.0;


   Float64 skew = 1.0 + (m_L/(90*m_d))*(sqrt(tan(WBFL::Units::ConvertFromSysUnits(avg_skew_angle,WBFL::Units::Measure::Radian))));

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


/****************************************************************************
CLASS
   LldfTypeF
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
LldfTypeF::LldfTypeF(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                             Uint32 Nl, Float64 wLane,
                             Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                             Float64 leftDe,Float64 rightDe,
                             Float64 PossionRatio, 
                             Float64 skewAngle1, Float64 skewAngle2,
                             bool bMomentSkew, bool bShearSkew) :
LldfTypeG(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane,
              L,W,I,J,b,d,leftDe,rightDe,PossionRatio, 
              skewAngle1, skewAngle2,
              bMomentSkew, bShearSkew)
{
}

ILiveLoadDistributionFactor::DFResult LldfTypeF::GetMomentDF_Int_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );

   if ( m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore || InteriorMomentEquationRule(bSISpec,false) )
   {
      Float64 b = WBFL::Units::ConvertFromSysUnits(m_b,bSISpec ? WBFL::Units::Measure::Millimeter  : WBFL::Units::Measure::Inch);
      Float64 L = WBFL::Units::ConvertFromSysUnits(m_L,bSISpec ? WBFL::Units::Measure::Millimeter  : WBFL::Units::Measure::Feet);
      Float64 I = WBFL::Units::ConvertFromSysUnits(m_I,bSISpec ? WBFL::Units::Measure::Millimeter4 : WBFL::Units::Measure::Inch4);
      Float64 J = WBFL::Units::ConvertFromSysUnits(m_J,bSISpec ? WBFL::Units::Measure::Millimeter4 : WBFL::Units::Measure::Inch4);

      Float64 K = (bSISpec ? 2.8 : 33.3);

      Float64 k = 2.5*pow((Float64)GetNb(), -0.2);
      if ( k < 1.5 )
         k = 1.5;

      Float64 mg = k*pow(b/(K*L),0.5)*pow(I/J,0.25);

      g.ControllingMethod = SPEC_EQN;
      g.EqnData.bWasUsed = true;
      g.EqnData.e = 1.0;
      g.EqnData.m = Utility::GetMultiplePresenceFactor(1);
      g.EqnData.mg = mg;
      g.mg = g.EqnData.mg;
   }
   else
   {
      // lever rule
      CHECK(m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
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

ILiveLoadDistributionFactor::DFResult LldfTypeF::GetMomentDF_Int_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );

   if ( m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore || InteriorMomentEquationRule(bSISpec,false) )
   {
      Float64 b = WBFL::Units::ConvertFromSysUnits(m_b,bSISpec ? WBFL::Units::Measure::Millimeter  : WBFL::Units::Measure::Inch);
      Float64 L = WBFL::Units::ConvertFromSysUnits(m_L,bSISpec ? WBFL::Units::Measure::Millimeter  : WBFL::Units::Measure::Feet);
      Float64 I = WBFL::Units::ConvertFromSysUnits(m_I,bSISpec ? WBFL::Units::Measure::Millimeter4 : WBFL::Units::Measure::Inch4);
      Float64 J = WBFL::Units::ConvertFromSysUnits(m_J,bSISpec ? WBFL::Units::Measure::Millimeter4 : WBFL::Units::Measure::Inch4);

      Float64 K1 = (bSISpec ? 7600 : 305);
      Float64 K2 = (bSISpec ?    1 :  12);

      Float64 k = 2.5*pow((Float64)GetNb(),-0.2);
      if ( k < 1.5 )
         k = 1.5;

      Float64 mg = k*pow(b/K1,0.6)*pow(b/(K2*L),0.2)*pow(I/J,0.06);

      g.ControllingMethod = SPEC_EQN;
      g.EqnData.e = 1.0;
      g.EqnData.bWasUsed = true;
      g.EqnData.m = Utility::GetMultiplePresenceFactor(2);
      g.EqnData.mg = mg;
      g.mg = mg;
   }
   else
   {
      // lever rule
      CHECK(m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::IntGirder, NumLoadedLanes::TwoOrMore, true);
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

bool LldfTypeF::TestRangeOfApplicability(Location loc) const
{
   if (!DoCheckApplicablity())
      return true;

   bool bSISpec = (LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );
   bool doThrow=true;

   // most rules are for exterior moment
   ExteriorMomentEquationRule(bSISpec, doThrow);

   // if we have skew
   if ( (m_bSkewMoment || m_bSkewShear) && (!IsZero(m_SkewAngle1) || !IsZero(m_SkewAngle2)) )
   {
      Float64 skew_max = WBFL::Units::ConvertToSysUnits( 60.0, WBFL::Units::Measure::Degree );
      if ( !IsLE(m_SkewAngle1,skew_max) || !IsLE(m_SkewAngle2,skew_max) )
         THROW_DF( XRangeOfApplicability, SkewAngle, _T("Excessive skew angle. See Table 4.6.2.2.3c-1"));

      Float64 skew_delta_max = WBFL::Units::ConvertToSysUnits( 10.0, WBFL::Units::Measure::Degree );
      if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
         THROW_DF( XRangeOfApplicability, SkewAngleDiff, _T("Excessive difference in skew angles. See Article 4.6.2.2.2e"));

      // the depth range is only appicable if Table 4.6.2.2.3c-1 is used
      Float64 dMin = bSISpec ?  430 : 17;
      Float64 dMax = bSISpec ? 1500 : 60;
      Float64 d = WBFL::Units::ConvertFromSysUnits(m_d,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Inch);
      if ( d < dMin || dMax < d )
         THROW_DF(XRangeOfApplicability, GirderDepth, _T("Depth (d) of beam is out of range. See Table 4.6.2.2.3c-1"));
   }
   
   return true;
}

bool LldfTypeF::InteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   Float64 bMin = bSISpec ?  900 : 35;
   Float64 bMax = bSISpec ? 1500 : 60;
   Float64 b = WBFL::Units::ConvertFromSysUnits(m_b,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Inch);
   if ( b < bMin || bMax < b )
      THROW_DF(XRangeOfApplicability, BeamWidth, _T("Width (b), of beam is out of range. See Table 4.6.2.2.3a-1"));

   Float64 Lmin = bSISpec ?  6000 :  20;
   Float64 Lmax = bSISpec ? 37000 : 120;
   Float64 L = WBFL::Units::ConvertFromSysUnits(m_L,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Feet);
   if ( L < Lmin || Lmax < L )
      THROW_DF(XRangeOfApplicability, SpanLength, _T("Span Length (L) is out of range. See Table 4.6.2.2.3a-1"));

   GirderIndexType nb = GetNb();
   if ( nb < 5 || 20 < nb )
      THROW_DF(XRangeOfApplicability, NumGirders, _T("Number of girders is out of range (5<=Ng<=20). See Table 4.6.2.2.3a-1"));

   return true;
}

//======================== DEBUG      =======================================

/****************************************************************************
CLASS
   TxdotVoidedSlab
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
TxdotVoidedSlab::TxdotVoidedSlab(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                 Uint32 Nl, Float64 wLane,
                 Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                 Float64 leftDe,Float64 rightDe,
                 Float64 PossionRatio,
                 Float64 skewAngle1, Float64 skewAngle2):
// Txdot ignores skew
LldfTypeG(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane,
              L,W,I,J,b,d,leftDe,rightDe,PossionRatio, 
              skewAngle1, skewAngle2, false, false)
{
}

Float64 TxdotVoidedSlab::MomentSkewCorrectionFactor() const
{
   // for Txdot we don't correct for skew
   return 1.0; 
}

Float64 TxdotVoidedSlab::ShearSkewCorrectionFactor() const
{
   // for Txdot we don't correct for skew
   return 1.0; 
}

ILiveLoadDistributionFactor::DFResult TxdotVoidedSlab::GetMomentDF_Int_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   g = LldfTypeG::GetMomentDF_Int_1_Strength();

   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotVoidedSlab::GetMomentDF_Ext_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;
   bool bSISpec = LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI;

   // Lever rule must be applied at this level if ROA exceeded
   bool brule = ExteriorMomentEquationRule(bSISpec, false);

   if(m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::IgnoreUseLeverRule && !brule)
   {
      // lever rule
      CHECK(m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::One, true);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = MomentSkewCorrectionFactor();
      if ( m_bSkewMoment )
      {
         g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
      }
      g.SkewCorrectionFactor = skew;
      g.mg *= skew;
   }
   else
   {
      // Use interior rule if within
      g = LldfTypeG::GetMomentDF_Int_1_Strength();
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotVoidedSlab::GetMomentDF_Ext_2_Strength() const
{

   // Txdot uses single lane exterior moment for all 
   ILiveLoadDistributionFactor::DFResult g = GetMomentDF_Ext_1_Strength();
   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotVoidedSlab::GetShearDF_Int_1_Strength() const
{
   // Txdot uses single lane exterior moment for all 
   ILiveLoadDistributionFactor::DFResult g = GetMomentDF_Int_1_Strength();
   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotVoidedSlab::GetShearDF_Int_2_Strength() const
{
   // Txdot uses single lane exterior moment for all 
   ILiveLoadDistributionFactor::DFResult g = GetMomentDF_Int_1_Strength();
   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotVoidedSlab::GetShearDF_Ext_1_Strength() const
{
   // Txdot uses single lane exterior moment for all 
   ILiveLoadDistributionFactor::DFResult g = GetMomentDF_Ext_1_Strength();
   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotVoidedSlab::GetShearDF_Ext_2_Strength() const
{
   // Txdot uses single lane exterior moment for all 
   ILiveLoadDistributionFactor::DFResult g = GetMomentDF_Ext_1_Strength();
   return g;
}

bool TxdotVoidedSlab::TestRangeOfApplicability(Location loc) const
{
   if (!DoCheckApplicablity())
      return true;

   bool doThrow=true;
   Float64 w2 = m_b/2.0; // half of girder width
   if (DfSide::LeftSide == m_Side && m_LeftCurbOverhang-w2 >  TOLERANCE ||
       DfSide::RightSide== m_Side && m_RightCurbOverhang-w2 > TOLERANCE)
   {
      THROW_DF(XRangeOfApplicability, CurbLineOffset, _T("The TxDOT live load distribution factor method does not allow for deck overhangs on slab beams. To fix this you can input factors manually or change settings to ignore the range of applicability requirements."));
   }

   return LldfTypeG::TestRangeOfApplicability(loc);
}

bool TxdotVoidedSlab::InteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   if (!LldfTypeG::InteriorMomentEquationRule(bSISpec, doThrow))
      return false;

   Float64 w2 = m_b/2.0; // half of girder width
   if (DfSide::LeftSide == m_Side && m_LeftCurbOverhang-w2 >  TOLERANCE ||
       DfSide::RightSide== m_Side && m_RightCurbOverhang-w2 > TOLERANCE)
   {
      THROW_DF(XRangeOfApplicability, CurbLineOffset, _T("The TxDOT live load distribution factor method does not allow for deck overhangs on slab beams. To fix this you can input factors manually or change settings to ignore the range of applicability requirements."));
   }

   return true;
}

bool TxdotVoidedSlab::ExteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   if (!LldfTypeG::ExteriorMomentEquationRule(bSISpec, doThrow))
      return false;

   Float64 w2 = m_b/2.0; // half of girder width
   if (DfSide::LeftSide == m_Side && m_LeftCurbOverhang-w2 >  TOLERANCE ||
       DfSide::RightSide== m_Side && m_RightCurbOverhang-w2 > TOLERANCE)
   {
      THROW_DF(XRangeOfApplicability, CurbLineOffset, _T("The TxDOT live load distribution factor method does not allow for deck overhangs on slab beams. To fix this you can input factors manually or change settings to ignore the range of applicability requirements."));
   }

   return true;
}

////////////////////////////////////////////////

TxdotLldfAdjacentBox::TxdotLldfAdjacentBox(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                            Uint32 Nl, Float64 wLane,
                            Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                            Float64 leftDe,Float64 rightDe,
                            Float64 PossionRatio,
                            Float64 skewAngle1, Float64 skewAngle2):
LldfTypeF(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,
              Nl,wLane,L,W,I,J,b,d,
              leftDe,rightDe,PossionRatio,
              skewAngle1,skewAngle2,true,true)
{
}

Float64 TxdotLldfAdjacentBox::MomentSkewCorrectionFactor() const
{
   // for Txdot we don't correct for skew
   return 1.0; 
}

ILiveLoadDistributionFactor::DFResult TxdotLldfAdjacentBox::GetMomentDF_Ext_1_Strength() const
{
   // always connected as unit (type f)
   ILiveLoadDistributionFactor::DFResult gext = LldfTypeF::GetMomentDF_Ext_1_Strength();

   ILiveLoadDistributionFactor::DFResult gint = LldfTypeF::GetMomentDF_Int_1_Strength();
   if (gext.mg < gint.mg)
   {
      // exterior cannot exceed interior
      gext.ControllingMethod |= INTERIOR_OVERRIDE;
      gext.mg = gint.mg;
   }

   return gext;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfAdjacentBox::GetMomentDF_Ext_2_Strength() const
{
   // always connected as unit (type f)
   ILiveLoadDistributionFactor::DFResult gext = LldfTypeF::GetMomentDF_Ext_2_Strength();

   ILiveLoadDistributionFactor::DFResult gint = LldfTypeF::GetMomentDF_Int_2_Strength();
   if (gext.mg < gint.mg)
   {
      // exterior cannot exceed interior
      gext.ControllingMethod |= INTERIOR_OVERRIDE;
      gext.mg = gint.mg;
   }

   return gext;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfAdjacentBox::GetBaseShearDF_Ext_1_Strength() const
{
   // NOTE: WSDOT changed LldfTypeG::GetShearDF_Ext_1_Strength() to better match the common interpretation of AASHTO.
   // This returned a different results than previous versions, as such TxdotLldfAdjacentBox::GetShearDF_Ext_1_Strength()
   // could no longer call that method to get the LLDF. This function is a copy of the old LldfTypeG::GetShearDF_Ext_1_Strength()
   // so the TxDOT interpretation does not change
   ILiveLoadDistributionFactor::DFResult g;
   
   bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );

   if ( ExteriorShearEquationRule(bSISpec) )
   {
      if ( !IandJOutOfRangeRule(bSISpec) )
      {
         g = GetShearDF_Int_1_Strength();

         if (g.ControllingMethod & SPEC_EQN)
         {
            // only apply e factor to equation method
            bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );
            Float64 de_raw = m_Side == DfSide::LeftSide ? m_LeftDe : m_RightDe;
            Float64 de = WBFL::Units::ConvertFromSysUnits(de_raw,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Feet);
            Float64 K = (bSISpec ? 6100 : 20);

            Float64 e = 1.25 + de/K;
            if ( e < 1 )
               e = 1.0;

            g.ControllingMethod |= E_OVERRIDE;
            g.EqnData.e = e;
            g.mg *= e;
         }
         else
         {
            CHECK(0); // should always be using equation unless rules are screwed up.
         }
      }
      else
      {
         // After much discussion with TxDOT and pouring over the spec, we have decided to be
         // consistant with the interior shear rule and use the moment factor if I/J is out of 
         // range. Yet another hole in the spec...
         g = GetMomentDF_Ext_1_Strength();
         g.ControllingMethod |= MOMENT_OVERRIDE;

         // Need to remove moment skew factor and apply shear skew
         g.mg /= g.SkewCorrectionFactor;
         g.SkewCorrectionFactor = 1.0;

         Float64 skew = ShearSkewCorrectionFactor();
         if ( m_bSkewShear )
         {
            g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
         }
         g.SkewCorrectionFactor = skew;
         g.mg *= skew;
      }
   }
   else
   {
      // default to lever rule
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::One, true);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = ShearSkewCorrectionFactor();
      if ( m_bSkewShear )
      {
         g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
      }
      g.SkewCorrectionFactor = skew;
      g.mg *= skew;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfAdjacentBox::GetShearDF_Ext_1_Strength() const
{
   // always connected as unit (type f)
   ILiveLoadDistributionFactor::DFResult gext = GetBaseShearDF_Ext_1_Strength();

   ILiveLoadDistributionFactor::DFResult gint = LldfTypeF::GetShearDF_Int_1_Strength();
   if (gext.mg < gint.mg)
   {
      // exterior cannot exceed interior
      gext.ControllingMethod |= INTERIOR_OVERRIDE;
      gext.mg = gint.mg;
   }

   return gext;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfAdjacentBox::GetBaseShearDF_Ext_2_Strength() const
{
   // NOTE: WSDOT changed LldfTypeG::GetShearDF_Ext_2_Strength() to better match the common interpretation of AASHTO.
   // This returned a different results than previous versions, as such TxdotLldfAdjacentBox::GetShearDF_Ext_2_Strength()
   // could no longer call that method to get the LLDF. This function is a copy of the old LldfTypeG::GetShearDF_Ext_2_Strength()
   // so the TxDOT interpretation does not change
   ILiveLoadDistributionFactor::DFResult g;
   
   bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );

   if ( ExteriorShearEquationRule(bSISpec) )
   {

      if ( !IandJOutOfRangeRule(bSISpec) )
      {

         g = GetShearDF_Int_2_Strength();

         if (g.ControllingMethod & SPEC_EQN)
         {
            // only use e factor for equation methods
            bool bSISpec = ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI );

            Float64 de_raw = m_Side == DfSide::LeftSide ? m_LeftDe : m_RightDe;
            Float64 de = WBFL::Units::ConvertFromSysUnits(de_raw,bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Feet);

            Float64 b  = WBFL::Units::ConvertFromSysUnits(m_b, bSISpec?WBFL::Units::Measure::Millimeter:WBFL::Units::Measure::Inch);

            Float64 K1 = (bSISpec ?  1200 : 48);
            Float64 K2 = (bSISpec ?     1 : 12);
            Float64 K3 = (bSISpec ?   610 :  2);
            Float64 K4 = (bSISpec ? 12200 : 40);

            Float64 K5 = K1/b;
            if ( 1 < K5 )
               K5 = 1.0;

            Float64 K6 = (de + b/K2 - K3)/K4;

            if ( K6 < 0 )
               K6 = 0; // This isn't in AASHTO, but we don't want to take the square root of a negative number

            Float64 e = 1 + pow(K6,0.5);

            if ( e < 1 )
               e = 1.0;

            // HACK: put 48/b factor in e, although it's not technically part in spec
            g.EqnData.K = K5; // Need for reporting, this is awful, but don't see any better hacks
            e *= K5;

            g.EqnData.e = e;
            g.mg *= e;
            g.ControllingMethod |= E_OVERRIDE;
         }
         else
         {
            CHECK(0); // rules messed up?
         }
      }
      else
      {
         // After much discussion with TxDOT and pouring over the spec, we have decided to be
         // consistant with the interior shear rule and use the moment factor if I/J is out of 
         // range. Yet another hole in the spec...
         g = GetMomentDF_Ext_2_Strength();
         g.ControllingMethod |= MOMENT_OVERRIDE;

         // Need to remove moment skew factor and apply shear skew
         g.mg /= g.SkewCorrectionFactor;
         g.SkewCorrectionFactor = 1.0;

         Float64 skew = ShearSkewCorrectionFactor();
         if ( m_bSkewShear )
         {
            g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
         }
         g.SkewCorrectionFactor = skew;
         g.mg *= skew;
      }
   }
   else
   {
      // default to lever rule
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::TwoOrMore, true);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = ShearSkewCorrectionFactor();
      if ( m_bSkewShear )
      {
         g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
      }
      g.SkewCorrectionFactor = skew;
      g.mg *= skew;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfAdjacentBox::GetShearDF_Ext_2_Strength() const
{
   // always connected as unit (type f)
   ILiveLoadDistributionFactor::DFResult gext = GetBaseShearDF_Ext_2_Strength();

   ILiveLoadDistributionFactor::DFResult gint = LldfTypeF::GetShearDF_Int_2_Strength();
   if (gext.mg < gint.mg)
   {
      // exterior cannot exceed interior
      gext.ControllingMethod |= INTERIOR_OVERRIDE;
      gext.mg = gint.mg;
   }

   return gext;
}
