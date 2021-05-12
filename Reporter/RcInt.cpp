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
#include <Reporter\RcInt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

rptRcInt::rptRcInt(Int64 MyInt, Int32 MyWidth) :
rptReportContent()
{
   m_Value = MyInt;
   m_Width  = MyWidth;
}

rptRcInt::rptRcInt(Int64 MyInt, const std::_tstring& HyperTarget) :
rptReportContent()
{
   m_Value = MyInt;
   m_Width  = 0;

   SetHyperLink(HyperTarget);
}


rptRcInt::rptRcInt(const rptRcInt& rOther) :
rptReportContent(rOther)
{
   MakeCopy(rOther);
}

rptRcInt::~rptRcInt()
{
}

//======================== OPERATORS  =======================================
rptRcInt& rptRcInt::operator= (const rptRcInt& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

rptReportContent* rptRcInt::CreateClone() const 
{ 
   return new rptRcInt(*this); 
}

void rptRcInt::Accept( rptRcVisitor& MyVisitor )
{
   MyVisitor.VisitRcInt(this);
}

rptRcInt* rptRcInt::Sv(Int64 MyInt)
{
   std::unique_ptr<rptRcInt> tmp( std::make_unique<rptRcInt>(MyInt,m_Width) );
   return tmp.release();
}

Int64 rptRcInt::GetValue() const
{
   return m_Value;
}

void rptRcInt::SetValue(Int64 MyInt)
{
   m_Value = MyInt;
}

Int32 rptRcInt::GetWidth()
{
   return m_Width;
}

void rptRcInt::SetWidth(Int32 MyWidth)
{
   m_Width = MyWidth;
}

void rptRcInt::MakeCopy(const rptRcInt& rOther)
{
   m_Value = rOther.m_Value;
   m_Width  = rOther.m_Width ;
}

void rptRcInt::MakeAssignment(const rptRcInt& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}
