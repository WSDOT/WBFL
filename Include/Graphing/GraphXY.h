///////////////////////////////////////////////////////////////////////
// Graphing - Line graph plotting and graph definition management library
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

#include <Graphing/GraphingExp.h>
#include <Graphing/PointMapper.h>
#include <Graphing/AxisXY.h>
#include <System\INumericFormatTool.h>
#include <map>

namespace WBFL
{
   namespace Graphing
   {
      /// An X-Y line graph object.
      class GRAPHINGCLASS GraphXY
      {
      public:
         /// Defines the border style for the graph legend
         enum class Style {
            None,  ///< legend does not have a border
            Checker, ///< each legend item has a rectangular border
            Boundary ///< legend has a single rectangular border
         };

         using DataSeries = std::vector<Point>;

         GraphXY() = delete;
         GraphXY(WBFL::System::NumericFormatTool* pXAxisFormat, WBFL::System::NumericFormatTool* pYAxisFormat);

         virtual ~GraphXY();

         /// Creates a new data series in the graph.  Returns a cookie used to
         /// reference this data series at a later time.
         IndexType CreateDataSeries();

         /// Creates a new data series in the graph and defines the attributes of the pen used to draw the line.
         /// Returns a cookie used to reference this data series at a later time.
         IndexType CreateDataSeries(LPCTSTR lpszLabel,///< name of the data series
            int nPenStyle, ///< pen style
            int nWidth, ///< pen width
            COLORREF crColor ///< pen color
         );

         /// Find an existing data series and return its cookie. Returns INVALID_INDEX if not found
         IndexType FindDataSeries(LPCTSTR lpszLabel);

         /// @brief  Updates the label for a data series
         /// @param cookie Data series identifier returned from CreateDataSeries
         /// @param lpszLabel Data series label
         void SetDataSeriesLabel(IndexType cookie, LPCTSTR lpszLabel);

         /// Returns the list of data series cookies
         std::vector<IndexType> GetCookies() const;

         /// Gets the data series data
         void GetDataSeriesData(IndexType cookie, std::_tstring* pLabel, int* pPenStyle, int* pWidth, COLORREF* pColor) const;

         /// Gets the data series data points
         void GetDataSeriesPoints(IndexType cookie, DataSeries* pvPoints) const;

         /// Adds an individual point to the graph.
         void AddPoint(IndexType cookie, const Point& rPoint);

         /// Adds a collection of points to the graph.
         void AddPoints(IndexType cookie, const DataSeries& vPoints);

         /// Sets the points to the graph.
         void SetPoints(IndexType cookie, const DataSeries& vPoints);

         /// Removes all the points from the graph
         void ClearPoints(IndexType cookie);

         /// Clears all data from the graph
         void ClearData();

         /// Returns the point of points in the graph
         IndexType GetPointCount(IndexType cookie) const;

         /// Removes the data series from the graph.
         void RemoveDataSeries(IndexType cookie);

         /// Returns the number of data series from the graph
         IndexType GetDataSeriesCount() const;

         /// Returns the output rectangle
         RECT GetOutputRect() const;

         /// Sets the device rectangle that the world points will be mapped to.
         /// NOTE: This must be called at least once prior to Draw()
         void SetOutputRect(const RECT& rOutputRect);

         // Get raw boundary of data rect. This means that min boundaries and 'Pinned" status are ignored
         Rect GetRawWorldRect() const;

         /// Draws the graph on the given device context.
         /// This method calls UpdateGraphMetrics, DrawBackground, and DrawDataSeries
         /// You can call these three steps individual if you want to enhance the
         /// graph drawing. You MUST call UpdateGraphMetrics before any drawing
         /// takes place
         virtual void Draw(HDC hDC);

         /// Draw only the background
         virtual void DrawBackground(HDC hDC);

         /// Draw only the data series
         virtual void DrawDataSeries(HDC hDC);

         /// Updates the metrics of the graph. Must be called before calling any drawing methods except for  Draw.
         virtual void UpdateGraphMetrics(HDC hDC);

         /// Sets the graph title
         void SetTitle(LPCTSTR strTitle);

         /// Returns the graph title
         LPCTSTR GetTitle() const;

         /// Sets the title size in points
         void SetTitleSize(LONG size);

         /// Returns the title size in points
         LONG GetTitleSize() const;

         /// Sets the graph subtitle
         void SetSubtitle(LPCTSTR strSubtitle);

         /// Returns the graph subtitle
         LPCTSTR GetSubtitle() const;

         /// Sets the Subtitle size in points
         void SetSubtitleSize(LONG size);

         /// Returns the Subtitle size in points
         LONG GetSubtitleSize() const;

         /// Sets the size in points of titles for x and y axis
         void SetAxisTitleSize(LONG size);

         /// Returns the size in points of titles for x and y axis
         LONG GetAxisTitleSize() const;

         /// Sets size in points of subtitles for x and y axis
         void SetAxisSubtitleSize(LONG size);

         /// Returns the size in points of subtitles for x and y axis
         LONG GetAxisSubtitleSize() const;

         /// Sets the title for the X axis
         void SetXAxisTitle(LPCTSTR strTitle);

         /// Returns the title for the X axis
         LPCTSTR GetXAxisTitle() const;

         /// Sets the subtitle for the X axis
         void SetXAxisSubtitle(LPCTSTR strSubtitle);

         /// Returns the subtitle for the x axis
         LPCTSTR GetXAxisSubtitle() const;

         /// Sets the numeric formatting for x axis
         void SetXAxisValueFormat(WBFL::System::NumericFormatTool* pFormat);

         /// Returns the numeric formatting for x axis
         const WBFL::System::NumericFormatTool* GetXAxisValueFormat() const;

         /// Sets the x axis scale
         void SetXAxisScale(AxisXY::AxisScale scale);

         /// Returns the x axis scale
         AxisXY::AxisScale GetXAxisScale() const;

         /// Sets the y axis scale
         void SetYAxisScale(AxisXY::AxisScale scale);

         /// Returns the y axis scale
         AxisXY::AxisScale GetYAxisScale() const;

         /// Sets the numeric formatting for y axis
         void SetYAxisValueFormat(WBFL::System::NumericFormatTool* pFormat);

         /// Gets the numeric formatting for y axis
         const WBFL::System::NumericFormatTool* GetYAxisValueFormat() const;

         /// Sets the title for the Y axis
         void SetYAxisTitle(LPCTSTR strTitle);

         /// Returns the title for the Y axis
         LPCTSTR GetYAxisTitle() const;

         /// Sets the subtitle for the Y axis
         void SetYAxisSubtitle(LPCTSTR strSubtitle);

         /// Returns the title for the Y axis
         LPCTSTR GetYAxisSubtitle() const;

         /// Sets the number of minor tics on the x axis
         void SetXAxisNumberOfMinorTics(LONG num);

         /// Returns the number of minor tics on the x axis
         LONG GetXAxisNumberOfMinorTics() const;

         /// Sets the number of minor tics on the y axis.
         void SetYAxisNumberOfMinorTics(LONG num);

         /// Returns the number of minor tics on the y axis
         LONG GetYAxisNumberOfMinorTics() const;

         /// Sets the number of Major tics on the x axis
         void SetXAxisNumberOfMajorTics(LONG num);

         /// Returns the number of Major tics on the x axis
         LONG GetXAxisNumberOfMajorTics() const;

         /// Sets the number of Major tics on the y axis.
         void SetYAxisNumberOfMajorTics(LONG num);

         /// Returns the number of Major tics on the y axis
         LONG GetYAxisNumberOfMajorTics() const;

         /// Sets the angle from the X-axis for the text in 10ths of a degree
         /// (455 = 45.5 degrees)
         void SetXAxisLabelAngle(LONG angle);

         /// Returns the angle from the X-axis for the text in 10ths of a degree
         LONG GetXAxisLabelAngle() const;

         /// Sets the angle from the X-axis for the text in 10ths of a degree
         // (455 = 45.5 degrees)
         void SetYAxisLabelAngle(LONG angle);

         /// Returns the angle from the Y-axis for the text in 10ths of a degree
         LONG GetYAxisLabelAngle() const;

         /// Sets if nice numbers are to be used for X axis
         void XAxisNiceRange(bool nice);

         /// Returns true if nice numbers are to be used for X axis
         bool XAxisNiceRange() const;

         /// Forces X-axis values into the specified range.
         void SetXAxisForcedRange(Float64 leftVal, Float64 rightVal, Float64 increment);

         /// Returns true if X-axis values are forced into a range
         bool IsXAxisRangeForced() const;

         /// Sets if nice numbers are to be used for Y axis
         void YAxisNiceRange(bool nice);

         /// Returns true if nice numbers are to be used for Y axis
         bool YAxisNiceRange() const;

         /// Forces zero to be contained along Y axis
         void PinYAxisAtZero(bool pin);

         /// Returns true if the Y axis is forced to contain zero
         bool PinYAxisAtZero() const;

         /// Specifies if the X and Y axis are to have the same scale
         void IsotropicAxes(bool bIsotropic);

         /// Returns true if the X and Y axis have the same scale
         bool IsotropicAxes() const;

         /// Specifies if a horizontal control line is to be drawn. 
         /// The horizontal control line is located at Y=0. 
         /// This line is not an axis and is not labeled. 
         /// It provides a reference for Y=0;
         void HorizontalControlLine(bool set);

         /// Returns true if a horizontal control line is to be drawn
         bool HorizontalControlLine() const;

         /// Sets whether to show the grid or not
         void DrawGrid(bool doDraw) { m_DoDrawGrid = doDraw; }

         /// Returns true if a grid is to be drawn
         bool DrawGrid() const { return m_DoDrawGrid; }

         /// Sets whether to draw the graph legend
         void DrawLegend(bool bDrawLegend) { m_bDrawLegend = bDrawLegend; }

         /// Returns true if the graph legend is to be drawn
         bool DrawLegend() const { return m_bDrawLegend; }

         /// Sets the legend border style
         void SetLegendBorderStyle(Style type);

         /// Returns the legend border style
         Style GetLegendBorderStyle() const;

         /// Sets the pen style for a dataset. Parameters are the same as for CreatePen in the Windows API.
         void SetPenStyle(IndexType cookie, int nPenStyle, int nWidth, COLORREF crColor);

         /// Set the pen style for the overlay grid
         void SetGridPenStyle(int nPenStyle, int nWidth, COLORREF crColor);

         /// Sets the pen style for the horizontal control line
         void SetHorizontalControlLinePenStyle(int nPenStyle, int nWidth, COLORREF crColor);

         /// Sets the label that will be displayed in the legend
         void SetDataLabel(IndexType cookie, LPCTSTR lpszLabel);

         /// Returns a point mapper for drawing into the client area of the graph
         const PointMapper& GetClientAreaPointMapper(HDC hDC);

         /// Sets the background color of the client area
         void SetClientAreaColor(COLORREF color) { m_ClientAreaColor = color; }

         /// Returns the background color of the client area
         COLORREF GetClientAreaColor() const { return m_ClientAreaColor; }

         /// Sets the minimum zoom bounds for the graph in world coordinates. This is
         /// the smallest height and width that the graph will shrink to. Setting this to zero
         /// will allow you to display data from very small domains, but will also cause
         /// numerical problems if the actual width or height of the data set is zero.
         /// The default values for height and width are 1.0e-6.
         void SetMinimumZoomBounds(Float64 Height, Float64 Width);

         /// Returns teh minimum zoom bounds
         void GetMinimumZoomBounds(Float64* pHeight, Float64* pWidth) const;

         /// Sets the minimum size of the graph. The graph plotting space will be no smaller
         /// than these values regardless of the size of the data sets
         void SetMinimumSize(Float64 Xmin, Float64 Xmax, Float64 Ymin, Float64 Ymax);

         /// Returns the minimum size of the graph
         void GetMinimumSize(Float64* pXmin, Float64* pXmax, Float64* pYmin, Float64* pYmax) const;

      private:
         struct PenData
         {
            int Style;
            int Width;
            COLORREF Color;
         };

         struct GraphData
         {
            std::_tstring Label;
            PenData Pen;
            DataSeries Series;
         };

         using GraphDataMap = std::map<IndexType, GraphData>;
         GraphDataMap m_GraphDataMap;

         Rect m_WorldRect{Float64_Max, Float64_Max, -Float64_Max, -Float64_Max };

         AxisXY m_XAxis;
         AxisXY m_YAxis;
         bool m_XAxisRangeForced = false; // if true, the XAxis range is forced by the user
         bool m_XAxisNiceRange = true; // if true, the XAxis is set to a nice range
         bool m_YAxisNiceRange = true;
         bool m_PinYAxisAtZero = true;
         bool m_bIsotropicAxes = false;
         bool m_bHorizontalControlLine = true;

         bool m_DoDrawAxis = true;
         bool m_DoDrawGrid = true;
         bool m_bDrawLegend = true;
         Style m_LegendBorderStyle = Style::Checker;
         PenData m_GridPenData{ PS_SOLID,1,RGB(0,0,0) };
         PenData m_HorzControlLinePenData{ PS_SOLID,2,RGB(0,0,0) };

         std::_tstring m_GraphTitle;
         std::_tstring m_GraphSubtitle;
         LONG    m_GraphTitleSize = 14;
         LONG    m_GraphSubtitleSize = 10;
         LONG    m_LegendFontSize = 8;

         COLORREF m_ClientAreaColor = RGB(240, 240, 240);

         Float64 m_MinZoomHeight = 1.0e-06;
         Float64 m_MinZoomWidth = 1.0e-06;

         Float64 m_Xmin = 0, m_Xmax = 1, m_Ymin = 0, m_Ymax = 1;
         bool m_bWasMinSet = false;

         RECT m_OutputRect;
         RECT m_LegendRect;
         SIZE m_LegendItemSize;
         int  m_nLegendRows;
         int  m_nLegendCols;
         int  m_LegendBorder;
         int  m_LegendSymbolLength;

         PointMapper m_PointMapper;

         // metrics for drawing graph - don't need to copy since they are 
         // updated on every draw.
         LONG    m_TitleLoc;
         LONG    m_SubtitleLoc;

         static const Float64 m_RightBorderFraction;



         void DrawCurve(HDC hDC);
         void DrawAxes(HDC hDC);
         void DrawLegend(HDC hDC);
         int UpdateLegendMetrics(HDC hDC);
      };
   }; // Graphing
}; // WBFL

