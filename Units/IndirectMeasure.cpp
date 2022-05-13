///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
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


#include <Units\UnitsLib.h>
#include <Units\IndirectMeasure.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Units;

IndirectMeasure::~IndirectMeasure()
{
}

#if defined _DEBUG

// Helper macros for AssertValid()
#define TEST_MEASURE(m) if ( !m.UnitOfMeasure.AssertValid() ) return false; \
                        if ( m.Tol < 0 ) return false; \
                        if ( m.Precision > m.Width ) return false;

bool IndirectMeasure::AssertValid() const
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
   TEST_MEASURE( WindPressure );
   TEST_MEASURE( Velocity );

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

void IndirectMeasure::Dump(dbgDumpContext& os) const
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
   dump_it(os,_T("WindPressure"),    WindPressure );
   dump_it(os,_T("Velocity"),        Velocity     );
}

#endif // _DEBUG
