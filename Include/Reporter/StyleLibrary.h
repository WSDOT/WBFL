///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2023  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_REPORTER_STYLELIBRARY_H_
#define INCLUDED_REPORTER_STYLELIBRARY_H_

#pragma once

#include <Reporter\ReporterExp.h>

#undef CB_NONE
#undef CB_THIN
#undef CJ_LEFT
#undef CJ_RIGHT
#undef CJ_CENTER
#undef CA_TOP
#undef CA_MIDDLE
#undef CA_BOTTOM
#undef CA_BASELINE
#undef BORDER_MASK
#undef JUSTIFY_MASK
#undef VALIGN_MASK

#define CB_NONE     0x0001
#define CB_THIN     0x0002

#define CJ_LEFT     0x0010
#define CJ_RIGHT    0x0020
#define CJ_CENTER   0x0040

#define CA_TOP      0x0100
#define CA_MIDDLE   0x0200
#define CA_BOTTOM   0x0400
#define CA_BASELINE 0x0800

#define BORDER_MASK 0x0003
#define JUSTIFY_MASK 0x0070
#define VALIGN_MASK 0x0F00

class rptRcTable;

/// A library of style information
class REPORTERCLASS rptStyleLibrary
{
public:
   /// Table cell justification
   enum Justification { Left, Right };

   /// Initialize the styles in the style library and initialize the image path name
   static void InitStyles(
      const std::_tstring& imagePathName ///< Root path to all images that will be referenced into the report
   );

   /// Returns the Style for the Report Title.
   static const std::_tstring& GetReportTitleStyle();

   /// Returns the Style for the Report Subtitle.
   static const std::_tstring& GetReportSubtitleStyle();

   /// Returns the Style for the Chapter Titles.
   static const std::_tstring& GetChapterTitleStyle();

   /// Returns the style for Headings
   static const std::_tstring& GetHeadingStyle();

   /// Returns the style for Subheadings
   static const std::_tstring& GetSubheadingStyle(); 

   /// Returns the style for Level 1 Headings
   static const std::_tstring& GetLevel1HeadingStyle();

   /// Returns the style for Level 2 Headings
   static const std::_tstring& GetLevel2HeadingStyle();

   /// Returns the style for Level 3 Headings
   static const std::_tstring& GetLevel3HeadingStyle();

   /// Returns the style for Level 4 Headings
   static const std::_tstring& GetLevel4HeadingStyle();

   /// Returns the style for Level 5 Headings
   static const std::_tstring& GetLevel5HeadingStyle();

   /// Returns the style for Level 6 Headings
   static const std::_tstring& GetLevel6HeadingStyle();

   /// Returns the style for table column headings
   static const std::_tstring& GetTableColumnHeadingStyle();

   /// Returns the style for table data in cells
   static const std::_tstring& GetTableDataStyle(Justification justify = Left);

   /// Returns the style for table cells. Use the CS_XXXX and CJ_XXXX constants to specify a style.
   static const std::_tstring& GetTableCellStyle(Uint32 style);

   /// Returns the style for footnotes
   static const std::_tstring& GetFootnoteStyle();

   /// Returns the maximum table width to be used in any given chapter
   static Float64 GetMaxTableWidth();

   /// Returns a pointer to a dynamically allocated default table with 0.75" wide columns.
   /// If bLoadingColumn is true, column 1 is 1.5" wide
   static rptRcTable* CreateDefaultTable(unsigned numColumns, std::_tstring label,bool bLoadingColumn = false);

   /// Returnssa pointer to a dynamically allocated default table with 0.75" wide columns
   /// This table does not have a heading row.
   static rptRcTable* CreateTableNoHeading(unsigned numColumns, std::_tstring label);

   // Returns the path to where the images are stored.
   static const std::_tstring& GetImagePath();

private:
   rptStyleLibrary() = delete;
   rptStyleLibrary(const rptStyleLibrary&) = delete;
   rptStyleLibrary& operator=(const rptStyleLibrary&) = delete;

   static std::_tstring ms_ReportTitleStyle;
   static std::_tstring ms_ReportSubtitleStyle;
   static std::_tstring ms_ChapterTitleStyle;
   static std::_tstring ms_HeadingStyle;
   static std::_tstring ms_SubheadingStyle;
   static std::_tstring ms_Heading1Style;
   static std::_tstring ms_Heading2Style;
   static std::_tstring ms_Heading3Style;
   static std::_tstring ms_Heading4Style;
   static std::_tstring ms_Heading5Style;
   static std::_tstring ms_Heading6Style;
   static std::_tstring ms_TableColumnHeadingStyle;
   static std::_tstring ms_TableDataStyleLeftJustify;
   static std::_tstring ms_TableDataStyleRightJustify;
   static std::_tstring ms_FootnoteStyle;
   static std::array<std::_tstring, 6> ms_TableCellStyle;
   static std::_tstring ms_ImagePath;
   static Float64 ms_MaxTableWidth;
};

#endif // INCLUDED_REPORTER_STYLELIBRARY_H_

