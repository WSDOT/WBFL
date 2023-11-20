#include "pch.h"
#include "CppUnitTest.h"
#include "Reporter\ReportContent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReporterUnitTests
{
	TEST_CLASS(ReportContentUnitTests)
	{
	public:

		TEST_METHOD(ConstructorTest)
		{
			auto rc = rptRcImage(std::_tstring(rptStyleManager::GetImagePath()) + _T("Test.png"));

			Assert::IsFalse(rc.IsHyperLink());
		}

		TEST_METHOD(CopyConstructorTest)
		{
			auto rc = rptRcImage(std::_tstring(rptStyleManager::GetImagePath()) + _T("Test.png"));
			rc.SetHyperLink(_T("test_target"));
			auto rc_copy(rc);

			// Check if the hyperlinks of both objects match
			Assert::AreEqual(rc.GetHyperTarget(), rc_copy.GetHyperTarget());
		}

		TEST_METHOD(AssignmentOperatortest)
		{
			auto rc = rptRcPercentage(99);
			auto rc_new = rc;

			Assert::AreEqual(rc.AsString(), rc_new.AsString());
		}

		TEST_METHOD(HyperLinkTest)
		{
			auto rc = rptRcScalar();
			auto test_str = _T("test");
			rc.SetHyperLink(test_str);

			Assert::IsTrue(rc.IsHyperLink());

		}
	};

}
