///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

#include <Reporter\ReporterLib.h>
#include <Reporter\RcTable.h>
#include <Reporter\RcString.h>
#include <Reporter\RcUnitValue.h>
#include <Reporter\RcSectionValue.h>
#include <xutility>
#include <MathEx.h>

rptRcTable::rptRcTable(ColumnIndexType NumColumns, Float64 InitWidth)
{
   CHECK(NumColumns>0);
   m_NumColumns = NumColumns;

   // first row is header unless overridden
   m_NumberOfHeaderRows = 1;
   m_NumberOfStripedRows = 1;
   m_bStripeRows = true;

   // set cell padding to 0"
   m_CellPad = 0.0;

   // set alignment
   m_Alignment = rptRiStyle::LEFT;

   // allocate style holders for each of the table columns and set
   // the table as the next step in the stle chain-of-dependency

   m_pColumnStyles = new rptStyleHolder[m_NumColumns];
   CHECK(m_pColumnStyles);
   for (ColumnIndexType i = 0; i<NumColumns; i++)
      (m_pColumnStyles+i)->SetParent(this);

   m_pStripeRowColumnStyles = new rptStyleHolder[m_NumColumns];
   CHECK(m_pStripeRowColumnStyles);
   for (ColumnIndexType i = 0; i < NumColumns; i++)
   {
      (m_pStripeRowColumnStyles+i)->SetParent(this);
   }

   // push columns onto the rows and set cell widths

   Float64 CellWidth = InitWidth / NumColumns;

   for ( ColumnIndexType i = 0; i < NumColumns; i++)
   {
      m_TableData.emplace_back( /*ColumnVector()*/ );
      // push the header row onto the table and set the parent of the 
      // header row cells to be the table itself.
      m_TableData[i].emplace_back( /*rptTableCellParagraph()*/ );
      rptParagraph& rp = m_TableData[i][0];
      rp.SetParent(this);

      m_ColumnWidths.push_back(CellWidth);
   }

   // set style parent of caption and label to this table
   m_Caption.SetParent(this);
   m_Label.SetParent(this);

   // set up some reasonable styles for cell borders
   m_OutsideBorderStyle           = rptRiStyle::HAIR_THICK;
   m_InsideBorderStyle            = rptRiStyle::NOBORDER;
   m_HeaderBottomBorderStyle      = rptRiStyle::DOUBLE_LINE;

}


rptRcTable::rptRcTable(const rptRcTable& rOther) :
rptReportContent(rOther)
{
   m_pColumnStyles = 0;
   m_pStripeRowColumnStyles = 0;
   MakeCopy(rOther);
}

rptRcTable::~rptRcTable()
{
   // remove the array of column styles
   delete[] m_pColumnStyles;
   delete[] m_pStripeRowColumnStyles;
}

rptRcTable& rptRcTable::operator= (const rptRcTable& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

rptTableCellParagraph& rptRcTable::operator()( RowIndexType RowNo, ColumnIndexType ColNo)
{
   PRECONDITION(ColNo<m_NumColumns);
   if ( m_NumColumns <= ColNo )
   {
      ColNo = m_NumColumns-1;
   }

   // check if row entry has been allocated. if not, push default paragraphs
   // on as a placeholder
   RowIndexType nRows = m_TableData[ColNo].size();
   if (nRows - m_NumberOfHeaderRows <= RowNo)
   {
      for (RowIndexType row = nRows; row <= RowNo; row++)
      {
         m_TableData[ColNo].emplace_back( /*rptTableCellParagraph()*/ );

         if ( IsStripedRow(row) )
            m_TableData[ColNo].back().SetParent(m_pStripeRowColumnStyles+ColNo);
         else
            m_TableData[ColNo].back().SetParent(m_pColumnStyles+ColNo);
      }
   }

   return m_TableData[ColNo][RowNo];
}

const rptTableCellParagraph& rptRcTable::operator()(RowIndexType RowNo, ColumnIndexType ColNo) const
{
   PRECONDITION(ColNo<m_NumColumns);

   if ( m_NumColumns <= ColNo )
   {
      ColNo = m_NumColumns-1;
   }

   // check if row entry has been allocated. If it has not, then assert out
   // We can't grow the table because this is a const method
   CHECKX( RowNo < (RowIndexType)m_TableData[ColNo].size(), _T("The specified row has not been allocated"));

   return m_TableData[ColNo][RowNo];
}

rptReportContent* rptRcTable::CreateClone() const 
{ 
   return new rptRcTable(*this); 
}

void rptRcTable::Accept( rptRcVisitor& MyVisitor )
{
   MyVisitor.VisitRcTable(this);
}

RowIndexType rptRcTable::GetNumberOfRows()
{
   // return the length of the longest column
   RowIndexType NumRows = 0;
   for (ColumnIndexType i = 0; i<m_NumColumns; i++)
   {
      // The compiler can't tell if there parameters are unsigned ints or
      // unsigned shorts.  We have to tell it specifically so it can
      // use the template method.
      NumRows = Max( NumRows, (RowIndexType)m_TableData[i].size() );
   }

   return NumRows;
}

void rptRcTable::SetColumnWidth(ColumnIndexType ColNo, Float64 MyWidth)
{
   CHECK(ColNo<m_NumColumns);
   CHECK(MyWidth>0);

   if ( m_NumColumns <= ColNo )
   {
      ColNo = m_NumColumns-1;
   }

   // set new width
   m_ColumnWidths[ColNo] = MyWidth;
}

Float64 rptRcTable::GetTableWidth() const
{
   CHECK(m_NumColumns>0);

   Float64 tmp =0.;
   for (ColumnIndexType i = 0; i<m_NumColumns; i++)
   {
      tmp += GetColumnWidth(i);
   }

   return  tmp;
}

Float64 rptRcTable::GetColumnWidth(ColumnIndexType ColNo) const
{
   CHECK(ColNo<m_NumColumns);

   if ( m_NumColumns <= ColNo )
   {
      ColNo = m_NumColumns-1;
   }

   return  m_ColumnWidths[ColNo];
}

void rptRcTable::SetCellPad(Float64 MyCellPad)
{
   CHECK(MyCellPad>=0);
   m_CellPad = MyCellPad;
}

Float64 rptRcTable::GetCellPad() const
{
   return m_CellPad;
}

void rptRcTable::SetAlignment(rptRiStyle::AlignmentType Align)
{
   m_Alignment = Align;
}

rptRiStyle::AlignmentType rptRcTable::GetAlignment()
{
   return m_Alignment;
}

void rptRcTable::SetColumnStyle(ColumnIndexType ColNo, const rptStyleName& MyStyleName)
{
   CHECK(ColNo<m_NumColumns);

   if ( m_NumColumns <= ColNo )
   {
      ColNo = m_NumColumns-1;
   }

   // set the style for the style holder
   (m_pColumnStyles+ColNo)->SetStyleName(MyStyleName);

   if ( m_NumberOfHeaderRows == 0 )
   {
      m_TableData[ColNo][0].SetStyleName(MyStyleName);
   }
}

void rptRcTable::SetStripeRowColumnStyle(ColumnIndexType ColNo, const rptStyleName& MyStyleName)
{
   CHECK(ColNo<m_NumColumns);

   if ( m_NumColumns <= ColNo )
   {
      ColNo = m_NumColumns-1;
   }

   // set the style for the style holder
   (m_pStripeRowColumnStyles+ColNo)->SetStyleName(MyStyleName);
}

void rptRcTable::ClearColumnStyle(ColumnIndexType ColNo)
{
   CHECK(ColNo<m_NumColumns);

   if ( m_NumColumns <= ColNo )
   {
      ColNo = m_NumColumns-1;
   }

   // clear the style for the style holder
   (m_pColumnStyles+ColNo)->ClearStyle();
   (m_pStripeRowColumnStyles+ColNo)->ClearStyle();
}

void rptRcTable::FillColumn(ColumnIndexType ColNo, rptRcUnitValue& ProtoReal, const std::vector<Float64>& vValues)
{
   CHECK(ColNo<m_NumColumns);

   if ( m_NumColumns <= ColNo )
   {
      ColNo = m_NumColumns-1;
   }

   // check if header row entry has been allocated.
   CHECK(m_TableData[ColNo].size()>0);

   RowIndexType nRows = vValues.size();

   // cycle through all of the Float64s and push them into the table as rptRcReals

   for ( RowIndexType i = 0; i < nRows; i++ )
   {
      m_TableData[ColNo].emplace_back( /*rptTableCellParagraph()*/ );
      rptParagraph& rploc = m_TableData[ColNo].back();

      if ( IsStripedRow(i) )
      {
         rploc.SetParent(m_pStripeRowColumnStyles+ColNo);
      }
      else
      {
         rploc.SetParent(m_pColumnStyles+ColNo);
      }

      // make a new real from the proto type and stream it away
      ProtoReal.SetValue( vValues[i] );
      rploc << ProtoReal.CreateClone();
   }
}

void rptRcTable::FillColumn(ColumnIndexType colNo,rptRcSectionValue& rPrototype,const std::vector<WBFL::System::SectionValue>& vValues)
{
   CHECK( colNo < m_NumColumns );

   if ( m_NumColumns <= colNo )
   {
      colNo = m_NumColumns-1;
   }

   // check if header row entry has been allocated.
   CHECK( m_TableData[colNo].size() > 0 );

   std::vector<WBFL::System::SectionValue>::const_iterator i;
   RowIndexType row = 0;
   for ( i = vValues.begin(); i != vValues.end(); i++ )
   {
      m_TableData[colNo].emplace_back( /*rptTableCellParagraph()*/ );
      rptParagraph& rploc = m_TableData[colNo].back();

      if ( IsStripedRow(row) )
      {
         rploc.SetParent(m_pStripeRowColumnStyles+colNo);
      }
      else
      {
         rploc.SetParent(m_pColumnStyles+colNo);
      }

      row++;

      // make a new real from the proto type and stream it away
      rPrototype.SetValue( *i );
      rploc << rPrototype.CreateClone();
   }
}

void rptRcTable::FillColumn(ColumnIndexType ColNo, rptRcInt& ProtoInt, const std::vector<Int64>& vValues)
{
   CHECK(ColNo<m_NumColumns);

   if ( m_NumColumns <= ColNo )
   {
      ColNo = m_NumColumns-1;
   }

   // check if header row entry has been allocated.
   CHECK(m_TableData[ColNo].size()>0);

   RowIndexType nRows = vValues.size();

   // cycle through all of the Float64s and push them into the table as rptRcInt's

   for (RowIndexType i = 0; i<nRows; i++)
   {
      m_TableData[ColNo].emplace_back( /*rptTableCellParagraph()*/ );
      rptParagraph& rploc = m_TableData[ColNo].back();
      
      if ( IsStripedRow(i) )
      {
         rploc.SetParent(m_pStripeRowColumnStyles+ColNo);
      }
      else
      {
         rploc.SetParent(m_pColumnStyles+ColNo);
      }

      rploc << ( ProtoInt.Sv(vValues[i] ) );
   }
}

void rptRcTable::FillColumn(ColumnIndexType ColNo, const std::vector<std::_tstring>& vValues)
{
   CHECK(ColNo<m_NumColumns);

   if ( m_NumColumns <= ColNo )
   {
      ColNo = m_NumColumns-1;
   }

   // check if header row entry has been allocated. 
   CHECK(m_TableData[ColNo].size()>0);

   RowIndexType nRows = vValues.size();

   // cycle through all of the strings and push them into the table as rptRcStrings

   for (RowIndexType i = 0; i<nRows; i++)
   {
      m_TableData[ColNo].emplace_back( /*rptTableCellParagraph()*/ );
      rptParagraph& rploc = m_TableData[ColNo].back();

      if ( IsStripedRow(i) )
      {
         rploc.SetParent(m_pStripeRowColumnStyles+ColNo);
      }
      else
      {
         rploc.SetParent(m_pColumnStyles+ColNo);
      }

      rploc << new rptRcString(vValues[i] );
   }
}

void rptRcTable::SetInsideBorderStyle(rptRiStyle::BorderStyle MyStyle)
{
   CHECK(MyStyle!=rptRiStyle::BRDRSIZE);

   m_InsideBorderStyle = MyStyle;
}

rptRiStyle::BorderStyle rptRcTable::GetInsideBorderStyle() const
{
   return m_InsideBorderStyle;
}

void rptRcTable::SetOutsideBorderStyle(rptRiStyle::BorderStyle MyStyle)
{
   CHECK(MyStyle!=rptRiStyle::BRDRSIZE);

   m_OutsideBorderStyle = MyStyle;
}

rptRiStyle::BorderStyle rptRcTable::GetOutsideBorderStyle() const
{
   return m_OutsideBorderStyle;
}

void rptRcTable::SetHeaderBottomBorderStyle(rptRiStyle::BorderStyle MyStyle)
{
   CHECK(MyStyle!=rptRiStyle::BRDRSIZE);

   m_HeaderBottomBorderStyle = MyStyle;
}

rptRiStyle::BorderStyle rptRcTable::GetHeaderBottomBorderStyle() const
{
   return m_HeaderBottomBorderStyle;
}

void rptRcTable::SetTableHeaderStyle( const rptStyleName& MyStyleName)
{
   // loop over columns and set style of header paragraphs

   for (ColumnIndexType i = 0; i<m_NumColumns; i++)
   {
      CHECK(m_TableData[i].size());

      // set for header row paragraphs only
      for (RowIndexType j = 0; j < m_NumberOfHeaderRows; j++ )
      {
         if ( (RowIndexType)m_TableData[i].size() <= j )
         {
            m_TableData[i].emplace_back(/*rptTableCellParagraph()*/);
         }

         m_TableData[i][j].SetStyleName(MyStyleName);
      }
   }
}

void rptRcTable::SetColumnSpan(RowIndexType RowNo, ColumnIndexType ColNo, ColumnIndexType span, bool bSkipSpannedCells)
{
   CHECK(ColNo<m_NumColumns);
   CHECK(ColNo+(span==SKIP_CELL?1:span)-1<m_NumColumns);
   //CHECK(span>=-1);

   if(ColNo<m_NumColumns) 
   {
      // check if row entry has been allocated. if not, push default paragraphs
      // on as a placeholder
      ColumnIndexType cEnd = ColNo + (span == SKIP_CELL ? 1 : span);
      cEnd = min(cEnd, m_NumColumns); // don't allow overflow
      for ( ColumnIndexType c = ColNo; c < cEnd; c++)
      {
         RowIndexType nRows = m_TableData[c].size();
         if (nRows-m_NumberOfHeaderRows <= RowNo)
         {
            for (RowIndexType i=nRows; i<=RowNo; i++)
            {
               bool bIsStripedRow = IsStripedRow(i);
               m_TableData[c].emplace_back(/*rptTableCellParagraph()*/);

               if (bIsStripedRow)
               {
                  m_TableData[c].back().SetParent(m_pStripeRowColumnStyles + c);
               }
               else
               {
                  m_TableData[c].back().SetParent(m_pColumnStyles + c);
               }
            }
         }
      }

      m_TableData[ColNo][RowNo].m_ColSpan = span;

      if (bSkipSpannedCells && span != SKIP_CELL)
      {
         ColumnIndexType endSkipping = ColNo + span;
         for (ColumnIndexType i = ColNo+1; i < endSkipping && i < m_NumColumns; i++)
         {
            CHECK(m_TableData[i][RowNo].m_ColSpan != SKIP_CELL); // if this fires, the current cell is already skipped... you have overlapping spanning regions
            m_TableData[i][RowNo].m_ColSpan = SKIP_CELL;
         }
      }
   }
}

void rptRcTable::SetRowSpan(RowIndexType RowNo, ColumnIndexType ColNo, RowIndexType span,bool bSkipSpannedCells)
{
   CHECK(ColNo<m_NumColumns);
   //CHECK(span>=-1);

   if(ColNo<m_NumColumns) 
   {
      // check if row entry has been allocated. if not, push default paragraphs
      // on as a placeholder
      RowIndexType nRows = m_TableData[ColNo].size();
      RowIndexType endRow = RowNo + (span == SKIP_CELL ? 0 : span);
      if (nRows-m_NumberOfHeaderRows <= endRow)
      {
         for (RowIndexType i = nRows; i <= endRow; i++)
         {
            m_TableData[ColNo].emplace_back( /*rptTableCellParagraph()*/ );

            if (IsStripedRow(i))
            {
               m_TableData[ColNo].back().SetParent(m_pStripeRowColumnStyles + ColNo);
            }
            else
            {
               m_TableData[ColNo].back().SetParent(m_pColumnStyles + ColNo);
            }
         }
      }

      m_TableData[ColNo][RowNo].m_RowSpan = span;
      if (bSkipSpannedCells && span != SKIP_CELL)
      {
         for (RowIndexType r = RowNo + 1; r < endRow; r++)
         {
            m_TableData[ColNo][r].m_RowSpan = SKIP_CELL;
         }
      }
   }
}

void rptRcTable::SetRowColumnSpan(RowIndexType RowNo, ColumnIndexType ColNo, RowIndexType rowSpan, ColumnIndexType colSpan, bool bSkipSpannedCells)
{
   CHECK(ColNo < m_NumColumns);
   CHECK(ColNo + (colSpan == SKIP_CELL ? 1 : colSpan) - 1 < m_NumColumns);
   //CHECK(span>=-1);

   if (ColNo < m_NumColumns)
   {
      // check if row entry has been allocated. if not, push default paragraphs
      // on as a placeholder
      RowIndexType nRows = m_TableData[ColNo].size();
      if (nRows - m_NumberOfHeaderRows <= RowNo)
      {
         for (RowIndexType i = nRows; i <= RowNo; i++)
         {
            bool bIsStripedRow = IsStripedRow(i);
            ColumnIndexType jEnd = (colSpan == SKIP_CELL ? 1 : colSpan);
            for (ColumnIndexType j = 0; j < jEnd; j++)
            {
               m_TableData[ColNo + j].emplace_back(/*rptTableCellParagraph()*/);

               if (bIsStripedRow)
               {
                  m_TableData[ColNo + j].back().SetParent(m_pStripeRowColumnStyles + ColNo + j);
               }
               else
               {
                  m_TableData[ColNo + j].back().SetParent(m_pColumnStyles + ColNo + j);
               }
            }
         }
      }

      m_TableData[ColNo][RowNo].m_RowSpan = rowSpan;
      m_TableData[ColNo][RowNo].m_ColSpan = colSpan;
   
      if (bSkipSpannedCells && colSpan != SKIP_CELL)
      {
         ColumnIndexType endColumnSkipping = ColNo + colSpan;
         RowIndexType endRowSkipping = RowNo + (rowSpan == SKIP_CELL ? 0 : rowSpan);
         for (ColumnIndexType c = ColNo + 1; c < endColumnSkipping && c < m_NumColumns; c++)
         {
            m_TableData[c][RowNo].m_ColSpan = SKIP_CELL; // skip remaining cells on the primary row in this skip range
         }

         // for all the remaining rows, skip the entire column span
         for (RowIndexType r = RowNo + 1; r < endRowSkipping; r++)
         {
            for (ColumnIndexType c = ColNo; c < endColumnSkipping && c < m_NumColumns; c++)
            {
               m_TableData[c][r].m_RowSpan = SKIP_CELL;
               m_TableData[c][r].m_ColSpan = SKIP_CELL;
            }
         }
      }
   }
}

void rptRcTable::GetCellSpans(RowIndexType RowNo, ColumnIndexType ColNo, RowIndexType* pRowSpan, ColumnIndexType* pColSpan)
{
   CHECK(ColNo<m_NumColumns);

   if ( m_NumColumns <= ColNo )
   {
      ColNo = m_NumColumns-1;
   }

   // check if row entry has been allocated. if not, push default paragraphs
   // on as a placeholder
   RowIndexType nRows = m_TableData[ColNo].size();
   if (nRows-m_NumberOfHeaderRows < RowNo + (m_NumberOfHeaderRows == 0 ? 1 : 0))
   {
      for (RowIndexType i=nRows; i<=RowNo; i++)
      {
         m_TableData[ColNo].emplace_back( /*rptTableCellParagraph()*/ );

         if ( IsStripedRow(i) )
            m_TableData[ColNo].back().SetParent(m_pStripeRowColumnStyles+ColNo);
         else
            m_TableData[ColNo].back().SetParent(m_pColumnStyles+ColNo);
      }
   }

   rptTableCellParagraph& rpara = m_TableData[ColNo][RowNo];
   *pRowSpan = rpara.m_RowSpan;
   *pColSpan = rpara.m_ColSpan;
}

void rptRcTable::SetNumberOfHeaderRows(RowIndexType nrows)
{
   if ( nrows == 0 )
   {
      // we are losing the header rows
      for (ColumnIndexType col = 0; col < m_NumColumns; col++ )
      {
         for (RowIndexType row = 0; row < m_NumberOfHeaderRows; row++ )
         {
            if ((RowIndexType)m_TableData[col].size() <= row)
            {
               m_TableData[col].emplace_back(/*rptTableCellParagraph()*/);
            }

            m_TableData[col][row].SetStyleName( m_pColumnStyles[col].GetStyleName() );
         }
      }

      m_NumberOfHeaderRows = nrows;
   }
   else
   {
      m_NumberOfHeaderRows = nrows;
      SetTableHeaderStyle(m_TableData[0][0].GetStyleName());
   }
}

RowIndexType rptRcTable::GetNumberOfHeaderRows() const
{
   return m_NumberOfHeaderRows;
}

void rptRcTable::EnableRowStriping(bool bEnable)
{
   m_bStripeRows = bEnable;
}

bool rptRcTable::EnableRowStriping() const
{
   return m_bStripeRows;
}

void rptRcTable::SetNumberOfStripedRows(RowIndexType nrows)
{
   m_NumberOfStripedRows = nrows;
}

RowIndexType rptRcTable::GetNumberOfStripedRows()
{
   return m_NumberOfStripedRows;
}

bool rptRcTable::IsStripedRow(RowIndexType row) const
{
   RowIndexType stripeGroup = (row-m_NumberOfHeaderRows)/m_NumberOfStripedRows;
   return m_bStripeRows && (stripeGroup % 2 != 0);
}

void rptRcTable::MakeCopy(const rptRcTable& rOther)
{
   m_NumColumns                 = rOther.m_NumColumns;
   m_Label                      = rOther.m_Label;
   m_Caption                    = rOther.m_Caption;
   m_ColumnWidths               = rOther.m_ColumnWidths;
   m_OutsideBorderStyle         = rOther.m_OutsideBorderStyle;
   m_InsideBorderStyle          = rOther.m_InsideBorderStyle;
   m_HeaderBottomBorderStyle    = rOther.m_HeaderBottomBorderStyle;
   m_CellPad                    = rOther.m_CellPad;
   m_Alignment                  = rOther.m_Alignment;
   m_NumberOfHeaderRows         = rOther.m_NumberOfHeaderRows;
   m_NumberOfStripedRows        = rOther.m_NumberOfStripedRows;
   m_bStripeRows                = rOther.m_bStripeRows;

   // stl copy will copy table data, but style chain of responsibility
   // will still point to table being copied - need to rebuild chain.
   m_TableData                  = rOther.m_TableData;

   // deal with column StyleHolders
   //  first allocate room
   delete[] m_pColumnStyles;
   m_pColumnStyles = new rptStyleHolder[m_NumColumns];
   CHECK(m_pColumnStyles);
   // next copy the style holders and reset their parents to point to
   // this table
   for (ColumnIndexType i = 0; i<m_NumColumns; i++)
   {
      *(m_pColumnStyles+i) = *(rOther.m_pColumnStyles+i);
      (m_pColumnStyles+i)->ClearParent();
      (m_pColumnStyles+i)->SetParent(this);
   }

   // deal with column StyleHolders
   //  first allocate room
   delete[] m_pStripeRowColumnStyles;
   m_pStripeRowColumnStyles = new rptStyleHolder[m_NumColumns];
   CHECK(m_pStripeRowColumnStyles);
   // next copy the style holders and reset their parents to point to
   // this table
   for (ColumnIndexType i = 0; i < m_NumColumns; i++)
   {
      *(m_pStripeRowColumnStyles+i) = *(rOther.m_pStripeRowColumnStyles+i);
      (m_pStripeRowColumnStyles+i)->ClearParent();
      (m_pStripeRowColumnStyles+i)->SetParent(this);
   }

   // loop over all cells in table and set up parents
   for ( ColumnIndexType i = 0; i < m_NumColumns; i++)
   {
      ColumnIndexType clsize = m_TableData[i].size();
      CHECK(clsize);

      // first row in column is header - it's parent for styles is
      // the table itself
      m_TableData[i][0].ClearParent();
      m_TableData[i][0].SetParent(this);

      // the rest of the rows look to thier ColumnStyles for style info.
      for (ColumnIndexType j=1; j<clsize; j++)
      {
         m_TableData[i][j].ClearParent(); 
         if ( IsStripedRow(j) )
            m_TableData[i][j].SetParent(m_pStripeRowColumnStyles+i);
         else
            m_TableData[i][j].SetParent(m_pColumnStyles+i);
      }
   }

}

void rptRcTable::MakeAssignment(const rptRcTable& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}

void rptRcTable::SetNumberOfColumns(ColumnIndexType nColumns)
{
   CHECK(nColumns>0);

   // hang onto old points
   rptStyleHolder* pColumnStyles = m_pColumnStyles;
   rptStyleHolder* pStripeRowColumnStyles = m_pStripeRowColumnStyles;

   // create new style objects and copy the old styles into the new styles
   m_pColumnStyles = new rptStyleHolder[nColumns];
   m_pStripeRowColumnStyles = new rptStyleHolder[nColumns];
   for ( ColumnIndexType i = 0; i < nColumns; i++ )
   {
      if ( i < m_NumColumns )
      {
         *(m_pColumnStyles+i) = *(pColumnStyles+i);
         (m_pColumnStyles+i)->ClearParent();
         (m_pColumnStyles+i)->SetParent(this);

         *(m_pStripeRowColumnStyles+i) = *(pStripeRowColumnStyles+i);
         (m_pStripeRowColumnStyles+i)->ClearParent();
         (m_pStripeRowColumnStyles+i)->SetParent(this);
      }
      else
      {
         *(m_pColumnStyles+i) = *(m_pColumnStyles+i-1);
         (m_pColumnStyles+i)->ClearParent();
         (m_pColumnStyles+i)->SetParent(this);

         *(m_pStripeRowColumnStyles+i) = *(m_pStripeRowColumnStyles+i-1);
         (m_pStripeRowColumnStyles+i)->ClearParent();
         (m_pStripeRowColumnStyles+i)->SetParent(this);
      }
   }

   // loop over all cells in table and set up new parents
   for ( ColumnIndexType i = 0; i < m_NumColumns; i++)
   {
      ColumnIndexType clsize = m_TableData[i].size();
      CHECK(clsize);

      // first row in column is header - it's parent for styles is
      // the table itself
      m_TableData[i][0].ClearParent();
      m_TableData[i][0].SetParent(this);

      // the rest of the rows look to thier ColumnStyles for style info.
      for (ColumnIndexType j=1; j<clsize; j++)
      {
         m_TableData[i][j].ClearParent(); 
         if ( IsStripedRow(j) )
         {
            m_TableData[i][j].SetParent(m_pStripeRowColumnStyles+i);
         }
         else
         {
            m_TableData[i][j].SetParent(m_pColumnStyles+i);
         }
      }
   }

   // resize the column and tables
   m_ColumnWidths.resize(nColumns,m_ColumnWidths.back());
   m_TableData.resize(nColumns,ColumnVector());

   // add default data to all new columns
   for ( ColumnIndexType i = m_NumColumns; i < nColumns; i++ )
   {
      RowIndexType nHeaderRows = GetNumberOfHeaderRows();
      for ( RowIndexType j = 0; j < nHeaderRows; j++ )
      {
         m_TableData[i].emplace_back( /*rptTableCellParagraph()*/ );
         m_TableData[i][j].SetStyleName( m_TableData[0][j].GetStyleName() );
      }

      RowIndexType nRows = GetNumberOfRows();
      for ( RowIndexType j = nHeaderRows; j < nRows; j++ )
      {
         m_TableData[i].emplace_back( /*rptTableCellParagraph()*/ );
         if ( IsStripedRow(j) )
         {
            m_TableData[i][j].SetParent(m_pStripeRowColumnStyles+i);
         }
         else
         {
            m_TableData[i][j].SetParent(m_pColumnStyles+i);
         }
      }
   }

   // done with the old styles
   delete[] pColumnStyles;
   delete[] pStripeRowColumnStyles;

   // set the new number of columns
   m_NumColumns = nColumns;
}
