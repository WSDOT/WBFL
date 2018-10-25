///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2010  Washington State Department of Transportation
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
#include <Reporter\RcUnsigned.h>        // class implementation

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptRcUnsigned
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptRcUnsigned::rptRcUnsigned(Uint32 MyUs) :
rptReportContent()
{
   m_TheUnsigned = MyUs;
   m_Width  = 0;
}


rptRcUnsigned::rptRcUnsigned(Uint32 MyUs, const std::_tstring& HyperTarget) :
rptReportContent()
{
   m_TheUnsigned = MyUs;
   m_Width  = 0;

   SetHyperLink(HyperTarget);
}


rptRcUnsigned::rptRcUnsigned(const rptRcUnsigned& rOther) :
rptReportContent(rOther)
{
   MakeCopy(rOther);
}

rptRcUnsigned::~rptRcUnsigned()
{
}

//======================== OPERATORS  =======================================
rptRcUnsigned& rptRcUnsigned::operator= (const rptRcUnsigned& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

rptReportContent* rptRcUnsigned::CreateClone() const 
{ 
   return new rptRcUnsigned(*this); 
}

   //
   // accept a visitor
   //
void rptRcUnsigned::Accept( rptRcVisitor& MyVisitor )
{
   MyVisitor.VisitRcUnsigned(this);
}


//
// stream to the paragraph stream
//
rptRcUnsigned* rptRcUnsigned::Sv(Uint32 MyUs)
{
   rptRcUnsigned* tmp = new rptRcUnsigned(MyUs);
   tmp->m_Width= m_Width;
   return tmp;
}
//
// set and get the integer value
//
Uint32 rptRcUnsigned::GetVal()
{
   return m_TheUnsigned;
}

void rptRcUnsigned::SetVal(Uint32 MyUs)
{
   m_TheUnsigned = MyUs;
}
//
// set/get the number of characters that the Int32 is to fit in. The purpose
// of the width option is to allow values to be printed like: 007 (i.e., the
// Int32 value is left-padded with zeros to fit into the width.
//
Int32 rptRcUnsigned::GetWidth()
{
   return m_Width;
}

void rptRcUnsigned::SetWidth(Int32 MyWidth)
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
void rptRcUnsigned::MakeCopy(const rptRcUnsigned& rOther)
{
   m_TheUnsigned = rOther.m_TheUnsigned;
   m_Width  = rOther.m_Width ;
}

void rptRcUnsigned::MakeAssignment(const rptRcUnsigned& rOther)
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

