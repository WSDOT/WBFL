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
#pragma once

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/ProfileElement.h>
#include <CoordGeom/ProfilePoint.h>
#include <CoordGeom/Profile.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief An object that represent a parabolic vertical curve.
      /// @image html Images/VertCurve.png
      /// * PBG = Point on Back Grade
      /// * PFG = Point on Forward Grade
      /// * PVI = Point of Vertical Intersection
      /// * BVC = Begin Vertical Curve
      /// * EVC = End Vertical Curve
      /// * E = Vertical distance from curve to tangent lines
      /// * H = Vertical distance from curve to PVI
      /// * g1 = Entry Grade
      /// * g2 = Exit Grade
      /// * L1 = Entry length
      /// * L2 = Exit Length
      class COORDGEOMCLASS VerticalCurve : public ProfileElement
      {
      private:
         VerticalCurve() = default;
         VerticalCurve(const VerticalCurve&) = default;
         VerticalCurve& operator=(const VerticalCurve&) = delete;

      public:
         ~VerticalCurve() = default;

         /// @brief Creates a VerticalCurve
         /// @return 
         static std::shared_ptr<VerticalCurve> Create();

         /// @brief Creates and initializes a VerticalCurve using points on the profile grade and curve lengths.
         /// @param pbg Point on the back grade
         /// @param pvi Point of vertical intersection
         /// @param pfg Point on forward grade
         /// @param L1 Back length from the BVC to the PVI
         /// @param L2 Forward length from the PVI to the EVC
         /// @return 
         static std::shared_ptr<VerticalCurve> Create(const ProfilePoint& pbg, const ProfilePoint& pvi, const ProfilePoint& pfg, Float64 L1, Float64 L2);

         /// @brief Creates and initializes a VerticalCurve using back grade and forward grade points located at the BVC and EVC and the back and forward grades
         /// @param pbg Point on the back grade at the BVC
         /// @param pfg Point on the forward grade at the EVC
         /// @param g1 Back grade
         /// @param g2 Forward grade
         /// @return 
         static std::shared_ptr<VerticalCurve> Create(const ProfilePoint& pbg, const ProfilePoint& pfg, Float64 g1, Float64 g2);

         /// @brief Initializes the VerticalCurve
         /// @param pbg Point on the back grade
         /// @param pvi Point of vertical intersection
         /// @param pfg Point on forward grade
         /// @param L1 Back length from the BVC to the PVI
         /// @param L2 Forward length from the PVI to the EVC
         void Init(const ProfilePoint& pbg, const ProfilePoint& pvi, const ProfilePoint& pfg, Float64 L1, Float64 L2);

         /// @brief Initializes the VerticalCurve
         /// @param pbg Point on the back grade at the BVC
         /// @param pfg Point on the forward grade at the EVC
         /// @param g1 Back grade
         /// @param g2 Forward grade
         void Init(const ProfilePoint& pbg, const ProfilePoint& pfg, Float64 g1, Float64 g2);

         /// @brief Sets the point on back grade
         /// @param pbg 
         void SetPBG(const ProfilePoint& pbg);
         const ProfilePoint& GetPBG() const;

         /// @brief Sets the point of vertical intersection
         /// @param pvi 
         void SetPVI(const ProfilePoint& pvi);
         const ProfilePoint& GetPVI() const;

         /// @brief Sets the point on forward grade
         /// @param pfg 
         void SetPFG(const ProfilePoint& pfg);
         const ProfilePoint& GetPFG() const;

         /// @brief Sets the curve lengths
         /// @param l1 Back length from the BVC to the PVI
         /// @param l2 Forward length from the PVI to the EVC
         void SetLength(Float64 l1, Float64 l2);

         /// @brief Sets back length
         /// @param l1 Back length from BVC to PVI
         void SetL1(Float64 l1);

         /// @brief Sets forward length
         /// @param l2 Forward length from PVI to EVC
         void SetL2(Float64 l2);

         /// @brief Returns the curve length parameters
         /// @return Returns a tuple of the form (TotalLength,L1,L2);
         std::tuple<Float64,Float64,Float64> GetCurveLengths() const;

         /// @brief Returns the curve length from BVC to PVI
         Float64 GetL1() const;

         /// @brief Returns the curve length from PVI to EVC
         Float64 GetL2() const;

         /// @brief Sets the back grade
         /// @param g1 
         void SetEntryGrade(Float64 g1);
         Float64 GetEntryGrade() const;

         /// @brief Sets the forward grade
         /// @param g2 
         void SetExitGrade(Float64 g2);
         Float64 GetExitGrade() const;

         /// @brief Returns the begin of vertical curve point
         /// @return 
         ProfilePoint GetBVC() const;

         /// @brief Returns the end of vertical curve point
         /// @return 
         ProfilePoint GetEVC() const;

         /// @brief Returns the high point in the curve
         /// @return 
         ProfilePoint GetHighPoint() const;

         /// @brief Returns the low point in the curve
         /// @return 
         ProfilePoint GetLowPoint() const;

         /// @brief Computes the profile grade at the specified station
         /// @param station 
         /// @return 
         Float64 GetGrade(const Station& station) const;

         /// @brief Computes the profile elevation at the specified station
         /// @param station 
         /// @return 
         Float64 GetElevation(const Station& station) const;

         /// @brief Vertical distance at any point on the curve to the tangent grade. 
         /// \f$ t < L_1, E = H \left(\frac{t}{L_1} \right)^2 \f$, otherwise \f$ E = H \left( \frac{L-t}{L_2} \right)^2 \f$
         /// @param t 
         /// @return 
         Float64 GetE(Float64 t) const;

         /// @brief Vertical distance from the curve to the VPI. 
         /// \f$ H = \frac{L_1 L_2 A}{2(L_1 + L_2)} \f$
         /// @return 
         Float64 GetH() const;

         /// @brief Vertical curve constant for left half of curve if unsymmetrical or the entire curve is symmetric. Horizontal distance need to make a 0.01 change in gradient.
         /// \f$ K = \frac{A}{L} \f$
         /// The K value is effectively an express for degree of curvature. The inverse of K is the minimum radius.
         /// \f$ \frac{K}{2} \f$ is the second derivative of the curve equation and represents the rate of change of the profile grade.
         /// @return 
         Float64 GetK1() const;

         /// @brief Vertical curve constant for right half of curve if unsymmetrical or the entire curve is symmetric. Horizontal distance need to make a 0.01 change in gradient.
         /// @return 
         Float64 GetK2() const;

         /// @brief Algebraic difference in gradients
         /// \f$ A = g_2 - g_1 \f$
         /// @return 
         Float64 GetA() const;

         //
         // ProfileElement
         //
         virtual std::shared_ptr<ProfileElement> Clone() const override;
         virtual const ProfilePoint& GetStartPoint() const override;
         virtual const ProfilePoint& GetEndPoint() const override;
         virtual Float64 GetLength() const override;
         virtual std::pair<Float64, Float64> ComputeGradeAndElevation(const Station& station) const override;

      private:
         // if true, L1, L2, BVC, PVI, and EVC are computed from PBG, PFG, g1, and g2
         // assuming BVC=PBG and EVC=PFG
         void ComputeFromGradePoints(bool bCompute);
         bool ComputeFromGradePoints() const;
         bool m_bComputeFromGrades{ false };

         mutable ProfilePoint m_PBG; // point on back grade
         mutable ProfilePoint m_PVI; // point of vertical grade intersection
         mutable ProfilePoint m_PFG; // point on forward grade

         mutable ProfilePoint m_BVC; // begin vertical curve
         mutable ProfilePoint m_EVC; // end vertical curve

         // These values can either be input or computed depending on m_bComputeFromGrades
         mutable Float64 m_L1{ 0.0 }, m_L2{ 0.0 }; // Half-length of curve
         mutable Float64 m_g1{ 0.0 }, m_g2{ 0.0 }; // entry and exit grades


         mutable bool m_bIsDirty{ true };
         void MakeDirty();
         bool IsValid() const; // return true if the curve is valid
         void UpdateCurve() const;

         std::shared_ptr<const Alignment> GetAlignment() const;

         // Station, elevation, grade of the transition point
         std::tuple<Station,Float64,Float64> TransitionPoint() const;
      };
   };
};
