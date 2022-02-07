///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
// Copyright © 1999-2021  Washington State Department of Transportation
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

#if !defined GraphXY_H_
#define GraphXY_H_
#pragma once

// SYSTEM INCLUDES
//
#include <map>
#include <GraphicsLib\GraphicsLibExp.h>
#include <GraphicsLib\PointMapper.h>
#include <WBFLGeometry.h>
#include <system\INumericFormatToolBase.h>
#include <GraphicsLib\AxisXY.h>

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   grGraphXY

   Simple X-Y Graphing tool.


DESCRIPTION
   Simple X-Y Graphing tool design specifically for use with MFC.

LOG
   rab : 09.03.1997 : Created file
*****************************************************************************/

class GRCLASS grGraphXY
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // constructor
   grGraphXY(sysNumericFormatTool& rXAxisFormat, sysNumericFormatTool& rYAxisFormat);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~grGraphXY();

   //------------------------------------------------------------------------
   // Creates a new data series in the graph.  Returns a cookie used to
   // reference this data series at a later time.
   IndexType CreateDataSeries();
   IndexType CreateDataSeries(LPCTSTR lpszLabel,int nPenStyle, int nWidth, COLORREF crColor);

   // Find an existing data series and return its cookie. Returns INVALID_INDEX if not found
   IndexType FindDataSeries(LPCTSTR lpszLabel);

   //------------------------------------------------------------------------
   // Adds an individual point to the graph.
   void AddPoint(IndexType cookie,const gpPoint2d& rPoint);

   //------------------------------------------------------------------------
   // Adds a collection of points to the graph.
   void AddPoints(IndexType cookie,const std::vector<gpPoint2d>& vPoints);

   //------------------------------------------------------------------------
   // Removes all the points from the graph
   void ClearPoints(IndexType cookie);

   //------------------------------------------------------------------------
   // Clears all data from the graph
   void ClearData();

   //------------------------------------------------------------------------
   // Returns the point of points in the graph
   IndexType GetPointCount(IndexType cookie) const;

   //------------------------------------------------------------------------
   // Removes the data series from the graph.
   void RemoveDataSeries(IndexType cookie);

   //------------------------------------------------------------------------
   // Returns the number of data series from the graph
   IndexType GetDataSeriesCount() const;

   //------------------------------------------------------------------------
   // Returns the output rectangle
   RECT GetOutputRect() const;

   //------------------------------------------------------------------------
   // Sets the device rectangle that the world points will be mapped to.
   // NOTE: This must be called at least once prior to Draw()
   void SetOutputRect(const RECT& rOutputRect);

   //------------------------------------------------------------------------
   // Draws the graph on the given device context.
   // This method calls UpdateGraphMetrics, DrawBackground, and DrawDataSeries
   // You can call these three steps individual if you want to enhance the
   // graph drawing. You MUST call UpdateGraphMetrics before any drawing
   // takes place
   virtual void Draw(HDC hDC);

   //------------------------------------------------------------------------
   // Draw only the background
   virtual void DrawBackground(HDC hDC);

   //------------------------------------------------------------------------
   // Draw only the data series
   virtual void DrawDataSeries(HDC hDC);

   virtual void UpdateGraphMetrics(HDC hDC);

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Return the graph title
   LPCTSTR GetTitle() const;

   //------------------------------------------------------------------------
   // Set the graph title
   void SetTitle(LPCTSTR strTitle);

   //------------------------------------------------------------------------
   // Return the title size in points
   LONG GetTitleSize() const;

   //------------------------------------------------------------------------
   // Set the title size in points
   void SetTitleSize(LONG size);

   //------------------------------------------------------------------------
   // Return the graph subtitle
   LPCTSTR GetSubtitle() const;

   //------------------------------------------------------------------------
   // Set the graph subtitle
   void SetSubtitle(LPCTSTR strSubtitle);

   //------------------------------------------------------------------------
   // Return the Subtitle size in points
   LONG GetSubtitleSize() const;

   //------------------------------------------------------------------------
   // Set the Subtitle size in points
   void SetSubtitleSize(LONG size);

   //------------------------------------------------------------------------
   // set size in points of titles for x and y axis'
   void SetAxisTitleSize(LONG size);

   //------------------------------------------------------------------------
   // set size in points of titles for x and y axis'
   LONG GetAxisTitleSize() const;

   //------------------------------------------------------------------------
   // set size in points of subtitles for x and y axis'
   void SetAxisSubtitleSize(LONG size);

   //------------------------------------------------------------------------
   // set size in points of subtitles for x and y axis'
   LONG GetAxisSubtitleSize() const;

   //------------------------------------------------------------------------
   // Set the title for the X axis
   void SetXAxisTitle(LPCTSTR strTitle);

   //------------------------------------------------------------------------
   // Return the title for the X axis
   LPCTSTR GetXAxisTitle() const;

   //------------------------------------------------------------------------
   // Set the subtitle for the X axis
   void SetXAxisSubtitle(LPCTSTR strSubtitle);

   //------------------------------------------------------------------------
   // Return the subtitle for the x axis
   LPCTSTR GetXAxisSubtitle() const;

   //------------------------------------------------------------------------
   // Set numeric formatting for x axis
   void SetXAxisValueFormat(sysNumericFormatTool& format);

   //------------------------------------------------------------------------
   // Get numeric formatting for x axis
   const sysNumericFormatTool* GetXAxisValueFormat() const;

   void SetXAxisScale(grAxisXY::AxisScale scale);
   grAxisXY::AxisScale GetXAxisScale() const;
   void SetYAxisScale(grAxisXY::AxisScale scale);
   grAxisXY::AxisScale GetYAxisScale() const;

   //------------------------------------------------------------------------
   // Set numeric formatting for y axis
   void SetYAxisValueFormat(sysNumericFormatTool& format);

   //------------------------------------------------------------------------
   // Get numeric formatting for y axis
   const sysNumericFormatTool* GetYAxisValueFormat() const;

   //------------------------------------------------------------------------
   // set the title for the Y axis
   void SetYAxisTitle(LPCTSTR strTitle);

   //------------------------------------------------------------------------
   // Get the title for the Y axis
   LPCTSTR GetYAxisTitle() const;

   //------------------------------------------------------------------------
   // Set the subtitle for the Y axis
   void SetYAxisSubtitle(LPCTSTR strSubtitle);

   //------------------------------------------------------------------------
   // Get the title for the Y axis
   LPCTSTR GetYAxisSubtitle() const;

   //------------------------------------------------------------------------
   // Get the number of minor tics on the x axis
   LONG GetXAxisNumberOfMinorTics() const;

   //------------------------------------------------------------------------
   // Set the number of minor tics on the x axis
   void SetXAxisNumberOfMinorTics(LONG num);

   //------------------------------------------------------------------------
   // Get the number of minor tics on the y axis
   LONG GetYAxisNumberOfMinorTics() const;

   //------------------------------------------------------------------------
   // Set the number of minor tics on the y axis.
   void SetYAxisNumberOfMinorTics(LONG num);

   //------------------------------------------------------------------------
   // Get the number of Major tics on the x axis
   LONG GetXAxisNumberOfMajorTics() const;

   //------------------------------------------------------------------------
   // Set the number of Major tics on the x axis
   void SetXAxisNumberOfMajorTics(LONG num);

   //------------------------------------------------------------------------
   // Get the number of Major tics on the y axis
   LONG GetYAxisNumberOfMajorTics() const;

   //------------------------------------------------------------------------
   // Set the number of Major tics on the y axis.
   void SetYAxisNumberOfMajorTics(LONG num);

   //------------------------------------------------------------------------
   // Sets/Gets the angle from the X-axis for the text in 10ths of a degree
   // (455 = 45.5 degrees)
   LONG GetXAxisLabelAngle() const;
   void SetXAxisLabelAngle(LONG angle);

   //------------------------------------------------------------------------
   // Sets/Gets the angle from the X-axis for the text in 10ths of a degree
   // (455 = 45.5 degrees)
   LONG GetYAxisLabelAngle() const;
   void SetYAxisLabelAngle(LONG angle);

   //------------------------------------------------------------------------
   // Get if nice numbers are to be used for X axis
   bool GetXAxisNiceRange() const;

   //------------------------------------------------------------------------
   // Set if nice numbers are to be used for X axis
   void SetXAxisNiceRange(bool nice=true);

   void SetXAxisForcedRange(Float64 leftVal, Float64 rightVal, Float64 increment);
   bool IsXAxisRangeForced() const;

   //------------------------------------------------------------------------
   // Get if nice numbers are to be used for Y axis
   bool GetYAxisNiceRange() const;

   //------------------------------------------------------------------------
   // Set if nice numbers are to be used for Y axis
   void SetYAxisNiceRange(bool nice=true);

   //------------------------------------------------------------------------
   // Get insurance that zero is contained along Y axis no matter what the min/max
   // Y values are. This is true, by default.
   bool GetPinYAxisAtZero() const;

   //------------------------------------------------------------------------
   // Set insurance that zero is contained along Y axis no matter what the min/max
   // Y values are.
   void SetPinYAxisAtZero(bool pin=true);

   //------------------------------------------------------------------------
   // If set to true, the X and Y axis will have the same scale
   void SetIsotropicAxes(bool bIsotropic=true);
   bool GetIsotropicAxes() const;

   void SetHorizontalControlLine(bool set = true);
   bool GetHorizontalControlLine() const;

   //------------------------------------------------------------------------
   // Set whether to show the grid or not
   void SetDoDrawGrid(bool doDraw=true) {m_DoDrawGrid=doDraw;}

   //------------------------------------------------------------------------
   // Determine if grid is to be drawn
   bool GetDoDrawGrid() const {return m_DoDrawGrid;}

   //------------------------------------------------------------------------
   bool DrawLegend() const { return m_bDrawLegend; }
   void DrawLegend(bool bDrawLegend) { m_bDrawLegend = bDrawLegend; }

   //------------------------------------------------------------------------
   enum LegendBoarderType {lbNoBoarder, lbCheckerBoarder, lbBoundary};

   void SetLegendBoarderStyle(LegendBoarderType type);
   LegendBoarderType GetLegendBoarderStyle() const;

   //------------------------------------------------------------------------
   // Set the pen style for a dataset
   // nPenStyle, nWidth and crColor are defined the same as for the 
   // CreatePen Windows api call.
   void SetPenStyle(IndexType cookie, int nPenStyle, int nWidth, COLORREF crColor);

   //------------------------------------------------------------------------
   // Set the pen style for the overlay grid
   // nPenStyle, nWidth and crColor are defined the same as for the 
   // CreatePen Windows api call.
   void SetGridPenStyle(int nPenStyle, int nWidth, COLORREF crColor);

   void SetHorizontalControlLinePenStyle(int nPenStyle, int nWidth, COLORREF crColor);

   // GROUP: INQUIRY

   //------------------------------------------------------------------------
   // Sets the label that will be displayed in the legend
   void SetDataLabel(IndexType cookie,LPCTSTR lpszLabel);

   //------------------------------------------------------------------------
   // Get a point mapper for drawing into the client area of the graph
   const grlibPointMapper& GetClientAreaPointMapper(HDC hDC);

   //------------------------------------------------------------------------
   // Set the background color of the client area
   void SetClientAreaColor(COLORREF color) {m_ClientAreaColor=color;}

   //------------------------------------------------------------------------
   // Get the background color of the client area
   COLORREF GetClientAreaColor() const {return m_ClientAreaColor;}

   //------------------------------------------------------------------------
   // Get/Set the minimum zoom bounds for the graph in world coordinates. This is
   // the smallest height and width that the graph will shrink to. Setting this to zero
   // will allow you to display data from very small domains, but will also cause
   // numerical problems if the actual width or height of the data set is zero.
   // The default values for height and width are 1.0e-6.
   void GetMinimumZoomBounds(Float64* pHeight, Float64* pWidth) const;
   void SetMinimumZoomBounds(Float64 Height, Float64 Width);

   // Set/Get the minimum size of the graph. The graph plotting space will be no smaller
   // than these values regardless of the size of the data sets
   void SetMinimumSize(Float64 Xmin,Float64 Xmax,Float64 Ymin,Float64 Ymax);
   void GetMinimumSize(Float64* pXmin,Float64* pXmax,Float64* pYmin,Float64* pYmax) const;

protected:

private:
   // GROUP: DATA MEMBERS
   struct PenData
   {
      int Style;
      int Width;
      COLORREF Color;
   };

   typedef std::vector<gpPoint2d> DataSeries;

   struct GraphData
   {
      std::_tstring Label;
      PenData Pen;
      DataSeries Series;
   };

   typedef std::map<IndexType,GraphData> GraphDataMap;
   GraphDataMap m_GraphDataMap;

   gpRect2d m_WorldRect;

   RECT m_OutputRect;
   RECT m_LegendRect;
   SIZE m_LegendItemSize;
   int  m_nLegendRows;
   int  m_nLegendCols;
   int  m_LegendBorder;
   int  m_LegendSymbolLength;

   grAxisXY m_XAxis;
   grAxisXY m_YAxis;
   bool m_XAxisRangeForced; // if true, the XAxis range is forced by the user
   bool m_XAxisNiceRange; // if true, the XAxis is set to a nice range
   bool m_YAxisNiceRange;
   bool m_PinYAxisAtZero;
   bool m_bIsotropicAxes;
   bool m_bHorizontalControlLine;

   grlibPointMapper m_PointMapper;
   bool m_IsBroken;

   bool m_DoDrawAxis;
   bool m_DoDrawGrid;
   bool m_bDrawLegend;
   LegendBoarderType m_LegendBoarderType;
   PenData m_GridPenData;
   PenData m_HorzControlLinePenData;

   std::_tstring m_GraphTitle;
   std::_tstring m_GraphSubtitle;
   LONG    m_GraphTitleSize;
   LONG    m_GraphSubtitleSize;
   LONG    m_LegendFontSize;

   COLORREF m_ClientAreaColor;

   // metrics for drawing graph - don't need to copy since they are 
   // updated on every draw.
   LONG    m_TitleLoc;
   LONG    m_SubtitleLoc;

   static const Float64 m_RightBorderFraction;

   Float64 m_MinZoomHeight;
   Float64 m_MinZoomWidth;

   Float64 m_Xmin, m_Xmax, m_Ymin, m_Ymax;

   // GROUP: LIFECYCLE
   grGraphXY();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void DrawCurve(HDC hDC);
   void DrawAxes(HDC hDC);
   void DrawLegend(HDC hDC);
   void SetBroken();
   void SetFixed();
   int UpdateLegendMetrics(HDC hDC);

   // GROUP: ACCESS
   // GROUP: INQUIRY
   bool IsBroken();

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

#endif // GraphXY_H_

