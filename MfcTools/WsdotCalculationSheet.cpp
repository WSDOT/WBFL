///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright © 1999-2016  Washington State Department of Transportation
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

/****************************************************************************
CLASS
   WsdotCalculationSheet
****************************************************************************/

#include "stdafx.h"
#include <MfcTools\WsdotCalculationSheet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
WsdotCalculationSheet::WsdotCalculationSheet():
m_Margins(20,10,10,10),
m_MaxSheetNo(1),
m_FontFace("Arial"),
m_PointSize(100)

{
}

WsdotCalculationSheet::WsdotCalculationSheet(const WsdotCalculationSheet& rOther)
{
   MakeCopy(rOther);
}

WsdotCalculationSheet::~WsdotCalculationSheet()
{
}

//======================== OPERATORS  =======================================
WsdotCalculationSheet& WsdotCalculationSheet::operator= (const WsdotCalculationSheet& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

CRect WsdotCalculationSheet::Print(CDC* pDC, Uint32 sheetNumber, bool doPrint)
{
   // we like to work in  LOMETRIC
   int oldmode = pDC->SetMapMode(MM_LOMETRIC);

   // create our fonts
   m_RegFont.CreatePointFont(m_PointSize,m_FontFace,pDC);
   LOGFONT lf;
   m_RegFont.GetLogFont(&lf);
   lf.lfWeight = FW_BOLD;
   m_BoldFont.CreateFontIndirect(&lf);
   m_TitleFont.CreatePointFont(m_PointSize,_T("Arial Black"),pDC);
   // file name font is 2 points smaller
   m_FileNameFont.CreatePointFont(m_PointSize-20,m_FontFace,pDC);

   // calculate placement of page elements
   if (!CalculateMetrics(pDC))
      return CRect();

   if (doPrint)
   {
      // Draw border around page
      LOGBRUSH solid = {BS_SOLID,RGB(0,0,0),0};
      CPen thick(PS_GEOMETRIC,4,&solid);
      CPen* poldpen = pDC->SelectObject(&thick);
      int ytop = m_Border.top - m_LineSpacing*2;
      pDC->MoveTo(m_Border.left, ytop);
      pDC->LineTo(m_Border.left, m_Border.bottom);
      pDC->LineTo(m_Border.right, m_Border.bottom);
      pDC->LineTo(m_Border.right, ytop);
      pDC->LineTo(m_Border.left, ytop);

      CPen thin(PS_GEOMETRIC,1,&solid);
      pDC->SelectObject(&thin);
      ytop -= m_LineSpacing;
      pDC->MoveTo(m_Border.left,  ytop);
      pDC->LineTo(m_Border.right, ytop);
      pDC->SelectObject(&thick);
      ytop -= m_LineSpacing;
      pDC->MoveTo(m_Border.left,  ytop);
      pDC->LineTo(m_Border.right, ytop);
      ytop = m_Border.bottom + m_LineSpacing;
      pDC->MoveTo(m_Border.left,  ytop);
      pDC->LineTo(m_Border.right, ytop);

      // place text
      // Company name
      CFont* poldfont = pDC->SelectObject(&m_TitleFont);
      if (!m_Company.IsEmpty())
         pDC->TextOut(m_CompanyLoc.x, m_CompanyLoc.y, m_Company);

      pDC->SetTextAlign(TA_LEFT|TA_TOP|TA_UPDATECP); // auto update text loc

      // job #
      pDC->SelectObject(&m_BoldFont);
      pDC->MoveTo(m_JobNumberLoc);
      pDC->TextOut(0,0,_T("Job Number: "));
      if(!m_JobNumber.IsEmpty())
      {
         pDC->SelectObject(m_RegFont);
         pDC->TextOut(0,0,m_JobNumber);
      }

      // sheet
      pDC->SelectObject(&m_BoldFont);
      pDC->MoveTo(m_SheetLoc);
      pDC->TextOut(0,0,_T("Sheet "));
      CString tmp;
      tmp.Format(_T("%d"),sheetNumber);
      pDC->SelectObject(m_RegFont);
      pDC->TextOut(0,0,tmp);
      pDC->SelectObject(&m_BoldFont);
      pDC->TextOut(0,0,_T(" of "));
      tmp.Format(_T("%d"),m_MaxSheetNo);
      pDC->SelectObject(m_RegFont);
      pDC->TextOut(0,0,tmp);

      // bridge
      pDC->SelectObject(&m_BoldFont);
      pDC->MoveTo(m_BridgeLoc);
      pDC->TextOut(0,0,_T("Bridge: "));
      if(!m_Bridge.IsEmpty())
      {
         pDC->SelectObject(m_RegFont);
         pDC->TextOut(0,0,m_Bridge);
      }

      // bridge id
      pDC->SelectObject(&m_BoldFont);
      pDC->MoveTo(m_BridgeIdLoc);
      pDC->TextOut(0,0,_T("BridgeId: "));
      if(!m_BridgeId.IsEmpty())
      {
         pDC->SelectObject(m_RegFont);
         pDC->TextOut(0,0,m_BridgeId);
      }

      // Engineer
      pDC->SelectObject(&m_BoldFont);
      pDC->MoveTo(m_EngineerLoc);
      pDC->TextOut(0,0,_T("Engineer: "));
      if(!m_Engineer.IsEmpty())
      {
         pDC->SelectObject(m_RegFont);
         pDC->TextOut(0,0,m_Engineer);
      }

      // Title
      pDC->SelectObject(&m_BoldFont);
      pDC->MoveTo(m_TitleLoc);
      if(!m_Title.IsEmpty())
      {
         pDC->TextOut(0,0,m_Title);
      }

      // date
      pDC->SelectObject(&m_BoldFont);
      pDC->MoveTo(m_DateLoc);
      pDC->TextOut(0,0,_T("Date: "));

      sysTime now;
      now.PrintDate( true );
      CString time(now.AsString().c_str());
      time.TrimRight();
      pDC->SelectObject(m_RegFont);
      pDC->TextOut(0,0,time);

      // file name
      pDC->SelectObject(&m_FileNameFont);
      pDC->MoveTo(m_FileNameLoc);
      if(!m_FileName.IsEmpty())
      {
         pDC->TextOut(0,0,m_FileName);
      }

      // clean up DC
      pDC->SelectObject(poldpen);
      pDC->SelectObject(poldfont);
   }

   // calculate client area
   CRect client(m_Border.left, m_Border.top-4*m_LineSpacing, m_Border.right, m_Border.bottom+m_LineSpacing);
   pDC->LPtoDP(&client);
   pDC->SetMapMode(oldmode);
   return client;
}

//======================== ACCESS     =======================================


void WsdotCalculationSheet::SetTitle(const CString& title)
{
   m_Title = title;
}

CString WsdotCalculationSheet::GetTitle() const
{
   return m_Title;
}

void WsdotCalculationSheet::SetEngineer(const CString& engineer)
{
   m_Engineer = engineer;
}

CString WsdotCalculationSheet::GetEngineer() const
{
   return m_Engineer;
}

void WsdotCalculationSheet::SetCompany(const CString& company)
{
   m_Company = company;
}

CString WsdotCalculationSheet::GetCompany() const
{
   return m_Company;
}


void WsdotCalculationSheet::SetBridgeID(const CString& bridgeId)
{
   m_BridgeId = bridgeId;
}

CString WsdotCalculationSheet::GetBridgeId() const
{
   return m_BridgeId;
}

void WsdotCalculationSheet::SetBridgeName( const CString& bridge)
{
   m_Bridge = bridge;
}

CString WsdotCalculationSheet::GetBridgeName() const
{
   return m_Bridge;
}


void WsdotCalculationSheet::SetJobNumber(const CString& jobNumber)
{
   m_JobNumber = jobNumber;
}

CString WsdotCalculationSheet::GetJobNumber() const
{
   return m_JobNumber;
}

void WsdotCalculationSheet::SetFileName(const CString& FileName)
{
   m_FileName = FileName;
}

CString WsdotCalculationSheet::GetFileName() const
{
   return m_FileName;
}

void WsdotCalculationSheet::SetMargins( const gpRect2d margins)
{
   CHECK(margins.Left()>=0 && margins.Right()>=0 && margins.Top()>=0 && margins.Bottom()>=0 );
   m_Margins = margins;
}

gpRect2d WsdotCalculationSheet::GetMargins() const
{
   return m_Margins;
}

void WsdotCalculationSheet::SetMaxSheetNumber(Uint32 maxSheetNumber)
{
   m_MaxSheetNo = maxSheetNumber;
}

Uint32 WsdotCalculationSheet::GetMaxSheetNumber() const
{
   return m_MaxSheetNo;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void WsdotCalculationSheet::MakeCopy(const WsdotCalculationSheet& rOther)
{
   m_Title = rOther.m_Title;
   m_Engineer = rOther.m_Engineer;
   m_Bridge = rOther.m_Bridge;
   m_BridgeId = rOther.m_BridgeId;
   m_JobNumber = rOther.m_JobNumber;
   m_FileName = rOther.m_FileName;
   m_MaxSheetNo = rOther.m_MaxSheetNo;
   m_Margins = rOther.m_Margins;
   m_FontFace = rOther.m_FontFace;
   m_PointSize = rOther.m_PointSize;
}

void WsdotCalculationSheet::MakeAssignment(const WsdotCalculationSheet& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bool WsdotCalculationSheet::CalculateMetrics(CDC* pDC)
{
   // get horizontal and vertical size of device
   CPoint pnt(pDC->GetDeviceCaps(PHYSICALWIDTH), pDC->GetDeviceCaps(PHYSICALHEIGHT));
   pDC->DPtoLP(&pnt);

   int mmhorz = pnt.x;
   int mmvert = -pnt.y;

   CPoint opnt(pDC->GetDeviceCaps(PHYSICALOFFSETX), pDC->GetDeviceCaps(PHYSICALOFFSETY));
   pDC->DPtoLP(&opnt);

   // don't even try if sheet is too small
   if (mmhorz <2000 || mmvert<2000)
      return false;

   // border:
   m_LineSpacing = 6 * 10; // 6mm line spacing

   m_Border.left   = LONG(m_Margins.Left()*10 - opnt.x);
   m_Border.right  = LONG(mmhorz - m_Margins.Right()*10 - opnt.x);
   m_Border.top    = LONG(-m_Margins.Top()*10 - opnt.y);
   m_Border.bottom = LONG(-mmvert + m_Margins.Bottom()*10 - opnt.y);

   // center company name at top of page
   CFont* oldfont = pDC->SelectObject(&m_TitleFont);
   CSize csiz = pDC->GetTextExtent( m_Company );
   m_CompanyLoc.x = (m_Border.left+m_Border.right)/2 - csiz.cx/2;
   m_CompanyLoc.y = m_Border.top - m_LineSpacing/2;

   m_BridgeLoc.x = m_Border.left + 20;
   m_BridgeLoc.y = m_Border.top - 2*m_LineSpacing - 10;

   m_BridgeIdLoc.x = m_Border.right - 650;
   m_BridgeIdLoc.y = m_BridgeLoc.y;

   m_SheetLoc.x = m_Border.right - 280;
   m_SheetLoc.y = m_BridgeLoc.y;

   m_EngineerLoc.x = m_BridgeLoc.x;
   m_EngineerLoc.y = m_BridgeLoc.y - m_LineSpacing;

   m_JobNumberLoc.x = m_Border.left + 850;  
   m_JobNumberLoc.y = m_EngineerLoc.y;

   m_DateLoc.x = m_BridgeIdLoc.x;
   m_DateLoc.y = m_EngineerLoc.y;

   pDC->SelectObject(&m_BoldFont);
   csiz = pDC->GetTextExtent( m_Title );
   m_TitleLoc.x = (m_Border.left+m_Border.right)/2 - csiz.cx/2;
   m_TitleLoc.y = m_Border.bottom + m_LineSpacing - 10;

   pDC->SelectObject(&m_FileNameFont);
   csiz = pDC->GetTextExtent( "C" );
   m_FileNameLoc.x = m_Border.left + csiz.cx;
   m_FileNameLoc.y = m_Border.bottom + m_LineSpacing + 11*csiz.cy/10;

   pDC->SelectObject(oldfont);
   return true;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
