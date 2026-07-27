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
#include <FEA2D\DistributedLoad.h>
#include <FEA2D\Member.h>
#include <FEA2D\Model.h>
#include <FEA2D\XFEA2D.h>
#include "Beam.h"
#include "MbrLoad.h"

#include <cmath>
#include <MathEx.h>

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
// through the owning DistributedLoad's fields. See the Pimpl design note
// in Include\FEA2D\PointLoad.h.
class DistributedLoad::MbrLoadView : public Internals::MbrLoad
{
public:
   explicit MbrLoadView(const DistributedLoad* pOwner) : m_pOwner(pOwner) {}

   void GetForceVector(long leftBC, long rightBC, Float64 Length, Float64 Angle, Float64* vector) override
   {
      Float64 La, Lb, WxStart, WyStart, WxEnd, WyEnd;
      GetLocalData(Angle, Length, &La, &Lb, &WxStart, &WyStart, &WxEnd, &WyEnd);

      vector[0] = vector[1] = vector[2] = vector[3] = vector[4] = vector[5] = 0;

      Float64 Fx1, Fy1, Mz1, Fx2, Fy2, Mz2;
      if (WxStart != 0.0 || WxEnd != 0.0)
      {
         Internals::TrapezoidalLdBeam Pbeam(WxStart, WxEnd, La, Lb, Internals::Beam::ForceX, Length, 1, 1, leftBC, rightBC);
         Pbeam.GetReactions(Fx1, Fy1, Mz1, Fx2, Fy2, Mz2);
         vector[0] += Fx1; vector[1] += Fy1; vector[2] += Mz1;
         vector[3] += Fx2; vector[4] += Fy2; vector[5] += Mz2;
      }

      if (WyStart != 0.0 || WyEnd != 0.0)
      {
         Internals::TrapezoidalLdBeam Pbeam(WyStart, WyEnd, La, Lb, Internals::Beam::ForceY, Length, 1, 1, leftBC, rightBC);
         Pbeam.GetReactions(Fx1, Fy1, Mz1, Fx2, Fy2, Mz2);
         vector[0] += Fx1; vector[1] += Fy1; vector[2] += Mz1;
         vector[3] += Fx2; vector[4] += Fy2; vector[5] += Mz2;
      }
   }

   void GetDispVector(long leftBC, long rightBC, Float64 Length, Float64 Angle, Float64 EA, Float64 EI, Float64* vector) override
   {
      Float64 La, Lb, WxStart, WyStart, WxEnd, WyEnd;
      GetLocalData(Angle, Length, &La, &Lb, &WxStart, &WyStart, &WxEnd, &WyEnd);

      vector[0] = vector[1] = vector[2] = vector[3] = vector[4] = vector[5] = 0;

      Float64 Dx1, Dy1, Rz1, Dx2, Dy2, Rz2;
      if (WxStart != 0.0 || WxEnd != 0.0)
      {
         Internals::TrapezoidalLdBeam Pbeam(WxStart, WxEnd, La, Lb, Internals::Beam::ForceX, Length, EA, EI, leftBC, rightBC);
         Pbeam.GetDeflections(Dx1, Dy1, Rz1, Dx2, Dy2, Rz2);
         vector[0] += Dx1; vector[1] += Dy1; vector[2] += Rz1;
         vector[3] += Dx2; vector[4] += Dy2; vector[5] += Rz2;
      }

      if (WyStart != 0.0 || WyEnd != 0.0)
      {
         Internals::TrapezoidalLdBeam Pbeam(WyStart, WyEnd, La, Lb, Internals::Beam::ForceY, Length, EA, EI, leftBC, rightBC);
         Pbeam.GetDeflections(Dx1, Dy1, Rz1, Dx2, Dy2, Rz2);
         vector[0] += Dx1; vector[1] += Dy1; vector[2] += Rz1;
         vector[3] += Dx2; vector[4] += Dy2; vector[5] += Rz2;
      }
   }

   void GetInternalForces(Float64 x, Float64 Length, Float64 Angle, MemberFaceType face, Float64* pFx, Float64* pFy, Float64* pMz) override
   {
      Float64 La, Lb, Wxa, Wya, Wxb, Wyb;
      GetLocalData(Angle, Length, &La, &Lb, &Wxa, &Wya, &Wxb, &Wyb);

      if (La == Lb ||
          (La == 0.0 && Lb == 0.0) ||
          ((face == MemberFaceType::Left) && (x <= La)) ||
          ((face == MemberFaceType::Right) && (x >= Lb)))
      {
         // Load has no contribution at this location
         *pFx = 0; *pFy = 0; *pMz = 0;
         return;
      }

      if (face == MemberFaceType::Left)
      {
         if (x < Lb)
         {
            // get uniform load values at x
            Wxb = Wxa + (Wxb - Wxa) / (Lb - La) * (x - La);
            Wyb = Wya + (Wyb - Wya) / (Lb - La) * (x - La);
            Lb = x;
         }

         *pFx = (Wxa + Wxb) / 2. * (Lb - La);
         *pFy = (Wya + Wyb) / 2. * (Lb - La);
         if (*pFy != 0.0)
         {
            // moment arm to resultant force from left end
            Float64 ma = La + 2. * (Wyb / 3. + Wya / 6.) * (Lb - La) / (Wya + Wyb);
            *pMz = (*pFy) * (ma - x);
         }
         else
         {
            *pMz = 0.0;
         }
      }
      else // face == MemberFaceType::Right
      {
         if (x > La)
         {
            // get uniform load values at x
            Wxa = Wxa + (Wxb - Wxa) / (Lb - La) * (x - La);
            Wya = Wya + (Wyb - Wya) / (Lb - La) * (x - La);
            La = x;
         }

         *pFx = (Wxb + Wxa) / 2. * (Lb - La);
         *pFy = (Wyb + Wya) / 2. * (Lb - La);
         if (*pFy != 0.0)
         {
            // moment arm to resultant force from left end
            Float64 ma = La + 2. * (Wyb / 3. + Wya / 6.) * (Lb - La) / (Wya + Wyb);
            *pMz = (*pFy) * (ma - x);
         }
         else
         {
            *pMz = 0.0;
         }
      }
   }

   void GetDeflection(Float64 x, long leftBC, long rightBC, Float64 Length, Float64 Angle, Float64 EA, Float64 EI, Float64* pdx, Float64* pdy, Float64* prz) override
   {
      *pdx = 0.0; *pdy = 0.0; *prz = 0.0;

      Float64 La, Lb, WxStart, WyStart, WxEnd, WyEnd;
      GetLocalData(Angle, Length, &La, &Lb, &WxStart, &WyStart, &WxEnd, &WyEnd);

      if (WxStart != 0.0 || WxEnd != 0.0)
      {
         Internals::TrapezoidalLdBeam Pbeam(WxStart, WxEnd, La, Lb, Internals::Beam::ForceX, Length, EA, EI, leftBC, rightBC);
         Pbeam.GetDeflection(x, *pdx, *pdy, *prz);
      }

      if (WyStart != 0.0 || WyEnd != 0.0)
      {
         Float64 dx, dy, rz;
         Internals::TrapezoidalLdBeam Pbeam(WyStart, WyEnd, La, Lb, Internals::Beam::ForceY, Length, EA, EI, leftBC, rightBC);
         Pbeam.GetDeflection(x, dx, dy, rz);
         *pdx += dx; *pdy += dy; *prz += rz;
      }
   }

   void GetOriginForces(Float64 Length, Float64 Angle, Float64* pFx, Float64* pFy, Float64* pMz) override
   {
      Float64 La, Lb, Wxa, Wya, Wxb, Wyb;
      GetLocalData(Angle, Length, &La, &Lb, &Wxa, &Wya, &Wxb, &Wyb);

      if (La == Lb || (m_pOwner->m_WEnd == 0.0 && m_pOwner->m_WStart == 0.0))
      {
         *pFx = 0; *pFy = 0; *pMz = 0;
         return;
      }

      *pFx = (Wxa + Wxb) / 2. * (Lb - La);
      *pFy = (Wya + Wyb) / 2. * (Lb - La);
      if (*pFy != 0.0)
      {
         // moment arm to resultant force from left end
         Float64 ma = La + 2. * (Wyb / 3. + Wya / 6.) * (Lb - La) / (Wya + Wyb);
         *pMz = (*pFy) * ma;
      }
      else
      {
         if (fabs(Wya) == fabs(Wyb) && !IsZero(Wya) && !IsZero(Wyb))
         {
            // this happens when Wa and Wb have opposite signs but equal
            // magnitude - the moment effect is not zero... treat the
            // loading as two triangular loads with the zero load point
            // being at La + (Lb-La)/2
            CHECK(::BinarySign(Wya) != ::BinarySign(Wyb));
            Float64 ma = (La + (Lb - La) / 6.) * Wya * (Lb - La) / 4.;
            Float64 mb = (La + 5. * (Lb - La) / 6.) * Wyb * (Lb - La) / 4.;
            *pMz = ma + mb;
         }
         else
         {
            *pMz = 0.0;
         }
      }
   }

private:
   const DistributedLoad* m_pOwner;

   void GetLocalData(Float64 Angle, Float64 length, Float64* pStartLoc, Float64* pEndLoc, Float64* pWxStart, Float64* pWyStart, Float64* pWxEnd, Float64* pWyEnd) const
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
            THROW_FEA2D(ReasonCode::DistLoadOffGirderEnd);
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
            THROW_FEA2D(ReasonCode::DistLoadOffGirderEnd);
         }
      }

      // Local force components
      Float64 wxend, wxstart, wyend, wystart;
      LoadOrientation orientation = m_pOwner->m_Orientation;
      LoadDirection direction = m_pOwner->m_Direction;
      Float64 m_WEnd = m_pOwner->m_WEnd;
      Float64 m_WStart = m_pOwner->m_WStart;

      if (orientation == LoadOrientation::Global || orientation == LoadOrientation::GlobalProjected)
      {
         Float64 ca = cos(Angle);
         Float64 sa = sin(Angle);

         // factor for projection
         Float64 wend, wstart;
         if (orientation == LoadOrientation::GlobalProjected)
         {
            if (direction == LoadDirection::Fx)
            {
               wend = m_WEnd * fabs(sa);
               wstart = m_WStart * fabs(sa);
            }
            else // LoadDirection::Fy
            {
               wend = m_WEnd * fabs(ca);
               wstart = m_WStart * fabs(ca);
            }
         }
         else
         {
            wend = m_WEnd;
            wstart = m_WStart;
         }

         // perform rotation into member coords
         if (direction == LoadDirection::Fx)
         {
            wxend = wend * ca;
            wyend = -wend * sa;
            wxstart = wstart * ca;
            wystart = -wstart * sa;
         }
         else // LoadDirection::Fy
         {
            wxend = wend * sa;
            wyend = wend * ca;
            wxstart = wstart * sa;
            wystart = wstart * ca;
         }
      }
      else
      {
         if (direction == LoadDirection::Fx)
         {
            wxend = m_WEnd;
            wyend = 0.0;
            wxstart = m_WStart;
            wystart = 0.0;
         }
         else // LoadDirection::Fy
         {
            wxend = 0.0;
            wyend = m_WEnd;
            wxstart = 0.0;
            wystart = m_WStart;
         }
      }

      // flip values if user entered start>end
      if (endloc < startloc)
      {
         *pStartLoc = endloc;
         *pEndLoc = startloc;
         *pWxEnd = wxstart;
         *pWyEnd = wystart;
         *pWxStart = wxend;
         *pWyStart = wyend;
      }
      else
      {
         *pStartLoc = startloc;
         *pEndLoc = endloc;
         *pWxEnd = wxend;
         *pWyEnd = wyend;
         *pWxStart = wxstart;
         *pWyStart = wystart;
      }
   }
};

DistributedLoad::DistributedLoad(Model* pModel, LoadCaseIDType loadingID, LoadIDType id, MemberIDType memberID, LoadDirection direction, Float64 startLocation, Float64 endLocation, Float64 wStart, Float64 wEnd, LoadOrientation orientation) :
   m_pModel(pModel), m_LoadingID(loadingID), m_ID(id), m_MemberID(memberID), m_Orientation(orientation), m_Direction(direction),
   m_StartLocation(startLocation), m_EndLocation(endLocation), m_WStart(wStart), m_WEnd(wEnd),
   m_pMbrLoadView(std::make_unique<MbrLoadView>(this))
{
   CheckLoadOrientation(orientation);
}

DistributedLoad::~DistributedLoad() = default;

LoadIDType DistributedLoad::GetID() const noexcept { return m_ID; }

MemberIDType DistributedLoad::GetMemberID() const noexcept { return m_MemberID; }

bool DistributedLoad::SetMemberID(MemberIDType id) noexcept
{
   if (m_MemberID != id) { m_MemberID = id; m_pModel->OnLoadingChanged(m_LoadingID); return true; }
   return false;
}

LoadOrientation DistributedLoad::GetOrientation() const noexcept { return m_Orientation; }

bool DistributedLoad::SetOrientation(LoadOrientation orientation)
{
   CheckLoadOrientation(orientation);
   if (m_Orientation != orientation) { m_Orientation = orientation; m_pModel->OnLoadingChanged(m_LoadingID); return true; }
   return false;
}

LoadDirection DistributedLoad::GetDirection() const noexcept { return m_Direction; }

bool DistributedLoad::SetDirection(LoadDirection direction) noexcept
{
   if (m_Direction != direction) { m_Direction = direction; m_pModel->OnLoadingChanged(m_LoadingID); return true; }
   return false;
}

Float64 DistributedLoad::GetStartLocation() const noexcept { return m_StartLocation; }

bool DistributedLoad::SetStartLocation(Float64 location)
{
   if (location < -1.0)
   {
      THROW_FEA2D(ReasonCode::InvalidDistLoadLocation);
   }
   if (m_StartLocation != location) { m_StartLocation = location; m_pModel->OnLoadingChanged(m_LoadingID); return true; }
   return false;
}

Float64 DistributedLoad::GetEndLocation() const noexcept { return m_EndLocation; }

bool DistributedLoad::SetEndLocation(Float64 location)
{
   if (location < -1.0)
   {
      THROW_FEA2D(ReasonCode::InvalidDistLoadLocation);
   }
   if (m_EndLocation != location) { m_EndLocation = location; m_pModel->OnLoadingChanged(m_LoadingID); return true; }
   return false;
}

Float64 DistributedLoad::GetWStart() const noexcept { return m_WStart; }
bool DistributedLoad::SetWStart(Float64 w) noexcept { if (m_WStart != w) { m_WStart = w; m_pModel->OnLoadingChanged(m_LoadingID); return true; } return false; }
Float64 DistributedLoad::GetWEnd() const noexcept { return m_WEnd; }
bool DistributedLoad::SetWEnd(Float64 w) noexcept { if (m_WEnd != w) { m_WEnd = w; m_pModel->OnLoadingChanged(m_LoadingID); return true; } return false; }

LoadCaseIDType DistributedLoad::GetLoadingID() const noexcept { return m_LoadingID; }

Internals::MbrLoad* DistributedLoad::GetMbrLoad() const noexcept { return m_pMbrLoadView.get(); }
