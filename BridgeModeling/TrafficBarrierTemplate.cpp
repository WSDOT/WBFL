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
   bmfTrafficBarrierTemplate
****************************************************************************/

#include <BridgeModeling\TrafficBarrierTemplate.h>
#include <BridgeModeling\TrafficBarrier.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
bmfTrafficBarrierTemplate::bmfTrafficBarrierTemplate(const std::_tstring& name,
                                                     const gmTrafficBarrier* pTB,
                                                     const matConcreteEx* pConc) :
m_Name( name ),
m_pTB( pTB ),
m_pConc( pConc )
{
   PRECONDITION( name.length() > 0 );
   PRECONDITION( pTB != NULL );
   PRECONDITION( pConc != NULL );
}

bmfTrafficBarrierTemplate::bmfTrafficBarrierTemplate(const bmfTrafficBarrierTemplate& rOther)
{
   MakeCopy(rOther);
}

bmfTrafficBarrierTemplate::~bmfTrafficBarrierTemplate()
{
}

//======================== OPERATORS  =======================================
bmfTrafficBarrierTemplate& bmfTrafficBarrierTemplate::operator= (const bmfTrafficBarrierTemplate& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
bmfTrafficBarrier* bmfTrafficBarrierTemplate::CreateTrafficBarrier() const
{
   return new bmfTrafficBarrier( this );
}

//======================== ACCESS     =======================================
void bmfTrafficBarrierTemplate::SetName(const std::_tstring& name)
{
   PRECONDITION( name.length() > 0 );
   m_Name = name;
}

std::_tstring bmfTrafficBarrierTemplate::GetName() const
{
   return m_Name;
}

void bmfTrafficBarrierTemplate::SetTrafficBarrierShape(const gmTrafficBarrier* pTB)
{
   PRECONDITION( pTB != NULL );
   m_pTB = pTB;
}

const gmTrafficBarrier* bmfTrafficBarrierTemplate::GetTrafficBarrierShape()
{
   return m_pTB;
}

const gmTrafficBarrier* bmfTrafficBarrierTemplate::GetTrafficBarrierShape() const
{
   return m_pTB;
}

void bmfTrafficBarrierTemplate::SetConcrete(const matConcreteEx* pConc)
{
   PRECONDITION( pConc != NULL );
   m_pConc = pConc;
}

const matConcreteEx* bmfTrafficBarrierTemplate::GetConcrete()
{
   return m_pConc;
}

const matConcreteEx* bmfTrafficBarrierTemplate::GetConcrete() const
{
   return m_pConc;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void bmfTrafficBarrierTemplate::MakeCopy(const bmfTrafficBarrierTemplate& rOther)
{
   // Add copy code here...
   m_Name  = rOther.m_Name;
   m_pTB   = rOther.m_pTB;
   m_pConc = rOther.m_pConc;
}

void bmfTrafficBarrierTemplate::MakeAssignment(const bmfTrafficBarrierTemplate& rOther)
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
bool bmfTrafficBarrierTemplate::AssertValid() const
{
   return true;
}

void bmfTrafficBarrierTemplate::Dump(dbgDumpContext& os) const
{
   os << "Dump for bmfTrafficBarrierTemplate" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool bmfTrafficBarrierTemplate::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("bmfTrafficBarrierTemplate");

   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for bmfTrafficBarrierTemplate");

   TESTME_EPILOG("TrafficBarrierTemplate");
}
#endif // _UNITTEST
