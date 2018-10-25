///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
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

#include <Units\UnitsLib.h>
#include <Units\UnitTest.h>
#include <Units\AutoSysUnits.h>
#include <Units\Measure.h>
#include <Units\SysUnitsMgr.h>
#include <Units\SysUnitsMgrListener.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   unitUnitTest
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
bool unitUnitTest::TestMe(dbgLog& rlog)
{
   bool tst=true;
#if defined _UNITTEST

   tst &= unitAutoSysUnits::TestMe(rlog);
   tst &= unitMeasure::TestMe(rlog);
   tst &= unitSysUnitsMgr::TestMe(rlog);
   tst &= unitSysUnitsMgrListener::TestMe(rlog);


#endif
   return tst;
}

