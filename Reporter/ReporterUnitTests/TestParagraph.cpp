#include "pch.h"
#include "CppUnitTest.h"
#include "Reporter\Paragraph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReporterUnitTests
{
	TEST_CLASS(ParagraphUnitTests)
	{
	public:

		TEST_METHOD(InsertContentOperatorTest)
		{
			std::_tostringstream osp;
			osp << "Paragraph 1";
			auto paragraph = rptParagraph(osp.str());
			paragraph << rptRcColor(rptRiStyle::Bisque);
			auto it = paragraph.Begin();
			Assert::IsTrue(it != paragraph.End());

		}

		TEST_METHOD(InsertContentMethodTest)
		{
			std::_tostringstream osp;
			osp << "Paragraph 1";
			auto paragraph = rptParagraph(osp.str());
			paragraph << rptRcInt();
			auto rc = new rptRcInt(5, 5);
			paragraph.InsertContent(1, rc);
			auto it = paragraph.Begin();
			Assert::IsTrue(it != paragraph.End());
		}

		TEST_METHOD(SetNameTest)
		{
			std::_tostringstream osp;
			osp << "Paragraph 1";
			rptParagraph paragraph;
			paragraph.SetName(osp.str().c_str());

			Assert::IsTrue(osp.str() == paragraph.GetName());
		}

		TEST_METHOD(IsEmptyTest)
		{
			std::_tostringstream osp;
			osp << "Paragraph 1";
			rptParagraph paragraph(osp.str());
			paragraph << rptRcColor(rptRiStyle::Azure);

			// Check if the newly created paragraph is not empty
			Assert::IsFalse(paragraph.IsEmpty());

			// Check if an empty paragraph is indeed empty
			rptParagraph emptyParagraph;
			Assert::IsTrue(emptyParagraph.IsEmpty());
		}

		TEST_METHOD(CloneParagraphTest)
		{
			std::_tostringstream osp;
			osp << "Paragraph 1";
			rptParagraph paragraph(osp.str());
			rptRcInt rc1(1, 1);
			rptRcInt rc2(5, 5);
			rptRcInt rc3(10, 10);
			paragraph << rc1;
			paragraph << rc2;
			paragraph << rc3;

			auto clonedParagraph = paragraph.CreateClone();

			// Check if the cloned paragraph has the same name as the original one
			Assert::AreEqual(paragraph.GetName(), clonedParagraph->GetName());

			auto originalIter = paragraph.ConstBegin();
			auto clonedIter = clonedParagraph->ConstBegin();

			// Check if the cloned paragraph has the same content as the original one
			while (originalIter != paragraph.ConstEnd() && clonedIter != clonedParagraph->ConstEnd())
			{
				auto originalIntContent = std::dynamic_pointer_cast<rptRcInt>(*originalIter);
				auto clonedIntContent = std::dynamic_pointer_cast<rptRcInt>(*clonedIter);

				Assert::AreEqual(originalIntContent->GetValue(), clonedIntContent->GetValue());
				Assert::AreEqual(originalIntContent->GetWidth(), clonedIntContent->GetWidth());
				++originalIter;
				++clonedIter;
			}

		}

		class MockParagraphVisitor : public rptParagraphVisitor {
		public:
			bool visited = false;

			void VisitParagraph(rptParagraph* paragraph) override {
				visited = true;
			}

			void VisitHeading(rptHeading* heading) override {
				visited = true;
			}
		};

		TEST_METHOD(AcceptTest)
		{
			std::_tostringstream osp;
			osp << "Test Paragraph";
			rptParagraph paragraph(osp.str());
			MockParagraphVisitor mockVisitor;
			paragraph.Accept(mockVisitor);

			// Check if the visitor was invoked by the Accept method
			Assert::IsTrue(mockVisitor.visited);
		}

	};

}
	
