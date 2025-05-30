///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

#include <WBFLTypes.h>

namespace WBFL
{
   namespace EAF
   {
      enum class UnitMode
      {
         SI = 1,
         US = 2
      };
      inline constexpr auto operator+(UnitMode t) noexcept { return std::underlying_type<UnitMode>::type(t); }

      enum class StatusSeverityType
      {
         Information,
         Warning,
         Error
      };
      inline constexpr auto operator+(StatusSeverityType t) noexcept { return std::underlying_type<StatusSeverityType>::type(t); }

      enum class LpFrameMode
      {
         On,
         Off
      };

      enum class CustomReportError 
      {
         ParentMissingAtLoad,   // Parent for custom missing at program load time
         ParentMissingAtImport, // Parent for custom missing when importing
         ChapterMissingAtLoad,
         ChapterMissingAtImport
      };

      enum class CustomReportHelp
      {
         CustomReport,
         FavoriteReport
      };

      enum class HttpGetResult
      {
         Ok,
         InvalidUrl,
         ConnectionError,
         NotFound
      };

      enum class HelpResult
      {
         OK,
         DocSetNotFound,
         TopicNotFound
      };

      // Return values from EAFShowStatusMessage
      enum class StatusItemDisplayReturn
      {
         Close,   // dialog closed without doing anything
         Remove,  // dialog closed after removing status item
         Edit     // dialog closed 
      };

   };
};

using StatusGroupIDType = IDType;
using StatusCallbackIDType = IDType;
using StatusItemIDType = IDType;

