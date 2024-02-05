///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Tools
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
#include <DManip/DisplayObjectDefaultImpl.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief Interface defining a polyline display object. 
      /// This is a display object composted of a collection of points
      class iPolyLineDisplayObject : public DisplayObjectDefaultImpl
      {
      public:
         using DisplayObjectDefaultImpl::DisplayObjectDefaultImpl;

         virtual void SetPoints(const std::vector<WBFL::Geometry::Point2d>& points) = 0;
         virtual void AddPoints(const std::vector<WBFL::Geometry::Point2d>& points) = 0;
         virtual void AddPoint(const WBFL::Geometry::Point2d& point) = 0;
         virtual void InsertPoint(IndexType idx, const WBFL::Geometry::Point2d& point) = 0;
         virtual const WBFL::Geometry::Point2d& GetPoint(IndexType idx) const = 0;
         virtual void RemovePoint(IndexType idx) = 0;
         virtual IndexType GetPointCout() const = 0;
         virtual void ClearPoints() = 0;
         virtual void SetColor(COLORREF color) = 0;
         virtual COLORREF GetColor() const = 0;
         virtual void SetWidth(unsigned width) = 0;
         virtual unsigned GetWidth() const = 0;
         virtual void SetPointType(PointType ptType) = 0;
         virtual PointType GetPointType() const = 0;
         virtual void SetPointSize(UINT size) = 0;
         virtual UINT GetPointSize() const = 0;
      };
   };
};
