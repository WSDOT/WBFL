///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

// MappingImpl.cpp: implementation of the CMappingImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include <WBFLDManip.h>
#include <DManip\DManip_clsid.cpp>
#include <DManip\DManipTypes.h>
#include <DManip\Mapping.h>
#include <DManip\CoordinateMap.h>
#include "MappingImpl.h"

#include <MathEx.h>
#include <algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMappingImpl::CMappingImpl()
{
   // crazy dummy values to help detect errors
   m_WEX_over_LEX = -9999; // m_WorldExtentX/m_LogicalExtentX
   m_WEY_over_LEY = -9999; // m_WorldExtentY/m_LogicalExtentY
   m_LEX_over_WEX = -9999; // m_LogicalExtentX/m_WorldExtentX
   m_LEY_over_WEY = -9999; // m_LogicalExtentY/m_WorldExtentY
}

CMappingImpl::~CMappingImpl()
{
   // if this assert fires it means that there was a mismatch in the number of 
   // calls to PrepareDC and CleanUpDC. This is not good form.
   if (!m_Stack.empty())
   {
      CollectionIndexType siz = m_Stack.size();
      ATLASSERT(0);
   }
}

HRESULT CMappingImpl::FinalConstruct()
{
   m_WorldExtentX = 1.;
   m_WorldExtentY = 1.;
   m_WorldOriginX = 0.;
   m_WorldOriginY = 0.;

   m_LogicalExtentX = 1;
   m_LogicalExtentY = 1;
   m_LogicalOriginX = 1;
   m_LogicalOriginY = 1;
   m_OriginalLogicalExtentX = 1;
   m_OriginalLogicalExtentY = 1;

   SetRotation(0,0,0);

   UpdateMappingScale();

   m_MappingMode = DManip::Anisotropic;

   return S_OK;
}


STDMETHODIMP_(void) CMappingImpl::PrepareDC(CDC* dc)
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

STDMETHODIMP_(void) CMappingImpl::CleanUpDC(CDC* dc)
{
   StackFrame& item = m_Stack.front();

   // pop DC off of stack
   m_Stack.pop_back();
//   TRACE("CMappingImpl::Pop DC %d \n",m_Stack.size());
}


STDMETHODIMP_(void) CMappingImpl::CleanUpPrintDC(CDC* dc)
{
   // pop all print DCs off of stack
   // we must do this because there is no way to know how many dc's were popped
   // onto our stack during printing
//   TRACE("CMappingImpl::Pop Print DC %d\n",m_Stack.size());
   while(!m_Stack.empty())
      m_Stack.pop_back();
}


STDMETHODIMP_(void) CMappingImpl::SetWorldExt(Float64 wx,Float64 wy)
{
   m_WorldExtentX = wx;
   m_WorldExtentY = wy;

   UpdateLogicalExtents();
}

STDMETHODIMP_(void) CMappingImpl::SetWorldExt(ISize2d* wExt)
{
   Float64 dx,dy;
   wExt->get_Dx(&dx);
   wExt->get_Dy(&dy);
   SetWorldExt( dx, dy );
}

STDMETHODIMP_(void) CMappingImpl::GetWorldExt(Float64* wx,Float64* wy)
{
   *wx = m_WorldExtentX;
   *wy = m_WorldExtentY;
}

STDMETHODIMP_(void) CMappingImpl::GetWorldExt(ISize2d* *wExt)
{
   CComPtr<ISize2d> ext;
   ext.CoCreateInstance(CLSID_Size2d);
   ext->put_Dx(m_WorldExtentX);
   ext->put_Dy(m_WorldExtentY);

   (*wExt) = ext;
   (*wExt)->AddRef();
}

STDMETHODIMP_(void) CMappingImpl::SetWorldOrg(Float64 wx,Float64 wy)
{
   m_WorldOriginX = wx;
   m_WorldOriginY = wy;
}

STDMETHODIMP_(void) CMappingImpl::SetWorldOrg(IPoint2d* wOrg)
{
   Float64 x,y;
   wOrg->get_X(&x);
   wOrg->get_Y(&y);
   SetWorldOrg( x, y );
}

STDMETHODIMP_(void) CMappingImpl::GetWorldOrg(Float64* wx,Float64* wy)
{
   *wx = m_WorldOriginX;
   *wy = m_WorldOriginY;
}

STDMETHODIMP_(void) CMappingImpl::GetWorldOrg(IPoint2d* *wOrg)
{
   CComPtr<IPoint2d> org;
   org.CoCreateInstance(CLSID_Point2d);
   org->put_X(m_WorldOriginX);
   org->put_Y(m_WorldOriginY);

   (*wOrg) = org;
   (*wOrg)->AddRef();
}

STDMETHODIMP_(void) CMappingImpl::SetLogicalOrg(LONG lx,LONG ly)
{
   m_LogicalOriginX = lx;
   m_LogicalOriginY = ly;

   UpdateLogicalExtents();
}

STDMETHODIMP_(void) CMappingImpl::GetLogicalOrg(LONG* lx,LONG* ly)
{
   *lx = m_LogicalOriginX;
   *ly = m_LogicalOriginY;
}

STDMETHODIMP_(void) CMappingImpl::SetLogicalExt(LONG lx,LONG ly)
{
   m_OriginalLogicalExtentX = lx;
   m_OriginalLogicalExtentY = ly;

   UpdateLogicalExtents();
}

STDMETHODIMP_(void) CMappingImpl::GetLogicalExt(LONG* lx,LONG* ly)
{
   *lx = m_OriginalLogicalExtentX;
   *ly = m_OriginalLogicalExtentY;
}

STDMETHODIMP_(void) CMappingImpl::GetAdjustedLogicalExt(LONG* lx,LONG* ly)
{
   *lx = m_LogicalExtentX;
   *ly = m_LogicalExtentY;
}

STDMETHODIMP_(void) CMappingImpl::GetAdjustedWorldExt(Float64* dx,Float64* dy)
{
   // convert adjusted logical extents to world
   Float64 wox, woy, wex, wey;
   LPtoWP(m_LogicalOriginX, m_LogicalOriginY, &wox, &woy);
   LPtoWP(m_LogicalOriginX + m_OriginalLogicalExtentX, m_LogicalOriginY + m_OriginalLogicalExtentY, &wex, &wey);

   *dx = fabs(wox-wex);
   *dy = fabs(woy-wey);
}
 

STDMETHODIMP_(void) CMappingImpl::SetMappingMode(DManip::MapMode mm)
{
   m_MappingMode = mm;
   UpdateLogicalExtents();
}

STDMETHODIMP_(DManip::MapMode) CMappingImpl::GetMappingMode()
{
   return m_MappingMode;
}

STDMETHODIMP_(void) CMappingImpl::SetRotation(Float64 cx,Float64 cy,Float64 angle)
{
   m_RotationX = cx;
   m_RotationY = cy;
   m_Rotation  = angle;
   m_sinR = sin(angle);
   m_cosR = cos(angle);
}

STDMETHODIMP_(void) CMappingImpl::SetRotation(IPoint2d* c,Float64 angle)
{
   Float64 cx,cy;
   c->get_X(&cx);
   c->get_Y(&cy);
   SetRotation(cx,cy,angle);
}

STDMETHODIMP_(void) CMappingImpl::GetRotation(Float64* cx,Float64* cy,Float64* angle)
{
   *cx = m_RotationX;
   *cy = m_RotationY;
   *angle = m_Rotation;
}

//////////////////////////////////////////////////////////
// iCoordinateMap
STDMETHODIMP_(void) CMappingImpl::MPtoWP(Float64 mx,Float64 my,Float64* wx,Float64* wy)
{
   // clockwise rotation
   *wx = (mx - m_RotationX)*m_cosR - (my - m_RotationY)*m_sinR;
   *wy = (mx - m_RotationX)*m_sinR + (my - m_RotationY)*m_cosR;
}

STDMETHODIMP_(void) CMappingImpl::MPtoWP(IPoint2d* mp,Float64* wx,Float64* wy)
{
   Float64 mx,my;
   mp->get_X(&mx);
   mp->get_Y(&my);
   MPtoWP(mx,my,wx,wy);
}

STDMETHODIMP_(void) CMappingImpl::WPtoMP(Float64 wx,Float64 wy,Float64* mx,Float64* my)
{
   // counter-clockwise rotation
   *mx =  wx*m_cosR + wy*m_sinR + m_RotationX;
   *my = -wx*m_sinR + wy*m_cosR + m_RotationY;
}

STDMETHODIMP_(void) CMappingImpl::WPtoMP(IPoint2d* wp,Float64* mx,Float64* my)
{
   Float64 wx,wy;
   wp->get_X(&wx);
   wp->get_Y(&wy);
   WPtoMP(wx,wy,mx,my);
}

STDMETHODIMP_(void) CMappingImpl::WPtoLP(Float64 wx,Float64 wy,LONG* lx,LONG* ly)
{
   if (m_WorldExtentX == 0)
   {
      *lx = m_LogicalOriginX;
   }
   else
   {
      Float64 x;
      x = (wx - m_WorldOriginX)*m_LEX_over_WEX + m_LogicalOriginX;
      *lx = round_to_nearest_whole_number(x);
   }

   if ( m_WorldExtentY == 0 )
   {
      *ly = m_LogicalOriginY;
   }
   else
   {
      Float64 y;
      y = (wy - m_WorldOriginY)*m_LEY_over_WEY + m_LogicalOriginY;
      *ly = round_to_nearest_whole_number(y);
   }
}

STDMETHODIMP_(void) CMappingImpl::WPtoLP(IPoint2d* wp,LONG* lx,LONG* ly)
{
   Float64 x,y;
   wp->get_X(&x);
   wp->get_Y(&y);

   WPtoLP( x, y, lx, ly );
}

STDMETHODIMP_(void) CMappingImpl::LPtoWP(LONG lx,LONG ly,Float64* wx,Float64* wy)
{
   if (m_LogicalExtentX == 0)
   {
      *wx = 0.0;
   }
   else
   {
      *wx = (lx - m_LogicalOriginX)*m_WEX_over_LEX + m_WorldOriginX;
   }

   if (m_LogicalExtentY == 0)
   {
      *wy = 0.0;
   }
   else
   {
      *wy = (ly - m_LogicalOriginY)*m_WEY_over_LEY + m_WorldOriginY;
   }
}

STDMETHODIMP_(void) CMappingImpl::LPtoWP(LONG lx,LONG ly,IPoint2d** wp)
{
   Float64 wx,wy;
   LPtoWP(lx,ly,&wx,&wy);

   CComPtr<IPoint2d> p;
   p.CoCreateInstance(CLSID_Point2d);

   p->Move(wx,wy);

   (*wp) = p;
   (*wp)->AddRef();
}

STDMETHODIMP_(void) CMappingImpl::WPtoTP(Float64 wx,Float64 wy,LONG* tx,LONG* ty)
{
   // two-step conversion
   LONG lx, ly;
   WPtoLP(wx, wy, &lx, &ly);

   LPtoTP(lx, ly, tx, ty);
}

STDMETHODIMP_(void) CMappingImpl::TPtoWP(LONG tx,LONG ty,Float64* wx,Float64* wy)
{
   // two-step conversion
   LONG lx, ly;
   TPtoLP(tx, ty, &lx, &ly);

   LPtoWP(lx, ly, wx, wy);
}

STDMETHODIMP_(void) CMappingImpl::LPtoTP(LONG lx,LONG ly,LONG* tx,LONG* ty)
{
   ATLASSERT(!m_Stack.empty());
   StackFrame& item = m_Stack.front();

   *tx = round_to_nearest_whole_number( item.m_TextCoordMapperX.GetA(lx) );
   *ty = round_to_nearest_whole_number( item.m_TextCoordMapperY.GetA(ly) );
}

STDMETHODIMP_(void) CMappingImpl::TPtoLP(LONG tx,LONG ty,LONG* lx,LONG* ly)
{
   ATLASSERT(!m_Stack.empty());
   StackFrame& item = m_Stack.front();

   *lx = round_to_nearest_whole_number( item.m_TextCoordMapperX.GetB(tx) );
   *ly = round_to_nearest_whole_number( item.m_TextCoordMapperY.GetB(ty) );
}

STDMETHODIMP_(CSize) CMappingImpl::GetTextWindowExtent()
{
   LONG lox, loy;
   LPtoTP(0, 0, &lox, &loy);

   LONG lex, ley;
   LPtoTP(m_OriginalLogicalExtentX, m_OriginalLogicalExtentY, &lex, &ley);

   return CSize( abs(lex-lox), abs(ley-loy) );
}
 
STDMETHODIMP_(CSize) CMappingImpl::GetTextExtent(const LOGFONT& font, LPCTSTR lpszText)
{
   if (m_Stack.empty())
   {
      ATLASSERT(0);
      return CSize(1440, 144);
   }

   // get most recent dc from stack
   CDC* pdc = m_Stack.front().m_pDC;
   ASSERT_VALID(pdc);
   ATLASSERT(pdc->m_hAttribDC);

   CFont cfont;
   cfont.CreatePointFontIndirect(&font,pdc);

   CFont* tfont = pdc->SelectObject(&cfont);
   CSize size = pdc->GetTextExtent(lpszText);
   pdc->SelectObject(tfont);

   return size;
}

void CMappingImpl::UpdateLogicalExtents()
{
   if (m_WorldExtentX==0.0 || m_OriginalLogicalExtentX==0 ||
       m_WorldExtentY==0.0 || m_OriginalLogicalExtentY==0)
   {
      m_LogicalExtentX = m_OriginalLogicalExtentX;
      m_LogicalExtentY = m_OriginalLogicalExtentY;
      UpdateMappingScale();
      return;
   }

   if ( m_MappingMode == DManip::Anisotropic )
   {
      // Just a straight mapping
      m_LogicalExtentX = m_OriginalLogicalExtentX;
      m_LogicalExtentY = m_OriginalLogicalExtentY;

   }
   else if ( m_MappingMode == DManip::Isotropic )
   {
      // prevent divide by zero issues
      if (!IsZero(m_WorldExtentX) && !IsZero(m_WorldExtentX) && m_OriginalLogicalExtentY != 0 )
      {
         // compute aspect ratio of logical and world extents
         Float64 logical_aspect_ratio = fabs((Float64)m_OriginalLogicalExtentX/(Float64)m_OriginalLogicalExtentY);
         Float64 world_aspect_ratio   = fabs(m_WorldExtentX/m_WorldExtentY);

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

void CMappingImpl::UpdateMappingScale()
{
   if ( m_LogicalExtentX == 0 )
      m_WEX_over_LEX = 1;
   else
      m_WEX_over_LEX = m_WorldExtentX/(Float64)m_LogicalExtentX;

   if ( m_LogicalExtentY == 0 )
      m_WEY_over_LEY = 1;
   else
      m_WEY_over_LEY = m_WorldExtentY/(Float64)m_LogicalExtentY;


   if ( IsZero(m_WorldExtentX) )
      m_LEX_over_WEX = 1;
   else
      m_LEX_over_WEX = (Float64)m_LogicalExtentX/m_WorldExtentX;

   if ( IsZero(m_WorldExtentY) )
      m_LEY_over_WEY = 1;
   else
      m_LEY_over_WEY = (Float64)m_LogicalExtentY/m_WorldExtentY;
}