#include <System\SysLib.h>

/****************************************************************************
CLASS
   abfBroker
****************************************************************************/

#include <System\Broker.h>
#include <System\XBroker.h>

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
abfBroker::abfBroker()
{
}

abfBroker::~abfBroker()
{
   // Must delete any owned agent before going out of scope.
   AgentIterator i;
   for ( i = m_Agents.begin(); i != m_Agents.end(); i++ )
   {
      AgentData& ad = (*i).second;
      if ( ad.second )
         delete ad.first;
   }
   m_Agents.clear();
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
#define AgentEntry( a,b,c ) EntryData( (a), AgentData( (b), (c) ) )
void abfBroker::RegisterAgent(abfAgent* pAgent, bool bOwnsAgent)
{
   Int32 routing_number = m_RoutingNumbers.ReserveNextId();
   pAgent->SetBroker( this );
   pAgent->SetRoutingNumber( routing_number );
   m_Agents.insert( AgentEntry( routing_number, pAgent, bOwnsAgent ) );
   pAgent->OnRegistered();
}

void abfBroker::UnregisterAgent(abfAgent* pAgent)
{
   Int32 routing_number = pAgent->GetRoutingNumber();

   AgentIterator found = m_Agents.find( routing_number );

   WARN( found == m_Agents.end(), "Agent not found" );

   if ( found != m_Agents.end() )
   {
      // Agent was found, unregister it
      AgentData& ad = (*found).second;
      abfAgent* ptr_agent = ad.first;
      CHECK( pAgent == ptr_agent );

      pAgent->OnUnregistering();
      ptr_agent->SetBroker( 0 );
      ptr_agent->SetRoutingNumber( -1 );

      if ( ad.second ) // OwnsAgent
         delete ptr_agent;

      m_Agents.erase( found );
   }
}

void abfBroker::SystemReset()
{
   AgentIterator begin = m_Agents.begin();
   AgentIterator end   = m_Agents.end();

   while ( begin != end )
   {
      abfAgent* ptr_agent = (*begin++).second.first;
      ptr_agent->Reset();
   }
}

Int32 abfBroker::Route(abfRequest& rRequest)
{
   // Make sure this is a clean request.
   rRequest.Reset();

   // Find the target agent
   Int32 routing_number = rRequest.GetRoutingNumber();
   if ( routing_number < 0 )
      THROW(abfXBroker,InvalidRoutingNumber);

   AgentIterator found = m_Agents.find( routing_number );

   if ( found == m_Agents.end() )
      THROW(abfXBroker,AgentNotFound);

   abfAgent* ptr_agent = (*found).second.first;

   // Dispatch the request to the agent.
   return ptr_agent->Dispatch( rRequest.GetId(), 0, (Uint32)&rRequest );
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
#if defined _DEBUG
bool abfBroker::AssertValid() const
{
   return true;
}

void abfBroker::Dump(dbgDumpContext& os) const
{
   os << "Dump for abfBroker" << endl;
   DumpAgents( os );
}

void abfBroker::DumpAgents(dbgDumpContext& os) const
{
   ConstAgentIterator begin = m_Agents.begin();
   ConstAgentIterator end   = m_Agents.end();

   while ( begin != end )
   {
      os << "=======================================================" <<endl;
      const abfAgent* ptr_agent = (*begin++).second.first;
      ptr_agent->Dump( os );
      os << endl;
   }
}
#endif // _DEBUG

#if defined _UNITTEST
bool abfBroker::TestMe(dbgLog& rlog)
{
   TESTME_PROLOGUE("abfBroker");
   #pragma Reminder("Implement Unit Tests")
   TEST_NOT_IMPLEMENTED("Unit Tests Not Implemented for abfBroker");
   TESTME_EPILOG("abfBroker");
}
#endif // _UNITTEST
