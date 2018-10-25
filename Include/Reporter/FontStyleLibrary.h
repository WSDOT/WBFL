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

#ifndef INCLUDED_REPORTER_FONTSTYLELIBRARY_H_
#define INCLUDED_REPORTER_FONTSTYLELIBRARY_H_
#pragma once

#include <map>
#include <vector>
#include <Reporter\ReporterExp.h>
#include <Reporter\RiStyle.h>
#include <System\SingletonKiller.h>

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//
// public typedef for style names
typedef std::_tstring rptStyleName;

// typedefs for private stl stuff - should go in class, but templates won't allow it
//typedef std::map<rptStyleName, rptRiStyle, std::less<rptStyleName>, std::allocator<rptRiStyle> > StyleMap;
//typedef StyleMap::iterator StyleMapIterator;
//typedef StyleMap::const_iterator ConstStyleMapIterator;


/*****************************************************************************
CLASS 
   rptFontStyleLibrary

   A library for font styles for an application


DESCRIPTION
   This class is a singleton class that contains all font information for
   styles used in Reporter reports.

   NOTE: This library has a built-in default style that uses the reserved
         name "Default". This style is meant to be used as the "body text"
         style for your documents and should be used that way.

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rdp : 10.01.1997 : Created file
*****************************************************************************/

class REPORTERCLASS rptFontStyleLibrary
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Singleton implementation - this is the only way to get an instance of this baby
   static rptFontStyleLibrary* Instance();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   // Add a new style to the library - returns true if successful
   // Will not overwrite an existing style of the same name if one exists.
   // Do not add a style named "Default" here - change default style by
   // calling GetDefaultStyle and changing it directly.
   bool AddNamedStyle(const rptStyleName& rmyName, const rptRiStyle& rmyStyle);

   //------------------------------------------------------------------------
   // Return a vector of the names of all styles in the library
   // The first name in this list will always be "Default".
   void GetStyleNames( std::vector<rptStyleName, std::allocator<rptStyleName> >& myNames ) const;

   //------------------------------------------------------------------------
   // Get a const reference to a named style
   // The default style may be gotten with the name "Default".
   const rptRiStyle& GetNamedStyle(const rptStyleName& rmyStyleName) const;

   //------------------------------------------------------------------------
   // Get a changable reference to a named style
   // The default style may be gotten with the name "Default".
   rptRiStyle& GetNamedStyle(const rptStyleName& myStyle);

   //------------------------------------------------------------------------
   // Get a const reference to the default style
   const rptRiStyle& GetDefaultStyle() const;

   //------------------------------------------------------------------------
   // Get a reference to the default style
   rptRiStyle& GetDefaultStyle();

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

   // singleton instance
   static rptFontStyleLibrary* ms_pInstance;

   typedef sysSingletonKillerT<rptFontStyleLibrary> Killer;
   friend Killer;
   static Killer ms_Killer;

   // map of custom styles
   typedef std::map<rptStyleName, rptRiStyle, std::less<rptStyleName>, std::allocator<rptRiStyle> > StyleMap;
   StyleMap m_StyleMap;

   // a default style
   rptRiStyle m_DefaultStyle;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   rptFontStyleLibrary();
   //------------------------------------------------------------------------
   // Destructor
   virtual ~rptFontStyleLibrary();

   // Prevent accidental copying and assignment
   rptFontStyleLibrary(const rptFontStyleLibrary&);
   rptFontStyleLibrary& operator=(const rptFontStyleLibrary&);

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_REPORTER_FONTSTYLELIBRARY_H_
