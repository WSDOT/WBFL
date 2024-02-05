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
#include <DManip/Tool.h>
#include <DManip/Draggable.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A tool object implementing the iTool and iToolIcon interfaces.
      /// Also implements the iDraggable interface so that tools can be dragged from
      /// the CToolPalette and dropped on the CDisplayView or onto a display object
      class DMANIPCLASS Tool :
         public iTool,
         public iToolIcon,
         public iDraggable
      {
      private:
         Tool(UINT id) : m_ID(id) {}
      
      public:
         static std::shared_ptr<Tool> Create(UINT id = -1) { return std::shared_ptr<Tool>(new Tool(id)); }
         virtual ~Tool();
   
         // iTool Implementation
         virtual void SetID(UINT id) override;
         virtual UINT GetID() const override;
         virtual void SetToolTipText(LPCTSTR lpszText) override;
         virtual std::_tstring GetToolTipText() const override;

         // iToolIcon interface
         virtual HRESULT SetIcon(HINSTANCE hInstance, WORD IconResId) override;

         // iDraggable Implementation
         virtual void SetDragData(std::shared_ptr<iDragData> dd) override;
         virtual std::shared_ptr<iDragData> GetDragData() override;
         virtual UINT Format() override;
         virtual void PrepareDrag(std::shared_ptr<iDragDataSink> pSink) override;
         virtual void OnDrop(std::shared_ptr<iDragDataSource> pSource) override;
         virtual void OnDragMoved(const WBFL::Geometry::Size2d& offset) override;
         virtual void OnMoved() override;
         virtual void OnCopied() override;
         virtual void DrawDragImage(CDC* pDC, std::shared_ptr<const iCoordinateMap> map, const POINT& dragStart, const POINT& dragPoint) override;

         static CLIPFORMAT ms_cfFormat;

      private:
         UINT m_ID = -1; // This is the ID of the associated control on the tool palette
         std::_tstring m_strToolTipText = _T("");
         std::shared_ptr<iDragData> m_pDragData;

         HINSTANCE m_hIconInstance = 0;
         WORD      m_IconResId = 0;
         HICON     m_Icon = 0;
         CDC       m_MemDC; // memory dc and bitmap for animation
         CBitmap   m_Bitmap;
         bool      m_First = true;
         CPoint    m_OldPoint;
         bool      m_bDrawIcon = true;

         void LoadIcon();
      };
   };
};
