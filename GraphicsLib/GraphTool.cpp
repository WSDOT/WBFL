///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
// Copyright © 1999-2013  Washington State Department of Transportation
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

#include <GraphicsLib\GraphicsLibLib.h>
#include <GraphicsLib\GraphTool.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   grGraphTool
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
grGraphTool::grGraphTool()
{
}

grGraphTool::~grGraphTool()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bool grGraphTool::TextOutRotated(HDC hDC, LONG x, LONG y, LONG rotation, 
                                 LPCTSTR lpszText, LONG textlen, 
                                 LONG nPointSize, LPCTSTR lpszFacename)
{
   if (textlen<=0) return true;


   HFONT new_font = CreateRotatedFont( hDC, rotation,nPointSize, lpszFacename);
   CHECK(new_font);
   if(new_font==NULL) return false;

   int old_bk = ::SetBkMode(hDC,TRANSPARENT);
   HGDIOBJ old_font = ::SelectObject(hDC, new_font);

   if (textlen>1)
   {
      // have to hack in centered code since Windows version doesn't work
      UINT old_align = GetTextAlign(hDC);
      if ( (old_align&DT_CENTER) !=0 )
      {
         LONG left  = textlen/2;
         LONG right = textlen-left;
         SetTextAlign(hDC, DT_RIGHT | DT_BOTTOM );
         ::TextOut(hDC, x, y, lpszText, left);
         lpszText+=left;
         ::SetTextAlign(hDC, DT_LEFT|DT_BOTTOM );
         ::TextOut(hDC, x, y,  lpszText, right);
         ::SetTextAlign(hDC, old_align);
      }
      else
         ::TextOut(hDC, x, y, lpszText, textlen);

   }
   else
   {
      ::TextOut(hDC, x, y, lpszText, textlen);
   }

   ::SelectObject(hDC, old_font);
   ::DeleteObject(new_font);
   ::SetBkMode(hDC,old_bk);

   return true;
}

HFONT grGraphTool::CreateRotatedFont(HDC hDC, LONG rotation, LONG nPointSize, LPCTSTR lpszFaceName)
{
   CHECK(hDC!=NULL);

   if (rotation>3600 || rotation<0) 
      rotation %= 3600; 

	LOGFONT logFont;
	memset(&logFont, 0, sizeof(LOGFONT));
	logFont.lfCharSet = DEFAULT_CHARSET;
	logFont.lfHeight = nPointSize;
   logFont.lfEscapement = rotation;
   logFont.lfOrientation= rotation;
	lstrcpyn(logFont.lfFaceName, lpszFaceName, sizeof(logFont.lfFaceName)/sizeof(logFont.lfFaceName[0]));

	// convert nPointSize to logical units based on DC
	POINT pt;
	pt.y = ::GetDeviceCaps(hDC, LOGPIXELSY) * logFont.lfHeight;
	pt.y /= 72;    // 72 points/inch
	::DPtoLP(hDC, &pt, 1);
	POINT ptOrg = { 0, 0 };
	::DPtoLP(hDC, &ptOrg, 1);
	logFont.lfHeight = -abs(pt.y - ptOrg.y);

	return CreateFontIndirect(&logFont);
}


void grGraphTool::CalculateNiceRange(const Float64 originalMin, const Float64 originalMax,
                        CollectionIndexType& numberOfSegments,
                        Float64& niceMin, Float64& niceMax,
                        Float64& niceIncrement)
{
   // this is a butt-ugly routine that was converted from fortran - excuse
   // the mess, but it works

   Float64 exponent, factor, scale_fac, test_scale, adjusted_min, adjusted_max; 
   LONG  nmin, nmax, need;
   bool  is_defseg;

   const Float64  tol = 1.0e-09;
   const CollectionIndexType nscale = 9;
   const Float64 prturb = 1.1;
   const Float64 supply[nscale] = {25.0, 20.0, 15.0, 10.0, 5.0, 2.5, 2.0, 1.0, 0.5 };

   niceMin = originalMin;
   niceMax = originalMax;

//  may need to perturb values to make reasonable graph

   if (IsEqual(niceMin,niceMax))
   {
       if (IsZero(niceMin))
       {
           niceMax = 1.0;
       }
       else
       {
           niceMin = niceMin/prturb;
           niceMax = niceMax*prturb;
       }
   }
   else if (niceMin > niceMax)
   {
       Float64 temp = niceMin;
       niceMin = niceMax;
       niceMax = temp;
   }

   if (niceMax-niceMin <= tol)
   {
       niceMin -= tol;
       niceMax += tol;
   }

//  set nseg to default if .lt. 1

   if (numberOfSegments < 1)
   {
      numberOfSegments = 7;
      is_defseg = true;
   }
   else
   {
      is_defseg = false;
   }

//     get down to business

   exponent = floor(log10((niceMax - niceMin)/numberOfSegments));
   factor = pow(10.0, exponent);

//     test each scale and keep the largest one that works

   for (CollectionIndexType i=0; i<nscale; i++)
   {
       test_scale = factor*supply[i];
       nmin = (LONG)floor(niceMin/test_scale);
       nmax = (LONG)ceil(niceMax/test_scale);
       need = nmax - nmin;

       if (need <= (int)numberOfSegments)
       {
           scale_fac = test_scale;
           adjusted_min = nmin*scale_fac;
           adjusted_max = nmax*scale_fac;
       }
       else
          continue;
   }

   // try to 'shrink' the outer bounds if the original max or min only
   // slightly intrudes into the nice range.

   const Float64 range_tol = (niceMax-niceMin)/300.; // could put this out to interface
                                                    // if very precise graphing were needed.

   if ( adjusted_max-scale_fac+range_tol > niceMax && need>1 )  // shrink upper range if original is
   {                                                            // only slightly above next band.
      adjusted_max -= scale_fac;
      need--;
   }

   if ( adjusted_min+scale_fac-range_tol < niceMin && need>1 )  // shrink lower range
   {
      adjusted_min += scale_fac;
      need--;
   }

// return adjusted max and min

   numberOfSegments = need;
   niceIncrement    = scale_fac;

   niceMin = adjusted_min;
   niceMax = adjusted_max;
}


void grGraphTool::DrawRect(HDC hDC, const grlibPointMapper& mapper, const gpRect2d& rect, 
                           COLORREF borderColor, 
                           bool doFill, COLORREF fillColor)
{
   HBRUSH brush     = ::CreateSolidBrush( fillColor );
   HBRUSH old_brush = (HBRUSH)::SelectObject( hDC, brush );

   HPEN pen     = ::CreatePen( PS_SOLID, 1, borderColor);
   HPEN old_pen = (HPEN)::SelectObject( hDC, pen );

   const int num_points=5;
   POINT device_points[num_points]; // closed rect
   LONG  dx,dy;

   gpPoint2d top_left = rect.TopLeft();
   gpPoint2d bottom_right = rect.BottomRight();

   mapper.WPtoDP(top_left.X(),top_left.Y(),&dx,&dy);
   device_points[0].x = dx;
   device_points[0].y = dy;
   mapper.WPtoDP(top_left.X(),bottom_right.Y(),&dx,&dy);
   device_points[1].x = dx;
   device_points[1].y = dy;
   mapper.WPtoDP(bottom_right.X(),bottom_right.Y(),&dx,&dy);
   device_points[2].x = dx;
   device_points[2].y = dy;
   mapper.WPtoDP(bottom_right.X(),top_left.Y(),&dx,&dy);
   device_points[3].x = dx;
   device_points[3].y = dy;

   device_points[4] = device_points[0]; // <<<< Force closure

   if (doFill)
   {
      // ALTERNATE is the Windows default, I will set it here
      // anyway just incase someone decides to change the default.
      ::SetPolyFillMode(hDC,ALTERNATE);
      ::Polygon(hDC,device_points,num_points);
   }
   else
   {
      ::Polyline(hDC,device_points,num_points);
   }

   // Cleanup
   ::SelectObject( hDC, old_brush );
   ::DeleteObject( brush );
   ::SelectObject( hDC, old_pen );
   ::DeleteObject( pen );
}



//======================== ACCESS     =======================================
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
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

