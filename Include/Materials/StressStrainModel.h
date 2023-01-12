///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#include <Materials/MaterialsExp.h>

namespace WBFL
{
   namespace Materials
   {
      /// Abstract base class for the constituitive model of an engineering material
      class MATCLASS StressStrainModel
      {
      public:
         StressStrainModel() = default;
         StressStrainModel(const std::_tstring& strName);
         StressStrainModel(const StressStrainModel&) = default;
         virtual ~StressStrainModel() = default;

         StressStrainModel& operator=(const StressStrainModel&) = delete;

         /// Creates a clone of the stress-strain model
         virtual std::unique_ptr<StressStrainModel> Clone() const = 0;

         /// Sets the name of the stress-strain model
         void SetName(const std::_tstring& name);

         /// Returns the name of the stress-strain model
         std::_tstring GetName() const;

         /// Returns the strain associated with yielding of the material
         virtual Float64 GetYieldStrain() const = 0;

         /// Returns the modulus of elasticity
         virtual Float64 GetModulusOfElasticity() const = 0;

         /// Returns the stress at a given level of strain
         /// 
         /// \return a pair that contains the stress level for the strain and a boolean that indicates if the strain is within the material limits
         virtual std::pair<Float64,bool> ComputeStress(Float64 strain) const = 0;

         /// Returns the range of strain values applicable to the model
         virtual void GetStrainLimits(Float64* pMinStart, Float64* pMaxStrain) const = 0;

         /// Returns the strain that corresponds to the peak stress
         virtual Float64 GetStrainAtPeakStress() const = 0;

      #if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST

      private:
         std::_tstring m_Name{_T("Unknown")};
      };
   };
};
