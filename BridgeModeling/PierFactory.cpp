///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2015  Washington State Department of Transportation
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfPierFactory
****************************************************************************/

#include <BridgeModeling\PierFactory.h>
#include <BridgeModeling\Pier.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfPierFactory::bmfPierFactory()
{
}

bmfPierFactory::bmfPierFactory(const bmfPierFactory& rOther)
{
   MakeCopy(rOther);
}

bmfPierFactory::~bmfPierFactory()
{
}

//======================== OPERATORS  =======================================
bmfPierFactory& bmfPierFactory::operator= (const bmfPierFactory& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
bmfPier* bmfPierFactory::CreatePier()
{
   return new bmfPier();
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfPierFactory::MakeCopy(const bmfPierFactory& rOther)
{
   // Add copy code here...
}

void bmfPierFactory::MakeAssignment(const bmfPierFactory& rOther)
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

//======================== DEBUG      =======================================
#if defined _DEBUG
bool bmfPierFactory::AssertValid() const
{
   return true;
}

void bmfPierFactory::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfPierFactory" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfPierFactory::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfPierFactory");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bmfPierFactory");

   TESTME_EPILOG("PierFactory");
}
#endif // _UNITTEST
