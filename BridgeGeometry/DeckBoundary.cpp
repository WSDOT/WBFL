// DeckBoundary.cpp : Implementation of CDeckBoundary

#include "stdafx.h"
#include "DeckBoundary.h"


// CDeckBoundary

HRESULT CDeckBoundary::UpdateGeometry()
{
   ATLASSERT( m_BackEdgeID      != m_ForwardEdgeID );
   ATLASSERT( m_LeftEdgeID      != m_RightEdgeID );

   for ( int i = 0; i < 2; i++ )
   {
      m_LeftEdgePoint[i].Release();
      m_LeftEdgeBreakPoint[i].Release();
      m_RightEdgeBreakPoint[i].Release();
      m_RightEdgePoint[i].Release();
   }

   m_LeftEdgePath.Release();
   m_RightEdgePath.Release();

   CreateDeckBoundaryEndPoints(etStart, m_BackEdgeID,    m_BackEdgeType,    &m_LeftEdgePoint[etStart],&m_LeftEdgeBreakPoint[etStart],&m_RightEdgeBreakPoint[etStart],&m_RightEdgePoint[etStart] );
   CreateDeckBoundaryEndPoints(etEnd,   m_ForwardEdgeID, m_ForwardEdgeType, &m_LeftEdgePoint[etEnd],  &m_LeftEdgeBreakPoint[etEnd],  &m_RightEdgeBreakPoint[etEnd],  &m_RightEdgePoint[etEnd]   );

   CreateEdgePath(m_LeftEdgeID, m_LeftEdgePoint[etStart], m_LeftEdgePoint[etEnd], &m_LeftEdgePath);
   CreateEdgePath(m_RightEdgeID,m_RightEdgePoint[etStart],m_RightEdgePoint[etEnd],&m_RightEdgePath);

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


   if ( m_vbBreakLeftEdge[endType] == VARIANT_TRUE )
   {
      // intersect edge path with left break line
      m_pBridge->FindLayoutLine(m_LeftEdgeBreakID,&left_edge_break_path);
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
      m_pBridge->FindLayoutLine(m_LeftEdgeID,&left_edge_path);
      left_edge_path->Intersect(break_line,pntEnd2,&pntEnd1);
   }
   else
   {
      // intersect edge path with left edge path
      m_pBridge->FindLayoutLine(m_LeftEdgeID,&left_edge_path);
      left_edge_path->Intersect(end_line,alignment_point,&pntEnd1);
   }

   if ( m_vbBreakRightEdge[endType] == VARIANT_TRUE )
   {
      // intersect edge path with right break line
      m_pBridge->FindLayoutLine(m_RightEdgeBreakID,&right_edge_break_path);
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
      m_pBridge->FindLayoutLine(m_RightEdgeID,&right_edge_path);
      right_edge_path->Intersect(break_line,pntEnd3,&pntEnd4);
   }
   else
   {
      // intersect edge path with right edge path
      m_pBridge->FindLayoutLine(m_RightEdgeID,&right_edge_path);
      right_edge_path->Intersect(end_line,alignment_point,&pntEnd4);
   }


   pntEnd1.CopyTo(end1);
   pntEnd4.CopyTo(end4);

   if ( pntEnd2 )
      pntEnd2.CopyTo(end2);

   if ( pntEnd3 )
      pntEnd3.CopyTo(end3);
   
   return S_OK;
}

HRESULT CDeckBoundary::CreateEdgePath(LineIDType edgePathID, IPoint2d* pntStart, IPoint2d* pntEnd,IPath** pPath)
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

STDMETHODIMP CDeckBoundary::get_Perimeter(CollectionIndexType nPointsPerSide,IPoint2dCollection** pPoints)
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

   return get_PerimeterEx(nPointsPerSide,firstPierID,lastPierID,pPoints);
}

STDMETHODIMP CDeckBoundary::get_PerimeterEx(CollectionIndexType nPointsPerSide,PierIDType startPierID,PierIDType endPierID,IPoint2dCollection** pPoints)
{
   CHECK_RETOBJ(pPoints);

   CComPtr<IPoint2dCollection> points;
   points.CoCreateInstance(CLSID_Point2dCollection);

   CComPtr<ICogoModel> cogoModel;
   m_pBridge->get_CogoModel(&cogoModel);
   CComPtr<ICogoEngine> cogoEngine;
   cogoModel->get_Engine(&cogoEngine);
   CComQIPtr<IDivide2> divide(cogoEngine);

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
      points->Add(m_LeftEdgePoint[etStart]);
      
      if ( m_vbBreakLeftEdge[etStart] == VARIANT_TRUE )
         points->Add(m_LeftEdgeBreakPoint[etStart]);

      if ( m_vbBreakRightEdge[etStart] == VARIANT_TRUE )
         points->Add(m_RightEdgeBreakPoint[etStart]);

      points->Add(m_RightEdgePoint[etStart]);

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
      m_LeftEdgePath->Intersect(centerline,alignment_point,&pntLeft);
      m_RightEdgePath->Intersect(centerline,alignment_point,&pntRight);

      points->Add(pntLeft);
      points->Add(pntRight);

      Float64 offset;
      m_LeftEdgePath->Offset( pntLeft,  &left_edge_start,  &offset);
      m_RightEdgePath->Offset(pntRight, &right_edge_start, &offset);
   }

   // determine where to stop dividing the DeckBoundary edge paths
   CComPtr<IPoint2d> pntLeftEnd, pntRightEnd;
   if ( lastPierID == endPierID )
   {
      m_LeftEdgePoint[etEnd].CopyTo(&pntLeftEnd);
      m_RightEdgePoint[etEnd].CopyTo(&pntRightEnd);
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
      m_LeftEdgePath->Intersect(centerline,alignment_point,&pntLeftEnd);
      m_RightEdgePath->Intersect(centerline,alignment_point,&pntRightEnd);
   }

   // determine where to stop dividing the edge paths
   Float64 left_edge_end, right_edge_end, offset;
   m_LeftEdgePath->Offset( pntLeftEnd,  &left_edge_end,  &offset);
   m_RightEdgePath->Offset(pntRightEnd, &right_edge_end, &offset);

   // divide the right edge path and put the points in the container
   CComPtr<IPoint2dCollection> right_edge_points;
   divide->Path(m_RightEdgePath,nPointsPerSide,right_edge_start,right_edge_end,&right_edge_points);

   for ( CollectionIndexType idx = 0; idx < nPointsPerSide; idx++ )
   {
      CComPtr<IPoint2d> p;
      right_edge_points->get_Item(idx,&p);
      points->Add(p);
   }

   // define the transverse line at the end of the DeckBoundary
   if ( lastPierID == endPierID )
   {
      points->Add(m_RightEdgePoint[etEnd]);

      if ( m_vbBreakRightEdge[etEnd] == VARIANT_TRUE )
         points->Add(m_RightEdgeBreakPoint[etEnd]);
      
      if ( m_vbBreakLeftEdge[etEnd] == VARIANT_TRUE )
         points->Add(m_LeftEdgeBreakPoint[etEnd]);

      points->Add(m_LeftEdgePoint[etEnd]);
   }
   else
   {
      points->Add(pntRightEnd);
      points->Add(pntLeftEnd);
   }

   // divide the left edge and put the points in the container
   CComPtr<IPoint2dCollection> left_edge_points;
   divide->Path(m_LeftEdgePath,nPointsPerSide,left_edge_start,left_edge_end,&left_edge_points);

   for ( CollectionIndexType idx = nPointsPerSide; 0 < idx; idx-- )
   {
      CComPtr<IPoint2d> p;
      left_edge_points->get_Item(idx-1,&p);
      points->Add(p);
   }

   // close the perimeter shape
   CComPtr<IPoint2d> pnt;
   points->get_Item(0,&pnt);
   points->Add(pnt);

   points.CopyTo(pPoints);

   return S_OK;
}

STDMETHODIMP CDeckBoundary::get_TransverseEdgePoints(EndType endType,IPoint2d** ppLeft,IPoint2d** ppLeftBreak,IPoint2d** ppRightBreak,IPoint2d** ppRight)
{
   CHECK_RETOBJ(ppLeft);
   CHECK_RETOBJ(ppLeftBreak);
   CHECK_RETOBJ(ppRightBreak);
   CHECK_RETOBJ(ppRight);

   m_LeftEdgePoint[endType]->Clone(ppLeft);

   if ( m_LeftEdgeBreakPoint[endType] )
      m_LeftEdgeBreakPoint[endType]->Clone(ppLeftBreak);

   if ( m_RightEdgeBreakPoint[endType] )
      m_RightEdgeBreakPoint[endType]->Clone(ppRightBreak);

   m_RightEdgePoint[endType]->Clone(ppRight);

   return S_OK;
}

STDMETHODIMP CDeckBoundary::get_LeftEdgePath(VARIANT_BOOL vbLayoutLine,IPath** path)
{
   if ( vbLayoutLine == VARIANT_TRUE )
   {
      return m_pBridge->FindLayoutLine(m_LeftEdgeID,path);
   }
   else
   {
      return m_LeftEdgePath.CopyTo(path);
   }
}
 
STDMETHODIMP CDeckBoundary::get_RightEdgePath(VARIANT_BOOL vbLayoutLine,IPath** path)
{
   if ( vbLayoutLine == VARIANT_TRUE )
   {
      return m_pBridge->FindLayoutLine(m_RightEdgeID,path);
   }
   else
   {
      return m_RightEdgePath.CopyTo(path);
   }
}
