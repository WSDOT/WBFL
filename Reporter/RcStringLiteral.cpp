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
#include <Reporter\RcStringLiteral.h>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

rptRcStringLiteral::rptRcStringLiteral(LPCTSTR  YourStr,bool bNoWrap) :
m_TheString( YourStr ),
m_bNoWrap(bNoWrap)
{
}

rptRcStringLiteral::rptRcStringLiteral(const std::_tstring& YourString,bool bNoWrap) :
m_TheString( YourString ),
m_bNoWrap(bNoWrap)
{
}

rptRcStringLiteral::rptRcStringLiteral(LPCTSTR  YourStr, const std::_tstring& HyperTarget,bool bNoWrap) :
m_TheString( YourStr ),
m_bNoWrap(bNoWrap)
{
   SetHyperLink(HyperTarget);
}

rptRcStringLiteral::rptRcStringLiteral(const std::_tstring& YourString, const std::_tstring& HyperTarget,bool bNoWrap) :
m_TheString( YourString ),
m_bNoWrap(bNoWrap)
{
   SetHyperLink(HyperTarget);
}

rptRcStringLiteral::rptRcStringLiteral(const rptRcStringLiteral& rRcString):
rptReportContent(rRcString)
{
   MakeCopy( rRcString );

}

rptRcStringLiteral::~rptRcStringLiteral()
{
}

rptRcStringLiteral& rptRcStringLiteral::operator=(const rptRcStringLiteral& rRcString)
{
   if (this != &rRcString)
      MakeAssignment(rRcString);
   return *this;
} // operator =

rptReportContent* rptRcStringLiteral::CreateClone() const 
{ 
   return new rptRcStringLiteral(*this); 
}

void rptRcStringLiteral::Accept( rptRcVisitor& MyVisitor )
{
   MyVisitor.VisitRcStringLiteral(this);
}

void rptRcStringLiteral::NoWrap(bool bNoWrap)
{
   m_bNoWrap = bNoWrap;
}

bool rptRcStringLiteral::NoWrap() const
{
   return m_bNoWrap;
}

rptReportContent&  rptRcStringLiteral::SetValue(LPCTSTR str)
{
   m_TheString = str;
   return *this;
}

void rptRcStringLiteral::MakeCopy(const rptRcStringLiteral& rRcString)
{
   m_TheString = rRcString.m_TheString;
   m_bNoWrap   = rRcString.m_bNoWrap;
}

void rptRcStringLiteral::MakeAssignment(const rptRcStringLiteral& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}
