///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_RCFLOWMODIFIER_H_
#define INCLUDED_REPORTER_RCFLOWMODIFIER_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>
#include <Reporter\ReportingUtils.h>
#include <string>

/// Report Content that changes the flow of a report such as newlines, newpages and tabs.
///
/// The class inherits from report content and its insertion in the report stream signals 
/// a change in the report flow. Currently supported functions are line breaks, page breaks, and tabs.
class REPORTERCLASS rptRcFlowModifier : public rptReportContent
{
public:

   /// types for changing document flow
   enum FlowModifier  
   { 
      NEW_LINE,  ///< Insert a new line
      NEW_PAGE,  ///< Insert a page break
      TAB ///< Insert a tab
   };

   rptRcFlowModifier(
      FlowModifier ModifierType,  ///< The flow modifier type
      Uint16 nRepeat=1 ///< Number of times to repeat the flow modifier
   );

   rptRcFlowModifier(const rptRcFlowModifier& rOther);
   virtual ~rptRcFlowModifier();

   rptRcFlowModifier& operator=(const rptRcFlowModifier& rOther);

   /// Returns the modifier type
   FlowModifier GetModifierType() const {return m_ModifierType;}

   /// Returns the repeat count
   Uint16 GetRepeatCount() const {return m_nRepeat;}

   /// Creates a clone
   rptReportContent* CreateClone() const;

   /// Accept a visitor and calls VisitRcFlowModifier(this)
   void Accept( rptRcVisitor& MyVisitor )
   {
      MyVisitor.VisitRcFlowModifier(this);
   }

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRcFlowModifier& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptRcFlowModifier& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   FlowModifier m_ModifierType;
   Uint16     m_nRepeat;
};

/// Line break factory that creates rptRcFlowModifier initialized to create a line break
class REPORTERCLASS rptLineBreakFactory
{
public:
   /// Creates the rptRcFlowModifier
   operator rptReportContent*();
};

/// Adds a line break to a report
///
///    *pPara << _T("Some Text") << rptNewLine;
#define rptNewLine rptLineBreakFactory()

/// Page break factory that creates rptRcFlowModifier initialized to create a page break
class REPORTERCLASS rptPageBreakFactory
{
public:
   /// Creates the rptRcFlowModifier
   operator rptReportContent*();
};

/// Adds a page break to a report
///
///    *pPara << rptNewPage;
#define rptNewPage rptPageBreakFactory()

/// Tab factory that creates rptRcFlowModifier initialized to create a tab
class REPORTERCLASS rptHardTabFactory
{
public:
   /// Creates the rptRcFlowModifier
   operator rptReportContent*();
};

/// Adds a tab break to a report
///
///    *pPara << rptTab << rptTab << _T("Some Text") << rptNewLine;
#define rptTab rptHardTabFactory()

#endif
