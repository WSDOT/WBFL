#include <WBFL.h>

/****************************************************************************
CLASS
   dbgTestLogger
****************************************************************************/

#include <System\TestLogger.h>
#include <iostream>

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
dbgTestLogger::dbgTestLogger(): 
os(std::cout),
m_NumErrors(0)
{
}

dbgTestLogger::dbgTestLogger(std::ostream& ros): 
os(ros),
m_NumErrors(0)
{
}

dbgTestLogger::~dbgTestLogger()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void dbgTestLogger::AddEntryToLog(std::string& msg, bool isError)
{
   if (isError) m_NumErrors++;

   LogEntry ent;
   ent.IsError = isError;
   ent.Msg = msg;

   m_ErrorLog.push_back(ent);
}

Int32 dbgTestLogger::GetNumEntries() const
{
   return m_ErrorLog.size();
}

Int32 dbgTestLogger::GetNumErrors() const
{
   return m_NumErrors;
}

void dbgTestLogger::DumpErrorsInLog(std::ostream& os)
{
   for (EntryVecIterator i=m_ErrorLog.begin(); i!=m_ErrorLog.end(); i++)
   {
      if ((*i).IsError)
         os<< (*i).Msg;
   }
}

void dbgTestLogger::DumpEntireLog(std::ostream& os)
{
   for (EntryVecIterator i=m_ErrorLog.begin(); i!=m_ErrorLog.end(); i++)
         os<< (*i).Msg;
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
