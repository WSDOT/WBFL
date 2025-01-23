///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2025  Washington State Department of Transportation
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

#pragma once

#include <ReportManager\ReportManagerExp.h>
#include <ReportManager\ReportSpecification.h>
#include <ReportManager\ReportHint.h>
#include <Reporter\Chapter.h>

namespace WBFL
{
   namespace Reporting
   {
      /// A factory class to create a Title Page chapter for a report
      class REPORTMANAGERCLASS TitlePageBuilder  
      {
      public:
	      TitlePageBuilder(LPCTSTR title = _T(""));
	      TitlePageBuilder(const TitlePageBuilder& other) = default;
	      virtual ~TitlePageBuilder() = default;

         /// Sets the title for the title page
         void SetReportTitle(LPCTSTR title);
         
         /// Returns the title
         const std::_tstring& GetReportTitle() const;

         /// Builds the Title Page chapter based on the ReportSpecification
         virtual rptChapter* Build(const std::shared_ptr<const ReportSpecification>& pRptSpec) const = 0;

         /// Returns true if the title page needs to be re-built based on a reporting hint and reporting specification.
         /// Default implementation returns false
         virtual bool NeedsUpdate(const std::shared_ptr<const ReportHint>&, const std::shared_ptr<const ReportSpecification>& pRptSpec) const;

         /// Create a copy of the Title Page object
         virtual std::unique_ptr<TitlePageBuilder> Clone() const = 0;

      private:
         std::_tstring m_Title;
      };
   };
};
