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
#include <DManip/DisplayObjectDefaultImpl.h>
#include <DManip/TextBlock.h>
#include <DManip/DManipTypes.h>
#include <DManip/ConnectorImpl.h>
#include <DManip/NestedDisplayObjectEventRelay.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief A display object that represents dimension lines on an engineering drawing
      /// All lengths, such as witness length, are in twips (1/1440 inches)
      class DMANIPCLASS DimensionLine :
         public DisplayObjectDefaultImpl,
         public Connector<DisplayObjectDefaultImpl>
      {
      protected:
         DimensionLine(IDType id);

      private:
         void Init();

      public:
         static std::shared_ptr<DimensionLine> Create(IDType id = INVALID_ID);
         virtual ~DimensionLine();

         /// @brief Angle of the dimension line, measured from horizontal
         /// @param angle 
         void SetAngle(Float64 angle);
         Float64 GetAngle() const;

         /// @brief Sets the length of the witness line
         /// @param l 
         void SetWitnessLength(LONG l);
         LONG GetWitnessLength() const;

         /// @brief Sets an additional length to be added to the witness line, but this length is not drawn
         /// @param l 
         void SetHiddenWitnessLength(LONG l);
         LONG GetHiddenWitnessLength() const;

         /// @brief Sets the witness line offset. The witness line offset is the distance from the connector point to the start of the witness line.
         /// @param wOffset 
         void SetWitnessOffset(LONG wOffset);
         LONG GetWitnessOffset() const;

         /// @brief Set the size of the arrow heads
         /// @param size cx is width, cy is length
         void SetArrowHeadSize(CSize size);
         CSize GetArrowHeadSize() const;

         /// @brief Sets the arrow head style
         /// @param style 
         void SetArrowHeadStyle(ArrowHeadStyleType style);
         ArrowHeadStyleType GetArrowHeadStyle() const;

         /// @brief Sets autotext model. When enabled, the dimension line text is automatically updated as the end points of the dimension line move.
         /// @param bEnable 
         void EnableAutoText(bool bEnable);
         bool IsAutoTextEnabled() const;

         /// @brief Sets the text block object used to display the dimension line text.
         /// @param pTextBlock 
         void SetTextBlock(std::shared_ptr<iTextBlock> pTextBlock);
         std::shared_ptr<iTextBlock> GetTextBlock();
         std::shared_ptr<const iTextBlock> GetTextBlock() const;


         // iDisplayObject Implementation
         virtual void SetDisplayList(std::weak_ptr<iDisplayList> pDL) override;
         virtual void Draw(CDC* pDC) override;
         virtual void Highlight(CDC* pDC,bool bHighlight) override;

         // Size and Hit Testing
         virtual bool HitTest(const POINT& point) const override;
         virtual WBFL::Geometry::Rect2d GetBoundingBox() const override; 

         // Tool Tips
         virtual std::_tstring GetToolTipText() const override;
         virtual void SetMaxTipWidth(INT maxWidth) override;
         virtual INT GetMaxTipWidth() const override;
         virtual void SetTipDisplayTime(INT iTime) override;
         virtual INT GetTipDisplayTime() const override;

         virtual bool OnLButtonDown(UINT nFlags, const POINT& point) override;
         virtual bool OnLButtonUp(UINT nFlags, const POINT& point) override;
         virtual bool OnLButtonDblClk(UINT nFlags, const POINT& point) override;
         virtual bool OnRButtonDown(UINT nFlags, const POINT& point) override;
         virtual bool OnRButtonUp(UINT nFlags, const POINT& point) override;
         virtual bool OnRButtonDblClk(UINT nFlags, const POINT& point) override;
         virtual bool OnMouseMove(UINT nFlags, const POINT& point) override;
         virtual bool OnMouseWheel(UINT nFlags, short zDelta, const POINT& point) override;
         virtual bool OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) override;
         virtual bool OnContextMenu(CWnd* pWnd, const POINT& point) override;

      private:
         std::shared_ptr<iTextBlock> m_TextBlock;

         Float64 m_Angle = 0;
         bool m_bAlignWithPlugs = true;
         LONG   m_HiddenWitnessLength = 0;
         LONG   m_LenWitness = (1440*3)/8;
         LONG   m_DimOffset = (1440/16);
         LONG   m_WitnessOffset = (1440/32);
         int   m_ArrowHeight = (1440/16);
         int   m_ArrowWidth = (1440/16);

         struct ARROWHEAD
         {
            CPoint tip,left,right;
         };

         mutable ARROWHEAD m_StartArrow;
         mutable ARROWHEAD m_EndArrow;

         ArrowHeadStyleType m_Style = ArrowHeadStyleType::Filled;

         bool m_bAutoText = false; // If TRUE, the text is equal to the distance between plugs

         // Working points
         mutable CPoint m_ptA, m_ptB, m_ptC, m_ptD, m_ptE, m_ptF, m_ptZ, m_ptStart, m_ptEnd;
         virtual void UpdateWorkPoints() const;
         void UpdateArrowHeads(Float64 stx, Float64 sty) const;
         void UpdateTextBlock() const;
         void IncludePointInRect(CPoint p,CRect* pRect) const;

         WBFL::Geometry::Point2d GetStartPoint() const;
         WBFL::Geometry::Point2d GetEndPoint() const;

         std::shared_ptr<NestedDisplayObjectEventRelay> m_EventRelay;
      };
   };
};
