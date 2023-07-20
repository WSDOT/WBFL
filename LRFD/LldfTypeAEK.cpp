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

#include <Lrfd\LldfTypeAEK.h>
#include <Lrfd\XRangeOfApplicability.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\Utility.h>
#include <Units\Convert.h>

using namespace WBFL::LRFD;

LldfTypeAEK::LldfTypeAEK(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                                 Uint32 Nl, Float64 wLane,
                                 Float64 L,Float64 ts,Float64 n,
                                 Float64 I, Float64 A, Float64 eg,
                                 bool bXFrames,
                                 Float64 skewAngle1, Float64 skewAngle2,
                                 bool bSkewMoment,
                                 bool bSkewShear) :
// For aek's de and roadoverhange are the same because there is a single web
LldfTypeAEKIJ(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,
                  Nl,wLane,leftOverhang,rightOverhang,L,ts,n,
                  I,A,eg, skewAngle1, skewAngle2,bSkewMoment,bSkewShear)
{
   m_bXFrames = bXFrames;
}

ILiveLoadDistributionFactor::DFResult LldfTypeAEK::GetMomentDF_Ext_1_Strength() const
{
   Float64 skew;
   ILiveLoadDistributionFactor::DFResult g;

   g = LldfTypeAEKIJ::GetMomentDF_Ext_1_Strength(); // accounts for skew

   if (m_bXFrames)
   {
      // but not less than that which would be obtained by assuming that the
      // cross-section deflects and rotates as a rigid cross-section. 4.6.2.2.2d
      g.RigidData = DistributeByRigidMethod(m_Side, m_Spacings, m_LeftCurbOverhang, m_RightCurbOverhang, m_wLane, 1, 1,true);

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

ILiveLoadDistributionFactor::DFResult LldfTypeAEK::GetMomentDF_Ext_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;
   Float64 skew;

   g = LldfTypeAEKIJ::GetMomentDF_Ext_2_Strength();

   if (m_bXFrames)
   {
      // but not less than that which would be obtained by assuming that the
      // cross-section deflects and rotates as a rigid cross-section. 4.6.2.2.2d
      g.RigidData = DistributeByRigidMethod(m_Side, m_Spacings, m_LeftCurbOverhang, m_RightCurbOverhang, m_wLane,2,m_Nl, true);
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

ILiveLoadDistributionFactor::DFResult LldfTypeAEK::GetShearDF_Ext_1_Strength() const
{
   Float64 skew;
   ILiveLoadDistributionFactor::DFResult g;

   g = LldfTypeAEKIJ::GetShearDF_Ext_1_Strength(); // accounts for skew

   if (m_bXFrames)
   {
      // but not less than that which would be obtained by assuming that the
      // cross-section deflects and rotates as a rigid cross-section. 4.6.2.2.2d
      g.RigidData = DistributeByRigidMethod(m_Side, m_Spacings, m_LeftCurbOverhang, m_RightCurbOverhang, m_wLane, 1, 1, true);

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

ILiveLoadDistributionFactor::DFResult LldfTypeAEK::GetShearDF_Ext_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult g;
   Float64 skew;

   g = LldfTypeAEKIJ::GetShearDF_Ext_2_Strength();

   if (m_bXFrames)
      {
         // but not less than that which would be obtained by assuming that the
         // cross-section deflects and rotates as a rigid cross-section. 4.6.2.2.2d
         g.RigidData = DistributeByRigidMethod(m_Side, m_Spacings, m_LeftCurbOverhang, m_RightCurbOverhang, m_wLane,2,m_Nl, true);
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

///////////////////////////////////////////

WsdotLldfTypeAEK::WsdotLldfTypeAEK(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,Float64 leftOverhang,Float64 rightOverhang,
                                           Uint32 Nl, Float64 wLane,
                                           Float64 L,Float64 ts,Float64 n,
                                           Float64 I, Float64 A, Float64 eg,
                                           Float64 leftSlabOverhang,Float64 rightSlabOverhang,
                                           bool bXFrames,
                                           Float64 skewAngle1, Float64 skewAngle2,
                                           bool bSkewMoment,
                                           bool bSkewShear,
                                           Float64 slabCantileverThreshold) :
LldfTypeAEKIJ(gdr,Savg,gdrSpacings,leftOverhang,rightOverhang,
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

bool WsdotLldfTypeAEK::SlabCantileverTest() const
{
   Float64 slab_cantilever = m_Side==DfSide::LeftSide ? m_LeftSlabOverhang : m_RightSlabOverhang;
   return IsGT(m_SlabCantileverThreshold*m_Savg,slab_cantilever,0.001);
}

ILiveLoadDistributionFactor::DFResult WsdotLldfTypeAEK::GetMomentDF_Ext_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult gi;
   gi = LldfTypeAEKIJ::GetMomentDF_Int_1_Strength();

   if (SlabCantileverTest())
   {
      // compare with lever rule with mpf=1.0
      ILiveLoadDistributionFactor::DFResult gext;
      gext.ControllingMethod = LEVER_RULE;
      gext.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::One, true);

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

ILiveLoadDistributionFactor::DFResult WsdotLldfTypeAEK::GetMomentDF_Ext_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult gext;

   if (SlabCantileverTest())
   {
      // subclass will compute using interior with e factor, or lever rule
      gext = LldfTypeAEKIJ::GetMomentDF_Ext_2_Strength();

      // Additional rule here is that we must exceed the interior value for both lever and equation cases
      if (gext.ControllingMethod & SPEC_EQN)
      {
         gext.EqnData.m = Utility::GetMultiplePresenceFactor(2);

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
         ILiveLoadDistributionFactor::DFResult gint = LldfTypeAEKIJ::GetMomentDF_Int_2_Strength();
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

ILiveLoadDistributionFactor::DFResult WsdotLldfTypeAEK::GetShearDF_Ext_1_Strength() const
{
   ILiveLoadDistributionFactor::DFResult gi;
   gi = LldfTypeAEKIJ::GetShearDF_Int_1_Strength();

   if (SlabCantileverTest())
   {
      // compare with lever rule with mpf=1.0
      ILiveLoadDistributionFactor::DFResult gext;
      gext.ControllingMethod = LEVER_RULE;
      gext.LeverRuleData = DistributeByLeverRuleEx(Location::ExtGirder, NumLoadedLanes::One, true);

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

ILiveLoadDistributionFactor::DFResult WsdotLldfTypeAEK::GetShearDF_Ext_2_Strength() const
{
   ILiveLoadDistributionFactor::DFResult gext;

   if (SlabCantileverTest())
   {
      // subclass will compute using interior with e factor, or lever rule
      gext = LldfTypeAEKIJ::GetShearDF_Ext_2_Strength();

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
         gext.EqnData.m = Utility::GetMultiplePresenceFactor(2);
      }
      else if (gext.ControllingMethod & LEVER_RULE)
      {
         ILiveLoadDistributionFactor::DFResult gint = LldfTypeAEKIJ::GetShearDF_Int_2_Strength();
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
