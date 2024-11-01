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
rptReportContent()
{
}

rptRcEquation::rptRcEquation(const std::_tstring& fileName, const std::_tstring& laTeX, rptRcEquation::DisplayType dsp) :
rptReportContent(),
m_FileName( fileName ),
m_LaTeX(laTeX),
m_mathDisplay(dsp)
{
}

void rptRcEquation::Accept( rptRcVisitor& rVisitor )
{
   rVisitor.VisitRcEquation( this );
}

rptReportContent* rptRcEquation::CreateClone() const
{
   return new rptRcEquation( *this );
}

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

void rptRcEquation::SetMathDisplay(rptRcEquation::DisplayType dsp)
{
    m_mathDisplay = dsp;
}

rptRcEquation::DisplayType rptRcEquation::GetMathDisplay() const
{
    return m_mathDisplay;
}
