#include "pch.h"
#include "CppUnitTest.h"
#include <EAF\EAFLegalNoticeWiz.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EAFUnitTests
{
	TEST_CLASS(TestLegalNoticeWiz)
	{
	public:

		TEST_METHOD(ShowLegalNoticeAgain_RoundTrips)
		{
			// ShowAgain uses inverted sense from the "Don't show me this again" checkbox
			// it proxies to (ShowAgain=TRUE means the checkbox is unchecked). Confirm the
			// getter/setter pair agrees with itself in both directions.
			CEAFLegalNoticeWiz wiz(nullptr);

			wiz.ShowLegalNoticeAgain(TRUE);
			Assert::AreEqual((BOOL)TRUE, wiz.ShowLegalNoticeAgain());

			wiz.ShowLegalNoticeAgain(FALSE);
			Assert::AreEqual((BOOL)FALSE, wiz.ShowLegalNoticeAgain());
		}

		TEST_METHOD(GiveChoice_StoresValue)
		{
			CEAFLegalNoticeWiz wiz(nullptr);

			// Default (startup/mandatory-acceptance) mode
			wiz.GiveChoice(TRUE);

			// Review mode, invoked from a Help menu command after the app is already running
			wiz.GiveChoice(FALSE);

			// No public getter exists for m_bGiveChoice; this test exists to catch a build
			// break if the signature changes, and documents the two calling modes. The
			// actual button-visibility behavior driven by this flag is exercised via
			// OnInitDialog, which requires a real window (see class remarks) and is not
			// covered by this native unit test.
		}

		TEST_METHOD(GetLicenseText_AROSL)
		{
			CString strText = EAFGetLicenseText(EAFLicenseType::AROSL);
			Assert::IsFalse(strText.IsEmpty());
			Assert::IsTrue(strText.Find(_T("ALTERNATE ROUTE OPEN SOURCE LICENSE")) >= 0);
		}

		TEST_METHOD(GetLicenseText_ARLOSL)
		{
			CString strText = EAFGetLicenseText(EAFLicenseType::ARLOSL);
			Assert::IsFalse(strText.IsEmpty());
			Assert::IsTrue(strText.Find(_T("ALTERNATE ROUTE LIBRARY OPEN SOURCE LICENSE")) >= 0);
		}

		TEST_METHOD(GetDisclaimerText_ReturnsExpectedContent)
		{
			CString strText = EAFGetDisclaimerText();
			Assert::IsFalse(strText.IsEmpty());
			Assert::IsTrue(strText.Find(_T("DISCLAIMER")) >= 0);
			Assert::IsTrue(strText.Find(_T("INDEMNIFICATION")) >= 0);
		}
	};
}
