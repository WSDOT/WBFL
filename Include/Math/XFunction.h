///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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

#include <Math\MathExp.h>
#include <System\Exception.h>

#define THROW_FUNCTION(reason) throw WBFL::Math::XFunction(reason,_T(__FILE__),__LINE__)

namespace WBFL
{
   namespace Math
   {

      /// Math function evaluation error exception.  Thrown from Function::Evaluate() if an error occurs.
      class MATHCLASS XFunction : public WBFL::System::XBase
      {
      public:
         enum class Reason {
            Unknown,     ///< Evaluation failed for an unknown reason
            Undefined,   ///< Function is not defined at the evalation point
            MultiValued, ///< Function is multivalued at the evaluation point
            PosInfinity, ///< Function evaluation is positive infinity
            NegInfinity  ///< Function evaluation is negative infinity
         };

         XFunction(Reason reason, const std::_tstring& file, Uint32 line);
         XFunction(const XFunction&) = default;
         virtual ~XFunction() = default;

         XFunction& operator=(const XFunction&) = default;

         virtual void Throw() const override;
         virtual Int32 GetReason() const noexcept override;

         Reason GetReasonCode() const noexcept;


      private:
         Reason  m_Reason{ Reason::Unknown };
      };
   };
};
