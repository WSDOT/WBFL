///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
// Copyright © 1999-2019  Washington State Department of Transportation
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

// ReportSpecificationBuilder.cpp: implementation of the CReportSpecificationBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportManager.h"
#include <ReportManager\ReportSpecificationBuilder.h>
#include "ReportSpecDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportSpecificationBuilder::CReportSpecificationBuilder()
{

}

CReportSpecificationBuilder::~CReportSpecificationBuilder()
{

}

std::shared_ptr<CReportSpecification> CReportSpecificationBuilder::CreateReportSpec(const CReportDescription& rptDesc, std::shared_ptr<CReportSpecification>& pRptSpec)
{
   if ( 0 < rptDesc.GetChapterCount() )
   {
      AFX_MANAGE_STATE(AfxGetStaticModuleState());
      CReportSpecDlg dlg(&rptDesc,pRptSpec);
      if ( dlg.DoModal() == IDOK )
      {
         return DoCreateReportSpec(rptDesc,dlg.m_ChapterList);
      }
      else
      {
         return nullptr;
      }
   }
   else
   {
      return DoCreateReportSpec(rptDesc,rptDesc.GetChapterInfo());
   }
}

std::shared_ptr<CReportSpecification> CReportSpecificationBuilder::CreateDefaultReportSpec(const CReportDescription& rptDesc)
{
   std::vector<CChapterInfo> vChInfo = rptDesc.GetChapterInfo();
   return DoCreateReportSpec(rptDesc,vChInfo);
}

std::shared_ptr<CReportSpecification> CReportSpecificationBuilder::DoCreateReportSpec(const CReportDescription& rptDesc,const std::vector<CChapterInfo>& vChInfo)
{
   std::shared_ptr<CReportSpecification> pRptSpec( std::make_shared<CReportSpecification>(rptDesc.GetReportName()) );
   rptDesc.ConfigureReportSpecification(vChInfo,pRptSpec);
   return pRptSpec;
}

std::shared_ptr<CReportSpecification> CReportSpecificationBuilder::DoCreateReportSpec(const CReportDescription& rptDesc,const std::vector<std::_tstring>& vChList)
{
   std::shared_ptr<CReportSpecification> pRptSpec( std::make_shared<CReportSpecification>(rptDesc.GetReportName()) );
   rptDesc.ConfigureReportSpecification(vChList,pRptSpec);
   return pRptSpec;
}
