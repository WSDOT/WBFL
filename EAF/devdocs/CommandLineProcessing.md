Command Line Processing {#WBFL_EAF_CommandLine}
==================================================
`IEAFProcessCommandLine` (`Include\EAF\EAFUIIntegration.h`) lets an agent - core or extension - handle
its own command-line switches:
~~~
class IEAFProcessCommandLine
{
public:
   // Return TRUE if the command line was handled, otherwise FALSE. cmdInfo is the basic command
   // line info from the application class; re-parse it with your own CEAFCommandLineInfo-derived
   // class to get your own parameters:
   //
   // CMyCommandLineInfo ci;
   // EAFGetApp()->ParseCommandLine(ci);
   // cmdInfo = ci; // copies the base parameters - note this slices the object
   // if (ci.IsThisMyCommandLine) { DoSomethingUseful(); return TRUE; }
   // return FALSE;
   virtual BOOL ProcessCommandLineOptions(CEAFCommandLineInfo& cmdInfo) = 0;
};
~~~
Note the interface comment: **do not register this with the broker.** It's discovered differently
from every other integration point on this page - `CEAFBrokerDocument::ProcessCommandLineOptions`
(`WBFL\EAF\EAFBrokerDocument.cpp`) probes every loaded agent with `dynamic_pointer_cast`, core agents
first and then extension agents, calling `ProcessCommandLineOptions` on the first one that implements
the interface and returns `TRUE`:
~~~
for (each core agent, then each extension agent)
{
   auto processCommandLine = std::dynamic_pointer_cast<IEAFProcessCommandLine>(agent);
   if (processCommandLine && processCommandLine->ProcessCommandLineOptions(cmdInfo))
      return TRUE; // handled
}
return FALSE;
~~~
Since this is a plain RTTI probe rather than a broker interface lookup, any agent can opt in just by
inheriting the interface - no `REGISTER_INTERFACE` call needed, and it's available to core agents and
extension agents alike.

A substantial real example is `XBeamRate`'s `CXBRateCommandLineProcessor`
(`XBeamRate\XBeamRateCommandLineProcessor.h`/`.cpp`), used by `CXBeamRateAgent::ProcessCommandLineOptions`:
it re-parses the command line with its own `CXBRateCommandLineInfo`, handles a `-regtests` batch mode
that iterates every physical pier in the open model and runs regression tests against each, and falls
through to the active document's own command-line handling for anything it doesn't recognize.
