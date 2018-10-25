///////////////////////////////////////////////////////////////////////
// Roark - Simple span beam forumla, patterned after Roark's formulas
//         for Stress and Strain
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_ROARK_UNITTEST_H_
#define INCLUDED_ROARK_UNITTEST_H_
#pragma once

#include <Roark\RoarkExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rkUnitTest

   Unit Testing class for the Roark package.


DESCRIPTION
   Unit Testing class for the Roark package.


COPYRIGHT
   Copyright © 1997-1998
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 10.21.1998 : Created file
*****************************************************************************/

class ROARKCLASS rkUnitTest
{
public:
   // GROUP: LIFECYCLE


   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   static bool TestMe(dbgLog& rlog);
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   rkUnitTest(const rkUnitTest&);
   rkUnitTest& operator=(const rkUnitTest&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

public:
   // GROUP: DEBUG
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//


#endif // INCLUDED_ROARK_UNITTEST_H_
