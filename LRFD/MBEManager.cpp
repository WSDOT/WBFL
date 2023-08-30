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
#include <Lrfd/MBEManager.h>
#include <Lrfd/MBEManagerListener.h>
#include <algorithm>

using namespace WBFL::LRFD;

// Make the default, the most current version
MBEManager::Edition MBEManager::ms_Edition = MBEManager::GetLatestEdition();
bool MBEManager::ms_IsDamaged = false;

MBEManager::Listeners MBEManager::ms_Listeners;


void MBEManager::BeginDamage()
{
   ms_IsDamaged = true;
}

void MBEManager::EndDamage()
{
   ms_IsDamaged = false;
   NotifyAllListeners();
}

bool MBEManager::IsDamaged()
{
   return ms_IsDamaged;
}

MBEManager::Edition MBEManager::SetEdition(Edition edition)
{
   if (edition == ms_Edition )
      return ms_Edition;

   Edition temp = ms_Edition;
   ms_Edition = edition;
   NotifyAllListeners();
   return temp;
}

MBEManager::Edition MBEManager::GetEdition()
{
   return ms_Edition;
}

MBEManager::Edition MBEManager::GetLatestEdition()
{
   return (MBEManager::Edition)(std::underlying_type<MBEManager::Edition>::type(Edition::LastEdition) - 1);
}

LPCTSTR MBEManager::GetSpecificationName()
{
   return _T("The Manual for Bridge Evaluation");
}

LPCTSTR MBEManager::GetEditionAsString(bool bAbbreviated)
{
   return GetEditionAsString(ms_Edition,bAbbreviated);
}

LPCTSTR MBEManager::GetEditionAsString(MBEManager::Edition edition,bool bAbbreviated)
{
   switch(edition)
   {
   case Edition::FirstEdition2008:
      return (bAbbreviated ? _T("LRFR2008") : _T("First Edition 2008"));

   case Edition::FirstEditionWith2010Interims:
      return (bAbbreviated ? _T("LRFR2010") : _T("First Edition 2008, with 2010 interim provisions"));

   case Edition::SecondEdition2011:
      return (bAbbreviated ? _T("LRFR2011") : _T("Second Edition 2011"));
      
   case Edition::SecondEditionWith2011Interims:
      return (bAbbreviated ? _T("LRFR2011i") : _T("Second Edition 2011, with 2011 interim provisions"));

   case Edition::SecondEditionWith2013Interims:
      return (bAbbreviated ? _T("LRFR2013") : _T("Second Edition 2011, with 2011-2013 interim provisions"));

   case Edition::SecondEditionWith2014Interims:
      return (bAbbreviated ? _T("LRFR2015") : _T("Second Edition 2011, with 2011-2014 interim provisions"));

   case Edition::SecondEditionWith2015Interims:
      return (bAbbreviated ? _T("LRFR2015") : _T("Second Edition 2011, with 2011-2015 interim provisions"));
   
   case Edition::SecondEditionWith2016Interims:
      return (bAbbreviated ? _T("LRFR2016") : _T("Second Edition 2011, with 2011-2016 interim provisions"));

   case Edition::ThirdEdition2018:
      return (bAbbreviated ? _T("LRFR2018") : _T("Third Edition 2018"));

   case Edition::ThirdEditionWith2020Interims:
      return (bAbbreviated ? _T("LRFR2020") : _T("Third Edition 2018, with 2020 interim provisions"));

   case Edition::LastEdition:
      return GetEditionAsString(GetLatestEdition(), bAbbreviated);

   default:
      CHECK(false);
      return _T("LRFR2008");
   }
}

MBEManager::Edition MBEManager::GetEdition(LPCTSTR strAbbrev)
{
   std::_tstring strSpecVersion(strAbbrev);
   if(strSpecVersion == _T("LRFR2008"))
   {
      return Edition::FirstEdition2008;
   }
   else if(strSpecVersion == _T("LRFR2010"))
   {
      return Edition::FirstEditionWith2010Interims;
   }
   else if (strSpecVersion == _T("LRFR2011"))
   {
      return Edition::SecondEdition2011;
   }
   else if (strSpecVersion == _T("LRFR2011i"))
   {
      return Edition::SecondEditionWith2011Interims;
   }
   else if (strSpecVersion == _T("LRFR2013"))
   {
      return Edition::SecondEditionWith2013Interims;
   }
   else if (strSpecVersion == _T("LRFR2014"))
   {
      return Edition::SecondEditionWith2014Interims;
   }
   else if (strSpecVersion == _T("LRFR2015"))
   {
      return Edition::SecondEditionWith2015Interims;
   }
   else if (strSpecVersion == _T("LRFR2016"))
   {
      return Edition::SecondEditionWith2016Interims;
   }
   else if (strSpecVersion == _T("LRFR2018"))
   {
      return Edition::ThirdEdition2018;
   }
   else if (strSpecVersion == _T("LRFR2020"))
   {
      return Edition::ThirdEditionWith2020Interims;
   }
   else
   {
      CHECK(false);
      throw std::invalid_argument("Invalid specification identifier");
   }
}

void MBEManager::RegisterListener(MBEManagerListener* pListener)
{
   PRECONDITION(pListener != nullptr);
   ms_Listeners.push_back( pListener );
   pListener->OnRegistered();
}

void MBEManager::UnregisterListener(MBEManagerListener* pListener)
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

IndexType MBEManager::ListenerCount()
{
   return ms_Listeners.size();
}

void MBEManager::NotifyAllListeners()
{
   if ( !IsDamaged() )
   {
      for (auto* listener : ms_Listeners)
      {
         listener->OnUpdate();
      }
   }
}
