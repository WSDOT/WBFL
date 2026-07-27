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
#include <FEA2D\Loading.h>
#include <FEA2D\Model.h>
#include <FEA2D\Joint.h>
#include <FEA2D\Member.h>
#include <FEA2D\XFEA2D.h>

using namespace WBFL::FEA2D;

Loading::Loading(Model* pModel, LoadCaseIDType id) :
   m_pModel(pModel), m_ID(id)
{
}

LoadCaseIDType Loading::GetID() const noexcept
{
   return m_ID;
}

//
// Joint loads
//
JointLoad& Loading::CreateJointLoad(LoadIDType id, JointIDType jointID, Float64 Fx, Float64 Fy, Float64 Mz)
{
   if (m_JointLoads.find(id) != m_JointLoads.end())
   {
      THROW_FEA2D(ReasonCode::JointLoadWithIdAlreadyExists);
   }

   auto load = std::unique_ptr<JointLoad>(new JointLoad(m_pModel, m_ID, id, jointID, Fx, Fy, Mz));
   JointLoad* pLoad = load.get();
   m_JointLoads.emplace(id, std::move(load));
   m_pModel->OnLoadingChanged(m_ID);
   return *pLoad;
}

JointLoad* Loading::FindJointLoad(LoadIDType id) const noexcept
{
   auto it = m_JointLoads.find(id);
   return it == m_JointLoads.end() ? nullptr : it->second.get();
}

JointLoad* Loading::FindJointLoadByIndex(IndexType index) const noexcept
{
   if (m_JointLoads.size() <= index)
      return nullptr;
   auto it = m_JointLoads.begin();
   std::advance(it, index);
   return it->second.get();
}

bool Loading::RemoveJointLoad(LoadIDType id)
{
   bool removed = m_JointLoads.erase(id) != 0;
   if (removed) { m_pModel->OnLoadingChanged(m_ID); }
   return removed;
}

void Loading::ClearJointLoads() noexcept
{
   if (!m_JointLoads.empty())
   {
      m_JointLoads.clear();
      m_pModel->OnLoadingChanged(m_ID);
   }
}

IndexType Loading::GetJointLoadCount() const noexcept
{
   return m_JointLoads.size();
}

//
// Joint displacements
//
JointDisplacement& Loading::CreateJointDisplacement(LoadIDType id, JointIDType jointID, Float64 Dx, Float64 Dy, Float64 Rz)
{
   if (m_JointDisplacements.find(id) != m_JointDisplacements.end())
   {
      THROW_FEA2D(ReasonCode::JointDispWithIdAlreadyExists);
   }

   auto load = std::unique_ptr<JointDisplacement>(new JointDisplacement(m_pModel, m_ID, id, jointID, Dx, Dy, Rz));
   JointDisplacement* pLoad = load.get();
   m_JointDisplacements.emplace(id, std::move(load));
   m_pModel->OnLoadingChanged(m_ID);
   return *pLoad;
}

JointDisplacement* Loading::FindJointDisplacement(LoadIDType id) const noexcept
{
   auto it = m_JointDisplacements.find(id);
   return it == m_JointDisplacements.end() ? nullptr : it->second.get();
}

JointDisplacement* Loading::FindJointDisplacementByIndex(IndexType index) const noexcept
{
   if (m_JointDisplacements.size() <= index)
      return nullptr;
   auto it = m_JointDisplacements.begin();
   std::advance(it, index);
   return it->second.get();
}

bool Loading::RemoveJointDisplacement(LoadIDType id)
{
   bool removed = m_JointDisplacements.erase(id) != 0;
   if (removed) { m_pModel->OnLoadingChanged(m_ID); }
   return removed;
}

void Loading::ClearJointDisplacements() noexcept
{
   if (!m_JointDisplacements.empty())
   {
      m_JointDisplacements.clear();
      m_pModel->OnLoadingChanged(m_ID);
   }
}

IndexType Loading::GetJointDisplacementCount() const noexcept
{
   return m_JointDisplacements.size();
}

//
// Point loads
//
PointLoad& Loading::CreatePointLoad(LoadIDType id, MemberIDType memberID, Float64 location, Float64 Fx, Float64 Fy, Float64 Mz, LoadOrientation orientation)
{
   if (m_PointLoads.find(id) != m_PointLoads.end())
   {
      THROW_FEA2D(ReasonCode::PointLoadWithIdAlreadyExists);
   }

   auto load = std::unique_ptr<PointLoad>(new PointLoad(m_pModel, m_ID, id, memberID, location, Fx, Fy, Mz, orientation));
   PointLoad* pLoad = load.get();
   m_PointLoads.emplace(id, std::move(load));
   m_pModel->OnLoadingChanged(m_ID);
   return *pLoad;
}

PointLoad* Loading::FindPointLoad(LoadIDType id) const noexcept
{
   auto it = m_PointLoads.find(id);
   return it == m_PointLoads.end() ? nullptr : it->second.get();
}

PointLoad* Loading::FindPointLoadByIndex(IndexType index) const noexcept
{
   if (m_PointLoads.size() <= index)
      return nullptr;
   auto it = m_PointLoads.begin();
   std::advance(it, index);
   return it->second.get();
}

bool Loading::RemovePointLoad(LoadIDType id)
{
   bool removed = m_PointLoads.erase(id) != 0;
   if (removed) { m_pModel->OnLoadingChanged(m_ID); }
   return removed;
}

void Loading::ClearPointLoads() noexcept
{
   if (!m_PointLoads.empty())
   {
      m_PointLoads.clear();
      m_pModel->OnLoadingChanged(m_ID);
   }
}

IndexType Loading::GetPointLoadCount() const noexcept
{
   return m_PointLoads.size();
}

//
// Distributed loads
//
DistributedLoad& Loading::CreateDistributedLoad(LoadIDType id, MemberIDType memberID, LoadDirection direction, Float64 startLocation, Float64 endLocation, Float64 wStart, Float64 wEnd, LoadOrientation orientation)
{
   if (m_DistributedLoads.find(id) != m_DistributedLoads.end())
   {
      THROW_FEA2D(ReasonCode::DistLoadWithIdAlreadyExists);
   }

   auto load = std::unique_ptr<DistributedLoad>(new DistributedLoad(m_pModel, m_ID, id, memberID, direction, startLocation, endLocation, wStart, wEnd, orientation));
   DistributedLoad* pLoad = load.get();
   m_DistributedLoads.emplace(id, std::move(load));
   m_pModel->OnLoadingChanged(m_ID);
   return *pLoad;
}

DistributedLoad* Loading::FindDistributedLoad(LoadIDType id) const noexcept
{
   auto it = m_DistributedLoads.find(id);
   return it == m_DistributedLoads.end() ? nullptr : it->second.get();
}

DistributedLoad* Loading::FindDistributedLoadByIndex(IndexType index) const noexcept
{
   if (m_DistributedLoads.size() <= index)
      return nullptr;
   auto it = m_DistributedLoads.begin();
   std::advance(it, index);
   return it->second.get();
}

bool Loading::RemoveDistributedLoad(LoadIDType id)
{
   bool removed = m_DistributedLoads.erase(id) != 0;
   if (removed) { m_pModel->OnLoadingChanged(m_ID); }
   return removed;
}

void Loading::ClearDistributedLoads() noexcept
{
   if (!m_DistributedLoads.empty())
   {
      m_DistributedLoads.clear();
      m_pModel->OnLoadingChanged(m_ID);
   }
}

IndexType Loading::GetDistributedLoadCount() const noexcept
{
   return m_DistributedLoads.size();
}

//
// Member strains
//
MemberStrain& Loading::CreateMemberStrain(LoadIDType id, MemberIDType memberID, Float64 startLocation, Float64 endLocation, Float64 axialStrain, Float64 curvatureStrain)
{
   if (m_MemberStrains.find(id) != m_MemberStrains.end())
   {
      THROW_FEA2D(ReasonCode::MemberStrainWithIdAlreadyExists);
   }

   auto load = std::unique_ptr<MemberStrain>(new MemberStrain(m_pModel, m_ID, id, memberID, startLocation, endLocation, axialStrain, curvatureStrain));
   MemberStrain* pLoad = load.get();
   m_MemberStrains.emplace(id, std::move(load));
   m_pModel->OnLoadingChanged(m_ID);
   return *pLoad;
}

MemberStrain* Loading::FindMemberStrain(LoadIDType id) const noexcept
{
   auto it = m_MemberStrains.find(id);
   return it == m_MemberStrains.end() ? nullptr : it->second.get();
}

MemberStrain* Loading::FindMemberStrainByIndex(IndexType index) const noexcept
{
   if (m_MemberStrains.size() <= index)
      return nullptr;
   auto it = m_MemberStrains.begin();
   std::advance(it, index);
   return it->second.get();
}

bool Loading::RemoveMemberStrain(LoadIDType id)
{
   bool removed = m_MemberStrains.erase(id) != 0;
   if (removed) { m_pModel->OnLoadingChanged(m_ID); }
   return removed;
}

void Loading::ClearMemberStrains() noexcept
{
   if (!m_MemberStrains.empty())
   {
      m_MemberStrains.clear();
      m_pModel->OnLoadingChanged(m_ID);
   }
}

IndexType Loading::GetMemberStrainCount() const noexcept
{
   return m_MemberStrains.size();
}

//
// Fem-related functions
//
void Loading::ApplyLoads(const Model* pModel)
{
   // apply joint loads
   for (auto& [id, jntLd] : m_JointLoads)
   {
      JointIDType jointId = jntLd->GetJointID();
      Joint* jnt = pModel->FindJoint(jointId);
      if (jnt == nullptr)
      {
         THROW_FEA2D(ReasonCode::JointLoadRefJointNotExists);
      }

      jnt->ApplyLoad(jntLd.get());
   }

   // apply joint deflections
   for (auto& [id, jntDisp] : m_JointDisplacements)
   {
      JointIDType jointId = jntDisp->GetJointID();
      Joint* jnt = pModel->FindJoint(jointId);
      if (jnt == nullptr)
      {
         THROW_FEA2D(ReasonCode::JointDispRefJointNotExists);
      }

      jnt->ApplyLoad(jntDisp.get());
   }

   // point loads applied to members
   for (auto& [id, ptLd] : m_PointLoads)
   {
      MemberIDType memberId = ptLd->GetMemberID();
      Member* mbr = pModel->FindMember(memberId);
      if (mbr == nullptr)
      {
         THROW_FEA2D(ReasonCode::PointLoadRefMemberNotExists);
      }

      mbr->ApplyLoad(ptLd->GetMbrLoad());
   }

   // distributed loads applied to members
   for (auto& [id, dstLd] : m_DistributedLoads)
   {
      MemberIDType memberId = dstLd->GetMemberID();
      Member* mbr = pModel->FindMember(memberId);
      if (mbr == nullptr)
      {
         THROW_FEA2D(ReasonCode::DistLoadRefMemberNotExists);
      }

      mbr->ApplyLoad(dstLd->GetMbrLoad());
   }

   // member strains
   for (auto& [id, ms] : m_MemberStrains)
   {
      MemberIDType memberId = ms->GetMemberID();
      Member* mbr = pModel->FindMember(memberId);
      if (mbr == nullptr)
      {
         THROW_FEA2D(ReasonCode::PointLoadRefMemberNotExists); // matches CLoading::ApplyLoads, which (re)uses this same reason code for member strains
      }

      mbr->ApplyLoad(ms->GetMbrLoad());
   }
}

// apply loads to a single member
void Loading::ApplyLoads(Member* pMember)
{
   MemberIDType mid = pMember->GetID();

   for (auto& [id, ptLd] : m_PointLoads)
   {
      if (ptLd->GetMemberID() == mid)
      {
         pMember->ApplyLoad(ptLd->GetMbrLoad());
      }
   }

   for (auto& [id, dstLd] : m_DistributedLoads)
   {
      if (dstLd->GetMemberID() == mid)
      {
         pMember->ApplyLoad(dstLd->GetMbrLoad());
      }
   }

   for (auto& [id, ms] : m_MemberStrains)
   {
      if (ms->GetMemberID() == mid)
      {
         pMember->ApplyLoad(ms->GetMbrLoad());
      }
   }
}
