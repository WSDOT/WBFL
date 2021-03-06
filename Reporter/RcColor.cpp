///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright � 1999-2021  Washington State Department of Transportation
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
#include <Reporter\RcColor.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
CLASS
   rptRcColor
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptRcColor::rptRcColor(rptRiStyle::FontColor MyColor) :
rptReportContent()
{
   m_Color = MyColor;
}


rptRcColor::rptRcColor(const rptRcColor& rOther) :
rptReportContent(rOther)
{
   MakeCopy(rOther);
}


rptRcColor::~rptRcColor()
{
}

//======================== OPERATORS  =======================================
rptRcColor& rptRcColor::operator= (const rptRcColor& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
rptRiStyle::FontColor rptRcColor::GetFontColor()
{
   return m_Color;
}


void rptRcColor::SetFontColor(rptRiStyle::FontColor MyColor)
{
   m_Color = MyColor;
}
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rptRcColor::MakeCopy(const rptRcColor& rOther)
{
   m_Color = rOther.m_Color;
}

void rptRcColor::MakeAssignment(const rptRcColor& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}

rptReportContent* rptRcColor::CreateClone() const
{ 
   return new rptRcColor(*this); 
}


//
// accept a visitor
//
void rptRcColor::Accept( rptRcVisitor& MyVisitor )
{
   MyVisitor.VisitRcColor(this);
}



//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

