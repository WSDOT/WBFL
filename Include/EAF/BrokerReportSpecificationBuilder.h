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

#pragma once

#include <EAF\EAFExp.h>
#include <ReportManager\ReportManager.h>
#include <EAF\Broker.h>

namespace WBFL
{
   namespace EAF
   {
      class EAFCLASS BrokerReportSpecificationBuilder :
         public WBFL::Reporting::ReportSpecificationBuilder
      {
      public:
         BrokerReportSpecificationBuilder(std::weak_ptr<WBFL::EAF::Broker> pBroker);
         ~BrokerReportSpecificationBuilder() = default;
         
         inline std::shared_ptr<WBFL::EAF::Broker> GetBroker() const { return m_pBroker.lock(); }

         virtual std::shared_ptr<WBFL::Reporting::ReportSpecification> CreateReportSpec(const WBFL::Reporting::ReportDescription& rptDesc, std::shared_ptr<WBFL::Reporting::ReportSpecification> pRptSpec) const override;
         virtual std::shared_ptr<WBFL::Reporting::ReportSpecification> CreateDefaultReportSpec(const WBFL::Reporting::ReportDescription& rptDesc) const override;


      protected:
         std::weak_ptr<WBFL::EAF::Broker> m_pBroker;
      };
   };
};
