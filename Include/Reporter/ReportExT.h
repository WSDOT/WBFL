///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#ifndef INCLUDED_REPORTER_REPORTEXT_H_
#define INCLUDED_REPORTER_REPORTEXT_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Reporter\ReporterExp.h>
#include <Reporter\Report.h>
#include <UnitMgt\IndirectMeasure.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

#define RPT_STATIONFORMAT(rpt) &(rpt)->GetUnitsOfMeasure().StationFormat

#define RPT_SHORTLENGTH(rpt) &(rpt)->GetUnitsOfMeasure().ShortLength
#define RPT_REGLENGTH(rpt)   &(rpt)->GetUnitsOfMeasure().RegLength
#define RPT_LONGLENGTH(rpt)  &(rpt)->GetUnitsOfMeasure().LongLength

#define RPT_REGAREA(rpt)     &(rpt)->GetUnitsOfMeasure().RegArea
#define RPT_BIGAREA(rpt)     &(rpt)->GetUnitsOfMeasure().BigArea

#define RPT_REGVOLUME(rpt)   &(rpt)->GetUnitsOfMeasure().RegVolume
#define RPT_BIGVOLUME(rpt)   &(rpt)->GetUnitsOfMeasure().BigVolume

#define RPT_MOMINERTIA(rpt)  &(rpt)->GetUnitsOfMeasure().MomInertia

#define RPT_REGFORCE(rpt)    &(rpt)->GetUnitsOfMeasure().RegForce
#define RPT_BIGFORCE(rpt)    &(rpt)->GetUnitsOfMeasure().BigForce

#define RPT_REGMOMENT(rpt)   &(rpt)->GetUnitsOfMeasure().RegMoment
#define RPT_BIGMOMENT(rpt)   &(rpt)->GetUnitsOfMeasure().BigMoment

#define RPT_REGSTRESS(rpt)   &(rpt)->GetUnitsOfMeasure().RegStress
#define RPT_BIGSTRESS(rpt)   &(rpt)->GetUnitsOfMeasure().BigStress


#define RPT_SHORTLENGTHTOL(rpt) (rpt)->GetUnitsOfMeasure().ShortLengthTol
#define RPT_REGLENGTHTOL(rpt)   (rpt)->GetUnitsOfMeasure().RegLengthTol
#define RPT_LONGLENGTHTOL(rpt)  (rpt)->GetUnitsOfMeasure().LongLengthTol

#define RPT_REGAREATOL(rpt)     (rpt)->GetUnitsOfMeasure().RegAreaTol
#define RPT_BIGAREATOL(rpt)     (rpt)->GetUnitsOfMeasure().BigAreaTol

#define RPT_REGVOLUMETOL(rpt)   (rpt)->GetUnitsOfMeasure().RegVolumeTol
#define RPT_BIGVOLUMETOL(rpt)   (rpt)->GetUnitsOfMeasure().BigVolumeTol

#define RPT_MOMINERTIATOL(rpt)  (rpt)->GetUnitsOfMeasure().MomInertiaTol

#define RPT_REGFORCETOL(rpt)    (rpt)->GetUnitsOfMeasure().RegForceTol
#define RPT_BIGFORCETOL(rpt)    (rpt)->GetUnitsOfMeasure().BigForceTol

#define RPT_REGMOMENTTOL(rpt)   (rpt)->GetUnitsOfMeasure().RegMomentTol
#define RPT_BIGMOMENTTOL(rpt)   (rpt)->GetUnitsOfMeasure().BigMomentTol

#define RPT_REGSTRESSTOL(rpt)   (rpt)->GetUnitsOfMeasure().RegStressTol
#define RPT_BIGSTRESSTOL(rpt)   (rpt)->GetUnitsOfMeasure().BigStressTol

/*****************************************************************************
CLASS 
   rptReportExT

   This is a template class that provides a storage area, of type T, for
   indirect units of measure.


DESCRIPTION
   Derived from rptReport, this is an extended report class.  This is a
   template class that provides a storage area, of type T, for indirect units
   of measure.

LOG
   rab : 11.13.1997 : Created file
*****************************************************************************/

template <class T>
class rptReportExT : public rptReport
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Report with fully defined style and page layout.
   rptReportExT(const std::_tstring& rReportName = _T("")) :
      rptReport(rReportName)
      {
      }

   //------------------------------------------------------------------------
   rptReportExT(const std::_tstring& rReportName,
                const rptStyleName& rStyleName,
                const rptPageLayout& rLayout) :
   rptReport( rReportName, rStyleName, rLayout )
   {
   }

   //------------------------------------------------------------------------
   rptReportExT(const rptReportExT& rOther) :
      rptReport(),
      m_UnitsOfMeasure( rOther.m_UnitsOfMeasure )
   {
   }

   //------------------------------------------------------------------------
   rptReportExT(const T& unitsOfMeasure) :
      rptReport(),
      m_UnitsOfMeasure( unitsOfMeasure )
      {
      }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptReportExT()
   {
   }

   // GROUP: OPERATORS

   //------------------------------------------------------------------------
   rptReportExT& operator=(const rptReportExT& rOther)
   {
      if ( this != &rOther )
         m_UnitsOfMeasure = rOther.m_UnitsOfMeasure;

      return *this;
   }

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the units of measure for this report.
   void SetUnitsOfMeasure(const T& unitsOfMeasure)
   {
      m_UnitsOfMeasure = unitsOfMeasure;
   }

   //------------------------------------------------------------------------
   // Returns the units of measure for this report.
   const T& GetUnitsOfMeasure() const
   {
      return m_UnitsOfMeasure;
   }


   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const
   {
      return true;
   }

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const
   {
   }
#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   T m_UnitsOfMeasure;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

//#pragma warning( disable : 4231 ) 
REPORTERTPL rptReportExT<unitmgtIndirectMeasure>;
typedef rptReportExT<unitmgtIndirectMeasure> rptReportEx;


#endif // INCLUDED_REPORTER_REPORTEXT_H_
