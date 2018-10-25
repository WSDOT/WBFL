///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
#include <Units\SysUnitsMgrListener.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
CLASS
   unitsSysUnitsMgrListener
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
unitSysUnitsMgrListener::unitSysUnitsMgrListener()
{
}

unitSysUnitsMgrListener::unitSysUnitsMgrListener(const unitSysUnitsMgrListener& rOther)
{
}

unitSysUnitsMgrListener::~unitSysUnitsMgrListener()
{
}

//======================== OPERATORS  =======================================
unitSysUnitsMgrListener& unitSysUnitsMgrListener::operator= (const unitSysUnitsMgrListener& rOther)
{
   return *this;
}

//======================== OPERATIONS =======================================
void unitSysUnitsMgrListener::OnRegistered()
{
   // Do nothing
}

void unitSysUnitsMgrListener::OnUnregistered()
{
   // Do nothing
}

void unitSysUnitsMgrListener::OnUpdate()
{
   // Do nothing
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool unitSysUnitsMgrListener::AssertValid() const
{
   return true;
}

void unitSysUnitsMgrListener::Dump(dbgDumpContext& os) const
{
   os << "Dump for unitSysUnitsMgrListener" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool unitSysUnitsMgrListener::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("unitSysUnitsMgrListener");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for unitSysUnitsMgrListener");
   TESTME_EPILOG("unitSysUnitsMgrListener");
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


