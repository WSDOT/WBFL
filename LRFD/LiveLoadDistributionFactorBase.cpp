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
#include <Lrfd\LiveLoadDistributionFactorBase.h>
#include <Lrfd\Utility.h>
#include <Lrfd\VersionMgr.h>
#include <set>
#include <algorithm>

using namespace WBFL::LRFD;

// Local function for negating multiple presence factors. 
// Used to compute fatigue factor from strength
static void NegateMpf(ILiveLoadDistributionFactor::DFResult& g)
{
   // Some methods compute mpf explicitly, equation method will not
   if (g.LeverRuleData.bWasUsed)
   {
      Float64 mpf =  g.LeverRuleData.m;
      g.LeverRuleData.mg /= mpf;
      g.LeverRuleData.m = 1.0;

      if (g.ControllingMethod & LEVER_RULE)
      {
         g.mg /= mpf;
      }
   }

   if (g.RigidData.bWasUsed)
   {
      Float64 mpf =  g.RigidData.m;
      g.RigidData.mg /= mpf;
      g.RigidData.m = 1.0;

      if (g.ControllingMethod & RIGID_METHOD)
      {
         g.mg /= mpf;
      }
   }

   if (g.LanesBeamsData.bWasUsed)
   {
      Float64 mpf =  g.LanesBeamsData.m;
      g.LanesBeamsData.mg /= mpf;
      g.LanesBeamsData.m = 1.0;

      if (g.ControllingMethod & LANES_DIV_BEAMS)
      {
         g.mg /= mpf;
      }
   }

   // Check if equation method controlled
   if (g.ControllingMethod & SPEC_EQN)
   {
      Float64 mpf = Utility::GetMultiplePresenceFactor(1);
      g.mg /= mpf;
   }
}


// Local Class for maximizing land/truck placement for the lever rule for
// interior beams. This assumes that the maximum condition will occur when
// an axle is directly over the beam being investigated. However, there are four
// configurations that must be computed.
// 1) left axle over beam, shy distance on left side of lane
// 2)  "" " """""""""""""""""""""""""""""  right side
// 3) right axle over beam, shy distance on left side
// 4)  "" " """""""""""""""""""""""""""""  right side
//
// Where the shy distance is the minimum distance between the axle and lane boundary.
//
// This class computes the axle locations and lever response for each of the 4 configurations
// above. Enveloping over these 4 should give the max lever rule response for any give number of
// lanes
class InteriorLeverRuleAxlePlacer
{
public:
   enum ControllingStrategy {LeftAxleLeftShy,LeftAxleRightShy,RightAxleLeftShy,RightAxleRightShy};


   InteriorLeverRuleAxlePlacer(Float64 Sleft, Float64 Sright,
                                          Float64 leftCurb, Float64 rightCurb,
                                          Float64 shyDist, Float64 axleWidth, 
                                          Float64 wLane):
   m_Sleft(Sleft),m_Sright(Sright),
   m_leftCurb(leftCurb),m_rightCurb(rightCurb),
   m_shyDist(shyDist),m_axleWidth(axleWidth),m_wLane(wLane),
   m_IsComputed(false)
   {
   }

   Float64 ComputeMaxFactor(IndexType nL, bool applyMpf, ControllingStrategy* pControl); // compute factor only for Nl, return max strategy
   ILiveLoadDistributionFactor::LeverRuleMethod ComputeLeverRuleDistribution(IndexType nL, bool applyMpf, ControllingStrategy strategy); // return filled in class

private:
   Float64 m_Sleft;      // girder spacing to left and right of our beam
   Float64 m_Sright;
   Float64 m_leftCurb;   // distance from our beam to the left/right curb
   Float64 m_rightCurb;
   Float64 m_shyDist;   
   Float64 m_axleWidth;
   Float64 m_wLane;

   bool m_IsComputed; // have we computed yet?

   struct LaneLocation
   {
      Float64 LeftAxleLocation;  // measured postive both left and right away from beam
      Float64 RightAxleLocation;

      Float64 LeftAxleLeverForce;   // unit load times lever / (spacing)
      Float64 RightAxleLeverForce;

      LaneLocation():
      LeftAxleLeverForce(0.0),RightAxleLeverForce(0.0),LeftAxleLocation(Float64_Max),RightAxleLocation(Float64_Max)
      {;}

      bool operator==(const LaneLocation& rOther) const
      { 
         return LeftAxleLeverForce+RightAxleLeverForce == rOther.LeftAxleLeverForce+rOther.RightAxleLeverForce;
      }

      bool operator<(const LaneLocation& rOther) const 
      { 
         // TRICKY: The whole reason we are using a set here is to sort the lanes by their maximum effectiveness.
         //         This means that we want the lanes with the largest applied lever to be first in the list.
         //         Hence that greater than's
         if ( !(*this==rOther)) // small chance that left and right placements could have same LeverForce
         {
            return LeftAxleLeverForce+RightAxleLeverForce > rOther.LeftAxleLeverForce+rOther.RightAxleLeverForce; 
         }
         else
         {
            return LeftAxleLocation > rOther.LeftAxleLocation;
         }
      }
   };

   // These are possible lane/axle locations for each of the four possible locations
   // They will be ordered by the maximum lever they apply to our girder
   using LaneSet = std::set<LaneLocation>;
   LaneSet m_LeftAxleLeftShy;
   LaneSet m_LeftAxleRightShy;
   LaneSet m_RightAxleLeftShy;
   LaneSet m_RightAxleRightShy;

   /////////
   void Compute();
   void ComputeLaneLayout(Float64 laneSplitLoc, Float64 leftShy, Float64 rightShy, LaneSet& rLaneSet);

};


// Here we compute the possible lane layouts for each of the four possible configurations
void InteriorLeverRuleAxlePlacer::Compute()
{
   if (!m_IsComputed)
   {
      // Distance from lane split to nearest axle when truck is shifted to far side of lane
      Float64 out_shy = m_wLane - m_axleWidth - m_shyDist;
      assert(out_shy>=m_shyDist);

      // Case 1) left axle over beam, shy distance on left side of lane
      ComputeLaneLayout(-m_shyDist, m_shyDist, m_shyDist, m_LeftAxleLeftShy);

      // Case 2) left axle over beam, shy distance on right side of lane
      ComputeLaneLayout(-out_shy, m_shyDist, out_shy, m_LeftAxleRightShy);

      // Case 3) right axle over beam, shy distance on left side of lane
      ComputeLaneLayout(out_shy, out_shy, m_shyDist, m_RightAxleLeftShy);

      // Case 4) right axle over beam, shy distance on right side of lane
      ComputeLaneLayout(m_shyDist, m_shyDist, m_shyDist, m_RightAxleRightShy);

      m_IsComputed = true;
   }
}

// This function does the heavy lifting for computing lane/axle locations.
// The input is the location of the nearest lane split to our girder (left is positive)
// and the distance from the lane split to the nearest girders to the left and right of it
void InteriorLeverRuleAxlePlacer::ComputeLaneLayout(Float64 laneSplitLoc, Float64 leftShy, Float64 rightShy, LaneSet& rLaneSet)
{
   const Float64 LANETOLER=1.0e-04;

   // First start from lane split working to to right side
   Float64 left_lane_edge = laneSplitLoc;
   bool first=true;
   while(true)
   {

// The following commented out code makes lane placement account for exterior
// barriers. Remove commenting if a decision is made to account.

//      if (left_lane_edge+m_wLane < m_rightCurb+LANETOLER)
//      {
         LaneLocation lane_loc;

         Float64 left_axle;
         if (first)
         {
            // For the first lane, we want to use the passed in shy distance. Then
            // use the min shy distance after
            left_axle = left_lane_edge + rightShy;
            first = false;
         }
         else
         {
            left_axle = left_lane_edge + m_shyDist;
         }

         if (left_axle < m_Sright)
         {
            // left axle applies force
            lane_loc.LeftAxleLocation   = m_Sright-left_axle; // on right side axle locs are positive
            lane_loc.LeftAxleLeverForce = (m_Sright-left_axle)/(2.0*m_Sright);

            Float64 right_axle = left_axle + m_axleWidth;
            if (right_axle < m_Sright)
            {
               // right axle applies force
               lane_loc.RightAxleLocation   = m_Sright-right_axle;
               lane_loc.RightAxleLeverForce = (m_Sright-right_axle)/(2.0*m_Sright);
            }

            rLaneSet.insert(lane_loc);
         }
         else
         {
            break; // left axle past spacing
         }
//      }
//      else
//      {
//         // lane won't fit
//         break;
//      }

      // on to next lane
      left_lane_edge += m_wLane;
   }

   // Now add lanes to left side
   // For sanity's sake (at least mine), use positive spacings even though we are working on the 
   // left (negative) side. The only adjustments required is to flip the sign of the lane split
   // and signs of axle locations when they are save.
   Float64 right_lane_edge = -1.0*laneSplitLoc;
   first = true;
   while(true)
   {
//      if (right_lane_edge+m_wLane < m_leftCurb+LANETOLER)
//      {
         LaneLocation lane_loc;

         Float64 right_axle;
         if (first)
         {
            // For the first lane, we want to use the passed in shy distance. Then
            // use the min shy distance after
            right_axle = right_lane_edge + leftShy;
            first = false;
         }
         else
         {
            right_axle = right_lane_edge + m_shyDist;
         }

         if (right_axle < m_Sleft)
         {
            // Store axles left of beam as negative
            // left axle applies force
            lane_loc.RightAxleLocation   = -(m_Sleft-right_axle);
            lane_loc.RightAxleLeverForce = (m_Sleft-right_axle)/(2.0*m_Sleft);

            Float64 left_axle = right_axle + m_axleWidth;
            if (left_axle < m_Sleft)
            {
               // right axle applies force
               lane_loc.LeftAxleLocation   = -(m_Sleft-left_axle); // on left side axle locations are negative
               lane_loc.LeftAxleLeverForce = (m_Sleft-left_axle)/(2.0*m_Sleft);
            }

            rLaneSet.insert(lane_loc);
         }
         else
         {
            break;
         }
//      }
//      else
//      {
//         // lane won't fit
//         break;
//      }

      right_lane_edge += m_wLane;
   }
}

Float64 InteriorLeverRuleAxlePlacer::ComputeMaxFactor(IndexType nL, bool applyMpf, ControllingStrategy* pControl)
{
   Compute();

   Float64 gmax = 0;
   *pControl = LeftAxleLeftShy;

   // Check each of our four cases for our max
   // 1) Left-Left
   Uint32   nl_used = 0;
   Float64 gsum = 0.0;
   for (LaneSet::iterator it=m_LeftAxleLeftShy.begin(); it!=m_LeftAxleLeftShy.end(); it++)
   {
      const LaneLocation& lloc = *it;
      gsum += lloc.LeftAxleLeverForce + lloc.RightAxleLeverForce;

      nl_used++;
      if (nL <= nl_used)
      {
         break;
      }
   }

   gsum *= (applyMpf ? Utility::GetMultiplePresenceFactor(nl_used) : 1.0);
   if (gmax < gsum)
   {
      gmax = gsum;
      *pControl = LeftAxleLeftShy;
   }

   // 2) Left-Right
   nl_used = 0;
   gsum = 0.0;
   for (LaneSet::iterator it=m_LeftAxleRightShy.begin(); it!=m_LeftAxleRightShy.end(); it++)
   {
      const LaneLocation& lloc = *it;
      gsum += lloc.LeftAxleLeverForce + lloc.RightAxleLeverForce;

      nl_used++;
      if (nL <= nl_used)
      {
         break;
      }
   }

   gsum *= (applyMpf ? Utility::GetMultiplePresenceFactor(nl_used) : 1.0);
   if (gmax < gsum)
   {
      gmax = gsum;
      *pControl = LeftAxleRightShy;
   }

   // 3) Right-Left
   nl_used = 0;
   gsum = 0.0;
   for (LaneSet::iterator it=m_RightAxleLeftShy.begin(); it!=m_RightAxleLeftShy.end(); it++)
   {
      const LaneLocation& lloc = *it;
      gsum += lloc.LeftAxleLeverForce + lloc.RightAxleLeverForce;

      nl_used++;
      if (nL <= nl_used)
      {
         break;
      }
   }

   gsum *= (applyMpf ? Utility::GetMultiplePresenceFactor(nl_used) : 1.0);
   if (gmax < gsum)
   {
      gmax = gsum;
      *pControl = RightAxleLeftShy;
   }

   // 4) Right-Right
   nl_used = 0;
   gsum = 0.0;
   for (LaneSet::iterator it=m_RightAxleRightShy.begin(); it!=m_RightAxleRightShy.end(); it++)
   {
      const LaneLocation& lloc = *it;
      gsum += lloc.LeftAxleLeverForce + lloc.RightAxleLeverForce;

      nl_used++;
      if (nL <= nl_used)
      {
         break;
      }
   }

   gsum *= (applyMpf ? Utility::GetMultiplePresenceFactor(nl_used) : 1.0);
   if (gmax < gsum)
   {
      gmax = gsum;
      *pControl = RightAxleRightShy;
   }

   return gmax;
}

ILiveLoadDistributionFactor::LeverRuleMethod InteriorLeverRuleAxlePlacer::ComputeLeverRuleDistribution(IndexType nL, bool applyMpf, ControllingStrategy strategy)
{
   Compute();

   ILiveLoadDistributionFactor::LeverRuleMethod lrd;

   // get controlling location strategy
   LaneSet* pLaneSet = 0;
   switch (strategy)
   {
      case LeftAxleLeftShy:
         pLaneSet = &m_LeftAxleLeftShy;
         break;
      case LeftAxleRightShy:
         pLaneSet = &m_LeftAxleRightShy;
         break;
      case RightAxleLeftShy:
         pLaneSet = &m_RightAxleLeftShy;
         break;
      case RightAxleRightShy:
         pLaneSet = &m_RightAxleRightShy;
         break;
      default:
         assert(0);
   }

   // compute raw factor and store axle locations
   Uint32   nl_used = 0;
   Float64 gsum = 0.0;
   for (LaneSet::iterator it=pLaneSet->begin(); it!=pLaneSet->end(); it++)
   {
      const LaneLocation& lloc = *it;

      if (lloc.LeftAxleLeverForce > 0.0)
      {
         gsum += lloc.LeftAxleLeverForce;
         lrd.AxleLocations.push_back(lloc.LeftAxleLocation);
      }

      if (lloc.RightAxleLeverForce > 0.0)
      {
         gsum += lloc.RightAxleLeverForce;
         lrd.AxleLocations.push_back(lloc.RightAxleLocation);
      }

      nl_used++;
      if (nL <= nl_used)
      {
         break;
      }
   }

   // can only partially fill lrd
   lrd.m = (applyMpf ? Utility::GetMultiplePresenceFactor(nl_used) : 1.0);
   lrd.mg = gsum * lrd.m;
   lrd.nLanesUsed = nl_used;
   lrd.bWasUsed = true;

   return lrd;
}

//////////////////////////

LiveLoadDistributionFactorBase::LiveLoadDistributionFactorBase(GirderIndexType gdr,Float64 Savg,const std::vector<Float64>& gdrSpacings,
                                      Float64 leftOverhang,Float64 rightOverhang,
                                      IndexType Nl, Float64 wLane,
                                      bool bSkewMoment,bool bSkewShear):
 m_GdrNum(gdr),
 m_Spacings(gdrSpacings),
 m_Savg(Savg),  
 m_LeftCurbOverhang(leftOverhang),
 m_RightCurbOverhang(rightOverhang),
 m_Nl(Nl),
 m_wLane(wLane),
 m_bSkewMoment(bSkewMoment),
 m_bSkewShear(bSkewShear)
{
    // Cache nb
    m_Nb = gdrSpacings.size()+1;

    // Compute which side our girder is on. Center leans to Left
    m_Side = (gdr <= m_Nb/2) ? DfSide::LeftSide : DfSide::RightSide;
}

Float64 LiveLoadDistributionFactorBase::MomentDF(Location loc,NumLoadedLanes numLanes,LimitState ls) const
{
   ILiveLoadDistributionFactor::DFResult g;
   g = MomentDFEx(loc, numLanes, ls);
   return g.mg;
}

Float64 LiveLoadDistributionFactorBase::ShearDF(Location loc,NumLoadedLanes numLanes,LimitState ls) const
{
   ILiveLoadDistributionFactor::DFResult g;
   g = ShearDFEx(loc, numLanes, ls);
   return g.mg;
}

Float64 LiveLoadDistributionFactorBase::ReactionDF(Location loc,NumLoadedLanes numLanes,LimitState ls) const
{
   ILiveLoadDistributionFactor::DFResult g;
   g = ReactionDFEx(loc, numLanes, ls);
   return g.mg;
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::MomentDFEx(Location loc,NumLoadedLanes numLanes,LimitState ls) const
{
   TestRangeOfApplicability(loc);

   ILiveLoadDistributionFactor::DFResult g;

   switch(loc)
   {
   case Location::IntGirder:
           switch(numLanes)
              {
              case NumLoadedLanes::One:
                   switch(ls)
                      {
                      case LimitState::StrengthI:
                      case LimitState::StrengthII:
                      case LimitState::StrengthIII:
                      case LimitState::StrengthIV:
                      case LimitState::StrengthV:
                      case LimitState::ExtremeEventI:
                      case LimitState::ExtremeEventII_IC:
                      case LimitState::ExtremeEventII_CV:
                      case LimitState::ExtremeEventII_CT:
                      case LimitState::ServiceI:
                      case LimitState::ServiceIA:
                      case LimitState::ServiceII:
                      case LimitState::ServiceIII:
                           g = GetMomentDF_Int_1_Strength();
                           break;

                     case LimitState::FatigueI:
                     case LimitState::FatigueII:
                           g = GetMomentDF_Int_Fatigue();
                           break;
                      }
                   break;

              case NumLoadedLanes::TwoOrMore:
                   switch(ls)
                      {
                      case LimitState::StrengthI:
                      case LimitState::StrengthII:
                      case LimitState::StrengthIII:
                      case LimitState::StrengthIV:
                      case LimitState::StrengthV:
                      case LimitState::ExtremeEventI:
                      case LimitState::ExtremeEventII_IC:
                      case LimitState::ExtremeEventII_CV:
                      case LimitState::ExtremeEventII_CT:
                      case LimitState::ServiceI:
                      case LimitState::ServiceIA:
                      case LimitState::ServiceII:
                      case LimitState::ServiceIII:
                           g = GetMomentDF_Int_2_Strength();
                           break;

                     case LimitState::FatigueI:
                     case LimitState::FatigueII:
                           // throw an exception
                           break;
                      }
                   break;
              }
           break;

      case Location::ExtGirder:
           switch(numLanes)
              {
              case NumLoadedLanes::One:
                   switch(ls)
                      {
                      case LimitState::StrengthI:
                      case LimitState::StrengthII:
                      case LimitState::StrengthIII:
                      case LimitState::StrengthIV:
                      case LimitState::StrengthV:
                      case LimitState::ExtremeEventI:
                      case LimitState::ExtremeEventII_IC:
                      case LimitState::ExtremeEventII_CV:
                      case LimitState::ExtremeEventII_CT:
                      case LimitState::ServiceI:
                      case LimitState::ServiceIA:
                      case LimitState::ServiceII:
                      case LimitState::ServiceIII:
                           g = GetMomentDF_Ext_1_Strength();
                           break;

                     case LimitState::FatigueI:
                     case LimitState::FatigueII:
                           g = GetMomentDF_Ext_Fatigue();
                           break;
                      }
                   break;

              case NumLoadedLanes::TwoOrMore:
                   switch(ls)
                      {
                      case LimitState::StrengthI:
                      case LimitState::StrengthII:
                      case LimitState::StrengthIII:
                      case LimitState::StrengthIV:
                      case LimitState::StrengthV:
                      case LimitState::ExtremeEventI:
                      case LimitState::ExtremeEventII_IC:
                      case LimitState::ExtremeEventII_CV:
                      case LimitState::ExtremeEventII_CT:
                      case LimitState::ServiceI:
                      case LimitState::ServiceIA:
                      case LimitState::ServiceII:
                      case LimitState::ServiceIII:
                           g = GetMomentDF_Ext_2_Strength();
                           break;

                     case LimitState::FatigueI:
                     case LimitState::FatigueII:
                           // throw an exception
                           break;
                      }
                   break;
              }
           break;
      }

   return g;
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::ShearDFEx(Location loc,NumLoadedLanes numLanes,LimitState ls) const
{
   TestRangeOfApplicability(loc);

   ILiveLoadDistributionFactor::DFResult g;

   switch(loc)
      {
      case Location::IntGirder:
           switch(numLanes)
              {
              case NumLoadedLanes::One:
                   switch(ls)
                      {
                      case LimitState::StrengthI:
                      case LimitState::StrengthII:
                      case LimitState::StrengthIII:
                      case LimitState::StrengthIV:
                      case LimitState::StrengthV:
                      case LimitState::ExtremeEventI:
                      case LimitState::ExtremeEventII_IC:
                      case LimitState::ExtremeEventII_CV:
                      case LimitState::ExtremeEventII_CT:
                      case LimitState::ServiceI:
                      case LimitState::ServiceIA:
                      case LimitState::ServiceII:
                      case LimitState::ServiceIII:
                           g = GetShearDF_Int_1_Strength();
                           break;

                     case LimitState::FatigueI:
                     case LimitState::FatigueII:
                           g = GetShearDF_Int_Fatigue();
                           break;
                      }
                   break;

              case NumLoadedLanes::TwoOrMore:
                   switch(ls)
                      {
                      case LimitState::StrengthI:
                      case LimitState::StrengthII:
                      case LimitState::StrengthIII:
                      case LimitState::StrengthIV:
                      case LimitState::StrengthV:
                      case LimitState::ExtremeEventI:
                      case LimitState::ExtremeEventII_IC:
                      case LimitState::ExtremeEventII_CV:
                      case LimitState::ExtremeEventII_CT:
                      case LimitState::ServiceI:
                      case LimitState::ServiceIA:
                      case LimitState::ServiceII:
                      case LimitState::ServiceIII:
                           g = GetShearDF_Int_2_Strength();
                           break;

                     case LimitState::FatigueI:
                     case LimitState::FatigueII:
                           // throw an exception
                           break;
                      }
                   break;
              }
           break;

      case Location::ExtGirder:
           switch(numLanes)
              {
              case NumLoadedLanes::One:
                   switch(ls)
                      {
                      case LimitState::StrengthI:
                      case LimitState::StrengthII:
                      case LimitState::StrengthIII:
                      case LimitState::StrengthIV:
                      case LimitState::StrengthV:
                      case LimitState::ExtremeEventI:
                      case LimitState::ExtremeEventII_IC:
                      case LimitState::ExtremeEventII_CV:
                      case LimitState::ExtremeEventII_CT:
                      case LimitState::ServiceI:
                      case LimitState::ServiceIA:
                      case LimitState::ServiceII:
                      case LimitState::ServiceIII:
                           g = GetShearDF_Ext_1_Strength();
                           break;

                     case LimitState::FatigueI:
                     case LimitState::FatigueII:
                           g = GetShearDF_Ext_Fatigue();
                           break;
                      }
                   break;

              case NumLoadedLanes::TwoOrMore:
                   switch(ls)
                      {
                      case LimitState::StrengthI:
                      case LimitState::StrengthII:
                      case LimitState::StrengthIII:
                      case LimitState::StrengthIV:
                      case LimitState::StrengthV:
                      case LimitState::ExtremeEventI:
                      case LimitState::ExtremeEventII_IC:
                      case LimitState::ExtremeEventII_CV:
                      case LimitState::ExtremeEventII_CT:
                      case LimitState::ServiceI:
                      case LimitState::ServiceIA:
                      case LimitState::ServiceII:
                      case LimitState::ServiceIII:
                           g = GetShearDF_Ext_2_Strength();
                           break;

                     case LimitState::FatigueI:
                     case LimitState::FatigueII:
                           // throw an exception
                           break;
                      }
                   break;
              }
           break;
      }

   return g;
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::ReactionDFEx(Location loc,NumLoadedLanes numLanes,LimitState ls) const
{
   TestRangeOfApplicability(loc);

   ILiveLoadDistributionFactor::DFResult g;

   switch(loc)
      {
      case Location::IntGirder:
           switch(numLanes)
              {
              case NumLoadedLanes::One:
                   switch(ls)
                      {
                      case LimitState::StrengthI:
                      case LimitState::StrengthII:
                      case LimitState::StrengthIII:
                      case LimitState::StrengthIV:
                      case LimitState::StrengthV:
                      case LimitState::ExtremeEventI:
                      case LimitState::ExtremeEventII_IC:
                      case LimitState::ExtremeEventII_CV:
                      case LimitState::ExtremeEventII_CT:
                      case LimitState::ServiceI:
                      case LimitState::ServiceIA:
                      case LimitState::ServiceII:
                      case LimitState::ServiceIII:
                           g = GetReactionDF_Int_1_Strength();
                           break;

                     case LimitState::FatigueI:
                     case LimitState::FatigueII:
                           g = GetReactionDF_Int_Fatigue();
                           break;
                      }
                   break;

              case NumLoadedLanes::TwoOrMore:
                   switch(ls)
                      {
                      case LimitState::StrengthI:
                      case LimitState::StrengthII:
                      case LimitState::StrengthIII:
                      case LimitState::StrengthIV:
                      case LimitState::StrengthV:
                      case LimitState::ExtremeEventI:
                      case LimitState::ExtremeEventII_IC:
                      case LimitState::ExtremeEventII_CV:
                      case LimitState::ExtremeEventII_CT:
                      case LimitState::ServiceI:
                      case LimitState::ServiceIA:
                      case LimitState::ServiceII:
                      case LimitState::ServiceIII:
                           g = GetReactionDF_Int_2_Strength();
                           break;

                     case LimitState::FatigueI:
                     case LimitState::FatigueII:
                           // throw an exception
                           break;
                      }
                   break;
              }
           break;

      case Location::ExtGirder:
           switch(numLanes)
              {
              case NumLoadedLanes::One:
                   switch(ls)
                      {
                      case LimitState::StrengthI:
                      case LimitState::StrengthII:
                      case LimitState::StrengthIII:
                      case LimitState::StrengthIV:
                      case LimitState::StrengthV:
                      case LimitState::ExtremeEventI:
                      case LimitState::ExtremeEventII_IC:
                      case LimitState::ExtremeEventII_CV:
                      case LimitState::ExtremeEventII_CT:
                      case LimitState::ServiceI:
                      case LimitState::ServiceIA:
                      case LimitState::ServiceII:
                      case LimitState::ServiceIII:
                           g = GetReactionDF_Ext_1_Strength();
                           break;

                     case LimitState::FatigueI:
                     case LimitState::FatigueII:
                           g = GetReactionDF_Ext_Fatigue();
                           break;
                      }
                   break;

              case NumLoadedLanes::TwoOrMore:
                   switch(ls)
                      {
                      case LimitState::StrengthI:
                      case LimitState::StrengthII:
                      case LimitState::StrengthIII:
                      case LimitState::StrengthIV:
                      case LimitState::StrengthV:
                      case LimitState::ExtremeEventI:
                      case LimitState::ExtremeEventII_IC:
                      case LimitState::ExtremeEventII_CV:
                      case LimitState::ExtremeEventII_CT:
                      case LimitState::ServiceI:
                      case LimitState::ServiceIA:
                      case LimitState::ServiceII:
                      case LimitState::ServiceIII:
                           g = GetReactionDF_Ext_2_Strength();
                           break;

                     case LimitState::FatigueI:
                     case LimitState::FatigueII:
                           // throw an exception
                           break;
                      }
                   break;
              }
           break;
      }

   return g;
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::GetReactionDF_Int_1_Strength() const
{
   return GetShearDF_Int_1_Strength();
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::GetReactionDF_Int_2_Strength() const
{
   return GetShearDF_Int_2_Strength();
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::GetReactionDF_Int_Fatigue() const
{
   return GetShearDF_Int_Fatigue();
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::GetReactionDF_Ext_1_Strength() const
{
   return GetShearDF_Ext_1_Strength();
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::GetReactionDF_Ext_2_Strength() const
{
   return GetShearDF_Ext_2_Strength();
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::GetReactionDF_Ext_Fatigue() const
{
   return GetShearDF_Ext_Fatigue();
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::GetMomentDF_Int_Fatigue() const
{

 ILiveLoadDistributionFactor::DFResult g = GetMomentDF_Int_1_Strength();
 
 // negate multiple presence factor;
 NegateMpf( g );

 return g;
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::GetMomentDF_Ext_Fatigue() const
{

 ILiveLoadDistributionFactor::DFResult g = GetMomentDF_Ext_1_Strength();
 
 // negate multiple presence factor;
 NegateMpf( g );

 return g;
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::GetShearDF_Int_Fatigue() const
{

 ILiveLoadDistributionFactor::DFResult g = GetShearDF_Int_1_Strength();
 
 // negate multiple presence factor;
 NegateMpf( g );

 return g;
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::GetShearDF_Ext_Fatigue() const
{

 ILiveLoadDistributionFactor::DFResult g = GetShearDF_Ext_1_Strength();
 
 // negate multiple presence factor;
 NegateMpf( g );

 return g;
}




ILiveLoadDistributionFactor::LeverRuleMethod LiveLoadDistributionFactorBase::DistributeByLeverRuleEx(Location loc,NumLoadedLanes numLanes, bool applyMpf) const
{
   GirderIndexType nl = (numLanes==NumLoadedLanes::TwoOrMore) ? m_Nl : 1;

   // Pick adjacent girder if needed
   GirderIndexType gdr = m_GdrNum;

   GirderIndexType nb1 = GetNb()-1; // id of right-most girder
   if (0 < nb1)
   {
      if (loc==Location::IntGirder)
      {
         if (m_GdrNum==0 || m_GdrNum==nb1)
         {
            // Looking for interior factor, and current girder is exterior; get adjacent on correct side
            gdr = m_Side == DfSide::LeftSide ? 1 : nb1-1;
         }
      }
      else
      {
         if (0 < m_GdrNum || m_GdrNum!=nb1)
         {
            // Looking for exterior factor, and current girder is interior; get adjacent on correct side
            gdr = m_Side == DfSide::LeftSide ? 0 : nb1;
         }
      }
   }

   ILiveLoadDistributionFactor::LeverRuleMethod g;
   g = DistributeByLeverRule(gdr, m_Spacings, m_LeftCurbOverhang, m_RightCurbOverhang, m_wLane, nl, applyMpf);

   return g;
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::DistributeMomentByLeverRule(Location loc,NumLoadedLanes numLanes, bool applyMpf) const
{
   ILiveLoadDistributionFactor::DFResult g;
   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(loc, numLanes, applyMpf);
   g.mg = g.LeverRuleData.mg;

   Float64 skew = MomentSkewCorrectionFactor();
   if ( m_bSkewMoment )
   {
      g.ControllingMethod |= MOMENT_SKEW_CORRECTION_APPLIED;
   }

   g.SkewCorrectionFactor = skew;
   g.mg *= skew;

   return g;
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::DistributeShearByLeverRule(Location loc,NumLoadedLanes numLanes, bool applyMpf) const
{
   ILiveLoadDistributionFactor::DFResult g;
   g.ControllingMethod = LEVER_RULE;
   g.LeverRuleData = DistributeByLeverRuleEx(loc, numLanes, applyMpf);
   g.mg = g.LeverRuleData.mg;

   Float64 skew = ShearSkewCorrectionFactor();
   if ( m_bSkewShear )
   {
      g.ControllingMethod |= SHEAR_SKEW_CORRECTION_APPLIED;
   }

   g.SkewCorrectionFactor = skew;
   g.mg *= skew;

   return g;
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorBase::DistributeReactionByLeverRule(Location loc,NumLoadedLanes numLanes, bool applyMpf) const
{
   return DistributeShearByLeverRule(loc, numLanes, applyMpf);
}

void LiveLoadDistributionFactorBase::SetRangeOfApplicabilityAction(RangeOfApplicabilityAction action)
{
   m_RangeOfApplicabilityAction = action;
}

RangeOfApplicabilityAction LiveLoadDistributionFactorBase::GetRangeOfApplicabilityAction() const
{
   return m_RangeOfApplicabilityAction;
}

//////////////////////////

void LiveLoadDistributionFactorMixin::IgnoreMpfLeverRule(bool doIgnore)
{
   m_IgnoreMpfForLeverRuleSingleLane = doIgnore;
}

bool LiveLoadDistributionFactorMixin::IgnoreMpfLeverRule() const
{
   return m_IgnoreMpfForLeverRuleSingleLane;
}

ILiveLoadDistributionFactor::LeverRuleMethod LiveLoadDistributionFactorMixin::DistributeByLeverRule(GirderIndexType beamNum,const std::vector<Float64>& Spacings, Float64 leftOverhang, Float64 rightOverhang,
                                                                                                            Float64 wLane,IndexType Nl, bool applyMpf) const
{
   // control loop
   IndexType firstL = 1; // assume single lane
   IndexType topL = 2;
   if (1 < Nl)
   {
      firstL = 2;
      topL = Nl+1;
   }

   ILiveLoadDistributionFactor::LeverRuleMethod lrd;

   GirderIndexType nb = Spacings.size()+1;
   bool bExteriorBeam = beamNum==0 || beamNum==nb-1;

   if (nb==1)
   {
      // Single girder structure, use lanes/beams method 
      if (applyMpf)
      {
         // Lanes beams method will max when Nl * MPF is maximized. 
         IndexType   nl_at_max = 0;
         Float64 mfmpf_max = 0.0;
         for (IndexType i = firstL; i < topL; i++)
         {
            Float64 nfmpf = Nl * Utility::GetMultiplePresenceFactor(i);
            if (mfmpf_max < nfmpf)
            {
               mfmpf_max = nfmpf;
               nl_at_max = i;
            }
         }

         lrd.mg = mfmpf_max;
         lrd.nLanesUsed = nl_at_max;
         lrd.m = Utility::GetMultiplePresenceFactor(nl_at_max);
      }
      else
      {
         lrd.mg = (Float64)Nl;
         lrd.nLanesUsed = Nl;
         lrd.m = 1.0;
      }

      lrd.Sleft = 0.0;
      lrd.Sright = 0.0;
      lrd.Nb = 1;
      lrd.bWasUsed = true;
   }
   else if (bExteriorBeam)
   {
      // Our computation function treats all exterior girders as if they are left side. 
      // Organize data such
      Float64 S;
      Float64 curbOverhang;
      if (beamNum==0)
      {
         S = Spacings.front();
         curbOverhang = leftOverhang;
      }
      else
      {
         S = Spacings.back();
         curbOverhang = rightOverhang;
      }

      // Get max for all lane combinations
      for ( IndexType i = firstL; i < topL; i++ )
      {
         ILiveLoadDistributionFactor::LeverRuleMethod currLRD = DistributeByLeverRulePerLaneExterior(nb, S, curbOverhang, wLane, i, applyMpf);
         if ( lrd.mg < currLRD.mg )
         {
            lrd = currLRD;
         }
      }
   }
   else
   {
      // This is an interior beam for a multi beam structure. Use our utility class to compute
      Float64 left_spacing  = Spacings[beamNum-1];
      Float64 right_spacing = Spacings[beamNum];

      // distances from our beam to curb
      Float64 left_curb = leftOverhang;
      for (GirderIndexType is = 0; is<beamNum; is++)
      {
         left_curb += Spacings[is];
      }

      Float64 right_curb = rightOverhang;
      for (GirderIndexType is=beamNum; is<nb-1; is++)
      {
         right_curb += Spacings[is];
      }

      Float64 wheelLineSpacing = GetWheelLineSpacing(); // wheel line spacing
      Float64 shyDist = GetShyDistance(); // Closest distance that wheel can get to lane

      InteriorLeverRuleAxlePlacer strategy(left_spacing, right_spacing, left_curb, right_curb,
                                                      shyDist, wheelLineSpacing, wLane);

      // Save number of lanes that gives max df
      Float64 df_max = 0.0;
      IndexType   idx_max = 0;
      InteriorLeverRuleAxlePlacer::ControllingStrategy strat_max = InteriorLeverRuleAxlePlacer::LeftAxleLeftShy;
      for ( IndexType i = firstL; i < topL; i++ )
      {
         InteriorLeverRuleAxlePlacer::ControllingStrategy strat;
         Float64 df = strategy.ComputeMaxFactor(i,applyMpf,&strat);
         if ( df_max < df )
         {
            df_max = df;
            idx_max = i;
            strat_max = strat;
         }
      }

      // now get max factor, mpf, lanes used, and axle information
      lrd = strategy.ComputeLeverRuleDistribution(idx_max, applyMpf, strat_max);

      // fill rest of lr data
      lrd.bWasUsed = true;
      lrd.bWasExterior = false;
      lrd.de = 0.0; // doesn't matter since we're interior
      lrd.Nb = nb;
      lrd.Sleft  = left_spacing;
      lrd.Sright = right_spacing;
   }

   return lrd; 
}


ILiveLoadDistributionFactor::LeverRuleMethod LiveLoadDistributionFactorMixin::DistributeByLeverRulePerLaneExterior(GirderIndexType Nb, Float64 S, Float64 curbOverhang,Float64 wLane,IndexType Nl, bool applyMpf) const
{
   ILiveLoadDistributionFactor::LeverRuleMethod lrData;     // distribution factor
   lrData.bWasUsed = true;
   lrData.bWasExterior = true;
   lrData.Nb = Nb;
   lrData.Sleft = S;
   lrData.Sright = S;
   lrData.de = curbOverhang;

   Float64 wheelLineSpacing = GetWheelLineSpacing(); // wheel line spacing
   Float64 shyDist = GetShyDistance(); // Closest distance that wheel can get to lane

   Float64 leverLength = S + curbOverhang;

   // To maximize the reaction at the first interior girder, position the lanes
   // as far to the left as possible and axles within lanes to left as far as possible
   Float64 cummd = 0;  // cumulative distance from first interior
                     // girder to axle under consideration
   IndexType nLanesUsed = 0;

   for (IndexType ilane = 0; ilane < Nl; ilane++)
   {
      Float64 lft_ll = ilane*wLane; // left most location of current lane measured from curb

      Float64 lft_axl = lft_ll + shyDist;          // leftmost possible axle location left edge of lane
      Float64 lft_axl_lvr = leverLength - lft_axl; // lever length of left axle

      // See if axles fit to left of interior beam
      // first left;
      if ( 0 < lft_axl_lvr )
      {
         cummd += lft_axl_lvr;
         lrData.AxleLocations.push_back(lft_axl_lvr);
         nLanesUsed ++; // only add for left axle

         // now right axle
         Float64 rgt_axl_lvr = lft_axl_lvr - wheelLineSpacing;

         if ( 0 < rgt_axl_lvr )
         {
            cummd += rgt_axl_lvr;
            lrData.AxleLocations.push_back(rgt_axl_lvr);
         }
         else
         {
            break; // axles don't get any closer
         }
      }
      else
      {
         break; // axles don't get any closer
      }
   }

   lrData.nLanesUsed = nLanesUsed;

   // TxDOT/WSDOT rule for exterior I and U beams when a single truck controls
   if (!applyMpf || (m_IgnoreMpfForLeverRuleSingleLane && nLanesUsed==1))
   {
      lrData.m = 1.0;
   }
   else
   {
      lrData.m = Utility::GetMultiplePresenceFactor(nLanesUsed);
   }

   lrData.mg = lrData.m * cummd/(2*S); // per lanes (includes multiple presence factor)

   return lrData;
}


ILiveLoadDistributionFactor::RigidMethod LiveLoadDistributionFactorMixin::DistributeByRigidMethod(
      ILiveLoadDistributionFactor::DfSide side,const std::vector<Float64>& rSpacings, 
      Float64 leftOverhang, Float64 rightOverhang,Float64 wLane,IndexType firstLoadedLane,IndexType lastLoadedLane, bool applyMpf) const
{
   // See Section 4.6.2.2.2d
   ILiveLoadDistributionFactor::RigidMethod rmData;
   rmData.bWasUsed = true;

   Float64 Xext;  // horizontal distance from the center of gravity of the
                  // pattern of girders to the exterior girder (mm)
   Float64 x;     // horizontal distance from the center of gravity of the
                  // pattern of girders to each girder (mm)
   Float64 e;     // eccentricity of a lane from the center of gravity of the
                  // pattern of girders (mm)
   Float64 cg;    // location of center of gravity of the pattern of girders from
                  // the left curb line
   Float64 sumx2; // Summation of x^2
   Float64 sume;  // Summation of e;

   GirderIndexType nb = rSpacings.size()+1;

   // Set up problem so it works from left to right
   Float64 overhang;
   std::vector<Float64> lr_spacings(rSpacings.size());

   if (side==ILiveLoadDistributionFactor::DfSide::LeftSide)
   {
      overhang = leftOverhang;
      std::copy(rSpacings.begin(),rSpacings.end(),lr_spacings.begin());
   }
   else
   {
      overhang = rightOverhang;
      std::copy_backward(rSpacings.begin(),rSpacings.end(),lr_spacings.end());
   }


   // compute cg wrt curb
   Float64 loc = overhang;
   cg = loc;

   for (std::vector<Float64>::iterator its=lr_spacings.begin(); its!=lr_spacings.end(); its++)
   {
      loc += *its;

      cg += loc;
   }

   cg = cg/nb;

   // Second moment of each beam
   x = overhang - cg;  // first exterior girder
   rmData.x.push_back(x);
   sumx2 = pow(x,2);
   for (std::vector<Float64>::iterator its=lr_spacings.begin(); its!=lr_spacings.end(); its++)
   {
      x += *its;
      sumx2 += pow(x,2);

      rmData.x.push_back(x);
   }

   Xext = cg - overhang;
   rmData.Xext = Xext;

   // Determine which number of lanes will control
   IndexType ln_ctrl  = 0;
   Float64 sume_max = -Float64_Max;
   for (IndexType cur_nl=firstLoadedLane; cur_nl<=lastLoadedLane; cur_nl++)
   {
      sume = 0;
      for (IndexType i = 0; i < cur_nl; i++)
      {
         e = cg - GetShyDistance() - 0.5*GetWheelLineSpacing() - i*wLane;
         sume += e;
      }

      sume *= (applyMpf ? Utility::GetMultiplePresenceFactor(cur_nl) : 1.0);

      if (sume_max < sume )
      {
         sume_max = sume;
         ln_ctrl = cur_nl;
      }
   }

   // Now compute df data for maximal lane configuration
   sume = 0;
   for (IndexType i = 0; i < ln_ctrl; i++)
   {
      e = cg - GetShyDistance() - 0.5*GetWheelLineSpacing() - i*wLane;
      sume += e;

      rmData.e.push_back(e);
   }

   rmData.m = (applyMpf ? Utility::GetMultiplePresenceFactor(ln_ctrl) : 1.0);
   rmData.mg = rmData.m * (((Float64)ln_ctrl)/((Float64)nb) + Xext*sume/sumx2);
   rmData.Nb = (Float64)nb;
   rmData.Nl = (Float64)ln_ctrl;

   return rmData;
}


Float64 LiveLoadDistributionFactorMixin::GetShyDistance() const
{
   // LRFD 3.6.1.3.1
   Float64 shy;

   if ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI )
   {
      shy = WBFL::Units::ConvertToSysUnits(600.0, WBFL::Units::Measure::Millimeter);
   }
   else
   {
      shy = WBFL::Units::ConvertToSysUnits(2.0, WBFL::Units::Measure::Feet);
   }

   return shy;
}

Float64 LiveLoadDistributionFactorMixin::GetWheelLineSpacing() const
{
   // LRFD Figure 3.6.1.2.2-1
   Float64 space;
   if ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI )
   {
      space = WBFL::Units::ConvertToSysUnits(1800.0, WBFL::Units::Measure::Millimeter);
   }
   else
   {
      space = WBFL::Units::ConvertToSysUnits(6.0, WBFL::Units::Measure::Feet);
   }

   return space;
}

Float64 LiveLoadDistributionFactorMixin::GetTruckWidth() const
{
   // LRFD 3.6.1.2.1
   Float64 width;
   if ( LRFDVersionMgr::GetUnits() == LRFDVersionMgr::Units::SI )
   {
      width = WBFL::Units::ConvertToSysUnits(3000.0, WBFL::Units::Measure::Millimeter);
   }
   else
   {
      width = WBFL::Units::ConvertToSysUnits(10.0, WBFL::Units::Measure::Feet);
   }

   return width;
}

Float64 LiveLoadDistributionFactorMixin::GetDistanceToAxle(Float64 S,Float64 overhang,Float64 wLane,GirderIndexType nbeam,AxleIndexType nWheelLine,bool bAlignLeft) const
{
   // nbeam and naxle are zero-based beam and axle indices, respectively,
   // counted from the left side of the cross-section, looking ahead on
   // station.
   Float64 wheelLineSpacing; // wheel line spacing
   Float64 d; // distance from nbeam to naxle
   Float64 truckWidth;

   wheelLineSpacing = GetWheelLineSpacing();
   truckWidth = GetTruckWidth();

   Float64 LCl; // Left hand side lane clearance for a truck left aligned in a design lane
   Float64 LCr; // Left hand side lane clearance for a truck right aligned in a design lane

   LCl = (truckWidth - wheelLineSpacing)/2;
   LCr = wLane - truckWidth/2 - wheelLineSpacing/2;

   AxleIndexType wp; // Wheel line position (0 if left wheel line, 1 if right wheel line)
   wp = nWheelLine % 2;

   Uint32 lp; // Lane position (2 wheel lines per lane)
   lp = Uint32(nWheelLine/2);

   if ( bAlignLeft )
   {
      d = nbeam*S + overhang - lp*wLane - LCl - wp*wheelLineSpacing;
   }
   else
   {
      Uint32 lo; // Lane offset: Offset position from nbeam
      lo = Uint32(lp/2);
      if ( lp % 2 == 0 )
      {
         // Even lane positions
         d = wLane - LCl + lo*wLane - LCr - (!wp)*wheelLineSpacing;
      }
      else
      {
         // Odd lane positions
         d = LCl + lo*wLane + wp*wheelLineSpacing + LCl;
      }
   }

   return d;
}

ILiveLoadDistributionFactor::DFResult LiveLoadDistributionFactorMixin::GetLanesBeamsMethod(IndexType Nl,GirderIndexType Nb, bool applyMpf) const
{
   ILiveLoadDistributionFactor::DFResult g;

   g.ControllingMethod = LANES_DIV_BEAMS;
   g.LanesBeamsData.bWasUsed = true;
   g.LanesBeamsData.Nb = Nb;
   g.LanesBeamsData.Nl = Nl;
   g.LanesBeamsData.mg = (Float64)Nl/(Float64)Nb;

   Float64 m = (applyMpf ? Utility::GetMultiplePresenceFactor(Nl) : 1.0);
   g.LanesBeamsData.m = m;

   g.LanesBeamsData.mg *= m;

   g.SkewCorrectionFactor = 1.0;
   g.mg = g.LanesBeamsData.mg;

   return g;
}

