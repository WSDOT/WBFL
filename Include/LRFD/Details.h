///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <Lrfd\LrfdExp.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Struct containing details of rebar development length calculations
      struct LRFDCLASS REBARDEVLENGTHDETAILS
      {
         Float64 Ab; ///< Area of bar
         Float64 db; ///< diameter of bar
         Float64 fy; ///< yield strength
         Float64 fc; ///< concrete strength
         Float64 lambdaRl;  ///< Reinforcement location factor
         Float64 lambdaLw;  ///< Lightweight concrete modification factor or density modification factor
         Float64 lambdaCf; ///< Coating factor
         Float64 factor; ///< Total Factor applied to equation

         bool bRlCfLimit; ///< if true, lambdaRl*lambdaCf was limited to 1.7

         // Two equations for #11 or smaller (before 2015)
         Float64 ldb1; ///< Result of first equation
         Float64 ldb2; ///< Result of second equation
         Float64 ldb; ///< controlling value
         Float64 ld; ///< factor*ldb = development length
      };
   };
};

