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
#include "MemberImpl.h"
#include <FEA2D\Model.h>
#include <FEA2D\XFEA2D.h>
#include "Beam.h" // BEAM_FIXED / BEAM_RELEASE_MZ / BEAM_RELEASE_FX constants only

#include <cmath>
#include <MathEx.h>
#include <System\Flags.h>

using namespace WBFL::FEA2D;

namespace
{
   constexpr long MBR_RELEASE_NONE = 0;
   constexpr long MBR_RELEASE_MZ = 0x0001;
   constexpr long MBR_RELEASE_FX = 0x0002;
   constexpr Float64 EPS = 0.10; // tolerance for GetRealLocation's end-of-member bounds check
}

Member::Member(Model* pModel, MemberIDType id, JointIDType startJoint, JointIDType endJoint, Float64 EA, Float64 EI) :
   m_pImpl(std::make_unique<MemberImpl>(this, pModel, id, startJoint, endJoint, EA, EI))
{
   CHECK(EA >= 0.0);
   CHECK(EI >= 0.0);
}

Member::~Member() = default;

Member::MemberImpl::MemberImpl(Member* pMember, Model* pModel, MemberIDType id, JointIDType startJoint, JointIDType endJoint, Float64 EA, Float64 EI) :
   m_pModel(pModel),
   m_ID(id),
   m_StartReleases(MBR_RELEASE_NONE),
   m_EndReleases(MBR_RELEASE_NONE),
   m_EA(EA),
   m_EI(EI),
   m_TransMatrix(Member::TotalDOF, Member::TotalDOF),
   m_Kglobal(Member::TotalDOF, Member::TotalDOF),
   m_Klocal(Member::TotalDOF, Member::TotalDOF),
   m_Fglobal(),
   m_Dlocal(),
   m_Rlocal(),
   m_JointKeeper(pMember, pModel)
{
   m_JointKeeper.PutStartJoint(startJoint);
   m_JointKeeper.PutEndJoint(endJoint);
}

MemberIDType Member::GetID() const noexcept
{
   return m_pImpl->m_ID;
}

JointIDType Member::GetStartJoint() const noexcept
{
   return m_pImpl->m_JointKeeper.GetStartJoint();
}

bool Member::SetStartJoint(JointIDType id) noexcept
{
   bool changed = m_pImpl->m_JointKeeper.PutStartJoint(id);
   if (changed) { m_pImpl->m_pModel->OnStructuralChange(); }
   return changed;
}

JointIDType Member::GetEndJoint() const noexcept
{
   return m_pImpl->m_JointKeeper.GetEndJoint();
}

bool Member::SetEndJoint(JointIDType id) noexcept
{
   bool changed = m_pImpl->m_JointKeeper.PutEndJoint(id);
   if (changed) { m_pImpl->m_pModel->OnStructuralChange(); }
   return changed;
}

Float64 Member::GetEA() const noexcept
{
   return m_pImpl->m_EA;
}

bool Member::SetEA(Float64 EA)
{
   if (EA <= 0.0)
   {
      THROW_FEA2D(ReasonCode::StiffnessMustBePositive);
   }

   if (m_pImpl->m_EA != EA)
   {
      m_pImpl->m_EA = EA;
      m_pImpl->m_pModel->OnStructuralChange();
      return true;
   }
   return false;
}

Float64 Member::GetEI() const noexcept
{
   return m_pImpl->m_EI;
}

bool Member::SetEI(Float64 EI)
{
   if (EI <= 0.0)
   {
      THROW_FEA2D(ReasonCode::StiffnessMustBePositive);
   }

   if (m_pImpl->m_EI != EI)
   {
      m_pImpl->m_EI = EI;
      m_pImpl->m_pModel->OnStructuralChange();
      return true;
   }
   return false;
}

Float64 Member::GetLength() const
{
   // This method uses a different way of calculating lengths than the
   // internal JointKeeper class because this length must be correct in
   // real-time (we don't watch to see if joints move).
   JointIDType startjoint = m_pImpl->m_JointKeeper.GetStartJoint();
   JointIDType endjoint = m_pImpl->m_JointKeeper.GetEndJoint();

   if (startjoint == endjoint)
   {
      THROW_FEA2D(ReasonCode::MemberHasSameJoints);
   }

   Joint* pStartJoint = m_pImpl->m_pModel->FindJoint(startjoint);
   if (pStartJoint == nullptr)
   {
      THROW_FEA2D(ReasonCode::MemberJointNotExists);
   }

   Joint* pEndJoint = m_pImpl->m_pModel->FindJoint(endjoint);
   if (pEndJoint == nullptr)
   {
      THROW_FEA2D(ReasonCode::MemberJointNotExists);
   }

   Float64 dx = pStartJoint->GetX() - pEndJoint->GetX();
   Float64 dy = pStartJoint->GetY() - pEndJoint->GetY();
   Float64 length = sqrt(dx * dx + dy * dy);

   if (length == 0.0)
   {
      THROW_FEA2D(ReasonCode::ZeroLengthMember);
   }

   return length;
}

long Member::GetReleaseTypeFlag(MemberReleaseType releaseType) const noexcept
{
   switch (releaseType)
   {
   case MemberReleaseType::None:
      return MBR_RELEASE_NONE;
   case MemberReleaseType::Mz:
      return MBR_RELEASE_MZ;
   case MemberReleaseType::Fx:
      return MBR_RELEASE_FX;
   default:
      CHECK(false); // is there a new release type?
      return MBR_RELEASE_NONE;
   }
}

bool Member::ReleaseEnd(MemberEndType end, MemberReleaseType releaseType) noexcept
{
   long* pReleases = (end == MemberEndType::Start) ? &m_pImpl->m_StartReleases : &m_pImpl->m_EndReleases;

   if (releaseType == MemberReleaseType::None)
   {
      // all member end releases are being removed
      *pReleases = MBR_RELEASE_NONE;
   }
   else
   {
      *pReleases |= GetReleaseTypeFlag(releaseType);
   }
   m_pImpl->m_pModel->OnStructuralChange();
   return true;
}

bool Member::IsReleased(MemberEndType end, MemberReleaseType releaseType) const noexcept
{
   long flag = GetReleaseTypeFlag(releaseType);
   long releases = (end == MemberEndType::Start) ? m_pImpl->m_StartReleases : m_pImpl->m_EndReleases;
   return (releases == 0 && flag == 0) || WBFL::System::Flags<long>::IsSet(releases, flag);
}

bool Member::operator==(const Member& mbr) const noexcept
{
   return m_pImpl->m_ID == mbr.m_pImpl->m_ID;
}

Float64 Member::GetRealLocation(Float64 length, Float64 loc)
{
   CHECK(length > 0.0);

   Float64 tloc = -1.0;

   if (loc < 0.0)
   {
      // fractional location
      if (loc >= -1)
      {
         tloc = -loc * length;
      }
   }
   else
   {
      // explicit location specified
      if (loc <= length + EPS)
      {
         tloc = loc;
      }
   }

   return tloc;
}

Float64 Member::GetRealLocation(Float64 loc) const
{
   Float64 length = m_pImpl->m_JointKeeper.GetLength();
   return GetRealLocation(length, loc);
}

Float64 Member::GetAngle() const
{
   return m_pImpl->m_JointKeeper.GetAngle();
}

///////////////
//// FE-Related internal functions

void Member::InitModel()
{
   m_pImpl->m_JointKeeper.m_Dirty = true;

   Joint *StartJnt, *EndJnt;
   m_pImpl->m_JointKeeper.GetJoints(&StartJnt, &EndJnt);
   StartJnt->Link(this);
   EndJnt->Link(this);

   BuildTransformationMatrix();
   BuildKlocal();
   BuildKglobal();
}

void Member::BuildTransformationMatrix()
{
   // 2d Transformation matrix
   // [ c  s  0  0  0  0]
   // [-s  c  0  0  0  0]
   // [ 0  0  1  0  0  0]
   // [ 0  0  0  c  s  0]
   // [ 0  0  0 -s  c  0]
   // [ 0  0  0  0  0  1]

   Float64 Angle = m_pImpl->m_JointKeeper.GetAngle();
   Float64 s = sin(Angle);
   Float64 c = cos(Angle);

   Internals::Matrix& m_TransMatrix = m_pImpl->m_TransMatrix;

   m_TransMatrix(0,0) = c;    m_TransMatrix(0,1) = s;    m_TransMatrix(0,2) = 0;
   m_TransMatrix(0,3) = 0;    m_TransMatrix(0,4) = 0;    m_TransMatrix(0,5) = 0;

   m_TransMatrix(1,0) = -s;   m_TransMatrix(1,1) = c;    m_TransMatrix(1,2) = 0;
   m_TransMatrix(1,3) = 0;    m_TransMatrix(1,4) = 0;    m_TransMatrix(1,5) = 0;

   m_TransMatrix(2,0) = 0;    m_TransMatrix(2,1) = 0;    m_TransMatrix(2,2) = 1;
   m_TransMatrix(2,3) = 0;    m_TransMatrix(2,4) = 0;    m_TransMatrix(2,5) = 0;

   m_TransMatrix(3,0) = 0;    m_TransMatrix(3,1) = 0;    m_TransMatrix(3,2) = 0;
   m_TransMatrix(3,3) = c;    m_TransMatrix(3,4) = s;    m_TransMatrix(3,5) = 0;

   m_TransMatrix(4,0) = 0;    m_TransMatrix(4,1) = 0;    m_TransMatrix(4,2) = 0;
   m_TransMatrix(4,3) = -s;   m_TransMatrix(4,4) = c;    m_TransMatrix(4,5) = 0;

   m_TransMatrix(5,0) = 0;    m_TransMatrix(5,1) = 0;    m_TransMatrix(5,2) = 0;
   m_TransMatrix(5,3) = 0;    m_TransMatrix(5,4) = 0;    m_TransMatrix(5,5) = 1;
}

void Member::BuildKlocal()
{
   Float64 Length = m_pImpl->m_JointKeeper.GetLength();

   Float64 vk = IsReleased(MemberEndType::Start, MemberReleaseType::Fx) || IsReleased(MemberEndType::End, MemberReleaseType::Fx) ? 0 : 1;

   Float64 vi = IsReleased(MemberEndType::Start, MemberReleaseType::Mz) ? 0 : 1;
   Float64 vj = IsReleased(MemberEndType::End, MemberReleaseType::Mz) ? 0 : 1;
   Float64 v = 4 - vi * vj;

   Float64 m_EA = m_pImpl->m_EA;
   Float64 m_EI = m_pImpl->m_EI;

   /* compute global stiffness matrix */
   Float64 A =  m_EA/Length * vk;
   Float64 D = -m_EA/Length * vk;
   Float64 G =  (12*m_EI/pow(Length,3)) * (vi + vi*vj + vj)/v;
   Float64 H =   (6*m_EI/pow(Length,2)) * (2*vi + vi*vj)/v;
   Float64 J = -(12*m_EI/pow(Length,3)) * (vi + vi*vj + vj)/v;
   Float64 K =   (6*m_EI/pow(Length,2)) * (2*vj + vi*vj)/v;
   Float64 L =   (4*m_EI/Length)        * (3*vi)/v;
   Float64 N =  -(6*m_EI/pow(Length,2)) * (2*vi + vi*vj)/v;
   Float64 O =   (2*m_EI/Length)        * (3*vi*vj)/v;
   Float64 P =  m_EA/Length * vk;
   Float64 S =  (12*m_EI/pow(Length,3)) * (vi + vi*vj + vj)/v;
   Float64 T =  -(6*m_EI/pow(Length,2)) * (2*vj + vi*vj)/v;
   Float64 U =   (4*m_EI/Length)        * (3*vj)/v;

   Internals::Matrix& m_Klocal = m_pImpl->m_Klocal;

   m_Klocal(0,0) = A;  m_Klocal(0,1) = 0;  m_Klocal(0,2) = 0;  m_Klocal(0,3) = D;  m_Klocal(0,4) = 0;  m_Klocal(0,5) = 0;
   m_Klocal(1,0) = 0;  m_Klocal(1,1) = G;  m_Klocal(1,2) = H;  m_Klocal(1,3) = 0;  m_Klocal(1,4) = J;  m_Klocal(1,5) = K;
   m_Klocal(2,0) = 0;  m_Klocal(2,1) = H;  m_Klocal(2,2) = L;  m_Klocal(2,3) = 0;  m_Klocal(2,4) = N;  m_Klocal(2,5) = O;
   m_Klocal(3,0) = D;  m_Klocal(3,1) = 0;  m_Klocal(3,2) = 0;  m_Klocal(3,3) = P;  m_Klocal(3,4) = 0;  m_Klocal(3,5) = 0;
   m_Klocal(4,0) = 0;  m_Klocal(4,1) = J;  m_Klocal(4,2) = N;  m_Klocal(4,3) = 0;  m_Klocal(4,4) = S;  m_Klocal(4,5) = T;
   m_Klocal(5,0) = 0;  m_Klocal(5,1) = K;  m_Klocal(5,2) = O;  m_Klocal(5,3) = 0;  m_Klocal(5,4) = T;  m_Klocal(5,5) = U;
}

void Member::BuildKglobal()
{
   Internals::Matrix Temp(TotalDOF, TotalDOF);

   m_pImpl->m_TransMatrix.Multiply(m_pImpl->m_Klocal, Temp, Internals::MultiplyMode::ATB);
   Temp.Multiply(m_pImpl->m_TransMatrix, m_pImpl->m_Kglobal);
}

void Member::ClearLoads()
{
   // This object does not own its loads... Do not delete them.
   // Simply empty the container.
   m_pImpl->m_Loads.clear();
}

void Member::ComputeResults()
{
   bool useClassic = true;
   Joint *StartJnt, *EndJnt;
   m_pImpl->m_JointKeeper.GetJoints(&StartJnt, &EndJnt);

   for (long dof = 0; dof < Joint::NumDof && useClassic; dof++)
   {
      if (StartJnt->GetCondensedDOF(dof) >= 0)
         useClassic = false;
   }

   for (long dof = 0; dof < Joint::NumDof && useClassic; dof++)
   {
      if (EndJnt->GetCondensedDOF(dof) >= 0)
         useClassic = false;
   }

   if (useClassic)
      ComputeClassicResults();
   else
      ComputeFemResults();
}

void Member::ComputeFemResults()
{
   // compute mbr end forces (local)
   ComputeForces();

   // compute mbr end deflections (local)
   ComputeDeflections();
}

void Member::ComputeClassicResults()
{
   Float64 dx1=0,dy1=0,rz1=0; // start deflections
   Float64 dx2=0,dy2=0,rz2=0; // end deflections
   Float64 Fx1=0,Fy1=0,Mz1=0; // start forces
   Float64 Fx2=0,Fy2=0,Mz2=0; // end forces
   Float64 force[TotalDOF];
   Float64 disp[TotalDOF];

   // for every load in the current Loading
   // compute member end deflections, rotations, and forces
   for (Internals::MbrLoad* mbrLdPtr : m_pImpl->m_Loads)
   {
      Internals::MbrLoad& mbrLd = *mbrLdPtr;

      Float64 angle = m_pImpl->m_JointKeeper.GetAngle();
      Float64 length = m_pImpl->m_JointKeeper.GetLength();
      mbrLd.GetForceVector(m_pImpl->m_StartReleases, m_pImpl->m_EndReleases, length, angle, force);
      mbrLd.GetDispVector(m_pImpl->m_StartReleases, m_pImpl->m_EndReleases, length, angle, m_pImpl->m_EA, m_pImpl->m_EI, disp);

      Fx1 += force[0]; Fy1 += force[1]; Mz1 += force[2];
      Fx2 += force[3]; Fy2 += force[4]; Mz2 += force[5];

      dx1 += disp[0]; dy1 += disp[1]; rz1 += disp[2];
      dx2 += disp[3]; dy2 += disp[4]; rz2 += disp[5];
   }

   Internals::Vector6& m_Dlocal = m_pImpl->m_Dlocal;
   Internals::Vector6& m_Rlocal = m_pImpl->m_Rlocal;

   m_Dlocal(0) = dx1; m_Dlocal(1) = dy1; m_Dlocal(2) = rz1;
   m_Dlocal(3) = dx2; m_Dlocal(4) = dy2; m_Dlocal(5) = rz2;

   m_Rlocal(0) = Fx1; m_Rlocal(1) = Fy1; m_Rlocal(2) = Mz1;
   m_Rlocal(3) = Fx2; m_Rlocal(4) = Fy2; m_Rlocal(5) = Mz2;
}

void Member::ComputeDeflections()
{
   Float64 Dglobal[6];
   Internals::Vector6 Disp;
   Joint *StartJnt, *EndJnt;
   m_pImpl->m_JointKeeper.GetJoints(&StartJnt, &EndJnt);

   StartJnt->GetDeflection(Dglobal);
   EndJnt->GetDeflection(&Dglobal[3]);
   Disp(0) = Dglobal[0]; Disp(1) = Dglobal[1]; Disp(2) = Dglobal[2];
   Disp(3) = Dglobal[3]; Disp(4) = Dglobal[4]; Disp(5) = Dglobal[5];

   Internals::Vector6& m_Dlocal = m_pImpl->m_Dlocal;
   m_pImpl->m_TransMatrix.Multiply(Disp, m_Dlocal);

   // adjust member end rotation at released ends.
   Float64 r1, r2;
   if (IsReleased(MemberEndType::Start, MemberReleaseType::Mz) && IsReleased(MemberEndType::End, MemberReleaseType::Mz))
   {
      GetPinPinRotation(r1, r2);
      m_Dlocal(2) = r1;
      m_Dlocal(5) = r2;
   }
   else if (IsReleased(MemberEndType::Start, MemberReleaseType::Mz))
   {
      // Start joint rotation is incorrect for this member.
      // Adjust based on actual boundary condition.
      GetPinFixRotation(r1);
      m_Dlocal(2) = r1;
   }
   else if (IsReleased(MemberEndType::End, MemberReleaseType::Mz))
   {
      // End joint rotation is incorrect for this member.
      // Adjust based on actual boundary condition.
      GetFixPinRotation(r2);
      m_Dlocal(5) = r2;
   }
}

void Member::ComputeForces()
{
   Float64 Dglobal[6];
   Internals::Vector6 Disp;
   Internals::Vector6 Rglobal;
   Joint *StartJnt, *EndJnt;
   m_pImpl->m_JointKeeper.GetJoints(&StartJnt, &EndJnt);

   StartJnt->GetDeflection(Dglobal);
   EndJnt->GetDeflection(&Dglobal[3]);
   Disp(0) = Dglobal[0]; Disp(1) = Dglobal[1]; Disp(2) = Dglobal[2];
   Disp(3) = Dglobal[3]; Disp(4) = Dglobal[4]; Disp(5) = Dglobal[5];

   m_pImpl->m_Kglobal.Multiply(Disp, Rglobal);
   Rglobal -= m_pImpl->m_Fglobal;
   m_pImpl->m_TransMatrix.Multiply(Rglobal, m_pImpl->m_Rlocal);
}

void Member::ComputeJointDeflectionForce(Internals::Vector6& pdf) const
{
   // compute element forces due to a joint deflection
   Internals::Vector6 Disp;
   Disp.Zero();
   Joint *StartJnt, *EndJnt;
   m_pImpl->m_JointKeeper.GetJoints(&StartJnt, &EndJnt);
   if (StartJnt->WasDeflectionLoadApplied())
   {
      Disp(0) = StartJnt->m_dispLoad[0];
      Disp(1) = StartJnt->m_dispLoad[1];
      Disp(2) = StartJnt->m_dispLoad[2];
   }

   if (EndJnt->WasDeflectionLoadApplied())
   {
      Disp(3) = EndJnt->m_dispLoad[0];
      Disp(4) = EndJnt->m_dispLoad[1];
      Disp(5) = EndJnt->m_dispLoad[2];
   }

   m_pImpl->m_Kglobal.Multiply(Disp, pdf);
}

void Member::GetGlobalJntForces(JointIDType jntId, Float64* force) const
{
   Internals::Vector6 Rglobal;
   m_pImpl->m_TransMatrix.Multiply(m_pImpl->m_Rlocal, Rglobal, Internals::MultiplyMode::ATB);

   LONG start = (LONG)jntId * TotalDOF / NumJoints;
   LONG end = start + TotalDOF / NumJoints;

   LONG count = 0;
   for (LONG i = start; i < end; i++, count++)
   {
      force[count] = Rglobal(i);
   }
}

JointIDType Member::GetJointNum(const Joint* j) const
{
   Joint *StartJnt, *EndJnt;
   m_pImpl->m_JointKeeper.GetJoints(&StartJnt, &EndJnt);

   if (j == StartJnt)
      return 0;
   else if (j == EndJnt)
      return 1;
   else
   {
      CHECK(false); // "Member::GetJointNum - Joint not found"
      return INVALID_ID;
   }
}

void Member::GetResults(MbrResult* pres) const
{
   for (long i = 0; i < 6; i++)
   {
      pres->SetDeflection(i, m_pImpl->m_Dlocal(i));
      pres->SetForce(i, m_pImpl->m_Rlocal(i));
   }
}

void Member::SetResults(const MbrResult& res)
{
   Internals::Vector6& m_Dlocal = m_pImpl->m_Dlocal;
   Internals::Vector6& m_Rlocal = m_pImpl->m_Rlocal;
   for (long i = 0; i < 6; i++)
   {
      m_Dlocal(i) = res.GetDeflection(i);
      m_Rlocal(i) = res.GetForce(i);
   }
}

void Member::GetInternalForces(Float64 loc, MemberFaceType face, Float64* force) const
{
   Float64 fx, fy, mz; // Contribution of a single external load
   Float64 Fx = 0, Fy = 0, Mz = 0; // Contribution of all external loads
   Float64 Rx, Ry, Rz; // Member End Forces

   Float64 angle  = m_pImpl->m_JointKeeper.GetAngle();
   Float64 length = m_pImpl->m_JointKeeper.GetLength();

   // Iterate over all loads on this member, for the active Loading
   for (Internals::MbrLoad* mbrLd : m_pImpl->m_Loads)
   {
      // Member loads know how to compute their own internal force effects.
      mbrLd->GetInternalForces(loc, length, angle, face, &fx, &fy, &mz);

      // Integrate the internal forces for this load into the resultant
      // internal force. The effect of the member end forces associated
      // with this load are not included.
      Fx += fx;
      Fy += fy;
      Mz += mz;
   }

   // Add effects of member end forces
   if (face == MemberFaceType::Right)
   {
      Rx = m_pImpl->m_Rlocal(3);
      Ry = m_pImpl->m_Rlocal(4);
      Rz = m_pImpl->m_Rlocal(5);
      force[0] =  Fx + Rx;
      force[1] =  Fy + Ry;
      force[2] =  Mz + Ry*(length - loc) + Rz;
   }
   else
   {
      Rx = m_pImpl->m_Rlocal(0);
      Ry = m_pImpl->m_Rlocal(1);
      Rz = m_pImpl->m_Rlocal(2);
      force[0] =  Fx +  Rx;
      force[1] =  Fy +  Ry;
      force[2] =  Mz + -Ry*loc + Rz;
   }
}

void Member::GetDeflection(Float64 loc, Float64* disp) const
{
   Float64 dx, dy, rz;

   disp[0] = 0;
   disp[1] = 0;
   disp[2] = 0;

   Float64 angle  = m_pImpl->m_JointKeeper.GetAngle();
   Float64 length = m_pImpl->m_JointKeeper.GetLength();

   for (Internals::MbrLoad* mbrLd : m_pImpl->m_Loads)
   {
      mbrLd->GetDeflection(loc, BEAM_FIXED, BEAM_FIXED, length, angle, m_pImpl->m_EA, m_pImpl->m_EI, &dx, &dy, &rz);
      disp[0] += dx;
      disp[1] += dy;
      disp[2] += rz;
   }

   // Deflections due to beam action
   // compute based on the fact that we know that the deflection
   // due to beam action at member ends will be in the form of a cubic along
   // the member.
   // Can write in the form y = ax^3  + bx^2 + cx + d
   //                       y'= 3ax^2 + 2bx  + c
   //
   // can then solve for boundary conditions: y(0)  = D0,   y(L)  = DL
   //                                         y'(0) = R0,   y'(L) = RL
   // and find that d = D0
   //               c = R0
   // can find a and b by substituting and solving
   Float64 L = length;
   Float64 D0 = m_pImpl->m_Dlocal(1);
   Float64 DL = m_pImpl->m_Dlocal(4);
   Float64 R0 = m_pImpl->m_Dlocal(2);
   Float64 RL = m_pImpl->m_Dlocal(5);

   Float64 a = (RL + R0)/(L*L) + 2.0*(D0-DL)/(L*L*L);
   Float64 b = (RL - R0)/(2.0*L) - (3.0*a*L)/2.0;
   Float64 c = R0;
   Float64 d = D0;

   // only affects y and y' deflection
   disp[1] += a*loc*loc*loc + b*loc*loc + c*loc + d;
   disp[2] += 3.0*a*loc*loc + 2.0*b*loc + c;

   // Compute axial effects of frame deflection
   disp[0] += m_pImpl->m_Dlocal(0) + (m_pImpl->m_Dlocal(3) - m_pImpl->m_Dlocal(0))*loc/length;
}

void Member::GetPinPinRotation(Float64& rz1, Float64& rz2) const
{
   Float64 vector[6];

   rz1 = 0;
   rz2 = 0;

   Float64 angle  = m_pImpl->m_JointKeeper.GetAngle();
   Float64 length = m_pImpl->m_JointKeeper.GetLength();

   for (Internals::MbrLoad* load : m_pImpl->m_Loads)
   {
      load->GetDispVector(BEAM_RELEASE_MZ, BEAM_RELEASE_MZ, length, angle, m_pImpl->m_EA, m_pImpl->m_EI, vector);
      rz1 += vector[2];
      rz2 += vector[5];
   }

   // rigid body rotation only
   Float64 dy = m_pImpl->m_Dlocal(4) - m_pImpl->m_Dlocal(1);
   Float64 rot = dy/length; // small angle assumption - really is ATAN
   rz1 += rot;
   rz2 += rot;
}

void Member::GetPinFixRotation(Float64& rz1) const
{
   Float64 disp_vector[6];
   rz1 = 0;

   Float64 angle  = m_pImpl->m_JointKeeper.GetAngle();
   Float64 length = m_pImpl->m_JointKeeper.GetLength();

   for (Internals::MbrLoad* load : m_pImpl->m_Loads)
   {
      load->GetDispVector(BEAM_RELEASE_MZ, BEAM_FIXED, length, angle, m_pImpl->m_EA, m_pImpl->m_EI, disp_vector);
      rz1 += disp_vector[2];
   }

   // compute rotation at start end due to overall y deflection
   Float64 dy = m_pImpl->m_Dlocal(1) - m_pImpl->m_Dlocal(4);
   Float64 r  = -3*dy/(2*length);
   rz1 += r;

   // rigid body rotation
   rz1 -= m_pImpl->m_Dlocal(5)/2.0;
}

void Member::GetFixPinRotation(Float64& rz2) const
{
   Float64 vector[6];
   rz2 = 0;

   Float64 angle  = m_pImpl->m_JointKeeper.GetAngle();
   Float64 length = m_pImpl->m_JointKeeper.GetLength();

   for (Internals::MbrLoad* load : m_pImpl->m_Loads)
   {
      load->GetDispVector(BEAM_FIXED, BEAM_RELEASE_MZ, length, angle, m_pImpl->m_EA, m_pImpl->m_EI, vector);
      rz2 += vector[5];
   }

   // compute rotation at end end due to overall y deflection
   Float64 dy = m_pImpl->m_Dlocal(4) - m_pImpl->m_Dlocal(1);
   Float64 r  = 3*dy/(2*length);
   rz2 += r;

   // rigid body rotation
   rz2 -= m_pImpl->m_Dlocal(2)/2.0;
}

void Member::AssembleF()
{
   // Assembles the local and global force vectors for the applied loads.
   // Loads should have been applied for the active load case.
   Internals::Vector6 Flocal;
   Flocal(0) = 0; Flocal(1) = 0; Flocal(2) = 0;
   Flocal(3) = 0; Flocal(4) = 0; Flocal(5) = 0;

   Float64 angle  = m_pImpl->m_JointKeeper.GetAngle();
   Float64 length = m_pImpl->m_JointKeeper.GetLength();

   Float64 vector[TotalDOF];

   for (Internals::MbrLoad* mbrLd : m_pImpl->m_Loads)
   {
      mbrLd->GetForceVector(m_pImpl->m_StartReleases, m_pImpl->m_EndReleases, length, angle, vector);

      // Integrate the force vector into this member's local force vector
      for (long i = 0; i < TotalDOF; i++)
         Flocal(i) -= vector[i];
   }

   // Compute Global Force Vector
   if (angle != 0.0)
   {
      m_pImpl->m_TransMatrix.Multiply(Flocal, m_pImpl->m_Fglobal, Internals::MultiplyMode::ATB);
   }
   else
   {
      m_pImpl->m_Fglobal = Flocal;
   }
}

LONG Member::GetNumDOF() const noexcept
{
   return TotalDOF;
}

LONG Member::GetNumJoints() const noexcept
{
   return NumJoints;
}

LONG Member::GetCondensedDOF(LONG dof) const
{
   Joint *StartJnt, *EndJnt;
   m_pImpl->m_JointKeeper.GetJoints(&StartJnt, &EndJnt);

   if (dof < 3)
      return StartJnt->GetCondensedDOF(dof);
   else
      return EndJnt->GetCondensedDOF(dof - 3);
}

Float64 Member::GetKglobal(LONG DOFi, LONG DOFj) const
{
   return m_pImpl->m_Kglobal(DOFi, DOFj);
}

void Member::ApplyLoad(Internals::MbrLoad* load)
{
   m_pImpl->m_Loads.push_back(load);
}

void Member::GetFglobal(Float64* f) const
{
   // first compute member forces due to joint deflections
   // forces are transient since they are not needed later
   Internals::Vector6 dforce;
   ComputeJointDeflectionForce(dforce);

   for (long i = 0; i < TotalDOF; i++)
      f[i] = m_pImpl->m_Fglobal(i) - dforce(i);
}

bool Member::IsEquilibriumSatisfied(Float64 forceTolerance, Float64 momentTolerance)
{
   Float64 _fx, _fy, _mz; // Contribution of a single external load
   Float64 fx = 0, fy = 0, mz = 0; // Contribution of all external loads on the member

   Float64 length = m_pImpl->m_JointKeeper.GetLength();
   Float64 angle = m_pImpl->m_JointKeeper.GetAngle();

   for (Internals::MbrLoad* mbrLd : m_pImpl->m_Loads)
   {
      mbrLd->GetOriginForces(length, angle, &_fx, &_fy, &_mz);
      fx += _fx;
      fy += _fy;
      mz += _mz;
   }

   Float64 fx1 = m_pImpl->m_Rlocal(0);
   Float64 fy1 = m_pImpl->m_Rlocal(1);
   Float64 mz1 = m_pImpl->m_Rlocal(2);
   Float64 fx2 = m_pImpl->m_Rlocal(3);
   Float64 fy2 = m_pImpl->m_Rlocal(4);
   Float64 mz2 = m_pImpl->m_Rlocal(5);
   Float64 Fx = fx + fx1 + fx2;
   Float64 Fy = fy + fy1 + fy2;
   Float64 Mz = mz + mz1 + mz2 + length*fy2;

   if (!IsZero(Fx, forceTolerance))
   {
      CHECK(false);
      return false;
   }

   if (!IsZero(Fy, forceTolerance))
   {
      CHECK(false);
      return false;
   }

   if (!IsZero(Mz, momentTolerance))
   {
      CHECK(false);
      return false;
   }

   return true;
}

////////////////// The JointKeeper

Member::MemberImpl::JointKeeper::JointKeeper(Member* pMember, Model* pModel) :
   m_pMember(pMember),
   m_pModel(pModel),
   m_StartJoint(-1),
   m_EndJoint(-1),
   m_pStartJoint(nullptr),
   m_pEndJoint(nullptr),
   m_Length(0.0),
   m_Angle(0.0),
   m_Dirty(true)
{
}

bool Member::MemberImpl::JointKeeper::PutStartJoint(JointIDType id)
{
   if (m_StartJoint != id)
   {
      m_StartJoint = id;
      m_Dirty = true;
      return true;
   }
   return false;
}

JointIDType Member::MemberImpl::JointKeeper::GetStartJoint() const noexcept
{
   return m_StartJoint;
}

bool Member::MemberImpl::JointKeeper::PutEndJoint(JointIDType id)
{
   if (m_EndJoint != id)
   {
      m_EndJoint = id;
      m_Dirty = true;
      return true;
   }
   return false;
}

JointIDType Member::MemberImpl::JointKeeper::GetEndJoint() const noexcept
{
   return m_EndJoint;
}

void Member::MemberImpl::JointKeeper::GetJoints(Joint** pStart, Joint** pEnd)
{
   if (m_Dirty)
   {
      Compute();
   }

   CHECK(m_pStartJoint != nullptr);
   CHECK(m_pEndJoint != nullptr);

   *pStart = m_pStartJoint;
   *pEnd   = m_pEndJoint;
}

Float64 Member::MemberImpl::JointKeeper::GetLength()
{
   if (m_Dirty)
   {
      Compute();
   }
   CHECK(m_pStartJoint != nullptr);
   CHECK(m_pEndJoint != nullptr);

   return m_Length;
}

Float64 Member::MemberImpl::JointKeeper::GetAngle()
{
   if (m_Dirty)
   {
      Compute();
   }
   CHECK(m_pStartJoint != nullptr);
   CHECK(m_pEndJoint != nullptr);

   return m_Angle;
}

void Member::MemberImpl::JointKeeper::Compute()
{
   m_pStartJoint = nullptr;
   m_pEndJoint = nullptr;

   m_pStartJoint = m_pModel->FindJoint(m_StartJoint);
   if (m_pStartJoint == nullptr)
   {
      THROW_FEA2D(ReasonCode::MemberJointNotExists);
   }

   m_pEndJoint = m_pModel->FindJoint(m_EndJoint);
   if (m_pEndJoint == nullptr)
   {
      THROW_FEA2D(ReasonCode::MemberJointNotExists);
   }

   Float64 dx = m_pStartJoint->GetX() - m_pEndJoint->GetX();
   Float64 dy = m_pStartJoint->GetY() - m_pEndJoint->GetY();
   m_Length = sqrt(dx*dx + dy*dy);

   if (m_Length == 0.0)
   {
      THROW_FEA2D(ReasonCode::ZeroLengthMember);
   }

   m_Angle = atan2(m_pEndJoint->GetY() - m_pStartJoint->GetY(), m_pEndJoint->GetX() - m_pStartJoint->GetX());

   m_Dirty = false;
}
