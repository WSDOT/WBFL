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

#include <System\SysExp.h>
#include <string>
#include <sstream>

#undef THROW
#undef THROW_EX
#if defined _DEBUG
// debug bug version breaks with an assert before throwing
#define THROW(ex,code)          {ASSERT(false); throw ex(ex::code, _T(__FILE__), __LINE__ );}
#define THROW_EX(ex,code,extra) {ASSERT(false); throw ex(ex::code,extra,_T(__FILE__),__LINE__);}
#else
#define THROW(ex,code)          {throw ex(ex::code, _T(__FILE__), __LINE__ );}
#define THROW_EX(ex,code,extra) {throw ex(ex::code,extra,_T(__FILE__),__LINE__);}
#endif // _DEBUG

namespace WBFL
{
   namespace System
   {
      // Implementation note - not deriving from std::exception because it's "what" function requires a constant string
      // when the exception object is initialized. WBFL exceptions have a message string that is built up from information
      // provided to the exception including the filename and line number from where the exception originated.

      /// Base class for all WBFL exceptions.
      class SYSCLASS XBase
      {
      public:
         XBase() = default;
         XBase(const std::_tstring& file, Uint32 line);
         XBase(const XBase&) = default;
         virtual ~XBase();

         XBase& operator=(const XBase&) = default;

         /// Throws this exception object.  This throw differs from a standard C++
         /// throw in that the object thrown is a clone based on the dynamic type
         /// of the object.  The standard C++ throw throws a clone based on an
         /// object's static type,  thereby slicing the object and losing specific
         /// error information contained within the subclass.
         ///
         /// All classes derived from sysXBase must implement this method as follows:
         /// void myClass::Throw() const { throw *static_cast<const myClass*>(this); }
         virtual void Throw() const = 0;

         /// Returns a reason code for the exception.  Concrete classes derived
         /// from XBase must provide an implementation for this method that
         /// returns an enum value as the actual enum type (Recall that enum's
         /// can be safely converted to integer values, but not the other way
         /// around).
         virtual Int32 GetReason() const noexcept = 0;

         /// Assigns an error message to pMsg.  The default implementation is to 
         /// create a message in the following format:
         ///
         /// A *exception_type* error, number *reason*, has occured in *filename* at line *line*.
         ///
         /// Where exception_type is the dynamic type of the exception,
         /// reason is the reason code returned by GetReason(),
         /// filename is the filename returned by GetFile(),  and
         /// line is the line number returned by GetLine().
         virtual void GetErrorMessage(std::_tstring* pMsg) const;

         /// Returns the name of the file where the exception was originally thrown.
         /// This method will not throw an exception.
         const std::_tstring& GetFile() const noexcept;

         /// Returns the line number from where the exceptino was originally thrown.
         /// This method will not throw an exception.
         Uint32 GetLine() const noexcept;

       private:
         std::_tstring m_File{ _T("Unspecified") };
         Uint32  m_Line{ 0 };
      };
   };
};
