///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <Lrfd\LrfdExp.h>

#include <Materials/SimpleConcrete.h>
#include <MathEx.h>

struct LRFDCLASS lrfdUHPCShearData
{
   // Input Parameters
   Float64 Mu{ 0.0 };
   Float64 Nu{ 0.0 };
   Float64 Vu{ 0.0 };
   Float64 phi{ 0.0 };
   Float64 Vp{ 0.0 };
   Float64 dv{ 0.0 }; // dv for longitudinal strain and longitudinal tension tie
   Float64 dv_uhpc{ Float64_Max }; // dv for use in Vuhpc and shear stress calculations, but not more than dv
   Float64 bv{ 0.0 };
   Float64 Es{ 0.0 };
   Float64 As{ 0.0 };
   Float64 Eps{ 0.0 };
   Float64 Aps{ 0.0 };
   Float64 Ec{ 0.0 };
   Float64 Ac{ 0.0 };
   Float64 fpo{ 0.0 };
   Float64 ft{ 0.0 };
   Float64 ftloc{ 0.0 };
   Float64 etloc{ 0.0 };
   Float64 etcr{ 0.0 };
   Float64 alpha{ PI_OVER_2 };
   Float64 gamma_u{ 0.0 };

   Float64 fy{ 0.0 };
   Float64 AvS{ 0.0 }; // Av/s per 5.8.2.5 (equation 5.8.2.5-1)

   // Output Parameters
   Float64 fv{ 0.0 };
   Float64 Theta{ 0.0 };
   Float64 rho{ 0.0 };
   Float64 es{ 0.0 };
   Float64 e2{ 0.0 };
   Float64 ev{ 0.0 };

   Float64 dv_per_1_7_2_8() const { return Min(dv, dv_uhpc); }
};

class LRFDCLASS lrfdUHPCShear
{
public:
   lrfdUHPCShear() = delete;
    ~lrfdUHPCShear() = delete;

   static bool ComputeShearResistanceParameters(lrfdUHPCShearData* pData);

#if defined _UNITTEST
public:
   static bool TestMe(WBFL::Debug::Log& rlog);
private:
   static bool TestCase1(WBFL::Debug::Log& rlog);
   static bool TestCase2(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
};
