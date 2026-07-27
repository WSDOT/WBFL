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
#include <FEA2D\JointLoad.h>
#include <FEA2D\JointDisplacement.h>
#include <FEA2D\PointLoad.h>
#include <FEA2D\DistributedLoad.h>
#include <FEA2D\MemberStrain.h>
#include <WBFLTypes.h>
#include <map>
#include <memory>

namespace WBFL
{
   namespace FEA2D
   {
      class Model;
      class Member;

      /// A load case - owns the five load-type collections applied to
      /// joints/members for this loading. Owned exclusively by the Model it
      /// was created on - see the design note on ownership/lifetime in
      /// Joint.h; the same applies here (private constructor and
      /// destructor, Model as the only friend). Loading is in turn the
      /// owner of its own five load-type collections, with the identical
      /// pattern applied one level down (see JointLoad.h etc.).
      ///
      /// Index-based access iterates the underlying std::map in key (ID)
      /// order - see the same note on Model.h.
      class FEA2DCLASS Loading
      {
      public:
         Loading(const Loading&) = delete;
         Loading& operator=(const Loading&) = delete;

         LoadCaseIDType GetID() const noexcept;

         // Joint loads
         JointLoad& CreateJointLoad(LoadIDType id, JointIDType jointID, Float64 Fx, Float64 Fy, Float64 Mz);
         JointLoad* FindJointLoad(LoadIDType id) const noexcept;
         JointLoad* FindJointLoadByIndex(IndexType index) const noexcept;
         bool RemoveJointLoad(LoadIDType id);
         void ClearJointLoads() noexcept;
         IndexType GetJointLoadCount() const noexcept;

         // Joint displacements (support settlements/rotations)
         JointDisplacement& CreateJointDisplacement(LoadIDType id, JointIDType jointID, Float64 Dx, Float64 Dy, Float64 Rz);
         JointDisplacement* FindJointDisplacement(LoadIDType id) const noexcept;
         JointDisplacement* FindJointDisplacementByIndex(IndexType index) const noexcept;
         bool RemoveJointDisplacement(LoadIDType id);
         void ClearJointDisplacements() noexcept;
         IndexType GetJointDisplacementCount() const noexcept;

         // Point loads
         PointLoad& CreatePointLoad(LoadIDType id, MemberIDType memberID, Float64 location, Float64 Fx, Float64 Fy, Float64 Mz, LoadOrientation orientation = LoadOrientation::Member);
         PointLoad* FindPointLoad(LoadIDType id) const noexcept;
         PointLoad* FindPointLoadByIndex(IndexType index) const noexcept;
         bool RemovePointLoad(LoadIDType id);
         void ClearPointLoads() noexcept;
         IndexType GetPointLoadCount() const noexcept;

         // Distributed loads
         DistributedLoad& CreateDistributedLoad(LoadIDType id, MemberIDType memberID, LoadDirection direction, Float64 startLocation, Float64 endLocation, Float64 wStart, Float64 wEnd, LoadOrientation orientation = LoadOrientation::Member);
         DistributedLoad* FindDistributedLoad(LoadIDType id) const noexcept;
         DistributedLoad* FindDistributedLoadByIndex(IndexType index) const noexcept;
         bool RemoveDistributedLoad(LoadIDType id);
         void ClearDistributedLoads() noexcept;
         IndexType GetDistributedLoadCount() const noexcept;

         // Member strains
         MemberStrain& CreateMemberStrain(LoadIDType id, MemberIDType memberID, Float64 startLocation, Float64 endLocation, Float64 axialStrain, Float64 curvatureStrain);
         MemberStrain* FindMemberStrain(LoadIDType id) const noexcept;
         MemberStrain* FindMemberStrainByIndex(IndexType index) const noexcept;
         bool RemoveMemberStrain(LoadIDType id);
         void ClearMemberStrains() noexcept;
         IndexType GetMemberStrainCount() const noexcept;

      private:
         friend class Model;
         friend struct std::default_delete<Loading>; // see the design note in Joint.h

         Loading(Model* pModel, LoadCaseIDType id);
         ~Loading() = default;

         // Applies every load in this Loading to the model - joint
         // loads/displacements to their referenced joints, point
         // loads/distributed loads/member strains to their referenced
         // members. Throws XFEA2D if a load references a joint/member that
         // doesn't exist. Called by Model::EnsureAnalyzed(). Takes a const
         // Model* since EnsureAnalyzed() is itself const (see the design
         // note there) - the lookups this does (FindJoint/FindMember) are
         // already const, and mutation happens through the Joint*/Member*
         // they return, which unique_ptr indirection keeps mutable
         // regardless of the Model's own constness.
         void ApplyLoads(const Model* pModel);
         // Narrower variant: applies only the point loads/distributed
         // loads/member strains in this Loading that reference pMember.
         void ApplyLoads(Member* pMember);

         Model* m_pModel;
         LoadCaseIDType m_ID;

         std::map<LoadIDType, std::unique_ptr<JointLoad>> m_JointLoads;
         std::map<LoadIDType, std::unique_ptr<JointDisplacement>> m_JointDisplacements;
         std::map<LoadIDType, std::unique_ptr<PointLoad>> m_PointLoads;
         std::map<LoadIDType, std::unique_ptr<DistributedLoad>> m_DistributedLoads;
         std::map<LoadIDType, std::unique_ptr<MemberStrain>> m_MemberStrains;
      };
   };
};
