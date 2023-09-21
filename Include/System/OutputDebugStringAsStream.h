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


#include <sstream>
#include <Windows.h>

namespace WBFL
{
   namespace Debug
   {
      namespace
      {
         template<class CharT, class TraitsT = std::char_traits<CharT>>
         class basic_debugbuf : public std::basic_stringbuf<CharT, TraitsT>
         {
         public:
            virtual ~basic_debugbuf() { sync(); }

         protected:
            int sync()
            {
               output_debug_string(this->str().c_str());
               this->str(std::basic_string<CharT>()); // cear the string buffer
               return 0;
            }

            void output_debug_string(const CharT* text) {}
         };


         template<>
         void basic_debugbuf<char>::output_debug_string(const char* text)
         {
            ::OutputDebugStringA(text);
         }

         template<>
         void basic_debugbuf<wchar_t>::output_debug_string(const wchar_t* text)
         {
            ::OutputDebugStringW(text);
         }
      }

      /// Class that allows the Windows OutputDebugString function, which writes text to the Debugger Output Window,
      /// to be treated as a std::ostream.
      /// 
      /// The implementation of this class is based on the example found at
      /// https://gist.github.com/comargo/f7fe244e539325cef0f66704b58dc35a
      /// 
      /// Example
      /// ~~~
      /// WBFL::Debug::dostream debug_stream;
      /// Logger::SetOutput(&debug_stream);
      /// Logger::LogMessage("Error Message"); // the string is written to the debugger output window
      /// debug_stream << "A differement message" << std::endl; // this string is written to the debugger output window too
      /// ~~~
      template<class CharT, class TraitsT = std::char_traits<CharT>>
      class basic_dostream : public std::basic_ostream<CharT, TraitsT>
      {
      public:
         basic_dostream() : std::basic_ostream<CharT, TraitsT>(new basic_debugbuf<CharT, TraitsT>())
         {
         }

         ~basic_dostream()
         {
            delete this->rdbuf();
         }
      };

      SYSTPL basic_dostream<char>;
      using dostream = basic_dostream<char>;

      SYSTPL basic_dostream<wchar_t>;
      using wdostream = basic_dostream<wchar_t>;
   }
}