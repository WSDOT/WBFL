///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysExp.h>
#include <System\LogContext.h>
#include <fstream>

namespace WBFL
{
   namespace Debug
   {
      /// Logging context that writes to a file
      class SYSCLASS FileLogContext : public LogContext
      {
      public:
         FileLogContext() = default;
         FileLogContext(const std::_tstring& fname);
         FileLogContext(const FileLogContext&) = delete;
         virtual ~FileLogContext();

         FileLogContext& operator=(const FileLogContext&) = delete;

         virtual LogContext& operator<<(const std::_tstring& s) override;
         virtual LogContext& operator<<(LPCTSTR s) override;
         virtual LogContext& operator<<(TCHAR c) override;    
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

         virtual LogContext& EndLine() override;

         /// Return a reference to an ostream that we can stream to.
         std::_tostream& GetStream();
         operator std::_tostream&();

      private:
#pragma warning ( disable : 4251 ) // m_os is not accessible to clients
         std::_tofstream m_os;
      };
   };
};
