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

#include <FEA2D\FEA2DLib.h>
#include "ModelImpl.h"
#include <FEA2D\XFEA2D.h>

#include <cmath>
#include <cstdlib>
#include <MathEx.h>

using namespace WBFL::FEA2D;

namespace
{
   constexpr Float64 EPS = 0.10; // default equilibrium tolerance (also what the Fem2d COM facade needs for behavioral continuity)
}

Model::Model() :
   m_pImpl(std::make_unique<ModelImpl>())
{
}

Model::~Model() = default;

void Model::Clear() noexcept
{
   m_Joints.clear();
   m_Members.clear();
   m_Loadings.clear();
   m_POIs.clear();

   ClearAnalysis();

   // a cleared model is like a freshly-constructed one: nothing to solve yet
   m_pImpl->m_bStructuralDirty = true;
   m_pImpl->m_DirtyLoadings.clear();
}

Joint& Model::CreateJoint(JointIDType id, Float64 x, Float64 y)
{
   if (m_Joints.find(id) != m_Joints.end())
   {
      THROW_FEA2D(ReasonCode::JointWithIdAlreadyExists);
   }

   auto joint = std::unique_ptr<Joint>(new Joint(this, id, x, y));
   Joint* pJoint = joint.get();
   m_Joints.emplace(id, std::move(joint));
   OnStructuralChange();
   return *pJoint;
}

Joint* Model::FindJoint(JointIDType id) const noexcept
{
   auto it = m_Joints.find(id);
   return it == m_Joints.end() ? nullptr : it->second.get();
}

Joint* Model::FindJointByIndex(IndexType index) const noexcept
{
   if (m_Joints.size() <= index)
      return nullptr;

   auto it = m_Joints.begin();
   std::advance(it, index);
   return it->second.get();
}

bool Model::RemoveJoint(JointIDType id)
{
   bool removed = m_Joints.erase(id) != 0;
   if (removed)
   {
      OnStructuralChange();
   }
   return removed;
}

void Model::ClearJoints() noexcept
{
   if (!m_Joints.empty())
   {
      m_Joints.clear();
      OnStructuralChange();
   }
}

IndexType Model::GetJointCount() const noexcept
{
   return m_Joints.size();
}

Member& Model::CreateMember(MemberIDType id, JointIDType startJoint, JointIDType endJoint, Float64 EA, Float64 EI)
{
   // matches legacy MemberCollection::Create's eager same-joints check -
   // Member::GetLength() also checks this lazily (for a member whose
   // joints were changed post-creation via SetStartJoint/SetEndJoint), but
   // Create() itself must reject it immediately too.
   if (startJoint == endJoint)
   {
      THROW_FEA2D(ReasonCode::MemberHasSameJoints);
   }

   if (m_Members.find(id) != m_Members.end())
   {
      THROW_FEA2D(ReasonCode::MemberWithIdAlreadyExists);
   }

   auto member = std::unique_ptr<Member>(new Member(this, id, startJoint, endJoint, EA, EI));
   Member* pMember = member.get();
   m_Members.emplace(id, std::move(member));
   OnStructuralChange();
   return *pMember;
}

Member* Model::FindMember(MemberIDType id) const noexcept
{
   auto it = m_Members.find(id);
   return it == m_Members.end() ? nullptr : it->second.get();
}

Member* Model::FindMemberByIndex(IndexType index) const noexcept
{
   if (m_Members.size() <= index)
      return nullptr;

   auto it = m_Members.begin();
   std::advance(it, index);
   return it->second.get();
}

bool Model::RemoveMember(MemberIDType id)
{
   bool removed = m_Members.erase(id) != 0;
   if (removed)
   {
      OnStructuralChange();
   }
   return removed;
}

void Model::ClearMembers() noexcept
{
   if (!m_Members.empty())
   {
      m_Members.clear();
      OnStructuralChange();
   }
}

IndexType Model::GetMemberCount() const noexcept
{
   return m_Members.size();
}

std::vector<MemberIDType> Model::GetAttachedMembers(JointIDType jointId) const
{
   std::vector<MemberIDType> result;
   for (const auto& [id, pMember] : m_Members)
   {
      if (pMember->GetStartJoint() == jointId || pMember->GetEndJoint() == jointId)
      {
         result.push_back(id);
      }
   }
   return result;
}

Loading& Model::CreateLoading(LoadCaseIDType id)
{
   if (m_Loadings.find(id) != m_Loadings.end())
   {
      THROW_FEA2D(ReasonCode::LoadingWithIdAlreadyExists);
   }

   auto loading = std::unique_ptr<Loading>(new Loading(this, id));
   Loading* pLoading = loading.get();
   m_Loadings.emplace(id, std::move(loading));
   OnLoadingChanged(id);
   return *pLoading;
}

Loading* Model::FindLoading(LoadCaseIDType id) const noexcept
{
   auto it = m_Loadings.find(id);
   return it == m_Loadings.end() ? nullptr : it->second.get();
}

Loading* Model::FindLoadingByIndex(IndexType index) const noexcept
{
   if (m_Loadings.size() <= index)
      return nullptr;

   auto it = m_Loadings.begin();
   std::advance(it, index);
   return it->second.get();
}

bool Model::RemoveLoading(LoadCaseIDType id)
{
   bool removed = m_Loadings.erase(id) != 0;
   if (removed)
   {
      // this loadcase no longer exists - drop it from the dirty set (no
      // longer anything to solve) and purge any stale cached results for
      // it, so a query against a removed-then-different-loading-recreated
      // id can't accidentally see stale data, and a query against a
      // removed-and-never-recreated id throws LoadingNotFound instead of
      // silently returning what used to be there
      m_pImpl->m_DirtyLoadings.erase(id);
      for (auto& [jid, array] : m_pImpl->m_JntResults) { array->Remove(id); }
      for (auto& [mid, array] : m_pImpl->m_MbrResults) { array->Remove(id); }
      InvalidateCachedPoiResults(id);
   }
   return removed;
}

void Model::ClearLoadings() noexcept
{
   if (!m_Loadings.empty())
   {
      m_Loadings.clear();
      m_pImpl->m_DirtyLoadings.clear();
      m_pImpl->m_JntResults.clear();
      m_pImpl->m_MbrResults.clear();
      m_pImpl->m_PoiResults.clear();
      m_pImpl->m_SimplePOIResultCache.ClearCache();
   }
}

IndexType Model::GetLoadingCount() const noexcept
{
   return m_Loadings.size();
}

POI& Model::CreatePOI(PoiIDType id, MemberIDType memberID, Float64 location)
{
   if (m_POIs.find(id) != m_POIs.end())
   {
      THROW_FEA2D(ReasonCode::PoiWithIdAlreadyExists);
   }

   auto poi = std::unique_ptr<POI>(new POI(this, id, memberID, location)); // may itself throw InvalidPoiLocation
   POI* pPOI = poi.get();
   m_POIs.emplace(id, std::move(poi));
   return *pPOI;
}

POI* Model::FindPOI(PoiIDType id) const noexcept
{
   auto it = m_POIs.find(id);
   return it == m_POIs.end() ? nullptr : it->second.get();
}

POI* Model::FindPOIByIndex(IndexType index) const noexcept
{
   if (m_POIs.size() <= index)
      return nullptr;

   auto it = m_POIs.begin();
   std::advance(it, index);
   return it->second.get();
}

bool Model::RemovePOI(PoiIDType id)
{
   bool removed = m_POIs.erase(id) != 0;
   if (removed)
   {
      // drop any cached result for the now-gone POI, so a later query
      // against a removed-and-recreated id can't see stale data (and a
      // query against a removed id throws PoiNotFound rather than serving
      // whatever was last cached for it)
      InvalidatePOI(id);
   }
   return removed;
}

void Model::ClearPOIs() noexcept
{
   m_POIs.clear();
   m_pImpl->m_PoiResults.clear();
   m_pImpl->m_SimplePOIResultCache.ClearCache();
}

IndexType Model::GetPOICount() const noexcept
{
   return m_POIs.size();
}

////////////////////////////////////////////////////////////////////////////////
/////////// Dirty-notification hooks (see EnsureAnalyzed() below) //////////////
////////////////////////////////////////////////////////////////////////////////

void Model::OnStructuralChange() const noexcept
{
   m_pImpl->m_bStructuralDirty = true;
}

void Model::OnLoadingChanged(LoadCaseIDType lc) const noexcept
{
   m_pImpl->m_DirtyLoadings.insert(lc);
}

void Model::InvalidatePOI(PoiIDType id) const noexcept
{
   m_pImpl->m_PoiResults.erase(id);
   // cheap and always correct to drop unconditionally rather than checking
   // whether the 1-slot cache happens to hold this POI right now
   m_pImpl->m_SimplePOIResultCache.ClearCache();
}

void Model::InvalidateCachedPoiResults(LoadCaseIDType lc) const noexcept
{
   for (auto& [id, array] : m_pImpl->m_PoiResults)
   {
      array->Remove(lc);
   }
   m_pImpl->m_SimplePOIResultCache.ClearCache();
}

Float64 Model::GetForceEquilibriumTolerance() const noexcept
{
   return m_pImpl->m_ForceEquilibriumTolerance;
}

void Model::SetForceEquilibriumTolerance(Float64 tol) noexcept
{
   m_pImpl->m_ForceEquilibriumTolerance = tol;
}

Float64 Model::GetMomentEquilibriumTolerance() const noexcept
{
   return m_pImpl->m_MomentEquilibriumTolerance;
}

void Model::SetMomentEquilibriumTolerance(Float64 tol) noexcept
{
   m_pImpl->m_MomentEquilibriumTolerance = tol;
}

const std::_tstring& Model::GetName() const noexcept
{
   return m_pImpl->m_Name;
}

void Model::SetName(const std::_tstring& name)
{
   m_pImpl->m_Name = name;
}

////////////////////////////////////////////////////////////////////////////////
/////////// FEM Analysis Related Functions /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// [K][d]=[F]: K only depends on the structure (joints/members/releases/
// EA/EI), not on any loading, so it only needs assembling and factoring
// once per structural change (StiffnessAnalysis()/FemAnalysis() below,
// gated on m_bStructuralDirty) - every loading after that is a cheap
// back-substitution against the already-factored K (the m_K.Solve() call
// in the loop below), not a re-factorization. A structural change
// invalidates every loading's stored results (the DOF numbering itself
// changed), which is why it also repopulates m_DirtyLoadings with every
// loading id; a loading-only change (a load added/removed/edited) only
// needs that one loading's entry in m_DirtyLoadings.
void Model::EnsureAnalyzed() const
{
   if (m_pImpl->m_bStructuralDirty)
   {
      CheckModel();
      StiffnessAnalysis(); // reassembles + factors K; also clears every stored result (ClearAnalysis())
      m_pImpl->m_bStructuralDirty = false;

      m_pImpl->m_DirtyLoadings.clear();
      for (const auto& [lc, pLoading] : m_Loadings)
      {
         m_pImpl->m_DirtyLoadings.insert(lc);
      }
   }

   if (m_pImpl->m_DirtyLoadings.empty())
   {
      return;
   }

   for (LoadCaseIDType lc : m_pImpl->m_DirtyLoadings)
   {
      Loading* pLoading = FindLoading(lc);
      CHECK(pLoading != nullptr); // RemoveLoading/ClearLoadings drop removed ids from m_DirtyLoadings

      ClearLoads();
      pLoading->ApplyLoads(this);

      if (0 < m_pImpl->m_NumCondensedDOF)
      {
         AssembleGlobalForceVector();

         try
         {
            m_pImpl->m_K.Solve(m_pImpl->m_pF);
         }
         catch (Internals::SymBandedMatrix::SymBandedSolverException&)
         {
            THROW_FEA2D(ReasonCode::MatrixBackSubstitution);
         }

         ApplyJntDeflections();
      }
      else
      {
         SolveDeflectionsClassical();
      }

      ComputeAllMemberResults();
      ComputeAllJointReactions();
      CheckEquilibrium();
      StoreJntResults(lc);
      StoreMbrResults(lc);
      InvalidateCachedPoiResults(lc); // these results just got replaced - any cached POI result derived from the old ones is stale
   }
   m_pImpl->m_DirtyLoadings.clear();
}

void Model::CheckModel() const
{
   // must have at least two joints to have a model
   if (m_Joints.size() < 2)
   {
      THROW_FEA2D(ReasonCode::ModelHasNoJoints);
   }

   // must have at least one member
   if (m_Members.size() < 1)
   {
      THROW_FEA2D(ReasonCode::ModelHasNoMembers);
   }
}

void Model::StiffnessAnalysis() const
{
   ClearAnalysis();
   InitModel();

   if (0 < m_pImpl->m_NumCondensedDOF)
   {
      FemAnalysis();
   }
}

void Model::FemAnalysis() const
{
   m_pImpl->m_BandWidth = ComputeBandWidth();

   AssembleGlobalStiffnessMatrix();

   try
   {
      m_pImpl->m_K.Factor();
   }
   catch (Internals::SymBandedMatrix::SymBandedSolverException&)
   {
      THROW_FEA2D(ReasonCode::MatrixFactoring);
   }
}

LONG Model::ComputeBandWidth() const
{
   LONG bw = 1;
   for (const auto& [id, pMember] : m_Members)
   {
      LONG nDOF = pMember->GetNumDOF();
      for (LONG j = 0; j < nDOF; j++)
      {
         for (LONG k = 0; k < nDOF; k++)
         {
            LONG dof1 = pMember->GetCondensedDOF(j);
            LONG dof2 = pMember->GetCondensedDOF(k);
            if (dof1 >= 0 && dof2 >= 0)
            {
               bw = Max(bw, (LONG)(std::abs(dof1 - dof2) + 1));
            }
         }
      }
   }

   return bw;
}

void Model::InitModel() const
{
   // Initialize joints by assigning global and condensed dof numbers
   m_pImpl->m_NumCondensedDOF = 0;
   m_pImpl->m_NumGlobalDOF = 0;

   for (auto& [id, pJoint] : m_Joints)
   {
      LONG nGDOFused, nCDOFused;
      pJoint->InitModel(m_pImpl->m_NumGlobalDOF, m_pImpl->m_NumCondensedDOF, nGDOFused, nCDOFused);
      m_pImpl->m_NumGlobalDOF += nGDOFused;
      m_pImpl->m_NumCondensedDOF += nCDOFused;
   }

   // Allow all the members a chance to initialize themselves
   for (auto& [id, pMember] : m_Members)
   {
      pMember->InitModel();
   }
}

void Model::ClearLoads() const
{
   for (auto& [id, pJoint] : m_Joints)
   {
      pJoint->ClearLoads();
   }

   for (auto& [id, pMember] : m_Members)
   {
      pMember->ClearLoads();
   }
}

void Model::ClearAnalysis() const noexcept
{
   m_pImpl->m_JntResults.clear();
   m_pImpl->m_MbrResults.clear();
   m_pImpl->m_PoiResults.clear();
   m_pImpl->m_SimplePOIResultCache.ClearCache();

   m_pImpl->FreeFGlobal();

   m_pImpl->m_BandWidth = -1;
   m_pImpl->m_NumGlobalDOF = -1;
   m_pImpl->m_NumCondensedDOF = -1;
}

void Model::AssembleGlobalStiffnessMatrix() const
{
   m_pImpl->m_K.Resize(m_pImpl->m_NumCondensedDOF, m_pImpl->m_BandWidth);
   m_pImpl->m_K.Zero();

   for (auto& [id, pMember] : m_Members)
   {
      LONG dof = pMember->GetNumDOF();

      for (LONG i = 0; i < dof; i++)
      {
         for (LONG j = 0; j < dof; j++)
         {
            LONG CDOFi = pMember->GetCondensedDOF(i);
            LONG CDOFj = pMember->GetCondensedDOF(j);

            if (CDOFi >= 0 && CDOFj >= 0 && CDOFj >= CDOFi) // only map symmetrical values (upper triangle)
            {
               Float64 k = pMember->GetKglobal(i, j);
               m_pImpl->m_K.SumVal(CDOFi, CDOFj, k);
            }
         }
      }
   }
}

void Model::AssembleGlobalForceVector() const
{
   if (m_pImpl->m_pF == nullptr)
   {
      m_pImpl->m_pF = new Float64[m_pImpl->m_NumCondensedDOF];
   }

   for (LONG i = 0; i < m_pImpl->m_NumCondensedDOF; i++)
   {
      m_pImpl->m_pF[i] = 0.0;
   }

   AssembleJointLoads();
   AssembleElementLoads();
}

void Model::AssembleJointLoads() const
{
   Float64 f[Joint::NumDof];

   for (auto& [id, pJoint] : m_Joints)
   {
      pJoint->GetFglobal(f);

      for (LONG i = 0; i < Joint::NumDof; i++)
      {
         LONG dof = pJoint->GetCondensedDOF(i);
         if (dof >= 0)
         {
            m_pImpl->m_pF[dof] += f[i];
         }
      }
   }
}

void Model::AssembleElementLoads() const
{
   Float64 f[Member::TotalDOF];

   for (auto& [id, pMember] : m_Members)
   {
      LONG ndof = pMember->GetNumDOF();

      // Each member has to assemble its force vector in global coordinates
      // before it can be integrated into the global force vector.
      pMember->AssembleF();
      pMember->GetFglobal(f);

      for (LONG dof = 0; dof < ndof; dof++)
      {
         LONG cdof = pMember->GetCondensedDOF(dof);
         if (cdof >= 0)
         {
            m_pImpl->m_pF[cdof] += f[dof];
         }
      }
   }
}

void Model::ApplyJntDeflections() const
{
   Float64 disp[Joint::NumDof];

   for (auto& [id, pJoint] : m_Joints)
   {
      for (LONG dof = 0; dof < Joint::NumDof; dof++)
      {
         LONG cdof = pJoint->GetCondensedDOF(dof);
         disp[dof] = (cdof < 0) ? 0.0 : m_pImpl->m_pF[cdof];
      }

      // Apply the deflection to the joint for use in further results processing.
      pJoint->SetDeflection(disp);
   }
}

void Model::ComputeAllMemberResults() const
{
   for (auto& [id, pMember] : m_Members)
   {
      pMember->ComputeResults();
   }
}

void Model::ComputeAllJointReactions() const
{
   for (auto& [id, pJoint] : m_Joints)
   {
      pJoint->ComputeReactions();
   }
}

void Model::SolveDeflectionsClassical() const
{
   // Since all global dof's are constrained, all global deflections are
   // zero. Individual members adjust their own end rotations based on
   // member end boundary conditions (see Member::ComputeDeflections).
   const Float64 disp[3] = { 0, 0, 0 };

   for (auto& [id, pJoint] : m_Joints)
   {
      pJoint->SetDeflection(disp);
   }
}

void Model::CheckEquilibrium() const
{
   Float64 forceTol = m_pImpl->m_ForceEquilibriumTolerance;
   Float64 momentTol = m_pImpl->m_MomentEquilibriumTolerance;

   for (auto& [id, pJoint] : m_Joints)
   {
      if (!pJoint->IsEquilibriumSatisfied(forceTol, momentTol))
      {
         THROW_FEA2D(ReasonCode::JointEquilibriumNotSatisfied);
      }
   }

   for (auto& [id, pMember] : m_Members)
   {
      if (!pMember->IsEquilibriumSatisfied(forceTol, momentTol))
      {
         THROW_FEA2D(ReasonCode::MemberEquilibriumNotSatisfied);
      }
   }
}

//////////// Results storage and retrieval

void Model::StoreJntResults(LoadCaseIDType lc) const
{
   Float64 force[Joint::NumDof];
   Float64 disp[Joint::NumDof];

   for (auto& [id, pJoint] : m_Joints)
   {
      pJoint->GetReactions(force);
      pJoint->GetDeflection(disp);

      auto it = m_pImpl->m_JntResults.find(id);
      ModelImpl::JntResultArray* array;
      if (it != m_pImpl->m_JntResults.end())
      {
         array = it->second.get();
      }
      else
      {
         auto newArray = std::make_unique<ModelImpl::JntResultArray>(id);
         array = newArray.get();
         m_pImpl->m_JntResults.emplace(id, std::move(newArray));
      }

      ModelImpl::JntResult* pres = array->Find(lc);
      if (pres != nullptr)
      {
         pres->SetActions(force, disp);
      }
      else
      {
         ModelImpl::JntResult result(lc, force, disp);
         array->Add(result);
      }
   }
}

void Model::StoreMbrResults(LoadCaseIDType lc) const
{
   for (auto& [id, pMember] : m_Members)
   {
      auto it = m_pImpl->m_MbrResults.find(id);
      ModelImpl::MbrResultArray* array;
      if (it != m_pImpl->m_MbrResults.end())
      {
         array = it->second.get();
      }
      else
      {
         auto newArray = std::make_unique<ModelImpl::MbrResultArray>(id);
         array = newArray.get();
         m_pImpl->m_MbrResults.emplace(id, std::move(newArray));
      }

      ModelImpl::MbrResult result(lc);
      pMember->GetResults(&result);

      ModelImpl::MbrResult* pres = array->Find(lc);
      if (pres != nullptr)
      {
         *pres = result;
      }
      else
      {
         array->Add(result);
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
/////////// Results query surface ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Model::ComputeJointDeflections(LoadCaseIDType lc, JointIDType jointId, Float64* pDx, Float64* pDy, Float64* pRz) const
{
   EnsureAnalyzed();

   auto it = m_pImpl->m_JntResults.find(jointId);
   if (it == m_pImpl->m_JntResults.end())
   {
      THROW_FEA2D(ReasonCode::JointNotFound);
   }

   const ModelImpl::JntResult* result = it->second->Find(lc);
   if (result == nullptr)
   {
      THROW_FEA2D(ReasonCode::LoadingNotFound);
   }

   *pDx = result->GetDeflection(0);
   *pDy = result->GetDeflection(1);
   *pRz = result->GetDeflection(2);
}

void Model::ComputeMemberDeflections(LoadCaseIDType lc, MemberIDType memberId, Float64* pStartDx, Float64* pStartDy, Float64* pStartRz, Float64* pEndDx, Float64* pEndDy, Float64* pEndRz) const
{
   EnsureAnalyzed();

   auto it = m_pImpl->m_MbrResults.find(memberId);
   if (it == m_pImpl->m_MbrResults.end())
   {
      THROW_FEA2D(ReasonCode::MemberNotFound);
   }

   const ModelImpl::MbrResult* result = it->second->Find(lc);
   if (result == nullptr)
   {
      THROW_FEA2D(ReasonCode::LoadingNotFound);
   }

   *pStartDx = result->GetDeflection(0);
   *pStartDy = result->GetDeflection(1);
   *pStartRz = result->GetDeflection(2);
   *pEndDx = result->GetDeflection(3);
   *pEndDy = result->GetDeflection(4);
   *pEndRz = result->GetDeflection(5);
}

void Model::ComputeReactions(LoadCaseIDType lc, JointIDType jointId, Float64* pFx, Float64* pFy, Float64* pMz) const
{
   EnsureAnalyzed();

   auto it = m_pImpl->m_JntResults.find(jointId);
   if (it == m_pImpl->m_JntResults.end())
   {
      THROW_FEA2D(ReasonCode::JointNotFound);
   }

   const ModelImpl::JntResult* result = it->second->Find(lc);
   if (result == nullptr)
   {
      THROW_FEA2D(ReasonCode::LoadingNotFound);
   }

   *pFx = result->GetForce(0);
   *pFy = result->GetForce(1);
   *pMz = result->GetForce(2);
}

void Model::ComputeMemberForces(LoadCaseIDType lc, MemberIDType memberId, LoadOrientation orientation, Float64* pStartFx, Float64* pStartFy, Float64* pStartMz, Float64* pEndFx, Float64* pEndFy, Float64* pEndMz) const
{
   EnsureAnalyzed();

   auto it = m_pImpl->m_MbrResults.find(memberId);
   if (it == m_pImpl->m_MbrResults.end())
   {
      THROW_FEA2D(ReasonCode::MemberNotFound);
   }

   const ModelImpl::MbrResult* result = it->second->Find(lc);
   if (result == nullptr)
   {
      THROW_FEA2D(ReasonCode::LoadingNotFound);
   }

   if (orientation == LoadOrientation::Member)
   {
      // member results are stored in local coords
      *pStartFx = result->GetForce(0);
      *pStartFy = result->GetForce(1);
      *pStartMz = result->GetForce(2);
      *pEndFx = result->GetForce(3);
      *pEndFy = result->GetForce(4);
      *pEndMz = result->GetForce(5);
   }
   else
   {
      if (orientation != LoadOrientation::Global && orientation != LoadOrientation::GlobalProjected)
      {
         THROW_FEA2D(ReasonCode::InvalidLoadOrientation);
      }

      // orient results into global coords - get orientation of member and
      // rotate results into global coordinates
      Member* mbr = FindMember(memberId);
      CHECK(mbr != nullptr); // the lookup above (m_pImpl->m_MbrResults) should have caught a missing member already

      Float64 ang = mbr->GetAngle();
      Float64 c = cos(ang);
      Float64 s = sin(ang);

      Float64 fx = result->GetForce(0);
      Float64 fy = result->GetForce(1);
      *pStartFx = fx * c - fy * s;
      *pStartFy = fx * s + fy * c;
      *pStartMz = result->GetForce(2);

      fx = result->GetForce(3);
      fy = result->GetForce(4);
      *pEndFx = fx * c - fy * s;
      *pEndFy = fx * s + fy * c;
      *pEndMz = result->GetForce(5);
   }
}

void Model::GetPoiResult(LoadCaseIDType lc, PoiIDType poiId, Float64 force[6], Float64 disp[3]) const
{
   // look in the simple (negative-load-case) cache first
   if (m_pImpl->m_SimplePOIResultCache.IsHit(poiId, lc))
   {
      const ModelImpl::PoiResult& cached = m_pImpl->m_SimplePOIResultCache.m_PoiResult;
      for (int i = 0; i < 6; i++) force[i] = cached.GetForce(i);
      for (int i = 0; i < 3; i++) disp[i] = cached.GetDeflection(i);
      return;
   }

   // then the long-term (positive-load-case) cache
   auto poiIt = m_pImpl->m_PoiResults.find(poiId);
   if (poiIt != m_pImpl->m_PoiResults.end())
   {
      const ModelImpl::PoiResult* cached = poiIt->second->Find(lc);
      if (cached != nullptr)
      {
         for (int i = 0; i < 6; i++) force[i] = cached->GetForce(i);
         for (int i = 0; i < 3; i++) disp[i] = cached->GetDeflection(i);
         return;
      }
   }

   // not cached - compute it now
   POI* poi = FindPOI(poiId);
   if (poi == nullptr)
   {
      THROW_FEA2D(ReasonCode::PoiNotFound);
   }

   MemberIDType mid = poi->GetMemberID();
   Member* mbr = FindMember(mid);
   if (mbr == nullptr)
   {
      THROW_FEA2D(ReasonCode::PoiReferencesMemberNotExists);
   }

   Loading* loading = FindLoading(lc);
   if (loading == nullptr)
   {
      THROW_FEA2D(ReasonCode::LoadingNotFound);
   }

   auto mrit = m_pImpl->m_MbrResults.find(mid);
   if (mrit == m_pImpl->m_MbrResults.end())
   {
      THROW_FEA2D(ReasonCode::MemberNotFound);
   }
   const ModelImpl::MbrResult* mbrResult = mrit->second->Find(lc);
   if (mbrResult == nullptr)
   {
      THROW_FEA2D(ReasonCode::LoadingNotFound);
   }

   Float64 pl = poi->GetLocation();
   Float64 poiloc = mbr->GetRealLocation(pl);
   if (poiloc == -1.0)
   {
      if (pl < 0.0)
      {
         THROW_FEA2D(ReasonCode::PoiFractionalOutOfRange);
      }
      else
      {
         THROW_FEA2D(ReasonCode::PoiLocatedOffMemberEnd);
      }
   }

   // restore member state to the solution for this loading, then pull
   // internal forces/deflection at the POI location
   mbr->ClearLoads();
   loading->ApplyLoads(mbr);
   mbr->SetResults(*mbrResult);

   mbr->GetInternalForces(poiloc, MemberFaceType::Left, force);
   mbr->GetInternalForces(poiloc, MemberFaceType::Right, &force[3]);

   // reverse sign of forces to comply with sign conventions
   for (int i = 0; i < 6; i++)
   {
      force[i] = -1.0 * force[i];
   }

   mbr->GetDeflection(poiloc, disp);

   ModelImpl::PoiResult result(lc, force, disp);

   if (0 < lc)
   {
      // positive load cases get long-term caching
      auto it2 = m_pImpl->m_PoiResults.find(poiId);
      ModelImpl::PoiResultArray* array;
      if (it2 != m_pImpl->m_PoiResults.end())
      {
         array = it2->second.get();
      }
      else
      {
         auto newArray = std::make_unique<ModelImpl::PoiResultArray>(poiId);
         array = newArray.get();
         m_pImpl->m_PoiResults.emplace(poiId, std::move(newArray));
      }

      ModelImpl::PoiResult* pres = array->Find(lc);
      if (pres != nullptr)
      {
         *pres = result;
      }
      else
      {
         array->Add(result);
      }
   }
   else
   {
      // negative load cases go in the simple cache to avoid container overhead
      m_pImpl->m_SimplePOIResultCache.Update(poiId, lc, result);
   }
}

void Model::ComputePOIDeflections(LoadCaseIDType lc, PoiIDType poiId, LoadOrientation orientation, Float64* pDx, Float64* pDy, Float64* pRz) const
{
   EnsureAnalyzed();

   Float64 force[6], disp[3];
   GetPoiResult(lc, poiId, force, disp);

   if (orientation == LoadOrientation::Member)
   {
      *pDx = disp[0];
      *pDy = disp[1];
      *pRz = disp[2];
   }
   else if (orientation == LoadOrientation::Global || orientation == LoadOrientation::GlobalProjected)
   {
      POI* poi = FindPOI(poiId);
      CHECK(poi != nullptr); // GetPoiResult above already validated this
      Member* mbr = FindMember(poi->GetMemberID());
      CHECK(mbr != nullptr);

      Float64 ang = mbr->GetAngle();
      Float64 c = cos(ang);
      Float64 s = sin(ang);

      *pDx = disp[0] * c - disp[1] * s;
      *pDy = disp[0] * s + disp[1] * c;
      *pRz = disp[2];
   }
   else
   {
      THROW_FEA2D(ReasonCode::InvalidLoadOrientation);
   }
}

void Model::ComputePOIForces(LoadCaseIDType lc, PoiIDType poiId, MemberFaceType face, LoadOrientation orientation, Float64* pFx, Float64* pFy, Float64* pMz) const
{
   EnsureAnalyzed();

   Float64 force[6], disp[3];
   GetPoiResult(lc, poiId, force, disp);

   int offset = (face == MemberFaceType::Left) ? 0 : 3;

   if (orientation == LoadOrientation::Member)
   {
      *pFx = force[0 + offset];
      *pFy = force[1 + offset];
      *pMz = force[2 + offset];
   }
   else if (orientation == LoadOrientation::Global || orientation == LoadOrientation::GlobalProjected)
   {
      POI* poi = FindPOI(poiId);
      CHECK(poi != nullptr); // GetPoiResult above already validated this
      Member* mbr = FindMember(poi->GetMemberID());
      CHECK(mbr != nullptr);

      Float64 ang = mbr->GetAngle();
      Float64 c = cos(ang);
      Float64 s = sin(ang);

      Float64 lfx = force[0 + offset];
      Float64 lfy = force[1 + offset];
      *pFx = lfx * c - lfy * s;
      *pFy = lfx * s + lfy * c;
      *pMz = force[2 + offset];
   }
   else
   {
      THROW_FEA2D(ReasonCode::InvalidLoadOrientation);
   }
}
