///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2014  Washington State Department of Transportation
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
// NAME:          bmfSpan           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeModeling\Span.h>                  // class implementation
#include <BridgeModeling\Bridge.h>
#include <BridgeModeling\GirderPath.h>
#include <BridgeModeling\Girder.h>
#include <MathEx.h>
#include <GraphicsLib\GraphTool.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DIAG_DECLARE_GROUP(bmf)

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bmfSpan::bmfSpan()
{
   m_ID = 0;
   m_pBridge = 0;

   m_pStartPier = 0;
   m_pEndPier = 0;

   m_GirderCount = 0;

//   m_RefGirderIndex  = -1; // If < 0, automatically center girder lines
}

bmfSpan::~bmfSpan()
{
} // ~Span

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void bmfSpan::CreateGirder(bmfGirderTemplate* pTpl,GirderIndexType gdrPathIdx)
{
   GirderIndexType first_idx, last_idx;
 
   if ( gdrPathIdx < 0 )
   {
      GirderIndexType nGirders;
      Float64 spacing;
      bmfMeasuredWhere where;
      bmfMeasuredHow how;

      GetGirderPathLayout( nGirders,
                           spacing,
                           where,
                           how );
      first_idx = 0;
      last_idx = nGirders;
   }
   else
   {
      first_idx = gdrPathIdx;
      last_idx = first_idx + 1;
   }

   for ( GirderIndexType idx = first_idx; idx < last_idx; idx++ )
   {
      bmfGirderPath* pGirderPath = GetGirderPath( idx );
      CHECKX( pGirderPath != 0, _T("Error finding girder path") );

      pGirderPath->BuildGirder( pTpl );
      DoInitGirder( pGirderPath->GetGirder() );
  }
}

bmfGirder* bmfSpan::GetGirder(GirderIndexType gdrPathIdx)
{
   bmfGirderPath* pGirderPath = GetGirderPath( gdrPathIdx );
   CHECKX( pGirderPath != 0, _T("Error getting girder path"));

   return pGirderPath->GetGirder();
}

const bmfGirder* bmfSpan::GetGirder(GirderIndexType gdrPathIdx) const
{
   bmfGirderPath* pGirderPath = GetGirderPath( gdrPathIdx );
   CHECKX( pGirderPath != 0, _T("Error getting girder path"));

   return pGirderPath->GetGirder();
}

void bmfSpan::GetGirders(std::vector<bmfGirder*>& vGirders)
{
   GirderPathIterator begin = m_GirderPaths.begin();
   GirderPathIterator end   = m_GirderPaths.end();

   while ( begin != end )
   {
      boost::shared_ptr<bmfGirderPath>& pGirderPath = *begin++;
      vGirders.push_back( pGirderPath->GetGirder() );
   }
}

void bmfSpan::GetGirders(std::vector<const bmfGirder*>& vGirders) const
{
   ConstGirderPathIterator begin = m_GirderPaths.begin();
   ConstGirderPathIterator end   = m_GirderPaths.end();

   while ( begin != end )
   {
      const boost::shared_ptr<bmfGirderPath>& pGirderPath = *begin++;
      vGirders.push_back( pGirderPath->GetGirder() );
   }
}

void bmfSpan::SetID(SpanIDType id)
{
   m_ID = id;
} // SetID

void bmfSpan::OnSetup()
{
   UpdateGirderPaths();
} // OnSetup

void bmfSpan::OnStartPierChanged()
{
   UpdateGirderPaths();
} // OnStartPierChanged

void bmfSpan::OnEndPierChanged()
{
   UpdateGirderPaths();
} // OnEndPierChanged

void bmfSpan::OnAlignmentChanged()
{
   UpdateGirderPaths();
} // OnAlignmentChanged

void bmfSpan::LayoutGirderPaths(GirderIndexType nGirders,
                               Float64 spacing,
                               bmfMeasuredWhere where,
                               bmfMeasuredHow how)
{
   // This interface constrains the problem to equally spaced,
   // parallel girder lines.

   m_GirderCount = nGirders;
   m_GirderLineSpacing = spacing;
   m_Where = where;
   m_How = how;

   Float64 offset;
   offset = (m_GirderCount - 1) * m_GirderLineSpacing / 2.0;

   for (GirderIndexType gdrPathIdx = 0; gdrPathIdx < m_GirderCount; gdrPathIdx++)
   {
      bmfGirderPath* pPath = new bmfGirderPath(this, 
                                               gdrPathIdx,
                                               offset,
                                               m_Where,
                                               m_How,
                                               offset,
                                               m_Where,
                                               m_How);

      StoreGirderPath( gdrPathIdx, pPath );
      pPath->OnSpanChanged();

      offset -= m_GirderLineSpacing;
   }
}

void bmfSpan::GetGirderPathLayout(GirderIndexType& nGirders,
                                 Float64& spacing,
                                 bmfMeasuredWhere& where,
                                 bmfMeasuredHow& how) const
{
   nGirders = m_GirderCount;
   spacing  = m_GirderLineSpacing;
   where    = m_Where;
   how      = m_How;
}

void bmfSpan::ClearGirderPaths()
{
   m_GirderPaths.clear();
}

gpRect2d bmfSpan::GetBoundingBox() const
{
   gpRect2d box;

   for (GirderIndexType girderIdx = 0; girderIdx < GetGirderPathCount(); girderIdx++)
   {
      // Draw the girder path
      const bmfGirder* p_girder = GetGirder( girderIdx );

      if ( !p_girder )
      {
         const bmfGirderPath* p_path = GetGirderPath( girderIdx );
         CComPtr<IPoint2d> start,end;
         p_path->GetStartPoint(&start);
         p_path->GetEndPoint(&end);

         Float64 sx,sy,ex,ey;
         start->get_X(&sx); start->get_Y(&sy);
         end->get_X(&ex); end->get_Y(&ey);

         gpRect2d my_box;
         my_box.Left()   = sx;
         my_box.Right()  = ex;
         my_box.Top()    = sy;
         my_box.Bottom() = ey;

         if ( girderIdx == 0 )
            box = my_box;
         else
            box.Union( my_box );
      }
      else
      {
         if ( girderIdx == 0 )
            box = p_girder->GetBoundingBox();
         else
            box.Union( p_girder->GetBoundingBox() );
      }
   }

   return box;
}

void bmfSpan::PlanView(HDC hDC,const grlibPointMapper& mapper,
                       bool bLabelAlignment, bool bLabelGirders) const
{
   WATCHX( bmf, BMF_LEVEL_DRAW, "Drawing span " << GetID() );

   gpPoint2d pnt;
   LONG dx,dy;
   POINT p;
   Float64 start_station;
   Float64 end_station;
   HPEN hOldPen;
   HPEN hAlignmentPen;
   HPEN hGdrPathPen;
   HPEN hGirderPen;

   // Setup Pens
   int lw = bmfBridge::GetSolidLineWidth(hDC);

   hAlignmentPen = (HPEN)::CreatePen(PS_DASHDOT, 1, RGB(   0,   0,   0) );
   hGdrPathPen   = (HPEN)::CreatePen(PS_DASH,    1, RGB(   0, 255,   0) );
   hGirderPen    = (HPEN)::CreatePen(PS_SOLID,   lw, RGB( 128, 128, 128) );

   CComPtr<IAlignment> alignment;
   m_pBridge->GetAlignment(&alignment);

   start_station = m_pStartPier->GetAheadBearingStation();
   end_station = m_pEndPier->GetBackBearingStation();

   // Draw Centerline of span
   CComPtr<IPoint2d> start_pnt;
   alignment->LocatePoint(CComVariant(start_station),omtAlongDirection, 0.0,CComVariant(0.0),&start_pnt); 
   mapper.WPtoDP(start_pnt, &dx, &dy);
   ::MoveToEx(hDC,dx,dy,&p);

   hOldPen = (HPEN)::SelectObject(hDC,hAlignmentPen);
   Int16 nChords = 100;
   Float64 station_step = (end_station - start_station)/(nChords-1);
   for ( Int16 i = 0; i < nChords; i++ )
   {
      Float64 station = start_station + i*station_step;
      CComPtr<IPoint2d> pnt;
      alignment->LocatePoint(CComVariant(station),omtAlongDirection, 0.0,CComVariant(0.0),&pnt);
      mapper.WPtoDP(pnt,&dx,&dy);
      ::LineTo(hDC,dx,dy);
   }

//   if (bLabelAlignment)
//   {
//      // Label span
//      mapper.WPtoDP( 0.5*(start_pnt.X() + end_pnt.X()),
//                     0.5*(start_pnt.Y() + end_pnt.Y()),
//                     &dx, &dy);
//      TCHAR label[10];
//      _itoa( GetID()+1, label, 10 ); // Add 1 because we have a zero-based index
//      std::_tstring message("Span ");
//      message += label;
//      message += " - ";
//      message += GetBearing().AsBearingString();
//
//      // cw = clockwise, ccw = counter clockwise
//      Float64 cw_angle_from_north = GetBearing().AsFloat64();
//      Float64 ccw_angle_from_east = PI_OVER_2 - cw_angle_from_north;
//
//      if ( ccw_angle_from_east < 0 )
//         ccw_angle_from_east += TWO_PI;
//
//      if ( PI_OVER_2 < ccw_angle_from_east && IsLE(ccw_angle_from_east, 3*PI_OVER_2 ) )
//         ccw_angle_from_east -= M_PI;
//
//      Int32 intang = ccw_angle_from_east * (float)(180./M_PI)*10;
//      UINT old_align = ::SetTextAlign( hDC, TA_BOTTOM | TA_CENTER );
//      grGraphTool::TextOutRotated(hDC, dx, dy, intang, message.c_str(), message.size()-1, 10);
//
//      ::SetTextAlign(hDC, old_align);
//   } // bLabelAlignment

   // Draw Girder Lines
   for (GirderIndexType girderIdx = 0; girderIdx < GetGirderPathCount(); girderIdx++)
   {
      // Draw the girder path
      bmfGirderPath* p_path = GetGirderPath( girderIdx );
      ::SelectObject(hDC,hGdrPathPen);
      p_path->Draw( hDC, mapper );

      if (bLabelGirders)
      {
         // Label girder path
         CComPtr<IPoint2d> start_pnt, end_pnt;
         p_path->GetStartPoint(&start_pnt);
         p_path->GetEndPoint(&end_pnt);
         Float64 sx,sy,ex,ey;
         start_pnt->get_X(&sx); start_pnt->get_Y(&sy);
         end_pnt->get_X(&ex); end_pnt->get_Y(&ey);

         Float64 x = sx + 0.25*(ex-sx);
         Float64 y = sy + 0.25*(ey-sy);
         mapper.WPtoDP( x, y, &dx, &dy);
         std::_tstring message;
         message = (TCHAR)((TCHAR)(girderIdx) + 'A');

         // cw = clockwise, ccw = counter clockwise
         CComPtr<IDirection> brg;
         p_path->GetBearing(&brg);
         Float64 brgValue;
         brg->get_Value(&brgValue);
         Float64 ccw_angle_from_east = brgValue;

         if ( ccw_angle_from_east < 0 )
            ccw_angle_from_east += TWO_PI;

         if ( PI_OVER_2 < ccw_angle_from_east && IsLE(ccw_angle_from_east, 3*PI_OVER_2 ) )
            ccw_angle_from_east -= M_PI;

         Int32 intang = Int32(ccw_angle_from_east * (float)(180./M_PI)*10);
         UINT old_align = ::SetTextAlign( hDC, TA_BOTTOM | TA_CENTER );
         grGraphTool::TextOutRotated(hDC, dx, dy, intang, message.c_str(), (LONG)message.size(), 8);

         ::SetTextAlign( hDC, old_align );
      }

      // Draw the girder
      bmfGirder* p_girder = p_path->GetGirder();
      if ( p_girder )
      {
         ::SelectObject( hDC, hGirderPen );
         p_girder->PlanView( hDC, mapper );
      }
   }

   // Cleanup
   ::SelectObject( hDC, hOldPen );
   ::DeleteObject( hAlignmentPen );
   ::DeleteObject( hGdrPathPen );
   ::DeleteObject( hGirderPen );
} // Draw


//======================== ACCESS     =======================================
Float64 bmfSpan::GetLength() const
{
   return (m_pEndPier->GetBackBearingStation() - m_pStartPier->GetAheadBearingStation());
} // GetLength

Float64 bmfSpan::GetGirderPathSpacing(GirderIndexType gdrPathIdx,
                                    Side side,
                                    Float64 distFromStart)
{
   // :TODO: rab 01.28.97 : Fix implementation
   // :METHOD: bmfSpan::GetGirderPathSpacing
   //
   // This method is supposed to compute the distance to the adjacent
   // girder path, measured normal to the girder path of interest.
   // This simple implementation just returns the parallel girder path
   // spacing.  Use the cogo model to compute it correctly

   Float64 spacing;

   if ( ( IsFirstGirderPath( gdrPathIdx ) && side == Left ) ||
        ( IsLastGirderPath( gdrPathIdx )  && side == Right ) )
   {
      // This is the exterior side of the exterior girder.
      // Let spacing be considered the distance between the
      // exterior girder path and the edge of the slab.
      bmfSlab* pslab = GetBridge()->GetSlab();
      if ( pslab )
         spacing = pslab->GetOverhang();
      else
         spacing = 0.0;
   }
   else
      spacing = m_GirderLineSpacing;

   return spacing;
}

Float64 bmfSpan::GetGirderPathOffset(GirderIndexType gdrPathIdx, Float64 station) const
{
   bmfGirderPath* ppath = GetGirderPath(gdrPathIdx);
   CHECK(ppath);
   if (!ppath)
      return 0;

   return ppath->NormalOffsetFromAlignment(station);
}


Float64 bmfSpan::GetTributaryWidth(GirderIndexType gdrPathIdx, Float64 distFromStart)
{
   Float64 spacing_left;
   Float64 spacing_right;
   Float64 trib_width;

   spacing_left  = GetGirderPathSpacing( gdrPathIdx, Left,  distFromStart );
   spacing_right = GetGirderPathSpacing( gdrPathIdx, Right, distFromStart );

   if ( IsInteriorGirderPath( gdrPathIdx ) )
   {
      trib_width = ( spacing_left + spacing_right ) / 2.;
   }
   else
   {
      // This is an exterior girder
      CHECK( IsExteriorGirderPath( gdrPathIdx ) );

      trib_width = 0;
      if ( IsFirstGirderPath( gdrPathIdx ) )
         trib_width += spacing_left;
      else
         trib_width += spacing_left / 2.;

      if ( IsLastGirderPath( gdrPathIdx ) )
         trib_width += spacing_right;
      else
         trib_width += spacing_right / 2.;
   }

   return trib_width;
}

void bmfSpan::GetBearing(IDirection** ppBearing) const
{
   CComPtr<IAlignment> alignment;
   m_pBridge->GetAlignment(&alignment);

   CComPtr<IPoint2d> start_pnt, end_pnt;
   alignment->LocatePoint( CComVariant(StartBrgStation()), omtAlongDirection, 0.00, CComVariant(0.00), &start_pnt);
   alignment->LocatePoint( CComVariant(EndBrgStation()),   omtAlongDirection, 0.00, CComVariant(0.00), &end_pnt);

   CComPtr<ICogoEngine> engine;
   engine.CoCreateInstance(CLSID_CogoEngine);
   ATLASSERT(engine != NULL);

   CComQIPtr<IMeasure2> measure(engine);
   measure->Direction(start_pnt,end_pnt,ppBearing);
} // GetBearing

bmfBridge* bmfSpan::GetBridge() const
{
   return m_pBridge;
} // GetBridge

void bmfSpan::SetBridge(bmfBridge* pBridge)
{
   m_pBridge = pBridge;
} // SetBridge

bmfPier* bmfSpan::GetStartPier() const
{
   return m_pStartPier;
}

bmfPier* bmfSpan::GetEndPier() const
{
   return m_pEndPier;
} 

//======================== INQUIRY    =======================================
SpanIDType bmfSpan::GetID() const
{
   return m_ID;
} // GetID

Float64 bmfSpan::StartStation() const
{
   return m_pStartPier->GetStation();
} // StartStation

Float64 bmfSpan::StartBrgStation() const
{
   return m_pStartPier->GetAheadBearingStation();
} // StartBrgStation

Float64 bmfSpan::EndStation() const
{
   return m_pEndPier->GetStation();
} // EndStation

Float64 bmfSpan::EndBrgStation() const
{
   return m_pEndPier->GetBackBearingStation();
} // EndBrgStation

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfSpan::UpdateGirderPaths()
{
   GirderPathIterator begin = m_GirderPaths.begin();
   GirderPathIterator end   = m_GirderPaths.end();

   while ( begin != end )
   {
      boost::shared_ptr<bmfGirderPath>& ppath = *begin++;
      ppath->OnSpanChanged();
   }
} // Update

void bmfSpan::DoInitGirder( bmfGirder* pGirder )
{
   // Does nothing by default.
}


//======================== ACCESS     =======================================

void bmfSpan::StoreGirderPath(GirderIndexType gdrPathIdx, bmfGirderPath* pGirderPath)
{
   m_GirderPaths.insert(m_GirderPaths.begin() + gdrPathIdx, boost::shared_ptr<bmfGirderPath>(pGirderPath) );
} // StoreGirderPan

bmfGirderPath* bmfSpan::GetGirderPath(GirderIndexType gdrPathIdx) const
{
   WARN( gdrPathIdx > m_GirderPaths.size()-1,
        "Girder Path " << gdrPathIdx << " does not exist" );

   if ( gdrPathIdx > m_GirderPaths.size()-1 )
      return 0;

   return m_GirderPaths[gdrPathIdx].get();
} // GetGirderPath

//======================== INQUIRY    =======================================

bool bmfSpan::IsInteriorGirderPath(GirderIndexType gdrPathIdx) const
{
   return !IsExteriorGirderPath(gdrPathIdx);
} // IsInteriorGirderPath

bool bmfSpan::IsExteriorGirderPath(GirderIndexType gdrPathIdx) const
{
   return ( (gdrPathIdx == 0 || gdrPathIdx == (GetGirderPathCount() - 1)) ? true : false);
} // IsExteriorGirderPath

bool bmfSpan::IsFirstGirderPath(GirderIndexType gdrPathIdx) const
{
   return (gdrPathIdx == 0 ? true : false);
} // IsFirstGirderPath

bool bmfSpan::IsLastGirderPath(GirderIndexType gdrPathIdx) const
{
   return (gdrPathIdx == (GetGirderPathCount() - 1) ? true : false);
} // IsLastGirderPath

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void bmfSpan::SetStartPier(bmfPier* pPier)
{
   m_pStartPier = pPier;
   OnStartPierChanged();
} // SetStartPier

void bmfSpan::SetEndPier(bmfPier* pPier)
{
   m_pEndPier = pPier;
   OnEndPierChanged();
} // SetEndPier

//======================== ACCESS     =======================================
//======================== INQUERY ==========================================
