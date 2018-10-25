///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#include <Reporter\ReporterLib.h>
#include <Reporter\Chapter.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptChapter
****************************************************************************/



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================


rptChapter::rptChapter() :
m_Name( _T("") ),
m_DoEjectPageBefore(false)
{}

rptChapter::rptChapter(const std::_tstring& name) :
m_Name( name ),
m_DoEjectPageBefore(false)
{}


rptChapter::rptChapter(const std::_tstring& name,const rptStyleName& rStyleName, 
                       const rptPageLayout& rLayout):
rptReportLayoutItem(rStyleName, rLayout),
m_Name( name ),
m_DoEjectPageBefore(false)
{
}


rptChapter::~rptChapter()
{
}


//======================== OPERATORS  =======================================

rptChapter& rptChapter::operator << (const rptParagraph& rParagraph )
{
   Insert( rParagraph );
   return *this;
}


rptChapter& rptChapter::operator << (rptParagraph* pParagraph )
{
   Insert( pParagraph );
   return *this;
}

void rptChapter::Insert(const rptParagraph& rPara)
{
   Insert( rPara.CreateClone() );
}

void rptChapter::Insert(rptParagraph* pPara)
{
   boost::shared_ptr<rptParagraph> pp(pPara);
   pp->SetParent( this );
   m_ParagraphVec.push_back( pp );
}

//======================== OPERATIONS =======================================

void rptChapter::Accept( rptChapterVisitor& MyVisitor )
{

   MyVisitor.VisitChapter(this);
}

//======================== ACCESS     =======================================

bool rptChapter::GetEjectPageBreakBefore() const
{
   return m_DoEjectPageBefore;
}

void rptChapter::SetEjectPageBreakBefore(bool doBreak)
{
   m_DoEjectPageBefore = doBreak;
}

rptChapter::ConstChapterParagraphIterator rptChapter::ConstBegin()
{
   return m_ParagraphVec.begin();
}

rptChapter::ConstChapterParagraphIterator rptChapter::ConstEnd()
{
   return m_ParagraphVec.end();
}

rptChapter::ChapterParagraphIterator rptChapter::Begin()
{
   return m_ParagraphVec.begin();
}

rptChapter::ChapterParagraphIterator rptChapter::End()
{
   return m_ParagraphVec.end();
}

LPCTSTR rptChapter::GetName() const
{
   if (!m_Name.empty())
      return m_Name.c_str();
   else
      return 0;
}

void rptChapter::SetName(LPCTSTR name)
{
   m_Name.assign( name ? name : _T("") );
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptChapter::rptChapter(const rptChapter& rOther):
rptReportLayoutItem(rOther)
{
   m_ParagraphVec.clear();

   ConstChapterParagraphIterator i;
   for ( i  = rOther.m_ParagraphVec.begin();
         i != rOther.m_ParagraphVec.end();
         i++ )
   {
      const boost::shared_ptr<rptParagraph>& p_para = *i;
      Insert( *p_para );
      // Using the reference version of Insert because we want a clone
      // to be made.  We can't own the same paragraph as rOther
   }

   m_Name.assign( rOther.GetName() );
}
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

