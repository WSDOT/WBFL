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
#include <CoordGeom/Station.h>

namespace WBFL
{
   namespace COGO
   {
      /// @brief A factory that creates a single diaphragm line. Note that multiple diaphragms can be defined along the single diaphragm line.
      /// @image html SingleDiaphragmLineFactory.png
      /// In the image above, a series of three diaphragms are created using the single diaphragm line that pass through the station at the specified orientation. 
      /// The diaphragm lines can also be staggered.
      class COORDGEOMCLASS SingleDiaphragmLineFactory : public DiaphragmLineFactory
      {
      public:
         SingleDiaphragmLineFactory() = default;
         SingleDiaphragmLineFactory(const SingleDiaphragmLineFactory&) = default;
         ~SingleDiaphragmLineFactory() = default;
         SingleDiaphragmLineFactory& operator=(const SingleDiaphragmLineFactory&) = default;

         /// @brief The alignment identifier for the station where the diaphragm line is created
         /// @param alignmentID 
         void SetAlignmentID(IDType alignmentID);
         IDType GetAlignmentID() const;

         /// @brief The station where the diaphragm line is created
         /// @param station 
         void SetStation(const Station& station);
         const Station& GetStation() const;

         /// @brief The orientation of the diaphragm line
         /// @param strOrientation 
         void SetOrientation(const std::_tstring& strOrientation);
         const std::_tstring& GetOrientation() const;

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
         IDType m_AlignmentID = INVALID_ID;
         Station m_Station;
         std::_tstring m_strOrientation;
         bool m_bIsStaggered;
         std::array<IDType, 2> m_GirderLineID;
      };
   };
};
