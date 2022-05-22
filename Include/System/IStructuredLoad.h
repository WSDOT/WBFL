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
      /// Pure interface class for loading structured data from a data source.
      /// This class was based on an article by Neil Hunt of Rational Corp.
      /// call Unit Testing. The class is certainly useful for more than unit testing.
      /// 
      /// Property read routines. All of these calls try to read a property at the
      /// current file pointer location. If the function returns true, the property
      /// was read and the file pointer advances. If the function returns false,
      /// the property was not at the current locaton and the file pointer does not
      /// advance.
      class SYSCLASS IStructuredLoad
      {
      public:
         virtual ~IStructuredLoad() = default;

         /// Check for the Beginning of a named structured data unit. If true is 
         /// returned, the beginning of the unit was found and the file pointer is
         /// advanced. If false is returned, the file pointer does not advance.
         /// After a unit has been entered, GetVersion may be called to get its
         /// version
         virtual bool BeginUnit(LPCTSTR name) = 0;

         /// Check for the end of a structured data chunk that was started by a call to BeginUnit.
         virtual bool EndUnit() = 0;

         /// Get the version number of the current unit
         virtual Float64 GetVersion() = 0;
   
         /// Get the version number of the unit that is the parent to this unit
         virtual Float64 GetParentVersion() = 0;

         /// Get the name of the unit that is the parent to this unit
         virtual std::_tstring GetParentUnit() = 0;

         /// Get the version number of the top-most unit
         virtual Float64 GetTopVersion() = 0;

         /// Read a string property
         virtual bool Property(LPCTSTR name, std::_tstring* pvalue) = 0;

         /// Read a real number property
         virtual bool Property(LPCTSTR name, Float64* pvalue) = 0;

         /// Read an Integer property
         virtual bool Property(LPCTSTR name, Int16* pvalue) = 0;

         /// Read an unsigned Integer property
         virtual bool Property(LPCTSTR name, Uint16* pvalue) = 0;

         /// Read an Integer property
         virtual bool Property(LPCTSTR name, Int32* pvalue) = 0;

         /// Read an unsigned Integer property
         virtual bool Property(LPCTSTR name, Uint32* pvalue) = 0;

         /// Read an Integer property
         virtual bool Property(LPCTSTR name, Int64* pvalue) = 0;

         /// Read an unsigned Integer property
         virtual bool Property(LPCTSTR name, Uint64* pvalue) = 0;

         /// Read an Integer property
         virtual bool Property(LPCTSTR name, LONG* pvalue) = 0;

         /// Read an unsigned Integer property
         virtual bool Property(LPCTSTR name, ULONG* pvalue) = 0;

         /// Read a bool property
         virtual bool Property(LPCTSTR name, bool* pvalue) = 0;

         /// Am I at the end of the "File"?
         virtual bool Eof()const  = 0;

         /// Dump state as a text string into os. This is primarily to be used for error handling.
         virtual std::_tstring GetStateDump() const = 0;

         /// Returns the current unit as a text string
         virtual std::_tstring GetUnit() const = 0;
      };
   };
};
