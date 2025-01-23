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

#include <LRFD\LrfdExp.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Computes the creep coefficient per Article 5.4.2.3.2
      class LRFDCLASS CreepCoefficient
      {
      public:
         enum class CuringMethod { Normal, Accelerated };

         CreepCoefficient() = default;
         virtual ~CreepCoefficient() = default;

         /// @brief Computes the creep coefficient
         /// @param t Time under consideration
         /// @param ti Time when load is applied
         /// @return Creep coefficient
         virtual Float64 GetCreepCoefficient(Float64 t, Float64 ti) const;

         void SetRelHumidity(Float64 H);
         Float64 GetRelHumidity() const;

         void SetVolume(Float64 V);
         Float64 GetVolume() const;

         void SetSurfaceArea(Float64 S);
         Float64 GetSurfaceArea() const;

         void SetFci(Float64 fci);
         Float64 GetFci() const;

         virtual Float64 GetAdjustedInitialAge(Float64 ti) const;

         void SetCuringMethod(CuringMethod method);
         CuringMethod GetCuringMethod() const;

         void SetCuringMethodTimeAdjustmentFactor(Float64 f);
         Float64 GetCuringMethodTimeAdjustmentFactor() const;

         Float64 GetKf() const;
         virtual Float64 GetKtd(Float64 t) const;

      protected:
         Float64 m_H = 0;
         Float64 m_Fci = 0;
         Float64 m_V = 0;
         Float64 m_S = 1;
         CuringMethod m_CuringMethod = CuringMethod::Normal;
         Float64 m_CuringMethodTimeAdjustmentFactor = 7.0*24*60*60; // 7 days, measured in seconds

         mutable Float64 m_kc = 0;
         mutable Float64 m_kf = 0;
         mutable bool m_bUpdate = true; // True if a parameter has been changed and an update is required

         virtual void Update() const;
         virtual Float64 ComputeKf() const;
         virtual Float64 ComputeKtd(Float64 t) const;
      };
   };
};
