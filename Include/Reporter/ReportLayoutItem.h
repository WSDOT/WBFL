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

#ifndef INCLUDED_REPORTER_REPORTLAYOUTITEM_H_
#define INCLUDED_REPORTER_REPORTLAYOUTITEM_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportItem.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class REPORTERCLASS rptPageLayout;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptReportLayoutItem

   This class has both a report item's style and a page layout


DESCRIPTION
   This class adds page layout properties to the ReportItem class, which already 
   owns the report item style and can chain responsibility for style.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 03.28.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptReportLayoutItem : public rptReportItem
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptReportLayoutItem();

   //------------------------------------------------------------------------
   // construct with custom style and layout
   rptReportLayoutItem( const rptStyleName& rStyleName, const rptPageLayout& rLayout);

   //------------------------------------------------------------------------
   // Copy constructor
   rptReportLayoutItem(const rptReportLayoutItem& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptReportLayoutItem();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   // Returns reference to itself
   rptReportLayoutItem& operator = (const rptReportLayoutItem& rOther);

   // GROUP: OPERATIONS
   //
   //------------------------------------------------------------------------
   // access to my page layout. Be very careful in changing the page layout
   // returned from this call because it's gotten from a chain of dependency 
   // (i.e., you might not know who's page layout your changing!).
   //
   virtual rptPageLayout* GetpPageLayout();

   //------------------------------------------------------------------------
   // set my page layout
   void SetPageLayout( const rptPageLayout& rPageLayout);

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   void MakeCopy(const rptReportLayoutItem& rOther);
   void MakeAssignment(const rptReportLayoutItem& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   //
   //------------------------------------------------------------------------
   // my page layout
   rptPageLayout* m_pPageLayout;

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

#endif
