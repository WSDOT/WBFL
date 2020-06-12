///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2020  Washington State Department of Transportation
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
#include <Reporter\RcComposite.h>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptRcComposite           
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

// constructors
// non-hyperlink versions
rptRcComposite::rptRcComposite()
{
}

rptRcComposite::rptRcComposite(int count, ...)
{
   va_list args;
   va_start(args, count);
   for (int i = 0; i < count; i++)
   {
      rptReportContent* pRptContent = va_arg(args, rptReportContent*);
      AddContent(pRptContent);
   }
   va_end(args);
}

rptRcComposite::ConstContentIterator rptRcComposite::ConstBegin() const
{
   return m_ContentVec.cbegin();
}

rptRcComposite::ConstContentIterator rptRcComposite::ConstEnd() const
{
   return m_ContentVec.cend();
}

rptRcComposite::ContentIterator rptRcComposite::Begin()
{
   return m_ContentVec.begin();
}

rptRcComposite::ContentIterator rptRcComposite::End()
{
   return m_ContentVec.end();
}

// copy constructor
rptRcComposite::rptRcComposite(const rptRcComposite& rRcComposite):
rptReportContent(rRcComposite)
{
   MakeCopy( rRcComposite );

} // rptRcComposite


// destructor
rptRcComposite::~rptRcComposite()
{
} // ~rptRcComposite

//======================== OPERATORS  =======================================

rptRcComposite& rptRcComposite::operator = (const rptRcComposite& rRcComposite)
{
   if (this != &rRcComposite)
      MakeAssignment(rRcComposite);
   return *this;
} // operator =


//======================== OPERATIONS =======================================
rptReportContent* rptRcComposite::CreateClone() const 
{ 
   return new rptRcComposite(*this); 
}

void rptRcComposite::Accept( rptRcVisitor& MyVisitor )
{
   MyVisitor.VisitRcComposite(this);
}

void rptRcComposite::AddContent(const rptReportContent & rContent)
{
   std::shared_ptr<rptReportContent> rcp( rContent.CreateClone() );
   m_ContentVec.push_back(rcp);
}

void rptRcComposite::AddContent(rptReportContent * PContent)
{
   std::shared_ptr<rptReportContent> rcp( PContent );
   m_ContentVec.push_back(rcp);
}

bool rptRcComposite::Empty()
{
   return m_ContentVec.empty();
}

size_t rptRcComposite::Count()
{
   return m_ContentVec.size();
}

void rptRcComposite::ClearContents()
{
   m_ContentVec.clear();
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void rptRcComposite::MakeCopy(const rptRcComposite& rRcComposite)
{
   // deep copy
   m_ContentVec.clear();

   ConstContentIterator it = rRcComposite.ConstBegin();
   while (it != rRcComposite.ConstEnd())
   {
      this->AddContent(**it);

      it++;
   }


}


void rptRcComposite::MakeAssignment(const rptRcComposite& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY ==========================================

