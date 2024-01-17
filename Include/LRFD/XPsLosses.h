///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <Lrfd\LrfdExp.h>
#include <System\Exception.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Exception object thrown when the PsLosses class encounters an exceptional condition.
      class LRFDCLASS XPsLosses : public WBFL::System::XBase
      {
      public:
         enum class Reason {
            fpjOutOfRange,   // The jacking stress, fpj does not exceed 0.5fpu. (See 5.9.5.4.4b)
            fcOutOfRange,    // 28MPa(4KSI) <= f'c <= 70MPa(10KSI)
            Specification,   // wrong specification version
            StrandType,      // wrong stand type
            Unknown
         };

         XPsLosses() = delete;
         XPsLosses(Reason reason, LPCTSTR file, Uint32 line);
         XPsLosses(const XPsLosses& rOther) = default;
         virtual ~XPsLosses() = default;

         XPsLosses& operator=(const XPsLosses&) = default;

         virtual void Throw() const override;
         virtual Int32 GetReason() const noexcept override;
         Reason GetReasonCode() const noexcept;

      private:
         Reason m_Reason;
      };
   };
};
