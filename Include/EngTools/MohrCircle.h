///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
// Copyright © 1999-2015  Washington State Department of Transportation
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

#ifndef INCLUDED_ENGTOOLS_MOHRCIRCLE_H_
#define INCLUDED_ENGTOOLS_MOHRCIRCLE_H_
#pragma once

// SYSTEM INCLUDES
//
#include <EngTools\EngToolsExp.h>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   etMohrCircle

   Mohr's circle


DESCRIPTION
   Mohr's Circle.

REFERENCES
   Advanced Strength and Applied Elasticity
   A.C. Ugural & S. K. Fenster


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.16.1997 : Created file
*****************************************************************************/

class ENGTOOLSCLASS etMohrCircle
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor. Sets center and radius to 0.
   etMohrCircle();

   //------------------------------------------------------------------------
   // Constructs a mohr's circle for a give state of stress/strain.
   etMohrCircle(Float64 sii,Float64 sjj,Float64 sij);

   //------------------------------------------------------------------------
   // Copy constructor
   etMohrCircle(const etMohrCircle& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~etMohrCircle();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   etMohrCircle& operator = (const etMohrCircle& rOther);

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Computes the state of strains/stresses/etc. on a plane defined by
   // angle.  If bSysUnits is true, angle is considered to be in
   // system units, otherwise it is taken to be in radians. Angle is measured
   // counterclockwise from the global X direction.
   void ComputeState(Float64* pSii,Float64* pSjj, Float64* pSij,Float64 angle,bool bSysUnits = true);

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Get sii
   Float64 GetSii() {return m_Sii;}

   //------------------------------------------------------------------------
   // Get sjj
   Float64 GetSjj() {return m_Sjj;}

   //------------------------------------------------------------------------
   // Get sij
   Float64 GetSij() {return m_Sij;}

   //------------------------------------------------------------------------
   // Set sii
   void SetSii(Float64 sii);

   //------------------------------------------------------------------------
   // Set sjj
   void SetSjj(Float64 sjj);

   //------------------------------------------------------------------------
   // Set sij
   void SetSij(Float64 sij);

   //------------------------------------------------------------------------
   // Returns the maximum principle value.
   Float64 GetSmax() const;
   
   //------------------------------------------------------------------------
   // Returns the minimum principle value.
   Float64 GetSmin() const;
   
   //------------------------------------------------------------------------
   // Returns the maximum "shear" value.
   Float64 GetTmax() const;

   //------------------------------------------------------------------------
   // Returns the direction of the principle axis measured counterclockwise
   // from the global X axis. If bSysUnits is true, it is returned in system
   // units, otherwise it is returned in radians.
   Float64 GetPrincDirection(bool bSysUnits = true) const;

   //------------------------------------------------------------------------
   // Returns the center point of the mohr's circle.
   Float64 GetCenter() const;

   //------------------------------------------------------------------------
   // Returns the radius of the mohr's circle.
   Float64 GetRadius() const;

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
   static bool TestMe();
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const etMohrCircle& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const etMohrCircle& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   Float64 m_Sii;  // input variables
   Float64 m_Sjj;
   Float64 m_Sij;

   Float64 m_Smin;
   Float64 m_Smax;
   // Note: Internal principle angle is stored in clockwise direction.
   Float64 m_Angle;
   Float64 m_Radius;
   Float64 m_Center;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_ENGTOOLS_MOHRCIRCLE_H_
