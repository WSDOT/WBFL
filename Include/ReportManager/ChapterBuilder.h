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

class rptChapter;

namespace WBFL
{
   namespace Reporting
   {
      /// Abstract factory to create rptChapter objects
      class REPORTMANAGERCLASS ChapterBuilder  
      {
      public:
	      ChapterBuilder() = default;
	      virtual ~ChapterBuilder() = default;

         /// Returns a key used to search for this chapter builder. Calls GetName() by default.
         virtual LPCTSTR GetKey() const;

         /// Returns the chapter name
         virtual LPCTSTR GetName() const = 0;

         /// Returns the maximum output level supported by this chapter
         virtual Uint16 GetMaxLevel() const = 0;

         /// Return true if this chapter is to be selected by default
         virtual bool Select() const = 0;

         /// Builds the chapter based on the reporting specification and output level
         virtual rptChapter* Build(const std::shared_ptr<const ReportSpecification>& pRptSpec,Uint16 level) const = 0;

         /// Creates a clone this chapter builder
         virtual std::unique_ptr<ChapterBuilder> Clone() const = 0;

         /// Returns true if the chapter needs to be re-built based on a reporting hint, reporting specification, and output level.
         /// Default implementation returns false
         virtual bool NeedsUpdate(const std::shared_ptr<const ReportHint>& pHint, const std::shared_ptr<const ReportSpecification>& pRptSpec,Uint16 level) const;
      };
   };
};
