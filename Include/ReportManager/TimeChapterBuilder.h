///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2024  Washington State Department of Transportation
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
#include <ReportManager\ChapterBuilder.h>
#include <System\Time.h>

namespace WBFL
{
   namespace Reporting
   {
      /// A specialized chapter builder that records and displays the amount of time it takes to create a report
      /// This chapter builder may be useful for debugging and improving performance
      /// The chapter should be built using the version of Build that takes the start and end time
      class REPORTMANAGERCLASS TimeChapterBuilder : public ChapterBuilder
      {
      public:
         TimeChapterBuilder() = default;
         virtual ~TimeChapterBuilder() = default;

         virtual LPCTSTR GetName() const override;
         virtual Uint16 GetMaxLevel() const override;
         virtual bool Select() const override;
         /// Builds a dummy chapter without timing information. Use the overloaded Build method
         virtual rptChapter* Build(const std::shared_ptr<const ReportSpecification>& pRptSpec, Uint16 level) const override;

         /// Use this Build method to report timing
         virtual rptChapter* Build(
            WBFL::System::Time& start,  ///< Time when an operation begins
            WBFL::System::Time& end ///< Time whe an operation ends
         ) const;
         virtual std::unique_ptr<ChapterBuilder> Clone() const override;
      };
   };
};
