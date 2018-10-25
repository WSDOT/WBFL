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
   bmfTrafficBarrier
****************************************************************************/

#include <BridgeModeling\TrafficBarrier.h>
#include <BridgeModeling\TrafficBarrierTemplate.h>
#include <GeomModel\Section.h>
#include <GeomModel\TrafficBarrier.h>
#include <Material\ConcreteEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfTrafficBarrier::bmfTrafficBarrier(const bmfTrafficBarrierTemplate* pTpl)
{
   PRECONDITION( pTpl != NULL );
   m_pTpl = pTpl;
}

bmfTrafficBarrier::bmfTrafficBarrier(const bmfTrafficBarrier& rOther)
{
   m_pTpl = 0;
   MakeCopy(rOther);
}

bmfTrafficBarrier::~bmfTrafficBarrier()
{
}

//======================== OPERATORS  =======================================
bmfTrafficBarrier& bmfTrafficBarrier::operator= (const bmfTrafficBarrier& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
gmSection* bmfTrafficBarrier::CreateSection() const
{
   std::auto_ptr<gmSection> pSection( new gmSection );
   pSection->AddComponent( *(m_pTpl->GetTrafficBarrierShape()),
                           m_pTpl->GetConcrete()->GetE(),
                           m_pTpl->GetConcrete()->GetDensity() );

   return pSection.release();
}

//======================== ACCESS     =======================================
std::string bmfTrafficBarrier::GetName() const
{
   return m_pTpl->GetName();
}

const gmTrafficBarrier* bmfTrafficBarrier::GetTrafficBarrierShape() const
{
   return m_pTpl->GetTrafficBarrierShape();
}

const matConcreteEx* bmfTrafficBarrier::GetConcrete() const
{
   return m_pTpl->GetConcrete();
}

const bmfTrafficBarrierTemplate* bmfTrafficBarrier::GetTemplate() const
{
   return m_pTpl;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfTrafficBarrier::MakeCopy(const bmfTrafficBarrier& rOther)
{
   m_pTpl = rOther.m_pTpl;
}

void bmfTrafficBarrier::MakeAssignment(const bmfTrafficBarrier& rOther)
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
bool bmfTrafficBarrier::AssertValid() const
{
   return true;
}

void bmfTrafficBarrier::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfTrafficBarrier" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfTrafficBarrier::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfTrafficBarrier");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bmfTrafficBarrier");

   TESTME_EPILOG("bmfTrafficBarrier");
}
#endif // _UNITTEST
