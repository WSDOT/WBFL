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
#include <Materials/StressStrainModel.h>
#include <Materials/MaterialTypes.h>
#include <Units/Units.h>

namespace WBFL
{
   namespace Materials
   {
      /// Material model for carbon steel reinforcement
      ///
      /// The general form of the model include strain hardening
      /// \f[ f(\epsilon_s) = \begin{cases}
      ///    E_s \epsilon_s & : \epsilon_s \le \epsilon_y \\
      ///    f_y & : \epsilon_y \lt \epsilon_s \le \epsilon_{sh} \\
      ///    f_u - (f_u - f_y)\frac{(\epsilon_{fr} - \epsilon_s)^2}{(\epsilon_{sh} - \epsilon_{fr})^2} & : \epsilon_{sh} \lt \epsilon_s \le \epsilon_{fr}
      /// \end{cases}
      /// \f]
      ///
      /// If strain hardening is excluded from the model, a simple elastic-plastic model is used
      /// \f[ f(\epsilon_s) = \begin{cases}
      ///    E_s \epsilon_s & : \epsilon_s \le \epsilon_y \\
      ///    f_y & : \epsilon_y \lt \epsilon_s \le \epsilon_{fr} 
      /// \end{cases}
      /// \f]
      class MATCLASS RebarModel : public StressStrainModel
      {
      public:
         RebarModel() = default;
         RebarModel(const std::_tstring& strName, Float64 fy = WBFL::Units::ConvertToSysUnits(60, WBFL::Units::Measure::KSI), Float64 Es = WBFL::Units::ConvertToSysUnits(29000, WBFL::Units::Measure::KSI), Float64 er = 0.07);
         RebarModel(const std::_tstring& strName, Float64 fy, Float64 fu, Float64 Es, Float64 esh, Float64 er);
         RebarModel(const RebarModel&) = default;
         virtual ~RebarModel() = default;

         RebarModel& operator=(const RebarModel&) = delete;

         /// Set the model properties for the elastic-plastic model
         /// \param fy yield stress
         /// \param Es modulus of elasticity
         /// \param er rupture strain
         void SetProperties(Float64 fy, Float64 Es, Float64 er);

         /// Set the model properties for the strain hardening model
         /// \param fy yield stress
         /// \param fu ultimate stress
         /// \param Es modulus of elasticity
         /// \param esh strain hardening limit
         /// \param er rupture strain
         void SetProperties(Float64 fy, Float64 fu, Float64 Es, Float64 esh, Float64 er);

         /// Gets the model properties and indicates if it is a strain-hardening or elastic-plastic model
         void GetProperties(Float64* pfy, Float64* pfu, Float64* pEs, Float64* pesh, Float64* per, bool* pIsStrainHardening) const;

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
         Float64 m_MinStrain{ -10 }; // assumes material doesn't fracture in compression
         Float64 m_MaxStrain{ 0.07 };
         Float64 m_esh{ 0.006 };
         Float64 m_fy{ 60.0 }; // KSI
         Float64 m_fu{ 90.0 }; // KSI
         Float64 m_Es{ 29000.0 }; // KSI
         bool m_bStrainHardeningModel{ true };
      };
   };
};
