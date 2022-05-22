///////////////////////////////////////////////////////////////////////
// Graphing - Line graph plotting and graph definition management library
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <System\NumericFormatTool.h>

namespace WBFL
{
   namespace Graphing
   {

/// A Windows-specific class for creating axis lines for graphs.
///
/// This class may be used to draw a horizontal X or vertical Y axis with 
/// tic marks, value labels and an axis label on the screen. This is a 
/// moderately simple axis class that was designed for graphing floating 
/// point numbers onto a rectangular graph.
/// 
/// Although the axis can be either drawn horizontally or vertically, there
/// is a local coordinate system (measured in Windows Logical Coord's) that
/// follows the axis. The system is as follows:
/// 
///                     Ay
///                     ^
///                     |      
///                     |      
///                     |--------|--------|--------|-------|----> Ax
/// 
class GRAPHINGCLASS AxisXY
{
public:

   /// Location of tic marks relative to the axis.
   /// If axis is oriented in the Y direction, then Below means right and Above means to the left.
   enum class TicLocation {Above, Center, Below};

   /// Location of text realtive to the axis. 
   /// If axis is oriented in the Y direction, then Below means right and Above means to the left.
   enum class TextLocation {Above, Below};

   /// Axis orientation either horizontal (X) or vertical (Y)
   enum class AxisOrientation {X, Y};

   /// Axis scale type
   enum class AxisScale { Linear, Logarithmic, Integral };

   AxisXY(AxisOrientation orientation, WBFL::System::NumericFormatTool& rFormat);
   AxisXY(AxisOrientation orientation, Int32 AxMin, Int32 AxMax, Int32 AyValue, WBFL::System::NumericFormatTool& rFormat);
   AxisXY(const AxisXY& rOther) = default;

   ~AxisXY();

   AxisXY& operator=(const AxisXY& rOther) = default;

   /// Sets the axis orientation.
   /// AxMin and AxMax define the starting and ending locations along the length
   /// of the axis in Windows device coord's. AyMax defines off axis location.
   /// This means that for the X_AXIS orientation, AxMin and AxMax will be in
   /// the logical X direction, and for the Y_AXIS direction, AxMax and AxMin
   /// will be in the logical Y direction.
   void SetOrientation(AxisOrientation orientation, Int32 AxMin, Int32 AxMax, Int32 AyValue);

   /// Draws the axis onto the given device context
   void Draw(HDC hDC);

   /// Sets the desired axis range in 'world' coordinates along the length of 
   /// the axis. This range will be transformed into 'nice' numbers which
   /// can be retrieved via the GetAxisRange function
   void SetNiceAxisRange(Float64 leftVal, Float64 rightVal,bool bOffsetZero);

   /// This function allows you to 'force' the axis range and major tic
   /// increment instead of letting the axis pick nice numbers for you.
   void SetForcedAxisRange(Float64 leftVal, Float64 rightVal, Float64 increment);

   /// Get the current axis range and major tic increment.
   void GetAxisRange(Float64* pLeftVal, Float64* pRightVal, Float64* pIncrement) const;


   /// Sets font size for the axis title
   void SetTitleFontSize(Int32 FontSize);

   /// Returns the font size for the axis title
   Int32 GetTitleFontSize() const;

   /// Sets font size for the axis subtitle
   void SetSubtitleFontSize(Int32 FontSize);

   /// Returns font size for the axis subtitle
   Int32 GetSubtitleFontSize() const;

   /// Set the font size for axis values
   void SetValueFontSize(Int32 FontSize);

   /// Returns the font size for axis values
   Int32 GetValueFontSize() const;

   /// Sets the inclination angle of the axis value text. Angle is in 10ths of a degree (input 900 for 90 degrees)
   void SetValueAngle(LONG angle);

   /// Returns the inclination angle of the axis value text.
   LONG GetValueAngle() const;

   /// Sets the numeric formatting
   void SetValueFormat(WBFL::System::NumericFormatTool& format);

   /// Returns the numeric formatting
   const WBFL::System::NumericFormatTool* GetValueFormat() const;

   /// Set the location of the tic marks along the axis
   void SetTicLocation(AxisXY::TicLocation location);

   /// Returns the tic location
   AxisXY::TicLocation GetTicLocation() const;

   /// Sets the location of the Text wrt the axis.
   void SetTextLocation(AxisXY::TextLocation location);

   /// Returns the current Text location
   AxisXY::TextLocation GetTextLocation() const;

   /// Sets the desired number of major tic spaces along the axis. Note that this 
   /// value is only a suggestion to the 'nice' number generator.
   void SetNumberOfMajorTics(Int32 numTics);

   /// Returns the number of major tic spaces along the axis
   Int32 GetNumberOfMajorTics() const;

   // Sets the desired number of minor tic spaces between major tics. Values
   /// less than two will be interpreted as zero.
   void SetNumberOfMinorTics(Int32 numTics);

   /// Returns the number of minor tics
   Int32 GetNumberOfMinorTics() const;

   /// Set whether to show tic marks or not
   void SetShowTics(bool doShow);

   /// Returns true if tic marks are to be show
   bool GetShowTics() const;

   /// Set the title text
   void SetTitleText(LPCTSTR text);
   
   /// Get the title text
   LPCTSTR GetTitleText() const;

   /// Set the subtitle text
   void SetSubtitleText(LPCTSTR text);

   /// Get the subtitle text
   LPCTSTR GetSubtitleText() const;

   /// Set whether to show text or not
   void SetShowText(bool doShow);

   /// Returns true if tex is shown
   bool GetShowText() const;

   /// Sets the axis scale
   void SetScale(AxisXY::AxisScale scale);

   /// Returns the axis scale
   AxisXY::AxisScale GetScale() const;

   /// Returns the 'thickness' of the axis in logical coordinates. This includes 
   /// the height of the tic marks plus the height of the title and subtitle,
   /// including spacing between them.
   Int32 GetThickness(HDC hDC);

private:
   AxisOrientation m_Orientation;
   Int32             m_MinLocation;
   Int32             m_MaxLocation;
   Int32             m_YLocation;

   LONG m_ValueAngle; // angle of text
   Float64 m_LeftAxisValue;
   Float64 m_RightAxisValue;
   Float64 m_AxisIncrement;
   LONG    m_NumberOfMajorTics;
   LONG    m_NumberOfMinorTics;
   AxisXY::TicLocation m_TicLocation;
   bool   m_DoShowTics;
   bool   m_DoShowText;
   AxisXY::TextLocation m_TextLocation;

   AxisXY::AxisScale m_Scale;

   std::_tstring m_AxisTitle;
   std::_tstring m_AxisSubtitle;

   LONG   m_AxisTitleSize;
   LONG   m_AxisSubtitleSize;
   LONG   m_AxisValueSize;
   WBFL::System::NumericFormatTool* m_pValueFormat;

   // struct to hold private axis metrics

   bool   m_MetricsDirtyFlag;
   struct AxisMetrics 
   {
      LONG   TicSize;
      LONG   MajorTicBottom;
      LONG   MajorTicTop;
      LONG   MinorTicBottom;
      LONG   MinorTicTop;
      LONG   ValueTextLoc;
      LONG   TitleTextLoc;
      LONG   SubtitleTextLoc;
      LONG   UpperLimit;
      LONG   LowerLimit;
      AxisMetrics();
      ~AxisMetrics();

   } m_AxisMetrics;


   void Init();
   void UpdateAxisMetrics(HDC hDC);

#if defined _DEBUG
   bool AssertValid() const;
   void Dump(WBFL::Debug::LogContext& os) const;
#endif // _DEBUG

#if defined _UNITTEST
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST
};


   }; // Graphing
}; // WBFL

