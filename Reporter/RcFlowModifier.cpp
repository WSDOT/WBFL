///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2014, Washington State Department of Transportation, All Rights Reserved
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
#include <Reporter\RcFlowModifier.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptRcFlowModifier
****************************************************************************/



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptRcFlowModifier::rptRcFlowModifier(FlowModifier ModifierType, Uint16 NumTimes) :
rptReportContent()
{
   m_ModifierType = ModifierType;
   m_NumTimes     = NumTimes;
}

rptRcFlowModifier::rptRcFlowModifier(const rptRcFlowModifier& rOther) :
rptReportContent(rOther)
{
   MakeCopy(rOther);
}

rptRcFlowModifier::~rptRcFlowModifier()
{
}

//======================== OPERATORS  =======================================
rptRcFlowModifier& rptRcFlowModifier::operator= (const rptRcFlowModifier& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
rptReportContent* rptRcFlowModifier::CreateClone() const
{ 
   return new rptRcFlowModifier(*this); 
}

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void rptRcFlowModifier::MakeCopy(const rptRcFlowModifier& rOther)
{
   m_NumTimes     = rOther.m_NumTimes;
   m_ModifierType = rOther.m_ModifierType;
}

void rptRcFlowModifier::MakeAssignment(const rptRcFlowModifier& rOther)
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


rptLineBreak::operator rptReportContent*()
{
   return new rptRcFlowModifier(rptRcFlowModifier::NEW_LINE);
}

rptPageBreak::operator rptReportContent*()
{
   return new rptRcFlowModifier(rptRcFlowModifier::NEW_PAGE);
}

rptHardTab::operator rptReportContent*()
{
   return new rptRcFlowModifier(rptRcFlowModifier::TAB);
}
