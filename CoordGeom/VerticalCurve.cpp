///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/VerticalCurve.h>
#include <CoordGeom/Alignment.h>
#include <CoordGeom/XCoordGeom.h>
#include <CoordGeom/COGO.h>

using namespace WBFL::COGO;

std::shared_ptr<VerticalCurve> VerticalCurve::Create()
{
   return std::shared_ptr<VerticalCurve>(new VerticalCurve());
}

std::shared_ptr<VerticalCurve> VerticalCurve::Create(const ProfilePoint& pbg, const ProfilePoint& pvi, const ProfilePoint& pfg, Float64 L1, Float64 L2)
{
   auto vc = Create();
   vc->Init(pbg, pvi, pfg, L1, L2);
   return vc;
}

std::shared_ptr<VerticalCurve> VerticalCurve::Create(const ProfilePoint& pbg, const ProfilePoint& pfg, Float64 g1, Float64 g2)
{
   auto vc = Create();
   vc->Init(pbg, pfg, g1, g2);
   return vc;
}

void VerticalCurve::Init(const ProfilePoint& pbg, const ProfilePoint& pvi, const ProfilePoint& pfg, Float64 L1, Float64 L2)
{
   SetPBG(pbg);
   SetPVI(pvi);
   SetPFG(pfg);
   SetLength(L1, L2);
   ComputeFromGradePoints(false);
}

void VerticalCurve::Init(const ProfilePoint& pbg, const ProfilePoint& pfg, Float64 g1, Float64 g2)
{
   SetPBG(pbg);
   SetPFG(pfg);
   SetEntryGrade(g1);
   SetExitGrade(g2);
   ComputeFromGradePoints(true);
}

void VerticalCurve::ComputeFromGradePoints(bool bCompute)
{
   m_bComputeFromGrades = bCompute;
   MakeDirty();
}

bool VerticalCurve::ComputeFromGradePoints() const
{
   return m_bComputeFromGrades;
}

void VerticalCurve::SetPBG(const ProfilePoint& pbg)
{
   m_PBG = pbg;
   MakeDirty();
}

const ProfilePoint& VerticalCurve::GetPBG() const
{
   return m_PBG;
}

void VerticalCurve::SetPVI(const ProfilePoint& pvi)
{
   m_PVI = pvi;
   MakeDirty();
}

const ProfilePoint& VerticalCurve::GetPVI() const
{
   if (m_bComputeFromGrades)
   {
      UpdateCurve();
   }
   return m_PVI;
}

void VerticalCurve::SetPFG(const ProfilePoint& pfg)
{
   m_PFG = pfg;
   MakeDirty();
}

const ProfilePoint& VerticalCurve::GetPFG() const
{
   return m_PFG;
}

void VerticalCurve::SetLength(Float64 l1, Float64 l2)
{
   m_L1 = l1;
   m_L2 = l2;
   MakeDirty();
}

void VerticalCurve::SetL1(Float64 l1)
{
   m_L1 = l1;
   MakeDirty();
}

void VerticalCurve::SetL2(Float64 l2)
{
   m_L2 = l2;
   MakeDirty();
}

std::tuple<Float64, Float64, Float64> VerticalCurve::GetCurveLengths() const
{
   UpdateCurve();
   return std::make_tuple(m_L1 + m_L2, m_L1, m_L2);
}

Float64 VerticalCurve::GetL1() const
{
   UpdateCurve();
   return m_L1;
}

Float64 VerticalCurve::GetL2() const
{
   UpdateCurve();
   return m_L2;
}

void VerticalCurve::SetEntryGrade(Float64 g1)
{
   m_g1 = g1;
   MakeDirty();
}

Float64 VerticalCurve::GetEntryGrade() const
{
   UpdateCurve();
   return m_g1;
}

void VerticalCurve::SetExitGrade(Float64 g2)
{
   m_g2 = g2;
   MakeDirty();
}

Float64 VerticalCurve::GetExitGrade() const
{
   UpdateCurve();
   return m_g2;
}

ProfilePoint VerticalCurve::GetBVC() const
{
   UpdateCurve();
   return m_BVC;
}

ProfilePoint VerticalCurve::GetEVC() const
{
   UpdateCurve();
   return m_EVC;
}

ProfilePoint VerticalCurve::GetHighPoint() const
{
   UpdateCurve();

   ProfilePoint high_point;
   if (IsZero(m_L1) && IsZero(m_L2))
   {
      // this curve is has no length so it is just a profile point
      high_point = m_PVI;
   }
   else
   {
      auto bvc = GetBVC();
      auto pvi = GetPVI();
      auto evc = GetEVC();
      auto g1 = GetEntryGrade();
      auto g2 = GetExitGrade();


      auto [staTrans,elevTrans,gTrans] = TransitionPoint();

      auto alignment = GetAlignment();
      // High point on left curve
      Float64 bvcValue   = COGO::ConvertToNormalizedStation(alignment,bvc.GetStation());
      Float64 transValue = COGO::ConvertToNormalizedStation(alignment,staTrans);
      Float64 xLeft = -g1 * m_L1 / (gTrans - g1) + bvcValue;
      Float64 yLeft;
      if (bvcValue < xLeft && xLeft < transValue)
      {
         // high point is on the curve
         yLeft = GetElevation(xLeft);
      }
      else
      {
         // high point is off the curve, check the extreme ends
         if (bvc.GetElevation() < elevTrans)
         {
            xLeft = transValue;
            yLeft = elevTrans;
         }
         else
         {
            xLeft = bvcValue;
            yLeft = bvc.GetElevation();
         }
      }

      // High point on right curve
      Float64 evcValue = COGO::ConvertToNormalizedStation(alignment, evc.GetStation());
      Float64 xRight = -gTrans * m_L2 / (g2 - gTrans) + transValue;
      Float64 yRight;
      if (transValue < xRight && xRight < evcValue)
      {
         // high point is on the curve
         yRight = GetElevation(xRight);
      }
      else
      {
         // high point is off the curve, check the extreme ends
         if (evc.GetElevation() < elevTrans)
         {
            xRight = transValue;
            yRight = elevTrans;
         }
         else
         {
            xRight = evcValue;
            yRight = evc.GetElevation();
         }
      }

      if (yRight <= yLeft)
      {
         auto station = COGO::ConvertFromNormalizedStation(alignment, xLeft);
         high_point.Move(station, yLeft);
      }
      else
      {
         auto station = COGO::ConvertFromNormalizedStation(alignment, xRight);
         high_point.Move(station, yRight);
      }
   }

   return high_point;
}

ProfilePoint VerticalCurve::GetLowPoint() const
{
   UpdateCurve();

   ProfilePoint low_point;

   if (IsZero(m_L1) && IsZero(m_L2))
   {
      // this curve is has no length so it is just a profile point
      low_point = m_PVI;
   }
   else
   {
      auto bvc = GetBVC();
      auto pvi = GetPVI();
      auto evc = GetEVC();
      auto g1 = GetEntryGrade();
      auto g2 = GetExitGrade();

      auto [staTrans, elevTrans, gTrans] = TransitionPoint();

      auto alignment = GetAlignment();

      // Low point on left curve
      Float64 bvcValue = COGO::ConvertToNormalizedStation(alignment, bvc.GetStation());
      Float64 transValue = COGO::ConvertToNormalizedStation(alignment,staTrans);
      Float64 xLeft = -g1 * m_L1 / (gTrans - g1) + bvcValue;
      Float64 yLeft;
      if (bvcValue < xLeft && xLeft < transValue)
      {
         // low point is on the curve
         yLeft = GetElevation(xLeft);
      }
      else
      {
         // low point is off the curve, check the ends
         if (elevTrans < bvc.GetElevation())
         {
            xLeft = transValue;
            yLeft = elevTrans;
         }
         else
         {
            xLeft = bvcValue;
            yLeft = bvc.GetElevation();
         }
      }

      // Low point on right curve
      Float64 evcValue = COGO::ConvertToNormalizedStation(alignment,evc.GetStation());
      Float64 xRight = -gTrans * m_L2 / (g2 - gTrans) + transValue;
      Float64 yRight;
      if (transValue < xRight && xRight < evcValue)
      {
         // low point is on the curve
         yRight = GetElevation(xRight);
      }
      else
      {
         // low point is off the curve, check the ends
         if (elevTrans < evc.GetElevation())
         {
            xRight = transValue;;
            yRight = elevTrans;
         }
         else
         {
            xRight = evcValue;
            yRight = evc.GetElevation();
         }
      }

      if (yLeft < yRight)
      {
         auto station = COGO::ConvertFromNormalizedStation(alignment, xLeft);
         low_point.Move(station, yLeft);
      }
      else
      {
         auto station = COGO::ConvertFromNormalizedStation(alignment, xRight);
         low_point.Move(station, yRight);
      }
   }

   return low_point;
}

Float64 VerticalCurve::GetGrade(const Station& station) const
{
   UpdateCurve();

   auto g1 = GetEntryGrade();
   auto g2 = GetExitGrade();

   Float64 grade = 0.0;

   auto alignment = GetAlignment();

   if (IsZero(m_L1) && IsZero(m_L2))
   {
      // this curve is has no length so it is just a profile point
      auto result = COGO::CompareStations(alignment,station, m_PVI.GetStation());
      if (0 < result)
      {
         // Before curve
         grade = g1;
      }
      else if (result < 0)
      {
         // After curve
         grade = g2;
      }
      else
      {
         // exactly at PVI
         grade = g1;
      }
   }
   else
   {
      auto bvc = GetBVC();
      auto evc = GetEVC();

      if (0 < COGO::CompareStations(alignment,station,bvc.GetStation()))
      {
         // Before curve
         grade = g1;
      }
      else if (0 < COGO::CompareStations(alignment,evc.GetStation(),station))
      {
         // After curve
         grade = g2;
      }
      else
      {
         // On curve
         auto [staTrans, elevTrans, gTrans] = TransitionPoint();


         if (0 < COGO::CompareStations(alignment,station,staTrans))
         {
            // station is left of PVI
            Float64 x = COGO::DistanceBetweenStations(alignment,bvc.GetStation(),station);
            Float64 L = COGO::DistanceBetweenStations(alignment,bvc.GetStation(), staTrans);
            Float64 g = (gTrans - g1) * x / L + g1;
            grade = g;
         }
         else
         {
            // station is right of PVI
            Float64 x = COGO::DistanceBetweenStations(alignment,staTrans, station);
            Float64 L = COGO::DistanceBetweenStations(alignment,staTrans, evc.GetStation());
            Float64 g = (g2 - gTrans) * x / L + gTrans;
            grade = g;
         }
      }
   }
   return grade;
}

Float64 VerticalCurve::GetElevation(const Station& station) const
{
   UpdateCurve();

   Float64 staValue = COGO::ConvertToNormalizedStation(GetAlignment(),station);

   auto g1 = GetEntryGrade();
   auto g2 = GetExitGrade();

   Float64 elev = 0.0;

   if (IsZero(m_L1) && IsZero(m_L2))
   {
      // this curve is has no length so it is just a profile point
      auto [staPVI,elevPVI] = m_PVI.GetLocation();

      Float64 pviValue = COGO::ConvertToNormalizedStation(GetAlignment(),staPVI);

      if (IsEqual(pviValue, staValue))
      {
         elev = elevPVI;
      }
      else if (staValue < pviValue)
      {
         // Before curve
         elev = elevPVI - g1 * (pviValue - staValue);
      }
      else if (pviValue < staValue)
      {
         // After curve
         elev = elevPVI + g2 * (staValue - pviValue);
      }
      else
      {
         CHECK(false); // should not get here
      }
   }
   else
   {
      auto bvc = GetBVC(); // can we use m_BVC directly?
      auto [staBVC,elevBVC] = bvc.GetLocation();
      
      Float64 bvcValue = COGO::ConvertToNormalizedStation(GetAlignment(),staBVC);

      auto evc = GetEVC(); // can we use m_EVC directly?

      auto [staEVC,elevEVC] = evc.GetLocation();
      Float64 evcValue = COGO::ConvertToNormalizedStation(GetAlignment(),staEVC);

      if (staValue < bvcValue)
      {
         // Before curve
         elev = elevBVC - g1 * (bvcValue - staValue);
      }
      else if (evcValue < staValue)
      {
         // After curve
         elev = elevEVC + g2 * (staValue - evcValue);
      }
      else
      {
         // On curve
         auto [staTrans,elevTrans,gradeTrans] = TransitionPoint();
         Float64 transValue = COGO::ConvertToNormalizedStation(GetAlignment(), staTrans);

         if (staValue < transValue)
         {
            // station is left of PVI
            Float64 x = staValue - bvcValue;
            Float64 L = transValue - bvcValue;
            Float64 y;
            if (IsZero(L))
            {
               y = elevBVC;
            }
            else
            {
               y = (gradeTrans - g1) * pow(x, 2) / (2 * L) + g1 * x + elevBVC;
            }
            elev = y;
         }
         else
         {
            // station is right of PVI
            Float64 x = staValue - transValue;
            Float64 L = evcValue - transValue;
            Float64 y;
            if (IsZero(L))
            {
               y = elevTrans;
            }
            else
            {
               y = (g2 - gradeTrans) * pow(x, 2) / (2 * L) + gradeTrans * x + elevTrans;
            }

            elev = y;
         }
      }
   }
   return elev;
}

Float64 VerticalCurve::GetE(Float64 t) const
{
   auto [L,L1,L2] = GetCurveLengths();

   Float64 h = GetH();

   Float64 e = 0;
   if (IsZero(h))
   {
      e = 0;
   }
   else if (t < L1)
   {
      e = h * pow(t / L1, 2);
   }
   else
   {
      // get t from end of curve
      t = (L1 + L2 - t);
      e = h * pow(t / L2, 2);
   }
   return e;
}

Float64 VerticalCurve::GetH() const
{
   auto [L, L1, L2] = GetCurveLengths();

   if (IsZero(L))
   {
      return 0.0;
   }

   Float64 a = GetA();

   return (L1 * L2 * a) / (2 * (L1 + L2));
}

Float64 VerticalCurve::GetK1() const
{
   auto [L, L1, L2] = GetCurveLengths();

   Float64 k = 0;
   if (IsZero(L2) || IsEqual(L1, L2))
   {
      // curve is symmetric
      Float64 a = GetA();
      Float64 L = L1 + L2;
      k = IsZero(L) ? Float64_Max : a / L;
   }
   else
   {
      // curve is unsymmetrical
      auto [station,elev,grade] = TransitionPoint();

      Float64 entry_grade = GetEntryGrade();

      Float64 a = grade - entry_grade;
      k = a / L1;
   }

   return k;
}

Float64 VerticalCurve::GetK2() const
{
   auto [L, L1, L2] = GetCurveLengths();

   Float64 k = 0;
   if (IsZero(L2) || IsEqual(L1, L2))
   {
      // curve is symmetric
      k = GetK1();
   }
   else
   {
      auto [station,elev,grade] = TransitionPoint();

      Float64 exit_grade = GetExitGrade();

      Float64 a = exit_grade - grade;
      k = a / L1;
   }
   return k;
}

Float64 VerticalCurve::GetA() const
{
   // NOTE: don't use m_g1 and m_g2 direction. They may be invalid. 
   // The GetXXXGrade() functions compute the current grades if needed
   return GetExitGrade() - GetEntryGrade();
}

//
// ProfileElement methods
//

std::shared_ptr<ProfileElement> VerticalCurve::Clone() const
{
   return std::shared_ptr<ProfileElement>(new VerticalCurve(*this));
}

const ProfilePoint& VerticalCurve::GetStartPoint() const
{
   UpdateCurve();
   return m_BVC;
}

const ProfilePoint& VerticalCurve::GetEndPoint() const
{
   UpdateCurve();
   return m_EVC;
}

Float64 VerticalCurve::GetLength() const
{
   UpdateCurve();
   return m_L1 + m_L2;
}

//
// Private methods
//

void VerticalCurve::MakeDirty()
{
   m_bIsDirty = true;

   __super::OnProfileElementChanged();
}

bool VerticalCurve::IsValid() const
{
   auto alignment = GetAlignment();

   if (m_bComputeFromGrades)
   {
      if (IsEqual(m_g1, m_g2))
      {
         Float64 pbg, pfg;
         try
         {
            pbg = COGO::ConvertToNormalizedStation(alignment, m_PBG.GetStation());
            pfg = COGO::ConvertToNormalizedStation(alignment, m_PFG.GetStation());
         }
         catch (...)
         {
            // if this curve is not associated with a profile and alignment, stations must be normalized
            return false;
         }

         Float64 elevPBG = m_PBG.GetElevation();
         Float64 elevPFG = m_PFG.GetElevation();

         Float64 elev = elevPBG + m_g1 * (pfg - pbg);
         if (!IsEqual(elevPFG, elev))
         {
            // Grade lines never intersect... g1 and g2 are the same so the
            // grades are parallel lines. The line going from PBG must
            // pass through PFG otherwise the profile is discontinuous and invalid
            return false;
         }
      }
   }
   else
   {
      if (IsZero(m_L1) && !IsZero(m_L2))
      {
         // L2 must be zero if L1 is zero
         return false;
      }

      Float64 pbg, pvi, pfg;
      try
      {
         pbg = COGO::ConvertToNormalizedStation(alignment, m_PBG.GetStation());
         pvi = COGO::ConvertToNormalizedStation(alignment, m_PVI.GetStation());
         pfg = COGO::ConvertToNormalizedStation(alignment, m_PFG.GetStation());
      }
      catch (...)
      {
         // if this curve is not associated with a profile and alignment, stations must be normalized
         return false;
      }

      if (pvi < pbg || pfg < pvi)
      {
         return false;
      }
   }

   return true;
}

void VerticalCurve::UpdateCurve() const
{
   if (m_bIsDirty)
   {
      if (!IsValid())
         THROW_COGO(WBFL_COGO_E_VERTCURVEPOINTS);

      auto alignment = GetAlignment();

      if (m_bComputeFromGrades)
      {
         // Need to compute L1, L2, and PVI

         // BVC = PBG and EVC = PFG
         m_BVC.Move(m_PBG.GetStation(), m_PBG.GetElevation());
         m_EVC.Move(m_PFG.GetStation(), m_PFG.GetElevation());

         Float64 staBVC = COGO::ConvertToNormalizedStation(alignment, m_BVC.GetStation());
         Float64 staEVC = COGO::ConvertToNormalizedStation(alignment, m_EVC.GetStation());
         Float64 elevBVC = m_BVC.GetElevation();
         Float64 elevEVC = m_EVC.GetElevation();

         Float64 staPVI;
         if (IsZero(m_g2 - m_g1))
         {
            // entry and exit grades are the same
            // so there isn't a point where the grade breaks
            // just use the mid-point between begin and end curve stations
            staPVI = (staBVC + staEVC) / 2;
         }
         else
         {
            staPVI = ((elevBVC - elevEVC) + m_g2 * (staEVC - staBVC)) / (m_g2 - m_g1) + staBVC;
         }
         m_L1 = staPVI - staBVC;
         m_L2 = staEVC - staPVI;

         // we need to be concerned with station equations so we just can't add m_L1 to
         // the BVC station... make PVI be a copy of BVC and then use the IncrementStationBy
         // method to compute the station of the PVI taking into account station equations
         Station pviStation = COGO::IncrementStationBy(alignment, m_BVC.GetStation(), m_L1);

         // compute the PVI elevation
         Float64 elevPVI = elevBVC + m_L1 * m_g1;

         m_PVI.Move(pviStation, elevPVI);

         if (IsEqual(m_L1, m_L2))
         {
            // symmetric curve
            m_L1 = m_L1 + m_L2;
            m_L2 = 0;
         }
      }
      else
      {
         // need to compute BVC, EVC, g1, and g2

         // Compute g1 and g2
         const auto& staPBG = m_PBG.GetStation();
         const auto& staPVI = m_PVI.GetStation();
         const auto& staPFG = m_PFG.GetStation();

         Float64 elevPBG = m_PBG.GetElevation();
         Float64 elevPVI = m_PVI.GetElevation();
         Float64 elevPFG = m_PFG.GetElevation();

         Float64 dx = COGO::DistanceBetweenStations(alignment, staPBG, staPVI);
         Float64 dy = elevPVI - elevPBG;

         m_g1 = IsZero(dx) ? 0 : dy / dx;

         dx = COGO::DistanceBetweenStations(alignment, staPVI, staPFG);
         dy = elevPFG - elevPVI;

         m_g2 = IsZero(dx) ? 0 : dy / dx;

         // Compute BVC and EVC
         Float64 staPVIValue = COGO::ConvertToNormalizedStation(alignment, staPVI);

         Float64 l1 = m_L1;
         Float64 l2 = m_L2;
         if (IsZero(m_L2))
         {
            // curve is symmetric with m_L1 being the total length
            l1 /= 2;
            l2 = l1;
         }

         Float64 staBVC = staPVIValue - l1;
         Float64 elevBVC = elevPVI - m_g1 * l1;
         m_BVC.Move(staBVC, elevBVC);

         Float64 staEVC = staPVIValue + l2;
         Float64 elevEVC = elevPVI + m_g2 * l2;
         m_EVC.Move(staEVC, elevEVC);
      }

      m_bIsDirty = false;
   }
}

std::shared_ptr<const Alignment> VerticalCurve::GetAlignment() const
{
   auto profile = GetProfile();
   auto alignment = (profile ? profile->GetAlignment() : nullptr);
   return alignment;
}

std::pair<Float64, Float64> VerticalCurve::ComputeGradeAndElevation(const Station& station) const
{
   return std::make_pair(GetGrade(station), GetElevation(station));
}

std::tuple<Station,Float64,Float64> VerticalCurve::TransitionPoint() const
{
   // Computes the station, elevation, and grade at the transition point
   // between the two vertical curves - asymmetric vertical curves are actually two symmetric vertical curves

   auto bvc = GetBVC();
   auto evc = GetEVC();
   auto g1 = GetEntryGrade();
   auto g2 = GetExitGrade();

   Float64 elevPVI1 = bvc.GetElevation() + g1 * m_L1 / 2; // Elevation at intersection of g1 and grade at PVI

   Float64 h; // distance from PVI to curve
   if (IsZero(m_L1 + m_L2))
   {
      h = 0;
   }
   else
   {
      h = m_L1 * m_L2 * (g2 - g1) / (2 * (m_L1 + m_L2)); // positive if sag curve
   }

   const auto& station = m_PVI.GetStation();
   auto elevation = m_PVI.GetElevation() + h;
   Float64 grade;
   if (IsZero(m_L1))
   {
      grade = g1;
   }
   else
   {
      grade = (elevation - elevPVI1) * 2 / m_L1;
   }

   return std::make_tuple(station, elevation, grade);
}
