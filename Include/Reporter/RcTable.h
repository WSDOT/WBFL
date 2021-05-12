//////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_RCTABLE_H_
#define INCLUDED_REPORTER_RCTABLE_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\Paragraph.h>
#include <Reporter\ReportingUtils.h>
#include <Reporter\StyleHolder.h>
#include <Reporter\RcInt.h>
#include <System\SectionValue.h>
#include <vector>

#define SKIP_CELL INVALID_INDEX

class rptRcTable;

/// Paragraph that is specialized for use in a table
class REPORTERCLASS rptTableCellParagraph : public rptParagraph
{
public:
   rptTableCellParagraph(): rptParagraph(), m_ColSpan(1), m_RowSpan(1), m_FillBackGroundColor(rptRiStyle::Default)
   {
   }

   /// Sets the table cell background fill color
   void SetFillBackGroundColor(rptRiStyle::FontColor color)
   {
      m_FillBackGroundColor = color;
   }

   /// Returns the table cell background fill color
   rptRiStyle::FontColor GetFillBackGroundColor() const
   {
      return m_FillBackGroundColor;
   }

private:
   friend rptRcTable;
   rptRiStyle::FontColor m_FillBackGroundColor;
   ColumnIndexType m_ColSpan;
   RowIndexType m_RowSpan;
};

/// Tabular report content
///
/// This class defines a table. Each cell in the table may be treated as a separate paragraph.
class REPORTERCLASS rptRcTable : public rptReportContent
{
public:
   rptRcTable(
      ColumnIndexType NumColumns, ///< Number of columns
      Float64 InitWidth ///< Initial total width of the table
   );

   rptRcTable(const rptRcTable& rOther);

   virtual ~rptRcTable();

   rptRcTable& operator=(const rptRcTable& rOther);

   /// Returns an individual table cell paragraph
   ///
   ///    table(5,5) << 15.235;
   ///
   /// The cells in column zero are column header cells.
   rptTableCellParagraph& operator()(RowIndexType RowNo, ColumnIndexType ColNo);

   /// Returns an individual table cell paragraph
   ///
   /// The cells in column zero are column header cells.
   const rptTableCellParagraph& operator()(RowIndexType RowNo, ColumnIndexType ColNo) const;


   /// Accepts a visitor and calls VisitRcTable(this)
   void Accept( rptRcVisitor& MyVisitor );

   /// Creates a clone
   virtual rptReportContent* CreateClone() const override;

   /// Returns the table Label paragraph
   ///
   /// The table label is placed below the caption and above the table.
   rptParagraph& TableLabel() {return m_Label;}

   /// Returns the table Caption paragram
   ///
   /// The table caption is placed above the table.
   rptParagraph& TableCaption() {return m_Caption;}

   /// Returns number of rows in the table, including the heading row
   RowIndexType GetNumberOfRows();

   /// Sets the horizontal alignment of table on the page
   void SetAlignment(rptRiStyle::AlignmentType Align);

   /// Returns the horizontal alignment of table on the page
   rptRiStyle::AlignmentType GetAlignment();

   /// Returns the number of columns
   ColumnIndexType GetNumberOfColumns() {return m_NumColumns;}

   /// Sets the number of columns
   void SetNumberOfColumns(ColumnIndexType nColumns);

   /// Sets the width (in inches) of a given column
   void SetColumnWidth(ColumnIndexType ColNo, Float64 MyWidth);

   /// Sets the style of a given column
   void SetColumnStyle(ColumnIndexType ColNo, const rptStyleName& MyStyleName);

   /// Set the stripe row style of a given column
   void SetStripeRowColumnStyle(ColumnIndexType ColNo, const rptStyleName& MyStyleName);

   /// Clear the style of a given column to allow column to inherit style from the table chain of responsibility.
   void ClearColumnStyle(ColumnIndexType ColNo);

   /// Returns the width (in inches) of the table
   Float64 GetTableWidth() const;

   /// Returns the width (in inches) of a given column
   Float64 GetColumnWidth(ColumnIndexType ColNo) const;

   /// Sets the cell padding, distance between cell content and cell border (in inches)
   void SetCellPad(Float64 MyCellPad);

   /// Returns the cell padding.
   Float64 GetCellPad() const;

   /// Fills a column with Float64 values by using the given rptRcUnitValue object as a prototype.
   /// Only the values are put into the column, not the unit strings.
   /// This function will append the data to any other data that exists in the column.
   void FillColumn(ColumnIndexType ColNo, rptRcUnitValue& ProtoReal, const std::vector<Float64>& vValues);

   /// Fills a columne with section values by using the given rptRcSectionValue object as a prototype.
   /// This function will append the data to any other data that exists in the column.
   void FillColumn(ColumnIndexType colNo,rptRcSectionValue& rPrototype, const std::vector<sysSectionValue>& vValues);

   /// Fills a column with integer values by using the given rptRcInt object as a prototype.
   /// This function will append the data to any other data that exists in the column.
   void FillColumn(ColumnIndexType ColNo, rptRcInt& ProtoInt, const std::vector<Int64>& vValues);

   /// Fills a column with text strings.
   /// This function will append the data to any other data that exists in the column.
   void FillColumn(ColumnIndexType ColNo,const std::vector<std::_tstring>& vStrings);

   /// Sets the border style of all inside borders in the table
   void SetInsideBorderStyle(rptRiStyle::BorderStyle MyStyle);

   /// Returns the border style of all inside borders in the table
   rptRiStyle::BorderStyle GetInsideBorderStyle() const;

   /// Sets the border style of the table perimeter
   void SetOutsideBorderStyle(rptRiStyle::BorderStyle MyStyle);

   /// Returns the border style of the table perimeter
   rptRiStyle::BorderStyle GetOutsideBorderStyle() const;

   /// Sets the border style of the line below the header row
   void SetHeaderBottomBorderStyle(rptRiStyle::BorderStyle MyStyle);

   /// Returns the border style of the line below the header row
   rptRiStyle::BorderStyle GetHeaderBottomBorderStyle() const;

   /// Sets style of table header text
   ///
   /// The table header style will have that of overall table style if this is not used. 
   /// This setting will override individual cell style settings.
   void SetTableHeaderStyle( const rptStyleName& MyStyleName);

   /// Sets number of columns to right that a given cell will span
   ///
   /// span==1 is the default
   /// span==0 will cause it to span all following columns
   /// span==SKIP_CELL will cause the cell at this location not to be generated
   /// if bSkipSpannedCells is true, all columns from ColNo+1 to ColNo+span-1 are filled with SKIP_CELL
   void SetColumnSpan(RowIndexType RowNo, ColumnIndexType ColNo, ColumnIndexType span, bool bSkipSpannedCells=true);

   /// Sets number of rows below that a given cell will span 
   /// span==1 is the default
   /// span==0 will case it to span all following rows
   /// span == SKIP_CELL will cause the cell at this location not to be generated
   /// if bSkipSpannedCells is true, all rows from RolNo+1 to RolNo+span-1 are filled with SKIP_CELL
   void SetRowSpan(RowIndexType RowNo, ColumnIndexType ColNo, RowIndexType span, bool bSkipSpannedCells=true);

   /// Spans rows and columns together
   void SetRowColumnSpan(RowIndexType RowNo, ColumnIndexType ColNo, RowIndexType rowSpan, ColumnIndexType colSpan, bool bSkipSpannedCells = true);

   /// Returns row and column spanning information for a given cell
   void GetCellSpans(RowIndexType RowNo, ColumnIndexType ColNo, RowIndexType* pRowSpan, ColumnIndexType* pColSpan);

   /// Sets the number of header rows
   void SetNumberOfHeaderRows(RowIndexType nrows);

   /// Returns the number of header rows
   RowIndexType GetNumberOfHeaderRows() const;

   /// Sets the row striping option.
   void EnableRowStriping(
      bool bEnable ///< If true, every number of striped rows is styled with the striped row style
   );

   /// Returns the row striping setting
   bool EnableRowStriping() const;

   /// Sets the number of rows to be striped together
   void SetNumberOfStripedRows(RowIndexType nrows);

   /// Returns the number of rows that are striped together
   RowIndexType GetNumberOfStripedRows();

   /// Returns true if the specified row uses the row striping style
   bool IsStripedRow(RowIndexType row) const;

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRcTable& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptRcTable& rOther);

private:
   rptRcTable() = delete;

   ColumnIndexType m_NumColumns;
   RowIndexType m_NumberOfHeaderRows;
   RowIndexType m_NumberOfStripedRows;
   bool m_bStripeRows;
   rptParagraph m_Label;
   rptParagraph m_Caption;

   // 2D array of paragraphs - the table data
   // Column Headers are held in row zero
   typedef std::vector<rptTableCellParagraph>  ColumnVector;
   typedef std::vector<ColumnVector> TableData;
   TableData m_TableData;

   // width of table column widths in inches
   std::vector<Float64> m_ColumnWidths;

   // Distance between cell content and cell border
   Float64 m_CellPad;

   // Table alignment wrt margins
   rptRiStyle::AlignmentType m_Alignment;

   // array of styles for table columns. These styles are pertinent only to
   // the table rows below the table header. Could not use an stl container
   // to hold these guys because the table cells refer to there addresses
   // directly.
   rptStyleHolder* m_pColumnStyles;
   rptStyleHolder* m_pStripeRowColumnStyles;

   // default border style for table perimeter
   rptRiStyle::BorderStyle m_OutsideBorderStyle;

   // default border style for table interior
   rptRiStyle::BorderStyle m_InsideBorderStyle;

   // default border style for line below header
   rptRiStyle::BorderStyle m_HeaderBottomBorderStyle;
};

#endif // INCLUDED_REPORTER_RCTABLE_H_
