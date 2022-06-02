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

#ifndef INCLUDED_REPORTER_RCHYPERTARGET_H_
#define INCLUDED_REPORTER_RCHYPERTARGET_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>
#include <string>


/// Report content that defines a target to a hyperlink
class REPORTERCLASS rptRcHyperTarget : public rptReportContent
{
public:
   rptRcHyperTarget
   (
      const std::_tstring& YourTarget ///< The target name
   );

   rptRcHyperTarget(const rptRcHyperTarget& rRcHyperTarget);

   virtual ~rptRcHyperTarget();

   rptRcHyperTarget& operator=(const rptRcHyperTarget& rRcHyperTarget);

   /// Creates a clone
   rptReportContent* CreateClone() const;

   /// Accepts a visitor and calls VisitRcHyperTarget(this)
   void Accept( rptRcVisitor& MyVisitor );

   /// Returns the hyperlink target name
   const std::_tstring& GetTargetName() const {return m_TheTarget; }

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRcHyperTarget& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptRcHyperTarget& rOther);

private:
   std::_tstring m_TheTarget;

   rptRcHyperTarget() = delete;
};

#endif // INCLUDED_REPORTER_RCHYPERTARGET_H_
