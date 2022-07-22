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
#include <Materials/ConcreteSecantModulusModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

void ConcreteSecantModulusModel::SetK1Model(const std::shared_ptr<ConcretePhysicalTestingCorrectionFactorModel>& model)
{
   m_K1Model = model;
}

const std::shared_ptr<ConcretePhysicalTestingCorrectionFactorModel>& ConcreteSecantModulusModel::GetK1Model() const
{
   return m_K1Model;
}

void ConcreteSecantModulusModel::SetK2Model(const std::shared_ptr<ConcretePhysicalTestingCorrectionFactorModel>& model)
{
   m_K2Model = model;
}

const std::shared_ptr<ConcretePhysicalTestingCorrectionFactorModel>& ConcreteSecantModulusModel::GetK2Model() const
{
   return m_K2Model;
}

#if defined _DEBUG
bool ConcreteSecantModulusModel::AssertValid() const
{
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void ConcreteSecantModulusModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for ConcreteSecantModulusModel")         << WBFL::Debug::endl;
   os << _T("====================")         << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool ConcreteSecantModulusModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ConcreteSecantModulusModel");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for ConcreteSecantModulusModel");
   TESTME_EPILOG("ConcreteSecantModulusModel");
}
#endif // _UNITTEST


///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////

ConstantConcreteSecantModulusModel::ConstantConcreteSecantModulusModel(Float64 Ec) :
   ConcreteSecantModulusModel(), m_Ec(Ec)
{
}

void ConstantConcreteSecantModulusModel::SetEc28(Float64 Ec)
{
   m_Ec = Ec;
}

Float64 ConstantConcreteSecantModulusModel::GetEc28() const
{
   return m_Ec;
}

Float64 ConstantConcreteSecantModulusModel::GetEc(Float64 age) const
{
   if (age < 0) return 0;
   return m_Ec;
}

#if defined _DEBUG
bool ConstantConcreteSecantModulusModel::AssertValid() const
{
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void ConstantConcreteSecantModulusModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for ConstantConcreteSecantModulusModel") << WBFL::Debug::endl;
   os << _T("====================") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <MathEx.h>
bool ConstantConcreteSecantModulusModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ConstantConcreteSecantModulusModel");

   ConstantConcreteSecantModulusModel model(4000.0);
   TRY_TESTME(IsEqual(model.GetEc(10), 4000.0));
   TRY_TESTME(IsEqual(model.GetEc(56), 4000.0));

   TESTME_EPILOG("ConstantConcreteSecantModulusModel");
}
#endif // _UNITTEST


///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////

SteppedConcreteSecantModulusModel::SteppedConcreteSecantModulusModel(Float64 Eci, Float64 age, Float64 Ec) :
   ConcreteSecantModulusModel(),
   m_Eci(Eci), m_Age(age), m_Ec(Ec)
{
}

void SteppedConcreteSecantModulusModel::SetEc(Float64 Eci, Float64 age, Float64 Ec)
{
   m_Eci = Eci;
   m_Age = age;
   m_Ec = Ec;
}

void SteppedConcreteSecantModulusModel::GetEc(Float64* pEci, Float64* page, Float64* pEc) const
{
   *pEci = m_Eci;
   *page = m_Age;
   *pEc = m_Ec;
}

Float64 SteppedConcreteSecantModulusModel::GetEc(Float64 age) const
{
   if (age < 0) return 0;

   return age < m_Age ? m_Eci : m_Ec;
}


#if defined _DEBUG
bool SteppedConcreteSecantModulusModel::AssertValid() const
{
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void SteppedConcreteSecantModulusModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for SteppedConcreteSecantModulusModel") << WBFL::Debug::endl;
   os << _T("====================") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool SteppedConcreteSecantModulusModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("SteppedConcreteSecantModulusModel");

   SteppedConcreteSecantModulusModel model(4000.0, 28, 7000.0);
   TRY_TESTME(IsEqual(model.GetEc(10), 4000.0));
   TRY_TESTME(IsEqual(model.GetEc(56), 7000.0));

   TESTME_EPILOG("SteppedConcreteSecantModulusModel");
}
#endif // _UNITTEST
