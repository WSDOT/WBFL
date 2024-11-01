///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <string>

/// Report content for an equation.
///
/// This type of report content allows a static image file or LaTeX to be placed into a report.
/// Use only the LaTex coding for the equation. The equation delimiters are automatically inserted
/// into the text string based on the DisplayType
class REPORTERCLASS rptRcEquation : public rptReportContent
{
public:

   /// Math display type
   enum class DisplayType
   {
       InLine,
       Block,
   };

   /// Creates equation content with an unspecified image file and LaTex code
   rptRcEquation();

   rptRcEquation(
      const std::_tstring& fileName, ///< Path to image file
      const std::_tstring& laTeX, ///< LaTex code
      DisplayType dsp=DisplayType::InLine ///< math display type
   );

   rptRcEquation(const rptRcEquation& rOther) = default;

   virtual ~rptRcEquation() = default;

   rptRcEquation& operator=(const rptRcEquation& rOther) = default;

   /// Accepts a visitor and calls VisitRcEquation(this)
   virtual void Accept( rptRcVisitor& rVisitor ) override;

   /// Creates a clone
   virtual rptReportContent* CreateClone() const override;

   /// Returns the name of the image file
   const std::_tstring& GetFileName() const;

   /// Returns the code for LaTex
   const std::_tstring& GetLaTeX() const;

   /// Sets the name of the image file
   void SetFileName(const std::_tstring& fileName);

   /// Sets the code LaTeX
   void SetLaTeX(const std::_tstring& laTex);

   /// Sets the math display
   void SetMathDisplay(DisplayType dsp);

   /// Returns the math display
   DisplayType GetMathDisplay() const;

private:
   std::_tstring m_FileName = _T("Unspecified");
   std::_tstring m_LaTeX;
   DisplayType m_mathDisplay = DisplayType::InLine;
};
