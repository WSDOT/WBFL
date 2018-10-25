///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#include <Material\MatLib.h>
#include <Material\Rebar.h>
#include <Units\SysUnits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matRebar
****************************************************************************/
// -1 means the material is not defined
// Index 0 = A615, 1 = A706, 2 = A1035

static Float64 gs_Fy40[3] = { ::ConvertToSysUnits(40,unitMeasure::KSI), -1, -1 };
static Float64 gs_Fu40[3] = { ::ConvertToSysUnits(60,unitMeasure::KSI), -1, -1 };
static Float64 gs_Es40[3] = { ::ConvertToSysUnits(29000,unitMeasure::KSI), -1, -1 };

static Float64 gs_Fy60[3] = { ::ConvertToSysUnits(60,unitMeasure::KSI),    ::ConvertToSysUnits(60,unitMeasure::KSI), -1 };
static Float64 gs_Fu60[3] = { ::ConvertToSysUnits(90,unitMeasure::KSI),    ::ConvertToSysUnits(80,unitMeasure::KSI), -1 };
static Float64 gs_Es60[3] = { ::ConvertToSysUnits(29000,unitMeasure::KSI), ::ConvertToSysUnits(29000,unitMeasure::KSI), -1 };
static Float64 gs_Fy75[3] = { ::ConvertToSysUnits(75,unitMeasure::KSI),    -1, -1 };
static Float64 gs_Fu75[3] = { ::ConvertToSysUnits(100,unitMeasure::KSI),   -1, -1 };
static Float64 gs_Es75[3] = { ::ConvertToSysUnits(29000,unitMeasure::KSI), -1, -1 };

static Float64 gs_Fy80[3] = { ::ConvertToSysUnits(80,unitMeasure::KSI),    ::ConvertToSysUnits(80,unitMeasure::KSI), -1 };
static Float64 gs_Fu80[3] = { ::ConvertToSysUnits(105,unitMeasure::KSI),    ::ConvertToSysUnits(100,unitMeasure::KSI), -1 };
static Float64 gs_Es80[3] = { ::ConvertToSysUnits(29000,unitMeasure::KSI), ::ConvertToSysUnits(29000,unitMeasure::KSI), -1 };

static Float64 gs_Fy100[3] = { -1, -1, ::ConvertToSysUnits(100,unitMeasure::KSI) };
static Float64 gs_Fu100[3] = { -1, -1, ::ConvertToSysUnits(150,unitMeasure::KSI) };
static Float64 gs_Es100[3] = { -1, -1, ::ConvertToSysUnits(29000,unitMeasure::KSI) };

static Float64 gs_Area[11] = {
   ::ConvertToSysUnits(0.11,unitMeasure::Inch2),  // #3
   ::ConvertToSysUnits(0.20,unitMeasure::Inch2),  // #4
   ::ConvertToSysUnits(0.31,unitMeasure::Inch2),  // #5
   ::ConvertToSysUnits(0.44,unitMeasure::Inch2),  // #6
   ::ConvertToSysUnits(0.60,unitMeasure::Inch2),  // #7
   ::ConvertToSysUnits(0.79,unitMeasure::Inch2),  // #8 
   ::ConvertToSysUnits(1.00,unitMeasure::Inch2),  // #9
   ::ConvertToSysUnits(1.27,unitMeasure::Inch2),  // #10
   ::ConvertToSysUnits(1.56,unitMeasure::Inch2),  // #11
   ::ConvertToSysUnits(2.25,unitMeasure::Inch2),  // #14
   ::ConvertToSysUnits(4.00,unitMeasure::Inch2)   // #18
};

static Float64 gs_Diameter[11] = {
   ::ConvertToSysUnits(0.375,unitMeasure::Inch),  // #3
   ::ConvertToSysUnits(0.500,unitMeasure::Inch),  // #4
   ::ConvertToSysUnits(0.625,unitMeasure::Inch),  // #5
   ::ConvertToSysUnits(0.750,unitMeasure::Inch),  // #6
   ::ConvertToSysUnits(0.875,unitMeasure::Inch),  // #7
   ::ConvertToSysUnits(1.000,unitMeasure::Inch),  // #8 
   ::ConvertToSysUnits(1.128,unitMeasure::Inch),  // #9
   ::ConvertToSysUnits(1.270,unitMeasure::Inch),  // #10
   ::ConvertToSysUnits(1.410,unitMeasure::Inch),  // #11
   ::ConvertToSysUnits(1.693,unitMeasure::Inch),  // #14
   ::ConvertToSysUnits(2.257,unitMeasure::Inch)   // #18
};

int SizeIndex(matRebar::Size size)
{
   switch(size)
   {
   case matRebar::bs3:  return 0;
   case matRebar::bs4:  return 1;
   case matRebar::bs5:  return 2;
   case matRebar::bs6:  return 3;
   case matRebar::bs7:  return 4;
   case matRebar::bs8:  return 5;
   case matRebar::bs9:  return 6;
   case matRebar::bs10: return 7;
   case matRebar::bs11: return 8;
   case matRebar::bs14: return 9;
   case matRebar::bs18: return 10;
   default:
      ASSERT(FALSE);
      return 0;
   }; 

   return 0;
}

int TypeIndex(matRebar::Type type)
{
   switch(type)
   {
   case matRebar::A615:  return 0;
   case matRebar::A706:  return 1;
   case matRebar::A1035: return 2;
   default:
      ASSERT(FALSE);
      return 0;
   }

   return 0;
}


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
matRebar::matRebar() :
m_Name(_T("Unknown"))
{
   m_Size = bs3;
   m_Type = A615;
   m_Grade = Grade60;
   int idx = TypeIndex(m_Type);
   m_Fu = gs_Fu60[idx];
   m_Fy = gs_Fy60[idx];
   m_Es = gs_Es60[idx];

   idx = SizeIndex(m_Size);
   m_Dimension = gs_Diameter[idx];
   m_Area      = gs_Area[idx];
}

matRebar::matRebar(const std::_tstring& name,
            Grade grade,
            Type type,
            Size size) :
m_Name( name )
{
   m_Grade = grade;
   m_Type = type;
   m_Size = size;

   int idx = TypeIndex(m_Type);
   switch(m_Grade)
   {
   case matRebar::Grade40:
      m_Fu = gs_Fu40[idx];
      m_Fy = gs_Fy40[idx];
      m_Es = gs_Es40[idx];
      break;

   case matRebar::Grade60:
      m_Fu = gs_Fu60[idx];
      m_Fy = gs_Fy60[idx];
      m_Es = gs_Es60[idx];
      break;

   case matRebar::Grade75:
      m_Fu = gs_Fu75[idx];
      m_Fy = gs_Fy75[idx];
      m_Es = gs_Es75[idx];
      break;

   case matRebar::Grade80:
      m_Fu = gs_Fu80[idx];
      m_Fy = gs_Fy80[idx];
      m_Es = gs_Es80[idx];
      break;

   case matRebar::Grade100:
      m_Fu = gs_Fu100[idx];
      m_Fy = gs_Fy100[idx];
      m_Es = gs_Es100[idx];
      break;
   }

   idx = SizeIndex(m_Size);
   m_Dimension = gs_Diameter[idx];
   m_Area      = gs_Area[idx];
}

matRebar::matRebar(const matRebar& rOther)
{
   MakeCopy(rOther);
}

matRebar::~matRebar()
{
}

//======================== OPERATORS  =======================================
matRebar& matRebar::operator= (const matRebar& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool matRebar::AssertValid() const
{
   if ( m_Fy > m_Fu )
      return false;

   if ( m_Dimension <= 0 )
      return false;

   if ( m_Area <= 0 )
      return false;

   if ( m_Es <= 0 )
      return false;

   return true;
}

void matRebar::Dump(dbgDumpContext& os) const
{
   os << "Dump for matRebar" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool matRebar::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("matRebar");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for matRebar");
   TESTME_EPILOG("matRebar");
}
#endif // _UNITTEST

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void matRebar::MakeCopy(const matRebar& rOther)
{
   m_Name      = rOther.m_Name;
   m_Size = rOther.m_Size;
   m_Grade = rOther.m_Grade;
   m_Type = rOther.m_Type;
   m_Dimension = rOther.m_Dimension;
   m_Area      = rOther.m_Area;
   m_Fu       = rOther.m_Fu;
   m_Fy       = rOther.m_Fy;
   m_Es      = rOther.m_Es;
}

void matRebar::MakeAssignment(const matRebar& rOther)
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


