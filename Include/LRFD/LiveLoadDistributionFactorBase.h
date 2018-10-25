///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2018  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_LIVELOADDISTRIBUTIONFACTORBASE_H_
#define INCLUDED_LRFD_LIVELOADDISTRIBUTIONFACTORBASE_H_
#pragma once

// SYSTEM INCLUDES
//
#include <assert.h>

// PROJECT INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <Lrfd\ILiveLoadDistributionFactor.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
// NOTE: Use this inside of TestRangeOfApplicability() so it throws or returns a value 
//       depending on the need of the caller
#define THROW_DF(ex,code,extra) {if(doThrow) THROW_EX(ex,code,extra); return false; }

// MISCELLANEOUS
// A class with nifty utilities for computing common distribution factor stuff
class LRFDCLASS lrfdLiveLoadDistributionFactorMixin
{
public:
   //------------------------------------------------------------------------
   lrfdLiveLoadDistributionFactorMixin();

   //------------------------------------------------------------------------
   virtual lrfdILiveLoadDistributionFactor::LeverRuleMethod DistributeByLeverRule(GirderIndexType beamNum,const std::vector<Float64>& Spacings, Float64 leftOverhang, Float64 rightOverhang,Float64 wLane,IndexType Nl) const;
   //------------------------------------------------------------------------
   // Statical method only works for exterior beams
   virtual lrfdILiveLoadDistributionFactor::RigidMethod DistributeByStaticalMethod(lrfdILiveLoadDistributionFactor::DfSide side,const std::vector<Float64>& Spacings, Float64 leftOverhang, Float64 rightOverhang,Float64 wLane, IndexType firstLoadedLane,IndexType lastLoadedLane) const;
   //------------------------------------------------------------------------
   virtual Float64 GetShyDistance() const;
   //------------------------------------------------------------------------
   virtual Float64 GetWheelLineSpacing() const;
   //------------------------------------------------------------------------
   virtual Float64 GetTruckWidth() const;

   virtual lrfdILiveLoadDistributionFactor::DFResult GetLanesBeamsMethod(IndexType Nl,GirderIndexType Nb) const;

   // Local data to ignore MPF for lever rule when a single truck controls on exterior beams
   void IgnoreMpfLeverRule(bool doIgnore);
   bool IgnoreMpfLeverRule() const;

   //------------------------------------------------------------------------
   void MakeCopy(const lrfdLiveLoadDistributionFactorMixin& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdLiveLoadDistributionFactorMixin& rOther);


private:
   //------------------------------------------------------------------------
   lrfdILiveLoadDistributionFactor::LeverRuleMethod DistributeByLeverRulePerLaneExterior(GirderIndexType Nb, Float64 S, Float64 curbOverhang, Float64 wLane,IndexType Nl) const;
   //------------------------------------------------------------------------
   Float64 GetDistanceToAxle(Float64 S,Float64 roadOverhang,Float64 wLane,GirderIndexType nbeam,AxleIndexType naxle,bool bAlignLeft) const;


   bool m_IgnoreMpfForLeverRuleSingleLane;
};

//
/*****************************************************************************
CLASS 
   lrfdLiveLoadDistributionFactorBase

   Base class for common implementation of lrfdILiveLoadDistributionFactor


DESCRIPTION
   Base class for common implementation of lrfdILiveLoadDistributionFactor.
   This class implements template methods (Template Pattern) for computing
   live load distribution factors.  Derived classes provide the details.

LOG
   rab : 11.12.1998 : Created file
*****************************************************************************/

class LRFDCLASS lrfdLiveLoadDistributionFactorBase : public lrfdILiveLoadDistributionFactor, public lrfdLiveLoadDistributionFactorMixin
{
public:
   // GROUP: LIFECYCLE
   lrfdLiveLoadDistributionFactorBase(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,
                                      Float64 leftOverhang,Float64 rightOverhang,
                                      CollectionIndexType Nl, Float64 wLane,
                                      bool bSkewMoment, bool bSkewShear);
private:
   //------------------------------------------------------------------------
   // no default
   lrfdLiveLoadDistributionFactorBase();
public:

   //------------------------------------------------------------------------
   lrfdLiveLoadDistributionFactorBase(const lrfdLiveLoadDistributionFactorBase& rOther);
   
   //------------------------------------------------------------------------
   ~lrfdLiveLoadDistributionFactorBase();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   lrfdLiveLoadDistributionFactorBase& operator=(const lrfdLiveLoadDistributionFactorBase& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual Float64 MomentDF(Location loc,NumLoadedLanes numLanes,lrfdTypes::LimitState ls) const override;
   virtual DFResult MomentDFEx(Location loc,NumLoadedLanes numLanes,lrfdTypes::LimitState ls) const override;

   //------------------------------------------------------------------------
   virtual Float64 ShearDF(Location loc,NumLoadedLanes numLanes,lrfdTypes::LimitState ls) const override;
   virtual DFResult ShearDFEx(Location loc,NumLoadedLanes numLanes,lrfdTypes::LimitState ls) const override;
   
   //------------------------------------------------------------------------
   virtual Float64 ReactionDF(Location loc,NumLoadedLanes numLanes,lrfdTypes::LimitState ls) const override;
   virtual DFResult ReactionDFEx(Location loc,NumLoadedLanes numLanes,lrfdTypes::LimitState ls) const override;

   //------------------------------------------------------------------------
   virtual Float64 MomentSkewCorrectionFactor() const = 0;
   virtual Float64 ShearSkewCorrectionFactor() const = 0;

   //------------------------------------------------------------------------
   virtual lrfdILiveLoadDistributionFactor::DFResult DistributeMomentByLeverRule(Location loc,NumLoadedLanes numLanes) const override;
   virtual lrfdILiveLoadDistributionFactor::DFResult DistributeShearByLeverRule(Location loc,NumLoadedLanes numLanes) const override;
   virtual lrfdILiveLoadDistributionFactor::DFResult DistributeReactionByLeverRule(Location loc,NumLoadedLanes numLanes) const override;

   virtual lrfdILiveLoadDistributionFactor::LeverRuleMethod DistributeByLeverRuleEx(Location loc,NumLoadedLanes numLanes) const;

   // GROUP: ACCESS
   void SetRangeOfApplicabilityAction(LldfRangeOfApplicabilityAction check);
   LldfRangeOfApplicabilityAction GetRangeOfApplicabilityAction() const;

   // GROUP: INQUIRY
   // number of beams
   GirderIndexType GetNb() const
   {
      return m_Nb;
   }

protected:
   // GROUP: DATA MEMBERS
   GirderIndexType   m_GdrNum;
   std::vector<Float64> m_Spacings;
   Float64 m_Savg;
   Float64 m_LeftCurbOverhang;
   Float64 m_RightCurbOverhang;
   CollectionIndexType m_Nl;
   Float64 m_wLane;

   bool m_bSkewMoment;
   bool m_bSkewShear;

   DfSide  m_Side; // beam is nearest to this side

   GirderIndexType   m_Nb; // cached number of beams

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   LldfRangeOfApplicabilityAction m_RangeOfApplicabilityAction;

   virtual bool DoCheckApplicablity() const
   {
      return m_RangeOfApplicabilityAction==roaEnforce;
   }

   //------------------------------------------------------------------------
   void MakeCopy(const lrfdLiveLoadDistributionFactorBase& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const lrfdLiveLoadDistributionFactorBase& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // return true if test passes (we are within range)
   virtual bool TestRangeOfApplicability(Location loc) const = 0;

   // Override for specific supporting component and deck type
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Int_1_Strength() const = 0;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Int_2_Strength() const = 0;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_1_Strength() const = 0;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_2_Strength() const = 0;

   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Int_1_Strength() const = 0;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Int_2_Strength() const = 0;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_1_Strength() const = 0;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_2_Strength() const = 0;

   //------------------------------------------------------------------------
   virtual DFResult GetReactionDF_Int_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetReactionDF_Int_2_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetReactionDF_Ext_1_Strength() const;
   //------------------------------------------------------------------------
   virtual DFResult GetReactionDF_Ext_2_Strength() const;

   //
   // Default Behavior for fatigue is to remove multiple presence from single
   // lane strength case
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Int_Fatigue() const;
   //------------------------------------------------------------------------
   virtual DFResult GetMomentDF_Ext_Fatigue() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Int_Fatigue() const;
   //------------------------------------------------------------------------
   virtual DFResult GetShearDF_Ext_Fatigue() const;
   //------------------------------------------------------------------------
   virtual DFResult GetReactionDF_Ext_Fatigue() const;
   //------------------------------------------------------------------------
   virtual DFResult GetReactionDF_Int_Fatigue() const;

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_LIVELOADDISTRIBUTIONFACTORBASE_H_
