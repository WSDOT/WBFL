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

#ifndef INCLUDED_BRIDGEANALYSIS_SECTIONRESULTS_H_
#define INCLUDED_BRIDGEANALYSIS_SECTIONRESULTS_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <BridgeAnalysis\BridgeAnalysisExp.h>
#include <System\SectionAction.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

typedef sysSectionAction bamSectionResults;

/*****************************************************************************
CLASS 
   bamSectionResultsKey

   Lookup key for bamSectionResults objects


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
class BAMCLASS bamSectionResultsKey
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   bamSectionResultsKey();

   //------------------------------------------------------------------------
   bamSectionResultsKey(PoiIDType poi,IDType loading);

   //------------------------------------------------------------------------
   // Copy constructor
   bamSectionResultsKey(const bamSectionResultsKey& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~bamSectionResultsKey();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   bamSectionResultsKey& operator = (const bamSectionResultsKey& rOther);
   bool operator< (const bamSectionResultsKey& rOther) const;
   bool operator==(const bamSectionResultsKey& rOther) const;

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   void LoadingId(IDType loadingId);
   IDType LoadingId() const;
   void PointOfInterest(PoiIDType poi);
   PoiIDType PointOfInterest() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const bamSectionResultsKey& rOther);
   void MakeAssignment(const bamSectionResultsKey& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   IDType m_LoadingId;
   PoiIDType m_Poi;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};
//
//
///*****************************************************************************
//CLASS 
//   bamSectionResults
//
//   Encapsulates force and displacement results at a section.
//
//
//DESCRIPTION
//   Encapsulates force and displacement results at a section.
//
//BUGS
//   There are currently no known problems with this class.
//
//COPYRIGHT
//   Copyright (c) 1997
//   Washington State Department Of Transportation
//   All Rights Reserved
//
//LOG
//   rab : 08.19.1997 : Created file
//*****************************************************************************/
//
//class BAMCLASS bamSectionResults
//{
//public:
//   // GROUP: LIFECYCLE
//
//   //------------------------------------------------------------------------
//   // Default constructor
//   bamSectionResults();
//
//   //------------------------------------------------------------------------
//   bamSectionResults(const sysSectionValue& fx,
//                    const sysSectionValue& fy,
//                    const sysSectionValue& mz,
//                    const sysSectionValue& dx,
//                    const sysSectionValue& dy,
//                    const sysSectionValue& rz);
//
//   //------------------------------------------------------------------------
//   // Copy constructor
//   bamSectionResults(const bamSectionResults& rOther);
//
//   //------------------------------------------------------------------------
//   // Destructor
//   virtual ~bamSectionResults();
//
//   // GROUP: OPERATORS
//   //------------------------------------------------------------------------
//   // Assignment operator
//   //
//   // Returns reference to itself
//   bamSectionResults& operator = (const bamSectionResults& rOther);
//
//   //------------------------------------------------------------------------
//   bamSectionResults& operator+=(const bamSectionResults& rOther);
//   bamSectionResults& operator-=(const bamSectionResults& rOther);
//   bamSectionResults  operator-();
//   bamSectionResults& operator*=(Float64 d);
//
//   // GROUP: OPERATIONS
//   // GROUP: ACCESS
//   const sysSectionValue& Fx() const;
//   sysSectionValue& Fx();
//
//   const sysSectionValue& Fy() const;
//   sysSectionValue& Fy();
//
//   const sysSectionValue& Mz() const;
//   sysSectionValue& Mz();
//
//   const sysSectionValue& Dx() const;
//   sysSectionValue& Dx();
//
//   const sysSectionValue& Dy() const;
//   sysSectionValue& Dy();
//
//   const sysSectionValue& Rz() const;
//   sysSectionValue& Rz();
//
//   // GROUP: INQUIRY
//
//protected:
//   // GROUP: DATA MEMBERS
//   // GROUP: LIFECYCLE
//   // GROUP: OPERATORS
//   // GROUP: OPERATIONS
//   void MakeCopy(const bamSectionResults& rOther);
//   void MakeAssignment(const bamSectionResults& rOther);
//
//   // GROUP: ACCESS
//   // GROUP: INQUIRY
//
//private:
//   // GROUP: DATA MEMBERS
//   sysSectionValue m_Fx;
//   sysSectionValue m_Fy;
//   sysSectionValue m_Mz;
//   sysSectionValue m_Dx;
//   sysSectionValue m_Dy;
//   sysSectionValue m_Rz;
//
//   // GROUP: LIFECYCLE
//   // GROUP: OPERATORS
//   // GROUP: OPERATIONS
//   // GROUP: ACCESS
//   // GROUP: INQUIRY
//};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//
//bamSectionResults BAMFUNC operator+(const bamSectionResults& a,const bamSectionResults& b);
//bamSectionResults BAMFUNC operator-(const bamSectionResults& a,const bamSectionResults& b);
//bamSectionResults BAMFUNC operator*(Float64 d,const bamSectionResults& rhs);
//bamSectionResults BAMFUNC operator*(const bamSectionResults& lhs,Float64 d);
//bamSectionResults BAMFUNC operator*(const sysSectionValue& lhs,const bamSectionResults& rhs);
//bamSectionResults BAMFUNC operator*(const bamSectionResults& lhs,const sysSectionValue& rhs);

#endif // INCLUDED_BRIDGEANALYSIS_SECTIONRESULTS_H_

