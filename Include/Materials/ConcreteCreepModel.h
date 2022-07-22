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
      /// Abstract base class for a concrete shrinkage model. The purpose of this model is to 
      /// provide the free shrinkage strain of concrete at a specified age.
      class MATCLASS ConcreteCreepModel
      {
      public:
         ConcreteCreepModel() = default;
         ConcreteCreepModel(const ConcreteCreepModel& rOther) = default;

         virtual ~ConcreteCreepModel() = default;

         ConcreteCreepModel& operator=(const ConcreteCreepModel& rOther) = default;

         /// Returns the ratio of creep strain to initial strain (e.g. creep coefficient)
         /// \param t age of concrete (days)
         /// \param ti age of concrete at time of loading (days)
         virtual Float64 GetCreep(Float64 t,Float64 ti) const = 0;

#if defined _DEBUG
         virtual bool AssertValid() const;
         virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
      };
   };
};
