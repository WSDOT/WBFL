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

#include <Reporter\RcEquation.h>
#include <Reporter\RcVisitor.h>
#include <sstream>

rptRcEquation::rptRcEquation() :
rptReportContent(),
m_FileName( _T("Unspecified") ),
m_mathDisplay(InLine)
{
}

rptRcEquation::rptRcEquation(const std::_tstring& fileName, const std::_tstring& laTeX, rptRcEquation::Display dsp) :
rptReportContent(),
m_FileName( fileName ),
m_LaTeX(laTeX),
m_mathDisplay(dsp)
{
}

rptRcEquation::rptRcEquation(const rptRcEquation& rOther) :
rptReportContent(rOther)
{
   m_FileName = rOther.m_FileName;
   m_LaTeX = rOther.m_LaTeX;
   m_mathDisplay = rOther.m_mathDisplay;
}

rptRcEquation::~rptRcEquation()
{
}

rptRcEquation& rptRcEquation::operator= (const rptRcEquation& rOther)
{
   if( this != &rOther )
   {
      m_FileName = rOther.m_FileName;
      m_LaTeX = rOther.m_LaTeX;
      m_mathDisplay = rOther.m_mathDisplay;
   }

   return *this;
}

void rptRcEquation::Accept( rptRcVisitor& rVisitor )
{
#if defined _DEBUG
   // test to make sure the file exists
   WIN32_FIND_DATA findData;
   HANDLE handle = ::FindFirstFile(m_FileName.c_str(),&findData);
   CHECK(handle != INVALID_HANDLE_VALUE);
   if ( handle != INVALID_HANDLE_VALUE )
      ::FindClose(handle);
#endif
   rVisitor.VisitRcEquation( this );
}

rptReportContent* rptRcEquation::CreateClone() const
{
   return new rptRcEquation( *this );
}

//======================== ACCESS     =======================================

const std::_tstring& rptRcEquation::GetFileName() const
{
   return m_FileName;
}

void rptRcEquation::SetFileName(const std::_tstring& fileName)
{
   m_FileName = fileName;
}

const std::_tstring& rptRcEquation::GetLaTeX() const
{
    return m_LaTeX;
}

void rptRcEquation::SetLaTeX(const std::_tstring& LaTeX)
{
    m_LaTeX = LaTeX;
}

void rptRcEquation::SetMathDisplay(rptRcEquation::Display dsp)
{
    m_mathDisplay = dsp;
}

rptRcEquation::Display rptRcEquation::GetMathDisplay() const
{
    return m_mathDisplay;
}
