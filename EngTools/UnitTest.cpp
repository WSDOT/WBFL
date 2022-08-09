///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
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

#include <EngTools/EngToolsLib.h>
#include <EngTools/UnitTest.h>
#include <EngTools/MohrCircle.h>
#include <EngTools/BiaxialBeamStrain.h>
#include <EngTools/PrandtlMembraneSolver.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool WINAPI WBFL::EngTools::UnitTest::TestMe(WBFL::Debug::Log& rlog)
{
   bool tst = true;

#if defined _UNITTEST
   tst &= MohrCircle::TestMe(rlog);
   tst &= BiaxialBeamStrain::TestMe(rlog);
   tst &= PrandtlMembraneSolver::TestMe(rlog);
#endif

   return tst;
}
