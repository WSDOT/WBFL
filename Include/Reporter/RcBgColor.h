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

#ifndef INCLUDED_REPORTER_rptRcBgColor_H_
#define INCLUDED_REPORTER_rptRcBgColor_H_
#pragma once

#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>

/// Creates a new background color object
#define bgcolor(a)  new rptRcBgColor(rptRiStyle::a)

/// A class to change the background color of the report content stream.
///
/// This class is derived from ReportContent and is to be used for manipulating the background color of the current report content stream.
class REPORTERCLASS rptRcBgColor : public rptReportContent
{
public:
   rptRcBgColor(
      rptRiStyle::FontColor MyColor ///< Color specification
   );

   rptRcBgColor(const rptRcBgColor& rOther);

   virtual ~rptRcBgColor();

   rptRcBgColor& operator=(const rptRcBgColor& rOther);

   /// Creates a clone of this object
   rptReportContent* CreateClone() const;

   /// Accepts a report content visitor and calls VisitRcBgColor(this)
   void Accept( rptRcVisitor& MyVisitor );

   /// Get the color
   rptRiStyle::FontColor GetColor() const;

   /// Set the color
   void SetColor(rptRiStyle::FontColor MyColor);

protected:
   /// Copies the data from rOther to this object
   void MakeCopy(const rptRcBgColor& rOther);

   /// Assigns the data from rOther to this object
   void MakeAssignment(const rptRcBgColor& rOther);

private:
   rptRiStyle::FontColor m_Color;

   rptRcBgColor() = delete;
};

#endif // INCLUDED_REPORTER_rptRcBgColor_H_
