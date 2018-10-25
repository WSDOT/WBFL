///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2012  Washington State Department of Transportation
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

#include <BridgeModeling\BridgeModelingLib.h>

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          GirderPath           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeModeling\GirderPath.h>            // class implementation
#include <BridgeModeling\Bridge.h>
#include <BridgeModeling\Span.h>
#include <BridgeModeling\Girder.h>
#include <mathex.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DIAG_DECLARE_GROUP( bmf )

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfGirderPath::bmfGirderPath()
{
   m_pSpan = 0;

   m_GirderIdx = -1;

   m_OffsetStart      = 0;
   m_OffsetStartWhere = AtBearing;
   m_OffsetStartHow   = NormalToLine;

   m_OffsetEnd      = 0;
   m_OffsetEndWhere = AtBearing;
   m_OffsetEndHow   = NormalToLine;

   // Init to -1... This means points haven't been stored in the cogo model
   // yet
   m_StartBrgPnt    = -1;
   m_StartGirderPnt = -1;
   m_EndBrgPnt      = -1;
   m_EndGirderPnt   = -1;
} // GirderPath

bmfGirderPath::bmfGirderPath(bmfSpan* pSpan, 
                           GirderIndexType girderIdx,
                           Float64 startOffset,
                           bmfMeasuredWhere startWhere,
                           bmfMeasuredHow startHow,
                           Float64 endOffset,
                           bmfMeasuredWhere endWhere, 
                           bmfMeasuredHow endHow)

{
   m_pSpan = pSpan;

   m_GirderIdx = girderIdx;

   m_OffsetStart      = startOffset;
   m_OffsetStartWhere = startWhere;
   m_OffsetStartHow   = startHow;

   m_OffsetEnd      = endOffset;
   m_OffsetEndWhere = endWhere;
   m_OffsetEndHow   = endHow;

   // Init to -1... This means points haven't been stored in the cogo model
   // yet
   m_StartBrgPnt    = -1;
   m_StartGirderPnt = -1;
   m_EndBrgPnt      = -1;
   m_EndGirderPnt   = -1;
} // GirderPath

bmfGirderPath::~bmfGirderPath()
{
} // ~GirderPath

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfGirderPath::BuildGirder(bmfGirderTemplate* pTemplate)
{
   m_pGirder = std::auto_ptr<bmfGirder>(pTemplate->CreateGirder());
   m_pGirder->Associate( m_pSpan, this );
}

void bmfGirderPath::Draw(HDC hDC,const grlibPointMapper& mapper) const
{
   WATCHX( bmf, BMF_LEVEL_DRAW, "Drawing girder path " << m_GirderIdx );

   CComPtr<ICogoModel> model;
   GetCogoModel(&model);
   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   CComPtr<IPoint2d> start_pnt, end_pnt;
   points->get_Item(m_StartGirderPnt,&start_pnt);
   points->get_Item(m_EndGirderPnt,  &end_pnt);

   LONG dx, dy;

   mapper.WPtoDP(start_pnt, &dx, &dy);
   ::MoveToEx(hDC,dx,dy,NULL);

    mapper.WPtoDP(end_pnt, &dx, &dy);
   ::LineTo(hDC,dx,dy);
} // Draw


Float64 bmfGirderPath::NormalOffsetFromAlignment(Float64 station) const
{
   CComPtr<IAlignment> alignment;
   GetAlignment(&alignment);

   // get point on alignment at station
   CComPtr<IPoint2d> a_point;
   alignment->LocatePoint(CComVariant(station),omtAlongDirection, 0.00,CComVariant(0.00),&a_point);

   // Create a line that represents the girder path
   CComPtr<ILine2d> line;
   GetLine(&line);

   // Going to use the geometric utility object
   CComPtr<IGeomUtil2d> geom_util;
   geom_util.CoCreateInstance(CLSID_GeomUtil);
   ATLASSERT(geom_util != NULL);

   // Find the shortest distance from the point on the alignment to the
   // line representing the girder path. If the alignment point is on the right
   // of the girder path, offset will be > 0. This means the girder path is
   // offset to the left of the alignment so the offset that we want has the opposite
   // sign.
   Float64 offset;
   geom_util->ShortestDistanceToPoint(line,a_point,&offset);

   return -1.0*offset;
}

Float64 bmfGirderPath::EndDistanceFromStation(Float64 station) const
{
   CComPtr<IAlignment> alignment;
   GetAlignment(&alignment);

   // get point on alignment at station
   CComPtr<IPoint2d> a_point;
   alignment->LocatePoint(CComVariant(station),omtAlongDirection,0.00,CComVariant(0.00),&a_point);

   // Create a line that represents the girder path
   CComPtr<ILine2d> line;
   GetLine(&line);

   // Going to use the geometric utility object
   CComPtr<IGeomUtil2d> geom_util;
   geom_util.CoCreateInstance(CLSID_GeomUtil);
   ATLASSERT(geom_util != NULL);

   // Project point on alignment onto the girder path line
   CComPtr<IPoint2d> pnt_on_path;
   geom_util->PointOnLineNearest(line,a_point,&pnt_on_path);

   // Create a vector from start of the girder path to the point projected onto the path
   CComPtr<IPoint2d> start_point;
   GetStartPoint(&start_point);
   Float64 x1, y1, x2, y2;
   start_point->get_X(&x1);
   start_point->get_Y(&y1);
   pnt_on_path->get_X(&x2);
   pnt_on_path->get_Y(&y2);
   
   CComPtr<IVector2d> v1;
   v1.CoCreateInstance(CLSID_Vector2d);
   v1->put_X(x2-x1);
   v1->put_Y(y2-y1);

   // Get vector along the girder path
   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> v2;
   line->GetExplicit(&p,&v2);

   // v1 and v2 are on the same line (though they could be in opposite directions)
   // the projection of v1 onto v2 is equal to the distance from the start of the girder
   // to the section normal to "station". If the resulting projection is negative, the 
   // section occures before the start of the girder

   // Project v1 onto v2
   Float64 dist;
   v1->Projection(v2,&dist);

   return dist;
}

void bmfGirderPath::GetStationAndOffset(Float64 distFromStart,Float64* pStation,Float64* pOffset) const
{
   // Convert distFromStart to a cogo point
   CComPtr<IPoint2d> start;
   GetStartPoint(&start);

   CComPtr<IDirection> bearing;
   GetBearing(&bearing);

   CComPtr<ICogoEngine> engine;
   engine.CoCreateInstance(CLSID_CogoEngine);
   ATLASSERT(engine != NULL);

   CComQIPtr<ILocate2> locate(engine);

   CComPtr<IPoint2d> pnt;
   locate->ByDistDir(start,distFromStart,CComVariant(bearing), 0.00,  &pnt);

   CComPtr<IAlignment> alignment;
   GetAlignment(&alignment);

   CComPtr<IStation> station;
   alignment->Offset(pnt,&station,pOffset);
   station->get_Value(pStation);
}

bmfGirder* bmfGirderPath::GetGirder() const
{
   return m_pGirder.get();
}

GirderIndexType bmfGirderPath::GetGirderIdx() const
{
   return m_GirderIdx;
}

void bmfGirderPath::OnSpanChanged()
{
   // Add girder path points to the cogo model...
   // Remove any existing points first.

   SetCogoPointIDs();
   ClearCogoPoints();

   // Layout the cogo points based upon what we know
   if ( m_OffsetStartWhere == AtPier && m_OffsetEndWhere == AtPier )
      DoLayoutPierPier();
   else if ( m_OffsetStartWhere == AtPier && m_OffsetEndWhere == AtBearing )
      DoLayoutPierBearing();
   else if ( m_OffsetStartWhere == AtBearing && m_OffsetEndWhere == AtPier )
      DoLayoutBearingPier();
   else if ( m_OffsetStartWhere == AtBearing && m_OffsetEndWhere == AtBearing )
      DoLayoutBearingBearing();
   else
      CHECK( false );

   if ( m_pGirder.get() )
      m_pGirder->OnGirderPathChanged();

} // Update

Float64 bmfGirderPath::Length() const
{
   CComPtr<ICogoModel> model;
   GetCogoModel(&model);

   Float64 distance;
   CComPtr<IDirection> gdr_dir;
   
   CComQIPtr<IMeasure> measure(model);
   measure->Inverse(m_StartBrgPnt,m_EndBrgPnt,&distance,&gdr_dir);

   // get bearing of start pier to determine if length is positive or negative
   bmfPier* pstart_pier = m_pSpan->GetStartPier();
   CHECK(pstart_pier!=0);

   CComPtr<IDirection> pier_dir;
   pstart_pier->GetBearing(&pier_dir);
   Float64 pier_dir_value;
   pier_dir->get_Value(&pier_dir_value);

   Float64 gdr_dir_value;
   gdr_dir->get_Value(&gdr_dir_value);

   Float64 angle = pier_dir_value - gdr_dir_value;
   if ( angle < 0 )
      angle += 2.0*M_PI;

   if ( M_PI < angle )
      distance *= -1.0;


//
//   pier_dir->IncrementBy(CComVariant(-M_PI/2.0)); // pier alignment is along cap - rotate toward forward pier
//
//   CComPtr<IAngle> ang;
//   pier_dir->AngleBetween(gdr_dir,&ang);
//   Float64 fang;
//   ang->get_Value(&fang);
//   if (fang >= M_PI && fang <= 2.0*M_PI)
//      distance *= -1;

   return distance;
} // Length

//======================== ACCESS     =======================================
void bmfGirderPath::GetBrgStartPoint(IPoint2d** ppPoint) const
{
   CComPtr<ICogoModel> model;
   GetCogoModel(&model);

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   points->get_Item(m_StartBrgPnt,ppPoint);
}

void bmfGirderPath::GetBrgEndPoint(IPoint2d** ppPoint) const
{
   CComPtr<ICogoModel> model;
   GetCogoModel(&model);

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   points->get_Item(m_EndBrgPnt,ppPoint);
}

void bmfGirderPath::GetStartPoint(IPoint2d** ppPoint) const
{
   CComPtr<ICogoModel> model;
   GetCogoModel(&model);

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   points->get_Item(m_StartGirderPnt,ppPoint);
}

void bmfGirderPath::GetEndPoint(IPoint2d** ppPoint) const
{
   CComPtr<ICogoModel> model;
   GetCogoModel(&model);

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   points->get_Item(m_EndGirderPnt,ppPoint);
}

void bmfGirderPath::GetBearing(IDirection** ppBearing) const
{
   CComPtr<ICogoModel> model;
   GetCogoModel(&model);

   CComQIPtr<IMeasure> measure(model);
   measure->Direction(m_StartGirderPnt,m_EndGirderPnt,ppBearing);
}

void bmfGirderPath::GetSectionSkew(Float64 station,IAngle** skew) const
{
   // Difference in angles between the bearing of the girder and the
   // bearing of the alignment is the same as the difference between
   // normals.

   CComPtr<IDirection> brg_gdr;
   GetBearing(&brg_gdr);

   CComPtr<IAlignment> alignment;
   m_pSpan->GetBridge()->GetAlignment(&alignment);

   CComPtr<IDirection> brg_ali;
   alignment->Bearing(CComVariant(station),&brg_ali);

   brg_ali->AngleBetween(brg_gdr,skew);
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfGirderPath::DoLayoutPierPier()
{
   // Locate the ends of the girder and the bearing points by
   // creating temporary points at the pier/girder path intersection,
   // and then locating the desired points along the line.

   CComPtr<ICogoModel> model;
   GetCogoModel(&model);

   CComPtr<IAlignment> alignment;
   GetAlignment(&alignment);

   CComPtr<ICogoEngine> engine;
   engine.CoCreateInstance(CLSID_CogoEngine);
   ATLASSERT(engine != NULL);

   CComQIPtr<ILocate2> locate2(engine);

   Float64 pier_start_station;
   Float64 pier_end_station;
   Float64 adj_start_offset;
   Float64 adj_end_offset;
   Float64 start_brg_dist;
   Float64 end_brg_dist;
   Float64 start_end_dist;
   Float64 end_end_dist;
   CComPtr<IPoint2d> start_pnt, end_pnt;
   CComPtr<IPoint2d> temp_pnt;

   pier_start_station = m_pSpan->StartStation();
   pier_end_station   = m_pSpan->EndStation();

   CComPtr<IDirection> start_brg;
   CComPtr<IDirection> end_brg;
   m_pSpan->GetStartPier()->GetBearing(&start_brg);
   m_pSpan->GetEndPier()->GetBearing(&end_brg);

   CComPtr<IAngle> start_skew_angle;
   m_pSpan->GetStartPier()->GetSkewAngle(&start_skew_angle);
   Float64 valStartSkew;
   start_skew_angle->get_Value(&valStartSkew);

   CComPtr<IAngle> end_skew_angle;
   m_pSpan->GetEndPier()->GetSkewAngle(&end_skew_angle);
   Float64 valEndSkew;
   end_skew_angle->get_Value(&valEndSkew);

   // Adjust the start offset so that it is measured along the pier
   if ( m_OffsetStartHow == AlongLine )
      adj_start_offset = m_OffsetStart;
   else
      adj_start_offset = m_OffsetStart / cos( valStartSkew );

   // Adjust the end offset so that it is measured along the pier
   if ( m_OffsetEndHow == AlongLine )
      adj_end_offset = m_OffsetEnd;
   else
      adj_end_offset = m_OffsetEnd / cos( valEndSkew );

   // Find the coordinates of the points at the pier/girder line intersections
   alignment->LocatePoint( CComVariant(pier_start_station), omtAlongDirection, 0.00, CComVariant(0.00), &temp_pnt );
   locate2->ByDistDir(temp_pnt, adj_start_offset, CComVariant(start_brg), 0.00, &start_pnt);

   temp_pnt.Release();
   alignment->LocatePoint( CComVariant(pier_end_station), omtAlongDirection, 0.00, CComVariant(0.00),&temp_pnt );
   locate2->ByDistDir(temp_pnt, adj_end_offset,CComVariant(end_brg), 0.00, &end_pnt);

   // Locate the bearing/girder line intersection points
   const bmfConnection* pConnection = m_pSpan->GetStartPier()->GetConnection();
   start_brg_dist = pConnection->GetBearingOffset();
   if ( pConnection->GetHowBearingOffSetIsMeasured() == NormalToLine )
      start_brg_dist /= cos( valStartSkew );

   pConnection = m_pSpan->GetEndPier()->GetConnection();
   end_brg_dist = pConnection->GetBearingOffset();
   if ( pConnection->GetHowBearingOffSetIsMeasured() == NormalToLine )
      end_brg_dist /= cos( valEndSkew );

   CComPtr<IPoint2d> start_brg_pnt, end_brg_pnt;
   locate2->PointOnLine(start_pnt, end_pnt,   start_brg_dist,0.00, &start_brg_pnt);
   locate2->PointOnLine(end_pnt,   start_pnt, end_brg_dist,  0.00, &end_brg_pnt);
   CComPtr<IPointCollection> points;
   model->get_Points(&points);
   points->AddEx(m_StartBrgPnt,start_brg_pnt);
   points->AddEx(m_EndBrgPnt,  end_brg_pnt  );
   
   // Locate the ends of the girder
   pConnection = m_pSpan->GetStartPier()->GetConnection();
   start_end_dist = pConnection->GetGirderEndSize();
   if ( pConnection->GetHowGirderEndSizeIsMeasured() == NormalToLine )
      start_end_dist /= cos( valStartSkew );

   pConnection = m_pSpan->GetEndPier()->GetConnection();
   end_end_dist = pConnection->GetGirderEndSize();
   if ( pConnection->GetHowGirderEndSizeIsMeasured() == NormalToLine )
      end_end_dist /= cos( valEndSkew );

   CComQIPtr<ILocate> locate(model);
   locate->PointOnLine( m_StartGirderPnt, m_StartBrgPnt, m_EndBrgPnt,   -start_end_dist, 0.00 );
   locate->PointOnLine( m_EndGirderPnt,   m_EndBrgPnt,   m_StartBrgPnt, -end_end_dist,   0.00 );
} // DoLayoutPierPier 

void bmfGirderPath::DoLayoutPierBearing()
{
   CHECK( false ); // Not yet supported
} // DoLayoutPierBearing

void bmfGirderPath::DoLayoutBearingPier()
{
   CHECK( false ); // Not yet supported
} // DoLayoutBearingPier

void bmfGirderPath::DoLayoutBearingBearing()
{
   Float64 start_station;
   Float64 end_station;
   Float64 adj_start_offset;
   Float64 adj_end_offset;
   Float64 start_end_dist;
   Float64 end_end_dist;

   CComPtr<ICogoModel> model;
   GetCogoModel(&model);
   
   CComPtr<IAlignment> alignment;
   GetAlignment(&alignment);

   start_station = m_pSpan->StartBrgStation();
   end_station   = m_pSpan->EndBrgStation();

   CComPtr<IDirection> start_brg;
   CComPtr<IDirection> end_brg;
   m_pSpan->GetStartPier()->GetBearing(&start_brg);
   m_pSpan->GetEndPier()->GetBearing(&end_brg);

   // Adjust the start offset so that it is measured along the pier
   if ( m_OffsetStartHow == AlongLine )
      adj_start_offset = m_OffsetStart;
   else
   {
      CComPtr<IAngle> start_skew;
      m_pSpan->GetStartPier()->GetSkewAngle(&start_skew);
      Float64 value;
      start_skew->get_Value(&value);
      adj_start_offset = m_OffsetStart / cos( value );
   }

   // Adjust the end offset so that it is measured along the pier
   if ( m_OffsetEndHow == AlongLine )
      adj_end_offset = m_OffsetEnd;
   else
   {
      CComPtr<IAngle> end_skew;
      m_pSpan->GetEndPier()->GetSkewAngle(&end_skew);
      Float64 value;
      end_skew->get_Value(&value);
      adj_end_offset = m_OffsetEnd / cos( value );
   }

   // Using the alignment, location the girder/bearing intersection point
   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   CComPtr<IPoint2d> temp_pnt;
   alignment->LocatePoint( CComVariant(start_station), omtAlongDirection, adj_start_offset, CComVariant(start_brg), &temp_pnt);
   points->AddEx(m_StartBrgPnt,temp_pnt);

   temp_pnt.Release();
   alignment->LocatePoint( CComVariant(end_station), omtAlongDirection, adj_end_offset, CComVariant(end_brg), &temp_pnt);
   points->AddEx(m_EndBrgPnt, temp_pnt);
                           
   // Locate the ends of the girder
   start_end_dist = m_pSpan->GetStartPier()->GetConnection()->GetGirderEndSize();
   end_end_dist   = m_pSpan->GetEndPier()->GetConnection()->GetGirderEndSize();
   
   CComQIPtr<ILocate> locate(model);
   locate->PointOnLine(m_StartGirderPnt,m_StartBrgPnt,m_EndBrgPnt,-start_end_dist,0.00);
   locate->PointOnLine(m_EndGirderPnt,  m_EndBrgPnt,m_StartBrgPnt,-end_end_dist,  0.00);

} // DoLayoutBearingBearing

void bmfGirderPath::ClearCogoPoints()
{
   CComPtr<ICogoModel> model;
   GetCogoModel(&model);

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   points->Remove(m_StartBrgPnt);
   points->Remove(m_EndBrgPnt);
   points->Remove(m_StartGirderPnt);
   points->Remove(m_EndGirderPnt);
} // ClearCogoPoints

void bmfGirderPath::SetCogoPointIDs()
{
   SpanIDType spanID = m_pSpan->GetID();

   SpanIDType baseID = 10000*(spanID+1) + 100*(m_GirderIdx+1);

   m_StartGirderPnt = -1*(baseID + 1);
   m_StartBrgPnt    = -1*(baseID + 2);
   m_EndBrgPnt      = -1*(baseID + 3);
   m_EndGirderPnt   = -1*(baseID + 4);
}

//======================== ACCESS     =======================================

void bmfGirderPath::GetCogoModel(ICogoModel** ppModel) const
{
   m_pSpan->GetBridge()->GetCogoModel(ppModel);
} // GetCogoModel

void bmfGirderPath::GetAlignment(IAlignment** ppAlignment) const
{
   m_pSpan->GetBridge()->GetAlignment(ppAlignment);
} // GetAlignment

void bmfGirderPath::GetLine(ILine2d** ppLine) const
{
   // Create a line that represents the girder path
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);

   CComPtr<ICogoModel> model;
   GetCogoModel(&model);

   CComPtr<IPointCollection> points;
   model->get_Points(&points);

   CComPtr<IPoint2d> p1, p2;
   points->get_Item(m_StartGirderPnt,&p1);
   points->get_Item(m_EndGirderPnt,  &p2);

   line->ThroughPoints(p1,p2);

   (*ppLine) = line;
   (*ppLine)->AddRef();
}

//======================== INQUERY ==========================================
