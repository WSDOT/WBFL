///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#ifndef INCLUDED_REPORTER_RCUNSIGNED_H_
#define INCLUDED_REPORTER_RCUNSIGNED_H_
#pragma once

// SYSTEM INCLUDES
//
#include <sstream>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRcUnsigned

   Unsigned Report Content Class


DESCRIPTION
   This class is used to stream unsigned data to the report paragraphs. It is derived 
   from the generic ReportContent class.


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
   rdp : 04.11.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcUnsigned : public rptReportContent
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptRcUnsigned(Uint64 MyVal=0);

   //------------------------------------------------------------------------
   // Constructor with HyperLink
   rptRcUnsigned(Uint64 MyVal, const std::_tstring& HyperTarget);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcUnsigned(const rptRcUnsigned& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcUnsigned();

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   // Assignment operator
   // Returns reference to itself
   rptRcUnsigned& operator = (const rptRcUnsigned& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Create a type-safe clone
   rptReportContent* CreateClone() const;

   //------------------------------------------------------------------------
   // accept a visitor
   void Accept( rptRcVisitor& MyVisitor );

   //------------------------------------------------------------------------
   // stream the value only into to paragraph stream
   rptRcUnsigned* Sv(Uint64 Myint);

   //------------------------------------------------------------------------
   // Get the integer value
   Uint64 GetVal();

   //------------------------------------------------------------------------
   // Set the integer value
   void SetVal(Uint64 MyInt);

   //------------------------------------------------------------------------
   // Get the number of characters that the int is to fit in. The purpose
   // of the width option is to allow values to be printed like: 007 (i.e., the
   // int value is left-padded with zeros to fit into the width.
   Int32 GetWidth();

   //------------------------------------------------------------------------
   // Set the number of characters that the int is to fit in.
   void SetWidth(Int32 MyWidth);

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const rptRcUnsigned& rOther);
   virtual void MakeAssignment(const rptRcUnsigned& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   //------------------------------------------------------------------------
   // The unsigned value
   Uint64 m_TheUnsigned;
   //------------------------------------------------------------------------
   // Field width for value
   Int32 m_Width;

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

#endif // RcUnsigned_H_
