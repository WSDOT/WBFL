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

#ifndef INCLUDED_REPORTER_STYLEHOLDER_H_
#define INCLUDED_REPORTER_STYLEHOLDER_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportItem.h>


/// A style holder can be used as a link in the style chain of responsibility
/// so that styles can be created for abstract collections of report items. An
/// example of this is a holder for the style for all of the cells in a table column.
class REPORTERCLASS rptStyleHolder : public rptReportItem
{
public:
   rptStyleHolder();
   rptStyleHolder(const rptStyleName& MyStyleName);
   rptStyleHolder(const rptStyleHolder& rOther);
   virtual ~rptStyleHolder();

   rptStyleHolder& operator=(const rptStyleHolder& rOther);

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptStyleHolder& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptStyleHolder& rOther);
};

#endif // INCLUDED_REPORTER_STYLEHOLDER_H_
