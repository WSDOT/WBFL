Introduction {#WBFL_Reporting}
================
This library provides Reporting Management services in the WBFL Application Services Layer.

Reporting Management services include:
* Managing report builders
* Creating reports
* Displaying reports
* UI elements for users to modify report specifications

Key Concepts
------------
The ReportBuilderManager provides services for managing ReportBuilder objects, proving a user interface element to allow a user to select and configure a ReportSpecification, and creating ReportBrowser objects to display a report.

ReportBuilder objects create WBFL::Reports::Report objects based on a user supplied ReportSpecification. A ReportBuilder consists of a TitlePageBuilder and collection of ChapterBuilder objects. The ChapterBuilder objects create the chapters of a report and fill them with the report's content.

A ReportSpecification defines the chapters to be included in a report, chapter reporting level, and other report content such as headers and footers.

