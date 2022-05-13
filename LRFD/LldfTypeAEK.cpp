///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <Lrfd\LldfTypeAEK.h>
#include <Lrfd\XRangeOfApplicability.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\Utility.h>
#include <Units\Convert.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdLldfTypeAEK
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdLldfTypeAEK::lrfdLldfTypeAEK(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                                 Uint32 Nl, Float64 wLane,
                                 Float64 L,Float64 ts,Float64 n,
                                 Float64 I, Float64 A, Float64 eg,
                                 bool bXFrames,
                                 Float64 skewAngle1, Float64 skewAngle2,
                                 bool bSkewMoment,
                                 bool bSkewShear) :
// For aek's de and roadoverhange are the same because there is a single web
lrfdLldfTypeAEKIJ(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,
                  Nl,wLane,leftOverhang,rightOverhang,L,ts,n,
                  I,A,eg, skewAngle1, skewAngle2,bSkewMoment,bSkewShear)
{
   m_bXFrames = bXFrames;
}

lrfdLldfTypeAEK::lrfdLldfTypeAEK(const lrfdLldfTypeAEK& rOther) :
lrfdLldfTypeAEKIJ(rOther)
{
   MakeCopy(rOther);
}

lrfdLldfTypeAEK::~lrfdLldfTypeAEK()
{
}

//======================== OPERATORS  =======================================
lrfdLldfTypeAEK& lrfdLldfTypeAEK::operator= (const lrfdLldfTypeAEK& rOther)
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
void lrfdLldfTypeAEK::MakeCopy(const lrfdLldfTypeAEK& rOther)
{
   m_bXFrames = rOther.m_bXFrames;
   m_Nl = rOther.m_Nl;
}

void lrfdLldfTypeAEK::MakeAssignment(const lrfdLldfTypeAEK& rOther)
{
   lrfdLldfTypeAEKIJ::MakeAssignment( rOther );
   MakeCopy( rOther );
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeAEK::GetMomentDF_Ext_1_Strength() const
{
   Float64 skew;
   lrfdILiveLoadDistributionFactor::DFResult g;

   g = lrfdLldfTypeAEKIJ::GetMomentDF_Ext_1_Strength(); // accounts for skew

   if (m_bXFrames)
   {
      // but not less than that which would be obtained by assuming that the
      // cross-section deflects and rotates as a rigid cross-section. 4.6.2.2.2d
      g.RigidData = DistributeByStaticalMethod(m_Side, m_Spacings, m_LeftCurbOverhang, m_RightCurbOverhang, m_wLane, 1, 1,true);

      skew = MomentSkewCorrectionFactor();
      if ( g.mg < g.RigidData.mg*skew )
      {
         g.ControllingMethod = RIGID_METHOD;
         g.EqnData.bWasUsed = false;
         if ( m_bSkewMoment )
         {
            g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
         }
         g.mg = g.RigidData.mg*skew;
         g.SkewCorrectionFactor = skew;
      }
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeAEK::GetMomentDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;
   Float64 skew;

   g = lrfdLldfTypeAEKIJ::GetMomentDF_Ext_2_Strength();

   if (m_bXFrames)
   {
      // but not less than that which would be obtained by assuming that the
      // cross-section deflects and rotates as a rigid cross-section. 4.6.2.2.2d
      g.RigidData = DistributeByStaticalMethod(m_Side, m_Spacings, m_LeftCurbOverhang, m_RightCurbOverhang, m_wLane,2,m_Nl, true);
      skew = MomentSkewCorrectionFactor();
      if ( g.mg < g.RigidData.mg*skew )
      {
         g.ControllingMethod = RIGID_METHOD;
         g.EqnData.bWasUsed = false;
         if ( m_bSkewMoment )
         {
            g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
         }
         g.mg = g.RigidData.mg*skew;
         g.SkewCorrectionFactor = skew;
      }
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeAEK::GetShearDF_Ext_1_Strength() const
{
   Float64 skew;
   lrfdILiveLoadDistributionFactor::DFResult g;

   g = lrfdLldfTypeAEKIJ::GetShearDF_Ext_1_Strength(); // accounts for skew

   if (m_bXFrames)
   {
      // but not less than that which would be obtained by assuming that the
      // cross-section deflects and rotates as a rigid cross-section. 4.6.2.2.2d
      g.RigidData = DistributeByStaticalMethod(m_Side, m_Spacings, m_LeftCurbOverhang, m_RightCurbOverhang, m_wLane, 1, 1, true);

      skew = ShearSkewCorrectionFactor();
      if ( g.mg < g.RigidData.mg*skew )
      {
         g.ControllingMethod = RIGID_METHOD;
         g.EqnData.bWasUsed = false;
         if ( m_bSkewShear )
         {
            g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
         }
         g.mg = g.RigidData.mg*skew;
         g.SkewCorrectionFactor = skew;
      }
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeAEK::GetShearDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;
   Float64 skew;

   g = lrfdLldfTypeAEKIJ::GetShearDF_Ext_2_Strength();

   if (m_bXFrames)
      {
         // but not less than that which would be obtained by assuming that the
         // cross-section deflects and rotates as a rigid cross-section. 4.6.2.2.2d
         g.RigidData = DistributeByStaticalMethod(m_Side, m_Spacings, m_LeftCurbOverhang, m_RightCurbOverhang, m_wLane,2,m_Nl, true);
         skew = ShearSkewCorrectionFactor();
         if ( g.mg < g.RigidData.mg*skew )
         {
            g.ControllingMethod = RIGID_METHOD;
            g.EqnData.bWasUsed = false;
            if ( m_bSkewShear )
            {
               g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
            }
            g.mg = g.RigidData.mg*skew;
            g.SkewCorrectionFactor = skew;
         }
      }

   return g;
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
bool lrfdLldfTypeAEK::AssertValid() const
{
   return lrfdLldfTypeAEKIJ::AssertValid();
}

void lrfdLldfTypeAEK::Dump(dbgDumpContext& os) const
{
   lrfdLldfTypeAEKIJ::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdLldfTypeAEK::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdLldfTypeAEK");

   Float64 S = WBFL::Units::ConvertToSysUnits( 8., WBFL::Units::Measure::Feet );
   Float64 de = WBFL::Units::ConvertToSysUnits( 2., WBFL::Units::Measure::Feet );
   Float64 wLane = WBFL::Units::ConvertToSysUnits( 12., WBFL::Units::Measure::Feet );
   Float64 L = WBFL::Units::ConvertToSysUnits( 151., WBFL::Units::Measure::Feet );
   Float64 ts = WBFL::Units::ConvertToSysUnits( 7.5, WBFL::Units::Measure::Inch );
   Float64 n = 1.54;
   Float64 I = WBFL::Units::ConvertToSysUnits( 960951.2, WBFL::Units::Measure::Inch4 );
   Float64 A = WBFL::Units::ConvertToSysUnits( 977.359, WBFL::Units::Measure::Inch2 );
   Float64 eg = WBFL::Units::ConvertToSysUnits( 46.587, WBFL::Units::Measure::Inch );
   Int16 Nb = 5;
   Int16 Nl = 3;
   std::vector<Float64> spacings;
   spacings.assign(Nb-1,S);

   // use us units for this test
   lrfdVersionMgr::Units old_units = lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);


   lrfdLldfTypeAEK df(1,S,spacings,de,de,
                      Nl, wLane, L,ts,n,I,A,eg,
                      false,0.0,0.0,false,false);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.4575, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.67665, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.750, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.6697, 0.001) );
   
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.680, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.8144, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.750, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.6515, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.3812, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.6250, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.5666, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.625, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.3812, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.6250, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.5666, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.625, 0.001) );

   lrfdVersionMgr::SetUnits(old_units);

   TESTME_EPILOG("LldfTypeAEK");
}
#endif // _UNITTEST


/****************************************************************************
CLASS
   lrfdWsdotLldfTypeAEK
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdWsdotLldfTypeAEK::lrfdWsdotLldfTypeAEK(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                                           Uint32 Nl, Float64 wLane,
                                           Float64 L,Float64 ts,Float64 n,
                                           Float64 I, Float64 A, Float64 eg,
                                           Float64 leftSlabOverhang,Float64 rightSlabOverhang,
                                           bool bXFrames,
                                           Float64 skewAngle1, Float64 skewAngle2,
                                           bool bSkewMoment,
                                           bool bSkewShear,
                                           Float64 slabCantileverThreshold) :
lrfdLldfTypeAEKIJ(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,
                  Nl,wLane,leftOverhang,rightOverhang,L,ts,n,
                  I,A,eg, skewAngle1, skewAngle2,bSkewMoment,bSkewShear)
{
   // Note that bXFrames is ignored - neither wsdot nor txdot use the rigid method
   m_LeftSlabOverhang  = leftSlabOverhang;
   m_RightSlabOverhang = rightSlabOverhang;
   m_bIgnoreDe = true; // we ignore range of applicability for de and use lever rule.

   // Set the overhang threshold value
   m_SlabCantileverThreshold = slabCantileverThreshold;

   // WSDOT and TxDOT apply a MPF of 1.0 for exterior girders using the lever rule where one lane controls
   this->IgnoreMpfLeverRule(true);
}

lrfdWsdotLldfTypeAEK::lrfdWsdotLldfTypeAEK(const lrfdWsdotLldfTypeAEK& rOther) :
lrfdLldfTypeAEKIJ(rOther)
{
   MakeCopy(rOther);
}

lrfdWsdotLldfTypeAEK::~lrfdWsdotLldfTypeAEK()
{
}

//======================== OPERATORS  =======================================
lrfdWsdotLldfTypeAEK& lrfdWsdotLldfTypeAEK::operator= (const lrfdWsdotLldfTypeAEK& rOther)
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

bool lrfdWsdotLldfTypeAEK::SlabCantileverTest() const
{
   Float64 slab_cantilever = m_Side==LeftSide ? m_LeftSlabOverhang : m_RightSlabOverhang;
   return IsGT(m_SlabCantileverThreshold*m_Savg,slab_cantilever,0.001);
}

lrfdILiveLoadDistributionFactor::DFResult lrfdWsdotLldfTypeAEK::GetMomentDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult gi;
   gi = lrfdLldfTypeAEKIJ::GetMomentDF_Int_1_Strength();

   if (SlabCantileverTest())
   {
      // compare with lever rule with mpf=1.0
      lrfdILiveLoadDistributionFactor::DFResult gext;
      gext.ControllingMethod = LEVER_RULE;
      gext.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane, true);

      Float64 skew = MomentSkewCorrectionFactor();

      if (gi.mg <= gext.LeverRuleData.mg*skew)
      {
         if ( m_bSkewMoment )
         {
            gext.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
         }

         gext.mg = gext.LeverRuleData.mg*skew;
         gext.SkewCorrectionFactor = skew;

         gi = gext;
      }
      else
      {
         gi.ControllingMethod |= INTERIOR_OVERRIDE;
      }
   }
   else
   {
      gi.ControllingMethod |= INTERIOR_OVERRIDE;
   }

   return gi;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdWsdotLldfTypeAEK::GetMomentDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult gext;

   if (SlabCantileverTest())
   {
      // subclass will compute using interior with e factor, or lever rule
      gext = lrfdLldfTypeAEKIJ::GetMomentDF_Ext_2_Strength();

      // Additional rule here is that we must exceed the interior value for both lever and equation cases
      if (gext.ControllingMethod & SPEC_EQN)
      {
         gext.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(2);

         if (gext.EqnData.e < 1.0)
         {
           // interior controls, reset e to 1.0
            gext.mg /= gext.EqnData.e;
            gext.EqnData.e = 1.0;
            gext.ControllingMethod |= INTERIOR_OVERRIDE;
            gext.ControllingMethod ^=  E_OVERRIDE; // negate e override
         }
      }
      else if (gext.ControllingMethod & LEVER_RULE)
      {
         // We are into the lever rule, only additional rule here is that we must exceed the interior value
         lrfdILiveLoadDistributionFactor::DFResult gint = lrfdLldfTypeAEKIJ::GetMomentDF_Int_2_Strength();
         if (gext.mg < gint.mg)
         {
            gint.ControllingMethod |= INTERIOR_OVERRIDE;
            gext = gint;
         }
      }
   }
   else 
   {
      // Use interior directly
      gext = GetMomentDF_Int_2_Strength();
      gext.ControllingMethod |= INTERIOR_OVERRIDE;
   }

   return gext;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdWsdotLldfTypeAEK::GetShearDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult gi;
   gi = lrfdLldfTypeAEKIJ::GetShearDF_Int_1_Strength();

   if (SlabCantileverTest())
   {
      // compare with lever rule with mpf=1.0
      lrfdILiveLoadDistributionFactor::DFResult gext;
      gext.ControllingMethod = LEVER_RULE;
      gext.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane, true);

      Float64 skew = ShearSkewCorrectionFactor();

      if (gi.mg <= gext.LeverRuleData.mg*skew)
      {
         if ( m_bSkewShear )
         {
            gext.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
         }
         gext.mg = gext.LeverRuleData.mg*skew;
         gext.SkewCorrectionFactor = skew;

         gi = gext;
      }
      else
      {
         gi.ControllingMethod |= INTERIOR_OVERRIDE;
      }
   }
   else
   {
      gi.ControllingMethod |= INTERIOR_OVERRIDE;
   }

   return gi;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdWsdotLldfTypeAEK::GetShearDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult gext;

   if (SlabCantileverTest())
   {
      // subclass will compute using interior with e factor, or lever rule
      gext = lrfdLldfTypeAEKIJ::GetShearDF_Ext_2_Strength();

      // Additional rule here is that we must exceed the interior value for both lever and equation cases
      if (gext.ControllingMethod & SPEC_EQN)
      {
         if (gext.EqnData.e < 1.0)
         {
           // interior controls, reset e to 1.0
            gext.mg /= gext.EqnData.e;
            gext.EqnData.e = 1.0;
            gext.ControllingMethod |= INTERIOR_OVERRIDE;
            gext.ControllingMethod ^=  E_OVERRIDE; // negate e override
         }
         gext.EqnData.m = lrfdUtility::GetMultiplePresenceFactor(2);
      }
      else if (gext.ControllingMethod & LEVER_RULE)
      {
         lrfdILiveLoadDistributionFactor::DFResult gint = lrfdLldfTypeAEKIJ::GetShearDF_Int_2_Strength();
         if (gext.mg < gint.mg)
         {
            gint.ControllingMethod |= INTERIOR_OVERRIDE;
            gext = gint;
         }
      }
   }
   else 
   {
      // Use interior directly
      gext = GetShearDF_Int_2_Strength();
      gext.ControllingMethod |= INTERIOR_OVERRIDE;
   }

   return gext;
}

void lrfdWsdotLldfTypeAEK::MakeCopy(const lrfdWsdotLldfTypeAEK& rOther)
{
   m_LeftSlabOverhang  = rOther.m_LeftSlabOverhang;
   m_RightSlabOverhang = rOther.m_RightSlabOverhang;

   m_SlabCantileverThreshold = rOther.m_SlabCantileverThreshold;
}

void lrfdWsdotLldfTypeAEK::MakeAssignment(const lrfdWsdotLldfTypeAEK& rOther)
{
   lrfdLldfTypeAEKIJ::MakeAssignment( rOther );
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
bool lrfdWsdotLldfTypeAEK::AssertValid() const
{
   return lrfdLldfTypeAEKIJ::AssertValid();
}

void lrfdWsdotLldfTypeAEK::Dump(dbgDumpContext& os) const
{
   lrfdLldfTypeAEKIJ::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
#include <LRFD\AutoVersion.h>
bool lrfdWsdotLldfTypeAEK::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdWsdotLldfTypeAEK");

   lrfdAutoVersion av;
   lrfdVersionMgr::SetVersion(lrfdVersionMgr::FirstEdition1994);
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);

   Float64 S = WBFL::Units::ConvertToSysUnits( 2000., WBFL::Units::Measure::Millimeter );
   Float64 de = WBFL::Units::ConvertToSysUnits( 910., WBFL::Units::Measure::Millimeter );
   Float64 overhang = WBFL::Units::ConvertToSysUnits(950, WBFL::Units::Measure::Millimeter);
   Float64 wLane = WBFL::Units::ConvertToSysUnits( 3600., WBFL::Units::Measure::Millimeter );
   Float64 L = WBFL::Units::ConvertToSysUnits( 20000., WBFL::Units::Measure::Millimeter );
   Float64 ts = WBFL::Units::ConvertToSysUnits( 240., WBFL::Units::Measure::Millimeter );
   Float64 n = 1.32;
   Float64 I = WBFL::Units::ConvertToSysUnits( 216.9e9, WBFL::Units::Measure::Millimeter4 );
   Float64 A = WBFL::Units::ConvertToSysUnits( 653587., WBFL::Units::Measure::Millimeter2 );
   Float64 eg = WBFL::Units::ConvertToSysUnits( 908., WBFL::Units::Measure::Millimeter );
   Int16 Nb = 5;
   Int16 Nl = 3;
   std::vector<Float64> spacings;
   spacings.assign(Nb-1,S);

   lrfdWsdotLldfTypeAEK df(1,S,spacings,de,de,
                           Nl,wLane,L,ts,n,I,A,eg,
                           overhang,overhang,
                           false,0.0,0.0,false,false,0.4);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.480, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.649, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.705, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.711, 0.001) );
   
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.623, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.721, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.705, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.721, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.400, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.705, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.519, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.705, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.400, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.705, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.519, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.705, 0.001) );

   overhang = WBFL::Units::ConvertToSysUnits(1100, WBFL::Units::Measure::Millimeter);
   lrfdWsdotLldfTypeAEK df2(1,S,spacings,de,de,
                            Nl,wLane,L,ts,n,I,A,eg,
                            overhang,overhang,
                            false,0.0,0.0,false,false,0.5);

   TRY_TESTME( IsEqual( df2.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.480, 0.001) );
   TRY_TESTME( IsEqual( df2.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.649, 0.001) );
   TRY_TESTME( IsEqual( df2.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.705, 0.001) );
   TRY_TESTME( IsEqual( df2.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.711, 0.001) );
   
   TRY_TESTME( IsEqual( df2.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.623, 0.001) );
   TRY_TESTME( IsEqual( df2.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.721, 0.001) );
   TRY_TESTME( IsEqual( df2.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.705, 0.001) );
   TRY_TESTME( IsEqual( df2.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.7206, 0.001) );

   TRY_TESTME( IsEqual( df2.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.400, 0.001) );
   TRY_TESTME( IsEqual( df2.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.705, 0.001) );
   TRY_TESTME( IsEqual( df2.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.519, 0.001) );
   TRY_TESTME( IsEqual( df2.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.705, 0.001) );

   TRY_TESTME( IsEqual( df2.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.400, 0.001) );
   TRY_TESTME( IsEqual( df2.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.705, 0.001) );
   TRY_TESTME( IsEqual( df2.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.519, 0.001) );
   TRY_TESTME( IsEqual( df2.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.705, 0.001) );

   TESTME_EPILOG("lrfdWsdotLldfTypeAEK");
}
#endif // _UNITTEST
