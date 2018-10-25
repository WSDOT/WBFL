#include <System\SysLib.h>

/****************************************************************************
CLASS
   sysXEventHandler
****************************************************************************/

#include <System\XEventHandler.h>

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
sysXEventHandler::sysXEventHandler(const char* msg,const char* file,long line) :
sysXBase( file, line ),
m_Message( msg )
{
}

sysXEventHandler::sysXEventHandler(const sysXEventHandler& rOther) :
sysXBase( rOther )
{
   MakeCopy( rOther );
}

sysXEventHandler::~sysXEventHandler()
{
}

//======================== OPERATORS  =======================================
sysXEventHandler& sysXEventHandler::operator=(const sysXEventHandler& rOther)
{
   if ( this != &rOther )
      MakeAssignment( rOther );

   return *this;
}

//======================== OPERATIONS =======================================
void sysXEventHandler::Throw() const
{
   throw *static_cast<const sysXEventHandler*>(this); 
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void sysXEventHandler::MakeCopy(const sysXEventHandler& rOther)
{
   m_Message = rOther.m_Message;
}

void sysXEventHandler::MakeAssignment(const sysXEventHandler& rOther)
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

