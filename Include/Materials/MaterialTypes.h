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
      /// Constant indicating a type of concrete
      enum class ConcreteType { Normal, AllLightweight, SandLightweight, PCI_UHPC, FHWA_UHPC };

      /// Constant indicating a cement type
      enum class CementType { TypeI, TypeII };

      /// Constant a curing type
      enum class CuringType { Moist, Steam };

      /// Utility  method that returns if a concrete type is UHPC
      inline bool IsUHPC(WBFL::Materials::ConcreteType type)
      {
         return (type == WBFL::Materials::ConcreteType::PCI_UHPC || type == WBFL::Materials::ConcreteType::FHWA_UHPC) ? true : false;
      }

      /// Constant indicating the grade of prestressing strand
      enum class StrandGrade
      {
         Grade250, ///< Prestressing is Grade 250 (250 ksi)
         Grade270, ///< Prestressing is Grade 270 (270 ksi)
         Grade300  ///< Prestressing is Grade 300 (300 ksi)
      };

      /// Constant indicating the production type of prestressing strand
      enum class StrandType
      {
         LowRelaxation, ///< strand has low relaxation properties
         StressRelieved ///< strand has stress relieved properties
      };
   
      /// Constant indicating the type of longitudinal reinforcement modeled in a CircularManderSection
      enum class TransvReinforcementType
      {
         Spiral = 0, ///< Transverse reinforcement is a continuous spiral
         Hoops = 1   ///< Transverse reinforcement is discrete hoops
      };
   };
};

