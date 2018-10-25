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

#ifndef INCLUDED_BRIDGEANALYSIS_TRANSIENTLDENVELOPE_H_
#define INCLUDED_BRIDGEANALYSIS_TRANSIENTLDENVELOPE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <BridgeAnalysis\Envelope.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bamTransientLdEnvelope

   Special purpose envelope for use with transient loads.


DESCRIPTION
   Special purpose envelope for use with transient loads.  Unlike regular
   envelopes,  the zero-effect case must always be considered with transient
   loads.  This class overrides bamEnvelope's InitEnvelope() methods to
   initialize the envelope to zero.


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
   rab : 08.21.1997 : Created file
*****************************************************************************/

class BAMCLASS bamTransientLdEnvelope : public bamEnvelope
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bamTransientLdEnvelope(IDType id);

   //------------------------------------------------------------------------
   // Copy constructor
   bamTransientLdEnvelope(const bamTransientLdEnvelope& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bamTransientLdEnvelope();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bamTransientLdEnvelope& operator = (const bamTransientLdEnvelope& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   bamEnvelope* CreateClone() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const bamTransientLdEnvelope& rOther);
   void MakeAssignment(const bamTransientLdEnvelope& rOther);
   virtual void InitEnvelope(bamSectionResults* pMin,bamSectionResults* pMax) const;
   virtual void InitEnvelope(bamReaction* pMin, bamReaction* pMax) const;

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

#endif // INCLUDED_BRIDGEANALYSIS_TRANSIENTLDENVELOPE_H_

