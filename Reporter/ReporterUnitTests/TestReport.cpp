#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReporterUnitTests
{
	TEST_CLASS(ReportUnitTests)
	{
	public:

		TEST_METHOD(InsertChapterTest)
		{

			//Use a parameterized constructor

			rptReport report(_T("Test Report"), rptStyleManager::GetHeadingStyle(),rptPageLayout());
			std::_tostringstream os;
			os << "Chapter 1";
			auto chapter = new rptChapter(os.str());

			// Test if chapter is inserted successfully
			report << chapter;

			Assert::AreEqual((size_t)1, report.GetChapterCount());
		}

		TEST_METHOD(InsertChapterAtTest)
		{
			rptReport report(_T("Test Report"));
			std::_tostringstream os1;
			os1 << "Chapter 1";
			auto chapter1 = new rptChapter(os1.str());
			std::_tostringstream os2;
			os2 << "Chapter 2";
			auto chapter2 = new rptChapter(os2.str());

			report << chapter1;

			// Test if chapter is inserted at the specific location successfully
			report.InsertChapterAt(0, chapter2);

			Assert::AreEqual((size_t)2, report.GetChapterCount());
		}

		TEST_METHOD(EnableHeadingNumbersTest)
		{
			rptReport report(_T("Test Report"));

			// Test if heading numbers can be enabled successfully
			report.EnableHeadingNumbers(true);

			Assert::IsTrue(report.HeadingNumbersEnabled());
		}

		TEST_METHOD(ChapterIteratorTest)
		{
			rptReport report(_T("Test Report"));
			std::_tostringstream os1;
			os1 << "Chapter 1";
			auto chapter1 = new rptChapter(os1.str());
			std::_tostringstream os2;
			os2 << "Chapter 2";
			auto chapter2 = new rptChapter(os2.str());

			report << chapter1 << chapter2;

			// Test if chapter iterators are working correctly
			auto it = report.Begin();
			Assert::AreEqual((*it)->GetName(), _T("Chapter 1"));

			++it;
			Assert::AreEqual((*it)->GetName(), _T("Chapter 2"));
		}

		TEST_METHOD(AcceptVisitorTest)
		{
			rptReport report(_T("Test Report"));
			// Create a mock visitor for testing purposes
			class MockVisitor : public rptReportVisitor
			{
			public:
				void VisitReport(rptReport* report) override
				{
					Assert::IsTrue(report != nullptr);
				}
			};

			MockVisitor visitor;
			// Test if the visitor is accepted successfully
			report.Accept(visitor);
		}


	};
}
