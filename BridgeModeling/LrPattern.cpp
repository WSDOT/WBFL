///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfLrPattern
****************************************************************************/

#include <BridgeModeling\LrPattern.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfLrPattern::bmfLrPattern():
m_pRebar(0)
{
}

bmfLrPattern::bmfLrPattern(const matRebar* pRebar):
m_pRebar(pRebar)
{
   ASSERTVALID;
}

bmfLrPattern::~bmfLrPattern()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================

const matRebar* bmfLrPattern::GetRebar() const
{
   ASSERTVALID;
   return m_pRebar;
}

void bmfLrPattern::SetRebar(const matRebar* pRebar)
{
   PRECONDITION(pRebar!=0);
   m_pRebar = pRebar;
}

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
#if defined _DEBUG
bool bmfLrPattern::AssertValid() const
{

   return m_pRebar!=0;
}

void bmfLrPattern::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfLrPattern" << endl;

}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfLrPattern::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfLrPattern");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bmfLrPattern");

   TESTME_EPILOG("LrPattern");
}
#endif // _UNITTEST
