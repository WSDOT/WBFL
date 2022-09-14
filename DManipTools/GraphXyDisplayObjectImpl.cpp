///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
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

// GraphXyDisplayObject.cpp : Implementation of CGraphXyDisplayObject
#include "stdafx.h"
#include <WBFLDManipTools.h>
#include "DManipTools\DManipTools.h"
#include "GraphXyDisplayObjectImpl.h"
#include "DataPointDrawStrategyImpl.h"
#include "DataPointEventsImpl.h"

#include <MathEx.h>
#include <Math\CoordMapper1d.h>
#include <FLOAT.H>
#include <system\NumericFormatTool.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIC_SIZE 20

/////////////////////////////////////////////////////////////////////////////
// CGraphXyDisplayObject
static void CalculateNiceRange(const Float64 originalMin, const Float64 originalMax,
                               CollectionIndexType& numberOfSegments,
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
   const Float64 supply[nscale] = {25.0, 20.0, 15.0, 10.0, 5.0, 2.5, 2.0, 1.0, 0.5 };

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
           niceMin = niceMin/prturb;
           niceMax = niceMax*prturb;
       }
   }
   else if (niceMax < niceMin)
   {
       Float64 temp = niceMin;
       niceMin = niceMax;
       niceMax = temp;
   }

   if (niceMax-niceMin <= tol)
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

   exponent = floor(log10((niceMax - niceMin)/numberOfSegments));
   factor = pow(10.0, exponent);

//     test each scale and keep the largest one that works

   for (CollectionIndexType i = 0; i<nscale; i++)
   {
       test_scale = factor*supply[i];
       nmin = (Int32)floor(niceMin/test_scale);
       nmax = (Int32)ceil(niceMax/test_scale);
       need = nmax - nmin;

       if (need <= (Int32)numberOfSegments)
       {
           scale_fac = test_scale;
           adjusted_min = nmin*scale_fac;
           adjusted_max = nmax*scale_fac;
       }
       else
       {
          continue;
       }
   }

   // try to 'shrink' the outer bounds if the original max or min only
   // slightly intrudes into the nice range.

   const Float64 range_tol = (niceMax-niceMin)/300.; // could put this out to interface
                                                    // if very precise graphing were needed.

   if ( adjusted_max-scale_fac+range_tol > niceMax && need>1 )  // shrink upper range if original is
   {                                                            // only slightly above next band.
      adjusted_max -= scale_fac;
      need--;
   }

   if ( adjusted_min+scale_fac-range_tol < niceMin && need>1 )  // shrink lower range
   {
      adjusted_min += scale_fac;
      need--;
   }

// return adjusted max and min

   numberOfSegments = need;
   niceIncrement    = scale_fac;

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
               Float64 graphLeft, Float64 graphRight, Float64 graphTop, Float64 graphBottom):
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
      if ( IsEqual(graphTop, graphBottom, 1.0e-16) )
      {
         // graph ordinates are different.
         Float64 base = Round(graphTop);
         grtop    = base + 1.0;
         grbottom = base - 1.0;
      }
      else
      {
         grtop    = graphTop;
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
CGraphXyDisplayObject::CGraphXyDisplayObject():
m_NumDos(0),
m_pDisplayObject(nullptr),
m_DoDisplayAxisValues(VARIANT_TRUE),
m_DoDisplayGrid(VARIANT_TRUE),
m_NumberOfMajorIncrements(10)
{
}


STDMETHODIMP CGraphXyDisplayObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_iGraphXyDisplayObject
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CGraphXyDisplayObject::FinalConstruct()
{
   HRESULT hr = m_GraphBounds.CoCreateInstance(CLSID_Rect2d);
   if (FAILED(hr))
      return hr;

   // for some undocumented reason, you must ask for iunknown when aggregating
   IUnknown* myiu = this->GetControllingUnknown();
   hr = ::CoCreateInstance(CLSID_CompositeDisplayObject, myiu, CLSCTX_INPROC_SERVER,
                           IID_IUnknown, (void**)&m_pDisplayObject);

   if (FAILED(hr))
      return hr;

   return S_OK;
}

void::CGraphXyDisplayObject::FinalRelease()
{
   ClearDisplayObjects();

   m_pDisplayObject->Release();
}

STDMETHODIMP_(void) CGraphXyDisplayObject::get_GraphBounds(IRect2d **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_GraphBounds.CopyTo(pVal);
}

STDMETHODIMP_(void) CGraphXyDisplayObject::put_GraphBounds(IRect2d *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   ATLASSERT(newVal!=nullptr);

	m_GraphBounds = newVal;

}

STDMETHODIMP_(void) CGraphXyDisplayObject::get_Title(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_Title.Copy();
}

STDMETHODIMP_(void) CGraphXyDisplayObject::put_Title(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Title = newVal;
}

STDMETHODIMP_(void) CGraphXyDisplayObject::DataCount(CollectionIndexType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_DataSets.size();
}

STDMETHODIMP_(void) CGraphXyDisplayObject::AddData(iGraphXyDataProvider *dataSet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_DataSets.push_back( dataSet );
}

STDMETHODIMP CGraphXyDisplayObject::GetData(CollectionIndexType idx, iGraphXyDataProvider **dataSet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (0 <= idx && idx < m_DataSets.size())
   {
      return m_DataSets[idx].CopyTo(dataSet);
   }
   else
      return E_INVALIDARG;

	return S_OK;
}

HRESULT CGraphXyDisplayObject::RebuildDisplayObjects()
{
   HRESULT hr;
   // first remove display objects
   ClearDisplayObjects();

   // make sure we have some data and a rectangle to draw in
   Float64 gb_top, gb_bottom, gb_right, gb_left;
   hr = m_GraphBounds->get_Top(&gb_top);
   if (FAILED(hr))
      return hr;

   hr = m_GraphBounds->get_Bottom(&gb_bottom);
   if (FAILED(hr))
      return hr;

   hr = m_GraphBounds->get_Left(&gb_left);
   if (FAILED(hr))
      return hr;

   hr = m_GraphBounds->get_Right(&gb_right);
   if (FAILED(hr))
      return hr;

   if (gb_top-gb_bottom<=0 || gb_right-gb_left<=0)
   {
      // no canvas on which to draw
      ATLASSERT(false);
      return S_OK;
   }

   // draw data curves
   hr = DrawGraph(gb_top, gb_left, gb_right, gb_bottom);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

HRESULT CGraphXyDisplayObject::DrawAxis(GraphMapper& mapper)
{
   HRESULT hr;
   // outline
   hr = DrawAxisLine(mapper.m_WorldLeft, mapper.m_WorldBottom, mapper.m_WorldLeft, mapper.m_WorldTop); 
   if (FAILED(hr))
      return hr;

   hr = DrawAxisLine(mapper.m_WorldLeft, mapper.m_WorldBottom, mapper.m_WorldRight, mapper.m_WorldBottom); 
   if (FAILED(hr))
      return hr;

   hr = DrawAxisLine(mapper.m_WorldRight, mapper.m_WorldBottom, mapper.m_WorldRight, mapper.m_WorldTop); 
   if (FAILED(hr))
      return hr;

   hr = DrawAxisLine(mapper.m_WorldLeft, mapper.m_WorldTop, mapper.m_WorldRight, mapper.m_WorldTop); 
   if (FAILED(hr))
      return hr;

   // zero lines if needed
   if (mapper.m_GraphBottom<0.0 && mapper.m_GraphTop>0.0)
   {
      Float64 wz = mapper.GetWorldY(0.0);
      hr = DrawAxisLine(mapper.m_WorldLeft, wz, mapper.m_WorldRight, wz,3); 
      if (FAILED(hr))
         return hr;
   }

   if (mapper.m_GraphLeft<0.0 && mapper.m_GraphRight>0.0)
   {
      Float64 wz = mapper.GetWorldX(0.0);
      hr = DrawAxisLine(wz, mapper.m_WorldBottom, wz, mapper.m_WorldTop,3); 
      if (FAILED(hr))
         return hr;
   }

   return S_OK;
}

HRESULT CGraphXyDisplayObject::DrawAxisLine(Float64 startX, Float64 startY, Float64 endX, Float64 endY, UINT width)
{
   HRESULT hr;
   // start point
   CComPtr<IPoint2d> start_pnt;
   hr = start_pnt.CoCreateInstance(CLSID_Point2d);
   if (FAILED(hr))
      return hr;

   start_pnt->put_X(startX);
   start_pnt->put_Y(startY);

   CComPtr<iPointDisplayObject> start_rep;
   ::CoCreateInstance(CLSID_PointDisplayObject,nullptr,CLSCTX_ALL,IID_iPointDisplayObject,(void**)&start_rep);
   start_rep->SetPosition(start_pnt,FALSE,FALSE);
   CComQIPtr<iConnectable,&IID_iConnectable> start_connectable(start_rep);
   CComPtr<iSocket> start_socket;
   start_connectable->AddSocket(0,start_pnt,&start_socket);
   start_rep->Visible(FALSE);
   AddMyDisplayObject(start_rep);
   start_rep.Release();

   // end point
   CComPtr<IPoint2d> end_pnt;
   hr = end_pnt.CoCreateInstance(CLSID_Point2d);
   if (FAILED(hr))
      return hr;

   end_pnt->put_X(endX);
   end_pnt->put_Y(endY);

   CComPtr<iPointDisplayObject> end_rep;
   ::CoCreateInstance(CLSID_PointDisplayObject,nullptr,CLSCTX_ALL,IID_iPointDisplayObject,(void**)&end_rep);
   end_rep->SetPosition(end_pnt,FALSE,FALSE);
   CComQIPtr<iConnectable,&IID_iConnectable> end_connectable(end_rep);
   CComPtr<iSocket> end_socket;
   end_connectable->AddSocket(0,end_pnt,&end_socket);
   end_rep->Visible(FALSE);
   AddMyDisplayObject(end_rep);
   end_rep.Release();

   // line
   CComPtr<iLineDisplayObject> ll_rep;
   ::CoCreateInstance(CLSID_LineDisplayObject,nullptr,CLSCTX_ALL,IID_iLineDisplayObject,(void**)&ll_rep);
   CComQIPtr<iConnector,&IID_iConnector> ll_connector(ll_rep);
   CComPtr<iPlug> ll_startPlug;
   ll_connector->GetStartPlug(&ll_startPlug);
   CComPtr<iPlug> ll_endPlug;
   ll_connector->GetEndPlug(&ll_endPlug);
   DWORD dwCookie;
   start_socket->Connect(ll_startPlug,&dwCookie);
   end_socket->Connect(ll_endPlug,&dwCookie);

   CComPtr<iDrawLineStrategy> dlstrategy;
   ll_rep->GetDrawLineStrategy(&dlstrategy);

   CComQIPtr<iSimpleDrawLineStrategy,&IID_iSimpleDrawLineStrategy> strategy(dlstrategy);
   strategy->SetWidth(width);

   AddMyDisplayObject(ll_rep);

   return S_OK;
}

HRESULT CGraphXyDisplayObject::DrawGraph(Float64 worldTop, Float64 worldLeft, Float64 worldRight, Float64 worldBottom)
{
   HRESULT hr=S_OK;
   // get extents of curves
   Float64 gr_top, gr_left , gr_right, gr_bottom;
   hr = GetCurveBoundary(&gr_top, &gr_left, &gr_right, &gr_bottom);
   if (FAILED(hr))
      return hr;

   // set up mapping between "graph space" and world space
   GraphMapper mapper(worldLeft, worldRight, worldTop, worldBottom, gr_left,  gr_right, gr_top, gr_bottom);

   hr = DrawAxis(mapper);
   if (FAILED(hr))
      return hr;

   if (m_DoDisplayAxisValues==VARIANT_TRUE || m_DoDisplayGrid==VARIANT_TRUE && m_NumberOfMajorIncrements>1)
   {
      // compute nice number spacing - x  and y directions
      CollectionIndexType num_xsegs = m_NumberOfMajorIncrements;
      Float64 nice_xmin, nice_xmax, nice_xincrement;
      CalculateNiceRange( gr_left, gr_right, num_xsegs, nice_xmin, nice_xmax, nice_xincrement);

      CollectionIndexType num_ysegs = m_NumberOfMajorIncrements;
      Float64 nice_ymin, nice_ymax, nice_yincrement;
      CalculateNiceRange( gr_bottom, gr_top, num_ysegs, nice_ymin, nice_ymax, nice_yincrement);

      // compute tic height in world space
      Float64 tic_size;
      {
         Float64 ts_x = fabs(worldRight-worldLeft)/TIC_SIZE;
         Float64 ts_y = fabs(worldTop-worldBottom)/TIC_SIZE;
         tic_size = min(ts_x, ts_y);
      }

      // draw full grid or just tic marks depending on what's requested
      Float64 grid_bottom, grid_top, grid_left, grid_right;
      if (m_DoDisplayGrid==VARIANT_TRUE)
      {
         // full grid
         grid_bottom = worldBottom;
         grid_top    = worldTop;
         grid_left   = worldLeft;
         grid_right  = worldRight;
      }
      else
      {
         // tic's only
         grid_bottom = worldBottom - tic_size/2.;
         grid_top    = grid_bottom + tic_size;
         grid_left   = worldLeft - tic_size/2.;
         grid_right  = grid_left + tic_size;
      }

      // verticals
      for (CollectionIndexType ig = 0; ig<=num_xsegs; ig++)
      {
         Float64 grx = nice_xmin + ig*nice_xincrement;
         if (grx >= gr_left && grx<=gr_right)
         {
            Float64 wx = mapper.GetWorldX(grx);
            hr = DrawAxisLine(wx, grid_bottom, wx, grid_top); 
            if (FAILED(hr))
               return hr;
         }
      }

      // horizontals
      for (CollectionIndexType ig = 0; ig<=num_ysegs; ig++)
      {
         Float64 gry = nice_ymin + ig*nice_yincrement;
         if (gry >=gr_bottom && gry<=gr_top)
         {
            Float64 wy = mapper.GetWorldY(gry);
            hr = DrawAxisLine(grid_left, wy, grid_right, wy); 
            if (FAILED(hr))
               return hr;
         }
      }


      // Value Labels
      if (m_DoDisplayAxisValues==VARIANT_TRUE)
      {
         WBFL::System::NumericFormatTool formatter;

         // draw values along horizontal axis
         UINT locator = TA_CENTER | TA_TOP;
         Float64 tl_y = worldBottom-tic_size/2;

         for (CollectionIndexType ig = 0; ig<=num_xsegs; ig++)
         {
            Float64 grx = nice_xmin + ig*nice_xincrement;
            if (grx >= gr_left && grx<=gr_right)
            {
               Float64 wx = mapper.GetWorldX(grx);
               std::_tstring val = formatter.AsString(grx);

               DrawString(val, wx, tl_y, locator);
            }
         }

         // vertical axis labels
         locator = TA_LEFT | TA_BASELINE;
         Float64 tl_x = worldLeft+tic_size/2;
         for (CollectionIndexType ig = 0; ig<=num_ysegs; ig++)
         {
            Float64 gry = nice_ymin + ig*nice_yincrement;
            if (gry >=gr_bottom && gry<=gr_top)
            {
               Float64 wy = mapper.GetWorldY(gry);
               std::_tstring val = formatter.AsString(gry);

               DrawString(val, tl_x , wy, locator);
            }
         }
      }

   }

   hr = DrawCurves(mapper);
   if (FAILED(hr))
      return hr;

   return S_OK;
}

HRESULT CGraphXyDisplayObject::DrawString(std::_tstring& string, Float64 wx, Float64 wy, UINT textAlign)
{
   HRESULT hr;

   CComPtr<iEditableTextBlock> text_block;
   hr = ::CoCreateInstance(CLSID_TextBlock,nullptr,CLSCTX_ALL,IID_iTextBlock,(void**)&text_block);
   if (FAILED(hr))
   {
      ATLASSERT(false);
      return hr;
   }

   CComPtr<IPoint2d> point;
   hr = point.CoCreateInstance(CLSID_Point2d);
   if (FAILED(hr))
      return hr;

   point->put_X(wx);
   point->put_Y(wy);

   text_block->SetPosition(point);
   text_block->SetText(string.c_str());
   text_block->SetTextAlign(textAlign);

   CComPtr<iDisplayObject> disp(text_block);
   ATLASSERT(disp!=nullptr);

   AddMyDisplayObject(disp);

   return S_OK;
}


HRESULT CGraphXyDisplayObject::DrawCurves(GraphMapper& mapper)
{
   HRESULT hr;
   // loop over all curves and draw them
   for (DataSetIterator it=m_DataSets.begin(); it!=m_DataSets.end(); it++)
   {
      CComPtr<iGraphXyDataProvider> pdsp = *it;

      CComPtr<iDataSet2d> pds;
      pdsp->get_DataSet(&pds);

      CComPtr<iDataPointFactory> pfactory;
      pdsp->get_DataPointFactory(&pfactory);

      COLORREF graph_color = pfactory->get_Color();

      CollectionIndexType cnt;
      pds->get_Count(&cnt);

      bool first = true;
      CComPtr<iSocket> start_socket, end_socket;
      for (CollectionIndexType i = 0; i<cnt; i++)
      {
         CComPtr<IPoint2d> pnt;
         hr = pds->get_Item(i, &pnt);
         if (FAILED(hr))
            return hr;

         // map to 'world space'
         Float64 xo, yo, xm, ym;
         pnt->get_X(&xo);
         pnt->get_Y(&yo);

         xm = mapper.GetWorldX(xo);
         ym = mapper.GetWorldY(yo);

         CComPtr<iDisplayObject> dataPoint;
         hr = pfactory->CreateDataPoint(xo, yo, xm, ym, &dataPoint);
         if (FAILED(hr))
            return hr;

         AddMyDisplayObject(dataPoint);

         CComQIPtr<iConnectable,&IID_iConnectable> dp_connectable(dataPoint);
         end_socket=nullptr;
         dp_connectable->GetSocket(0,atByIndex,&end_socket);

         if (!first)
         {
            CComPtr<iLineDisplayObject> ll_rep;
            ::CoCreateInstance(CLSID_LineDisplayObject,nullptr,CLSCTX_ALL,IID_iLineDisplayObject,(void**)&ll_rep);
            CComQIPtr<iConnector,&IID_iConnector> ll_connector(ll_rep);
            CComPtr<iPlug> ll_startPlug;
            ll_connector->GetStartPlug(&ll_startPlug);
            CComPtr<iPlug> ll_endPlug;
            ll_connector->GetEndPlug(&ll_endPlug);
            DWORD dwCookie;
            start_socket->Connect(ll_startPlug,&dwCookie);
            end_socket->Connect(ll_endPlug,&dwCookie);

            CComPtr<iDrawLineStrategy> ds;
            ll_rep->GetDrawLineStrategy(&ds);
            CComPtr<iSimpleDrawLineStrategy> sds;
            hr = ds->QueryInterface(IID_iSimpleDrawLineStrategy,(void**)&sds);
            ATLASSERT(SUCCEEDED(hr));

            sds->SetColor( graph_color );
            sds->SetWidth(2);

            AddMyDisplayObject(ll_rep);
         }
         else
         {
            // can't add line first time through
            first = false;
         }

         start_socket=end_socket;
      }
   }

   return S_OK;
}

HRESULT CGraphXyDisplayObject::GetCurveBoundary(Float64* t, Float64* l, Float64* r, Float64* b)
{
   HRESULT hr;

   Float64 lt = -DBL_MAX;
   Float64 ll =  DBL_MAX;
   Float64 lr = -DBL_MAX;
   Float64 lb =  DBL_MAX;
   long num_dp = 0;
   for (DataSetIterator it=m_DataSets.begin(); it!=m_DataSets.end(); it++)
   {
      CComPtr<iGraphXyDataProvider> pdsp = *it;

      CComPtr<iDataSet2d> pds;
      pdsp->get_DataSet(&pds);

      CollectionIndexType cnt;
      pds->get_Count(&cnt);

      for (CollectionIndexType i = 0; i<cnt; i++)
      {
         num_dp++;
         CComPtr<IPoint2d> pnt;
         hr = pds->get_Item(i, &pnt);
         if (FAILED(hr))
            return hr;

         Float64 x, y;
         hr = pnt->get_X(&x);
         if (FAILED(hr))
            return hr;
         
         hr = pnt->get_Y(&y);
         if (FAILED(hr))
            return hr;

         if (y>lt)
            lt = y;

         if (y<lb)
            lb = y;

         if (x>lr)
            lr = x;

         if (x<ll)
            ll = x;
      }
   }

   if (num_dp<2 || lr-ll<=0)
   {
      // x Range is null, or not enough points to make a curve
      // just make a unit area to draw graph in
      *t =  1.0;
      *b = -1.0;
      *l = -1.0;
      *r =  1.0;
   }
   else if ( lt-lb<=0 )
   {
      // we have an x range but curve is horizontal - give default height of 1.0 so we can graph something
      *t = lt+1.0;
      *b = lt-1.0;
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

   return S_OK;
}

void CGraphXyDisplayObject::AddMyDisplayObject(iDisplayObject* pdo)
{
   HRESULT hr;
   CComPtr<iCompositeDisplayObject> pcdo;
   hr = m_pDisplayObject->QueryInterface(IID_iCompositeDisplayObject, (void**)&pcdo);
   ATLASSERT(SUCCEEDED(hr));

   pcdo->AddDisplayObject(pdo);
   m_NumDos++;
}

void CGraphXyDisplayObject::ClearDisplayObjects()
{
   if (m_NumDos>0)
   {
      HRESULT hr;
      CComPtr<iCompositeDisplayObject> pcdo;
      hr = m_pDisplayObject->QueryInterface(IID_iCompositeDisplayObject, (void**)&pcdo);
      ATLASSERT(SUCCEEDED(hr));

      // first go through all connectable display objects and disconnect sockets
      CollectionIndexType cnt =  pcdo->GetDisplayObjectCount();
      for (CollectionIndexType ic = 0; ic<cnt; ic++)
      {
         CComPtr<iDisplayObject> pdo;
         pcdo->GetDisplayObject(ic,atByIndex,&pdo);

         CComQIPtr<iConnectable,&IID_iConnectable> connectable(pdo);

         if (connectable)
         {
            connectable->RemoveAllSockets();
         }
      }

      pcdo->ClearDisplayObjects();
      m_NumDos = 0;
   }
}

STDMETHODIMP CGraphXyDisplayObject::Commit()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	return RebuildDisplayObjects();
}

STDMETHODIMP CGraphXyDisplayObject::ClearData()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_DataSets.clear();

   ClearDisplayObjects();

	return S_OK;
}

STDMETHODIMP_(void) CGraphXyDisplayObject::get_NumberOfMajorIncrements(CollectionIndexType *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_NumberOfMajorIncrements;
}

STDMETHODIMP CGraphXyDisplayObject::put_NumberOfMajorIncrements(CollectionIndexType newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (newVal>0)
      m_NumberOfMajorIncrements = newVal;
   else
      return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP_(void) CGraphXyDisplayObject::get_DoDisplayAxisValues(BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_DoDisplayAxisValues;
}

STDMETHODIMP_(void) CGraphXyDisplayObject::put_DoDisplayAxisValues(BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (newVal == VARIANT_TRUE)
      m_DoDisplayAxisValues = VARIANT_TRUE;
   else
      m_DoDisplayAxisValues = VARIANT_FALSE;
}

STDMETHODIMP_(void) CGraphXyDisplayObject::get_DoDisplayGrid(BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_DoDisplayGrid;
}

STDMETHODIMP_(void) CGraphXyDisplayObject::put_DoDisplayGrid(BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (newVal == VARIANT_TRUE)
      m_DoDisplayGrid = VARIANT_TRUE;
   else
      m_DoDisplayGrid = VARIANT_FALSE;
}

