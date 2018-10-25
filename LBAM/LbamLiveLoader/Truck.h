///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef __TRUCK_H_
#define __TRUCK_H_

#include "resource.h"       // main symbols
#include "WBFLLBAMLiveLoader.h"
#include "LBAMLiveLoader.hh"

#include <vector>

// This enum defines whether an axle is used or not for notional truck loads
// Previous version used a std::vector<bool>, but we found that performance was
// dramatically worse.
enum AxleState {AxleOff, AxleOn};

struct FtAxle
{
   FtAxle( Float64 originalSpacing, Float64 weight):
      m_Location(0.0),
      m_OriginalSpacing(originalSpacing),
      m_Weight(weight)
      {;}

   Float64 m_Location; // measured from front axle (becomes rear of backward)
   Float64 m_OriginalSpacing;
   Float64 m_Weight;
};

// FixedTruck 
// First axle in collection is always front axle of IVehicularLoad. remaining axle locations
// will be positive or negative depending if the truck is headed forward or backwards, respectively.
struct FixedTruck
{
   // use an initializer function 
   void Initialize(IVehicularLoad* pVl, bool applyImpact, ILiveLoadConfiguration* config=NULL);

   // Evaluate the primary truck response at a position along an influence line
   // This function attempts to apply all possible axles and returns a list of the axles that were
   // applied (returned non-zero) in the vector<bool>
   void EvaluatePrimary(Float64 position, InfluenceSideType side, Float64 flipFactor, 
                        IInfluenceLine* lftInfluence, IInfluenceLine* rgtInfluence, 
                        std::vector<AxleState>* lftAppliedAxles, std::vector<AxleState>* rgtAppliedAxles,
                        VARIANT_BOOL* isDualValued, Float64* leftValue, Float64* rightValue);

   // evaluate for a single influence line - left and right values are returned in left-side coordinates
   void EvaluatePrimaryInfl(Float64 position, InfluenceSideType side, IInfluenceLine* influence, std::vector<AxleState>* appliedAxles,
                                     VARIANT_BOOL* isDualValued, Float64* leftValue, Float64* rightValue);


   // location of front of truck (positivemost location) in local truck coord's
   Float64 FrontBumper()
   {
      ATLASSERT( !m_Axles.empty()); // forget to initialize?
      return m_Front;
   }

   // location of rear of truck (negativemost location) in local truck coord's
   Float64 RearBumper()
   {
      ATLASSERT( !m_Axles.empty());
      return m_Rear;
   }

   Float64 Length()
   {
      return fabs(m_Front - m_Rear);
   }

   Float64 MinAxleSpacing();
   Float64 MaxAxleSpacing();
   Float64 CenterOfGravity();

   bool NegMomentsAndReactions();

   // returns the heaviest axle, excluding the first and last axle, that is nearest to the center of the truck
   // (center is in terms of # of axles and not geometric positions0
   AxleIndexType HeaviestCentralAxle();

   TruckDirectionType GetTruckDirection();
   AxleIndexType GetPivotAxleIndex();
   void SetTruckDirection(TruckDirectionType direction,AxleIndexType pivotAxleIndex = 0);

   Float64 GetVariableAxleSpacing();
   void SetVariableAxleSpacing(Float64 spacing);

   bool IsVariableAxle();
   AxleIndexType GetVariableAxleIndex();
   Float64 GetMinVariableAxleSpacing();
   Float64 GetMaxVariableAxleSpacing();

   // get number of axles and location wrt first axle
   AxleIndexType GetNumAxles();
   Float64 GetAxleLocation(AxleIndexType idx);
   Float64 GetAxlePosition(AxleIndexType idx,Float64 truckPosition);

#if defined _DEBUG
   void DumpAxles(Float64 position);
#endif

private:
   void ComputeAxleLocations();

   typedef std::vector<FtAxle>     AxleContainer;
   typedef AxleContainer::iterator AxleIterator;

   Float64                m_Front;
   Float64                m_Rear;
   AxleContainer          m_Axles;
   std::vector<AxleState> m_ActiveAxles;

   bool m_bNegMomentsAndReactions;

   AxleIndexType        m_VariableAxleIndex; // spacing after this axle is variable
   Float64              m_VariableAxleSpacing;
   Float64              m_MaxVariableAxleSpacing;
   Float64              m_MinVariableAxleSpacing;
   TruckDirectionType   m_TruckDirection;
   AxleIndexType        m_PivotAxleIndex;
};














#endif