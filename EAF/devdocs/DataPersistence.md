Data Persistence {#WBFL_EAF_DataPersistence}
================================================
An Agent persists its own data into the project file by implementing `WBFL::EAF::IAgentPersist`
(`Include\EAF\Agent.h`):
~~~
class EAFCLASS IAgentPersist
{
public:
   virtual WBFL::EAF::Broker::LoadResult Load(WBFL::System::IStructuredLoad* pStrLoad) = 0;
   virtual bool Save(WBFL::System::IStructuredSave* pStrSave) = 0;
};
~~~
`IStructuredLoad`/`IStructuredSave` (`Include\System\IStructuredLoad.h`/`IStructuredSave.h`) are the
native, typed structured-storage interfaces. Reading and writing a property is a direct,
type-overloaded call:
~~~
WBFL::EAF::Broker::LoadResult CMyAgent::Load(WBFL::System::IStructuredLoad* pStrLoad)
{
   if (!pStrLoad->BeginUnit(_T("MyAgentData")))
      return WBFL::EAF::Broker::LoadResult::Error;

   std::_tstring answer;
   if (!pStrLoad->Property(_T("Answer"), &answer))
      return WBFL::EAF::Broker::LoadResult::Error;
   m_Answer = answer.c_str();

   if (!pStrLoad->EndUnit())
      return WBFL::EAF::Broker::LoadResult::Error;

   return WBFL::EAF::Broker::LoadResult::Success;
}

bool CMyAgent::Save(WBFL::System::IStructuredSave* pStrSave)
{
   pStrSave->BeginUnit(_T("MyAgentData"), 1.0);
   pStrSave->Property(_T("Answer"), m_Answer);
   pStrSave->EndUnit();
   return true;
}
~~~
`Property` has overloads for `LPCTSTR`/`std::_tstring`, `Float64`, the signed/unsigned integer
widths, `LONG`/`ULONG`, and `bool`. `BeginUnit`/`EndUnit` nest arbitrarily; `GetVersion` (plus
`GetParentVersion`/`GetParentUnit`/`GetTopVersion`) let a reader branch on the version a unit was
written with, the same version-gating pattern described in general terms in
`WBFLTools\devdocs\StructuredStorage.md`. A real example of this in practice: a beam-factory-style
component persists its dimension set as a named, versioned sub-unit inside its parent library entry,
and only wraps the dimensions in that sub-unit at all once the *parent's* schema version reaches the
value where that sub-unit was introduced - schema evolution gated on the containing object's version,
not just the sub-unit's own.

**Where persistence code actually lives.** `IAgentPersist` on the agent itself is one legitimate
place to put persistence logic (see `PGSuper\ExtensionAgentExample\ExampleExtensionAgent.cpp` for a
small, self-contained example), but real-world extensions just as often push project-specific
persistence down into their own value classes' own `Load`/`Save` methods instead, called from
wherever the agent (or another value class) already holds the same `IStructuredLoad`/
`IStructuredSave` pointer - there's no requirement that all of an agent's persisted data flow through
its own `IAgentPersist::Load`/`Save` bodies directly.

## Raw-unit passthrough
`IStructuredLoad::GetUnit()` returns the current unit as a raw XML string, verbatim, without needing
to understand its schema; `IStructuredSave::PutUnit(xml)` writes such a string back out unchanged.
This is what makes the following guarantee work, and it's worth understanding even though ordinary
`IAgentPersist` implementations never call `GetUnit`/`PutUnit` themselves:

`WBFL::EAF::Broker::Save` (`WBFL\EAF\Broker.cpp`) wraps every agent's data in its own `"Agent"` unit,
tagged with that agent's CLSID:
~~~
pStrSave->BeginUnit(_T("Agent"), 1.0);
pStrSave->Property(_T("CLSID"), strCLSID);
persist->Save(pStrSave); // the agent's own IAgentPersist::Save
pStrSave->EndUnit();
~~~
On load, `Broker::Load` reads the CLSID out of each `"Agent"` unit and looks for a currently-loaded
agent implementing `IAgentPersist` with that CLSID. If one isn't found - because, for example, a
third party's extension agent DLL isn't installed on this machine - the unit isn't discarded: the
Broker calls `GetUnit()` to capture the whole thing verbatim and holds onto it. The next time the
project is saved, every such captured unit is written back out unchanged via `PutUnit`. This is what
lets a project file round-trip losslessly through an installation that doesn't have a given extension
agent's DLL at all - the data is preserved exactly, ready to be picked up correctly whenever that
agent is available again.
