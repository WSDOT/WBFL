///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_LIVELOADSOLVER_H_
#define INCLUDED_BRIDGEANALYSIS_LIVELOADSOLVER_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\LiveLoad.h>
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


class BAMCLASS bamLiveLoadSolver
{
public:
   // LIFECYCLE

   // Method:      bamLiveLoadSolver
   // Description: Default c'tor
   // Return:      N/A
   bamLiveLoadSolver();

   // Method:      ~bamLiveLoadSolver
   // Description: d'tor
   // Return:      N/A
   virtual ~bamLiveLoadSolver(); 

   // OPERATORS
   // OPERATIONS

   // Method:      Solver
   // Description: Performs a live load analysis for the given live load
   // Return:      None
   virtual void Solve(bamLiveLoad& ll) = 0;
   virtual void Solve(bamLiveLoad& ll,PoiIDType poi) = 0;
   virtual void SolveStress(bamLiveLoad& ll,PoiIDType poi,CollectionIndexType spid) = 0;

   // Method:      SetBridgeModel
   // Description: Associates the bridge model with this solver.
   // Return:      None
   void SetBridgeModel(bamBridgeModel* pModel);

   // ACCESS
   // INQUIRY

protected:
   // DATA MEMBERS
   bamBridgeModel* m_pBridgeModel;

   // LIFECYCLE
   // OPERATORS
   // OPERATIONS
   void WriteSectionResults(const bamSectionResultsKey& key, const bamSectionResults& sr);
   bamSectionResults ReadSectionResults(const bamSectionResultsKey& key);
   void WriteSectionStress(const bamSectionStressKey& key,const bamSectionStress& ss);
   bamSectionStress ReadSectionStress(const bamSectionStressKey& key);
   void WriteReaction( const bamReactionKey& key, const bamReaction& reaction );
   bamReaction ReadReaction( const bamReactionKey& key );

   // ACCESS
   // INQUIRY

private:
   // DATA MEMBERS
   // LIFECYCLE
   bamLiveLoadSolver(const bamLiveLoadSolver& /*rOther*/);

   // OPERATORS
   bamLiveLoadSolver& operator = (const bamLiveLoadSolver& /*rOther*/);

   // OPERATIONS
   // ACCESS
   // INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_LIVELOADSOLVER_H_
