///////////////////////////////////////////////////////////////////////
// PGSuper - Prestressed Girder SUPERstructure Design and Analysis
// Copyright © 1999-2025  Washington State Department of Transportation
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

rptRcSymbol rptCDRatio::m_RcSymbolInfinity(rptRcSymbol::infinity);
WBFL::System::NumericFormatTool rptCDRatio::m_FormatTool(WBFL::System::NumericFormatTool::Format::Fixed,0,2);

rptCDRatio::rptCDRatio():
rptRcString(_T("Undef"))
{
}

rptCDRatio::rptCDRatio(const rptCDRatio& rOther) :
rptRcString(rOther)
{
}

rptReportContent* rptCDRatio::CreateClone() const
{
   return new rptCDRatio( *this );
}

rptReportContent& rptCDRatio::SetValue(Float64 cdr,bool passed)
{
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
      std::_tstring cds = m_FormatTool.AsString(cdr);

      if (cds == std::_tstring(_T("1.00")) && !passed)
      {
         // Force out of tolerance value to report 0.99
         cds = std::_tstring(_T("0.99"));
      }
      return rptRcString::SetValue(cds.c_str());
   }
}

rptReportContent& rptCDRatio::SetValue(Float64 capacity, Float64 demand, bool passed)
{
   if (!IsEqual(capacity,0.0) && IsEqual(demand,0.0))
   {
      return m_RcSymbolInfinity;
   }
   else
   {
      return rptRcString::SetValue(AsString(capacity,demand,passed).c_str());
   }
}

std::_tstring rptCDRatio::AsString(Float64 capacity, Float64 demand, bool passed) const
{
   if (Sign(capacity) != Sign(demand))
   {
      // Cannot have negative c/d
      return std::_tstring(_T("-"));
   }
   else if(IsEqual(capacity,0.0))
   {
//      ATLASSERT(false); // c/d for c==0.0 makes no sense - return return 0.00, but this should be caught by caller
      return std::_tstring(_T("0.00")); 
   }
   else if (IsEqual(demand,0.0))
   {
      return std::_tstring(_T("inf")); 
   }
   else
   {
      Float64 cd = capacity/demand;

      if (CDR_LARGE < cd)
      {
         return std::_tstring(_T("10+"));
      }
      else
      {
         std::_tstring cds = m_FormatTool.AsString(cd);

         if (cds==std::_tstring(_T("1.00")) && !passed)
         {
            // Force out of tolerance value to report 0.99
            return std::_tstring(_T("0.99"));
         }

         // Report computed value
         return cds;
      }
   }
}
