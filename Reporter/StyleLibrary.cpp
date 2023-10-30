

/****************************************************************************
CLASS
   rptStyleLibrary
****************************************************************************/
#include <Reporter\ReporterLib.h>
#include <Reporter\StyleLibrary.h>
#include <Reporter\FontStyleLibrary.h>
#include <Reporter\RcTable.h>

std::_tstring rptStyleLibrary::ms_ReportTitleStyle           = _T("ReportTitleStyle");
std::_tstring rptStyleLibrary::ms_ReportSubtitleStyle        = _T("ReportSubtitleStyle");
std::_tstring rptStyleLibrary::ms_ChapterTitleStyle          = _T("ChapterTitleStyle");
std::_tstring rptStyleLibrary::ms_HeadingStyle               = _T("HeadingStyle");
std::_tstring rptStyleLibrary::ms_SubheadingStyle            = _T("SubheadingStyle");
std::_tstring rptStyleLibrary::ms_TableColumnHeadingStyle    = _T("TableColumnHeadingStyle");
std::_tstring rptStyleLibrary::ms_TableDataStyleLeftJustify  = _T("TableDataStyle-LJ");
std::_tstring rptStyleLibrary::ms_TableDataStyleRightJustify = _T("TableDataStyle-RJ");
std::_tstring rptStyleLibrary::ms_FootnoteStyle              = _T("Footnote");
std::array<std::_tstring, 6> rptStyleLibrary::ms_TableCellStyle = {   _T("NB-LJ"),   _T("TB-LJ"),   _T("NB-RJ"),   _T("TB-RJ"),   _T("NB-CJ"),   _T("TB-CJ")};

std::_tstring rptStyleLibrary::ms_ImagePath= _T("");

Float64 rptStyleLibrary::ms_MaxTableWidth = 7.5; // 7.5" wide tables

void rptStyleLibrary::InitStyles(const std::_tstring& imagePath)
{
   // path name
   CHECK(imagePath.size()!=0);
   ms_ImagePath = imagePath;

   // load up the style library
   bool flag;
   rptFontStyleLibrary* psl = rptFontStyleLibrary::Instance();

   // Configure the default style
   rptRiStyle& default_style = psl->GetDefaultStyle();
   default_style.SetFontType(rptRiStyle::SWISS);
   default_style.SetFontSize(9);

   // Report Title
   rptRiStyle rpttitle;
   rpttitle.SetFontSize(16);
   rpttitle.SetBold( true );
   rpttitle.SetFontType(rptRiStyle::SWISS);
   rpttitle.SetAlignment(rptRiStyle::CENTER);
   flag = psl->AddNamedStyle(ms_ReportTitleStyle, rpttitle);
   //CHECK(flag);

   // Report Subtitle
   rptRiStyle rptsubtitle;
   rptsubtitle.SetFontSize(15);
   rptsubtitle.SetItalic( true );
   rptsubtitle.SetFontType(rptRiStyle::SWISS);
   rptsubtitle.SetAlignment(rptRiStyle::CENTER);
   flag = psl->AddNamedStyle(ms_ReportSubtitleStyle, rptsubtitle);
   //CHECK(flag);

   // Chapter Titles
   rptRiStyle  chaptertitle;
   chaptertitle.SetFontType(rptRiStyle::SWISS);
   chaptertitle.SetFontSize(13);
   chaptertitle.SetAlignment(rptRiStyle::LEFT);
   chaptertitle.SetBold( true );
   chaptertitle.SetColor( rptRiStyle::Blue );
   flag = psl->AddNamedStyle(ms_ChapterTitleStyle, chaptertitle);
   //CHECK(flag);
   
   // Headings
   rptRiStyle headings;
   headings.SetFontType(rptRiStyle::SWISS);
   headings.SetFontSize(11);
   headings.SetBold( true );
   flag = psl->AddNamedStyle(ms_HeadingStyle, headings);
   //CHECK(flag);
   
   // SubHeadings
   rptRiStyle subheadings;
   subheadings.SetFontType(rptRiStyle::SWISS);
   subheadings.SetFontSize(9);
   subheadings.SetItalic( true );
   subheadings.SetBold( true );
   flag = psl->AddNamedStyle(ms_SubheadingStyle, subheadings);
   //CHECK(flag);

   // Table Column Headings
   rptRiStyle colheadings;
   colheadings.SetFontSize(9);
   colheadings.SetFontType(rptRiStyle::SWISS);
   colheadings.SetAlignment(rptRiStyle::CENTER);
   colheadings.SetBold( true );
   flag = psl->AddNamedStyle(ms_TableColumnHeadingStyle, colheadings);
   //CHECK(flag);

   // Table cells

   // Table Data (Obsolete, but still in use)
   rptRiStyle table_data_style;
   table_data_style.SetFontType( rptRiStyle::SWISS );
   table_data_style.SetFontSize(9);
   table_data_style.SetAlignment( rptRiStyle::RIGHT );
   flag = psl->AddNamedStyle(ms_TableDataStyleRightJustify, table_data_style );

   table_data_style.SetAlignment( rptRiStyle::LEFT );
   flag = psl->AddNamedStyle(ms_TableDataStyleLeftJustify, table_data_style );
   //CHECK(flag);

   // Setup basic style
   rptRiStyle cell;
   cell.SetFontType(rptRiStyle::SWISS);
   cell.SetFontSize(9);

   // Style for No Border, Left Justified
   cell.SetAlignment(rptRiStyle::LEFT);
   cell.SetVerticalAlignment( rptRiStyle::TOP );
   cell.SetTopBorder(rptRiStyle::NOBORDER);
   cell.SetBottomBorder(rptRiStyle::NOBORDER);
   cell.SetLeftBorder(rptRiStyle::NOBORDER);
   cell.SetRightBorder(rptRiStyle::NOBORDER);
   psl->AddNamedStyle(ms_TableCellStyle[0],cell);

   // Style for Thin Border, Left Justified
   cell.SetTopBorder(rptRiStyle::HAIR_THICK);
   cell.SetBottomBorder(rptRiStyle::HAIR_THICK);
   cell.SetLeftBorder(rptRiStyle::HAIR_THICK);
   cell.SetRightBorder(rptRiStyle::HAIR_THICK);
   psl->AddNamedStyle(ms_TableCellStyle[1],cell);


   // Style for No Border, Right Justified
   cell.SetAlignment(rptRiStyle::RIGHT);
   cell.SetTopBorder(rptRiStyle::NOBORDER);
   cell.SetBottomBorder(rptRiStyle::NOBORDER);
   cell.SetLeftBorder(rptRiStyle::NOBORDER);
   cell.SetRightBorder(rptRiStyle::NOBORDER);
   psl->AddNamedStyle(ms_TableCellStyle[2],cell);

   // Style for Thin Border, Right Justified
   cell.SetTopBorder(rptRiStyle::HAIR_THICK);
   cell.SetBottomBorder(rptRiStyle::HAIR_THICK);
   cell.SetLeftBorder(rptRiStyle::HAIR_THICK);
   cell.SetRightBorder(rptRiStyle::HAIR_THICK);
   psl->AddNamedStyle(ms_TableCellStyle[3],cell);

   // Style for No Border, Center Justified
   cell.SetAlignment(rptRiStyle::CENTER);
   cell.SetTopBorder(rptRiStyle::NOBORDER);
   cell.SetBottomBorder(rptRiStyle::NOBORDER);
   cell.SetLeftBorder(rptRiStyle::NOBORDER);
   cell.SetRightBorder(rptRiStyle::NOBORDER);
   psl->AddNamedStyle(ms_TableCellStyle[4],cell);

   // Style for Thin Border, Right Justified
   cell.SetTopBorder(rptRiStyle::HAIR_THICK);
   cell.SetBottomBorder(rptRiStyle::HAIR_THICK);
   cell.SetLeftBorder(rptRiStyle::HAIR_THICK);
   cell.SetRightBorder(rptRiStyle::HAIR_THICK);
   psl->AddNamedStyle(ms_TableCellStyle[5],cell);

   // Footnote style
   rptRiStyle footnote;
   footnote.SetFontType( rptRiStyle::SWISS );
   footnote.SetFontSize(8);
   footnote.SetAlignment(rptRiStyle::LEFT);
   flag = psl->AddNamedStyle( ms_FootnoteStyle, footnote );
}

const std::_tstring& rptStyleLibrary::GetReportTitleStyle()
{
return ms_ReportTitleStyle;
}

const std::_tstring& rptStyleLibrary::GetReportSubtitleStyle()
{
return ms_ReportSubtitleStyle;
}

const std::_tstring& rptStyleLibrary::GetChapterTitleStyle()
{
return ms_ChapterTitleStyle;
}

const std::_tstring& rptStyleLibrary::GetHeadingStyle()
{
return ms_HeadingStyle;
}

const std::_tstring& rptStyleLibrary::GetSubheadingStyle()
{
return ms_SubheadingStyle;
}

const std::_tstring& rptStyleLibrary::GetTableColumnHeadingStyle()
{
return ms_TableColumnHeadingStyle;
}

const std::_tstring& rptStyleLibrary::GetTableDataStyle(Justification justify)
{
   return (justify == Left) ? ms_TableDataStyleLeftJustify : ms_TableDataStyleRightJustify;
}

const std::_tstring& rptStyleLibrary::GetTableCellStyle(Uint32 style)
{
   // Bit 1 = Border Style
   // Bit 2 = Justification
   //
   // 0 = No Border, Left Justified
   // 1 = Thin Border, Left Justified
   // 2 = No Border, Right Justified
   // 3 = Thin Border, Right Justified
   // 4 = No Border, Center Justified
   // 5 = Thin Border, Center Justified

   Int16 index = 0;

   if ( style & CB_NONE )
   {
      index |= 0x0000;
   }
   else if ( style & CB_THIN )
   {
      index |= 0x0001;
   }
   
   if ( style & CJ_LEFT )
   {
      index |= 0x0000;
   }
   else if ( style & CJ_RIGHT )
   {
      index |= 0x0002;
   }
   else if ( style & CJ_CENTER )
   {
      index |= 0x0004;
   }

   CHECK( 0 <= index && index <= 5 );

   return ms_TableCellStyle[index];
}

const std::_tstring& rptStyleLibrary::GetFootnoteStyle()
{
   return ms_FootnoteStyle;
}

Float64 rptStyleLibrary::GetMaxTableWidth()
{
   return ms_MaxTableWidth;
}

rptRcTable* rptStyleLibrary::CreateDefaultTable(unsigned numColumns, std::_tstring label,bool bLoadingColumn)
{
   rptRcTable* ptable = new rptRcTable( numColumns, rptStyleLibrary::GetMaxTableWidth() );
   if (!label.empty())
      ptable->TableLabel() << label;
   ptable->SetStyleName( rptStyleLibrary::GetTableDataStyle(Right) );
   ptable->TableLabel().SetStyleName( rptStyleLibrary::GetHeadingStyle() );
   ptable->SetTableHeaderStyle( rptStyleLibrary::GetTableColumnHeadingStyle() );
   ptable->SetOutsideBorderStyle( rptRiStyle::SINGLE_THICK );
   ptable->SetInsideBorderStyle( rptRiStyle::NOBORDER );
   ptable->SetCellPad( 0.0625 );

   // Limit all columns to 0.75" except first which is 1.2"
   ptable->SetColumnWidth(0,1.2);
   for (unsigned i = 1; i<numColumns; i++)
      ptable->SetColumnWidth(i,0.75);

   // Ok, Column 1 is 1.5"
   if ( bLoadingColumn )
   {
     ptable->SetColumnWidth(1,1.5);
     ptable->SetColumnStyle(1, rptStyleLibrary::GetTableDataStyle(Left) );
   }

   return ptable;
}

rptRcTable* rptStyleLibrary::CreateTableNoHeading(unsigned numColumns, std::_tstring label)
{
   rptRcTable* pTable = CreateDefaultTable(numColumns,label,false);

   pTable->SetTableHeaderStyle( rptStyleLibrary::GetTableCellStyle( CB_NONE | CJ_LEFT ) );
   pTable->SetHeaderBottomBorderStyle( rptRiStyle::NOBORDER );
   pTable->SetColumnStyle(0, rptStyleLibrary::GetTableCellStyle( CB_NONE | CJ_LEFT ) );
   for ( unsigned i = 1; i < numColumns; i++ )
   {
      pTable->SetColumnStyle(i, rptStyleLibrary::GetTableCellStyle( CB_NONE | CJ_RIGHT ) );
   }
   pTable->SetOutsideBorderStyle( rptRiStyle::SINGLE_THICK );
   pTable->SetInsideBorderStyle( rptRiStyle::NOBORDER );
   (*pTable)(0,numColumns-1).SetStyleName(rptStyleLibrary::GetTableCellStyle( CB_NONE | CJ_RIGHT ));

   return pTable;
}

const std::_tstring& rptStyleLibrary::GetImagePath()
{
   return ms_ImagePath;
}
