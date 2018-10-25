///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2014  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_STAGEDLOADCOMBINATION_H_
#define INCLUDED_BRIDGEANALYSIS_STAGEDLOADCOMBINATION_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\LoadCombination.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class bamBridgeModel;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bamStagedLoadCombination

   Combines loads from various models used in stage construction modeling.


DESCRIPTION
   Combines loads from various models used in stage construction modeling.

   Typically,  staged construction requires more than one structural analysis
   model to capture the correct behavior.  This class allows you to combine
   the analysis results from the owning bridge analysis model with additional
   bridge analysis models.  It is assumed that the loading identifiers are
   the same in all bridge analysis models and the points of interest in each
   of the models represent the same location in the real bridge structure.

   For example,  this load combination object will combine the results at 
   point of interest I for loading J.  It is assumed that all the models have
   a point of interest I and a loading J.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.10.1998 : Created file
*****************************************************************************/

class BAMCLASS bamStagedLoadCombination : public bamLoadCombination
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bamStagedLoadCombination(Int32 id);

   //------------------------------------------------------------------------
   // Copy constructor
   bamStagedLoadCombination(const bamStagedLoadCombination& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bamStagedLoadCombination();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   bamStagedLoadCombination& operator = (const bamStagedLoadCombination& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Add a loading to the combination.  All models added to this combination
   // must have a loading with this id.
   void AddLoading(IDType loadingId);

   //------------------------------------------------------------------------
   // Add a bridge model whose results will be combined with the results
   // for the owning bridge model.
   void AddModel(bamBridgeModel* pModel);

   //------------------------------------------------------------------------
   virtual bamSectionResults CombineSectionResults( PoiIDType poiId );

   //------------------------------------------------------------------------
   virtual bamSectionStress CombineSectionStress( PoiIDType poiId, CollectionIndexType spIdx );

   //------------------------------------------------------------------------
   virtual bamReaction CombineReactions( PierIDType supportId );

   //------------------------------------------------------------------------
   virtual bamLoadCombination* Clone() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   virtual void GetLoadings(std::vector<IDType>& loadingIds) const;

   // GROUP: INQUIRY


protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const bamStagedLoadCombination& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const bamStagedLoadCombination& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::vector<IDType> m_Loads;
   std::vector<bamBridgeModel*> m_Models;

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

#endif // INCLUDED_BRIDGEANALYSIS_STAGEDLOADCOMBINATION_H_
