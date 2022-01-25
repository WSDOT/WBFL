///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2021  Washington State Department of Transportation
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
#include <Lrfd\LldfTxdotMultiWeb.h>
#include <Lrfd\XRangeOfApplicability.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\Utility.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdTxdotLldfMultiWeb
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdTxdotLldfMultiWeb::lrfdTxdotLldfMultiWeb(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                                             Uint32 Nl, Float64 wLane,
                                             Float64 W, Float64 L, Float64 Kfactor,
                                             Float64 skewAngle1, Float64 skewAngle2) :
lrfdLiveLoadDistributionFactorBase(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane,false,false)
{
   m_W           = W;
   m_L           = L;
   m_Kfactor       = Kfactor;
   m_SkewAngle1  = skewAngle1;
   m_SkewAngle2  = skewAngle2;
}

lrfdTxdotLldfMultiWeb::lrfdTxdotLldfMultiWeb(const lrfdTxdotLldfMultiWeb& rOther) :
lrfdLiveLoadDistributionFactorBase(rOther)
{
   MakeCopy(rOther);
}

lrfdTxdotLldfMultiWeb::~lrfdTxdotLldfMultiWeb()
{
}

//======================== OPERATORS  =======================================
lrfdTxdotLldfMultiWeb& lrfdTxdotLldfMultiWeb::operator= (const lrfdTxdotLldfMultiWeb& rOther)
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
void lrfdTxdotLldfMultiWeb::MakeCopy(const lrfdTxdotLldfMultiWeb& rOther)
{
   lrfdLiveLoadDistributionFactorBase::MakeCopy(rOther);

   m_L           = rOther.m_L;
   m_W           = rOther.m_W;
   m_Kfactor     = rOther.m_Kfactor;
   m_SkewAngle1  = rOther.m_SkewAngle1;
   m_SkewAngle2  = rOther.m_SkewAngle2;
}

void lrfdTxdotLldfMultiWeb::MakeAssignment(const lrfdTxdotLldfMultiWeb& rOther)
{
   lrfdLiveLoadDistributionFactorBase::MakeAssignment( rOther );
   MakeCopy( rOther );
}

bool lrfdTxdotLldfMultiWeb::TestRangeOfApplicability(Location loc) const
{
   bool doThrow=true;

   // only return if we are throwing for range error
   if ( !DoCheckApplicablity() && doThrow)
      return true;

   if ( 6 < m_Nl )
      THROW_DF( lrfdXRangeOfApplicability, NumLanes, _T("Excessive number of lanes. See Table 4.6.2.2.2b-1"));

//   if ( !IsZero(m_SkewAngle1) || !IsZero(m_SkewAngle2) )
//      THROW_DF( lrfdXRangeOfApplicability, SkewAngle, "Skew corrections are not defined for this girder type. See 4.6.2.2.2e");

   if ( GetNb() < 4 )
      THROW_DF(lrfdXRangeOfApplicability, NumGirders, _T("Number of girders is out of range (4<=Ng). See Table 4.6.2.2.3a-1"));

   return true;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfMultiWeb::GetMomentDF_Int_1_Strength() const
{
   Float64 W, S, L;
   Float64 f;
   bool bSI = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;
   if ( bSI )
   {
      W = ::ConvertFromSysUnits(m_W,unitMeasure::Millimeter);
      S = ::ConvertFromSysUnits(m_Savg,unitMeasure::Millimeter);
      L = ::ConvertFromSysUnits(m_L,unitMeasure::Millimeter);
      f = 300;
   }
   else
   {
      W = ::ConvertFromSysUnits(m_W,unitMeasure::Feet);
      S = ::ConvertFromSysUnits(m_Savg,unitMeasure::Feet);
      L = ::ConvertFromSysUnits(m_L,unitMeasure::Feet);
      f = 1;
   }

//   Float64 K = (m_Nwebs>1) ? 2.2 : 2.0;
   Float64 C = m_Kfactor*(W/L);
   if ( m_Kfactor < C )
      C = m_Kfactor;

   // cannot have case where C>5, so:
   Float64 D = f*(11.5 - m_Nl + 1.4*m_Nl*pow(1-0.2*C,2));

   lrfdILiveLoadDistributionFactor::DFResult g;
   Float64 mg = S/D;

   S = ::ConvertFromSysUnits(m_Savg,unitMeasure::Feet);  // us or si, doesn't matter to TxDOT

   if (mg> S/10.0)
   {
      g.EqnData.mg = S/10.0;
      g.EqnData.bWasUsed = true;
      g.ControllingMethod = SPECIAL_OVERRIDE;
   }
   else
   {
      g.ControllingMethod = SPEC_EQN | S_OVER_D_METHOD;
      g.EqnData.bWasUsed = true;
      g.EqnData.D = ::ConvertToSysUnits(D,bSI? unitMeasure::Millimeter : unitMeasure::Feet);
      g.EqnData.C = C;
      g.EqnData.K = m_Kfactor;
      g.EqnData.mg = mg;
      g.EqnData.bWasUsed = true;
   }

   g.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(1);

   Float64 skew = MomentSkewCorrectionFactor();
   if ( m_bSkewMoment )
   {
      g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
   }

   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.EqnData.mg;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfMultiWeb::GetMomentDF_Int_2_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfMultiWeb::GetMomentDF_Ext_1_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfMultiWeb::GetMomentDF_Ext_2_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfMultiWeb::GetShearDF_Int_1_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

lrfdILiveLoadDistributionFactor::DFResult  lrfdTxdotLldfMultiWeb::GetShearDF_Int_2_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfMultiWeb::GetShearDF_Ext_1_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfMultiWeb::GetShearDF_Ext_2_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

Float64 lrfdTxdotLldfMultiWeb::MomentSkewCorrectionFactor() const
{
   return 1.0; // no skew correction given in AASHTO
}

Float64 lrfdTxdotLldfMultiWeb::ShearSkewCorrectionFactor() const
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
bool lrfdTxdotLldfMultiWeb::AssertValid() const
{
   return lrfdLiveLoadDistributionFactorBase::AssertValid();
}

void lrfdTxdotLldfMultiWeb::Dump(dbgDumpContext& os) const
{
   lrfdLiveLoadDistributionFactorBase::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdTxdotLldfMultiWeb::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdTxdotLldfMultiWeb");

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);

   Int16 Nb = 5;
   Float64 Savg = ::ConvertToSysUnits( 6, unitMeasure::Feet );
   std::vector<Float64> spacings;
   spacings.assign(Nb-1, Savg);
   Float64 wL = ::ConvertToSysUnits( 6, unitMeasure::Feet );
   Float64 L = ::ConvertToSysUnits( 120.25, unitMeasure::Feet );
   Int16 Nl = 3;
   Float64 ohang = Savg/2.0;
   Float64 W = (Nb)*Savg;

   lrfdTxdotLldfMultiWeb df(1,Savg,spacings,ohang,ohang,Nl,wL,W,L,2,0.0,0.0);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.55226, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.55226, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.8, 0.001) );
//   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.433, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.8, 0.001) );
   
//   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.8, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.6, 0.001) );
//   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.433, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.6667, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.8, 0.001) );
//   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.433, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.8, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.460188, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.6667, 0.001) );
//   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.6667, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.5, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.666667, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.460188, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.6667, 0.001) );
//   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.6667, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.5, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.666667, 0.001) );

   
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);

   TESTME_EPILOG("lrfdTxdotLldfMultiWeb");
}
#endif // _UNITTEST



