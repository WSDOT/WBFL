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
#include <FEA2D\Joint.h>
#include <FEA2D\Member.h>
#include <FEA2D\Loading.h>
#include <FEA2D\POI.h>
#include <WBFLTypes.h>
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <tchar.h>

// Native (non-COM) persistence interfaces - FEA2D has no ATL/COM dependency
// anywhere, including here; these headers are lightweight (no ATL/COM).
#include <System\IStructuredSave.h>
#include <System\IStructuredLoad.h>

namespace WBFL
{
   namespace FEA2D
   {
      /// The finite element model - owns every joint, member, loading, and
      /// POI, and exposes one natural signature per result-query type; the
      /// retained Fem2d COM facade fans that out to its several redundant
      /// result interfaces.
      ///
      /// There is no explicit "analyze now" step in this public API. Build
      /// the model, apply loads, and ask for results - the first query
      /// after a change transparently (re)factors the stiffness matrix if
      /// the structure changed, and (re)solves only the loadings whose
      /// loads actually changed, caching everything else. See the design
      /// note on EnsureAnalyzed() in Model.cpp for how that's done cheaply:
      /// [K][d]=[F] means K only needs factoring once per structural
      /// change, and each loading after that is a cheap back-substitution,
      /// not a full re-factorization.
      ///
      /// Index-based access iterates the underlying std::map in key (ID)
      /// order. This is not merely "an" ordering - the Fem2d COM facade's
      /// ATL collection template iterates its own map the same way (from
      /// begin() advancing idx times), and the facade's index-based access
      /// must stay bit-for-bit compatible with what its callers saw before,
      /// so this ordering is load-bearing, not incidental.
      class FEA2DCLASS Model
      {
      public:
         Model();
         ~Model();
         Model(const Model&) = delete;
         Model& operator=(const Model&) = delete;

         /// Removes every joint, member, loading, and POI, and discards any
         /// stored analysis results.
         void Clear() noexcept;

         // Joints
         Joint& CreateJoint(JointIDType id, Float64 x = 0.0, Float64 y = 0.0);
         Joint* FindJoint(JointIDType id) const noexcept;
         Joint* FindJointByIndex(IndexType index) const noexcept;
         bool RemoveJoint(JointIDType id);
         void ClearJoints() noexcept;
         IndexType GetJointCount() const noexcept;

         // Members
         Member& CreateMember(MemberIDType id, JointIDType startJoint, JointIDType endJoint, Float64 EA, Float64 EI);
         Member* FindMember(MemberIDType id) const noexcept;
         Member* FindMemberByIndex(IndexType index) const noexcept;
         bool RemoveMember(MemberIDType id);
         void ClearMembers() noexcept;
         IndexType GetMemberCount() const noexcept;

         /// Returns the IDs of every member whose start or end joint is
         /// jointId. Lives on Model, not Joint, because Model already owns
         /// the full member collection this query scans.
         std::vector<MemberIDType> GetAttachedMembers(JointIDType jointId) const;

         // Loadings
         Loading& CreateLoading(LoadCaseIDType id);
         Loading* FindLoading(LoadCaseIDType id) const noexcept;
         Loading* FindLoadingByIndex(IndexType index) const noexcept;
         bool RemoveLoading(LoadCaseIDType id);
         void ClearLoadings() noexcept;
         IndexType GetLoadingCount() const noexcept;

         // POIs
         POI& CreatePOI(PoiIDType id, MemberIDType memberID, Float64 location);
         POI* FindPOI(PoiIDType id) const noexcept;
         POI* FindPOIByIndex(IndexType index) const noexcept;
         bool RemovePOI(PoiIDType id);
         void ClearPOIs() noexcept;
         IndexType GetPOICount() const noexcept;

         // Equilibrium check tolerances (used to sanity-check the solution
         // after solving; default is 0.10 for both)
         Float64 GetForceEquilibriumTolerance() const noexcept;
         void SetForceEquilibriumTolerance(Float64 tol) noexcept;
         Float64 GetMomentEquilibriumTolerance() const noexcept;
         void SetMomentEquilibriumTolerance(Float64 tol) noexcept;

         // An optional, purely descriptive name - persisted, but otherwise
         // unused by FEA2D itself.
         const std::_tstring& GetName() const noexcept;
         void SetName(const std::_tstring& name);

         /// Serializes the full model (name, tolerances, joints, members,
         /// POIs, loadings) into an already-open WBFL::System::IStructuredSave,
         /// in the same on-disk format (version 3) that the retained Fem2d COM
         /// facade previously wrote directly (unit/property names and version
         /// numbers unchanged), so the facade can delegate its own Save() here
         /// via a COM-to-native adapter. Throws XFEA2D
         /// (ReasonCode::PersistenceIOError) if a storage call fails.
         void Save(WBFL::System::IStructuredSave* psave) const;
         /// Replaces the model's entire contents by deserializing from an
         /// already-open WBFL::System::IStructuredLoad (implicitly Clear()s
         /// first). Reads version 1/2/3 files. Throws XFEA2D
         /// (ReasonCode::PersistenceBadVersion / PersistenceInvalidFormat /
         /// PersistenceIOError) on a malformed or unreadable file.
         void Load(WBFL::System::IStructuredLoad* pload);

         // Results - one natural signature per query type; the retained
         // Fem2d COM facade fans this out to its three redundant result
         // interfaces rather than this core triplicating the logic. Each
         // of these transparently brings the model up to date first (see
         // the class-level note above) - throws XFEA2D if the model has
         // fewer than two joints or no members (ModelHasNoJoints /
         // ModelHasNoMembers), if the structure is unstable (MatrixFactoring
         // / MatrixBackSubstitution), if equilibrium isn't satisfied within
         // tolerance after solving (Joint/MemberEquilibriumNotSatisfied -
         // normally indicates a numerical/modeling bug, not a user input
         // error), or LoadingNotFound/JointNotFound/MemberNotFound if that
         // Loading/Joint/Member doesn't exist.
         void ComputeJointDeflections(LoadCaseIDType lc, JointIDType jointId, Float64* pDx, Float64* pDy, Float64* pRz) const;
         void ComputeMemberDeflections(LoadCaseIDType lc, MemberIDType memberId, Float64* pStartDx, Float64* pStartDy, Float64* pStartRz, Float64* pEndDx, Float64* pEndDy, Float64* pEndRz) const;
         void ComputeReactions(LoadCaseIDType lc, JointIDType jointId, Float64* pFx, Float64* pFy, Float64* pMz) const;
         /// orientation Member == results in member-local coordinates (the
         /// stored basis); orientation Global/GlobalProjected rotates into
         /// global coordinates.
         void ComputeMemberForces(LoadCaseIDType lc, MemberIDType memberId, LoadOrientation orientation, Float64* pStartFx, Float64* pStartFy, Float64* pStartMz, Float64* pEndFx, Float64* pEndFy, Float64* pEndMz) const;
         void ComputePOIDeflections(LoadCaseIDType lc, PoiIDType poiId, LoadOrientation orientation, Float64* pDx, Float64* pDy, Float64* pRz) const;
         void ComputePOIForces(LoadCaseIDType lc, PoiIDType poiId, MemberFaceType face, LoadOrientation orientation, Float64* pFx, Float64* pFy, Float64* pMz) const;

      private:
         friend class Joint;
         friend class Member;
         friend class Loading;
         friend class JointLoad;
         friend class PointLoad;
         friend class DistributedLoad;
         friend class MemberStrain;
         friend class JointDisplacement;
         friend class POI;

         std::map<JointIDType, std::unique_ptr<Joint>> m_Joints;
         std::map<MemberIDType, std::unique_ptr<Member>> m_Members;
         std::map<LoadCaseIDType, std::unique_ptr<Loading>> m_Loadings;
         std::map<PoiIDType, std::unique_ptr<POI>> m_POIs;

         // Dirty-notification hooks - called by the entity graph's mutators
         // (Joint/Member's structural setters; Loading's Create*/Remove*/
         // Clear*; the individual load types' value setters) when they
         // return true. Deliberately not a general observer/event system -
         // just enough state for EnsureAnalyzed() to know what's stale.
         void OnStructuralChange() const noexcept;
         void OnLoadingChanged(LoadCaseIDType lc) const noexcept;
         /// A POI's own location/member changed - its cached result (every
         /// loadcase) is stale, independent of any loading's dirty state.
         void InvalidatePOI(PoiIDType id) const noexcept;

         /// Brings the model up to date: (re)factors the stiffness matrix
         /// if the structure changed since the last call, then (re)solves
         /// and stores results for whichever loadings are still dirty
         /// (freshly created, changed, or invalidated by a structural
         /// change). Called at the top of every ComputeXxx method below -
         /// see the class-level design note. Logically const: from a
         /// caller's perspective the model's answers are unchanged, this
         /// only fills in memoized derived state. Physically achieved
         /// without `mutable` because m_pImpl and the four entity maps
         /// above are all unique_ptr-indirected, which doesn't propagate
         /// constness to the pointee - so every method this calls is
         /// itself const, all the way down.
         void EnsureAnalyzed() const;
         void CheckModel() const;
         void StiffnessAnalysis() const;
         void FemAnalysis() const;
         LONG ComputeBandWidth() const;
         void InitModel() const;
         void ClearLoads() const;
         void ClearAnalysis() const noexcept;
         void AssembleGlobalStiffnessMatrix() const;
         void AssembleGlobalForceVector() const;
         void AssembleJointLoads() const;
         void AssembleElementLoads() const;
         void ApplyJntDeflections() const;
         void ComputeAllMemberResults() const;
         void ComputeAllJointReactions() const;
         void CheckEquilibrium() const;
         void SolveDeflectionsClassical() const;
         void StoreJntResults(LoadCaseIDType lc) const;
         void StoreMbrResults(LoadCaseIDType lc) const;
         /// Drops any cached POI result for lc (every POI) - called after
         /// (re)solving lc, since those results were computed from the
         /// member results this just replaced.
         void InvalidateCachedPoiResults(LoadCaseIDType lc) const noexcept;
         /// Fills force[6] (left-face fx,fy,mz then right-face fx,fy,mz)
         /// and disp[3] (dx,dy,rz) for a POI, computing and caching the
         /// result on demand if it isn't already cached. Returns the
         /// values directly instead of a pointer into the (internal-only-
         /// typed) cache, so this stays nameable in the public header.
         void GetPoiResult(LoadCaseIDType lc, PoiIDType poiId, Float64 force[6], Float64 disp[3]) const;

         class ModelImpl;
         std::unique_ptr<ModelImpl> m_pImpl;
      };
   };
};
