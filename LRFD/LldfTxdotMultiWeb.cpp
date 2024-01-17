///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include <Lrfd/BDSManager.h>
#include <Lrfd\Utility.h>

using namespace WBFL::LRFD;

TxdotLldfMultiWeb::TxdotLldfMultiWeb(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                                             Uint32 Nl, Float64 wLane,
                                             Float64 W, Float64 L, Float64 Kfactor,
                                             Float64 skewAngle1, Float64 skewAngle2) :
LiveLoadDistributionFactorBase(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane,false,false)
{
   m_W           = W;
   m_L           = L;
   m_Kfactor       = Kfactor;
   m_SkewAngle1  = skewAngle1;
   m_SkewAngle2  = skewAngle2;
}

bool TxdotLldfMultiWeb::TestRangeOfApplicability(Location loc) const
{
   bool doThrow=true;

   // only return if we are throwing for range error
   if ( !DoCheckApplicablity() && doThrow)
      return true;

   if ( 6 < m_Nl )
      THROW_DF( XRangeOfApplicability, NumLanes, _T("Excessive number of lanes. See Table 4.6.2.2.2b-1"));

//   if ( !IsZero(m_SkewAngle1) || !IsZero(m_SkewAngle2) )
//      THROW_DF( XRangeOfApplicability, SkewAngle, "Skew corrections are not defined for this girder type. See 4.6.2.2.2e");

   if ( GetNb() < 4 )
      THROW_DF(XRangeOfApplicability, NumGirders, _T("Number of girders is out of range (4<=Ng). See Table 4.6.2.2.3a-1"));

   return true;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfMultiWeb::GetMomentDF_Int_1_Strength() const
{
   Float64 W, S, L;
   Float64 f;
   bool bSI = BDSManager::GetUnits() == BDSManager::Units::SI;
   if ( bSI )
   {
      W = WBFL::Units::ConvertFromSysUnits(m_W,WBFL::Units::Measure::Millimeter);
      S = WBFL::Units::ConvertFromSysUnits(m_Savg,WBFL::Units::Measure::Millimeter);
      L = WBFL::Units::ConvertFromSysUnits(m_L,WBFL::Units::Measure::Millimeter);
      f = 300;
   }
   else
   {
      W = WBFL::Units::ConvertFromSysUnits(m_W,WBFL::Units::Measure::Feet);
      S = WBFL::Units::ConvertFromSysUnits(m_Savg,WBFL::Units::Measure::Feet);
      L = WBFL::Units::ConvertFromSysUnits(m_L,WBFL::Units::Measure::Feet);
      f = 1;
   }

//   Float64 K = (m_Nwebs>1) ? 2.2 : 2.0;
   Float64 C = m_Kfactor*(W/L);
   if ( m_Kfactor < C )
      C = m_Kfactor;

   // cannot have case where C>5, so:
   Float64 D = f*(11.5 - m_Nl + 1.4*m_Nl*pow(1-0.2*C,2));

   ILiveLoadDistributionFactor::DFResult g;
   Float64 mg = S/D;

   S = WBFL::Units::ConvertFromSysUnits(m_Savg,WBFL::Units::Measure::Feet);  // us or si, doesn't matter to TxDOT

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
      g.EqnData.D = WBFL::Units::ConvertToSysUnits(D,bSI? WBFL::Units::Measure::Millimeter : WBFL::Units::Measure::Feet);
      g.EqnData.C = C;
      g.EqnData.K = m_Kfactor;
      g.EqnData.mg = mg;
      g.EqnData.bWasUsed = true;
   }

   g.EqnData.m = Utility::GetMultiplePresenceFactor(1);

   Float64 skew = MomentSkewCorrectionFactor();
   if ( m_bSkewMoment )
   {
      g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
   }

   g.SkewCorrectionFactor = skew;
   g.mg = skew*g.EqnData.mg;

   return g;
}

ILiveLoadDistributionFactor::DFResult TxdotLldfMultiWeb::GetMomentDF_Int_2_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

ILiveLoadDistributionFactor::DFResult TxdotLldfMultiWeb::GetMomentDF_Ext_1_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

ILiveLoadDistributionFactor::DFResult TxdotLldfMultiWeb::GetMomentDF_Ext_2_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

ILiveLoadDistributionFactor::DFResult TxdotLldfMultiWeb::GetShearDF_Int_1_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

ILiveLoadDistributionFactor::DFResult  TxdotLldfMultiWeb::GetShearDF_Int_2_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

ILiveLoadDistributionFactor::DFResult TxdotLldfMultiWeb::GetShearDF_Ext_1_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

ILiveLoadDistributionFactor::DFResult TxdotLldfMultiWeb::GetShearDF_Ext_2_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

Float64 TxdotLldfMultiWeb::MomentSkewCorrectionFactor() const
{
   return 1.0; // no skew correction given in AASHTO
}

Float64 TxdotLldfMultiWeb::ShearSkewCorrectionFactor() const
{
   return 1.0; // no skew correction given in AASHTO
}
