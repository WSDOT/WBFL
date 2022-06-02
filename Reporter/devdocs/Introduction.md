WBFL Reporter {#WBFL_Reporter}
========================
The WBFL Reporter Library provides report content definition services.

The Reporter Library models the contents of a report with the Report object. The Report object is composed from chapters, paragraphs, and report content items such as numbers, text strings, images, and tables. The Reporter Library also has a report rendering capability. Using the Visitor pattern, the contents of a report are traversed and content-specific visitor objects can read and process report content data.

The Reporter is an object-oriented software framework for creating scientific and engineering reports. The Reporter eases report creation by automating tasks such as unit conversion, table creation, and pagination. The Reporter also allows the user to create reports in a file format independent manner. Report visitors can generate HTML code for reports. The Reporter does not provide a report viewer.

The Reporter uses the Framework, Chain of Responsibility, Composite, Visitor, Prototype, and Singleton patterns.

Reporting Basics
-----------------
The following example code creates a report with some basic content

~~~~~~~~~~~~~~~~~~~~~~~~~~~
rptReport report;

rptChapter* pChapter = new rptChapter("Chapter 1"); // create a chapter
report << pChapter; // add the chapter to the report

rptParagraph* pPara = new rptParagraph; // create a paragraph
*pChapter << pPara; // add the paragraph to the chapter
*pPara << "Put some text in the report" << rptNewLine;

rptRcTable* pTable = rptStyleManager::CreateDefaultTable(2, "Table"); // create a table
*pPara << pTable; // add the table to the paragraph

// Fill up the table
*pTable(0,0) << "Heading 1";
*pTable(0,1) << "Heading 2";
*pTable(1,0) << "Value 1";
*pTable(1,1) << "Value 2";
~~~~~~~~~~~~~~~~~~~~~~~~~~~

This sample code renders the report into HTML.
~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::ofstream of("Report.html");
rptHtmlReportVisitor visitor(&of,logPixelsX,logPixelsY);
visitor.VisitReport(&report);
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Open the Report.html file to see the report.

The WBFL Engineering Application Framework (EAF) provides a built-in report viewer for your applications.