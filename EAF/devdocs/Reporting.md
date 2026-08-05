Reporting {#WBFL_EAF_Reporting}
==================================
An Agent integrates with the reporting system via `WBFL::EAF::IAgentReportingIntegration`,
registering and unregistering in `IntegrateWithReporting`.

`IEAFReportManager::AddReportBuilder` (`Include\EAF\EAFReportManager.h`) registers a new report,
assembled from a `WBFL::Reporting::ReportBuilder` with a title page builder, a report specification
builder, and one or more chapter builders:
~~~
GET_IFACE(IEAFReportManager, pRptMgr);
auto pRptBuilder = std::make_shared<WBFL::Reporting::ReportBuilder>(_T("My Report"));
pRptBuilder->SetTitlePageBuilder(std::make_shared<CMyTitlePageBuilder>());
pRptBuilder->AddChapterBuilder(std::make_shared<CMyChapterBuilder>());
pRptMgr->AddReportBuilder(pRptBuilder);
~~~


**Modifying a report someone else defined**, instead of building your own, means looking it up by
name and calling `InsertChapterBuilder`/`RemoveChapterBuilder` on the result:
~~~
GET_IFACE(IEAFReportManager, pRptMgr);
auto pRptBuilder = pRptMgr->GetReportBuilder(_T("Some Existing Report"));
pRptBuilder->InsertChapterBuilder(std::make_shared<CMyChapterBuilder>(), _T("SomeExistingChapterKey"));
~~~

**Hiding vs. removing.** `ReportBuilder::Hidden(bool)` keeps a report registered - still retrievable
by name, still generatable - but excludes it from the enumerated lists the UI builds
(`GetReportBuilderCount`/`GetReportNames` both take a `bIncludeHidden` flag, default `false`).
`IEAFReportManager::RemoveReportBuilder` fully unregisters a report and hands ownership back to the
caller.
