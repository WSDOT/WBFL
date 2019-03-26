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

#ifndef INCLUDED_REPORTER_RCUNITTAGT_H_
#define INCLUDED_REPORTER_RCUNITTAGT_H_
#pragma once

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <Reporter\ReporterExp.h>
#include <Reporter\RcUnitTag.h>
#include <Units\PhysicalT.h>

#if defined BUILDREPORTERLIB
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif // BUILDREPORTERLIB

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRcUnitTagT

   Report content for a unit tag.


DESCRIPTION
   Report content for a unit tag.  This type of report content is useful in
   table headers where a single unit tag is written for an entire row or
   column of data.

LOG
   rab : 11.12.1997 : Created file
*****************************************************************************/

template <class T>
class rptRcUnitTagT : public rptRcUnitTag
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptRcUnitTagT(const T* pUnitOfMeasure) :
      rptRcUnitTag(),
      m_pUnitOfMeasure( pUnitOfMeasure )
   {
   }

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcUnitTagT(const rptRcUnitTagT& rOther) :
      rptRcUnitTag(),
      m_pUnitOfMeasure( rOther.m_pUnitOfMeasure )
   {
   }

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcUnitTagT()
   {
   }

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rptRcUnitTagT& operator = (const rptRcUnitTagT& rOther)
   {
      if ( this != &rOther )
         m_pUnitOfMeasure = rOther.m_pUnitOfMeasure;

      return *this;
   }

   // GROUP: OPERATIONS


   //------------------------------------------------------------------------
   // Make a virtual copy
   virtual rptReportContent* CreateClone() const
   {
      return new rptRcUnitTagT<T>(*this);
   }

   //------------------------------------------------------------------------
   virtual std::_tstring AsString() const
   {
      return m_pUnitOfMeasure->UnitTag();
   }

   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const
   {
      return rptRcUnitTag::AssertValid() && m_pUnitOfMeasure != 0;
   }

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const
   {
      rptRcUnitTag::Dump( os );
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
   const T* m_pUnitOfMeasure;

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

#define DECLARE_RC_UNIT_TAG(u,t) \
   REPORTERTPL rptRcUnitTagT<u>; \
   typedef rptRcUnitTagT<u> t;

//#pragma warning( disable : 4231 ) 
DECLARE_RC_UNIT_TAG( unitMass,           rptMassUnitTag           );
DECLARE_RC_UNIT_TAG( unitMassPerLength,  rptMassPerLengthUnitTag  );
DECLARE_RC_UNIT_TAG( unitLength,         rptLengthUnitTag         );
DECLARE_RC_UNIT_TAG( unitTime,           rptTimeUnitTag           );
DECLARE_RC_UNIT_TAG( unitTemperature,    rptTemperatureUnitTag    );
DECLARE_RC_UNIT_TAG( unitAngle,          rptAngleUnitTag          );
DECLARE_RC_UNIT_TAG( unitLength2,        rptLength2UnitTag        );
DECLARE_RC_UNIT_TAG( unitLength3,        rptLength3UnitTag        );
DECLARE_RC_UNIT_TAG( unitLength4,        rptLength4UnitTag        );
DECLARE_RC_UNIT_TAG( unitPressure,       rptPressureUnitTag       );
DECLARE_RC_UNIT_TAG( unitDensity,        rptDensityUnitTag        );
DECLARE_RC_UNIT_TAG( unitForce,          rptForceUnitTag          );
DECLARE_RC_UNIT_TAG( unitForcePerLength, rptForcePerLengthUnitTag );
DECLARE_RC_UNIT_TAG( unitMomentPerAngle, rptMomentPerAngleUnitTag );
DECLARE_RC_UNIT_TAG( unitMoment,         rptMomentUnitTag         );
DECLARE_RC_UNIT_TAG( unitPerLength,      rptPerLengthUnitTag      );

typedef rptPressureUnitTag rptStressUnitTag;
typedef rptLength2UnitTag  rptAreaUnitTag;
typedef rptLength3UnitTag  rptVolumeUnitTag;
typedef rptLengthUnitTag   rptAreaPerLengthUnitTag;

#endif // INCLUDED_REPORTER_RCUNITTAGT_H_
