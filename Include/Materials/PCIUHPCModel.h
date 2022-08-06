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
#include <Materials/StressStrainModel.h>

namespace WBFL
{
   namespace Materials
   {
      /// Material model for Ultra High Performance Concrete (UHPC) per PCI Structural Design Guidance
      /// /todo - Add reference to publication
      class MATCLASS PCIUHPCModel : public StressStrainModel
      {
      public:
         PCIUHPCModel() = default;
         PCIUHPCModel(LPCTSTR lpszName);
         PCIUHPCModel(const std::_tstring& strName);
         PCIUHPCModel(const PCIUHPCModel&) = default;
         virtual ~PCIUHPCModel() = default;

         PCIUHPCModel& operator=(const PCIUHPCModel&) = delete;

         /// Sets the concrete strength
         void SetFc(Float64 fc);

         /// Returns the concrete strength
         Float64 GetFc() const;

         /// Creates a clone of the stress-strain model
         virtual std::unique_ptr<StressStrainModel> Clone() const override;

         /// Returns the strain associated with yielding of the material
         virtual Float64 GetYieldStrain() const override;

         /// Returns the modulus of elasticity
         virtual Float64 GetModulusOfElasticity() const override;

         /// Returns the stress at a given level of strain
         virtual std::pair<Float64, bool> ComputeStress(Float64 strain) const override;

         /// Returns the range of strain values applicable to the model
         virtual void GetStrainLimits(Float64* pMinStrain, Float64* pMaxStrain) const override;

         /// Returns the strain that corresponds to the peak stress
         virtual Float64 GetStrainAtPeakStress() const override;

      #if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
      #endif // _DEBUG

      #if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
      #endif // _UNITTEST

      private:
         Float64 m_fc{ 17.4 }; // in KSI units

         Float64 GetEc() const;
      };
   };
};
