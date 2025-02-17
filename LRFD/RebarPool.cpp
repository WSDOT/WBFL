///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright � 1999-2025  Washington State Department of Transportation
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

using namespace WBFL::LRFD;

RebarPool* RebarPool::ms_pInstance = nullptr;
RebarPool::Pool RebarPool::ms_Rebar;
RebarPool::Killer RebarPool::ms_Killer;

Int32 hash( WBFL::Materials::Rebar::Grade grade, WBFL::Materials::Rebar::Type type, WBFL::Materials::Rebar::Size size )
{
   Int32 hv = ((Int32)grade) | ((Int32)type) | ((Int32)size);
   return hv;
}

const RebarPool* RebarPool::GetInstance()
{
   if ( !ms_pInstance )
   {
      ms_pInstance = new RebarPool();
      ms_Killer.SetSingleton( ms_pInstance );
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

bool RebarPool::MapOldRebarKey(Int32 oldKey,WBFL::Materials::Rebar::Grade& grade,WBFL::Materials::Rebar::Type& type,WBFL::Materials::Rebar::Size& size)
{
   // old pool had A615 Grade 60 Steel so the keys were just the bar sizes
   // this method returns the full set of rebar key parameters for the old keys
   grade = WBFL::Materials::Rebar::Grade::Grade60;
   type = WBFL::Materials::Rebar::Type::A615;

   switch(oldKey)
   {
   case -1: size = WBFL::Materials::Rebar::Size::bsNone; break;
   case 0:  size = WBFL::Materials::Rebar::Size::bsNone; break;
   case 3:  size = WBFL::Materials::Rebar::Size::bs3;  break;
   case 4:  size = WBFL::Materials::Rebar::Size::bs4;  break;
   case 5:  size = WBFL::Materials::Rebar::Size::bs5;  break;
   case 6:  size = WBFL::Materials::Rebar::Size::bs6;  break;
   case 7:  size = WBFL::Materials::Rebar::Size::bs7;  break;
   case 8:  size = WBFL::Materials::Rebar::Size::bs8;  break;
   case 9:  size = WBFL::Materials::Rebar::Size::bs9;  break;
   case 10: size = WBFL::Materials::Rebar::Size::bs10; break;
   case 11: size = WBFL::Materials::Rebar::Size::bs11; break;
   case 14: size = WBFL::Materials::Rebar::Size::bs14; break;
   case 18: size = WBFL::Materials::Rebar::Size::bs18; break;
   default:
      CHECK(false);
      return false;
   }

   return true;
}

std::_tstring RebarPool::GetMaterialName(WBFL::Materials::Rebar::Type type,WBFL::Materials::Rebar::Grade grade)
{
   std::_tstring str;
   if ( type == WBFL::Materials::Rebar::Type::A615 )
   {
      switch(grade)
      {
      case WBFL::Materials::Rebar::Grade::Grade40:
         str = _T("AASHTO M31 (A615) - Grade 40");
         break;
      case WBFL::Materials::Rebar::Grade::Grade60:
         str = _T("AASHTO M31 (A615) - Grade 60");
         break;
      case WBFL::Materials::Rebar::Grade::Grade75:
         str = _T("AASHTO M31 (A615) - Grade 75");
         break;
      case WBFL::Materials::Rebar::Grade::Grade80:
         str = _T("AASHTO M31 (A615) - Grade 80");
         break;
      default:
         CHECK(false); // not value
         str = _T("Unknown");
         break;
      }
   }
   else if ( type == WBFL::Materials::Rebar::Type::A706 )
   {
      switch(grade)
      {
      case WBFL::Materials::Rebar::Grade::Grade60:
         str = _T("ASTM A706 - Grade 60");
         break;
      case WBFL::Materials::Rebar::Grade::Grade80:
         str = _T("ASTM A706 - Grade 80");
         break;
      case WBFL::Materials::Rebar::Grade::Grade40:
      case WBFL::Materials::Rebar::Grade::Grade75:
      default:
         CHECK(false); // not value
         str = _T("Unknown");
         break;
      }
   }
   else if ( type == WBFL::Materials::Rebar::Type::A1035 )
   {
      switch(grade)
      {
      case WBFL::Materials::Rebar::Grade::Grade100:
         str = _T("ASTM A1035 - Grade 100");
         break;
      case WBFL::Materials::Rebar::Grade::Grade40:
      case WBFL::Materials::Rebar::Grade::Grade75:
      case WBFL::Materials::Rebar::Grade::Grade80:
      default:
         CHECK(false); // not value
         str = _T("Unknown");
         break;
      }
   }

   return str;
}

std::_tstring RebarPool::GetBarSize(WBFL::Materials::Rebar::Size size)
{
   std::_tstring str;
   switch(size)
   {
   case WBFL::Materials::Rebar::Size::bs3:     str = _T("#3"); break;
   case WBFL::Materials::Rebar::Size::bs4:     str = _T("#4"); break;
   case WBFL::Materials::Rebar::Size::bs5:     str = _T("#5"); break;
   case WBFL::Materials::Rebar::Size::bs6:     str = _T("#6"); break;
   case WBFL::Materials::Rebar::Size::bs7:     str = _T("#7"); break;
   case WBFL::Materials::Rebar::Size::bs8:     str = _T("#8"); break;
   case WBFL::Materials::Rebar::Size::bs9:     str = _T("#9"); break;
   case WBFL::Materials::Rebar::Size::bs10:    str = _T("#10"); break;
   case WBFL::Materials::Rebar::Size::bs11:    str = _T("#11"); break;
   case WBFL::Materials::Rebar::Size::bs14:    str = _T("#14"); break;
   case WBFL::Materials::Rebar::Size::bs18:    str = _T("#18"); break;
   case WBFL::Materials::Rebar::Size::bsNone:  str = _T("None"); break;
   default:
      CHECK(false);
   }

   return str;
}

WBFL::Materials::Rebar::Size RebarPool::GetBarSize(LPCTSTR strSize)
{
   std::_tstring size(strSize);
   if ( size == _T("#3") )
      return WBFL::Materials::Rebar::Size::bs3;
   else if ( size == _T("#4") )
      return WBFL::Materials::Rebar::Size::bs4;
   else if ( size == _T("#5") )
      return WBFL::Materials::Rebar::Size::bs5;
   else if ( size == _T("#6") )
      return WBFL::Materials::Rebar::Size::bs6;
   else if ( size == _T("#7") )
      return WBFL::Materials::Rebar::Size::bs7;
   else if ( size == _T("#8") )
      return WBFL::Materials::Rebar::Size::bs8;
   else if ( size == _T("#9") )
      return WBFL::Materials::Rebar::Size::bs9;
   else if ( size == _T("#10") )
      return WBFL::Materials::Rebar::Size::bs10;
   else if ( size == _T("#11") )
      return WBFL::Materials::Rebar::Size::bs11;
   else if ( size == _T("#14") )
      return WBFL::Materials::Rebar::Size::bs14;
   else if ( size == _T("#18") )
      return WBFL::Materials::Rebar::Size::bs18;

   CHECK(false); // should never get here
   return WBFL::Materials::Rebar::Size::bsNone;
}

void RebarPool::GetBarSizeRange(WBFL::Materials::Rebar::Type type,WBFL::Materials::Rebar::Grade grade,WBFL::Materials::Rebar::Size& minSize,WBFL::Materials::Rebar::Size& maxSize)
{
   minSize = WBFL::Materials::Rebar::Size::bs3;
   maxSize = WBFL::Materials::Rebar::Size::bs18;
}

void RebarPool::GetTransverseBarSizeRange(WBFL::Materials::Rebar::Type type,WBFL::Materials::Rebar::Grade grade,WBFL::Materials::Rebar::Size& minSize,WBFL::Materials::Rebar::Size& maxSize)
{
   minSize = WBFL::Materials::Rebar::Size::bs3;
   maxSize = WBFL::Materials::Rebar::Size::bs8; // LRFD 5.10.2.1
}

const WBFL::Materials::Rebar* RebarPool::GetRebar(Int32 key) const
{
   std::map<Int32, std::shared_ptr<WBFL::Materials::Rebar> >::iterator found;

   found = ms_Rebar.find( key );
   if ( found == ms_Rebar.end() )
   {
      return nullptr;
   }

   return (*found).second.get();
} 

const WBFL::Materials::Rebar* RebarPool::GetRebar( WBFL::Materials::Rebar::Type type,
                                         WBFL::Materials::Rebar::Grade grade,
                                         WBFL::Materials::Rebar::Size size ) const
{
   return GetRebar( hash(grade,type,size) );
}

Int32 RebarPool::GetRebarKey(const WBFL::Materials::Rebar* pRebar) const
{
   return pRebar ? hash(pRebar->GetGrade(), pRebar->GetType(), pRebar->GetSize()) : -1;
}

#define NEW_BAR(name,size,type,grade) \
   ms_Rebar.insert( std::make_pair(hash(WBFL::Materials::Rebar::Grade::##grade,WBFL::Materials::Rebar::Type::##type,WBFL::Materials::Rebar::Size::##size),std::make_shared<WBFL::Materials::Rebar>(_T(name),WBFL::Materials::Rebar::Grade::##grade,WBFL::Materials::Rebar::Type::##type,WBFL::Materials::Rebar::Size::##size) ) );

RebarPool::RebarPool()
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

/////////////////////////////////

RebarIter::RebarIter(WBFL::Materials::Rebar::Type type,WBFL::Materials::Rebar::Grade grade,bool bTransverseBarsOnly)
{
   m_Type  = type;
   m_Grade = grade;
   m_bTransverseBarsOnly = bTransverseBarsOnly;

   // Make sure the rebar pool is up and running
   const RebarPool* pPool = RebarPool::GetInstance();

   Begin();
}

class BarDiaSorter
{
public:
   int operator() (const WBFL::Materials::Rebar* ps1,const WBFL::Materials::Rebar* ps2)
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

void RebarIter::Begin()
{
   WBFL::Materials::Rebar::Size minBarSize, maxBarSize;
   if ( m_bTransverseBarsOnly )
   {
      RebarPool::GetTransverseBarSizeRange(m_Type,m_Grade,minBarSize,maxBarSize);
   }
   else
   {
      RebarPool::GetBarSizeRange(m_Type,m_Grade,minBarSize,maxBarSize);
   }
   m_Bars.clear();
   CHECK(m_Bars.size() == 0);
   CHECK(m_Bars.empty() == true);
   std::map< Int32, std::shared_ptr<WBFL::Materials::Rebar> >* pBars = &RebarPool::ms_Rebar;
   std::map< Int32, std::shared_ptr<WBFL::Materials::Rebar> >::const_iterator iter;
   for ( iter = pBars->begin(); iter != pBars->end(); iter++ )
   {
      const std::shared_ptr<WBFL::Materials::Rebar>& AutoPtr = iter->second;
      const WBFL::Materials::Rebar* pRebar = AutoPtr.get();
      WBFL::Materials::Rebar::Size size = pRebar->GetSize();
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

void RebarIter::End()
{
   m_Current = m_End;
}

void RebarIter::Next()
{
   if ( m_Current != m_End )
   {
      m_Current++;
   }
}

void RebarIter::Move(Int32 pos)
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

void RebarIter::MoveBy(Int32 dPos)
{
   m_Current += dPos;
   if ( m_End < m_Current )
   {
      m_Current = m_End;
   }
}

RebarIter::operator void*() const
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

const WBFL::Materials::Rebar* RebarIter::GetCurrentRebar() const
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
void RebarIter::SetGrade(WBFL::Materials::Rebar::Grade grade)
{
   m_Grade = grade;
   Begin();
}

WBFL::Materials::Rebar::Grade RebarIter::GetGrade() const
{
   return m_Grade;
}

void RebarIter::SetType(WBFL::Materials::Rebar::Type type)
{
   m_Type = type;
   Begin();
}

WBFL::Materials::Rebar::Type RebarIter::GetType() const
{
   return m_Type;
}
