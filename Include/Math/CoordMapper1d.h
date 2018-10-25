///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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

#ifndef INCLUDED_MATH_COORDMAPPER1D_H_
#define INCLUDED_MATH_COORDMAPPER1D_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Math\MathExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   mathCoordMapper1d

   A class for mapping between two 1-D coordinate systems.


DESCRIPTION
   This class may be used to map between two different one-dimensional
   coordinate systems A and B. The two systems may be of different scales, 
   offset from each other and may point in different directions.

                    A1     A2
   -----------------|------|---------------->> A
                    
  <<----------------|------|----------------- B
                    B1     B2

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 08.14.1997 : Created file
*****************************************************************************/

class MATHCLASS mathCoordMapper1d
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor - mapping between A and B is one-to-one.
   mathCoordMapper1d();

   //------------------------------------------------------------------------
   // Constructor for systems with the same scale and only an offset.
   // Assuming that A points in the positive direction, d is the distance from
   // the origin of system A to the origin of System B along A
   // Set the IsSameDirection flag to true if the positive directions of the
   // two systems point the same way.
   //   -----------------|---------------------->> A
   //                    <--d-->
   //   <<----------------------|----------------- B
   mathCoordMapper1d(Float64 d, bool IsSameDirection);


   //------------------------------------------------------------------------
   // Constructor for systems that are arbitrarly oriented to each other.
   // All that you need to do is map two sets of points from each system
   // to each other and the mapper takes care of the rest.
   //
   //                   a1     a2
   //  -----------------|------|---------------->> A
   //                    
   // <<----------------|------|----------------- B
   //                   b1     b2
   // 
   mathCoordMapper1d(Float64 a1, Float64 b1, Float64 a2, Float64 b2);


   //------------------------------------------------------------------------
   // Copy constructor
   mathCoordMapper1d(const mathCoordMapper1d& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~mathCoordMapper1d();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   mathCoordMapper1d& operator = (const mathCoordMapper1d& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Set up the point mapping between two arbitrary 1d systems.
   //
   //                   a1     a2
   //  -----------------|------|---------------->> A
   //                    
   // <<----------------|------|----------------- B
   //                   b1     b2
   // 
   // This function will throw an mathXMath exception if a1==a2 || b1==b2
   //
   void SetCoordinateMap(Float64 a1, Float64 b1, Float64 a2, Float64 b2);

   //------------------------------------------------------------------------
   // Set up mapping for systems with the same scale and only an offset.
   // Assuming that A points in the positive direction, d is the distance from
   // the origin of system A to the origin of System B along A
   // Set the IsSameDirection flag to true if the positive directions of the
   // two systems point the same way.
   //   -----------------|---------------------->> A
   //                    <--d-->
   //   <<----------------------|----------------- B
   void SetMapSameScale(Float64 d, bool IsSameDirection);

   //------------------------------------------------------------------------
   // Map a value in system B to system A
   Float64 GetA( Float64 B) const;

   //------------------------------------------------------------------------
   // Map a value in system A to system B
   Float64 GetB( Float64 A) const;

   // GROUP: ACCESS

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const mathCoordMapper1d& rOther);
   virtual void MakeAssignment(const mathCoordMapper1d& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   // transform is in the form of A = Bc + d
   // where c and d are constants
   Float64 m_c, m_d;

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

#endif // INCLUDED_MATH_COORDMAPPER1D_H_

