///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright © 1999-2012  Washington State Department of Transportation
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

#include <Math\MathExp.h>
#include <Math\Function2d.h>


/*****************************************************************************
CLASS 
   mathPolynomial2d

DESCRIPTION
   Defines a polynomial function

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.17.1997 : Created file
*****************************************************************************/

class MATHCLASS mathPolynomial2d : public mathFunction2d
{
public:
   mathPolynomial2d();
   mathPolynomial2d(const mathPolynomial2d& rOther);
   mathPolynomial2d(const std::vector<Float64>& coefficients);
   virtual ~mathPolynomial2d();

   mathPolynomial2d& operator=(const mathPolynomial2d& rOther);

   void SetCoefficients(const std::vector<Float64>& coefficients);
   const std::vector<Float64>& GetCoefficients() const;
   
   virtual Float64 Evaluate(Float64 x) const;
   virtual mathFunction2d* Clone() const;

   mathPolynomial2d GetDerivative() const;

private:
   std::vector<Float64> m_Coefficients;
};
