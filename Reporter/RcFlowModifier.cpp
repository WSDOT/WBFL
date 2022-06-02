///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

rptRcFlowModifier::rptRcFlowModifier(FlowModifier ModifierType, Uint16 nRepeat) :
rptReportContent()
{
   m_ModifierType = ModifierType;
   m_nRepeat      = nRepeat;
}

rptRcFlowModifier::rptRcFlowModifier(const rptRcFlowModifier& rOther) :
rptReportContent(rOther)
{
   MakeCopy(rOther);
}

rptRcFlowModifier::~rptRcFlowModifier()
{
}

rptRcFlowModifier& rptRcFlowModifier::operator= (const rptRcFlowModifier& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

rptReportContent* rptRcFlowModifier::CreateClone() const
{ 
   return new rptRcFlowModifier(*this); 
}

void rptRcFlowModifier::MakeCopy(const rptRcFlowModifier& rOther)
{
   m_nRepeat = rOther.m_nRepeat;
   m_ModifierType = rOther.m_ModifierType;
}

void rptRcFlowModifier::MakeAssignment(const rptRcFlowModifier& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}


rptLineBreakFactory::operator rptReportContent*()
{
   return new rptRcFlowModifier(rptRcFlowModifier::NEW_LINE);
}

rptPageBreakFactory::operator rptReportContent*()
{
   return new rptRcFlowModifier(rptRcFlowModifier::NEW_PAGE);
}

rptHardTabFactory::operator rptReportContent*()
{
   return new rptRcFlowModifier(rptRcFlowModifier::TAB);
}
