#include "pch.h"
#include "CppUnitTest.h"
#include "Reporter\Heading.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReporterUnitTests
{
	TEST_CLASS(HeadingUnitTests)
	{
	public:

		TEST_METHOD(ConstructorTest)
		{
			Uint8 hLevel = 3;
			rptHeading heading(hLevel);

			// Check if the heading level matches the assigned value
			Assert::AreEqual(hLevel, heading.GetHeadingLevel());
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
			Uint8 hLevel = 4;
			rptHeading heading(hLevel);
			MockParagraphVisitor mockVisitor;
			heading.Accept(mockVisitor);

			// Check if the visitor was invoked by the Accept method
			Assert::IsTrue(mockVisitor.visited);
		}

		TEST_METHOD(EqualityTest)
		{
			Uint8 hLevel1 = 3;
			Uint8 hLevel2 = 3;
			rptHeading heading1(hLevel1);
			rptHeading heading2(hLevel2);

			// Check if two headings with the same heading level are considered equal
			Assert::IsTrue(heading1 == heading2);
		}
	};

}
