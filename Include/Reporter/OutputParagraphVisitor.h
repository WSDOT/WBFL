///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_OUTPUTPARAGRAPHVISITOR_H_
#define INCLUDED_REPORTER_OUTPUTPARAGRAPHVISITOR_H_
#pragma once

#include <ostream>
#include <Reporter\ReporterExp.h>
#include <Reporter\ParagraphVisitor.h>
#include <Reporter\Paragraph.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptOutputParagraphVisitor

   A ReportVisitor specialized to send an ascii report to an ostream


DESCRIPTION
   This class sends a simple ascii representation of a report to a class deriv
   ed from ostream.


   EXAMPLE
      Place examples here.
   END

BUGS
   There are currently no known problems with this class.

LOG
   rdp : 03.25.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptOutputParagraphVisitor : public rptParagraphVisitor
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor
   rptOutputParagraphVisitor(std::_tostream* pMyOstream/*, 
                           const rptUnitSnapShot* MypUnitSnapShot*/)
   {
      m_pOstream = pMyOstream;
      //m_pUnitSnapShot = MypUnitSnapShot;
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptOutputParagraphVisitor();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   virtual void VisitParagraph(rptParagraph*) = 0;
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   std::_tostream* m_pOstream;
   //const rptUnitSnapShot* m_pUnitSnapShot;
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS


   // GROUP: LIFECYCLE

   // Prevent accidental copying and assignment 
   // Default constructor
   rptOutputParagraphVisitor();
   rptOutputParagraphVisitor(const rptOutputParagraphVisitor&);
   rptOutputParagraphVisitor& operator=(const rptOutputParagraphVisitor&) = delete;

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_OUTPUTPARAGRAPHVISITOR_H_
