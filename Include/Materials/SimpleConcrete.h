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
#include <Materials/ConcreteTypes.h>

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

         //--------------------- UHPC Properties
         void SetFirstCrackingStrength(Float64 ffc);
         Float64 GetFirstCrackingStrength() const;
         void SetPostCrackingTensileStrength(Float64 frr);
         Float64 GetPostCrackingTensileStrength() const;
         void SetAutogenousShrinkage(Float64 as);
         Float64 GetAutogenousShrinkage() const;

         virtual std::unique_ptr<SimpleConcrete> CreateClone() const;

#if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

      private:
         // GROUP: DATA MEMBERS
         ConcreteType  m_Type;
         Float64     m_Fct;
         bool        m_bHasFct;
         std::_tstring m_Name;
         Float64     m_Fc;
         Float64     m_Density;
         Float64 m_WeightDensity;
         Float64 m_FrShear;
         Float64 m_FrFlexure;
         Float64     m_ModE;
         Float64     m_MaxAggregateSize;
         Float64     m_FiberLength;
         Float64     m_Lambda;

         // UHPC
         Float64 m_ffc;
         Float64 m_frr;
         Float64 m_AutogenousShrinkage;
      };
   };
};
