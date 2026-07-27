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
#include <FEA2D\MemberStrain.h>
#include <FEA2D\Member.h>
#include <FEA2D\Model.h>
#include <FEA2D\XFEA2D.h>
#include "Beam.h"
#include "MbrLoad.h"

using namespace WBFL::FEA2D;

// MbrLoadView - implements the internal MbrLoad interface by reading back
// through the owning MemberStrain's fields. See the Pimpl design note in
// Include\FEA2D\PointLoad.h.
class MemberStrain::MbrLoadView : public Internals::MbrLoad
{
public:
   explicit MbrLoadView(const MemberStrain* pOwner) : m_pOwner(pOwner) {}

   void GetForceVector(long leftBC, long rightBC, Float64 Length, Float64 Angle, Float64* vector) override
   {
      Float64 La, Lb;
      GetLocalData(Angle, Length, &La, &Lb);

      // Member strain loads need the referenced member's own EA/EI - unlike
      // PointLoad/DistributedLoad, which are handed EA/EI by the caller.
      Member* pmbr = m_pOwner->m_pModel->FindMember(m_pOwner->m_MemberID);
      CHECK(pmbr != nullptr);
      Float64 ea = pmbr->GetEA();
      Float64 ei = pmbr->GetEI();

      Internals::UniformMemberDistortionBeam beam(m_pOwner->m_AxialStrain, m_pOwner->m_CurvatureStrain, La, Lb, Length, ea, ei, leftBC, rightBC);
      Float64 fxl, fyl, mzl, fxr, fyr, mzr;
      beam.GetReactions(fxl, fyl, mzl, fxr, fyr, mzr);

      vector[0] = fxl; vector[1] = fyl; vector[2] = mzl;
      vector[3] = fxr; vector[4] = fyr; vector[5] = mzr;
   }

   void GetDispVector(long leftBC, long rightBC, Float64 Length, Float64 Angle, Float64 EA, Float64 EI, Float64* vector) override
   {
      Float64 La, Lb;
      GetLocalData(Angle, Length, &La, &Lb);

      Internals::UniformMemberDistortionBeam beam(m_pOwner->m_AxialStrain, m_pOwner->m_CurvatureStrain, La, Lb, Length, EA, EI, leftBC, rightBC);
      Float64 dxl, dyl, rzl, dxr, dyr, rzr;
      beam.GetDeflections(dxl, dyl, rzl, dxr, dyr, rzr);

      vector[0] = dxl; vector[1] = dyl; vector[2] = rzl;
      vector[3] = dxr; vector[4] = dyr; vector[5] = rzr;
   }

   void GetInternalForces(Float64 x, Float64 Length, Float64 Angle, MemberFaceType face, Float64* pFx, Float64* pFy, Float64* pMz) override
   {
      *pFx = 0; *pFy = 0; *pMz = 0;
   }

   void GetDeflection(Float64 x, long leftBC, long rightBC, Float64 Length, Float64 Angle, Float64 EA, Float64 EI, Float64* pdx, Float64* pdy, Float64* prz) override
   {
      Float64 La, Lb;
      GetLocalData(Angle, Length, &La, &Lb);

      Internals::UniformMemberDistortionBeam beam(m_pOwner->m_AxialStrain, m_pOwner->m_CurvatureStrain, La, Lb, Length, EA, EI, leftBC, rightBC);
      beam.GetDeflection(x, *pdx, *pdy, *prz);
   }

   void GetOriginForces(Float64 Length, Float64 Angle, Float64* pFx, Float64* pFy, Float64* pMz) override
   {
      *pFx = 0; *pFy = 0; *pMz = 0;
   }

private:
   const MemberStrain* m_pOwner;

   void GetLocalData(Float64 Angle, Float64 length, Float64* pStartLoc, Float64* pEndLoc) const
   {
      CHECK(length >= -1.0);

      Float64 startloc = Member::GetRealLocation(length, m_pOwner->m_StartLocation);
      if (startloc == -1.0)
      {
         if (m_pOwner->m_StartLocation < 0.0)
         {
            THROW_FEA2D(ReasonCode::FractionalValueOutOfRange);
         }
         else
         {
            THROW_FEA2D(ReasonCode::StrainLoadOffGirderEnd);
         }
      }

      Float64 endloc = Member::GetRealLocation(length, m_pOwner->m_EndLocation);
      if (endloc == -1.0)
      {
         if (m_pOwner->m_EndLocation < 0.0)
         {
            THROW_FEA2D(ReasonCode::FractionalValueOutOfRange);
         }
         else
         {
            THROW_FEA2D(ReasonCode::StrainLoadOffGirderEnd);
         }
      }

      // flip values if user entered start>end
      if (endloc < startloc)
      {
         *pStartLoc = endloc;
         *pEndLoc = startloc;
      }
      else
      {
         *pStartLoc = startloc;
         *pEndLoc = endloc;
      }
   }
};

MemberStrain::MemberStrain(Model* pModel, LoadCaseIDType loadingID, LoadIDType id, MemberIDType memberID, Float64 xStart, Float64 xEnd, Float64 axialStrain, Float64 curvatureStrain) :
   m_pModel(pModel), m_LoadingID(loadingID), m_ID(id), m_MemberID(memberID),
   m_AxialStrain(axialStrain), m_CurvatureStrain(curvatureStrain), m_StartLocation(xStart), m_EndLocation(xEnd),
   m_pMbrLoadView(std::make_unique<MbrLoadView>(this))
{
}

MemberStrain::~MemberStrain() = default;

LoadIDType MemberStrain::GetID() const noexcept { return m_ID; }

MemberIDType MemberStrain::GetMemberID() const noexcept { return m_MemberID; }

bool MemberStrain::SetMemberID(MemberIDType id) noexcept
{
   if (m_MemberID != id) { m_MemberID = id; m_pModel->OnLoadingChanged(m_LoadingID); return true; }
   return false;
}

Float64 MemberStrain::GetAxialStrain() const noexcept { return m_AxialStrain; }
bool MemberStrain::SetAxialStrain(Float64 strain) noexcept { if (m_AxialStrain != strain) { m_AxialStrain = strain; m_pModel->OnLoadingChanged(m_LoadingID); return true; } return false; }
Float64 MemberStrain::GetCurvatureStrain() const noexcept { return m_CurvatureStrain; }
bool MemberStrain::SetCurvatureStrain(Float64 strain) noexcept { if (m_CurvatureStrain != strain) { m_CurvatureStrain = strain; m_pModel->OnLoadingChanged(m_LoadingID); return true; } return false; }

Float64 MemberStrain::GetStartLocation() const noexcept { return m_StartLocation; }
bool MemberStrain::SetStartLocation(Float64 location) noexcept { if (m_StartLocation != location) { m_StartLocation = location; m_pModel->OnLoadingChanged(m_LoadingID); return true; } return false; }
Float64 MemberStrain::GetEndLocation() const noexcept { return m_EndLocation; }
bool MemberStrain::SetEndLocation(Float64 location) noexcept { if (m_EndLocation != location) { m_EndLocation = location; m_pModel->OnLoadingChanged(m_LoadingID); return true; } return false; }

LoadCaseIDType MemberStrain::GetLoadingID() const noexcept { return m_LoadingID; }

Internals::MbrLoad* MemberStrain::GetMbrLoad() const noexcept { return m_pMbrLoadView.get(); }
