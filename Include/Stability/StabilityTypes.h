///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2022  Washington State Department of Transportation
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

#include <Stability/StabilityExp.h>
#include <WBFLTypes.h>
#include <MathEx.h>

namespace WBFL
{
   namespace Stability
   {
      // Causes the compiler to instantiate the class and export it's symbols
      STABILITYTPL SimplePointT<Float64>;
      class STABILITYCLASS Point : public SimplePointT<Float64>
      {
      public:
         Point() = default;
         Point(const Point& other) = default;
         bool operator==(const Point& other) const { return IsEqual(X(), other.X()) && IsEqual(Y(), other.Y()); }
         bool operator!=(const Point & other) const {return !operator==(other);}

         Point& Offset(Float64 dx, Float64 dy) { X() += dx; Y() += dy; return *this; }
      };

      /// Constant indicating the face of a girder
      typedef enum GirderFace
      {
         Top, ///< Top face
         Bottom ///< Bottom face
      } GirderFace;

      /// Constant indicating the side of a girder
      typedef enum GirderSide
      {
         Left, ///< Left side
         Right ///< Right side
      } GirderSide;

      /// Constant indicate the direction of impact
      typedef enum ImpactDirection
      {
         NoImpact, ///< No impact
         ImpactUp, ///< Impact up
         ImpactDown ///< Impact down
      } ImpactDirection;

      /// Constant indicating when impact is considered in hauling stability analysis
      typedef enum HaulingImpact
      {
         NormalCrown, ///< impact applied only to the normal crown condition
         MaxSuper,    ///< impact applied only to the max superelevation condition   
         Both         ///< impact applied to both conditions
      } HaulingImpact;

      /// Constant indicating the direction of wind
      typedef GirderSide WindDirection;

      /// Constant indicating how wind load is defined
      typedef enum WindType
      {
         Speed, ///< defined by a wind speed and wind pressure is to be computed
         Pressure ///< wind pressure is input
      } WindType;

      /// Constant indicating a nominal corner of the girder
      typedef enum Corner
      {
         TopLeft,
         TopRight,
         BottomLeft,
         BottomRight
      } Corner;

      /// Constant indicate the location of a harp point
      typedef enum HarpPointLocation
      {
         StartHP, ///< Point near start of the girder where strands are deflected (typcially the left end of the girder)
         LeftHP, ///< Point where strands are deflected, left of mid-span
         RightHP, ///< Point where strands are deflected, right of mid-span
         EndHP ///< Point near end of the girder where strands are deflected (typcially the right end of the girder)
      } HarpPointLocation;

      /// Constant indicating the face of prismatic section of the girder
      typedef enum Section
      {
         Start, ///< Start of the section
         End ///< End of the section
      } Section;

      /// Constant indicating the type of centrifugal force occuring in the analysis
      typedef enum CFType
      {
         Adverse, ///< CF is towards the left (increases lateral deflection and roll over)
         Favorable ///< CF is towards the right
      } CFType;

      /// Constant indicating the method for compute the lateral offset of the center of mass /f$ z_o /f$
      typedef enum CalculationMethod
      {
         Exact, ///< A closed form, exact method 
         Approximate ///< An approximate numerical method
      } CalculationMethod;

      /// Constant indicating one of the hauling analysis crown slope types
      typedef enum HaulingSlope
      {
         CrownSlope, ///< The normal roadway crown slope
         Superelevation ///< Slope at maximum superelevation
      } HaulingSlope;

      /// Returns the GirderFace corresponding to a Corner
      inline GirderFace GetFace(Corner corner)
      {
         return (corner == TopLeft || corner == TopRight ? Top : Bottom);
      }

      /// Returns the GirderSide corresponding to a Corner
      inline GirderSide GetSide(Corner corner)
      {
         return (corner == TopLeft || corner == BottomLeft ? Left : Right);
      }
   }
}