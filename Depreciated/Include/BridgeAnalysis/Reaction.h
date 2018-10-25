///////////////////////////////////////////////////////////////////////
// BAM - Bridge Analysis Model, Analytical modeling of bridge structures
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_BRIDGEANALYSIS_REACTION_H_
#define INCLUDED_BRIDGEANALYSIS_REACTION_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//
/*****************************************************************************
CLASS 
   bamReactionKey

   Lookup key for bamReaction objects.


DESCRIPTION
   Lookup key for bamReaction objects.

BUGS
   There are currently no known problems with this class.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 08.19.1997 : Created file
*****************************************************************************/

class BAMCLASS bamReactionKey
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bamReactionKey();

   //------------------------------------------------------------------------
   bamReactionKey(SupportIDType supportId,IDType loadingId);

   //------------------------------------------------------------------------
   // Copy constructor
   bamReactionKey(const bamReactionKey& rOther);

   //------------------------------------------------------------------------
   // Destructor
   ~bamReactionKey();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bamReactionKey& operator = (const bamReactionKey& rOther);
   bool operator< (const bamReactionKey& rOther) const;
   bool operator==(const bamReactionKey& rOther) const;

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   void SupportId(SupportIDType supportId);
   SupportIDType SupportId() const;
   void LoadingId(IDType loadingId);
   IDType LoadingId() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const bamReactionKey& rOther);
   virtual void MakeAssignment(const bamReactionKey& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   SupportIDType m_SupportId;
   IDType m_LoadingId;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

/*****************************************************************************
CLASS 
   bamReaction

   Encapsulates a reaction.


DESCRIPTION
   Encapsulates a reaction.

BUGS
   There are currently no known problems with this class.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 08.19.1997 : Created file
*****************************************************************************/

class BAMCLASS bamReaction
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bamReaction();

   //------------------------------------------------------------------------
   bamReaction(Float64 fx,Float64 fy,Float64 mz,Float64 dx,Float64 dy,Float64 rz);

   //------------------------------------------------------------------------
   // Copy constructor
   bamReaction(const bamReaction& rOther);

   //------------------------------------------------------------------------
   // Destructor
   ~bamReaction();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bamReaction& operator = (const bamReaction& rOther);
   bamReaction& operator+= (const bamReaction& rOther);
   bamReaction& operator-= (const bamReaction& rOther);
   bamReaction& operator*= (Float64 d);
   bamReaction& operator/= (Float64 d);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   const Float64& Fx() const;
   Float64& Fx();

   const Float64& Fy() const;
   Float64& Fy();

   const Float64& Mz() const;
   Float64& Mz();

   const Float64& Dx() const;
   Float64& Dx();

   const Float64& Dy() const;
   Float64& Dy();

   const Float64& Rz() const;
   Float64& Rz();

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const bamReaction& rOther);
   virtual void MakeAssignment(const bamReaction& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Fx;
   Float64 m_Fy;
   Float64 m_Mz;
   Float64 m_Dx;
   Float64 m_Dy;
   Float64 m_Rz;

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
bamReaction BAMFUNC operator+(const bamReaction& lhs,const bamReaction& rhs);
bamReaction BAMFUNC operator-(const bamReaction& lhs,const bamReaction& rhs);
bamReaction BAMFUNC operator*(const bamReaction& lhs,Float64 d);
bamReaction BAMFUNC operator*(Float64 d,const bamReaction& rhs);

#endif // INCLUDED_BRIDGEANALYSIS_REACTION_H_

