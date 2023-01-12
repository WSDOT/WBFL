///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <Reporter\ReporterLib.h>
#include <Reporter\FontStyleLibrary.h>        // class implementation

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptFontStyleLibrary
****************************************************************************/


//typedef std::pair<StyleMap::iterator, bool> StylePair;
#define StylePair std::pair<StyleMap::iterator,bool>

////////////////////////// PUBLIC     ///////////////////////////////////////

rptFontStyleLibrary* rptFontStyleLibrary::ms_pInstance = 0;
rptFontStyleLibrary::Killer rptFontStyleLibrary::ms_Killer;


//======================== LIFECYCLE  =======================================

rptFontStyleLibrary* rptFontStyleLibrary::Instance()
{
   if ( ms_pInstance == 0 )
   {
      ms_pInstance=new rptFontStyleLibrary();
	  ms_Killer.SetSingleton( ms_pInstance );
   }
   return ms_pInstance;
}


rptFontStyleLibrary::rptFontStyleLibrary()
{
}

rptFontStyleLibrary::~rptFontStyleLibrary()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

bool rptFontStyleLibrary::AddNamedStyle(const rptStyleName& styleName, const rptRiStyle& rmyStyle)
{
   CHECKX(styleName != _T("Default"),_T("Default is always in library"));

   StylePair my_pair;
   my_pair = m_StyleMap.insert( std::make_pair(styleName, rmyStyle) );
   return my_pair.second;
}

void rptFontStyleLibrary::GetStyleNames(std::vector<rptStyleName, std::allocator<rptStyleName> >& myNames) const
{
   // clear out any existing stuff
   myNames.clear();

   // add "Default" to top of list
   myNames.push_back(_T("Default"));

   // get all names in map
   for (StyleMap::const_iterator i=m_StyleMap.begin(); i!=m_StyleMap.end(); i++)
   {
      myNames.push_back( (*i).first );
   }
}


const rptRiStyle& rptFontStyleLibrary::GetNamedStyle(const rptStyleName& rmyStyleName) const
{
   // check for default style first
   if (rmyStyleName == _T("Default") )
      return m_DefaultStyle;

   // search through custom style list
   StyleMap::const_iterator my_i = m_StyleMap.find(rmyStyleName);
   if (my_i != m_StyleMap.end() )
      return (*my_i).second;
   else
   {
      // should not have a case where looking for a named style that doesn't exist
      CHECKX(0,_T("Could not find named style in library"));
      return m_DefaultStyle;
   }
}

rptRiStyle& rptFontStyleLibrary::GetNamedStyle(const rptStyleName& rmyStyleName)
{
   // check for default style first
   if (rmyStyleName == _T("Default") )
      return m_DefaultStyle;

   // search through custom style list
   StyleMap::iterator my_i = m_StyleMap.find(rmyStyleName);
   if (my_i != m_StyleMap.end() )
      return (*my_i).second;
   else
   {
      // should not have a case where looking for a named style that doesn't exist
      CHECKX(0,_T("Could not find named style in library"));
      return m_DefaultStyle;
   }

}

const rptRiStyle& rptFontStyleLibrary::GetDefaultStyle() const
{
   return m_DefaultStyle;
}

rptRiStyle& rptFontStyleLibrary::GetDefaultStyle()
{
   return m_DefaultStyle;
}
