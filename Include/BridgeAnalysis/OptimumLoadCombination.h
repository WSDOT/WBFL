///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2011  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_OPTIMUMLOADCOMBINATION_H_
#define INCLUDED_BRIDGEANALYSIS_OPTIMUMLOADCOMBINATION_H_
#pragma once

// SYSTEM INCLUDES
//
#include <map>

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\LoadCombination.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bamOptimumLoadCombination

   Performs a optimal load combination on one of the degrees of freedom.


DESCRIPTION
   Performs a optimal load combination on one of the degrees of freedom.


   EXAMPLE
      Place examples here.
   END

BUGS
   There are currently no known problems with this class.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 08.14.1997 : Created file
*****************************************************************************/

class BAMCLASS bamOptimumLoadCombination : public bamLoadCombination
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bamOptimumLoadCombination(Int32 id, 
                             bamOptimumType type = otMaximum,
                             bamOptimumVariable variable = ovMz );

   //------------------------------------------------------------------------
   bamOptimumLoadCombination(const bamOptimumLoadCombination& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bamOptimumLoadCombination();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual bamSectionResults CombineSectionResults( Int32 poiId );
   virtual bamSectionStress CombineSectionStress( Int32 poiId, Int32 spIdx );

   //------------------------------------------------------------------------
   virtual bamReaction CombineReactions( Int32 supportId );

   //------------------------------------------------------------------------
   virtual bamLoadCombination* Clone() const;

   //------------------------------------------------------------------------
   void SetMultiplier(Float64 multiplier);

   //------------------------------------------------------------------------
   Float64 GetMultiplier() const;

   //------------------------------------------------------------------------
   void AddLoading(Int32 loadingId,Float64 minFactor,Float64 maxFactor);

   //------------------------------------------------------------------------
   void SetOptimizationType(bamOptimumType type);

   //------------------------------------------------------------------------
   bamOptimumType GetOptimizationType() const;

   //------------------------------------------------------------------------
   void SetOptimizationVariable(bamOptimumVariable variable);

   //------------------------------------------------------------------------
   bamOptimumVariable GetOptimizationVariable() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   virtual void GetLoadings(std::vector<Int32>& loadingIds) const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual bamSectionResults GetSectionResults(const bamSectionResultsKey& key);
   virtual bamSectionStress GetSectionStress(const bamSectionStressKey& key);

   //------------------------------------------------------------------------
   virtual bamReaction GetReaction(const bamReactionKey& key);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   bamOptimumType m_Type;
   bamOptimumVariable m_Variable;

   Float64 m_Multiplier;

#pragma warning( disable : 4251 )
   typedef std::pair<Float64,Float64> LoadFactors;
   typedef std::pair<Int32,LoadFactors> LoadEntry;
   typedef std::map<Int32,LoadFactors> LoadEntryContainer;
   typedef LoadEntryContainer::iterator LoadEntryIterator;
   typedef LoadEntryContainer::const_iterator ConstLoadEntryIterator;
   LoadEntryContainer m_LoadEntries;

   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   bamOptimumLoadCombination& operator=(const bamOptimumLoadCombination&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_OPTIMUMLOADCOMBINATION_H_

