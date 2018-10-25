///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2018  Washington State Department of Transportation
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

#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

template <class T>
class CSafeObjectUsage
{
public:
   CSafeObjectUsage(T* pObject)
   {
      // if this exception fires, the internal object you are trying to use
      // is being used for another purpose
      m_pObject = pObject;
      ATLASSERT(m_pObject->AddRef() == 2);
   }
   ~CSafeObjectUsage()
   {
      // if this exception fires, the internal object you are using is messed up
      ATLASSERT(m_pObject->Release() == 1);
      m_pObject = 0;
   }

private:
   T* m_pObject;
};

#define USE_LINE(_line_) CSafeObjectUsage<ILine2d> _safety_##_line_ (_line_)
#define USE_VECTOR(_vector_) CSafeObjectUsage<IVector2d> _safety_##_vector_ (_vector_)
#define USE_LINESEGMENT(_line_) CSafeObjectUsage<ILineSegment2d> _safety_##_line_ (_line_)

/////////////////////////////////////////////////////////////////////////////
// CBridgeGeometryTool
HRESULT CBridgeGeometryTool::FinalConstruct()
{
   HRESULT hr = m_CogoEngine.CoCreateInstance(CLSID_CogoEngine);
   if ( FAILED(hr) ) 
   {
      return hr;
   }

   hr = m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = m_Line1.CoCreateInstance(CLSID_Line2d);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = m_Line2.CoCreateInstance(CLSID_Line2d);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = m_LineSegment1.CoCreateInstance(CLSID_LineSegment2d);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = m_LineSegment2.CoCreateInstance(CLSID_LineSegment2d);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = m_Vector.CoCreateInstance(CLSID_Vector2d);
   if ( FAILED(hr) )
   {
      return hr;
   }

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
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
      {
			return S_OK;
      }
	}
	return S_FALSE;
}

STDMETHODIMP CBridgeGeometryTool::PointBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID, Float64 Xg, IPoint2d** point)
{
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISuperstructureMemberSegment> segment;
   Float64 Xs;
   SegmentIndexType segIdx;
   ssmbr->GetDistanceFromStartOfSegment(Xg,&Xs,&segIdx,&segment);
   ATLASSERT(segment);

   return PointBySegment(bridge,ssMbrID,segIdx,Xs,point);
}

STDMETHODIMP CBridgeGeometryTool::PointBySegment(IGenericBridge* bridge,GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 Xs, IPoint2d** point)
{
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISuperstructureMemberSegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   CComPtr<IGirderLine> girderLine;
   segment->get_GirderLine(&girderLine);

   // Xs is measured from the end of the superstructure member segment so
   // use the girder line points as the reference
   CComPtr<IPoint2d> p1, p2;
   girderLine->get_EndPoint(etStart,&p1);
   girderLine->get_EndPoint(etEnd,  &p2);

   CComPtr<ILocate2> locate;
   m_CogoEngine->get_Locate(&locate);

   // Xs is measured from p1
   locate->PointOnLine(p1,p2,Xs,0.00,point);

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::StationAndOffsetBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID, Float64 Xg, IStation** station, Float64* offset)
{
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISuperstructureMemberSegment> segment;
   Float64 Xs;
   SegmentIndexType segIdx;
   HRESULT hr = ssmbr->GetDistanceFromStartOfSegment(Xg,&Xs,&segIdx,&segment);
   ATLASSERT(SUCCEEDED(hr));
   ATLASSERT(segment);

   return StationAndOffsetBySegment(bridge,ssMbrID,segIdx,Xs,station,offset);
}

STDMETHODIMP CBridgeGeometryTool::StationAndOffsetBySegment(IGenericBridge* bridge,GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 Xs, IStation** station, Float64* offset)
{
   CComPtr<IPoint2d> point;
   PointBySegment(bridge,ssMbrID,segIdx,Xs,&point);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   alignment->Offset(point,station,offset);

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::GirderPathOffset(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx, VARIANT varStation,Float64* offset)
{
   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   // get point on alignment at station
   CComPtr<IPoint2d> point_on_alignment;
   alignment->LocatePoint(varStation,omtAlongDirection, 0.00,CComVariant(0.00),&point_on_alignment);

   // get the superstructure member
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   // get the segment
   CComPtr<ISuperstructureMemberSegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   // the the girder line
   CComPtr<IGirderLine> girderLine;
   segment->get_GirderLine(&girderLine);

   // Create a line that represents the girder path
   CComPtr<IPoint2d> p1, p2;
   girderLine->get_PierPoint(etStart,&p1);
   girderLine->get_PierPoint(etEnd,  &p2);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->ThroughPoints(p1,p2);

   // Going to use the geometric utility object
   CComPtr<IGeomUtil2d> geom_util;
   geom_util.CoCreateInstance(CLSID_GeomUtil);
   ATLASSERT(geom_util != nullptr);

   // Find the shortest distance from the point on the alignment to the
   // line representing the girder path. If the alignment point is on the right
   // of the girder path, offset will be > 0. This means the girder path is
   // offset to the left of the alignment so the offset that we want has the opposite
   // sign.
   geom_util->ShortestDistanceToPoint(line,point_on_alignment,offset);
   (*offset) *= -1;

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::GirderPathPoint(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx, VARIANT varStation,VARIANT varDirection,VARIANT_BOOL vbProject,IPoint2d** ppPoint)
{
   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   // get point on alignment at station
   CComPtr<IPoint2d> point_on_alignment;
   alignment->LocatePoint(varStation,omtAlongDirection, 0.00,CComVariant(0.00),&point_on_alignment);

   CComPtr<IDirection> dir;
   HRESULT hr = cogoUtil::DirectionFromVariant(varDirection,&dir);
   if ( FAILED(hr) )
   {
      ATLASSERT(false);
      return hr;
   }
   Float64 dirValue;
   dir->get_Value(&dirValue);

   CComPtr<ILine2d> cutLine;
   cutLine.CoCreateInstance(CLSID_Line2d);
   CComPtr<IVector2d> v;
   v.CoCreateInstance(CLSID_Vector2d);
   v->put_Direction(dirValue);
   v->Normalize();
   cutLine->SetExplicit(point_on_alignment,v);

   // get the superstructure member
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   // get the segment
   CComPtr<ISuperstructureMemberSegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   // the the girder line
   CComPtr<IGirderLine> girderLine;
   segment->get_GirderLine(&girderLine);

   // Create a line that represents the girder path
   CComPtr<IPoint2d> p1, p2;
   girderLine->get_EndPoint(etStart,&p1);
   girderLine->get_EndPoint(etEnd,  &p2);

   if ( vbProject == VARIANT_TRUE )
   {
      CComPtr<ILine2d> gdrLine;
      gdrLine.CoCreateInstance(CLSID_Line2d);
      gdrLine->ThroughPoints(p1,p2);

      // Going to use the geometric utility object
      HRESULT hr = m_GeomUtil->LineLineIntersect(cutLine,gdrLine,ppPoint);
      ATLASSERT(SUCCEEDED(hr));
      ATLASSERT(*ppPoint != nullptr);
   }
   else
   {
      CComPtr<ILineSegment2d> gdrLine;
      gdrLine.CoCreateInstance(CLSID_LineSegment2d);
      gdrLine->putref_StartPoint(p1);
      gdrLine->putref_EndPoint(p2);

      // Going to use the geometric utility object
      m_GeomUtil->IntersectLineWithLineSegment(cutLine,gdrLine,ppPoint);

      if ( *ppPoint == nullptr )
      {
         return E_FAIL;
      }
   }

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::DeckEdgePoint(IGenericBridge* bridge, Float64 station, IDirection* direction,DirectionType side, IPoint2d** point)
{
   // determine slab type and overhang
   CComPtr<IPath> path;
   HRESULT hr = GetDeckEdgePath(bridge,side,&path);
   if ( FAILED(hr) )
   {
      return hr;
   }

   // get the alignment
   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   // locate a point on the alignment at the given station
   CComPtr<IPoint2d> point_on_alignment;
   alignment->LocatePoint(CComVariant(station),omtAlongDirection, 0.00,CComVariant(0.00),&point_on_alignment);

   // Create a line to intersect with the edge of deck
   Float64 angle;
   direction->get_Value(&angle);

   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> vector;

   USE_LINE(m_Line1);
   m_Line1->GetExplicit(&p,&vector);
   vector->put_Direction(angle);

   m_Line1->SetExplicit(point_on_alignment,vector);

   path->Intersect(m_Line1,point_on_alignment,point);

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

   CComPtr<IBridgePier> first_pier, last_pier;
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
         {
            edge_points->Add(p);
         }
      }
   }

   // add final edge
   edge_points->Add(objLastPoint);

   (*points) = edge_points;
   (*points)->AddRef();

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::DeckOffset(IGenericBridge* bridge,Float64 station,IDirection* direction,DirectionType side,IStation** ppOffsetStation,Float64* pOffset)
{
   CHECK_RETVAL(pOffset);
   CHECK_RETOBJ(ppOffsetStation);

   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   CComPtr<IDirection> objDirection;
   if ( direction == nullptr )
   {
      alignment->Normal(CComVariant(station),&objDirection);
   }
   else
   {
      objDirection = direction;
   }

   CComPtr<IPoint2d> pntEdge;
   HRESULT hr = DeckEdgePoint(bridge,station,objDirection,side,&pntEdge);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return alignment->Offset(pntEdge,ppOffsetStation,pOffset);
}

STDMETHODIMP CBridgeGeometryTool::CurbOffset(IGenericBridge* bridge,Float64 station,IDirection* direction,DirectionType side,IStation** ppOffsetStation,Float64* pOffset)
{
   CHECK_RETVAL(pOffset);
   CHECK_RETOBJ(ppOffsetStation);

   Float64 offset;
   HRESULT hr = DeckOffset(bridge,station,direction,side,ppOffsetStation,&offset);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 distFromStartOfBridge = StationToDistance(bridge,station);

   // get connection length of barrier
   CComPtr<ISidewalkBarrier> barrier;
   if ( side == qcbLeft )
   {
      bridge->get_LeftBarrier(&barrier);
   }
   else
   {
      bridge->get_RightBarrier(&barrier);
   }

   Float64 connection_width;
   barrier->get_ExteriorCurbWidth(&connection_width);
   offset += (side == qcbLeft ? connection_width : -connection_width);

   *pOffset = offset;

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::InteriorCurbOffset(IGenericBridge* bridge,Float64 station,IDirection* direction,DirectionType side,IStation** ppOffsetStation,Float64* pOffset)
{
   CHECK_RETVAL(pOffset);
   CHECK_RETOBJ(ppOffsetStation);

   Float64 offset;
   HRESULT hr = DeckOffset(bridge,station,direction,side,ppOffsetStation,&offset);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 distFromStartOfBridge = StationToDistance(bridge,station);

   // get interior connection length of barrier
   CComPtr<ISidewalkBarrier> barrier;
   if ( side == qcbLeft )
   {
      bridge->get_LeftBarrier(&barrier);
   }
   else
   {
      bridge->get_RightBarrier(&barrier);
   }

   Float64 connection_width;
   barrier->get_CurbWidth(&connection_width);
   offset += (side == qcbLeft ? connection_width : -connection_width);

   *pOffset = offset;

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::CurbLinePoint(IGenericBridge* bridge,Float64 station,IDirection* direction,DirectionType side,IPoint2d** point)
{
   CHECK_RETVAL(point);

   CComPtr<IStation> offsetStation;
   Float64 offset;
   HRESULT hr = InteriorCurbOffset(bridge,station,direction,side,&offsetStation,&offset);
   if ( FAILED(hr) )
   {
      return hr;
   }

   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);
   return alignment->LocatePoint(CComVariant(offsetStation),omtAlongDirection,offset,CComVariant(direction),point);
}

STDMETHODIMP CBridgeGeometryTool::DeckOverhang(IGenericBridge* bridge,Float64 station,GirderIDType ssMbrID,IDirection* direction,DirectionType side,Float64* pOverhang)
{
   // Computes the offset from the superstructure member identified by "ssMbrID" to the edge of deck
   // on the side of the bridge specified by "side". The offset is measured along a line in
   // the direction specified by "direction" passing through "station". If "direction" is nullptr, the line 
   // is taken to be normal to the alignment at "station"

   //
   // Create a line passing through station in the specified direction
   //

   // Get the alignment
   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   // use a local object so that direction is reference counted
   // if dir is nullptr, the alignment normal is not ref counted and it leaks
   CComPtr<IDirection> dir(direction);

   // if dir is nullptr, use the normal to the alignment
   if ( dir == nullptr )
   {
      alignment->Normal(CComVariant(station),&dir);
   }

   // Get point on alignment at station
   CComPtr<IPoint2d> alignment_point;
   alignment->LocatePoint(CComVariant(station),omtAlongDirection, 0.00,CComVariant(0.00),&alignment_point);

   // Create a line through the alignment point in the direction of "direction"
   // Use the m_Line2 object (it is faster if we don't have to create it every time it is needed)
   USE_LINE(m_Line2);
   Float64 angle;
   dir->get_Value(&angle);
   
   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> v;
   m_Line2->GetExplicit(&p,&v);
   v->put_X(cos(angle));
   v->put_Y(sin(angle));
   m_Line2->SetExplicit(alignment_point,v);

   //
   // Get the intersection point of the line passing through the alignment and the superstructure member
   //

   // get the superstructure member
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   // using a line semgnet
   USE_LINESEGMENT(m_LineSegment1);

   // loop over all the segments until the line defined above intersects with one of the segments
   SegmentIndexType nSegments;
   ssmbr->get_SegmentCount(&nSegments);
   CComPtr<IPoint2d> pntSegment;
   for ( SegmentIndexType segIdx = 0; segIdx < nSegments; segIdx++ )
   {
      CComPtr<ISuperstructureMemberSegment> segment;
      ssmbr->get_Segment(segIdx,&segment);

      CComPtr<IGirderLine> girderLine;
      segment->get_GirderLine(&girderLine);

      CComPtr<IPoint2d> pnt1,pnt2;
      girderLine->get_PierPoint(etStart,&pnt1);
      girderLine->get_PierPoint(etEnd,  &pnt2);

      m_LineSegment1->ThroughPoints(pnt1,pnt2);

      CComPtr<IPoint2d> pntIntersect;
      m_GeomUtil->IntersectLineWithLineSegment(m_Line2,m_LineSegment1,&pntIntersect);
      if ( pntIntersect != nullptr )
      {
         // an intersection was found
         pntSegment = pntIntersect;
         break; // get the heck outta of the loop
      }
   }

   if ( pntSegment == nullptr )
   {
      // extend the last segment until there is an intersection
      CComPtr<ISuperstructureMemberSegment> segment;
      ssmbr->get_Segment(nSegments-1,&segment);

      CComPtr<IGirderLine> girderLine;
      segment->get_GirderLine(&girderLine);

      CComPtr<IPoint2d> pnt1,pnt2;
      girderLine->get_PierPoint(etStart,&pnt1);
      girderLine->get_PierPoint(etEnd,  &pnt2);

      USE_LINE(m_Line1);
      m_Line1->ThroughPoints(pnt1,pnt2);

      CComPtr<IPoint2d> pntIntersect;
      m_GeomUtil->LineLineIntersect(m_Line2,m_Line1,&pntSegment);
   }

   ATLASSERT(pntSegment != nullptr);

   //
   // Get the deck edge point
   //
   CComPtr<IPoint2d> pntEdge;
   HRESULT hr = DeckEdgePoint(bridge,station,dir,side,&pntEdge);
   if ( FAILED(hr) )
   {
      return hr;
   }


   // offset is distance between girder line point and deck point
   Float64 dist;
   m_GeomUtil->Distance(pntSegment,pntEdge,&dist);

   // Distance is always a positive quantity... distance needs to be < 0 if inboard of the girder line
   // create a vector from pntSegment to pntDeck
   Float64 x1,y1;
   Float64 x2,y2;
   pntSegment->Location(&x1,&y1);
   pntEdge->Location(&x2,&y2);

   v->put_X(x2-x1); 
   v->put_Y(y2-y1);

   // get the normal to the girder line (normal goes to the left of the line in this case)
   CComPtr<IPoint2d> pnt1,pnt2;
   m_LineSegment1->get_StartPoint(&pnt1);
   m_LineSegment1->get_EndPoint(&pnt2);

   // changing line 2... line 2 is now the girder line
   m_Line2->ThroughPoints(pnt1,pnt2);
   Float64 c;
   CComPtr<IVector2d> n;
   m_Line2->GetImplicit(&c,&n);

   // compute the dot product of the normal vector and the vector from the girder to the deck point
   Float64 dot;
   n->Dot(v,&dot);

   if ( dot < 0 && side == qcbLeft || 0 < dot && side == qcbRight )
   {
      dist *= -1;
   }

   *pOverhang = dist;
   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::DeckOverhangBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 Xg,IDirection* dir,DirectionType side,Float64* pOverhang)
{
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISuperstructureMemberSegment> segment;
   Float64 Xs;
   SegmentIndexType segIdx;
   ssmbr->GetDistanceFromStartOfSegment(Xg,&Xs,&segIdx,&segment);
   ATLASSERT(segment);

   return DeckOverhangBySegment(bridge,ssMbrID,segIdx,Xs,dir,side,pOverhang);
}

STDMETHODIMP CBridgeGeometryTool::DeckOverhangBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,IDirection* dir,DirectionType side,Float64* pOverhang)
{
   // Computes the distance from the centerline of the superstructure member to the edge of deck along a given direction

   // Get station and offset of point on segment where deck overhang is to be computed
   CComPtr<IStation> objStation;
   Float64 offset;
   HRESULT hr = StationAndOffsetBySegment(bridge,ssMbrID,segIdx,Xs,&objStation,&offset);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 station;
   objStation->get_Value(&station);

   // Get the alignment
   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   // use a local object so that direction is reference counted
   // if dir is nullptr, the alignment normal is not ref counted and it leaks
   CComPtr<IDirection> direction(dir);

   // if direction is nullptr, use the normal to the alignment
   if ( direction == nullptr )
   {
      alignment->Normal(CComVariant(objStation),&direction);
   }

   // Get point on edge of deck
   CComPtr<IPoint2d> pntDeck;
   hr = DeckEdgePoint(bridge,station,direction,side,&pntDeck);
   if ( FAILED(hr) )
   {
      return hr;
   }

   // Get point on alignment at station
   CComPtr<IPoint2d> alignment_point;
   alignment->LocatePoint(CComVariant(objStation),omtAlongDirection, 0.00,CComVariant(0.00),&alignment_point);

   // Create a line through the alignment point in the direction of "direction"
   // Use the m_Line1 object (it is faster if we don't have to create it every time it is needed)
   USE_LINE(m_Line1);
   Float64 angle;
   direction->get_Value(&angle);
   
   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> v;
   m_Line1->GetExplicit(&p,&v);
   v->put_X(cos(angle));
   v->put_Y(sin(angle));
   m_Line1->SetExplicit(alignment_point,v);


   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISuperstructureMemberSegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   CComPtr<IGirderLine> girderLine;
   segment->get_GirderLine(&girderLine);

   // get end points of the girder l ine
   CComPtr<IPoint2d> p1, p2;
   girderLine->get_PierPoint(etStart,&p1);
   girderLine->get_PierPoint(etEnd,  &p2);

   // line 2 is a cogo line object that represents the girder line
   USE_LINE(m_Line2);
   m_Line2->ThroughPoints(p1,p2);

   // intersect line from alignment with girder line
   CComPtr<IPoint2d> pntGirder;
   m_GeomUtil->LineLineIntersect(m_Line1,m_Line2,&pntGirder);

   // offset is distance between girder line point and deck point
   Float64 dist;
   m_GeomUtil->Distance(pntGirder,pntDeck,&dist);

   // Distance is always a positive quantity... distance needs to be < 0 if inboard of the girder line
   // create a vector from pntGirder to pntDeck
   Float64 x1,y1;
   Float64 x2,y2;
   pntGirder->Location(&x1,&y1);
   pntDeck->Location(&x2,&y2);

   v->put_X(x2-x1); 
   v->put_Y(y2-y1);

   // get the normal to the girder line (normal goes to the left of the line in this case)
   Float64 c;
   CComPtr<IVector2d> n;
   m_Line2->GetImplicit(&c,&n);

   // compute the dot product of the normal vector and the vector from the girder to the deck point
   Float64 dot;
   n->Dot(v,&dot);

   if ( dot < 0 && side == qcbLeft || 0 < dot && side == qcbRight )
   {
      dist *= -1;
   }

   *pOverhang = dist;
   return S_OK;
}

HRESULT CBridgeGeometryTool::GetDeckEdgePath(IGenericBridge* bridge,DirectionType side,IPath** ppPath)
{
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   if ( deck == nullptr )
   {
      // no deck...use the traffic barrier path
      CComPtr<ISidewalkBarrier> barrier;
      if ( side == qcbLeft )
      {
         bridge->get_LeftBarrier(&barrier);
      }
      else
      {
         bridge->get_RightBarrier(&barrier);
      }

      return barrier->get_Path(ppPath);
   }


   // Intersection line with path... we want the point to be the one nearest the point on the alignment
   CComPtr<IDeckBoundary> deckBoundary;
   deck->get_DeckBoundary(&deckBoundary);

   // VARIANT_TRUE to get the layout line and not the actual edge path. The actual deck edge path
   // teminates at the ends of the deck.
   deckBoundary->get_EdgePath((SideType)side,VARIANT_TRUE,ppPath); 

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::GirderSpacingBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 Xg,GirderIDType otherSSMbrID,Float64* pSpacing)
{
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISuperstructureMemberSegment> segment;
   Float64 Xs;
   SegmentIndexType segIdx;
   ssmbr->GetDistanceFromStartOfSegment(Xg,&Xs,&segIdx,&segment);
   ATLASSERT(segment);

   return GirderSpacingBySegment(bridge,ssMbrID,segIdx,Xs,otherSSMbrID,pSpacing);
}

STDMETHODIMP CBridgeGeometryTool::GirderSpacingBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIndex,Float64 Xs,GirderIDType otherSSMbrID,Float64* pSpacing)
{
   // Computes the perpendicular distance between the superstructure member (ssMbrID) at the a distance along this 
   // superstructure member (distFromStartOfSSMbr) and another superstructure member (otherSSMbrID)

   if ( otherSSMbrID == INVALID_ID )
   {
      *pSpacing = 0;
      return E_FAIL;
   }

   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);
   ATLASSERT(ssmbr); // why? bad ssMbrID?

   CComPtr<ISuperstructureMemberSegment> segment;
   ssmbr->get_Segment(segIndex,&segment);
   ATLASSERT(segment);

   CComPtr<IGirderLine> girderLine; // girderLine for this girder
   segment->get_GirderLine(&girderLine);

   // Get point object for point under consideration
   CComQIPtr<ILocate2> locate(m_CogoEngine);

   // get end points of girder line
   CComPtr<IPoint2d> p1, p2;
   girderLine->get_PierPoint(etStart,&p1);
   girderLine->get_PierPoint(etEnd,  &p2);

   // locate point on girder line where spacing is measured
   CComPtr<IPoint2d> pntOnGirder;
   locate->PointOnLine(p1,p2,Xs,0.00,&pntOnGirder);

   // Use m_Line1 for a line that is perpendicular to the girder line, throught pntOnGirder
   USE_LINE(m_Line1);
   m_Line1->ThroughPoints(p1,p2); // line runs along girderline
   m_Line1->RotateEx(pntOnGirder,PI_OVER_2); // rotate 90 degrees, centered on pntOnGirder

   // Get the girder line for the adjacent girder
   // We don't know which segment the normal line will intersect, so start with the
   // first one and work down the superstructure member
   CComPtr<ISuperstructureMember> otherSSMbr;
   bridge->get_SuperstructureMember(otherSSMbrID,&otherSSMbr);

   SegmentIndexType nSegments;
   otherSSMbr->get_SegmentCount(&nSegments);
   CComPtr<IPoint2d> pntOnOtherGirder;

   // Optimization: If there is a single segment, we can just use an infinite-length line to find intersection. Otherwise,
   // we will need to find intersection with line segments
   if (nSegments==1)
   {
      CComPtr<ISuperstructureMemberSegment> otherSegment;
      otherSSMbr->get_Segment(0, &otherSegment);
      CComPtr<IGirderLine> otherGirderLine; // girderLine for the girder spacing is measured to
      otherSegment->get_GirderLine(&otherGirderLine);

      // Use m_Line2 for second girder line (doesn't really matter which end points we use)
      USE_LINE(m_Line2);
      CComPtr<IPoint2d> p3, p4;
      otherGirderLine->get_PierPoint(etStart,&p3);
      otherGirderLine->get_PierPoint(etEnd,  &p4);
      m_Line2->ThroughPoints(p3,p4);

      // Intersect normal line and other girder line
      HRESULT hr = m_GeomUtil->LineLineIntersect(m_Line1,m_Line2,&pntOnOtherGirder);
      ATLASSERT(hr==S_OK);
   }
   else
   {
      // Loop over segments in adjacent girderline to find intersection
      for ( SegmentIndexType segIdx = 0; segIdx < nSegments; segIdx++ )
      {
         CComPtr<ISuperstructureMemberSegment> otherSegment;
         otherSSMbr->get_Segment(segIdx,&otherSegment);
         CComPtr<IGirderLine> otherGirderLine; // girderLine for the girder spacing is measured to
         otherSegment->get_GirderLine(&otherGirderLine);

         // Use m_LineSegment1 for second girder line 
         CComPtr<IPoint2d> ps, pe;
         otherGirderLine->get_PierPoint(etStart,&ps);
         otherGirderLine->get_PierPoint(etEnd,  &pe);

         // Tricky: We must have a line segment that can intersect with our normal line. And, if there is a skew 
         //         and we are at an end of the bridge, there is a chance that our normal will not intersect. So,
         //         manipulate the end segments so they extend past the ends of the bridge. Let's make the segment
         //         ~500x longer than current span length to achive this (arbitrary, but we need to keep precision)
         if (segIdx==0)
         {
            // segment at start end, extend line seg in ps direction
            Float64 len;
            girderLine->get_SpanLength(&len);
            ATLASSERT(len>0.0);
            len *= 500.0;

            Float64 xs, ys, xe, ye;
            ps->get_X(&xs);
            ps->get_Y(&ys);
            pe->get_X(&xe);
            pe->get_Y(&ye);
            USE_VECTOR(m_Vector);
            m_Vector->put_X(xs-xe);
            m_Vector->put_Y(ys-ye);
            m_Vector->Normalize(); // of length 1.0 in correct direction
            Float64 xv,yv;
            m_Vector->get_X(&xv);
            m_Vector->get_Y(&yv);

            ps->put_X(xs + xv*len);
            ps->put_Y(ys + yv*len);
         }

         if (segIdx==nSegments-1)
         {
            // segment at end end, extend line seg in pe direction
            Float64 len;
            girderLine->get_SpanLength(&len);
            ATLASSERT(len>0.0);
            len *= 500.0;

            Float64 xs, ys, xe, ye;
            ps->get_X(&xs);
            ps->get_Y(&ys);
            pe->get_X(&xe);
            pe->get_Y(&ye);
            USE_VECTOR(m_Vector);
            m_Vector->put_X(xe-xs);
            m_Vector->put_Y(ye-ys);
            m_Vector->Normalize(); // of length 1.0 in correct direction
            Float64 xv,yv;
            m_Vector->get_X(&xv);
            m_Vector->get_Y(&yv);

            pe->put_X(xe+xv*len);
            pe->put_Y(ye+yv*len);
         }

         USE_LINESEGMENT(m_LineSegment1);
         m_LineSegment1->ThroughPoints(ps,pe);

         // Intersect normal line and other girder line
         if ( m_GeomUtil->IntersectLineWithLineSegment(m_Line1,m_LineSegment1,&pntOnOtherGirder) == S_OK )
         {
            if ( pntOnOtherGirder != nullptr )
            {
               // point found
               break;
            }
         }
      }
   }

   // Big problems if we couldn't find intersection. This will likely end in a bust
   if ( pntOnOtherGirder == nullptr )
   {
      ATLASSERT(false); // point not found, and it should have been???
      return E_FAIL;
   }

   // compute distance to get spacing
   pntOnGirder->DistanceEx(pntOnOtherGirder,pSpacing);

   return S_OK;
}
