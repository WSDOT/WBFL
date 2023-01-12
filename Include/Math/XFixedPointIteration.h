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

#define THROW_FIXEDPOINTITERATION(reason,last) throw WBFL::Math::XFixedPointIteration(reason,last,_T(__FILE__),__LINE__)

namespace WBFL
{
   namespace Math
   {
      /// Fixed Point Iteration exception
      class MATHCLASS XFixedPointIteration : public WBFL::System::XBase
      {
      public:
         enum class Reason {
            Unknown,     ///< Evaluation failed for an unknown reason
            MaxIterExceeded ///< The maximum number of iterations were exceeded
         };

         XFixedPointIteration(Reason reason, Float64 last, const std::_tstring& file, Uint32 line);
         XFixedPointIteration(const XFixedPointIteration&) = default;
         virtual ~XFixedPointIteration() = default;

         XFixedPointIteration& operator=(const XFixedPointIteration&) = default;

         virtual void Throw() const override;
         virtual Int32 GetReason() const noexcept override;

         Reason GetReasonCode() const noexcept;

         Float64 GetLast() const noexcept;


      private:
         Reason  m_Reason{ Reason::Unknown };
         Float64 m_Last{ 0.0 };
      };
   };
};
