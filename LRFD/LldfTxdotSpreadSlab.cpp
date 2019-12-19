///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2019  Washington State Department of Transportation
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
#include <Units\SysUnits.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdTxdotLldfSpreadSlab
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdTxdotLldfSpreadSlab::lrfdTxdotLldfSpreadSlab(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                                             Uint32 Nl, Float64 wLane,
                                             Float64 d, Float64 L,
                                             Float64 skewAngle1, Float64 skewAngle2) :
lrfdLiveLoadDistributionFactorBase(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane,false,false)
{
   m_d           = d;
   m_L           = L;
   m_SkewAngle1  = skewAngle1;
   m_SkewAngle2  = skewAngle2;
}

lrfdTxdotLldfSpreadSlab::lrfdTxdotLldfSpreadSlab(const lrfdTxdotLldfSpreadSlab& rOther) :
lrfdLiveLoadDistributionFactorBase(rOther)
{
   MakeCopy(rOther);
}

lrfdTxdotLldfSpreadSlab::~lrfdTxdotLldfSpreadSlab()
{
}

//======================== OPERATORS  =======================================
lrfdTxdotLldfSpreadSlab& lrfdTxdotLldfSpreadSlab::operator= (const lrfdTxdotLldfSpreadSlab& rOther)
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
void lrfdTxdotLldfSpreadSlab::MakeCopy(const lrfdTxdotLldfSpreadSlab& rOther)
{
   lrfdLiveLoadDistributionFactorBase::MakeCopy(rOther);

   m_L           = rOther.m_L;
   m_d           = rOther.m_d;
   m_SkewAngle1  = rOther.m_SkewAngle1;
   m_SkewAngle2  = rOther.m_SkewAngle2;
}

void lrfdTxdotLldfSpreadSlab::MakeAssignment(const lrfdTxdotLldfSpreadSlab& rOther)
{
   lrfdLiveLoadDistributionFactorBase::MakeAssignment( rOther );
   MakeCopy( rOther );
}

bool lrfdTxdotLldfSpreadSlab::TestRangeOfApplicability(Location loc) const
{

   // only return if we are throwing for range error
   if (!DoCheckApplicablity())
      return true;

   return DoTestRangeOfApplicablity(true);
}

bool lrfdTxdotLldfSpreadSlab::DoTestRangeOfApplicablity(bool doThrow) const
{
   Float64 L = ::ConvertFromSysUnits(m_L,unitMeasure::Feet);

   Float64 m29ft_7in = 29.0 + 7.0/12.0;
   if ( IsLT(L, m29ft_7in) )
      THROW_DF( lrfdXRangeOfApplicability, SpanLength, _T("Span length is too short. Must be greater or equal to 29ft-7in"));

   Float64 m49ft_7in = 49.0 + 7.0/12.0;
   if ( IsGT(m49ft_7in, L) )
      THROW_DF( lrfdXRangeOfApplicability, SpanLength, _T("Span length is too long. Must be less than or equal to 49ft-7in"));

   Float64 S = ::ConvertFromSysUnits(m_Savg,unitMeasure::Feet);

   if ( IsLT(S, 6.5) )
      THROW_DF( lrfdXRangeOfApplicability, Spacing, _T("Girder spacing is too small. Must be greater than or equal to 6.5 ft"));

   if ( IsGT(11.0, S) )
      THROW_DF( lrfdXRangeOfApplicability, Spacing, _T("Girder spacing is too large. Must be less than or equal to 11.0 ft"));

   Float64 d = ::ConvertFromSysUnits(m_d,unitMeasure::Inch);

   if ( IsLT(d, 12.0) )
      THROW_DF( lrfdXRangeOfApplicability, GirderDepth, _T("Girder depth is too small. Must be greater than or equal to 12.0 in"));

   if ( IsGT(21.0, d) )
      THROW_DF( lrfdXRangeOfApplicability, GirderDepth, _T("Girder depth is too large. Must be less than or equal to 21.0 in"));

   if ( !(IsZero(m_SkewAngle1) && IsZero(m_SkewAngle2)) )
      THROW_DF( lrfdXRangeOfApplicability, SkewAngle, _T("Skew is non-zero, and skew corrections are not defined for this girder type. See TxDOT bridge design manual"));

   if ( GetNb() < 3 )
      THROW_DF(lrfdXRangeOfApplicability, NumGirders, _T("Number of girders is out of range (3<=Ng)."));

   return true;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfSpreadSlab::GetMomentDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicablity(false);
   if (isAppl || m_RangeOfApplicabilityAction == roaIgnore)
   {
      Float64 L = ::ConvertFromSysUnits(m_L, unitMeasure::Feet);
      Float64 S = ::ConvertFromSysUnits(m_Savg, unitMeasure::Feet);
      Float64 d = ::ConvertFromSysUnits(m_d, unitMeasure::Inch);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = this->GetLanesBeamsMethod(this->m_Nl, this->m_Nb);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 2.3, 0.35) * pow(S*d / (12.0*L*L), 0.25);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(1);
         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, OneLoadedLane);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfSpreadSlab::GetMomentDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicablity(false);
   if (isAppl || m_RangeOfApplicabilityAction == roaIgnore)
   {
      Float64 L = ::ConvertFromSysUnits(m_L, unitMeasure::Feet);
      Float64 S = ::ConvertFromSysUnits(m_Savg, unitMeasure::Feet);
      Float64 d = ::ConvertFromSysUnits(m_d, unitMeasure::Inch);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = this->GetLanesBeamsMethod(this->m_Nl, this->m_Nb);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 6.3, 0.6) * pow(S*d / (12.0*L*L), 0.125);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(2);
         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, TwoOrMoreLoadedLanes);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfSpreadSlab::GetMomentDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicablity(false);
   if (isAppl || m_RangeOfApplicabilityAction == roaIgnore)
   {
      Float64 L = ::ConvertFromSysUnits(m_L, unitMeasure::Feet);
      Float64 S = ::ConvertFromSysUnits(m_Savg, unitMeasure::Feet);
      Float64 d = ::ConvertFromSysUnits(m_d, unitMeasure::Inch);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = this->GetLanesBeamsMethod(this->m_Nl, this->m_Nb);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 1.7, 0.5) * pow(S*d / (12.0*L*L), 0.3);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(1);

         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   // exterior cannot be less than interior
   lrfdILiveLoadDistributionFactor::DFResult gint = GetMomentDF_Int_1_Strength();
   if (g.mg < gint.mg)
   {
      g = gint;
      g.ControllingMethod |= INTERIOR_OVERRIDE;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfSpreadSlab::GetMomentDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicablity(false);
   if (isAppl || m_RangeOfApplicabilityAction == roaIgnore)
   {
      Float64 L = ::ConvertFromSysUnits(m_L, unitMeasure::Feet);
      Float64 S = ::ConvertFromSysUnits(m_Savg, unitMeasure::Feet);
      Float64 d = ::ConvertFromSysUnits(m_d, unitMeasure::Inch);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = this->GetLanesBeamsMethod(this->m_Nl, this->m_Nb);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 9.0, 0.5) * pow(S*d / (12.0*L*L), 0.1);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(2);

         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, TwoOrMoreLoadedLanes);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   // exterior cannot be less than interior
   lrfdILiveLoadDistributionFactor::DFResult gint = GetMomentDF_Int_2_Strength();
   if (g.mg < gint.mg)
   {
      g = gint;
      g.ControllingMethod |= INTERIOR_OVERRIDE;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfSpreadSlab::GetShearDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicablity(false);
   if (isAppl || m_RangeOfApplicabilityAction == roaIgnore)
   {
      Float64 L = ::ConvertFromSysUnits(m_L, unitMeasure::Feet);
      Float64 S = ::ConvertFromSysUnits(m_Savg, unitMeasure::Feet);
      Float64 d = ::ConvertFromSysUnits(m_d, unitMeasure::Inch);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = this->GetLanesBeamsMethod(this->m_Nl, this->m_Nb);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 3.7, 0.65) * pow(d / (12.0*L), 0.25);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(1);

         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, OneLoadedLane);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult  lrfdTxdotLldfSpreadSlab::GetShearDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicablity(false);
   if (isAppl || m_RangeOfApplicabilityAction == roaIgnore)
   {
      Float64 L = ::ConvertFromSysUnits(m_L, unitMeasure::Feet);
      Float64 S = ::ConvertFromSysUnits(m_Savg, unitMeasure::Feet);
      Float64 d = ::ConvertFromSysUnits(m_d, unitMeasure::Inch);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = this->GetLanesBeamsMethod(this->m_Nl, this->m_Nb);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 5.0, 0.9) * pow(d / (12.0*L), 0.2);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(2);

         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, TwoOrMoreLoadedLanes);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfSpreadSlab::GetShearDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicablity(false);
   if (isAppl || m_RangeOfApplicabilityAction == roaIgnore)
   {
      Float64 S = ::ConvertFromSysUnits(m_Savg, unitMeasure::Feet);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = this->GetLanesBeamsMethod(this->m_Nl, this->m_Nb);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 15.7, 0.7);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(1);

         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   // exterior cannot be less than interior
   lrfdILiveLoadDistributionFactor::DFResult gint = GetShearDF_Int_1_Strength();
   if (g.mg < gint.mg)
   {
      g = gint;
      g.ControllingMethod |= INTERIOR_OVERRIDE;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfSpreadSlab::GetShearDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool isAppl = DoTestRangeOfApplicablity(false);
   if (isAppl || m_RangeOfApplicabilityAction == roaIgnore)
   {
      Float64 S = ::ConvertFromSysUnits(m_Savg, unitMeasure::Feet);

      if (GetNb() == 1)
      {
         // Single beam method counts on spacing which will be garbage
         g.ControllingMethod = LANES_DIV_BEAMS;
         g = this->GetLanesBeamsMethod(this->m_Nl, this->m_Nb);
         g.mg = g.LanesBeamsData.mg;
      }
      else
      {
         Float64 mg = pow(S / 19.0, 0.6);
         g.EqnData.mg = mg;
         g.EqnData.bWasUsed = true;
         g.ControllingMethod = SPEC_EQN;

         g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(2);

         g.SkewCorrectionFactor = 1.0;

         g.mg = mg;
      }
   }
   else
   {
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, TwoOrMoreLoadedLanes);
      g.SkewCorrectionFactor = 1.0;
      g.mg = g.LeverRuleData.mg;
   }

   // exterior cannot be less than interior
   lrfdILiveLoadDistributionFactor::DFResult gint = GetShearDF_Int_2_Strength();
   if (g.mg < gint.mg)
   {
      g = gint;
      g.ControllingMethod |= INTERIOR_OVERRIDE;
   }

   return g;
}

Float64 lrfdTxdotLldfSpreadSlab::MomentSkewCorrectionFactor() const
{
   return 1.0; // no skew allowed for this type, so use a value of 1.0
}

Float64 lrfdTxdotLldfSpreadSlab::ShearSkewCorrectionFactor() const
{
   return 1.0; // no skew allowed for this type, so use a value of 1.0
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
bool lrfdTxdotLldfSpreadSlab::AssertValid() const
{
   return lrfdLiveLoadDistributionFactorBase::AssertValid();
}

void lrfdTxdotLldfSpreadSlab::Dump(dbgDumpContext& os) const
{
   lrfdLiveLoadDistributionFactorBase::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdTxdotLldfSpreadSlab::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdTxdotLldfSpreadSlab");

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);

   Float64 Savg = ::ConvertToSysUnits( 7.5, unitMeasure::Feet );
   Int16 Nb = 5;
   std::vector<Float64> spacings;
   spacings.assign(Nb-1, Savg);
   Float64 d = ::ConvertToSysUnits( 15.0, unitMeasure::Inch );
   Float64 L = ::ConvertToSysUnits( 40.5, unitMeasure::Feet );
   Int16 Nl = 3;
   Float64 wLane = ::ConvertToSysUnits( 12.0, unitMeasure::Feet );
   Float64 ohang = Savg/2.0;

   lrfdTxdotLldfSpreadSlab df(1,Savg,spacings,ohang,ohang,Nl,wLane,d,L,0.0,0.0);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.41585, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.58219, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.44609, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.58219, 0.001) ); // <== interior beam controls
   
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.66347, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.71841, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.66347, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.71841, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.34654, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.37174, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.55289, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.55289, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.34654, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.37174, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.55289, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.55289, 0.001) );

   TESTME_EPILOG("lrfdTxdotLldfSpreadSlab");
}
#endif // _UNITTEST



