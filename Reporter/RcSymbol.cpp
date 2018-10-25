///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2014  Washington State Department of Transportation
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
#include <Reporter\RcSymbol.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptRcSymbol
****************************************************************************/



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptRcSymbol::rptRcSymbol(SymbolType Symbol) :
rptReportContent()
{
   m_SymbolType = Symbol;
}

rptRcSymbol::rptRcSymbol(const rptRcSymbol& rOther) :
rptReportContent(rOther)
{
   MakeCopy(rOther);
}

rptRcSymbol::~rptRcSymbol()
{
}

//======================== OPERATORS  =======================================
rptRcSymbol& rptRcSymbol::operator= (const rptRcSymbol& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

rptReportContent* rptRcSymbol::CreateClone() const
{ 
   return new rptRcSymbol(*this); 
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rptRcSymbol::MakeCopy(const rptRcSymbol& rOther)
{
   m_SymbolType = rOther.m_SymbolType;
}

void rptRcSymbol::MakeAssignment(const rptRcSymbol& rOther)
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


