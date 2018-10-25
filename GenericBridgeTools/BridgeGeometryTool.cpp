///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2013  Washington State Department of Transportation
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

// BridgeGeometryTool.cpp : Implementation of CBridgeGeometryTool
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "BridgeGeometryTool.h"
#include "Helpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBridgeGeometryTool
HRESULT CBridgeGeometryTool::FinalConstruct()
{
   HRESULT hr = m_CogoEngine.CoCreateInstance(CLSID_CogoEngine);
   if ( FAILED(hr) ) 
      return hr;

   return S_OK;
}

void CBridgeGeometryTool::FinalRelease()
{
}

STDMETHODIMP CBridgeGeometryTool::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBridgeGeometryTool
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CBridgeGeometryTool::Point(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx, Float64 distFromStartOfGirder, IPoint2d** point)
{
   // distFromStartOfSpan is measured along the girder line, from the intersection of the CL Pier and the CL girder
#pragma Reminder("UPDATE: Should be using actual path for the girderline")
   // Assuming a straight path for now (girder line paths have not been implemented yet)
   CComPtr<ICogoInfo> cogoinfo;
   bridge->get_CogoInfo(&cogoinfo);

   CogoElementKey startID, endID;
   cogoinfo->get_GirderEndPointID(spanIdx,gdrIdx,etStart,&startID);
   cogoinfo->get_GirderEndPointID(spanIdx,gdrIdx,etEnd,  &endID);

   CComPtr<ICogoModel> cogomodel;
   bridge->get_CogoModel(&cogomodel);

   CComPtr<IPointCollection> points;
   cogomodel->get_Points(&points);

   CComPtr<IPoint2d> p1, p2;
   points->get_Item(startID,&p1);
   points->get_Item(endID,  &p2);

   CComPtr<ILocate2> locate;
   m_CogoEngine->get_Locate(&locate);

   locate->PointOnLine(p1,p2,distFromStartOfGirder,0.00,point);

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::StationAndOffset(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,Float64 distFromStartOfGirder,IStation** station,Float64* offset)
{
   // distFromStartOfSpan is measured along the girder line, from the intersection of the CL pier and the CL girder

   CComPtr<IPoint2d> point;
   Point(bridge,spanIdx,gdrIdx,distFromStartOfGirder,&point);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   alignment->Offset(point,station,offset);

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::GirderPathOffset(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,VARIANT varStation,Float64* offset)
{
   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   // get point on alignment at station
   CComPtr<IPoint2d> a_point;
   alignment->LocatePoint(varStation,omtAlongDirection, 0.00,CComVariant(0.00),&a_point);

   // Create a line that represents the girder path
   CComPtr<ICogoInfo> cogoinfo;
   bridge->get_CogoInfo(&cogoinfo);

   CogoElementKey startID, endID;
   cogoinfo->get_PierGirderIntersectionPointID(spanIdx,   gdrIdx, qcbAfter,  &startID);
   cogoinfo->get_PierGirderIntersectionPointID(spanIdx+1, gdrIdx, qcbBefore, &endID);

   CComPtr<ICogoModel> cogomodel;
   bridge->get_CogoModel(&cogomodel);

   CComPtr<IPointCollection> points;
   cogomodel->get_Points(&points);

   CComPtr<IPoint2d> p1, p2;
   points->get_Item(startID,&p1);
   points->get_Item(endID,  &p2);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->ThroughPoints(p1,p2);

   // Going to use the geometric utility object
   CComPtr<IGeomUtil2d> geom_util;
   geom_util.CoCreateInstance(CLSID_GeomUtil);
   ATLASSERT(geom_util != NULL);

   // Find the shortest distance from the point on the alignment to the
   // line representing the girder path. If the alignment point is on the right
   // of the girder path, offset will be > 0. This means the girder path is
   // offset to the left of the alignment so the offset that we want has the opposite
   // sign.
   geom_util->ShortestDistanceToPoint(line,a_point,offset);
   (*offset) *= -1;

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::GirderLineBearing(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,IDirection** direction)
{
   CComPtr<ICogoInfo> cogoinfo;
   bridge->get_CogoInfo(&cogoinfo);

   CogoElementKey startID, endID;
   cogoinfo->get_PierGirderIntersectionPointID(spanIdx,   gdrIdx, qcbAfter,  &startID);
   cogoinfo->get_PierGirderIntersectionPointID(spanIdx+1, gdrIdx, qcbBefore, &endID);

   CComPtr<ICogoModel> cogomodel;
   bridge->get_CogoModel(&cogomodel);

   CComPtr<IPointCollection> points;
   cogomodel->get_Points(&points);

   CComPtr<IPoint2d> p1, p2;
   points->get_Item(startID,&p1);
   points->get_Item(endID,  &p2);

   CComPtr<IMeasure2> measure;
   m_CogoEngine->get_Measure(&measure);

   return measure->Direction(p1,p2,direction);
}

STDMETHODIMP CBridgeGeometryTool::GirderLinePoint(IGenericBridge* bridge,Float64 distFromStartOfBridge,GirderIndexType gdrIdx,SpanIndexType* spanIdx,Float64* distFromStartOfSpan)
{
   // Determine the span and the distance along that span which correspond to a 
   // distance from the start of the bridge and a girder line
   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   CComPtr<IEnumPiers> enum_piers;
   piers->get__EnumPiers(&enum_piers);

   CComPtr<IPier> pier;
   enum_piers->Next(1,&pier,NULL);

   CComPtr<IStation> objStartStation;
   pier->get_Station(&objStartStation);
   Float64 start_station;
   objStartStation->get_Value(&start_station);

   Float64 cut_station = start_station + distFromStartOfBridge;

   PierIndexType nPiers;
   piers->get_Count(&nPiers);
   SpanIndexType nSpans = SpanIndexType(nPiers - 1);

   // Find the span that contains this station
   SpanIndexType spanIndex = 0;
   if ( cut_station < start_station )
   {
      // before start of bridge
      spanIndex = 0;
   }
   else
   {
      Float64 end_station;
      pier.Release();
      while ( enum_piers->Next(1,&pier,NULL) != S_FALSE )
      {
         CComPtr<IStation> station;
         pier->get_Station(&station);
         station->get_Value(&end_station);

         if ( InRange(start_station,cut_station,end_station) )
         {
            // we found the span
            break;
         }

         // next pier... try again
         spanIndex++;
         start_station = end_station;
         pier.Release();
      }

      // don't go beyond the end of the bridge
      if ( nSpans <= spanIndex )
      {
         spanIndex = nSpans-1;
      }
   }

   // Get the start and end points of the girder line in this span

   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);
   CComPtr<ISpan> objSpan;
   spans->get_Item(spanIndex,&objSpan);
   GirderIndexType nGirders;
   objSpan->get_GirderCount(&nGirders);
   if ( gdrIdx == INVALID_INDEX )
   {
      // this means use the right-most girder
      gdrIdx = nGirders - 1;
   }

   if ( nGirders <= gdrIdx )
   {
      *spanIdx = INVALID_INDEX;
      *distFromStartOfSpan = 0;
      return S_FALSE;
   }

   CComPtr<ICogoInfo> cogoinfo;
   bridge->get_CogoInfo(&cogoinfo);
   CogoElementKey startPointID, endPointID;
   PierIndexType prevPierIdx = spanIndex;
   PierIndexType nextPierIdx = prevPierIdx+1;
   cogoinfo->get_PierGirderIntersectionPointID(prevPierIdx, gdrIdx, qcbAfter,  &startPointID);
   cogoinfo->get_PierGirderIntersectionPointID(nextPierIdx, gdrIdx, qcbBefore, &endPointID);

   CComPtr<ICogoModel> cogomodel;
   bridge->get_CogoModel(&cogomodel);

   CComPtr<IPointCollection> points;
   cogomodel->get_Points(&points);

   CComPtr<IPoint2d> startPoint,endPoint;
   points->get_Item(startPointID, &startPoint);
   points->get_Item(endPointID,   &endPoint  );

   // Create a point on the alignment at the cut station
   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   CComPtr<IPoint2d> cut_point;
   alignment->LocatePoint(CComVariant(cut_station),omtAlongDirection, 0.00,CComVariant(0.00),&cut_point);

   // Intersect the normal at the cut point with the girder line
   CComPtr<IDirection> normal;
   alignment->Normal(CComVariant(cut_station),&normal);

   CComPtr<IDirection> gdrBearing;
   GirderLineBearing(bridge,spanIndex,gdrIdx,&gdrBearing);

   CComQIPtr<IIntersect2> intersect(m_CogoEngine);

   CComPtr<IPoint2d> intersect_point;
   intersect->Bearings(cut_point,CComVariant(normal),0.00,startPoint,CComVariant(gdrBearing),0.00,&intersect_point);

   // Determine if the intersect_point actually falls in this span
   CComQIPtr<IMeasure2> measure(m_CogoEngine);

   Float64 girder_distance, cut_distance;
   measure->Distance(startPoint,endPoint,&girder_distance);
   measure->Distance(startPoint,intersect_point,&cut_distance);

   // if the cut is right at the end of the girder, this cleans up the "noise"
   if ( IsEqual(girder_distance,cut_distance) )
      cut_distance = girder_distance;

   Float64 angle = 0;
   // if cut_distance is zero, intersect_point is at the same
   // location as startPoint...

   // determine if the cut location is before, in, or after this span
   // (if the span is skewed cut locations can be off this span)
   //
   // cut_distance is always positive so compute the angle from
   // end to start to intersection... if the angle is not zero, then
   // the intersection is not on the same line as start-end and is not after start
   if ( !IsZero(cut_distance) )
   {
      CComPtr<IAngle> objAngle;
      measure->Angle(endPoint,startPoint,intersect_point,&objAngle);
      objAngle->get_Value(&angle);
   }

   if ( !IsEqual(angle,0.00) )
   {
      // Intersect point occurs in the previous span
      if ( spanIndex == 0 )
      {
         // before start of bridge
         *spanIdx = INVALID_INDEX;
         *distFromStartOfSpan = cut_distance - girder_distance;
         return S_FALSE;
      }

      spanIndex--;

      cogoinfo->get_PierGirderIntersectionPointID(spanIndex,gdrIdx,qcbAfter,&startPointID);

      startPoint.Release();
      points->get_Item(startPointID, &startPoint);

      measure->Distance(startPoint,intersect_point,&cut_distance);

      *distFromStartOfSpan = cut_distance;
      *spanIdx = spanIndex;
   }
   else if ( girder_distance < cut_distance )
   {
      // Intersect point occurs in next span
      spanIndex++;

      if ( nSpans <= spanIndex  )
      {
         // after end of bridge
         *spanIdx = INVALID_INDEX;
         *distFromStartOfSpan = girder_distance - cut_distance;
         return S_FALSE;
      }

      cogoinfo->get_PierGirderIntersectionPointID(spanIndex,gdrIdx,qcbAfter,&startPointID);

      startPoint.Release();
      points->get_Item(startPointID, &startPoint);

      measure->Distance(startPoint,intersect_point,&cut_distance);

      *distFromStartOfSpan = cut_distance;
      *spanIdx = spanIndex;
   }
   else
   {
      // Intersect point occurs in this span
      *spanIdx = spanIndex;
      *distFromStartOfSpan = cut_distance;
   }

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::DeckEdgePoint(IGenericBridge* bridge, Float64 station, IDirection* direction,DirectionType side, IPoint2d** point)
{
   // determine slab type and overhang
   CComPtr<IPath> path;
   HRESULT hr = GetDeckEdgePath(bridge,side,&path);
   if ( FAILED(hr) )
      return hr;

   // get the alignment
   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   // locate a point on the alignment at the given station
   CComPtr<IPoint2d> point_on_alignment;
   alignment->LocatePoint(CComVariant(station),omtAlongDirection, 0.00,CComVariant(0.00),&point_on_alignment);

   // Create a line to intersection with the path
   Float64 angle;
  direction->get_Value(&angle);

   CComPtr<IVector2d> vector;
   vector.CoCreateInstance(CLSID_Vector2d);
   vector->put_Direction(angle);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->SetExplicit(point_on_alignment,vector);

   // Intersection line with path... we want the point to be the one nearest the point on the alignment
   path->Intersect(line,point_on_alignment,point);

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::DeckEdgePoints(IGenericBridge* bridge,DirectionType side,CollectionIndexType nPoints,IPoint2dCollection** points)
{
   CComPtr<IPoint2dCollection> edge_points;
   edge_points.CoCreateInstance(CLSID_Point2dCollection);

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   PierIndexType nPiers;
   piers->get_Count(&nPiers);

   CComPtr<IPier> first_pier, last_pier;
   piers->get_Item(0,&first_pier);
   piers->get_Item(nPiers - 1,&last_pier);

   CComPtr<IStation> objFirstStation,objLastStation;
   first_pier->get_Station(&objFirstStation);
   last_pier->get_Station(&objLastStation);

   Float64 first_station, last_station;
   objFirstStation->get_Value(&first_station);
   objLastStation->get_Value(&last_station);

   CComPtr<IDirection> objFirstDirection, objLastDirection;
   first_pier->get_Direction(&objFirstDirection);
   last_pier->get_Direction(&objLastDirection); 
   
   Float64 first_direction, last_direction;
   objFirstDirection->get_Value(&first_direction);
   objLastDirection->get_Value(&last_direction);

   // Get station of deck points at first and last piers, projected normal to aligment
   CComPtr<IPoint2d> objFirstPoint, objLastPoint;
   DeckEdgePoint(bridge,first_station,objFirstDirection,side,&objFirstPoint);
   DeckEdgePoint(bridge,last_station, objLastDirection, side,&objLastPoint);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   CComPtr<IStation> objFirst_normal_station, objLast_normal_station;
   Float64 offset;

   alignment->Offset(objFirstPoint,&objFirst_normal_station,&offset);
   alignment->Offset(objLastPoint, &objLast_normal_station, &offset);

   Float64 first_normal_station, last_normal_station;
   objFirst_normal_station->get_Value(&first_normal_station);
   objLast_normal_station->get_Value( &last_normal_station);

   // If there is a skew, the first deck edge can be before the pier station, or after it. 
   // Same for the last deck edge. We must deal with this
   edge_points->Add(objFirstPoint);

   Float64 station_inc = (last_station - first_station)/(nPoints-1);
   Float64 station = first_station;
   Float64 direction = first_direction;
   for ( CollectionIndexType i = 0; i < nPoints; i++, station += station_inc)
   {
      if (station > first_normal_station && station < last_normal_station)
      {
         // Normal at station
         CComPtr<IDirection> objDirection;
         alignment->Normal(CComVariant(station), &objDirection);

         CComPtr<IPoint2d> p;
         DeckEdgePoint(bridge,station,objDirection,side,&p);

         if ( p )
            edge_points->Add(p);
      }
   }

   // add final edge
   edge_points->Add(objLastPoint);

   (*points) = edge_points;
   (*points)->AddRef();

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::DeckOffset(IGenericBridge* bridge,Float64 station,IDirection* direction,DirectionType side,Float64* pOffset)
{
   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   if ( direction == NULL )
      alignment->Normal(CComVariant(station),&direction);

   CComPtr<IPoint2d> pntEdge;
   HRESULT hr = DeckEdgePoint(bridge,station,direction,side,&pntEdge);
   if ( FAILED(hr) )
      return hr;

   Float64 offset;
   CComPtr<IStation> objStation;
   alignment->Offset(pntEdge,&objStation,&offset);

#if defined _DEBUG
   Float64 value;
   objStation->get_Value(&value);
   ATLASSERT( IsEqual(value,station,0.0005));
#endif // _DEBUG

   *pOffset = offset;

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::CurbOffset(IGenericBridge* bridge,Float64 station,IDirection* direction,DirectionType side,Float64* pOffset)
{
   Float64 offset;
   HRESULT hr = DeckOffset(bridge,station,direction,side,&offset);
   if ( FAILED(hr) )
      return hr;

   Float64 distFromStartOfBridge = StationToDistance(bridge,station);

   // get connection length of barrier
   CComPtr<ISidewalkBarrier> barrier;
   if ( side == qcbLeft )
      bridge->get_LeftBarrier(&barrier);
   else
      bridge->get_RightBarrier(&barrier);

   Float64 connection_width;
   barrier->get_ExteriorCurbWidth(&connection_width);
   offset += (side == qcbLeft ? connection_width : -connection_width);

   *pOffset = offset;

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::InteriorCurbOffset(IGenericBridge* bridge,Float64 station,IDirection* direction,DirectionType side,Float64* pOffset)
{
   Float64 offset;
   HRESULT hr = DeckOffset(bridge,station,direction,side,&offset);
   if ( FAILED(hr) )
      return hr;

   Float64 distFromStartOfBridge = StationToDistance(bridge,station);

   // get interior connection length of barrier
   CComPtr<ISidewalkBarrier> barrier;
   if ( side == qcbLeft )
      bridge->get_LeftBarrier(&barrier);
   else
      bridge->get_RightBarrier(&barrier);

   Float64 connection_width;
   barrier->get_CurbWidth(&connection_width);
   offset += (side == qcbLeft ? connection_width : -connection_width);

   *pOffset = offset;

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::DeckOverhang(IGenericBridge* bridge,Float64 station,IDirection* dir,DirectionType side,Float64* pOverhang)
{
   Float64 distFromStartOfBridge = StationToDistance(bridge,station);

   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   // use a local object so that direction is reference counted
   // if dir is NULL, the alignment normal is not ref counted and it leaks
   CComPtr<IDirection> direction(dir);

   // if direction is NULL, use the normal to the alignment
   if ( direction == NULL )
      alignment->Normal(CComVariant(station),&direction);

   // Get point on edge of deck
   CComPtr<IPoint2d> pntDeck;
   HRESULT hr = DeckEdgePoint(bridge,station,direction,side,&pntDeck);
   if ( FAILED(hr) )
      return hr;

   // Get point on alignment at station
   CComPtr<IPoint2d> alignment_point;
   alignment->LocatePoint(CComVariant(station),omtAlongDirection, 0.00,CComVariant(0.00),&alignment_point);

   // Create a construction line through the alignment point in the direction of "direction"
   Float64 angle;
   direction->get_Value(&angle);

   CComPtr<IVector2d> v;
   v.CoCreateInstance(CLSID_Vector2d);
   v->put_X(cos(angle));
   v->put_Y(sin(angle));

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->SetExplicit(alignment_point,v);

   // Utils needed
   CComPtr<ICogoInfo> cogoInfo;
   bridge->get_CogoInfo(&cogoInfo);

   CComPtr<ICogoModel> cogoModel;
   bridge->get_CogoModel(&cogoModel);

   CComPtr<IPointCollection> points;
   cogoModel->get_Points(&points);

   CComPtr<IGeomUtil2d> geomUtil;
   geomUtil.CoCreateInstance(CLSID_GeomUtil);

   /////////////////////////
   CComPtr<IPoint2d> pntGirder; // intersection of normal line and girder line
   CComPtr<ILine2d> girderLine;
   CComPtr<ISpanCollection> spans;
   bridge->get_Spans(&spans);
   SpanIndexType nSpans;
   spans->get_Count(&nSpans);

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);
   CComPtr<IPier> pier;
   piers->get_Item(1,&pier);
   CComPtr<IStation> pierStation;
   pier->get_Station(&pierStation);
   Float64 first_interior_pier_station;
   pierStation->get_Value(&first_interior_pier_station);

   pier.Release();
   pierStation.Release();
   piers->get_Item(nSpans-1,&pier);
   pier->get_Station(&pierStation);
   Float64 last_interior_pier_station;
   pierStation->get_Value(&last_interior_pier_station);
   
   for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
   {
      CComPtr<ISpan> span;
      spans->get_Item(spanIdx,&span);

      GirderIndexType nGirders = 0;
      span->get_GirderCount(&nGirders);

      // create a line for the outside girder
      ATLASSERT(0 < nGirders);
      GirderIndexType girderIdx = (side == qcbLeft ? 0 : nGirders-1);

      // Piers bounding span
      PierIndexType prev_pier = spanIdx;
      PierIndexType next_pier = spanIdx+1;

      CogoElementKey id;
      cogoInfo->get_PierGirderIntersectionPointID(prev_pier,girderIdx,qcbAfter,&id);
      CComPtr<IPoint2d> p1;
      points->get_Item(id,&p1);

      cogoInfo->get_PierGirderIntersectionPointID(next_pier,girderIdx,qcbBefore,&id);
      CComPtr<IPoint2d> p2;
      points->get_Item(id,&p2);

      if ( (spanIdx == 0 && station < first_interior_pier_station) || (spanIdx == nSpans-1 && last_interior_pier_station < station) )
      {
         // extend girders if in first or last span
         CComPtr<ILine2d> gdrLine;
         gdrLine.CoCreateInstance(CLSID_Line2d);
         gdrLine->ThroughPoints(p1,p2);

         // intersect line from alignment with girder line
         pntGirder.Release();
         geomUtil->LineLineIntersect(line,gdrLine,&pntGirder);
      }
      else
      {
         CComPtr<ILineSegment2d> gdrLine;
         gdrLine.CoCreateInstance(CLSID_LineSegment2d);
         gdrLine->ThroughPoints(p1,p2);

         // intersect line from alignment with girder line
         pntGirder.Release();
         geomUtil->IntersectLineWithLineSegment(line,gdrLine,&pntGirder);
      }

      if ( pntGirder != NULL ) // an intersection was found
      {
         // an intersection was found
         girderLine.CoCreateInstance(CLSID_Line2d);
         girderLine->ThroughPoints(p1,p2);
         break;
      }
   }

   if ( pntGirder == NULL )
   {
      // girder point is usually found by now, but there is a case where at an intermediate pier, the "line" can pass
      // between girder ends and not actually intersect

      //        .  | <- Cut Line passes between girders, no intersection found
      //         . |
      // ---------.|
      //           . 
      //           |.
      //           | .------------  <- CL Girder
      //           |  .
      //           |   .<- CL Pier
      // 
      

      // This is a last ditch effort... simply intersect "line" with the exterior girder line
      for ( SpanIndexType spanIdx = 0; spanIdx < nSpans; spanIdx++ )
      {
         CComPtr<ISpan> span;
         spans->get_Item(spanIdx,&span);

         GirderIndexType nGirders = 0;
         span->get_GirderCount(&nGirders);

         // create a line for the outside girder
         ATLASSERT(0 < nGirders);
         GirderIndexType girderIdx = (side == qcbLeft ? 0 : nGirders-1);

         // Piers bounding span
         PierIndexType prev_pier = spanIdx;
         PierIndexType next_pier = spanIdx+1;

         CComPtr<IPier> prevPier, nextPier;
         piers->get_Item(prev_pier,&prevPier);
         piers->get_Item(next_pier,&nextPier);

         CComPtr<IStation> objPrevPierStation, objNextPierStation;
         prevPier->get_Station(&objPrevPierStation);
         nextPier->get_Station(&objNextPierStation);

         Float64 prev_pier_station, next_pier_station;
         objPrevPierStation->get_Value(&prev_pier_station);
         objNextPierStation->get_Value(&next_pier_station);

         if ( ::InRange(prev_pier_station,station,next_pier_station) )
         {
            CogoElementKey id;
            cogoInfo->get_PierGirderIntersectionPointID(prev_pier,girderIdx,qcbAfter,&id);
            CComPtr<IPoint2d> p1;
            points->get_Item(id,&p1);

            cogoInfo->get_PierGirderIntersectionPointID(next_pier,girderIdx,qcbBefore,&id);
            CComPtr<IPoint2d> p2;
            points->get_Item(id,&p2);

            // extend girders if in first or last span
            girderLine.CoCreateInstance(CLSID_Line2d);
            girderLine->ThroughPoints(p1,p2);

            // intersect line from alignment with girder line
            pntGirder.Release();
            geomUtil->LineLineIntersect(line,girderLine,&pntGirder);

            break;
         }
      }
   }
   ATLASSERT(pntGirder != NULL);

   //// Determine which span the deck edge point lies in by creating creating a local coordinate system
   //// with the origin at the intersection of the centerline pier and alignment. The Y direction
   //// is along the CL Pier. If X of the deck point is >= 0 in this coordinate system and X
   //// is less than zero in a coordinate system at the next pier, the point is in the span

   //bool bFound = false;
   //SpanIndexType spanIdx = 0; // this is what we are trying to find
   //CComPtr<IPierCollection> piers;
   //bridge->get_Piers(&piers);
   //PierIndexType nPiers;
   //piers->get_Count(&nPiers);

   //if ( nPiers <= 2 )
   //{
   //   // single span bridge.
   //   spanIdx = 0;
   //}
   //else
   //{
   //   CComPtr<ICoordinateXform2d> xform;
   //   xform.CoCreateInstance(CLSID_CoordinateXform2d);

   //   CComPtr<IPier> pier;
   //   piers->get_Item(0,&pier);
   //   CComPtr<IDirection> dirPier;
   //   pier->get_Direction(&dirPier); // direction of Y-axis in local coordinate system
   //   dirPier->IncrementBy(CComVariant(-PI_OVER_2)); // direction of X-axis in local coordinate system

   //   Float64 dirStartPier;
   //   dirPier->get_Value(&dirStartPier);


   //   long ID;
   //   cogoInfo->get_PierPointID(0,pptAlignment,&ID);

   //   CComPtr<IPoint2d> pntStartPier;
   //   points->get_Item(ID,&pntStartPier);

   //   for ( PierIndexType pierIdx = 1; pierIdx < nPiers; pierIdx++ )
   //   {
   //      pier.Release();
   //      dirPier.Release();

   //      piers->get_Item(pierIdx,&pier);
   //      pier->get_Direction(&dirPier); // direction of Y-axis in local coordinate system
   //      dirPier->IncrementBy(CComVariant(-PI_OVER_2)); // direction of X-axis in local coordinate system

   //      Float64 dirEndPier;
   //      dirPier->get_Value(&dirEndPier);

   //      cogoInfo->get_PierPointID(pierIdx,pptAlignment,&ID);
   //      CComPtr<IPoint2d> pntEndPier;
   //      points->get_Item(ID,&pntEndPier);

   //      xform->putref_NewOrigin(pntStartPier);
   //      xform->put_RotationAngle(dirStartPier);

   //      CComPtr<IPoint2d> pnt1;
   //      xform->XformEx(pntDeck,xfrmOldToNew,&pnt1);

   //      xform->putref_NewOrigin(pntEndPier);
   //      xform->put_RotationAngle(dirEndPier);

   //      CComPtr<IPoint2d> pnt2;
   //      xform->XformEx(pntDeck,xfrmOldToNew,&pnt2);

   //      Float64 x1;
   //      pnt1->get_X(&x1);

   //      Float64 x2;
   //      pnt2->get_X(&x2);

   //      if ( pierIdx == 1 && x1 < 0 )
   //      {
   //         // deck edge point is before the first pier
   //         ATLASSERT(x2 < 0);
   //         spanIdx = 0;
   //         bFound = true;
   //         break;
   //      }
   //      else if ( 0 <= x1 && x2 <= 0 )
   //      {
   //         spanIdx = pierIdx-1;
   //         bFound = true;
   //         break;
   //      }
   //      else if ( pierIdx == nPiers-1 && 0 < x2 )
   //      {
   //         // deck edge point is after last pier
   //         ATLASSERT(0 < x1);
   //         spanIdx = nPiers-2;
   //         bFound = true;
   //         break;
   //      }

   //      pntStartPier.Release();
   //      pntStartPier = pntEndPier;
   //      dirStartPier = dirEndPier;
   //   }
   //}

   //if ( !bFound )
   //{
   //   // deck point projects beyond last pier... just use the last span
   //   spanIdx = nPiers-2;
   //}

   //CComPtr<ISpanCollection> spans;
   //bridge->get_Spans(&spans);

   //CComPtr<ISpan> span;
   //spans->get_Item(spanIdx,&span);

   //GirderIndexType nGirders = 0;
   //span->get_GirderCount(&nGirders);

   //// create a line for the outside girder
   //ATLASSERT(0 < nGirders);
   //GirderIndexType girderIdx = (side == qcbLeft ? 0 : nGirders-1);

   //// Piers bounding span
   //PierIndexType prev_pier = spanIdx;
   //PierIndexType next_pier = spanIdx+1;

   //long id;
   //cogoInfo->get_PierGirderIntersectionPointID(prev_pier,girderIdx,qcbAfter,&id);
   //CComPtr<IPoint2d> p1;
   //points->get_Item(id,&p1);

   //cogoInfo->get_PierGirderIntersectionPointID(next_pier,girderIdx,qcbBefore,&id);
   //CComPtr<IPoint2d> p2;
   //points->get_Item(id,&p2);

   //CComPtr<ILine2d> gdrLine;
   //gdrLine.CoCreateInstance(CLSID_Line2d);
   //gdrLine->ThroughPoints(p1,p2);

   //// intersect line from alignment with girder line
   //CComPtr<IPoint2d> pntGirder;
   //geomUtil->LineLineIntersect(line,gdrLine,&pntGirder);

   // offset is distance between girder line point and deck point
   Float64 dist;
   geomUtil->Distance(pntGirder,pntDeck,&dist);

   // Distance is always a positive quantity... distance needs to be < 0 if inboard of the girder line
   // create a vector from pntGirder to pntDeck
   Float64 x1,y1;
   Float64 x2,y2;
   pntGirder->get_X(&x1); pntGirder->get_Y(&y1);
   pntDeck->get_X(&x2);   pntDeck->get_Y(&y2);

   v->put_X(x2-x1); 
   v->put_Y(y2-y1);

   // get the normal to the girder line (normal goes to the left of the line in this case)
   Float64 c;
   CComPtr<IVector2d> n;
   girderLine->GetImplicit(&c,&n);

   // compute the dot product of the normal vector and the vector from the girder to the deck point
   Float64 dot;
   n->Dot(v,&dot);

   if ( dot < 0 && side == qcbLeft || 0 < dot && side == qcbRight )
      dist *= -1;

   *pOverhang = dist;
   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::DeckOverhangFromGirder(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,Float64 distFromStartOfGirder,DirectionType side,Float64* pOverhang)
{
   // Computes the distance from the girder to the edge of the deck along a line passing through the point on the
   // girder that is normal to the alignment. The overhang distance is < 0 if the edge of the deck is inboard
   // of the girder

   // convert location along girder to a point
   CComPtr<IPoint2d> pntGirder;
   Point(bridge,spanIdx,gdrIdx,distFromStartOfGirder,&pntGirder);


   // get deck edge point
   // need station and offset of girder point
   CComPtr<IStation> objStation;
   Float64 offset;
   StationAndOffset(bridge,spanIdx,gdrIdx,distFromStartOfGirder,&objStation,&offset);

   Float64 station;
   objStation->get_Value(&station);


   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   // measure normal to girder
   CComPtr<IDirection> direction;
   alignment->Normal(CComVariant(objStation),&direction);

   // Get point on edge of deck
   CComPtr<IPoint2d> pntDeck;
   HRESULT hr = DeckEdgePoint(bridge,station,direction,side,&pntDeck);
   if ( FAILED(hr) )
      return hr;

   // Utils needed
   CComPtr<ICogoInfo> cogoInfo;
   bridge->get_CogoInfo(&cogoInfo);

   CComPtr<ICogoModel> cogoModel;
   bridge->get_CogoModel(&cogoModel);

   CComPtr<IPointCollection> points;
   cogoModel->get_Points(&points);

   CComPtr<IGeomUtil2d> geomUtil;
   geomUtil.CoCreateInstance(CLSID_GeomUtil);

   // offset is distance between girder line point and deck point
   Float64 dist;
   geomUtil->Distance(pntGirder,pntDeck,&dist);

   // Distance is always a positive quantity... distance needs to be < 0 if inboard of the girder line
   // create a vector from pntGirder to pntDeck
   Float64 x1,y1;
   Float64 x2,y2;
   pntGirder->get_X(&x1); pntGirder->get_Y(&y1);
   pntDeck->get_X(&x2);   pntDeck->get_Y(&y2);

   CComPtr<IVector2d> v;
   v.CoCreateInstance(CLSID_Vector2d);
   v->put_X(x2-x1); 
   v->put_Y(y2-y1);

   // get the normal to the girder line (normal goes to the left of the line in this case)
   // Piers bounding span
   PierIndexType prev_pier = spanIdx;
   PierIndexType next_pier = prev_pier+1;

   CogoElementKey id;
   cogoInfo->get_PierGirderIntersectionPointID(prev_pier,gdrIdx,qcbAfter,&id);
   CComPtr<IPoint2d> p1;
   points->get_Item(id,&p1);

   cogoInfo->get_PierGirderIntersectionPointID(next_pier,gdrIdx,qcbBefore,&id);
   CComPtr<IPoint2d> p2;
   points->get_Item(id,&p2);

   CComPtr<ILine2d> gdrLine;
   gdrLine.CoCreateInstance(CLSID_Line2d);
   gdrLine->ThroughPoints(p1,p2);

   Float64 c;
   CComPtr<IVector2d> n;
   gdrLine->GetImplicit(&c,&n);

   // compute the dot product of the normal vector and the vector from the girder to the deck point
   Float64 dot;
   n->Dot(v,&dot);

   if ( dot < 0 && side == qcbLeft || 0 < dot && side == qcbRight )
      dist *= -1;

   *pOverhang = dist;
   return S_OK;
}

HRESULT CBridgeGeometryTool::GetDeckEdgePath(IGenericBridge* bridge,DirectionType side,IPath** ppPath)
{
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   CComQIPtr<ICastSlab> cip(deck);
   CComQIPtr<IPrecastSlab> sip(deck);
   CComQIPtr<IOverlaySlab> overlay(deck);

   if ( cip == NULL && sip == NULL && overlay == NULL )
      return Error(IDS_E_UNKNOWNDECKTYPE,IID_IBridgeGeometryTool,GBMT_E_UNKNOWNDECKTYPE);

   CComPtr<IPath> path;
   if ( cip )
      (side == qcbLeft) ? cip->get_LeftOverhangPath(&path)     : cip->get_RightOverhangPath(&path);
   else if ( sip )
      (side == qcbLeft) ? sip->get_LeftOverhangPath(&path)     : sip->get_RightOverhangPath(&path);
   else if ( overlay )
      (side == qcbLeft) ? overlay->get_LeftOverhangPath(&path) : overlay->get_RightOverhangPath(&path);

   *ppPath = path;
   (*ppPath)->AddRef();
   return S_OK;
}

HRESULT CBridgeGeometryTool::GetPierLine(IGenericBridge* bridge,PierIndexType pierIdx,ILine2d** ppLine)
{
   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   CComPtr<IPier> pier;
   piers->get_Item(pierIdx,&pier);

   CComPtr<ICogoInfo> cogoInfo;
   bridge->get_CogoInfo(&cogoInfo);

   CComPtr<ICogoModel> cogoModel;
   bridge->get_CogoModel(&cogoModel);

   CComPtr<IPointCollection> points;
   cogoModel->get_Points(&points);

   CogoElementKey leftPntID, rightPntID;
   cogoInfo->get_PierPointID(pierIdx,pptLeft, &leftPntID);
   cogoInfo->get_PierPointID(pierIdx,pptRight,&rightPntID);

   CComPtr<IPoint2d> pntLeft, pntRight;
   points->get_Item(leftPntID, &pntLeft);
   points->get_Item(rightPntID,&pntRight);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   line->ThroughPoints(pntRight,pntLeft);

   *ppLine = line;
   (*ppLine)->AddRef();

   return S_OK;
}
