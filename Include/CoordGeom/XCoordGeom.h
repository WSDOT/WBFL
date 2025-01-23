///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <System/Exception.h>

#define THROW_COGO(reason) throw WBFL::COGO::XCoordGeom(reason,_T(__FILE__),__LINE__)

namespace WBFL
{
   namespace COGO
   {
      constexpr Int32 WBFL_COGO_E_POINTNOTFOUND = 1;
      constexpr Int32 WBFL_COGO_E_DIRECTIONSTRING = 2;
      constexpr Int32 WBFL_COGO_E_DIRECTION = 3;
      constexpr Int32 WBFL_COGO_E_AZIMUTH = 4;
      constexpr Int32 WBFL_COGO_E_ANGLESTRING = 5;
      constexpr Int32 WBFL_COGO_E_ANGLE = 6;
      constexpr Int32 WBFL_COGO_E_STATION = 7;
      constexpr Int32 WBFL_COGO_E_INVALIDINDEX = 8;
      constexpr Int32 WBFL_COGO_E_POINTPROJECTION = 9;
      constexpr Int32 WBFL_COGO_E_INVALIDARG = 10;
      constexpr Int32 WBFL_COGO_E_CUBICSPLINEPOINTS = 11;
      constexpr Int32 WBFL_COGO_E_SPIRALSOVERLAP = 12;
      constexpr Int32 WBFL_COGO_E_SUPERTRANSITIONERROR = 14;
      constexpr Int32 WBFL_COGO_E_STATIONEQUATIONBACK = 15;
      constexpr Int32 WBFL_COGO_E_STATIONEQUATIONAHEAD = 16;
      constexpr Int32 WBFL_COGO_E_STATIONRANGEERROR = 17;
      constexpr Int32 WBFL_COGO_E_VERTCURVEPOINTS = 18;
      constexpr Int32 WBFL_COGO_E_SURFACESLOPEMISMATCHERROR = 19;
      constexpr Int32 WBFL_COGO_E_NOINTERSECTION = 20;
      constexpr Int32 WBFL_COGO_E_COINCIDENTPOINTS = 21;
      constexpr Int32 WBFL_COGO_E_POINTINCIRCLE = 22;

      /// @brief Coordinate geometry modeling exception
      class COORDGEOMCLASS XCoordGeom : public WBFL::System::XBase
      {
      public:
         XCoordGeom() = delete;
         XCoordGeom(Int32 reason, const std::_tstring& file, Uint32 line);
         virtual ~XCoordGeom() = default;

         XCoordGeom& operator=(const XCoordGeom&) = default;

         virtual void Throw() const override;
         virtual Int32 GetReason() const noexcept override;

      private:
         Int32 m_Reason;
      };
   }; // COGO
}; // WBFL
