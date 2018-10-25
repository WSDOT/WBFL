

/****************************************************************************
CLASS
   rptStyleLibrary
****************************************************************************/
#include <Reporter\ReporterLib.h>
#include <Reporter\StyleLibrary.h>
#include <Reporter\FontStyleLibrary.h>
#include <Reporter\RcTable.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


std::string rptStyleLibrary::ms_ReportTitleStyle           = "ReportTitleStyle";
std::string rptStyleLibrary::ms_ReportSubtitleStyle        = "ReportSubtitleStyle";
std::string rptStyleLibrary::ms_ChapterTitleStyle          = "ChapterTitleStyle";
std::string rptStyleLibrary::ms_HeadingStyle               = "HeadingStyle";
std::string rptStyleLibrary::ms_SubheadingStyle            = "SubheadingStyle";
std::string rptStyleLibrary::ms_TableColumnHeadingStyle    = "TableColumnHeadingStyle";
std::string rptStyleLibrary::ms_TableDataStyleLeftJustify  = "TableDataStyle-LJ";
std::string rptStyleLibrary::ms_TableDataStyleRightJustify = "TableDataStyle-RJ";
std::string rptStyleLibrary::ms_FootnoteStyle              = "Footnote";
std::string rptStyleLibrary::ms_TableCellStyle[4]          = {"NB-LJ","TB-LJ","NB-RJ","TB-RJ"};

std::string rptStyleLibrary::ms_ImagePath= "";

Float64 rptStyleLibrary::ms_MaxTableWidth = 7.5; // 7.5" wide tables



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================


void rptStyleLibrary::InitStyles(const std::string& imagePath)
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

   // Footnote style
   rptRiStyle footnote;
   footnote.SetFontType( rptRiStyle::SWISS );
   footnote.SetFontSize(8);
   footnote.SetAlignment(rptRiStyle::LEFT);
   flag = psl->AddNamedStyle( ms_FootnoteStyle, footnote );
}


const std::string& rptStyleLibrary::GetReportTitleStyle()
{
return ms_ReportTitleStyle;
}

const std::string& rptStyleLibrary::GetReportSubtitleStyle()
{
return ms_ReportSubtitleStyle;
}

const std::string& rptStyleLibrary::GetChapterTitleStyle()
{
return ms_ChapterTitleStyle;
}

const std::string& rptStyleLibrary::GetHeadingStyle()
{
return ms_HeadingStyle;
}

const std::string& rptStyleLibrary::GetSubheadingStyle()
{
return ms_SubheadingStyle;
}

const std::string& rptStyleLibrary::GetTableColumnHeadingStyle()
{
return ms_TableColumnHeadingStyle;
}

const std::string& rptStyleLibrary::GetTableDataStyle(Justification justify)
{
   return (justify == Left) ? ms_TableDataStyleLeftJustify : ms_TableDataStyleRightJustify;
}

const std::string& rptStyleLibrary::GetTableCellStyle(Uint32 style)
{
   // Bit 1 = Border Style
   // Bit 2 = Justification
   //
   // 0 = No Border, Left Justified
   // 1 = Thin Border, Left Justified
   // 2 = No Border, Right Justified
   // 3 = Thin Border, Right Justified

   Int16 index = 0;

   if ( style & CB_NONE )
      index |= 0x0000;
   else if ( style & CB_THIN )
      index |= 0x0001;
   
   if ( style & CJ_LEFT )
      index |= 0x0000;
   else if ( style & CJ_RIGHT )
      index |= 0x0002;

   CHECK( 0 <= index && index <= 3 );

   return ms_TableCellStyle[index];
}

const std::string& rptStyleLibrary::GetFootnoteStyle()
{
   return ms_FootnoteStyle;
}

Float64 rptStyleLibrary::GetMaxTableWidth()
{
   return ms_MaxTableWidth;
}

rptRcTable* rptStyleLibrary::CreateDefaultTable(unsigned numColumns, std::string label,bool bLoadingColumn)
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

rptRcTable* rptStyleLibrary::CreateTableNoHeading(unsigned numColumns, std::string label)
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

void make_upper( std::string::iterator begin,std::string::iterator end)
{
   while ( begin != end )
   {
      *begin = toupper(*begin);
      begin++;
   }
}

const std::string& rptStyleLibrary::GetImagePath()
{
   return ms_ImagePath;
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

