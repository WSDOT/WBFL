///////////////////////////////////////////////////////////////////////////////
// generic support draw routines to share between Supports and TemporarySupports

#include "stdafx.h"
#include "DrawSupports.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void DrawZeroLengthSupport(CDC* pDC, BoundaryConditionType ct, long cx, long cy, long wid, long hgt)
{
   if ( ct == bcFixed )
   {
      DrawFixedSupport( pDC, cx, cy, wid, hgt);
   }
   else if ( ct == bcPinned )
   {
      DrawPinnedSupport( pDC, cx, cy, wid, hgt);
   }
   else if ( ct == bcRoller )
   {
      DrawRollerSupport( pDC, cx, cy, wid, hgt);
   }
   else
      ATLASSERT(0);
}

void DrawGround(CDC* pDC, long cx, long cy, long wid, long hgt)
{
   // base
   pDC->MoveTo(cx-wid,cy);
   pDC->LineTo(cx+hgt,cy);

   // tics
   long num_tics=6;
   long tic_size = (2*hgt)/(num_tics+2);
   long yt = cy;
   long yb = yt + tic_size;
   long xl = cx-wid+tic_size;
   for (long i=0; i<=num_tics+1; i++)
   {
      pDC->MoveTo(xl, yt);
      pDC->LineTo(xl-tic_size, yb);

      xl+=tic_size;
   }
}

void DrawRollerSupport(CDC* pDC, long cx, long cy, long wid, long hgt)
{
      // roller support
      DrawGround(pDC, cx, cy+hgt, wid, hgt);

      // triangle
      POINT points[4];
      points[0].x = cx;
      points[0].y = cy;
      points[1].x = cx-wid/2;
      points[1].y = cy+2*hgt/3;
      points[2].x = cx+wid/2;
      points[2].y = points[1].y;
      points[3].x = cx;
      points[3].y = cy;
      pDC->Polygon(points,4);

      // tip circle
      long esx=wid/5;
      long esy=hgt/5;
      pDC->Ellipse(cx-esx, cy-esy, cx+esx, cy+esy);

      // rollers
      esx=wid/5;
      esy=hgt/5;
      long rt = cy+hgt-esy;
      long rx = cx - wid/2;
      pDC->Ellipse(rx, rt, rx+esx, cy+hgt);
      rx = cx-esx/2;
      pDC->Ellipse(rx, rt, rx+esx, cy+hgt);
      rx = cx + wid/2 - esx;
      pDC->Ellipse(rx, rt, rx+esx, cy+hgt);
}

void DrawFixedSupport(CDC* pDC, long cx, long cy, long wid, long hgt)
{
      // fixed support
      DrawGround(pDC, cx, cy+hgt, wid, hgt);

      pDC->Rectangle(cx-wid/3, cy, cx+wid/3, cy+hgt);
}

void DrawPinnedSupport(CDC* pDC, long cx, long cy, long wid, long hgt)
{
      // pinned support
      DrawGround(pDC, cx, cy+hgt, wid, hgt);

      // triangle
      POINT points[4];
      points[0].x = cx;
      points[0].y = cy;
      points[1].x = cx-wid/2;
      points[1].y = cy+hgt;
      points[2].x = cx+wid/2;
      points[2].y = cy+hgt;
      points[3].x = cx;
      points[3].y = cy;
      pDC->Polygon(points,4);

      // tip circle
      long esx=wid/5;
      long esy=hgt/5;
      pDC->Ellipse(cx-esx, cy-esy, cx+esx, cy+esy);
}
