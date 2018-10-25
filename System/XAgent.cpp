#include <System\SysLib.h>

/****************************************************************************
CLASS
   abfXAgent
****************************************************************************/

#include <System\XAgent.h>

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
abfXAgent::abfXAgent(const char* msg,bool isFatal,const char* file, long line) :
sysXBase( file, line )
{
   m_Message = msg;
   m_IsFatal = isFatal;
}

abfXAgent::abfXAgent(const abfXAgent& rOther) :
sysXBase( rOther )
{
   MakeCopy( rOther );
}

abfXAgent::~abfXAgent()
{
}

//======================== OPERATORS  =======================================
abfXAgent& abfXAgent::operator=(const abfXAgent& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================
void abfXAgent::Throw() const
{
   throw *static_cast<const abfXAgent*>(this); 
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
bool abfXAgent::IsFatal() const
{
   return m_IsFatal;
}

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void abfXAgent::MakeCopy(const abfXAgent& rOther)
{
   m_Message = rOther.m_Message;
   m_IsFatal = rOther.m_IsFatal;
}

void abfXAgent::MakeAssignment(const abfXAgent& rOther)
{
   sysXBase::MakeAssignment( rOther );
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
bool abfXAgent::AssertValid() const
{
   return true;
}

void abfXAgent::Dump(dbgDumpContext& os) const
{
   os << "Dump for abfXAgent" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool abfXAgent::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("abfXAgent");
   #pragma Reminder("Implement Unit Tests")
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for abfXAgent");
   TESTME_EPILOG("abfXAgent");
}
#endif // _UNITTEST
