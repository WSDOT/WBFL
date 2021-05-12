///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_RCVISITOR_H_
#define INCLUDED_REPORTER_RCVISITOR_H_
#pragma once

#include <Reporter\ReporterExp.h>

class REPORTERCLASS rptRcTable;
class REPORTERCLASS rptRcString;
class REPORTERCLASS rptRcStringLiteral;
class REPORTERCLASS rptRcFlowModifier;
class REPORTERCLASS rptRcInt;
class REPORTERCLASS rptRcUnsigned;
class REPORTERCLASS rptRcFontModifier;
class REPORTERCLASS rptRcColor;
class REPORTERCLASS rptRcBgColor;
class REPORTERCLASS rptParagraph;
class REPORTERCLASS rptRcDateTime;
class REPORTERCLASS rptRcHyperTarget;
class REPORTERCLASS rptRcImage;
class REPORTERCLASS rptRcSymbol;
class REPORTERCLASS rptRcScalar;
class REPORTERCLASS rptRcPercentage;
class REPORTERCLASS rptRcUnitTag;
class REPORTERCLASS rptRcUnitValue;
class REPORTERCLASS rptRcSectionValue;
class REPORTERCLASS rptRcSectionScalar;
class REPORTERCLASS rptRcStation;
class REPORTERCLASS rptRcComposite;

/// Abstract class to visit all ReportContent objects in a report. 
class REPORTERCLASS rptRcVisitor
{
public:
   rptRcVisitor();

   virtual ~rptRcVisitor();

   virtual void VisitRcTable(rptRcTable*) = 0;
   virtual void VisitRcString(rptRcString*) = 0;
   virtual void VisitRcStringLiteral(rptRcStringLiteral*) = 0;
   virtual void VisitRcInt(rptRcInt*) = 0;
   virtual void VisitRcUnsigned(rptRcUnsigned*) = 0;
   virtual void VisitRcFlowModifier(rptRcFlowModifier*) = 0;
   virtual void VisitRcFontModifier(rptRcFontModifier*) = 0;
   virtual void VisitRcColor(rptRcColor*) = 0;
   virtual void VisitRcBgColor(rptRcBgColor*) = 0;
   virtual void VisitRcDateTime(rptRcDateTime*) = 0;
   virtual void VisitRcHyperTarget(rptRcHyperTarget*) = 0;
   virtual void VisitRcImage(rptRcImage*) = 0;
   virtual void VisitRcSymbol(rptRcSymbol*) = 0;
   virtual void VisitRcScalar(rptRcScalar*) = 0;
   virtual void VisitRcPercentage(rptRcPercentage*) = 0;
   virtual void VisitRcUnitTag(rptRcUnitTag*) = 0;
   virtual void VisitRcUnitValue(rptRcUnitValue*) = 0;
   virtual void VisitRcSectionValue(rptRcSectionValue*) = 0;
   virtual void VisitRcSectionScalar(rptRcSectionScalar*) = 0;
   virtual void VisitRcStation(rptRcStation*) = 0;
   virtual void VisitRcComposite(rptRcComposite*) = 0;

private:
   rptRcVisitor(const rptRcVisitor&) = delete;
   rptRcVisitor& operator=(const rptRcVisitor&) = delete;
};

#endif // INCLUDED_REPORTER_RCVISITOR_H_
