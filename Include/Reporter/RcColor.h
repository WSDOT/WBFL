///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_RCCOLOR_H_
#define INCLUDED_REPORTER_RCCOLOR_H_
#pragma once

#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

// :WARNING: This doesn't look safe
#define color(a)  new rptRcColor(rptRiStyle::a)

/*****************************************************************************
CLASS 
   rptRcColor

   A class to change the color of the report content stream.


DESCRIPTION
   This class is derived from ReportContent and is to be used for
   manipulating the color of the current report content stream.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 04.11.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcColor : public rptReportContent
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptRcColor(rptRiStyle::FontColor MyColor);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcColor(const rptRcColor& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcColor();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   rptRcColor& operator = (const rptRcColor& rOther);

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Clone thyself
   rptReportContent* CreateClone() const;

   //------------------------------------------------------------------------
   // accept a visitor
   //
   void Accept( rptRcVisitor& MyVisitor );

   // GROUP: ACCESS
   //
   //------------------------------------------------------------------------
   // Get the color
   rptRiStyle::FontColor GetFontColor();

   //------------------------------------------------------------------------
   // Set the color
   void SetFontColor(rptRiStyle::FontColor MyColor);
   //
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Function to aid in copying
   void MakeCopy(const rptRcColor& rOther);

   //------------------------------------------------------------------------
   // Function to aid in assignment
   void MakeAssignment(const rptRcColor& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   //------------------------------------------------------------------------
   // The current color
   rptRiStyle::FontColor m_Color;
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

#endif // INCLUDED_REPORTER_RCCOLOR_H_
