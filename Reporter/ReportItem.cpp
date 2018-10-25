///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2010  Washington State Department of Transportation
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
#include <Reporter\ReportItem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptReportItem           
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

rptReportItem::rptReportItem()
{
   m_pParent = 0;
   m_pStyleName  = 0;

} // rptReportItem


rptReportItem::rptReportItem(const rptStyleName& rStyleName)
{
   m_pParent = 0;
   m_pStyleName = new rptStyleName( rStyleName );

} // rptReportItem


rptReportItem::rptReportItem(const rptReportItem& rOther)
{
   m_pParent = 0;
   m_pStyleName  = 0;
   MakeCopy( rOther );
} // rptReportItem

rptReportItem::~rptReportItem()
{
   ClearStyle();
} // ~rptReportItem

//======================== OPERATORS  =======================================

rptReportItem& rptReportItem::operator = (const rptReportItem& rOther)
{
   if ( &rOther != this )
      MakeAssignment( rOther );

   return *this;
} // operator =

//======================== OPERATIONS =======================================
void rptReportItem::SetParent( rptReportItem* pParent)
{
   CHECKX(m_pParent==0,_T("Bad style to set parent while another exists"));
   CHECKX(pParent,_T("Don't set parent to null pointer - use Clear instead"));
   m_pParent = pParent;
}


void rptReportItem::SetStyleName( const rptStyleName& rStyleName)
{
   ClearStyle();
   
   m_pStyleName = new rptStyleName(rStyleName);
}

void rptReportItem::ClearStyle()
{
   if(m_pStyleName)
      delete m_pStyleName;
   
   m_pStyleName = 0;
}

rptStyleName rptReportItem::GetStyleName() const
{
   if ( m_pStyleName )
   {
      return *m_pStyleName;
   }
   else
   {
      // no style locally - ask parent.

      rptReportItem* myp = GetpParent();
      CHECKX(myp,_T("Child must have parent to get style"));

      return  myp->GetStyleName();
   }
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rptReportItem::MakeCopy(const rptReportItem& rItem)
{
   // copy parents' pointer
   m_pParent = rItem.m_pParent;

   //
   // styles get copied

   ClearStyle();
   if( rItem.m_pStyleName != NULL)
      m_pStyleName = new rptStyleName( *rItem.m_pStyleName );
   else
      m_pStyleName = 0;
}


void rptReportItem::MakeAssignment(const rptReportItem& rOther)
{
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

