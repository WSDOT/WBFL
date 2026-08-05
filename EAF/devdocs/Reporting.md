Reporting {#WBFL_EAF_Reporting}
==================================
An Agent integrates with the reporting system via `WBFL::EAF::IAgentReportingIntegration`,
registering and unregistering in `IntegrateWithReporting`.

## Registering a report
`IEAFReportManager::AddReportBuilder` (`Include\EAF\EAFReportManager.h`) registers a new report,
assembled from a `WBFL::ReportMgr::ReportBuilder` with a title page builder, a report specification
builder, and one or more chapter builders:
~~~
GET_IFACE(IEAFReportManager, pRptMgr);
auto pRptBuilder = std::make_shared<WBFL::ReportMgr::ReportBuilder>(_T("My Report"));
pRptBuilder->SetTitlePageBuilder(std::make_shared<CMyTitlePageBuilder>());
pRptBuilder->AddChapterBuilder(std::make_shared<CMyChapterBuilder>());
pRptMgr->AddReportBuilder(pRptBuilder);
~~~
A report also needs a `ReportSpecificationBuilder`
(`pRptBuilder->SetReportSpecificationBuilder(...)`) - see \ref WBFL_Reporting_Specifications
"Report Specifications" for what it's responsible for, and \ref WBFL_EAF_Reporting_QuickReports
"Quick Reports" below for how it gets invoked.

## Modifying a report someone else defined
Instead of building your own, look it up by name and call `InsertChapterBuilder`/
`RemoveChapterBuilder` on the result:
~~~
GET_IFACE(IEAFReportManager, pRptMgr);
auto pRptBuilder = pRptMgr->GetReportBuilder(_T("Some Existing Report"));
pRptBuilder->InsertChapterBuilder(std::make_shared<CMyChapterBuilder>(), _T("SomeExistingChapterKey"));
~~~

## Hiding vs. removing
`ReportBuilder::Hidden(bool)` keeps a report registered - still retrievable by name, still
generatable - but excludes it from the enumerated lists the UI builds
(`GetReportBuilderCount`/`GetReportNames` both take a `bIncludeHidden` flag, default `false`).
`IEAFReportManager::RemoveReportBuilder` fully unregisters a report and hands ownership back to the
caller.

## The Report menu, toolbar button, and view context menus are generated
None of the places a user picks a report from are hand-authored per report - they're all populated
at runtime from whatever is currently registered with `IEAFReportManager`. The `.rc` resources
involved are just empty scaffolding: PGSuper's `View > Reports` submenu and its `IDR_REPORTS`
context-menu template both start out as a single placeholder `MENUITEM`, filled in by
`CEAFBrokerDocument::PopulateReportMenu`/`BuildReportMenu` (`WBFL\EAF\EAFBrokerDocument.cpp`), which
iterates `IEAFReportManager::GetReportNames()` and appends one menu item per report.

The same mechanism drives all three surfaces:
- **Main menu** - `CPGSDocBase::PopulateReportMenu()` (`PGSuper\PGSuperAppPlugin\PGSuperDocBase.cpp`)
  finds the `View > Reports` submenu and calls `CEAFBrokerDocument::PopulateReportMenu` on it.
- **Toolbar button** - the `ID_VIEW_REPORTS` toolbar button has a dropdown arrow; its `TBN_DROPDOWN`
  handler, `CPGSDocBase::OnViewReports`, loads the same `IDR_REPORTS` template, strips its
  placeholder item, and calls `PopulateReportMenu` on it before showing it under the button.
- **View context menus** - a view's right-click "Reports" submenu loads `IDR_REPORTS` and calls
  `PopulateReportMenu` the same way.

Because generation is centralized, registering or hiding a report (see above) automatically updates
every menu/toolbar/context-menu surface the next time it's populated - there's nothing else to keep
in sync.

## Generic UI building blocks
A `ReportSpecificationBuilder::CreateReportSpec` is free to show whatever UI it wants - down to
`CMyReportSpecificationBuilder`'s single `AfxQuestion` prompt (see
\ref WBFL_Reporting_Specifications "Report Specifications"). Nothing requires a particular dialog
base class. That said, ReportManager and EAF provide a few reusable pieces:
- `CReportSpecDlg` (`WBFL\ReportManager\ReportSpecDlg.h/.cpp`) - a generic chapter-only picker
  (report name plus a `CCheckListBox` of chapters), useful when a report has no domain selection of
  its own to prompt for.
- `CReportDlg` (`WBFL\ReportManager\ReportDlg.h/.cpp`) - the report-browser host dialog, embedding
  a `ReportBrowser` with OK/Cancel/Print buttons.
- `CEAFSelectReportDlg` (`WBFL\EAF\EAFSelectReportDlg.h/.cpp`) - a plain report-*type* picker list,
  used when the application needs the user to choose which report to run.

Most PGSuper/PGSplice reports instead show a domain-aware spec dialog - a chapter picker plus
span/girder/segment selectors. `CSpanGirderReportDlg`/`CSpanItemReportDlg`
(`PGSuper\Include\Reporting\SpanItemReportDlg.h`, `SpanGirderReportDlg.h/.cpp`) is the concrete
example behind `CGirderReportSpecificationBuilder::CreateReportSpec`: it takes a `Mode` enum
(`GroupAndChapters`, `GirderAndChapters`, `GroupGirderAndChapters`, `GroupGirderSegmentAndChapters`)
that controls which domain combo boxes appear alongside the chapter list. Treat it as one worked
example, not an exhaustive list - PGSuper has a couple dozen domain-specific report dialogs
following the same shape (chapter checklist plus whatever selectors that report's specification
needs).

## The Configure Reports dialog
`CConfigureReportsDlg` (`WBFL\EAF\ConfigureReportsDlg.h/.cpp`, a `CPropertySheet`) is the
user-facing management UI for reports, independent of any single report's own spec dialog:
- `CFavoriteReportsPage` (`FavoriteReportsPage.h/.cpp`) - a checklist of every registered report,
  letting the user mark reports as favorites. `CConfigureReportsDlg::IsFavorite`/`GetFavorites`
  back the "show only favorites" menu filter.
- `CCustomReportsPage`/`CEditCustomReportDlg` (`CustomReportsPage.*`, `EditCustomReportDlg.*`) -
  lets the user build a named report that's really just a saved chapter subset of an existing
  report (parent report, available/selected chapters, reorder).

\anchor WBFL_EAF_Reporting_QuickReports
## Quick Reports
A "quick report" is not a different report - it's the same `ReportBuilder`, invoked with
`bPrompt = FALSE`. The entire behavioral difference lives in one fork,
`CEAFReportView::CreateReportSpecification` (`WBFL\EAF\EAFReportView.cpp`):
~~~
m_pRptSpecBuilder = pRptBuilder->GetReportSpecificationBuilder();
if ( bPromptForSpec )
{
   m_pReportSpec = m_pRptSpecBuilder->CreateReportSpec(rptDesc, m_pReportSpec);
}
else
{
   m_pReportSpec = m_pRptSpecBuilder->CreateDefaultReportSpec(rptDesc);
}
~~~
This is the other half of the generation described above: `BuildReportMenu(pMenu, bQuickReport)`
builds the reports menu twice, once per mode, with two disjoint command-ID ranges computed by
`GetReportCommand(rptIdx, bQuickReport)` (both offset from `EAF_REPORT_MENU_BASE`, quick-report IDs
occupying the lower range and normal-report IDs the upper one). `OnCmdMsg` checks which range an
incoming command ID falls in and routes accordingly: `OnReport(nID)` calls
`CreateReportView(rptIdx, /*bPrompt=*/TRUE)`; `OnQuickReport(nID)` calls
`CreateReportView(rptIdx, /*bPrompt=*/FALSE)`.

A context-menu quick report (e.g. right-click in a girder view) additionally has to make sure
`CreateDefaultReportSpec`'s selection-inference has something to work with. Frames like
`CGirderModelChildFrame::OnCmdMsg` (`PGSuper\PGSuperAppPlugin\GirderModelChildFrame.cpp`)
temporarily substitute the *view's own* current girder into the document's global selection before
routing a quick-report command, then restore the prior selection afterward - so "quick report from
this view" reports on what's currently showing without a lasting selection change elsewhere in the
application.

## Making your own report support Quick Reports
This is the payoff for implementing `CreateDefaultReportSpec` well (see
\ref WBFL_Reporting_Specifications "Report Specifications" for the full contract and two worked
examples):
- If `CreateDefaultReportSpec` can infer everything it needs from current application state - like
  `CGirderReportSpecificationBuilder`, from `ISelection` - the quick-report menu entry produces the
  report immediately, with no dialog.
- If it can't - like `CMyReportSpecificationBuilder`, which has no notion of a "current" message to
  report on - delegating to `CreateReportSpec` is the correct, honest fallback. The quick-report
  menu entry still appears and still works; it just always prompts, exactly as if the user had
  chosen the normal, non-quick menu entry instead.

Neither answer is wrong. A report only needs a real `CreateDefaultReportSpec` implementation if it
has some notion of "the thing I'd report on right now" to infer from - otherwise there is nothing
dishonest about always asking.
