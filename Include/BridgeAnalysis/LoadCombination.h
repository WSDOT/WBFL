///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
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

#ifndef INCLUDED_BRIDGEANALYSIS_LOADCOMBINATION_H_
#define INCLUDED_BRIDGEANALYSIS_LOADCOMBINATION_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\SectionResults.h>
#include <BridgeAnalysis\SectionStress.h>
#include <BridgeAnalysis\Reaction.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bamBridgeModel;

// MISCELLANEOUS
//

class BAMCLASS bamLoadCombination
{
public:
   // LIFECYCLE

   // Method:      LoadCombination
   // Description: Explicit c'tor
   // Return:      N/A
   bamLoadCombination(IDType id);
   bamLoadCombination(const bamLoadCombination& rOther);

   // Method:      ~LoadCombination
   // Description: d'tor
   // Return:      N/A
   virtual ~bamLoadCombination(); 

   // OPERATORS
   // OPERATIONS

   // Method:      GetID
   // Description: 
   // Return:      Returns the loading id
   IDType GetID() const;
   void SetID(IDType id);

   virtual bamSectionResults CombineSectionResults( PoiIDType poiId ) = 0;
   virtual bamSectionStress CombineSectionStress( PoiIDType poiId, CollectionIndexType spIdx ) = 0;
   virtual bamReaction CombineReactions( SupportIDType supportId ) = 0;

   void SetBridgeModel(bamBridgeModel* pModel);
   bamBridgeModel& GetBridgeModel() const;

   virtual bamLoadCombination* Clone() const = 0;

   // ACCESS
   virtual void GetLoadings(std::vector<IDType>& loadingIds) const = 0;

   // INQUIRY

protected:
   // DATA MEMBERS
   // LIFECYCLE
   // OPERATORS
   // OPERATIONS

   // ACCESS
   // INQUIRY

private:
   // DATA MEMBERS
   IDType m_ID;
   bamBridgeModel* m_pBridgeModel;

   // LIFECYCLE
   // OPERATORS
   bamLoadCombination& operator = (const bamLoadCombination& /*rLoadCombination*/);  // Remove to enable assignment

   // OPERATIONS
   // ACCESS
   // INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_LOADCOMBINATION_H_
