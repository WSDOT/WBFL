///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2011  Washington State Department of Transportation
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

/****************************************************************************
CLASS
   rptRcInt
****************************************************************************/



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptRcInt::rptRcInt(Int32 MyInt) :
rptReportContent()
{
   m_TheInt = MyInt;
   m_Width  = 0;
}


rptRcInt::rptRcInt(Int32 MyInt, const std::_tstring& HyperTarget) :
rptReportContent()
{
   m_TheInt = MyInt;
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

   //
   // accept a visitor
   //

void rptRcInt::Accept( rptRcVisitor& MyVisitor )
{
   MyVisitor.VisitRcInt(this);
}


//
// stream to the paragraph stream
//
rptRcInt* rptRcInt::Sv(Int32 MyInt)
{
   std::auto_ptr<rptRcInt> tmp( new rptRcInt(MyInt) );
   tmp->m_Width= m_Width;
   return tmp.release();
}
//
// set and get the integer value
//
Int32 rptRcInt::GetVal()
{
   return m_TheInt;
}

void rptRcInt::SetVal(Int32 MyInt)
{
   m_TheInt = MyInt;
}
//
// set/get the number of characters that the Int32 is to fit in. The purpose
// of the width option is to allow values to be printed like: 007 (i.e., the
// Int32 value is left-padded with zeros to fit into the width.
//
Int32 rptRcInt::GetWidth()
{
   return m_Width;
}

void rptRcInt::SetWidth(Int32 MyWidth)
{
   m_Width = MyWidth;
}

// GROUP: ACCESS
// GROUP: INQUIRY


//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rptRcInt::MakeCopy(const rptRcInt& rOther)
{
   m_TheInt = rOther.m_TheInt;
   m_Width  = rOther.m_Width ;
}

void rptRcInt::MakeAssignment(const rptRcInt& rOther)
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
//======================== INQUERY    =======================================

