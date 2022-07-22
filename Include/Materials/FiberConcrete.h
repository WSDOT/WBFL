///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#include <Materials/MaterialsExp.h>
#include <Materials/Concrete.h>

namespace WBFL
{
   namespace Materials
   {
      /// Abstract base class for fiber reinforced concrete
      class MATCLASS FiberConcrete : public Concrete
      {
      public:
         /// Sets name to "Unknown" and density, fc, and modulus of elasticity to zero.
         FiberConcrete();

         FiberConcrete(
            const std::_tstring& name, ///< Name of the material
            Float64 fiberLength ///< fiber length
         );

         FiberConcrete(const FiberConcrete& rOther) = default;

         virtual ~FiberConcrete() = default;

         FiberConcrete& operator=(const FiberConcrete& rOther) = default;

         void SetFiberLength(Float64 fiberLength);
         Float64 GetFiberLength() const;

      private:
         Float64 m_FiberLength{ 0.0 };

#if defined _DEBUG
      public:
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
      public:
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };
   };
};
