Documentation and Help {#WBFL_EAF_Documentation}
===================================================
An Agent integrates its own help content with the application's documentation system by implementing
`WBFL::EAF::IAgentDocumentationIntegration` (`Include\EAF\Agent.h`):
~~~
class EAFCLASS IAgentDocumentationIntegration
{
public:
   virtual CString GetDocumentationSetName() const = 0;
   virtual bool LoadDocumentationMap() = 0;
   virtual std::pair<WBFL::EAF::HelpResult,CString> GetDocumentLocation(UINT nHID) const = 0;
};
~~~
`HelpResult` (`Include\EAF\EAFTypes.h`) is `OK`, `DocSetNotFound`, or `TopicNotFound`.

## The doc-map file
`LoadDocumentationMap` is expected to populate an in-memory `nHID -> relative URL` map from a `.dm`
file - a trivially simple line-oriented text format, one `numericHelpID=RelativeTopicPath` pair per
line. `EAFGetDocumentationMapFile`/`EAFLoadDocumentationMap` (`Include\EAF\EAFUtilities.h`) do the
file resolution and parsing for you:
~~~
bool CMyAgent::LoadDocumentationMap()
{
   CString strDocMapFile = EAFGetDocumentationMapFile(GetDocumentationSetName(), GetDocumentationURL());
   return EAFLoadDocumentationMap(strDocMapFile, m_HelpTopics); // m_HelpTopics: std::map<UINT,CString>
}

std::pair<WBFL::EAF::HelpResult,CString> CMyAgent::GetDocumentLocation(UINT nHID) const
{
   auto found = m_HelpTopics.find(nHID);
   if (found == m_HelpTopics.end())
      return { WBFL::EAF::HelpResult::TopicNotFound, CString() };

   CString strURL;
   strURL.Format(_T("%s%s"), GetDocumentationURL(), found->second);
   return { WBFL::EAF::HelpResult::OK, strURL };
}
~~~
`EAFGetDocumentationMapFile` resolves the `.dm` file either over HTTP (if the application is
configured to use online documentation, `CEAFApp::UseOnlineDocumentation()`) or locally, and the
documentation root URL it's combined with typically has the product's own (major.minor-trimmed)
version folded into the path, so each shipped version gets its own doc set.

## The `PluginAppDocumentationImpl` helper
Rather than hand-roll the above, a `WBFL::EAF::PluginApp` (`Include\EAF\PluginApp.h`) can delegate to
`WBFL::EAF::PluginAppDocumentationImpl` (`Include\EAF\PluginAppDocumentationImpl.h`), a small
composition helper that implements the same doc-set-name/map-file/URL-resolution logic once, for
reuse across every plugin app rather than reimplementing it per plugin.

## `PGS::IPluginDocumentation`
PGSuper's Project Importer/Data Importer/Data Exporter plug-ins (see the "Extensibility" page in the
PGSuper devdocs) have their own, structurally identical
interface, `PGS::IPluginDocumentation` (`PGSuper\Include\Plugins\PGSuperIEPlugin.h`) - same three
methods, same `HelpResult` type, just scoped to that narrower plug-in category rather than to full
Agents. It isn't derived from `IAgentDocumentationIntegration`; it's a separate interface with the
same shape.

## When not to implement this
Not every integration point needs its own documentation set. Code that runs at the application-shell
level, before any document or help context exists, legitimately skips this interface entirely rather
than implementing a degenerate version of it.
