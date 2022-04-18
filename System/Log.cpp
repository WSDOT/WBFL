///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysLib.h>

/****************************************************************************
CLASS
   dbgLog
****************************************************************************/

#include <System\Log.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
dbgLog::dbgLog(): 
m_NumErrors(0)
{
   m_pDumpCtx = &m_DefDumpCtx;
}

dbgLog::dbgLog(dbgDumpContext* pDumpCtx): 
m_pDumpCtx( pDumpCtx ),
m_NumErrors(0)
{
}

dbgLog::~dbgLog()
{
}

//======================== OPERATORS  =======================================

dbgLog& dbgLog::operator<<(const std::_tstring& s)
{
   *m_pDumpCtx << s;
   return *this;
}

dbgLog& dbgLog::operator<<(LPCTSTR s)
{
   *m_pDumpCtx << s;
   return *this;
}

dbgLog& dbgLog::operator<<(TCHAR c)
{
   *m_pDumpCtx << c;
   return *this;
}

dbgLog& dbgLog::operator<<(bool n)
{
   *m_pDumpCtx << n;
   return *this;
}

dbgLog& dbgLog::operator<<(Int16 n)
{
   *m_pDumpCtx << n;
   return *this;
}

dbgLog& dbgLog::operator<<(Uint16 n)
{
   *m_pDumpCtx << n;
   return *this;
}

dbgLog& dbgLog::operator<<(Int32 n)
{
   *m_pDumpCtx << n;
   return *this;
}

dbgLog& dbgLog::operator<<(Uint32 n)
{
   *m_pDumpCtx << n;
   return *this;
}

dbgLog& dbgLog::operator<<(Int64 n)
{
   *m_pDumpCtx << n;
   return *this;
}

dbgLog& dbgLog::operator<<(Uint64 n)
{
   *m_pDumpCtx << n;
   return *this;
}

dbgLog& dbgLog::operator<<(Float32 n)    
{
   *m_pDumpCtx << n;
   return *this;
}

dbgLog& dbgLog::operator<<(Float64 n)
{
   *m_pDumpCtx << n;
   return *this;
}

dbgLog& dbgLog::operator<<(Float80 n)
{
   *m_pDumpCtx << n;
   return *this;
}

dbgLog& dbgLog::operator<<(void * n)
{
   *m_pDumpCtx << n;
   return *this;
}

// wild-ass code to make the manipulator stuff work.
dbgLog& dbgLog::operator<<(dbgLog& (*pf)(dbgLog&))
{
   (*pf)(*this);
   return *this;
}


//======================== OPERATIONS =======================================
void dbgLog::AddEntryToLog(std::_tstring& msg,  dbgLog::EntryType type)
{
   if (type == dbgLog::Failed)
   {
      m_NumErrors++; // can set a break here when test fails
   }

   LogEntry ent;
   ent.Type = type;
   ent.Msg  = msg;

   m_ErrorLog.push_back(ent);
}

size_t dbgLog::GetNumEntries() const
{
   return m_ErrorLog.size();
}

size_t dbgLog::GetNumErrors() const
{
   return m_NumErrors;
}

size_t dbgLog::GetTestCount(EntryType type) const
{
   size_t cTests = 0;
   for ( ConstEntryVecIterator i = m_ErrorLog.begin(); i != m_ErrorLog.end(); i++ )
   {
      if ( (*i).Type == type )
         cTests++;
   }

   return cTests;
}

void dbgLog::DumpFilteredLog(dbgLog::EntryType type)
{
   for (EntryVecIterator i=m_ErrorLog.begin(); i!=m_ErrorLog.end(); i++)
   {
      if ((*i).Type==type)
      {
        // endl doesn't seem to be working correctly in this special case.
         *m_pDumpCtx << (*i).Msg << endl;
      }
   }
}

void dbgLog::DumpEntireLog()
{
   for (EntryVecIterator i=m_ErrorLog.begin(); i!=m_ErrorLog.end(); i++)
   {
      // endl doesn't seem to be working correctly in this special case.
      *m_pDumpCtx << (*i).Msg << endl;
   }
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
