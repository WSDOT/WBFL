#include "pch.h"
#include "CppUnitTest.h"
#include <Reporter\ReporterLib.h>
#include <Reporter\HtmlReportVisitor.h>


#include <fstream>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReporterUnitTests
{
    TEST_CLASS(HtmlReportVisitorUnitTests)
    {
    public:

        TEST_METHOD(VisitReportTest)
        {
            // Creating a test report with a chapter and paragraph
            rptChapter* pChapter = new rptChapter;
            rptParagraph* pPara = new rptParagraph;
            (*pChapter) << pPara;
            (*testReport) << pChapter;

            // Adding some text to the paragraph
            *pPara << _T("This is a test");

            // Defining the output filename
            std::wstring m_Filename = L"output.html";

            // Creating an output file stream
            std::_tofstream ofile(m_Filename.c_str());

            // Initializing the report visitor
            rptHtmlReportVisitor visitor(&ofile, m_LogPixelsX, m_LogPixelsY, rptHtmlHelper::BrowserType::IE);

            // Visiting the report
            visitor.VisitReport(testReport.get());

            // Closing the output file
            ofile.close();

            // Opening the file to read its contents
            std::ifstream file(m_Filename);
            std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            // Performing checks on the file content
            Assert::IsTrue(fileContents.find("<!DOCTYPE HTML PUBLIC \"-//Spyglass//DTD HTML 2.0 Extended//EN\">") != std::string::npos);
            Assert::IsTrue(fileContents.find("<html>") != std::string::npos);
            Assert::IsTrue(fileContents.find("<head>") != std::string::npos);
            Assert::IsTrue(fileContents.find("<meta title=\"WSDOT Engineering Reporter on") != std::string::npos);
//            Assert::IsTrue(fileContents.find("<title>\"WSDOT Engineering Reporter on") != std::string::npos);
            Assert::IsTrue(fileContents.find("<BODY onDragStart=\"onde()\" >") != std::string::npos);
            Assert::IsTrue(fileContents.find("<SCRIPT LANGUAGE=\"JavaScript\">") != std::string::npos);
            Assert::IsTrue(fileContents.find("</html>") != std::string::npos);

            // Also, check for the presence of the specific text
            Assert::IsTrue(fileContents.find("This is a test") != std::string::npos);
        }

    private:

        std::shared_ptr<rptReport> testReport = std::make_shared<rptReport>(_T("Test Report"));
        Uint32 m_LogPixelsX{ static_cast<Uint32>(96) };
        Uint32 m_LogPixelsY{ static_cast<Uint32>(96) };
    };
}

