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

#ifndef INCLUDED_BRIDGEANALYSIS_SIMPLERESULTSMANAGER_H_
#define INCLUDED_BRIDGEANALYSIS_SIMPLERESULTSMANAGER_H_
#pragma once

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          bamSimpleResultsManager
// SYNOPSIS:      
// DESCRIPTION:   Provides a simple implementation of the AnalysisResults-
//                Manager interface.
// EXAMPLES:      
// BUGS:          
// ALSO SEE:
//////////////////X////////////////////X/////////////////////////////////////

// SYSTEM INCLUDES
//
#include <map>

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\AnalysisResultsManager.h>
#include <BridgeAnalysis\Reaction.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

class BAMCLASS bamSimpleResultsManager : public bamAnalysisResultsManager
{
public:
   // LIFECYCLE
   bamSimpleResultsManager();
   virtual ~bamSimpleResultsManager(); 

   // OPERATORS
   // OPERATIONS

   //------------------------------------------------------------------------
   virtual void CreateStorage(IDType loadingId);

   //------------------------------------------------------------------------
   virtual void DestroyStorage(IDType loadingId);

   //------------------------------------------------------------------------
   virtual bamSectionResults ReadSectionResults(const bamSectionResultsKey& key) const;

   //------------------------------------------------------------------------
   virtual void WriteSectionResults(const bamSectionResultsKey& key,const bamSectionResults& sr);

   //------------------------------------------------------------------------
   virtual bamReaction ReadReaction(const bamReactionKey& key) const;

   //------------------------------------------------------------------------
   virtual void WriteReaction(const bamReactionKey& key,const bamReaction& reaction);

   virtual void WriteSectionStress(const bamSectionStressKey& key,const bamSectionStress& s);
   virtual bamSectionStress ReadSectionStress(const bamSectionStressKey& key) const;

   // ACCESS
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
   typedef std::map<bamSectionResultsKey,bamSectionResults> SectionResultsContainer;
   typedef std::pair<bamSectionResultsKey,bamSectionResults> SectionResultEntry;
   typedef SectionResultsContainer::iterator SectionResultsIterator;
   typedef SectionResultsContainer::const_iterator ConstSectionResultsIterator;

   typedef std::map<bamReactionKey,bamReaction> ReactionContainer;
   typedef ReactionContainer::iterator ReactionIterator;
   typedef ReactionContainer::const_iterator ConstReactionIterator;
   typedef std::pair<bamReactionKey,bamReaction> ReactionEntry;

   typedef std::map<bamSectionStressKey,bamSectionStress> SectionStressContainer;
   typedef std::pair<bamSectionStressKey,bamSectionStress> SectionStressEntry;
   typedef SectionStressContainer::iterator SectionStressIterator;
   typedef SectionStressContainer::const_iterator ConstSectionStressIterator;

#pragma warning ( disable : 4251 )
   SectionResultsContainer m_SectionResults;
   ReactionContainer m_Reactions;
   SectionStressContainer m_SectionStresses;


   // LIFECYCLE
   bamSimpleResultsManager(const bamSimpleResultsManager& /*rSimpleResultsManager*/);               // Remove to enable copy

   // OPERATORS
   bamSimpleResultsManager& operator = (const bamSimpleResultsManager& /*rSimpleResultsManager*/);  // Remove to enable assignment

   // OPERATIONS
   // ACCESS
   // INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif //  INCLUDED_BRIDGEANALYSIS_SIMPLERESULTSMANAGER_H_
