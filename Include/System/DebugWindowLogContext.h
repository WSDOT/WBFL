///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <System/SysExp.h>
#include <System/LogContext.h>

namespace WBFL
{
   namespace Debug
   {
      /// Logging context that writes to the debugger window
      class SYSCLASS DebugWindowLogContext : public LogContext
      {
      public:
         DebugWindowLogContext();
         virtual ~DebugWindowLogContext();

         virtual LogContext& operator<<(const std::_tstring& s) override;
         virtual LogContext& operator<<(LPCTSTR s) override;
         virtual LogContext& operator<<(TCHAR ch) override;    
         virtual LogContext& operator<<(DWORD n) override;    
         virtual LogContext& operator<<(bool n) override;
         virtual LogContext& operator<<(Int16 n) override;
         virtual LogContext& operator<<(Uint16 n) override;
         virtual LogContext& operator<<(Int32 n) override;
         virtual LogContext& operator<<(Uint32 n) override;
         virtual LogContext& operator<<(Int64 n) override;
         virtual LogContext& operator<<(Uint64 n) override;
         virtual LogContext& operator<<(Float32 n) override;    
         virtual LogContext& operator<<(Float64 n) override;
         virtual LogContext& operator<<(Float80 n) override;
         virtual LogContext& operator<<(void * n) override;
         virtual LogContext& operator<<(const WBFL::System::SectionValue& n) override;

         virtual LogContext& EndLine();
      };
   };
};
