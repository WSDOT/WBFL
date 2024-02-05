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

namespace WBFL
{
   namespace DManip
   {

      /// @brief Indicates how a display object can be selected
      enum class SelectionType
      {
         None,  ///< cannot be selected
         NotUI, ///< cannot be selected via the user interface (but can be selected through code)
         All    ///< can be selected by any means
      };

      /// @brief Defines the access key type for display lists, display objects, etc.
      enum class AccessType
      {
         ByID,
         ByIndex
      };

      /// @brief Defines mapping modes for scaling views
      enum class MapMode 
      {
         Isotropic, ///< X and Y axes have the same scale
         Anisotropic  ///< The scale of the X and Y axes can be different
      };

      /// @brief Defines a mapping mode modifier
      enum class MapModeModifier 
      {
         NoFit,   ///< No adjustments
         BestFitX,  ///< Adjusts scale so the size is maximized in the X-direction
         BestFitY,  ///< Adjusts scale so the size is maximized in the Y-direction
         BestFitXY  ///< Adjusts scale so the size is maximized in the X or Y direction, whichever gives the best fit
      };

      /// @brief Defines the arrow head style for dimension lines
      enum class ArrowHeadStyleType
      {
         Lines, ///< Arrow heads are lines
         Open, ///< Arrow head is non-filled triangle
         Filled  ///< Arrow head is filled triangle
      };

      /// @brief Defines line styles
      enum class LineStyleType
      {
         Null, Solid, Dot, Dash, Centerline
      };

      /// @brief Defines how a point is drawing
      enum class PointType
      {
         None,   ///< Nothing drawing at the vertices
         Circle, ///< An open circle is drawn at the vertices
         Dot,    ///< A solid dot is drawn at the vertices
         Square,
         CrossHair
         // Triangle
         // Pentagon
         // Hexagon
         // Star???
      };
   };
};
