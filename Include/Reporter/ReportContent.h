///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

#if !defined INCLUDED_REPORTER_REPORTCONTENT_H_
#define INCLUDED_REPORTER_REPORTCONTENT_H_

#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportItem.h>

class REPORTERCLASS rptRcVisitor;
class REPORTERCLASS rptHyperLinkDefinition;

/// This abstract class represents the content of a report. 
///
/// This class is an abstract base class representing the low-level content that makes up a report (e.g., strings, paragraphs, font control, numbers...)
class REPORTERCLASS rptReportContent : public rptReportItem
{
public:
   rptReportContent();
   rptReportContent(const rptReportContent& rOther);
   virtual ~rptReportContent();

   virtual rptReportContent& operator=(const rptReportContent& rOther);

   /// Returns true if this report content a hyperlink
   bool IsHyperLink() const;

   /// Returns the hyperlink target
   const std::_tstring& GetHyperTarget() const;

   /// Makes this report content a hyperlink and point it to HyperTarget
   void SetHyperLink(const std::_tstring& HyperTarget);

   /// Accepts a visitor and calls VisitReportContent(this)
   virtual void Accept( rptRcVisitor& MyVisitor ) = 0;

   /// Creates a clone
   virtual rptReportContent* CreateClone() const = 0;
 
protected:
   /// pointer to hypertext link information. Pointer is non-null if this piece of report content is a hyperlink
   rptHyperLinkDefinition* m_pHyperLink;

   /// Copies the content from rOther to this object
   void MakeCopy(const rptReportContent& rContent);

   /// Assigns the content from oOther to this object
   virtual void MakeAssignment(const rptReportContent& rOther);
};

#endif // INCLUDED_REPORTER_REPORTCONTENT_H_
