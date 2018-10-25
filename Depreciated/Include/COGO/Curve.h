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

#ifndef INCLUDED_COGO_CURVE_H_
#define INCLUDED_COGO_CURVE_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Cogo\CogoExp.h>
#include <Cogo\CogoAngle.h>
#include <Cogo\CogoDirection.h>
#include <GeometricPrimitives\Primitives.h>
#include <GeometricPrimitives\Line2d.h> // for gpLine2d::Side

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   cogoCurve

   This class encapsulates a circular curve.


DESCRIPTION
   This class encapsulates a circular curve.  Curves are represented by
   four coordinate points.  All curve parameters can be derived from these
   points.

COPYRIGHT
   Copyright (c) 1999
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 04.21.1999 : Created file
*****************************************************************************/

class COGOCLASS cogoCurve
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   cogoCurve();

   //------------------------------------------------------------------------
   cogoCurve(const gpPoint2d& pc,const gpPoint2d& pi,const gpPoint2d& pt, const gpPoint2d& cc);

   //------------------------------------------------------------------------
   cogoCurve(const cogoDirection& bkBrg,const cogoDirection& fwdBrg,const gpPoint2d& pi,Float64 radius);

   //------------------------------------------------------------------------
   // Copy constructor
   cogoCurve(const cogoCurve& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~cogoCurve();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   // Returns reference to itself
   cogoCurve& operator = (const cogoCurve& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the point of curvature.
   void SetPC(const gpPoint2d& pc);

   //------------------------------------------------------------------------
   // Returns the point of curvature.
   gpPoint2d GetPC() const;

   //------------------------------------------------------------------------
   // Sets the point of intersection of the curve tangents.
   void SetPI(const gpPoint2d& pi);

   //------------------------------------------------------------------------
   // Returns the point of intersection of the curve tangents.
   gpPoint2d GetPI() const;

   //------------------------------------------------------------------------
   // Sets the point of tangency.
   void SetPT(const gpPoint2d& pt);

   //------------------------------------------------------------------------
   // Returns the point of tangency.
   gpPoint2d GetPT() const;

   //------------------------------------------------------------------------
   // Sets the center point.
   void SetCC(const gpPoint2d& cc);

   //------------------------------------------------------------------------
   // Returns the center point
   gpPoint2d GetCC() const;

   //------------------------------------------------------------------------
   // Returns the length of the curve
   Float64 GetL() const;

   //------------------------------------------------------------------------
   // Returns the tangent of the curve
   Float64 GetT() const;

   //------------------------------------------------------------------------
   // Returns the eccentricity of the curve
   Float64 GetE() const;

   //------------------------------------------------------------------------
   // Returns the chord of the curve
   Float64 GetC() const;

   //------------------------------------------------------------------------
   // Returns the mid ordinant of the curve
   Float64 GetMO() const;

   //------------------------------------------------------------------------
   // Returns the degree of curvature
   cogoAngle GetDC() const;
   
   //------------------------------------------------------------------------
   // Returns the delta angle
   cogoAngle GetDelta() const;

   //------------------------------------------------------------------------
   // Returns the radius of the curve
   Float64 GetR() const;

   //------------------------------------------------------------------------
   // Returns the direction of the back tangent
   cogoDirection GetBackTangent() const;

   //------------------------------------------------------------------------
   // Returns the direction of the ahead tangent
   cogoDirection GetAheadTangent() const;

   //------------------------------------------------------------------------
   // Returns the direction of the curve
   gpLine2d::Side GetDirection() const;

   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const cogoCurve& rOther);
   void MakeAssignment(const cogoCurve& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   gpPoint2d m_PC;
   gpPoint2d m_PI;
   gpPoint2d m_PT;
   gpPoint2d m_CC;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
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

#endif // INCLUDED_COGO_CURVE_H_

