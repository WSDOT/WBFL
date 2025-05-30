///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysExp.h>
#include <strstream>

namespace WBFL
{
   namespace System
   {
      class SYSCLASS Logger
      {
      public:
         enum class Severity
         {
            Debug,   ///< Debugging and diagnostic message
            Info,    ///< General informational message
            Warning, ///< Warning of possible issue
            Error    ///< Something has gone wrong
         };

         /// @brief Sets the output stream for logging
         /// @param stream 
         static void SetOutput(std::ostream* stream);

         /// @brief Sets the logging verbosity. Any messages with a Severity at this level or greater are logged.
         /// @param verbosity 
         static void Verbosity(Severity verbosity);

         /// @brief Returns the current logging verbosity
         /// @return 
         static Severity Verbosity();

         /// @brief Returns the maximum severity logged
         /// @return 
         static Severity MaxVerbosity();

         static void Message(Severity type, const std::wstring& message);
         static void Info(const std::wstring& message) { Message(Severity::Info, message); }
         static void Debug(const std::wstring& message) { Message(Severity::Debug, message); }
         static void Warning(const std::wstring& message) { Message(Severity::Warning, message); }
         static void Error(const std::wstring& message) { Message(Severity::Error, message); }

         static void Message(Severity type, const std::string& message);
         static void Info(const std::string& message) { Message(Severity::Info, message); }
         static void Debug(const std::string& message) { Message(Severity::Debug, message); }
         static void Warning(const std::string& message) { Message(Severity::Warning, message); }
         static void Error(const std::string& message) { Message(Severity::Error, message); }

      private:
         static std::ostream* log;

         static Severity verbosity;
         static Severity max_severity;
      };
   };
};
