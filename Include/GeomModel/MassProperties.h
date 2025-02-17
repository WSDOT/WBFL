///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright � 1999-2025  Washington State Department of Transportation
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

#include <GeomModel/GeomModelExp.h>

namespace WBFL
{
   namespace Geometry
   {
      /// This class encapsulates the mass properties of a section.
      class GEOMMODELCLASS MassProperties
      {
      public:
         MassProperties() = default;

         MassProperties(Float64 mpl);

         ~MassProperties() = default;

         MassProperties(const MassProperties&) = default;
         MassProperties& operator=(const MassProperties&) = default;

         MassProperties operator+(const MassProperties& other);
         MassProperties operator-(const MassProperties& other);

         MassProperties& operator+=(const MassProperties& other);
         MassProperties& operator-=(const MassProperties& other);

         /// Sets the mass per length of the section.
         void SetMassPerLength(Float64 mpl);
   
         /// Returns the mass per length of the section.
         Float64 GetMassPerLength() const;

      private:
         Float64  m_Mpl{ 0.0 };
      };
   }; // Geometry
}; // WBFL
