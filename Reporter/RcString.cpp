///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2015  Washington State Department of Transportation
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
#include <Reporter\RcString.h>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptRcString           
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

// constructors
// non-hyperlink versions
rptRcString::rptRcString(LPCTSTR  YourStr,bool bNoWrap) :
m_TheString( YourStr ),
m_bNoWrap(bNoWrap)
{
}

rptRcString::rptRcString(const std::_tstring& YourString,bool bNoWrap) :
m_TheString( YourString ),
m_bNoWrap(bNoWrap)
{
}

// hyperlink versions
rptRcString::rptRcString(LPCTSTR  YourStr, const std::_tstring& HyperTarget,bool bNoWrap) :
m_TheString( YourStr ),
m_bNoWrap(bNoWrap)
{
   SetHyperLink(HyperTarget);
}

rptRcString::rptRcString(const std::_tstring& YourString, const std::_tstring& HyperTarget,bool bNoWrap) :
m_TheString( YourString ),
m_bNoWrap(bNoWrap)
{
   SetHyperLink(HyperTarget);
}


// copy constructor
rptRcString::rptRcString(const rptRcString& rRcString):
rptReportContent(rRcString)
{
   MakeCopy( rRcString );

} // rptRcString


// destructor
rptRcString::~rptRcString()
{
} // ~rptRcString

//======================== OPERATORS  =======================================

rptRcString& rptRcString::operator = (const rptRcString& rRcString)
{
   if (this != &rRcString)
      MakeAssignment(rRcString);
   return *this;
} // operator =


//======================== OPERATIONS =======================================
rptReportContent* rptRcString::CreateClone() const 
{ 
   return new rptRcString(*this); 
}

void rptRcString::Accept( rptRcVisitor& MyVisitor )
{
   MyVisitor.VisitRcString(this);
}

void rptRcString::NoWrap(bool bNoWrap)
{
   m_bNoWrap = bNoWrap;
}

bool rptRcString::NoWrap() const
{
   return m_bNoWrap;
}

rptReportContent&  rptRcString::SetValue(LPCTSTR str)
{
   m_TheString = str;
   return *this;
}


//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void rptRcString::MakeCopy(const rptRcString& rRcString)
{
   m_TheString = rRcString.m_TheString;
   m_bNoWrap   = rRcString.m_bNoWrap;
}


void rptRcString::MakeAssignment(const rptRcString& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY ==========================================

