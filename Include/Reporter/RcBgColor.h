///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#ifndef INCLUDED_REPORTER_rptRcBgColor_H_
#define INCLUDED_REPORTER_rptRcBgColor_H_
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
#define bgcolor(a)  new rptRcBgColor(rptRiStyle::a)

/*****************************************************************************
CLASS 
   rptRcBgColor

   A class to change the background color of the report content stream.


DESCRIPTION
   This class is derived from ReportContent and is to be used for
   manipulating the color of the current report content stream.

LOG
   rdp : 02.22.2020 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcBgColor : public rptReportContent
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptRcBgColor(rptRiStyle::FontColor MyColor);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcBgColor(const rptRcBgColor& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcBgColor();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   rptRcBgColor& operator = (const rptRcBgColor& rOther);

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
   rptRiStyle::FontColor GetColor();

   //------------------------------------------------------------------------
   // Set the color
   void SetColor(rptRiStyle::FontColor MyColor);
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
   void MakeCopy(const rptRcBgColor& rOther);

   //------------------------------------------------------------------------
   // Function to aid in assignment
   void MakeAssignment(const rptRcBgColor& rOther);

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

#endif // INCLUDED_REPORTER_rptRcBgColor_H_
