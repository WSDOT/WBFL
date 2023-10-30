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
#include <Materials/MaterialTypes.h>

namespace WBFL
{
   namespace Materials
   {
      /// Base class for Portland Cement concrete material models.
      ///
      /// This is a static concrete model. All properties are provided as the model is created.
      /// For example, modulus of elasticity is provided, not computed by this model.
      class MATCLASS SimpleConcrete
      {
      public:
         /// Sets name to "Unknown" and density, fc, and modulus of elasticity to zero.
         SimpleConcrete();

         SimpleConcrete(
            const std::_tstring& name, ///< Name of the material
            Float64 fc,  ///< compressive strength
            Float64 density,  ///< density used for modulus of elasticity
            Float64 wDensity,  ///< density used for dead loads
            Float64 modE,  ///< modulus of elasticity
            Float64 frShear,  ///< modulus of rupture for shear
            Float64 frFlexure ///< modulus of rupture for flexure
         );

         SimpleConcrete(const SimpleConcrete& rOther) = default;

         virtual ~SimpleConcrete();

         SimpleConcrete& operator=(const SimpleConcrete& rOther) = default;

         bool operator==(const SimpleConcrete& rOther) const;
         bool operator!=(const SimpleConcrete& rOther) const;

         void SetType(ConcreteType type);
         ConcreteType GetType() const;

         static std::_tstring GetTypeName(ConcreteType type, bool bFull);
         static ConcreteType GetTypeFromTypeName(LPCTSTR strName);

         void SetAggSplittingStrength(Float64 ft);
         Float64 GetAggSplittingStrength() const;
         bool HasAggSplittingStrength() const;
         void HasAggSplittingStrength(bool bHasFct);


         void SetName(const std::_tstring& name);
         std::_tstring GetName() const;

         void SetFc(Float64 fc);
         Float64 GetFc() const;

         void SetDensity(Float64 density);
         Float64 GetDensity() const;

         void SetDensityForWeight(Float64 d);
         Float64 GetDensityForWeight() const;

         void SetShearFr(Float64 fr);
         Float64 GetShearFr() const;
         void SetFlexureFr(Float64 fr);
         Float64 GetFlexureFr() const;

         void SetE(Float64 modE);
         Float64 GetE() const;

         void SetMaxAggregateSize(Float64 size);
         Float64 GetMaxAggregateSize() const;

         // Set/Get the fiber length for fiber reinforced materials
         void SetFiberLength(Float64 length);
         Float64 GetFiberLength() const;

         /// Lightweight concrete modification factor
         void SetLambda(Float64 lambda);
         Float64 GetLambda() const;

         /// PCI UHPC Properties
         void SetFirstCrackingStrength(Float64 ffc);
         Float64 GetFirstCrackingStrength() const;
         void SetPostCrackingTensileStrength(Float64 frr);
         Float64 GetPostCrackingTensileStrength() const;
         void SetAutogenousShrinkage(Float64 as);
         Float64 GetAutogenousShrinkage() const;

         /// UHPC Parameters
         void SetCompressionResponseReductionFactor(Float64 alpha_u);
         Float64 GetCompressionResponseReductionFactor() const;
         void SetCompressiveStrainLimit(Float64 ecu);
         void SetElasticTensileStrainLimit(Float64 etcr);
         Float64 GetElasticTensileStrainLimit() const;
         void SetInitialEffectiveCrackingStrength(Float64 ft_cri);
         Float64 GetInitialEffectiveCrackingStrength() const;
         void SetDesignEffectiveCrackingStrength(Float64 ft_cr);
         Float64 GetDesignEffectiveCrackingStrength() const;
         void SetCrackLocalizationStrength(Float64 ft_loc);
         Float64 GetCrackLocalizationStrength() const;
         void SetCrackLocalizationStrain(Float64 et_loc);
         Float64 GetCrackLocalizationStrain() const;
         void SetFiberOrientationReductionFactor(Float64 gamma_u);
         Float64 GetFiberOrientationReductionFactor() const;

         Float64 GetElasticCompressiveStrainLimit() const; 
         Float64 GetCompressiveStrainLimit(bool* pbIsExperimental = nullptr) const; // computed per GS 1.4.2.4

         virtual std::unique_ptr<SimpleConcrete> CreateClone() const;

      private:
         // GROUP: DATA MEMBERS
         ConcreteType  m_Type = ConcreteType::Normal;
         Float64     m_Fct = 0.0;
         bool        m_bHasFct = false;
         std::_tstring m_Name = _T("Unknown");
         Float64     m_Fc = 0.0;
         Float64     m_Density = 0.0;
         Float64 m_WeightDensity = 0.0;
         Float64 m_FrShear = 0.0;
         Float64 m_FrFlexure = 0.0;
         Float64     m_ModE = 0.0;
         Float64     m_MaxAggregateSize = 0.0;
         Float64     m_FiberLength = 0.0;
         Float64     m_Lambda = 0.0;

         // PCI UHPC
         Float64 m_ffc = 0.0;
         Float64 m_frr = 0.0;
         Float64 m_AutogenousShrinkage = 0.0;

         // UHPC
         Float64 m_alpha_u = 0.0;
         Float64 m_ecu = 0.0;
         Float64 m_etcr = 0.0;
         Float64 m_ftcri = 0.0;
         Float64 m_ftcr = 0.0;
         Float64 m_ftloc = 0.0;
         Float64 m_etloc = 0.0;
         Float64 m_gamma_u = 0.0;
         bool m_bExperimental_ecu = false;
      };
   };
};
