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

#ifndef INCLUDED_REPORTER_OUTPUTRCVISITOR_H_
#define INCLUDED_REPORTER_OUTPUTRCVISITOR_H_
#pragma once

#include <ostream>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportingUtils.h>
#include <Reporter\RcVisitor.h>
#include <Reporter\RcSymbol.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptOutputRcVisitor

   An abstract ReportVisitor specialized to send report content to an ostream


DESCRIPTION
   This abstract class helps set up needed data to send report content to a class 
   derived from ostream.


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
   rdp : 03.25.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptOutputRcVisitor : public rptRcVisitor
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // constructor
   rptOutputRcVisitor(std::ostream* pMyOstream);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptOutputRcVisitor();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   std::ostream* m_pOstream;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // get a roman sybol equivalent for a greek symbol
   virtual Uint8 GetRomanForGreek(rptRcSymbol::SymbolType sym);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment
   rptOutputRcVisitor();
   rptOutputRcVisitor(const rptOutputRcVisitor&);
   rptOutputRcVisitor& operator=(const rptOutputRcVisitor&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_OUTPUTRCVISITOR_H_
