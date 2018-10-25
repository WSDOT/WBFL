///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2010  Washington State Department of Transportation
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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\RebarPool.h>
#include <Units\SysUnits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdRebarPool
****************************************************************************/

lrfdRebarPool* lrfdRebarPool::ms_pInstance = 0;
std::vector<boost::shared_ptr<matRebar> > lrfdRebarPool::ms_Rebar;
lrfdRebarPool::Killer lrfdRebarPool::ms_Killer;

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdRebarPool::~lrfdRebarPool()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

//======================== ACCESS     =======================================
lrfdRebarPool* lrfdRebarPool::GetInstance()
{
   if ( !ms_pInstance )
   {
      ms_pInstance = new lrfdRebarPool;
      ms_Killer.SetDoomed( ms_pInstance );
   }

   return ms_pInstance;
}

// Maps rebar key (the rebar designation number) to an index in ms_Rebar
const Int16 gs_KeyMap[19] = {
-1,  // 0
-1,  // 1
-1,  // 2
 0,  // 3
 1,  // 4
 2,  // 5
 3,  // 6
 4,  // 7
 5,  // 8
 6,  // 9
 7,  // 10
 8,  // 11
-1,  // 12
-1,  // 13
 9,  // 14
-1,  // 15
-1,  // 16
-1,  // 17
10   // 18
};

const matRebar* lrfdRebarPool::GetRebar(BarSizeType key)
{
   ATLASSERT( 0 <= key && key <= 18 );
   ATLASSERT( gs_KeyMap[key] != -1 );

   if ( 0 <= key && key < 19 )
   {
       Int16 index = gs_KeyMap[key];
       if ( index == -1 )
          return NULL;

       return ms_Rebar[index].get(); 
   }

   return NULL;
}

BarSizeType lrfdRebarPool::GetRebarKey(const matRebar* pRebar)
{
   CHECK( pRebar != NULL );

   Int16 index = 0; // Index into ms_Rebar where pRebar is located
   RebarPool::iterator i;
   for ( i = ms_Rebar.begin(); i != ms_Rebar.end(); i++, index++ )
   {
      boost::shared_ptr<matRebar>& ptr_rebar = *i;
      if ( ptr_rebar.get() == pRebar ) // do they point to the same location?
         break; // Yes, we found it.
   }

   // We went through the entire loop and didn't find it
   if ( (Int16)ms_Rebar.size() <= index)
      return INVALID_BAR_SIZE;

   // We've got the index, now back out the key from gs_KeyMap
   for ( BarSizeType key = 0; key < 19; key++ )
   {
      if ( gs_KeyMap[key] == index )
         return key;
   }

   CHECKX( false, "Code should never get here!!!" );
   return INVALID_BAR_SIZE;
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdRebarPool::AssertValid() const
{
   return true;
}

void lrfdRebarPool::Dump(dbgDumpContext& os) const
{
   os << "Dump for lrfdRebarPool" << endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

#define NEW_BAR(name,nd,na,fu,fy,e) \
   ms_Rebar.push_back( boost::shared_ptr<matRebar>(new matRebar(name,::ConvertToSysUnits(fu, unitMeasure::KSI),::ConvertToSysUnits(fy, unitMeasure::KSI),::ConvertToSysUnits(e, unitMeasure::KSI),matRebar::Circle,::ConvertToSysUnits(nd,unitMeasure::Inch),::ConvertToSysUnits(na,unitMeasure::Inch2) ) ) );

//======================== LIFECYCLE  =======================================
lrfdRebarPool::lrfdRebarPool()
{
   // Based on Table 5.1-2, WSDOT BDM, April 1993
   NEW_BAR(  "#3 (10M)",0.375, 0.11, 90, 60, 29000 );
   NEW_BAR(  "#4 (13M)",0.50 , 0.20, 90, 60, 29000 ); 
   NEW_BAR(  "#5 (16M)",0.625, 0.31, 90, 60, 29000 );
   NEW_BAR(  "#6 (19M)",0.75 , 0.44, 90, 60, 29000 );
   NEW_BAR(  "#7 (22M)",0.875, 0.60, 90, 60, 29000 ); 
   NEW_BAR(  "#8 (25M)",1.0  , 0.79, 90, 60, 29000 );
   NEW_BAR(  "#9 (29M)",1.13 , 1.00, 90, 60, 29000 ); 
   NEW_BAR( "#10 (32M)",1.27 , 1.27, 90, 60, 29000 );
   NEW_BAR( "#11 (36M)",1.41 , 1.56, 90, 60, 29000 );
   NEW_BAR( "#14 (43M)",1.69 , 2.25, 90, 60, 29000 );
   NEW_BAR( "#18 (57M)",2.26 , 4.00, 90, 60, 29000 );
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


/****************************************************************************
CLASS
   lrfdRebarIter
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
lrfdRebarIter::lrfdRebarIter()
{
   SetRange();
   Begin();
}

lrfdRebarIter::lrfdRebarIter(const lrfdRebarIter& rOther)
{
   MakeCopy( rOther );
}

lrfdRebarIter::~lrfdRebarIter()
{
}

//======================== OPERATORS  =======================================
lrfdRebarIter& lrfdRebarIter::operator=(const lrfdRebarIter& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================
void lrfdRebarIter::Begin()
{
   m_CurrentIdx = m_Begin;
}

void lrfdRebarIter::End()
{
   m_CurrentIdx = m_End;
}

void lrfdRebarIter::Next()
{
   m_CurrentIdx++;
}

void lrfdRebarIter::Move(Int32 pos)
{
   m_CurrentIdx = pos;
}

void lrfdRebarIter::MoveBy(Int32 dPos)
{
   m_CurrentIdx = dPos;
}

lrfdRebarIter::operator void*() const
{
   if ( m_CurrentIdx >= m_End )
      return 0;
   else
      return (void*)1;
}

const matRebar* lrfdRebarIter::GetCurrentRebar() const
{
   if ( *this )
   {
      return lrfdRebarPool::ms_Rebar[m_CurrentIdx].get();
   }
   else
   {
      return 0;
   }
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdRebarIter::AssertValid() const
{
   return true;
}

void lrfdRebarIter::Dump(dbgDumpContext& os) const
{
   os << "Dump for lrfdRebarIter" << endl;
}

#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
void lrfdRebarIter::MakeAssignment(const lrfdRebarIter& rOther)
{
   MakeCopy( rOther );
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdRebarIter::SetRange()
{
   m_Begin = 0;
   m_End   = lrfdRebarPool::ms_Rebar.size();
}

void lrfdRebarIter::MakeCopy(const lrfdRebarIter& rOther)
{
   m_CurrentIdx = rOther.m_CurrentIdx;
   m_Begin      = rOther.m_Begin;
   m_End        = rOther.m_End;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


#if defined _UNITTEST

bool lrfdRebarPool::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdRebarPool");

   lrfdRebarPool* pPool = lrfdRebarPool::GetInstance();

   // Test to see if the rebar returned from the iterator can
   // be found in the pool.
   lrfdRebarIter iter;
   for ( iter.Begin(); iter; iter.Next() )
   {
      const matRebar* pRebar1 = iter.GetCurrentRebar();
      BarSizeType key = pPool->GetRebarKey( pRebar1 );
      const matRebar* pRebar2 = pPool->GetRebar( key );
      TRY_TESTME( pRebar1 == pRebar2 );
   }

   // Test to see pool correctly rejects a rebar not in the pool
   boost::shared_ptr<matRebar> pDummyRebar( new matRebar );
   Int32 key = pPool->GetRebarKey( pDummyRebar.get() );
   TRY_TESTME( key == INVALID_INDEX );

   TESTME_EPILOG("lrfdRebarPool");
}

bool lrfdRebarIter::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdRebarIter");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for lrfdRebarIter");
   TESTME_EPILOG("lrfdRebarIter");
}
#endif // _UNITTEST


