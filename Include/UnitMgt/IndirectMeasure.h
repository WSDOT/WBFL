///////////////////////////////////////////////////////////////////////
// UnitMgt - Service for managing display units indirectly
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

#ifndef INCLUDED_UNITMGT_INDIRECTMEASURE_H_
#define INCLUDED_UNITMGT_INDIRECTMEASURE_H_
#pragma once

#include <Units\Units.h>
#include <System\System.h>
#include <UnitMgt\UnitMgtExp.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

template <class T>
class unitmgtIndirectMeasureDataT
{
public:
   unitmgtIndirectMeasureDataT(const T& um,Float64 t = 0.001,Int16 w = 6,Int16 p = 3) :
      UnitOfMeasure(um), Tol(t), Width(w), Precision(p), Format( sysNumericFormatTool::Automatic )
      {
      }

   unitmgtIndirectMeasureDataT(const unitmgtIndirectMeasureDataT& rOther) :
      UnitOfMeasure( rOther.UnitOfMeasure),
      Tol( rOther.Tol ),
      Width( rOther.Width ),
      Precision( rOther.Precision ),
      Format( rOther.Format )
      {
      }
   unitmgtIndirectMeasureDataT& operator=(const unitmgtIndirectMeasureDataT& rOther)
   {
      if ( this != &rOther )
      {
         UnitOfMeasure = rOther.UnitOfMeasure;
         Tol = rOther.Tol;
         Width = rOther.Width;
         Precision = rOther.Precision;
         Format = rOther.Format;
      }

      return *this;
   }

   void Update(const T& um,Float64 t,Int16 w,Int16 p,sysNumericFormatTool::Format f)
   {
      UnitOfMeasure = um;
      Tol           = t;
      Width         = w;
      Precision     = p;
      Format        = f;
   }

   T UnitOfMeasure;
   Float64 Tol;
   Uint16 Width;
   Uint16 Precision;
   sysNumericFormatTool::Format Format;
};

struct unitmgtScalar
{
   Uint16 Width;
   Uint16 Precision;
   sysNumericFormatTool::Format Format;
};

// These templates must be pre-instantiated so that they 
// can be exported
#define DECLARE_INDIRECT_MEASURE_DATA(u,t) \
   UNITMGTTPL unitmgtIndirectMeasureDataT<u>; \
   typedef unitmgtIndirectMeasureDataT<u> t;

DECLARE_INDIRECT_MEASURE_DATA( unitMass,           unitmgtMassData           );
DECLARE_INDIRECT_MEASURE_DATA( unitMassPerLength,  unitmgtMassPerLengthData  );
DECLARE_INDIRECT_MEASURE_DATA( unitLength,         unitmgtLengthData         );
DECLARE_INDIRECT_MEASURE_DATA( unitTime,           unitmgtTimeData           );
DECLARE_INDIRECT_MEASURE_DATA( unitTemperature,    unitmgtTemperatureData    );
DECLARE_INDIRECT_MEASURE_DATA( unitAngle,          unitmgtAngleData          );
DECLARE_INDIRECT_MEASURE_DATA( unitLength2,        unitmgtLength2Data        );
DECLARE_INDIRECT_MEASURE_DATA( unitLength3,        unitmgtLength3Data        );
DECLARE_INDIRECT_MEASURE_DATA( unitLength4,        unitmgtLength4Data        );
DECLARE_INDIRECT_MEASURE_DATA( unitPressure,       unitmgtPressureData       );
DECLARE_INDIRECT_MEASURE_DATA( unitDensity,        unitmgtDensityData        );
DECLARE_INDIRECT_MEASURE_DATA( unitUnitWeight,     unitmgtUnitWeightData     );
DECLARE_INDIRECT_MEASURE_DATA( unitForce,          unitmgtForceData          );
DECLARE_INDIRECT_MEASURE_DATA( unitForcePerLength, unitmgtForcePerLengthData );
DECLARE_INDIRECT_MEASURE_DATA( unitMomentPerAngle, unitmgtMomentPerAngleData );
DECLARE_INDIRECT_MEASURE_DATA( unitMoment,         unitmgtMomentData         );
DECLARE_INDIRECT_MEASURE_DATA( unitPerLength,      unitmgtPerLengthData      );
DECLARE_INDIRECT_MEASURE_DATA( unitForceLength2,   unitmgtForceLength2Data   );
DECLARE_INDIRECT_MEASURE_DATA( unitSqrtPressure,   unitmgtSqrtPressureData   );

typedef unitmgtPressureData unitmgtStressData;
typedef unitmgtLengthData   unitmgtAreaPerLengthData;


/*****************************************************************************
CLASS 
   unitmgtIndirectMeasure

   A POD struct that encapsulates variables for indirect units of measure and
   the zeroness of the units of measure.


DESCRIPTION
   A POD struct that encapsulates variables for indirect units of measure and
   the zeroness of the units of measure.  This class is intended to be used
   as a value for unitmgtLibraryT.


COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 11.09.1997 : Created file
*****************************************************************************/

class UNITMGTCLASS unitmgtIndirectMeasure
{
public:
   // GROUP: DATA MEMBERS
   std::_tstring               Name;

   unitStationFormat         StationFormat; 

   unitmgtScalar             Scalar;

   unitmgtLengthData         ComponentDim;
   unitmgtLengthData         XSectionDim;
   unitmgtLengthData         SpanLength;
   unitmgtLengthData         AlignmentLength;
   unitmgtLengthData         Displacement;
   unitmgtLength2Data        Area;
   unitmgtLength4Data        MomentOfInertia;
   unitmgtLength3Data        SectModulus;
   unitmgtAreaPerLengthData  AvOverS;
   unitmgtPressureData       Stress;
   unitmgtPressureData       SmallStress;
   unitmgtPressureData       ModE;
   unitmgtForceData          GeneralForce;
   unitmgtForceData          Tonnage;
   unitmgtForceData          Shear;
   unitmgtMomentData         Moment;
   unitmgtMomentData         SmallMoment;
   unitmgtAngleData          Angle;
   unitmgtAngleData          RadAngle;
   unitmgtDensityData        Density;
   unitmgtMassPerLengthData  MassPerLength;
   unitmgtForcePerLengthData ForcePerLength;
   unitmgtMomentPerAngleData MomentPerAngle;
   unitmgtTimeData           Time;
   unitmgtTimeData           Time2;
   unitmgtPerLengthData      PerLength;
   unitmgtPerLengthData      Curvature;
   unitmgtForceLength2Data   ForceLength2;
   unitmgtSqrtPressureData   SqrtPressure;

   // GROUP: LIFECYCLE
   unitmgtIndirectMeasure();
   unitmgtIndirectMeasure(const unitmgtIndirectMeasure& rOther);
   ~unitmgtIndirectMeasure();

   // GROUP: OPERATORS
   unitmgtIndirectMeasure& operator= (const unitmgtIndirectMeasure& rOther);

   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   virtual bool AssertValid() const;
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const unitmgtIndirectMeasure& rOther);
   virtual void MakeAssignment(const unitmgtIndirectMeasure& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
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

#endif
