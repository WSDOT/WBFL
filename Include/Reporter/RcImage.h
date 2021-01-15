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

#ifndef INCLUDED_REPORTER_RCIMAGE_H_
#define INCLUDED_REPORTER_RCIMAGE_H_
#pragma once

#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>
#include <string>

/// Report content for an image.
///
/// This type of report content allows a static image file to be placed into a report.
class REPORTERCLASS rptRcImage : public rptReportContent
{
public:
   /// Image alignment type
   enum Align
   {
      Baseline,
      Middle,
      Subscript,
      Superscript,
      TextTop,
      TextBottom,
      Top,
      Bottom
   };

   /// Image float type
   enum Float
   {
      Left,
      Right,
      None
   };

   /// Creates an image content with an unspecified image file
   rptRcImage();

   rptRcImage(
      const std::_tstring& fileName, ///< Path to image file
      Align align=Baseline, ///< image alignment
      Float flt=None ///< image float
   );

   rptRcImage(const rptRcImage& rOther);

   virtual ~rptRcImage();

   rptRcImage& operator=(const rptRcImage& rOther);

   /// Accepts a visitor and calls VisitRcImage(this)
   virtual void Accept( rptRcVisitor& rVisitor ) override;

   /// Creates a clone
   virtual rptReportContent* CreateClone() const override;

   /// Returns the name of the image file
   const std::_tstring& GetFileName() const;

   /// Sets the name of the image file
   void SetFileName(const std::_tstring& fileName);

   /// Returns the image description text
   const std::_tstring& GetPictureDescription() const;

   /// Sets the image description text
   void SetPictureDescription(const std::_tstring& PictureDescription);

   /// Sets the image alignment
   void SetImageAlignment(Align a);

   /// Returns the image aligment
   Align GetImageAlignment() const;

   /// Sets the image float
   void SetImageFloat(Float flt);

   /// Returns the image float
   Float GetImageFloat() const;

private:
   std::_tstring m_FileName;
   std::_tstring m_PictureDescription;
   Align m_Align;
   Float m_Float;
};

#endif // INCLUDED_REPORTER_RcImage_H_
