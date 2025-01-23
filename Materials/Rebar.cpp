///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#include <Materials/MatLib.h>
#include <Materials/Rebar.h>
#include <Units\Convert.h>

using namespace WBFL::Materials;

// -1 means the material is not defined
// Index 0 = A615, 1 = A706, 2 = A1035

static Float64 gs_Fy40[3] = { WBFL::Units::ConvertToSysUnits(40,WBFL::Units::Measure::KSI), -1, -1 };
static Float64 gs_Fu40[3] = { WBFL::Units::ConvertToSysUnits(60,WBFL::Units::Measure::KSI), -1, -1 };
static Float64 gs_Es40[3] = { WBFL::Units::ConvertToSysUnits(29000,WBFL::Units::Measure::KSI), -1, -1 };

static Float64 gs_Fy60[3] = { WBFL::Units::ConvertToSysUnits(60,WBFL::Units::Measure::KSI),    WBFL::Units::ConvertToSysUnits(60,WBFL::Units::Measure::KSI), -1 };
static Float64 gs_Fu60[3] = { WBFL::Units::ConvertToSysUnits(90,WBFL::Units::Measure::KSI),    WBFL::Units::ConvertToSysUnits(80,WBFL::Units::Measure::KSI), -1 };
static Float64 gs_Es60[3] = { WBFL::Units::ConvertToSysUnits(29000,WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(29000,WBFL::Units::Measure::KSI), -1 };
static Float64 gs_Fy75[3] = { WBFL::Units::ConvertToSysUnits(75,WBFL::Units::Measure::KSI),    -1, -1 };
static Float64 gs_Fu75[3] = { WBFL::Units::ConvertToSysUnits(100,WBFL::Units::Measure::KSI),   -1, -1 };
static Float64 gs_Es75[3] = { WBFL::Units::ConvertToSysUnits(29000,WBFL::Units::Measure::KSI), -1, -1 };

static Float64 gs_Fy80[3] = { WBFL::Units::ConvertToSysUnits(80,WBFL::Units::Measure::KSI),    WBFL::Units::ConvertToSysUnits(80,WBFL::Units::Measure::KSI), -1 };
static Float64 gs_Fu80[3] = { WBFL::Units::ConvertToSysUnits(105,WBFL::Units::Measure::KSI),    WBFL::Units::ConvertToSysUnits(100,WBFL::Units::Measure::KSI), -1 };
static Float64 gs_Es80[3] = { WBFL::Units::ConvertToSysUnits(29000,WBFL::Units::Measure::KSI), WBFL::Units::ConvertToSysUnits(29000,WBFL::Units::Measure::KSI), -1 };

static Float64 gs_Fy100[3] = { -1, -1, WBFL::Units::ConvertToSysUnits(100,WBFL::Units::Measure::KSI) };
static Float64 gs_Fu100[3] = { -1, -1, WBFL::Units::ConvertToSysUnits(150,WBFL::Units::Measure::KSI) };
static Float64 gs_Es100[3] = { -1, -1, WBFL::Units::ConvertToSysUnits(29000,WBFL::Units::Measure::KSI) };

static Float64 gs_Fy120[3] = { -1, -1, WBFL::Units::ConvertToSysUnits(120,WBFL::Units::Measure::KSI) };
static Float64 gs_Fu120[3] = { -1, -1, WBFL::Units::ConvertToSysUnits(150,WBFL::Units::Measure::KSI) };
static Float64 gs_Es120[3] = { -1, -1, WBFL::Units::ConvertToSysUnits(29000,WBFL::Units::Measure::KSI) };

static Float64 gs_Elongation_A615[6][11] = {
   //#3   #4     #5    #6   #7     #8    #9    #10   #11   #14  #18
   {0.11, 0.12, 0.12, 0.12, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}, // Grade 40  // -1.0 means not specified in the standard
   {0.09, 0.09, 0.09, 0.09, 0.08, 0.08, 0.07, 0.07, 0.07, 0.07, 0.07}, // Grade 60
   {0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.06, 0.06, 0.06, 0.06}, // Grade 75
   {0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.06, 0.06, 0.06, 0.06}, // Grade 80
   {0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.06, 0.06, 0.06, 0.06}, // Grade 100
   {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}, // Grade 120
};

static Float64 gs_Elongation_A706[6][11] = {
   //#3   #4     #5    #6   #7     #8    #9    #10   #11   #14  #18
   {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}, // Grade 40
   {0.14, 0.14, 0.14, 0.14, 0.12, 0.12, 0.12, 0.12, 0.12, 0.10, 0.10}, // Grade 60
   {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}, // Grade 75
   {0.12, 0.12, 0.12, 0.12, 0.12, 0.12, 0.12, 0.12, 0.12, 0.10, 0.10}, // Grade 80
   {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}, // Grade 100
   {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}, // Grade 120
};

static Float64 gs_Elongation_A1035[6][11] = {
   //#3   #4     #5    #6   #7     #8    #9    #10   #11   #14  #18
   {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}, // Grade 40
   {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}, // Grade 60
   {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}, // Grade 75
   {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}, // Grade 80
   {0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.06, 0.06}, // Grade 100
   {0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.07, 0.06, 0.06} // Grade 120
};

static Float64 gs_Area[11] = {
   WBFL::Units::ConvertToSysUnits(0.11,WBFL::Units::Measure::Inch2),  // #3 
   WBFL::Units::ConvertToSysUnits(0.20,WBFL::Units::Measure::Inch2),  // #4
   WBFL::Units::ConvertToSysUnits(0.31,WBFL::Units::Measure::Inch2),  // #5
   WBFL::Units::ConvertToSysUnits(0.44,WBFL::Units::Measure::Inch2),  // #6
   WBFL::Units::ConvertToSysUnits(0.60,WBFL::Units::Measure::Inch2),  // #7
   WBFL::Units::ConvertToSysUnits(0.79,WBFL::Units::Measure::Inch2),  // #8 
   WBFL::Units::ConvertToSysUnits(1.00,WBFL::Units::Measure::Inch2),  // #9
   WBFL::Units::ConvertToSysUnits(1.27,WBFL::Units::Measure::Inch2),  // #10
   WBFL::Units::ConvertToSysUnits(1.56,WBFL::Units::Measure::Inch2),  // #11
   WBFL::Units::ConvertToSysUnits(2.25,WBFL::Units::Measure::Inch2),  // #14
   WBFL::Units::ConvertToSysUnits(4.00,WBFL::Units::Measure::Inch2)   // #18
};

static Float64 gs_Diameter[11] = {
   WBFL::Units::ConvertToSysUnits(0.375,WBFL::Units::Measure::Inch),  // #3
   WBFL::Units::ConvertToSysUnits(0.500,WBFL::Units::Measure::Inch),  // #4
   WBFL::Units::ConvertToSysUnits(0.625,WBFL::Units::Measure::Inch),  // #5
   WBFL::Units::ConvertToSysUnits(0.750,WBFL::Units::Measure::Inch),  // #6
   WBFL::Units::ConvertToSysUnits(0.875,WBFL::Units::Measure::Inch),  // #7
   WBFL::Units::ConvertToSysUnits(1.000,WBFL::Units::Measure::Inch),  // #8 
   WBFL::Units::ConvertToSysUnits(1.128,WBFL::Units::Measure::Inch),  // #9
   WBFL::Units::ConvertToSysUnits(1.270,WBFL::Units::Measure::Inch),  // #10
   WBFL::Units::ConvertToSysUnits(1.410,WBFL::Units::Measure::Inch),  // #11
   WBFL::Units::ConvertToSysUnits(1.693,WBFL::Units::Measure::Inch),  // #14
   WBFL::Units::ConvertToSysUnits(2.257,WBFL::Units::Measure::Inch)   // #18
};

int SizeIndex(Rebar::Size size)
{
   switch(size)
   {
   case Rebar::Size::bs3:  return 0;
   case Rebar::Size::bs4:  return 1;
   case Rebar::Size::bs5:  return 2;
   case Rebar::Size::bs6:  return 3;
   case Rebar::Size::bs7:  return 4;
   case Rebar::Size::bs8:  return 5;
   case Rebar::Size::bs9:  return 6;
   case Rebar::Size::bs10: return 7;
   case Rebar::Size::bs11: return 8;
   case Rebar::Size::bs14: return 9;
   case Rebar::Size::bs18: return 10;
   default:
      CHECK(FALSE);
      return 0;
   }; 

   return 0;
}

int TypeIndex(Rebar::Type type)
{
   switch(type)
   {
   case Rebar::Type::A615:  return 0;
   case Rebar::Type::A706:  return 1;
   case Rebar::Type::A1035: return 2;
   default:
      CHECK(FALSE);
      return 0;
   }

   return 0;
}

int GradeIndex(Rebar::Grade grade)
{
   switch (grade)
   {
   case Rebar::Grade::Grade40: return 0;
   case Rebar::Grade::Grade60: return 1;
   case Rebar::Grade::Grade75: return 2;
   case Rebar::Grade::Grade80: return 3;
   case Rebar::Grade::Grade100: return 4;
   case Rebar::Grade::Grade120: return 5;
   default:
      CHECK(FALSE);
      return 0;
   }

   return 0;
}


Rebar::Rebar() :
m_Name(_T("Unknown"))
{
   m_Size = Size::bs3;
   m_Type = Type::A615;
   m_Grade = Grade::Grade60;

   int idx = SizeIndex(m_Size);
   m_Dimension = gs_Diameter[idx];
   m_Area      = gs_Area[idx];
}

Rebar::Rebar(const std::_tstring& name,
            Grade grade,
            Type type,
            Size size) :
m_Name( name )
{
   m_Grade = grade;
   m_Type = type;
   m_Size = size;

   int idx = SizeIndex(m_Size);
   m_Dimension = gs_Diameter[idx];
   m_Area      = gs_Area[idx];
}

Float64 Rebar::GetUltimateStrength(Type type,Grade grade)
{
   Float64 value = -1;
   int index = TypeIndex(type);
   switch (grade)
   {
   case Grade40:
      value = gs_Fu40[index];
      break;

   case Grade60:
      value = gs_Fu60[index];
      break;

   case Grade75:
      value = gs_Fu75[index];
      break;

   case Grade80:
      value = gs_Fu80[index];
      break;

   case Grade100:
      value = gs_Fu100[index];
      break;

   case Grade120:
      value = gs_Fu120[index];
      break;

   default:
      CHECK(false); // should not get here
   }

   CHECK(0 < value);
   return value;
}

Float64 Rebar::GetYieldStrength(Type type,Grade grade)
{
   Float64 value = -1;
   int index = TypeIndex(type);
   switch (grade)
   {
   case Grade40:
      value = gs_Fy40[index];
      break;

   case Grade60:
      value = gs_Fy60[index];
      break;

   case Grade75:
      value = gs_Fy75[index];
      break;

   case Grade80:
      value = gs_Fy80[index];
      break;

   case Grade100:
      value = gs_Fy100[index];
      break;

   case Grade120:
      value = gs_Fy120[index];
      break;

   default:
      CHECK(false); // should not get here
   }

   CHECK(0 < value);
   return value;
}

Float64 Rebar::GetE(Type type,Grade grade)
{
   Float64 value = -1;
   int index = TypeIndex(type);
   switch (grade)
   {
   case Grade40:
      value = gs_Es40[index];
      break;

   case Grade60:
      value = gs_Es60[index];
      break;

   case Grade75:
      value = gs_Es75[index];
      break;

   case Grade80:
      value = gs_Es80[index];
      break;

   case Grade100:
      value = gs_Es100[index];
      break;

   case Grade120:
      value = gs_Es120[index];
      break;

   default:
      CHECK(false); // should not get here
   }

   CHECK(0 < value);
   return value;
}

Float64 Rebar::GetElongation(Type type, Grade grade, Size size)
{
   int gradeIdx = GradeIndex(grade);
   int sizeIdx = SizeIndex(size);
   Float64 e = -1.0;
   switch (type)
   {
   case Type::A615: e = gs_Elongation_A615[gradeIdx][sizeIdx]; break;
   case Type::A706: e = gs_Elongation_A706[gradeIdx][sizeIdx]; break;
   case Type::A1035: e = gs_Elongation_A1035[gradeIdx][sizeIdx]; break;
   default: CHECK(false);
   }

   CHECK(e != -1.0);
   return e;
}

#if defined _DEBUG
bool Rebar::AssertValid() const
{
   if ( m_Dimension <= 0 )
      return false;

   if ( m_Area <= 0 )
      return false;

   return true;
}
#endif // _DEBUG
