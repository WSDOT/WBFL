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
      /// @brief Exception object thrown when the lrfdCreepCoefficient class can't compute
      /// the creep coefficient.  This will only occur when the V/S ratio exceeds the
      /// limit specified in the LRFD specification;
      class LRFDCLASS XCreepCoefficient : public WBFL::System::XBase
      {
      public:
         enum class Reason { VSRatio, Specification };

         XCreepCoefficient() = delete;
         XCreepCoefficient(Reason reason, LPCTSTR file, Uint32 line);
         XCreepCoefficient(const XCreepCoefficient&) = default;
         virtual ~XCreepCoefficient() override = default;

         XCreepCoefficient& operator=(const XCreepCoefficient&) = default;

         virtual void Throw() const override;
         virtual Int32 GetReason() const noexcept override;
         Reason GetReasonCode() const noexcept;

      private:
         Reason m_Reason;
      };
   };
};
