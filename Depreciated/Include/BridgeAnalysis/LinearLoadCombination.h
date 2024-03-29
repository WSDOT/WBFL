///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright � 1999-2022  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_LINEARLOADCOMBINATION_H_
#define INCLUDED_BRIDGEANALYSIS_LINEARLOADCOMBINATION_H_
#pragma once

// SYSTEM INCLUDES
//
#include <map>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\LoadCombination.h>


// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

class BAMCLASS bamLinearLoadCombination : public bamLoadCombination
{
public:
   // LIFECYCLE
   bamLinearLoadCombination(IDType id);
   bamLinearLoadCombination(const bamLinearLoadCombination& rOther);
   virtual ~bamLinearLoadCombination(); 

   // OPERATORS
   // OPERATIONS
   void AddLoading(IDType loadingId,Float64 loadFactor);
   void SetMultiplier(Float64 multiplier);

   virtual bamSectionResults CombineSectionResults( PoiIDType poiId );
   virtual bamSectionStress CombineSectionStress( PoiIDType poiId, CollectionIndexType spIdx );
   virtual bamReaction CombineReactions( SupportIDType supportId );

   // ACCESS
   virtual void GetLoadings(std::vector<IDType>& loadingIds) const;

   // INQUIRY

protected:
   // DATA MEMBERS
   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   bamLoadCombination* Clone() const;

   // ACCESS
   // INQUIRY

private:
   // DATA MEMBERS
   Float64 m_Multiplier;

#pragma warning( disable : 4251 )
   typedef std::map<IDType, Float64> LoadEntryContainer;
   typedef LoadEntryContainer::iterator LoadEntryIterator;
   typedef LoadEntryContainer::const_iterator ConstLoadEntryIterator;
   typedef std::pair<IDType,Float64> LoadEntry;
   LoadEntryContainer m_LoadEntries;

   // LIFECYCLE
   // OPERATORS
   bamLinearLoadCombination& operator = (const bamLinearLoadCombination& /*rLinearLoadCombination*/);  // Remove to enable assignment

   // OPERATIONS
   // ACCESS
   // INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_LINEARLOADCOMBINATION_H_
