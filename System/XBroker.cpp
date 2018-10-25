#include <System\SysLib.h>

/****************************************************************************
CLASS
   abfXBroker
****************************************************************************/

#include <System\XBroker.h>        // class implementation

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
abfXBroker::abfXBroker(Reason reason,const char* file,long line) :
sysXBase( file, line ),
m_Reason( reason )
{
}

abfXBroker::abfXBroker(const abfXBroker& rOther) :
sysXBase( rOther )
{
   MakeCopy( rOther );
}

abfXBroker::~abfXBroker()
{
}

//======================== OPERATORS  =======================================
abfXBroker& abfXBroker::operator=(const abfXBroker& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================
void abfXBroker::Throw() const
{
   throw *static_cast<const abfXBroker*>(this); 
}

void abfXBroker::GetErrorMessage(std::string* pMsg) const
{
   sysXBase::GetErrorMessage( pMsg );
   std::string reason;

  switch( m_Reason )
   {
     case InvalidRoutingNumber:
        reason = "Invalid Routing Number";
     break;
 
     case AgentNotFound:
        reason = "Agent Not Found";
     break;
   }

  (*pMsg) += "\n";
  (*pMsg) += reason;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void abfXBroker::MakeCopy(const abfXBroker& rOther)
{
   m_Reason = rOther.m_Reason;
}

void abfXBroker::MakeAssignment(const abfXBroker& rOther)
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
bool abfXBroker::AssertValid() const
{
   return true;
}

void abfXBroker::Dump(dbgDumpContext& os) const
{
   os << "Dump for abfXBroker" << endl;
}
#endif // _DEBUG

#if defined _UNITTEST
bool abfXBroker::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("abfXBroker");
   #pragma Reminder("Implement Unit Tests")
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for abfXBroker");
   TESTME_EPILOG("abfXBroker");
}
#endif // _UNITTEST
