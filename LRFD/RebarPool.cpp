///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\RebarPool.h>
#include <algorithm>

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
std::map<Int32, std::shared_ptr<matRebar> > lrfdRebarPool::ms_Rebar;
lrfdRebarPool::Killer lrfdRebarPool::ms_Killer;

Int32 hash( matRebar::Grade grade, matRebar::Type type, matRebar::Size size )
{
   Int32 hv = ((Int32)grade) | ((Int32)type) | ((Int32)size);
   return hv;
}

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

bool lrfdRebarPool::MapOldRebarKey(Int32 oldKey,matRebar::Grade& grade,matRebar::Type& type,matRebar::Size& size)
{
   // old pool had A615 A615 Steel, grade 60
   grade = matRebar::Grade60;
   type = matRebar::A615;

   switch(oldKey)
   {
   case -1: size = matRebar::bsNone; break;
   case 0:  size = matRebar::bsNone; break;
   case 3:  size = matRebar::bs3;  break;
   case 4:  size = matRebar::bs4;  break;
   case 5:  size = matRebar::bs5;  break;
   case 6:  size = matRebar::bs6;  break;
   case 7:  size = matRebar::bs7;  break;
   case 8:  size = matRebar::bs8;  break;
   case 9:  size = matRebar::bs9;  break;
   case 10: size = matRebar::bs10; break;
   case 11: size = matRebar::bs11; break;
   case 14: size = matRebar::bs14; break;
   case 18: size = matRebar::bs18; break;
   default:
      ATLASSERT(false);
      return false;
   }

   return true;
}

std::_tstring lrfdRebarPool::GetMaterialName(matRebar::Type type,matRebar::Grade grade)
{
   std::_tstring str;
   if ( type == matRebar::A615 )
   {
      switch(grade)
      {
      case matRebar::Grade40:
         str = _T("AASHTO M31 (A615) - Grade 40");
         break;
      case matRebar::Grade60:
         str = _T("AASHTO M31 (A615) - Grade 60");
         break;
      case matRebar::Grade75:
         str = _T("AASHTO M31 (A615) - Grade 75");
         break;
      case matRebar::Grade80:
         str = _T("AASHTO M31 (A615) - Grade 80");
         break;
      default:
         ATLASSERT(false); // not value
         str = _T("Unknown");
         break;
      }
   }
   else if ( type == matRebar::A706 )
   {
      switch(grade)
      {
      case matRebar::Grade60:
         str = _T("ASTM A706 - Grade 60");
         break;
      case matRebar::Grade80:
         str = _T("ASTM A706 - Grade 80");
         break;
      case matRebar::Grade40:
      case matRebar::Grade75:
      default:
         ATLASSERT(false); // not value
         str = _T("Unknown");
         break;
      }
   }
   else if ( type == matRebar::A1035 )
   {
      switch(grade)
      {
      case matRebar::Grade100:
         str = _T("ASTM A1035 - Grade 100");
         break;
      case matRebar::Grade40:
      case matRebar::Grade75:
      case matRebar::Grade80:
      default:
         ATLASSERT(false); // not value
         str = _T("Unknown");
         break;
      }
   }

   return str;
}

std::_tstring lrfdRebarPool::GetBarSize(matRebar::Size size)
{
   std::_tstring str;
   switch(size)
   {
   case matRebar::bs3:     str = _T("#3"); break;
   case matRebar::bs4:     str = _T("#4"); break;
   case matRebar::bs5:     str = _T("#5"); break;
   case matRebar::bs6:     str = _T("#6"); break;
   case matRebar::bs7:     str = _T("#7"); break;
   case matRebar::bs8:     str = _T("#8"); break;
   case matRebar::bs9:     str = _T("#9"); break;
   case matRebar::bs10:    str = _T("#10"); break;
   case matRebar::bs11:    str = _T("#11"); break;
   case matRebar::bs14:    str = _T("#14"); break;
   case matRebar::bs18:    str = _T("#18"); break;
   case matRebar::bsNone:  str = _T("None"); break;
   default:
      ATLASSERT(false);
   }

   return str;
}

matRebar::Size lrfdRebarPool::GetBarSize(LPCTSTR strSize)
{
   std::_tstring size(strSize);
   if ( size == _T("#3") )
      return matRebar::bs3;
   else if ( size == _T("#4") )
      return matRebar::bs4;
   else if ( size == _T("#5") )
      return matRebar::bs5;
   else if ( size == _T("#6") )
      return matRebar::bs6;
   else if ( size == _T("#7") )
      return matRebar::bs7;
   else if ( size == _T("#8") )
      return matRebar::bs8;
   else if ( size == _T("#9") )
      return matRebar::bs9;
   else if ( size == _T("#10") )
      return matRebar::bs10;
   else if ( size == _T("#11") )
      return matRebar::bs11;
   else if ( size == _T("#14") )
      return matRebar::bs14;
   else if ( size == _T("#18") )
      return matRebar::bs18;

   ATLASSERT(false); // should never get here
   return matRebar::bsNone;
}

void lrfdRebarPool::GetBarSizeRange(matRebar::Type type,matRebar::Grade grade,matRebar::Size& minSize,matRebar::Size& maxSize)
{
   minSize = matRebar::bs3;
   maxSize = matRebar::bs18;
}

void lrfdRebarPool::GetTransverseBarSizeRange(matRebar::Type type,matRebar::Grade grade,matRebar::Size& minSize,matRebar::Size& maxSize)
{
   minSize = matRebar::bs3;
   maxSize = matRebar::bs8; // LRFD 5.10.2.1
}

const matRebar* lrfdRebarPool::GetRebar(Int32 key)
{
   std::map<Int32, std::shared_ptr<matRebar> >::iterator found;

   found = ms_Rebar.find( key );
   if ( found == ms_Rebar.end() )
   {
      return nullptr;
   }

   return (*found).second.get();
} 

const matRebar* lrfdRebarPool::GetRebar( matRebar::Type type,
                                         matRebar::Grade grade,
                                         matRebar::Size size )
{
   return GetRebar( hash(grade,type,size) );
}

Int32 lrfdRebarPool::GetRebarKey(const matRebar* pRebar)
{
   return hash( pRebar->GetGrade(), pRebar->GetType(), pRebar->GetSize() );
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
   os << _T("Dump for lrfdRebarPool") << endl;
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

#define NEW_BAR(name,size,type,grade) \
   ms_Rebar.insert( std::make_pair(hash(matRebar::##grade,matRebar::##type,matRebar::##size),std::make_shared<matRebar>(_T(name),matRebar::##grade,matRebar::##type,matRebar::##size) ) );

//======================== LIFECYCLE  =======================================
lrfdRebarPool::lrfdRebarPool()
{
   // A615 (A615) Grade 60 must come first so we don't mess up
   // legacy rebar pool keys
   NEW_BAR(  "#3", bs3,  A615, Grade60 );
   NEW_BAR(  "#4", bs4,  A615, Grade60 ); 
   NEW_BAR(  "#5", bs5,  A615, Grade60 ); 
   NEW_BAR(  "#6", bs6,  A615, Grade60 ); 
   NEW_BAR(  "#7", bs7,  A615, Grade60 ); 
   NEW_BAR(  "#8", bs8,  A615, Grade60 ); 
   NEW_BAR(  "#9", bs9,  A615, Grade60 ); 
   NEW_BAR( "#10", bs10, A615, Grade60 ); 
   NEW_BAR( "#11", bs11, A615, Grade60 ); 
   NEW_BAR( "#14", bs14, A615, Grade60 ); 
   NEW_BAR( "#18", bs18, A615, Grade60 ); 

   NEW_BAR(  "#3", bs3,  A615, Grade40 );
   NEW_BAR(  "#4", bs4,  A615, Grade40 ); 
   NEW_BAR(  "#5", bs5,  A615, Grade40 ); 
   NEW_BAR(  "#6", bs6,  A615, Grade40 ); 
   NEW_BAR(  "#7", bs7,  A615, Grade40 ); 
   NEW_BAR(  "#8", bs8,  A615, Grade40 ); 
   NEW_BAR(  "#9", bs9,  A615, Grade40 ); 
   NEW_BAR( "#10", bs10, A615, Grade40 ); 
   NEW_BAR( "#11", bs11, A615, Grade40 ); 
   NEW_BAR( "#14", bs14, A615, Grade40 ); 
   NEW_BAR( "#18", bs18, A615, Grade40 ); 

   NEW_BAR(  "#3", bs3,  A615, Grade75 );
   NEW_BAR(  "#4", bs4,  A615, Grade75 ); 
   NEW_BAR(  "#5", bs5,  A615, Grade75 ); 
   NEW_BAR(  "#6", bs6,  A615, Grade75 ); 
   NEW_BAR(  "#7", bs7,  A615, Grade75 ); 
   NEW_BAR(  "#8", bs8,  A615, Grade75 ); 
   NEW_BAR(  "#9", bs9,  A615, Grade75 ); 
   NEW_BAR( "#10", bs10, A615, Grade75 ); 
   NEW_BAR( "#11", bs11, A615, Grade75 ); 
   NEW_BAR( "#14", bs14, A615, Grade75 ); 
   NEW_BAR( "#18", bs18, A615, Grade75 ); 

   NEW_BAR(  "#3", bs3,  A615, Grade80 );
   NEW_BAR(  "#4", bs4,  A615, Grade80 ); 
   NEW_BAR(  "#5", bs5,  A615, Grade80 ); 
   NEW_BAR(  "#6", bs6,  A615, Grade80 ); 
   NEW_BAR(  "#7", bs7,  A615, Grade80 ); 
   NEW_BAR(  "#8", bs8,  A615, Grade80 ); 
   NEW_BAR(  "#9", bs9,  A615, Grade80 ); 
   NEW_BAR( "#10", bs10, A615, Grade80 ); 
   NEW_BAR( "#11", bs11, A615, Grade80 ); 
   NEW_BAR( "#14", bs14, A615, Grade80 ); 
   NEW_BAR( "#18", bs18, A615, Grade80 ); 

   NEW_BAR(  "#3", bs3,  A706, Grade60 );
   NEW_BAR(  "#4", bs4,  A706, Grade60 ); 
   NEW_BAR(  "#5", bs5,  A706, Grade60 ); 
   NEW_BAR(  "#6", bs6,  A706, Grade60 ); 
   NEW_BAR(  "#7", bs7,  A706, Grade60 ); 
   NEW_BAR(  "#8", bs8,  A706, Grade60 ); 
   NEW_BAR(  "#9", bs9,  A706, Grade60 ); 
   NEW_BAR( "#10", bs10, A706, Grade60 ); 
   NEW_BAR( "#11", bs11, A706, Grade60 ); 
   NEW_BAR( "#14", bs14, A706, Grade60 ); 
   NEW_BAR( "#18", bs18, A706, Grade60 ); 

   NEW_BAR(  "#3", bs3,  A706, Grade80 );
   NEW_BAR(  "#4", bs4,  A706, Grade80 ); 
   NEW_BAR(  "#5", bs5,  A706, Grade80 ); 
   NEW_BAR(  "#6", bs6,  A706, Grade80 ); 
   NEW_BAR(  "#7", bs7,  A706, Grade80 ); 
   NEW_BAR(  "#8", bs8,  A706, Grade80 ); 
   NEW_BAR(  "#9", bs9,  A706, Grade80 ); 
   NEW_BAR( "#10", bs10, A706, Grade80 ); 
   NEW_BAR( "#11", bs11, A706, Grade80 ); 
   NEW_BAR( "#14", bs14, A706, Grade80 ); 
   NEW_BAR( "#18", bs18, A706, Grade80 ); 

   NEW_BAR(  "#3", bs3,  A1035, Grade100 );
   NEW_BAR(  "#4", bs4,  A1035, Grade100 ); 
   NEW_BAR(  "#5", bs5,  A1035, Grade100 ); 
   NEW_BAR(  "#6", bs6,  A1035, Grade100 ); 
   NEW_BAR(  "#7", bs7,  A1035, Grade100 ); 
   NEW_BAR(  "#8", bs8,  A1035, Grade100 ); 
   NEW_BAR(  "#9", bs9,  A1035, Grade100 ); 
   NEW_BAR( "#10", bs10, A1035, Grade100 ); 
   NEW_BAR( "#11", bs11, A1035, Grade100 ); 
   NEW_BAR( "#14", bs14, A1035, Grade100 ); 
   NEW_BAR( "#18", bs18, A1035, Grade100 ); 
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
lrfdRebarIter::lrfdRebarIter(matRebar::Type type,matRebar::Grade grade,bool bTransverseBarsOnly)
{
   m_Type  = type;
   m_Grade = grade;
   m_bTransverseBarsOnly = bTransverseBarsOnly;

   // Make sure the rebarpool is up and running
   lrfdRebarPool* pPool = lrfdRebarPool::GetInstance();

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
   {
      MakeAssignment( rOther );
   }

   return *this;
}

//======================== OPERATIONS =======================================
class BarDiaSorter
{
public:
   int operator() (const matRebar* ps1,const matRebar* ps2)
   {
      if (ps1->GetNominalDimension() == ps2->GetNominalDimension() )
      {
         return ps1->GetUltimateStrength() < ps2->GetUltimateStrength();
      }
      else
      {
         return ps1->GetNominalDimension() < ps2->GetNominalDimension();
      }
   }
};

void lrfdRebarIter::Begin()
{
   matRebar::Size minBarSize, maxBarSize;
   if ( m_bTransverseBarsOnly )
   {
      lrfdRebarPool::GetTransverseBarSizeRange(m_Type,m_Grade,minBarSize,maxBarSize);
   }
   else
   {
      lrfdRebarPool::GetBarSizeRange(m_Type,m_Grade,minBarSize,maxBarSize);
   }
   m_Bars.clear();
   CHECK(m_Bars.size() == 0);
   CHECK(m_Bars.empty() == true);
   std::map< Int32, std::shared_ptr<matRebar> >* pBars = &lrfdRebarPool::ms_Rebar;
   std::map< Int32, std::shared_ptr<matRebar> >::const_iterator iter;
   for ( iter = pBars->begin(); iter != pBars->end(); iter++ )
   {
      const std::shared_ptr<matRebar>& AutoPtr = iter->second;
      const matRebar* pRebar = AutoPtr.get();
      matRebar::Size size = pRebar->GetSize();
      if ( minBarSize <= size && size <= maxBarSize && pRebar->GetGrade() == m_Grade && pRebar->GetType() == m_Type )
      {
         m_Bars.push_back( pRebar );
      }
   }

   // sort by diameter to make list pretty
   std::sort(m_Bars.begin(), m_Bars.end(), BarDiaSorter());

   m_Begin   = m_Bars.begin();
   m_Current = m_Begin;
   m_End     = m_Bars.end();
}

void lrfdRebarIter::End()
{
   m_Current = m_End;
}

void lrfdRebarIter::Next()
{
   if ( m_Current != m_End )
   {
      m_Current++;
   }
}

void lrfdRebarIter::Move(Int32 pos)
{
   m_Current = m_Begin;
   if ( m_End < m_Begin + pos )
   {
      m_Current = m_End;
   }
   else
   {
      m_Current = m_Begin + pos;
   }
}

void lrfdRebarIter::MoveBy(Int32 dPos)
{
   m_Current += dPos;
   if ( m_End < m_Current )
   {
      m_Current = m_End;
   }
}

lrfdRebarIter::operator void*() const
{
   if ( m_Current != m_End )
   {
      return (void*)1;
   }
   else
   {
      return nullptr;
   }
}

const matRebar* lrfdRebarIter::GetCurrentRebar() const
{
   if ( *this )
   {
      return (*m_Current);
   }
   else
   {
      return nullptr;
   }
}
void lrfdRebarIter::SetGrade(matRebar::Grade grade)
{
   m_Grade = grade;
   Begin();
}

matRebar::Grade lrfdRebarIter::GetGrade() const
{
   return m_Grade;
}

void lrfdRebarIter::SetType(matRebar::Type type)
{
   m_Type = type;
   Begin();
}

matRebar::Type lrfdRebarIter::GetType() const
{
   return m_Type;
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

void lrfdRebarIter::MakeCopy(const lrfdRebarIter& rOther)
{
   m_Current = rOther.m_Current;
   m_Begin   = rOther.m_Begin;
   m_End     = rOther.m_End;
   m_Grade   = rOther.m_Grade;
   m_Type    = rOther.m_Type;
   m_bTransverseBarsOnly = rOther.m_bTransverseBarsOnly;
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
   //std::shared_ptr<matRebar> pDummyRebar( new matRebar );
   //Int32 key = pPool->GetRebarKey( pDummyRebar.get() );
   //TRY_TESTME( key == INVALID_INDEX );

   TESTME_EPILOG("lrfdRebarPool");
}

bool lrfdRebarIter::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("lrfdRebarIter");
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for lrfdRebarIter");
   TESTME_EPILOG("lrfdRebarIter");
}
#endif // _UNITTEST


