///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2018  Washington State Department of Transportation
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

#include <GeomModel\GeomModelLib.h>
#include <GeomModel\MassProperties.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmMassProperties
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
gmMassProperties::gmMassProperties():
m_Mpl(0)
{
}

gmMassProperties::gmMassProperties(Float64 mpl):
m_Mpl(mpl)
{
}

gmMassProperties::gmMassProperties(const gmMassProperties& rOther)
{
   MakeCopy(rOther);
}

gmMassProperties::~gmMassProperties()
{
}

//======================== OPERATORS  =======================================
gmMassProperties& gmMassProperties::operator= (const gmMassProperties& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================

Float64 gmMassProperties::SetMassPerLength(Float64 mpl)
{
   Float64 tmp = m_Mpl;
   m_Mpl = mpl;
   return tmp;

}

Float64 gmMassProperties::MassPerLength() const
{
   return m_Mpl;
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmMassProperties::AssertValid() const
{
   return true;
}

void gmMassProperties::Dump(dbgDumpContext& os) const
{
   os << "Dump for gmMassProperties" << endl;
   os << " m_Mpl   = "<< m_Mpl << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool gmMassProperties::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmMassProperties");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented");
   TESTME_EPILOG("gmMassProperties");
}
#endif // _UNITTEST

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void gmMassProperties::MakeCopy(const gmMassProperties& rOther)
{
   m_Mpl = rOther.m_Mpl;
}

void gmMassProperties::MakeAssignment(const gmMassProperties& rOther)
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


