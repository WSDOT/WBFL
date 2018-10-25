///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

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


#include <Reporter\ReporterExp.h>


/*****************************************************************************
CLASS 
   rptStyleLibrary

   A convenient place to hold common text styles.


DESCRIPTION
   A purely static class used for maintaining consistent text style
   information

COPYRIGHT
   Copyright (c) 1999
   BridgeSight Software
   All Rights Reserved

*****************************************************************************/

class REPORTERCLASS rptStyleLibrary
{
public:
   enum Justification { Left, Right };

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Initialize the styles in the style library
   // and initialize the image path name
   static void InitStyles(const std::string& imagePathName);

   //------------------------------------------------------------------------
   // Return the Style for the Report Title.
   static const std::string& GetReportTitleStyle();

   //------------------------------------------------------------------------
   // Return the Style for the Report Subtitle.
   static const std::string& GetReportSubtitleStyle();

   //------------------------------------------------------------------------
   // Return the Style for the Chapter Titles.
   static const std::string& GetChapterTitleStyle();

   //------------------------------------------------------------------------
   // Return the style for Headings
   static const std::string& GetHeadingStyle();

   //------------------------------------------------------------------------
   // Return the style for Subheadings
   static const std::string& GetSubheadingStyle(); 

   //------------------------------------------------------------------------
   // Return the style for table column headings
   static const std::string& GetTableColumnHeadingStyle();

   //------------------------------------------------------------------------
   // Return the style for table data in cells
   static const std::string& GetTableDataStyle(Justification justify = Left);

   //------------------------------------------------------------------------
   // Returns the style for table cells.  Use the CS_XXXX and CJ_XXXX constants
   // to specify a style.
   static const std::string& GetTableCellStyle(Uint32 style);

   //------------------------------------------------------------------------
   static const std::string& GetFootnoteStyle();

   //------------------------------------------------------------------------
   // Returns the maximum table width to be used in any given chapter
   static Float64 GetMaxTableWidth();

   //------------------------------------------------------------------------ 
   // Returns a pointer to a dynamically allocated defaultly configured table 
   // with 0.75" wide columns
   // If bLoadingColumn is true, column 1 is 1.5" wide
   static rptRcTable* CreateDefaultTable(unsigned numColumns, std::string label,bool bLoadingColumn = false);

   //------------------------------------------------------------------------ 
   // Returns a pointer to a dynamically allocated defaultly configured table 
   // with 0.75" wide columns
   // This table does not have a heading row.
   static rptRcTable* CreateTableNoHeading(unsigned numColumns, std::string label);

   //------------------------------------------------------------------------ 
   // Returns the path to where the images are stored.
   static const std::string& GetImagePath();

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   static std::string ms_ReportTitleStyle;
   static std::string ms_ReportSubtitleStyle;
   static std::string ms_ChapterTitleStyle;
   static std::string ms_HeadingStyle;
   static std::string ms_SubheadingStyle;
   static std::string ms_TableColumnHeadingStyle;
   static std::string ms_TableDataStyleLeftJustify;
   static std::string ms_TableDataStyleRightJustify;
   static std::string ms_FootnoteStyle;
   static std::string ms_TableCellStyle[4];

   static std::string ms_ImagePath;
   static Float64 ms_MaxTableWidth;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptStyleLibrary();
   // Prevent accidental copying and assignment
   rptStyleLibrary(const rptStyleLibrary&);
   rptStyleLibrary& operator=(const rptStyleLibrary&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_STYLELIBRARY_H_

