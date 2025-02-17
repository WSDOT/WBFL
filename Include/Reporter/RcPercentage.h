///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright � 1999-2025  Washington State Department of Transportation
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
#include <Reporter\RcScalar.h>
#include <System\NumericFormatTool.h>
#include <string>

/// Report content for a percentage value.
class REPORTERCLASS rptRcPercentage : public rptRcScalar
{
public:
   rptRcPercentage();

   rptRcPercentage(Float64 value);

   rptRcPercentage(const rptRcPercentage& rOther);

   virtual ~rptRcPercentage();

   /// Accepts a visitor and calls VisitRcPercentage(this)
   virtual void Accept( rptRcVisitor& rVisitor ) override;

   /// Creates a clone
   virtual rptReportContent* CreateClone() const override;

   /// Returns the value as a text string
   ///
   /// The value is multiplied by 100 and "%" is appended to the string
   virtual std::_tstring AsString() const override;
};
