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
#pragma once

#include <CoordGeom/CoordGeomExp.h>
#include <CoordGeom/DiaphragmLineFactory.h>
#include <CoordGeom/Direction.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief Creates a diaphragm line through a point.
      /// @image html ThroughPointDiaphragmLineFactory.png
      /// In the example shown above, a diaphragm line is defined by a point and the direction of the line. Two individual diaphragms are created by specifying
      /// a subset of the girder lines. The individual diaphragms can be along the line or staggered.
      class COORDGEOMCLASS ThroughPointDiaphragmLineFactory : public DiaphragmLineFactory
      {
      public:
         ThroughPointDiaphragmLineFactory() = default;
         ThroughPointDiaphragmLineFactory(const ThroughPointDiaphragmLineFactory&) = default;
         ~ThroughPointDiaphragmLineFactory() = default;
         ThroughPointDiaphragmLineFactory& operator=(const ThroughPointDiaphragmLineFactory&) = default;

         /// @brief The point through which the diaphragm line passes
         /// @param point 
         void SetPoint(const WBFL::Geometry::Point2d& point);
         const WBFL::Geometry::Point2d& GetPoint() const;

         /// @brief The direction of the diaphragm line
         /// @param direction 
         void SetDirection(const Direction& direction);
         const Direction& GetDireciton() const;

         /// @brief The diaphragm line identifier
         /// @param id 
         void SetDiaphragmLineID(IDType id);
         IDType GetDiaphragmLineID() const;

         /// @brief If true, the diaphragms lines are staggered, otherwise they are in a continuous line
         /// @param bIsStaggered 
         void IsStaggered(bool bIsStaggered);
         bool IsStaggered() const;

         /// @brief The identifiers of the girder lines between which the diaphragm line extends
         /// @param side 
         /// @param id 
         void SetGirderLineID(SideType side, IDType id);
         IDType GetGirderLineID(SideType side) const;

         virtual std::vector<std::shared_ptr<DiaphragmLine>> Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const override;

#if defined _UNITTEST
         /// A self-test function - returns true if passed.
         static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST


      private:
         IDType m_ID = INVALID_ID;
         WBFL::Geometry::Point2d m_Point;
         Direction m_Direction;
         bool m_bIsStaggered;
         std::array<IDType, 2> m_GirderLineID;
      };
   };
};
