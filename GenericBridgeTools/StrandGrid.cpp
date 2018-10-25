///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2010  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// StrandGrid.cpp : Implementation of CStrandGrid
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "StrandGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrandGrid

STDMETHODIMP CStrandGrid::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStrandGrid
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CStrandGrid::FinalConstruct()
{
   CComPtr<IGeomUtil> geom_util;
   HRESULT hr = geom_util.CoCreateInstance(CLSID_GeomUtil);
   if ( FAILED(hr) )
      return hr;

   geom_util->get_Point2dFactory(&m_Point2dFactory);

   m_GridBoundingBox.CoCreateInstance(CLSID_Rect2d);
   m_CurrentFill.CoCreateInstance(CLSID_LongArray);
   m_MaxFill.CoCreateInstance(CLSID_LongArray);

   m_VerticalAdjustment = 0.0;

   m_bUpdateGrid = true;
   m_bUpdateFill = true;

   return S_OK;
}

void CStrandGrid::FinalRelease()
{
}

STDMETHODIMP CStrandGrid::AddGridPoint(/*[in]*/IPoint2d* point)
{
   CHECK_IN(point);

   Float64 x, y;
   point->get_X(&x);
   point->get_Y(&y);

   if ( x < 0 )
      return E_INVALIDARG; // x must be 0.0 or more

   m_GridPoints.push_back( GridPoint2d(x,y) );

   InvalidateGrid();

   return S_OK;
}

STDMETHODIMP CStrandGrid::AddGridPoints(/*[in]*/IPoint2dCollection* points)
{
   CHECK_IN(points);

   CollectionIndexType cur_cnt = m_GridPoints.size();
   
   CollectionIndexType cnt;
   points->get_Count(&cnt);

   m_GridPoints.reserve(cur_cnt + cnt);

   for (CollectionIndexType i=0; i<cnt; i++)
   {
      CComPtr<IPoint2d> point;
      points->get_Item(i, &point);

      HRESULT hr = AddGridPoint(point);
      if ( FAILED(hr) )
         return hr;
   }

   InvalidateGrid();

   return S_OK;
}

STDMETHODIMP CStrandGrid::get_GridPointCount(/*[out,retval]*/GridIndexType* count)
{
   CHECK_RETVAL(count);

   *count = m_GridPoints.size();
   return S_OK;
}

STDMETHODIMP CStrandGrid::get_GridPoint(/*[in]*/ GridIndexType idx,/*[out,retval]*/IPoint2d** point)
{
   if (idx < 0 || (GridIndexType)m_GridPoints.size() <= idx)
      return E_INVALIDARG;

   const GridPoint2d& pnt = m_GridPoints[idx];
   Float64 x = pnt.dPointX;
   Float64 y = pnt.dPointY;

   HRESULT hr = m_Point2dFactory->CreatePoint(point);
   if ( FAILED(hr) )
      return hr;
   
   (*point)->Move(x, y);

   return S_OK;
}

STDMETHODIMP CStrandGrid::get_GridPoints(/*[out,retval]*/IPoint2dCollection** points)
{
   CHECK_RETOBJ(points);

   CComPtr<IPoint2dCollection> new_points;
   new_points.CoCreateInstance(CLSID_Point2dCollection);

   for (GridCollectionIterator it=m_GridPoints.begin(); it!=m_GridPoints.end(); it++)
   {
      const GridPoint2d& pnt = *it;

      CComPtr<IPoint2d> point;
      HRESULT hr = m_Point2dFactory->CreatePoint(&point);
      if ( FAILED(hr) )
         return hr;
   
      point->Move(pnt.dPointX , pnt.dPointY );

      new_points->Add(point);
   }

   return new_points.CopyTo(points);
}

STDMETHODIMP CStrandGrid::RemoveGridPoint(/*[in]*/ GridIndexType idx)
{
   if (idx < 0 || (GridIndexType)m_GridPoints.size() <= idx)
      return E_INVALIDARG;

   m_GridPoints.erase( m_GridPoints.begin() + idx);

   InvalidateGrid();

   return S_OK;
}

STDMETHODIMP CStrandGrid::ClearGridPoints()
{
   m_GridPoints.clear();

   InvalidateGrid();

   return S_OK;
}

STDMETHODIMP CStrandGrid::GridBoundingBox(/*[out,retval]*/IRect2d** box)
{
   CHECK_RETOBJ(box);

   ValidateGrid();

   return m_GridBoundingBox.CopyTo(box);
}

// IStrandGridFiller
STDMETHODIMP CStrandGrid::get_MaxStrandCount(/*[out,retval]*/StrandIndexType* count)
{
   CHECK_RETVAL(count);
   ValidateGrid();

   *count = m_MaxCount;

   return S_OK;
}


STDMETHODIMP CStrandGrid::GetMaxStrandFill(/*[out,retval]*/ILongArray** maxFill)
{
   CHECK_RETOBJ(maxFill);

   ValidateGrid();

   return m_MaxFill.CopyTo(maxFill);
}


STDMETHODIMP CStrandGrid::get_StrandFill(/*[out,retval]*/ILongArray** fill)
{
   CHECK_RETOBJ(fill);

   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   return m_CurrentFill->Clone(fill);
}

STDMETHODIMP CStrandGrid::put_StrandFill(/*[in]*/ILongArray* fill)
{
   // fill contains the number of strands to be used at each grid position
   // if fill->Item == 2, the a strand is placed at +x and -x

   CHECK_IN(fill);

   InvalidateFill();

   // fill size does not have to match grid size
   CollectionIndexType nGridPoints;
   fill->get_Count(&nGridPoints);

   GridIndexType gridPointIdx = 0;
   for (GridCollectionIterator it=m_GridPoints.begin(); it!=m_GridPoints.end(); it++)
   {
      if (gridPointIdx < (GridIndexType)nGridPoints)
      {
         StrandIndexType nStrandsAtGridPoint;
         fill->get_Item(gridPointIdx, &nStrandsAtGridPoint);

         if ( 0 <= nStrandsAtGridPoint && nStrandsAtGridPoint <= 2 )
         {
            it->nStrandsAtGridPoint = StrandIndexType(nStrandsAtGridPoint);
         }
         else
         {
            ATLASSERT(FALSE); // invalid fill number -> there is something wrong with the grid definition
            it->nStrandsAtGridPoint = 0;
         }
      }
      else
      {
         it->nStrandsAtGridPoint = 0;
      }

      gridPointIdx++;
   }

   return S_OK;
}


STDMETHODIMP CStrandGrid::put_StrandMover(/*[out,retval]*/IStrandMover* mover)
{
   CHECK_IN(mover);

   m_pStrandMover = mover;

   return S_OK;
}

STDMETHODIMP CStrandGrid::get_VerticalStrandAdjustment(/*[out,retval]*/Float64* adjustment)
{
   CHECK_RETVAL(adjustment);

   *adjustment = m_VerticalAdjustment;
   return S_OK;
}

STDMETHODIMP CStrandGrid::put_VerticalStrandAdjustment(/*[in]*/Float64 adjustment)
{
   // we do not need to invalidate data

   m_VerticalAdjustment = adjustment;

   return S_OK;
}

STDMETHODIMP CStrandGrid::GetStrandCount(/*[out,retval]*/ StrandIndexType* count)
{
   CHECK_RETVAL(count);

   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   *count = GetStrandCount();
   return S_OK;
}


STDMETHODIMP CStrandGrid::RemoveAllStrands()
{
   InvalidateFill();

   for (GridCollectionIterator it=m_GridPoints.begin(); it!=m_GridPoints.end(); it++)
   {
      it->nStrandsAtGridPoint = 0;
   }

   return S_OK;
}

STDMETHODIMP CStrandGrid::GetStrandPositions(/*[out,retval]*/IPoint2dCollection** points)
{
   CHECK_RETOBJ(points);

   ValidateFill();

   CComPtr<IPoint2dCollection> local_points;
   HRESULT hr = local_points.CoCreateInstance(CLSID_Point2dCollection);
   if ( FAILED(hr) )
      return hr;

   GridIndexType nGridPoints = m_GridPoints.size();
   for(GridIndexType gridPointIdx = 0; gridPointIdx < nGridPoints; gridPointIdx++ )
   {
      const GridPoint2d& gpoint = m_GridPoints[gridPointIdx];
      StrandIndexType nStrandsAtGridPoint = gpoint.nStrandsAtGridPoint;
      ATLASSERT(0 <= nStrandsAtGridPoint && nStrandsAtGridPoint <= 2);

      if (0 < nStrandsAtGridPoint)
      {
         Float64 old_x = gpoint.dPointX;
         Float64 old_y = gpoint.dPointY;

         Float64 x, y;
         this->AdjustStrand(old_x,old_y,&x, &y);

         if (nStrandsAtGridPoint == 1)
         {
            CComPtr<IPoint2d> point;
            HRESULT hr = m_Point2dFactory->CreatePoint(&point);
            if ( FAILED(hr) )
               return hr;
         
            // single strands must always be placed at center
            point->Move(0.0, y);
            local_points->Add(point);
         }
         else if (1 < nStrandsAtGridPoint)
         {
            // place two strands at +/-X
            CComPtr<IPoint2d> point;
            HRESULT hr = m_Point2dFactory->CreatePoint(&point);
            if ( FAILED(hr) )
               return hr;
         
            point->Move(x, y);
            local_points->Add(point);

            CComPtr<IPoint2d> point2;
            hr = m_Point2dFactory->CreatePoint(&point2);
            if ( FAILED(hr) )
               return hr;

            point2->Move(-x, y);
            local_points->Add(point2);
         }
      }
   }

   return local_points.CopyTo(points);
}

STDMETHODIMP CStrandGrid::StrandIndexToGridIndex(/*[in]*/ StrandIndexType strandIndex, /*[out,retval]*/ GridIndexType* gridIndex)
{
   CHECK_RETVAL(gridIndex);

   ValidateFill();

   HRESULT hr = S_OK;

   if ( strandIndex < 0 || (StrandIndexType)m_StrandToGridMap.size() <= strandIndex)
   {
      hr = E_INVALIDARG;
   }
   else
   {
      *gridIndex = m_StrandToGridMap[strandIndex];
   }

   return hr;
}

STDMETHODIMP CStrandGrid::StrandIndexToGridIndexEx(/*[in]*/ILongArray* fill, /*[in]*/ StrandIndexType strandIndex, /*[out,retval]*/ GridIndexType* gridIndex)
{
   // given a strand fill sequence (fill), find the grid index for the given strand index
   CHECK_IN(fill);
   CHECK_RETVAL(gridIndex);

   ValidateGrid();

   HRESULT hr = S_OK;

   // get number of gird points
   GridIndexType nGridPoints = m_GridPoints.size();

   // get number of points in the fill sequence
   CollectionIndexType nFillPoints;
   fill->get_Count(&nFillPoints);

   // limit the loop to the min of these
   GridIndexType nPoints = min(nGridPoints, (GridIndexType)nFillPoints);

   StrandIndexType nStrands = 0;
   GridIndexType fillIdx;
   for( fillIdx = 0; fillIdx < nPoints; fillIdx++)
   {
      StrandIndexType nStrandsAtGridPoint;
      fill->get_Item(fillIdx, &nStrandsAtGridPoint);
      ATLASSERT(0 <= nStrandsAtGridPoint && nStrandsAtGridPoint <= 2);

      nStrands += nStrandsAtGridPoint;

      if (strandIndex <= nStrands)
      {
         *gridIndex = fillIdx;
         break; // found what we were looking for... break out of the loop
      }
   }

   if ( nPoints <= fillIdx )
      hr = E_INVALIDARG;  // the fill sequence was bad (the grid index was never found)

   return hr;
}


STDMETHODIMP CStrandGrid::get_CG( /*[out]*/Float64* cgx, /*[out]*/Float64* cgy)
{
   CHECK_RETVAL(cgx);
   CHECK_RETVAL(cgy);

   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   *cgx = 0.0;
   *cgy = 0.0;

   Float64 sumY = 0.0;
   StrandIndexType nStrandsUsed = 0;
   for (GridCollectionIterator it=m_GridPoints.begin(); it!=m_GridPoints.end(); it++)
   {
      const GridPoint2d& gridPoint = *it;
      StrandIndexType nStrandsAtGridPoint = gridPoint.nStrandsAtGridPoint;

      if ( 0 < nStrandsAtGridPoint)
      {
         Float64 old_x = gridPoint.dPointX;
         Float64 old_y = gridPoint.dPointY;
      
         Float64 x, y;
         AdjustStrand(old_x,old_y,&x, &y);

         if ( nStrandsAtGridPoint == 1)
         {
            sumY += y;
         }
         else if (nStrandsAtGridPoint == 2)
         {
            sumY += y+y;
         }

         nStrandsUsed += nStrandsAtGridPoint;
      }
   }

   if ( 0 < nStrandsUsed )
   {
      *cgx = 0.0;
      *cgy = sumY/(Float64)nStrandsUsed;
   }

   return S_OK;
}

STDMETHODIMP CStrandGrid::get_StrandBoundingBox(/*[out,retval]*/IRect2d** box)
{
   CHECK_RETOBJ(box);

   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   CComPtr<IRect2d> bounding_box;
   bounding_box.CoCreateInstance(CLSID_Rect2d);

   StrandIndexType nStrands = GetStrandCount();

   if (0 < nStrands)
   {
      Float64 left(DBL_MAX),   bottom(DBL_MAX);
      Float64 right(-DBL_MAX), top(-DBL_MAX);

      for (GridCollectionIterator it=m_GridPoints.begin(); it!=m_GridPoints.end(); it++)
      {
         const GridPoint2d& gridPoint = *it;
         StrandIndexType nStrandsAtGridPoint = gridPoint.nStrandsAtGridPoint;

         if ( 0 < nStrandsAtGridPoint )
         {
            Float64 old_x = gridPoint.dPointX;
            Float64 old_y = gridPoint.dPointY;
         
            Float64 x, y;
            AdjustStrand(old_x,old_y,&x, &y);


            if ( nStrandsAtGridPoint == 1)
            {
               left   = min(left,  0.0);
               right  = max(right, 0.0);
               bottom = min(bottom, y);
               top    = max(top, y);
            }
            else if (nStrandsAtGridPoint == 2)
            {
               left   = min(left,  -x);
               right  = max(right,  x);
               bottom = min(bottom, y);
               top    = max(top,    y);
            }

         }

         bounding_box->put_Left(left);
         bounding_box->put_Right(right);
         bounding_box->put_Bottom(bottom);
         bounding_box->put_Top(top);
      }
   }


   return bounding_box.CopyTo(box);
}

STDMETHODIMP CStrandGrid::get_FilledGridBounds( /*[out]*/Float64* bottomElev, /*[out]*/Float64* topElev)
{
   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   return get_FilledGridBoundsEx(m_CurrentFill, bottomElev, topElev);
}

STDMETHODIMP CStrandGrid::get_FilledGridBoundsEx(/*[in]*/ILongArray* fill, /*[out]*/Float64* bottomElev, /*[out]*/Float64* topElev)
{
   CHECK_IN(fill);
   CHECK_RETVAL(bottomElev);
   CHECK_RETVAL(topElev);

   ValidateGrid(); // only need to validate grid since fill is external

   Float64 the_min=  Float64_Max;
   Float64 the_max= -Float64_Max;

   GridIndexType nGridPoints = m_GridPoints.size();
   CollectionIndexType nFillPoints;
   fill->get_Count(&nFillPoints);

   GridIndexType nPoints = min((GridIndexType)nFillPoints, nGridPoints);
   Uint32 counter = 0; // counter to keep track of how many elevations get evaluated
   GridIndexType fillIdx;
   for(fillIdx = 0; fillIdx < nPoints; fillIdx++)
   {
      StrandIndexType nStrandsAtGridPoint;
      fill->get_Item(fillIdx, &nStrandsAtGridPoint);
      ATLASSERT(0 <= nStrandsAtGridPoint && nStrandsAtGridPoint <= 2);
     
      if (0 < nStrandsAtGridPoint)
      {
         Float64 yv = m_GridPoints[fillIdx].dPointY + m_VerticalAdjustment;

         the_max = max(the_max,yv);
         the_min = min(the_min,yv);

         counter++;
      }
   }

   if (0 < counter)
   {
      *bottomElev = the_min;
      *topElev = the_max;
   }
   else
   {
      // no elevations were evaluated so use values of 0.0 instead of the out of bounds values
      // the loop started with
      *bottomElev = 0.0;
      *topElev    = 0.0;
   }

   return S_OK;
}


STDMETHODIMP CStrandGrid::GetStrandCountEx(/*[in]*/ILongArray* fill, /*[out,retval]*/ StrandIndexType* count)
{
   CHECK_IN(fill);
   CHECK_RETVAL(count);

   ValidateGrid(); // only need to validate grid since fill is external


   GridIndexType nGridPoints = m_GridPoints.size();
   CollectionIndexType nFillPoints;
   fill->get_Count(&nFillPoints);

   GridIndexType nPoints = min((GridIndexType)nFillPoints, nGridPoints);

   StrandIndexType nStrands = 0;
   for(GridIndexType fillIdx = 0; fillIdx < nPoints; fillIdx++)
   {
      StrandIndexType nStrandsAtGridPoint;
      fill->get_Item(fillIdx, &nStrandsAtGridPoint);
      ATLASSERT(0 <= nStrandsAtGridPoint && nStrandsAtGridPoint <= 2);

      if (nStrandsAtGridPoint == 1)
      {
         nStrands++;
      }
      else if (nStrandsAtGridPoint == 2)
      {
         if (0.0 < m_GridPoints[fillIdx].dPointX)
         {
            // mirror across Y axis = 2 strands
            nStrands += 2;
         }
         else
         {
            // strand on Y axis
            nStrands++;
         }
      }
   }

   *count = nStrands;

   return S_OK;
}

STDMETHODIMP CStrandGrid::GetStrandPositionsEx(/*[in]*/ILongArray* fill, /*[out,retval]*/IPoint2dCollection** points)
{
   CHECK_IN(fill);
   CHECK_RETOBJ(points);

   ValidateFill();

   CComPtr<IPoint2dCollection> local_points;
   HRESULT hr = local_points.CoCreateInstance(CLSID_Point2dCollection);
   if ( FAILED(hr) )
      return hr;

   GridIndexType nGridPoints = m_GridPoints.size();
   CollectionIndexType nFillPoints;
   fill->get_Count(&nFillPoints);

   GridIndexType nPoints = min((GridIndexType)nFillPoints, nGridPoints);

   for(GridIndexType fillIdx = 0; fillIdx < nPoints; fillIdx++)
   {
      const GridPoint2d& gpoint = m_GridPoints[fillIdx];
      StrandIndexType nStrandsAtGridPoint;
      fill->get_Item(fillIdx, &nStrandsAtGridPoint);
      ATLASSERT(0 <= nStrandsAtGridPoint && nStrandsAtGridPoint <= 2);

      if (0 < nStrandsAtGridPoint)
      {
         Float64 old_x = gpoint.dPointX;
         Float64 old_y = gpoint.dPointY;

         Float64 x, y;
         this->AdjustStrand(old_x,old_y,&x, &y);


         if (nStrandsAtGridPoint == 1)
         {
            CComPtr<IPoint2d> point;
            HRESULT hr = m_Point2dFactory->CreatePoint(&point);
            if ( FAILED(hr) )
               return hr;
         
            // single strands must always be placed at center
            point->Move(0.0, y);
            local_points->Add(point);
         }
         else if (1 < nStrandsAtGridPoint)
         {
            // place two strands at +/-X
            CComPtr<IPoint2d> point;
            HRESULT hr = m_Point2dFactory->CreatePoint(&point);
            if ( FAILED(hr) )
               return hr;
         
            point->Move(x, y);
            local_points->Add(point);

            CComPtr<IPoint2d> point2;
            hr = m_Point2dFactory->CreatePoint(&point2);
            if ( FAILED(hr) )
               return hr;

            point2->Move(-x, y);
            local_points->Add(point2);
         }
      }
   }

   return local_points.CopyTo(points);
}

STDMETHODIMP CStrandGrid::get_CGEx(/*[in]*/ILongArray* fill, /*[out]*/Float64* cgx, /*[out]*/Float64* cgy)
{
   CHECK_IN(fill);
   CHECK_RETVAL(cgx);
   CHECK_RETVAL(cgy);

   ValidateGrid(); // only need to validate grid since fill is external

   GridIndexType nGridPoints = m_GridPoints.size();
   CollectionIndexType nFillPoints;
   fill->get_Count(&nFillPoints);

   GridIndexType nPoints = min((GridIndexType)nFillPoints, nGridPoints);

   Uint32 nPointsUsed = 0;
   Float64 y_sum = 0.0;

   *cgx = 0.0;
   *cgy = 0.0;

   for(GridIndexType fillIdx = 0; fillIdx < nPoints; fillIdx++)
   {
      StrandIndexType nStrandsAtGridPoint;
      fill->get_Item(fillIdx, &nStrandsAtGridPoint);
      ATLASSERT(0 <= nStrandsAtGridPoint && nStrandsAtGridPoint <= 2);

      if (0 < nStrandsAtGridPoint)
      {
         const GridPoint2d& gpoint = m_GridPoints[fillIdx];
         Float64 old_x = gpoint.dPointX;
         Float64 old_y = gpoint.dPointY;

         Float64 x, y;
         this->AdjustStrand(old_x,old_y,&x, &y);


         if (nStrandsAtGridPoint == 1)
         {
            nPointsUsed++;
            y_sum += y;
         }
         else if (1 < nStrandsAtGridPoint)
         {
            nPointsUsed+=2;
            y_sum += (y+y);
         }
      }
   }

   *cgx = 0.0;
   if ( nPointsUsed == 0 )
      *cgy = 0.0;
   else
      *cgy = y_sum/(Float64)nPointsUsed;

   return S_OK;
}

STDMETHODIMP CStrandGrid::get_StrandBoundingBoxEx(/*[in]*/ILongArray* fill, /*[out,retval]*/IRect2d** box)
{
   CHECK_IN(fill);
   CHECK_RETOBJ(box);

   ValidateGrid(); // only need to validate grid since fill is external

   CComPtr<IRect2d> bound_box;
   HRESULT hr = bound_box.CoCreateInstance(CLSID_Rect2d);
   if ( FAILED(hr) )
       return hr;

   GridIndexType nGridPoints = m_GridPoints.size();
   CollectionIndexType nFillPoints;
   fill->get_Count(&nFillPoints);

   GridIndexType nPoints = min((GridIndexType)nFillPoints, nGridPoints);
//   ATLASSERT(nFillPoints==nGridPoints); // values should match, but will run if not

   if (0 < nPoints)
   {
      Float64 left(Float64_Max),   bottom(Float64_Max);
      Float64 right(-Float64_Max), top(-Float64_Max);

      for(GridIndexType fillIdx = 0; fillIdx < nPoints; fillIdx++)
      {
         const GridPoint2d& gpoint = m_GridPoints[fillIdx];
         Float64 old_x = gpoint.dPointX;
         Float64 old_y = gpoint.dPointY;

         StrandIndexType nStrandsAtGridPoint;
         fill->get_Item(fillIdx, &nStrandsAtGridPoint);
         ATLASSERT(0 <= nStrandsAtGridPoint && nStrandsAtGridPoint <= 2);

         Float64 x, y;
         this->AdjustStrand(old_x,old_y,&x, &y);

         if ( nStrandsAtGridPoint == 1 || x == 0.0)
         {
            left   = min(left,  0.0);
            right  = max(right, 0.0);
            bottom = min(bottom, y);
            top    = max(top, y);
         }
         else if (nStrandsAtGridPoint == 2)
         {
            left   = min(left,  -x);
            right  = max(right,  x);
            bottom = min(bottom, y);
            top    = max(top,    y);
         }

         bound_box->put_Left(left);
         bound_box->put_Right(right);
         bound_box->put_Bottom(bottom);
         bound_box->put_Top(top);
      }
   }

   return bound_box.CopyTo(box);
}

STDMETHODIMP CStrandGrid::get_RowsWithStrand(/*[out,retval]*/RowIndexType* nRows)
{
   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   CHECK_RETVAL(nRows);

   *nRows = m_Rows.size();

   return S_OK;
}

STDMETHODIMP CStrandGrid::get_NumStrandsInRow(/*[in]*/RowIndexType rowIdx,/*[out,retval]*/StrandIndexType* nStrands)
{
   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   if ( rowIdx < 0 || (RowIndexType)m_Rows.size() <= rowIdx )
      return E_INVALIDARG; // bad row index

   CHECK_RETVAL(nStrands);

   RowIndexType currentRowIdx = 0;
   std::set<Row>::const_iterator iter;
   for ( iter = m_Rows.begin(); iter != m_Rows.end(); iter++ )
   {
      if (rowIdx == currentRowIdx)
      {
         StrandIndexType nStrandsThisRow = 0;
         const Row::GridPointsType& grid_points_in_row = iter->GridPoints;
         Row::GridPointsType::const_iterator gridPointIter;
         for (gridPointIter = grid_points_in_row.begin(); gridPointIter != grid_points_in_row.end(); gridPointIter++)
         {
            GridIndexType gridPointIdx = *gridPointIter;
            nStrandsThisRow += m_GridPoints[gridPointIdx].nStrandsAtGridPoint;
         }

         *nStrands = nStrandsThisRow;
         break;
      }

      currentRowIdx++;
   }

   return S_OK;
}

STDMETHODIMP CStrandGrid::get_StrandsInRow(/*[in]*/RowIndexType rowIdx,/*[out,retval]*/ILongArray** gridIndex)
{
   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   if ( (RowIndexType)m_Rows.size() <= rowIdx )
      return E_INVALIDARG; // row index is out of range

   CHECK_RETOBJ(gridIndex);

   CComPtr<ILongArray> strandIndicies;
   strandIndicies.CoCreateInstance(CLSID_LongArray);

   RowIndexType currentRowIdx = 0;
   std::set<Row>::const_iterator iter;

   // loop over all of the rows
   for ( iter = m_Rows.begin(); iter != m_Rows.end(); iter++ )
   {
      const Row& row = *iter;

      if (rowIdx == currentRowIdx)
      {
         // this is the row we are looking for

         // loop over all the grid points in this row
         const Row::GridPointsType& grid_points_in_row = row.GridPoints;
         Row::GridPointsType::const_iterator gridPointIter;
         for (gridPointIter = grid_points_in_row.begin(); gridPointIter != grid_points_in_row.end(); gridPointIter++)
         {
            GridIndexType gridPointInRowIdx = *gridPointIter;

            StrandIndexType nStrandsAtGridPoint = m_GridPoints[gridPointInRowIdx].nStrandsAtGridPoint;

            ATLASSERT(0 < nStrandsAtGridPoint); // if nStrandsAtGridPoint == 0, StrandPositionIndex is undefined
            for ( StrandIndexType idx = 0; idx < nStrandsAtGridPoint; idx++ )
            {
               StrandIndexType strandPositionIndex = m_GridPoints[gridPointInRowIdx].StrandPositionIndex[idx];
               strandIndicies->Add(strandPositionIndex);
            }
         }

         break;
      }

      currentRowIdx++;
   }

   return strandIndicies.CopyTo(gridIndex);
}

STDMETHODIMP CStrandGrid::GetStrandDebondCount(/*[out,retval]*/ StrandIndexType* count)
{
   CHECK_RETVAL(count);

   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   StrandIndexType nDebondedStrands = 0;
   for (GridCollectionIterator iter = m_GridPoints.begin(); iter != m_GridPoints.end(); iter++)
   {
      GridPoint2d& gridPoint = *iter;
      if ( 0 < gridPoint.nStrandsAtGridPoint && gridPoint.bIsDebonded )
         nDebondedStrands += gridPoint.nStrandsAtGridPoint;
   }

   *count = nDebondedStrands;

   return (0 <= nDebondedStrands ? S_OK : S_FALSE);
}


STDMETHODIMP CStrandGrid::DebondStrandByGridIndex(/*[in]*/GridIndexType grdIndex,/*[in]*/Float64 l1,/*[in]*/Float64 l2)
{
   ValidateGrid();

   if ( grdIndex < 0 || (GridIndexType)m_GridPoints.size() <= grdIndex )
      return E_INVALIDARG;

   GridPoint2d& sp = m_GridPoints[grdIndex];
   sp.bIsDebonded = true;
   sp.DebondLength[0] = l1;
   sp.DebondLength[1] = l2;

   AddDebondSection(grdIndex,l1,l2);

   return S_OK;
}

STDMETHODIMP CStrandGrid::GetDebondedStrandsByGridIndex(/*[out,retval]*/ILongArray** grdIndexes)
{
   CHECK_RETOBJ(grdIndexes);

   ValidateGrid();

   CComPtr<ILongArray> gridPointIndiciesForDebondedStrands;
   gridPointIndiciesForDebondedStrands.CoCreateInstance(CLSID_LongArray);

   GridIndexType gridPointIndex = 0;
   for (GridCollectionIterator iter = m_GridPoints.begin(); iter != m_GridPoints.end(); iter++)
   {
      const GridPoint2d& gridPoint = *iter;
      if (gridPoint.bIsDebonded)
      {
         gridPointIndiciesForDebondedStrands->Add(gridPointIndex);
      }

      gridPointIndex++;
   }

   return gridPointIndiciesForDebondedStrands.CopyTo(grdIndexes);
}

STDMETHODIMP CStrandGrid::GetDebondLengthByGridIndex(/*[in]*/GridIndexType grdIndex,/*[out]*/Float64* YCoord, /*[out]*/Float64* l1,/*[out]*/Float64* l2)
{
   CHECK_RETVAL(l1);
   CHECK_RETVAL(l2);

   ValidateGrid();

   if ( grdIndex < 0 || (GridIndexType)m_GridPoints.size() <= grdIndex )
      return E_INVALIDARG;

   GridPoint2d& sp = m_GridPoints[grdIndex];
   *YCoord = sp.dPointY + m_VerticalAdjustment;

   if (sp.bIsDebonded)
   {
      *l1 = sp.DebondLength[0];
      *l2 = sp.DebondLength[1];
      return S_OK;
   }
   else
   {
      *l1 = 0.0;
      *l2 = 0.0;
   }

   return S_FALSE;
}

STDMETHODIMP CStrandGrid::GetDebondLengthByPositionIndex(/*[in]*/StrandIndexType positionIndex, /*[out]*/Float64* YCoord, /*[out]*/Float64* l1,/*[out]*/Float64* l2)
{
   CHECK_RETVAL(l1);
   CHECK_RETVAL(l2);

   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   GridIndexType grid_idx;
   hr = StrandIndexToGridIndex(positionIndex, &grid_idx);
   if (FAILED(hr))
      return hr;

   return GetDebondLengthByGridIndex(grid_idx, YCoord, l1, l2);
}

STDMETHODIMP CStrandGrid::GetBondedLengthByPositionIndex(/*[in]*/StrandIndexType positionIndex, /*[in]*/Float64 distFromStart, /*[in]*/Float64 girderLength,
                                              /*[out]*/Float64* YCoord, /*[out]*/Float64* leftBond, /*[out]*/Float64* rightBond)
{
   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   GridIndexType grid_idx;
   hr = StrandIndexToGridIndex(positionIndex, &grid_idx);
   if (FAILED(hr))
      return hr;

   return GetBondedLengthByGridIndex(grid_idx, distFromStart, girderLength, YCoord, leftBond, rightBond);
}

STDMETHODIMP CStrandGrid::GetBondedLengthByGridIndex(/*[in]*/GridIndexType grdIndex, /*[in]*/Float64 distFromStart, /*[in]*/Float64 girderLength,
                                              /*[out]*/Float64* YCoord, /*[out]*/Float64* leftBond, /*[out]*/Float64* rightBond)
{
   if (girderLength<0.0 || distFromStart<0.0 || girderLength < distFromStart)
   {
      ATLASSERT(0);
      return E_INVALIDARG;
   }

   ValidateGrid();

   if ( grdIndex < 0 || (GridIndexType)m_GridPoints.size() <= grdIndex )
   {
      ATLASSERT(0);
      return E_INVALIDARG;
   }


   GridPoint2d& gridPoint = m_GridPoints[grdIndex];
   *YCoord = gridPoint.dPointY + m_VerticalAdjustment;

   if (gridPoint.bIsDebonded)
   {
      *leftBond = distFromStart - gridPoint.DebondLength[0];
      if (*leftBond<0.0)
      {
         *leftBond=0.0;
         *rightBond=0.0;
      }
      else
      {
         *rightBond = girderLength - gridPoint.DebondLength[1] - distFromStart;
         if (*rightBond<0.0)
         {
            *leftBond=0.0;
            *rightBond=0.0;
         }
      }

      return S_OK;
   }
   else
   {
      *leftBond = distFromStart;
      *rightBond = girderLength-distFromStart;
      return S_FALSE;
   }

}



STDMETHODIMP CStrandGrid::GetStrandsDebondedByPositionIndex(/*[in]*/Float64 distFromStart,/*[in]*/Float64 girderLength, /*[out,retval]*/ILongArray** positionIndexes)
{
   CHECK_RETOBJ(positionIndexes);

   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   if (distFromStart<0.0 || girderLength < distFromStart)
   {
      return E_INVALIDARG;
   }

   CComPtr<ILongArray> array;
   array.CoCreateInstance(CLSID_LongArray);

   Float64 gl2 =girderLength/2.0;

   if (distFromStart < gl2)
   {
      // at left end of girder
      for (GridCollectionIterator iter = m_GridPoints.begin(); iter != m_GridPoints.end(); iter++)
      {
         // first validate fill data and clean up if needed
         const GridPoint2d& gp = *iter;
         StrandIndexType nStrandsAtGridPoint = gp.nStrandsAtGridPoint;

         if (0 < nStrandsAtGridPoint && gp.bIsDebonded)
         {
            Float64 debond_length = gp.DebondLength[0];

            ATLASSERT(debond_length < gl2); // should be blocked in UI

            if ( distFromStart <= debond_length )
            {
               array->Add(gp.StrandPositionIndex[0]);

               if (nStrandsAtGridPoint == 2)
                  array->Add(gp.StrandPositionIndex[1]);
            }
         }
      }
   }
   else
   {
      // at right end of girder
      Float64 dist_from_end = girderLength-distFromStart;

      for (GridCollectionIterator iter = m_GridPoints.begin(); iter != m_GridPoints.end(); iter++)
      {
         // first validate fill data and clean up if needed
         const GridPoint2d& gp = *iter;
         StrandIndexType nStrandsAtGridPoint = gp.nStrandsAtGridPoint;

         if (0 < nStrandsAtGridPoint && gp.bIsDebonded)
         {
            Float64 debond_length = gp.DebondLength[1];

            ATLASSERT(debond_length < gl2); // should be blocked in UI

            if ( dist_from_end <= debond_length )
            {
               array->Add(gp.StrandPositionIndex[0]);

               if (nStrandsAtGridPoint == 2)
                  array->Add(gp.StrandPositionIndex[1]);
            }
         }
      }
   }

   return array.CopyTo(positionIndexes);
}


STDMETHODIMP CStrandGrid::get_StrandDebondInRow(/*[in]*/ RowIndexType rowIdx,/*[out,retval]*/StrandIndexType* nStrands)
{
   CHECK_RETVAL(nStrands);

   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   if ( rowIdx < 0 || (RowIndexType)m_Rows.size() <= rowIdx )
      return E_INVALIDARG;

   // advance the iterator to the correct location
   std::set<Row>::const_iterator iter = m_Rows.begin();
   for ( RowIndexType i = 0; i < rowIdx; i++ )
      iter++;

   const Row& row = *iter;
   *nStrands = 0;

   Row::GridPointsType::const_iterator gridPointInRowIter;
   for ( gridPointInRowIter = row.GridPoints.begin(); gridPointInRowIter != row.GridPoints.end(); gridPointInRowIter++ )
   {
      GridIndexType gridPointInRowIndex = *gridPointInRowIter;
      const GridPoint2d& gridPoint = m_GridPoints[gridPointInRowIndex];

      if ( 0 < gridPoint.nStrandsAtGridPoint && gridPoint.bIsDebonded )
         (*nStrands)+= gridPoint.nStrandsAtGridPoint;
   }

   return S_OK;
}

STDMETHODIMP CStrandGrid::IsExteriorStrandDebondedInRow(/*[in]*/ RowIndexType rowIndex,/*[out,retval]*/VARIANT_BOOL* bResult)
{
   CHECK_RETVAL(bResult);

   HRESULT hr = ValidateFill();
   if (FAILED(hr))
      return hr;

   if ( rowIndex < 0 || (RowIndexType)m_Rows.size() <= rowIndex )
      return E_INVALIDARG;

   // advance the iterator
   std::set<Row>::const_iterator iter = m_Rows.begin();
   for ( RowIndexType i = 0; i < rowIndex; i++ )
      iter++;

   // this is the row we want
   const Row& row = *iter;

   GridIndexType exteriorGridPointIndex; // grid point index of the exterior strand in this row

   Float64 xmax = 0; // distance from Y axis to grid point

   // iterate over all the grid points in this row
   Row::GridPointsType::const_iterator gridPointInRowIter;
   for ( gridPointInRowIter = row.GridPoints.begin(); gridPointInRowIter != row.GridPoints.end(); gridPointInRowIter++ )
   {
      GridIndexType gridPointInRowIndex = *gridPointInRowIter;
      const GridPoint2d& gridPoint = m_GridPoints[gridPointInRowIndex];

      Float64 x = gridPoint.dPointX;
      if ( xmax <= fabs(x) )
      {
         xmax = fabs(x);
         exteriorGridPointIndex = gridPointInRowIndex;
      }
   }

   const GridPoint2d& exteriorGridPoint = m_GridPoints[exteriorGridPointIndex];
   *bResult = (exteriorGridPoint.bIsDebonded ? VARIANT_TRUE : VARIANT_FALSE);

   return S_OK;
}

STDMETHODIMP CStrandGrid::GetDebondSections(/*[out]*/IDblArray** arrLeft,/*[out]*/IDblArray** arrRight)
{
   CHECK_RETOBJ(arrLeft);
   CHECK_RETOBJ(arrRight);

   CComPtr<IDblArray> objLeft, objRight;
   objLeft.CoCreateInstance(CLSID_DblArray);
   objRight.CoCreateInstance(CLSID_DblArray);

   std::set<DebondSection>::iterator iter;
   for ( iter = m_LeftSections.begin(); iter != m_LeftSections.end(); iter++ )
   {
      DebondSection& section = *iter;
      objLeft->Add( section.Location );
   }

   std::set<DebondSection>::reverse_iterator riter;
   for ( riter = m_RightSections.rbegin(); riter != m_RightSections.rend(); riter++ )
   {
      DebondSection& section = *riter;
      objRight->Add( section.Location );
   }

   (*arrLeft) = objLeft;
   (*arrLeft)->AddRef();

   (*arrRight) = objRight;
   (*arrRight)->AddRef();

   return S_OK;
}

STDMETHODIMP CStrandGrid::GetDebondAtLeftSection(/*[in]*/SectionIndexType sectionIdx,/*[out,retval]*/ILongArray** strandIndexes)
{
   // find section from left end
   CHECK_RETOBJ(strandIndexes);
   if ( sectionIdx < 0 || (SectionIndexType)m_LeftSections.size() <= sectionIdx )
      return E_INVALIDARG;

   // loop over the sections until the iterator is at the correct position
   std::set<DebondSection>::iterator iter;
   SectionIndexType idx = 0;
   for ( iter = m_LeftSections.begin(); iter != m_LeftSections.end() && idx != sectionIdx; iter++, idx++ )
   {
   }

   ATLASSERT(iter != m_LeftSections.end() && idx == sectionIdx );

   DebondSection& rsection = *iter;

   return GetDebondAtSection(rsection,strandIndexes);
}

STDMETHODIMP CStrandGrid::GetDebondAtRightSection(/*[in]*/SectionIndexType sectionIdx,/*[out,retval]*/ILongArray** strandIndexes)
{
   // find section from right end
   CHECK_RETOBJ(strandIndexes);
   if ( sectionIdx < 0 || (SectionIndexType)m_RightSections.size() <= sectionIdx )
      return E_INVALIDARG;

   // reverse loop over the sections until the iterator is at the correct position
   std::set<DebondSection>::reverse_iterator riter;
   SectionIndexType idx = 0;
   for ( riter = m_RightSections.rbegin(); riter != m_RightSections.rend() && idx != sectionIdx; riter++, idx++ )
   {
   }

   ATLASSERT(riter != m_RightSections.rend() && idx == sectionIdx );
 
   DebondSection& rsection = *riter;

   return GetDebondAtSection(rsection,strandIndexes);
}

STDMETHODIMP CStrandGrid::ClearDebonding()
{
   m_LeftSections.clear();
   m_RightSections.clear();

   typedef std::vector<GridPoint2d> GridCollection;
   GridCollectionIterator iter;
   for ( iter = m_GridPoints.begin(); iter != m_GridPoints.end(); iter++ )
   {
      GridPoint2d& gp = *iter;
      gp.bIsDebonded = false;
      gp.DebondLength[0] = 0;
      gp.DebondLength[1] = 0;
   };

   return S_OK;
}

//////// Private //////////////////////
///////////////////////////////////////
void CStrandGrid::AddDebondSection(GridIndexType gridIdx,Float64 left,Float64 right)
{
  // Place this debond point in a section
   DebondSection target;
   target.Location = left;
   std::set<DebondSection>::iterator found = m_LeftSections.find(target);
   if ( found != m_LeftSections.end() )
   {
      DebondSection& section = *found;
      section.GridPoints.insert(gridIdx);
   }
   else
   {
      DebondSection section;
      section.Location = target.Location;
      section.GridPoints.insert( gridIdx );
      std::pair<std::set<DebondSection>::iterator,bool> result = m_LeftSections.insert(section);
      ATLASSERT(result.second == true);
   }

   target.Location = right;
   found = m_RightSections.find(target);
   if ( found != m_RightSections.end() )
   {
      DebondSection& section = *found;
      section.GridPoints.insert(gridIdx);
   }
   else
   {
      DebondSection section;
      section.Location = target.Location;
      section.GridPoints.insert( gridIdx );
      std::pair<std::set<DebondSection>::iterator,bool> result = m_RightSections.insert(section);
      ATLASSERT(result.second == true);
   }
}

void CStrandGrid::InvalidateGrid()
{
   m_bUpdateGrid = true;
   InvalidateFill();
}

void CStrandGrid::ValidateGrid()
{
   if (m_bUpdateGrid)
   {
      m_GridBoundingBox->SetEmpty();
      m_MaxFill->Clear();
      m_MaxFill->Reserve(m_GridPoints.size());
      m_MaxCount=0;
      for (GridCollectionIterator it=m_GridPoints.begin(); it!=m_GridPoints.end(); it++)
      {
         const GridPoint2d& pnt = *it;

         m_GridBoundingBox->BoundPoint(pnt.dPointX , pnt.dPointY);

         // if there is a postive X value, then two strands can be placed.
         StrandIndexType val = (pnt.dPointX > 0.0) ? 2 : 1;

         m_MaxFill->Add(val);
         m_MaxCount+=val;
      }

      m_bUpdateGrid = false;
   }
}

void CStrandGrid::InvalidateFill()
{
   m_bUpdateFill = true;
}

HRESULT CStrandGrid::ValidateFill()
{
   if (m_bUpdateFill)
   {
      ValidateGrid();

      m_StrandToGridMap.clear();
      m_CurrentFill->ReDim(m_GridPoints.size());
      GridIndexType gridPointIdx = 0;
      GridIndexType positionIdx = 0;
      for (GridCollectionIterator iter = m_GridPoints.begin(); iter != m_GridPoints.end(); iter++)
      {
         GridPoint2d& gridPoint = *iter;

         // first validate fill data and clean up if needed
         StrandIndexType nStrandsAtGridPoint = gridPoint.nStrandsAtGridPoint;

         if (0 <= nStrandsAtGridPoint && nStrandsAtGridPoint <= 2)
         {
            m_CurrentFill->put_Item(gridPointIdx, nStrandsAtGridPoint);
         }
         else
         {
            // strand placement data is corrupt
            ATLASSERT(0);
            nStrandsAtGridPoint = 0;
            m_CurrentFill->put_Item(gridPointIdx, 0);
         }

         // map filled strand point positions to grid location and reverse
         gridPoint.StrandPositionIndex[0] = -1;
         gridPoint.StrandPositionIndex[1] = -1;

         if (0 < nStrandsAtGridPoint)
         {
            gridPoint.StrandPositionIndex[0] = positionIdx++;

            m_StrandToGridMap.push_back(gridPointIdx);
         
            if (nStrandsAtGridPoint == 2)
            {
               gridPoint.StrandPositionIndex[1] = positionIdx++;

               m_StrandToGridMap.push_back(gridPointIdx);
            }
         }

         gridPointIdx++;
      }

      // compute filled rows
      m_Rows.clear();

      StrandIndexType nStrands = GetStrandCount();
      if (0 < nStrands)
      {
         GridIndexType gridPointIdx = 0;
         for (GridCollectionIterator iter = m_GridPoints.begin(); iter != m_GridPoints.end(); iter++)
         {
            const GridPoint2d& gridPoint = *iter;
            StrandIndexType nStrandsAtGridPoint = gridPoint.nStrandsAtGridPoint;

            // rows
            if (0 < nStrandsAtGridPoint)
            {
               Float64 x = gridPoint.dPointX;
               Float64 y = gridPoint.dPointY;
               
               // note that row heights are unadjusted
               Row target;
               target.Elevation = y;

               std::set<Row>::iterator found = m_Rows.find(target);
               if ( found != m_Rows.end() )
               {
                  Row& row = *found;
                  row.GridPoints.push_back(gridPointIdx);
               }
               else
               {
                  target.GridPoints.push_back( gridPointIdx );
                  std::pair<std::set<Row>::iterator,bool> result = m_Rows.insert(target);
                  ATLASSERT(result.second == true);
               }
            }

            gridPointIdx++;
         }
      }

      m_bUpdateFill = false;
   }

   return S_OK;
}

void CStrandGrid::AdjustStrand(Float64 originalX, Float64 originalY, Float64* newX, Float64* newY )
{
   if (m_pStrandMover)
   {
      m_pStrandMover->TranslateStrand( originalX, originalY, m_VerticalAdjustment, newX, newY );
   }
   else
   {
      // by default just translate verticaly
      *newX = originalX;
      *newY = originalY + m_VerticalAdjustment;
   }
}

StrandIndexType CStrandGrid::GetStrandCount()
{
   return m_StrandToGridMap.size();
}

HRESULT CStrandGrid::GetDebondAtSection(DebondSection& rSection,/*[out,retval]*/ILongArray** strandIndexes)
{
   // Gets the strand indicies of the strands that are debonded at a section
   CComPtr<ILongArray> array;
   array.CoCreateInstance(CLSID_LongArray);

   DebondSection::GridPointsType::iterator gridPointsAtSectionIter;
   for (gridPointsAtSectionIter = rSection.GridPoints.begin(); gridPointsAtSectionIter != rSection.GridPoints.end(); gridPointsAtSectionIter++)
   {
      GridIndexType gridPointAtSectionIndex = *gridPointsAtSectionIter;
      const GridPoint2d& gridPointAtSection = m_GridPoints[gridPointAtSectionIndex];

      if (0 < gridPointAtSection.nStrandsAtGridPoint)
      {
         ATLASSERT(gridPointAtSection.bIsDebonded);

         array->Add(gridPointAtSection.StrandPositionIndex[0]);

         if (1 < gridPointAtSection.nStrandsAtGridPoint)
         {
            array->Add(gridPointAtSection.StrandPositionIndex[1]);
         }
      }
   }

   return array.CopyTo(strandIndexes);

}
