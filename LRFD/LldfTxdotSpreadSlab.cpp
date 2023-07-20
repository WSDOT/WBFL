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
#include <Lrfd\LldfTxdotSpreadSlab.h>
#include <Lrfd\XRangeOfApplicability.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\Utility.h>

using namespace WBFL::LRFD;

TxdotLldfSpreadSlab::TxdotLldfSpreadSlab(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                                             Uint32 Nl, Float64 wLane,
                                             Float64 d, Float64 L, Float64 ts,
                                             Float64 skewAngle1, Float64 skewAngle2) :
LiveLoadDistributionFactorBase(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane,false,false)
{
   m_d           = d;
   m_L           = L;
   m_ts          = ts;
   m_SkewAngle1  = skewAngle1;
   m_SkewAngle2  = skewAngle2;
}

bool TxdotLldfSpreadSlab::TestRangeOfApplicability(Location loc) const
{

   // only return if we are throwing for range error
   if (!DoCheckApplicablity())
      return true;

   return DoTestRangeOfApplicability(true);
}

bool TxdotLldfSpreadSlab::DoTestRangeOfApplicability(bool doThrow) const
{
   Float64 L = WBFL::Units::ConvertFromSysUnits(m_L,WBFL::Units::Measure::Feet);

   if ( IsLT(L, 31.0) )
      THROW_DF( XRangeOfApplicability, SpanLength, _T("Span length is too short. Must be greater or equal to 31.0 ft"));

   if ( IsGT(51.0, L) )
      THROW_DF( XRangeOfApplicability, SpanLength, _T("Span length is too long. Must be less than or equal to 51.0 ft"));

   Float64 S = WBFL::Units::ConvertFromSysUnits(m_Savg,WBFL::Units::Measure::Feet);

   if ( IsLT(S, 6.5) )
      THROW_DF( XRangeOfApplicability, Spacing, _T("Girder spacing is too small. Must be greater than or equal to 6.5 ft"));

   if ( IsGT(11.0, S) )
      THROW_DF( XRangeOfApplicability, Spacing, _T("Girder spacing is too large. Must be less than or equal to 11.0 ft"));

   Float64 d = WBFL::Units::ConvertFromSysUnits(m_d,WBFL::Units::Measure::Inch);

   if ( IsLT(d, 12.0) )
      THROW_DF( XRangeOfApplicability, GirderDepth, _T("Girder depth is too small. Must be greater than or equal to 12.0 in"));

   if ( IsGT(21.0, d) )
      THROW_DF( XRangeOfApplicability, GirderDepth, _T("Girder depth is too large. Must be less than or equal to 21.0 in"));

   Float64 ts = WBFL::Units::ConvertFromSysUnits(m_ts,WBFL::Units::Measure::Inch);

   if ( IsLT(ts, 8.0) )
      THROW_DF( XRangeOfApplicability, GirderDepth, _T("Slab depth is too small. Must be greater than or equal to 8.0 in"));

   if ( IsGT(8.5, ts) )
      THROW_DF( XRangeOfApplicability, GirderDepth, _T("Slab depth is too large. Must be less than or equal to 8.5 in"));

   if ( !(IsZero(m_SkewAngle1) && IsZero(m_SkewAngle2)) )
      THROW_DF( XRangeOfApplicability, SkewAngle, _T("Skew is non-zero, and skew corrections are not defined for this girder type. See TxDOT bridge design manual"));

   if ( GetNb() < 3 )
      THROW_DF(XRangeOfApplicability, NumGirders, _T("Number of girders is out of range (3<=Ng)."));

   return true;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfSpreadSlab::GetMomentDF_Int_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicability(false);
   if (isAppl || m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore)
   {
      Float64 L = WBFL::Units::ConvertFromSysUnits(m_L, WBFL::Units::Measure::Feet);
      Float64 S = WBFL::Units::ConvertFromSysUnits(m_Savg, WBFL::Units::Measure::Feet);
      Float64 d = WBFL::Units::ConvertFromSysUnits(m_d, WBFL::Units::Measure::Inch);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = this->GetLanesBeamsMethod(this->m_Nl, this->m_Nb,true);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 2.3, 0.35) * pow(S*d / (12.0*L*L), 0.25);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = Utility::GetMultiplePresenceFactor(1);
         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      CHECK(m_RangeOfApplicabilityAction==RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::IntGirder, NumLoadedLanes::One,true);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfSpreadSlab::GetMomentDF_Int_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicability(false);
   if (isAppl || m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore)
   {
      Float64 L = WBFL::Units::ConvertFromSysUnits(m_L, WBFL::Units::Measure::Feet);
      Float64 S = WBFL::Units::ConvertFromSysUnits(m_Savg, WBFL::Units::Measure::Feet);
      Float64 d = WBFL::Units::ConvertFromSysUnits(m_d, WBFL::Units::Measure::Inch);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = this->GetLanesBeamsMethod(this->m_Nl, this->m_Nb,true);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 6.3, 0.6) * pow(S*d / (12.0*L*L), 0.125);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = Utility::GetMultiplePresenceFactor(2);
         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      CHECK(m_RangeOfApplicabilityAction== RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::IntGirder, NumLoadedLanes::TwoOrMore,true);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfSpreadSlab::GetMomentDF_Ext_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicability(false);
   if (isAppl || m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore)
   {
      Float64 L = WBFL::Units::ConvertFromSysUnits(m_L, WBFL::Units::Measure::Feet);
      Float64 S = WBFL::Units::ConvertFromSysUnits(m_Savg, WBFL::Units::Measure::Feet);
      Float64 d = WBFL::Units::ConvertFromSysUnits(m_d, WBFL::Units::Measure::Inch);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = GetLanesBeamsMethod(m_Nl, m_Nb, true);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 1.7, 0.5) * pow(S*d / (12.0*L*L), 0.3);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = Utility::GetMultiplePresenceFactor(1);

         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      CHECK(m_RangeOfApplicabilityAction== RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::One, true);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   // exterior cannot be less than interior
   ILiveLoadDistributionFactor::DFResult gint = GetMomentDF_Int_1_Strength();
   if (g.mg < gint.mg)
   {
      g = gint;
      g.ControllingMethod |= INTERIOR_OVERRIDE;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfSpreadSlab::GetMomentDF_Ext_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicability(false);
   if (isAppl || m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore)
   {
      Float64 L = WBFL::Units::ConvertFromSysUnits(m_L, WBFL::Units::Measure::Feet);
      Float64 S = WBFL::Units::ConvertFromSysUnits(m_Savg, WBFL::Units::Measure::Feet);
      Float64 d = WBFL::Units::ConvertFromSysUnits(m_d, WBFL::Units::Measure::Inch);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = this->GetLanesBeamsMethod(this->m_Nl, this->m_Nb,true);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 9.0, 0.5) * pow(S*d / (12.0*L*L), 0.1);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = Utility::GetMultiplePresenceFactor(2);

         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      CHECK(m_RangeOfApplicabilityAction== RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::TwoOrMore, true);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   // exterior cannot be less than interior
   ILiveLoadDistributionFactor::DFResult gint = GetMomentDF_Int_2_Strength();
   if (g.mg < gint.mg)
   {
      g = gint;
      g.ControllingMethod |= INTERIOR_OVERRIDE;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfSpreadSlab::GetShearDF_Int_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicability(false);
   if (isAppl || m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore)
   {
      Float64 L = WBFL::Units::ConvertFromSysUnits(m_L, WBFL::Units::Measure::Feet);
      Float64 S = WBFL::Units::ConvertFromSysUnits(m_Savg, WBFL::Units::Measure::Feet);
      Float64 d = WBFL::Units::ConvertFromSysUnits(m_d, WBFL::Units::Measure::Inch);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = GetLanesBeamsMethod(m_Nl, m_Nb, true);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 3.7, 0.65) * pow(d / (12.0*L), 0.25);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = Utility::GetMultiplePresenceFactor(1);

         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      CHECK(m_RangeOfApplicabilityAction== RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::IntGirder, NumLoadedLanes::One, true);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfSpreadSlab::GetShearDF_Int_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicability(false);
   if (isAppl || m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore)
   {
      Float64 L = WBFL::Units::ConvertFromSysUnits(m_L, WBFL::Units::Measure::Feet);
      Float64 S = WBFL::Units::ConvertFromSysUnits(m_Savg, WBFL::Units::Measure::Feet);
      Float64 d = WBFL::Units::ConvertFromSysUnits(m_d, WBFL::Units::Measure::Inch);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = GetLanesBeamsMethod(m_Nl, m_Nb, true);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 5.0, 0.9) * pow(d / (12.0*L), 0.2);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = Utility::GetMultiplePresenceFactor(2);

         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      CHECK(m_RangeOfApplicabilityAction== RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::IntGirder, NumLoadedLanes::TwoOrMore, true);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfSpreadSlab::GetShearDF_Ext_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicability(false);
   if (isAppl || m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore)
   {
      Float64 S = WBFL::Units::ConvertFromSysUnits(m_Savg, WBFL::Units::Measure::Feet);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = GetLanesBeamsMethod(m_Nl, m_Nb, true);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 15.7, 0.7);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = Utility::GetMultiplePresenceFactor(1);

         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      CHECK(m_RangeOfApplicabilityAction== RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::One, true);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   // exterior cannot be less than interior
   ILiveLoadDistributionFactor::DFResult gint = GetShearDF_Int_1_Strength();
   if (g.mg < gint.mg)
   {
      g = gint;
      g.ControllingMethod |= INTERIOR_OVERRIDE;
   }

   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfSpreadSlab::GetShearDF_Ext_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicability(false);
   if (isAppl || m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Ignore)
   {
      Float64 S = WBFL::Units::ConvertFromSysUnits(m_Savg, WBFL::Units::Measure::Feet);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = this->GetLanesBeamsMethod(this->m_Nl, this->m_Nb, true);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 19.0, 0.6);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = Utility::GetMultiplePresenceFactor(2);

         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      CHECK(m_RangeOfApplicabilityAction== RangeOfApplicabilityAction::IgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::TwoOrMore, true);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   // exterior cannot be less than interior
   ILiveLoadDistributionFactor::DFResult gint = GetShearDF_Int_2_Strength();
   if (g.mg < gint.mg)
   {
      g = gint;
      g.ControllingMethod |= INTERIOR_OVERRIDE;
   }

   return g;
}

Float64 TxdotLldfSpreadSlab::MomentSkewCorrectionFactor() const
{
   return 1.0; // no skew allowed for this type, so use a value of 1.0
}

Float64 TxdotLldfSpreadSlab::ShearSkewCorrectionFactor() const
{
   return 1.0; // no skew allowed for this type, so use a value of 1.0
}
