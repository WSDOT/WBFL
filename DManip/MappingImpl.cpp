///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include "pch.h"
#include <DManip/MappingImpl.h>
#include <DManip/DisplayView.h>

using namespace WBFL::DManip;

LONG round_to_nearest_whole_number(Float64 x)
{
   // :WARNING: rab 11.15.96 : Possible loss of data
   // :METHOD: round_to_nearest_whole_number()
   //
   // ceil and floor return Float64. These return values must
   // be cast to LONG. Float64s are 8 byte and longs are 4 byte
   // this could result in a possible loss of data. (Though I've
   // never experienced it)

   return  LONG((x - LONG(x)) > 0.5) ? (LONG)ceil(x) : (LONG)floor(x);
} // round_to_nearest_whole_number


Mapping::Mapping()
{
   // crazy dummy values to help detect errors
   m_WEX_over_LEX = -9999; // m_WorldExtentX/m_LogicalExtentX
   m_WEY_over_LEY = -9999; // m_WorldExtentY/m_LogicalExtentY
   m_LEX_over_WEX = -9999; // m_LogicalExtentX/m_WorldExtentX
   m_LEY_over_WEY = -9999; // m_LogicalExtentY/m_WorldExtentY

   m_WorldExtent.SetDimensions(1.0,1.0);

   m_LogicalExtentX = 1;
   m_LogicalExtentY = 1;
   m_LogicalOriginX = 1;
   m_LogicalOriginY = 1;
   m_OriginalLogicalExtentX = 1;
   m_OriginalLogicalExtentY = 1;

   SetRotation(0, 0, 0);

   UpdateMappingScale();

   m_MappingMode = MapMode::Anisotropic;
}

Mapping::~Mapping()
{
   // if this assert fires it means that there was a mismatch in the number of 
   // calls to PrepareDC and CleanUpDC. This is not good form.
   if (!m_Stack.empty())
   {
      IndexType siz = m_Stack.size();
      ATLASSERT(false);
   }
}

void Mapping::PrepareDC(CDC* dc)
{
   // save off dc and mapping information
   StackFrame item;

   item.m_pDC = dc;

   // use himetric since we have a handy conversion built into our dc
   CSize size(m_OriginalLogicalExtentX,m_OriginalLogicalExtentY);  // value is arbitrary, but large for more accuracy
   dc->LPtoHIMETRIC(&size); // returns size in 0.01 millimeters

   // convert from 0.01 millimeters to twips. Know that 1 twip = 0.017639mm
   Float64 twips_x = ((Float64)size.cx / 100) / 0.017639;
   Float64 twips_y = ((Float64)size.cy / 100) / 0.017639;

   item.m_TextCoordMapperX.SetCoordinateMap(0.0, m_LogicalOriginX, twips_x, m_LogicalOriginX+m_OriginalLogicalExtentX);

   if ( 0 < m_LogicalExtentY )
   {
      // logical y is up
      item.m_TextCoordMapperY.SetCoordinateMap(0.0, m_LogicalOriginY, twips_y, m_LogicalOriginY+m_OriginalLogicalExtentY);
   }
   else
   {
      // logical y is down
      item.m_TextCoordMapperY.SetCoordinateMap(0.0, m_LogicalOriginY, twips_y, m_LogicalOriginY-m_OriginalLogicalExtentY);
   }
   
   m_Stack.push_back(item);
}

void Mapping::CleanUpDC(CDC* dc)
{
   StackFrame& item = m_Stack.front();

   // pop DC off of stack
   m_Stack.pop_back();
//   TRACE("Mapping::Pop DC %d \n",m_Stack.size());
}


void Mapping::CleanUpPrintDC(CDC* dc)
{
   // pop all print DCs off of stack
   // we must do this because there is no way to know how many dc's were popped
   // onto our stack during printing
//   TRACE("Mapping::Pop Print DC %d\n",m_Stack.size());
   while(!m_Stack.empty())
      m_Stack.pop_back();
}


void Mapping::SetWorldExt(Float64 wx,Float64 wy)
{
   SetWorldExt({ wx,wy });
}

void Mapping::SetWorldExt(const WBFL::Geometry::Size2d& wExt)
{
   m_WorldExtent = wExt;
   UpdateLogicalExtents();
}

const WBFL::Geometry::Size2d& Mapping::GetWorldExt() const
{
   return m_WorldExtent;
}

void Mapping::SetWorldOrg(Float64 wx,Float64 wy)
{
   SetWorldOrg({ wx,wy });
}

void Mapping::SetWorldOrg(const WBFL::Geometry::Point2d& wOrg)
{
   m_WorldOrigin = wOrg;
}

const WBFL::Geometry::Point2d& Mapping::GetWorldOrg() const
{
   return m_WorldOrigin;
}

void Mapping::SetLogicalOrg(const POINT& org)
{
   SetLogicalOrg(org.x, org.y);
}

void Mapping::SetLogicalOrg(LONG lx,LONG ly)
{
   m_LogicalOriginX = lx;
   m_LogicalOriginY = ly;

   UpdateLogicalExtents();
}

POINT Mapping::GetLogicalOrg() const
{
   return { m_LogicalOriginX, m_LogicalOriginY };
}

void Mapping::SetLogicalExt(LONG lx,LONG ly)
{
   m_OriginalLogicalExtentX = lx;
   m_OriginalLogicalExtentY = ly;

   UpdateLogicalExtents();
}

SIZE Mapping::GetLogicalExt() const
{
   return { m_OriginalLogicalExtentX, m_OriginalLogicalExtentY };
}

SIZE Mapping::GetAdjustedLogicalExt() const
{
   return { m_LogicalExtentX, m_LogicalExtentY };
}

WBFL::Geometry::Size2d Mapping::GetAdjustedWorldExt() const
{
   // convert adjusted logical extents to world
   Float64 wox, woy, wex, wey;
   LPtoWP(m_LogicalOriginX, m_LogicalOriginY, &wox, &woy);
   LPtoWP(m_LogicalOriginX + m_OriginalLogicalExtentX, m_LogicalOriginY + m_OriginalLogicalExtentY, &wex, &wey);

   return { fabs(wox - wex), fabs(woy - wey) };
}
 

void Mapping::SetMappingMode(MapMode mm)
{
   m_MappingMode = mm;
   UpdateLogicalExtents();
}

MapMode Mapping::GetMappingMode()
{
   return m_MappingMode;
}

void Mapping::SetRotation(Float64 cx,Float64 cy,Float64 angle)
{
   m_RotationX = cx;
   m_RotationY = cy;
   m_Rotation  = angle;
   m_sinR = sin(angle);
   m_cosR = cos(angle);
}

void Mapping::SetRotation(const WBFL::Geometry::Point2d& c,Float64 angle)
{
   auto [cx, cy] = c.GetLocation();
   SetRotation(cx,cy,angle);
}

std::pair<WBFL::Geometry::Point2d,Float64> Mapping::GetRotation() const
{
   return { {m_RotationX, m_RotationY}, m_Rotation };
}

//////////////////////////////////////////////////////////
// iCoordinateMap
void Mapping::MPtoWP(Float64 mx,Float64 my,Float64* wx,Float64* wy) const
{
   // clockwise rotation
   *wx = (mx - m_RotationX)*m_cosR - (my - m_RotationY)*m_sinR;
   *wy = (mx - m_RotationX)*m_sinR + (my - m_RotationY)*m_cosR;
}

WBFL::Geometry::Point2d Mapping::MPtoWP(const WBFL::Geometry::Point2d& mp) const
{
   auto [mx, my] = mp.GetLocation();
   Float64 wx, wy;
   MPtoWP(mx, my, &wx, &wy);
   return { wx,wy };
}

void Mapping::WPtoMP(Float64 wx, Float64 wy, Float64* mx, Float64* my) const
{
   // counter-clockwise rotation
   *mx = wx * m_cosR + wy * m_sinR + m_RotationX;
   *my = -wx * m_sinR + wy * m_cosR + m_RotationY;
}

void Mapping::WPtoMP(const WBFL::Geometry::Point2d& wp,Float64* mx,Float64* my) const
{
   auto [wx, wy] = wp.GetLocation();
   WPtoMP(wx,wy,mx,my);
}

void Mapping::WPtoLP(Float64 wx,Float64 wy,LONG* lx,LONG* ly) const
{
   if (m_WorldExtent.Dx() == 0)
   {
      *lx = m_LogicalOriginX;
   }
   else
   {
      Float64 x;
      x = (wx - m_WorldOrigin.X())*m_LEX_over_WEX + m_LogicalOriginX;
      *lx = round_to_nearest_whole_number(x);
   }

   if ( m_WorldExtent.Dy() == 0 )
   {
      *ly = m_LogicalOriginY;
   }
   else
   {
      Float64 y;
      y = (wy - m_WorldOrigin.Y())*m_LEY_over_WEY + m_LogicalOriginY;
      *ly = round_to_nearest_whole_number(y);
   }
}

void Mapping::WPtoLP(const WBFL::Geometry::Point2d& wp,LONG* lx,LONG* ly) const
{
   auto [x, y] = wp.GetLocation();
   WPtoLP( x, y, lx, ly );
}

void Mapping::LPtoWP(LONG lx,LONG ly,Float64* wx,Float64* wy) const
{
   if (m_LogicalExtentX == 0)
   {
      *wx = 0.0;
   }
   else
   {
      *wx = (lx - m_LogicalOriginX)*m_WEX_over_LEX + m_WorldOrigin.X();
   }

   if (m_LogicalExtentY == 0)
   {
      *wy = 0.0;
   }
   else
   {
      *wy = (ly - m_LogicalOriginY)*m_WEY_over_LEY + m_WorldOrigin.Y();
   }
}

WBFL::Geometry::Point2d Mapping::LPtoWP(LONG lx,LONG ly) const
{
   Float64 wx,wy;
   LPtoWP(lx,ly,&wx,&wy);
   return WBFL::Geometry::Point2d(wx, wy);
}

void Mapping::WPtoTP(Float64 wx,Float64 wy,LONG* tx,LONG* ty) const
{
   // two-step conversion
   LONG lx, ly;
   WPtoLP(wx, wy, &lx, &ly);

   LPtoTP(lx, ly, tx, ty);
}

void Mapping::TPtoWP(LONG tx,LONG ty,Float64* wx,Float64* wy) const
{
   // two-step conversion
   LONG lx, ly;
   TPtoLP(tx, ty, &lx, &ly);

   LPtoWP(lx, ly, wx, wy);
}

void Mapping::LPtoTP(LONG lx,LONG ly,LONG* tx,LONG* ty) const
{
   ATLASSERT(!m_Stack.empty());
   const StackFrame& item = m_Stack.front();

   *tx = round_to_nearest_whole_number( item.m_TextCoordMapperX.GetA(lx) );
   *ty = round_to_nearest_whole_number( item.m_TextCoordMapperY.GetA(ly) );
}

void Mapping::TPtoLP(LONG tx,LONG ty,LONG* lx,LONG* ly) const
{
   ATLASSERT(!m_Stack.empty());
   const StackFrame& item = m_Stack.front();

   *lx = round_to_nearest_whole_number( item.m_TextCoordMapperX.GetB(tx) );
   *ly = round_to_nearest_whole_number( item.m_TextCoordMapperY.GetB(ty) );
}

CSize Mapping::GetTextWindowExtent() const
{
   LONG lox, loy;
   LPtoTP(0, 0, &lox, &loy);

   LONG lex, ley;
   LPtoTP(m_OriginalLogicalExtentX, m_OriginalLogicalExtentY, &lex, &ley);

   return CSize( abs(lex-lox), abs(ley-loy) );
}
 
CSize Mapping::GetTextExtent(const CDisplayView* pView, const LOGFONT& font, LPCTSTR lpszText) const
{
   if (m_Stack.empty())
   {
      ATLASSERT(false);
      return CSize(1440, 144);
   }

   // get most recent dc from stack
   CDC* pdc = m_Stack.front().m_pDC;
   ASSERT_VALID(pdc);
   ATLASSERT(pdc->m_hAttribDC);

   LOGFONT lf = font;
   pView->ScaleFont(lf);

   CFont cfont;
   cfont.CreatePointFontIndirect(&lf,pdc);

   CFont* tfont = pdc->SelectObject(&cfont);
   CSize size = pdc->GetTextExtent(lpszText);
   pdc->SelectObject(tfont);

   return size;
}

void Mapping::UpdateLogicalExtents()
{
   if (m_WorldExtent.Dx() == 0.0 || m_OriginalLogicalExtentX ==0 ||
       m_WorldExtent.Dy() == 0.0 || m_OriginalLogicalExtentY == 0)
   {
      m_LogicalExtentX = m_OriginalLogicalExtentX;
      m_LogicalExtentY = m_OriginalLogicalExtentY;
      UpdateMappingScale();
      return;
   }

   if ( m_MappingMode == MapMode::Anisotropic )
   {
      // Just a straight mapping
      m_LogicalExtentX = m_OriginalLogicalExtentX;
      m_LogicalExtentY = m_OriginalLogicalExtentY;

   }
   else if ( m_MappingMode == MapMode::Isotropic )
   {
      // prevent divide by zero issues
      if (!IsZero(m_WorldExtent.Dx()) && !IsZero(m_WorldExtent.Dx()) && m_OriginalLogicalExtentY != 0 )
      {
         // compute aspect ratio of logical and world extents
         Float64 logical_aspect_ratio = fabs((Float64)m_OriginalLogicalExtentX/(Float64)m_OriginalLogicalExtentY);
         Float64 world_aspect_ratio   = fabs(m_WorldExtent.Dx()/m_WorldExtent.Dy());

         // adjust aspect ratio of logical space to match world
         if (logical_aspect_ratio < world_aspect_ratio)
         {
            // world is too wide - must adjust y only
            m_LogicalExtentX = m_OriginalLogicalExtentX;

            Float64 yneeded =  (Float64)abs(m_OriginalLogicalExtentX)/world_aspect_ratio;

            // retain sign always
            m_LogicalExtentY = BinarySign(m_OriginalLogicalExtentY)*round_to_nearest_whole_number(yneeded);
         }
         else 
         {
            // world is too narrow - must adjust x only
            m_LogicalExtentY = m_OriginalLogicalExtentY;

            Float64 xneeded = (Float64)abs(m_OriginalLogicalExtentY) * world_aspect_ratio;

            m_LogicalExtentX = BinarySign(m_OriginalLogicalExtentX)*round_to_nearest_whole_number(xneeded);
         }
      }
   }

   UpdateMappingScale();
} 

void Mapping::UpdateMappingScale()
{
   if ( m_LogicalExtentX == 0 )
      m_WEX_over_LEX = 1;
   else
      m_WEX_over_LEX = m_WorldExtent.Dx()/(Float64)m_LogicalExtentX;

   if ( m_LogicalExtentY == 0 )
      m_WEY_over_LEY = 1;
   else
      m_WEY_over_LEY = m_WorldExtent.Dy()/(Float64)m_LogicalExtentY;


   if ( IsZero(m_WorldExtent.Dx()) )
      m_LEX_over_WEX = 1;
   else
      m_LEX_over_WEX = (Float64)m_LogicalExtentX/m_WorldExtent.Dx();

   if ( IsZero(m_WorldExtent.Dy()) )
      m_LEY_over_WEY = 1;
   else
      m_LEY_over_WEY = (Float64)m_LogicalExtentY/m_WorldExtent.Dy();
}