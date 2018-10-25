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

#ifndef INCLUDED_BRIDGEANALYSIS_SECTIONSTRESS_H_
#define INCLUDED_BRIDGEANALYSIS_SECTIONSTRESS_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <System\SectionValue.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   bamSectionStressKey

   Lookup key for bamSectionStress objects


DESCRIPTION
   Lookup key for bamSectionResults objects

BUGS
   There are currently no known problems with this class.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 08.19.1997 : Created file
*****************************************************************************/
class BAMCLASS bamSectionStressKey
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bamSectionStressKey();

   //------------------------------------------------------------------------
   bamSectionStressKey(PoiIDType poi,CollectionIndexType idx,IDType loading);

   //------------------------------------------------------------------------
   // Copy constructor
   bamSectionStressKey(const bamSectionStressKey& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bamSectionStressKey();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bamSectionStressKey& operator = (const bamSectionStressKey& rOther);
   bool operator< (const bamSectionStressKey& rOther) const;
   bool operator==(const bamSectionStressKey& rOther) const;

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   void LoadingId(IDType loadingId);
   IDType LoadingId() const;
   void StressPointIdx(IndexType idx);
   IndexType StressPointIdx() const;
   void PointOfInterest(IDType poi);
   IDType PointOfInterest() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const bamSectionStressKey& rOther);
   void MakeAssignment(const bamSectionStressKey& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   IDType m_LoadingId;
   CollectionIndexType m_StressPointIdx;
   PoiIDType m_Poi;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};


/*****************************************************************************
CLASS 
   bamSectionStress

   Encapsulates force and displacement results at a section.


DESCRIPTION
   Encapsulates force and displacement results at a section.

BUGS
   There are currently no known problems with this class.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 08.19.1997 : Created file
*****************************************************************************/

class BAMCLASS bamSectionStress
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bamSectionStress();

   //------------------------------------------------------------------------
   bamSectionStress(const sysSectionValue& f);

   //------------------------------------------------------------------------
   // Copy constructor
   bamSectionStress(const bamSectionStress& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bamSectionStress();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bamSectionStress& operator = (const bamSectionStress& rOther);

   //------------------------------------------------------------------------
   bamSectionStress& operator+=(const bamSectionStress& rOther);
   bamSectionStress& operator-=(const bamSectionStress& rOther);
   bamSectionStress  operator-();
   bamSectionStress& operator*=(Float64 d);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   const sysSectionValue& F() const;
   sysSectionValue& F();

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const bamSectionStress& rOther);
   void MakeAssignment(const bamSectionStress& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   sysSectionValue m_f;

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
bamSectionStress BAMFUNC operator+(const bamSectionStress& a,const bamSectionStress& b);
bamSectionStress BAMFUNC operator-(const bamSectionStress& a,const bamSectionStress& b);
bamSectionStress BAMFUNC operator*(Float64 d,const bamSectionStress& rhs);
bamSectionStress BAMFUNC operator*(const bamSectionStress& lhs,Float64 d);
bamSectionStress BAMFUNC operator*(const sysSectionValue& lhs,const bamSectionStress& rhs);
bamSectionStress BAMFUNC operator*(const bamSectionStress& lhs,const sysSectionValue& rhs);

#endif // INCLUDED_BRIDGEANALYSIS_SECTIONSTRESS_H_

