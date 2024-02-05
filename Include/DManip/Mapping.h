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
#include <DManip/DManipTypes.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief Interface that defines mapping between model and world space
      class DMANIPCLASS iMapping
      {
      public:
         // Set up text scaling factors in the DC
         // this method should be called from OnPrepareDC in your view
         // and it must be cleaned up after drawing by calling CleanUpDC
         virtual void PrepareDC(CDC* dc) = 0;
         virtual void CleanUpDC(CDC* dc) = 0;
         // Print DC's must be cleaned up by this call from CView::OnEndPrinting
         virtual void CleanUpPrintDC(CDC* dc) = 0;

         // Set up world extents. mapping is to logical extents,
         virtual void SetWorldExt(Float64 wx,Float64 wy) = 0;
         virtual void SetWorldExt(const WBFL::Geometry::Size2d& wExt) = 0;
         virtual const WBFL::Geometry::Size2d& GetWorldExt() const = 0;

         virtual void SetWorldOrg(Float64 wx,Float64 wy) = 0;
         virtual void SetWorldOrg(const WBFL::Geometry::Point2d& wOrg) = 0;
         virtual const WBFL::Geometry::Point2d& GetWorldOrg() const = 0;

         virtual void SetLogicalOrg(const POINT& org) = 0;
         virtual void SetLogicalOrg(LONG lx,LONG ly) = 0;
         virtual POINT GetLogicalOrg() const = 0;
         virtual void SetLogicalExt(LONG lx,LONG ly) = 0;
         virtual SIZE GetLogicalExt() const = 0;
         virtual SIZE GetAdjustedLogicalExt() const = 0;
         virtual WBFL::Geometry::Size2d GetAdjustedWorldExt() const = 0;

         virtual void SetMappingMode(MapMode mm) = 0;
         virtual MapMode GetMappingMode() = 0;

         virtual void SetRotation(Float64 cx,Float64 cy,Float64 angle) = 0;
         virtual void SetRotation(const WBFL::Geometry::Point2d& c,Float64 angle) = 0;
         virtual std::pair<WBFL::Geometry::Point2d,Float64> GetRotation() const = 0;
      };
   };
};
