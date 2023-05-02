///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <CoordGeom/Utilities.h>

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


      Station staTrans;
      Float64 elevTrans, gTrans;
      std::tie(staTrans,elevTrans,gTrans) = TransitionPoint();

      auto alignment = GetAlignment();
      // High point on left curve
      Float64 bvcValue   = Utilities::ConvertToNormalizedStation(alignment,bvc.GetStation());
      Float64 transValue = Utilities::ConvertToNormalizedStation(alignment,staTrans);
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
      Float64 evcValue = Utilities::ConvertToNormalizedStation(alignment, evc.GetStation());
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
         auto station = Utilities::ConvertFromNormalizedStation(alignment, xLeft);
         high_point.Move(station, yLeft);
      }
      else
      {
         auto station = Utilities::ConvertFromNormalizedStation(alignment, xRight);
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

      Station staTrans;
      Float64 elevTrans, gTrans;
      std::tie(staTrans, elevTrans, gTrans) = TransitionPoint();

      auto alignment = GetAlignment();

      // Low point on left curve
      Float64 bvcValue = Utilities::ConvertToNormalizedStation(alignment, bvc.GetStation());
      Float64 transValue = Utilities::ConvertToNormalizedStation(alignment,staTrans);
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
      Float64 evcValue = Utilities::ConvertToNormalizedStation(alignment,evc.GetStation());
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
         auto station = Utilities::ConvertFromNormalizedStation(alignment, xLeft);
         low_point.Move(station, yLeft);
      }
      else
      {
         auto station = Utilities::ConvertFromNormalizedStation(alignment, xRight);
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
      auto result = Utilities::CompareStations(alignment,station, m_PVI.GetStation());
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

      if (0 < Utilities::CompareStations(alignment,station,bvc.GetStation()))
      {
         // Before curve
         grade = g1;
      }
      else if (0 < Utilities::CompareStations(alignment,evc.GetStation(),station))
      {
         // After curve
         grade = g2;
      }
      else
      {
         // On curve
         Station staTrans;
         Float64 elevTrans, gTrans;
         std::tie(staTrans, elevTrans, gTrans) = TransitionPoint();


         if (0 < Utilities::CompareStations(alignment,station,staTrans))
         {
            // station is left of PVI
            Float64 x = Utilities::DistanceBetweenStations(alignment,bvc.GetStation(),station);
            Float64 L = Utilities::DistanceBetweenStations(alignment,bvc.GetStation(), staTrans);
            Float64 g = (gTrans - g1) * x / L + g1;
            grade = g;
         }
         else
         {
            // station is right of PVI
            Float64 x = Utilities::DistanceBetweenStations(alignment,staTrans, station);
            Float64 L = Utilities::DistanceBetweenStations(alignment,staTrans, evc.GetStation());
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

   Float64 staValue = Utilities::ConvertToNormalizedStation(GetAlignment(),station);

   auto g1 = GetEntryGrade();
   auto g2 = GetExitGrade();

   Float64 elev = 0.0;

   if (IsZero(m_L1) && IsZero(m_L2))
   {
      // this curve is has no length so it is just a profile point
      Station staPVI;
      Float64 elevPVI;
      std::tie(staPVI,elevPVI) = m_PVI.GetLocation();

      Float64 pviValue = Utilities::ConvertToNormalizedStation(GetAlignment(),staPVI);

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
      Station staBVC;
      Float64 elevBVC;
      std::tie(staBVC,elevBVC) = bvc.GetLocation();
      
      Float64 bvcValue = Utilities::ConvertToNormalizedStation(GetAlignment(),staBVC);

      auto evc = GetEVC(); // can we use m_EVC directly?

      Station staEVC;
      Float64 elevEVC;
      std::tie(staEVC,elevEVC) = evc.GetLocation();
      Float64 evcValue = Utilities::ConvertToNormalizedStation(GetAlignment(),staEVC);

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
         Station staTrans;
         Float64 elevTrans, gradeTrans; // transition point
         std::tie(staTrans,elevTrans,gradeTrans) = TransitionPoint();
         Float64 transValue = Utilities::ConvertToNormalizedStation(GetAlignment(), staTrans);

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
   Float64 L, L1, L2;
   std::tie(L,L1,L2) = GetCurveLengths();

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
   Float64 L, L1, L2;
   std::tie(L,L1,L2) = GetCurveLengths();

   if (IsZero(L))
   {
      return 0.0;
   }

   Float64 a = GetA();

   return (L1 * L2 * a) / (2 * (L1 + L2));
}

Float64 VerticalCurve::GetK1() const
{
   Float64 L, L1, L2;
   std::tie(L, L1, L2) = GetCurveLengths();

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
      Station station;
      Float64 elev;
      Float64 grade;
      std::tie(station,elev,grade) = TransitionPoint();

      Float64 entry_grade = GetEntryGrade();

      Float64 a = grade - entry_grade;
      k = a / L1;
   }

   return k;
}

Float64 VerticalCurve::GetK2() const
{
   Float64 L, L1, L2;
   std::tie(L, L1, L2) = GetCurveLengths();

   Float64 k = 0;
   if (IsZero(L2) || IsEqual(L1, L2))
   {
      // curve is symmetric
      k = GetK1();
   }
   else
   {
      Station station;
      Float64 elev;
      Float64 grade;
      std::tie(station,elev,grade) = TransitionPoint();

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
            pbg = Utilities::ConvertToNormalizedStation(alignment, m_PBG.GetStation());
            pfg = Utilities::ConvertToNormalizedStation(alignment, m_PFG.GetStation());
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
         pbg = Utilities::ConvertToNormalizedStation(alignment, m_PBG.GetStation());
         pvi = Utilities::ConvertToNormalizedStation(alignment, m_PVI.GetStation());
         pfg = Utilities::ConvertToNormalizedStation(alignment, m_PFG.GetStation());
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

         Float64 staBVC = Utilities::ConvertToNormalizedStation(alignment, m_BVC.GetStation());
         Float64 staEVC = Utilities::ConvertToNormalizedStation(alignment, m_EVC.GetStation());
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
         Station pviStation = Utilities::IncrementStationBy(alignment, m_BVC.GetStation(), m_L1);

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

         Float64 dx = Utilities::DistanceBetweenStations(alignment, staPBG, staPVI);
         Float64 dy = elevPVI - elevPBG;

         m_g1 = IsZero(dx) ? 0 : dy / dx;

         dx = Utilities::DistanceBetweenStations(alignment, staPVI, staPFG);
         dy = elevPFG - elevPVI;

         m_g2 = IsZero(dx) ? 0 : dy / dx;

         // Compute BVC and EVC
         Float64 staPVIValue = Utilities::ConvertToNormalizedStation(alignment, staPVI);

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

#if defined _UNITTEST
bool VerticalCurve::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("VerticalCurve");
   TRY_TESTME(Test1(rlog, true));
   TRY_TESTME(Test1(rlog, false));
   TRY_TESTME(Test2(rlog));
   TRY_TESTME(Test3(rlog, true));
   TRY_TESTME(Test3(rlog, false));
   TESTME_EPILOG("VerticalCurve");
}

bool VerticalCurve::Test1(WBFL::Debug::Log& rlog, bool bStandAlone)
{
   TESTME_PROLOGUE("VerticalCurve::Test1");

   auto vc = VerticalCurve::Create();

   if (!bStandAlone)
   {
      auto alignment = Alignment::Create();
      auto profile = Profile::Create();
      alignment->AddProfile(0, profile);
      profile->AddProfileElement(vc);
   }
   
   ProfilePoint pbg;
   ProfilePoint pvi;
   ProfilePoint pfg;


   // Sag curve
   pbg.Move(100, 100);
   pvi.Move(200, 50);
   pfg.Move(400, 100);

   vc->Init(pbg, pvi, pfg, 100, 200);

   TRY_TESTME(IsEqual(vc->GetEntryGrade(), -0.5));
   TRY_TESTME(IsEqual(vc->GetExitGrade(), 0.25));
   TRY_TESTME(IsEqual(vc->GetLength(), 300.0));

   TRY_TESTME(IsEqual(vc->GetElevation(150), 81.25));
   TRY_TESTME(IsEqual(vc->GetElevation(200), 75.0));
   TRY_TESTME(IsEqual(vc->GetElevation(250), 76.5625));

   TRY_TESTME(IsEqual(vc->GetGrade(150), -0.25));
   TRY_TESTME(IsEqual(vc->GetGrade(200), 0.0));
   TRY_TESTME(IsEqual(vc->GetGrade(250),0.0625));
   TRY_TESTME(IsEqual(vc->GetGrade(0), -0.5));
   TRY_TESTME(IsEqual(vc->GetGrade(600), 0.25));

   TRY_TESTME(vc->GetHighPoint() == ProfilePoint(100, 100)); // high point at start
   TRY_TESTME(vc->GetLowPoint() == ProfilePoint(200, 75.0)); // low point between ends

   // adjust the curve so the high point is at the end
   pfg.SetElevation(200);
   vc->SetPFG(pfg);
   TRY_TESTME(vc->GetHighPoint() == ProfilePoint(400, 200)); // high point at end

   // make a crest curve
   pbg.Move(100,100);
   pvi.Move(200, 150);
   pfg.Move(300, 50);
   vc->SetPBG(pbg);
   vc->SetPVI(pvi);
   vc->SetPFG(pfg);
   vc->SetLength(100, 100);

   // high point between ends
   TRY_TESTME(vc->GetHighPoint() == ProfilePoint(166.66667, 116.66667)); 

   // low point at end
   TRY_TESTME(vc->GetLowPoint() == ProfilePoint(300, 50));

   // adjust the curve so the low point at start
   pbg.SetElevation(10);
   vc->SetPBG(pbg);
   TRY_TESTME(vc->GetLowPoint() == ProfilePoint(100, 10));

   // From "Fundamentals of Surveying" Schmidt and Wong, Third Edition
   // PWS Engineering Press, 1985, ISBN 0-534-04161-2, pg 453, Example 12.3
   pbg.Move(4850, 436.34);
   pvi.Move(5250, 432.34);
   pfg.Move(5650, 441.14);
   vc->SetPBG(pbg);
   vc->SetPVI(pvi);
   vc->SetPFG(pfg);
   vc->SetLength(400, 400);

   TRY_TESTME(IsEqual(vc->GetElevation(4700), 437.84));
   TRY_TESTME(IsEqual(vc->GetElevation(4850), 436.34));
   TRY_TESTME(IsEqual(vc->GetElevation(4900), 435.89));
   TRY_TESTME(IsEqual(vc->GetElevation(5000), 435.29));
   TRY_TESTME(IsEqual(vc->GetElevation(5100), 435.09));
   TRY_TESTME(IsEqual(vc->GetElevation(5200), 435.29));
   TRY_TESTME(IsEqual(vc->GetElevation(5300), 435.89));
   TRY_TESTME(IsEqual(vc->GetElevation(5400), 436.89));
   TRY_TESTME(IsEqual(vc->GetElevation(5500), 438.29));
   TRY_TESTME(IsEqual(vc->GetElevation(5600), 440.09));
   TRY_TESTME(IsEqual(vc->GetElevation(5650), 441.14));
   TRY_TESTME(IsEqual(vc->GetElevation(6000), 448.84));

   TRY_TESTME(vc->GetHighPoint() == ProfilePoint(5650, 441.14));
   TRY_TESTME(vc->GetLowPoint() == ProfilePoint(5100, 435.09));

   Float64 L, L1, L2;
   std::tie(L, L1, L2) = vc->GetCurveLengths();

   Float64 g1 = vc->GetEntryGrade();
   Float64 g2 = vc->GetExitGrade();

   Float64 A = vc->GetA();
   TRY_TESTME(IsEqual(A, g2 - g1));
   TRY_TESTME(IsEqual(vc->GetK1(), A / L));
   TRY_TESTME(IsEqual(vc->GetK2(), A / L));
   TRY_TESTME(IsEqual(vc->GetH(), A* L1* L2 / (2 * L)));
   TRY_TESTME(IsEqual(vc->GetE(0), 0.0));
   TRY_TESTME(IsEqual(vc->GetE(L), 0.0));
   TRY_TESTME(IsEqual(vc->GetE(L1), vc->GetH()));
   TRY_TESTME(IsEqual(vc->GetE(L1 / 2), 0.8));
   TRY_TESTME(IsEqual(vc->GetE(L1 + L2 / 2), 0.8));

   // put the points out of order
   vc->SetPBG(pfg);
   vc->SetPVI(pvi);
   vc->SetPFG(pbg);
   try { vc->GetLength(); }
   catch (XCoordGeom& e) { TRY_TESTME(e.GetReason() == WBFL_COGO_E_VERTCURVEPOINTS); }

   TESTME_EPILOG("VerticalCurve::Test1");
}

bool VerticalCurve::Test2(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("VerticalCurve::Test2");

   auto vc = VerticalCurve::Create();

   auto alignment = Alignment::Create();
   auto profile = Profile::Create();
   alignment->AddProfile(0, profile);
   profile->AddProfileElement(vc);

   ProfilePoint pbg;
   ProfilePoint pvi;
   ProfilePoint pfg;

   // create station equation
   alignment->AddStationEquation(150, 250);
   alignment->AddStationEquation(400, 200);

   // Sag curve
   pbg.Move(100, 100);
   pvi.Move(Station(1,300), 50); // Station 3+00 in Station Equation Zone 1
   pfg.Move(400, 100);

   vc->Init(pbg, pvi, pfg, 100, 200);

   TRY_TESTME(IsEqual(vc->GetEntryGrade(), -0.5));
   TRY_TESTME(IsEqual(vc->GetExitGrade(), 0.25));
   TRY_TESTME(IsEqual(vc->GetLength(), 300.));

   auto station = alignment->ConvertFromNormalizedStation(150);
   TRY_TESTME(IsEqual(vc->GetElevation(station), 81.25));
   TRY_TESTME(IsEqual(vc->GetGrade(station), -0.25));

   station = alignment->ConvertFromNormalizedStation(200);
   TRY_TESTME(IsEqual(vc->GetElevation(station), 75.0));
   TRY_TESTME(IsEqual(vc->GetGrade(station), 0.0));

   station = alignment->ConvertFromNormalizedStation(250);
   TRY_TESTME(IsEqual(vc->GetElevation(station), 76.5625));
   TRY_TESTME(IsEqual(vc->GetGrade(station), 0.0625));

   station = alignment->ConvertFromNormalizedStation(0);
   TRY_TESTME(IsEqual(vc->GetElevation(station), 150.));
   TRY_TESTME(IsEqual(vc->GetGrade(station), -0.50));

   station = alignment->ConvertFromNormalizedStation(600);
   TRY_TESTME(IsEqual(vc->GetElevation(station), 150.0));
   TRY_TESTME(IsEqual(vc->GetGrade(station), 0.25));

   // high point at start
   TRY_TESTME(vc->GetHighPoint() == ProfilePoint(Station(0, 100), 100.0));

   // low point between ends
   TRY_TESTME(vc->GetLowPoint() == ProfilePoint(Station(1, 300), 75.0));

   // high point at end
   pfg.SetElevation(200);
   vc->SetPFG(pfg);
   TRY_TESTME(vc->GetHighPoint() == ProfilePoint(Station(2, 300), 200.0));

   TESTME_EPILOG("VerticalCurve::Test2");
}

bool VerticalCurve::Test3(WBFL::Debug::Log& rlog, bool bStandAlone)
{
   TESTME_PROLOGUE("VerticalCurve::Test3");
   // This is same as Test1, except that instead of PBG and PFG being points off the curve, 
   // they are the BVC and EVC. We input grades instead of lengths (PVI gets computed)
   auto vc = VerticalCurve::Create();

   if (!bStandAlone)
   {
      auto alignment = Alignment::Create();
      auto profile = Profile::Create();
      alignment->AddProfile(0, profile);
      profile->AddProfileElement(vc);
   }


   ProfilePoint pbg;
   ProfilePoint pfg;


   // Sag curve
   pbg.Move(100, 100);
   pfg.Move(400, 100);
   vc->Init(pbg, pfg, -0.5, 0.25);

   Float64 l, l1, l2;
   std::tie(l,l1,l2) = vc->GetCurveLengths();
   TRY_TESTME(IsEqual(l, 300.0));
   TRY_TESTME(IsEqual(l1, 100.0));
   TRY_TESTME(IsEqual(l2, 200.0));

   TRY_TESTME(IsEqual(vc->GetElevation(150), 81.25));
   TRY_TESTME(IsEqual(vc->GetElevation(200), 75.0));
   TRY_TESTME(IsEqual(vc->GetElevation(250), 76.5625));

   TRY_TESTME(IsEqual(vc->GetGrade(150), -0.25));
   TRY_TESTME(IsEqual(vc->GetGrade(200), 0.0));
   TRY_TESTME(IsEqual(vc->GetGrade(250), 0.0625));
   TRY_TESTME(IsEqual(vc->GetGrade(0), -0.5));
   TRY_TESTME(IsEqual(vc->GetGrade(600), 0.25));

   TRY_TESTME(vc->GetHighPoint() == ProfilePoint(100, 100)); // high point at start
   TRY_TESTME(vc->GetLowPoint() == ProfilePoint(200, 75.0)); // low point between ends

   // adjust the curve so the high point is at the end
   pfg.SetElevation(200);
   vc->SetPFG(pfg);
   TRY_TESTME(vc->GetHighPoint() == ProfilePoint(400, 200)); // high point at end

   // high point at end
   pfg.SetElevation(200);
   vc->SetPFG(pfg);
   vc->SetExitGrade(0.75);
   TRY_TESTME(vc->GetHighPoint() == ProfilePoint(400, 200)); // high point at end

   TESTME_EPILOG("VerticalCurve::Test3");
}

#endif // _UNITTEST


