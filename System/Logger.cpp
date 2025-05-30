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

#include <System\SysLib.h>
#include <System\Logger.h>
#include <sstream>
#include <array>
#include <atlconv.h>
#include <ctime>
#include <iomanip>

// Implementation note: There are dual versions of the logging functions based on character/string type
// This is because most of our system uses unicode strings but exceptions (what() method) only have
// an ascii string version.

using namespace WBFL::System;

std::ostream* Logger::log = nullptr;
Logger::Severity Logger::verbosity = Logger::Severity::Info;
Logger::Severity Logger::max_severity = Logger::Severity::Info;

const std::array<std::string, 4> severity_strings{ "Debug", "Info", "Warning", "Error"};

constexpr auto operator+(Logger::Severity type) noexcept
{
   return std::underlying_type<Logger::Severity>::type(type);
}

std::string get_time()
{
   std::ostringstream os;
   time_t now = time(nullptr);
   os << std::put_time(localtime(&now), "%F %T");
   return os.str();
}

void plain_text_message(std::ostream& out, Logger::Severity type, const std::string& message)
{
   out << "[" << severity_strings[+type] << "] ";
   out << "[" << get_time().c_str() << "] ";
   out << message.c_str() << std::endl;
}

void Logger::SetOutput(std::ostream* stream1)
{
   log = stream1;
}

void Logger::Verbosity(Severity v)
{
   verbosity = v;
}

Logger::Severity Logger::Verbosity()
{
   return verbosity;
}

Logger::Severity Logger::MaxVerbosity()
{
   return max_severity;
}

void Logger::Message(Logger::Severity type, const std::wstring& message)
{
   if (type < verbosity) 
   {
      // skip lower level messages
      return;
   }

   if (max_severity < type) {
      max_severity = type;
   }

   if (log != nullptr)
   {
      USES_CONVERSION;
      plain_text_message(*log, type, T2A(message.c_str()));
   }
}

void Logger::Message(Logger::Severity type, const std::string& message)
{
   if (type < verbosity) {
      return;
   }

   if (max_severity < type) {
      max_severity = type;
   }

   if (log != nullptr)
      plain_text_message(*log, type, message);
}
