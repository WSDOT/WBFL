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

#include <Materials/MatLib.h>
#include <Materials/Concrete.h>
#include <Materials/XConcrete.h>
#include <Materials/ConcreteStrengthModel.h>
#include <Materials/ConcreteSecantModulusModel.h>
#include <Materials/ConcreteShrinkageModel.h>
#include <Materials/ConcreteCreepModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

Concrete::Concrete(const std::_tstring& name) :
   m_Name(name)
{
}

void Concrete::SetName(const std::_tstring& name)
{
   m_Name = name;
}

std::_tstring Concrete::GetName() const
{
   return m_Name;
}

void Concrete::SetStrengthModel(const std::shared_ptr<const ConcreteStrengthModel>& model)
{
   m_StrengthModel = model;
}

const std::shared_ptr<const ConcreteStrengthModel>& Concrete::GetStrengthModel() const
{
   return m_StrengthModel;
}

void Concrete::SetSecantModulusModel(const std::shared_ptr<const ConcreteSecantModulusModel>& model)
{
   m_SecantModulusModel = model;
}

const std::shared_ptr<const ConcreteSecantModulusModel>& Concrete::GetSecantModulusModel() const
{
   return m_SecantModulusModel;
}

void Concrete::SetShrinkageModel(const std::shared_ptr<const ConcreteShrinkageModel>& model)
{
   m_ShrinkageModel = model;
}

const std::shared_ptr<const ConcreteShrinkageModel>& Concrete::GetShrinkageModel() const
{
   return m_ShrinkageModel;
}

void Concrete::SetCreepModel(const std::shared_ptr<const ConcreteCreepModel>& model)
{
   m_CreepModel = model;
}

const std::shared_ptr<const ConcreteCreepModel>& Concrete::GetCreepModel() const
{
   return m_CreepModel;
}

Float64 Concrete::GetFc(Float64 age) const
{
   if (m_StrengthModel == nullptr) THROW_CONCRETE(_T("Concrete - Concrete strength model not defined"));

   return m_StrengthModel->GetFc(age);
}

Float64 Concrete::GetEc(Float64 age) const
{
   if (m_SecantModulusModel == nullptr) THROW_CONCRETE(_T("Concrete - Concrete secant modulus model not defined"));

   return m_SecantModulusModel->GetEc(age);
}

Float64 Concrete::GetShrinkageStrain(Float64 age) const
{
   if (m_ShrinkageModel == nullptr) THROW_CONCRETE(_T("Concrete - Shrinkage model not defined"));

   return m_ShrinkageModel->GetShrinkageStrain(age);
}

Float64 Concrete::GetCreep(Float64 t, Float64 ti) const
{
   if (m_CreepModel == nullptr) THROW_CONCRETE(_T("Concrete - Creep model not defined"));

   return m_CreepModel->GetCreep(t, ti);
}


#if defined _DEBUG
bool Concrete::AssertValid() const
{
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void Concrete::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for Concrete") << WBFL::Debug::endl;
   os << _T("====================") << WBFL::Debug::endl;
   os << _T("Name    : ") << m_Name.c_str() << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <MathEx.h>
bool Concrete::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Concrete");

   Concrete concrete;

   // Test that exceptions are thrown for missing models
   try
   {
      concrete.GetFc(10.);
   }
   catch (XConcrete& /*ex*/)
   {
      TRY_TESTME(true);
   }

   try
   {
      concrete.GetEc(10.);
   }
   catch (XConcrete& /*ex*/)
   {
      TRY_TESTME(true);
   }

   try
   {
      concrete.GetShrinkageStrain(10.0);
   }
   catch (XConcrete& /*ex*/)
   {
      TRY_TESTME(true);
   }

   try
   {
      concrete.GetCreep(10.0, 1.0);
   }
   catch (XConcrete& /*ex*/)
   {
      TRY_TESTME(true);
   }

   // test to verify the concrete object uses the assigned models
   // (unit tests of the models are done by the model itself)
   std::shared_ptr<ConcreteStrengthModel> fc_model = std::make_shared<ConstantConcreteStrengthModel>(4.0);
   std::shared_ptr<ConcreteSecantModulusModel> Ec_model = std::make_shared<ConstantConcreteSecantModulusModel>(4000.0);

   concrete.SetStrengthModel(fc_model);
   concrete.SetSecantModulusModel(Ec_model);
   try
   {
      TRY_TESTME(IsEqual(concrete.GetFc(10), 4.0));
      TRY_TESTME(IsEqual(concrete.GetEc(10), 4000.0));
   }
   catch (XConcrete& /*ex*/)
   {
      TRY_TESTME(false);
   }

   TESTME_EPILOG("Concrete");
}
#endif // _UNITTEST
