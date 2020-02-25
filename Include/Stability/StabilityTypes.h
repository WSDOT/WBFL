///////////////////////////////////////////////////////////////////////
// Stability
// Copyright © 1999-2020  Washington State Department of Transportation
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

#include <Stability\StabilityExp.h>

typedef struct stbTypes
{
   typedef enum GirderFace
   {
      Top,
      Bottom
   } GirderFace;

   typedef enum GirderSide
   {
      Left,
      Right
   } GirderSide;

   typedef enum ImpactDirection
   {
      NoImpact,
      ImpactUp,
      ImpactDown
   } ImpactDirection;

   typedef enum HaulingImpact
   {
      NormalCrown, // impact applied only to the normal crown condition
      MaxSuper,    // impact applied only to the max superelevation condition   
      Both         // impact applied to both conditions
   } HaulingImpact;

   typedef GirderSide WindDirection;

   typedef enum WindType
   {
      Speed,
      Pressure
   } WindType;

   typedef enum Corner
   {
      TopLeft,
      TopRight,
      BottomLeft,
      BottomRight
   } Corner;

   typedef enum HarpPointLocation
   {
      StartHP,
      LeftHP,
      RightHP,
      EndHP
   } HarpPointLocation;

   typedef enum Section
   {
      Start,
      End
   } Section;

   typedef enum CFType
   {
      Adverse, // CF is towards the left (increases lateral deflection and roll over)
      Favorable // CF is towards the right
   } CFType;

   typedef enum CalculationMethod
   {
      Exact,
      Approximate
   } CalculationMethod;

   typedef enum HaulingSlope
   {
      CrownSlope,
      Superelevation
   } HaulingSlope;

} stbTypes;

inline stbTypes::GirderFace GetFace(stbTypes::Corner corner)
{
   return (corner == stbTypes::TopLeft || corner == stbTypes::TopRight ? stbTypes::Top : stbTypes::Bottom);
}

inline stbTypes::GirderSide GetSide(stbTypes::Corner corner)
{
   return (corner == stbTypes::TopLeft || corner == stbTypes::BottomLeft? stbTypes::Left : stbTypes::Right);
}
