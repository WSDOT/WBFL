#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReporterUnitTests
{

	TEST_CLASS(TestFontStyleLibrary)
	{
	public:
		TEST_METHOD(AddNamedStyleTest)
		{
			rptFontStyleLibrary* styleLibrary = rptFontStyleLibrary::Instance();
			rptRiStyle style;
			bool result = styleLibrary->AddNamedStyle(_T("TestStyle"), style);
			Assert::IsTrue(result);
		}

		TEST_METHOD(GetDefaultStyleTest)
		{
			rptFontStyleLibrary* styleLibrary = rptFontStyleLibrary::Instance();
			const rptRiStyle& style = styleLibrary->GetDefaultStyle();
			Assert::IsNotNull(&style);
		}

		TEST_METHOD(SetHeadingStyleTest)
		{
			rptFontStyleLibrary* styleLibrary = rptFontStyleLibrary::Instance();
			rptRiStyle style;
			styleLibrary->SetHeadingStyle(1, style);
			const rptRiStyle& retrievedStyle = styleLibrary->GetHeadingStyle(1);
			Assert::AreEqual(style.GetFontSize(), retrievedStyle.GetFontSize());
		}

		TEST_METHOD(GetStyleNamesTest)
		{
			rptFontStyleLibrary* styleLibrary = rptFontStyleLibrary::Instance();
			std::vector<rptStyleName> styleNames;
			styleLibrary->GetStyleNames(styleNames);
			Assert::IsTrue(styleNames.size() > 0);
		}

		TEST_METHOD(GetNamedStyleTest)
		{
			rptFontStyleLibrary* styleLibrary = rptFontStyleLibrary::Instance();
			const rptRiStyle& defaultStyle = styleLibrary->GetDefaultStyle();
			const rptRiStyle& retrievedDefaultStyle = styleLibrary->GetNamedStyle(_T("Default"));
			Assert::AreEqual(defaultStyle.GetFontSize(), retrievedDefaultStyle.GetFontSize());
		}

		TEST_METHOD(GetHeadingStyleTest)
		{
			rptFontStyleLibrary* styleLibrary = rptFontStyleLibrary::Instance();
			const rptRiStyle& headingStyle = styleLibrary->GetHeadingStyle(1);
			Assert::IsNotNull(&headingStyle);
		}
	};

}
