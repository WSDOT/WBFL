///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2020  Washington State Department of Transportation
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

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <Reporter\RcVisitor.h>
#include <string>


class REPORTERCLASS rptRcVisitor;

/// Report content for a text string.
class REPORTERCLASS rptRcString : public rptReportContent
{
public:
   /// Constructor
   rptRcString(
      LPCTSTR YourStr, ///< The text string
      bool bNoWrap = false ///< If true, word wrapping is prevented
   );

   /// Constructor
   rptRcString(
      const std::_tstring& YourString, ///< The text string
      bool bNoWrap = false ///< If true, word wrapping is prevented
   );

   /// Constructor
   rptRcString(
      LPCTSTR YourStr, ///< The text string
      const std::_tstring& HyperTarget, ///< Name of hyperlink target
      bool bNoWrap = false ///< If true, word wrapping is prevented
   );

   /// Constructor
   rptRcString(
      const std::_tstring& YourString, ///< The text string
      const std::_tstring& HyperTarget, ///< Name of hyperlink target
      bool bNoWrap = false ///< If true, word wrapping is prevented
   );

   rptRcString(const rptRcString& rRcString);

   virtual ~rptRcString();

   rptRcString& operator=(const rptRcString& rRcString);

   /// Sets word wrapping mode
   void NoWrap(bool bNoWrap /**! If true, word wrapping is prevented*/);

   /// Returns the word wrapping mode
   bool NoWrap() const;

   /// Creates a clone
   rptReportContent* CreateClone() const;

   /// Accepts a visitor and calls VisitRcString(this)
   void Accept( rptRcVisitor& MyVisitor );

   /// Sets the value of this content and returns a reference to this
   virtual rptReportContent&  SetValue(LPCTSTR str);

   /// Returns the text string
   const std::_tstring& GetString() const {return m_TheString; }

protected:
   /// Copies the content from rOther to this object
   void MakeCopy(const rptRcString& rOther);

   /// Assigns the content from oOther to this object
   void MakeAssignment(const rptRcString& rOther);

private:
   rptRcString() = delete;
   std::_tstring m_TheString;
   bool m_bNoWrap;
};

#endif // INCLUDED_REPORTER_RCSTRING_H_
