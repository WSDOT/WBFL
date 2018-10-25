///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
// Copyright © 1999-2017  Washington State Department of Transportation
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
#include <GraphicsLib\Dimension.h>
#include <GraphicsLib\PointMapper.h>
#include <GraphicsLib\GraphTool.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   grDimension
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

// some metrics for laying out our dimensions
// all metrics are based on fractions of the text height of the label
static const Float64 ARROW_LENGTH = 1.0;
static const Float64 ARROW_WIDTH  = 0.35;
static const Float64 HOOK_OFFSET  = 0.25;
static const Float64 DIM_OFFSET   = 0.5;    // from top down to horiz line
static const Float64 WITNESS_LINE_LENGTH = 1.5; // length of vertical lines
static const Float64 DIM_ADJACENT_SPACING = 1.5; // spacing by space factors
static const Float64 LEADER_LINE_LENGTH = 2.0;   // length of leaders if text is outside

// free function to draw an arrow - may want to put in a library some day
void DrawArrow(HDC hDC, const grlibPointMapper& mapper, 
               const gpPoint2d& endpt, Float64 dir);

Float64 CalcVerticalDimHeight(Float64 spaceFactor, Float64 referenceHgt);
//======================== LIFECYCLE  =======================================

grDimension::grDimension():
m_VPos(Above),
m_Style(Horizontal),
m_DoDrawArrows(true),
m_SpaceFactor(0.0),
m_HPos(Center),
m_AdditionalOffset(0)
{
   m_Label.SetPointSize(8);
}

grDimension::grDimension(const gpPoint2d& pointA, const gpPoint2d& pointB, const std::_tstring& label):
m_PointA(pointA),
m_PointB(pointB),
m_VPos(Above),
m_Style(Horizontal),
m_DoDrawArrows(true),
m_SpaceFactor(0.0),
m_HPos(Center),
m_AdditionalOffset(0)
{
   m_Label.SetLabel(label);
   m_Label.SetPointSize(8);
}

grDimension::grDimension(const grDimension& rOther)
{
   MakeCopy(rOther);
}

grDimension::~grDimension()
{
}

//======================== OPERATORS  =======================================
grDimension& grDimension::operator= (const grDimension& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

void grDimension::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   // only support horizontal dimensions for now
   PRECONDITION(m_Style==Horizontal||m_Style==Vertical);

   // update geometry
   if(!UpdateGeometry( hDC, mapper))
      return;

   POINT p;
   HPEN hDimPen = (HPEN)::CreatePen(PS_SOLID, 1, RGB(   0,   0,   0) );
   HPEN hOldPen = (HPEN)::SelectObject(hDC,hDimPen);
   HBRUSH hDimBrush = (HBRUSH)::GetStockObject(BLACK_BRUSH);
   HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, hDimBrush);
   int old_bk = ::SetBkMode(hDC,TRANSPARENT);

   // draw vertical witness lines
   long dvx, dvy;

   // left
   mapper.WPtoDP(m_LeftWitness[0].X(), m_LeftWitness[0].Y(), &dvx, &dvy);
   ::MoveToEx(hDC, dvx, dvy, &p);
   mapper.WPtoDP(m_LeftWitness[1].X(), m_LeftWitness[1].Y(), &dvx, &dvy);
   ::LineTo(hDC, dvx, dvy);

   // right
   mapper.WPtoDP(m_RightWitness[0].X(), m_RightWitness[0].Y(), &dvx, &dvy);
   ::MoveToEx(hDC, dvx, dvy, &p);
   mapper.WPtoDP(m_RightWitness[1].X(), m_RightWitness[1].Y(), &dvx, &dvy);
   ::LineTo(hDC, dvx, dvy);

   // horizontal leader lines
   // left
   mapper.WPtoDP(m_LeftLeader[0].X(), m_LeftLeader[0].Y(), &dvx, &dvy);
   ::MoveToEx(hDC, dvx, dvy, &p);
   mapper.WPtoDP(m_LeftLeader[1].X(), m_LeftLeader[1].Y(), &dvx, &dvy);
   ::LineTo(hDC, dvx, dvy);

   // right
   mapper.WPtoDP(m_RightLeader[0].X(), m_RightLeader[0].Y(), &dvx, &dvy);
   ::MoveToEx(hDC, dvx, dvy, &p);
   mapper.WPtoDP(m_RightLeader[1].X(), m_RightLeader[1].Y(), &dvx, &dvy);
   ::LineTo(hDC, dvx, dvy);

   // arrows
   if (m_DoDrawArrows)
   {
      // left arrow
      DrawArrow(hDC, mapper, m_LeftArrowLoc, m_LeftArrowDir);

      // right arrow
      DrawArrow(hDC, mapper, m_RightArrowLoc, m_RightArrowDir);
   }

   // label
   m_Label.Draw(hDC, mapper);

// debugging for bounding rect problems
//   gpRect2d wbox = GetBoundingBox(hDC, mapper);
//   grGraphTool::DrawRect(hDC,mapper,wbox,RGB(255,0,255));

   // Cleanup
   ::SelectObject( hDC, hOldPen );
   ::SelectObject( hDC, hOldBrush);
   ::DeleteObject( hDimPen );
   ::DeleteObject( hDimBrush);
   ::SetBkMode(hDC,old_bk);
}

//======================== ACCESS     =======================================

   // GROUP: ACCESS

void grDimension::SetStyle(DimensionStyle style)
{
   CHECK(style==Horizontal||style==Vertical); 
   m_Style=style;
}


void grDimension::SetVerticalDimensionPos(grDimension::VerticalDimensionPos pos)
{
   m_VPos = pos;
}

grDimension::VerticalDimensionPos grDimension::GetVerticalDimensionPos() const
{
   return m_VPos;
}

void grDimension::SetHorizontalDimensionPos(HorizontalDimensionPos pos)
{
   m_HPos = pos;
}

grDimension::HorizontalDimensionPos grDimension::GetHorizontalDimensionPos() const
{
   return m_HPos;
}

void grDimension::SetHookPoints(const gpPoint2d& pointA, const gpPoint2d& pointB)
{
   m_PointA = pointA;
   m_PointB = pointB;
}

void grDimension::GetHookPoints(gpPoint2d* pointA, gpPoint2d* pointB) const
{
   *pointA = m_PointA;
   *pointB = m_PointB;
}

void grDimension::SetLabel(const std::_tstring& label)
{
   m_Label.SetLabel(label);
}

std::_tstring grDimension::GetLabel() const
{
   return m_Label.GetLabel();
}

void grDimension::SetPointSize(Uint32 pt)
{
   m_Label.SetPointSize(pt);
}

Uint32 grDimension::GetPointSize() const
{
   return m_Label.GetPointSize();
}

void grDimension::SetSpaceFactor(Float64 factor)
{
   CHECK(factor>=0.0);
   m_SpaceFactor = factor;
}

Float64 grDimension::GetSpaceFactor() const
{
   return m_SpaceFactor;
}


//======================== INQUIRY    =======================================

gpRect2d grDimension::GetBoundingBox(HDC hDC, const grlibPointMapper& mapper) const
{
   // update geometry
   if(!UpdateGeometry( hDC, mapper))
      return gpRect2d();

   // bound text rect and all control points
   gpRect2d rect = m_Label.GetBoundingBox(hDC, mapper);

   rect.BoundPoint(m_PointA);
   rect.BoundPoint(m_PointB);
   rect.BoundPoint(m_LeftWitness[0]);
   rect.BoundPoint(m_LeftWitness[1]);
   rect.BoundPoint(m_RightWitness[0]);
   rect.BoundPoint(m_RightWitness[1]);
   rect.BoundPoint(m_LeftLeader[0]);
   rect.BoundPoint(m_LeftLeader[1]);
   rect.BoundPoint(m_RightLeader[0]);
   rect.BoundPoint(m_RightLeader[1]);
   rect.BoundPoint(m_LeftArrowLoc);
   rect.BoundPoint(m_RightArrowLoc);

   return rect;
}

LONG grDimension::GetApproxVerticalHeight(HDC hDC) const
{
   LONG ref_hgt = m_Label.GetLineHeight(hDC);
   LONG apr_hgt = (LONG)CalcVerticalDimHeight(m_SpaceFactor, ref_hgt);
   LONG txt_hgt = ref_hgt * (LONG)m_Label.GetNumLines();
   return max(apr_hgt,txt_hgt);
}

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void grDimension::MakeCopy(const grDimension& rOther)
{
   m_PointA            = rOther.m_PointA;
   m_PointB            = rOther.m_PointB;           
   m_Label             = rOther.m_Label;
   m_Style             = rOther.m_Style;
   m_VPos              = rOther.m_VPos;
   m_HPos              = rOther.m_HPos;
   m_DoDrawArrows      = rOther.m_DoDrawArrows;
   m_SpaceFactor       = rOther.m_SpaceFactor;
   m_AdditionalOffset  = rOther.m_AdditionalOffset;

}

void grDimension::MakeAssignment(const grDimension& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bool grDimension::UpdateGeometry(HDC hDC, const grlibPointMapper& mapper) const
{
   // only support horizontal dimensions for now
   PRECONDITION(m_Style==Horizontal||m_Style==Vertical);

   if (m_Style==Horizontal)
      return UpdateHorizontal(hDC, mapper);
   else
      return UpdateVertical(hDC, mapper);
}

bool grDimension::UpdateHorizontal(HDC hDC, const grlibPointMapper& mapper) const
{
   // make sure we have something to dimension
   Float64 xlen = m_PointB.X()- m_PointA.X();
   CHECK(!IsZero(xlen));

   // make sure we are going from left to right
   gpPoint2d start_pt = (xlen>0 ? m_PointA : m_PointB);
   gpPoint2d end_pt   = (xlen>0 ? m_PointB : m_PointA);
   xlen = abs(xlen);

   // all metrics are based on font height. get the y size of the label 
   gpSize2d wsiz;
   wsiz = m_Label.GetSize(hDC, mapper);
   Float64 label_width   = wsiz.Dx();
   Float64 label_height  = wsiz.Dy();
   Float64 reference_hgt = m_Label.GetLineHeight(hDC, mapper);

   // locate vertical witness lines
   Float64 wx, wy;
   Float64 ytop;

   if (m_VPos==Above)
      ytop = max(start_pt.Y(), end_pt.Y()) + CalcVerticalDimHeight(m_SpaceFactor, reference_hgt);
   else
      ytop = min(start_pt.Y(), end_pt.Y()) - CalcVerticalDimHeight(m_SpaceFactor, reference_hgt);
      
   // left
   if (m_VPos==Above)
      wy =  start_pt.Y() + HOOK_OFFSET*reference_hgt;
   else
      wy =  start_pt.Y() - HOOK_OFFSET*reference_hgt;

   m_LeftWitness[0].X() = start_pt.X();
   m_LeftWitness[0].Y() = wy;
   m_LeftWitness[1].X() = start_pt.X();
   m_LeftWitness[1].Y() = ytop;

   // right
   if (m_VPos==Above)
      wy =  end_pt.Y() + HOOK_OFFSET*reference_hgt;
   else
      wy =  end_pt.Y() - HOOK_OFFSET*reference_hgt;

   m_RightWitness[0].X() = end_pt.X();
   m_RightWitness[0].Y() = wy;
   m_RightWitness[1].X() = end_pt.X();
   m_RightWitness[1].Y() = ytop;

   // leader lines
   Float64 yline;
   if (m_VPos==Above)
      yline = ytop - DIM_OFFSET*reference_hgt - m_AdditionalOffset;
   else
      yline = ytop + DIM_OFFSET*reference_hgt + m_AdditionalOffset;

   // see if text fits between arrows
   bool fits = xlen - (2*ARROW_LENGTH+1)*reference_hgt > label_width;

   if(m_HPos==Center)
   {
      if (fits && m_Label.GetNumLines()>0)
      {
         // if text fits center it between leader lines
         // left line
         m_LeftLeader[0].X() = start_pt.X();
         m_LeftLeader[0].Y() = yline;

         wx = (start_pt.X()+end_pt.X())/2. - label_width/2. - reference_hgt/2.;
         m_LeftLeader[1].X() = wx;
         m_LeftLeader[1].Y() = yline;

         // right line
         wx = (start_pt.X()+end_pt.X())/2. + label_width/2. + reference_hgt/2.;
         m_RightLeader[0].X() = wx;
         m_RightLeader[0].Y() = yline;
         m_RightLeader[1].X() = end_pt.X();
         m_RightLeader[1].Y() = yline;
      }
      else
      {
         // text doesn't fit, just draw line all the way across
         // and we'll put text above
         m_LeftLeader[0].X() = start_pt.X();
         m_LeftLeader[0].Y() = yline;
         m_LeftLeader[1].X() = end_pt.X();
         m_LeftLeader[1].Y() = yline;
         m_RightLeader[0].X() = start_pt.X();    // null
         m_RightLeader[0].Y() = yline;
         m_RightLeader[1].X() = start_pt.X();
         m_RightLeader[1].Y() = yline;
      }
   }
   else
   {
      // dimension text is located to either right or left 
      // left line
      m_LeftLeader[0].X() = start_pt.X() - LEADER_LINE_LENGTH*reference_hgt;
      m_LeftLeader[0].Y() = yline;
      m_LeftLeader[1].X() = start_pt.X();
      m_LeftLeader[1].Y() = yline;

      // right line
      m_RightLeader[0].X() = end_pt.X();
      m_RightLeader[0].Y() = yline;
      m_RightLeader[1].X() = end_pt.X() + LEADER_LINE_LENGTH*reference_hgt;
      m_RightLeader[1].Y() = yline;
   }

   // arrows
   m_LeftArrowLoc.X() = start_pt.X();
   m_LeftArrowLoc.Y() = yline;
   m_LeftArrowDir = m_HPos==Center ? M_PI : 0.0;

   m_RightArrowLoc.X() = end_pt.X();
   m_RightArrowLoc.Y() = yline;
   m_RightArrowDir = m_HPos==Center ? 0.0 : M_PI;

   gpPoint2d text_loc;
   text_loc.Y() = yline;
   // text
   if (m_HPos==Center)
   {
      text_loc.X() = (start_pt.X()+end_pt.X())/2.;

      // if text doesn't fit, put it above line
      if (!fits)
      {
         if (m_VPos==Above)
            text_loc.Y() = yline + label_height/2.;
         else
            text_loc.Y() = yline - label_height/2.;
      }

      // text location, orientation and bounds
      m_Label.SetLocation(text_loc, grLabel::Center, grLabel::Middle);
   }
   else if (m_HPos==Left)
   {
      text_loc.X() = m_LeftLeader[0].X() - reference_hgt*HOOK_OFFSET;
      m_Label.SetLocation(text_loc, grLabel::Right, grLabel::Middle);
   }
   else
   {
      text_loc.X() = m_RightLeader[1].X() + reference_hgt*HOOK_OFFSET;
      m_Label.SetLocation(text_loc, grLabel::Left, grLabel::Middle);
   }

   return true;
}

bool grDimension::UpdateVertical(HDC hDC, const grlibPointMapper& mapper) const
{
   // make sure we have something to dimension
   Float64 ylen = m_PointB.Y()- m_PointA.Y();
   if(IsZero(ylen))
      return false;

   // make sure we are going from left to right
   gpPoint2d start_pt = (ylen<0 ? m_PointA : m_PointB);
   gpPoint2d end_pt   = (ylen<0 ? m_PointB : m_PointA);

   ylen = abs(ylen);

   // all metrics are based on font height. get the y size of the label 
   gpSize2d wsiz;
   wsiz = m_Label.GetSize(hDC, mapper);
   Float64 label_width   = wsiz.Dx();
   Float64 label_height  = wsiz.Dy();
   Float64 reference_hgt = m_Label.GetLineHeight(hDC, mapper);

   // locate horizontal witness lines
   Float64 wx;
   Float64 xtop;

   if (m_VPos==Above)
      xtop = max(start_pt.X(), end_pt.X()) + 
             (m_SpaceFactor*DIM_ADJACENT_SPACING + 
              WITNESS_LINE_LENGTH+HOOK_OFFSET)*reference_hgt +
              m_AdditionalOffset;
   else
      xtop = min(start_pt.X(), end_pt.X()) - 
             (m_SpaceFactor*DIM_ADJACENT_SPACING + WITNESS_LINE_LENGTH+HOOK_OFFSET)*reference_hgt -
              m_AdditionalOffset;
      
   // left
   if (m_VPos==Above)
      wx =  start_pt.X() + HOOK_OFFSET*reference_hgt;
   else
      wx =  start_pt.X() - HOOK_OFFSET*reference_hgt;

   m_LeftWitness[0].X() = wx;
   m_LeftWitness[0].Y() = start_pt.Y();
   m_LeftWitness[1].X() = xtop;
   m_LeftWitness[1].Y() = start_pt.Y();

   // right
   if (m_VPos==Above)
      wx =  end_pt.X() + HOOK_OFFSET*reference_hgt;
   else
      wx =  end_pt.X() - HOOK_OFFSET*reference_hgt;

   m_RightWitness[0].X() = wx;
   m_RightWitness[0].Y() = end_pt.Y();
   m_RightWitness[1].X() = xtop;
   m_RightWitness[1].Y() = end_pt.Y();

   // leader lines
   Float64 xline;
   if (m_VPos==Above)
      xline = xtop - DIM_OFFSET*reference_hgt;
   else
      xline = xtop + DIM_OFFSET*reference_hgt;

   if (m_HPos==Center)
   {
      if (m_Label.GetNumLines()>0)
      {
         // if text fits center it between leader lines
         // left line
         m_LeftLeader[0].X() = xline;
         m_LeftLeader[0].Y() = start_pt.Y();

         Float64 wy = (start_pt.Y()+end_pt.Y())/2. + label_height;
         m_LeftLeader[1].X() = xline;
         m_LeftLeader[1].Y() = wy;

         // right line
         wy = (start_pt.Y()+end_pt.Y())/2. - label_height;
         m_RightLeader[0].X() = xline;
         m_RightLeader[0].Y() = wy;
         m_RightLeader[1].X() = xline;
         m_RightLeader[1].Y() = end_pt.Y();
      }
      else
      {
         // no text , just draw line all the way across
         m_LeftLeader[0].X() = xline;
         m_LeftLeader[0].Y() = start_pt.Y();
         m_LeftLeader[1].X() = xline;
         m_LeftLeader[1].Y() = end_pt.Y();
         m_RightLeader[0].X() = xline;    // null
         m_RightLeader[0].Y() = start_pt.Y();
         m_RightLeader[1].X() = xline;
         m_RightLeader[1].Y() = start_pt.Y();
      }
   }
   else
   {
      m_LeftLeader[0].X() = xline;
      m_LeftLeader[0].Y() = start_pt.Y() + LEADER_LINE_LENGTH*reference_hgt;
      m_LeftLeader[1].X() = xline;
      m_LeftLeader[1].Y() = start_pt.Y();

      // right line
      m_RightLeader[0].X() = xline;
      m_RightLeader[0].Y() = end_pt.Y();
      m_RightLeader[1].X() = xline;
      m_RightLeader[1].Y() = end_pt.Y() - LEADER_LINE_LENGTH*reference_hgt;
   }
   // arrows
   m_LeftArrowLoc.X() = xline;
   m_LeftArrowLoc.Y() = start_pt.Y();
   m_LeftArrowDir = m_HPos==Center ? M_PI/2. : -M_PI/2.;

   m_RightArrowLoc.X() = xline;
   m_RightArrowLoc.Y() = end_pt.Y();
   m_RightArrowDir = m_HPos==Center ? -M_PI/2. : M_PI/2.;

   // text location, orientation and bounds
   gpPoint2d text_loc;
   text_loc.X() = xline;
   if (m_HPos==Center)
   {
      text_loc.Y() = (start_pt.Y()+end_pt.Y())/2.-label_height/2.;
      m_Label.SetLocation(text_loc, grLabel::Center, grLabel::Middle);
   }
   else if (m_HPos==Left)
   {
      text_loc.Y() = m_LeftLeader[0].Y() + label_height/2.0;
      m_Label.SetLocation(text_loc, grLabel::Center, grLabel::Bottom);
   }
   else
   {
      text_loc.Y() = m_RightLeader[1].Y() - label_height/2.0;
      m_Label.SetLocation(text_loc, grLabel::Center, grLabel::Top);
   }

   return true;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool grDimension::AssertValid() const
{
   return true;
}

void grDimension::Dump(dbgDumpContext& os) const
{
   os << "Dump for grDimension" << endl;
   os << "m_PointA"<< endl;
   m_PointA.Dump(os);
   os << "m_PointB"<< endl;
   m_PointB.Dump(os);
   os << " m_Style = "<<m_Style<<endl;
   os << " m_VPos  = "<<m_VPos<<endl;
   os << " m_HPos  = "<<m_HPos<<endl;
   os << " m_DoDrawArrows = "<< m_DoDrawArrows<<endl;
   os << " m_SpaceFactor = "<< m_SpaceFactor<<endl<<endl;
   os << " m_AdditionalOffset"<< m_AdditionalOffset<<endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool grDimension::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("grDimension");

   // tough class to test since it's graphical. must manually use a project.

   TESTME_EPILOG("Dimension");
}
#endif // _UNITTEST


void DrawArrow(HDC hDC, const grlibPointMapper& mapper, 
               const gpPoint2d& endpt, Float64 dir)
{
   /*
   // build arrow at zero degrees and rotate
   gpPoint2d wpnt1(endpt.X()-length, endpt.Y()+width/2.);
   gpPoint2d wpnt2(endpt.X()-length, endpt.Y()-width/2.);
   if (dir!=0)
   {
      wpnt1.Rotate(endpt, dir);
      wpnt2.Rotate(endpt, dir);
   } 
   */
   SIZE siz;
   ::GetTextExtentPoint32(hDC,_T("oo"), 2, &siz);
   siz.cy/=6;
   siz.cx/=2;

   // transform to device coords and draw
   POINT     dpnt[3];
   mapper.WPtoDP(endpt.X(), endpt.Y(), &(dpnt[0].x), &(dpnt[0].y));
   if (dir==0)
   {
      dpnt[1].x = dpnt[0].x - siz.cx;
      dpnt[1].y = dpnt[0].y + siz.cy;
      dpnt[2].x = dpnt[0].x - siz.cx;
      dpnt[2].y = dpnt[0].y - siz.cy;
   }
   else if (dir==M_PI)
   {
      dpnt[1].x = dpnt[0].x + siz.cx;
      dpnt[1].y = dpnt[0].y - siz.cy;
      dpnt[2].x = dpnt[0].x + siz.cx;
      dpnt[2].y = dpnt[0].y + siz.cy;
   }
   else if (dir==M_PI/2)
   {
      dpnt[1].x = dpnt[0].x + siz.cy;
      dpnt[1].y = dpnt[0].y + siz.cx;
      dpnt[2].x = dpnt[0].x - siz.cy;
      dpnt[2].y = dpnt[0].y + siz.cx;
   }
   else if (dir==-M_PI/2)
   {
      dpnt[1].x = dpnt[0].x - siz.cy;
      dpnt[1].y = dpnt[0].y - siz.cx;
      dpnt[2].x = dpnt[0].x + siz.cy;
      dpnt[2].y = dpnt[0].y - siz.cx;
   }
   else
      CHECK(0);  // rotation not defined

   ::Polygon(hDC, dpnt, 3);
}

Float64 CalcVerticalDimHeight(Float64 spaceFactor, Float64 referenceHgt)
{
   return (spaceFactor*DIM_ADJACENT_SPACING + WITNESS_LINE_LENGTH+HOOK_OFFSET)*referenceHgt;
}
