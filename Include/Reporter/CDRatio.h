///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <Reporter\ReporterExp.h>
#include <Reporter\RcString.h>
#include <Reporter\RcSymbol.h>
#include <System\NumericFormatTool.h>

#define CDR_NA   -1  ///< reports "N/A"
#define CDR_SKIP -2  ///< reports "-"
#define CDR_INF  9999999 ///< reports infinity symbol
#define CDR_LARGE 10 ///< anything larger than this value is reported as 10+

/// Report content for Capacity/Demand ratios
class REPORTERCLASS rptCDRatio : public rptRcString
{
public:
   rptCDRatio();
   rptCDRatio(const rptCDRatio& rOther);

   /// Creates a clone
   virtual rptReportContent* CreateClone() const override;

   /// Returns the report content objects
   virtual rptReportContent& SetValue(
      Float64 cdr, ///< the C/D ratio
      bool passed ///< pass/fail state
   );

   /// Returns the report content
   virtual rptReportContent& SetValue(
      Float64 capacity,  ///< capacity
      Float64 demand,  ///< demand
      bool passed ///< pass/fail state
   );

protected:
   /// Returns the capacity demand ratio as a string
   virtual std::_tstring AsString(Float64 capacity, Float64 demand, bool passed) const;

private:
   static WBFL::System::NumericFormatTool m_FormatTool;
   static rptRcSymbol m_RcSymbolInfinity;
};

/// Macro for reporting passing state of a rating factor
#define RF_PASS(_cd_,_rf_) _cd_.SetValue(_rf_,1.0,true)

/// Macro for reporting failed state of a rating factor
#define RF_FAIL(_cd_,_rf_) color(Red) << _cd_.SetValue(_rf_ < 0 ? 0 : _rf_,0 < _rf_ ? 1 : 0,false) << color(Black)

/// Macro for reporting passing state of a capacity/demand ratio
#define CD_PASS(_cdr_,_cd_) RPT_PASS << rptNewLine << _T("(") << _cdr_.SetValue(_cd_ < 0 ? CDR_SKIP : _cd_,true) << _T(")")

/// Macro for reporting failed state of a capacity/demand ratio
#define CD_FAIL(_cdr_,_cd_) RPT_FAIL << rptNewLine << _T("(") << _cdr_.SetValue(_cd_ < 0 ? CDR_SKIP : _cd_,false) << _T(")")
