Report Specifications {#WBFL_Reporting_Specifications}
========================================================
A `WBFL::ReportMgr::ReportBuilder` (see \ref WBFL_Reporting "Introduction") turns a
`ReportSpecification` into a `WBFL::Reports::Report` by running the report's `TitlePageBuilder` and
its selected `ChapterBuilder`s. This page is about the specification itself - what it is, who
builds it, and how a third-party report plugs into that machinery. Chapter authoring and report
build orchestration are not covered here - see `ChapterBuilder`
(`Include\ReportManager\ChapterBuilder.h`) and `ReportBuilder::CreateReport` for that. The report
*content* model (`rptReport`/`rptChapter`) is a separate library, Reporter - see \ref WBFL_Reporter
"Introduction" - not part of ReportManager and out of scope here.

## ReportSpecification
`WBFL::ReportMgr::ReportSpecification` (`Include\ReportManager\ReportSpecification.h`) is a plain
data object: report name/title, an ordered list of `ChapterInfo` (chapter key + reporting level),
and header/footer text. It answers "what to report on and how", as opposed to `ReportBuilder`,
which answers "how to render it". A `ReportSpecification` is produced fresh every time a report is
generated or regenerated - `ReportBuilder::CreateReport` and `ReportBuilder::NeedsUpdate` both take
one as a parameter rather than the report holding this state itself.

## ReportDescription and chapter selection
`WBFL::ReportMgr::ReportDescription` (`Include\ReportManager\ReportDescription.h`) is the catalog a
`ReportSpecificationBuilder` uses when building a `ReportSpecification`. It's derived from a
report's registered `ChapterBuilder`s (`ReportBuilder::GetReportDescription()`), and its
`ChapterInfo` entries (key, name, max level, default-selected) are what populate a chapter-picker
UI. `ReportDescription::ConfigureReportSpecification(...)` turns a chapter selection - either the
description's own defaults, or a UI-collected list of `ChapterInfo`/chapter keys - into a populated
`ReportSpecification`.

## ReportSpecificationBuilder
`WBFL::ReportMgr::ReportSpecificationBuilder` (`Include\ReportManager\ReportSpecificationBuilder.h`)
is a strategy object with two virtual methods:
~~~
virtual std::shared_ptr<ReportSpecification> CreateReportSpec(const ReportDescription& rptDesc, std::shared_ptr<ReportSpecification> pRptSpec) const;
virtual std::shared_ptr<ReportSpecification> CreateDefaultReportSpec(const ReportDescription& rptDesc) const;
~~~
`CreateReportSpec` shows UI and may return `nullptr` if the user cancels. `CreateDefaultReportSpec`
must not show UI - it's the method used for a "quick report" (see
\ref WBFL_EAF_Reporting_QuickReports "Quick Reports"). Both exist because the report's own
specification builder is the only code that knows whether producing a spec without prompting is
even possible.

`PGSuper\ExtensionAgentExample`'s `CMyReportSpecificationBuilder`
(`MyReportSpecificationBuilder.cpp`) is a small, complete implementation worth reading end to end:
~~~
std::shared_ptr<ReportSpecification> CMyReportSpecificationBuilder::CreateReportSpec(const ReportDescription& rptDesc, std::shared_ptr<ReportSpecification> pRptSpec) const
{
   CString strAnswer;
   AfxQuestion(_T("My Report Specification"), _T("Enter some text to put into the report"), _T(""), strAnswer);
   std::shared_ptr<CMyReportSpecification> pSpec(std::make_shared<CMyReportSpecification>(rptDesc.GetReportName(), m_pBroker));
   pSpec->SetMessage(strAnswer);
   std::shared_ptr<ReportSpecification> pNewRptSpec(std::dynamic_pointer_cast<ReportSpecification>(pSpec));

   rptDesc.ConfigureReportSpecification(pNewRptSpec);   // populate the chapter list from defaults
   return pNewRptSpec;
}

std::shared_ptr<ReportSpecification> CMyReportSpecificationBuilder::CreateDefaultReportSpec(const ReportDescription& rptDesc) const
{
   // there is no default configuration for this report. The user must be prompted every time
   return CreateReportSpec(rptDesc, std::shared_ptr<ReportSpecification>());
}
~~~
`CreateReportSpec` prompts (here with a single `AfxQuestion`; a real report typically shows a
dialog instead - see \ref WBFL_EAF_Reporting "Reporting"), builds the domain specification, and
calls `ConfigureReportSpecification` to fill in its chapter list.
`CreateDefaultReportSpec` has nothing sensible to default to here - there's no "current message" to
report on - so it honestly delegates back to `CreateReportSpec` instead of fabricating one. That's
a legitimate, common answer: a report is not required to support a silent path, and delegating like
this just means its quick-report menu entry still prompts.

Contrast that with `CGirderReportSpecificationBuilder::CreateDefaultReportSpec`
(`PGSuper\Reporting\SpanGirderReportSpecificationBuilder.cpp`), which infers the group/girder from
the application's current selection (`ISelection`) and only falls back to prompting when the
selection is genuinely ambiguous - e.g. more than one group and no girder selected:
~~~
std::shared_ptr<ReportSpecification> CGirderReportSpecificationBuilder::CreateDefaultReportSpec(const ReportDescription& rptDesc) const
{
   GET_IFACE2(GetBroker(), ISelection, pSelection);
   CSelection selection = pSelection->GetSelection();
   ...
   if ( /* selection resolves to exactly one group/girder */ )
   {
      // ...no prompting required
   }
   else if ( /* selection is ambiguous */ )
   {
      // going to have to prompt the user
      return CreateReportSpec(rptDesc, std::shared_ptr<ReportSpecification>());
   }
   ...
}
~~~
Both are correct implementations of the same contract - which one applies depends entirely on
whether the application's current state is enough to know what the report should be about.

## Domain-specific specifications
A `ReportSpecification` subclass adds whatever data its chapters need. `CBrokerReportSpecification`/
`CBrokerReportSpecificationBuilder` (`PGSuper\Include\Reporting\BrokerReportSpecification.h`,
`BrokerReportSpecificationBuilder.h`) add access to the application's broker
(`std::weak_ptr<WBFL::EAF::Broker>`) so chapter content can pull live model data - this is what
`CMyReportSpecification` derives from. PGSuper's `CGirderReportSpecification`
(`PGSuper\Include\Reporting\SpanGirderReportSpecificationBuilder.h`) is the same pattern at
production scale, adding a `CGirderKey`/`CSegmentKey`. `WBFL::EAF::BrokerReportSpecification`
(`Include\EAF\BrokerReportSpecification.h`) is the equivalent, non-PGSuper-specific base available
to other EAF-hosted applications.

## Adding this to your own extension agent
Everything above is what your `ReportSpecification`/`ReportSpecificationBuilder` need to
*implement*. For how to *register* them - `IEAFReportManager::AddReportBuilder`,
`ReportBuilder::SetReportSpecificationBuilder`, `AddChapterBuilder` - and how to instead add a
chapter to a report someone else already defined, see "Creating an Extension Agent"
(`PGSuper\devdocs\Procedures\Creating_an_Extension_Agent.md`), whose `Reports` section walks
through this exact `CMyReportSpecificationBuilder`/`CMyChapterBuilder` example end to end.
