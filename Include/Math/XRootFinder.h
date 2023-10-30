///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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

#include <Math\MathExp.h>
#include <System\Exception.h>

#define THROW_ROOTFINDER(reason) throw WBFL::Math::XRootFinder(reason,_T(__FILE__),__LINE__)

namespace WBFL
{
   namespace Math
   {

      /// The root finder failed
      class MATHCLASS XRootFinder : public WBFL::System::XBase
      {
      public:
         enum class Reason {
            Unknown,        ///< The reason is unknown
            RootNotPresent, ///< A root is not present
            BracketFailed,  ///< could not bracket root in range.
            MaxIterExceeded ///< The maximum number of iterations were exceeded
         };

         XRootFinder(Reason reason, const std::_tstring& file, Uint32 line);

         XRootFinder(const XRootFinder&) = default;

         virtual ~XRootFinder() = default;

         XRootFinder& operator=(const XRootFinder&) = default;

         virtual void Throw() const override;
         virtual Int32 GetReason() const noexcept override;

         Reason GetReasonCode() const noexcept;

      private:
         Reason m_Reason;
      };
   };
};
