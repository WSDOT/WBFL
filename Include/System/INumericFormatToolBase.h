///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2020  Washington State Department of Transportation
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

#ifndef INCLUDED_SYSTEM_INUMERICFORMATTOOLBASE_H_
#define INCLUDED_SYSTEM_INUMERICFORMATTOOLBASE_H_
#pragma once

#include <string>
#include <System\SysExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   sysINumericFormatToolBase

   Pure abstract base class that formats numeric values and returns them as strings.  


DESCRIPTION

LOG
   rdp : 11.24.1998 : Created file
*****************************************************************************/

class SYSCLASS sysINumericFormatToolBase
{  
public:
   // GROUP: ENUMERATIONS
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   virtual ~sysINumericFormatToolBase() {}

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Convert a Float64 to a string. That's the main purpose for this class
   virtual std::_tstring AsString(Float64 value) const = 0;

   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
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
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};
// INLINE METHODS
//
// EXTERNAL REFERENCES
//

#endif // INCLUDED_SYSTEM_INUMERICFORMATTOOLBASE_H_
