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
#include <vector>
#include <DManip/Mapping.h>
#include <DManip/CoordinateMap.h>
#include <DManip/DManipTypes.h>

#include <Math/CoordMapper1d.h>

class CDisplayView;

namespace WBFL
{
   namespace DManip
   {
      /// @brief Object that provides coordinate mapping
      class DMANIPCLASS Mapping :
         public iMapping,
         public iCoordinateMap
      {
      public:
	      Mapping();
	      virtual ~Mapping();

         // iMapping Implementation
         virtual void PrepareDC(CDC* dc) override;
         virtual void CleanUpDC(CDC* dc) override;
         virtual void CleanUpPrintDC(CDC* dc) override;
         virtual void SetWorldExt(Float64 wx, Float64 wy) override;
         virtual void SetWorldExt(const WBFL::Geometry::Size2d& wExt) override;
         virtual const WBFL::Geometry::Size2d& GetWorldExt() const override;
         virtual void SetWorldOrg(Float64 wx, Float64 wy) override;
         virtual void SetWorldOrg(const WBFL::Geometry::Point2d& wOrg) override;
         virtual const WBFL::Geometry::Point2d& GetWorldOrg() const override;
         virtual void SetLogicalOrg(const POINT& org) override;
         virtual void SetLogicalOrg(LONG lx, LONG ly) override;
         virtual POINT GetLogicalOrg() const override;
         virtual void SetLogicalExt(LONG lx, LONG ly) override;
         virtual SIZE GetLogicalExt() const override;
         virtual SIZE GetAdjustedLogicalExt() const override;
         virtual WBFL::Geometry::Size2d GetAdjustedWorldExt() const override;
         virtual void SetMappingMode(MapMode mm) override;
         virtual MapMode GetMappingMode() override;
         virtual void SetRotation(Float64 cx, Float64 cy, Float64 angle) override;
         virtual void SetRotation(const WBFL::Geometry::Point2d& c, Float64 angle) override;
         virtual std::pair<WBFL::Geometry::Point2d, Float64> GetRotation() const override;

         // iCoordinateMap Implementation
         virtual void MPtoWP(Float64 mx,Float64 my,Float64* wx,Float64* wy) const override;
         virtual WBFL::Geometry::Point2d MPtoWP(const WBFL::Geometry::Point2d& mp) const override;
         virtual void WPtoMP(Float64 wx,Float64 wy,Float64* mx,Float64* my) const override;
         virtual void WPtoMP(const WBFL::Geometry::Point2d& wp,Float64* mx,Float64* my) const override;
         virtual void WPtoLP(Float64 wx,Float64 wy,LONG* lx,LONG* ly) const override;
         virtual void WPtoLP(const WBFL::Geometry::Point2d& wp,LONG* lx,LONG* ly) const override;
         virtual void LPtoWP(LONG lx,LONG ly,Float64* wx,Float64* wy) const override;
         virtual WBFL::Geometry::Point2d LPtoWP(LONG lx,LONG ly) const override;
         virtual void WPtoTP(Float64 wx,Float64 wy,LONG* tx,LONG* ty) const override;
         virtual void TPtoWP(LONG tx,LONG ty,Float64* wx,Float64* wy) const override;
         virtual void LPtoTP(LONG lx,LONG ly,LONG* tx,LONG* ty) const override;
         virtual void TPtoLP(LONG tx,LONG ty,LONG* lx,LONG* ly) const override;
         virtual CSize GetTextWindowExtent() const override;
         virtual CSize GetTextExtent(const CDisplayView* pView,const LOGFONT& font, LPCTSTR lpszText) const override;

      private:
         WBFL::Geometry::Size2d m_WorldExtent;
         WBFL::Geometry::Point2d m_WorldOrigin;
         LONG   m_LogicalExtentX;
         LONG   m_LogicalExtentY;
         LONG   m_OriginalLogicalExtentX;
         LONG   m_OriginalLogicalExtentY;
         LONG   m_LogicalOriginX;
         LONG   m_LogicalOriginY;

         // do these divisions once and store the result
         // otherwise they would have to happen thousands for times
         // for every point that gets mapped
         void UpdateMappingScale();
         Float64 m_WEX_over_LEX; // m_WorldExtentX/m_LogicalExtentX
         Float64 m_WEY_over_LEY; // m_WorldExtentY/m_LogicalExtentY
         Float64 m_LEX_over_WEX; // m_LogicalExtentX/m_WorldExtentX
         Float64 m_LEY_over_WEY; // m_LogicalExtentY/m_WorldExtentY

         Float64 m_Rotation; // rotation angle;
         Float64 m_RotationX; 
         Float64 m_RotationY; // center of rotation
         Float64 m_cosR; // cosine of the rotation angle
         Float64 m_sinR; // sine of the rotation angle

         MapMode         m_MappingMode;

         // use a stack to hold the current DC and any other DC's that 
         // are out there in time. Mapping information for each DC must also be stored
         struct StackFrame
         {
            // coordinate mapper from text space to logical space
            // A coordinate is text, B coordinate is logical
            WBFL::Math::CoordMapper1d m_TextCoordMapperX;
            WBFL::Math::CoordMapper1d m_TextCoordMapperY;

            // local dc so we can determine font metrics
            CDC*  m_pDC;
         };

         std::vector<StackFrame> m_Stack;

         void UpdateLogicalExtents();
      };
   };
};
