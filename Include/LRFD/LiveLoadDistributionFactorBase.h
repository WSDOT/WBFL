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

#pragma once

#include <Lrfd\LrfdExp.h>
#include <Lrfd\ILiveLoadDistributionFactor.h>

namespace WBFL
{
   namespace LRFD
   {
      // NOTE: Use this inside of TestRangeOfApplicability() so it throws or returns a value 
      //       depending on the need of the caller
      #define THROW_DF(ex,code,extra) {if(doThrow) THROW_EX(ex,ex::Reason::code,extra); return false; }

      /// @brief A class with nifty utilities for computing common distribution factor stuff
      class LRFDCLASS LiveLoadDistributionFactorMixin
      {
      public:
         LiveLoadDistributionFactorMixin() = default;
         LiveLoadDistributionFactorMixin(const LiveLoadDistributionFactorMixin&) = default;
         virtual ~LiveLoadDistributionFactorMixin() = default;
         LiveLoadDistributionFactorMixin& operator=(const LiveLoadDistributionFactorMixin&) = default;

         virtual ILiveLoadDistributionFactor::LeverRuleMethod DistributeByLeverRule(GirderIndexType beamNum,const std::vector<Float64>& Spacings, Float64 leftOverhang, Float64 rightOverhang,Float64 wLane,IndexType Nl, bool applyMpf) const;

         /// @brief Computes distribution factor by rigid (statical) method. This is only for exterior beams
         virtual ILiveLoadDistributionFactor::RigidMethod DistributeByRigidMethod(ILiveLoadDistributionFactor::DfSide side,const std::vector<Float64>& Spacings, Float64 leftOverhang, Float64 rightOverhang,
                                                                                         Float64 wLane, IndexType firstLoadedLane,IndexType lastLoadedLane, bool applyMpf) const;

         /// @brief Returns the distance from the curb line to the wheel line
         virtual Float64 GetShyDistance() const;

         /// @brief Returns the spacing between wheel lines
         virtual Float64 GetWheelLineSpacing() const;

         /// @brief Returns the width of the truck
         virtual Float64 GetTruckWidth() const;

         virtual ILiveLoadDistributionFactor::DFResult GetLanesBeamsMethod(IndexType Nl,GirderIndexType Nb, bool applyMpf) const;

         void IgnoreMpfLeverRule(bool doIgnore);
         bool IgnoreMpfLeverRule() const;

      private:
         ILiveLoadDistributionFactor::LeverRuleMethod DistributeByLeverRulePerLaneExterior(GirderIndexType Nb, Float64 S, Float64 curbOverhang, Float64 wLane,IndexType Nl, bool applyMpf) const;
         Float64 GetDistanceToAxle(Float64 S,Float64 roadOverhang,Float64 wLane,GirderIndexType nbeam,AxleIndexType naxle,bool bAlignLeft) const;

         bool m_IgnoreMpfForLeverRuleSingleLane = false;
      };

      /// @brief Base class for common implementation of ILiveLoadDistributionFactor.
      /// This class implements template methods (Template Pattern) for computing
      /// live load distribution factors.  Derived classes provide the details.
      class LRFDCLASS LiveLoadDistributionFactorBase : public ILiveLoadDistributionFactor, public LiveLoadDistributionFactorMixin
      {
      public:
         LiveLoadDistributionFactorBase() = delete;
         LiveLoadDistributionFactorBase(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,
                                            Float64 leftOverhang,Float64 rightOverhang,
                                            IndexType Nl, Float64 wLane,
                                            bool bSkewMoment, bool bSkewShear);

         LiveLoadDistributionFactorBase(const LiveLoadDistributionFactorBase&) = default;
         ~LiveLoadDistributionFactorBase() = default;

         LiveLoadDistributionFactorBase& operator=(const LiveLoadDistributionFactorBase&) = default;

         virtual Float64 MomentDF(Location loc,NumLoadedLanes numLanes,LimitState ls) const override;
         virtual DFResult MomentDFEx(Location loc,NumLoadedLanes numLanes,LimitState ls) const override;

         virtual Float64 ShearDF(Location loc,NumLoadedLanes numLanes,LimitState ls) const override;
         virtual DFResult ShearDFEx(Location loc,NumLoadedLanes numLanes,LimitState ls) const override;
   
         virtual Float64 ReactionDF(Location loc,NumLoadedLanes numLanes,LimitState ls) const override;
         virtual DFResult ReactionDFEx(Location loc,NumLoadedLanes numLanes,LimitState ls) const override;

         virtual Float64 MomentSkewCorrectionFactor() const = 0;
         virtual Float64 ShearSkewCorrectionFactor() const = 0;

         virtual ILiveLoadDistributionFactor::DFResult DistributeMomentByLeverRule(Location loc,NumLoadedLanes numLanes, bool applyMpf) const override;
         virtual ILiveLoadDistributionFactor::DFResult DistributeShearByLeverRule(Location loc,NumLoadedLanes numLanes, bool applyMpf) const override;
         virtual ILiveLoadDistributionFactor::DFResult DistributeReactionByLeverRule(Location loc,NumLoadedLanes numLanes, bool applyMpf) const override;

         virtual ILiveLoadDistributionFactor::LeverRuleMethod DistributeByLeverRuleEx(Location loc,NumLoadedLanes numLanes, bool applyMpf) const;

         void SetRangeOfApplicabilityAction(RangeOfApplicabilityAction check);
         RangeOfApplicabilityAction GetRangeOfApplicabilityAction() const;

         GirderIndexType GetNb() const
         {
            return m_Nb;
         }

      protected:
         GirderIndexType   m_GdrNum;
         std::vector<Float64> m_Spacings;
         Float64 m_Savg;
         Float64 m_LeftCurbOverhang;
         Float64 m_RightCurbOverhang;
         IndexType m_Nl;
         Float64 m_wLane;

         bool m_bSkewMoment;
         bool m_bSkewShear;

         DfSide  m_Side; // beam is nearest to this side

         GirderIndexType   m_Nb; // cached number of beams

         RangeOfApplicabilityAction m_RangeOfApplicabilityAction;

         virtual bool DoCheckApplicablity() const
         {
            return m_RangeOfApplicabilityAction == RangeOfApplicabilityAction::Enforce;
         }

         /// @brief return true if test passes (we are within range)
         virtual bool TestRangeOfApplicability(Location loc) const = 0;

         virtual DFResult GetMomentDF_Int_1_Strength() const = 0;
         virtual DFResult GetMomentDF_Int_2_Strength() const = 0;
         virtual DFResult GetMomentDF_Ext_1_Strength() const = 0;
         virtual DFResult GetMomentDF_Ext_2_Strength() const = 0;

         virtual DFResult GetShearDF_Int_1_Strength() const = 0;
         virtual DFResult GetShearDF_Int_2_Strength() const = 0;
         virtual DFResult GetShearDF_Ext_1_Strength() const = 0;
         virtual DFResult GetShearDF_Ext_2_Strength() const = 0;

         virtual DFResult GetReactionDF_Int_1_Strength() const;
         virtual DFResult GetReactionDF_Int_2_Strength() const;
         virtual DFResult GetReactionDF_Ext_1_Strength() const;
         virtual DFResult GetReactionDF_Ext_2_Strength() const;

         // Default Behavior for fatigue is to remove multiple presence from single lane strength case
         virtual DFResult GetMomentDF_Int_Fatigue() const;
         virtual DFResult GetMomentDF_Ext_Fatigue() const;
         virtual DFResult GetShearDF_Int_Fatigue() const;
         virtual DFResult GetShearDF_Ext_Fatigue() const;
         virtual DFResult GetReactionDF_Ext_Fatigue() const;
         virtual DFResult GetReactionDF_Int_Fatigue() const;
      };
   };
};
