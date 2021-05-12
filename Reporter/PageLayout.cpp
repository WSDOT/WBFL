///////////////////////////////////////////////////////////////////////
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

#include <Reporter\ReporterLib.h>
#include <Reporter\PageLayout.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptPageLayout
****************************************************************************/



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptPageLayout::rptPageLayout()
{
   // set up page to some reasonable defaults for margins and leave header
   // and footer blank.
  
    m_PageHeight    = 11.0;
    m_PageWidth     = 8.5;
    m_TopMargin     = 1.0;
    m_BottomMargin  = 1.0;
    m_LeftMargin    = 0.75;
    m_RightMargin   = 0.75;

    m_PageOrientation = poDefault;

    // Set the styles of the header and footer paragraphs to default
    m_FooterParagraph.SetStyleName(_T("Default"));
    m_HeaderParagraph.SetStyleName(_T("Default"));
}


rptPageLayout::rptPageLayout(const rptPageLayout& rOther)
{
   MakeCopy(rOther);
}

rptPageLayout::~rptPageLayout()
{
}

//======================== OPERATORS  =======================================
rptPageLayout& rptPageLayout::operator=(const rptPageLayout& rOther)
{
   if( this != &rOther )
      MakeCopy(rOther);

   return *this;
}

//======================== OPERATIONS =======================================
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
void rptPageLayout::MakeCopy(const rptPageLayout& rOther)
{
   m_PageHeight    = rOther.m_PageHeight;
   m_PageWidth     = rOther.m_PageWidth;
   m_TopMargin     = rOther.m_TopMargin;
   m_BottomMargin  = rOther.m_BottomMargin;
   m_LeftMargin    = rOther.m_LeftMargin;
   m_RightMargin   = rOther.m_RightMargin;

   m_FooterParagraph = rOther.m_FooterParagraph;
   m_HeaderParagraph = rOther.m_HeaderParagraph;

   m_PageOrientation = rOther.m_PageOrientation;
}

//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

