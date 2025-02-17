///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright � 1999-2025  Washington State Department of Transportation
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

/****************************************************************************
CLASS
   rptChapter
****************************************************************************/



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================


rptChapter::rptChapter() :
m_Name( _T("") ),
m_bEjectPageBefore(false)
{}

rptChapter::rptChapter(const std::_tstring& name) :
m_Name( name ),
m_bEjectPageBefore(false)
{}


rptChapter::rptChapter(const std::_tstring& name,const rptStyleName& rStyleName, 
                       const rptPageLayout& rLayout):
rptReportLayoutItem(rStyleName, rLayout),
m_Name( name ),
m_bEjectPageBefore(false)
{
}

rptChapter::~rptChapter()
{
}

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
   std::shared_ptr<rptParagraph> pp(pPara);
   pp->SetParent( this );
   m_ParagraphVec.push_back( pp );
}

void rptChapter::Accept( rptChapterVisitor& MyVisitor )
{
   MyVisitor.VisitChapter(this);
}

bool rptChapter::GetEjectPageBreakBefore() const
{
   return m_bEjectPageBefore;
}

void rptChapter::SetEjectPageBreakBefore(bool doBreak)
{
   m_bEjectPageBefore = doBreak;
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
      return nullptr;
}

void rptChapter::SetName(LPCTSTR name)
{
   m_Name.assign( name ? name : _T("") );
}

rptChapter::rptChapter(const rptChapter& rOther):
rptReportLayoutItem(rOther)
{
   m_ParagraphVec.clear();

   for(const auto para : rOther.m_ParagraphVec)
   {
      Insert( *para );
      // Using the reference version of Insert because we want a clone
      // to be made.  We can't own the same paragraph as rOther
   }

   m_Name.assign( rOther.GetName() );
}

