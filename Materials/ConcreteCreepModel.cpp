///////////////////////////////////////////////////////////////////////
// Materials - Analytical and Product modeling of civil engineering materials
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

#include <Materials/MatLib.h>
#include <Materials/ConcreteCreepModel.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Materials;

#if defined _DEBUG
bool ConcreteCreepModel::AssertValid() const
{
   return true;
}

void ConcreteCreepModel::Dump(WBFL::Debug::LogContext& os) const
{
   os << _T("Dump for ConcreteCreepModel") << WBFL::Debug::endl;
   os << _T("====================") << WBFL::Debug::endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool ConcreteCreepModel::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("ConcreteCreepModel");

   TESTME_EPILOG("ConcreteCreepModel");
}
#endif // _UNITTEST
