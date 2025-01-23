///////////////////////////////////////////////////////////////////////
// Graphing - Line graph plotting and graph definition management library
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


#include <Graphing/GraphingExp.h>
#include <Graphing/PointMapper.h>

namespace WBFL
{
   namespace Graphing
   {

/// A class to represent a label which may be drawn on the screen
/// 
/// This class allows you to put a mult-line label at a precise location in
/// world coordinates on the screen. Multi-line labels are created by putting
/// std::endl's (\n's) into the label string.
/// 
/// The point size of the font can be specified, but the font is always arial.
class GRAPHINGCLASS Label
{
public:
   /// Defines the horizontal position of hook point
   enum class HorizontalPosition {Left, Center, Right};

   /// Defines the vertical position of hook point
   enum class VerticalPosition {Top, Middle, Bottom};

   /// Creates a label with the hook point at Center-Middle
   Label();

   Label(const Label& other) = default;

   /// Creates a label specifying the hook point location and label text
   Label(const Point& point, const std::_tstring& label);

   virtual ~Label();

   Label& operator = (const Label& rOther) = default;

   /// Draws the label. Label is drawn left justified using the settings defined by the DC
   virtual void Draw(HDC hDC, const PointMapper& mapper) const;

   /// Sets the Horizontal Position mode as to where the hook
   /// point is located on the bounding box of the label.
   void SetHorizontalPosition(HorizontalPosition pos);

   /// Returns the horizontal position mode
   HorizontalPosition GetHorizontalPosition() const;

   /// Sets the vertical Position mode as to where the hook
   /// point is located on the bounding box of the label.
   void SetVerticalPosition(VerticalPosition pos);

   /// Returns the vertical position mode
   VerticalPosition GetVerticalPosition() const;

   /// Sets the hook point
   void SetHookPoint(const Point& point);

   /// Returns hook point.
   Point GetHookPoint() const;

   /// Sets the hook point and orientation all at once
   void SetLocation(const Point& point, HorizontalPosition hpos, VerticalPosition pos);

   /// Sets the label to be placed on the dimension. std::endl's (\n's) in the string
   /// will start a new line and create a multiline label.
   void SetLabel(const std::_tstring& label);

   /// Returns the label
   std::_tstring GetLabel() const;

   /// Set point size for label
   void SetPointSize(Uint32 siz);

   /// Returns point size for label
   Uint32 GetPointSize() const;

   // Gets bounding box for dimension to be drawn
   virtual Rect GetBoundingBox(HDC hDC, const PointMapper& mapper) const;

   /// Gets the size for dimension to be drawn
   virtual Size GetSize(HDC hDC, const PointMapper& mapper) const;

   /// Gets the number of lines in label
   IndexType GetLineCount() const;

   /// Gets the height of a single ine in the lable in world coordinates
   Float64 GetLineHeight(HDC hDC, const PointMapper& mapper) const;

   /// Gets the height of a single line in the label in device coordinates
   LONG GetLineHeight(HDC hDC) const;

private:
   Point m_HookPoint;
   std::vector<std::_tstring> m_Labels;
   HorizontalPosition            m_HorizPos;
   VerticalPosition             m_VertPos;
   Int32                    m_PointSize;

   void Init();

public:
#if defined _DEBUG
   virtual bool AssertValid() const;
   virtual void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG
};

   }; // Graphing
}; // WBFL

