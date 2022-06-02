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

#ifndef INCLUDED_REPORTER_REPORTLAYOUTITEM_H_
#define INCLUDED_REPORTER_REPORTLAYOUTITEM_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportItem.h>

class REPORTERCLASS rptPageLayout;

/// This class has both a report item's style and a page layout
///
/// This class adds page layout properties to the ReportItem class, which already 
/// owns the report item style and can chain responsibility for style.
class REPORTERCLASS rptReportLayoutItem : public rptReportItem
{
public:
   rptReportLayoutItem();

   rptReportLayoutItem( 
      const rptStyleName& rStyleName, ///< style to initialize this item with
      const rptPageLayout& rLayout ///< layout for this item
   );

   rptReportLayoutItem(const rptReportLayoutItem& rOther);

   virtual ~rptReportLayoutItem();

   rptReportLayoutItem& operator = (const rptReportLayoutItem& rOther);

   /// Returns the page layout object. 
   ///
   /// Be very careful in changing the page layout returned from this call because it's gotten from a chain of dependency 
   /// (i.e., you might not know who's page layout your changing!).
   virtual rptPageLayout* GetPageLayout();

   /// Set the page layout
   void SetPageLayout( const rptPageLayout& rPageLayout);

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptReportLayoutItem& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptReportLayoutItem& rOther);

private:
   rptPageLayout* m_pPageLayout;
};

#endif
