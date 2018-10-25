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

#ifndef INCLUDED_REPORTER_REPORTER_H_
#define INCLUDED_REPORTER_REPORTER_H_
#pragma once

// This is a master include file for the Reporting Package
#if defined(BUILDREPORTERLIB)
	#error Do not use this header file in the Reporting Package
   #error It is for external users only
#endif

#include <Reporter\Report.h>
#include <Reporter\ReportExT.h>
#include <Reporter\ReportingUtils.h>
#include <Reporter\Chapter.h>
#include <Reporter\Paragraph.h>
#include <Reporter\RcFlowModifier.h>
#include <Reporter\RcFontModifier.h>
#include <Reporter\RcColor.h>
#include <Reporter\RcHyperTarget.h>
#include <Reporter\RcInt.h>
#include <Reporter\RcScalar.h>
#include <Reporter\RcSectionScalar.h>
#include <Reporter\RcSectionValue.h>
#include <Reporter\RcSectionValueT.h>
#include <Reporter\RcStation.h>
#include <Reporter\RcString.h>
#include <Reporter\RcSymbol.h>
#include <Reporter\RcTable.h>
#include <Reporter\RcUnitTag.h>
#include <Reporter\RcUnitTagT.h>
#include <Reporter\RcUnitValue.h>
#include <Reporter\RcUnitValueT.h>
#include <Reporter\RcUnsigned.h>
#include <Reporter\RcImage.h>
#include <Reporter\RcDateTime.h>
#include <Reporter\PageLayout.h>
#include <Reporter\HtmlReportVisitor.h>
#include <Reporter\FormattedLengthUnitValue.h>
#include <Reporter\ReportingUtils.h>

#endif // INCLUDED_REPORTER_REPORTER_H_