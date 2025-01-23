///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#ifndef INCLUDED_REPORTER_RCSTATION_H_
#define INCLUDED_REPORTER_RCSTATION_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Units\StationFormat.h>

/// Report content for stations.
class REPORTERCLASS rptRcStation : public rptReportContent
{
public:
   rptRcStation(
      Float64 station, ///< Station value
      const WBFL::Units::StationFormat* pFormat ///< Object used for unit conversion and formatting the value into a station string (e.g. 125+34.33)
   );

   rptRcStation(const rptRcStation& rOther);
   virtual ~rptRcStation();

   rptRcStation& operator=(const rptRcStation& rOther);

    /// Accepts a visitor and calls VisitRcStation(this)
   virtual void Accept( rptRcVisitor& rVisitor ) override;

   /// Creates a clone
   virtual rptReportContent* CreateClone() const override;

   /// Sets the station value and returns a reference to this
   rptReportContent& SetStation(Float64 station);

   /// Returns the station value
   Float64 GetStation(
      bool bConvert = false ///< If true, the returned value is converted into the specified unit of measure
   ) const;

   /// Returns the station as a formatted text string
   std::_tstring AsString() const;


protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRcStation& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptRcStation& rOther);

private:
   rptRcStation() = delete;
   Float64 m_Station;
   const WBFL::Units::StationFormat* m_pFormat;
};

#endif // INCLUDED_REPORTER_RCSTATION_H_
