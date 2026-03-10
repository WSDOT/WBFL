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

namespace WBFL
{
   namespace Geometry
   {
      class Point2d;
   };

   namespace DManip
   {
      class iDisplayObject;

      /// @brief Interface implemented by DropSite objects. 
      /// Client applications implement drop site objects and associate them with display objects that can have other display objects dropped on then.
      class DMANIPCLASS iDropSite
      {
      public:
         /// @brief Called by the framework when a display object is dragged over another. 
         /// The drop site indicates whether the display objects can be dropped by returning a drop effect
         virtual DROPEFFECT CanDrop(COleDataObject* pDataObject,DWORD dwKeyState,const WBFL::Geometry::Point2d& point) = 0;

         /// @brief Called by the framework when display objects are dropped on the drop site.
         virtual void OnDropped(COleDataObject* pDataObject,DROPEFFECT dropEffect, const WBFL::Geometry::Point2d& point) = 0;

         /// @brief Associated a display object with this drop site
         virtual void SetDisplayObject(std::weak_ptr<iDisplayObject> pDO) = 0;
         virtual std::shared_ptr<iDisplayObject> GetDisplayObject() = 0;

         /// @brief Call by the framework when the drop site needs to be highlighted
         virtual void Highlight(CDC* pDC,BOOL bHighlight) = 0;
      };
   };
};
