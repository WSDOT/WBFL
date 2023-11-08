#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReporterUnitTests
{
	TEST_CLASS(StyleManagerUnitTests)
	{
	public:

		TEST_METHOD(GetReportTitleStyleTest)
		{
			LPCTSTR expectedStyle = _T("ReportTitle");
			Assert::AreEqual(expectedStyle, rptStyleManager::GetReportTitleStyle());
		}

		TEST_METHOD(GetReportSubtitleStyleTest)
		{
			LPCTSTR expectedStyle = _T("ReportSubtitle");
			Assert::AreEqual(expectedStyle, rptStyleManager::GetReportSubtitleStyle());
		}

		TEST_METHOD(GetChapterTitleStyleTest)
		{
			LPCTSTR expectedStyle = _T("ChapterTitle");
			Assert::AreEqual(expectedStyle, rptStyleManager::GetChapterTitleStyle());
		}

		TEST_METHOD(GetHeadingStyleTest)
		{
			LPCTSTR expectedStyle = _T("Heading");
			Assert::AreEqual(expectedStyle, rptStyleManager::GetHeadingStyle());
		}

		TEST_METHOD(GetSubheadingStyleTest)
		{
			LPCTSTR expectedStyle = _T("Subheading");
			Assert::AreEqual(expectedStyle, rptStyleManager::GetSubheadingStyle());
		}

		TEST_METHOD(GetTableColumnHeadingStyleTest)
		{
			LPCTSTR expectedStyle = _T("ColumnHeading");
			Assert::AreEqual(expectedStyle, rptStyleManager::GetTableColumnHeadingStyle());
		}
		TEST_METHOD(CreateHeadingDefaultTest)
		{
			rptHeading* heading = rptStyleManager::CreateHeading();
			Assert::AreEqual((Uint8)1, heading->GetHeadingLevel());
		}

		TEST_METHOD(CreateHeadingTest)
		{
			Uint8 hLevel = 3;
			rptHeading* heading = rptStyleManager::CreateHeading(hLevel);
			Assert::IsNotNull(heading);
			Assert::AreEqual(hLevel, heading->GetHeadingLevel());
		}

		TEST_METHOD(CreateDefaultTableTest)
		{
			ColumnIndexType numColumns = 5;
			std::_tstring label = _T("Test Table");
			rptRcTable* table = rptStyleManager::CreateDefaultTable(numColumns, label);
			Assert::IsNotNull(table);
			Assert::AreEqual(numColumns, table->GetNumberOfColumns());
		}

		TEST_METHOD(CreateTableNoHeadingTest)
		{
			ColumnIndexType numColumns = 4;
			std::_tstring label = _T("No Heading Table");
			rptRcTable* table = rptStyleManager::CreateTableNoHeading(numColumns, label);
			Assert::IsNotNull(table);
			Assert::AreEqual(numColumns, table->GetNumberOfColumns());
		}

		TEST_METHOD(CreateLayoutTableTest)
		{
			ColumnIndexType numColumns = 6;
			std::_tstring label = _T("Layout Table");
			rptRcTable* table = rptStyleManager::CreateLayoutTable(numColumns, label);
			Assert::IsNotNull(table);
			Assert::AreEqual(numColumns, table->GetNumberOfColumns());
		}

		TEST_METHOD(GetImagePathTest)
		{
			LPCTSTR expectedPath = rptStyleManager::GetImagePath();
			Assert::IsTrue(expectedPath != nullptr);
		}

		TEST_METHOD(GetReportCoverImageTest)
		{
			LPCTSTR expectedImage = rptStyleManager::GetReportCoverImage();
			Assert::IsTrue(expectedImage != nullptr);
		}

		TEST_METHOD(GetTableCellStyleTest)
		{
			Uint32 style = CB_NONE | CJ_RIGHT; // No Border, Right Justified
			LPCTSTR expectedStyle = _T("NB-RJ");
			Assert::AreEqual(expectedStyle, rptStyleManager::GetTableCellStyle(style));
		}

		TEST_METHOD(GetTableStripeRowCellStyleTest)
		{
			Uint32 style = CB_THIN | CJ_LEFT; // Thin Border, Right Justified
			LPCTSTR expectedStyle = _T("SR-TB-LJ");
			Assert::AreEqual(expectedStyle, rptStyleManager::GetTableStripeRowCellStyle(style));
		}

		TEST_METHOD(GetFootnoteStyleTest)
		{
			LPCTSTR expectedStyle = _T("Footnote");
			Assert::AreEqual(expectedStyle, rptStyleManager::GetFootnoteStyle());
		}

		TEST_METHOD(GetCopyrightStyleTest)
		{
			LPCTSTR expectedStyle = _T("Copyright");
			Assert::AreEqual(expectedStyle, rptStyleManager::GetCopyrightStyle());
		}

		TEST_METHOD(GetMaxTableWidthTest)
		{
			Float64 expectedWidth = 7.5;
			Assert::AreEqual(expectedWidth, rptStyleManager::GetMaxTableWidth());
		}

		TEST_METHOD(ConfigureTableTest)
		{
			rptRcTable* pTable = new rptRcTable(3, 7.5);
			rptStyleManager::ConfigureTable(pTable);
			Assert::IsTrue(pTable->GetNumberOfColumns() == 3);
		}

		TEST_METHOD(InitStylesTest)
		{
			rptStyleManager::InitStyles();

			// Test if styles are properly initialized
			Assert::AreEqual(_T("ReportTitle"), rptStyleManager::GetReportTitleStyle());
			Assert::AreEqual(_T("ReportSubtitle"), rptStyleManager::GetReportSubtitleStyle());
			Assert::AreEqual(_T("ChapterTitle"), rptStyleManager::GetChapterTitleStyle());
			Assert::AreEqual(_T("Heading"), rptStyleManager::GetHeadingStyle());
			Assert::AreEqual(_T("Subheading"), rptStyleManager::GetSubheadingStyle());

			// Test for table cell styles
			for (int i = 0; i < 6; i++)
			{
				LPCTSTR expectedStyle = rptStyleManager::GetTableCellStyle(i);
				Assert::IsNotNull(expectedStyle);

				LPCTSTR expectedStripeRowStyle = rptStyleManager::GetTableStripeRowCellStyle(i);
				Assert::IsNotNull(expectedStripeRowStyle);
			}

			// Test for footnote and copyright styles
			Assert::AreEqual(_T("Footnote"), rptStyleManager::GetFootnoteStyle());
			Assert::AreEqual(_T("Copyright"), rptStyleManager::GetCopyrightStyle());

			// Test the font type and size of default style
			rptFontStyleLibrary* psl = rptFontStyleLibrary::Instance();
			rptRiStyle defaultStyle = psl->GetDefaultStyle();
			Assert::AreEqual(9, static_cast<int>(defaultStyle.GetFontSize()));
			Assert::AreEqual(static_cast<int>(rptRiStyle::SWISS), static_cast<int>(defaultStyle.GetFontType()));

			// Test the alignment and other properties of chapter titles
			rptRiStyle chapterTitleStyle = psl->GetNamedStyle(rptStyleManager::GetChapterTitleStyle());
			Assert::AreEqual(13, static_cast<int>(chapterTitleStyle.GetFontSize()));
			Assert::IsTrue(chapterTitleStyle.GetBold());
			Assert::AreEqual(static_cast<int>(rptRiStyle::LEFT), static_cast<int>(chapterTitleStyle.GetAlignment()));
			Assert::AreEqual(static_cast<int>(rptRiStyle::Blue), static_cast<int>(chapterTitleStyle.GetColor()));
		}



	};
}
