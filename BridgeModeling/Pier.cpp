///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2010  Washington State Department of Transportation
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
// NAME:          bmfPier           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <BridgeModeling\Pier.h>                  // class implementation
#include <BridgeModeling\Bridge.h>
#include <BridgeModeling\Span.h>
#include <MathEx.h>
#include <GraphicsLib\GraphTool.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DIAG_DECLARE_GROUP( bmf )

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bmfPier::bmfPier()
{
   m_ID = 0;
   m_Station = 0.;
   m_pBridge = 0;
   m_pLeftSpan = 0;
   m_pRightSpan = 0;
   m_pConnection = 0;
} // bmfPier

bmfPier::bmfPier(Float64 station,const bmfPierLayout& pl,const bmfConnection* pConnection)
{
   m_ID = 0;
   m_pBridge = 0;
   m_pLeftSpan = 0;
   m_pRightSpan = 0;

   m_Station = station;

   m_Layout = pl;

   m_pConnection = pConnection;
} // bmfPier

bmfPier::bmfPier(const bmfPier& rOther)
{
   m_ID = 0;
   m_Station = 0.;
   m_pBridge = 0;
   m_pLeftSpan = 0;
   m_pRightSpan = 0;
   m_pConnection = 0;

   MakeCopy( rOther );
}

bmfPier::~bmfPier()
{
} // ~bmfPier

//======================== OPERATORS  =======================================
bmfPier& bmfPier::operator=(const bmfPier& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

bool bmfPier::operator == (const bmfPier& p)
{
   return ( GetStation() == p.GetStation() ? true : false);
}

//======================== OPERATIONS =======================================

void bmfPier::SetID(Int32 id)
{
   m_ID = id;
} // SetID

void bmfPier::OnSetup()
{
   // Does nothing by default
} // OnSetup

void bmfPier::Draw(HDC hDC, const grlibPointMapper& mapper, bool show_label) const
{
   WATCHX( bmf, BMF_LEVEL_DRAW, "Drawing pier " << GetID() );

   Int32 dx,dy;
   POINT p;
   HPEN hClPierPen;
   HPEN hBearingPen;
   HPEN hPierPen;
   HPEN hOldPen;

   int lw = bmfBridge::GetSolidLineWidth(hDC);

   hClPierPen  = (HPEN)::CreatePen(PS_DASHDOT, 1,RGB(255,   0,   0) );
   hBearingPen = (HPEN)::CreatePen(PS_DOT,     1, RGB(  0,   0, 255) );
   hPierPen    = (HPEN)::CreatePen(PS_SOLID,   lw, RGB(128, 128, 128) );
   
   CComPtr<IAlignment> alignment;
   m_pBridge->GetAlignment(&alignment);

   // 
   // Determine Width of pier
   //
   Float64 pier_width_left = 0; // perpendicular to the alignment
   Float64 pier_width_right = 0;
   Float64 pier_width;

   // Get the slab overhang
   bmfSlab* p_slab = m_pBridge->GetSlab();
   Float64 overhang;
   if ( p_slab )
      overhang = p_slab->GetOverhang();
   else
      overhang = 0;

   CComPtr<IAngle> skewAngle;
   GetSkewAngle(&skewAngle);
   Float64 skewAngleValue;
   skewAngle->get_Value(&skewAngleValue);

   const bmfSpan* p_span;
   p_span = GetLeftSpan();
   if ( p_span )
   {
      Int32 num_girders;
      Float64 spacing;
      bmfMeasuredHow how;
      bmfMeasuredWhere where;
      p_span->GetGirderPathLayout( num_girders, spacing, where, how );
      pier_width_left = 2*overhang + (num_girders-1)*spacing;

	   // adjust for skew
	   pier_width_left /= cos( skewAngleValue );
   }

   p_span = GetRightSpan();
   if ( p_span )
   {
      Int32 num_girders;
      Float64 spacing;
      bmfMeasuredHow how;
      bmfMeasuredWhere where;
      p_span->GetGirderPathLayout( num_girders, spacing, where, how );
      pier_width_right = 2*overhang + (num_girders-1)*spacing;

	   // adjust for skew
	   pier_width_right /= cos( skewAngleValue );
   }

   if ( IsZero(pier_width_left) )
      pier_width = pier_width_right;
   else if ( IsZero(pier_width_right) )
      pier_width = pier_width_left;
   else
      pier_width = (pier_width_left + pier_width_right)/2;

   //
   // Draw CL Pier
   //
   hOldPen = (HPEN)::SelectObject(hDC,hClPierPen);

   CComPtr<IDirection> bearing;
   GetBearing(&bearing);

   CComPtr<IPoint2d> pnt;
   alignment->LocatePoint( CComVariant(GetStation()), -pier_width/2, CComVariant(bearing), &pnt );
   mapper.WPtoDP(pnt, &dx, &dy);
   ::MoveToEx(hDC,dx,dy,&p);

   pnt.Release();
   alignment->LocatePoint( CComVariant(GetStation()),  pier_width/2, CComVariant(bearing), &pnt);
   mapper.WPtoDP(pnt, &dx, &dy);
   ::LineTo(hDC,dx,dy);

   //
   // Draw the CL Bearing Lines
   //
   ::SelectObject(hDC,hBearingPen);
   p_span = GetLeftSpan();
   if ( p_span )
   {
      pnt.Release();
      alignment->LocatePoint( CComVariant(GetBackBearingStation()), -pier_width_left/2, CComVariant(bearing), &pnt );
      mapper.WPtoDP(pnt, &dx, &dy);
      ::MoveToEx( hDC, dx, dy, &p );

      pnt.Release();
      alignment->LocatePoint( CComVariant(GetBackBearingStation()),  pier_width_left/2, CComVariant(bearing), &pnt );
      mapper.WPtoDP(pnt, &dx, &dy);
      ::LineTo( hDC, dx, dy );
   }

   p_span = GetRightSpan();
   if ( p_span )
   {
      pnt.Release();
      alignment->LocatePoint( CComVariant(GetAheadBearingStation()), -pier_width_right/2, CComVariant(bearing), &pnt );
      mapper.WPtoDP(pnt, &dx, &dy);
      ::MoveToEx( hDC, dx, dy, &p );

      pnt.Release();
      alignment->LocatePoint( CComVariant(GetAheadBearingStation()),  pier_width_right/2, CComVariant(bearing), &pnt );
      mapper.WPtoDP(pnt, &dx, &dy);
      ::LineTo( hDC, dx, dy );
   }

   // 
   // Draw a rectangle symbol to represent the pier
   //
   Float64 depth_left  = 1.2 * ( GetStation() - GetBackBearingStation() );
   Float64 depth_right = 1.2 * ( GetAheadBearingStation() - GetStation() );

   Float64 station_left  = GetStation() - depth_left;
   Float64 station_right = GetStation() + depth_right;
   if ( IsZero( pier_width_left ) )
      pier_width_left = pier_width_right;
   if ( IsZero( pier_width_right ) )
      pier_width_right = pier_width_left;

   CComPtr<IPoint2d> p1, p2, p3, p4;
   alignment->LocatePoint( CComVariant(station_left),  -pier_width_left/2,  CComVariant(bearing), &p1 );
   alignment->LocatePoint( CComVariant(station_right), -pier_width_right/2, CComVariant(bearing), &p2 );
   alignment->LocatePoint( CComVariant(station_right),  pier_width_right/2, CComVariant(bearing), &p3 );
   alignment->LocatePoint( CComVariant(station_left),   pier_width_left/2,  CComVariant(bearing), &p4 );

   POINT point[5];
   mapper.WPtoDP( p1, &point[0].x, &point[0].y );
   mapper.WPtoDP( p2, &point[1].x, &point[1].y );
   mapper.WPtoDP( p3, &point[2].x, &point[2].y );
   mapper.WPtoDP( p4, &point[3].x, &point[3].y );

   point[4] = point[0];

   ::SelectObject(hDC,hPierPen);
   ::Polyline( hDC, point, 5 );

   if (show_label)
   {
      //
      // Label Pier
      //
      pnt.Release();
      alignment->LocatePoint( CComVariant(GetStation()), 0.00, CComVariant(0.00), &pnt );
      mapper.WPtoDP( pnt, &dx, &dy );
      char label[10]; // arbitrary label size... I doubt we will ever exceed it
      _itoa_s( GetID()+1, label, 10, 10 ); // Add one because we have a zero-based index
      std::string message( "Pier ");
      message += label;

      Float64 ccw_angle_from_east;
      bearing->get_Value(&ccw_angle_from_east);

      if ( ccw_angle_from_east < 0 )
         ccw_angle_from_east += TWO_PI;

      if ( PI_OVER_2 < ccw_angle_from_east && IsLE(ccw_angle_from_east, 3*PI_OVER_2 ) )
         ccw_angle_from_east -= M_PI;

      Int32 intang = (Int32)(ccw_angle_from_east * (float)(180./M_PI)*10);

      UINT old_align = ::SetTextAlign( hDC, TA_BOTTOM | TA_CENTER );
      grGraphTool::TextOutRotated(hDC, dx, dy, intang, message.c_str(), message.length(), 8);
   } // show_label

   // Cleanup dc
   ::SelectObject( hDC, hOldPen );
   ::DeleteObject( hClPierPen );
   ::DeleteObject( hBearingPen );
   ::DeleteObject( hPierPen );
} // Draw

void bmfPier::OnAlignmentChanged()
{
   // Does nothing by default.
}

void bmfPier::Move(Float64 station)
{
   m_Station = station;
} // Move

void bmfPier::Layout(const bmfPierLayout& pl)
{
   m_Layout = pl;
} // Layout

void bmfPier::SetConnection(const bmfConnection* pConnection)
{
   m_pConnection = pConnection;
} // SetConnection

//======================== ACCESS     =======================================
Float64 bmfPier::GetStation() const
{
   return m_Station;
} // GetStation

Float64 bmfPier::GetAheadBearingStation() const
{
   Float64 station;
   Float64 bearing_offset;

   bearing_offset = m_pConnection->GetBearingOffset();

   switch( m_pConnection->GetHowBearingOffSetIsMeasured() )
   {
   case AlongLine:
        // Do nothing
        break;

   case NormalToLine:
        // Interpert as normal to the pier
        CComPtr<IAngle> skewAngle;
        GetSkewAngle(&skewAngle);
        Float64 angle;
        skewAngle->get_Value(&angle);
        bearing_offset /= cos( fabs( angle ) );
        break;
   }

   station = GetStation() + bearing_offset;

   return station;
}

Float64 bmfPier::GetBackBearingStation() const
{
   Float64 station;
   Float64 bearing_offset;

   bearing_offset = m_pConnection->GetBearingOffset();

   switch( m_pConnection->GetHowBearingOffSetIsMeasured() )
   {
   case AlongLine:
        // Do nothing
        break;

   case NormalToLine:
        // Interpert as normal to the pier
        CComPtr<IAngle> skewAngle;
        GetSkewAngle(&skewAngle);
        Float64 angle;
        skewAngle->get_Value(&angle);
        bearing_offset /= cos( fabs( angle ) );
        break;
   }

   station = GetStation() - bearing_offset;

   return station;
}

void bmfPier::GetSkewAngle(IAngle** ppSkewAngle) const
{
   CComPtr<IAngle> skewAngle;

   switch( m_Layout.GetOrientation() )
   {
   case bmfPierLayout::NormalToAlignment:
      skewAngle.CoCreateInstance(CLSID_Angle);
      break;

   case bmfPierLayout::SkewAngle:
      m_Layout.GetSkewAngle(&skewAngle);
      break;

   case bmfPierLayout::Bearing:
      CComPtr<IAlignment> alignment;
      m_pBridge->GetAlignment(&alignment);

      CComPtr<IDirection> brg_of_normal;
      alignment->Normal(CComVariant(GetStation()),&brg_of_normal);  // right of alignment
      brg_of_normal->IncrementBy( CComVariant(M_PI) ); // make left of alignment

      CComPtr<IDirection> bearing;
      m_Layout.GetBearing(&bearing); // should be left of alignment

      bearing->AngleBetween(brg_of_normal,&skewAngle);

      Float64 skew_angle_value;
      skewAngle->get_Value(&skew_angle_value);
      if ( M_PI < skew_angle_value )
      {
         // skew is right of bearing
         // make the skew angle value a neg value
         skew_angle_value = -2*M_PI + skew_angle_value;
         skewAngle->put_Value(skew_angle_value);
      }

      break;
   }

   (*ppSkewAngle) = skewAngle;
   (*ppSkewAngle)->AddRef();
} // GetSkewAngle

void bmfPier::GetBearing(IDirection** ppBearing) const
{
   CComPtr<IDirection> bearing;
   CComPtr<IAngle> skewAngle;

   CComPtr<IAlignment> alignment;
   m_pBridge->GetAlignment(&alignment);

   switch( m_Layout.GetOrientation() )
   {
   case bmfPierLayout::NormalToAlignment:
      alignment->Normal(CComVariant(GetStation()),&bearing);  // right of alignment
      bearing->IncrementBy(CComVariant(M_PI)); // make left of alignment
      break;

   case bmfPierLayout::SkewAngle:
      alignment->Normal(CComVariant(GetStation()),&bearing);  // right of alignment
      bearing->IncrementBy(CComVariant(M_PI)); // make left of alignment
      m_Layout.GetSkewAngle(&skewAngle);
      bearing->IncrementBy(CComVariant(skewAngle));
      break;

   case bmfPierLayout::Bearing:
      m_Layout.GetBearing(&bearing); // should be left of alignment
      break;
   }

   (*ppBearing) = bearing;
   (*ppBearing)->AddRef();
} // GetBearing

const bmfConnection* bmfPier::GetConnection() const
{
   return m_pConnection;
} // GetConnection

bmfPierLayout bmfPier::GetLayout() const
{
   return m_Layout;
} // GetLayout

void bmfPier::MakeCopy(const bmfPier& rOther)
{
   m_Station = rOther.GetStation();
   m_Layout = rOther.GetLayout();
   m_pConnection = rOther.m_pConnection;
}

void bmfPier::MakeAssignment(const bmfPier& rOther)
{
   MakeCopy( rOther );
}

void bmfPier::SetBridge(bmfBridge* pBridge)
{
   m_pBridge = pBridge;
} // SetBridge

void bmfPier::SetLeftSpan(bmfSpan* pSpan)
{
   m_pLeftSpan = pSpan;
}

bmfSpan* bmfPier::GetLeftSpan()
{
   return m_pLeftSpan;
}

const bmfSpan* bmfPier::GetLeftSpan() const
{
   return m_pLeftSpan;
}

void bmfPier::SetRightSpan(bmfSpan* pSpan)
{
   m_pRightSpan = pSpan;
}

bmfSpan* bmfPier::GetRightSpan()
{
   return m_pRightSpan;
}

const bmfSpan* bmfPier::GetRightSpan() const
{
   return m_pRightSpan;
}

gpRect2d bmfPier::GetBoundingBox() const
{
   // 
   // Determine Width of pier
   //
   Float64 pier_width_left = 0; // perpendicular to the alignment
   Float64 pier_width_right = 0;
   Float64 pier_width;

   // Get the slab overhang
   bmfSlab* p_slab = m_pBridge->GetSlab();
   Float64 overhang;
   if ( p_slab )
      overhang = p_slab->GetOverhang();
   else
      overhang = 0;

   const bmfSpan* p_span;
   p_span = GetLeftSpan();
   if ( p_span )
   {
      Int32 num_girders;
      Float64 spacing;
      bmfMeasuredHow how;
      bmfMeasuredWhere where;
      p_span->GetGirderPathLayout( num_girders, spacing, where, how );
      pier_width_left = 2*overhang + (num_girders-1)*spacing;
   }

   p_span = GetRightSpan();
   if ( p_span )
   {
      Int32 num_girders;
      Float64 spacing;
      bmfMeasuredHow how;
      bmfMeasuredWhere where;
      p_span->GetGirderPathLayout( num_girders, spacing, where, how );
      pier_width_right = 2*overhang + (num_girders-1)*spacing;
   }

   if ( IsZero(pier_width_left) )
      pier_width = pier_width_right;
   else if ( IsZero(pier_width_right) )
      pier_width = pier_width_left;
   else
      pier_width = (pier_width_left + pier_width_right)/2;

   Float64 depth_left  = 1.2 * ( GetStation() - GetBackBearingStation() );
   Float64 depth_right = 1.2 * ( GetAheadBearingStation() - GetStation() );

   Float64 station_left  = GetStation() - depth_left;
   Float64 station_right = GetStation() + depth_right;
   if ( IsZero( pier_width_left ) )
      pier_width_left = pier_width_right;
   if ( IsZero( pier_width_right ) )
      pier_width_right = pier_width_left;

   CComPtr<IAlignment> alignment;
   m_pBridge->GetAlignment(&alignment);

   CComPtr<IDirection> bearing;
   GetBearing(&bearing);
   CComPtr<IPoint2d> p1, p2, p3, p4;
   alignment->LocatePoint( CComVariant(station_left),   pier_width_left/2,  CComVariant(bearing), &p1 );
   alignment->LocatePoint( CComVariant(station_right),  pier_width_right/2, CComVariant(bearing), &p2 );
   alignment->LocatePoint( CComVariant(station_right), -pier_width_right/2, CComVariant(bearing), &p3 );
   alignment->LocatePoint( CComVariant(station_left),  -pier_width_left/2,  CComVariant(bearing), &p4 );

   Float64 x1, y1;
   Float64 x2, y2;
   Float64 x3, y3;
   Float64 x4, y4;
   p1->get_X(&x1); p1->get_Y(&y1);
   p2->get_X(&x2); p2->get_Y(&y2);
   p3->get_X(&x3); p3->get_Y(&y3);
   p4->get_X(&x4); p4->get_Y(&y4);

   gpRect2d box;
   box.Left()   = min( min( x1, x2 ), min( x3, x4 ) );
   box.Bottom() = min( min( y1, y2 ), min( y3, y4 ) );
   box.Right()  = max( max( x1, x2 ), max( x3, x4 ) );
   box.Top()    = max( max( y1, y2 ), max( y3, y4 ) );

   return box;
}

//======================== INQUIRY    =======================================
Int32 bmfPier::GetID() const
{
   return m_ID;
} // GetID

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
//======================== ACCESS     =======================================
//======================== INQUERY ==========================================
