///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2013  Washington State Department of Transportation
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

#ifndef INCLUDED_REPORTER_HTMLHELPER_H_
#define INCLUDED_REPORTER_HTMLHELPER_H_
#pragma once

#include <map>
#include <ostream>
#include <Reporter\ReporterExp.h>
#include <Reporter\FontStyleLibrary.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class rptRiStyle;
class rptPageLayout;

// MISCELLANEOUS
//

// typedefs for private stl stuff - should go in class, but templates won't allow it
//typedef std::map<rptStyleName, std::_tstring, std::less<rptStyleName>, std::allocator<std::_tstring> > StyleElementMap;
//typedef StyleElementMap::iterator StyleElementMapIterator;
//typedef StyleElementMap::const_iterator ConstStyleElementMapIterator;

/*****************************************************************************
CLASS 
   rptHtmlHelper

   This class contains helper functions to aid the htmlVisitor classses in
   getting their job done.


DESCRIPTION
   A bucket for html code generation utilities.


   EXAMPLE
      Place examples here.
   END

BUGS
   There are currently no known problems with this class.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 05.08.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptHtmlHelper
{
public:
   // enum for paragraph anchor starting value. for toc generation
   // 100 chapters - should be a realistic limitation
   enum {ParaStart=100};

   // GROUP: LIFECYCLE
   //------------------------------------------------------------------------
   // Default constructor 
   rptHtmlHelper();

   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Get stylistic information to put into HTML style block.
   static std::_tstring GetStyleString(const rptRiStyle& MyStyle);

   //------------------------------------------------------------------------
   // Get page layout information to put into HTML style block.
   static std::_tstring GetPageLayoutString(const rptPageLayout& MyLayout);

   //------------------------------------------------------------------------
   // Visit font library. Write library style information to the ostream, and set
   // up style name - htlm element name mapping.
   void VisitFontLibrary(std::_tostream& os);

   //------------------------------------------------------------------------
   // Get html element name for a given style name (e.g., H1,H2...)
   // string is returned empty if no name exists
   std::_tstring GetElementName(const rptStyleName& rstyleName) const;
   

   // GROUP: ACCESS
   // GROUP: INQUIRY

protected:
   // GROUP: DATA MEMBERS

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS

   bool m_DidVisit;

   typedef std::map<rptStyleName, std::_tstring, std::less<rptStyleName>, std::allocator<std::_tstring> > StyleElementMap;
   StyleElementMap m_StyleElementMap;

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

#endif // INCLUDED_REPORTER_HTMLHELPER_H_
