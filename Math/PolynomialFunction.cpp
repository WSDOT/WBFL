///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
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

#include <Math\MathLib.h>
#include <Math\PolynomialFunction.h>
#include <Math\XFunction.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Math;

PolynomialFunction::PolynomialFunction(const std::vector<Float64>& coefficients) :
m_Coefficients(coefficients)
{
}

void PolynomialFunction::SetCoefficients(const std::vector<Float64>& coefficients)
{
   m_Coefficients = coefficients;
}

const std::vector<Float64>& PolynomialFunction::GetCoefficients() const
{
   return m_Coefficients;
}

Float64 PolynomialFunction::Evaluate(Float64 x) const
{
   if ( m_Coefficients.size() == 0 )
      THROW_FUNCTION(XFunction::Reason::Undefined);

   std::vector<Float64>::const_reverse_iterator iter;
   iter = m_Coefficients.rbegin();

   Float64 y = 0;
   Float64 X = 1;
   do 
   {
      Float64 K = *iter;
      y += K*X;

      iter++;
      X *= x;
   } while (iter != m_Coefficients.rend() );

   return y;
}

std::unique_ptr<Function> PolynomialFunction::Clone() const
{
   return std::make_unique<PolynomialFunction>(*this);
}

PolynomialFunction PolynomialFunction::GetDerivative() const
{
   std::vector<Float64> coefficients;

   std::vector<Float64>::const_reverse_iterator iter = m_Coefficients.rbegin();
   iter++; // skip last coefficient
   int C = 1;
   for ( ; iter != m_Coefficients.rend(); iter++, C++ )
   {
      Float64 K = *iter;
      coefficients.insert( coefficients.begin(), C*K );
   }

   ASSERT(coefficients.size() == m_Coefficients.size()-1);

   return PolynomialFunction(coefficients);
}

#if defined _UNITTEST
bool PolynomialFunction::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("PolynomialFunction");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for PolynomialFunction");
   TESTME_EPILOG("PolynomialFunction");
}
#endif
