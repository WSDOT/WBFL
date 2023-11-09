// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include <Reporter/Reporter.h>
#include <Reporter/Report.h>
#include <Reporter/Chapter.h>
#include <Reporter/Paragraph.h>
#include <Reporter/Heading.h>
#include <Reporter/ReportContent.h>  //add subclasses to this test
#include <Reporter/ReportItem.h> //add as part of report content
#include <Reporter/StyleManager.h>
#include <Reporter/FontStyleLibrary.h>
#include <Reporter/HtmlReportVisitor.h>
#include <Reporter/ChapterVisitor.h>
#include <Reporter/OutputChapterVisitor.h>
#include <Reporter/HtmlChapterVisitor.h>
#include <Reporter/ParagraphVisitor.h>
#include <Reporter/OutputParagraphVisitor.h>
#include <Reporter/HtmlParagraphVisitor.h>
#include <Reporter/RcVisitor.h>
#include <Reporter/OutputRcVisitor.h>
#include <Reporter/HtmlRcVisitor.h>

#endif //PCH_H
