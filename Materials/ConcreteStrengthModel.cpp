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
#include <Materials/ConcreteStrengthModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

#if defined _DEBUG
bool ConcreteStrengthModel::AssertValid() const
{
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void ConcreteStrengthModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for ConcreteStrengthModel")         << WBFL::Debug::endl;
   os << _T("====================")         << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool ConcreteStrengthModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ConcreteStrengthModel");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for ConcreteStrengthModel");
   TESTME_EPILOG("ConcreteStrengthModel");
}
#endif // _UNITTEST


///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////

ConstantConcreteStrengthModel::ConstantConcreteStrengthModel(Float64 fc) :
   ConcreteStrengthModel(), m_Fc(fc)
{
}

void ConstantConcreteStrengthModel::SetFc28(Float64 fc)
{
   m_Fc = fc;
}

Float64 ConstantConcreteStrengthModel::GetFc28() const
{
   return m_Fc;
}

Float64 ConstantConcreteStrengthModel::GetFc(Float64 age) const
{
   if (age < 0) return 0;

   return m_Fc;
}

#if defined _DEBUG
bool ConstantConcreteStrengthModel::AssertValid() const
{
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void ConstantConcreteStrengthModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for ConstantConcreteStrengthModel") << WBFL::Debug::endl;
   os << _T("====================") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
#include <MathEx.h>
bool ConstantConcreteStrengthModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ConstantConcreteStrengthModel");

   ConstantConcreteStrengthModel model(4.0);
   TRY_TESTME(IsEqual(model.GetFc(10), 4.0));
   TRY_TESTME(IsEqual(model.GetFc(56), 4.0));

   TESTME_EPILOG("ConstantConcreteStrengthModel");
}
#endif // _UNITTEST


///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////

SteppedConcreteStrengthModel::SteppedConcreteStrengthModel(Float64 fci, Float64 age, Float64 fc) :
   ConcreteStrengthModel(),
   m_Fci(fci), m_Age(age), m_Fc(fc)
{
}

void SteppedConcreteStrengthModel::SetFc(Float64 fci, Float64 age, Float64 fc)
{
   m_Fci = fci;
   m_Age = age;
   m_Fc = fc;
}

void SteppedConcreteStrengthModel::GetFc(Float64* pfci, Float64* page, Float64* pfc) const
{
   *pfci = m_Fci;
   *page = m_Age;
   *pfc = m_Fc;
}

Float64 SteppedConcreteStrengthModel::GetFc(Float64 age) const
{
   if (age < 0) return 0;

   return age < m_Age ? m_Fci : m_Fc;
}


#if defined _DEBUG
bool SteppedConcreteStrengthModel::AssertValid() const
{
   //if ( !(m_Fc > 0) )
   //   return false;

   //if ( !(m_Density > 0) )
   //   return false;

   //if ( !(m_ModE > 0) )
   //   return false;

   return true;
}

void SteppedConcreteStrengthModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for SteppedConcreteStrengthModel") << WBFL::Debug::endl;
   os << _T("====================") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool SteppedConcreteStrengthModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("SteppedConcreteStrengthModel");

   SteppedConcreteStrengthModel model(4.0, 28, 7.0);
   TRY_TESTME(IsEqual(model.GetFc(10), 4.0));
   TRY_TESTME(IsEqual(model.GetFc(56), 7.0));

   TESTME_EPILOG("SteppedConcreteStrengthModel");
}
#endif // _UNITTEST
