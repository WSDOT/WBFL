#include <System\SysLib.h>

/****************************************************************************
CLASS
   abfAgent
****************************************************************************/

#include <System\Agent.h>
#include <System\Broker.h>

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
abfAgent::abfAgent()
{
   m_pBroker = 0;
}

abfAgent::~abfAgent()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void abfAgent::DefineTier(TierLevel level,Int32 minRequestId, Int32 maxRequestId)
{
   TierInfo ti;
   ti.m_TierLevel    = level;
   ti.m_MinRequestId = minRequestId;
   ti.m_MaxRequestId = maxRequestId;
   ti.m_IsValid      = false;

   m_TierInfo.push_back( ti );
}

void abfAgent::Reset()
{
   TierInfoIterator begin = m_TierInfo.begin();
   TierInfoIterator end   = m_TierInfo.end();

   while ( begin != end )
   {
      TierInfo& ti = *begin++;
      ti.m_IsValid = false;
   }
}

void abfAgent::OnRegistered()
{
}

void abfAgent::OnUnregistering()
{
}

//======================== ACCESS     =======================================
void abfAgent::SetBroker(abfBroker* pBroker)
{
   m_pBroker = pBroker;
}

//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
Int32 abfAgent::DispatchEvent(sysEventInfo& info, Uint16 p1, Uint32 p2)
{
   abfRequest* pRequest = (abfRequest*)(p2);
   ValidateTier( pRequest->GetId() );
   return sysEventHandler::DispatchEvent( info, p1, p2 );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void abfAgent::ValidateTier( Int32 requestId )
{
   TierInfo& ti = GetTierInfo( requestId );

   if ( ti.m_IsValid )
      return;

   switch( ti.m_TierLevel )
   {
   case Level1:
      ValidateTier1();
      break;

   case Level2:
      ValidateTier2();
      break;

   case Level3:
      ValidateTier3();
      break;

   case Level4:
      ValidateTier4();
      break;

   case Level5:
      ValidateTier5();
      break;

   case Level6:
      ValidateTier6();
      break;

   case Level7:
      ValidateTier7();
      break;

   case Level8:
      ValidateTier8();
      break;

   case Level9:
      ValidateTier9();
      break;
   }

   ti.m_IsValid = true;
}

//======================== ACCESS     =======================================

TierInfo& abfAgent::GetTierInfo( Int32 requestId )
{
   TierInfoIterator begin = m_TierInfo.begin();
   TierInfoIterator end   = m_TierInfo.end();

   TierInfo& ti = *begin;
   while ( begin != end )
   {
      if ( (ti.m_MinRequestId <= requestId) && (requestId < ti.m_MaxRequestId) )
         break;

      begin++;
   }

   return ti;
}

//======================== INQUERY    =======================================

//======================== DEBUG      =======================================
#if defined _DEBUG
bool abfAgent::AssertValid() const
{
   return true;
}

void abfAgent::Dump(dbgDumpContext& os) const
{
   os << "Dump for abfAgent" << endl;
   os << "Routing Number : " << GetRoutingNumber() << endl;
   os << "Tier Information" << endl;
   os << "Number of levels : " << (Uint32)m_TierInfo.size() << endl;
   ConstTierInfoIterator i;
   for ( i = m_TierInfo.begin(); i != m_TierInfo.end(); i++ )
   {
      const TierInfo& ti = *i;
      os << "Tier Level : " << (Uint32)ti.m_TierLevel << endl;
      os << "   Min Request Id : " << ti.m_MinRequestId << endl;
      os << "   Max Request Id : " << ti.m_MaxRequestId << endl;
      os << "   Tier Status    : " << (ti.m_IsValid ? "Valid" : "Invalid") << endl;
   }
}
#endif // _DEBUG

#if defined _UNITTEST
bool abfAgent::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("abfAgent");
   #pragma Reminder("Implement Unit Tests")
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for abfAgent");
   TESTME_EPILOG("abfAgent");
}
#endif // _UNITTEST
