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

      /// A concentrated force/moment applied at a location along a member.
      /// Owned exclusively by the WBFL::FEA2D::Loading it was created on -
      /// see the design note on ownership/lifetime in Joint.h; the same
      /// applies here (private constructor and destructor, Loading as the
      /// only friend).
      ///
      /// PointLoad implements the internal MbrLoad interface via a private
      /// companion object (m_pMbrLoadView) rather than by inheriting from
      /// Internals::MbrLoad directly - inheriting would require this public
      /// header to include the private MbrLoad.h. See the Pimpl design
      /// note at the top of Member.h for the same reasoning.
      class FEA2DCLASS PointLoad
      {
      public:
         PointLoad(const PointLoad&) = delete;
         PointLoad& operator=(const PointLoad&) = delete;

         LoadIDType GetID() const noexcept;

         MemberIDType GetMemberID() const noexcept;
         bool SetMemberID(MemberIDType id) noexcept;

         LoadOrientation GetOrientation() const noexcept;
         /// Throws XFEA2D(ReasonCode::InvalidLoadOrientation) for an
         /// out-of-range enum value.
         bool SetOrientation(LoadOrientation orientation);

         /// Location along the member: >= 0 is an absolute distance from
         /// the start joint; in [-1.0, 0.0) it's a fraction of the member
         /// length (e.g. -0.5 is midspan).
         Float64 GetLocation() const noexcept;
         /// Throws XFEA2D(ReasonCode::InvalidPointLoadLocation) if location < -1.0.
         bool SetLocation(Float64 location);

         void GetForce(Float64* pFx, Float64* pFy, Float64* pMz) const noexcept;
         /// Always reports changed, unconditionally
         void SetForce(Float64 Fx, Float64 Fy, Float64 Mz) noexcept;

         Float64 GetFx() const noexcept;
         bool SetFx(Float64 fx) noexcept;
         Float64 GetFy() const noexcept;
         bool SetFy(Float64 fy) noexcept;
         Float64 GetMz() const noexcept;
         bool SetMz(Float64 mz) noexcept;

         /// Returns the ID of the Loading this load belongs to
         LoadCaseIDType GetLoadingID() const noexcept;

      private:
         friend class Loading;
         friend struct std::default_delete<PointLoad>; // see the design note in Joint.h

         PointLoad(Model* pModel, LoadCaseIDType loadingID, LoadIDType id, MemberIDType memberID, Float64 location, Float64 Fx, Float64 Fy, Float64 Mz, LoadOrientation orientation);
         ~PointLoad(); // defined out-of-line in PointLoad.cpp - Internals::MbrLoad is incomplete here

         /// Returns the MbrLoad-interface view of this load, for wiring
         /// into a Member's load list. Internal use only.
         Internals::MbrLoad* GetMbrLoad() const noexcept;

         Model* m_pModel; // for reporting this loadcase dirty on mutation (Model::OnLoadingChanged)
         LoadCaseIDType m_LoadingID;
         LoadIDType m_ID;
         MemberIDType m_MemberID;
         LoadOrientation m_Orientation;
         Float64 m_Location;
         Float64 m_Fx;
         Float64 m_Fy;
         Float64 m_Mz;

         class MbrLoadView;
         std::unique_ptr<Internals::MbrLoad> m_pMbrLoadView;
      };
   };
};
