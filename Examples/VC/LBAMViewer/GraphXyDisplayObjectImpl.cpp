///////////////////////////////////////////////////////////////////////////////
// generic support draw routines to share between Supports and TemporarySupports

#include "stdafx.h"
#include "GraphXyDisplayObjectImpl.h"
#include "DataPointDrawStrategyImpl.h"
#include "DataPointEventsImpl.h"
#include "DataSet2dImpl.h"
#include "LegendEntryImpl.h"

#include <MathEx.h>
#include <Math\CoordMapper1d.h>
#include <FLOAT.H>
#include <system\NumericFormatTool.h>

#define TIC_SIZE 20

static void CalculateNiceRange(const Float64 originalMin, const Float64 originalMax,
   IndexType& numberOfSegments,
   Float64& niceMin, Float64& niceMax,
   Float64& niceIncrement)
{
   // this is a butt-ugly routine that was converted from fortran - excuse
   // the mess, but it works
   Float64 exponent, factor, scale_fac, test_scale, adjusted_min, adjusted_max;
   Int32  nmin, nmax, need;
   bool  is_defseg;

   const Float64  tol = 1.0e-09;
   const Int32 nscale = 9;
   const Float64 prturb = 1.1;
   const Float64 supply[nscale] = { 25.0, 20.0, 15.0, 10.0, 5.0, 2.5, 2.0, 1.0, 0.5 };

   niceMin = originalMin;
   niceMax = originalMax;

   //  may need to perturb values to make reasonable graph

   if (niceMin == niceMax)
   {
      if (niceMin == 0.0)
      {
         niceMax = 1.0;
      }
      else
      {
         niceMin = niceMin / prturb;
         niceMax = niceMax * prturb;
      }
   }
   else if (niceMax < niceMin)
   {
      Float64 temp = niceMin;
      niceMin = niceMax;
      niceMax = temp;
   }

   if (niceMax - niceMin <= tol)
   {
      niceMin -= tol;
      niceMax += tol;
   }

   //  set nseg to default if .lt. 1

   if (numberOfSegments < 1)
   {
      numberOfSegments = 6;
      is_defseg = true;
   }
   else
   {
      is_defseg = false;
   }

   //     get down to business

   exponent = floor(log10((niceMax - niceMin) / numberOfSegments));
   factor = pow(10.0, exponent);

   //     test each scale and keep the largest one that works

   for (IndexType i = 0; i < nscale; i++)
   {
      test_scale = factor * supply[i];
      nmin = (Int32)floor(niceMin / test_scale);
      nmax = (Int32)ceil(niceMax / test_scale);
      need = nmax - nmin;

      if (need <= (Int32)numberOfSegments)
      {
         scale_fac = test_scale;
         adjusted_min = nmin * scale_fac;
         adjusted_max = nmax * scale_fac;
      }
      else
      {
         continue;
      }
   }

   // try to 'shrink' the outer bounds if the original max or min only
   // slightly intrudes into the nice range.

   const Float64 range_tol = (niceMax - niceMin) / 300.; // could put this out to interface
   // if very precise graphing were needed.

   if (adjusted_max - scale_fac + range_tol > niceMax && need > 1)  // shrink upper range if original is
   {                                                            // only slightly above next band.
      adjusted_max -= scale_fac;
      need--;
   }

   if (adjusted_min + scale_fac - range_tol < niceMin && need>1)  // shrink lower range
   {
      adjusted_min += scale_fac;
      need--;
   }

   // return adjusted max and min

   numberOfSegments = need;
   niceIncrement = scale_fac;

   niceMin = adjusted_min;
   niceMax = adjusted_max;
}

/////////////////////////////////////////////////////////////////////////////
// GraphMapper
// handy class for mapping between world space and graph space
class GraphMapper
{
public:
   GraphMapper(Float64 worldLeft, Float64 worldRight, Float64 worldTop, Float64 worldBottom,
      Float64 graphLeft, Float64 graphRight, Float64 graphTop, Float64 graphBottom) :
      m_WorldLeft(worldLeft),
      m_WorldRight(worldRight),
      m_WorldTop(worldTop),
      m_WorldBottom(worldBottom),
      m_GraphLeft(graphLeft),
      m_GraphRight(graphRight),
      m_GraphTop(graphTop),
      m_GraphBottom(graphBottom)
   {
      // set up mappers
      m_xMapper.SetCoordinateMap(worldLeft, graphLeft, worldRight, graphRight);

      // make sure we have some y ordinate to work with
      Float64 grtop, grbottom;
      if (IsEqual(graphTop, graphBottom, 1.0e-16))
      {
         // graph ordinates are different.
         Float64 base = Round(graphTop);
         grtop = base + 1.0;
         grbottom = base - 1.0;
      }
      else
      {
         grtop = graphTop;
         grbottom = graphBottom;
      }

      m_yMapper.SetCoordinateMap(worldBottom, grbottom, worldTop, grtop);
   }

   // public data members
   Float64 m_WorldLeft;
   Float64 m_WorldRight;
   Float64 m_WorldTop;
   Float64 m_WorldBottom;
   Float64 m_GraphLeft;
   Float64 m_GraphRight;
   Float64 m_GraphTop;
   Float64 m_GraphBottom;

   // mapping functions
   Float64 GetWorldX(Float64 graphX)
   {
      return m_xMapper.GetA(graphX);
   }
   Float64 GetWorldY(Float64 graphY)
   {
      return m_yMapper.GetA(graphY);
   }
   Float64 GetGraphX(Float64 worldX)
   {
      return m_xMapper.GetB(worldX);
   }
   Float64 GetGraphY(Float64 worldY)
   {
      return m_yMapper.GetB(worldY);
   }
private:
   GraphMapper();
   WBFL::Math::CoordMapper1d m_xMapper;
   WBFL::Math::CoordMapper1d m_yMapper;
};

/////////////////////////////////////////////////////////////////////////////
// CGraphXyDisplayObject
CGraphXyDisplayObject::CGraphXyDisplayObject(IDType id) :
   iGraphXyDisplayObject(id),
   m_NumDos(0),
   m_DoDisplayAxisValues(VARIANT_TRUE),
   m_DoDisplayGrid(VARIANT_TRUE),
   m_NumberOfMajorIncrements(10)
{
}

WBFL::Geometry::Rect2d CGraphXyDisplayObject::GetGraphBounds()
{
   return m_GraphBounds;
}

void CGraphXyDisplayObject::SetGraphBounds(const WBFL::Geometry::Rect2d& newVal)
{
   m_GraphBounds = newVal;
}

std::_tstring CGraphXyDisplayObject::GetTitle()
{
   return m_Title;
}

void CGraphXyDisplayObject::SetTitle(const std::_tstring& title)
{
   m_Title = title;
}

IndexType CGraphXyDisplayObject::GetDataCount()
{
   return m_DataSets.size();
}

void CGraphXyDisplayObject::AddData(std::shared_ptr<iGraphXyDataProvider> dataSet)
{
   m_DataSets.push_back(dataSet);
}

std::shared_ptr<iGraphXyDataProvider> CGraphXyDisplayObject::GetData(IndexType idx)
{
   CHECK(0 <= idx && idx < m_DataSets.size());
   return m_DataSets[idx];
}

void CGraphXyDisplayObject::RebuildDisplayObjects()
{
   // first remove display objects
   ClearDisplayObjects();

   // make sure we have some data and a rectangle to draw in
   Float64 gb_top = m_GraphBounds.Top();
   Float64 gb_bottom = m_GraphBounds.Bottom();
   Float64 gb_right = m_GraphBounds.Right();
   Float64 gb_left = m_GraphBounds.Left();

   if (gb_top - gb_bottom <= 0 || gb_right - gb_left <= 0)
   {
      // no canvas on which to draw
      CHECK(false);
      return;
   }

   // draw data curves
   DrawGraph(gb_top, gb_left, gb_right, gb_bottom);
}

void CGraphXyDisplayObject::DrawAxis(GraphMapper& mapper)
{
   // outline
   DrawAxisLine(mapper.m_WorldLeft, mapper.m_WorldBottom, mapper.m_WorldLeft, mapper.m_WorldTop);

   DrawAxisLine(mapper.m_WorldLeft, mapper.m_WorldBottom, mapper.m_WorldRight, mapper.m_WorldBottom);

   DrawAxisLine(mapper.m_WorldRight, mapper.m_WorldBottom, mapper.m_WorldRight, mapper.m_WorldTop);

   DrawAxisLine(mapper.m_WorldLeft, mapper.m_WorldTop, mapper.m_WorldRight, mapper.m_WorldTop);

   // zero lines if needed
   if (mapper.m_GraphBottom < 0.0 && mapper.m_GraphTop>0.0)
   {
      Float64 wz = mapper.GetWorldY(0.0);
      DrawAxisLine(mapper.m_WorldLeft, wz, mapper.m_WorldRight, wz, 3);
   }

   if (mapper.m_GraphLeft < 0.0 && mapper.m_GraphRight>0.0)
   {
      Float64 wz = mapper.GetWorldX(0.0);
      DrawAxisLine(wz, mapper.m_WorldBottom, wz, mapper.m_WorldTop, 3);
   }
}

void CGraphXyDisplayObject::DrawAxisLine(Float64 startX, Float64 startY, Float64 endX, Float64 endY, UINT width)
{
   // start point
   WBFL::Geometry::Point2d start_pnt(startX, startY);

   auto start_rep = WBFL::DManip::PointDisplayObject::Create();
   start_rep->SetPosition(start_pnt, false, false);
   auto start_connectable = std::dynamic_pointer_cast<WBFL::DManip::iConnectable>(start_rep);
   auto start_socket = start_connectable->AddSocket(0, start_pnt);
   start_rep->Visible(false);
   AddMyDisplayObject(start_rep);

   // end point
   WBFL::Geometry::Point2d end_pnt(endX,endY);

   auto end_rep = WBFL::DManip::PointDisplayObject::Create();
   end_rep->SetPosition(end_pnt, false, false);
   auto end_connectable = std::dynamic_pointer_cast<WBFL::DManip::iConnectable>(end_rep);
   auto end_socket = end_connectable->AddSocket(0, end_pnt);
   end_rep->Visible(false);
   AddMyDisplayObject(end_rep);

   // line
   auto ll_rep = WBFL::DManip::LineDisplayObject::Create();
   auto ll_connector = std::dynamic_pointer_cast<WBFL::DManip::iConnector>(ll_rep);
   auto ll_startPlug = ll_connector->GetStartPlug();
   auto ll_endPlug = ll_connector->GetEndPlug();
   DWORD dwCookie;
   dwCookie = start_socket->Connect(ll_startPlug);
   dwCookie = end_socket->Connect(ll_endPlug);

   auto dlstrategy = ll_rep->GetDrawLineStrategy();
   auto strategy = std::dynamic_pointer_cast<WBFL::DManip::SimpleDrawLineStrategy>(dlstrategy);
   strategy->SetWidth(width);

   AddMyDisplayObject(ll_rep);
}

void CGraphXyDisplayObject::DrawGraph(Float64 worldTop, Float64 worldLeft, Float64 worldRight, Float64 worldBottom)
{
   // get extents of curves
   Float64 gr_top, gr_left, gr_right, gr_bottom;
   GetCurveBoundary(&gr_top, &gr_left, &gr_right, &gr_bottom);

   // set up mapping between "graph space" and world space
   GraphMapper mapper(worldLeft, worldRight, worldTop, worldBottom, gr_left, gr_right, gr_top, gr_bottom);

   DrawAxis(mapper);

   if (m_DoDisplayAxisValues == VARIANT_TRUE || m_DoDisplayGrid == VARIANT_TRUE && m_NumberOfMajorIncrements > 1)
   {
      // compute nice number spacing - x  and y directions
      IndexType num_xsegs = m_NumberOfMajorIncrements;
      Float64 nice_xmin, nice_xmax, nice_xincrement;
      CalculateNiceRange(gr_left, gr_right, num_xsegs, nice_xmin, nice_xmax, nice_xincrement);

      IndexType num_ysegs = m_NumberOfMajorIncrements;
      Float64 nice_ymin, nice_ymax, nice_yincrement;
      CalculateNiceRange(gr_bottom, gr_top, num_ysegs, nice_ymin, nice_ymax, nice_yincrement);

      // compute tic height in world space
      Float64 tic_size;
      {
         Float64 ts_x = fabs(worldRight - worldLeft) / TIC_SIZE;
         Float64 ts_y = fabs(worldTop - worldBottom) / TIC_SIZE;
         tic_size = min(ts_x, ts_y);
      }

      // draw full grid or just tic marks depending on what's requested
      Float64 grid_bottom, grid_top, grid_left, grid_right;
      if (m_DoDisplayGrid == VARIANT_TRUE)
      {
         // full grid
         grid_bottom = worldBottom;
         grid_top = worldTop;
         grid_left = worldLeft;
         grid_right = worldRight;
      }
      else
      {
         // tic's only
         grid_bottom = worldBottom - tic_size / 2.;
         grid_top = grid_bottom + tic_size;
         grid_left = worldLeft - tic_size / 2.;
         grid_right = grid_left + tic_size;
      }

      // verticals
      for (IndexType ig = 0; ig <= num_xsegs; ig++)
      {
         Float64 grx = nice_xmin + ig * nice_xincrement;
         if (grx >= gr_left && grx <= gr_right)
         {
            Float64 wx = mapper.GetWorldX(grx);
            DrawAxisLine(wx, grid_bottom, wx, grid_top);
         }
      }

      // horizontals
      for (IndexType ig = 0; ig <= num_ysegs; ig++)
      {
         Float64 gry = nice_ymin + ig * nice_yincrement;
         if (gry >= gr_bottom && gry <= gr_top)
         {
            Float64 wy = mapper.GetWorldY(gry);
            DrawAxisLine(grid_left, wy, grid_right, wy);
         }
      }


      // Value Labels
      if (m_DoDisplayAxisValues == VARIANT_TRUE)
      {
         WBFL::System::NumericFormatTool formatter;

         // draw values along horizontal axis
         UINT locator = TA_CENTER | TA_TOP;
         Float64 tl_y = worldBottom + tic_size;

         for (IndexType ig = 0; ig <= num_xsegs; ig++)
         {
            Float64 grx = nice_xmin + ig * nice_xincrement;
            if (grx >= gr_left && grx <= gr_right)
            {
               Float64 wx = mapper.GetWorldX(grx);
               std::_tstring val = formatter.AsString(grx);

               DrawString(val, wx, tl_y, locator);
            }
         }

         // vertical axis labels
         locator = TA_LEFT | TA_BASELINE;
         Float64 tl_x = worldLeft + tic_size / 2;
         for (IndexType ig = 0; ig <= num_ysegs; ig++)
         {
            Float64 gry = nice_ymin + ig * nice_yincrement;
            if (gry >= gr_bottom && gry <= gr_top)
            {
               Float64 wy = mapper.GetWorldY(gry);
               std::_tstring val = formatter.AsString(gry);

               DrawString(val, tl_x, wy, locator);
            }
         }
      }

   }

   DrawCurves(mapper);
}

void CGraphXyDisplayObject::DrawString(std::_tstring& string, Float64 wx, Float64 wy, UINT textAlign)
{
   auto text_block = WBFL::DManip::TextBlock::Create();

   WBFL::Geometry::Point2d point(wx, wy);

   text_block->SetPosition(point);
   text_block->SetText(string.c_str());
   text_block->SetTextAlign(textAlign);

   AddMyDisplayObject(text_block);
}


void CGraphXyDisplayObject::DrawCurves(GraphMapper& mapper)
{
   // loop over all curves and draw them
   for (DataSetIterator it = m_DataSets.begin(); it != m_DataSets.end(); it++)
   {
      auto pdsp = *it;

      auto pds = pdsp->GetDataSet();

      auto pfactory = pdsp->GetDataPointFactory();

      COLORREF graph_color = pfactory->GetColor();

      IndexType cnt = pds->GetCount();

      bool first = true;
      std::shared_ptr<WBFL::DManip::iSocket> start_socket, end_socket;
      for (IndexType i = 0; i < cnt; i++)
      {
         auto pnt = pds->GetItem(i);

         // map to 'world space'
         Float64 xo, yo, xm, ym;
         xo = pnt.X();
         yo = pnt.Y();

         xm = mapper.GetWorldX(xo);
         ym = mapper.GetWorldY(yo);

         auto dataPoint = pfactory->CreateDataPoint(xo, yo, xm, ym);

         AddMyDisplayObject(dataPoint);

         auto dp_connectable = std::dynamic_pointer_cast<WBFL::DManip::iConnectable>(dataPoint);
         end_socket = dp_connectable->GetSocket(0, AccessType::ByIndex);

         if (!first)
         {
            auto ll_rep = WBFL::DManip::LineDisplayObject::Create();
            auto ll_connector = std::dynamic_pointer_cast<WBFL::DManip::iConnector>(ll_rep);
            auto ll_startPlug = ll_connector->GetStartPlug();
            auto ll_endPlug = ll_connector->GetEndPlug();
            DWORD dwCookie;
            dwCookie = start_socket->Connect(ll_startPlug);
            dwCookie = end_socket->Connect(ll_endPlug);

            auto ds = ll_rep->GetDrawLineStrategy();
            auto sds = std::dynamic_pointer_cast<WBFL::DManip::SimpleDrawLineStrategy>(ds);

            sds->SetColor(graph_color);
            sds->SetWidth(2);

            AddMyDisplayObject(ll_rep);
         }
         else
         {
            // can't add line first time through
            first = false;
         }

         start_socket = end_socket;
      }
   }
}

void CGraphXyDisplayObject::GetCurveBoundary(Float64* t, Float64* l, Float64* r, Float64* b)
{
   Float64 lt = -DBL_MAX;
   Float64 ll = DBL_MAX;
   Float64 lr = -DBL_MAX;
   Float64 lb = DBL_MAX;
   long num_dp = 0;
   for (DataSetIterator it = m_DataSets.begin(); it != m_DataSets.end(); it++)
   {
      auto pdsp = *it;

      auto pds = pdsp->GetDataSet();

      IndexType cnt = pds->GetCount();

      for (IndexType i = 0; i < cnt; i++)
      {
         num_dp++;
         auto pnt = pds->GetItem(i);

         auto [x, y] = pnt.GetLocation();

         if (y > lt)
            lt = y;

         if (y < lb)
            lb = y;

         if (x > lr)
            lr = x;

         if (x < ll)
            ll = x;
      }
   }

   if (num_dp < 2 || lr - ll <= 0)
   {
      // x Range is null, or not enough points to make a curve
      // just make a unit area to draw graph in
      *t = 1.0;
      *b = -1.0;
      *l = -1.0;
      *r = 1.0;
   }
   else if (lt - lb <= 0)
   {
      // we have an x range but curve is horizontal - give default height of 1.0 so we can graph something
      *t = lt + 1.0;
      *b = lt - 1.0;
      *l = ll;
      *r = lr;
   }
   else
   {
      *t = lt;
      *b = lb;
      *l = ll;
      *r = lr;
   }
}

void CGraphXyDisplayObject::AddMyDisplayObject(std::shared_ptr<WBFL::DManip::iDisplayObject> pdo)
{
   AddDisplayObject(pdo);
   m_NumDos++;
}

void CGraphXyDisplayObject::ClearDisplayObjects()
{
   if (m_NumDos > 0)
   {
      // first go through all connectable display objects and disconnect sockets
      IndexType cnt = GetDisplayObjectCount();
      for (IndexType ic = 0; ic < cnt; ic++)
      {
         auto pdo = GetDisplayObject(ic, AccessType::ByIndex);

         auto connectable = std::dynamic_pointer_cast<WBFL::DManip::iConnectable>(pdo);

         if (connectable)
         {
            connectable->RemoveAllSockets();
         }
      }

      CompositeDisplayObject::ClearDisplayObjects();
      m_NumDos = 0;
   }
}

void CGraphXyDisplayObject::Commit()
{
   return RebuildDisplayObjects();
}

void CGraphXyDisplayObject::ClearData()
{
   m_DataSets.clear();
   ClearDisplayObjects();
}

IndexType CGraphXyDisplayObject::GetNumberOfMajorIncrements()
{
   return m_NumberOfMajorIncrements;
}

void CGraphXyDisplayObject::SetNumberOfMajorIncrements(IndexType newVal)
{
   m_NumberOfMajorIncrements = newVal;
}

BOOL CGraphXyDisplayObject::DoDisplayAxisValues()
{
   return m_DoDisplayAxisValues;
}

void CGraphXyDisplayObject::DoDisplayAxisValues(BOOL newVal)
{
   m_DoDisplayAxisValues = newVal;
}

BOOL CGraphXyDisplayObject::DoDisplayGrid()
{
   return m_DoDisplayGrid;
}

void CGraphXyDisplayObject::DoDisplayGrid(BOOL newVal)
{
   m_DoDisplayGrid = newVal;
}

/////////////////////////////////////////////////////////////////
CGraphXyDataProvider::CGraphXyDataProvider()
{
   m_DataSet = std::make_shared<CDataSet2dImpl>();
   m_Factory = std::make_shared<CLegendEntryImpl>();
}

void CGraphXyDataProvider::SetDataSet(std::shared_ptr<iDataSet2d> dataSet)
{
   m_DataSet = dataSet;
}

std::shared_ptr<iDataSet2d> CGraphXyDataProvider::GetDataSet()
{
   return m_DataSet;
}

void CGraphXyDataProvider::SetDataPointFactory(std::shared_ptr<iDataPointFactory> factory)
{
  m_Factory = factory;
}

std::shared_ptr<iDataPointFactory> CGraphXyDataProvider::GetDataPointFactory()
{
   return m_Factory;
}