///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
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

#include <FEA2D\FEA2DExp.h>
#include <WBFLTypes.h>
#include <memory>

namespace WBFL
{
   namespace FEA2D
   {
      class Model;

      /// A point of interest - a query location along a member, used to
      /// request results (forces/deflections) without creating a joint
      /// there. Owned exclusively by the Model it was created on - see the
      /// design note on ownership/lifetime in Joint.h; the same applies
      /// here (private constructor and destructor, Model as the only
      /// friend). Unlike the load types, POI carries no analysis behavior
      /// of its own - it's a location marker consulted later by the
      /// results-computation surface.
      class FEA2DCLASS POI
      {
      public:
         POI(const POI&) = delete;
         POI& operator=(const POI&) = delete;

         PoiIDType GetID() const noexcept;

         MemberIDType GetMemberID() const noexcept;
         bool SetMemberID(MemberIDType id) noexcept;

         /// Location along the member: >= 0 is an absolute distance from
         /// the start joint; in [-1.0, 0.0) it's a fraction of the member
         /// length.
         Float64 GetLocation() const noexcept;
         /// Throws XFEA2D(ReasonCode::InvalidPoiLocation) if location < -1.0.
         bool SetLocation(Float64 location);

      private:
         friend class Model;
         friend struct std::default_delete<POI>; // see the design note in Joint.h

         /// Throws XFEA2D(ReasonCode::InvalidPoiLocation) if location < -1.0.
         POI(Model* pModel, PoiIDType id, MemberIDType memberID, Float64 location);
         ~POI() = default;

         Model* m_pModel; // for invalidating this POI's cached result on mutation (Model::InvalidatePOI)
         PoiIDType m_ID;
         MemberIDType m_MemberID;
         Float64 m_Location;
      };
   };
};
