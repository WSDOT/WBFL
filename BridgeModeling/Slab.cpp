///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2015  Washington State Department of Transportation
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

/****************************************************************************
CLASS
   bmfSlab           
****************************************************************************/

#include <BridgeModeling\Slab.h>
#include <BridgeModeling\Bridge.h>
#include <BridgeModeling\Span.h>
#include <BridgeModeling\Pier.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

bmfSlab::bmfSlab(const matConcreteEx* pConc,Float64 grossDepth,Float64 overhang,Float64 offset,Float64 sacDepth,Float64 overlayDepth,Float64 density)
{
   PRECONDITION( pConc != 0 );
   PRECONDITION( grossDepth > 0 );
   PRECONDITION( overhang > 0 );
   PRECONDITION( offset > 0 && offset >= grossDepth );
   PRECONDITION( sacDepth >= 0 );
   PRECONDITION( overlayDepth >= 0 );
   PRECONDITION( density >= 0 );

   m_pConc            = pConc;
   m_GrossDepth       = grossDepth;
   m_Overhang         = overhang;
   m_SlabOffset       = offset;
   m_SacrificialDepth = sacDepth;
   m_OverlayDepth     = overlayDepth;
   m_OverlayDensity   = density;

   Init();

   ASSERTVALID;
}

bmfSlab::bmfSlab(const bmfSlab& rOther)
{
   MakeCopy( rOther );

   ASSERTVALID;
} // Slab

bmfSlab::~bmfSlab()
{
} // ~Slab

//======================== OPERATORS  =======================================

bmfSlab& bmfSlab::operator = (const bmfSlab& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   ASSERTVALID;

   return *this;
} // operator =

//======================== OPERATIONS =======================================

void bmfSlab::PlanView(HDC hDC, const grlibPointMapper& mapper) const
{
   ASSERTVALID;

   if (!m_IsGeometryCorrect)
      UpdateGeometry();

   HPEN hOldPen, hPen;

   // Setup DC
   int lw = bmfBridge::GetSolidLineWidth(hDC);
   hPen = ::CreatePen(PS_SOLID,lw,RGB(125,125,125));
   hOldPen = (HPEN)::SelectObject(hDC,hPen);

   CComPtr<ICogoModel> cogo;
   m_pBridge->GetCogoModel(&cogo);

   CComPtr<IAlignment> alignment;
   m_pBridge->GetAlignment(&alignment);

   CComPtr<IPointCollection> points;
   cogo->get_Points(&points);

   // Draw start edge
   CComPtr<IPoint2d> p1, p2;
   points->get_Item(m_StartLeftId,  &p1);
   points->get_Item(m_StartRightId, &p2);

   POINT pnt1, pnt2;
   mapper.WPtoDP( p1, &pnt1.x, &pnt1.y );
   mapper.WPtoDP( p2, &pnt2.x, &pnt2.y );

   ::MoveToEx( hDC, pnt1.x, pnt1.y, NULL );
   ::LineTo( hDC, pnt2.x, pnt2.y );

   const bmfSpan* pSpan = m_pBridge->GetSpan(0);
   CHECK( pSpan != 0 );
   Float64 frame_width = FrameWidth(pSpan);
   Float64 overhang = GetOverhang();
   Float64 offset = overhang + frame_width/2;
   Int16 nChords = 100;
   Float64 start_station = pSpan->GetStartPier()->GetStation();
   Float64 end_station = pSpan->GetEndPier()->GetStation();
   Float64 station_step = (end_station - start_station)/(nChords-1);

   CComPtr<IDirection> start_brg;
   pSpan->GetStartPier()->GetBearing(&start_brg);

   CComPtr<IAngle> start_skew, end_skew;
   pSpan->GetStartPier()->GetSkewAngle(&start_skew);
   pSpan->GetEndPier()->GetSkewAngle(&end_skew);

   Float64 start_skew_value, end_skew_value;
   start_skew->get_Value(&start_skew_value);
   end_skew->get_Value(&end_skew_value);

   Float64 diff_angle_value = end_skew_value - start_skew_value;
   Float64 delta_skew_value = diff_angle_value/(nChords-1);

   CComPtr<IDirection> skew_dir;
   start_brg->Clone(&skew_dir);

   // Draw Left Edge
   ::MoveToEx( hDC, pnt1.x, pnt1.y, NULL );
   for ( Int16 i = 0; i < nChords; i++ )
   {
      LONG dx, dy;
      Float64 station = start_station + i*station_step;

      CComPtr<IDirection> normal;
      alignment->Normal(CComVariant(station),&normal); // toward right of alignment
      normal->IncrementBy(CComVariant(M_PI)); // now toward left of alignment
      
      Float64 normal_value;
      normal->get_Value(&normal_value);

      CComPtr<IAngle> skew;
      skew_dir->AngleBetween(normal,&skew);
      
      Float64 skew_value;
      skew->get_Value(&skew_value);

      Float64 offset2; // offset adjusted for skew angle;
      offset2 = offset / fabs(cos(skew_value));
      
      CComPtr<IPoint2d> pnt;
      alignment->LocatePoint(CComVariant(station),omtAlongDirection, -offset2,CComVariant(skew_dir),&pnt);

      mapper.WPtoDP(pnt,&dx,&dy);
      ::LineTo(hDC,dx,dy);

      skew_dir->put_Value( normal_value + delta_skew_value*i + start_skew_value );
   }

   // Draw Right Edge
   skew_dir.Release();
   start_brg->Clone(&skew_dir);

   ::MoveToEx( hDC, pnt2.x, pnt2.y, NULL );
   for ( Int16 i = 0; i < nChords; i++ )
   {
      LONG dx, dy;
      Float64 station = start_station + i*station_step;

      CComPtr<IDirection> normal;
      alignment->Normal(CComVariant(station),&normal); // toward right of alignment
      normal->IncrementBy(CComVariant(M_PI)); // now toward left of alignment

      Float64 normal_value;
      normal->get_Value(&normal_value);


      CComPtr<IAngle> skew;
      skew_dir->AngleBetween(normal,&skew);

      Float64 skew_value;
      skew->get_Value(&skew_value);

      Float64 offset2; // offset adjusted for skew angle;
      offset2 = offset / fabs(cos(skew_value));

      CComPtr<IPoint2d> pnt;
      alignment->LocatePoint(CComVariant(station), omtAlongDirection, offset2,CComVariant(skew_dir),&pnt);      
      mapper.WPtoDP(pnt,&dx,&dy);
      ::LineTo(hDC,dx,dy);

      skew_dir->put_Value( normal_value + delta_skew_value*i + start_skew_value );
   }

   // Draw end edge
   p1.Release();
   p2.Release();
   points->get_Item(m_EndLeftId,&p1);
   points->get_Item(m_EndRightId,&p2);

   mapper.WPtoDP( p1, &pnt1.x, &pnt1.y );
   mapper.WPtoDP( p2, &pnt2.x, &pnt2.y );
   ::MoveToEx( hDC, pnt1.x, pnt1.y, NULL );
   ::LineTo( hDC, pnt2.x, pnt2.y );


   // Clean up
   ::SelectObject(hDC,hOldPen);
   ::DeleteObject(hPen);
} // Draw

void bmfSlab::OnAlignmentChanged()
{
   UpdateGeometry();
}

gpRect2d bmfSlab::GetExtents() const
{
   if (!m_IsGeometryCorrect)
      UpdateGeometry();

   Float64 minX, maxX, minY, maxY;

   minX =  Float64_Max;
   maxX = -Float64_Max;
   minY =  Float64_Max;
   maxY = -Float64_Max;

   CComPtr<ICogoModel> cogo;
   m_pBridge->GetCogoModel(&cogo);

   CComPtr<IPointCollection> points;
   cogo->get_Points(&points);

   CComPtr<IPoint2d> pnt;
   Float64 x,y;
   points->get_Item(m_StartLeftId,&pnt);
   pnt->get_X(&x); pnt->get_Y(&y);

   minX = min( minX,  x );
   maxX = max( maxX,  x );
   minY = min( minY,  y );
   maxY = max( maxY,  y );
   
   pnt.Release();
   points->get_Item(m_StartRightId,&pnt);
   pnt->get_X(&x); pnt->get_Y(&y);
   minX = min( minX,  x );
   maxX = max( maxX,  x );
   minY = min( minY,  y );
   maxY = max( maxY,  y );
   
   pnt.Release();
   points->get_Item(m_EndLeftId,&pnt);
   pnt->get_X(&x); pnt->get_Y(&y);
   minX = min( minX,  x );
   maxX = max( maxX,  x );
   minY = min( minY,  y );
   maxY = max( maxY,  y );
   
   pnt.Release();
   points->get_Item(m_EndRightId,&pnt);
   pnt->get_X(&x); pnt->get_Y(&y);
   minX = min( minX,  x );
   maxX = max( maxX,  x );
   minY = min( minY,  y );
   maxY = max( maxY,  y );

   gpRect2d extents( minX, minY, maxX, maxY );
   return extents;
} // GetExtents

//======================== ACCESS     =======================================
const matConcreteEx* bmfSlab::GetConcrete() const
{
   return m_pConc;
}

Float64 bmfSlab::GetStructuralDepth() const
{
   Float64 depth;
   depth = GetGrossDepth() - m_SacrificialDepth;
   return depth;
} // GetStructuralDepth

void bmfSlab::SetGrossDepth(Float64 depth)
{
   m_GrossDepth = depth;
}

void bmfSlab::SetOverhang(Float64 overhang)
{
   m_Overhang = overhang;
   UpdateGeometry();
}

void bmfSlab::SetOffset(Float64 offset)
{
   m_SlabOffset = offset;
}

void bmfSlab::SetOverlayDepth(Float64 depth)
{
   m_OverlayDepth = depth;
}

void bmfSlab::SetOverlayDensity(Float64 density)
{
   m_OverlayDensity = density;
}

Float64 bmfSlab::GetWidth() const
{
   const bmfSpan* pSpan = m_pBridge->GetSpan(0);
   CHECK(pSpan != 0 );

   return 2*GetOverhang() + FrameWidth(pSpan);
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
Float64 bmfSlab::FrameWidth(const bmfSpan* pSpan) const
{
   Float64 frame_width; // width between exterior girders
   GirderIndexType girder_line_count;
   Float64 spacing;
   bmfMeasuredWhere where;
   bmfMeasuredHow how;

   m_pBridge->GetGirderPathLayout( pSpan->GetID(),
                                   girder_line_count,
                                   spacing,
                                   where,
                                   how );

   frame_width = (girder_line_count-1) * spacing;

   return frame_width;
}


//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfSlab::Init()
{
   m_IsGeometryCorrect = false;
   m_StartLeftId  = -1;
   m_StartRightId = -2;
   m_EndLeftId    = -3;
   m_EndRightId   = -4;
}

void bmfSlab::SetBridge(bmfBridge* pBridge)
{
   m_pBridge = pBridge;
   UpdateGeometry();
} // SetBridge

void bmfSlab::MakeCopy( const bmfSlab& rOther)
{
   m_pConc            = rOther.m_pConc;
   m_GrossDepth       = rOther.m_GrossDepth;
   m_Overhang         = rOther.m_Overhang;
   m_SlabOffset       = rOther.m_SlabOffset;
   m_SacrificialDepth = rOther.m_SacrificialDepth;
   m_OverlayDepth     = rOther.m_OverlayDepth;
   m_OverlayDensity   = rOther.m_OverlayDensity;

   Init();

   ASSERTVALID;
}

void bmfSlab::MakeAssignment( const bmfSlab& rOther)
{
   MakeCopy( rOther );
}

void bmfSlab::UpdateGeometry() const
{
   // :TODO: rab 12.20.96 : Update for complex bridge geometry
   // :METHOD: Slab::UpdateGeometry()
   //
   // This method is implemented around the assumption that there
   // is only one span and it is straight.
   //
   // This method will need to be updated when more complex bridge geometry
   // is used.
#pragma Reminder("bmfSlab::UpdateGeometry - assume one straight span")
   // upon closer inspection... it looks like this works for multiple spans
   // of simple geometry (loops on spans). RAB 6.3.04
   // If used for multi-span, there is a bug in the slab corner point IDs.. there are only 4 of them

   ClearPoints();

   CComPtr<IAlignment> alignment;
   m_pBridge->GetAlignment(&alignment);

   CComPtr<ICogoModel> cogo;
   m_pBridge->GetCogoModel(&cogo);

   CComPtr<IPointCollection> points;
   cogo->get_Points(&points);

   Float64 first_pier_station;
   Float64 last_pier_station;
   GirderIndexType girder_line_count;
   Float64 frame_width; // width between exterior girders
   Float64 offset_to_edge_of_slab;
   Float64 spacing;
   bmfMeasuredWhere where;
   bmfMeasuredHow how;

   std::vector<bmfSpan*> vSpans;
   m_pBridge->GetSpans( vSpans );
   std::vector<bmfSpan*>::iterator i;
   for ( i = vSpans.begin(); i != vSpans.end(); i++ )
   {
      const bmfSpan* pSpan = *i;
      const bmfPier* pStartPier = pSpan->GetStartPier();
      const bmfPier* pEndPier = pSpan->GetEndPier();

      first_pier_station = pStartPier->GetStation();
      last_pier_station  = pEndPier->GetStation();

      m_pBridge->GetGirderPathLayout( pSpan->GetID(),
                                      girder_line_count,
                                      spacing,
                                      where,
                                      how );

      // :WARNING: rab 12.20.96: Assumption
      // :METHOD: Slab::UpdateGeometry()
      //
      // This computation assumes that the girder framing is symetrical
      // about the alignment. This will change when more complex
      // geometry is used.
      frame_width = FrameWidth(pSpan);
      offset_to_edge_of_slab = GetOverhang() + frame_width / 2;

      CComPtr<IAngle> skew_angle;
      pStartPier->GetSkewAngle(&skew_angle);
      Float64 skew_angle_value;
      skew_angle->get_Value(&skew_angle_value);

      offset_to_edge_of_slab /= fabs(cos( skew_angle_value ));

      CComPtr<IDirection> pier_direction;
      pStartPier->GetBearing(&pier_direction);

      CComPtr<IPoint2d> temp_pnt;
      alignment->LocatePoint( CComVariant(first_pier_station), omtAlongDirection, offset_to_edge_of_slab, CComVariant(pier_direction), &temp_pnt);
      points->AddEx(m_StartLeftId,temp_pnt);

      temp_pnt.Release();
      alignment->LocatePoint( CComVariant(first_pier_station), omtAlongDirection, -offset_to_edge_of_slab, CComVariant(pier_direction), &temp_pnt);
      points->AddEx(m_StartRightId,temp_pnt);

      offset_to_edge_of_slab = GetOverhang() + frame_width / 2;

      skew_angle.Release();
      pEndPier->GetSkewAngle(&skew_angle);
      skew_angle->get_Value(&skew_angle_value);
      offset_to_edge_of_slab /= fabs(cos( skew_angle_value ));

      pier_direction.Release();
      pEndPier->GetBearing(&pier_direction);

      temp_pnt.Release();
      alignment->LocatePoint( CComVariant(last_pier_station), omtAlongDirection, offset_to_edge_of_slab, CComVariant(pier_direction), &temp_pnt);
      points->AddEx(m_EndLeftId,temp_pnt);

      temp_pnt.Release();
      alignment->LocatePoint( CComVariant(last_pier_station), omtAlongDirection, -offset_to_edge_of_slab, CComVariant(pier_direction), &temp_pnt);
      points->AddEx(m_EndRightId,temp_pnt);
   }

   m_IsGeometryCorrect = true;
} // UpdateGeometry

void bmfSlab::ClearPoints() const
{

   CComPtr<ICogoModel> cogo;
   m_pBridge->GetCogoModel(&cogo);

   CComPtr<IPointCollection> points;
   cogo->get_Points(&points);

   points->Remove(m_StartLeftId);
   points->Remove(m_StartRightId);
   points->Remove(m_EndLeftId);
   points->Remove(m_EndRightId);
}

//======================== ACCESS     =======================================
//======================== INQUERY ==========================================

//======================== DEBUG   ==========================================
#if defined _DEBUG
bool bmfSlab::AssertValid() const
{
   if ( m_pConc == 0 )
      return false;

   if ( m_GrossDepth <= 0 )
      return false;

   if ( m_Overhang <= 0 )
      return false;

   if ( m_SlabOffset <= 0 || m_SlabOffset < m_GrossDepth )
      return false;

   if ( m_SacrificialDepth < 0 || m_GrossDepth < m_SacrificialDepth )
      return false;

   if ( m_OverlayDepth < 0 )
      return false;

   if ( m_OverlayDensity < 0 )
      return false;

   return true;
}

void bmfSlab::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfSlab" << endl;
   os << "================" << endl;
   os << "m_pConc             = " << (void*)m_pConc << endl;
   os << "m_GrossDepth        = " << m_GrossDepth << endl;
   os << "m_Overhang          = " << m_Overhang << endl;
   os << "m_SlabOffset        = " << m_SlabOffset << endl;
   os << "m_SacrificialDepth  = " << m_SacrificialDepth << endl;
   os << "m_OverlayDepth      = " << m_OverlayDepth << endl;
   os << "m_OverlayDensity    = " << m_OverlayDensity << endl;
   os << "m_IsGeometryCorrect = " << m_IsGeometryCorrect << endl;
   os << "m_StartLeftId       = " << m_StartLeftId << endl;
   os << "m_StartRightId      = " << m_StartRightId << endl;
   os << "m_EndLeftId         = " << m_EndLeftId << endl;
   os << "m_EndRightId        = " << m_EndRightId << endl;
   os << "m_pBridge           = " << m_pBridge << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfSlab::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfSlab");
   // This class does not exist in isolation.  Test with a bridge model.
   TESTME_EPILOG("bmfSlab");
}
#endif // _UNITTEST
