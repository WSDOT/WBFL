///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
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

#include <GraphicsLib\GraphicsLibLib.h>
#include <GraphicsLib\Label.h>
#include <GraphicsLib\GraphTool.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   grLabel
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////
// free function to parse a string with std::endl's in it and return them into a vector of strings
std::vector<std::_tstring> ParseLabel(const std::_tstring& label);
std::_tstring UnParseLabel(const std::vector<std::_tstring> labels);
void GetLabelSize(HDC hDC, const std::vector<std::_tstring>& labels, LONG pointSize, SIZE* psiz, LONG* pline_hgt);

//======================== LIFECYCLE  =======================================
grLabel::grLabel()
{
   Init();
} 

grLabel::grLabel(const gpPoint2d& point, const std::_tstring& label)
{
   Init();
   m_HookPoint = point;
   m_Labels = ParseLabel(label);
}

grLabel::grLabel(const grLabel& rOther)
{
   MakeCopy(rOther);
}

grLabel::~grLabel()
{
}

//======================== OPERATORS  =======================================
grLabel& grLabel::operator= (const grLabel& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

void grLabel::Draw(HDC hDC, const grlibPointMapper& mapper) const
{
   IndexType siz = m_Labels.size();
   if (siz>0)
   {
      HFONT new_font = grGraphTool::CreateRotatedFont(hDC, 0, m_PointSize);
      HGDIOBJ old_font = ::SelectObject(hDC, new_font);
      UINT  old_align = ::SetTextAlign( hDC, TA_BASELINE | TA_LEFT );
      int old_bk = ::SetBkMode(hDC,TRANSPARENT);

      TEXTMETRIC tm;
      ::GetTextMetrics(hDC, &tm);
      LONG line_hgt = tm.tmHeight + tm.tmExternalLeading;
 
      gpRect2d wbox = GetBoundingBox(hDC, mapper);
      LONG dvx, dvy;
      mapper.WPtoDP(wbox.Left(), wbox.Top(), &dvx, &dvy);
      dvy += tm.tmAscent;

      for (IndexType i=0; i<siz; i++)
      {
         ::TextOut( hDC, dvx, dvy, m_Labels[i].c_str(), (int)m_Labels[i].size());
         dvy += line_hgt;
      }

// debugging code for bounding rect problems
//      grGraphTool::DrawRect(hDC,mapper,wbox,RGB(0,255,0));

      ::SelectObject(hDC, old_font);
      ::SetTextAlign( hDC, old_align);
      ::DeleteObject(new_font);
      ::SetBkMode(hDC,old_bk);
   }
}

//======================== ACCESS     =======================================
void grLabel::SetHorizPosition(HorizPosition pos)
{
   m_HorizPos = pos;
}

grLabel::HorizPosition grLabel::GetHorizPosition() const
{
   return m_HorizPos;
}

void grLabel::SetVertPosition(VertPosition pos)
{
   m_VertPos = pos;
}

grLabel::VertPosition grLabel::GetVertPosition() const
{
   return m_VertPos;
}

void grLabel::SetHookPoint(const gpPoint2d& point)
{
   m_HookPoint = point;
}

gpPoint2d grLabel::GetHookPoint() const
{
   return m_HookPoint;
}

void grLabel::SetLocation(const gpPoint2d& point, HorizPosition hpos, VertPosition vpos)
{
   m_HookPoint = point;
   m_HorizPos = hpos;
   m_VertPos = vpos;
}

void grLabel::SetLabel(const std::_tstring& label)
{
   m_Labels = ParseLabel(label);
}

std::_tstring grLabel::GetLabel() const
{
   return UnParseLabel(m_Labels);
}

void grLabel::SetPointSize(Uint32 siz)
{
   CHECK(siz>0);
   m_PointSize = siz;
}

Uint32 grLabel::GetPointSize() const
{
   return m_PointSize;
}

//======================== INQUIRY    =======================================
gpRect2d grLabel::GetBoundingBox(HDC hDC, const grlibPointMapper& mapper) const
{
   gpRect2d tmpBox;

   // get size of label in world coord's
   gpSize2d tsiz(GetSize(hDC, mapper));

   // now orient it in space
   switch (m_HorizPos)
   {
   case Left:
      tmpBox.Left() = m_HookPoint.X();
      tmpBox.Right()= m_HookPoint.X() + tsiz.Dx();
      break;
   case Center:
      tmpBox.Left() = m_HookPoint.X() - tsiz.Dx()/2.;
      tmpBox.Right()= m_HookPoint.X() + tsiz.Dx()/2.;
      break;
   case Right:
      tmpBox.Left() = m_HookPoint.X() - tsiz.Dx();
      tmpBox.Right()= m_HookPoint.X();
      break;
   default:
      CHECK(0);
   }

   switch (m_VertPos)
   {
   case Top:
      tmpBox.Top()   = m_HookPoint.Y();
      tmpBox.Bottom()= m_HookPoint.Y() - tsiz.Dy();
      break;
   case Middle:
      tmpBox.Top()   = m_HookPoint.Y() + tsiz.Dy()/2.;
      tmpBox.Bottom()= m_HookPoint.Y() - tsiz.Dy()/2.;
      break;
   case Bottom:
      tmpBox.Top()   = m_HookPoint.Y() + tsiz.Dy();
      tmpBox.Bottom()= m_HookPoint.Y();
      break;
   default:
      CHECK(0);
   }

   return tmpBox;
}

gpSize2d grLabel::GetSize(HDC hDC, const grlibPointMapper& mapper) const
{
   // get size in dc coords
   SIZE tsiz;
   LONG line_hgt;
   GetLabelSize(hDC, m_Labels, m_PointSize, &tsiz, &line_hgt);

   // convert to world
   gpSize2d tmp;
   tmp.Dx() = tsiz.cx * mapper.GetScaleX();
   tmp.Dy() = tsiz.cy * mapper.GetScaleY();
   return tmp;
}

IndexType grLabel::GetNumLines() const
{
   return m_Labels.size();
}

Float64 grLabel::GetLineHeight(HDC hDC, const grlibPointMapper& mapper) const
{
   LONG line_hgt = GetLineHeight(hDC);
   Float64 hgt = line_hgt * mapper.GetScaleY();
   return hgt;
}

LONG grLabel::GetLineHeight(HDC hDC) const
{
   HFONT new_font = grGraphTool::CreateRotatedFont(hDC, 0, m_PointSize);
   HGDIOBJ old_font = ::SelectObject(hDC, new_font);

   TEXTMETRIC tm;
   ::GetTextMetrics(hDC, &tm);
   LONG line_hgt = tm.tmHeight + tm.tmExternalLeading;

   ::SelectObject(hDC, old_font);
   ::DeleteObject(new_font);
   return line_hgt;
}
////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void grLabel::MakeCopy(const grLabel& rOther)
{
   m_HookPoint = rOther.m_HookPoint;
   m_Labels    = rOther.m_Labels;
   m_HorizPos  = rOther.m_HorizPos;
   m_VertPos   = rOther.m_VertPos;
   m_PointSize = rOther.m_PointSize;
}

void grLabel::MakeAssignment(const grLabel& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void grLabel::Init()
{
   m_Labels.clear();
   m_HorizPos = Center;
   m_VertPos = Middle;
   m_PointSize = 10;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool grLabel::AssertValid() const
{
   return true;
}

void grLabel::Dump(dbgDumpContext& os) const
{
   os << "Dump for grLabel" << endl;
   os << "  m_HookPoint :"<< endl; 
   m_HookPoint.Dump(os);
   IndexType siz = m_Labels.size();
   for (IndexType i=0; i<siz; i++)
   {
      os << " m_Labels["<<i<<"] = "<<m_Labels[i]<<endl;
   }
   os << "  m_HorizPos  = " <<m_HorizPos << endl; 
   os << "  m_VertPos   = " <<m_VertPos << endl;  
   os << "  m_PointSize = " <<m_PointSize<<endl;
}
#endif // _DEBUG

std::vector<std::_tstring> ParseLabel(const std::_tstring& label)
{
   std::vector<std::_tstring> label_list;
   std::_tstring tmp;
   std::_tstring::size_type start_loc = 0;
   std::_tstring::size_type end_loc = 0;
   do {
      end_loc = label.find(_T("\n"), start_loc); // find an std::endl
      tmp = label.substr(start_loc, end_loc);
      label_list.push_back(tmp);
      start_loc = end_loc+1;
   } while (end_loc!= std::_tstring::npos);

   return label_list;
}

std::_tstring UnParseLabel(const std::vector<std::_tstring> labels)
{
   // loop through vector and rebuild original label
   std::_tstring tmp;
   std::_tostringstream os;
   IndexType siz = labels.size();
   for (IndexType i=0; i<siz; i++)
   {
      os << labels[i];
      if (i!=siz-1)
         os << std::endl;
   }
   return os.str();
}

void GetLabelSize(HDC hDC, const std::vector<std::_tstring>& labels, LONG pointSize, SIZE* psiz, LONG* pline_hgt)
{
   HFONT new_font = grGraphTool::CreateRotatedFont(hDC, 0, pointSize);
   HGDIOBJ old_font = ::SelectObject(hDC, new_font);

   psiz->cx = 0;
   psiz->cy = 0;
   *pline_hgt = 0;

   // max width
   IndexType siz = labels.size();
   for (IndexType i=0; i<siz; i++)
   {
      SIZE tsiz;
      ::GetTextExtentPoint32(hDC,labels[i].c_str(), (int)labels[i].size(), &tsiz);

      psiz->cx = max(psiz->cx, tsiz.cx);
   }

   // get height from text metrics
   if (siz>0)
   {
      TEXTMETRIC tm;
      GetTextMetrics(hDC, &tm);
      *pline_hgt = tm.tmHeight + tm.tmExternalLeading;
      psiz->cy = *pline_hgt * (LONG)siz;
   }

   ::SelectObject(hDC,old_font);
   ::DeleteObject(new_font);
}