///////////////////////////////////////////////////////////////////////
// PGSuper - Prestressed Girder SUPERstructure Design and Analysis
// Copyright © 1999-2016  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Open Source License as 
// published by the Washington State Department of Transportation, 
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but 
// distribution is AS IS, WITHOUT ANY WARRANTY; without even the implied 
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See 
// the Alternate Route Open Source License for more details.
//
// You should have received a copy of the Alternate Route Open Source 
// License along with this program; if not, write to the Washington 
// State Department of Transportation, Bridge and Structures Office, 
// P.O. Box  47340, Olympia, WA 98503, USA or e-mail 
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <Reporter\ReporterLib.h>
#include <Reporter\CDRatio.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/****************************************************************************
CLASS
   rptCDRatio
****************************************************************************/


////////////////////////// PUBLIC     ///////////////////////////////////////
rptCDRatio::rptCDRatio():
rptRcString(_T("Undef")),
m_RcSymbolInfinity(rptRcSymbol::INFINITY),
m_Capacity(0.0), m_Demand(0.0), m_Passed(false)
{
   Init();
}

rptCDRatio::rptCDRatio(Float64 capacity, Float64 demand, bool passed):
rptRcString(_T("Undef")),
m_RcSymbolInfinity(rptRcSymbol::INFINITY),
m_Capacity(capacity), m_Demand(demand), m_Passed(passed)
{
   Init();

   rptRcString::SetValue(this->AsString().c_str());
}

void rptCDRatio::Init()
{
   m_FormatTool.SetFormat(sysNumericFormatTool::Fixed);
   m_FormatTool.SetPrecision(2);
}


rptCDRatio::rptCDRatio(const rptCDRatio& rOther) :
m_RcSymbolInfinity(rptRcSymbol::INFINITY),
rptRcString(rOther)
{
   MakeCopy( rOther );
}

rptCDRatio& rptCDRatio::operator = (const rptCDRatio& rOther)
{
   if ( this != &rOther )
   {
      MakeAssignment( rOther );
   }

   return *this;
}

rptReportContent* rptCDRatio::CreateClone() const
{
   return new rptCDRatio( *this );
}

rptReportContent& rptCDRatio::SetValue(Float64 cdr)
{
   m_CDR = cdr;
   if ( cdr == CDR_INF )
   {
      return m_RcSymbolInfinity;
   }
   else if ( cdr == CDR_NA )
   {
      return rptRcString::SetValue(_T("N/A"));
   }
   else if ( cdr == CDR_SKIP )
   {
      return rptRcString::SetValue(_T("-"));
   }
   else if ( CDR_LARGE <= cdr )
   {
      return rptRcString::SetValue(_T("10+"));
   }
   else
   {
      return rptRcString::SetValue(m_FormatTool.AsString(cdr).c_str());
   }
}

rptReportContent& rptCDRatio::SetValue(Float64 capacity, Float64 demand, bool passed)
{
   m_Capacity = capacity;
   m_Demand = demand;
   m_Passed = passed;

   if (!IsEqual(m_Capacity,0.0) && IsEqual(m_Demand,0.0))
   {
      return m_RcSymbolInfinity;
   }
   else
   {
      return rptRcString::SetValue(AsString().c_str());
   }
}

std::_tstring rptCDRatio::AsString() const
{
   if (Sign(m_Capacity) != Sign(m_Demand))
   {
      // Cannot have negative c/d
      return std::_tstring(_T("-"));
   }
   else if(IsEqual(m_Capacity,0.0))
   {
//      ATLASSERT(false); // c/d for c==0.0 makes no sense - return return 0.00, but this should be caught by caller
      return std::_tstring(_T("0.00")); 
   }
   else if (IsEqual(m_Demand,0.0))
   {
      return std::_tstring(_T("inf")); 
   }
   else
   {
      Float64 cd = m_Capacity/m_Demand;

      if (CDR_LARGE < cd)
      {
         return std::_tstring(_T("10+"));
      }
      else
      {
         std::_tstring cds = m_FormatTool.AsString(cd);

         if (cds==std::_tstring(_T("1.00")) && !m_Passed)
         {
            // Force out of tolerance value to report 0.99
            return std::_tstring(_T("0.99"));
         }

         // Report computed value
         return cds;
      }
   }
}

void rptCDRatio::MakeCopy(const rptCDRatio& rOther)
{
   m_Capacity = rOther.m_Capacity;
   m_Demand = rOther.m_Demand;
   m_Passed = rOther.m_Passed;
}

void rptCDRatio::MakeAssignment(const rptCDRatio& rOther)
{
   MakeCopy( rOther );
}