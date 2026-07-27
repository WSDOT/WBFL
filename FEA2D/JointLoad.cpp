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
#include <FEA2D\JointLoad.h>
#include <FEA2D\Model.h>

using namespace WBFL::FEA2D;

JointLoad::JointLoad(Model* pModel, LoadCaseIDType loadingID, LoadIDType id, JointIDType jointID, Float64 Fx, Float64 Fy, Float64 Mz) :
   m_pModel(pModel), m_LoadingID(loadingID), m_ID(id), m_JointID(jointID), m_Fx(Fx), m_Fy(Fy), m_Mz(Mz)
{
}

LoadIDType JointLoad::GetID() const noexcept
{
   return m_ID;
}

JointIDType JointLoad::GetJointID() const noexcept
{
   return m_JointID;
}

bool JointLoad::SetJointID(JointIDType jointID) noexcept
{
   if (m_JointID != jointID)
   {
      m_JointID = jointID;
      m_pModel->OnLoadingChanged(m_LoadingID);
      return true;
   }
   return false;
}

void JointLoad::GetForce(Float64* pFx, Float64* pFy, Float64* pMz) const noexcept
{
   *pFx = m_Fx;
   *pFy = m_Fy;
   *pMz = m_Mz;
}

void JointLoad::SetForce(Float64 Fx, Float64 Fy, Float64 Mz) noexcept
{
   m_Fx = Fx;
   m_Fy = Fy;
   m_Mz = Mz;
   m_pModel->OnLoadingChanged(m_LoadingID);
}

Float64 JointLoad::GetFx() const noexcept
{
   return m_Fx;
}

bool JointLoad::SetFx(Float64 fx) noexcept
{
   if (m_Fx != fx)
   {
      m_Fx = fx;
      m_pModel->OnLoadingChanged(m_LoadingID);
      return true;
   }
   return false;
}

Float64 JointLoad::GetFy() const noexcept
{
   return m_Fy;
}

bool JointLoad::SetFy(Float64 fy) noexcept
{
   if (m_Fy != fy)
   {
      m_Fy = fy;
      m_pModel->OnLoadingChanged(m_LoadingID);
      return true;
   }
   return false;
}

Float64 JointLoad::GetMz() const noexcept
{
   return m_Mz;
}

bool JointLoad::SetMz(Float64 mz) noexcept
{
   if (m_Mz != mz)
   {
      m_Mz = mz;
      m_pModel->OnLoadingChanged(m_LoadingID);
      return true;
   }
   return false;
}

LoadCaseIDType JointLoad::GetLoadingID() const noexcept
{
   return m_LoadingID;
}
