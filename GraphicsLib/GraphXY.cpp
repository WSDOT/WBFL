///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
// Copyright © 1999-2015  Washington State Department of Transportation
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

#include <GraphicsLib\GraphicsLibLib.h>
#include <MathEx.h>
#include <GraphicsLib\GraphXY.h>
#include <float.h>
#include <algorithm>
#include <GraphicsLib\GraphTool.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   grGraphXY
****************************************************************************/
static const Float64 DEFAULT_ZOOM=1.0e-06;

// Predicate function object used for sorting points based on their
// X coordinate.
class PointSorter
{
public:
   bool operator()(const gpPoint2d& p1, const gpPoint2d& p2) const;
};

bool PointSorter::operator()(const gpPoint2d& p1,const gpPoint2d& p2) const
{
   return p1.X() < p2.X();
}

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
grGraphXY::grGraphXY(sysNumericFormatTool& rXAxisFormat, sysNumericFormatTool& rYAxisFormat) :
m_WorldRect( DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX ),
m_XAxis(grAxisXY::X_AXIS, rXAxisFormat),
m_YAxis(grAxisXY::Y_AXIS, rYAxisFormat),
m_GraphTitleSize(14),
m_GraphSubtitleSize(10),
m_LegendFontSize(8),
m_ClientAreaColor(RGB(240,240,240)),
m_DoDrawAxis(true),
m_DoDrawGrid(true),
m_bDrawLegend(true),
m_LegendBoarderType(lbCheckerBoarder),
m_XAxisNiceRange(true),
m_YAxisNiceRange(true),
m_PinYAxisAtZero(true),
m_bIsotropicAxes(false),
m_MinZoomHeight(DEFAULT_ZOOM),
m_MinZoomWidth(DEFAULT_ZOOM),
m_Xmin(0),
m_Xmax(1),
m_Ymin(0),
m_Ymax(1)
{
   // set up the x axis
   m_XAxis.SetNumberOfMinorTics(5);
   m_XAxis.SetTicLocation(grAxisXY::TIC_ABOVE);
   m_YAxis.SetTextLocation(grAxisXY::TEXT_BELOW);

   // set up the y axis
   m_YAxis.SetTicLocation(grAxisXY::TIC_BELOW);
   m_YAxis.SetTextLocation(grAxisXY::TEXT_ABOVE);
   m_YAxis.SetNumberOfMinorTics(5);

   m_GridPenData.Style = PS_SOLID;
   m_GridPenData.Color = RGB(0,0,0);
   m_GridPenData.Width = 1;
}

grGraphXY::~grGraphXY()
{
}

//======================== OPERATORS  =======================================
grGraphXY& grGraphXY::operator= (const grGraphXY& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
IndexType grGraphXY::CreateDataSeries()
{
   return CreateDataSeries(_T(""),PS_SOLID,1,RGB(0,0,0));
}

IndexType grGraphXY::CreateDataSeries(LPCTSTR lpszLabel,int nPenStyle, int nWidth, COLORREF crColor)
{
   IndexType cookie = m_GraphDataMap.size();

   GraphData gd;
   gd.Label = lpszLabel;
   gd.Pen.Color = crColor;
   gd.Pen.Width = nWidth;
   gd.Pen.Style = nPenStyle;
   m_GraphDataMap.insert(std::make_pair(cookie,gd));
   return cookie;
}

void grGraphXY::AddPoint(IndexType cookie,const gpPoint2d& rPoint)
{
   GraphDataMap::iterator found = m_GraphDataMap.find(cookie);
   if ( found != m_GraphDataMap.end() )
   {
      GraphData& gd = (*found).second;
      gd.Series.push_back(rPoint);
      SetBroken();
   }
}

void grGraphXY::AddPoints(IndexType cookie,const std::vector<gpPoint2d>& vPoints)
{
   GraphDataMap::iterator found = m_GraphDataMap.find(cookie);
   if ( found != m_GraphDataMap.end() )
   {
      GraphData& gd = (*found).second;
      gd.Series.insert(gd.Series.end(),vPoints.begin(),vPoints.end());
      SetBroken();
   }
}

void grGraphXY::ClearPoints(IndexType cookie)
{
   GraphDataMap::iterator found = m_GraphDataMap.find(cookie);
   if ( found != m_GraphDataMap.end() )
   {
      GraphData& gd = (*found).second;
      gd.Series.clear();
      SetBroken();
   }
}

void grGraphXY::ClearData()
{
   m_GraphDataMap.clear();
}


IndexType grGraphXY::GetPointCount(IndexType cookie) const
{
   GraphDataMap::const_iterator found = m_GraphDataMap.find(cookie);
   if ( found != m_GraphDataMap.end() )
   {
      const GraphData& gd = (*found).second;
      return gd.Series.size();
   }

   return 0;
}

void grGraphXY::RemoveDataSeries(IndexType cookie)
{
   m_GraphDataMap.erase( cookie );
   SetBroken();
}

IndexType grGraphXY::GetDataSeriesCount() const
{
   return m_GraphDataMap.size();
}

void grGraphXY::SetOutputRect(const RECT& rOutputRect)
{
   m_OutputRect = rOutputRect;
   SetBroken();
}

RECT grGraphXY::GetOutputRect() const
{
   return m_OutputRect;
}

void grGraphXY::Draw(HDC hDC)
{
   UpdateGraphMetrics(hDC);
   DrawBackground( hDC );
   DrawDataSeries( hDC );

}

void grGraphXY::DrawBackground(HDC hDC)
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
	::ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &c_rect, NULL, 0, NULL);
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

   grGraphTool::TextOutRotated(hDC, tx, m_TitleLoc, 0,
                      m_GraphTitle.c_str(), (LONG)m_GraphTitle.size(),
                      m_GraphTitleSize);

   grGraphTool::TextOutRotated(hDC, tx, m_SubtitleLoc, 0,
                      m_GraphSubtitle.c_str(), (LONG)m_GraphSubtitle.size(),
                      m_GraphSubtitleSize);
}

void grGraphXY::DrawDataSeries(HDC hDC)
{
   DrawCurve( hDC );
}

//======================== ACCESS     =======================================

LPCTSTR grGraphXY::GetTitle() const
{
   return m_GraphTitle.c_str();
}

void grGraphXY::SetTitle(LPCTSTR strTitle)
{
   m_GraphTitle = strTitle;
}

LONG grGraphXY::GetTitleSize() const
{
   return m_GraphTitleSize;
}

void grGraphXY::SetTitleSize(LONG size)
{
   m_GraphTitleSize = size;
}

LPCTSTR grGraphXY::GetSubtitle() const
{
   return m_GraphSubtitle.c_str();
}

void grGraphXY::SetSubtitle(LPCTSTR strSubtitle)
{
    m_GraphSubtitle = strSubtitle;
}

LONG grGraphXY::GetSubtitleSize() const
{
   return m_GraphSubtitleSize;
}

void grGraphXY::SetSubtitleSize(LONG size)
{
   m_GraphSubtitleSize = size;
}

void grGraphXY::SetAxisTitleSize(LONG size)
{
   m_XAxis.SetTitleFontSize(size);
   m_YAxis.SetTitleFontSize(size);
}

LONG grGraphXY::GetAxisTitleSize() const
{
   return m_XAxis.GetTitleFontSize();
}

void grGraphXY::SetAxisSubtitleSize(LONG size)
{
   m_XAxis.SetSubtitleFontSize(size);
   m_YAxis.SetSubtitleFontSize(size);
}

LONG grGraphXY::GetAxisSubtitleSize() const
{
   return m_XAxis.GetSubtitleFontSize();
}

LONG grGraphXY::GetXAxisLabelAngle() const
{
   return m_XAxis.GetValueAngle();
}

void grGraphXY::SetXAxisLabelAngle(LONG angle)
{
   m_XAxis.SetValueAngle(angle);
}

LONG grGraphXY::GetYAxisLabelAngle() const
{
   return m_YAxis.GetValueAngle();
}

void grGraphXY::SetYAxisLabelAngle(LONG angle)
{
   m_YAxis.SetValueAngle(angle);
}

void grGraphXY::SetXAxisTitle(LPCTSTR strTitle)
{
   m_XAxis.SetTitleText(strTitle);
}

LPCTSTR grGraphXY::GetXAxisTitle() const
{
   return m_XAxis.GetTitleText();
}

void grGraphXY::SetXAxisSubtitle(LPCTSTR strSubtitle)
{
   m_XAxis.SetSubtitleText(strSubtitle);
}

LPCTSTR grGraphXY::GetXAxisSubtitle() const
{
   return m_XAxis.GetSubtitleText();
}

void grGraphXY::SetYAxisTitle(LPCTSTR strTitle)
{
   m_YAxis.SetTitleText(strTitle);
}

LPCTSTR grGraphXY::GetYAxisTitle() const
{
   return m_YAxis.GetTitleText();
}

void grGraphXY::SetYAxisSubtitle(LPCTSTR strSubtitle)
{
   m_YAxis.SetSubtitleText(strSubtitle);

}

LPCTSTR grGraphXY::GetYAxisSubtitle() const
{
   return m_YAxis.GetSubtitleText();
}

LONG grGraphXY::GetXAxisNumberOfMinorTics() const
{
   return m_XAxis.GetNumberOfMinorTics();
}

void grGraphXY::SetXAxisNumberOfMinorTics(LONG num)
{
   m_XAxis.SetNumberOfMinorTics(num);
}

LONG grGraphXY::GetYAxisNumberOfMinorTics() const
{
   return m_YAxis.GetNumberOfMinorTics();
}

void grGraphXY::SetYAxisNumberOfMinorTics(LONG num)
{
   m_YAxis.SetNumberOfMinorTics(num);
}

void grGraphXY::SetXAxisValueFormat(sysNumericFormatTool& format)
{
   m_XAxis.SetValueFormat(format);
}

const sysNumericFormatTool* grGraphXY::GetXAxisValueFormat() const
{
   return  m_XAxis.GetValueFormat();
}

void grGraphXY::SetXAxisScale(grAxisXY::AxisScale scale)
{
   m_XAxis.SetScale(scale);
   if ( m_XAxis.GetScale() == grAxisXY::INTEGRAL )
   {
      m_XAxisNiceRange = false; // can't have nice range with INTEGRAL
   }
}

grAxisXY::AxisScale grGraphXY::GetXAxisScale() const
{
   return m_XAxis.GetScale();
}

void grGraphXY::SetYAxisScale(grAxisXY::AxisScale scale)
{
   m_YAxis.SetScale(scale);
   if ( m_YAxis.GetScale() == grAxisXY::INTEGRAL )
   {
      m_YAxisNiceRange = false; // can't have nice range with INTEGRAL
   }
}

grAxisXY::AxisScale grGraphXY::GetYAxisScale() const
{
   return m_YAxis.GetScale();
}

void grGraphXY::SetYAxisValueFormat(sysNumericFormatTool& format)
{
   m_YAxis.SetValueFormat(format);
}

const sysNumericFormatTool* grGraphXY::GetYAxisValueFormat() const
{
   return  m_YAxis.GetValueFormat();
}

void grGraphXY::SetPenStyle(IndexType cookie, int nPenStyle, int nWidth, COLORREF crColor)
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

void grGraphXY::SetGridPenStyle(int nPenStyle, int nWidth, COLORREF crColor)
{
   m_GridPenData.Style = nPenStyle;
   m_GridPenData.Color = crColor;
   m_GridPenData.Width = nWidth;
}

void grGraphXY::SetDataLabel(IndexType cookie,LPCTSTR lpszLabel)
{
   GraphDataMap::iterator found = m_GraphDataMap.find(cookie);
   if ( found != m_GraphDataMap.end() )
   {
      GraphData& gd = (*found).second;
      gd.Label = lpszLabel;
   }
}

void grGraphXY::GetMinimumZoomBounds(Float64* pHeight, Float64* pWidth) const
{
   *pHeight = m_MinZoomHeight;
   *pWidth  = m_MinZoomWidth;
}

void grGraphXY::SetMinimumZoomBounds(Float64 Height, Float64 Width)
{
   CHECK(Height>0); // this will cause numeric problems
   CHECK(Width>0); // this will cause numeric problems

   m_MinZoomHeight = Height;
   m_MinZoomWidth  = Width;
}

void grGraphXY::SetMinimumSize(Float64 Xmin,Float64 Xmax,Float64 Ymin,Float64 Ymax)
{
   m_Xmin = Xmin;
   m_Xmax = Xmax;
   m_Ymin = Ymin;
   m_Ymax = Ymax;
}

void grGraphXY::GetMinimumSize(Float64* pXmin,Float64* pXmax,Float64* pYmin,Float64* pYmax) const
{
   *pXmin = m_Xmin;
   *pXmax = m_Xmax;
   *pYmin = m_Ymin;
   *pYmax = m_Ymax;
}

void grGraphXY::SetLegendBoarderStyle(LegendBoarderType type)
{
   m_LegendBoarderType = type;
}

grGraphXY::LegendBoarderType grGraphXY::GetLegendBoarderStyle() const
{
   return m_LegendBoarderType;
}

//======================== INQUIRY    =======================================

const grlibPointMapper& grGraphXY::GetClientAreaPointMapper(HDC hDC)
{
   // set up the graph layout
   UpdateGraphMetrics(hDC);

   return m_PointMapper;
}


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void grGraphXY::MakeCopy(const grGraphXY& rOther)
{
   m_GraphDataMap  = rOther.m_GraphDataMap;
   m_WorldRect     = rOther.m_WorldRect;
   m_OutputRect    = rOther.m_OutputRect;

   m_PointMapper = rOther.m_PointMapper;
   m_IsBroken    = rOther.m_IsBroken;
   m_DoDrawAxis  = rOther.m_DoDrawAxis;
   m_DoDrawGrid  = rOther.m_DoDrawGrid;
   m_bDrawLegend = rOther.m_bDrawLegend;

   m_GraphTitle         = rOther.m_GraphTitle;
   m_GraphTitleSize     = rOther.m_GraphTitleSize;
   m_GraphSubtitle      = rOther.m_GraphSubtitle;
   m_GraphSubtitleSize  = rOther.m_GraphSubtitleSize;

   m_XAxis = rOther.m_XAxis;
   m_YAxis = rOther.m_YAxis;
   m_XAxisNiceRange = rOther.m_XAxisNiceRange;
   m_YAxisNiceRange = rOther.m_YAxisNiceRange;
   m_GridPenData    = rOther.m_GridPenData;

   m_ClientAreaColor = rOther.m_ClientAreaColor;

   m_MinZoomHeight = rOther.m_MinZoomHeight;
   m_MinZoomWidth  = rOther.m_MinZoomWidth;

   m_Xmin = rOther.m_Xmin;
   m_Xmax = rOther.m_Xmax;
   m_Ymin = rOther.m_Ymin;
   m_Ymax = rOther.m_Ymax;
}

void grGraphXY::MakeAssignment(const grGraphXY& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void grGraphXY::UpdateGraphMetrics(HDC hDC)
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
         gpPoint2d& p = *dataSeriesIter;
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
      m_WorldRect.Left()   = m_XAxis.GetScale() == grAxisXY::LINEAR ? 0.0 : 0.1;
      m_WorldRect.Right()  = 1.0;
      m_WorldRect.Top()    = m_YAxis.GetScale() == grAxisXY::LINEAR ? 0.0 : 0.1;
      m_WorldRect.Bottom() = 1.0;
   }

   // make sure zero is in Y range if requested
   if (m_PinYAxisAtZero && m_YAxis.GetScale() == grAxisXY::LINEAR)
   {
      gpPoint2d pnt((m_WorldRect.Left()+m_WorldRect.Right())/2., 0.0);
      m_WorldRect.BoundPoint(pnt);
   }

   // make sure that graph ranges are at least equal to the min zoom height and width.
   if (m_WorldRect.Height()< m_MinZoomHeight)
   {
      Float64 cen = (m_WorldRect.Top() + m_WorldRect.Bottom())/2.0;
      m_WorldRect.Top()    = cen + m_MinZoomHeight/2.0;
      m_WorldRect.Bottom() = cen - m_MinZoomHeight/2.0;
   }

   if (m_WorldRect.Width()< m_MinZoomWidth)
   {
      Float64 cen = (m_WorldRect.Right() + m_WorldRect.Left())/2.0;
      m_WorldRect.Right() = cen + m_MinZoomWidth/2.0;
      m_WorldRect.Left()  = cen - m_MinZoomWidth/2.0;
   }

   if ( m_XAxis.GetScale() != grAxisXY::LOGARITHMIC )
   {
      m_WorldRect.Left()   = min(m_WorldRect.Left(),  m_Xmin);
      m_WorldRect.Right()  = max(m_WorldRect.Right(), m_Xmax);
   }

   if ( m_YAxis.GetScale() != grAxisXY::LOGARITHMIC )
   {
      m_WorldRect.Top()    = max(m_WorldRect.Top(),   m_Ymax);
      m_WorldRect.Bottom() = min(m_WorldRect.Bottom(),m_Ymin);
   }

   if ( m_bIsotropicAxes )
   {
      Float64 width = m_WorldRect.Width();
      Float64 height = m_WorldRect.Height();
      gpPoint2d center = m_WorldRect.Center();
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
   if ( m_XAxis.GetScale() == grAxisXY::INTEGRAL )
   {
      client_left = 1;
      inc = 1;
      client_right = max(client_left+inc,(Float64)nMaxDataPoints);
      m_XAxis.SetForcedAxisRange(client_left,client_right,inc);
   }
   else
   {
      if (GetXAxisNiceRange())
      {
         m_XAxis.SetNiceAxisRange(m_WorldRect.Left(), m_WorldRect.Right(),false);
         m_XAxis.GetAxisRange(client_left, client_right, inc);
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

   if ( m_YAxis.GetScale() == grAxisXY::INTEGRAL )
   {
      client_bottom = 1;
      client_top = (Float64)nMaxDataPoints;
      inc = 1;
      m_YAxis.SetForcedAxisRange(client_top, client_bottom, inc);
   }
   else
   {
      if (GetYAxisNiceRange())
      {
         m_YAxis.SetNiceAxisRange(m_WorldRect.Bottom(), m_WorldRect.Top(),true);
         m_YAxis.GetAxisRange(client_bottom, client_top, inc);
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

   if ( m_XAxis.GetScale() == grAxisXY::LOGARITHMIC )
   {
      client_left  = log10(client_left);
      client_right = log10(client_right);
   }

   if ( m_YAxis.GetScale() == grAxisXY::LOGARITHMIC )
   {
      client_top    = log10(client_top);
      client_bottom = log10(client_bottom);
   }

   gpRect2d world_client_rect(client_left, client_bottom, client_right, client_top);

   // set up for title and subtitle

   // most metrics are based on font sizes. get sizes for title and subtitle
   HFONT title_font = grGraphTool::CreateRotatedFont(hDC, 0, m_GraphTitleSize);
   HGDIOBJ old_font = ::SelectObject(hDC, title_font);
   SIZE size;
   ::GetTextExtentPoint32(hDC,_T("AA"),2,&size);

   LONG title_size = labs(size.cy);

   HFONT subtitle_font = grGraphTool::CreateRotatedFont(hDC, 0, m_GraphSubtitleSize);
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
   int nLegendItems = UpdateLegendMetrics(hDC);
   m_LegendRect.left = m_OutputRect.left + left_border;
   m_LegendRect.right = m_OutputRect.right - right_border;
   m_LegendRect.top = m_OutputRect.top + top_border;

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
      m_XAxis.SetOrientation(grAxisXY::X_AXIS, device_client_rect.left, device_client_rect.right,
                            device_client_rect.bottom);
      m_YAxis.SetOrientation(grAxisXY::Y_AXIS, device_client_rect.bottom, device_client_rect.top,
                            device_client_rect.left);
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

   // ready to draw
   SetFixed();
}

void grGraphXY::DrawCurve(HDC hDC)
{
   grAxisXY::AxisScale scaleX = m_XAxis.GetScale();
   grAxisXY::AxisScale scaleY = m_YAxis.GetScale();

   // draw curve in color
   GraphDataMap::iterator map_iter;
   for ( map_iter = m_GraphDataMap.begin(); map_iter != m_GraphDataMap.end(); map_iter++ )
   {
      GraphData& gd = (*map_iter).second;

      LOGBRUSH logBrush;
      logBrush.lbColor = gd.Pen.Color;
      logBrush.lbStyle = BS_SOLID;
      logBrush.lbHatch = 0; // not used because lbStyle is BS_SOLID

      HPEN hPen = ::ExtCreatePen(PS_GEOMETRIC | gd.Pen.Style, gd.Pen.Width, &logBrush, 0, NULL);
      HGDIOBJ hOldPen = ::SelectObject(hDC,hPen);

      DataSeries& ds = gd.Series;
      POINT* p_points = new POINT[ ds.size() ];

      Int16 count = 0;
      DataSeries::iterator ds_iter;
      for ( ds_iter = gd.Series.begin(); ds_iter != gd.Series.end(); ds_iter++ )
      {
         gpPoint2d p = *ds_iter;
         if ( scaleX == grAxisXY::INTEGRAL )
         {
            p.X() = count+1;
         }

         if ( scaleY == grAxisXY::INTEGRAL )
         {
            p.Y() = count+1;
         }

         POINT dp;
         m_PointMapper.WPtoDP( scaleX == grAxisXY::LINEAR || scaleX == grAxisXY::INTEGRAL ? p.X() : log10(p.X()),
                               scaleY == grAxisXY::LINEAR || scaleY == grAxisXY::INTEGRAL ? p.Y() : log10(p.Y()),
                               &dp.x, &dp.y );

         p_points[count++] = dp;
      }

      ::Polyline(hDC, p_points, count );

      delete[] p_points;

      ::SelectObject(hDC,hOldPen);
      ::DeleteObject(hPen);
   }
}

void grGraphXY::DrawAxes(HDC hDC)
{
   // first deal with grid lines. then draw axes
   HPEN my_hpen = CreatePen(m_GridPenData.Style,m_GridPenData.Width,m_GridPenData.Color);
   HGDIOBJ old_hpen = ::SelectObject(hDC, my_hpen );

   Float64 left_val, right_val, x_increment;
   m_XAxis.GetAxisRange(left_val, right_val, x_increment);
   Float64 bot_val, top_val, y_increment;
   m_YAxis.GetAxisRange(bot_val, top_val, y_increment);

   grAxisXY::AxisScale scaleX = m_XAxis.GetScale();
   grAxisXY::AxisScale scaleY = m_YAxis.GetScale();

   if ( scaleX == grAxisXY::LOGARITHMIC )
   {
      x_increment = floor(pow(10.0,left_val))/10.0;
   }

   if ( scaleY == grAxisXY::LOGARITHMIC )
   {
      y_increment = floor(pow(10.0,bot_val))/10.0;
   }

   if (m_DoDrawGrid)
   {
      // draw a grid along major x and y tic lines

      // x axis grid
      LONG   ldx, ldy, rdx, rdy;
      Float64 curr_val;
      if ( scaleX == grAxisXY::LINEAR || scaleX == grAxisXY::INTEGRAL )
      {
         curr_val = left_val + x_increment;
      }
      else
      {
         curr_val = x_increment;
      }

      while ( ::IsLE(curr_val,right_val) )
      {
         m_PointMapper.WPtoDP(scaleX == grAxisXY::LINEAR || scaleX == grAxisXY::INTEGRAL? curr_val : log10(curr_val), scaleY == grAxisXY::LINEAR || scaleY == grAxisXY::INTEGRAL? bot_val : log10(bot_val), &ldx, &ldy);
         m_PointMapper.WPtoDP(scaleX == grAxisXY::LINEAR || scaleX == grAxisXY::INTEGRAL? curr_val : log10(curr_val), scaleY == grAxisXY::LINEAR || scaleY == grAxisXY::INTEGRAL? top_val : log10(top_val), &rdx, &rdy);

         POINT pnt;
         ::MoveToEx(hDC,ldx,ldy,&pnt);
         ::LineTo(hDC,rdx,rdy);

         if ( scaleX == grAxisXY::LINEAR || scaleX == grAxisXY::INTEGRAL )
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
      if ( scaleY == grAxisXY::LINEAR || scaleY == grAxisXY::INTEGRAL)
      {
         curr_val = bot_val + y_increment;
      }
      else
      {
         curr_val = y_increment;
      }

      while ( ::IsLE(curr_val,top_val) )
      {
         m_PointMapper.WPtoDP(scaleX == grAxisXY::LINEAR || scaleX == grAxisXY::INTEGRAL ? left_val  : log10(left_val),  scaleY == grAxisXY::LINEAR || scaleY == grAxisXY::INTEGRAL ? curr_val : log10(curr_val), &ldx, &ldy);
         m_PointMapper.WPtoDP(scaleX == grAxisXY::LINEAR || scaleX == grAxisXY::INTEGRAL ? right_val : log10(right_val), scaleY == grAxisXY::LINEAR || scaleY == grAxisXY::INTEGRAL ? curr_val : log10(curr_val), &rdx, &rdy);

         POINT pnt;
         ::MoveToEx(hDC, ldx,ldy,&pnt);
         ::LineTo(hDC,rdx,rdy);

         if ( scaleY == grAxisXY::LINEAR || scaleY == grAxisXY::INTEGRAL )
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
   else
   {
      // don't draw grid, but do draw a horizontal line along Y=0
      if ( (0 < top_val && bot_val < 0) || (top_val < 0 && 0 < bot_val))
      {
         LONG   ldx, ldy, rdx, rdy;

         m_PointMapper.WPtoDP(scaleX == grAxisXY::LINEAR || scaleX == grAxisXY::INTEGRAL ? left_val  : log10(left_val),  0., &ldx, &ldy);
         m_PointMapper.WPtoDP(scaleX == grAxisXY::LINEAR || scaleX == grAxisXY::INTEGRAL ? right_val : log10(right_val), 0., &rdx, &rdy);

         POINT pnt;
         ::MoveToEx(hDC,ldx,ldy,&pnt);
         ::LineTo(hDC,rdx,rdy);
      }
   }
   ::SelectObject(hDC, old_hpen);
   ::DeleteObject(my_hpen);

   m_YAxis.Draw(hDC);
   m_XAxis.Draw(hDC);
}

void grGraphXY::DrawLegend(HDC hDC)
{
   UINT textAlign = ::SetTextAlign(hDC,TA_TOP | TA_LEFT);

   if (m_LegendBoarderType==lbBoundary)
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

      if (m_LegendBoarderType==lbCheckerBoarder)
      {
         // Draw a cell for each individual legend item
         ::Rectangle(hDC,x,y,x+m_LegendItemSize.cx,y+m_LegendItemSize.cy);
      }

      // draw the line symbol
      LOGBRUSH logBrush;
      logBrush.lbColor = gd.Pen.Color;
      logBrush.lbStyle = BS_SOLID;
      logBrush.lbHatch = 0; // not used because lbStyle is BS_SOLID

      HPEN hPen = ::ExtCreatePen(PS_GEOMETRIC | gd.Pen.Style, gd.Pen.Width, &logBrush, 0, NULL);
      HGDIOBJ old_pen = ::SelectObject(hDC,hPen);

      POINT last_point;
      ::MoveToEx(hDC,x+m_LegendBorder,y+m_LegendItemSize.cy/2,&last_point);
      ::LineTo(hDC,x+m_LegendBorder+m_LegendSymbolLength,y+m_LegendItemSize.cy/2);

      ::SelectObject(hDC,old_pen);
      ::DeleteObject(hPen);

      SIZE text_size;
      ::GetTextExtentPoint32(hDC,gd.Label.c_str(),(LONG)gd.Label.length(),&text_size);

      grGraphTool::TextOutRotated(hDC, x+2*m_LegendBorder+m_LegendSymbolLength, y + text_size.cy/2, 0,
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

void grGraphXY::SetBroken()
{
   m_IsBroken = true;
}

void grGraphXY::SetFixed()
{
   m_IsBroken = false;
}

//======================== ACCESS     =======================================

LONG grGraphXY::GetXAxisNumberOfMajorTics() const
{
   return m_XAxis.GetNumberOfMajorTics();
}

void grGraphXY::SetXAxisNumberOfMajorTics(LONG num)
{
   m_XAxis.SetNumberOfMajorTics(num);
}

LONG grGraphXY::GetYAxisNumberOfMajorTics() const
{
   return m_YAxis.GetNumberOfMajorTics();
}

void grGraphXY::SetYAxisNumberOfMajorTics(LONG num)
{
   m_YAxis.SetNumberOfMajorTics(num);
}

bool grGraphXY::GetXAxisNiceRange() const
{
   return m_XAxisNiceRange;
}

void grGraphXY::SetXAxisNiceRange(bool nice)
{
   m_XAxisNiceRange = nice;

   if ( m_XAxisNiceRange && m_XAxis.GetScale() == grAxisXY::INTEGRAL )
   {
      m_XAxis.SetScale(grAxisXY::LINEAR); // can't have nice range and INTEGRAL
   }
}

bool grGraphXY::GetYAxisNiceRange() const
{
   return m_YAxisNiceRange;
}

void grGraphXY::SetYAxisNiceRange(bool nice)
{
   m_YAxisNiceRange = nice;

   if ( m_YAxisNiceRange && m_YAxis.GetScale() == grAxisXY::INTEGRAL )
   {
      m_YAxis.SetScale(grAxisXY::LINEAR); // can't have nice range and INTEGRAL
   }
}

bool grGraphXY::GetPinYAxisAtZero() const
{
   return m_PinYAxisAtZero;
}

void grGraphXY::SetPinYAxisAtZero(bool pin)
{
   m_PinYAxisAtZero = pin;
}

void grGraphXY::SetIsotropicAxes(bool bIsotropic)
{
   m_bIsotropicAxes = bIsotropic;
}

bool grGraphXY::GetIsotropicAxes() const
{
   return m_bIsotropicAxes;
}

int grGraphXY::UpdateLegendMetrics(HDC hDC)
{
   int dpi = ::GetDeviceCaps(hDC,LOGPIXELSX);
   m_LegendBorder = dpi/32; // 1/16" border
   m_LegendSymbolLength = dpi/3; // 1/2" symbol

   HFONT font = grGraphTool::CreateRotatedFont(hDC, 0, m_LegendFontSize);
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

//======================== INQUERY    =======================================
bool grGraphXY::IsBroken()
{
   return m_IsBroken;
}

const Float64 grGraphXY::m_RightBorderFraction = .05;


//======================== DEBUG      =======================================
#if defined _DEBUG
bool grGraphXY::AssertValid() const
{
   return true;
}

void grGraphXY::Dump(dbgDumpContext& os) const
{
   os << "Dump for grGraphXY" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool grGraphXY::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("grGraphXY");

   // tough class to test since it's graphical. must manually use a project.

   TESTME_EPILOG("grGraphXY");
}
#endif // _UNITTEST

