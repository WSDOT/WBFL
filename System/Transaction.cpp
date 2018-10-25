///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2017  Washington State Department of Transportation
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

#include <System\SysLib.h>

//////////////////X////////////////////X/////////////////////////////////////
// NAME:          txnTransaction           
// SYNOPSIS:      
//////////////////X////////////////////X/////////////////////////////////////

#include <System\Transaction.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

txnTransaction::txnTransaction()
{
} // txnTransaction

txnTransaction::~txnTransaction()
{
} // ~txnTransaction

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bool txnTransaction::Execute()
{
   // Does nothing by default
   return true;
} // Execute

void txnTransaction::Undo()
{
   // Does nothing by default
} // Undo

void txnTransaction::Log(std::_tostream& os) const
{
   os << Name();
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

bool txnTransaction::IsUndoable()
{
   return false;
} // IsUndoable

bool txnTransaction::IsRepeatable()
{
   return false;
} // IsRepeatable

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
//======================== INQUERY ==========================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool txnTransaction::AssertValid() const
{
   return true;
}

void txnTransaction::Dump(dbgDumpContext& os) const
{
   os << "Dump for txnTransaction" << endl;
   os << Name();
}
#endif // _DEBUG

#if defined _UNITTEST
bool txnTransaction::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("txnTransaction");
   TRY_TESTME( true ); // This is an Abstract base class,  nothing to test here
   TESTME_EPILOG("txnTransaction");
}
#endif // _UNITTEST
