#ifndef INCLUDED_REPORTMANAGER_H_
#define INCLUDED_REPORTMANAGER_H_

// This is a master include file for the Reporting Package
#if defined(BUILDREPORTMANAGERLIB)
	#error Do not use this header file in the Report Manager Package
   #error It is for external users only
#endif

#include <ReportManager\ChapterBuilder.h>
#include <ReportManager\ReportBrowser.h>
#include <ReportManager\ReportBuilder.h>
#include <ReportManager\ReportBuilderManager.h>
#include <ReportManager\ReportDescription.h>
#include <ReportManager\ReportSpecification.h>
#include <ReportManager\ReportSpecificationBuilder.h>

#endif // INCLUDED_REPORTMANAGER_H_