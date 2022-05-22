///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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

#include "stdafx.h"
#include <EAF\EAFTransaction.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool CEAFTransaction::Execute()
{
   // Does nothing by default
   return true;
}

void CEAFTransaction::Undo()
{
   // Does nothing by default
}

void CEAFTransaction::Log(std::_tostream& os) const
{
   os << Name();
}

bool CEAFTransaction::IsUndoable() const
{
   return false;
}

bool CEAFTransaction::IsRepeatable() const
{
   return false;
}

#if defined _DEBUG
bool CEAFTransaction::AssertValid() const
{
   return true;
}

void CEAFTransaction::Dump(WBFL::Debug::LogContext& os) const
{
   os << "Dump for CEAFTransaction" << WBFL::Debug::endl;
   os << Name();
}
#endif // _DEBUG

#if defined _UNITTEST
bool CEAFTransaction::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CEAFTransaction");
   TRY_TESTME( true ); // This is an Abstract base class,  nothing to test here
   TESTME_EPILOG("CEAFTransaction");
}
#endif // _UNITTEST
