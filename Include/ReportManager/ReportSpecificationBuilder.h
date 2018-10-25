///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
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

// ReportSpecificationBuilder.h: interface for the CReportSpecificationBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTSPECIFICATIONBUILDER_H__61D4A42A_E3A2_417F_AFAA_A62C9E163716__INCLUDED_)
#define AFX_REPORTSPECIFICATIONBUILDER_H__61D4A42A_E3A2_417F_AFAA_A62C9E163716__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ReportManager\ReportManagerExp.h>
#include <ReportManager\ReportSpecification.h>
#include <ReportManager\ReportDescription.h>
#include <boost\shared_ptr.hpp>

class REPORTMANAGERCLASS CReportSpecificationBuilder  
{
public:
	CReportSpecificationBuilder();
	virtual ~CReportSpecificationBuilder();

   // the second parameter is a previously created report specification that can be used
   // to initialize the user interface when editing 
   virtual boost::shared_ptr<CReportSpecification> CreateReportSpec(const CReportDescription& rptDesc,
                                                                    boost::shared_ptr<CReportSpecification>& pRptSpec);
   virtual boost::shared_ptr<CReportSpecification> CreateDefaultReportSpec(const CReportDescription& rptDesc);

protected:
   boost::shared_ptr<CReportSpecification> DoCreateReportSpec(const CReportDescription& rptDesc,const std::vector<CChapterInfo>& vChInfo);
};

#endif // !defined(AFX_REPORTSPECIFICATIONBUILDER_H__61D4A42A_E3A2_417F_AFAA_A62C9E163716__INCLUDED_)
