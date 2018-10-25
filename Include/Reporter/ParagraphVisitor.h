///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#ifndef INCLUDED_REPORTER_PARAGRAPHVISITOR_H_
#define INCLUDED_REPORTER_PARAGRAPHVISITOR_H_
#pragma once

#include <Reporter\ReporterExp.h>

//
// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class REPORTERCLASS rptParagraph;


// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptParagraphVisitor

   Abstract class to visit all objects in a paragraph. 

DESCRIPTION
   Visits all report content in a paragraph for a purpose.

   EXAMPLE
      Place examples here.
   END

BUGS
   There are currently no known problems with this class.

KEYWORDS
   Reporter

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class REPORTERCLASS rptParagraphVisitor
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptParagraphVisitor();

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptParagraphVisitor();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Visit a paragraph
   virtual void VisitParagraph(rptParagraph*)=0;
   // GROUP: OPERATIONS
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

   // Prevent accentidal copying and assignment
   //------------------------------------------------------------------------
   // Cant make copies
   rptParagraphVisitor(const rptParagraphVisitor&);
   //------------------------------------------------------------------------
   // Assignment is private
   rptParagraphVisitor& operator=(const rptParagraphVisitor&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_PARAGRAPHVISITOR_H_
