///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2016  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_ANALYSISRESULTSMANAGER_H_
#define INCLUDED_BRIDGEANALYSIS_ANALYSISRESULTSMANAGER_H_
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

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bamAnalysisResultsManager

   Abstract class that provides an interface for reading and writing
   structural analysis results.

DESCRIPTION
   Abstract class that provides an interface for reading and writing
   structural analysis results.  The bridge analysis framework uses this
   interface to read and write structural analysis results, with no knowledge
   as to where the results really being stored.  This abstraction allobam
   clients to implement virtually any storage scheme they like.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class BAMCLASS bamAnalysisResultsManager
{
public:

   //------------------------------------------------------------------------
   // virtual destructor
   virtual ~bamAnalysisResultsManager(){}

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Called by the framework prior to storing any results for <i>loadingId</i>.
   // This gives a subclass an opportunity to create and initialize any
   // necessary storage.
   //
   // Does nothing by default
   virtual void CreateStorage(IDType loadingId) = 0;

   //------------------------------------------------------------------------
   // Called by the framework went storage for <i>loadingId</i> is not longer
   // needed.  If storage isn't currently allocated, this method should do
   // nothing.
   virtual void DestroyStorage(IDType loadingId) = 0;

   //------------------------------------------------------------------------
   virtual bamSectionResults ReadSectionResults(const bamSectionResultsKey& key) const = 0;

   //------------------------------------------------------------------------
   virtual void WriteSectionResults(const bamSectionResultsKey& key,const bamSectionResults& sr) = 0;

   //------------------------------------------------------------------------
   virtual bamReaction ReadReaction(const bamReactionKey& key) const = 0;

   //------------------------------------------------------------------------
   // Commits reactions to the storage system.
   virtual void WriteReaction(const bamReactionKey& key,const bamReaction& reaction) = 0;

   //------------------------------------------------------------------------
   virtual void WriteSectionStress(const bamSectionStressKey& key,const bamSectionStress& s) = 0;
   virtual bamSectionStress ReadSectionStress(const bamSectionStressKey& key) const = 0;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_ANALYSISRESULTSMANAGER_H_
