///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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
#include <DManip/DManipExp.h>

class CDisplayView;

namespace WBFL
{
   namespace DManip
   {
      /// @brief Interface defining coordinate mapping between logical, text, model, and world coordinate spaces
      /// Model Space - the space in which the model is created
      /// World Space - space resulting from the model space being rotated, translated, and scaled 
      /// Logical Space - space of the drawing window
      /// Text Space - space for text, in twips
      class DMANIPCLASS iCoordinateMap
      {
      public:
         /// @{
         /// @brief Maps Model point to World Point conversions
         virtual void MPtoWP(Float64 mx,Float64 my,Float64* wx,Float64* wy) const = 0;
         virtual WBFL::Geometry::Point2d MPtoWP(const WBFL::Geometry::Point2d& mp) const = 0;

         virtual void WPtoMP(Float64 wx,Float64 wy,Float64* mx,Float64* my) const = 0;
         virtual void WPtoMP(const WBFL::Geometry::Point2d& wp,Float64* mx,Float64* my) const = 0;
         /// @}

         /// @{
         /// @brief Maps World point to Logical Point conversions
         virtual void WPtoLP(Float64 wx,Float64 wy,LONG* lx,LONG* ly) const = 0;
         virtual void WPtoLP(const WBFL::Geometry::Point2d& wp,LONG* lx,LONG* ly) const = 0;

         virtual void LPtoWP(LONG lx,LONG ly,Float64* wx,Float64* wy) const = 0;
         virtual WBFL::Geometry::Point2d LPtoWP(LONG lx,LONG ly) const = 0;
         /// @}

         /// @{
         /// @brief Maps points to Text space. This space is always isometrically mapped.
         ///  -The origin of this space is at the Logical Origin
         ///  -Each text unit is a twip, or 1/20 of a point.(Because a point is 1/72 inch, a twip is 1/1440 inch.) 
         ///  -Positive X is to the right positive Y is up on the device.
         virtual void WPtoTP(Float64 wx,Float64 wy,LONG* tx,LONG* ty) const = 0;
         virtual void TPtoWP(LONG tx,LONG ty,Float64* wx,Float64* wy) const = 0;

         virtual void LPtoTP(LONG lx,LONG ly,LONG* tx,LONG* ty) const = 0;
         virtual void TPtoLP(LONG tx,LONG ty,LONG* lx,LONG* ly) const = 0;
         /// @}

         /// @brief Get size of window in text space coordinates (twips)
         /// This window is the size of the logical extents.
         virtual CSize GetTextWindowExtent() const = 0;

         /// @brief Get text extent in logical coordinates. Font dimensions are expected in
         /// 1/10 points (i.e., in form needed by CreatePointFontIndirect).
         /// Adjust for DPI scaling
         virtual CSize GetTextExtent(const CDisplayView* pView,const LOGFONT& font, LPCTSTR lpszText) const = 0;
      };
   };
};
