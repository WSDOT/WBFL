///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
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

// TitlePageBuilder.h: interface for the CTitlePageBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TitlePageBuilder_H__A02521C5_E5AB_410C_A5C2_0D76AEDFDCA3__INCLUDED_)
#define AFX_TitlePageBuilder_H__A02521C5_E5AB_410C_A5C2_0D76AEDFDCA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ReportManager\ReportManagerExp.h>
#include <ReportManager\ReportSpecification.h>
#include <ReportManager\ReportHint.h>
#include <Reporter\Chapter.h>

class REPORTMANAGERCLASS CTitlePageBuilder  
{
public:
	CTitlePageBuilder();
	virtual ~CTitlePageBuilder();

   virtual rptChapter* Build(boost::shared_ptr<CReportSpecification>& pRptSpec) = 0;
   virtual bool NeedsUpdate(CReportHint* pHint,boost::shared_ptr<CReportSpecification>& pRptSpec);
};

#endif // !defined(AFX_TitlePageBuilder_H__A02521C5_E5AB_410C_A5C2_0D76AEDFDCA3__INCLUDED_)
