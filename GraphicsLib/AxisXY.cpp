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
#include <GraphicsLib\AxisXY.h>

#include <MathEx.h>
#include <Math\CoordMapper1d.h>
#include <GraphicsLib\GraphTool.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   grAxisXY
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LifECYCLE  =======================================
grAxisXY::grAxisXY(AxisOrientation orientation, const sysINumericFormatToolBase& rFormat):
m_pValueFormat(&rFormat)
{
   Init();
   SetOrientation(orientation, 0, 1, 0);
}

grAxisXY::grAxisXY(AxisOrientation orientation, Int32 AxMin, Int32 AxMax, Int32 AyValue,
const sysINumericFormatToolBase& rFormat):
m_pValueFormat(&rFormat)
{
   CHECK(AxMin<AxMax);
   Init();
   SetOrientation(orientation, AxMin, AxMax, AyValue);
}


grAxisXY::grAxisXY(const grAxisXY& rOther)
{
   MakeCopy(rOther);
}

grAxisXY::~grAxisXY()
{
}

//======================== OPERATORS  =======================================
grAxisXY& grAxisXY::operator= (const grAxisXY& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

void grAxisXY::SetOrientation(AxisOrientation orientation, Int32 AxMin, Int32 AxMax,
                              Int32 AyValue)
{
   // set metrics dirty
   m_MetricsDirtyFlag = true;

   m_Orientation = orientation;
   m_MinLocation = AxMin;
   m_MaxLocation = AxMax;
   m_YLocation   = AyValue;
}


void grAxisXY::Draw(HDC hDC)
{
   // set up a pen to draw axis with.
   HPEN my_hpen   = ::CreatePen(PS_SOLID, 2, RGB(0,0,0) );
   HGDIOBJ old_hpen = ::SelectObject (hDC, my_hpen);
   int old_bk = ::SetBkMode(hDC,TRANSPARENT);

   // set text alignement for axis value labels
   if ( m_ValueAngle == 0 )
      ::SetTextAlign(hDC, TA_CENTER | TA_TOP);
   else
      ::SetTextAlign(hDC, TA_RIGHT  | TA_TOP);

   // make sure metrics are up to date
   UpdateAxisMetrics(hDC);

   // Set up mapping between device coords and world (axis) coords. Axis coords
   // will be the A axis.
   mathCoordMapper1d axis_mapper;

   axis_mapper.SetCoordinateMap(m_Scale == LINEAR ? m_LeftAxisValue  : log10(m_LeftAxisValue),  m_MinLocation, 
                                m_Scale == LINEAR ? m_RightAxisValue : log10(m_RightAxisValue), m_MaxLocation);

   // Draw the main axis line
   POINT p1, p2;
   if (m_Orientation == X_AXIS)
   {
      p1.x = m_MinLocation; p1.y = m_YLocation;
      p2.x = m_MaxLocation; p2.y = m_YLocation;
   }
   else
   {
      p1.y = m_MinLocation; p1.x = m_YLocation;
      p2.y = m_MaxLocation; p2.x = m_YLocation;
   }
   POINT pnt;
   ::MoveToEx(hDC, p1.x, p1.y, &pnt);
   ::LineTo(hDC, p2.x, p2.y);

   // Deal with Tic marks and value labels

   if (m_DoShowTics)
   {
      // draw tics and values
      if ( m_Scale == LINEAR )
      {
         Float64 tic_value = m_LeftAxisValue;
         Float64 tic_prev;
         Int32 num_incrs = (Int32)ceil( (m_RightAxisValue-m_LeftAxisValue)/m_AxisIncrement );
         for (Int32 i=0; i<=num_incrs; i++)
         {
            Int32 tic_l = (Int32)Round( axis_mapper.GetB(tic_value) );

            // draw major tic
            if (m_Orientation == X_AXIS)
            {
               POINT pt1={tic_l,m_AxisMetrics.MajorTicTop}, pt2={tic_l,m_AxisMetrics.MajorTicBottom};
               ::MoveToEx(hDC, pt1.x, pt1.y, &pnt);
               ::LineTo(hDC, pt2.x, pt2.y);
            }
            else
            {
               POINT pt1={m_AxisMetrics.MajorTicTop, tic_l}, pt2={m_AxisMetrics.MajorTicBottom, tic_l};
               ::MoveToEx(hDC, pt1.x, pt1.y, &pnt);
               ::LineTo(hDC, pt2.x, pt2.y);
            }

            // draw value text
            if (m_DoShowText)
            {
               std::_tstring value_text = m_pValueFormat->AsString(tic_value);

               if (m_Orientation == X_AXIS)
               {
                  LONG old_a;
                  if ( m_ValueAngle == 0 )
                     old_a = ::SetTextAlign(hDC, TA_CENTER | TA_TOP);
                  else
                     old_a = ::SetTextAlign(hDC, TA_RIGHT  | TA_TOP);

                  grGraphTool::TextOutRotated(hDC, tic_l, m_AxisMetrics.ValueTextLoc, m_ValueAngle,
                                     value_text.c_str(), (LONG)value_text.size(),
                                     m_AxisValueSize);
                  ::SetTextAlign(hDC, old_a);            
               }
               else
               {
                  UINT old_a = SetTextAlign(hDC, TA_RIGHT | TA_BASELINE);
                  grGraphTool::TextOutRotated(hDC, m_AxisMetrics.ValueTextLoc, tic_l,  m_ValueAngle,
                                     value_text.c_str(), (LONG)value_text.size(),
                                     m_AxisValueSize);
                  ::SetTextAlign(hDC, old_a);            
               }
            }

            // minor tics
            if (i>0 && m_NumberOfMinorTics>1)
            {
               Float64 minor_tic_inc = (tic_value-tic_prev)/m_NumberOfMinorTics;
               Float64 minor_tic_l = tic_prev;
               for (Int32 j=1; j<m_NumberOfMinorTics; j++)
               {
                  minor_tic_l += minor_tic_inc;
                  tic_l = (Int32)Round( axis_mapper.GetB(minor_tic_l) );

                  if (m_Orientation == X_AXIS)
                  {
                     POINT pm1={tic_l,m_AxisMetrics.MinorTicTop}, 
                           pm2={tic_l,m_AxisMetrics.MinorTicBottom};
                     ::MoveToEx(hDC, pm1.x, pm1.y, &pnt);
                     ::LineTo(hDC, pm2.x, pm2.y);
                  }
                  else
                  {
                     POINT pm1={m_AxisMetrics.MinorTicTop, tic_l},
                           pm2={m_AxisMetrics.MinorTicBottom, tic_l};
                     ::MoveToEx(hDC, pm1.x, pm1.y, &pnt);
                     ::LineTo(hDC, pm2.x, pm2.y);
                  }
               }
            }
            tic_prev = tic_value;
            tic_value += m_AxisIncrement;
         }
      }
      else
      {
         // LOG scale
         int exp1 = (m_LeftAxisValue == 0 ? 0 : (int)floor(log10(m_LeftAxisValue)));
         int exp2 = (int)floor(log10(m_RightAxisValue));
         for ( int i = exp1; i <= exp2; i++ )
         {
            Float64 tic_value = pow(10,(Float64)i);
            Int32 tic_l = (Int32)Round(axis_mapper.GetB(log10(tic_value)));

            // draw major tic
            if (m_Orientation == X_AXIS)
            {
               POINT pt1={tic_l,m_AxisMetrics.MajorTicTop}, pt2={tic_l,m_AxisMetrics.MajorTicBottom};
               ::MoveToEx(hDC, pt1.x, pt1.y, &pnt);
               ::LineTo(hDC, pt2.x, pt2.y);
            }
            else
            {
               POINT pt1={m_AxisMetrics.MajorTicTop, tic_l}, pt2={m_AxisMetrics.MajorTicBottom, tic_l};
               ::MoveToEx(hDC, pt1.x, pt1.y, &pnt);
               ::LineTo(hDC, pt2.x, pt2.y);
            }

            // draw value text
            if (m_DoShowText)
            {
               std::_tstring value_text = m_pValueFormat->AsString(tic_value);

               if (m_Orientation == X_AXIS)
               {
                  LONG old_a;
                  if ( m_ValueAngle == 0 )
                     old_a = ::SetTextAlign(hDC, TA_CENTER | TA_TOP);
                  else
                     old_a = ::SetTextAlign(hDC, TA_RIGHT  | TA_TOP);

                  grGraphTool::TextOutRotated(hDC, tic_l, m_AxisMetrics.ValueTextLoc, m_ValueAngle,
                                     value_text.c_str(), (LONG)value_text.size(),
                                     m_AxisValueSize);
                  ::SetTextAlign(hDC, old_a);            
               }
               else
               {
                  UINT old_a = SetTextAlign(hDC, TA_RIGHT | TA_BASELINE);
                  grGraphTool::TextOutRotated(hDC, m_AxisMetrics.ValueTextLoc, tic_l,  m_ValueAngle,
                                     value_text.c_str(), (LONG)value_text.size(),
                                     m_AxisValueSize);
                  ::SetTextAlign(hDC, old_a);            
               }
            }

            // minor tics
            if (i < exp2 && 1 < m_NumberOfMinorTics)
            {
               for ( int j = 1; j < 10; j++ )
               {
                  Float64 minor_tic = j*pow(10,(Float64)i);
                  tic_l = (Int32)Round( axis_mapper.GetB(log10(minor_tic)) );

                  if (m_Orientation == X_AXIS)
                  {
                     POINT pm1={tic_l,m_AxisMetrics.MinorTicTop}, 
                           pm2={tic_l,m_AxisMetrics.MinorTicBottom};
                     ::MoveToEx(hDC, pm1.x, pm1.y, &pnt);
                     ::LineTo(hDC, pm2.x, pm2.y);
                  }
                  else
                  {
                     POINT pm1={m_AxisMetrics.MinorTicTop, tic_l},
                           pm2={m_AxisMetrics.MinorTicBottom, tic_l};
                     ::MoveToEx(hDC, pm1.x, pm1.y, &pnt);
                     ::LineTo(hDC, pm2.x, pm2.y);
                  }
               }
            }
         }
      }
   }

   // draw text title and subtitle

   if (m_DoShowText)
   {
      // set text alignment for axis titles

      //Int32 tit_hl = (Int32)Round( m_Scale == LINEAR ? axis_mapper.GetB( (m_LeftAxisValue+m_RightAxisValue)/2 ) : axis_mapper.GetB( log10( (m_LeftAxisValue+m_RightAxisValue)/2 ) ));
      Int32 tit_hl = (m_MinLocation + m_MaxLocation)/2;

      if (m_Orientation == X_AXIS)
      {
         ::SetTextAlign(hDC, TA_CENTER | TA_TOP);
         grGraphTool::TextOutRotated(hDC, tit_hl, m_AxisMetrics.TitleTextLoc, 0,
                            m_AxisTitle.c_str(), (LONG)m_AxisTitle.size(),
                            m_AxisTitleSize);

         grGraphTool::TextOutRotated(hDC, tit_hl, m_AxisMetrics.SubtitleTextLoc, 0,
                            m_AxisSubtitle.c_str(), (LONG)m_AxisSubtitle.size(),
                            m_AxisSubtitleSize);

      }
      else
      {
         ::SetTextAlign(hDC, TA_CENTER | TA_BASELINE);
         grGraphTool::TextOutRotated(hDC, 
                                     m_AxisMetrics.TitleTextLoc , tit_hl, 900,
                                     m_AxisTitle.c_str(), (LONG)m_AxisTitle.size(),
                                     m_AxisTitleSize);

         grGraphTool::TextOutRotated(hDC,
                                     m_AxisMetrics.SubtitleTextLoc ,tit_hl, 900,
                                     m_AxisSubtitle.c_str(), (LONG)m_AxisSubtitle.size(),
                                     m_AxisSubtitleSize);
      }
   }

   ::SelectObject (hDC, old_hpen);
   ::DeleteObject(my_hpen);
   ::SetBkMode(hDC,old_bk);
}

void grAxisXY::SetNiceAxisRange(Float64 leftVal, Float64 rightVal,bool bOffsetZero)
{
   // set metrics dirty
   m_MetricsDirtyFlag = true;

   if ( m_Scale == LINEAR )
   {
      CollectionIndexType num_tic = m_NumberOfMajorTics;
      grGraphTool::CalculateNiceRange(leftVal, rightVal, bOffsetZero, num_tic, m_LeftAxisValue, 
                                      m_RightAxisValue, m_AxisIncrement);
   }
   else //( m_Scale == LOGARITHMIC )
   {
      // Compute nice log value
      Float64 exp1 = floor(log10(leftVal));
      m_LeftAxisValue = pow(10,exp1);

      Float64 exp2 = ceil(log10(rightVal));
      m_RightAxisValue = pow(10,exp2);

      m_AxisIncrement = (m_RightAxisValue - m_LeftAxisValue)/(exp2-exp1);
   }
}

void grAxisXY::SetForcedAxisRange(Float64 leftVal, Float64 rightVal, Float64 increment)
{
   // set metrics dirty
   m_MetricsDirtyFlag = true;

   CHECK(increment!=0);
   CHECK( (increment>0 && leftVal<rightVal) || (increment<0 && leftVal>rightVal));

   m_LeftAxisValue  = leftVal;
   m_RightAxisValue = rightVal;
   m_AxisIncrement  = increment;
}

Int32 grAxisXY::GetThickness(HDC hDC)
{
   UpdateAxisMetrics(hDC);

   return labs(m_AxisMetrics.UpperLimit-m_AxisMetrics.LowerLimit);
}


void grAxisXY::GetAxisRange(Float64& leftVal, Float64& rightVal, Float64& increment)
{
   leftVal   = m_LeftAxisValue;
   rightVal  = m_RightAxisValue;
   increment = m_AxisIncrement;
}

   // GROUP: ACCESS

void grAxisXY::SetTitleFontSize(Int32 fontSize)
{
   CHECK(fontSize>0);

   // set metrics dirty
   m_MetricsDirtyFlag = true;

   m_AxisTitleSize = fontSize;
}

Int32 grAxisXY::GetTitleFontSize()
{
   return m_AxisTitleSize;
}

void grAxisXY::SetSubtitleFontSize(Int32 fontSize)
{
   CHECK(fontSize>0);

   // set metrics dirty
   m_MetricsDirtyFlag = true;

   m_AxisSubtitleSize = fontSize;
}

Int32 grAxisXY::GetSubtitleFontSize()
{
   return m_AxisSubtitleSize;
}

void grAxisXY::SetValueFontSize(Int32 fontSize)
{
   CHECK(fontSize>0);

   // set metrics dirty
   m_MetricsDirtyFlag = true;

   m_AxisValueSize = fontSize;
}

Int32 grAxisXY::GetValueFontSize()
{
   // set metrics dirty
   m_MetricsDirtyFlag = true;

   return m_AxisValueSize;
}

void grAxisXY::SetValueAngle(LONG angle)
{
   m_ValueAngle = angle;
}

LONG grAxisXY::GetValueAngle() const
{
   return m_ValueAngle;
}

void grAxisXY::SetValueFormat(const sysINumericFormatToolBase& format)
{
   m_pValueFormat = &format;
}

const sysINumericFormatToolBase* grAxisXY::GetValueFormat() const
{
   return m_pValueFormat;
}


void grAxisXY::SetTicLocation(grAxisXY::TicLocation location)
{
   m_TicLocation = location;
}

grAxisXY::TicLocation grAxisXY::GetTicLocation()
{
   return m_TicLocation;
}

void grAxisXY::SetTextLocation(grAxisXY::TextLocation location)
{
   // set metrics dirty
   m_MetricsDirtyFlag = true;

   m_TextLocation = location;
}

grAxisXY::TextLocation grAxisXY::GetTextLocation()
{
   return m_TextLocation;
}

void grAxisXY::SetNumberOfMajorTics(Int32 numTics)
{
   // set metrics dirty
   m_MetricsDirtyFlag = true;

   if (numTics<1)
      m_NumberOfMajorTics = 1;
   else
      m_NumberOfMajorTics = numTics;
}


Int32 grAxisXY::GetNumberOfMajorTics()
{
   return m_NumberOfMajorTics;
}

void grAxisXY::SetNumberOfMinorTics(Int32 numTics)
{
   // set metrics dirty
   m_MetricsDirtyFlag = true;

   if (numTics<2)
      m_NumberOfMinorTics = 0;
   else
      m_NumberOfMinorTics = numTics;
}

Int32 grAxisXY::GetNumberOfMinorTics()
{
   return m_NumberOfMinorTics;
}

void grAxisXY::SetShowTics(bool doShow)
{
   // set metrics dirty
   m_MetricsDirtyFlag = true;

   m_DoShowTics = doShow;
}

bool grAxisXY::GetShowTics()
{
   return m_DoShowTics;
}

void grAxisXY::SetTitleText(const std::_tstring& text)
{
   // set metrics dirty
   m_MetricsDirtyFlag = true;

   m_AxisTitle = text.c_str();
}

std::_tstring grAxisXY::GetTitleText()
{
   // set metrics dirty
   m_MetricsDirtyFlag = true;

   return m_AxisTitle;
}

void grAxisXY::SetSubtitleText(const std::_tstring& text)
{
   // set metrics dirty
   m_MetricsDirtyFlag = true;

   m_AxisSubtitle = text.c_str();
}

std::_tstring grAxisXY::GetSubtitleText()
{
   return m_AxisSubtitle;
}

void grAxisXY::SetShowText(bool doShow)
{
   // set metrics dirty
   m_MetricsDirtyFlag = true;

   m_DoShowText = doShow;
}

bool grAxisXY::GetShowText()
{
   return m_DoShowText;
}

void grAxisXY::SetScale(grAxisXY::AxisScale scale)
{
   m_Scale = scale;
}

grAxisXY::AxisScale grAxisXY::GetScale() const
{
   return m_Scale;
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LifECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void grAxisXY::MakeCopy(const grAxisXY& rOther)
{
   m_Orientation       = rOther.m_Orientation;
   m_MinLocation       = rOther.m_MinLocation;      
   m_MaxLocation       = rOther.m_MaxLocation;      
   m_YLocation         = rOther.m_YLocation;        

   m_LeftAxisValue     = rOther.m_LeftAxisValue;    
   m_RightAxisValue    = rOther.m_RightAxisValue;   
   m_AxisIncrement     = rOther.m_AxisIncrement;    
   m_NumberOfMajorTics = rOther.m_NumberOfMajorTics;
   m_NumberOfMinorTics = rOther.m_NumberOfMinorTics;
   m_TicLocation       = rOther.m_TicLocation;      
   m_TextLocation      = rOther.m_TextLocation;     

   m_AxisTitle         = rOther.m_AxisTitle;        
   m_AxisSubtitle      = rOther.m_AxisSubtitle;     
   m_AxisTitleSize     = rOther.m_AxisTitleSize;    
   m_AxisSubtitleSize  = rOther.m_AxisSubtitleSize; 
   m_AxisValueSize     = rOther.m_AxisValueSize;    
   m_pValueFormat      = rOther.m_pValueFormat;

   m_ValueAngle        = rOther.m_ValueAngle;

   m_Scale             = rOther.m_Scale;

   // force recalculation of metrics rather than copy them.
   m_MetricsDirtyFlag = true;
}

void grAxisXY::MakeAssignment(const grAxisXY& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LifECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void grAxisXY::UpdateAxisMetrics(HDC hDC)
{
   // most metrics are based on font sizes. get sizes for title and subtitle
   HFONT titfont = grGraphTool::CreateRotatedFont(hDC, 0, m_AxisTitleSize);
   HGDIOBJ old_font = ::SelectObject(hDC, titfont);
   SIZE siz;
   ::GetTextExtentPoint32(hDC,_T("AA"),2,&siz);

   LONG title_size = labs(siz.cy);

   HFONT subtitfont = grGraphTool::CreateRotatedFont(hDC, 0, m_AxisSubtitleSize);
   ::SelectObject(hDC, subtitfont);
   ::GetTextExtentPoint32(hDC,_T("AA"),2,&siz);

   LONG subtitle_size = labs(siz.cy);

   // determine tic size based on title font size
   m_AxisMetrics.TicSize = title_size/2;

   // ugly code here
   // in order to get things to space nicely
   // need to adjust text extends for rotated text box
   LONG max_value_width = 0;
   LONG max_value_height = 0;
   Float64 curr_value = m_LeftAxisValue;
   HFONT valuefont = grGraphTool::CreateRotatedFont(hDC, m_ValueAngle, m_AxisValueSize);
   ::SelectObject(hDC, valuefont);
   LONG num_incrs = (LONG)ceil( (m_RightAxisValue-m_LeftAxisValue)/m_AxisIncrement);
   for (LONG i=0; i<=num_incrs; i++)
   {
      std::_tstring value_text(m_pValueFormat->AsString(curr_value));
      ::GetTextExtentPoint32(hDC,value_text.c_str(),(int)value_text.size(),&siz);
      Float64 angle = ::ToRadians(m_ValueAngle/10.);
      Float64 width  = siz.cx*cos(angle) + siz.cy*sin(angle);
      Float64 height = siz.cx*sin(angle) + siz.cy*cos(angle);

      max_value_width  = max(max_value_width, Int32(width));
      max_value_height = max(max_value_height,Int32(height));

      curr_value += m_AxisIncrement;
   }
   //max_value_width  = (Int32)(Float64(max_value_width)*1.1);        // a little more space
   //max_value_height = (Int32)(Float64(max_value_height)*1.1);        // a little more space

   // clean up
   ::SelectObject(hDC, old_font);
   ::DeleteObject(titfont);
   ::DeleteObject(subtitfont);
   ::DeleteObject(valuefont);

   // determine vertical tic coords
   // remember - coordinates are upside down
  
   if (m_DoShowTics)
   {
      if (m_TicLocation == TIC_ABOVE)
      {
         m_AxisMetrics.MajorTicBottom = m_YLocation;
         m_AxisMetrics.MajorTicTop    = m_YLocation - m_AxisMetrics.TicSize;
         m_AxisMetrics.MinorTicBottom = m_YLocation;
         m_AxisMetrics.MinorTicTop    = m_YLocation - m_AxisMetrics.TicSize/2;
      }
      else if (m_TicLocation == TIC_CENTER)
      {
         m_AxisMetrics.MajorTicBottom = m_YLocation + m_AxisMetrics.TicSize/2;
         m_AxisMetrics.MajorTicTop    = m_YLocation - m_AxisMetrics.TicSize/2;
         m_AxisMetrics.MinorTicBottom = m_YLocation + m_AxisMetrics.TicSize/4;
         m_AxisMetrics.MinorTicTop    = m_YLocation - m_AxisMetrics.TicSize/4;
      }
      else if (m_TicLocation == TIC_BELOW)
      {
         m_AxisMetrics.MajorTicBottom = m_YLocation + m_AxisMetrics.TicSize;
         m_AxisMetrics.MajorTicTop    = m_YLocation;
         m_AxisMetrics.MinorTicBottom = m_YLocation + m_AxisMetrics.TicSize/2;
         m_AxisMetrics.MinorTicTop    = m_YLocation;
      }
      else
         CHECKX(0, _T("Bad tic location") );
   }
   else
   {
      // tics are not drawn - set locations to center of axis in order
      // for depth calculation to work out correctly
      m_AxisMetrics.MajorTicBottom = m_YLocation;
      m_AxisMetrics.MajorTicTop    = m_YLocation;
      m_AxisMetrics.MinorTicBottom = m_YLocation; 
      m_AxisMetrics.MinorTicTop    = m_YLocation;
   }

   // init upper and lower bounds
   m_AxisMetrics.UpperLimit = m_AxisMetrics.MajorTicTop;
   m_AxisMetrics.LowerLimit = m_AxisMetrics.MajorTicBottom;


   if (m_DoShowTics && m_DoShowText)
   {
      // location of text for values
      if (m_TextLocation == TEXT_ABOVE)
         m_AxisMetrics.ValueTextLoc = m_AxisMetrics.MajorTicTop - m_AxisMetrics.TicSize/2;
      else
         m_AxisMetrics.ValueTextLoc = m_AxisMetrics.MajorTicBottom + m_AxisMetrics.TicSize/2;
   }
   else
      m_AxisMetrics.ValueTextLoc = m_AxisMetrics.MajorTicBottom;


   // Title and subtitle
   if (m_DoShowText)
   {
      Int32 value_space;
      Int32 value_height;
      if (m_Orientation == X_AXIS)
      {
         value_space = m_AxisMetrics.TicSize;
         value_height = max_value_height;
      }
      else
      {
         value_space  = max_value_width;
         value_height = max_value_width;
      }

      if (m_TextLocation == TEXT_ABOVE)
      {
         m_AxisMetrics.SubtitleTextLoc = m_AxisMetrics.ValueTextLoc - value_space;

         if (!m_AxisSubtitle.empty())
            m_AxisMetrics.TitleTextLoc = m_AxisMetrics.SubtitleTextLoc - subtitle_size;
         else
            m_AxisMetrics.TitleTextLoc = m_AxisMetrics.ValueTextLoc - value_space;
         
         m_AxisMetrics.UpperLimit = m_AxisMetrics.TitleTextLoc;

         if (!m_AxisTitle.empty())
            m_AxisMetrics.UpperLimit = m_AxisMetrics.TitleTextLoc - title_size;

         if (!m_AxisSubtitle.empty())
            m_AxisMetrics.UpperLimit = m_AxisMetrics.SubtitleTextLoc - subtitle_size;
      }
      else
      {
         m_AxisMetrics.TitleTextLoc    = m_AxisMetrics.ValueTextLoc + value_height;// - title_size/2;
         m_AxisMetrics.SubtitleTextLoc = m_AxisMetrics.TitleTextLoc + 3*subtitle_size/2;

         if (!m_AxisTitle.empty())
            m_AxisMetrics.LowerLimit = m_AxisMetrics.TitleTextLoc + title_size;

         if (!m_AxisSubtitle.empty())
            m_AxisMetrics.LowerLimit = m_AxisMetrics.SubtitleTextLoc + subtitle_size;
      }
   }
   else
   {
      m_AxisMetrics.TitleTextLoc = m_AxisMetrics.ValueTextLoc;
      m_AxisMetrics.SubtitleTextLoc = m_AxisMetrics.ValueTextLoc;
   }
   // metrics are now up to date
   m_MetricsDirtyFlag = false;
}

void grAxisXY::Init()
{
   // set up some defaults
   m_Orientation = X_AXIS;
   m_MinLocation = 0;
   m_MaxLocation = 100;
   m_YLocation   = 0;

   m_ValueAngle = 0;

   m_LeftAxisValue  = 0;
   m_RightAxisValue = 1;
   m_AxisIncrement  = 0.1;
   m_NumberOfMajorTics = 7;
   m_NumberOfMinorTics = 0;
   m_TicLocation  = TIC_BELOW;
   m_TextLocation = TEXT_BELOW;
   m_DoShowText   = true;
   m_DoShowTics   = true;

   m_AxisTitleSize    = 12;
   m_AxisSubtitleSize = 10;
   m_AxisValueSize    = 10;
   m_MetricsDirtyFlag = true;

   m_Scale = LINEAR;
}


//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


////////////////
grAxisXY::AxisMetrics::AxisMetrics()
{
   TicSize=0;
   MajorTicBottom=0;
   MajorTicTop=0;
   MinorTicBottom=0;
   MinorTicTop=0;
   ValueTextLoc=0;
   TitleTextLoc=0;
   SubtitleTextLoc=0;
}

grAxisXY::AxisMetrics::~AxisMetrics()
{
}


//======================== DEBUG      =======================================
#if defined _DEBUG
bool grAxisXY::AssertValid() const
{
   return true;
}

void grAxisXY::Dump(dbgDumpContext& os) const
{
   os << "Dump for grAxisXY" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool grAxisXY::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("grAxisXY");

   // tough class to test since it's graphical. must manually use a project.

   TESTME_EPILOG("grAxisXY");
}
#endif // _UNITTEST

