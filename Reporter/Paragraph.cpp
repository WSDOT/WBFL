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
#include <Reporter\Paragraph.h>
#include <Reporter\RcString.h>
#include <Reporter\RcInt.h>
#include <Reporter\RcUnsigned.h>
#include <Reporter\RcDateTime.h>
#include <Reporter\RcHyperTarget.h>
#include <Reporter\RcSymbol.h>
#include <Reporter\RcScalar.h>

#include <boost\shared_ptr.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptParagraph           
****************************************************************************/



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

rptParagraph::rptParagraph()
{

} // rptParagraph

rptParagraph::rptParagraph(const rptStyleName& rStyleName):
rptReportItem(rStyleName)
{
} // rptParagraph

rptParagraph::rptParagraph(const rptParagraph& rParagraph):
rptReportItem(rParagraph)
{
   MakeCopy(rParagraph);

} // rptParagraph


rptParagraph::~rptParagraph()
{
} // ~rptParagraph

//======================== OPERATORS  =======================================

rptParagraph& rptParagraph::operator = (const rptParagraph& rParagraph)
{
   if(this != &rParagraph)
      MakeAssignment(rParagraph);

   return *this;
} // operator =

rptParagraph& rptParagraph::operator << (const rptReportContent& rContent )
{
   //
   // create a clone and set its parent
   //
   boost::shared_ptr<rptReportContent> rcp( rContent.CreateClone() );
   rcp->SetParent(this);
   m_ContentVec.push_back(rcp);
   return *this;
}

//
// stream a pointer to a rptReportContent object. NOTE that the paragraph
// now becomes responsible for deleting this object
//
rptParagraph& rptParagraph::operator << (rptReportContent* pContent )
{
   boost::shared_ptr<rptReportContent> pc(pContent);
   pc->SetParent(this);
   m_ContentVec.push_back( pc );
   return *this;
}

   
rptParagraph& rptParagraph::operator << (const std::_tstring& str)
{
   boost::shared_ptr<rptReportContent> rcp( new rptRcString(str) );
   rcp->SetParent(this);
   m_ContentVec.push_back( rcp );
   return *this;
}

rptParagraph& rptParagraph::operator << (LPCTSTR str)
{
   boost::shared_ptr<rptReportContent> rcp( new rptRcString(str) );
   rcp->SetParent(this);
   m_ContentVec.push_back( rcp );
   return *this;
}

rptParagraph& rptParagraph::operator<< (Int8 value)
{
   boost::shared_ptr<rptReportContent> rcp(new rptRcString(std::_tstring(1,value)));
   rcp->SetParent(this);
   m_ContentVec.push_back( rcp );
   return *this;
}

rptParagraph& rptParagraph::operator<< (Int16 value)
{
   boost::shared_ptr<rptReportContent> p_rc( new rptRcInt( (Int64)value ) );
   p_rc->SetParent( this );
   m_ContentVec.push_back( p_rc );
   return *this;
}

rptParagraph& rptParagraph::operator<< (Int32 value)
{
   boost::shared_ptr<rptReportContent> p_rc( new rptRcInt( (Int64)value ) );
   p_rc->SetParent( this );
   m_ContentVec.push_back( p_rc );
   return *this;
}

rptParagraph& rptParagraph::operator<< (Int64 value)
{
   boost::shared_ptr<rptReportContent> p_rc( new rptRcInt( (Int64)value ) );
   p_rc->SetParent( this );
   m_ContentVec.push_back( p_rc );
   return *this;
}

rptParagraph& rptParagraph::operator<< (Uint8 value)
{
   boost::shared_ptr<rptReportContent> p_rc(new rptRcUnsigned( (Uint64)value ));
   p_rc->SetParent( this );
   m_ContentVec.push_back( p_rc );
   return *this;
}

rptParagraph& rptParagraph::operator<< (Uint16 value)
{
   boost::shared_ptr<rptReportContent> p_rc( new rptRcUnsigned( (Uint64)value ) );
   p_rc->SetParent( this );
   m_ContentVec.push_back( p_rc );
   return *this;
}

rptParagraph& rptParagraph::operator<< (Uint32 value)
{
   boost::shared_ptr<rptReportContent> p_rc( new rptRcUnsigned( (Uint64)value ) );
   p_rc->SetParent( this );
   m_ContentVec.push_back( p_rc );
   return *this;
}

rptParagraph& rptParagraph::operator<< (Uint64 value)
{
   boost::shared_ptr<rptReportContent> p_rc( new rptRcUnsigned( (Uint64)value ) );
   p_rc->SetParent( this );
   m_ContentVec.push_back( p_rc );
   return *this;
}

rptParagraph& rptParagraph::operator<< (Float32 value)
{
   boost::shared_ptr<rptReportContent> rcp( new rptRcScalar( (Float64)value ) );
   rcp->SetParent(this);
   m_ContentVec.push_back( rcp );
   return *this;
}

rptParagraph& rptParagraph::operator<< (Float64 value)
{
   boost::shared_ptr<rptReportContent> rcp(new rptRcScalar( (Float64)value ));
   rcp->SetParent(this);
   m_ContentVec.push_back( rcp );
   return *this;
}

//======================== OPERATIONS =======================================

void rptParagraph::Accept( rptParagraphVisitor& MyVisitor )
{
   MyVisitor.VisitParagraph(this);
}


rptParagraph* rptParagraph::CreateClone() const
{
   std::auto_ptr<rptParagraph> tmp( new rptParagraph );
   *tmp = *this;
   return tmp.release();
}


void rptParagraph::MakeCopy( const rptParagraph& rParagraph) 
{
   m_Name = rParagraph.m_Name;

   m_ContentVec.clear();

   // copy paragraph's ReportContent
   ConstParagraphContentIterator icv;
   for ( icv  = rParagraph.m_ContentVec.begin(); 
         icv != rParagraph.m_ContentVec.end();
         icv++ )
   {
          boost::shared_ptr<rptReportContent> rc( (*icv)->CreateClone() );
          m_ContentVec.push_back(rc);
   }
}


void rptParagraph::MakeAssignment(const rptParagraph& rOther)
{
   rptReportItem::MakeAssignment(rOther);
   MakeCopy( rOther );
}



//======================== ACCESS     =======================================
LPCTSTR rptParagraph::GetName() const
{
   if (!m_Name.empty())
      return m_Name.c_str();
   else
      return 0;
}

void rptParagraph::SetName(LPCTSTR name)
{
   m_Name.assign( name ? name : _T("") );
}


rptParagraph::ConstParagraphContentIterator rptParagraph::ConstBegin()
{
   return m_ContentVec.begin();
}

rptParagraph::ConstParagraphContentIterator rptParagraph::ConstEnd()
{
   return m_ContentVec.end();
}

rptParagraph::ParagraphContentIterator rptParagraph::Begin()
{
   return m_ContentVec.begin();
}

rptParagraph::ParagraphContentIterator rptParagraph::End()
{
   return m_ContentVec.end();
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
//======================== INQUERY ==========================================

