///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include "stdafx.h"
#include <EAF\BrokerReportSpecificationBuilder.h>
#include <EAF\BrokerReportSpecification.h>

using namespace WBFL::EAF;

BrokerReportSpecificationBuilder::BrokerReportSpecificationBuilder(std::weak_ptr<WBFL::EAF::Broker> pBroker)
{
   m_pBroker = pBroker;
}

std::shared_ptr<WBFL::Reporting::ReportSpecification> BrokerReportSpecificationBuilder::CreateReportSpec(const WBFL::Reporting::ReportDescription& rptDesc, std::shared_ptr<WBFL::Reporting::ReportSpecification> pRptSpec) const
{
   // create a regular report spec using the base class implementation... that way we get to use the UI
   auto pReportSpec = WBFL::Reporting::ReportSpecificationBuilder::CreateReportSpec(rptDesc,pRptSpec);
   if ( pReportSpec == nullptr )
   {
      return pReportSpec;
   }

   // create a new report spec of our type
   std::shared_ptr<WBFL::Reporting::ReportSpecification> pEAFRptSpec(std::make_shared<BrokerReportSpecification>(rptDesc.GetReportName(), m_pBroker));

   // copy the data from the regular report spec to our report spec
   pEAFRptSpec->SetReportName(pReportSpec->GetReportName().c_str());
   pEAFRptSpec->SetChapterInfo(pReportSpec->GetChapterInfo());
   pEAFRptSpec->SetLeftHeader(pReportSpec->GetLeftHeader().c_str());
   pEAFRptSpec->SetCenterHeader(pReportSpec->GetCenterHeader().c_str());
   pEAFRptSpec->SetLeftFooter(pReportSpec->GetLeftFooter().c_str());
   pEAFRptSpec->SetCenterFooter(pReportSpec->GetCenterFooter().c_str());

   return pEAFRptSpec;
}

std::shared_ptr<WBFL::Reporting::ReportSpecification> BrokerReportSpecificationBuilder::CreateDefaultReportSpec(const WBFL::Reporting::ReportDescription& rptDesc) const
{
   // Use all chapters at the maximum level
   std::shared_ptr<WBFL::Reporting::ReportSpecification> pRptSpec( std::make_shared<BrokerReportSpecification>(rptDesc.GetReportName(),m_pBroker) );

   rptDesc.ConfigureReportSpecification(pRptSpec);

   return pRptSpec;
}