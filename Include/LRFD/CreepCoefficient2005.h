///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <LRFD\LrfdExp.h>
#include <LRFD\CreepCoefficient.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Computes the creep coefficient per Article 5.4.2.3.2 
      /// Based on 2005 interim provisions (and perhaps later)
      class LRFDCLASS CreepCoefficient2005 : public CreepCoefficient
      {
      public:
         CreepCoefficient2005() = default;
         virtual ~CreepCoefficient2005() = default;

         virtual Float64 GetCreepCoefficient(Float64 t, Float64 ti) const override;
         virtual Float64 GetAdjustedInitialAge(Float64 ti) const override;

         void SetK1(Float64 k1);
         Float64 GetK1() const;
         void SetK2(Float64 k2);
         Float64 GetK2() const;

         Float64 GetKvs() const;
         Float64 GetKhc() const;
         virtual Float64 GetKtd(Float64 t) const override;

         virtual Float64 GetKl(Float64 ti) const;

      protected:
         virtual Float64 GetUltimateCreep() const;
         virtual Float64 ComputeKvs() const;
         virtual Float64 ComputeKhc() const;
         virtual Float64 ComputeKf() const;
         virtual Float64 ComputeKtd(Float64 t) const;

         Float64 m_K1 = 1.0; // averaging factor
         Float64 m_K2 = 1.0; // bounding factor

         mutable Float64 m_kvs; // volume-surface ratio factor
         mutable Float64 m_khc; // humidity factor

         virtual void Update() const;
      };
   };
};
