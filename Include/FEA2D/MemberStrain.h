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
      class Model;
      class Loading;

      namespace Internals
      {
         class MbrLoad;
      };

      /// A uniform axial/curvature strain applied over some or all of a
      /// member's length (e.g. thermal gradient, prestress shortening).
      /// Owned exclusively by the WBFL::FEA2D::Loading it was created on -
      /// see the design note on ownership/lifetime in Joint.h; the same
      /// applies here (private constructor and destructor, Loading as the
      /// only friend). See the Pimpl design note in PointLoad.h for why
      /// this doesn't inherit from Internals::MbrLoad directly.
      ///
      /// Unlike PointLoad/DistributedLoad, MemberStrain's GetForceVector
      /// looks up the referenced member's EA/EI from the member itself
      /// rather than taking them as parameters like the other load types
      /// do - so it needs a Model* to resolve the member by ID.
      class FEA2DCLASS MemberStrain
      {
      public:
         MemberStrain(const MemberStrain&) = delete;
         MemberStrain& operator=(const MemberStrain&) = delete;

         LoadIDType GetID() const noexcept;

         MemberIDType GetMemberID() const noexcept;
         bool SetMemberID(MemberIDType id) noexcept;

         Float64 GetAxialStrain() const noexcept;
         bool SetAxialStrain(Float64 strain) noexcept;
         Float64 GetCurvatureStrain() const noexcept;
         bool SetCurvatureStrain(Float64 strain) noexcept;

         /// Locations along the member: >= 0 is an absolute distance from
         /// the start joint; in [-1.0, 0.0) it's a fraction of the member
         /// length.
         Float64 GetStartLocation() const noexcept;
         bool SetStartLocation(Float64 location) noexcept;
         Float64 GetEndLocation() const noexcept;
         bool SetEndLocation(Float64 location) noexcept;

         /// Returns the ID of the Loading this load belongs to
         LoadCaseIDType GetLoadingID() const noexcept;

      private:
         friend class Loading;
         friend struct std::default_delete<MemberStrain>; // see the design note in Joint.h

         MemberStrain(Model* pModel, LoadCaseIDType loadingID, LoadIDType id, MemberIDType memberID, Float64 xStart, Float64 xEnd, Float64 axialStrain, Float64 curvatureStrain);
         ~MemberStrain(); // defined out-of-line in MemberStrain.cpp - Internals::MbrLoad is incomplete here

         /// Returns the MbrLoad-interface view of this load, for wiring
         /// into a Member's load list. Internal use only.
         Internals::MbrLoad* GetMbrLoad() const noexcept;

         Model* m_pModel; // for resolving the referenced member's EA/EI in GetForceVector
         LoadCaseIDType m_LoadingID;
         LoadIDType m_ID;
         MemberIDType m_MemberID;
         Float64 m_AxialStrain;
         Float64 m_CurvatureStrain;
         Float64 m_StartLocation;
         Float64 m_EndLocation;

         class MbrLoadView;
         std::unique_ptr<Internals::MbrLoad> m_pMbrLoadView;
      };
   };
};
