///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

struct eafTypes
{
   typedef enum UnitMode
   {
      umSI = 1,
      umUS = 2
   } UnitMode;

   // Status Item Severity Type
   typedef enum StatusSeverityType
   {
      statusInformation,
      statusWarning,
      statusError
   } StatusSeverityType;

   typedef enum LpFrameMode
   { 
      lpfOn, 
      lpfOff
   } LpFrameMode;

   typedef enum CustomReportError {
      creParentMissingAtLoad,   // Parent for custom missing at program load time
      creParentMissingAtImport, // Parent for custom missing when importing
      creChapterMissingAtLoad,
      creChapterMissingAtImport
   } CustomReportError;

   typedef enum CustomReportHelp
   {
      crhCustomReport,
      crhFavoriteReport
   } CustomReportHelp;

   typedef enum HttpGetResult
   {
      hgrOk,
      hgrInvalidUrl,
      hgrConnectionError,
      hgrNotFound
   } HttpGetResult;

   typedef enum HelpResult
   {
      hrOK,
      hrDocSetNotFound,
      hrTopicNotFound
   } HelpResult;
};

typedef IDType StatusGroupIDType;
typedef IDType StatusCallbackIDType;
typedef IDType StatusItemIDType;
