///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#include <Reporter\ReporterLib.h>
#include <Reporter\Report.h>        // class implementation
#include <Reporter\PageLayout.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptReport
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================


rptReport::rptReport(const std::_tstring& rReportName):
rptReportLayoutItem(_T("Default"), rptPageLayout())
{
   m_ReportName = rReportName;
}


rptReport::rptReport(const std::_tstring& rReportName,
                     const rptStyleName& rStyleName,
                     const rptPageLayout& rLayout):
rptReportLayoutItem(rStyleName, rLayout)
{
   m_ReportName = rReportName;
}


rptReport::~rptReport()
{
}


//======================== OPERATORS  =======================================

rptReport& rptReport::operator << (rptChapter* pChapter )
{
   boost::shared_ptr<rptChapter> pc ( pChapter );
   pc->SetParent( this );
   m_ChapterVec.push_back( pc );
   return *this;
}

bool rptReport::InsertChapterAt(ChapterListSizeType location, rptChapter* pChapter )
{
   if (0 <= location && location < m_ChapterVec.size())
   {
      boost::shared_ptr<rptChapter> pc ( pChapter );
      pc->SetParent( this );

      ChapterListIterator it( m_ChapterVec.begin() );
      m_ChapterVec.insert(it+location, pc );

      return true;
   }
   else
   {
      return false;
   }
}

rptReport::ChapterListSizeType rptReport::GetChapterCount() const
{
   return m_ChapterVec.size();
}


//======================== OPERATIONS =======================================


void rptReport::Accept( rptReportVisitor& MyVisitor )
{
   MyVisitor.VisitReport(this);
}



//======================== ACCESS     =======================================

rptReport::ConstChapterListIterator rptReport::ConstBegin()
{
   return m_ChapterVec.begin();
}

rptReport::ConstChapterListIterator rptReport::ConstEnd()
{
   return m_ChapterVec.end();
}

rptReport::ChapterListIterator rptReport::Begin()
{
   return m_ChapterVec.begin();
}

rptReport::ChapterListIterator rptReport::End()
{
   return m_ChapterVec.end();
}

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

