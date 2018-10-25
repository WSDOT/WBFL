///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#ifndef INCLUDED_REPORTER_HYPERLINKDEFINITION_H_
#define INCLUDED_REPORTER_HYPERLINKDEFINITION_H_
#pragma once

#include <string>
#include <Reporter\ReporterExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptHyperLinkDefinition

   This class defines a hyperlink definition


DESCRIPTION
   This class may be attached to a piece of report content to define the
   content as a hyperlink.


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
   rdp : 05.07.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptHyperLinkDefinition
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor - Must define hyper target.
   rptHyperLinkDefinition(const std::string& HyperTarget);

   //------------------------------------------------------------------------
   // Copy constructor
   rptHyperLinkDefinition(const rptHyperLinkDefinition& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptHyperLinkDefinition();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   rptHyperLinkDefinition& operator = (const rptHyperLinkDefinition& rOther);

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   //
   // Return the target location
   std::string GetTargetName() const;

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const rptHyperLinkDefinition& rOther);
   void MakeAssignment(const rptHyperLinkDefinition& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   // the target that we are linking to
   std::string m_TargetName;

   // GROUP: LIFECYCLE
   // Default constructor - hidden
   rptHyperLinkDefinition();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_HYPERLINKDEFINITION_H_
