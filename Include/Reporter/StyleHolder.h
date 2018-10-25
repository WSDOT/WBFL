///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_STYLEHOLDER_H_
#define INCLUDED_REPORTER_STYLEHOLDER_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportItem.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptStyleHolder

   This class creates a "do nothing" concrete version of ReportItem that may
   be used as a holder for styles.


DESCRIPTION
   A StyleHolder can be used as a link in the style chain of responsibility
   so that styles can be created for abstract collections of report items. An
   example of this is a holder for the style for all of the cells in a table
   column.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 04.30.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptStyleHolder : public rptReportItem
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptStyleHolder();

   //------------------------------------------------------------------------
   // Constructor with style
   rptStyleHolder(const rptStyleName& MyStyleName);

   //------------------------------------------------------------------------
   // Copy constructor
   rptStyleHolder(const rptStyleHolder& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptStyleHolder();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   rptStyleHolder& operator = (const rptStyleHolder& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const rptStyleHolder& rOther);
   void MakeAssignment(const rptStyleHolder& rOther);

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

#endif // INCLUDED_REPORTER_STYLEHOLDER_H_
