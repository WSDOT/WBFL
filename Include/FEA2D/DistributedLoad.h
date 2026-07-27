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
#include <FEA2D\Enums.h>
#include <WBFLTypes.h>
#include <memory>

namespace WBFL
{
   namespace FEA2D
   {
      class Loading;
      class Model;

      namespace Internals
      {
         class MbrLoad;
      };

      /// A trapezoidal distributed load applied over some or all of a
      /// member's length. Owned exclusively by the WBFL::FEA2D::Loading it
      /// was created on - see the design note on ownership/lifetime in
      /// Joint.h; the same applies here (private constructor and
      /// destructor, Loading as the only friend). See the Pimpl design
      /// note in PointLoad.h for why this doesn't inherit from
      /// Internals::MbrLoad directly.
      class FEA2DCLASS DistributedLoad
      {
      public:
         DistributedLoad(const DistributedLoad&) = delete;
         DistributedLoad& operator=(const DistributedLoad&) = delete;

         LoadIDType GetID() const noexcept;

         MemberIDType GetMemberID() const noexcept;
         bool SetMemberID(MemberIDType id) noexcept;

         LoadOrientation GetOrientation() const noexcept;
         /// Throws XFEA2D(ReasonCode::InvalidLoadOrientation) for an
         /// out-of-range enum value.
         bool SetOrientation(LoadOrientation orientation);

         LoadDirection GetDirection() const noexcept;
         bool SetDirection(LoadDirection direction) noexcept;

         /// Locations along the member: >= 0 is an absolute distance from
         /// the start joint; in [-1.0, 0.0) it's a fraction of the member
         /// length.
         Float64 GetStartLocation() const noexcept;
         /// Throws XFEA2D(ReasonCode::InvalidDistLoadLocation) if newVal < -1.0.
         bool SetStartLocation(Float64 location);
         Float64 GetEndLocation() const noexcept;
         /// Throws XFEA2D(ReasonCode::InvalidDistLoadLocation) if newVal < -1.0.
         bool SetEndLocation(Float64 location);

         Float64 GetWStart() const noexcept;
         bool SetWStart(Float64 w) noexcept;
         Float64 GetWEnd() const noexcept;
         bool SetWEnd(Float64 w) noexcept;

         /// Returns the ID of the Loading this load belongs to
         LoadCaseIDType GetLoadingID() const noexcept;

      private:
         friend class Loading;
         friend struct std::default_delete<DistributedLoad>; // see the design note in Joint.h

         DistributedLoad(Model* pModel, LoadCaseIDType loadingID, LoadIDType id, MemberIDType memberID, LoadDirection direction, Float64 startLocation, Float64 endLocation, Float64 wStart, Float64 wEnd, LoadOrientation orientation);
         ~DistributedLoad(); // defined out-of-line in DistributedLoad.cpp - Internals::MbrLoad is incomplete here

         /// Returns the MbrLoad-interface view of this load, for wiring
         /// into a Member's load list. Internal use only.
         Internals::MbrLoad* GetMbrLoad() const noexcept;

         Model* m_pModel; // for reporting this loadcase dirty on mutation (Model::OnLoadingChanged)
         LoadCaseIDType m_LoadingID;
         LoadIDType m_ID;
         MemberIDType m_MemberID;
         LoadOrientation m_Orientation;
         LoadDirection m_Direction;
         Float64 m_StartLocation;
         Float64 m_EndLocation;
         Float64 m_WStart;
         Float64 m_WEnd;

         class MbrLoadView;
         std::unique_ptr<Internals::MbrLoad> m_pMbrLoadView;
      };
   };
};
