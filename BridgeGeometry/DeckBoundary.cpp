///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2014  Washington State Department of Transportation
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
      alignment->ProjectPoint(pntEnd2,&pntOnAlignment);

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
      alignment->ProjectPoint(pntEnd3,&pntOnAlignment);

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

   return get_PerimeterEx(nMinPointsPerSide,firstPierID,lastPierID,pPoints);
}

STDMETHODIMP CDeckBoundary::get_PerimeterEx(CollectionIndexType nMinPointsPerSide,PierIDType startPierID,PierIDType endPierID,IPoint2dCollection** pPoints)
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
   if ( firstPierID == startPierID )
   {
      // starting with first pier
      // use the DeckBoundary transverse end points at the start
      boundaryPoints->Add(m_EdgePoint[etStart][stLeft]);
      
      if ( m_vbBreakEdge[etStart][stLeft] == VARIANT_TRUE )
      {
         boundaryPoints->Add(m_EdgeBreakPoint[etStart][stLeft]);
      }

      if ( m_vbBreakEdge[etStart][stRight] == VARIANT_TRUE )
      {
         boundaryPoints->Add(m_EdgeBreakPoint[etStart][stRight]);
      }

      boundaryPoints->Add(m_EdgePoint[etStart][stRight]);

      left_edge_start  = 0;
      right_edge_start = 0;
   }
   else
   {
      // get the centerline of the start pier
      CComPtr<ILine2d> centerline;
      startPier->get_Centerline(&centerline);

      CComPtr<IPoint2d> alignment_point;
      startPier->get_AlignmentPoint(&alignment_point);

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
   if ( lastPierID == endPierID )
   {
      m_EdgePoint[etEnd][stLeft].CopyTo(&pntLeftEnd);
      m_EdgePoint[etEnd][stRight].CopyTo(&pntRightEnd);
   }
   else
   {
      // get the centerline of the end pier
      CComPtr<ILine2d> centerline;
      endPier->get_Centerline(&centerline);

      CComPtr<IPoint2d> alignment_point;
      endPier->get_AlignmentPoint(&alignment_point);

      // intersect centerline of pier with left and right DeckBoundary edges
      // these two points define the start edge of the DeckBoundary
      m_EdgePath[stLeft]->Intersect(centerline,alignment_point,&pntLeftEnd);
      m_EdgePath[stRight]->Intersect(centerline,alignment_point,&pntRightEnd);
   }

   // determine where to stop dividing the edge paths
   Float64 left_edge_end, right_edge_end, offset;
   m_EdgePath[stLeft]->Offset( pntLeftEnd,  &left_edge_end,  &offset);
   m_EdgePath[stRight]->Offset(pntRightEnd, &right_edge_end, &offset);

   std::map<Float64,CComPtr<IPoint2d>> rightPathPoints;
   CComPtr<IEnumPathElements> enumPathElements;
   m_EdgePath[stRight]->get__EnumPathElements(&enumPathElements);
   CComPtr<IPathElement> pathElement;
   while ( enumPathElements->Next(1,&pathElement,NULL) != S_FALSE )
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

      case petHorzCurve:
         {
            CComQIPtr<IHorzCurve> horzCurve(pUnk);
            CComPtr<IPoint2d> pntTS, pntSC, pntCS, pntST;
            horzCurve->get_TS(&pntTS);
            horzCurve->get_SC(&pntSC);
            horzCurve->get_CS(&pntCS);
            horzCurve->get_ST(&pntST);
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
            while ( enumPoints->Next(1,&point,NULL) != S_FALSE )
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

      std::vector<CComPtr<IPoint2d>>::iterator iter(points.begin());
      std::vector<CComPtr<IPoint2d>>::iterator end(points.end());
      for ( ; iter != end; iter++ )
      {
         CComPtr<IPoint2d> point(*iter);
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

   std::map<Float64,CComPtr<IPoint2d>>::iterator rightPathPointIter(rightPathPoints.begin());
   std::map<Float64,CComPtr<IPoint2d>>::iterator rightPathPointIterEnd(rightPathPoints.end());
   for ( ; rightPathPointIter != rightPathPointIterEnd; rightPathPointIter++ )
   {
      CComPtr<IPoint2d> point = rightPathPointIter->second;
      boundaryPoints->Add(point);
   }

   // define the transverse line at the end of the DeckBoundary
   if ( lastPierID == endPierID )
   {
      boundaryPoints->Add(m_EdgePoint[etEnd][stRight]);

      if ( m_vbBreakEdge[etEnd][stRight] == VARIANT_TRUE )
      {
         boundaryPoints->Add(m_EdgeBreakPoint[etEnd][stRight]);
      }
      
      if ( m_vbBreakEdge[etEnd][stLeft] == VARIANT_TRUE )
      {
         boundaryPoints->Add(m_EdgeBreakPoint[etEnd][stLeft]);
      }

      boundaryPoints->Add(m_EdgePoint[etEnd][stLeft]);
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
   while ( enumPathElements->Next(1,&pathElement,NULL) != S_FALSE )
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

      case petHorzCurve:
         {
            CComQIPtr<IHorzCurve> horzCurve(pUnk);
            CComPtr<IPoint2d> pntTS, pntSC, pntCS, pntST;
            horzCurve->get_TS(&pntTS);
            horzCurve->get_SC(&pntSC);
            horzCurve->get_CS(&pntCS);
            horzCurve->get_ST(&pntST);
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
            while ( enumPoints->Next(1,&point,NULL) != S_FALSE )
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

      std::vector<CComPtr<IPoint2d>>::iterator iter(points.begin());
      std::vector<CComPtr<IPoint2d>>::iterator end(points.end());
      for ( ; iter != end; iter++ )
      {
         CComPtr<IPoint2d> point(*iter);
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

   std::map<Float64,CComPtr<IPoint2d>,std::greater<Float64>>::iterator leftPathPointIter(leftPathPoints.begin());
   std::map<Float64,CComPtr<IPoint2d>,std::greater<Float64>>::iterator leftPathPointIterEnd(leftPathPoints.end());
   for ( ; leftPathPointIter != leftPathPointIterEnd; leftPathPointIter++ )
   {
      CComPtr<IPoint2d> point = leftPathPointIter->second;
      boundaryPoints->Add(point);
   }

   // close the perimeter shape
   CComPtr<IPoint2d> pnt;
   boundaryPoints->get_Item(0,&pnt);
   boundaryPoints->Add(pnt);

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
