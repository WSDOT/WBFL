///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2026  Washington State Department of Transportation
//                        Bridge and Structures Office
///////////////////////////////////////////////////////////////////////
// TestPersistence.cpp
//
// Ported from F:\ARP\WBFL\Fem2d\Test\TestPersistence.cpp - round-trips a
// model through IStructuredStorage2 Save/Load and verifies computed results
// are identical before and after. The model is saved to a file this test
// creates itself (via CLSID_StructuredSave2/CLSID_StructuredLoad2), so no
// external fixture is required.
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

namespace Fem2dUnitTests
{

namespace
{
   // Saves and loaded results for a single quantity - Equal() confirms the
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
      Fem2dModelFixture fixture;
      CComPtr<IFem2dModel>& pmodel = fixture.Model;

      CComPtr<IFem2dJointCollection> pJoints;
      ASSERT_HR(pmodel->get_Joints(&pJoints));

      CComPtr<IFem2dJoint> pJoint1, pJoint2, pJoint3, pJoint4, pJoint5;
      CComPtr<IFem2dJoint> pJoint6, pJoint7, pJoint8, pJoint9;
      ASSERT_MC(fixture, pJoints->Create(1, 0.0, 0.0, &pJoint1));
      ASSERT_MC(fixture, pJoints->Create(2, 0.0, 24.0, &pJoint2));
      ASSERT_MC(fixture, pJoints->Create(3, 0.0, 36.0, &pJoint3));
      ASSERT_MC(fixture, pJoints->Create(4, 24.0, 0.0, &pJoint4));
      ASSERT_MC(fixture, pJoints->Create(5, 24.0, 24.0, &pJoint5));
      ASSERT_MC(fixture, pJoints->Create(6, 24.0, 36.0, &pJoint6));
      ASSERT_MC(fixture, pJoints->Create(7, 24.0, 56.0, &pJoint7));
      ASSERT_MC(fixture, pJoints->Create(8, 48.0, 0.0, &pJoint8));
      ASSERT_MC(fixture, pJoints->Create(9, 48.0, 24.0, &pJoint9));

      ASSERT_MC(fixture, pJoint1->Support());
      ASSERT_MC(fixture, pJoint4->Support());
      ASSERT_MC(fixture, pJoint4->ReleaseDof(jrtMz));
      ASSERT_MC(fixture, pJoint8->Support());
      ASSERT_MC(fixture, pJoint8->ReleaseDof(jrtMz));

      CComPtr<IFem2dMemberCollection> pMembers;
      ASSERT_HR(pmodel->get_Members(&pMembers));

      Float64 E = 3.0;
      Float64 A = 5.0;
      Float64 I = 7.0;
      CComPtr<IFem2dMember> pMember1, pMember2, pMember3, pMember4, pMember5;
      CComPtr<IFem2dMember> pMember6, pMember7, pMember8, pMember9, pMember10, pMember11;
      ASSERT_MC(fixture, pMembers->Create(1, 1, 2, E * A, E * I, &pMember1));
      ASSERT_MC(fixture, pMembers->Create(2, 2, 3, E * A, E * I, &pMember2));
      ASSERT_MC(fixture, pMembers->Create(3, 3, 7, E * A, E * I, &pMember3));
      ASSERT_MC(fixture, pMembers->Create(4, 3, 6, E * A, E * I, &pMember4));
      ASSERT_MC(fixture, pMembers->Create(5, 2, 5, E * A, E * I, &pMember5));
      ASSERT_MC(fixture, pMembers->Create(6, 6, 7, E * A, E * I, &pMember6));
      ASSERT_MC(fixture, pMembers->Create(7, 5, 6, E * A, E * I, &pMember7));
      ASSERT_MC(fixture, pMembers->Create(8, 7, 9, E * A, E * I, &pMember8));
      ASSERT_MC(fixture, pMembers->Create(9, 5, 9, E * A, E * I, &pMember9));
      ASSERT_MC(fixture, pMembers->Create(10, 4, 5, E * A, E * I, &pMember10));
      ASSERT_MC(fixture, pMembers->Create(11, 8, 9, E * A, E * I, &pMember11));

      ASSERT_MC(fixture, pMember5->ReleaseEnd(metStart, mbrReleaseMz));
      ASSERT_MC(fixture, pMember9->ReleaseEnd(metEnd, mbrReleaseMz));

      CComPtr<IFem2dLoadingCollection> pLoadings;
      ASSERT_HR(pmodel->get_Loadings(&pLoadings));
      CComPtr<IFem2dLoading> pLoading1;
      ASSERT_LC(fixture, pLoadings->Create(1, &pLoading1));

      CComPtr<IFem2dDistributedLoadCollection> pDistributedLoads;
      ASSERT_HR(pLoading1->get_DistributedLoads(&pDistributedLoads));
      CComPtr<IFem2dDistributedLoad> pDistributedLoad1, pDistributedLoad2;
      ASSERT_LC(fixture, pDistributedLoads->Create(1, 3, loadDirFy, -0.1, -0.7, -2.0, 0.0, lotMember, &pDistributedLoad1));
      ASSERT_LC(fixture, pDistributedLoad1->put_Orientation(lotGlobalProjected)); // apply in global coords
      ASSERT_LC(fixture, pDistributedLoads->Create(2, 8, loadDirFy, -0.2, -0.6, -3.0, 0.0, lotMember, &pDistributedLoad2));

      CComPtr<IFem2dJointLoadCollection> pJointLoads;
      ASSERT_HR(pLoading1->get_JointLoads(&pJointLoads));
      CComPtr<IFem2dJointLoad> pJointLoad;
      ASSERT_LC(fixture, pJointLoads->Create(1, 3, 12.0, 0.0, 0.0, &pJointLoad));

      CComPtr<IFem2dPointLoadCollection> pPointLoads;
      ASSERT_HR(pLoading1->get_PointLoads(&pPointLoads));
      CComPtr<IFem2dPointLoad> pPointLoad;
      ASSERT_LC(fixture, pPointLoads->Create(1, 1, -0.6, 4.0, -3.0, 0.0, lotMember, &pPointLoad));

      CComPtr<IFem2dMemberStrainCollection> pMemberStrains;
      ASSERT_HR(pLoading1->get_MemberStrains(&pMemberStrains));
      CComPtr<IFem2dMemberStrain> pMemberStrain;
      ASSERT_LC(fixture, pMemberStrains->Create(1, 7, 0.0, -1.0, 0.05, 0.0, &pMemberStrain));

      // Loading 2 - support deflection case
      CComPtr<IFem2dLoading> pLoading2;
      ASSERT_LC(fixture, pLoadings->Create(2, &pLoading2));

      CComPtr<IFem2dJointDeflectionCollection> pJointDeflections;
      ASSERT_HR(pLoading2->get_JointDeflections(&pJointDeflections));
      CComPtr<IFem2dJointDeflection> pJointDeflection;
      ASSERT_LC(fixture, pJointDeflections->Create(1, 4, 0.4, -0.6, 0.0, &pJointDeflection));

      CComPtr<IFem2dPOICollection> pPOIs;
      ASSERT_HR(pmodel->get_POIs(&pPOIs));
      CComPtr<IFem2dPOI> pPOI35, pPOI1025;
      ASSERT_HR(pPOIs->Create(35, 3, -0.5, &pPOI35));
      ASSERT_HR(pPOIs->Create(1025, 10, -0.25, &pPOI1025));

      // save model off to a file
      {
         CComPtr<IStructuredSave2> psave;
         ASSERT_HR(psave.CoCreateInstance(CLSID_StructuredSave2));
         Assert::IsTrue(psave != nullptr);

         ASSERT_HR(psave->Open(CComBSTR("Fem2dUnitTests_Persistence.xml")));

         IStructuredStorage2* pstor;
         ASSERT_HR(pmodel->QueryInterface(&pstor));
         ASSERT_HR(pstor->Save(psave));
         ASSERT_HR(psave->Close());
         pstor->Release();
      }

      TpComp cmp1, cmp2;

      CComQIPtr<IFem2dModelResults> presults(pmodel);

      // loading 1
      Float64 fx, fy, mz;
      ASSERT_HR(presults->ComputeReactions(1, 1, &fx, &fy, &mz));
      cmp1.R_1.SetSaved(fx, fy, mz);
      ASSERT_HR(presults->ComputeReactions(1, 4, &fx, &fy, &mz));
      cmp1.R_4.SetSaved(fx, fy, mz);

      Float64 dx, dy, rz;
      ASSERT_HR(presults->ComputePOIDeflections(2, 35, lotGlobal, &dx, &dy, &rz));
      cmp1.PD_35.SetSaved(dx, dy, rz);
      ASSERT_HR(presults->ComputePOIDeflections(2, 1025, lotGlobal, &dx, &dy, &rz));
      cmp1.PD_1025.SetSaved(dx, dy, rz);

      ASSERT_HR(presults->ComputePOIForces(2, 35, mftLeft, lotMember, &fx, &fy, &mz));
      cmp1.PF_35.SetSaved(fx, fy, mz);
      ASSERT_HR(presults->ComputePOIForces(2, 1025, mftLeft, lotMember, &fx, &fy, &mz));
      cmp1.PF_1025.SetSaved(fx, fy, mz);

      // loading 2
      ASSERT_HR(presults->ComputeReactions(2, 1, &fx, &fy, &mz));
      cmp2.R_1.SetSaved(fx, fy, mz);
      ASSERT_HR(presults->ComputeReactions(2, 4, &fx, &fy, &mz));
      cmp2.R_4.SetSaved(fx, fy, mz);

      ASSERT_HR(presults->ComputePOIDeflections(2, 35, lotGlobal, &dx, &dy, &rz));
      cmp2.PD_35.SetSaved(dx, dy, rz);
      ASSERT_HR(presults->ComputePOIDeflections(2, 1025, lotGlobal, &dx, &dy, &rz));
      cmp2.PD_1025.SetSaved(dx, dy, rz);

      ASSERT_HR(presults->ComputePOIForces(2, 35, mftLeft, lotMember, &fx, &fy, &mz));
      cmp2.PF_35.SetSaved(fx, fy, mz);
      ASSERT_HR(presults->ComputePOIForces(2, 1025, mftLeft, lotMember, &fx, &fy, &mz));
      cmp2.PF_1025.SetSaved(fx, fy, mz);

      // now clear the model out and reload it
      pmodel->Clear();

      CComPtr<IStructuredLoad2> pload;
      ASSERT_HR(pload.CoCreateInstance(CLSID_StructuredLoad2));
      Assert::IsTrue(pload != nullptr);

      ASSERT_HR(pload->Open(CComBSTR("Fem2dUnitTests_Persistence.xml")));

      IStructuredStorage2* pstor;
      ASSERT_HR(pmodel->get_StructuredStorage(&pstor));
      ASSERT_HR(pstor->Load(pload));
      pstor->Release();

      // loading 1
      ASSERT_HR(presults->ComputeReactions(1, 1, &fx, &fy, &mz));
      cmp1.R_1.SetLoaded(fx, fy, mz);
      ASSERT_HR(presults->ComputeReactions(1, 4, &fx, &fy, &mz));
      cmp1.R_4.SetLoaded(fx, fy, mz);

      ASSERT_HR(presults->ComputePOIDeflections(2, 35, lotGlobal, &dx, &dy, &rz));
      cmp1.PD_35.SetLoaded(dx, dy, rz);
      ASSERT_HR(presults->ComputePOIDeflections(2, 1025, lotGlobal, &dx, &dy, &rz));
      cmp1.PD_1025.SetLoaded(dx, dy, rz);

      ASSERT_HR(presults->ComputePOIForces(2, 35, mftLeft, lotMember, &fx, &fy, &mz));
      cmp1.PF_35.SetLoaded(fx, fy, mz);
      ASSERT_HR(presults->ComputePOIForces(2, 1025, mftLeft, lotMember, &fx, &fy, &mz));
      cmp1.PF_1025.SetLoaded(fx, fy, mz);

      // loading 2
      ASSERT_HR(presults->ComputeReactions(2, 1, &fx, &fy, &mz));
      cmp2.R_1.SetLoaded(fx, fy, mz);
      ASSERT_HR(presults->ComputeReactions(2, 4, &fx, &fy, &mz));
      cmp2.R_4.SetLoaded(fx, fy, mz);

      ASSERT_HR(presults->ComputePOIDeflections(2, 35, lotGlobal, &dx, &dy, &rz));
      cmp2.PD_35.SetLoaded(dx, dy, rz);
      ASSERT_HR(presults->ComputePOIDeflections(2, 1025, lotGlobal, &dx, &dy, &rz));
      cmp2.PD_1025.SetLoaded(dx, dy, rz);

      ASSERT_HR(presults->ComputePOIForces(2, 35, mftLeft, lotMember, &fx, &fy, &mz));
      cmp2.PF_35.SetLoaded(fx, fy, mz);
      ASSERT_HR(presults->ComputePOIForces(2, 1025, mftLeft, lotMember, &fx, &fy, &mz));
      cmp2.PF_1025.SetLoaded(fx, fy, mz);

      // this compares all results calculated before/after the round trip
      Assert::IsTrue(cmp1.Equal(), L"Loading 1 results changed after save/load round trip");
      Assert::IsTrue(cmp2.Equal(), L"Loading 2 results changed after save/load round trip");
   }
};
} // namespace Fem2dUnitTests
