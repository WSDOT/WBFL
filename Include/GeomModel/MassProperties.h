///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
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

#ifndef INCLUDED_GEOMMODEL_MASSPROPERTIES_H_
#define INCLUDED_GEOMMODEL_MASSPROPERTIES_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GeomModel\GeomModelExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   gmMassProperties

   This class encapsulates the mass properties of a section.


DESCRIPTION
   This class encapsulates the mass properties of a section.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 01.06.1998 : Created file
*****************************************************************************/

class GEOMMODELCLASS gmMassProperties
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.  Initializes all the properties to zero.
   gmMassProperties();

   //------------------------------------------------------------------------
   // Explicit constructor.  Initializes the mass per length to mpl.
   gmMassProperties(Float64 mpl);

   //------------------------------------------------------------------------
   // Copy constructor
   gmMassProperties(const gmMassProperties& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~gmMassProperties();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   gmMassProperties& operator = (const gmMassProperties& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // SetMassPerLength
   // Sets the mass per length of the section. Returns the old value.
   Float64 SetMassPerLength(Float64 mpl);

   //------------------------------------------------------------------------
   // MassPerLength
   // Returns the mass per length of the section.
   Float64 MassPerLength() const;

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
   void MakeCopy(const gmMassProperties& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const gmMassProperties& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   Float64  m_Mpl;

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

#endif // INCLUDED_GEOMMODEL_MASSPROPERTIES_H_
