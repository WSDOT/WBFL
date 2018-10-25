///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#ifndef INCLUDED_REPORTER_RCFLOWMODIFIER_H_
#define INCLUDED_REPORTER_RCFLOWMODIFIER_H_
#pragma once

#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>
#include <Reporter\ReportingUtils.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS

/*****************************************************************************
CLASS 
   rptRcFlowModifier

   Report Content that changes the flow of a report such as newlines newpages and tabs.


DESCRIPTION
   The class inherits from report content and its insertion in the report stream signals 
   a change in the report flow. Currently supported functions are line breaks, page breaks,
   and tabs.


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
   rdp : 04.09.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcFlowModifier : public rptReportContent
{
public:

   //------------------------------------------------------------------------
   // types for changing document flow
   enum FlowModifier  { NEW_LINE, NEW_PAGE, TAB};

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Constructor: Set flow modifier type and number of times it is to be
   // repeated
   rptRcFlowModifier(FlowModifier ModifierType, Uint16 NumTimes=1);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcFlowModifier(const rptRcFlowModifier& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcFlowModifier();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   // Returns reference to itself
   rptRcFlowModifier& operator = (const rptRcFlowModifier& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Get the modifier type
   FlowModifier GetModifierType() {return m_ModifierType;}

   //------------------------------------------------------------------------
   // Get the number of times to apply the modifier
   Uint16 GetNumberOfTimes() {return m_NumTimes;}

   //------------------------------------------------------------------------
   // create a type-correct clone
   rptReportContent* CreateClone() const;

   //------------------------------------------------------------------------
   // Accept a report content visitor
   void Accept( rptRcVisitor& MyVisitor )
   {
      MyVisitor.VisitRcFlowModifier(this);
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   // Function to aid in copying
   void MakeCopy(const rptRcFlowModifier& rOther);
   //------------------------------------------------------------------------
   // Function to aid in assignment
   void MakeAssignment(const rptRcFlowModifier& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   //------------------------------------------------------------------------
   // Type of this flow modifier
   FlowModifier m_ModifierType;
   //------------------------------------------------------------------------
   // Number of times modifier is to be applied
   Uint16     m_NumTimes;
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

class REPORTERCLASS rptLineBreak
{
public:
   operator rptReportContent*();
};
#define rptNewLine rptLineBreak()

class REPORTERCLASS rptPageBreak
{
public:
   operator rptReportContent*();
};
#define rptNewPage rptPageBreak()

class REPORTERCLASS rptHardTab
{
public:
   operator rptReportContent*();
};
#define rptTab rptHardTab()

#endif
