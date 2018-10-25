#include <Reporter\ReportExT.h>
#include <Reporter\Reporter.h>
#include <Reporter\HtmlReportVisitor.h>

#include <Units\Measure.h>
#include <Units\StationFormat.h>
#include <UnitMgt\Library.h>

#include <iostream>
#include <fstream>

int main(void)
{
   unitmgtIndirectMeasure si;
   si.StationFormat = unitStationFormats.SI;
   si.ShortLength = unitMeasure::Millimeter;
   si.RegLength   = unitMeasure::Meter;
   si.LongLength  = unitMeasure::Kilometer;

   unitmgtIndirectMeasure us;
   us.StationFormat = unitStationFormats.US;
   us.ShortLength = unitMeasure::Inch;
   us.RegLength   = unitMeasure::Feet;
   us.LongLength  = unitMeasure::Mile;

   unitmgtLibrary unit_library;
   unit_library.AddEntry( "SI", si );
   unit_library.AddEntry( "US", us );

   rptReportEx   report;
   rptChapter*   p_chapter   = new rptChapter;
   rptParagraph* p_paragraph = new rptParagraph;

   report << p_chapter;
   *p_chapter << p_paragraph;

   rptLengthUnitValue a(10.0,
                        RPT_SHORTLENGTH(&report),
                        RPT_SHORTLENGTHTOL(&report) );
   *p_paragraph << a << nl;

   rptLengthUnitValue b(10.0,
                        RPT_REGLENGTH(&report),
                        RPT_REGLENGTHTOL(&report) );
   *p_paragraph << b << nl;

   rptLengthUnitValue c(10.0,
                        RPT_LONGLENGTH(&report),
                        RPT_LONGLENGTHTOL(&report) );
   *p_paragraph << c << nl;

   rptRcStation station(123456.7890,RPT_STATIONFORMAT(&report));
   *p_paragraph << station << nl;

   //
   // Realize the report
   //
   std::ofstream si_file("c:\\temp\\si.htm");
   std::ofstream us_file("c:\\temp\\us.htm");

   report.SetUnitsOfMeasure( unit_library.GetEntry("SI") );
   rptHtmlReportVisitor si_visitor( &si_file );
   si_visitor.VisitReport( &report );

   report.SetUnitsOfMeasure( unit_library.GetEntry("US") );
   rptHtmlReportVisitor us_visitor( &us_file );
   us_visitor.VisitReport( &report );

   return 0;
}