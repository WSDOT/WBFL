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

#ifndef INCLUDED_REPORTER_RCCOLOR_H_
#define INCLUDED_REPORTER_RCCOLOR_H_
#pragma once

#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>


/// Creates a new foreground color object
#define color(a)  new rptRcColor(rptRiStyle::a)

/// A class to change the color of the report content stream.
///
/// This class is derived from ReportContent and is to be used for manipulating the foreground color of the current report content stream.
class REPORTERCLASS rptRcColor : public rptReportContent
{
public:
   rptRcColor(
      rptRiStyle::FontColor MyColor ///< The color specification
   );

   rptRcColor(const rptRcColor& rOther);

   virtual ~rptRcColor();

   rptRcColor& operator=(const rptRcColor& rOther);

   /// Creates a clone
   rptReportContent* CreateClone() const;

   /// Accepts a visitor and calls VisitRcColor(this)
   void Accept( rptRcVisitor& MyVisitor );

   /// Get the color
   rptRiStyle::FontColor GetFontColor() const;

   /// Set the color
   void SetFontColor(rptRiStyle::FontColor MyColor);

protected:
   /// Copies the data from rOther to this object
   void MakeCopy(const rptRcColor& rOther);

   /// Assigns the data from rOther to this object
   void MakeAssignment(const rptRcColor& rOther);


private:
   rptRiStyle::FontColor m_Color;

   rptRcColor() = delete;
};

#endif // INCLUDED_REPORTER_RCCOLOR_H_
