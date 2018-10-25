///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2012  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_ENVELOPE_H_
#define INCLUDED_BRIDGEANALYSIS_ENVELOPE_H_
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
struct bamPointOfInterest;
struct bamStressPoint;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bamEnvelope

   Extreme response values for a collection of loadings.


DESCRIPTION
   Extreme response values for a collection of loadings.

   An envelope interrogates a collections of loadings and
   determines the extreme structural responses.

   An envelope is a dependent loading. It is similar to a load
   combination in that it is dependent upon other loadings and
   it produces new loading entries in the analysis results
   manager.

   By default, all envelopes are created.  Envelopes can be selectively
   enabled.

   Upon insertion into a bridge model, each envelope type is assigned
   a loading id.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 07.01.1997 : Created file
*****************************************************************************/

class BAMCLASS bamEnvelope
{
public:
   enum ExtremeValueType { Min, Max };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor - Creates an envelope object.
   bamEnvelope(IDType id);

   //------------------------------------------------------------------------
   // Copy constructor - Creates an envelope object that is a copy of
   // <i>rOther</i>.
   bamEnvelope(const bamEnvelope& rOther);

   //------------------------------------------------------------------------
   // Destructor - Cleans up the envelope object
   virtual ~bamEnvelope(); 

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator - Assigns the members of <i>rOther</i> to <b>this</b>.
   bamEnvelope& operator = (const bamEnvelope& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   virtual bamEnvelope* CreateClone() const;

   //------------------------------------------------------------------------
   // Adds a loading id to the list of loadings to be considered in the
   // envelope.
   void AddLoading(IDType loadingId);

   //------------------------------------------------------------------------
   // Adds multiple loading ids to the list of loadings to be considered in
   // the envelope.
   void AddLoading(std::vector<IDType>& loadingIds);

   //------------------------------------------------------------------------
   // Associates a bridge model with this envelope. Called by the framework
   // when the envelope is inserted into a bridge model. Do not call this
   // method directly.
   void SetBridgeModel(bamBridgeModel* pModel);

   //------------------------------------------------------------------------
   // Does the enveloping operation. Called by the framework. Do not call 
   // this method directly.
   void DoEnvelope() const;

   //------------------------------------------------------------------------
   // Does the enveloping operation. Called by the framework. Do not call 
   // this method directly.
   void DoEnvelope(PoiIDType poi) const;

   void DoEnvelopeSectionStress(PoiIDType poi,CollectionIndexType srid) const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Returns the envelope's identifier
   IDType GetID() const;

   //------------------------------------------------------------------------
   // Sets the envelope's identifier.
   void SetID(IDType id);

   //------------------------------------------------------------------------
   // Sets the loading identifier and enables enveloping for the extreme 
   // value type.
   void SetLoadingIds(IDType minLoadingId,IDType maxLoadingId);
   
   //------------------------------------------------------------------------
   // Returns the loading identifier for the extreme value type.
   IDType GetLoadingId(bamEnvelope::ExtremeValueType ev) const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const bamEnvelope& rOther);
   void MakeAssignment(const bamEnvelope& rOther);
   virtual void InitEnvelope(bamSectionResults* pMin,bamSectionResults* pMax) const;
   virtual void InitEnvelope(bamSectionStress* pMin, bamSectionStress* pMax) const;
   virtual void InitEnvelope(bamReaction* pMin,bamReaction* pMax) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   IDType m_Id;  // Not a loading Id, this is the envelope identifier
   bamBridgeModel* m_pBridgeModel;

   // loading Id's for envelope
   IDType m_MinId;
   IDType m_MaxId;

   typedef std::vector<IDType> LoadingContainer;
   typedef LoadingContainer::const_iterator ConstLoadingIterator;
   LoadingContainer m_Loadings;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void DoEnvelopeSectionResults() const;
   void DoEnvelopeSectionStress() const;
   void DoEnvelopeReactions() const;

   void DoEnvelopeSectionResults(PoiIDType poi) const;
   void DoEnvelopeSectionStress(PoiIDType poi) const;
   void DoEnvelopeSectionStress(const bamPointOfInterest& poi,const bamSectionResults& srMin,const bamSectionResults& srMax,const bamStressPoint& sp) const;

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_BRIDGEANALYSIS_ENVELOPE_H_
