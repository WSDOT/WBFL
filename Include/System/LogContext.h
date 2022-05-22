///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#pragma once

#include <System\SysExp.h>


namespace WBFL
{
   namespace System
   {
      class SectionValue;
   };

   namespace Debug
   {
      /// Abstract logging context.
      class SYSCLASS LogContext
      {
      public:
         LogContext();
         virtual ~LogContext();

         virtual LogContext& operator<<(const std::_tstring& s) = 0;
         virtual LogContext& operator<<(LPCTSTR s) = 0;
         virtual LogContext& operator<<(TCHAR ch) = 0;
         virtual LogContext& operator<<(DWORD n) = 0;
         virtual LogContext& operator<<(bool n) = 0;
         virtual LogContext& operator<<(Int16 n) = 0;
         virtual LogContext& operator<<(Uint16 n) = 0;
         virtual LogContext& operator<<(Int32 n) = 0;
         virtual LogContext& operator<<(Uint32 n) = 0;
         virtual LogContext& operator<<(Int64 n) = 0;
         virtual LogContext& operator<<(Uint64 n) = 0;
         virtual LogContext& operator<<(Float32 n) = 0;
         virtual LogContext& operator<<(Float64 n) = 0;
         virtual LogContext& operator<<(Float80 n) = 0;
         virtual LogContext& operator<<(void * n) = 0;
         virtual LogContext& operator<<(const WBFL::System::SectionValue& n) = 0;

         virtual LogContext& EndLine() = 0;
      };

      SYSFUNC LogContext& operator<<(LogContext& dc, LogContext& (*pf)(LogContext&));
      SYSFUNC LogContext& endl(LogContext& dmpCtx);
   };
};
