#include <System\SysLib.h>
#include <stdlib.h>
#include <System\EventHandler.h>
#include <System\XEventHandler.h>

//
// Searches the list of response table entries looking for a match
//
// Since class sysEventHandler doesn't have any entries, this default
// implementation just returns false
//
bool
sysEventHandler::Find(sysEventInfo&, sysEqualOperator)
{
  return false;
}

//
// Dispatch a message to an event handler given a found response table entry
//
Int32 sysEventHandler::DispatchEvent(sysEventInfo& eventInfo, Uint16 param1, Uint32 param2)
{
  PRECONDITION(eventInfo.m_Entry);
  return (*eventInfo.m_Entry->m_Dispatcher)(
           *eventInfo.m_Object,
           (sysAnyPMF&)eventInfo.m_Entry->m_Pmf,
           param1, param2
         );
}

//
// Search for the event given the message and it and dispatch to the
// event handler if found.
//
Int32 sysEventHandler::Dispatch(Uint16 event, Uint16 p1, Uint32 p2)
{
  sysEventInfo eventInfo( event );

  if ( !Find(eventInfo) )
     throw sysXEventHandler("Missing event handler", __FILE__, __LINE__ );

  return DispatchEvent(eventInfo, p1, p2);
}

//
// Low-level response table search function. Alloabf optional equal operator
// function to be provided
//
// Fills in Entry member of eventInfo and returns true if found.
//
bool sysEventHandler::SearchEntries(sysGenericTableEntry* entries,
                                   sysEventInfo&         eventInfo,
                                   sysEqualOperator      equal)
{
  if (equal) {
    while (entries->m_Dispatcher != 0) {
      if (equal(*entries, eventInfo)) {
        eventInfo.m_Entry = entries;
        return true;
      }
      entries++;
    }
  }
  else {
    while (entries->m_Dispatcher != 0) {
      if (entries->m_Event == eventInfo.m_Event) {
        eventInfo.m_Entry = entries;
        return true;
      }
      entries++;
    }
  }

  return false;
}
