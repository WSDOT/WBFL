///////////////////////////////////////////////////////////////////////
// RC - Reinforced Concrete Section Capacity Analysis Library
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

#ifndef INCLUDED_REINFORCEDCONCRETE_CAPACITYSOLUTION_H_
#define INCLUDED_REINFORCEDCONCRETE_CAPACITYSOLUTION_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <ReinforcedConcrete\ReinfConcExp.h>
#include <GeometricPrimitives\GeometricPrimitives.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rcaCapacitySolution

   This class encapsulates the solution of the reinforced concrete capacity
   problem.


DESCRIPTION
   This class encapsulates the solution of the reinforced concrete capacity
   problem.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 02.05.1998 : Created file
*****************************************************************************/

class REINFCONCCLASS rcaCapacitySolution
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rcaCapacitySolution();

   //------------------------------------------------------------------------
   // Default constructor
   rcaCapacitySolution(Float64 P,
                       Float64 mx,
                       Float64 my,
                       Float64 beta1,
                       const gpLine2d& naLine,
                       Float64 compFiberDist,
                       Float64 compBlockOffset,
                       Float64 areaAboveNeutralAxis,
                       Float64 compBlockArea,
                       Float64 compRes, const gpPoint2d& compResLoc,
                       Float64 tensRes, const gpPoint2d& tensResLoc);

   //------------------------------------------------------------------------
   // Copy constructor
   rcaCapacitySolution(const rcaCapacitySolution& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rcaCapacitySolution();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rcaCapacitySolution& operator = (const rcaCapacitySolution& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // GetNeutralAxis
   // Retreives the position of the neutral axis.
   void GetNeutralAxis(gpLine2d* line) const;
   void SetNeutralAxis(const gpLine2d& line);

   //------------------------------------------------------------------------
   // GetCompressionBlockBoundary
   // Gets the location of the compression block boundary.  The first form 
   // returns the location of the compression block boundary as an offset 
   // from the neutral axis.  The second form returns two points on the 
   // compression block boundary line.
   Float64 GetCompressionBlockBoundary() const;
   void GetCompressionBlockBoundary(gpLine2d* line);
   void SetCompressionBlockBoundary(Float64 compBlockOffset);

   //------------------------------------------------------------------------
   // GetAxialForce
   // Returns the resultant axial force.
   Float64 GetAxialForce() const;
   void SetAxialForce(Float64 p);

   //------------------------------------------------------------------------
   // GetMx
   // Returns the moment capacity for bending about the x axis.
   Float64 GetMx() const;
   void SetMx(Float64 mx);

   //------------------------------------------------------------------------
   // GetMy
   // Returns the moment capacity for bending about the y axis.
   Float64 GetMy() const;
   void SetMy(Float64 my);

   //------------------------------------------------------------------------
   // GetCompFiberDistance
   // Returns the normal distance from the neutral axis to the extreme 
   // concrete compressive fiber.
   Float64 GetCompFiberDistance() const;
   void SetCompFiberDistance(Float64 compFiberDist);

   //------------------------------------------------------------------------
   // GetForceRes
   // Returns the magnitudes of the compressive and tensile force resultants
   // (compRes and tensRes), and their locations (compResLoc and tensResLoc,
   // respectively).
   void GetForceRes(Float64* compRes, gpPoint2d* compResLoc, 
                    Float64* tensRes, gpPoint2d* tensResLoc)const;
   void SetForceRes(Float64 compRes, const gpPoint2d& compResLoc, 
                    Float64 tensRes, const gpPoint2d& tensResLoc);

   //------------------------------------------------------------------------
   // GetBeta1
   // Retreives Beta1 for the rcaCapacityModel associated with this solution.
   Float64 GetBeta1() const;
   void SetBeta1(Float64 beta1);

   //------------------------------------------------------------------------
   // GetAreaAboveNeutralAxis
   // Retreives the area of concrete above the neutral axis.
   Float64 GetAreaAboveNeutralAxis() const;
   void SetAreaAboveNeutralAxis(Float64 areaAboveNeutralAxis);

   //------------------------------------------------------------------------
   // GetCompressionBlockArea
   // Retreives the area of the concrete compression block.
   Float64 GetCompressionBlockArea() const;
   void SetCompressionBlockArea(Float64 compBlockArea);

   //------------------------------------------------------------------------
   // GetCompressionBlockDepth
   // Returns the depth of the compression block.  The compression block depth 
   // is computed as the difference between the distance to the extreme fiber 
   // in compression and the compression block boundary.
   Float64 GetCompressionBlockDepth() const;


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
   //------------------------------------------------------------------------
   void MakeCopy(const rcaCapacitySolution& rOther);

   //------------------------------------------------------------------------
   virtual void MakeAssignment(const rcaCapacitySolution& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   Float64   m_P;
   Float64   m_Mx;
   Float64   m_My;
   Float64   m_Beta1;
   gpLine2d  m_NaLine;
   Float64   m_CompFiberDist;
   Float64   m_CompBlockOffset;
   Float64   m_AreaAboveNeutralAxis;
   Float64   m_CompBlockArea;
   Float64   m_CompRes;
   gpPoint2d m_CompResLoc;
   Float64   m_TensRes;
   gpPoint2d m_TensResLoc;


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

#endif // INCLUDED_REINFORCEDCONCRETE_CAPACITYSOLUTION_H_
