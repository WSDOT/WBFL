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
#include <Lrfd\LRFRVersionMgr.h>
#include <Lrfd\LRFRVersionMgrListener.h>
#include <algorithm>

using namespace WBFL::LRFD;

// Make the default, the most current version
LRFRVersionMgr::Version LRFRVersionMgr::ms_Version = LRFRVersionMgr::GetLatestVersion();
bool LRFRVersionMgr::ms_IsDamaged = false;

LRFRVersionMgr::Listeners LRFRVersionMgr::ms_Listeners;


void LRFRVersionMgr::BeginDamage()
{
   ms_IsDamaged = true;
}

void LRFRVersionMgr::EndDamage()
{
   ms_IsDamaged = false;
   NotifyAllListeners();
}

bool LRFRVersionMgr::IsDamaged()
{
   return ms_IsDamaged;
}

LRFRVersionMgr::Version LRFRVersionMgr::SetVersion(Version version)
{
   if ( version == ms_Version )
      return ms_Version;

   Version temp = ms_Version;
   ms_Version = version;
   NotifyAllListeners();
   return temp;
}

LRFRVersionMgr::Version LRFRVersionMgr::GetVersion()
{
   return ms_Version;
}

LRFRVersionMgr::Version LRFRVersionMgr::GetLatestVersion()
{
   return (LRFRVersionMgr::Version)(std::underlying_type<LRFRVersionMgr::Version>::type(Version::LastVersion) - 1);
}

LPCTSTR LRFRVersionMgr::GetCodeString()
{
   return _T("The Manual for Bridge Evaluation");
}

LPCTSTR LRFRVersionMgr::GetVersionString(bool bAbbreviated)
{
   return GetVersionString(ms_Version,bAbbreviated);
}

LPCTSTR LRFRVersionMgr::GetVersionString(LRFRVersionMgr::Version version,bool bAbbreviated)
{
   switch( version )
   {
   case Version::FirstEdition2008:
      return (bAbbreviated ? _T("LRFR2008") : _T("First Edition 2008"));

   case Version::FirstEditionWith2010Interims:
      return (bAbbreviated ? _T("LRFR2010") : _T("First Edition 2008, with 2010 interim provisions"));

   case Version::SecondEdition2011:
      return (bAbbreviated ? _T("LRFR2011") : _T("Second Edition 2011"));
      
   case Version::SecondEditionWith2011Interims:
      return (bAbbreviated ? _T("LRFR2011i") : _T("Second Edition 2011, with 2011 interim provisions"));

   case Version::SecondEditionWith2013Interims:
      return (bAbbreviated ? _T("LRFR2013") : _T("Second Edition 2011, with 2011-2013 interim provisions"));

   case Version::SecondEditionWith2014Interims:
      return (bAbbreviated ? _T("LRFR2015") : _T("Second Edition 2011, with 2011-2014 interim provisions"));

   case Version::SecondEditionWith2015Interims:
      return (bAbbreviated ? _T("LRFR2015") : _T("Second Edition 2011, with 2011-2015 interim provisions"));
   
   case Version::SecondEditionWith2016Interims:
      return (bAbbreviated ? _T("LRFR2016") : _T("Second Edition 2011, with 2011-2016 interim provisions"));

   case Version::ThirdEdition2018:
      return (bAbbreviated ? _T("LRFR2018") : _T("Third Edition 2018"));

   case Version::ThirdEditionWith2020Interims:
      return (bAbbreviated ? _T("LRFR2020") : _T("Third Edition 2018, with 2020 interim provisions"));

   case Version::LastVersion:
      return GetVersionString(GetLatestVersion(), bAbbreviated);

   default:
      CHECK(false);
      return _T("LRFR2008");
   }
}

LRFRVersionMgr::Version LRFRVersionMgr::GetVersion(LPCTSTR strAbbrev)
{
   std::_tstring strSpecVersion(strAbbrev);
   if(strSpecVersion == _T("LRFR2008"))
   {
      return Version::FirstEdition2008;
   }
   else if(strSpecVersion == _T("LRFR2010"))
   {
      return Version::FirstEditionWith2010Interims;
   }
   else if (strSpecVersion == _T("LRFR2011"))
   {
      return Version::SecondEdition2011;
   }
   else if (strSpecVersion == _T("LRFR2011i"))
   {
      return Version::SecondEditionWith2011Interims;
   }
   else if (strSpecVersion == _T("LRFR2013"))
   {
      return Version::SecondEditionWith2013Interims;
   }
   else if (strSpecVersion == _T("LRFR2014"))
   {
      return Version::SecondEditionWith2014Interims;
   }
   else if (strSpecVersion == _T("LRFR2015"))
   {
      return Version::SecondEditionWith2015Interims;
   }
   else if (strSpecVersion == _T("LRFR2016"))
   {
      return Version::SecondEditionWith2016Interims;
   }
   else if (strSpecVersion == _T("LRFR2018"))
   {
      return Version::ThirdEdition2018;
   }
   else if (strSpecVersion == _T("LRFR2020"))
   {
      return Version::ThirdEditionWith2020Interims;
   }
   else
   {
      CHECK(false);
      throw std::invalid_argument("Invalid specification identifier");
   }
}

void LRFRVersionMgr::RegisterListener(LRFRVersionMgrListener* pListener)
{
   PRECONDITION(pListener != nullptr);
   ms_Listeners.push_back( pListener );
   pListener->OnRegistered();
}

void LRFRVersionMgr::UnregisterListener(LRFRVersionMgrListener* pListener)
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

IndexType LRFRVersionMgr::ListenerCount()
{
   return ms_Listeners.size();
}

void LRFRVersionMgr::NotifyAllListeners()
{
   if ( !IsDamaged() )
   {
      for (auto* listener : ms_Listeners)
      {
         listener->OnUpdate();
      }
   }
}
