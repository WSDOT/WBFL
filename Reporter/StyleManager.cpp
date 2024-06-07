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
#include <Reporter\StyleManager.h>

#include <WBFLSTL.h>

std::_tstring rptStyleManager::ms_ReportTitleStyle           = _T("ReportTitle");
std::_tstring rptStyleManager::ms_ReportSubtitleStyle        = _T("ReportSubtitle");
std::_tstring rptStyleManager::ms_ChapterTitleStyle          = _T("ChapterTitle");
std::_tstring rptStyleManager::ms_HeadingStyle               = _T("Heading");
std::_tstring rptStyleManager::ms_SubheadingStyle            = _T("Subheading");
std::_tstring rptStyleManager::ms_TableColumnHeadingStyle    = _T("ColumnHeading");
std::_tstring rptStyleManager::ms_FootnoteStyle              = _T("Footnote");
std::_tstring rptStyleManager::ms_CopyrightStyle             = _T("Copyright");
std::array<std::_tstring, 6> rptStyleManager::ms_TableCellStyle = {   _T("NB-LJ"),   _T("TB-LJ"),   _T("NB-RJ"),   _T("TB-RJ"),   _T("NB-CJ"),   _T("TB-CJ")};
std::array<std::_tstring, 6> rptStyleManager::ms_TableStripeRowCellStyle = {_T("SR-NB-LJ"),_T("SR-TB-LJ"),_T("SR-NB-RJ"),_T("SR-TB-RJ"),_T("SR-NB-CJ"),_T("SR-TB-CJ")};
std::_tstring rptStyleManager::ms_ReportCoverImage           = _T("");

std::unique_ptr<std::_tstring> rptStyleManager::ms_pImagePath;

Float64 rptStyleManager::ms_MaxTableWidth = 7.5; // 7.5" wide tables

void rptStyleManager::InitStyles()
{
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
   rpttitle.SetIsHeading(true);
   rpttitle.SetBold( true );
   rpttitle.SetFontType(rptRiStyle::SWISS);
   rpttitle.SetAlignment(rptRiStyle::CENTER);
   flag = psl->AddNamedStyle(ms_ReportTitleStyle, rpttitle);
   //ATLASSERT(flag);

   // Report Subtitle
   rptRiStyle rptsubtitle;
   rptsubtitle.SetFontSize(15);
   rptsubtitle.SetIsHeading(true);
   rptsubtitle.SetItalic( true );
   rptsubtitle.SetFontType(rptRiStyle::SWISS);
   rptsubtitle.SetAlignment(rptRiStyle::CENTER);
   flag = psl->AddNamedStyle(ms_ReportSubtitleStyle, rptsubtitle);
   //ATLASSERT(flag);

   // Chapter Titles
   rptRiStyle  chaptertitle;
   chaptertitle.SetFontType(rptRiStyle::SWISS);
   chaptertitle.SetFontSize(13);
   chaptertitle.SetIsHeading(true);
   chaptertitle.SetAlignment(rptRiStyle::LEFT);
   chaptertitle.SetBold( true );
   chaptertitle.SetColor( rptRiStyle::Blue );
   flag = psl->AddNamedStyle(ms_ChapterTitleStyle, chaptertitle);
   //ATLASSERT(flag);
   
   // Headings
   rptRiStyle headings;
   headings.SetFontType(rptRiStyle::SWISS);
   headings.SetFontSize(11);
   headings.SetIsHeading(true);
   headings.SetBold( true );
   flag = psl->AddNamedStyle(ms_HeadingStyle, headings);
   //ATLASSERT(flag);
   
   // SubHeadings
   rptRiStyle subheadings;
   subheadings.SetFontType(rptRiStyle::SWISS);
   subheadings.SetFontSize(9);
   subheadings.SetIsHeading(true);
   subheadings.SetItalic( true );
   subheadings.SetBold( true );
   flag = psl->AddNamedStyle(ms_SubheadingStyle, subheadings);
   //ATLASSERT(flag);

   for (Uint16 hLevel = 1; hLevel <= 6; hLevel++)
   {

       PRECONDITION(1 <= hLevel && hLevel <= 6);

       // HTML Level Headings
       rptRiStyle heading;
       heading.SetFontType(rptRiStyle::SWISS);
       heading.SetFontSize(12 - hLevel);
       heading.SetIsHeading(true);
       heading.SetBold(true);
       psl->SetHeadingStyle(hLevel, heading);
       //ATLASSERT(flag);
   }

   //rptRiStyle  chaptertitle;
   //chaptertitle.SetFontType(rptRiStyle::SWISS);
   //chaptertitle.SetFontSize(13);
   //chaptertitle.SetIsHeading(true);
   //chaptertitle.SetAlignment(rptRiStyle::LEFT);
   //chaptertitle.SetBold(true);
   //chaptertitle.SetColor(rptRiStyle::Blue);
   //psl->SetHeadingStyle(1, chaptertitle);


   // Table Column Headings
   rptRiStyle colheadings;
   colheadings.SetFontSize(9);
   colheadings.SetFontType(rptRiStyle::SWISS);
   colheadings.SetAlignment(rptRiStyle::CENTER);
   colheadings.SetVerticalAlignment( rptRiStyle::TOP );
   colheadings.SetBold( true );
   colheadings.SetBGColor( rptRiStyle::LightSteelBlue );
   flag = psl->AddNamedStyle(ms_TableColumnHeadingStyle, colheadings);
   //ATLASSERT(flag);

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

   for ( int i = 0; i < 6; i++ )
   {
      rptRiStyle stripe_row_cell = psl->GetNamedStyle(ms_TableCellStyle[i]);
      stripe_row_cell.SetBGColor( rptRiStyle::AliceBlue );
      psl->AddNamedStyle( ms_TableStripeRowCellStyle[i],stripe_row_cell);
   }

   // Footnote style
   rptRiStyle footnote;
   footnote.SetFontType( rptRiStyle::SWISS );
   footnote.SetFontSize(8);
   footnote.SetAlignment(rptRiStyle::LEFT);
   flag = psl->AddNamedStyle( ms_FootnoteStyle, footnote );

   // Copyright style
   rptRiStyle copyright;
   copyright.SetFontType( rptRiStyle::SWISS );
   copyright.SetFontSize(8);
   copyright.SetAlignment(rptRiStyle::CENTER);
   flag = psl->AddNamedStyle( ms_CopyrightStyle, copyright );
}


LPCTSTR rptStyleManager::GetReportTitleStyle()
{
   return ms_ReportTitleStyle.c_str();
}

LPCTSTR rptStyleManager::GetReportSubtitleStyle()
{
   return ms_ReportSubtitleStyle.c_str();
}

LPCTSTR rptStyleManager::GetChapterTitleStyle()
{
   return ms_ChapterTitleStyle.c_str();
}

LPCTSTR rptStyleManager::GetHeadingStyle()
{
   return ms_HeadingStyle.c_str();
}

LPCTSTR rptStyleManager::GetSubheadingStyle()
{
   return ms_SubheadingStyle.c_str();
}

LPCTSTR rptStyleManager::GetTableColumnHeadingStyle()
{
   return ms_TableColumnHeadingStyle.c_str();
}

LPCTSTR rptStyleManager::GetTableCellStyle(Uint32 style)
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

   return ms_TableCellStyle[index].c_str();
}

LPCTSTR rptStyleManager::GetTableStripeRowCellStyle(Uint32 style)
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

   return ms_TableStripeRowCellStyle[index].c_str();
}

LPCTSTR rptStyleManager::GetFootnoteStyle()
{
   return ms_FootnoteStyle.c_str();
}

LPCTSTR rptStyleManager::GetCopyrightStyle()
{
   return ms_CopyrightStyle.c_str();
}

Float64 rptStyleManager::GetMaxTableWidth()
{
   return ms_MaxTableWidth;
}

rptHeading* rptStyleManager::CreateHeading(Uint8 hLevel)
{
    PRECONDITION(1 <= hLevel && hLevel <= 6);

    rptHeading* pHeading = new rptHeading(hLevel);

    return pHeading;
}

rptHeading* rptStyleManager::CreateChapterHeading()
{
   return CreateHeading(1);
}

rptHeading* rptStyleManager::CreateHeading()
{
    return CreateHeading(1);
}

rptHeading* rptStyleManager::CreateSubHeading()
{
    return CreateHeading(2);
}

rptRcTable* rptStyleManager::CreateDefaultTable(ColumnIndexType numColumns, const std::_tstring& strLabel)
{
   return CreateDefaultTable(numColumns,strLabel.c_str());
}

rptRcTable* rptStyleManager::CreateDefaultTable(ColumnIndexType numColumns, LPCTSTR lpszLabel)
{
   rptRcTable* pTable = new rptRcTable( numColumns, 0.0/*rptStyleManager::GetMaxTableWidth()*/ );
   if (lstrlen(lpszLabel) > 0)
   {
      pTable->TableLabel() << lpszLabel;
   }

   rptStyleManager::ConfigureTable(pTable);

   return pTable;
}

rptRcTable* rptStyleManager::CreateTableNoHeading(ColumnIndexType numColumns, const std::_tstring& strLabel)
{
   return CreateTableNoHeading(numColumns,strLabel.c_str());
}

rptRcTable* rptStyleManager::CreateTableNoHeading(ColumnIndexType numColumns, LPCTSTR lpszLabel)
{
   rptRcTable* pTable = CreateDefaultTable(numColumns,lpszLabel);

   pTable->SetTableHeaderStyle( rptStyleManager::GetTableCellStyle(CB_NONE | CJ_LEFT) );
   pTable->SetNumberOfHeaderRows(0);

   for ( Uint16 i = 0; i < numColumns; i++ )
   {
      pTable->SetColumnStyle(i, rptStyleManager::GetTableCellStyle( CB_NONE | CJ_LEFT ) );
      pTable->SetStripeRowColumnStyle( i, rptStyleManager::GetTableStripeRowCellStyle(CB_NONE | CJ_LEFT) );
   }

   return pTable;
}

rptRcTable* rptStyleManager::CreateLayoutTable(ColumnIndexType nColumns,const std::_tstring& strLabel)
{
   return CreateLayoutTable(nColumns,strLabel.c_str());
}

rptRcTable* rptStyleManager::CreateLayoutTable(ColumnIndexType nColumns,LPCTSTR lpszLabel)
{
   rptRcTable* pLayoutTable = CreateTableNoHeading(nColumns,lpszLabel);
   pLayoutTable->SetInsideBorderStyle(rptRiStyle::NOBORDER);
   pLayoutTable->SetOutsideBorderStyle(rptRiStyle::NOBORDER);
   pLayoutTable->EnableRowStriping(false);
   return pLayoutTable;
}

void rptStyleManager::ConfigureTable(rptRcTable* pTable)
{
   pTable->SetStyleName( rptStyleManager::GetTableCellStyle(CB_NONE | CJ_RIGHT) );
   pTable->TableLabel().SetStyleName( rptStyleManager::GetHeadingStyle() );
   pTable->SetTableHeaderStyle( rptStyleManager::GetTableColumnHeadingStyle() );
   pTable->SetOutsideBorderStyle( rptRiStyle::HAIR_THICK );
   pTable->SetInsideBorderStyle( rptRiStyle::NOBORDER );
   pTable->SetCellPad( 0.015625 );

   pTable->EnableRowStriping(true);

   ColumnIndexType numColumns = pTable->GetNumberOfColumns();

   for ( ColumnIndexType i = 0; i < numColumns; i++ )
   {
      pTable->SetColumnStyle( i, rptStyleManager::GetTableCellStyle(CB_NONE | CJ_RIGHT) );
      pTable->SetStripeRowColumnStyle( i, rptStyleManager::GetTableStripeRowCellStyle(CB_NONE | CJ_RIGHT) );
   }
}

LPCTSTR rptStyleManager::GetImagePath()
{
   if (ms_pImagePath.get() == nullptr)
   {
      // get the full path to the EXE file (this includes the EXE name and extensinon)
      TCHAR szBuff[_MAX_PATH];
      ::GetModuleFileName(::GetModuleHandle(nullptr), szBuff, _MAX_PATH);
      std::_tstring filename(szBuff);
      make_upper(filename.begin(), filename.end());

      // in the build enviroment, we have the EXE go into a RegFreeCOM\<configuration>\<platform> folder
      // however the images are under the main application source folder as they would be in a real release
      // remove the RegFreeCOM\<configuration>\<platform>. It's ok if this fails (and it will in a real release)
      // because it doesn't do anything.
#if defined _DEBUG
#if defined _WIN64
      std::_tstring strTarget(_T("REGFREECOM\\X64\\DEBUG\\"));
#else
      std::_tstring strTarget(_T("REGFREECOM\\WIN32\\DEBUG\\"));
#endif
#else
      // in a real release, the path doesn't contain RegFreeCOM\\Release, but that's
      // ok... the replace will fail and the string wont be altered.
#if defined _WIN64
      std::_tstring strTarget(_T("REGFREECOM\\X64\\RELEASE\\"));
#else
      std::_tstring strTarget(_T("REGFREECOM\\WIN32\\RELEASE\\"));
#endif
#endif
      auto pos = filename.find(strTarget);
      if (pos != std::_tstring::npos)
      {
         filename.replace(filename.begin() + pos, filename.begin() + pos + strTarget.size(), _T(""));
      }

      /*
      // The image file is at the same level as the EXE file. Work backwards to find last occurance of "\\"
      // and then replace everything after it (which is the application name and .EXE) with \IMAGES\
      */
      auto loc = filename.find_last_of(_T("\\"));
      filename.replace(filename.begin()+loc,filename.end(),_T("\\IMAGES\\"));
      ms_pImagePath = std::make_unique<std::_tstring>(filename);
   }

   return ms_pImagePath->c_str();
}

void rptStyleManager::SetReportCoverImage(LPCTSTR strImagePath)
{
   ms_ReportCoverImage = strImagePath;
   make_upper(ms_ReportCoverImage.begin(),ms_ReportCoverImage.end());
}

LPCTSTR rptStyleManager::GetReportCoverImage()
{
   if ( ms_ReportCoverImage == _T("") )
   {
      SetReportCoverImage(std::_tstring(std::_tstring(GetImagePath()) + _T("title_page_art.gif")).c_str());
   }
   return ms_ReportCoverImage.c_str();
}
