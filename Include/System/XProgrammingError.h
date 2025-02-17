///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright � 1999-2025  Washington State Department of Transportation
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
#include <System\Exception.h>

namespace WBFL
{
   namespace System
   {
      /// A programming error exception thrown when a programming error is encountered.
      class SYSCLASS XProgrammingError : public XBase
      {
      public:
         // GROUP: ENUMERATIONS
         enum Reason { Precondition,     ///< A precondition was not satisfied
                       InvalidValue,     ///< A value is invalid
                       ValueOutOfRange,  ///< A value was out of a required range
                       NotImplemented,   ///< A code segment is not implemented
                       AssertValidFailed, ///< A call to AssertValid() failed
                       Unspecified ///< The type of error is unspecified
         };

         XProgrammingError() = default;
         XProgrammingError(Reason reason, const std::_tstring& file, Uint32 line);
         virtual ~XProgrammingError() = default;

         XProgrammingError& operator=(const XProgrammingError&) = default;
         
         virtual void Throw() const override;
         virtual Int32 GetReason() const noexcept override;
         virtual Reason GetReasonCode() const noexcept;

      private:
         Reason m_Reason{ Unspecified };
      };
   };
};
