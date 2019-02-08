///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2019  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTSTYLEHOLDER_H_
#define INCLUDED_REPORTSTYLEHOLDER_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\RcTable.h>

#define RPT_BEARING(_value_) rptRcString(_value_,true)
#define RPT_ANGLE(_value_) rptRcString(_value_,true)

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

/*****************************************************************************
CLASS 
   rptStyleManager

   A convenient place to hold common text styles for the Pgsuper application


DESCRIPTION
   A purely static class used for maintaining consistent text style
   information

LOG
   rdp : 09.26.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptStyleManager
{
public:
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Initialize the styles in the style library
   static void InitStyles();

   //------------------------------------------------------------------------
   // Return the Style for the Report Title.
   static LPCTSTR GetReportTitleStyle();

   //------------------------------------------------------------------------
   // Return the Style for the Report Subtitle.
   static LPCTSTR GetReportSubtitleStyle();

   //------------------------------------------------------------------------
   // Return the Style for the Chapter Titles.
   static LPCTSTR GetChapterTitleStyle();

   //------------------------------------------------------------------------
   // Return the style for Headings
   static LPCTSTR GetHeadingStyle();

   //------------------------------------------------------------------------
   // Return the style for Subheadings
   static LPCTSTR GetSubheadingStyle(); 

   //------------------------------------------------------------------------
   // Return the style for table column headings
   static LPCTSTR GetTableColumnHeadingStyle();

   //------------------------------------------------------------------------
   // Returns the style for table cells.  Use the CS_XXXX and CJ_XXXX constants
   // to specify a style.
   static LPCTSTR GetTableCellStyle(Uint32 style);

   //------------------------------------------------------------------------
   // Returns the style for table cells.  Use the CS_XXXX and CJ_XXXX constants
   // to specify a style.
   static LPCTSTR GetTableStripeRowCellStyle(Uint32 style);

   //------------------------------------------------------------------------
   static LPCTSTR GetFootnoteStyle();

   //------------------------------------------------------------------------
   static LPCTSTR GetCopyrightStyle();

   //------------------------------------------------------------------------
   // Returns the maximum table width to be used in any given chapter
   static Float64 GetMaxTableWidth();

   //------------------------------------------------------------------------ 
   // Returns a pointer to a dynamically allocated defaultly configured table 
   // with 0.75" wide columns
   static rptRcTable* CreateDefaultTable(ColumnIndexType numColumns, LPCTSTR lpszLabel=nullptr);
   static rptRcTable* CreateDefaultTable(ColumnIndexType numColumns, const std::_tstring& strLabel);

   //------------------------------------------------------------------------ 
   // Returns a pointer to a dynamically allocated defaultly configured table 
   // with 0.75" wide columns
   // This table does not have a heading row.
   static rptRcTable* CreateTableNoHeading(ColumnIndexType numColumns, LPCTSTR lpszLabel=nullptr);
   static rptRcTable* CreateTableNoHeading(ColumnIndexType numColumns, const std::_tstring& strLabel);

   //------------------------------------------------------------------------ 
   // Returns a pointer to a dynamically allocated table configured to act as
   // a layout table. This table does not have visable borders and is intended
   // to be used to layout multi-column output (such as side by side tables)
   static rptRcTable* CreateLayoutTable(ColumnIndexType nColumns,const std::_tstring& strLabel);
   static rptRcTable* CreateLayoutTable(ColumnIndexType nColumns,LPCTSTR lpszLabel = nullptr);

   static void ConfigureTable(rptRcTable* pTable);

   //------------------------------------------------------------------------ 
   // Returns the path to where the images are stored.
   static LPCTSTR GetImagePath();

   static void SetReportCoverImage(LPCTSTR strImagePath);
   static LPCTSTR GetReportCoverImage();

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
   static std::_tstring ms_ReportTitleStyle;
   static std::_tstring ms_ReportSubtitleStyle;
   static std::_tstring ms_ChapterTitleStyle;
   static std::_tstring ms_HeadingStyle;
   static std::_tstring ms_SubheadingStyle;
   static std::_tstring ms_TableColumnHeadingStyle;
   static std::_tstring ms_FootnoteStyle;
   static std::_tstring ms_CopyrightStyle;
   static std::_tstring ms_TableCellStyle[6];
   static std::_tstring ms_TableStripeRowCellStyle[6];
   static std::unique_ptr<std::_tstring> ms_pImagePath;
   static Float64 ms_MaxTableWidth;
   static std::_tstring ms_ReportCoverImage;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptStyleManager();
   // Prevent accidental copying and assignment
   rptStyleManager(const rptStyleManager&);
   rptStyleManager& operator=(const rptStyleManager&) = delete;

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTSTYLEHOLDER_H_

