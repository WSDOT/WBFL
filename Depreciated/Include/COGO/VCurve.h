///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_COGO_VCURVE_H_
#define INCLUDED_COGO_VCURVE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Cogo\CogoExp.h>
#include <GeometricPrimitives\Primitives.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   cogoVCurve

   This class encapsulates a parabolic vertical curve.


DESCRIPTION
   This class encapsulates a parabolic vertical curve.  The curve is defined
   by the coordinates of the BVC, PVI, and EVC.  The X coordinate is taken
   as the station and the Y coordinate is taken as the elevation.

COPYRIGHT
   Copyright (c) 1999
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 04.23.1999 : Created file
*****************************************************************************/

class COGOCLASS cogoVCurve
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   cogoVCurve();

   //------------------------------------------------------------------------
   cogoVCurve(const gpPoint2d& bvc,const gpPoint2d& pvi,const gpPoint2d& evc);

   //------------------------------------------------------------------------
   // Copy constructor
   cogoVCurve(const cogoVCurve& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~cogoVCurve();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   // Returns reference to itself
   cogoVCurve& operator = (const cogoVCurve& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the point of curvature.
   void SetBVC(const gpPoint2d& bvc);

   //------------------------------------------------------------------------
   // Returns the point of curvature.
   gpPoint2d GetBVC() const;

   //------------------------------------------------------------------------
   // Sets the point of intersection of the curve tangents.
   void SetPVI(const gpPoint2d& pvi);

   //------------------------------------------------------------------------
   // Returns the point of intersection of the curve tangents.
   gpPoint2d GetPVI() const;

   //------------------------------------------------------------------------
   // Sets the point of tangency.
   void SetEVC(const gpPoint2d& evc);

   //------------------------------------------------------------------------
   // Returns the point of tangency.
   gpPoint2d GetEVC() const;

   //------------------------------------------------------------------------
   // Returns the length of the curve
   Float64 GetLength() const;

   //------------------------------------------------------------------------
   // Returns the starting grade
   Float64 GetG1() const;

   //------------------------------------------------------------------------
   // Returns the ending grade
   Float64 GetG2() const;

   //------------------------------------------------------------------------
   // Returns the grade at a given station
   Float64 GetGrade(Float64 station) const;

   //------------------------------------------------------------------------
   // Computes the high point of the curve
   gpPoint2d GetHighPoint() const;

   //------------------------------------------------------------------------
   // Computes the low point of the curve
   gpPoint2d GetLowPoint() const;

   //------------------------------------------------------------------------
   // Returns the elevation at a given station
   Float64 GetElevation(Float64 station) const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const cogoVCurve& rOther);
   void MakeAssignment(const cogoVCurve& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   gpPoint2d m_BVC;
   gpPoint2d m_PVI;
   gpPoint2d m_EVC;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   gpPoint2d MinMaxPoint() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY
#if defined _DEBUG
public:
   bool AssertValid() const;
   void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
public:
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_COGO_VCURVE_H_

