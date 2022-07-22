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

namespace WBFL
{
   namespace Materials
   {
      class ConcreteStrengthModel;
      class ConcreteSecantModulusModel;
      class ConcreteShrinkageModel;
      class ConcreteCreepModel;

      /// Base class for Portland Cement concrete material models.
      ///
      /// This is a static concrete model. All properties are provided as the model is created.
      /// For example, modulus of elasticity is provided, not computed by this model.
      class MATCLASS Concrete
      {
      public:
         Concrete() = default;

         Concrete(const std::_tstring& name);

         Concrete(const Concrete& rOther) = default;

         virtual ~Concrete() = default;

         Concrete& operator=(const Concrete& rOther) = default;

         void SetName(const std::_tstring& name);
         std::_tstring GetName() const;

         void SetStrengthModel(const std::shared_ptr<const ConcreteStrengthModel>& model);
         const std::shared_ptr<const ConcreteStrengthModel>& GetStrengthModel() const;

         void SetSecantModulusModel(const std::shared_ptr<const ConcreteSecantModulusModel>& model);
         const std::shared_ptr<const ConcreteSecantModulusModel>& GetSecantModulusModel() const;

         void SetShrinkageModel(const std::shared_ptr<const ConcreteShrinkageModel>& model);
         const std::shared_ptr<const ConcreteShrinkageModel>& GetShrinkageModel() const;

         void SetCreepModel(const std::shared_ptr<const ConcreteCreepModel>& model);
         const std::shared_ptr<const ConcreteCreepModel>& GetCreepModel() const;

         virtual Float64 GetFc(Float64 age) const;
         virtual Float64 GetEc(Float64 age) const;
         virtual Float64 GetShrinkageStrain(Float64 age) const;
         virtual Float64 GetCreep(Float64 t, Float64 ti) const;

      private:
         std::_tstring m_Name{ _T("Unknown") };

         std::shared_ptr<const ConcreteStrengthModel> m_StrengthModel;
         std::shared_ptr<const ConcreteSecantModulusModel> m_SecantModulusModel;
         std::shared_ptr<const ConcreteShrinkageModel> m_ShrinkageModel;
         std::shared_ptr<const ConcreteCreepModel> m_CreepModel;

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
