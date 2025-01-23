///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#include <Materials/MaterialsExp.h>
#include <Materials/StressStrainModel.h>
#include <Materials/MaterialTypes.h>

namespace WBFL
{
   namespace Materials
   {
      /// Material model for the Power Formula stress-strain model for prestress reinforcement
      ///
      /// Grade 270 Low Relaxation \f$ f_{ps} = \epsilon_{ps}\left[887 + \frac{27613}{(1+(112.4\epsilon_{ps})^{7.36})^{\frac{1}{7.36}}}\right] \le 270 ksi \f$
      ///
      /// Grade 270 Stress Relieved \f$ f_{ps} = \epsilon_{ps}\left[885 + \frac{27645}{(1+(118\epsilon_{ps})^{6})^{\frac{1}{6}}}\right] \le 270 ksi \f$
      ///
      /// Grade 250 Low Relaxation \f$ \begin{cases} f_{ps} = E_{ps}\epsilon_{ps} & \epsilon < 0.076
      /// f_{ps} = 250 - \frac{0.04}{\epsilon - 0.0064} \le 250 ksi \end{cases} \f$
      ///
      /// Grade 250 Stress Relieved \f$ \begin{cases} f_{ps} = E_{ps}\epsilon_{ps} & \epsilon < 0.076
      /// f_{ps} = 250 - \frac{0.04}{\epsilon - 0.0064} \le 250 ksi \end{cases} \f$
      class MATCLASS PSPowerFormulaModel : public StressStrainModel
      {
      public:
         PSPowerFormulaModel() = default;
         PSPowerFormulaModel(const std::_tstring& strName);
         PSPowerFormulaModel(const PSPowerFormulaModel&) = default;
         virtual ~PSPowerFormulaModel() = default;

         PSPowerFormulaModel& operator=(const PSPowerFormulaModel&) = delete;

         /// Set strand grade
         void SetStrandGrade(StrandGrade grade);
         StrandGrade GetStrandGrade() const;

         /// Set production type
         void SetStrandType(StrandType type);
         StrandType GetStrandType() const;

         /// Sets a scaling factor that is multiplied with the computed stress
         void SetScalingFactor(Float64 k);
         Float64 GetScalingFactor() const;

         /// Set the strain limits
         void SetStrainLimits(Float64 minStrain, Float64 maxStrain);

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

      private:
         StrandGrade m_Grade{ StrandGrade::Grade270 };
         StrandType m_Type{ StrandType::LowRelaxation };
         Float64 m_K{ 1.0 };
         Float64 m_MinStrain{ -10 }; // assumes material doesn't fracture in compression
         Float64 m_MaxStrain{ 0.035 }; // per ASTM A416 material specification
         Float64 m_fpu{ 270.0 }; // KSI
         Float64 m_Eps{ 28500.0 }; // KSI
      };
   };
};
