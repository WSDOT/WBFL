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
#include <FEA2D\PointLoad.h>
#include <FEA2D\Member.h>
#include <FEA2D\Model.h>
#include <FEA2D\XFEA2D.h>
#include "Beam.h"
#include "MbrLoad.h"

#include <cmath>

using namespace WBFL::FEA2D;

namespace
{
   void CheckLoadOrientation(LoadOrientation orientation)
   {
      if (orientation != LoadOrientation::Global && orientation != LoadOrientation::Member && orientation != LoadOrientation::GlobalProjected)
      {
         THROW_FEA2D(ReasonCode::InvalidLoadOrientation);
      }
   }
}

// MbrLoadView - implements the internal MbrLoad interface by reading back
// through the owning PointLoad's fields. See the Pimpl design note in
// Include\FEA2D\PointLoad.h.
class PointLoad::MbrLoadView : public Internals::MbrLoad
{
public:
   explicit MbrLoadView(const PointLoad* pOwner) : m_pOwner(pOwner) {}

   void GetForceVector(long leftBC, long rightBC, Float64 Length, Float64 Angle, Float64* vector) override
   {
      Float64 La;
      GetRealLoadLocation(Length, &La);

      vector[0] = vector[1] = vector[2] = vector[3] = vector[4] = vector[5] = 0;

      Float64 Px, Py, Mz;
      GetLoadComponents(Angle, &Px, &Py, &Mz);

      Float64 Fx1, Fy1, Mz1, Fx2, Fy2, Mz2;
      if (Px != 0.0)
      {
         Internals::ConcLdBeam Pbeam(Px, La, Internals::Beam::ForceX, Length, 1, 1, leftBC, rightBC);
         Pbeam.GetReactions(Fx1, Fy1, Mz1, Fx2, Fy2, Mz2);
         vector[0] += Fx1; vector[1] += Fy1; vector[2] += Mz1;
         vector[3] += Fx2; vector[4] += Fy2; vector[5] += Mz2;
      }

      if (Py != 0.0)
      {
         Internals::ConcLdBeam Vbeam(Py, La, Internals::Beam::ForceY, Length, 1, 1, leftBC, rightBC);
         Vbeam.GetReactions(Fx1, Fy1, Mz1, Fx2, Fy2, Mz2);
         vector[0] += Fx1; vector[1] += Fy1; vector[2] += Mz1;
         vector[3] += Fx2; vector[4] += Fy2; vector[5] += Mz2;
      }

      if (Mz != 0.0)
      {
         Internals::ConcLdBeam Mbeam(Mz, La, Internals::Beam::MomentZ, Length, 1, 1, leftBC, rightBC);
         Mbeam.GetReactions(Fx1, Fy1, Mz1, Fx2, Fy2, Mz2);
         vector[0] += Fx1; vector[1] += Fy1; vector[2] += Mz1;
         vector[3] += Fx2; vector[4] += Fy2; vector[5] += Mz2;
      }
   }

   void GetDispVector(long leftBC, long rightBC, Float64 Length, Float64 Angle, Float64 EA, Float64 EI, Float64* vector) override
   {
      Float64 La;
      GetRealLoadLocation(Length, &La);

      vector[0] = vector[1] = vector[2] = vector[3] = vector[4] = vector[5] = 0;

      Float64 Px, Py, Mz;
      GetLoadComponents(Angle, &Px, &Py, &Mz);
      Internals::ConcLdBeam Pbeam(Px, La, Internals::Beam::ForceX, Length, EA, EI, leftBC, rightBC);
      Internals::ConcLdBeam Vbeam(Py, La, Internals::Beam::ForceY, Length, EA, EI, leftBC, rightBC);
      Internals::ConcLdBeam Mbeam(Mz, La, Internals::Beam::MomentZ, Length, EA, EI, leftBC, rightBC);

      Float64 Dx1, Dy1, Rz1, Dx2, Dy2, Rz2;

      Pbeam.GetDeflections(Dx1, Dy1, Rz1, Dx2, Dy2, Rz2);
      vector[0] += Dx1; vector[1] += Dy1; vector[2] += Rz1;
      vector[3] += Dx2; vector[4] += Dy2; vector[5] += Rz2;

      Vbeam.GetDeflections(Dx1, Dy1, Rz1, Dx2, Dy2, Rz2);
      vector[0] += Dx1; vector[1] += Dy1; vector[2] += Rz1;
      vector[3] += Dx2; vector[4] += Dy2; vector[5] += Rz2;

      Mbeam.GetDeflections(Dx1, Dy1, Rz1, Dx2, Dy2, Rz2);
      vector[0] += Dx1; vector[1] += Dy1; vector[2] += Rz1;
      vector[3] += Dx2; vector[4] += Dy2; vector[5] += Rz2;
   }

   void GetInternalForces(Float64 x, Float64 Length, Float64 Angle, MemberFaceType face, Float64* pFx, Float64* pFy, Float64* pMz) override
   {
      Float64 La;
      GetRealLoadLocation(Length, &La);

      const Float64 L_EPS = 1.0e-10; // TRICKY: tolerance is very finicky
                                      // found that 1.0e-07 was too loose and 1.0e-15 too tight

      // Load contributes to the internal forces if it occurs before a left
      // cut face or the load and the left face cut are at the right end of
      // the member; symmetric logic for the right face.
      if (((face == MemberFaceType::Left) && (x <= La + L_EPS)) ||
          ((face == MemberFaceType::Right) && (x >= La - L_EPS)))
      {
         *pFx = 0; *pFy = 0; *pMz = 0;
         return;
      }

      Float64 Px, Py, Mo;
      GetLoadComponents(Angle, &Px, &Py, &Mo);

      *pFx = Px;
      *pFy = Py;
      *pMz = Mo + Py * (La - x);
   }

   void GetDeflection(Float64 x, long leftBC, long rightBC, Float64 Length, Float64 Angle, Float64 EA, Float64 EI, Float64* pdx, Float64* pdy, Float64* prz) override
   {
      Float64 La;
      GetRealLoadLocation(Length, &La);

      *pdx = 0; *pdy = 0; *prz = 0;

      Float64 Px, Py, Mz;
      GetLoadComponents(Angle, &Px, &Py, &Mz);
      Internals::ConcLdBeam Pbeam(Px, La, Internals::Beam::ForceX, Length, EA, EI, leftBC, rightBC);
      Internals::ConcLdBeam Vbeam(Py, La, Internals::Beam::ForceY, Length, EA, EI, leftBC, rightBC);
      Internals::ConcLdBeam Mbeam(Mz, La, Internals::Beam::MomentZ, Length, EA, EI, leftBC, rightBC);

      Float64 Dx, Dy, Rz;

      Pbeam.GetDeflection(x, Dx, Dy, Rz);
      *pdx += Dx; *pdy += Dy; *prz += Rz;

      Vbeam.GetDeflection(x, Dx, Dy, Rz);
      *pdx += Dx; *pdy += Dy; *prz += Rz;

      Mbeam.GetDeflection(x, Dx, Dy, Rz);
      *pdx += Dx; *pdy += Dy; *prz += Rz;
   }

   void GetOriginForces(Float64 Length, Float64 Angle, Float64* pFx, Float64* pFy, Float64* pMz) override
   {
      Float64 La;
      GetRealLoadLocation(Length, &La);

      Float64 Px, Py, Mo;
      GetLoadComponents(Angle, &Px, &Py, &Mo);

      *pFx = Px;
      *pFy = Py;
      *pMz = Mo + Py * La;
   }

private:
   const PointLoad* m_pOwner;

   void GetLoadComponents(Float64 Angle, Float64* pPx, Float64* pPy, Float64* pMz) const
   {
      LoadOrientation orientation = m_pOwner->m_Orientation;
      Float64 Fx = m_pOwner->m_Fx;
      Float64 Fy = m_pOwner->m_Fy;

      // Fx component
      if (orientation == LoadOrientation::Global || orientation == LoadOrientation::GlobalProjected)
      {
         *pPx = Fx * cos(Angle);
         *pPy = -Fx * sin(Angle);
      }
      else
      {
         *pPx = Fx;
         *pPy = 0;
      }

      // Fy component
      if (orientation == LoadOrientation::Global || orientation == LoadOrientation::GlobalProjected)
      {
         *pPx += Fy * sin(Angle);
         *pPy += Fy * cos(Angle);
      }
      else
      {
         *pPy += Fy;
      }

      // Mz component
      *pMz = m_pOwner->m_Mz;
   }

   void GetRealLoadLocation(Float64 length, Float64* pLoc) const
   {
      CHECK(length >= -1.0);

      Float64 loc = Member::GetRealLocation(length, m_pOwner->m_Location);

      if (loc == -1.0)
      {
         // we're in errorland
         if (m_pOwner->m_Location < 0.0)
         {
            // fractional error
            THROW_FEA2D(ReasonCode::FractionalValueOutOfRange);
         }
         else
         {
            // explicit location error
            THROW_FEA2D(ReasonCode::PointLoadOffGirderEnd);
         }
      }

      *pLoc = loc;
   }
};

PointLoad::PointLoad(Model* pModel, LoadCaseIDType loadingID, LoadIDType id, MemberIDType memberID, Float64 location, Float64 Fx, Float64 Fy, Float64 Mz, LoadOrientation orientation) :
   m_pModel(pModel), m_LoadingID(loadingID), m_ID(id), m_MemberID(memberID), m_Orientation(orientation), m_Location(location), m_Fx(Fx), m_Fy(Fy), m_Mz(Mz),
   m_pMbrLoadView(std::make_unique<MbrLoadView>(this))
{
   CheckLoadOrientation(orientation);
}

PointLoad::~PointLoad() = default;

LoadIDType PointLoad::GetID() const noexcept { return m_ID; }

MemberIDType PointLoad::GetMemberID() const noexcept { return m_MemberID; }

bool PointLoad::SetMemberID(MemberIDType id) noexcept
{
   if (m_MemberID != id) { m_MemberID = id; m_pModel->OnLoadingChanged(m_LoadingID); return true; }
   return false;
}

LoadOrientation PointLoad::GetOrientation() const noexcept { return m_Orientation; }

bool PointLoad::SetOrientation(LoadOrientation orientation)
{
   CheckLoadOrientation(orientation);
   if (m_Orientation != orientation) { m_Orientation = orientation; m_pModel->OnLoadingChanged(m_LoadingID); return true; }
   return false;
}

Float64 PointLoad::GetLocation() const noexcept { return m_Location; }

bool PointLoad::SetLocation(Float64 location)
{
   if (location < -1.0)
   {
      THROW_FEA2D(ReasonCode::InvalidPointLoadLocation);
   }

   if (m_Location != location) { m_Location = location; m_pModel->OnLoadingChanged(m_LoadingID); return true; }
   return false;
}

void PointLoad::GetForce(Float64* pFx, Float64* pFy, Float64* pMz) const noexcept
{
   *pFx = m_Fx; *pFy = m_Fy; *pMz = m_Mz;
}

void PointLoad::SetForce(Float64 Fx, Float64 Fy, Float64 Mz) noexcept
{
   m_Fx = Fx; m_Fy = Fy; m_Mz = Mz;
   m_pModel->OnLoadingChanged(m_LoadingID);
}

Float64 PointLoad::GetFx() const noexcept { return m_Fx; }
bool PointLoad::SetFx(Float64 fx) noexcept { if (m_Fx != fx) { m_Fx = fx; m_pModel->OnLoadingChanged(m_LoadingID); return true; } return false; }
Float64 PointLoad::GetFy() const noexcept { return m_Fy; }
bool PointLoad::SetFy(Float64 fy) noexcept { if (m_Fy != fy) { m_Fy = fy; m_pModel->OnLoadingChanged(m_LoadingID); return true; } return false; }
Float64 PointLoad::GetMz() const noexcept { return m_Mz; }
bool PointLoad::SetMz(Float64 mz) noexcept { if (m_Mz != mz) { m_Mz = mz; m_pModel->OnLoadingChanged(m_LoadingID); return true; } return false; }

LoadCaseIDType PointLoad::GetLoadingID() const noexcept { return m_LoadingID; }

Internals::MbrLoad* PointLoad::GetMbrLoad() const noexcept { return m_pMbrLoadView.get(); }
