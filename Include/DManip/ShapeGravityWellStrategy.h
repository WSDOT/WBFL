///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#include <DManip/DManipExp.h>
#include <DManip/GravityWellStrategy.h>

#include <GeomModel/Shape.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief Uses a shape to define the boundaries of a gravity well
      class DMANIPCLASS ShapeGravityWellStrategy : public iGravityWellStrategy
      {
      protected:
         ShapeGravityWellStrategy(std::shared_ptr<WBFL::Geometry::Shape> shape);

      public:
         static std::shared_ptr<ShapeGravityWellStrategy> Create(std::shared_ptr<WBFL::Geometry::Shape> shape=nullptr) { return std::shared_ptr<ShapeGravityWellStrategy>(new ShapeGravityWellStrategy(shape)); }
	      virtual ~ShapeGravityWellStrategy() = default;

         void SetShape(std::shared_ptr<WBFL::Geometry::Shape> shape);
         std::shared_ptr<WBFL::Geometry::Shape> GetShape();
         std::shared_ptr<const WBFL::Geometry::Shape> GetShape() const;

         // iGravityWellStrategy Implementation
         virtual void GetGravityWell(std::shared_ptr<const iDisplayObject> pDO, CRgn* pRgn) override;

      private:
         std::shared_ptr<WBFL::Geometry::Shape> m_Shape;
         std::shared_ptr<WBFL::Geometry::CompositeShape> m_CompositeShape;
      };
   };
};
