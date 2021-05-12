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

#ifndef INCLUDED_REPORTER_RCSTRING_H_
#define INCLUDED_REPORTER_RCSTRING_H_
#pragma once

// SYSTEM INCLUDES
//
#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class REPORTERCLASS rptRcVisitor;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRcString

   Summary text here
   
DESCRIPTION
   Detailed description here or delete this block
*****************************************************************************/

class REPORTERCLASS rptRcString : public rptReportContent
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // constructors
   // non-hyperlink versions
   rptRcString(LPCTSTR  YourStr,bool bNoWrap = false);
   rptRcString(const std::_tstring& YourString,bool bNoWrap = false);
   //------------------------------------------------------------------------
   // hyperlink versions - link to HyperTarget somewhere on page
   rptRcString(LPCTSTR  YourStr, const std::_tstring& HyperTarget,bool bNoWrap = false);
   rptRcString(const std::_tstring& YourString, const std::_tstring& HyperTarget,bool bNoWrap = false);

   void NoWrap(bool bNoWrap);
   bool NoWrap() const;

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcString();

   // GROUP: OPERATORS


   // GROUP: OPERATIONS

   rptReportContent* CreateClone() const;

   void Accept( rptRcVisitor& MyVisitor );

   //------------------------------------------------------------------------
   virtual rptReportContent&  SetValue(LPCTSTR str);

   // GROUP: ACCESS
   //
   // get the string
   //
   std::_tstring GetString() const {return m_TheString; }
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

   rptRcString(const rptRcString& rRcString);
   rptRcString& operator = (const rptRcString& rRcString);

private:
   // GROUP: DATA MEMBERS
   std::_tstring m_TheString;
   bool m_bNoWrap;

   // GROUP: LIFECYCLE

   // hide the constructor
   rptRcString();

   // GROUP: OPERATORS

   // GROUP: OPERATIONS
   void MakeCopy(const rptRcString& rRcString);
   void MakeAssignment(const rptRcString& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif
