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
#include <FEA2D\JointDisplacement.h>
#include <FEA2D\Model.h>

using namespace WBFL::FEA2D;

JointDisplacement::JointDisplacement(Model* pModel, LoadCaseIDType loadingID, LoadIDType id, JointIDType jointID, Float64 Dx, Float64 Dy, Float64 Rz) :
   m_pModel(pModel), m_LoadingID(loadingID), m_ID(id), m_JointID(jointID), m_Dx(Dx), m_Dy(Dy), m_Rz(Rz)
{
}

LoadIDType JointDisplacement::GetID() const noexcept
{
   return m_ID;
}

JointIDType JointDisplacement::GetJointID() const noexcept
{
   return m_JointID;
}

bool JointDisplacement::SetJointID(JointIDType jointID) noexcept
{
   if (m_JointID != jointID)
   {
      m_JointID = jointID;
      m_pModel->OnLoadingChanged(m_LoadingID);
      return true;
   }
   return false;
}

void JointDisplacement::GetDeflection(Float64* pDx, Float64* pDy, Float64* pRz) const noexcept
{
   *pDx = m_Dx;
   *pDy = m_Dy;
   *pRz = m_Rz;
}

void JointDisplacement::SetDeflection(Float64 Dx, Float64 Dy, Float64 Rz) noexcept
{
   m_Dx = Dx;
   m_Dy = Dy;
   m_Rz = Rz;
   m_pModel->OnLoadingChanged(m_LoadingID);
}

Float64 JointDisplacement::GetDx() const noexcept
{
   return m_Dx;
}

bool JointDisplacement::SetDx(Float64 dx) noexcept
{
   if (m_Dx != dx)
   {
      m_Dx = dx;
      m_pModel->OnLoadingChanged(m_LoadingID);
      return true;
   }
   return false;
}

Float64 JointDisplacement::GetDy() const noexcept
{
   return m_Dy;
}

bool JointDisplacement::SetDy(Float64 dy) noexcept
{
   if (m_Dy != dy)
   {
      m_Dy = dy;
      m_pModel->OnLoadingChanged(m_LoadingID);
      return true;
   }
   return false;
}

Float64 JointDisplacement::GetRz() const noexcept
{
   return m_Rz;
}

bool JointDisplacement::SetRz(Float64 rz) noexcept
{
   if (m_Rz != rz)
   {
      m_Rz = rz;
      m_pModel->OnLoadingChanged(m_LoadingID);
      return true;
   }
   return false;
}

LoadCaseIDType JointDisplacement::GetLoadingID() const noexcept
{
   return m_LoadingID;
}
