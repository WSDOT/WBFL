///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
// Copyright © 1999-2017  Washington State Department of Transportation
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

#if !defined INCLUDED_GRAPHICSLIB_AXISXY_H_
#define INCLUDED_GRAPHICSLIB_AXISXY_H_
#pragma once

// :COCOON: rdp 09.15.1997 : Cocoon limitations
// :FILE:   AxisXY.h
//
// All preprocessor stuff must go up here because of limitations in
// Cocoon.

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GraphicsLib\GraphicsLibExp.h>
#include <System\NumericFormatTool.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   grAxisXY

   A Windows-specific class for creating axis lines for graphs.


DESCRIPTION
   This class may be used to draw a horizontal X or vertical Y axis with 
   tic marks, value labels and an axis label on the screen. This is a 
   moderately simple axis class that was designed for graphing floating 
   point numbers onto a rectangular graph.

   Although the axis can be either drawn horizontally or vertically, there
   is a local coordinate system (measured in Windows Logical Coord's) that
   follows the axis. The system is as follows:

                       Ay
                       ^
                       |      

                       |--------|--------|--------|-------|  ---->Ax



   EXAMPLE
      Place examples here.
   END

BUGS
   There are currently no known problems with this class.

LOG
   rdp : 09.15.1997 : Created file
*****************************************************************************/

class GRCLASS grAxisXY
{
public:

   //------------------------------------------------------------------------
   // enum to specify location of tic marks. Either above the axis,
   // centered on the axis or below the axis.
   enum TicLocation {TIC_ABOVE, TIC_CENTER, TIC_BELOW};

   //------------------------------------------------------------------------
   // enum to specify location of axis text. Either above or below the axis,
   // If axis is oriented in the Y direction, then below means right and
   // above means to the left.
   enum TextLocation {TEXT_ABOVE, TEXT_BELOW};

   //------------------------------------------------------------------------
   // Axis orientation either horizontal (X) or vertical (Y)
   enum AxisOrientation {X_AXIS, Y_AXIS};

   enum AxisScale { LINEAR, LOGARITHMIC, INTEGRAL };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor - creates X or Y axis axis
   grAxisXY(AxisOrientation orientation, sysNumericFormatTool& rFormat);

   //------------------------------------------------------------------------
   // Constructor - defines location in windows logical coord's
   grAxisXY(AxisOrientation orientation, Int32 AxMin, Int32 AxMax, Int32 AyValue,
            sysNumericFormatTool& rFormat);

   //------------------------------------------------------------------------
   // Copy constructor
   grAxisXY(const grAxisXY& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~grAxisXY();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   //
   // Returns reference to itself
   grAxisXY& operator = (const grAxisXY& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Set Axis orientation.
   // AxMin and AxMax define the starting and ending locations along the length
   // of the axis in Windows device coord's. AyMax defines off axis location.
   // This means that for the X_AXIS orientation, AxMin and AxMax will be in
   // the logical X direction, and for the Y_AXIS direction, AxMax and AxMin
   // will be in the logical Y direction.
   void SetOrientation(AxisOrientation orientation, Int32 AxMin, Int32 AxMax,
                       Int32 AyValue);

   //------------------------------------------------------------------------
   // draw the axis onto the given device context
   void Draw(HDC hDC);

   //------------------------------------------------------------------------
   // Set the desired axis range in 'world' coordinates along the length of 
   // the axis. This range will be transformed into 'nice' numbers which
   // can be retrieved via the GetAxisRange function
   void SetNiceAxisRange(Float64 leftVal, Float64 rightVal,bool bOffsetZero);

   //------------------------------------------------------------------------
   // This function allows you to 'force' the axis range and major tic
   // increment instead of letting the axis pick nice numbers for you.
   void SetForcedAxisRange(Float64 leftVal, Float64 rightVal, Float64 increment);

   //------------------------------------------------------------------------
   // Get the current axis range and major tic increment.
   void GetAxisRange(Float64& leftVal, Float64& rightVal, Float64& increment) const;


   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Set Axis font size axis title
   void SetTitleFontSize(Int32 FontSize);

   //------------------------------------------------------------------------
   // Get Axis font size for axis title
   Int32 GetTitleFontSize() const;

   //------------------------------------------------------------------------
   // Set Axis font size for axis subtitle
   void SetSubtitleFontSize(Int32 FontSize);

   //------------------------------------------------------------------------
   // Get Axis font size for axis subtitle
   Int32 GetSubtitleFontSize() const;

   //------------------------------------------------------------------------
   // Set Axis font size for axis values
   void SetValueFontSize(Int32 FontSize);

   //------------------------------------------------------------------------
   // Get Axis font size for axis values
   Int32 GetValueFontSize() const;

   void SetValueAngle(LONG angle);
   LONG GetValueAngle() const;

   //------------------------------------------------------------------------
   // Set numeric formatting. This class does not own the tool, it only borrows
   // it and will not destroy the memory
   void SetValueFormat(sysNumericFormatTool& format);

   //------------------------------------------------------------------------
   // Get numeric formatting
   const sysNumericFormatTool* GetValueFormat() const;

   //------------------------------------------------------------------------
   // Set the location of the tic marks along the axis. Tic marks can either
   // be BELOW, ABOVE, or CENTERed on the axis. For axis' oriented in the Y
   // direction, this means right, left, or centered, respectively.
   void SetTicLocation(grAxisXY::TicLocation location);

   //------------------------------------------------------------------------
   // Get the current tic location
   grAxisXY::TicLocation GetTicLocation() const;

   //------------------------------------------------------------------------
   // Set the location of the Text wrt the axis. Text can either
   // be BELOW or ABOVE the axis. For axis' oriented in the Y
   // direction, this means right or left, respectively.
   void SetTextLocation(grAxisXY::TextLocation location);

   //------------------------------------------------------------------------
   // Get the current Text location
   grAxisXY::TextLocation GetTextLocation() const;

   //------------------------------------------------------------------------
   // Set the desired number of major tic spaces along the axis. Note that this 
   // value is only a suggestion to the 'nice' number generator.
   // values less than one will be interpreted as one.
   void SetNumberOfMajorTics(Int32 numTics);

   //------------------------------------------------------------------------
   Int32 GetNumberOfMajorTics() const;

   //------------------------------------------------------------------------
   // Set the desired number of minor tic spaces between major tics. Values
   // less than two will be interpreted as zero.
   void SetNumberOfMinorTics(Int32 numTics);

   //------------------------------------------------------------------------
   Int32 GetNumberOfMinorTics() const;

   //------------------------------------------------------------------------
   // Set whether to show tic marks or not
   void SetShowTics(bool doShow);

   //------------------------------------------------------------------------
   // Get whether to show tic marks or not
   bool GetShowTics() const;

   //------------------------------------------------------------------------
   // Set the title text
   void SetTitleText(LPCTSTR text);

   //------------------------------------------------------------------------
   // Get the title text
   LPCTSTR GetTitleText() const;

   //------------------------------------------------------------------------
   // Set the subtitle text
   void SetSubtitleText(LPCTSTR text);

   //------------------------------------------------------------------------
   // Get the subtitle text
   LPCTSTR GetSubtitleText() const;

   //------------------------------------------------------------------------
   // Set whether to show text or not
   void SetShowText(bool doShow);

   //------------------------------------------------------------------------
   // Get whether to show text or not
   bool GetShowText() const;

   void SetScale(grAxisXY::AxisScale scale);
   grAxisXY::AxisScale GetScale() const;

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // get the 'thickness' of the axis in logical coordinates. This includes 
   // the height of the tick marks plus the height of the title and subtitle,
   // including spacing between them.
   Int32 GetThickness(HDC hDC);

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const grAxisXY& rOther);
   virtual void MakeAssignment(const grAxisXY& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

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
   grAxisXY::TicLocation m_TicLocation;
   bool   m_DoShowTics;
   bool   m_DoShowText;
   grAxisXY::TextLocation m_TextLocation;

   grAxisXY::AxisScale m_Scale;

   std::_tstring m_AxisTitle;
   std::_tstring m_AxisSubtitle;

   LONG   m_AxisTitleSize;
   LONG   m_AxisSubtitleSize;
   LONG   m_AxisValueSize;
   sysNumericFormatTool* m_pValueFormat;

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


   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void Init();
   void UpdateAxisMetrics(HDC hDC);
   // GROUP: ACCESS
   // GROUP: INQUIRY
public:
   // GROUP: DEBUG
   #if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns true if the object is in a valid state, otherwise returns false.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the object to the given dump context.
   virtual void Dump(dbgDumpContext& os) const;
   #endif // _DEBUG

   #if defined _UNITTEST
   //------------------------------------------------------------------------
   // Runs a self-diagnostic test.  Returns true if the test passed,
   // otherwise false.
   static bool TestMe(dbgLog& rlog);
   #endif // _UNITTEST
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_GRAPHICSLIB_AXISXY_H_

