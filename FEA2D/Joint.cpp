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
#include <FEA2D\Joint.h>
#include <FEA2D\JointLoad.h>
#include <FEA2D\JointDisplacement.h>
#include <FEA2D\XFEA2D.h>
#include <FEA2D\Member.h>
#include <FEA2D\Model.h>

#include <MathEx.h>

using namespace WBFL::FEA2D;

namespace
{
   constexpr long jrtNone = 0;
   constexpr long jrtFx = 1;
   constexpr long jrtFy = 2;
   constexpr long jrtMz = 4;
   constexpr long jrtAll = 7;
}

Joint::Joint(Model* pModel, JointIDType id, Float64 x, Float64 y) :
   m_pModel(pModel), m_ID(id), m_X(x), m_Y(y), m_Releases(jrtAll), m_dispLoadApplied(false)
{
   for (int i = 0; i < NumDof; i++)
   {
      m_CondensedDOF[i] = -1;
      m_GlobalDOF[i] = -1;
   }
   ClearLoads();
}

JointIDType Joint::GetID() const noexcept
{
   return m_ID;
}

Float64 Joint::GetX() const noexcept
{
   return m_X;
}

bool Joint::SetX(Float64 x) noexcept
{
   if (m_X != x)
   {
      m_X = x;
      m_pModel->OnStructuralChange();
      return true;
   }
   return false;
}

Float64 Joint::GetY() const noexcept
{
   return m_Y;
}

bool Joint::SetY(Float64 y) noexcept
{
   if (m_Y != y)
   {
      m_Y = y;
      m_pModel->OnStructuralChange();
      return true;
   }
   return false;
}

bool Joint::IsDofReleased(JointReleaseType rel) const noexcept
{
   long relFlag = static_cast<long>(rel);
   if (relFlag == jrtNone)
   {
      return m_Releases == jrtNone;
   }
   else
   {
      long st = m_Releases & relFlag;
      return st == relFlag;
   }
}

bool Joint::IsDofSupported(JointReleaseType rel) const noexcept
{
   long relFlag = static_cast<long>(rel);
   if (relFlag == jrtNone)
   {
      return IsDofReleased(JointReleaseType::All);
   }
   else if (relFlag == jrtAll)
   {
      return IsDofReleased(JointReleaseType::None);
   }
   else
   {
      return !IsDofReleased(rel);
   }
}

bool Joint::IsSupport() const noexcept
{
   return m_Releases != jrtAll;
}

bool Joint::Support() noexcept
{
   if (m_Releases != jrtNone)
   {
      m_Releases = jrtNone;
      m_pModel->OnStructuralChange();
      return true;
   }
   return false;
}

bool Joint::Free() noexcept
{
   if (m_Releases != jrtAll)
   {
      m_Releases = jrtAll;
      m_pModel->OnStructuralChange();
      return true;
   }
   return false;
}

bool Joint::ReleaseDof(JointReleaseType rel) noexcept
{
   if (!IsDofReleased(rel))
   {
      m_Releases |= static_cast<long>(rel);
      m_pModel->OnStructuralChange();
      return true;
   }
   return false;
}

void Joint::InitModel(LONG nGDOF, LONG nCDOF, LONG& nGDOFused, LONG& nCDOFused)
{
   // Not attached to any elements yet
   m_AttachedMembers.clear();

   // no results yet
   ClearLoads();

   LONG count = 0;
   for (LONG i = 0; i < NumDof; i++)
   {
      m_GlobalDOF[i] = nGDOF + i;

      LONG n = 1 << i;
      if ((n & m_Releases) == n) // this dof is free
      {
         m_CondensedDOF[i] = nCDOF;
         nCDOF++;
         count++;
      }
      else
      {
         m_CondensedDOF[i] = -1;
      }
   }

   nGDOFused = NumDof;
   nCDOFused = count;
}

LONG Joint::GetCondensedDOF(LONG dof) const
{
   if (dof < 0 || dof > 2)
   {
      CHECK(false);
      THROW_FEA2D(ReasonCode::InvalidCondensedDof);
   }

   return m_CondensedDOF[dof];
}

LONG Joint::GetGlobalDOF(LONG dof) const
{
   if (dof < 0 || dof > 2)
   {
      CHECK(false);
      THROW_FEA2D(ReasonCode::InvalidGlobalDof);
   }

   return m_GlobalDOF[dof];
}

void Joint::ClearLoads()
{
   m_jntLoad[0] = 0;
   m_jntLoad[1] = 0;
   m_jntLoad[2] = 0;

   m_dispLoadApplied = false;
   m_dispLoad[0] = 0;
   m_dispLoad[1] = 0;
   m_dispLoad[2] = 0;

   m_Reaction[0] = 0;
   m_Reaction[1] = 0;
   m_Reaction[2] = 0;

   m_Disp[0] = 0;
   m_Disp[1] = 0;
   m_Disp[2] = 0;
}

void Joint::ApplyLoad(const JointLoad* ld)
{
   Float64 fx, fy, mz;
   ld->GetForce(&fx, &fy, &mz);
   m_jntLoad[0] += fx;
   m_jntLoad[1] += fy;
   m_jntLoad[2] += mz;
}

void Joint::ApplyLoad(const JointDisplacement* ld)
{
   // Deflections cannot be applied to released dofs
   Float64 dx, dy, rz;
   ld->GetDeflection(&dx, &dy, &rz);
   if ((dx != 0.0 && m_CondensedDOF[0] != -1) ||
       (dy != 0.0 && m_CondensedDOF[1] != -1) ||
       (rz != 0.0 && m_CondensedDOF[2] != -1))
   {
      THROW_FEA2D(ReasonCode::JointDispToFixedDofOnly);
   }

   m_dispLoadApplied = true;
   m_dispLoad[0] += dx;
   m_dispLoad[1] += dy;
   m_dispLoad[2] += rz;
}

void Joint::GetFglobal(Float64* v) const
{
   v[0] = m_jntLoad[0];
   v[1] = m_jntLoad[1];
   v[2] = m_jntLoad[2];
}

void Joint::SetDeflection(const Float64* disp)
{
   m_Disp[0] = disp[0];
   m_Disp[1] = disp[1];
   m_Disp[2] = disp[2];

   // this is a bit tricky and underhanded here, but set deflection
   // values to those prescribed by settlement loads if applied
   if (m_dispLoadApplied)
   {
      for (int i = 0; i < NumDof; i++)
      {
         if (m_dispLoad[i] != 0.0)
         {
            CHECK(m_Disp[i] == 0.0); // if a deflection load was applied, this node
                                     // had better be fixed and the solution must be zero
            m_Disp[i] = m_dispLoad[i];
         }
      }
   }
}

void Joint::GetDeflection(Float64* disp) const
{
   for (int i = 0; i < NumDof; i++)
      disp[i] = m_Disp[i];
}

void Joint::ComputeReactions()
{
   // Reactions = unbalanced member forces + loads applied directly to this joint
   m_Reaction[0] = 0;
   m_Reaction[1] = 0;
   m_Reaction[2] = 0;

   for (Member* ele : m_AttachedMembers)
   {
      JointIDType jntnum = ele->GetJointNum(this);
      Float64 react[3];
      ele->GetGlobalJntForces(jntnum, react);
      m_Reaction[0] += react[0];
      m_Reaction[1] += react[1];
      m_Reaction[2] += react[2];
   }
   m_Reaction[0] -= m_jntLoad[0];
   m_Reaction[1] -= m_jntLoad[1];
   m_Reaction[2] -= m_jntLoad[2];
}

void Joint::GetReactions(Float64* react) const
{
   for (int i = 0; i < NumDof; i++)
      react[i] = m_Reaction[i];
}

void Joint::Link(Member* pel)
{
   m_AttachedMembers.insert(pel);
}

bool Joint::IsEquilibriumSatisfied(Float64 forceTolerance, Float64 momentTolerance)
{
   // External forces
   Float64 fx = m_Reaction[0] + m_jntLoad[0];
   Float64 fy = m_Reaction[1] + m_jntLoad[1];
   Float64 mz = m_Reaction[2] + m_jntLoad[2];

   // Internal forces
   Float64 Fx = 0, Fy = 0, Mz = 0;
   for (Member* ele : m_AttachedMembers)
   {
      JointIDType jntId = ele->GetJointNum(this);
      Float64 eleEndForce[3];
      ele->GetGlobalJntForces(jntId, eleEndForce);
      Fx += eleEndForce[0];
      Fy += eleEndForce[1];
      Mz += eleEndForce[2];
   }

   Fx -= fx;
   Fy -= fy;
   Mz -= mz;

   // Check equilibrium
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
