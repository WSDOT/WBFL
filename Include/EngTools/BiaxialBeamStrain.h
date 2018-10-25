///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
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

#ifndef INCLUDED_ENGTOOLS_BIAXIALBEAMSTRAIN_H_
#define INCLUDED_ENGTOOLS_BIAXIALBEAMSTRAIN_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <EngTools\EngToolsExp.h>
#include <GeometricPrimitives\GeometricPrimitives.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class gpLine2d;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   etBiaxialBeamStrain

   This class represents a beam strain plane in x-y space


DESCRIPTION
   This class represents a strain plane for a cross sectional shape. 


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
   rdp : 07.23.1997 : Created file
*****************************************************************************/

class ENGTOOLSCLASS etBiaxialBeamStrain
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor; - set constant value strain
   etBiaxialBeamStrain(Float64 strain=0.0);


   //------------------------------------------------------------------------
   // Constructor
   // set strain values at three arbitrary points
   etBiaxialBeamStrain(const gpPoint2d& p1, Float64 s1, 
                       const gpPoint2d& p2, Float64 s2,
                       const gpPoint2d& p3, Float64 s3);

   //------------------------------------------------------------------------
   // Constructor
   // rnaLine describes the neutral axis.
   // p3 is a point away from the n.a. which has a known strain value.
   etBiaxialBeamStrain(const gpLine2d& rnaLine,
                       const gpPoint2d& p3,Float64 strain);

   //------------------------------------------------------------------------
   // Constructor
   // rnaLine describes the neutral axis.
   // dist is the distance measured normal from and Left of the n.a. to the
   // location of the strain value.
   etBiaxialBeamStrain(const gpLine2d& rnaLine,
                       Float64 dist, Float64 strain);

   //------------------------------------------------------------------------
   // Copy constructor
   etBiaxialBeamStrain(const etBiaxialBeamStrain& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~etBiaxialBeamStrain();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   etBiaxialBeamStrain& operator = (const etBiaxialBeamStrain& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Get the axial strain at given coordinates
   virtual Float64 GetAxialStrain(Float64 x, Float64 y) const;

   //------------------------------------------------------------------------
   // Get the axial strain at a point
   virtual Float64 GetAxialStrain(const gpPoint2d& pnt) const;

   //------------------------------------------------------------------------
   // Get the X location of a strain value for a given Y
   // You should always check to success flag to make sure that a valid location
   // was found
   virtual Float64 GetXStrainLocation(Float64 Strain, Float64 Y, bool& success);

   //------------------------------------------------------------------------
   // Get the Y location of a strain value for a given X
   // You should always check to success flag to make sure that a valid location
   // was found
   virtual Float64 GetYStrainLocation(Float64 Strain, Float64 X, bool& success);

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Set the strain plane to a new orientation.
   void SetStrainPlane(const gpLine2d& rnaLine,
                       const gpPoint2d& p3,Float64 strain);

   //------------------------------------------------------------------------
   // Set the strain plane to a new orientation.
   void SetStrainPlane(const gpPoint2d& p1, Float64 s1, 
                       const gpPoint2d& p2, Float64 s2,
                       const gpPoint2d& p3, Float64 s3);

   //------------------------------------------------------------------------
   // Set the strain plane to a new orientation.
   void SetStrainPlane(const gpLine2d& rnaLine,
                       Float64 dist, Float64 strain);

   //------------------------------------------------------------------------
   // Set the strain plane to a constant value
   void SetStrainPlane(Float64 strain);

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
   void Update(const gpPoint2d& p1, Float64 s1, 
               const gpPoint2d& p2, Float64 s2,
               const gpPoint2d& p3, Float64 s3);
   // GROUP: OPERATIONS
   void MakeCopy(const etBiaxialBeamStrain& rOther);
   void MakeAssignment(const etBiaxialBeamStrain& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   Float64 m_A;
   Float64 m_B;
   Float64 m_C;
   Float64 m_D;
   bool    m_IsConstantStrain;

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

#endif //INCLUDED_ENGTOOLS_BIAXIALBEAMSTRAIN_H_
