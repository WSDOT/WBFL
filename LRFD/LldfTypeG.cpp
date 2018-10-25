///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2010  Washington State Department of Transportation
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
#include <Units\SysUnits.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdLldfTypeG
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdLldfTypeG::lrfdLldfTypeG(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                             Uint32 Nl, Float64 wLane,
                             Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                             Float64 leftDe,Float64 rightDe,
                             Float64 PossionRatio, bool ignoreSkew,
                             Float64 skewAngle1, Float64 skewAngle2) :
lrfdLiveLoadDistributionFactorBase(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane)
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
   m_IgnoreSkew = ignoreSkew;
}

lrfdLldfTypeG::lrfdLldfTypeG(const lrfdLldfTypeG& rOther) :
lrfdLiveLoadDistributionFactorBase(rOther)
{
   MakeCopy(rOther);
}

lrfdLldfTypeG::~lrfdLldfTypeG()
{
}

//======================== OPERATORS  =======================================
lrfdLldfTypeG& lrfdLldfTypeG::operator= (const lrfdLldfTypeG& rOther)
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
void lrfdLldfTypeG::MakeCopy(const lrfdLldfTypeG& rOther)
{
   m_L           = rOther.m_L;
   m_W           = rOther.m_W;
   m_I           = rOther.m_I;
   m_J           = rOther.m_J;
   m_b           = rOther.m_b;
   m_d           = rOther.m_d;
   m_PoissonRatio = rOther.m_PoissonRatio;
   m_LeftDe      = rOther.m_LeftDe;
   m_RightDe     = rOther.m_RightDe;
   m_SkewAngle1  = rOther.m_SkewAngle1;
   m_SkewAngle2  = rOther.m_SkewAngle2;
   m_IgnoreSkew  = rOther.m_IgnoreSkew;
}

void lrfdLldfTypeG::MakeAssignment(const lrfdLldfTypeG& rOther)
{
   lrfdLiveLoadDistributionFactorBase::MakeAssignment( rOther );
   MakeCopy( rOther );
}


bool lrfdLldfTypeG::TestRangeOfApplicability(Location loc) const
{
   if (!DoCheckApplicablity())
      return true;

   bool doThrow=true;
   bool bSISpec = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );

   ExteriorMomentEquationRule(bSISpec, true);

   // This is not an out of range of applicability case... skew adjustment simply isn't applied in this case
   //Float64 skew_delta_max = ::ConvertToSysUnits( 10.0, unitMeasure::Degree );
   //if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
   //   THROW_DF( lrfdXRangeOfApplicability, SkewAngleDiff, "Excessive difference in skew angles. See Article 4.6.2.2.2e");


   if (!m_IgnoreSkew && (!IsZero(m_SkewAngle1) || !IsZero(m_SkewAngle2)) )
   {
      // only check this if we have skew
      Float64 Lmin = bSISpec ?  6000 :  20;
      Float64 Lmax = bSISpec ? 37000 : 120;
      Float64 L = ::ConvertFromSysUnits(m_L,bSISpec?unitMeasure::Millimeter:unitMeasure::Feet);
      if ( L < Lmin || Lmax < L )
         THROW_DF(lrfdXRangeOfApplicability, SpanLength, "Span Length (L) is out of range. See Table 4.6.2.2.3c-1");

      Float64 dMin = bSISpec ?  430 : 17;
      Float64 dMax = bSISpec ? 1500 : 60;
      Float64 d = ::ConvertFromSysUnits(m_d,bSISpec?unitMeasure::Millimeter:unitMeasure::Inch);
      if ( d < dMin || dMax < d )
         THROW_DF(lrfdXRangeOfApplicability, GirderDepth, "Depth (d) of beam is out of range. See Table 4.6.2.2.3c-1");

      Float64 bMin = bSISpec ?  900 : 35;
      Float64 bMax = bSISpec ? 1500 : 60;
      Float64 b = ::ConvertFromSysUnits(m_b,bSISpec?unitMeasure::Millimeter:unitMeasure::Inch);
      if ( b < bMin || bMax < b )
         THROW_DF(lrfdXRangeOfApplicability, BeamWidth, "Width (b), of beam is out of range. See Table 4.6.2.2.3c-1");
   }

   return true;
}

bool lrfdLldfTypeG::InteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   if ( 6 < m_Nl )
      THROW_DF( lrfdXRangeOfApplicability, NumLanes, "Excessive number of lanes. See Table 4.6.2.2.2b-1");

   if ( GetNb() < 4 )
      THROW_DF( lrfdXRangeOfApplicability, NumGirders, "Number of girders is out of range. Must be >=4, see 4.6.2.2.1");

   Float64 skew_max = ::ConvertToSysUnits( 45.0, unitMeasure::Degree );
   if ( !m_IgnoreSkew && (!IsLE(m_SkewAngle1,skew_max) || !IsLE(m_SkewAngle2,skew_max)) )
      THROW_DF( lrfdXRangeOfApplicability, SkewAngle, "Excessive skew angle. See Table 4.6.2.2.2b-1");

   return true;
}

bool lrfdLldfTypeG::ExteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   if (!InteriorMomentEquationRule(bSISpec, doThrow))
      return false;

   Float64 de_max = bSISpec ? ::ConvertToSysUnits(600.,unitMeasure::Millimeter) : ::ConvertToSysUnits(2.0,unitMeasure::Feet);
   Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;

   if ( de_max+1.0e-06 < de_raw )
         THROW_DF( lrfdXRangeOfApplicability, CurbLineOffset, "Curb offset (de) is out of range. See Table 4.6.2.2.2d-1");

   return true;
}

bool lrfdLldfTypeG::InteriorShearEquationRule(bool bSISpec) const
{
   Float64 bMin = bSISpec ?  900 : 35;
   Float64 bMax = bSISpec ? 1500 : 60;
   Float64 b = ::ConvertFromSysUnits(m_b,bSISpec?unitMeasure::Millimeter:unitMeasure::Inch);
   if ( b < bMin || bMax < b )
   {
      return false;
   }

   Float64 Lmin = bSISpec ?  6000 :  20;
   Float64 Lmax = bSISpec ? 37000 : 120;
   Float64 L = ::ConvertFromSysUnits(m_L,bSISpec?unitMeasure::Millimeter:unitMeasure::Feet);
   if ( L < Lmin || Lmax < L )
   {
      return false;
   }

   GirderIndexType nb = GetNb();
   if ( nb<5 || nb>20 )
   {
      return false;
   }

   return true;
}

bool lrfdLldfTypeG::ExteriorShearEquationRule(bool bSISpec) const
{
   if ( !InteriorShearEquationRule(bSISpec) )
      return false;

   Float64 de_max = bSISpec ? ::ConvertToSysUnits(600.,unitMeasure::Millimeter) : ::ConvertToSysUnits(2.0,unitMeasure::Feet);
   Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;

   if ( de_max < de_raw )
         return false;

   return true;
}

bool lrfdLldfTypeG::IandJOutOfRangeRule(bool bSISpec) const
{
   Float64 Jmin = bSISpec ? 1.0e10 : 25000;
   Float64 Jmax = bSISpec ? 2.5e11 : 610000;
   Float64 J = ::ConvertFromSysUnits(m_J,bSISpec?unitMeasure::Millimeter4:unitMeasure::Inch4);
   if ( J < Jmin || Jmax < J )
      return true;

   Float64 Imin = bSISpec ? 1.7e10 : 40000;
   Float64 Imax = bSISpec ? 2.5e11 : 610000;
   Float64 I = ::ConvertFromSysUnits(m_I,bSISpec?unitMeasure::Millimeter4:unitMeasure::Inch4);
   if ( I < Imin || Imax < I )
      return true;

   return false;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeG::GetMomentDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;

   if(m_RangeOfApplicabilityAction==roaIgnore || InteriorMomentEquationRule(bSISpec, false) )
   {
      // S/D method
      Float64 J, I, W, S, L;
      Float64 f;
      if ( bSISpec )
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
      g.EqnData.e = 1.0;
      g.EqnData.D = ::ConvertToSysUnits(D, bSISpec? unitMeasure::Millimeter : unitMeasure::Feet);
      g.EqnData.C = C;
      g.EqnData.K = K;
      g.EqnData.mg = S/D;
      g.mg = g.EqnData.mg;
   }
   else
   {
      // lever rule
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, OneLoadedLane);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = MomentSkewCorrectionFactor();
   g.SkewCorrectionFactor = skew;
   g.mg *= skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeG::GetMomentDF_Int_2_Strength() const
{
   return GetMomentDF_Int_1_Strength();
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeG::GetMomentDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
   
   if(m_RangeOfApplicabilityAction==roaIgnore || ExteriorMomentEquationRule(bSISpec, false) )
   {
      g = GetMomentDF_Int_1_Strength();

      Float64 A = (bSISpec ? 9100 : 30);
      Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;
      Float64 de = ::ConvertFromSysUnits(de_raw,bSISpec?unitMeasure::Millimeter:unitMeasure::Feet);

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
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
      g.mg = g.LeverRuleData.mg;

      g.EqnData.e = 1.0;
      Float64 skew = MomentSkewCorrectionFactor();
      g.SkewCorrectionFactor = skew;
      g.mg *= skew;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeG::GetMomentDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
   
   if(m_RangeOfApplicabilityAction==roaIgnore || ExteriorMomentEquationRule(bSISpec, false) )
   {
      g = GetMomentDF_Int_2_Strength();

      bool bSISpec = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
      Float64 A = (bSISpec ? 7600 : 25);

      Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;
      Float64 de = ::ConvertFromSysUnits(de_raw,bSISpec?unitMeasure::Millimeter:unitMeasure::Feet);

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
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, TwoOrMoreLoadedLanes);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = MomentSkewCorrectionFactor();
      g.SkewCorrectionFactor = skew;
      g.mg *= skew;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeG::GetShearDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );

   if ( InteriorShearEquationRule(bSISpec) )
   {
      if ( !IandJOutOfRangeRule(bSISpec) )
      {
         g.ControllingMethod = SPEC_EQN;
         g.EqnData.bWasUsed = true;

         Float64 b = ::ConvertFromSysUnits(m_b,bSISpec?unitMeasure::Millimeter:unitMeasure::Inch);
         Float64 L = ::ConvertFromSysUnits(m_L,bSISpec?unitMeasure::Millimeter:unitMeasure::Feet);
         Float64 I = ::ConvertFromSysUnits(m_I,bSISpec?unitMeasure::Millimeter4:unitMeasure::Inch4);
         Float64 J = ::ConvertFromSysUnits(m_J,bSISpec?unitMeasure::Millimeter4:unitMeasure::Inch4);

         Float64 K1 = (bSISpec ? 0.7 : 1.0);
         Float64 K2 = (bSISpec ? 1.0 : 130);

         g.EqnData.mg = K1*pow( b/(K2*L), 0.15) * pow( I/J, 0.05 );
         g.EqnData.e = 1.0;
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
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, OneLoadedLane);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = ShearSkewCorrectionFactor();
   g.SkewCorrectionFactor = skew;
   g.mg *= skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult  lrfdLldfTypeG::GetShearDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );

   if ( InteriorShearEquationRule(bSISpec) )
   {
      if ( !IandJOutOfRangeRule(bSISpec) )
      {
         g.ControllingMethod = SPEC_EQN;
         g.EqnData.bWasUsed = true;

         Float64 b = ::ConvertFromSysUnits(m_b,bSISpec?unitMeasure::Millimeter:unitMeasure::Inch);
         Float64 L = ::ConvertFromSysUnits(m_L,bSISpec?unitMeasure::Millimeter:unitMeasure::Feet);
         Float64 I = ::ConvertFromSysUnits(m_I,bSISpec?unitMeasure::Millimeter4:unitMeasure::Inch4);
         Float64 J = ::ConvertFromSysUnits(m_J,bSISpec?unitMeasure::Millimeter4:unitMeasure::Inch4);

         Float64 K1 = (bSISpec ? 4000 : 156);
         Float64 K2 = (bSISpec ? 1.0 : 12);
         Float64 K3 = (bSISpec ? 1200 : 48);

         Float64 K4 = b/K3;
         if ( K4 < 1.0 )
            K4 = 1.0;

         g.EqnData.mg = pow(b/K1,0.4) * pow(b/(K2*L),0.1) * pow(I/J,0.05) * K4;
         g.EqnData.e = 1.0;
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
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, TwoOrMoreLoadedLanes);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = ShearSkewCorrectionFactor();
   g.SkewCorrectionFactor = skew;
   g.mg *= skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeG::GetShearDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;
   
   bool bSISpec = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );

   if ( ExteriorShearEquationRule(bSISpec) )
   {
      if ( !IandJOutOfRangeRule(bSISpec) )
      {
         g = GetShearDF_Int_1_Strength();

         if (g.ControllingMethod & SPEC_EQN)
         {
            // only apply e factor to equation method
            bool bSISpec = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
            Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;
            Float64 de = ::ConvertFromSysUnits(de_raw,bSISpec?unitMeasure::Millimeter:unitMeasure::Feet);
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
            assert(0); // should always be using equation unless rules are screwed up.
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
         g.SkewCorrectionFactor = skew;
         g.mg *= skew;
      }
   }
   else
   {
      // default to lever rule
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, OneLoadedLane);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = ShearSkewCorrectionFactor();
      g.SkewCorrectionFactor = skew;
      g.mg *= skew;
   }

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeG::GetShearDF_Ext_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;
   
   bool bSISpec = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );

   if ( ExteriorShearEquationRule(bSISpec) )
   {

      if ( !IandJOutOfRangeRule(bSISpec) )
      {

         g = GetShearDF_Int_2_Strength();

         if (g.ControllingMethod & SPEC_EQN)
         {
            // only use e factor for equation methods
            bool bSISpec = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );

            Float64 de_raw = m_Side==LeftSide ? m_LeftDe : m_RightDe;
            Float64 de = ::ConvertFromSysUnits(de_raw,bSISpec?unitMeasure::Millimeter:unitMeasure::Feet);

            Float64 b  = ::ConvertFromSysUnits(m_b, bSISpec?unitMeasure::Millimeter:unitMeasure::Inch);

            Float64 K1 = (bSISpec ?  1200 : 48);
            Float64 K2 = (bSISpec ?     1 : 12);
            Float64 K3 = (bSISpec ?   610 :  2);
            Float64 K4 = (bSISpec ? 12200 : 40);

            Float64 K5 = K1/b;
            if ( K5 > 1 )
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
            assert(0); // rules messed up?
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
         g.SkewCorrectionFactor = skew;
         g.mg *= skew;
      }
   }
   else
   {
      // default to lever rule
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(ExtGirder, TwoOrMoreLoadedLanes);
      g.mg = g.LeverRuleData.mg;

      Float64 skew = ShearSkewCorrectionFactor();
      g.SkewCorrectionFactor = skew;
      g.mg *= skew;
   }

   return g;
}

Float64 lrfdLldfTypeG::MomentSkewCorrectionFactor() const
{
   // 4.6.2.2.2e - don't reduce moment if difference in skew is > 10 degree
   Float64 skew_delta_max = ::ConvertToSysUnits( 10.0, unitMeasure::Degree );
   if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
      return 1.0;

   Float64 avg_skew_angle = fabs(m_SkewAngle1 + m_SkewAngle2)/2.;

   if ( IsZero(avg_skew_angle) )
      return 1.0;

   if ( ::ConvertToSysUnits(60.,unitMeasure::Degree) < avg_skew_angle)
      avg_skew_angle = ::ConvertToSysUnits(60.,unitMeasure::Degree);


   Float64 skew = 1.05 - 0.25*tan(::ConvertFromSysUnits(avg_skew_angle,unitMeasure::Radian));

   return skew;
}

Float64 lrfdLldfTypeG::ShearSkewCorrectionFactor() const
{
   Float64 avg_skew_angle = fabs(m_SkewAngle1 + m_SkewAngle2)/2.;

   if ( IsZero(avg_skew_angle) )
      return 1.0;


   Float64 skew = 1.0 + (m_L/(90*m_d))*(sqrt(tan(::ConvertFromSysUnits(avg_skew_angle,unitMeasure::Radian))));

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
bool lrfdLldfTypeG::AssertValid() const
{
   return lrfdLiveLoadDistributionFactorBase::AssertValid();
}

void lrfdLldfTypeG::Dump(dbgDumpContext& os) const
{
   lrfdLiveLoadDistributionFactorBase::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdLldfTypeG::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdLldfTypeG");

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
   Float64 b = S;
   Float64 d = ::ConvertToSysUnits(18.0,unitMeasure::Inch);
   Float64 de = ::ConvertToSysUnits( -10.5, unitMeasure::Inch );

   lrfdLldfTypeG df(1,S,spacings,de,de,
                    Nl,wLane,
                    L,W,I,J,b,d,
                    de,de,0.2,
                    false,0.0,0.0);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.5523, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.5523, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.6051, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.5550, 0.001) );
   
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.600, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.6667, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.3125, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.3125, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.4601, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.5043, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI),  0.5000, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.2604, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.4601, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.5043, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII),  0.5000, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.2604, 0.001) );

   
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);

   TESTME_EPILOG("lrfdLldfTypeG");
}
#endif // _UNITTEST


/****************************************************************************
CLASS
   lrfdLldfTypeF
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdLldfTypeF::lrfdLldfTypeF(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                             Uint32 Nl, Float64 wLane,
                             Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                             Float64 leftDe,Float64 rightDe,
                             Float64 PossionRatio, bool ignoreSkew,
                             Float64 skewAngle1, Float64 skewAngle2) :
lrfdLldfTypeG(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane,
              L,W,I,J,b,d,leftDe,rightDe,PossionRatio, 
              ignoreSkew, skewAngle1, skewAngle2)
{
}

lrfdLldfTypeF::lrfdLldfTypeF(const lrfdLldfTypeF& rOther) :
lrfdLldfTypeG(rOther)
{
   MakeCopy(rOther);
}

lrfdLldfTypeF::~lrfdLldfTypeF()
{
}

//======================== OPERATORS  =======================================
lrfdLldfTypeF& lrfdLldfTypeF::operator= (const lrfdLldfTypeF& rOther)
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
void lrfdLldfTypeF::MakeCopy(const lrfdLldfTypeF& rOther)
{
   lrfdLldfTypeG::MakeCopy(rOther);
}

void lrfdLldfTypeF::MakeAssignment(const lrfdLldfTypeF& rOther)
{
   lrfdLldfTypeG::MakeAssignment( rOther );
   MakeCopy( rOther );
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeF::GetMomentDF_Int_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );

   if ( m_RangeOfApplicabilityAction==roaIgnore || InteriorMomentEquationRule(bSISpec,false) )
   {
      Float64 b = ::ConvertFromSysUnits(m_b,bSISpec ? unitMeasure::Millimeter  : unitMeasure::Inch);
      Float64 L = ::ConvertFromSysUnits(m_L,bSISpec ? unitMeasure::Millimeter  : unitMeasure::Feet);
      Float64 I = ::ConvertFromSysUnits(m_I,bSISpec ? unitMeasure::Millimeter4 : unitMeasure::Inch4);
      Float64 J = ::ConvertFromSysUnits(m_J,bSISpec ? unitMeasure::Millimeter4 : unitMeasure::Inch4);

      Float64 K = (bSISpec ? 2.8 : 33.3);

      Float64 k = 2.5*pow(GetNb(), -0.2);
      if ( k < 1.5 )
         k = 1.5;

      Float64 mg = k*pow(b/(K*L),0.5)*pow(I/J,0.25);

      g.ControllingMethod = SPEC_EQN;
      g.EqnData.bWasUsed = true;
      g.EqnData.e = 1.0;
      g.EqnData.mg = mg;
      g.mg = g.EqnData.mg;
   }
   else
   {
      // lever rule
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, OneLoadedLane);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = MomentSkewCorrectionFactor();
   g.SkewCorrectionFactor = skew;
   g.mg *= skew;

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdLldfTypeF::GetMomentDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   bool bSISpec = ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );

   if ( m_RangeOfApplicabilityAction==roaIgnore || InteriorMomentEquationRule(bSISpec,false) )
   {
      Float64 b = ::ConvertFromSysUnits(m_b,bSISpec ? unitMeasure::Millimeter  : unitMeasure::Inch);
      Float64 L = ::ConvertFromSysUnits(m_L,bSISpec ? unitMeasure::Millimeter  : unitMeasure::Feet);
      Float64 I = ::ConvertFromSysUnits(m_I,bSISpec ? unitMeasure::Millimeter4 : unitMeasure::Inch4);
      Float64 J = ::ConvertFromSysUnits(m_J,bSISpec ? unitMeasure::Millimeter4 : unitMeasure::Inch4);

      Float64 K1 = (bSISpec ? 7600 : 305);
      Float64 K2 = (bSISpec ?    1 :  12);

      Float64 k = 2.5*pow(GetNb(),-0.2);
      if ( k < 1.5 )
         k = 1.5;

      Float64 mg = k*pow(b/K1,0.6)*pow(b/(K2*L),0.2)*pow(I/J,0.06);

      g.ControllingMethod = SPEC_EQN;
      g.EqnData.e = 1.0;
      g.EqnData.bWasUsed = true;
      g.EqnData.mg = mg;
      g.mg = mg;
   }
   else
   {
      // lever rule
      assert(m_RangeOfApplicabilityAction==roaIgnoreUseLeverRule); // only way we should ever get here
      g.ControllingMethod = LEVER_RULE;
      g.LeverRuleData = DistributeByLeverRuleEx(IntGirder, TwoOrMoreLoadedLanes);
      g.mg = g.LeverRuleData.mg;
   }

   Float64 skew = MomentSkewCorrectionFactor();
   g.SkewCorrectionFactor = skew;
   g.mg *= skew;

   return g;
}

bool lrfdLldfTypeF::TestRangeOfApplicability(Location loc) const
{
   if (!DoCheckApplicablity())
      return true;

   bool bSISpec = (lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI );
   bool doThrow=true;

   // most rules are for exterior moment
   ExteriorMomentEquationRule(bSISpec, doThrow);

   // if we have skew
   if (!m_IgnoreSkew && (!IsZero(m_SkewAngle1) || !IsZero(m_SkewAngle2)) )
   {
      Float64 skew_max = ::ConvertToSysUnits( 60.0, unitMeasure::Degree );
      if ( !IsLE(m_SkewAngle1,skew_max) || !IsLE(m_SkewAngle2,skew_max) )
         THROW_DF( lrfdXRangeOfApplicability, SkewAngle, "Excessive skew angle. See Table 4.6.2.2.3c-1");

      Float64 skew_delta_max = ::ConvertToSysUnits( 10.0, unitMeasure::Degree );
      if ( skew_delta_max <= fabs(m_SkewAngle1 - m_SkewAngle2) )
         THROW_DF( lrfdXRangeOfApplicability, SkewAngleDiff, "Excessive difference in skew angles. See Article 4.6.2.2.2e");

      // the depth range is only appicable if Table 4.6.2.2.3c-1 is used
      Float64 dMin = bSISpec ?  430 : 17;
      Float64 dMax = bSISpec ? 1500 : 60;
      Float64 d = ::ConvertFromSysUnits(m_d,bSISpec?unitMeasure::Millimeter:unitMeasure::Inch);
      if ( d < dMin || dMax < d )
         THROW_DF(lrfdXRangeOfApplicability, GirderDepth, "Depth (d) of beam is out of range. See Table 4.6.2.2.3c-1");
   }
   
   return true;
}

bool lrfdLldfTypeF::InteriorMomentEquationRule(bool bSISpec, bool doThrow) const
{
   Float64 bMin = bSISpec ?  900 : 35;
   Float64 bMax = bSISpec ? 1500 : 60;
   Float64 b = ::ConvertFromSysUnits(m_b,bSISpec?unitMeasure::Millimeter:unitMeasure::Inch);
   if ( b < bMin || bMax < b )
      THROW_DF(lrfdXRangeOfApplicability, BeamWidth, "Width (b), of beam is out of range. See Table 4.6.2.2.3a-1");

   Float64 Lmin = bSISpec ?  6000 :  20;
   Float64 Lmax = bSISpec ? 37000 : 120;
   Float64 L = ::ConvertFromSysUnits(m_L,bSISpec?unitMeasure::Millimeter:unitMeasure::Feet);
   if ( L < Lmin || Lmax < L )
      THROW_DF(lrfdXRangeOfApplicability, SpanLength, "Span Length (L) is out of range. See Table 4.6.2.2.3a-1");

   GirderIndexType nb = GetNb();
   if ( nb < 5 || nb > 20 )
      THROW_DF(lrfdXRangeOfApplicability, NumGirders, "Number of girders is out of range (5<=Ng<=20). See Table 4.6.2.2.3a-1");

   return true;
}

//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdLldfTypeF::AssertValid() const
{
   return lrfdLldfTypeG::AssertValid();
}

void lrfdLldfTypeF::Dump(dbgDumpContext& os) const
{
   lrfdLldfTypeG::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdLldfTypeF::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdLldfTypeF");

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);

   Int16 Nb = 5;
   Float64 S = ::ConvertToSysUnits( 4, unitMeasure::Feet );
   std::vector<Float64> spacings;
   spacings.assign(Nb-1,S);
   Float64 L = ::ConvertToSysUnits( 115, unitMeasure::Feet );
   Float64 W = S*Nb;
   Float64 I = ::ConvertToSysUnits(559367.214,unitMeasure::Inch4);
   Float64 J = ::ConvertToSysUnits( 33064.695,unitMeasure::Inch4);
   Float64 wLane = ::ConvertToSysUnits( 12.0, unitMeasure::Feet );
   Int16 Nl = Int16((wLane*(Nb-1))/::ConvertToSysUnits(10., unitMeasure::Feet) );
   Float64 b = S;
   Float64 d = ::ConvertToSysUnits(18.0,unitMeasure::Inch);
   Float64 de = ::ConvertToSysUnits( -10.5, unitMeasure::Inch );

   lrfdLldfTypeF df(1,S,spacings,de,de,Nl,wLane,
                    L,W,I,J,b,d,
                    de,de,0.2,false,0.0,0.0);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.4114, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.3616, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.4508, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.363454, 0.001) );
   
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.4869, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.5138, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.5873, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.6000, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.3428, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.3757, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.4057, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.4894, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.3428, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.3757, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.4057, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.4894, 0.001) );

   
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);

   TESTME_EPILOG("lrfdLldfTypeF");
}
#endif // _UNITTEST

/****************************************************************************
CLASS
   lrfdTxdotVoidedSlab
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdTxdotVoidedSlab::lrfdTxdotVoidedSlab(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                 Uint32 Nl, Float64 wLane,
                 Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                 Float64 leftDe,Float64 rightDe,
                 Float64 PossionRatio,
                 Float64 skewAngle1, Float64 skewAngle2):
// Txdot ignores skew
lrfdLldfTypeG(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,Nl,wLane,
              L,W,I,J,b,d,leftDe,rightDe,PossionRatio, 
              true, skewAngle1, skewAngle2)
{
}

lrfdTxdotVoidedSlab::lrfdTxdotVoidedSlab(const lrfdTxdotVoidedSlab& rOther) :
lrfdLldfTypeG(rOther)
{
   MakeCopy(rOther);
}

lrfdTxdotVoidedSlab::~lrfdTxdotVoidedSlab()
{
}

//======================== OPERATORS  =======================================
lrfdTxdotVoidedSlab& lrfdTxdotVoidedSlab::operator= (const lrfdTxdotVoidedSlab& rOther)
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

Float64 lrfdTxdotVoidedSlab::MomentSkewCorrectionFactor() const
{
   // for Txdot we don't correct for skew
   return 1.0; 
}

Float64 lrfdTxdotVoidedSlab::ShearSkewCorrectionFactor() const
{
   // for Txdot we don't correct for skew
   return 1.0; 
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotVoidedSlab::GetMomentDF_Int_2_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   g = lrfdLldfTypeG::GetMomentDF_Int_1_Strength();

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotVoidedSlab::GetMomentDF_Ext_1_Strength() const
{
   lrfdILiveLoadDistributionFactor::DFResult g;

   g = lrfdLldfTypeG::GetMomentDF_Int_1_Strength();

   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotVoidedSlab::GetMomentDF_Ext_2_Strength() const
{

   // Txdot uses single lane exterior moment for all 
   lrfdILiveLoadDistributionFactor::DFResult g = GetMomentDF_Int_1_Strength();
   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotVoidedSlab::GetShearDF_Int_1_Strength() const
{
   // Txdot uses single lane exterior moment for all 
   lrfdILiveLoadDistributionFactor::DFResult g = GetMomentDF_Int_1_Strength();
   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotVoidedSlab::GetShearDF_Int_2_Strength() const
{
   // Txdot uses single lane exterior moment for all 
   lrfdILiveLoadDistributionFactor::DFResult g = GetMomentDF_Int_1_Strength();
   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotVoidedSlab::GetShearDF_Ext_1_Strength() const
{
   // Txdot uses single lane exterior moment for all 
   lrfdILiveLoadDistributionFactor::DFResult g = GetMomentDF_Int_1_Strength();
   return g;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotVoidedSlab::GetShearDF_Ext_2_Strength() const
{
   // Txdot uses single lane exterior moment for all 
   lrfdILiveLoadDistributionFactor::DFResult g = GetMomentDF_Int_1_Strength();
   return g;
}

void lrfdTxdotVoidedSlab::MakeCopy(const lrfdTxdotVoidedSlab& rOther)
{
   lrfdLldfTypeG::MakeCopy(rOther);
}

void lrfdTxdotVoidedSlab::MakeAssignment(const lrfdTxdotVoidedSlab& rOther)
{
   lrfdLldfTypeG::MakeAssignment( rOther );
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
bool lrfdTxdotVoidedSlab::AssertValid() const
{
   return lrfdLldfTypeG::AssertValid();
}

void lrfdTxdotVoidedSlab::Dump(dbgDumpContext& os) const
{
   lrfdLldfTypeG::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdTxdotVoidedSlab::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdTxdotVoidedSlab");
 
   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);

   Int16 Nb = 5;
   Float64 S = ::ConvertToSysUnits( 4, unitMeasure::Feet );
   std::vector<Float64> spacings;
   spacings.assign(Nb-1,S);
   Float64 L = ::ConvertToSysUnits( 115., unitMeasure::Feet );
   Float64 W = S*Nb;
   Float64 I = ::ConvertToSysUnits(559367.214,unitMeasure::Inch4);
   Float64 J = ::ConvertToSysUnits( 33064.695,unitMeasure::Inch4);
   Float64 wLane = ::ConvertToSysUnits( 12.0, unitMeasure::Feet );
   Int16 Nl = Int16((wLane*(Nb-1))/::ConvertToSysUnits(10., unitMeasure::Feet) );
   Float64 b = S;
   Float64 de = ::ConvertToSysUnits( -10.5, unitMeasure::Inch );
   Float64 d = ::ConvertToSysUnits(18.0,unitMeasure::Inch);

   lrfdTxdotVoidedSlab df(1,S,spacings,de,de,Nl,wLane,
                          L,W,I,J,b,d,
                          de,de,0.2,0.0,0.0);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.3484, 0.001) );
   
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.3484, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.2903, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.2903, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.2903, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.2903, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.2903, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.2903, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.2903, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.2903, 0.001) );

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);

   TESTME_EPILOG("lrfdTxdotVoidedSlab");
}
#endif // _UNITTEST


/****************************************************************************
CLASS
   lrfdTxdotLldfAdjacentBox
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdTxdotLldfAdjacentBox::lrfdTxdotLldfAdjacentBox(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                            Uint32 Nl, Float64 wLane,
                            Float64 L,Float64 W,Float64 I,Float64 J,Float64 b,Float64 d,
                            Float64 leftDe,Float64 rightDe,
                            Float64 PossionRatio,
                            Float64 skewAngle1, Float64 skewAngle2):
lrfdLldfTypeF(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,
              Nl,wLane,L,W,I,J,b,d,
              leftDe,rightDe,PossionRatio,
              false,skewAngle1,skewAngle2)
{
}

lrfdTxdotLldfAdjacentBox::lrfdTxdotLldfAdjacentBox(const lrfdTxdotLldfAdjacentBox& rOther) :
lrfdLldfTypeF(rOther)
{
   MakeCopy(rOther);
}

lrfdTxdotLldfAdjacentBox::~lrfdTxdotLldfAdjacentBox()
{
}

//======================== OPERATORS  =======================================
lrfdTxdotLldfAdjacentBox& lrfdTxdotLldfAdjacentBox::operator= (const lrfdTxdotLldfAdjacentBox& rOther)
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

Float64 lrfdTxdotLldfAdjacentBox::MomentSkewCorrectionFactor() const
{
   // for Txdot we don't correct for skew
   return 1.0; 
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfAdjacentBox::GetMomentDF_Ext_1_Strength() const
{
   // always connected as unit (type f)
   lrfdILiveLoadDistributionFactor::DFResult gext = lrfdLldfTypeF::GetMomentDF_Ext_1_Strength();

   lrfdILiveLoadDistributionFactor::DFResult gint = lrfdLldfTypeF::GetMomentDF_Int_1_Strength();
   if (gint.mg > gext.mg)
   {
      // exterior cannot exceed interior
      gext.ControllingMethod |= INTERIOR_OVERRIDE;
      gext.mg = gint.mg;
   }

   return gext;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfAdjacentBox::GetMomentDF_Ext_2_Strength() const
{
   // always connected as unit (type f)
   lrfdILiveLoadDistributionFactor::DFResult gext = lrfdLldfTypeF::GetMomentDF_Ext_2_Strength();

   lrfdILiveLoadDistributionFactor::DFResult gint = lrfdLldfTypeF::GetMomentDF_Int_2_Strength();
   if (gint.mg > gext.mg)
   {
      // exterior cannot exceed interior
      gext.ControllingMethod |= INTERIOR_OVERRIDE;
      gext.mg = gint.mg;
   }

   return gext;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfAdjacentBox::GetShearDF_Ext_1_Strength() const
{
   // always connected as unit (type f)
   lrfdILiveLoadDistributionFactor::DFResult gext = lrfdLldfTypeF::GetShearDF_Ext_1_Strength();

   lrfdILiveLoadDistributionFactor::DFResult gint = lrfdLldfTypeF::GetShearDF_Int_1_Strength();
   if (gint.mg > gext.mg)
   {
      // exterior cannot exceed interior
      gext.ControllingMethod |= INTERIOR_OVERRIDE;
      gext.mg = gint.mg;
   }

   return gext;
}

lrfdILiveLoadDistributionFactor::DFResult lrfdTxdotLldfAdjacentBox::GetShearDF_Ext_2_Strength() const
{
   // always connected as unit (type f)
   lrfdILiveLoadDistributionFactor::DFResult gext = lrfdLldfTypeF::GetShearDF_Ext_2_Strength();

   lrfdILiveLoadDistributionFactor::DFResult gint = lrfdLldfTypeF::GetShearDF_Int_2_Strength();
   if (gint.mg > gext.mg)
   {
      // exterior cannot exceed interior
      gext.ControllingMethod |= INTERIOR_OVERRIDE;
      gext.mg = gint.mg;
   }

   return gext;
}

void lrfdTxdotLldfAdjacentBox::MakeCopy(const lrfdTxdotLldfAdjacentBox& rOther)
{
   lrfdLldfTypeG::MakeCopy(rOther);
}

void lrfdTxdotLldfAdjacentBox::MakeAssignment(const lrfdTxdotLldfAdjacentBox& rOther)
{
   lrfdLldfTypeG::MakeAssignment( rOther );
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
bool lrfdTxdotLldfAdjacentBox::AssertValid() const
{
   return lrfdLldfTypeG::AssertValid();
}

void lrfdTxdotLldfAdjacentBox::Dump(dbgDumpContext& os) const
{
   lrfdLldfTypeG::Dump( os );
}
#endif // _DEBUG

#if defined _UNITTEST
bool lrfdTxdotLldfAdjacentBox::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdTxdotLldfAdjacentBox");

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::US);

   Int16 Nb = 5;
   Float64 S = ::ConvertToSysUnits( 4, unitMeasure::Feet );
   std::vector<Float64> spacings;
   spacings.assign(Nb-1,S);
   Float64 L = ::ConvertToSysUnits( 115., unitMeasure::Feet );
   Float64 W = S*Nb;
   Float64 I = ::ConvertToSysUnits(559367.214,unitMeasure::Inch4);
   Float64 J = ::ConvertToSysUnits( 33064.695,unitMeasure::Inch4);
   Float64 wLane = ::ConvertToSysUnits( 12.0, unitMeasure::Feet );
   Int16 Nl = Int16((wLane*(Nb-1))/::ConvertToSysUnits(10., unitMeasure::Feet) );
   Float64 b = S;
   Float64 de = ::ConvertToSysUnits( -10.5, unitMeasure::Inch );
   Float64 d = ::ConvertToSysUnits(18.0,unitMeasure::Inch);

   lrfdTxdotLldfAdjacentBox df(1,S,spacings,de,de,Nl,wLane,
                               L,W,I,J,b,d,
                               de,de,0.2,
                               0.0,0.0);

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.3484, 0.001) );
   
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.4869, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.5138, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::StrengthI), 0.4869, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::TwoOrMoreLoadedLanes,lrfdTypes::StrengthI), 0.5138, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.4869, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueI), 0.4869, 0.001) );

   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.MomentDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.3484, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::IntGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.4869, 0.001) );
   TRY_TESTME( IsEqual( df.ShearDF(lrfdILiveLoadDistributionFactor::ExtGirder,lrfdILiveLoadDistributionFactor::OneLoadedLane,lrfdTypes::FatigueII), 0.4869, 0.001) );

   lrfdVersionMgr::SetUnits(lrfdVersionMgr::SI);

   TESTME_EPILOG("lrfdTxdotLldfAdjacentBox");
}
#endif // _UNITTEST


