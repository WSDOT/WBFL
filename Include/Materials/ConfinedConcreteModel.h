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
#include <MathEx.h>

namespace WBFL
{
   namespace Materials
   {
      /// Base class for confined concrete sections for use in the ConfinedConcreteModel
      class MATCLASS ManderModelSection
      {
      public:
         ManderModelSection() = default;
         ManderModelSection(const ManderModelSection&) = default;
         virtual ~ManderModelSection() = default;
         ManderModelSection& operator=(const ManderModelSection&) = default;

         void SetTransvYieldStrength(Float64 fyh) { m_fyh = fyh; }
         Float64 GetTransvYieldStrength() const { return m_fyh; }

         void SetTransvReinforcementRuptureStrian(Float64 esu) { m_esu = esu; }
         Float64 GetTransvReinforcementRuptureStrain() const { return m_esu; }

         virtual Float64 GetTransvReinforcementRatio() const = 0;
         virtual Float64 GetConfinementEffectivenessCoefficient() const = 0;

      private:
         Float64 m_fyh{ 0.0 };
         Float64 m_esu{ 0.004 };
      };

      /// Section model a circular cross section based on formulations by Mander.
      class MATCLASS CircularManderSection : public ManderModelSection
      {
      public:
         CircularManderSection() = default;
         CircularManderSection(const CircularManderSection&) = default;
         virtual ~CircularManderSection() = default;
         CircularManderSection& operator=(const CircularManderSection&) = default;

         virtual Float64 GetTransvReinforcementRatio() const override
         {
            return 4.0 * m_Asp / (Get_ds() * m_S);
         }

         virtual Float64 GetConfinementEffectivenessCoefficient() const override
         {
            Float64 ke;
            Float64 s_ = m_S - m_db;
            Float64 ds = Get_ds();
            Float64 Ac = M_PI * ds * ds / 4;
            Float64 pcc = m_As / Ac;

            if (m_TransvReinforcementType == TransvReinforcementType::Spiral)
            {
               ke = (1 - s_ / (2 * ds)) / (1 - pcc);
            }
            else
            {
               CHECK(m_TransvReinforcementType == TransvReinforcementType::Hoops);
               ke = (1 - s_ / (2 * ds)) * (1 - s_ / (2 * ds)) / (1 - pcc);
            }
            return ke;
         }

         /// The type of transverse reinforcement used in the concrete member.
         void SetTransvReinforcemenType(TransvReinforcementType type) { m_TransvReinforcementType = type; }
         TransvReinforcementType GetTransvReinforcementType() const { return m_TransvReinforcementType; }

         /// Area of transverse reinforcement.
         void SetAsp(Float64 asp) { m_Asp = asp; }
         Float64 GetAsp() const { return m_Asp; }

         /// Area of longitudinal reinforcement.
         void SetAs(Float64 as) { m_As = as; }
         Float64 GetAs() const { return m_As; }

         /// Diameter of transverse reinforcement.
         void Set_db(Float64 db) { m_db = db; }
         Float64 Get_db() const { return m_db; }

         /// Spacing (pitch) of transverse reinforcement.
         void SetS(Float64 s) { m_S = s; }
         Float64 GetS() const { return m_S; }

         /// Diameter of the circular section.
         void SetDiameter(Float64 d) { m_Diameter = d; }
         Float64 GetDiameter() const { return m_Diameter; }

         /// Clear cover to longitindal reinforcement.
         void SetCover(Float64 c) { m_Cover = c; }
         Float64 GetCover() const { return m_Cover; }

      private:
         TransvReinforcementType m_TransvReinforcementType;
         Float64 m_Asp{ 0.0 };
         Float64 m_As{ 0.0 };
         Float64 m_db{ 0.0 };
         Float64 m_S{ 0.0 };
         Float64 m_Diameter{ 0.0 };
         Float64 m_Cover{ 0.0 };

         Float64 Get_ds() const { return m_Diameter - 2 * m_Cover - m_db; }
      };

      /// Confined concrete stress-strain model
      ///
      /// This model is based on Mander, et.al. "Theoretical Stress-Strain Model for Confined Concrete", ASCE Journal of Structural Engineering, V. 114. No. 8, August 1988
      class MATCLASS ConfinedConcreteModel : public StressStrainModel
      {
      public:
         ConfinedConcreteModel() = default;
         ConfinedConcreteModel(const std::_tstring& strName);
         ConfinedConcreteModel(const ConfinedConcreteModel&) = default;
         virtual ~ConfinedConcreteModel() = default;

         ConfinedConcreteModel& operator=(const ConfinedConcreteModel&) = delete;

         void SetSection(const std::shared_ptr<const ManderModelSection>& second);
         const std::shared_ptr<const ManderModelSection>& GetSection() const;

         /// Set compressive strength of unconfined concrete
         void Set_fco(Float64 fco);
         Float64 Get_fco() const;

         /// Set strain corresponding to the maximum stress in unconfined concrete
         void Set_eco(Float64 eco);
         Float64 Get_eco() const;

         /// Set ratio of increase strain at peak stress to increase in strength at peak stress due to confinement
         /// This value varies from 3 to 6 with a typical value of 5.
         void SetR(Float64 r);
         Float64 GetR() const;

         /// Computes the concrete properties
         /// \f[ f_r = \frac{1}{2} k_e \rho_s f_{yh} \f]
         /// \f[ f_{cc} = f_{co} \left( -1.254 + 2.254\sqrt{1+7.94\frac{f_r}{f_{cc}}} - 2\frac{f_r}{f_{co}}  \right) \f]
         /// \f[ e_{co} \left( 1+R\left(\frac{f_{cc}}{f_{co}} -1 \right) \right) \f]
         /// Returns a tuple of the format (fr,fcc,ecc);
         std::tuple<Float64,Float64,Float64> ComputeConcreteProperties() const;

         /// Creates a clone of the stress-strain model
         virtual std::unique_ptr<StressStrainModel> Clone() const override;

         /// Returns the strain associated with yielding of the material
         virtual Float64 GetYieldStrain() const override;

         /// Returns the modulus of elasticity
         virtual Float64 GetModulusOfElasticity() const override;

         /// Returns the stress at a given level of strain
         virtual std::pair<Float64, bool> ComputeStress(Float64 strain) const override;

         /// Returns the range of strain values applicable to the model
         virtual std::pair<Float64, Float64> GetStrainLimits() const override;

         /// Returns the strain that corresponds to the peak stress
         virtual Float64 GetStrainAtPeakStress() const override;

      private:
         Float64 m_fco{ 0.0 };
         Float64 m_eco{ 0.002 };
         Float64 m_R{ 5.0 };
         std::shared_ptr<const ManderModelSection> m_Section;

         Float64 GetEc() const; // returns Ec in PSI
      };
   };
};
