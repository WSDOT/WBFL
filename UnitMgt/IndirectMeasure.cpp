///////////////////////////////////////////////////////////////////////
// UnitMgt - Service for managing display units indirectly
// Copyright © 1999-2016  Washington State Department of Transportation
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

#include <UnitMgt\UnitMgtLib.h>
#include <UnitMgt\IndirectMeasure.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   unitmgtIndirectMeasure
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
unitmgtIndirectMeasure::unitmgtIndirectMeasure() :
   Name(_T("Default")),
   ComponentDim( unitMeasure::Millimeter ),
   XSectionDim( unitMeasure::Millimeter ),
   SpanLength( unitMeasure::Meter ),
   AlignmentLength( unitMeasure::Meter ),
   Deflection( unitMeasure::Millimeter ),
   Area( unitMeasure::Millimeter2 ),
   MomentOfInertia( unitMeasure::Millimeter4 ),
   SectModulus( unitMeasure::Millimeter3 ),
   AvOverS( unitMeasure::Meter2PerMeter ),
   Stress( unitMeasure::MPa ),
   SmallStress( unitMeasure::MPa ),
   ModE( unitMeasure::MPa ),
   GeneralForce( unitMeasure::Kilonewton ),
   Tonnage( unitMeasure::Kilonewton ),
   Shear( unitMeasure::Kilonewton ),
   Moment( unitMeasure::KilonewtonMeter ),
   SmallMoment( unitMeasure::NewtonMillimeter ),
   Angle( unitMeasure::Degree ),
   RadAngle( unitMeasure::Radian ),
   Density( unitMeasure::KgPerMeter3 ),
   MassPerLength( unitMeasure::KgPerMeter ),
   ForcePerLength( unitMeasure::KilonewtonPerMeter ),
   MomentPerAngle( unitMeasure::KiloNewtonMeterPerRadian ),
   Time( unitMeasure::Hour ),
   Time2( unitMeasure::Day ),
   Time3( unitMeasure::Day ),
   PerLength( unitMeasure::PerMillimeter ),
   Curvature( unitMeasure::PerMillimeter ),
   ForceLength2( unitMeasure::KilonewtonMeter2),
   SqrtPressure( unitMeasure::SqrtMPa )
{
      Scalar.Width = 8;
      Scalar.Precision = 3;
      Scalar.Format = sysNumericFormatTool::Fixed;
}

unitmgtIndirectMeasure::unitmgtIndirectMeasure(const unitmgtIndirectMeasure& rOther) :
   Name(_T("Default")),
   ComponentDim( unitMeasure::Millimeter ),
   XSectionDim( unitMeasure::Millimeter ),
   SpanLength( unitMeasure::Meter ),
   AlignmentLength( unitMeasure::Meter ),
   Deflection( unitMeasure::Millimeter ),
   Area( unitMeasure::Millimeter2 ),
   MomentOfInertia( unitMeasure::Millimeter4 ),
   SectModulus( unitMeasure::Millimeter3 ),
   AvOverS( unitMeasure::Meter2PerMeter ),
   Stress( unitMeasure::MPa ),
   SmallStress( unitMeasure::MPa ),
   ModE( unitMeasure::MPa ),
   GeneralForce( unitMeasure::Kilonewton ),
   Tonnage( unitMeasure::Kilonewton ),
   Shear( unitMeasure::Kilonewton ),
   Moment( unitMeasure::KilonewtonMeter ),
   SmallMoment( unitMeasure::NewtonMillimeter ),
   Angle( unitMeasure::Degree ),
   RadAngle( unitMeasure::Radian ),
   Density( unitMeasure::KgPerMeter3 ),
   MassPerLength( unitMeasure::KgPerMeter ),
   ForcePerLength( unitMeasure::KilonewtonPerMeter ),
   MomentPerAngle( unitMeasure::KiloNewtonMeterPerRadian ),
   Time( unitMeasure::Hour ),
   Time2( unitMeasure::Day ),
   Time3( unitMeasure::Day ),
   PerLength( unitMeasure::PerMillimeter ),
   Curvature( unitMeasure::PerMillimeter ),
   ForceLength2( unitMeasure::KilonewtonMeter2),
   SqrtPressure( unitMeasure::SqrtMPa)
{
      Scalar.Width = 8;
      Scalar.Precision = 3;
      Scalar.Format = sysNumericFormatTool::Fixed;

      MakeCopy( rOther );
}

unitmgtIndirectMeasure::~unitmgtIndirectMeasure()
{
}

//======================== OPERATORS  =======================================
unitmgtIndirectMeasure& unitmgtIndirectMeasure::operator=(const unitmgtIndirectMeasure& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG

// Helper macros for AssertValid()
#define TEST_MEASURE(m) if ( !m.UnitOfMeasure.AssertValid() ) return false; \
                        if ( m.Tol < 0 ) return false; \
                        if ( m.Precision > m.Width ) return false;

bool unitmgtIndirectMeasure::AssertValid() const
{
   TEST_MEASURE( ComponentDim );
   TEST_MEASURE( XSectionDim );
   TEST_MEASURE( SpanLength );
   TEST_MEASURE( AlignmentLength );
   TEST_MEASURE( Deflection );
   TEST_MEASURE( Area );
   TEST_MEASURE( MomentOfInertia );
   TEST_MEASURE( SectModulus );
   TEST_MEASURE( Stress );
   TEST_MEASURE( SmallStress );
   TEST_MEASURE( AvOverS );
   TEST_MEASURE( ModE );
   TEST_MEASURE( GeneralForce );
   TEST_MEASURE( Tonnage );
   TEST_MEASURE( Shear );
   TEST_MEASURE( Moment );
   TEST_MEASURE( SmallMoment );
   TEST_MEASURE( Angle );
   TEST_MEASURE( RadAngle );
   TEST_MEASURE( Density );
   TEST_MEASURE( MassPerLength );
   TEST_MEASURE( ForcePerLength );
   TEST_MEASURE( MomentPerAngle );
   TEST_MEASURE( Time );
   TEST_MEASURE( Time2 );
   TEST_MEASURE( Time3 );
   TEST_MEASURE( PerLength );
   TEST_MEASURE( ForceLength2 );
   TEST_MEASURE( SqrtPressure );

   return true;
}

// Template helper function for Dump
template <class T>
void dump_it(dbgDumpContext& os,LPCTSTR label,const T& unit)
{
   os << label << endl;
   os << _T('\t') << _T("Unit of Measure : ") << unit.UnitOfMeasure.UnitTag() << endl;
   os << _T('\t') << _T("Zeroness        : ") << unit.Tol            << endl;
}

void unitmgtIndirectMeasure::Dump(dbgDumpContext& os) const
{
   os << _T("Name = ") << Name << endl;
   dump_it(os,_T("ComponentDim"),    ComponentDim );
   dump_it(os,_T("XSectionDim"),     XSectionDim  );
   dump_it(os,_T("SpanLength"),      SpanLength   );
   dump_it(os,_T("AlignmentLength"), AlignmentLength   );
   dump_it(os,_T("Deflection"),    Deflection );
   dump_it(os,_T("Area"),            Area         );
   dump_it(os,_T("MomentOfInertia"), MomentOfInertia);
   dump_it(os,_T("SectModulus"),     SectModulus  );
   dump_it(os,_T("Stress"),          Stress       );
   dump_it(os,_T("SmallStress"),     SmallStress  );
   dump_it(os,_T("AvOverS"),         AvOverS      );
   dump_it(os,_T("ModE"),            ModE         );
   dump_it(os,_T("GeneralForce"),    GeneralForce );
   dump_it(os,_T("Tonnage"),         Tonnage );
   dump_it(os,_T("Shear"),           Shear        );
   dump_it(os,_T("Moment"),          Moment       );
   dump_it(os,_T("SmallMoment"),     SmallMoment  );
   dump_it(os,_T("Angle"),           Angle        );
   dump_it(os,_T("RadAngle"),        RadAngle     );
   dump_it(os,_T("Density"),         Density      );
   dump_it(os,_T("MassPerLength"),   MassPerLength);
   dump_it(os,_T("ForcePerLength"),  ForcePerLength);
   dump_it(os,_T("MomentPerAngle"),  MomentPerAngle);
   dump_it(os,_T("Time"),            Time         );
   dump_it(os,_T("Time2"),           Time2        );
   dump_it(os,_T("Time3"),           Time3        );
   dump_it(os,_T("PerLength"),       PerLength    );
   dump_it(os,_T("ForceLength2"),    ForceLength2 );
   dump_it(os,_T("SqrtPressure"),    SqrtPressure );

}

#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void unitmgtIndirectMeasure::MakeCopy(const unitmgtIndirectMeasure& rOther)
{
   Name = rOther.Name;

   StationFormat = rOther.StationFormat;

   Scalar = rOther.Scalar;

   ComponentDim    = rOther.ComponentDim;
   XSectionDim     = rOther.XSectionDim;
   SpanLength      = rOther.SpanLength;
   AlignmentLength = rOther.AlignmentLength;
   Deflection    = rOther.Deflection;
   Area            = rOther.Area;
   MomentOfInertia = rOther.MomentOfInertia;
   SectModulus     = rOther.SectModulus;
   Stress          = rOther.Stress;
   SmallStress     = rOther.SmallStress;
   AvOverS         = rOther.AvOverS;
   ModE            = rOther.ModE;
   GeneralForce    = rOther.GeneralForce;
   Tonnage         = rOther.Tonnage;
   Shear           = rOther.Shear;
   Moment          = rOther.Moment;
   SmallMoment     = rOther.SmallMoment;
   Angle           = rOther.Angle;
   RadAngle        = rOther.RadAngle;
   Density         = rOther.Density;
   MassPerLength   = rOther.MassPerLength;
   ForcePerLength  = rOther.ForcePerLength;
   MomentPerAngle  = rOther.MomentPerAngle;
   Time            = rOther.Time;
   Time2           = rOther.Time2;
   Time3           = rOther.Time3;
   PerLength       = rOther.PerLength;
   Curvature       = rOther.Curvature;
   ForceLength2    = rOther.ForceLength2;
   SqrtPressure    = rOther.SqrtPressure;
}

void unitmgtIndirectMeasure::MakeAssignment(const unitmgtIndirectMeasure& rOther)
{
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


