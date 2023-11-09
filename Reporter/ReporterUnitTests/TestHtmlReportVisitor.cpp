#include "pch.h"
#include "CppUnitTest.h"
#include <Reporter\ReporterLib.h>
#include <Reporter\HtmlReportVisitor.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReporterUnitTests
{
	TEST_CLASS(HtmlReportVisitorUnitTests)
	{
	public:

		TEST_METHOD(VisitReportTest)
		{

			std::wstring m_Filename = L"output.html";

			std::_tofstream ofile(m_Filename.c_str());

			rptHtmlReportVisitor visitor(&ofile, m_LogPixelsX, m_LogPixelsY);

			visitor.VisitReport(testReport.get());

			ofile.close(); // Close the file after writing to it

			std::ifstream file(m_Filename); // Open the file for reading
			std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()); // Read the entire file into a string

			Assert::IsTrue(fileContents.find("HTML") != std::string::npos); // Perform the necessary checks on the file content


		}

	private:

		std::shared_ptr<rptReport> testReport = std::make_shared<rptReport>(_T("Test Report"));
		Uint32 m_LogPixelsX{ static_cast<Uint32>(96) };
		Uint32 m_LogPixelsY{ static_cast<Uint32>(96) };
	};
}
