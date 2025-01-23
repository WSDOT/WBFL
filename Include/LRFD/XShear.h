///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <Lrfd\LrfdExp.h>
#include <System\Exception.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Exception object thrown when the Shear class encounters an exceptional condition.
      class LRFDCLASS XShear : public WBFL::System::XBase
      {
      public:
         enum class Reason { vfcOutOfRange,  // v/fc > 0.25. A bigger section is needed
                       MaxIterExceeded, // The maximum number of iterations was exceeded before a solution was found
                       StrainOutOfRange // The strain computed by eq'n 5.8.3.4.2-2, adjusted by eq'n 5.8.3.4.2-3, is out of the range supported by Figure 5.8.3.4.2-1 and Table 5.8.3.4.2-1
         };

         XShear() = delete;
         XShear(Reason reason, LPCTSTR file, Uint32 line);
         XShear(const XShear&) = default;
         virtual ~XShear() = default;

         XShear& operator=(const XShear&) = default;

         virtual void Throw() const override;
         virtual Int32 GetReason() const noexcept override;
         Reason GetReasonCode() const noexcept;

      private:
         Reason m_Reason;
      };
   };
};
