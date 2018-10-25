///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <Cogo\CogoLib.h>

/****************************************************************************
CLASS
   cogoUnitTest
****************************************************************************/

#include <Cogo\UnitTest.h>

#include <Cogo\CogoAngle.h>
#include <Cogo\CogoDirection.h>
#include <Cogo\CogoModel.h>
#include <Cogo\Roadway.h>
#include <Cogo\CogoHelpers.h>
#include <Cogo\Engine.h>
#include <Cogo\Profile.h>

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bool cogoUnitTest::TestMe(dbgLog& rlog)
{
   bool tst = true;

#if defined _UNITTEST
   tst &= cogoUtil::TestMe( rlog );
   tst &= cogoEngine::TestMe( rlog );
   tst &= cogoAngle::TestMe( rlog );
   tst &= cogoDirection::TestMe( rlog );
   tst &= cogoModel::TestMe( rlog );
   tst &= cogoRoadway::TestMe( rlog );
   tst &= cogoProfile::TestMe( rlog );
#endif

   return tst;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

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

//======================== DEBUG      =======================================
