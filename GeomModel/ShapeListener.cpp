///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2012  Washington State Department of Transportation
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

#include <GeomModel\GeomModelLib.h>
#include <GeomModel\ShapeListener.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   gmShapeListener
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

   const int gmShapeListener::PROPERTIES           = 0x0001;
   const int gmShapeListener::DISPLAY              = 0x0002;

//======================== LIFECYCLE  =======================================
gmShapeListener::gmShapeListener()
{
}


gmShapeListener::~gmShapeListener()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void gmShapeListener::OnRegistered(const gmIShape* pShape) const
{
   // do nothing
}

void gmShapeListener::OnUnregistered(const gmIShape* pShape) const
{
   // do nothing
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool gmShapeListener::AssertValid() const
{
   return true;
}

void gmShapeListener::Dump(dbgDumpContext& os) const
{
   os << "Dump for gmShapeListener" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool gmShapeListener::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("gmShapeListener");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented");
   TESTME_EPILOG("gmShapeListener");
}
#endif // _UNITTEST

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


