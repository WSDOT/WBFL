///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#include <Material\MatLib.h>
#include <Material\ConcreteListener.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   matConcreteListener
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
matConcreteListener::matConcreteListener()
{
}

matConcreteListener::~matConcreteListener()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void matConcreteListener::OnRegistered(matConcrete* /*pConcrete*/)
{
}

void matConcreteListener::OnUnregistered(matConcrete* /*pConcrete*/)
{
}

void matConcreteListener::OnConcreteChanged(matConcrete* /*pConcrete*/)
{
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool matConcreteListener::AssertValid() const
{
   return true;
}

void matConcreteListener::Dump(dbgDumpContext& os) const
{
   os << "Dump for matConcreteListener" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool matConcreteListener::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("matConcreteListener");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for matConcreteListener");
   TESTME_EPILOG("matConcreteListener");
}
#endif
////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


