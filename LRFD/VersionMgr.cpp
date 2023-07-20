///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\VersionMgr.h>
#include <Lrfd\VersionMgrListener.h>
#include <algorithm>

using namespace WBFL::LRFD;

// Make the default, the most current version
LRFDVersionMgr::Version LRFDVersionMgr::ms_Version = LRFDVersionMgr::GetLatestVersion();
LRFDVersionMgr::Units   LRFDVersionMgr::ms_Units   = LRFDVersionMgr::Units::US;
bool LRFDVersionMgr::ms_IsDamaged = false;

using Listeners = std::list<LRFDVersionMgrListener*,std::allocator<LRFDVersionMgrListener*>>;
Listeners LRFDVersionMgr::ms_Listeners;

void LRFDVersionMgr::BeginDamage()
{
   ms_IsDamaged = true;
}

void LRFDVersionMgr::EndDamage()
{
   ms_IsDamaged = false;
   NotifyAllListeners();
}

bool LRFDVersionMgr::IsDamaged()
{
   return ms_IsDamaged;
}

LRFDVersionMgr::Version LRFDVersionMgr::SetVersion(Version version)
{
   if ( version == ms_Version )
      return ms_Version;

   Version temp = ms_Version;
   ms_Version = version;

   if ( LRFDVersionMgr::Version::FourthEdition2007 <= ms_Version && ms_Units == LRFDVersionMgr::Units::SI )
   {
      // SI units were dropped from LRFD starting with 4th Edition 2007
      WATCH(_T("LRFD Specification units forced to US"));
      ms_Units = LRFDVersionMgr::Units::US;
   }

   NotifyAllListeners();
   return temp;
}

LRFDVersionMgr::Version LRFDVersionMgr::GetVersion()
{
   return ms_Version;
}

LRFDVersionMgr::Version LRFDVersionMgr::GetLatestVersion()
{
   return LRFDVersionMgr::Version(std::underlying_type<LRFDVersionMgr::Version>::type(Version::LastVersion) - 1);
}

LRFDVersionMgr::Units LRFDVersionMgr::SetUnits(Units units)
{
   if ( units == ms_Units )
      return ms_Units;

   Units temp = ms_Units;
   ms_Units = units;


   if ( LRFDVersionMgr::Version::FourthEdition2007 <= ms_Version && ms_Units == LRFDVersionMgr::Units::SI )
   {
      // SI units were dropped from LRFD starting with 4th Edition 2007
      WATCH(_T("LRFD Specification units forced to US"));
      ms_Units = LRFDVersionMgr::Units::US;
   }

   NotifyAllListeners();
   return temp;
}

LRFDVersionMgr::Units LRFDVersionMgr::GetUnits()
{
   return ms_Units;
}

LPCTSTR LRFDVersionMgr::GetCodeString()
{
   return _T("AASHTO LRFD Bridge Design Specifications");
}

LPCTSTR LRFDVersionMgr::GetVersionString(bool bAbbreviated)
{
   return LRFDVersionMgr::GetVersionString(ms_Version,bAbbreviated);
}

LPCTSTR LRFDVersionMgr::GetVersionString(LRFDVersionMgr::Version version,bool bAbbreviated)
{
   switch( version )
   {
   case Version::FirstEdition1994:
      return (bAbbreviated ? _T("AashtoLrfd1994") : _T("First Edition 1994"));

   case Version::FirstEditionWith1996Interims:
      return (bAbbreviated ? _T("AashtoLrfd1996") : _T("First Edition 1994 with 1996 interim provisions"));

   case Version::FirstEditionWith1997Interims:
      return (bAbbreviated ? _T("AashtoLrfd1997") : _T("First Edition 1994 with 1996 - 1997 interim provisions"));

   case Version::SecondEdition1998:
      return (bAbbreviated ? _T("AashtoLrfd1998") : _T("Second Edition 1998"));

   case Version::SecondEditionWith1999Interims:
      return (bAbbreviated ? _T("AashtoLrfd1999") : _T("Second Edition 1998 with 1999 interim provisions"));

   case Version::SecondEditionWith2000Interims:
      return (bAbbreviated ? _T("AashtoLrfd2000") : _T("Second Edition 1998 with 1999 - 2000 interim provisions"));

   case Version::SecondEditionWith2001Interims:
      return (bAbbreviated ? _T("AashtoLrfd2001") : _T("Second Edition 1998 with 1999 - 2001 interim provisions"));

   case Version::SecondEditionWith2002Interims:
      return (bAbbreviated ? _T("AashtoLrfd2002") : _T("Second Edition 1998 with 1999 - 2002 interim provisions"));

   case Version::SecondEditionWith2003Interims:
      return (bAbbreviated ? _T("AashtoLrfd2003") : _T("Second Edition 1998 with 1999 - 2003 interim provisions"));

   case Version::ThirdEdition2004:
      return (bAbbreviated ? _T("AashtoLrfd2004") : _T("Third Edition 2004"));

   case Version::ThirdEditionWith2005Interims:
      return (bAbbreviated ? _T("AashtoLrfd2005") : _T("Third Edition 2004 with 2005 interim provisions"));

   case Version::ThirdEditionWith2006Interims:
      return (bAbbreviated ? _T("AashtoLrfd2006") : _T("Third Edition 2004 with 2005 - 2006 interim provisions"));

      // NOTE: 4th is not spelled out in the official name of the 4th edition, but
      // it is spelled out in all other editions. That is why 4th is used here
      // instead of fourth
   case Version::FourthEdition2007:
      return (bAbbreviated ? _T("AashtoLrfd2007") : _T("4th Edition 2007"));

   case Version::FourthEditionWith2008Interims:
      return (bAbbreviated ? _T("AashtoLrfd2008") : _T("4th Edition 2007 with 2008 interim provisions"));

   case Version::FourthEditionWith2009Interims:
      return (bAbbreviated ? _T("AashtoLrfd2009") : _T("4th Edition 2007 with 2008 - 2009 interim provisions"));

   case Version::FifthEdition2010:
      return (bAbbreviated ? _T("AashtoLrfd2010") : _T("Fifth Edition 2010"));

   case Version::SixthEdition2012:
      return (bAbbreviated ? _T("AashtoLrfd2012") : _T("Sixth Edition 2012"));

   case Version::SixthEditionWith2013Interims:
      return (bAbbreviated ? _T("AashtoLrfd2013") : _T("Sixth Edition 2012 with 2013 interim provisions"));

   case Version::SeventhEdition2014:
      return (bAbbreviated ? _T("AashtoLrfd2014") : _T("Seventh Edition 2014"));

   case Version::SeventhEditionWith2015Interims:
      return (bAbbreviated ? _T("AashtoLrfd2015") : _T("Seventh Edition 2014 with 2015 interim provisions"));

   case Version::SeventhEditionWith2016Interims:
      return (bAbbreviated ? _T("AashtoLrfd2016") : _T("Seventh Edition 2014 with 2016 interim provisions"));

   case Version::EighthEdition2017:
      return (bAbbreviated ? _T("AashtoLrfd2017") : _T("8th Edition 2017"));

   case Version::NinthEdition2020:
      return (bAbbreviated ? _T("AashtoLrfd2020") : _T("9th Edition 2020"));

   case Version::LastVersion:
      return GetVersionString(GetLatestVersion(), bAbbreviated);

   default:
      CHECK(false);
      return _T("Unknown");
   }
}

LPCTSTR LRFDVersionMgr::GetUnitString()
{
   return ( ms_Units == Units::SI ? _T("SI Units") : _T("Customary U.S. Units")) ;
}

LRFDVersionMgr::Version LRFDVersionMgr::GetVersion(LPCTSTR strAbbrev)
{
   std::_tstring tmp(strAbbrev);
   if (tmp == _T("AashtoLrfd2020"))
   {
      return Version::NinthEdition2020;
   }
   else if(tmp==_T("AashtoLrfd2017"))
   {
      return Version::EighthEdition2017;
   }
   else if(tmp==_T("AashtoLrfd2016"))
   {
      return Version::SeventhEditionWith2016Interims;
   }
   else if(tmp==_T("AashtoLrfd2015"))
   {
      return Version::SeventhEditionWith2015Interims;
   }
   else if(tmp==_T("AashtoLrfd2014"))
   {
      return Version::SeventhEdition2014;
   }
   else if(tmp==_T("AashtoLrfd2013"))
   {
      return Version::SixthEditionWith2013Interims;
   }
   else if(tmp==_T("AashtoLrfd2012"))
   {
      return Version::SixthEdition2012;
   }
   else if(tmp==_T("AashtoLrfd2010"))
   {
      return Version::FifthEdition2010;
   }
   else if(tmp==_T("AashtoLrfd2009"))
   {
      return Version::FourthEditionWith2009Interims;
   }
   else if(tmp==_T("AashtoLrfd2008"))
   {
      return Version::FourthEditionWith2008Interims;
   }
   else if(tmp==_T("AashtoLrfd2007"))
   {
      return Version::FourthEdition2007;
   }
   else if(tmp==_T("AashtoLrfd2006"))
   {
      return Version::ThirdEditionWith2006Interims;
   }
   else if(tmp==_T("AashtoLrfd2005"))
   {
      return Version::ThirdEditionWith2005Interims;
   }
   else if(tmp==_T("AashtoLrfd2004"))
   {
      return Version::ThirdEdition2004;
   }
   else if(tmp==_T("AashtoLrfd2003"))
   {
      return Version::SecondEditionWith2003Interims;
   }
   else if(tmp==_T("AashtoLrfd2002"))
   {
      return Version::SecondEditionWith2002Interims;
   }
   else if(tmp==_T("AashtoLrfd2001"))
   {
      return Version::SecondEditionWith2001Interims;
   }
   else if(tmp==_T("AashtoLrfd2000"))
   {
      return Version::SecondEditionWith2000Interims;
   }
   else if(tmp==_T("AashtoLrfd1999"))
   {
      return Version::SecondEditionWith1999Interims;
   }
   else if(tmp==_T("AashtoLrfd1998"))
   {
      return Version::SecondEdition1998;
   }
   else if(tmp==_T("AashtoLrfd1997"))
   {
      return Version::FirstEditionWith1997Interims;
   }
   else if(tmp==_T("AashtoLrfd1996"))
   {
      return Version::FirstEditionWith1996Interims;
   }
   else if (tmp==_T("AashtoLrfd1994"))
   {
      return Version::FirstEdition1994;
   }
   else
   {
      CHECK(false);
      throw std::invalid_argument("Invalid specification identifier");
   }
}

void LRFDVersionMgr::RegisterListener(LRFDVersionMgrListener* pListener)
{
   PRECONDITION(pListener != nullptr);
   ms_Listeners.push_back( pListener );
   pListener->OnRegistered();
}

void LRFDVersionMgr::UnregisterListener(LRFDVersionMgrListener* pListener)
{
   Listeners::iterator found;
   found = std::find( ms_Listeners.begin(), ms_Listeners.end(), pListener );
   if ( found != ms_Listeners.end() )
   {
      pListener->OnUnregistered();
      ms_Listeners.erase( found );
   }
   else
   {
      throw std::invalid_argument("Invalid listener or listener not registered");
   }
}

IndexType LRFDVersionMgr::ListenerCount()
{
   return ms_Listeners.size();
}

void LRFDVersionMgr::NotifyAllListeners()
{
   if ( !IsDamaged() )
   {
      for (auto* listener : ms_Listeners)
      {
         listener->OnUpdate();
      }
   }
}
