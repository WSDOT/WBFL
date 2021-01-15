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
#include <Reporter\ReportContent.h>
#include <Reporter\HyperLinkDefinition.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

rptReportContent::rptReportContent()
{
   // Report Content is not a hyperlink by default
   m_pHyperLink = nullptr;
}

rptReportContent::rptReportContent(const rptReportContent& rReportContent)
{
   m_pHyperLink = 0;
   MakeCopy(rReportContent);

}

rptReportContent::~rptReportContent()
{
   delete m_pHyperLink;
}

rptReportContent& rptReportContent::operator=(const rptReportContent& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

inline bool rptReportContent::IsHyperLink() const
{
   return (m_pHyperLink==0) ? false : true;
}

const std::_tstring& rptReportContent::GetHyperTarget() const
{
   CHECK(m_pHyperLink);
   return m_pHyperLink->GetTargetName();
}

void rptReportContent::SetHyperLink(const std::_tstring& HyperTarget)
{
   if (m_pHyperLink)
      m_pHyperLink->SetTargetName(HyperTarget);
   else
      m_pHyperLink = new rptHyperLinkDefinition(HyperTarget);
}

void rptReportContent::MakeAssignment(const rptReportContent& rOther)
{
   rptReportItem::MakeAssignment( rOther );
   MakeCopy( rOther );
}

void rptReportContent::MakeCopy(const rptReportContent& rContent)
{
   // copy hyperlink data if it exists
   delete m_pHyperLink;
   m_pHyperLink = nullptr;

   if (rContent.m_pHyperLink)
      m_pHyperLink = new rptHyperLinkDefinition( *(rContent.m_pHyperLink) );
}
