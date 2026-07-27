///////////////////////////////////////////////////////////////////////
// FEA2D - Two-dimensional Finite Element Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestPersistence.cpp
//
// Mirrors Fem2d\Fem2dUnitTests\TestPersistence.cpp - round-trips a model
// through native IStructuredSave/IStructuredLoad (StructuredSaveXml/
// StructuredLoadXml) Save/Load and verifies computed results are
// identical before and after.
//
//              w
//         ============ 3
//                    /o
//                  /  |
//                /    |
//              /      |
//            /        |
//          /          |
//        2o-----------o4
//         |           |
//         |           |
//         |           |
//         |           |
//        1o           o5
//        ===         ===
//
// Frame with trapezoidal load, made up and verified using DrFrame.
#include "pch.h"

#include <System\FileStream.h>
#include <System\StructuredSaveXml.h>
#include <System\StructuredLoadXml.h>

namespace FEA2DUnitTests
{

namespace
{
   // Saved and loaded results for a single quantity - Equal() confirms the
   // structured-storage round trip reproduced the exact same computed value.
   struct DualVal
   {
      Float64 xs = 0.0, ys = 0.0, zs = 0.0; // saved
      Float64 xl = 0.0, yl = 0.0, zl = 0.0; // loaded
      void SetSaved(Float64 x, Float64 y, Float64 z) { xs = x; ys = y; zs = z; }
      void SetLoaded(Float64 x, Float64 y, Float64 z) { xl = x; yl = y; zl = z; }
      bool Equal() const { return xs == xl && ys == yl && zs == zl; }
   };

   struct TpComp
   {
      DualVal R_1, R_4;
      DualVal PD_35, PF_35, PD_1025, PF_1025;

      bool Equal() const
      {
         return R_1.Equal() && R_4.Equal() && PD_35.Equal() && PF_35.Equal() && PD_1025.Equal() && PF_1025.Equal();
      }
   };
}

TEST_CLASS(TestPersistence)
{
public:
   TEST_METHOD(SaveLoadRoundTrip_ResultsMatch)
   {
      Model model;
      model.CreateJoint(1, 0.0, 0.0);
      model.CreateJoint(2, 0.0, 24.0);
      model.CreateJoint(3, 0.0, 36.0);
      Joint& pJoint4 = model.CreateJoint(4, 24.0, 0.0);
      model.CreateJoint(5, 24.0, 24.0);
      model.CreateJoint(6, 24.0, 36.0);
      model.CreateJoint(7, 24.0, 56.0);
      Joint& pJoint8 = model.CreateJoint(8, 48.0, 0.0);
      model.CreateJoint(9, 48.0, 24.0);

      model.FindJoint(1)->Support();
      pJoint4.Support();
      pJoint4.ReleaseDof(JointReleaseType::Mz);
      pJoint8.Support();
      pJoint8.ReleaseDof(JointReleaseType::Mz);

      Float64 E = 3.0;
      Float64 A = 5.0;
      Float64 I = 7.0;
      model.CreateMember(1, 1, 2, E * A, E * I);
      model.CreateMember(2, 2, 3, E * A, E * I);
      model.CreateMember(3, 3, 7, E * A, E * I);
      model.CreateMember(4, 3, 6, E * A, E * I);
      Member& pMember5 = model.CreateMember(5, 2, 5, E * A, E * I);
      model.CreateMember(6, 6, 7, E * A, E * I);
      model.CreateMember(7, 5, 6, E * A, E * I);
      model.CreateMember(8, 7, 9, E * A, E * I);
      Member& pMember9 = model.CreateMember(9, 5, 9, E * A, E * I);
      model.CreateMember(10, 4, 5, E * A, E * I);
      model.CreateMember(11, 8, 9, E * A, E * I);

      pMember5.ReleaseEnd(MemberEndType::Start, MemberReleaseType::Mz);
      pMember9.ReleaseEnd(MemberEndType::End, MemberReleaseType::Mz);

      Loading& pLoading1 = model.CreateLoading(1);

      DistributedLoad& pDistLoad1 = pLoading1.CreateDistributedLoad(1, 3, LoadDirection::Fy, -0.1, -0.7, -2.0, 0.0, LoadOrientation::Member);
      pDistLoad1.SetOrientation(LoadOrientation::GlobalProjected); // apply in global coords
      pLoading1.CreateDistributedLoad(2, 8, LoadDirection::Fy, -0.2, -0.6, -3.0, 0.0, LoadOrientation::Member);

      pLoading1.CreateJointLoad(1, 3, 12.0, 0.0, 0.0);
      pLoading1.CreatePointLoad(1, 1, -0.6, 4.0, -3.0, 0.0, LoadOrientation::Member);
      pLoading1.CreateMemberStrain(1, 7, 0.0, -1.0, 0.05, 0.0);

      // Loading 2 - support deflection case
      Loading& pLoading2 = model.CreateLoading(2);
      pLoading2.CreateJointDisplacement(1, 4, 0.4, -0.6, 0.0);

      model.CreatePOI(35, 3, -0.5);
      model.CreatePOI(1025, 10, -0.25);


      // save model off to a file
      const wchar_t* filename = L"FEA2DUnitTests_Persistence.xml";
      {
         WBFL::System::FileStream file;
         Assert::IsTrue(file.open(filename, /*read=*/false));
         WBFL::System::StructuredSaveXml save;
         save.BeginSave(&file);

         model.Save(&save);

         save.EndSave();
      }

      TpComp cmp1, cmp2;

      // loading 1
      Float64 fx, fy, mz;
      model.ComputeReactions(1, 1, &fx, &fy, &mz);
      cmp1.R_1.SetSaved(fx, fy, mz);
      model.ComputeReactions(1, 4, &fx, &fy, &mz);
      cmp1.R_4.SetSaved(fx, fy, mz);

      Float64 dx, dy, rz;
      model.ComputePOIDeflections(2, 35, LoadOrientation::Global, &dx, &dy, &rz);
      cmp1.PD_35.SetSaved(dx, dy, rz);
      model.ComputePOIDeflections(2, 1025, LoadOrientation::Global, &dx, &dy, &rz);
      cmp1.PD_1025.SetSaved(dx, dy, rz);

      model.ComputePOIForces(2, 35, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      cmp1.PF_35.SetSaved(fx, fy, mz);
      model.ComputePOIForces(2, 1025, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      cmp1.PF_1025.SetSaved(fx, fy, mz);

      // loading 2
      model.ComputeReactions(2, 1, &fx, &fy, &mz);
      cmp2.R_1.SetSaved(fx, fy, mz);
      model.ComputeReactions(2, 4, &fx, &fy, &mz);
      cmp2.R_4.SetSaved(fx, fy, mz);

      model.ComputePOIDeflections(2, 35, LoadOrientation::Global, &dx, &dy, &rz);
      cmp2.PD_35.SetSaved(dx, dy, rz);
      model.ComputePOIDeflections(2, 1025, LoadOrientation::Global, &dx, &dy, &rz);
      cmp2.PD_1025.SetSaved(dx, dy, rz);

      model.ComputePOIForces(2, 35, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      cmp2.PF_35.SetSaved(fx, fy, mz);
      model.ComputePOIForces(2, 1025, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      cmp2.PF_1025.SetSaved(fx, fy, mz);

      // now clear the model out and reload it
      model.Clear();

      WBFL::System::FileStream file;
      Assert::IsTrue(file.open(filename, /*read=*/true));
      WBFL::System::StructuredLoadXml load;
      load.BeginLoad(&file);

      model.Load(&load);

      load.EndLoad();


      // loading 1
      model.ComputeReactions(1, 1, &fx, &fy, &mz);
      cmp1.R_1.SetLoaded(fx, fy, mz);
      model.ComputeReactions(1, 4, &fx, &fy, &mz);
      cmp1.R_4.SetLoaded(fx, fy, mz);

      model.ComputePOIDeflections(2, 35, LoadOrientation::Global, &dx, &dy, &rz);
      cmp1.PD_35.SetLoaded(dx, dy, rz);
      model.ComputePOIDeflections(2, 1025, LoadOrientation::Global, &dx, &dy, &rz);
      cmp1.PD_1025.SetLoaded(dx, dy, rz);

      model.ComputePOIForces(2, 35, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      cmp1.PF_35.SetLoaded(fx, fy, mz);
      model.ComputePOIForces(2, 1025, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      cmp1.PF_1025.SetLoaded(fx, fy, mz);

      // loading 2
      model.ComputeReactions(2, 1, &fx, &fy, &mz);
      cmp2.R_1.SetLoaded(fx, fy, mz);
      model.ComputeReactions(2, 4, &fx, &fy, &mz);
      cmp2.R_4.SetLoaded(fx, fy, mz);

      model.ComputePOIDeflections(2, 35, LoadOrientation::Global, &dx, &dy, &rz);
      cmp2.PD_35.SetLoaded(dx, dy, rz);
      model.ComputePOIDeflections(2, 1025, LoadOrientation::Global, &dx, &dy, &rz);
      cmp2.PD_1025.SetLoaded(dx, dy, rz);

      model.ComputePOIForces(2, 35, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      cmp2.PF_35.SetLoaded(fx, fy, mz);
      model.ComputePOIForces(2, 1025, MemberFaceType::Left, LoadOrientation::Member, &fx, &fy, &mz);
      cmp2.PF_1025.SetLoaded(fx, fy, mz);

      // this compares all results calculated before/after the round trip
      Assert::IsTrue(cmp1.Equal(), L"Loading 1 results changed after save/load round trip");
      Assert::IsTrue(cmp2.Equal(), L"Loading 2 results changed after save/load round trip");
   }
};
} // namespace FEA2DUnitTests
