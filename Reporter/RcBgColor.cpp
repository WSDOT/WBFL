///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <Reporter\RcBgColor.h>

rptRcBgColor::rptRcBgColor(rptRiStyle::FontColor MyColor) :
rptReportContent()
{
   m_Color = MyColor;
}


rptRcBgColor::rptRcBgColor(const rptRcBgColor& rOther) :
rptReportContent(rOther)
{
   MakeCopy(rOther);
}


rptRcBgColor::~rptRcBgColor()
{
}

rptRcBgColor& rptRcBgColor::operator= (const rptRcBgColor& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

rptRiStyle::FontColor rptRcBgColor::GetColor() const
{
   return m_Color;
}


void rptRcBgColor::SetColor(rptRiStyle::FontColor MyColor)
{
   m_Color = MyColor;
}

void rptRcBgColor::MakeCopy(const rptRcBgColor& rOther)
{
   m_Color = rOther.m_Color;
}

void rptRcBgColor::MakeAssignment(const rptRcBgColor& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}

rptReportContent* rptRcBgColor::CreateClone() const
{ 
   return new rptRcBgColor(*this); 
}

void rptRcBgColor::Accept( rptRcVisitor& MyVisitor )
{
   MyVisitor.VisitRcBgColor(this);
}
