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

#include "stdafx.h"
#include <MathEx.h>
#include <Graphing/GraphXY.h>
#include "GraphTool.h"
#include <float.h>
#include <algorithm>

using namespace WBFL::Graphing;

const Float64 GraphXY::m_RightBorderFraction = .05;

GraphXY::GraphXY(WBFL::System::NumericFormatTool* pXAxisFormat, WBFL::System::NumericFormatTool* pYAxisFormat)
{
   // set up the x axis
   m_XAxis.SetNumberOfMinorTics(5);
   m_XAxis.SetTicLocation(AxisXY::TicLocation::Above);
   m_XAxis.SetTextLocation(AxisXY::TextLocation::Below);
   m_XAxis.SetValueFormat(pXAxisFormat);

   // set up the y axis
   m_YAxis.SetTicLocation(AxisXY::TicLocation::Below);
   m_YAxis.SetTextLocation(AxisXY::TextLocation::Above);
   m_YAxis.SetNumberOfMinorTics(5);
   m_YAxis.SetValueFormat(pYAxisFormat);
}

GraphXY::~GraphXY()
{
}

//======================== OPERATIONS =======================================
IndexType GraphXY::CreateDataSeries()
{
   return CreateDataSeries(_T(""),PS_SOLID,1,RGB(0,0,0));
}

IndexType GraphXY::CreateDataSeries(LPCTSTR lpszLabel,int nPenStyle, int nWidth, COLORREF crColor)
{
   IndexType cookie = m_GraphDataMap.size();

   GraphData gd;
   gd.Label = (lpszLabel == nullptr ? _T("") : lpszLabel);
   gd.Pen.Color = crColor;
   gd.Pen.Width = nWidth;
   gd.Pen.Style = nPenStyle;
   m_GraphDataMap.insert(std::make_pair(cookie,gd));
   return cookie;
}

IndexType GraphXY::FindDataSeries(LPCTSTR lpszLabel)
{
   for (const auto& [index,series] : m_GraphDataMap)
   {
      if (series.Label == lpszLabel)
      {
         return index;
      }
   }

   return INVALID_INDEX;
}

void GraphXY::SetDataSeriesLabel(IndexType cookie, LPCTSTR lpszLabel)
{
   auto found = m_GraphDataMap.find(cookie);
   if(found != m_GraphDataMap.end())
   {
      found->second.Label = lpszLabel;
   }
}

std::vector<IndexType> GraphXY::GetCookies() const
{
    std::vector<IndexType> cookies;
    for (const auto& [index,data] : m_GraphDataMap)
    {
       // only return cookies for series that contain data
       if (0 < data.Series.size())
       {
          cookies.push_back(index);
       }
    }

    return cookies;
}

void GraphXY::GetDataSeriesData(IndexType cookie, std::_tstring* pLabel, int* pPenStyle, int* pWidth, COLORREF* pColor) const
{
   GraphDataMap::const_iterator found = m_GraphDataMap.find(cookie);
   CHECK(found != m_GraphDataMap.end());
   const auto [index, graph_data](*found);
   *pLabel = graph_data.Label;
   *pPenStyle = graph_data.Pen.Style;
   *pWidth = graph_data.Pen.Width;
   *pColor = graph_data.Pen.Color;
}

void GraphXY::GetDataSeriesPoints(IndexType cookie, DataSeries* pvPoints) const
{
   GraphDataMap::const_iterator found = m_GraphDataMap.find(cookie);
   if (found != m_GraphDataMap.end())
   {
      *pvPoints = found->second.Series;
   }
   else
   {
      ATLASSERT(0);
   }
}

void GraphXY::AddPoint(IndexType cookie,const Point& rPoint)
{
   GraphDataMap::iterator found = m_GraphDataMap.find(cookie);
   if ( found != m_GraphDataMap.end() )
   {
      GraphData& gd = (*found).second;
      gd.Series.push_back(rPoint);
   }
}

void GraphXY::AddPoints(IndexType cookie,const DataSeries& vPoints)
{
   GraphDataMap::iterator found = m_GraphDataMap.find(cookie);
   if ( found != m_GraphDataMap.end() )
   {
      GraphData& gd = (*found).second;
      gd.Series.insert(gd.Series.end(),vPoints.begin(),vPoints.end());
   }
}

void GraphXY::SetPoints(IndexType cookie, const DataSeries& vPoints)
{
   GraphDataMap::iterator found = m_GraphDataMap.find(cookie);
   if (found != m_GraphDataMap.end())
   {
      GraphData& gd = (*found).second;
      gd.Series = vPoints;
   }
}

void GraphXY::ClearPoints(IndexType cookie)
{
   GraphDataMap::iterator found = m_GraphDataMap.find(cookie);
   if ( found != m_GraphDataMap.end() )
   {
      GraphData& gd = (*found).second;
      gd.Series.clear();
   }
}

void GraphXY::ClearData()
{
   m_GraphDataMap.clear();
}

IndexType GraphXY::GetPointCount(IndexType cookie) const
{
   GraphDataMap::const_iterator found = m_GraphDataMap.find(cookie);
   if ( found != m_GraphDataMap.end() )
   {
      const GraphData& gd = (*found).second;
      return gd.Series.size();
   }

   return 0;
}

void GraphXY::RemoveDataSeries(IndexType cookie)
{
   m_GraphDataMap.erase( cookie );
}

IndexType GraphXY::GetDataSeriesCount() const
{
   return m_GraphDataMap.size();
}

void GraphXY::SetOutputRect(const RECT& rOutputRect)
{
   m_OutputRect = rOutputRect;
}

Rect GraphXY::GetRawWorldRect() const
{
   Rect worldRect(Float64_Max, Float64_Max,-Float64_Max,-Float64_Max);

   IndexType nDataPoints = 0;
   IndexType nMaxDataPoints = 0;
   GraphDataMap::const_iterator graphDataIter(m_GraphDataMap.begin());
   GraphDataMap::const_iterator graphDataIterEnd(m_GraphDataMap.end());
   for (; graphDataIter != graphDataIterEnd; graphDataIter++)
   {
      const GraphData& graphData = graphDataIter->second;

      IndexType nDP = 0;
      DataSeries::const_iterator dataSeriesIter(graphData.Series.begin());
      DataSeries::const_iterator dataSeriesIterEnd(graphData.Series.end());
      for (; dataSeriesIter != dataSeriesIterEnd; dataSeriesIter++)
      {
         const Point& p = *dataSeriesIter;
         worldRect.Left() = min(p.X(),worldRect.Left());
         worldRect.Right() = max(p.X(),worldRect.Right());
         worldRect.Top() = max(p.Y(),worldRect.Top());
         worldRect.Bottom() = min(p.Y(),worldRect.Bottom());
         nDataPoints++;
         nDP++;
      }
      nMaxDataPoints = max(nMaxDataPoints,nDP);
   }

   return worldRect;
}

RECT GraphXY::GetOutputRect() const
{
   return m_OutputRect;
}

void GraphXY::Draw(HDC hDC)
{
   UpdateGraphMetrics(hDC);
   DrawBackground( hDC );
   DrawDataSeries( hDC );

}

void GraphXY::DrawBackground(HDC hDC)
{
   // fill the client area with a color
   LONG dw, dh, dcx, dcy;
   m_PointMapper.GetDeviceExt(&dw, &dh);
   m_PointMapper.GetDeviceOrg(&dcx, &dcy);
   RECT c_rect;
   c_rect.left = dcx-(LONG)ceil(dw/2.);
   c_rect.top  = dcy-(LONG)ceil(dh/2.);
   c_rect.right = dcx+(LONG)ceil(dw/2.);
   c_rect.bottom = dcy+(LONG)ceil(dh/2.);

   // logic taken here from CDC::FillSolidRect
   COLORREF bg = ::SetBkColor(hDC, m_ClientAreaColor);
	::ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &c_rect, nullptr, 0, nullptr);
   ::SetBkColor(hDC, bg);

   // draw the axis'
   if (m_DoDrawAxis)    
   {
      DrawAxes( hDC );
   }

   if ( m_bDrawLegend )
   {
      DrawLegend( hDC );
   }

   // draw the title and subtitle
   LONG tx;
   ::SetTextAlign(hDC, TA_CENTER | TA_BASELINE);
   tx = (m_OutputRect.left+m_OutputRect.right)/2;

   GraphTool::TextOutRotated(hDC, tx, m_TitleLoc, 0,
                      m_GraphTitle.c_str(), (LONG)m_GraphTitle.size(),
                      m_GraphTitleSize);

   GraphTool::TextOutRotated(hDC, tx, m_SubtitleLoc, 0,
                      m_GraphSubtitle.c_str(), (LONG)m_GraphSubtitle.size(),
                      m_GraphSubtitleSize);
}

void GraphXY::DrawDataSeries(HDC hDC)
{
   DrawCurve( hDC );
}

LPCTSTR GraphXY::GetTitle() const
{
   return m_GraphTitle.c_str();
}

void GraphXY::SetTitle(LPCTSTR strTitle)
{
   m_GraphTitle = strTitle;
}

LONG GraphXY::GetTitleSize() const
{
   return m_GraphTitleSize;
}

void GraphXY::SetTitleSize(LONG size)
{
   m_GraphTitleSize = size;
}

LPCTSTR GraphXY::GetSubtitle() const
{
   return m_GraphSubtitle.c_str();
}

void GraphXY::SetSubtitle(LPCTSTR strSubtitle)
{
    m_GraphSubtitle = strSubtitle;
}

LONG GraphXY::GetSubtitleSize() const
{
   return m_GraphSubtitleSize;
}

void GraphXY::SetSubtitleSize(LONG size)
{
   m_GraphSubtitleSize = size;
}

void GraphXY::SetAxisTitleSize(LONG size)
{
   m_XAxis.SetTitleFontSize(size);
   m_YAxis.SetTitleFontSize(size);
}

LONG GraphXY::GetAxisTitleSize() const
{
   return m_XAxis.GetTitleFontSize();
}

void GraphXY::SetAxisSubtitleSize(LONG size)
{
   m_XAxis.SetSubtitleFontSize(size);
   m_YAxis.SetSubtitleFontSize(size);
}

LONG GraphXY::GetAxisSubtitleSize() const
{
   return m_XAxis.GetSubtitleFontSize();
}

LONG GraphXY::GetXAxisLabelAngle() const
{
   return m_XAxis.GetValueAngle();
}

void GraphXY::SetXAxisLabelAngle(LONG angle)
{
   m_XAxis.SetValueAngle(angle);
}

LONG GraphXY::GetYAxisLabelAngle() const
{
   return m_YAxis.GetValueAngle();
}

void GraphXY::SetYAxisLabelAngle(LONG angle)
{
   m_YAxis.SetValueAngle(angle);
}

void GraphXY::SetXAxisTitle(LPCTSTR strTitle)
{
   m_XAxis.SetTitleText(strTitle);
}

LPCTSTR GraphXY::GetXAxisTitle() const
{
   return m_XAxis.GetTitleText();
}

void GraphXY::SetXAxisSubtitle(LPCTSTR strSubtitle)
{
   m_XAxis.SetSubtitleText(strSubtitle);
}

LPCTSTR GraphXY::GetXAxisSubtitle() const
{
   return m_XAxis.GetSubtitleText();
}

void GraphXY::SetYAxisTitle(LPCTSTR strTitle)
{
   m_YAxis.SetTitleText(strTitle);
}

LPCTSTR GraphXY::GetYAxisTitle() const
{
   return m_YAxis.GetTitleText();
}

void GraphXY::SetYAxisSubtitle(LPCTSTR strSubtitle)
{
   m_YAxis.SetSubtitleText(strSubtitle);

}

LPCTSTR GraphXY::GetYAxisSubtitle() const
{
   return m_YAxis.GetSubtitleText();
}

LONG GraphXY::GetXAxisNumberOfMinorTics() const
{
   return m_XAxis.GetNumberOfMinorTics();
}

void GraphXY::SetXAxisNumberOfMinorTics(LONG num)
{
   m_XAxis.SetNumberOfMinorTics(num);
}

LONG GraphXY::GetYAxisNumberOfMinorTics() const
{
   return m_YAxis.GetNumberOfMinorTics();
}

void GraphXY::SetYAxisNumberOfMinorTics(LONG num)
{
   m_YAxis.SetNumberOfMinorTics(num);
}

void GraphXY::SetXAxisValueFormat(WBFL::System::NumericFormatTool* pFormat)
{
   m_XAxis.SetValueFormat(pFormat);
}

const WBFL::System::NumericFormatTool* GraphXY::GetXAxisValueFormat() const
{
   return  m_XAxis.GetValueFormat();
}

void GraphXY::SetXAxisScale(AxisXY::AxisScale scale)
{
   m_XAxis.SetScale(scale);
   if ( m_XAxis.GetScale() == AxisXY::AxisScale::Integral )
   {
      m_XAxisNiceRange = false; // can't have nice range with INTEGRAL
   }
}

AxisXY::AxisScale GraphXY::GetXAxisScale() const
{
   return m_XAxis.GetScale();
}

void GraphXY::SetYAxisScale(AxisXY::AxisScale scale)
{
   m_YAxis.SetScale(scale);
   if ( m_YAxis.GetScale() == AxisXY::AxisScale::Integral )
   {
      m_YAxisNiceRange = false; // can't have nice range with INTEGRAL
   }
}

AxisXY::AxisScale GraphXY::GetYAxisScale() const
{
   return m_YAxis.GetScale();
}

void GraphXY::SetYAxisValueFormat(WBFL::System::NumericFormatTool* pFormat)
{
   m_YAxis.SetValueFormat(pFormat);
}

const WBFL::System::NumericFormatTool* GraphXY::GetYAxisValueFormat() const
{
   return  m_YAxis.GetValueFormat();
}

void GraphXY::SetPenStyle(IndexType cookie, int nPenStyle, int nWidth, COLORREF crColor)
{
   GraphDataMap::iterator found = m_GraphDataMap.find(cookie);
   if ( found != m_GraphDataMap.end() )
   {
      GraphData& gd = (*found).second;
      gd.Pen.Color = crColor;
      gd.Pen.Style = nPenStyle;
      gd.Pen.Width = nWidth;
   }
}

void GraphXY::SetGridPenStyle(int nPenStyle, int nWidth, COLORREF crColor)
{
   m_GridPenData.Style = nPenStyle;
   m_GridPenData.Color = crColor;
   m_GridPenData.Width = nWidth;
}

void GraphXY::SetHorizontalControlLinePenStyle(int nPenStyle, int nWidth, COLORREF crColor)
{
   m_HorzControlLinePenData.Style = nPenStyle;
   m_HorzControlLinePenData.Color = crColor;
   m_HorzControlLinePenData.Width = nWidth;
}

void GraphXY::SetDataLabel(IndexType cookie,LPCTSTR lpszLabel)
{
   GraphDataMap::iterator found = m_GraphDataMap.find(cookie);
   if ( found != m_GraphDataMap.end() )
   {
      GraphData& gd = (*found).second;
      gd.Label = lpszLabel;
   }
}

void GraphXY::GetMinimumZoomBounds(Float64* pHeight, Float64* pWidth) const
{
   *pHeight = m_MinZoomHeight;
   *pWidth  = m_MinZoomWidth;
}

void GraphXY::SetMinimumZoomBounds(Float64 Height, Float64 Width)
{
   PRECONDITION(0 < Height); // this will cause numeric problems
   PRECONDITION(0 < Width); // this will cause numeric problems

   m_MinZoomHeight = Height;
   m_MinZoomWidth  = Width;
}

void GraphXY::SetMinimumSize(Float64 Xmin,Float64 Xmax,Float64 Ymin,Float64 Ymax)
{
   m_Xmin = Xmin;
   m_Xmax = Xmax;
   m_Ymin = Ymin;
   m_Ymax = Ymax;
   m_bWasMinSet = true;
}

void GraphXY::GetMinimumSize(Float64* pXmin,Float64* pXmax,Float64* pYmin,Float64* pYmax) const
{
   *pXmin = m_Xmin;
   *pXmax = m_Xmax;
   *pYmin = m_Ymin;
   *pYmax = m_Ymax;
}

void GraphXY::SetLegendBorderStyle(Style type)
{
   m_LegendBorderStyle = type;
}

GraphXY::Style GraphXY::GetLegendBorderStyle() const
{
   return m_LegendBorderStyle;
}

const PointMapper& GraphXY::GetClientAreaPointMapper(HDC hDC)
{
   // set up the graph layout
   UpdateGraphMetrics(hDC);

   return m_PointMapper;
}

void GraphXY::UpdateGraphMetrics(HDC hDC)
{
   m_WorldRect.Set(DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX);

   IndexType nDataPoints = 0;
   IndexType nMaxDataPoints = 0;
   GraphDataMap::iterator graphDataIter(m_GraphDataMap.begin());
   GraphDataMap::iterator graphDataIterEnd(m_GraphDataMap.end());
   for ( ; graphDataIter != graphDataIterEnd; graphDataIter++ )
   {
      GraphData& graphData = graphDataIter->second;

      IndexType nDP = 0;
      DataSeries::iterator dataSeriesIter(graphData.Series.begin());
      DataSeries::iterator dataSeriesIterEnd(graphData.Series.end());
      for ( ; dataSeriesIter != dataSeriesIterEnd; dataSeriesIter++ )
      {
         Point& p = *dataSeriesIter;
         m_WorldRect.Left()   = min( p.X(), m_WorldRect.Left()  );
         m_WorldRect.Right()  = max( p.X(), m_WorldRect.Right() );
         m_WorldRect.Top()    = max( p.Y(), m_WorldRect.Top() );
         m_WorldRect.Bottom() = min( p.Y(), m_WorldRect.Bottom() );
         nDataPoints++;
         nDP++;
      }
      nMaxDataPoints = max(nMaxDataPoints,nDP);
   }

   // if there is not any data points, then make the world 1x1
   if ( nDataPoints == 0 )
   {
      m_WorldRect.Left()   = m_XAxis.GetScale() == AxisXY::AxisScale::Linear ? 0.0 : 0.1;
      m_WorldRect.Right()  = 1.0;
      m_WorldRect.Top()    = m_YAxis.GetScale() == AxisXY::AxisScale::Linear ? 0.0 : 0.1;
      m_WorldRect.Bottom() = 1.0;
   }

   // make sure zero is in Y range if requested
   if (m_PinYAxisAtZero && m_YAxis.GetScale() == AxisXY::AxisScale::Linear)
   {
      Point pnt((m_WorldRect.Left()+m_WorldRect.Right())/2., 0.0);
      m_WorldRect.BoundPoint(pnt);
   }

   // make sure that graph ranges are at least equal to the min zoom height and width.
   if (m_WorldRect.Height() < m_MinZoomHeight)
   {
      Float64 cen = (m_WorldRect.Top() + m_WorldRect.Bottom())/2.0;
      m_WorldRect.Top()    = cen + m_MinZoomHeight/2.0;
      m_WorldRect.Bottom() = cen - m_MinZoomHeight/2.0;
   }

   if (m_WorldRect.Width() < m_MinZoomWidth)
   {
      Float64 cen = (m_WorldRect.Right() + m_WorldRect.Left())/2.0;
      m_WorldRect.Right() = cen + m_MinZoomWidth/2.0;
      m_WorldRect.Left()  = cen - m_MinZoomWidth/2.0;
   }

   if ( m_XAxis.GetScale() != AxisXY::AxisScale::Logarithmic && m_bWasMinSet)
   {
      m_WorldRect.Left() = min(m_WorldRect.Left(),m_Xmin);
      m_WorldRect.Right() = max(m_WorldRect.Right(),m_Xmax);
   }

   if ( m_YAxis.GetScale() != AxisXY::AxisScale::Logarithmic && m_bWasMinSet)
   {
      m_WorldRect.Top() = max(m_WorldRect.Top(),m_Ymax);
      m_WorldRect.Bottom() = min(m_WorldRect.Bottom(),m_Ymin);
   }

   if ( IsXAxisRangeForced() )
   {
      Float64 left,right,inc;
      m_XAxis.GetAxisRange(&left,&right,&inc);
      m_WorldRect.Left() = left;
      m_WorldRect.Right() = right;
   }

   if ( m_bIsotropicAxes )
   {
      Float64 width = m_WorldRect.Width();
      Float64 height = m_WorldRect.Height();
      Point center = m_WorldRect.Center();
      if ( width < height )
      {
         m_WorldRect.Left()  = center.X() - height/2;
         m_WorldRect.Right() = center.X() + height/2;
      }
      else
      {
         m_WorldRect.Top()    = center.Y() + width/2;
         m_WorldRect.Bottom() = center.Y() - width/2;
      }
   }

   // set ranges on axis to create graph world client rect area size
   Float64 client_left, client_right, client_bottom, client_top;
   Float64 inc;
   if ( m_XAxis.GetScale() == AxisXY::AxisScale::Integral )
   {
      client_left = 1;
      inc = 1;
      client_right = max(client_left+inc,(Float64)nMaxDataPoints);
      m_XAxis.SetForcedAxisRange(client_left,client_right,inc);
   }
   else
   {
      if (XAxisNiceRange())
      {
         m_XAxis.SetNiceAxisRange(m_WorldRect.Left(), m_WorldRect.Right(),false);
         m_XAxis.GetAxisRange(&client_left, &client_right, &inc);
      }
      else if ( IsXAxisRangeForced() )
      {
         m_XAxis.GetAxisRange(&client_left,&client_right,&inc);
      }
      else
      {
         client_left = m_WorldRect.Left();
         client_right = m_WorldRect.Right();
         CHECK(client_left!=client_right);
         Float64 wid = client_right-client_left;
         LONG numtic = GetXAxisNumberOfMajorTics() - 1;
         if (0 < numtic)
         {
            inc = wid/numtic;
         }
         else
         {
            CHECKX(0,_T("Number of tics must be >0"));
            inc = wid;
         }
         m_XAxis.SetForcedAxisRange(client_left, client_right, inc);
      }
   }

   if ( m_YAxis.GetScale() == AxisXY::AxisScale::Integral )
   {
      client_bottom = 1;
      client_top = (Float64)nMaxDataPoints;
      inc = 1;
      m_YAxis.SetForcedAxisRange(client_top, client_bottom, inc);
   }
   else
   {
      if (YAxisNiceRange())
      {
         m_YAxis.SetNiceAxisRange(m_WorldRect.Bottom(), m_WorldRect.Top(),false);
         m_YAxis.GetAxisRange(&client_bottom, &client_top, &inc);
      }
      else
      {
         client_top = m_WorldRect.Top();
         client_bottom = m_WorldRect.Bottom();
         CHECK(client_top!=client_bottom);
         Float64 wid = client_bottom-client_top;
         LONG numtic = GetYAxisNumberOfMajorTics() - 1;
         if (0 < numtic)
         {
            inc = wid/numtic;
         }
         else
         {
            CHECKX(0,_T("Number of tics must be >0"));
            inc = wid;
         }
         m_YAxis.SetForcedAxisRange(client_bottom, client_top, inc);
      }
   }

   if ( m_XAxis.GetScale() == AxisXY::AxisScale::Logarithmic )
   {
      client_left  = log10(client_left);
      client_right = log10(client_right);
   }

   if ( m_YAxis.GetScale() == AxisXY::AxisScale::Logarithmic )
   {
      client_top    = log10(client_top);
      client_bottom = log10(client_bottom);
   }

   Rect world_client_rect(client_left, client_bottom, client_right, client_top);

   // set up for title and subtitle

   // most metrics are based on font sizes. get sizes for title and subtitle
   HFONT title_font = GraphTool::CreateRotatedFont(hDC, 0, m_GraphTitleSize);
   HGDIOBJ old_font = ::SelectObject(hDC, title_font);
   SIZE size;
   ::GetTextExtentPoint32(hDC,_T("AA"),2,&size);

   LONG title_size = labs(size.cy);

   HFONT subtitle_font = GraphTool::CreateRotatedFont(hDC, 0, m_GraphSubtitleSize);
   ::SelectObject(hDC, subtitle_font);
   ::GetTextExtentPoint32(hDC,_T("AA"),2,&size);

   LONG subtitle_size = labs(size.cy);

   // clean up fonts
   ::SelectObject(hDC, old_font);
   ::DeleteObject(title_font);
   ::DeleteObject(subtitle_font);


   m_TitleLoc    = m_OutputRect.top + 3*title_size/2;
   m_SubtitleLoc = m_TitleLoc       + 3*subtitle_size/2;

   LONG out_height = abs(m_OutputRect.top-m_OutputRect.bottom);
   LONG out_width  = abs(m_OutputRect.left-m_OutputRect.right);

   // determine device client rect size by subtracting out space for axis' and borders
   LONG bottom_border = m_XAxis.GetThickness(hDC) + out_height/100;
   LONG left_border   = m_YAxis.GetThickness(hDC) + out_height/100;
   LONG top_border    = m_SubtitleLoc + subtitle_size/2 - m_OutputRect.top;
   LONG right_border  = (LONG)(m_RightBorderFraction * out_width);

   // Setup legend area
   m_LegendRect.left = m_OutputRect.left + left_border;
   m_LegendRect.right = m_OutputRect.right - right_border;
   m_LegendRect.top = m_OutputRect.top + top_border;
   m_LegendRect.bottom = m_LegendRect.top;

   if ( m_bDrawLegend )
   {
      int nLegendItems = UpdateLegendMetrics(hDC);
      if ( nLegendItems == 0 )
      {
         m_nLegendCols = 0;
         m_nLegendRows = 1;
      }
      else
      {
         m_nLegendCols = max(1, (m_LegendRect.right - m_LegendRect.left)/m_LegendItemSize.cx);
         m_nLegendRows = max(1, (int)ceil((float)nLegendItems/(float)m_nLegendCols));
      } 

   //   assert( nLegendItems <= m_nLegendRows*m_nLegendCols );
      
      m_LegendRect.bottom = m_LegendRect.top + m_LegendItemSize.cy*m_nLegendRows;
   }

   // play some games here with case where rect is too small to draw the axis and the 
   // graph. If too small, then only draw curves.
   RECT device_client_rect;

   // There was a bug with setting null or reverse graph orientations. 
   // Let's make sure we use what we test in the if block below
   int rleft = m_OutputRect.left + left_border;
   int rtop = 11*m_LegendRect.bottom/10;
   int rright = m_OutputRect.right  - right_border;
   int rbottom = m_OutputRect.bottom - bottom_border;

   if (rleft < rright && rbottom > rtop )
   {
      // axis' fit - draw them
      m_DoDrawAxis = true;

      ::SetRect(&device_client_rect, rleft, rtop, rright, rbottom); 

      // place x and y axis' on screen
      m_XAxis.SetOrientation(AxisXY::AxisOrientation::X, device_client_rect.left, device_client_rect.right, device_client_rect.bottom);
      m_YAxis.SetOrientation(AxisXY::AxisOrientation::Y, device_client_rect.bottom, device_client_rect.top, device_client_rect.left);
   }
   else
   {
      // axis's don't fit - only draw curve to full window extents
      m_DoDrawAxis = false;

      device_client_rect = m_OutputRect;
      device_client_rect.top = 11*m_LegendRect.bottom/10;
   }

   // set up point mapper
   m_PointMapper.SetWorldExt( world_client_rect.Size() );
   m_PointMapper.SetWorldOrg( world_client_rect.Center() );
   
   LONG width = device_client_rect.right - device_client_rect.left;
   LONG height = device_client_rect.bottom - device_client_rect.top;

   m_PointMapper.SetDeviceExt(width,height);

   POINT center;
   center.x = device_client_rect.left + width/2;
   center.y = device_client_rect.top + height/2;
   m_PointMapper.SetDeviceOrg( center.x, center.y );
}

void GraphXY::DrawCurve(HDC hDC)
{
   AxisXY::AxisScale scaleX = m_XAxis.GetScale();
   AxisXY::AxisScale scaleY = m_YAxis.GetScale();

   // draw curve in color
   for(const auto& graphDataRecord : m_GraphDataMap)
   {
      const GraphData& gd = graphDataRecord.second;

      LOGBRUSH logBrush;
      logBrush.lbColor = gd.Pen.Color;
      logBrush.lbStyle = BS_SOLID;
      logBrush.lbHatch = 0; // not used because lbStyle is BS_SOLID

      HPEN hPen = ::ExtCreatePen(PS_GEOMETRIC | gd.Pen.Style, gd.Pen.Width, &logBrush, 0, nullptr);
      HGDIOBJ hOldPen = ::SelectObject(hDC,hPen);

      const DataSeries& ds = gd.Series;
      auto p_points = std::make_unique<POINT[]>(ds.size());

      Int16 count = 0;
      for(auto p : gd.Series)
      {
         if ( scaleX == AxisXY::AxisScale::Integral )
         {
            p.X() = count+1;
         }

         if ( scaleY == AxisXY::AxisScale::Integral )
         {
            p.Y() = count+1;
         }

         POINT dp;
         m_PointMapper.WPtoDP( scaleX == AxisXY::AxisScale::Linear || scaleX == AxisXY::AxisScale::Integral ? p.X() : log10(p.X()),
                               scaleY == AxisXY::AxisScale::Linear || scaleY == AxisXY::AxisScale::Integral ? p.Y() : log10(p.Y()),
                               &dp.x, &dp.y );

         p_points[count++] = dp;
      }

      ::Polyline(hDC, p_points.get(), count);

      ::SelectObject(hDC,hOldPen);
      ::DeleteObject(hPen);
   }
}

void GraphXY::DrawAxes(HDC hDC)
{
   // first deal with grid lines. then draw axes
   HPEN my_hpen = CreatePen(m_GridPenData.Style,m_GridPenData.Width,m_GridPenData.Color);
   HGDIOBJ old_hpen = ::SelectObject(hDC, my_hpen );

   Float64 left_val, right_val, x_increment;
   m_XAxis.GetAxisRange(&left_val, &right_val, &x_increment);
   Float64 bot_val, top_val, y_increment;
   m_YAxis.GetAxisRange(&bot_val, &top_val, &y_increment);

   AxisXY::AxisScale scaleX = m_XAxis.GetScale();
   AxisXY::AxisScale scaleY = m_YAxis.GetScale();

   if ( scaleX == AxisXY::AxisScale::Logarithmic )
   {
      x_increment = floor(pow(10.0,left_val))/10.0;
   }

   if ( scaleY == AxisXY::AxisScale::Logarithmic )
   {
      y_increment = floor(pow(10.0,bot_val))/10.0;
   }

   if (m_DoDrawGrid)
   {
      // draw a grid along major x and y tic lines

      // x axis grid
      LONG   ldx, ldy, rdx, rdy;
      Float64 curr_val;
      if ( scaleX == AxisXY::AxisScale::Linear || scaleX == AxisXY::AxisScale::Integral )
      {
         curr_val = left_val + x_increment;
      }
      else
      {
         curr_val = x_increment;
      }

      while ( ::IsLE(curr_val,right_val) )
      {
         m_PointMapper.WPtoDP(scaleX == AxisXY::AxisScale::Linear || scaleX == AxisXY::AxisScale::Integral? curr_val : log10(curr_val), scaleY == AxisXY::AxisScale::Linear || scaleY == AxisXY::AxisScale::Integral? bot_val : log10(bot_val), &ldx, &ldy);
         m_PointMapper.WPtoDP(scaleX == AxisXY::AxisScale::Linear || scaleX == AxisXY::AxisScale::Integral? curr_val : log10(curr_val), scaleY == AxisXY::AxisScale::Linear || scaleY == AxisXY::AxisScale::Integral? top_val : log10(top_val), &rdx, &rdy);

         POINT pnt;
         ::MoveToEx(hDC,ldx,ldy,&pnt);
         ::LineTo(hDC,rdx,rdy);

         if ( scaleX == AxisXY::AxisScale::Linear || scaleX == AxisXY::AxisScale::Integral )
         {
            curr_val += x_increment;
         }
         else
         {
            curr_val = pow(10,x_increment);
            x_increment += 1.0;
         }
      }

      // y axis grid
      if ( scaleY == AxisXY::AxisScale::Linear || scaleY == AxisXY::AxisScale::Integral)
      {
         curr_val = bot_val + y_increment;
      }
      else
      {
         curr_val = y_increment;
      }

      while ( ::IsLE(curr_val,top_val) )
      {
         m_PointMapper.WPtoDP(scaleX == AxisXY::AxisScale::Linear || scaleX == AxisXY::AxisScale::Integral ? left_val  : log10(left_val),  scaleY == AxisXY::AxisScale::Linear || scaleY == AxisXY::AxisScale::Integral ? curr_val : log10(curr_val), &ldx, &ldy);
         m_PointMapper.WPtoDP(scaleX == AxisXY::AxisScale::Linear || scaleX == AxisXY::AxisScale::Integral ? right_val : log10(right_val), scaleY == AxisXY::AxisScale::Linear || scaleY == AxisXY::AxisScale::Integral ? curr_val : log10(curr_val), &rdx, &rdy);

         POINT pnt;
         ::MoveToEx(hDC, ldx,ldy,&pnt);
         ::LineTo(hDC,rdx,rdy);

         if ( scaleY == AxisXY::AxisScale::Linear || scaleY == AxisXY::AxisScale::Integral )
         {
            curr_val += y_increment;
         }
         else
         {
            curr_val = pow(10,y_increment);
            y_increment += 1.0;
         }
      }
   }

   if(m_bHorizontalControlLine || !m_DoDrawGrid)
   {
      // don't draw grid, but do draw a horizontal line along Y=0
      if ( (0 <= top_val && bot_val <= 0) || (top_val <= 0 && 0 <= bot_val))
      {
         LONG   ldx, ldy, rdx, rdy;

         m_PointMapper.WPtoDP(scaleX == AxisXY::AxisScale::Linear || scaleX == AxisXY::AxisScale::Integral ? left_val  : log10(left_val),  0., &ldx, &ldy);
         m_PointMapper.WPtoDP(scaleX == AxisXY::AxisScale::Linear || scaleX == AxisXY::AxisScale::Integral ? right_val : log10(right_val), 0., &rdx, &rdy);

         HPEN controlLinePen = CreatePen(m_HorzControlLinePenData.Style, m_HorzControlLinePenData.Width, m_HorzControlLinePenData.Color);
         HPEN lastPen = (HPEN)::SelectObject(hDC, controlLinePen);

         POINT pnt;
         ::MoveToEx(hDC,ldx,ldy,&pnt);
         ::LineTo(hDC,rdx,rdy);

         ::SelectObject(hDC, lastPen);
      }
   }
   ::SelectObject(hDC, old_hpen);
   ::DeleteObject(my_hpen);

   m_YAxis.Draw(hDC);
   m_XAxis.Draw(hDC);
}

void GraphXY::DrawLegend(HDC hDC)
{
   UINT textAlign = ::SetTextAlign(hDC,TA_TOP | TA_LEFT);

   if (m_LegendBorderStyle==Style::Boundary)
   {
      // bound entire legend rect
      ::Rectangle(hDC,m_LegendRect.left,m_LegendRect.top,m_LegendRect.right,m_LegendRect.bottom);
   }

   // draw the data labels
   int i = 0;
   int row = 0;
   int col = 0;
   GraphDataMap::iterator map_iter;
   for ( map_iter = m_GraphDataMap.begin(); map_iter != m_GraphDataMap.end(); map_iter++ )
   {
      GraphData& gd = (*map_iter).second;

      // if there is no data, skip the data label
      if ( gd.Series.size() == 0 || gd.Label.length() == 0 )
      {
         continue;
      }

      int x = m_LegendRect.left + col*m_LegendItemSize.cx;
      int y = m_LegendRect.top  + row*m_LegendItemSize.cy;

      if (m_LegendBorderStyle==Style::Checker)
      {
         // Draw a cell for each individual legend item
         ::Rectangle(hDC,x,y,x+m_LegendItemSize.cx,y+m_LegendItemSize.cy);
      }

      // draw the line symbol
      LOGBRUSH logBrush;
      logBrush.lbColor = gd.Pen.Color;
      logBrush.lbStyle = BS_SOLID;
      logBrush.lbHatch = 0; // not used because lbStyle is BS_SOLID

      HPEN hPen = ::ExtCreatePen(PS_GEOMETRIC | gd.Pen.Style, gd.Pen.Width, &logBrush, 0, nullptr);
      HGDIOBJ old_pen = ::SelectObject(hDC,hPen);

      POINT last_point;
      ::MoveToEx(hDC,x+m_LegendBorder,y+m_LegendItemSize.cy/2,&last_point);
      ::LineTo(hDC,x+m_LegendBorder+m_LegendSymbolLength,y+m_LegendItemSize.cy/2);

      ::SelectObject(hDC,old_pen);
      ::DeleteObject(hPen);

      SIZE text_size;
      ::GetTextExtentPoint32(hDC,gd.Label.c_str(),(LONG)gd.Label.length(),&text_size);

      GraphTool::TextOutRotated(hDC, x+2*m_LegendBorder+m_LegendSymbolLength, y + text_size.cy/2, 0,
                                 gd.Label.c_str(),(LONG)gd.Label.length(),
                                 m_LegendFontSize);

      col++;

      if ( m_nLegendCols <= col )
      {
         col = 0;
         row++;
      }
   }


   ::SetTextAlign(hDC,textAlign);
}

LONG GraphXY::GetXAxisNumberOfMajorTics() const
{
   return m_XAxis.GetNumberOfMajorTics();
}

void GraphXY::SetXAxisNumberOfMajorTics(LONG num)
{
   m_XAxis.SetNumberOfMajorTics(num);
}

LONG GraphXY::GetYAxisNumberOfMajorTics() const
{
   return m_YAxis.GetNumberOfMajorTics();
}

void GraphXY::SetYAxisNumberOfMajorTics(LONG num)
{
   m_YAxis.SetNumberOfMajorTics(num);
}

bool GraphXY::XAxisNiceRange() const
{
   return m_XAxisNiceRange;
}

void GraphXY::XAxisNiceRange(bool nice)
{
   m_XAxisNiceRange = nice;
   m_XAxisRangeForced = false;

   if ( m_XAxisNiceRange && m_XAxis.GetScale() == AxisXY::AxisScale::Integral )
   {
      m_XAxis.SetScale(AxisXY::AxisScale::Linear); // can't have nice range and INTEGRAL
   }
}

void GraphXY::SetXAxisForcedRange(Float64 leftVal, Float64 rightVal, Float64 increment)
{
   m_XAxisNiceRange = false;
   m_XAxisRangeForced = true;
   m_XAxis.SetForcedAxisRange(leftVal,rightVal,increment);
}

bool GraphXY::IsXAxisRangeForced() const
{
   return m_XAxisRangeForced;
}

bool GraphXY::YAxisNiceRange() const
{
   return m_YAxisNiceRange;
}

void GraphXY::YAxisNiceRange(bool nice)
{
   m_YAxisNiceRange = nice;

   if ( m_YAxisNiceRange && m_YAxis.GetScale() == AxisXY::AxisScale::Integral )
   {
      m_YAxis.SetScale(AxisXY::AxisScale::Linear); // can't have nice range and INTEGRAL
   }
}

bool GraphXY::PinYAxisAtZero() const
{
   return m_PinYAxisAtZero;
}

void GraphXY::PinYAxisAtZero(bool pin)
{
   m_PinYAxisAtZero = pin;
}

void GraphXY::IsotropicAxes(bool bIsotropic)
{
   m_bIsotropicAxes = bIsotropic;
}

bool GraphXY::IsotropicAxes() const
{
   return m_bIsotropicAxes;
}

void GraphXY::HorizontalControlLine(bool set)
{
   m_bHorizontalControlLine = set;
}

bool GraphXY::HorizontalControlLine() const
{
   return m_bHorizontalControlLine;
}

int GraphXY::UpdateLegendMetrics(HDC hDC)
{
   int dpi = ::GetDeviceCaps(hDC,LOGPIXELSX);
   m_LegendBorder = dpi/32; // 1/16" border
   m_LegendSymbolLength = dpi/3; // 1/2" symbol

   HFONT font = GraphTool::CreateRotatedFont(hDC, 0, m_LegendFontSize);
   HGDIOBJ old_font = ::SelectObject(hDC, font);

   int nItems = 0;
   int cx = 0;
   int cy = 0;
   GraphDataMap::iterator map_iter;
   for ( map_iter = m_GraphDataMap.begin(); map_iter != m_GraphDataMap.end(); map_iter++ )
   {
      GraphData& gd = (*map_iter).second;
      if ( 0 < gd.Label.length() && 0 < gd.Series.size() )
      {
         nItems++;

         SIZE item_size;
         ::GetTextExtentPoint32(hDC,gd.Label.c_str(),(LONG)gd.Label.length(),&item_size);

         cx = max(cx,item_size.cx);
         cy = max(cy,item_size.cy);
      }
   }

   // clean up fonts
   ::SelectObject(hDC, old_font);
   ::DeleteObject(font);

   m_LegendItemSize.cx = cx + 3*m_LegendBorder + m_LegendSymbolLength;
   m_LegendItemSize.cy = cy + 2*m_LegendBorder;

   return nItems;
}
