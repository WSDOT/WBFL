#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReporterUnitTests
{
	TEST_CLASS(ChapterUnitTests)
	{
	public:

		TEST_METHOD(InsertParagraphTest)
		{
			//Use a parameterized constructor

			rptChapter chapter(_T("Test Report"), rptStyleManager::GetHeadingStyle(), rptPageLayout());
			auto paragraph = std::make_shared<rptParagraph>();


			chapter << *paragraph;
			auto it = chapter.Begin();
			Assert::IsTrue(it != chapter.End());
		}

		TEST_METHOD(GetEjectPageBreakBeforeTest)
		{
			rptChapter chapter(_T("TestChapter"));
			Assert::IsFalse(chapter.GetEjectPageBreakBefore());
		}

		TEST_METHOD(SetEjectPageBreakBeforeTest)
		{
			rptChapter chapter(_T("TestChapter"));
			chapter.SetEjectPageBreakBefore(true);
			Assert::IsTrue(chapter.GetEjectPageBreakBefore());
		}

		TEST_METHOD(GetNameTest)
		{
			rptChapter chapter(_T("TestChapter"));
			Assert::AreEqual(_T("TestChapter"), chapter.GetName());
		}

		TEST_METHOD(SetNameTest)
		{
			rptChapter chapter(_T("TestChapter"));
			chapter.SetName(_T("NewTestChapter"));
			Assert::AreEqual(_T("NewTestChapter"), chapter.GetName());
		}

		TEST_METHOD(AcceptTest)
		{
			class MockChapterVisitor : public rptChapterVisitor
			{
			public:
				bool visited = false;

				void VisitChapter(rptChapter* chapter) override
				{
					visited = true;
				}
			};

			MockChapterVisitor mockVisitor;
			rptChapter chapter(_T("TestChapter"));
			chapter.Accept(mockVisitor);
			Assert::IsTrue(mockVisitor.visited);
		}

		TEST_METHOD(VisitTest)
		{
			class MockChapterVisitor : public rptChapterVisitor
			{
			public:
				bool visited = false;

				void VisitChapter(rptChapter* chapter) override
				{
					visited = true;
				}
			};

			rptChapter chapter(_T("TestChapter"));
			MockChapterVisitor mockVisitor;
			chapter.Accept(mockVisitor);
			Assert::IsTrue(mockVisitor.visited);
		}


	};
}

