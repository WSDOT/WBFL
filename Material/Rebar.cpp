///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
// Copyright © 1999-2010  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matRebar
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
matRebar::matRebar() :
m_Name("Unknown")
{
   m_Shape     = Circle;
   m_Dimension = 0.0;
   m_Area      = 0.0;
   m_Fpu       = 0.0;
   m_Fpy       = 0.0;
   m_ModE      = 0.0;
}

matRebar::matRebar(const std::string& name,
                   Float64 fpu,
                   Float64 fpy,
                   Float64 modE,
                   ShapeType st,
                   Float64 nd,
                   Float64 na ) :
m_Name( name )
{
   m_Shape     = st;
   m_Dimension = nd;
   m_Area      = na;
   m_Fpu       = fpu;
   m_Fpy       = fpy;
   m_ModE      = modE;
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
   if ( m_Fpy > m_Fpu )
      return false;

   if ( m_Dimension <= 0 )
      return false;

   if ( m_Area <= 0 )
      return false;

   if ( m_ModE <= 0 )
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
   m_Shape     = rOther.m_Shape;
   m_Dimension = rOther.m_Dimension;
   m_Area      = rOther.m_Area;
   m_Fpu       = rOther.m_Fpu;
   m_Fpy       = rOther.m_Fpy;
   m_ModE      = rOther.m_ModE;
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


