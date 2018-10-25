///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifndef INCLUDED_LRFD_LRFDTYPES_H_
#define INCLUDED_LRFD_LRFDTYPES_H_
#pragma once

// "Global" data types for the LRFD package
// These types aren't really global because they have been
// scoped in the lrfdTypes struct.
struct LRFDCLASS lrfdTypes
{
   enum Optimization { Min, Max };

   enum LimitState { StrengthI,
                     StrengthII,
                     StrengthIII,
                     StrengthIV,
                     StrengthV,
                     ExtremeEventI,
                     ExtremeEventII_IC,  // Extreme Event II with IC load
                     ExtremeEventII_CV,  // Extreme Event II with CV load
                     ExtremeEventII_CT,  // Extreme Event II with CT load
                     ServiceI,
                     ServiceIA,          // Service I with half dead load (5.9.4.2.1)
                     ServiceII,
                     ServiceIII,
                     FatigueI,
                     FatigueII,
                     LimitStateCount
   };
   enum LoadCombination { DC,
                          DD,
                          DW,
                          EH,
                          EV,
                          ES,
                          LLIM,
                          CE,
                          BR,
                          PL,
                          LS,
                          EL,
                          WA,
                          WS,
                          WL,
                          FR,
                          TU,
                          CR,
                          SH,
                          TG,
                          SE,
                          EQ,
                          IC,
                          CT,
                          CV,
                          LoadCombinationCount
   };
};

#endif // INCLUDED_LRFD_LRFDTYPES_H_