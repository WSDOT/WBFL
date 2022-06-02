///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2022  Washington State Department of Transportation
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

/// Report style name
typedef std::_tstring rptStyleName;


/// A library of font styles for an application
///
/// This class is a singleton class that contains all font information for styles used in Reporter reports.
/// This library has a built-in default style that uses the reserved name "Default". 
/// This style is meant to be used as the "body text" style for your documents and should be used that way.

class REPORTERCLASS rptFontStyleLibrary
{
public:
   /// Get an instance of the library object
   static rptFontStyleLibrary* Instance();

   /// Add a new style to the library. Returns true if successful.
   /// Will not overwrite an existing style of the same name if one exists.
   /// Do not add a style named "Default" here - change default style by
   /// calling GetDefaultStyle and changing it directly.
   bool AddNamedStyle(
      const rptStyleName& rmyName,  ///< name of style
      const rptRiStyle& rmyStyle ///< style definition
   );

   /// Fills a vector with the names of all styles in the library
   /// The first name in this list will always be "Default".
   void GetStyleNames( std::vector<rptStyleName, std::allocator<rptStyleName> >& myNames ) const;

   /// Returns a named style definition.
   const rptRiStyle& GetNamedStyle(const rptStyleName& rmyStyleName) const;

   /// Returns a named style definition.
   rptRiStyle& GetNamedStyle(const rptStyleName& myStyle);

   /// Returns the default style definition
   const rptRiStyle& GetDefaultStyle() const;

   /// Returns the default style definition
   rptRiStyle& GetDefaultStyle();

private:
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

   rptFontStyleLibrary();
   virtual ~rptFontStyleLibrary();

   rptFontStyleLibrary(const rptFontStyleLibrary&) = delete;
   rptFontStyleLibrary& operator=(const rptFontStyleLibrary&) = delete;

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
