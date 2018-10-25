///////////////////////////////////////////////////////////////////////
// BMF - Bridge Modeling Framework - Product modeling of bridge structures
// Copyright © 1999-2014  Washington State Department of Transportation
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

#include <BridgeModeling\BridgeModelingLib.h>

/****************************************************************************
CLASS
   bmfSpanFactory
****************************************************************************/

#include <BridgeModeling\SpanFactory.h>
#include <BridgeModeling\Span.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfSpanFactory::bmfSpanFactory()
{
}

bmfSpanFactory::bmfSpanFactory(const bmfSpanFactory& rOther)
{
   MakeCopy(rOther);
}

bmfSpanFactory::~bmfSpanFactory()
{
}

//======================== OPERATORS  =======================================
bmfSpanFactory& bmfSpanFactory::operator= (const bmfSpanFactory& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
bmfSpan* bmfSpanFactory::CreateSpan() const
{
   return new bmfSpan;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfSpanFactory::MakeCopy(const bmfSpanFactory& rOther)
{
   // Add copy code here...
}

void bmfSpanFactory::MakeAssignment(const bmfSpanFactory& rOther)
{
   MakeCopy( rOther );
}

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
bool bmfSpanFactory::AssertValid() const
{
   return true;
}

void bmfSpanFactory::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfSpanFactory" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfSpanFactory::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfSpanFactory");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bmfSpanFactory");

   TESTME_EPILOG("SpanFactory");
}
#endif // _UNITTEST
