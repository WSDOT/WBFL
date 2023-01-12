///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include "TxnTestClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


testUndoableTxn::testUndoableTxn() {}
bool testUndoableTxn::Execute() { WATCH(_T("testUndoableTxn::Execute()")); return true; }
void testUndoableTxn::Undo() { WATCH(_T("Undoing testUndoableTxn")); }
txnTransaction* testUndoableTxn::CreateClone() const { return new testUndoableTxn; }
void testUndoableTxn::Log(std::_tostream& os) const { os << Name() << std::endl; }
std::_tstring testUndoableTxn::Name() const { return _T("Undoable Txn"); }
bool testUndoableTxn::IsUndoable() { return true; }
bool testUndoableTxn::IsRepeatable() { return true; }


testNotUndoableTxn::testNotUndoableTxn() : txnTransaction() {}
bool testNotUndoableTxn::Execute() { WATCH(_T("testNotUndoableTxn::Execute()")); return true;}
txnTransaction* testNotUndoableTxn::CreateClone() const { return new testNotUndoableTxn; }
void testNotUndoableTxn::Log(std::_tostream& os) const { os << Name() << std::endl; }
std::_tstring testNotUndoableTxn::Name() const { return _T("Not Undoable Txn"); }
bool testNotUndoableTxn::IsUndoable() { return false; }
bool testNotUndoableTxn::IsRepeatable() { return true; }

testNotRepeatableTxn::testNotRepeatableTxn() : txnTransaction() {}
bool testNotRepeatableTxn::Execute() { WATCH(_T("testNotRepeatableTxn::Execute()")); return true; }
void testNotRepeatableTxn::Undo() { WATCH(_T("Undoing testNotRepeatableTxn")); }
txnTransaction* testNotRepeatableTxn::CreateClone() const { return new testNotRepeatableTxn; }
void testNotRepeatableTxn::Log(std::_tostream& os) const { os << Name() << std::endl; }
std::_tstring testNotRepeatableTxn::Name() const { return _T("Not Repeatable Txn"); }
bool testNotRepeatableTxn::IsUndoable() { return true; }
bool testNotRepeatableTxn::IsRepeatable() { return false; }
