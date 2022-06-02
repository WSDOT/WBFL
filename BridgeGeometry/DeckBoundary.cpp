///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2022  Washington State Department of Transportation
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

// DeckBoundary.cpp : Implementation of CDeckBoundary

#include "stdafx.h"
#include "DeckBoundary.h"
#include <map>
#include <vector>
#include <functional>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


typedef std::map<Float64,CComPtr<IPoint2d>> PathPointCollection;
typedef std::pair<Float64,CComPtr<IPoint2d>> PathPointEntry;

// CDeckBoundary

HRESULT CDeckBoundary::UpdateGeometry()
{
   ATLASSERT( m_TransverseEdgeID[etStart] != m_TransverseEdgeID[etEnd] );
   ATLASSERT( m_EdgeID[stLeft]            != m_EdgeID[stRight] );

   for ( int i = 0; i < 2; i++ )
   {
      EndType end = (EndType)i;

      m_EdgePoint[end][stLeft].Release();
      m_EdgeBreakPoint[end][stLeft].Release();

      m_EdgePoint[end][stRight].Release();
      m_EdgeBreakPoint[end][stRight].Release();

      SideType side = (SideType)i;
      m_EdgePath[side].Release();
   }

   CreateDeckBoundaryEndPoints(etStart, m_TransverseEdgeID[etStart], m_TransverseEdgeType[etStart], &m_EdgePoint[etStart][stLeft],&m_EdgeBreakPoint[etStart][stLeft],&m_EdgeBreakPoint[etStart][stRight],&m_EdgePoint[etStart][stRight] );
   CreateDeckBoundaryEndPoints(etEnd,   m_TransverseEdgeID[etEnd],   m_TransverseEdgeType[etEnd],   &m_EdgePoint[etEnd][stLeft],  &m_EdgeBreakPoint[etEnd][stLeft],  &m_EdgeBreakPoint[etEnd][stRight],  &m_EdgePoint[etEnd][stRight]   );

   CreateEdgePath(m_EdgeID[stLeft], m_EdgePoint[etStart][stLeft], m_EdgePoint[etEnd][stLeft], &m_EdgePath[stLeft]);
   CreateEdgePath(m_EdgeID[stRight],m_EdgePoint[etStart][stRight],m_EdgePoint[etEnd][stRight],&m_EdgePath[stRight]);

   return S_OK;
}

HRESULT CDeckBoundary::CreateDeckBoundaryEndPoints(EndType endType,LineIDType endLineID,DeckBoundaryEdgeType edgeType,IPoint2d** end1,IPoint2d** end2,IPoint2d** end3,IPoint2d** end4)
{
   // Locate end points
   CComPtr<ICogoModel> cogoModel;
   m_pBridge->get_CogoModel(&cogoModel);
   CComPtr<ICogoEngine> cogoEngine;
   cogoModel->get_Engine(&cogoEngine);
   CComQIPtr<IIntersect2> intersect(cogoEngine);

   CComPtr<IPath> left_edge_path;
   CComPtr<IPath> left_edge_break_path;
   CComPtr<IPath> right_edge_path;
   CComPtr<IPath> right_edge_break_path;

   CComPtr<ILine2d> end_line;
   CComPtr<IPoint2d> alignment_point;

   CComPtr<IPoint2d> pntEnd1; // intersection of end line and left edge
   CComPtr<IPoint2d> pntEnd2; // intersection of end line and left edge break
   CComPtr<IPoint2d> pntEnd3; // intersection of end line and right edge break
   CComPtr<IPoint2d> pntEnd4; // intersection of end line and right edge
   
   // Get path that represents the end of the DeckBoundary
   if ( edgeType == setPier )
   {
      CComPtr<IPierLine> pier;
      m_pBridge->FindPierLine(endLineID,&pier);

      pier->get_Centerline(&end_line);
      pier->get_AlignmentPoint(&alignment_point);
   }
   else
   {
      CComPtr<IPath> end_path;
      m_pBridge->FindLayoutLine(endLineID,&end_path);

      CollectionIndexType nPathElements;
      end_path->get_Count(&nPathElements);
      ATLASSERT(nPathElements == 1);

      CComPtr<IPathElement> pathElement;
      end_path->get_Item(0,&pathElement);

      PathElementType peType;
      pathElement->get_Type(&peType);
      ATLASSERT( peType == petLineSegment );

      CComPtr<IUnknown> punk;
      pathElement->get_Value(&punk);

      CComQIPtr<ILineSegment2d> line_segment(punk);
      CComPtr<IPoint2d> start,end;
      line_segment->get_StartPoint(&start);
      line_segment->get_EndPoint(&end);

      end_line.CoCreateInstance(CLSID_Line2d);
      end_line->ThroughPoints(start,end);

      CComPtr<IAlignment> alignment;
      m_pBridge->get_BridgeAlignment(&alignment);

      alignment->Intersect(end_line,start,&alignment_point);
   }


   if ( m_vbBreakEdge[endType][stLeft] == VARIANT_TRUE )
   {
      // intersect edge path with left break line
      m_pBridge->FindLayoutLine(m_EdgeBreakID[stLeft],&left_edge_break_path);
      left_edge_break_path->Intersect(end_line,alignment_point,&pntEnd2);

      // create a line that is normal to the alignment passing through this intersection point
      CComPtr<IAlignment> alignment;
      m_pBridge->get_BridgeAlignment(&alignment);

      CComPtr<IPoint2d> pntOnAlignment;
      Float64 distFromStart;
      VARIANT_BOOL vbOnProjection;
      alignment->ProjectPoint(pntEnd2,&pntOnAlignment, &distFromStart, &vbOnProjection);

      CComPtr<ILine2d> break_line;
      break_line.CoCreateInstance(CLSID_Line2d);
      break_line->ThroughPoints(pntOnAlignment,pntEnd2);

      // intersect break line with left edge path
      m_pBridge->FindLayoutLine(m_EdgeID[stLeft],&left_edge_path);
      left_edge_path->Intersect(break_line,pntEnd2,&pntEnd1);
   }
   else
   {
      // intersect edge path with left edge path
      m_pBridge->FindLayoutLine(m_EdgeID[stLeft],&left_edge_path);
      left_edge_path->Intersect(end_line,alignment_point,&pntEnd1);
   }

   if ( m_vbBreakEdge[endType][stRight] == VARIANT_TRUE )
   {
      // intersect edge path with right break line
      m_pBridge->FindLayoutLine(m_EdgeBreakID[stRight],&right_edge_break_path);
      right_edge_break_path->Intersect(end_line,alignment_point,&pntEnd3);

      // create a line that is normal to the alignment passing through this intersection point
      CComPtr<IAlignment> alignment;
      m_pBridge->get_BridgeAlignment(&alignment);

      CComPtr<IPoint2d> pntOnAlignment;
      Float64 distFromStart;
      VARIANT_BOOL vbOnProjection;
      alignment->ProjectPoint(pntEnd3,&pntOnAlignment, &distFromStart, &vbOnProjection);

      CComPtr<ILine2d> break_line;
      break_line.CoCreateInstance(CLSID_Line2d);
      break_line->ThroughPoints(pntOnAlignment,pntEnd3);

      // intersect break line with left edge path
      m_pBridge->FindLayoutLine(m_EdgeID[stRight],&right_edge_path);
      right_edge_path->Intersect(break_line,pntEnd3,&pntEnd4);
   }
   else
   {
      // intersect edge path with right edge path
      m_pBridge->FindLayoutLine(m_EdgeID[stRight],&right_edge_path);
      right_edge_path->Intersect(end_line,alignment_point,&pntEnd4);
   }

   ATLASSERT(pntEnd1 != nullptr);
   ATLASSERT(pntEnd4 != nullptr);
   pntEnd1.CopyTo(end1);
   pntEnd4.CopyTo(end4);

   if ( pntEnd2 )
   {
      pntEnd2.CopyTo(end2);
   }

   if ( pntEnd3 )
   {
      pntEnd3.CopyTo(end3);
   }
   
   return S_OK;
}

HRESULT CDeckBoundary::CreateEdgePath(PathIDType edgePathID, IPoint2d* pntStart, IPoint2d* pntEnd,IPath** pPath)
{
   CComPtr<IPath> edge_path;
   m_pBridge->FindLayoutLine(edgePathID,&edge_path);

   // get distance along path to pntStart and pntEnd, then create a sub-path between these two locations
   Float64 offset;
   Float64 distStart, distEnd;
   edge_path->Offset(pntStart,&distStart,&offset);
   ATLASSERT(IsZero(offset));

   edge_path->Offset(pntEnd,&distEnd,&offset);
   ATLASSERT(IsZero(offset));

   return edge_path->CreateSubPath(distStart,distEnd,pPath);
}

STDMETHODIMP CDeckBoundary::get_Perimeter(CollectionIndexType nMinPointsPerSide,IPoint2dCollection** pPoints)
{
   CComPtr<IPierLine> firstPier;
   m_pBridge->GetPierLine(0,&firstPier);

   PierIDType firstPierID;
   firstPier->get_ID(&firstPierID);

   PierIndexType nPiers;
   m_pBridge->get_PierLineCount(&nPiers);

   CComPtr<IPierLine> lastPier;
   m_pBridge->GetPierLine(nPiers-1,&lastPier);

   PierIDType lastPierID;
   lastPier->get_ID(&lastPierID);

   return get_PerimeterEx(nMinPointsPerSide,firstPierID,0.0,lastPierID,0.0,VARIANT_TRUE, pPoints);
}

STDMETHODIMP CDeckBoundary::get_PerimeterEx(CollectionIndexType nMinPointsPerSide,PierIDType startPierID,Float64 Xstart,PierIDType endPierID,Float64 Xend, VARIANT_BOOL bParallelToPiers, IPoint2dCollection** pPoints)
{
   CHECK_RETOBJ(pPoints);

   CComPtr<IPoint2dCollection> boundaryPoints;
   boundaryPoints.CoCreateInstance(CLSID_Point2dCollection);

   CComPtr<IPierLine> firstPier;
   m_pBridge->GetPierLine(0,&firstPier);

   PierIDType firstPierID;
   firstPier->get_ID(&firstPierID);

   PierIndexType nPiers;
   m_pBridge->get_PierLineCount(&nPiers);

   CComPtr<IPierLine> lastPier;
   m_pBridge->GetPierLine(nPiers-1,&lastPier);

   PierIDType lastPierID;
   lastPier->get_ID(&lastPierID);

   CComPtr<IPierLine> startPier, endPier;
   m_pBridge->FindPierLine(startPierID,&startPier);
   m_pBridge->FindPierLine(endPierID,  &endPier);

   Float64 left_edge_start, right_edge_start; // distance along the edge path to the start of this DeckBoundary segment

   // build starting edge of DeckBoundary
   if ( firstPierID == startPierID && IsZero(Xstart))
   {
      // starting with first pier
      // use the DeckBoundary transverse end points at the start
      CComPtr<IPoint2d> pntEdgeStartLeft;
      m_EdgePoint[etStart][stLeft]->Clone(&pntEdgeStartLeft);
      boundaryPoints->Add(pntEdgeStartLeft);
      
      if ( m_vbBreakEdge[etStart][stLeft] == VARIANT_TRUE )
      {
         CComPtr<IPoint2d> pntEdgeBreakStartLeft;
         m_EdgeBreakPoint[etStart][stLeft]->Clone(&pntEdgeBreakStartLeft);
         boundaryPoints->Add(pntEdgeBreakStartLeft);
      }

      if ( m_vbBreakEdge[etStart][stRight] == VARIANT_TRUE )
      {
         CComPtr<IPoint2d> pntEdgeBreakStartRight;
         m_EdgeBreakPoint[etStart][stRight]->Clone(&pntEdgeBreakStartRight);
         boundaryPoints->Add(pntEdgeBreakStartRight);
      }

      CComPtr<IPoint2d> pntEdgeStartRight;
      m_EdgePoint[etStart][stRight]->Clone(&pntEdgeStartRight);
      boundaryPoints->Add(pntEdgeStartRight);

      left_edge_start  = 0;
      right_edge_start = 0;
   }
   else
   {
      // get the centerline of the start pier
      CComPtr<ILine2d> centerline;
      startPier->get_Centerline(&centerline);

      CComPtr<IStation> objStation;
      startPier->get_Station(&objStation);

      CComPtr<IPoint2d> alignment_point;

      if (IsZero(Xstart))
      {
         startPier->get_AlignmentPoint(&alignment_point);
      }
      else
      {
         // Xstart is the distance, in stations along the alignment, to where we want to
         // start getting the perimeter relative to the centerline. get x,y of that point on the alignment and then
         // move centerline so it passes through that point. Make sure Xstart isn't before the start of the bridge

         // move the "centerline" so that it passes through the point defined by Xstart
         objStation->Offset(Xstart);

         CComPtr<IAlignment> alignment;
         m_pBridge->get_BridgeAlignment(&alignment);
         alignment->LocatePoint(CComVariant(objStation), OffsetMeasureType::omtNormal, 0.0, CComVariant(0), &alignment_point);
      }

      CComPtr<IPoint2d> pnt;
      CComPtr<IVector2d> vDir;
      centerline->GetExplicit(&pnt, &vDir);

      if (bParallelToPiers == VARIANT_FALSE)
      {
         CComPtr<IAlignment> alignment;
         m_pBridge->get_BridgeAlignment(&alignment);

         CComPtr<IDirection> normal;
         alignment->Normal(CComVariant(objStation), &normal);

         Float64 value;
         normal->get_Value(&value);

         vDir->put_Direction(value);
      }

      centerline->SetExplicit(alignment_point, vDir);

      // intersect centerline of pier with left and right DeckBoundary edges
      // these two points define the start edge of the DeckBoundary
      CComPtr<IPoint2d> pntLeft, pntRight;
      m_EdgePath[stLeft]->Intersect(centerline,alignment_point,&pntLeft);
      m_EdgePath[stRight]->Intersect(centerline,alignment_point,&pntRight);

      boundaryPoints->Add(pntLeft);
      boundaryPoints->Add(pntRight);

      Float64 offset;
      m_EdgePath[stLeft]->Offset( pntLeft,  &left_edge_start,  &offset);
      m_EdgePath[stRight]->Offset(pntRight, &right_edge_start, &offset);
   }

   // determine where to stop dividing the DeckBoundary edge paths
   CComPtr<IPoint2d> pntLeftEnd, pntRightEnd;
   if ( lastPierID == endPierID && IsZero(Xend) )
   {
      m_EdgePoint[etEnd][stLeft]->Clone(&pntLeftEnd);
      m_EdgePoint[etEnd][stRight]->Clone(&pntRightEnd);
   }
   else
   {
      // get the centerline of the end pier
      CComPtr<ILine2d> centerline;
      endPier->get_Centerline(&centerline);

      CComPtr<IStation> objStation;
      endPier->get_Station(&objStation);

      CComPtr<IPoint2d> alignment_point;
      if (IsZero(Xend))
      {
         endPier->get_AlignmentPoint(&alignment_point);
      }
      else
      {
         // Xend is the distance, in stations along the alignment, to where we want to
         // stop getting the perimeter, relative to the center. get x,y of that point on the alignment and then
         // move centerline so it passes through that point. Make sure Xend doesn't go too far off the bridge

         // move the "centerline" so that it passes through the point defined by Xend
         objStation->Offset(Xend);

         CComPtr<IAlignment> alignment;
         m_pBridge->get_BridgeAlignment(&alignment);

         alignment->LocatePoint(CComVariant(objStation), OffsetMeasureType::omtNormal, 0.0, CComVariant(0), &alignment_point);
      }

      CComPtr<IPoint2d> pnt;
      CComPtr<IVector2d> vDir;
      centerline->GetExplicit(&pnt, &vDir);

      if (bParallelToPiers == VARIANT_FALSE)
      {
         CComPtr<IAlignment> alignment;
         m_pBridge->get_BridgeAlignment(&alignment);

         CComPtr<IDirection> normal;
         alignment->Normal(CComVariant(objStation), &normal);

         Float64 value;
         normal->get_Value(&value);

         vDir->put_Direction(value);
      }

      centerline->SetExplicit(alignment_point, vDir);

      // intersect centerline of pier with left and right DeckBoundary edges
      // these two points define the start edge of the DeckBoundary
      m_EdgePath[stLeft]->Intersect(centerline,alignment_point,&pntLeftEnd);
      m_EdgePath[stRight]->Intersect(centerline,alignment_point,&pntRightEnd);
   }

   // determine where to stop dividing the edge paths
   Float64 left_edge_end, right_edge_end, offset;
   m_EdgePath[stLeft]->Offset( pntLeftEnd,  &left_edge_end,  &offset);
   m_EdgePath[stRight]->Offset(pntRightEnd, &right_edge_end, &offset);

   PathPointCollection rightPathPoints;
   CComPtr<IEnumPathElements> enumPathElements;
   m_EdgePath[stRight]->get__EnumPathElements(&enumPathElements);
   CComPtr<IPathElement> pathElement;
   while ( enumPathElements->Next(1,&pathElement,nullptr) != S_FALSE )
   {
      PathElementType type;
      pathElement->get_Type(&type);
      CComPtr<IUnknown> pUnk;
      pathElement->get_Value(&pUnk);
      Float64 distance, offset;
      std::vector<CComPtr<IPoint2d>> points;
      switch(type)
      {
      case petPoint:
         {
            CComQIPtr<IPoint2d> point(pUnk);
            points.push_back(point);
         }
         break;

      case petLineSegment:
         {
            CComQIPtr<ILineSegment2d> lineSegment(pUnk);
            CComPtr<IPoint2d> startPoint, endPoint;
            lineSegment->get_StartPoint(&startPoint);
            lineSegment->get_EndPoint(&endPoint);
            points.push_back(startPoint);
            points.push_back(endPoint);
         }
         break;

      case petCompoundCurve:
         {
            CComQIPtr<ICompoundCurve> CompoundCurve(pUnk);
            CComPtr<IPoint2d> pntTS, pntSC, pntCS, pntST;
            CompoundCurve->get_TS(&pntTS);
            CompoundCurve->get_SC(&pntSC);
            CompoundCurve->get_CS(&pntCS);
            CompoundCurve->get_ST(&pntST);
            points.push_back(pntTS);
            points.push_back(pntSC);
            points.push_back(pntCS);
            points.push_back(pntST);
         }
         break;

      case petCubicSpline:
         {
            CComQIPtr<ICubicSpline> spline(pUnk);
            CComPtr<IPoint2dCollection> splinePoints;
            spline->get_Points(&splinePoints);

            CComPtr<IPoint2d> point;
            CComPtr<IEnumPoint2d> enumPoints;
            splinePoints->get__Enum(&enumPoints);
            while ( enumPoints->Next(1,&point,nullptr) != S_FALSE )
            {
               points.push_back(point);
               point.Release();
            }
         }
         break;

      default:
         ATLASSERT(false); // is there a new type?
      }
      pathElement.Release();

      for( const auto& point : points)
      {
         m_EdgePath[stRight]->Offset(point,&distance,&offset); 
         if (::InRange(right_edge_start,distance,right_edge_end) )
         {
            rightPathPoints.insert(std::make_pair(distance,point));
         }
      }
   }

   Float64 pathLength = right_edge_end - right_edge_start;
   for ( CollectionIndexType idx = 0; idx < nMinPointsPerSide; idx++ )
   {
      Float64 distanceAlongPath = right_edge_start + pathLength*idx/(nMinPointsPerSide-1);
      CComPtr<IPoint2d> point;
      m_EdgePath[stRight]->LocatePoint(distanceAlongPath,omtAlongDirection,0.0,CComVariant(0),&point);
      rightPathPoints.insert(std::make_pair(distanceAlongPath,point));
   }

   for( const auto& rightPathPointEntry : rightPathPoints)
   {
      CComPtr<IPoint2d> point = rightPathPointEntry.second;
      CComPtr<IPoint2d> clone;
      point->Clone(&clone);
      boundaryPoints->Add(clone);
   }

   // define the transverse line at the end of the DeckBoundary
   if ( lastPierID == endPierID && IsZero(Xend))
   {
      CComPtr<IPoint2d> pntEdgeEndRight;
      m_EdgePoint[etEnd][stRight]->Clone(&pntEdgeEndRight);
      boundaryPoints->Add(pntEdgeEndRight);

      if ( m_vbBreakEdge[etEnd][stRight] == VARIANT_TRUE )
      {
         CComPtr<IPoint2d> pntEdgeBreakEndRight;
         m_EdgeBreakPoint[etEnd][stRight]->Clone(&pntEdgeBreakEndRight);
         boundaryPoints->Add(pntEdgeBreakEndRight);
      }
      
      if ( m_vbBreakEdge[etEnd][stLeft] == VARIANT_TRUE )
      {
         CComPtr<IPoint2d> pntEdgeBreakEndLeft;
         m_EdgeBreakPoint[etEnd][stLeft]->Clone(&pntEdgeBreakEndLeft);
         boundaryPoints->Add(pntEdgeBreakEndLeft);
      }

      CComPtr<IPoint2d> pntEdgeEndLeft;
      m_EdgePoint[etEnd][stLeft]->Clone(&pntEdgeEndLeft);
      boundaryPoints->Add(pntEdgeEndLeft);
   }
   else
   {
      boundaryPoints->Add(pntRightEnd);
      boundaryPoints->Add(pntLeftEnd);
   }

   std::map<Float64,CComPtr<IPoint2d>,std::greater<Float64>> leftPathPoints; // sort from greatest to least

   enumPathElements.Release();
   m_EdgePath[stLeft]->get__EnumPathElements(&enumPathElements);
   pathElement.Release();
   while ( enumPathElements->Next(1,&pathElement,nullptr) != S_FALSE )
   {
      PathElementType type;
      pathElement->get_Type(&type);
      CComPtr<IUnknown> pUnk;
      pathElement->get_Value(&pUnk);
      Float64 distance, offset;
      std::vector<CComPtr<IPoint2d>> points;
      switch(type)
      {
      case petPoint:
         {
            CComQIPtr<IPoint2d> point(pUnk);
            points.push_back(point);
         }
         break;

      case petLineSegment:
         {
            CComQIPtr<ILineSegment2d> lineSegment(pUnk);
            CComPtr<IPoint2d> startPoint, endPoint;
            lineSegment->get_StartPoint(&startPoint);
            lineSegment->get_EndPoint(&endPoint);
            points.push_back(startPoint);
            points.push_back(endPoint);
         }
         break;

      case petCompoundCurve:
         {
            CComQIPtr<ICompoundCurve> CompoundCurve(pUnk);
            CComPtr<IPoint2d> pntTS, pntSC, pntCS, pntST;
            CompoundCurve->get_TS(&pntTS);
            CompoundCurve->get_SC(&pntSC);
            CompoundCurve->get_CS(&pntCS);
            CompoundCurve->get_ST(&pntST);
            points.push_back(pntTS);
            points.push_back(pntSC);
            points.push_back(pntCS);
            points.push_back(pntST);
         }
         break;

      case petCubicSpline:
         {
            CComQIPtr<ICubicSpline> spline(pUnk);
            CComPtr<IPoint2dCollection> splinePoints;
            spline->get_Points(&splinePoints);

            CComPtr<IPoint2d> point;
            CComPtr<IEnumPoint2d> enumPoints;
            splinePoints->get__Enum(&enumPoints);
            while ( enumPoints->Next(1,&point,nullptr) != S_FALSE )
            {
               points.push_back(point);
               point.Release();
            }
         }
         break;

      default:
         ATLASSERT(false); // is there a new type?
      }
      pathElement.Release();

      for( const auto& point : points)
      {
         m_EdgePath[stLeft]->Offset(point,&distance,&offset); 
         if (::InRange(left_edge_start,distance,left_edge_end) )
         {
            leftPathPoints.insert(std::make_pair(distance,point));
         }
      }
   }

   pathLength = left_edge_end - left_edge_start;
   for ( CollectionIndexType idx = 0; idx < nMinPointsPerSide; idx++ )
   {
      Float64 distanceAlongPath = left_edge_start + pathLength*idx/(nMinPointsPerSide-1);
      CComPtr<IPoint2d> point;
      m_EdgePath[stLeft]->LocatePoint(distanceAlongPath,omtAlongDirection,0.0,CComVariant(0),&point);
      leftPathPoints.insert(std::make_pair(distanceAlongPath,point));
   }

   for( const auto& leftPathPointEntry : leftPathPoints)
   {
      CComPtr<IPoint2d> point = leftPathPointEntry.second;
      CComPtr<IPoint2d> clone;
      point->Clone(&clone);
      boundaryPoints->Add(clone);
   }

   // close the perimeter shape
   CComPtr<IPoint2d> pnt;
   boundaryPoints->get_Item(0,&pnt);
   CComPtr<IPoint2d> clone;
   pnt->Clone(&clone);
   boundaryPoints->Add(clone);

   boundaryPoints.CopyTo(pPoints);

   return S_OK;
}

STDMETHODIMP CDeckBoundary::get_TransverseEdgePoints(EndType endType,IPoint2d** ppLeft,IPoint2d** ppLeftBreak,IPoint2d** ppRightBreak,IPoint2d** ppRight)
{
   CHECK_RETOBJ(ppLeft);
   CHECK_RETOBJ(ppLeftBreak);
   CHECK_RETOBJ(ppRightBreak);
   CHECK_RETOBJ(ppRight);

   m_EdgePoint[endType][stLeft]->Clone(ppLeft);

   if ( m_EdgeBreakPoint[endType][stLeft] )
   {
      m_EdgeBreakPoint[endType][stLeft]->Clone(ppLeftBreak);
   }

   if ( m_EdgeBreakPoint[endType][stRight] )
   {
      m_EdgeBreakPoint[endType][stRight]->Clone(ppRightBreak);
   }

   m_EdgeBreakPoint[endType][stRight]->Clone(ppRight);

   return S_OK;
}

STDMETHODIMP CDeckBoundary::get_EdgePath(SideType side,VARIANT_BOOL vbLayoutPath,IPath** path)
{
   if ( vbLayoutPath == VARIANT_TRUE )
   {
      return m_pBridge->FindLayoutLine(m_EdgeID[side] ,path);
   }
   else
   {
      return m_EdgePath[side].CopyTo(path);
   }
}
