///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

/// Report content for a unit tag.
///
/// This type of report content is useful in table headers where a single unit tag is written for an entire row or column of data.
template <class T>
class rptRcUnitTagT : public rptRcUnitTag
{
public:
   rptRcUnitTagT(const T* pUnitOfMeasure) :
      rptRcUnitTag(),
      m_pUnitOfMeasure( pUnitOfMeasure )
   {
   }

   rptRcUnitTagT(const rptRcUnitTagT& rOther) :
      rptRcUnitTag(),
      m_pUnitOfMeasure( rOther.m_pUnitOfMeasure )
   {
   }

   virtual ~rptRcUnitTagT()
   {
   }

   rptRcUnitTagT& operator=(const rptRcUnitTagT& rOther)
   {
      if ( this != &rOther )
         m_pUnitOfMeasure = rOther.m_pUnitOfMeasure;

      return *this;
   }

   /// Creates a clone
   virtual rptReportContent* CreateClone() const override
   {
      return new rptRcUnitTagT<T>(*this);
   }

   /// Returns the unit tag string
   virtual const std::_tstring& AsString() const override
   {
      return m_pUnitOfMeasure->UnitTag();
   }

private:
   const T* m_pUnitOfMeasure;
};

#define DECLARE_RC_UNIT_TAG(u,t) \
   REPORTERTPL rptRcUnitTagT<u>; \
   typedef rptRcUnitTagT<u> t;

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
