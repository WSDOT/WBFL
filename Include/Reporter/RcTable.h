//////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

#include <vector>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\Paragraph.h>
#include <Reporter\ReportingUtils.h>
#include <Reporter\StyleHolder.h>
#include <Reporter\RcInt.h>
#include <System\SectionValue.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

#define SKIP_CELL INVALID_INDEX

/*****************************************************************************
CLASS 
   rptRcTable

   Data Table class


DESCRIPTION
   This class defines a two-dimensional table of report content. Each cell in
   the table may be treated as a separate paragraph.

LOG
   rdp : 04.21.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcTable : public rptReportContent
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // constructor
   // build an empty table with NumColumns Columns of equal width.
   // InitWidth is the inital total width and will change as column widths are modified.
   rptRcTable(ColumnIndexType NumColumns, Float64 InitWidth);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcTable(const rptRcTable& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcTable();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   // Returns reference to itself
   rptRcTable& operator = (const rptRcTable& rOther);

   //------------------------------------------------------------------------
   // Get an individual cell paragraph
   // Note that cells in column zero are column header cells.
   rptParagraph& operator()(RowIndexType RowNo, ColumnIndexType ColNo);

   //------------------------------------------------------------------------
   // constant version of get cell paragraph
   const rptParagraph& operator()(RowIndexType RowNo, ColumnIndexType ColNo) const;


   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Accept a visitor
   void Accept( rptRcVisitor& MyVisitor );

   //------------------------------------------------------------------------
   // Create a Clone
   rptReportContent* CreateClone() const;

   //------------------------------------------------------------------------
   // Get the table Label paragraph
   rptParagraph& TableLabel() {return m_Label;}

   //------------------------------------------------------------------------
   // Get the table Caption
   rptParagraph& TableCaption() {return m_Caption;}

   //------------------------------------------------------------------------
   // Get Number of rows in table - including the header row
   RowIndexType GetNumberOfRows();

   //------------------------------------------------------------------------
   // Set Distance between left edge of table and left margin
   void SetAlignment(rptRiStyle::AlignmentType Align);

   //------------------------------------------------------------------------
   // Get Distance between left edge of table and left margin
   rptRiStyle::AlignmentType GetAlignment();

   //------------------------------------------------------------------------
   // Get Number of columns in table
   ColumnIndexType GetNumberOfColumns() {return m_NumColumns;}

   void SetNumberOfColumns(ColumnIndexType nColumns);

   //------------------------------------------------------------------------
   // Set the width (in inches) of a given column
   void SetColumnWidth(ColumnIndexType ColNo, Float64 MyWidth);

   //------------------------------------------------------------------------
   // Set the style of a given column
   void SetColumnStyle(ColumnIndexType ColNo, const rptStyleName& MyStyleName);

   //------------------------------------------------------------------------
   // Set the stripe row style of a given column
   void SetStripeRowColumnStyle(ColumnIndexType ColNo, const rptStyleName& MyStyleName);

   //------------------------------------------------------------------------
   // Clear the style of a given column to allow column to inherit style back
   // from the table chain of responsibility.
   void ClearColumnStyle(ColumnIndexType ColNo);

   //------------------------------------------------------------------------
   // 
   // Get the width (in inches) of the table
   Float64 GetTableWidth() const;

   //------------------------------------------------------------------------
   // Get the width (in inches) of a given column
   Float64 GetColumnWidth(ColumnIndexType ColNo) const;

   //------------------------------------------------------------------------
   // Set the cell padding. Distance between cell content and cell border
   void SetCellPad(Float64 MyCellPad);

   //------------------------------------------------------------------------
   // Get the cell padding. Distance between cell content and cell border
   Float64 GetCellPad() const;

   //------------------------------------------------------------------------
   // Put a Float64 column by using the given rptRcReal object as a prototype.
   // Only the values are put into the column - not the unit strings.
   // This function will append the data to any other data that exists in 
   // the column.
   void PutFloat64Column(ColumnIndexType ColNo, rptRcUnitValue& ProtoReal, 
                        const std::vector<Float64>&);

   //------------------------------------------------------------------------
   // Put a section value column by using the given rptRcSectionValue object
   // as a prototype.
   void PutSectionValueColumn(ColumnIndexType colNo,
                              rptRcSectionValue& rPrototype,
                              const std::vector<sysSectionValue>& vValues);

   //------------------------------------------------------------------------
   // Put an integer column by using the given rptRcInt object as a prototype
   // This function will append the data to any other data that exists in 
   // the column.
   void PutLongColumn(ColumnIndexType ColNo, rptRcInt& ProtoInt, 
      const std::vector<Int32>&);

   //------------------------------------------------------------------------
   // Put a string column
   // This function will append the data to any other data that exists in 
   // the column.
   void PutStringColumn(ColumnIndexType ColNo,
      const std::vector<std::_tstring>&);

   //------------------------------------------------------------------------
   // Set the border style of all inside borders in the table
   void SetInsideBorderStyle(rptRiStyle::BorderStyle MyStyle);

   //------------------------------------------------------------------------
   // Get the border style of all inside borders in the table
   rptRiStyle::BorderStyle GetInsideBorderStyle() const;

   //------------------------------------------------------------------------
   // Set the border style of the table perimeter
   void SetOutsideBorderStyle(rptRiStyle::BorderStyle MyStyle);

   //------------------------------------------------------------------------
   // Get the border style of the table perimeter
   rptRiStyle::BorderStyle GetOutsideBorderStyle() const;

   //------------------------------------------------------------------------
   // set the border style of the line below the header row
   void SetHeaderBottomBorderStyle(rptRiStyle::BorderStyle MyStyle);

   //------------------------------------------------------------------------
   // get the border style of the line below the header row
   rptRiStyle::BorderStyle GetHeaderBottomBorderStyle() const;

   //------------------------------------------------------------------------
   // set style of table header text - note that the table header style will have
   // that of overall table style if this is not used. Note that this call will 
   // override individual cell style settings.
   void SetTableHeaderStyle( const rptStyleName& MyStyleName);

   //------------------------------------------------------------------------
   // Set number of Columns to right that a given cell will span
   // span==1 is the default
   // span==0 will case it to span all following columns
   // span==SKIP_CELL will cause the cell at this location not to be generated
   void SetColumnSpan(RowIndexType RowNo, ColumnIndexType ColNo, ColumnIndexType span);

   //------------------------------------------------------------------------
   // Set number of Columns to right that a given cell will span 
   // span==1 is the default
   // span==0 will case it to span all following rows
   // span == SKIP_CELL will cause the cell at this location not to be generated
   void SetRowSpan(RowIndexType RowNo, ColumnIndexType ColNo, RowIndexType span);

   //------------------------------------------------------------------------
   // Set column and row spans for a given cell
   void GetCellSpans(RowIndexType RowNo, ColumnIndexType ColNo, RowIndexType* pRowSpan, ColumnIndexType* pColSpan);

   // Set/Get number of rows in header
   void SetNumberOfHeaderRows(RowIndexType nrows);
   RowIndexType GetNumberOfHeaderRows() const;

   void EnableRowStriping(bool bEnable);
   bool EnableRowStriping() const;

   void SetNumberOfStripedRows(RowIndexType nrows);
   RowIndexType GetNumberOfStripedRows();

   bool IsStripedRow(RowIndexType row) const;

   //
   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   void MakeCopy(const rptRcTable& rOther);
   void MakeAssignment(const rptRcTable& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   //------------------------------------------------------------------------
   // number of columns in the table
   ColumnIndexType m_NumColumns;
   RowIndexType m_NumberOfHeaderRows;
   RowIndexType m_NumberOfStripedRows;
   bool m_bStripeRows;

   //------------------------------------------------------------------------
   // table lable
   rptParagraph m_Label;

   //------------------------------------------------------------------------
   // table caption
   rptParagraph m_Caption;

   // private class to store table-related paragraph data
   class rptTableCellParagraph : public rptParagraph
   {
   public:
      ColumnIndexType m_ColSpan;
      RowIndexType m_RowSpan;

      rptTableCellParagraph(): rptParagraph(), m_ColSpan(1), m_RowSpan(1)
      {
      }

   private:
   };

   //------------------------------------------------------------------------
   // 2D array of paragraphs - the table data
   // Column Headers are held in row zero
   typedef std::vector<rptTableCellParagraph>  ColumnVector;
   typedef std::vector<ColumnVector> TableData;
   TableData m_TableData;

   //------------------------------------------------------------------------
   // width of table column widths in inches
   std::vector<Float64> m_ColumnWidths;

   //------------------------------------------------------------------------
   // Distance between cell content and cell border
   Float64 m_CellPad;

   //------------------------------------------------------------------------
   // Table alignment wrt margins
   rptRiStyle::AlignmentType m_Alignment;

   //------------------------------------------------------------------------
   // array of styles for table columns. These styles are pertinent only to
   // the table rows below the table header. Could not use an stl container
   // to hold these guys because the table cells refer to there addresses
   // directly.
   rptStyleHolder* m_pColumnStyles;
   rptStyleHolder* m_pStripeRowColumnStyles;

   //------------------------------------------------------------------------
   // default border style for table perimeter
   rptRiStyle::BorderStyle m_OutsideBorderStyle;

   //------------------------------------------------------------------------
   // default border style for table interior
   rptRiStyle::BorderStyle m_InsideBorderStyle;

   //------------------------------------------------------------------------
   // default border style for line below header
   rptRiStyle::BorderStyle m_HeaderBottomBorderStyle;

   // GROUP: LIFECYCLE
   rptRcTable();
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif
