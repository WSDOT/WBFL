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

// Model::Save() / Model::Load() implementation.
//
// Uses the native WBFL::System::IStructuredSave/IStructuredLoad interfaces -
// FEA2D has no ATL/COM dependency anywhere, including here. Callers that
// only have a COM IStructuredSave2/IStructuredLoad2 pointer (the retained
// Fem2d and LBAM COM facades) wrap it in a ComStructuredSaveAdapter /
// ComStructuredLoadAdapter (WBFLTools) before calling in. Unit names,
// property names, and per-unit version numbers below match what the
// legacy engine (and the Fem2d COM facade before it was rebuilt on top of
// FEA2D) wrote, so existing saved files stay loadable.

#include <FEA2D\FEA2DLib.h>
#include "ModelImpl.h"
#include <FEA2D\XFEA2D.h>

#include <System\XStructuredSave.h>
#include <System\XStructuredLoad.h>

using namespace WBFL::FEA2D;
using WBFL::System::IStructuredSave;
using WBFL::System::IStructuredLoad;

namespace
{
   void chk(bool ok)
   {
      if (!ok)
      {
         THROW_FEA2D(ReasonCode::PersistenceInvalidFormat);
      }
   }

   void checkVersion(Float64 actual, Float64 expected)
   {
      if (actual != expected)
      {
         THROW_FEA2D(ReasonCode::PersistenceBadVersion);
      }
   }

   long getLong(IStructuredLoad* pload, LPCTSTR name)
   {
      long v;
      chk(pload->Property(name, &v));
      return v;
   }

   IndexType getCount(IStructuredLoad* pload)
   {
      ULONG v;
      chk(pload->Property(_T("Count"), &v));
      return v;
   }

   Float64 getDbl(IStructuredLoad* pload, LPCTSTR name)
   {
      Float64 v;
      chk(pload->Property(name, &v));
      return v;
   }

   std::_tstring getBstr(IStructuredLoad* pload, LPCTSTR name)
   {
      std::_tstring v;
      chk(pload->Property(name, &v));
      return v;
   }

   void putLong(IStructuredSave* psave, LPCTSTR name, long val)
   {
      psave->Property(name, val);
   }

   void putDbl(IStructuredSave* psave, LPCTSTR name, Float64 val)
   {
      psave->Property(name, val);
   }

   void putBstr(IStructuredSave* psave, LPCTSTR name, const std::_tstring& val)
   {
      psave->Property(name, val.c_str());
   }

   //
   // Per-entity Save/Load - unit names, property names, and per-unit
   // version numbers below must match the legacy engine exactly.
   //

   void SaveJoint(IStructuredSave* psave, const Joint& j)
   {
      psave->BeginUnit(_T("Joint"), 1.0);
      putLong(psave, _T("ID"), (long)j.GetID());
      putDbl(psave, _T("X"), j.GetX());
      putDbl(psave, _T("Y"), j.GetY());

      // reconstruct the raw release bitmask - jrtFx=1, jrtFy=2, jrtMz=4
      long releases = 0;
      if (j.IsDofReleased(JointReleaseType::Fx)) releases |= (long)JointReleaseType::Fx;
      if (j.IsDofReleased(JointReleaseType::Fy)) releases |= (long)JointReleaseType::Fy;
      if (j.IsDofReleased(JointReleaseType::Mz)) releases |= (long)JointReleaseType::Mz;
      putLong(psave, _T("Supports"), releases);

      psave->EndUnit();
   }

   void LoadJoint(IStructuredLoad* pload, Model& model)
   {
      chk(pload->BeginUnit(_T("Joint")));
      Float64 ver = pload->GetVersion();
      checkVersion(ver, 1.0);

      JointIDType id = (JointIDType)getLong(pload, _T("ID"));
      Float64 x = getDbl(pload, _T("X"));
      Float64 y = getDbl(pload, _T("Y"));
      long releases = getLong(pload, _T("Supports"));

      chk(pload->EndUnit());

      Joint& j = model.CreateJoint(id, x, y);
      j.Support();
      if (releases & (long)JointReleaseType::Fx) j.ReleaseDof(JointReleaseType::Fx);
      if (releases & (long)JointReleaseType::Fy) j.ReleaseDof(JointReleaseType::Fy);
      if (releases & (long)JointReleaseType::Mz) j.ReleaseDof(JointReleaseType::Mz);
   }

   void SaveMember(IStructuredSave* psave, const Member& m)
   {
      psave->BeginUnit(_T("Member"), 2.0);
      putLong(psave, _T("ID"), (long)m.GetID());
      putLong(psave, _T("StartJoint"), (long)m.GetStartJoint());
      putLong(psave, _T("EndJoint"), (long)m.GetEndJoint());
      putDbl(psave, _T("EA"), m.GetEA());
      putDbl(psave, _T("EI"), m.GetEI());

      long startRel = 0;
      if (m.IsReleased(MemberEndType::Start, MemberReleaseType::Mz)) startRel |= (long)MemberReleaseType::Mz;
      if (m.IsReleased(MemberEndType::Start, MemberReleaseType::Fx)) startRel |= (long)MemberReleaseType::Fx;
      long endRel = 0;
      if (m.IsReleased(MemberEndType::End, MemberReleaseType::Mz)) endRel |= (long)MemberReleaseType::Mz;
      if (m.IsReleased(MemberEndType::End, MemberReleaseType::Fx)) endRel |= (long)MemberReleaseType::Fx;

      putLong(psave, _T("StartRelease"), startRel);
      putLong(psave, _T("EndRelease"), endRel);
      psave->EndUnit();
   }

   void LoadMember(IStructuredLoad* pload, Model& model)
   {
      chk(pload->BeginUnit(_T("Member")));
      Float64 ver = pload->GetVersion();
      if (2.0 < ver)
      {
         THROW_FEA2D(ReasonCode::PersistenceBadVersion);
      }

      MemberIDType id = (MemberIDType)getLong(pload, _T("ID"));
      JointIDType startJnt = (JointIDType)getLong(pload, _T("StartJoint"));
      JointIDType endJnt = (JointIDType)getLong(pload, _T("EndJoint"));
      Float64 ea = getDbl(pload, _T("EA"));
      Float64 ei = getDbl(pload, _T("EI"));

      long startRel, endRel;
      if (ver < 2.0)
      {
         // v1: a single bool per end, meaning "Mz released"
         bool bStart, bEnd;
         chk(pload->Property(_T("StartRelease"), &bStart));
         startRel = bStart ? (long)MemberReleaseType::Mz : (long)MemberReleaseType::None;
         chk(pload->Property(_T("EndRelease"), &bEnd));
         endRel = bEnd ? (long)MemberReleaseType::Mz : (long)MemberReleaseType::None;
      }
      else
      {
         startRel = getLong(pload, _T("StartRelease"));
         endRel = getLong(pload, _T("EndRelease"));
      }

      chk(pload->EndUnit());

      Member& mbr = model.CreateMember(id, startJnt, endJnt, ea, ei);
      if (startRel & (long)MemberReleaseType::Mz) mbr.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);
      if (startRel & (long)MemberReleaseType::Fx) mbr.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Fx);
      if (endRel & (long)MemberReleaseType::Mz) mbr.ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);
      if (endRel & (long)MemberReleaseType::Fx) mbr.ReleaseEnd(MemberEndType::End, MemberReleaseType::Fx);
   }

   void SavePOI(IStructuredSave* psave, const POI& poi)
   {
      psave->BeginUnit(_T("POI"), 1.0);
      putLong(psave, _T("ID"), (long)poi.GetID());
      putLong(psave, _T("MemberID"), (long)poi.GetMemberID());
      putDbl(psave, _T("Location"), poi.GetLocation());
      psave->EndUnit();
   }

   void LoadPOI(IStructuredLoad* pload, Model& model)
   {
      chk(pload->BeginUnit(_T("POI")));
      Float64 ver = pload->GetVersion();
      checkVersion(ver, 1.0);

      PoiIDType id = (PoiIDType)getLong(pload, _T("ID"));
      MemberIDType mbr = (MemberIDType)getLong(pload, _T("MemberID"));
      Float64 loc = getDbl(pload, _T("Location"));

      chk(pload->EndUnit());

      model.CreatePOI(id, mbr, loc);
   }

   void SaveJointLoad(IStructuredSave* psave, const JointLoad& ld)
   {
      psave->BeginUnit(_T("JointLoad"), 1.0);
      putLong(psave, _T("ID"), (long)ld.GetID());
      putLong(psave, _T("JointID"), (long)ld.GetJointID());
      putDbl(psave, _T("Fx"), ld.GetFx());
      putDbl(psave, _T("Fy"), ld.GetFy());
      putDbl(psave, _T("Mz"), ld.GetMz());
      psave->EndUnit();
   }

   void LoadJointLoad(IStructuredLoad* pload, Loading& loading)
   {
      chk(pload->BeginUnit(_T("JointLoad")));
      Float64 ver = pload->GetVersion();
      checkVersion(ver, 1.0);

      LoadIDType id = (LoadIDType)getLong(pload, _T("ID"));
      JointIDType jnt = (JointIDType)getLong(pload, _T("JointID"));
      Float64 fx = getDbl(pload, _T("Fx"));
      Float64 fy = getDbl(pload, _T("Fy"));
      Float64 mz = getDbl(pload, _T("Mz"));

      chk(pload->EndUnit());
      loading.CreateJointLoad(id, jnt, fx, fy, mz);
   }

   void SaveJointDisplacement(IStructuredSave* psave, const JointDisplacement& ld)
   {
      // unit name "JointDeflection" preserved for file-format compatibility with legacy CJointDeflection
      psave->BeginUnit(_T("JointDeflection"), 1.0);
      putLong(psave, _T("ID"), (long)ld.GetID());
      putLong(psave, _T("JointID"), (long)ld.GetJointID());
      putDbl(psave, _T("Dx"), ld.GetDx());
      putDbl(psave, _T("Dy"), ld.GetDy());
      putDbl(psave, _T("Rz"), ld.GetRz());
      psave->EndUnit();
   }

   void LoadJointDisplacement(IStructuredLoad* pload, Loading& loading)
   {
      chk(pload->BeginUnit(_T("JointDeflection")));
      Float64 ver = pload->GetVersion();
      checkVersion(ver, 1.0);

      LoadIDType id = (LoadIDType)getLong(pload, _T("ID"));
      JointIDType jnt = (JointIDType)getLong(pload, _T("JointID"));
      Float64 dx = getDbl(pload, _T("Dx"));
      Float64 dy = getDbl(pload, _T("Dy"));
      Float64 rz = getDbl(pload, _T("Rz"));

      chk(pload->EndUnit());
      loading.CreateJointDisplacement(id, jnt, dx, dy, rz);
   }

   void SavePointLoad(IStructuredSave* psave, const PointLoad& ld)
   {
      psave->BeginUnit(_T("PointLoad"), 1.0);
      putLong(psave, _T("ID"), (long)ld.GetID());
      putLong(psave, _T("MemberID"), (long)ld.GetMemberID());
      putLong(psave, _T("Orientation"), (long)ld.GetOrientation());
      putDbl(psave, _T("Location"), ld.GetLocation());
      putDbl(psave, _T("Fx"), ld.GetFx());
      putDbl(psave, _T("Fy"), ld.GetFy());
      putDbl(psave, _T("Mz"), ld.GetMz());
      psave->EndUnit();
   }

   void LoadPointLoad(IStructuredLoad* pload, Loading& loading)
   {
      chk(pload->BeginUnit(_T("PointLoad")));
      Float64 ver = pload->GetVersion();
      checkVersion(ver, 1.0);

      LoadIDType id = (LoadIDType)getLong(pload, _T("ID"));
      MemberIDType mbr = (MemberIDType)getLong(pload, _T("MemberID"));
      LoadOrientation ori = (LoadOrientation)getLong(pload, _T("Orientation"));
      Float64 loc = getDbl(pload, _T("Location"));
      Float64 fx = getDbl(pload, _T("Fx"));
      Float64 fy = getDbl(pload, _T("Fy"));
      Float64 mz = getDbl(pload, _T("Mz"));

      chk(pload->EndUnit());
      loading.CreatePointLoad(id, mbr, loc, fx, fy, mz, ori);
   }

   void SaveDistributedLoad(IStructuredSave* psave, const DistributedLoad& ld)
   {
      psave->BeginUnit(_T("DistributedLoad"), 1.0);
      putLong(psave, _T("ID"), (long)ld.GetID());
      putLong(psave, _T("MemberID"), (long)ld.GetMemberID());
      putLong(psave, _T("Orientation"), (long)ld.GetOrientation());
      putLong(psave, _T("Direction"), (long)ld.GetDirection());
      putDbl(psave, _T("StartLocation"), ld.GetStartLocation());
      putDbl(psave, _T("EndLocation"), ld.GetEndLocation());
      putDbl(psave, _T("WStart"), ld.GetWStart());
      putDbl(psave, _T("WEnd"), ld.GetWEnd());
      psave->EndUnit();
   }

   void LoadDistributedLoad(IStructuredLoad* pload, Loading& loading)
   {
      chk(pload->BeginUnit(_T("DistributedLoad")));
      Float64 ver = pload->GetVersion();
      checkVersion(ver, 1.0);

      LoadIDType id = (LoadIDType)getLong(pload, _T("ID"));
      MemberIDType mbr = (MemberIDType)getLong(pload, _T("MemberID"));
      LoadOrientation ori = (LoadOrientation)getLong(pload, _T("Orientation"));
      LoadDirection dir = (LoadDirection)getLong(pload, _T("Direction"));
      Float64 startLoc = getDbl(pload, _T("StartLocation"));
      Float64 endLoc = getDbl(pload, _T("EndLocation"));
      Float64 wStart = getDbl(pload, _T("WStart"));
      Float64 wEnd = getDbl(pload, _T("WEnd"));

      chk(pload->EndUnit());
      loading.CreateDistributedLoad(id, mbr, dir, startLoc, endLoc, wStart, wEnd, ori);
   }

   void SaveMemberStrain(IStructuredSave* psave, const MemberStrain& ld)
   {
      psave->BeginUnit(_T("MemberStrain"), 1.0);
      putLong(psave, _T("ID"), (long)ld.GetID());
      putLong(psave, _T("MemberID"), (long)ld.GetMemberID());
      putDbl(psave, _T("AxialStrain"), ld.GetAxialStrain());
      putDbl(psave, _T("CurvatureStrain"), ld.GetCurvatureStrain());
      putDbl(psave, _T("StartLocation"), ld.GetStartLocation());
      putDbl(psave, _T("EndLocation"), ld.GetEndLocation());
      psave->EndUnit();
   }

   void LoadMemberStrain(IStructuredLoad* pload, Loading& loading)
   {
      chk(pload->BeginUnit(_T("MemberStrain")));
      Float64 ver = pload->GetVersion();
      checkVersion(ver, 1.0);

      LoadIDType id = (LoadIDType)getLong(pload, _T("ID"));
      MemberIDType mbr = (MemberIDType)getLong(pload, _T("MemberID"));
      Float64 axial = getDbl(pload, _T("AxialStrain"));
      Float64 curvature = getDbl(pload, _T("CurvatureStrain"));
      Float64 startLoc = getDbl(pload, _T("StartLocation"));
      Float64 endLoc = getDbl(pload, _T("EndLocation"));

      chk(pload->EndUnit());
      loading.CreateMemberStrain(id, mbr, startLoc, endLoc, axial, curvature);
   }

   //
   // Generic collection Save/Load, for Model's own top-level collections
   // (Joints/Members/POIs/Loadings), which Model::Save/Load can iterate
   // directly since they're defined as Model's own member functions.
   // On-disk shape (needed for file-format compatibility with what the
   // Fem2d COM facade previously wrote): BeginUnit(name,version), "Count"
   // property, N per-item units, EndUnit.
   //

   template <typename Col, typename SaveFn>
   void SaveCollection(IStructuredSave* psave, LPCTSTR name, const Col& col, SaveFn fn)
   {
      psave->BeginUnit(name, 1.0);
      putLong(psave, _T("Count"), (long)col.size());
      for (const auto& [id, item] : col)
      {
         fn(psave, *item);
      }
      psave->EndUnit();
   }

   template <typename Owner, typename LoadFn>
   void LoadCollection(IStructuredLoad* pload, LPCTSTR name, Owner& owner, LoadFn fn)
   {
      chk(pload->BeginUnit(name));
      Float64 ver = pload->GetVersion();
      checkVersion(ver, 1.0);

      IndexType count = getCount(pload);
      for (IndexType i = 0; i < count; i++)
      {
         fn(pload, owner);
      }

      chk(pload->EndUnit());
   }

   //
   // Loading's five sub-collections are private to Loading (no direct map
   // access from these free functions) - iterate via its public
   // Count()/FindByIndex() accessors instead. Bespoke rather than
   // templated since each accessor pair has a different name.
   //

   void SaveLoadingSubCollection(IStructuredSave* psave, LPCTSTR name, IndexType count)
   {
      psave->BeginUnit(name, 1.0);
      putLong(psave, _T("Count"), (long)count);
   }

   void SaveLoading(IStructuredSave* psave, const Loading& lc)
   {
      psave->BeginUnit(_T("Loading"), 1.0);
      putLong(psave, _T("ID"), (long)lc.GetID());

      // sub-collection order is part of the on-disk format and must not change
      SaveLoadingSubCollection(psave, _T("JointLoads"), lc.GetJointLoadCount());
      for (IndexType i = 0; i < lc.GetJointLoadCount(); i++) SaveJointLoad(psave, *lc.FindJointLoadByIndex(i));
      psave->EndUnit();

      SaveLoadingSubCollection(psave, _T("DistributedLoads"), lc.GetDistributedLoadCount());
      for (IndexType i = 0; i < lc.GetDistributedLoadCount(); i++) SaveDistributedLoad(psave, *lc.FindDistributedLoadByIndex(i));
      psave->EndUnit();

      SaveLoadingSubCollection(psave, _T("MemberStrains"), lc.GetMemberStrainCount());
      for (IndexType i = 0; i < lc.GetMemberStrainCount(); i++) SaveMemberStrain(psave, *lc.FindMemberStrainByIndex(i));
      psave->EndUnit();

      SaveLoadingSubCollection(psave, _T("JointDeflections"), lc.GetJointDisplacementCount());
      for (IndexType i = 0; i < lc.GetJointDisplacementCount(); i++) SaveJointDisplacement(psave, *lc.FindJointDisplacementByIndex(i));
      psave->EndUnit();

      SaveLoadingSubCollection(psave, _T("PointLoads"), lc.GetPointLoadCount());
      for (IndexType i = 0; i < lc.GetPointLoadCount(); i++) SavePointLoad(psave, *lc.FindPointLoadByIndex(i));
      psave->EndUnit();

      psave->EndUnit();
   }

   void LoadLoadingSubCollectionHeader(IStructuredLoad* pload, LPCTSTR name, IndexType* pCount)
   {
      chk(pload->BeginUnit(name));
      Float64 ver = pload->GetVersion();
      checkVersion(ver, 1.0);
      *pCount = getCount(pload);
   }

   void LoadLoading(IStructuredLoad* pload, Model& model)
   {
      chk(pload->BeginUnit(_T("Loading")));
      Float64 ver = pload->GetVersion();
      checkVersion(ver, 1.0);

      LoadCaseIDType id = (LoadCaseIDType)getLong(pload, _T("ID"));
      Loading& loading = model.CreateLoading(id);

      // sub-collection order is part of the on-disk format and must not change
      IndexType count;
      LoadLoadingSubCollectionHeader(pload, _T("JointLoads"), &count);
      for (IndexType i = 0; i < count; i++) LoadJointLoad(pload, loading);
      chk(pload->EndUnit());

      LoadLoadingSubCollectionHeader(pload, _T("DistributedLoads"), &count);
      for (IndexType i = 0; i < count; i++) LoadDistributedLoad(pload, loading);
      chk(pload->EndUnit());

      LoadLoadingSubCollectionHeader(pload, _T("MemberStrains"), &count);
      for (IndexType i = 0; i < count; i++) LoadMemberStrain(pload, loading);
      chk(pload->EndUnit());

      LoadLoadingSubCollectionHeader(pload, _T("JointDeflections"), &count);
      for (IndexType i = 0; i < count; i++) LoadJointDisplacement(pload, loading);
      chk(pload->EndUnit());

      LoadLoadingSubCollectionHeader(pload, _T("PointLoads"), &count);
      for (IndexType i = 0; i < count; i++) LoadPointLoad(pload, loading);
      chk(pload->EndUnit());

      chk(pload->EndUnit());
   }
}

// ── Model::Save / Model::Load ───────────────────────────────────────────

void Model::Save(IStructuredSave* psave) const
{
   try
   {
      static constexpr Float64 MY_VER = 3.0; // on-disk format version

      psave->BeginUnit(_T("Fem2d"), MY_VER);

      putBstr(psave, _T("Name"), m_pImpl->m_Name);
      putDbl(psave, _T("ForceEquilibriumTolerance"), m_pImpl->m_ForceEquilibriumTolerance);
      putDbl(psave, _T("MomentEquilibriumTolerance"), m_pImpl->m_MomentEquilibriumTolerance);

      // entity collections - order is part of the on-disk format and must not change
      SaveCollection(psave, _T("Joints"), m_Joints, SaveJoint);
      SaveCollection(psave, _T("Members"), m_Members, SaveMember);
      SaveCollection(psave, _T("POIs"), m_POIs, SavePOI);
      SaveCollection(psave, _T("Loadings"), m_Loadings, SaveLoading);

      psave->EndUnit();
   }
   catch (const WBFL::System::XStructuredSave&)
   {
      THROW_FEA2D(ReasonCode::PersistenceIOError);
   }
}

void Model::Load(IStructuredLoad* pload)
{
   try
   {
      Clear(); // start from an empty model

      static constexpr Float64 MY_VER = 3.0;

      chk(pload->BeginUnit(_T("Fem2d")));

      Float64 ver = pload->GetVersion();
      if (MY_VER < ver)
      {
         THROW_FEA2D(ReasonCode::PersistenceBadVersion);
      }

      if (1.0 < ver) // Name was added in v2
      {
         m_pImpl->m_Name = getBstr(pload, _T("Name"));
      }

      if (ver < 3.0)
      {
         // v1/v2: single combined tolerance
         Float64 tol = getDbl(pload, _T("EquilibriumTolerance"));
         m_pImpl->m_ForceEquilibriumTolerance = tol;
         m_pImpl->m_MomentEquilibriumTolerance = tol;
      }
      else
      {
         m_pImpl->m_ForceEquilibriumTolerance = getDbl(pload, _T("ForceEquilibriumTolerance"));
         m_pImpl->m_MomentEquilibriumTolerance = getDbl(pload, _T("MomentEquilibriumTolerance"));
      }

      // entity collections - order is part of the on-disk format and must not change
      LoadCollection(pload, _T("Joints"), *this, LoadJoint);
      LoadCollection(pload, _T("Members"), *this, LoadMember);
      LoadCollection(pload, _T("POIs"), *this, LoadPOI);
      LoadCollection(pload, _T("Loadings"), *this, LoadLoading);

      chk(pload->EndUnit());
   }
   catch (const WBFL::System::XStructuredLoad&)
   {
      // don't leave a partially-loaded model on failure - Clear() is
      // noexcept, so this can't throw out from under the conversion below
      Clear();
      THROW_FEA2D(ReasonCode::PersistenceIOError);
   }
   catch (...)
   {
      // covers XFEA2D thrown by chk()/checkVersion()/the entity Create*
      // calls above - same reasoning as the XStructuredLoad handler, but
      // rethrown unchanged rather than converted
      Clear();
      throw;
   }
}
