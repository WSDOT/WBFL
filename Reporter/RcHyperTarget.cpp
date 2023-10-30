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
#include <Reporter\RcHyperTarget.h>

rptRcHyperTarget::rptRcHyperTarget(const std::_tstring& YourTarget) :
   rptReportContent()
{
}

rptRcHyperTarget::rptRcHyperTarget(const rptRcHyperTarget& rRcHyperTarget):
rptReportContent(rRcHyperTarget)
{
   if (this != &rRcHyperTarget)
      MakeCopy(rRcHyperTarget);

}


rptRcHyperTarget::~rptRcHyperTarget()
{
}

rptRcHyperTarget& rptRcHyperTarget::operator=(const rptRcHyperTarget& rRcHyperTarget)
{
   if (this != &rRcHyperTarget)
      MakeAssignment(rRcHyperTarget);
   return *this;
}


rptReportContent* rptRcHyperTarget::CreateClone() const 
{ 
   return new rptRcHyperTarget(*this); 
}

void rptRcHyperTarget::Accept( rptRcVisitor& MyVisitor )
{
   MyVisitor.VisitRcHyperTarget(this);
}

void rptRcHyperTarget::MakeCopy(const rptRcHyperTarget& rRcHyperTarget)
{
   m_TheTarget = rRcHyperTarget.m_TheTarget;
}

void rptRcHyperTarget::MakeAssignment(const rptRcHyperTarget& rOther)
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
//======================== INQUERY ==========================================

