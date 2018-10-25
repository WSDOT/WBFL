///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2017  Washington State Department of Transportation
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

#include <string>
#include <Reporter\ReporterExp.h>
#include <Reporter\ReportContent.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   rptRcImage

   Report content for an image (.gif's and .jpeg's). This type of report content
   allows a static image file to be placed into a report. In the htlm world, this
   is would be implemented as a <img src="FileName", alt="PictureDescription>.
   It is likely that an rtf file writer would have to implement the image in the 
   form of an ole embedded object.

DESCRIPTION
   Report content for an image.

LOG
   rab : 11.12.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptRcImage : public rptReportContent
{
public:
   // GROUP: LIFECYCLE
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

   enum Float
   {
      Left,
      Right,
      None
   };

   //------------------------------------------------------------------------
   // Default constructor
   // File name is "Unspecified"
   rptRcImage();

   //------------------------------------------------------------------------
   // Constructor
   rptRcImage(const std::_tstring& fileName,Align align=Baseline,Float flt=None);

   //------------------------------------------------------------------------
   // Copy constructor
   rptRcImage(const rptRcImage& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptRcImage();

   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   rptRcImage& operator = (const rptRcImage& rOther);

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Accept a visitor
   virtual void Accept( rptRcVisitor& rVisitor );

   //------------------------------------------------------------------------
   // Make a virtual copy
   virtual rptReportContent* CreateClone() const;

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   std::_tstring GetFileName() const;

   //------------------------------------------------------------------------
   void SetFileName(const std::_tstring& fileName);

   //------------------------------------------------------------------------
   std::_tstring GetPictureDescription() const;

   //------------------------------------------------------------------------
   void SetPictureDescription(const std::_tstring& PictureDescription);

   void SetImageAlignment(Align a);
   Align GetImageAlignment() const;

   void SetImageFloat(Float flt);
   Float GetImageFloat() const;

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   virtual bool AssertValid() const;

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   virtual void Dump(dbgDumpContext& os) const;
#endif // _DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::_tstring m_FileName;
   std::_tstring m_PictureDescription;
   Align m_Align;
   Float m_Float;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_RcImage_H_
