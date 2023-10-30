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
#include <Lrfd/BDSManager.h>
#include <Lrfd/BDSManagerListener.h>
#include <algorithm>

using namespace WBFL::LRFD;

// Make the default, the most current version
BDSManager::Edition BDSManager::ms_Edition = BDSManager::GetLatestEdition();
BDSManager::Units   BDSManager::ms_Units   = BDSManager::Units::US;
bool BDSManager::ms_bIsDamaged = false;

using Listeners = std::list<BDSManagerListener*,std::allocator<BDSManagerListener*>>;
Listeners BDSManager::ms_Listeners;

void BDSManager::BeginDamage()
{
   ms_bIsDamaged = true;
}

void BDSManager::EndDamage()
{
   ms_bIsDamaged = false;
   NotifyAllListeners();
}

bool BDSManager::IsDamaged()
{
   return ms_bIsDamaged;
}

BDSManager::Edition BDSManager::SetEdition(Edition edition)
{
   if (edition == ms_Edition )
      return ms_Edition;

   Edition temp = ms_Edition;
   ms_Edition = edition;

   if ( BDSManager::Edition::FourthEdition2007 <= ms_Edition && ms_Units == BDSManager::Units::SI )
   {
      // SI units were dropped from LRFD starting with 4th Edition 2007
      WATCH(_T("LRFD Specification units forced to US"));
      ms_Units = BDSManager::Units::US;
   }

   NotifyAllListeners();
   return temp;
}

BDSManager::Edition BDSManager::GetEdition()
{
   return ms_Edition;
}

BDSManager::Edition BDSManager::GetLatestEdition()
{
   return BDSManager::Edition(std::underlying_type<BDSManager::Edition>::type(Edition::LastEdition) - 1);
}

BDSManager::Units BDSManager::SetUnits(Units units)
{
   if ( units == ms_Units )
      return ms_Units;

   Units temp = ms_Units;
   ms_Units = units;


   if ( BDSManager::Edition::FourthEdition2007 <= ms_Edition && ms_Units == BDSManager::Units::SI )
   {
      // SI units were dropped from LRFD starting with 4th Edition 2007
      WATCH(_T("LRFD Specification units forced to US"));
      ms_Units = BDSManager::Units::US;
   }

   NotifyAllListeners();
   return temp;
}

BDSManager::Units BDSManager::GetUnits()
{
   return ms_Units;
}

LPCTSTR BDSManager::GetSpecificationName()
{
   return _T("AASHTO LRFD Bridge Design Specifications");
}

LPCTSTR BDSManager::GetEditionAsString(bool bAbbreviated)
{
   return BDSManager::GetEditionAsString(ms_Edition,bAbbreviated);
}

LPCTSTR BDSManager::GetEditionAsString(BDSManager::Edition edition,bool bAbbreviated)
{
   switch(edition)
   {
   case Edition::FirstEdition1994:
      return (bAbbreviated ? _T("AashtoLrfd1994") : _T("First Edition 1994"));

   case Edition::FirstEditionWith1996Interims:
      return (bAbbreviated ? _T("AashtoLrfd1996") : _T("First Edition 1994 with 1996 interim provisions"));

   case Edition::FirstEditionWith1997Interims:
      return (bAbbreviated ? _T("AashtoLrfd1997") : _T("First Edition 1994 with 1996 - 1997 interim provisions"));

   case Edition::SecondEdition1998:
      return (bAbbreviated ? _T("AashtoLrfd1998") : _T("Second Edition 1998"));

   case Edition::SecondEditionWith1999Interims:
      return (bAbbreviated ? _T("AashtoLrfd1999") : _T("Second Edition 1998 with 1999 interim provisions"));

   case Edition::SecondEditionWith2000Interims:
      return (bAbbreviated ? _T("AashtoLrfd2000") : _T("Second Edition 1998 with 1999 - 2000 interim provisions"));

   case Edition::SecondEditionWith2001Interims:
      return (bAbbreviated ? _T("AashtoLrfd2001") : _T("Second Edition 1998 with 1999 - 2001 interim provisions"));

   case Edition::SecondEditionWith2002Interims:
      return (bAbbreviated ? _T("AashtoLrfd2002") : _T("Second Edition 1998 with 1999 - 2002 interim provisions"));

   case Edition::SecondEditionWith2003Interims:
      return (bAbbreviated ? _T("AashtoLrfd2003") : _T("Second Edition 1998 with 1999 - 2003 interim provisions"));

   case Edition::ThirdEdition2004:
      return (bAbbreviated ? _T("AashtoLrfd2004") : _T("Third Edition 2004"));

   case Edition::ThirdEditionWith2005Interims:
      return (bAbbreviated ? _T("AashtoLrfd2005") : _T("Third Edition 2004 with 2005 interim provisions"));

   case Edition::ThirdEditionWith2006Interims:
      return (bAbbreviated ? _T("AashtoLrfd2006") : _T("Third Edition 2004 with 2005 - 2006 interim provisions"));

      // NOTE: 4th is not spelled out in the official name of the 4th edition, but
      // it is spelled out in all other editions. That is why 4th is used here
      // instead of fourth
   case Edition::FourthEdition2007:
      return (bAbbreviated ? _T("AashtoLrfd2007") : _T("4th Edition 2007"));

   case Edition::FourthEditionWith2008Interims:
      return (bAbbreviated ? _T("AashtoLrfd2008") : _T("4th Edition 2007 with 2008 interim provisions"));

   case Edition::FourthEditionWith2009Interims:
      return (bAbbreviated ? _T("AashtoLrfd2009") : _T("4th Edition 2007 with 2008 - 2009 interim provisions"));

   case Edition::FifthEdition2010:
      return (bAbbreviated ? _T("AashtoLrfd2010") : _T("Fifth Edition 2010"));

   case Edition::SixthEdition2012:
      return (bAbbreviated ? _T("AashtoLrfd2012") : _T("Sixth Edition 2012"));

   case Edition::SixthEditionWith2013Interims:
      return (bAbbreviated ? _T("AashtoLrfd2013") : _T("Sixth Edition 2012 with 2013 interim provisions"));

   case Edition::SeventhEdition2014:
      return (bAbbreviated ? _T("AashtoLrfd2014") : _T("Seventh Edition 2014"));

   case Edition::SeventhEditionWith2015Interims:
      return (bAbbreviated ? _T("AashtoLrfd2015") : _T("Seventh Edition 2014 with 2015 interim provisions"));

   case Edition::SeventhEditionWith2016Interims:
      return (bAbbreviated ? _T("AashtoLrfd2016") : _T("Seventh Edition 2014 with 2016 interim provisions"));

   case Edition::EighthEdition2017:
      return (bAbbreviated ? _T("AashtoLrfd2017") : _T("8th Edition 2017"));

   case Edition::NinthEdition2020:
      return (bAbbreviated ? _T("AashtoLrfd2020") : _T("9th Edition 2020"));

   case Edition::LastEdition:
      return GetEditionAsString(GetLatestEdition(), bAbbreviated);

   default:
      CHECK(false);
      return _T("Unknown");
   }
}

LPCTSTR BDSManager::GetUnitAsString()
{
   return ( ms_Units == Units::SI ? _T("SI Units") : _T("Customary U.S. Units")) ;
}

BDSManager::Edition BDSManager::GetEdition(LPCTSTR strAbbrev)
{
   std::_tstring tmp(strAbbrev);
   if (tmp == _T("AashtoLrfd2020"))
   {
      return Edition::NinthEdition2020;
   }
   else if(tmp==_T("AashtoLrfd2017"))
   {
      return Edition::EighthEdition2017;
   }
   else if(tmp==_T("AashtoLrfd2016"))
   {
      return Edition::SeventhEditionWith2016Interims;
   }
   else if(tmp==_T("AashtoLrfd2015"))
   {
      return Edition::SeventhEditionWith2015Interims;
   }
   else if(tmp==_T("AashtoLrfd2014"))
   {
      return Edition::SeventhEdition2014;
   }
   else if(tmp==_T("AashtoLrfd2013"))
   {
      return Edition::SixthEditionWith2013Interims;
   }
   else if(tmp==_T("AashtoLrfd2012"))
   {
      return Edition::SixthEdition2012;
   }
   else if(tmp==_T("AashtoLrfd2010"))
   {
      return Edition::FifthEdition2010;
   }
   else if(tmp==_T("AashtoLrfd2009"))
   {
      return Edition::FourthEditionWith2009Interims;
   }
   else if(tmp==_T("AashtoLrfd2008"))
   {
      return Edition::FourthEditionWith2008Interims;
   }
   else if(tmp==_T("AashtoLrfd2007"))
   {
      return Edition::FourthEdition2007;
   }
   else if(tmp==_T("AashtoLrfd2006"))
   {
      return Edition::ThirdEditionWith2006Interims;
   }
   else if(tmp==_T("AashtoLrfd2005"))
   {
      return Edition::ThirdEditionWith2005Interims;
   }
   else if(tmp==_T("AashtoLrfd2004"))
   {
      return Edition::ThirdEdition2004;
   }
   else if(tmp==_T("AashtoLrfd2003"))
   {
      return Edition::SecondEditionWith2003Interims;
   }
   else if(tmp==_T("AashtoLrfd2002"))
   {
      return Edition::SecondEditionWith2002Interims;
   }
   else if(tmp==_T("AashtoLrfd2001"))
   {
      return Edition::SecondEditionWith2001Interims;
   }
   else if(tmp==_T("AashtoLrfd2000"))
   {
      return Edition::SecondEditionWith2000Interims;
   }
   else if(tmp==_T("AashtoLrfd1999"))
   {
      return Edition::SecondEditionWith1999Interims;
   }
   else if(tmp==_T("AashtoLrfd1998"))
   {
      return Edition::SecondEdition1998;
   }
   else if(tmp==_T("AashtoLrfd1997"))
   {
      return Edition::FirstEditionWith1997Interims;
   }
   else if(tmp==_T("AashtoLrfd1996"))
   {
      return Edition::FirstEditionWith1996Interims;
   }
   else if (tmp==_T("AashtoLrfd1994"))
   {
      return Edition::FirstEdition1994;
   }
   else
   {
      CHECK(false);
      throw std::invalid_argument("Invalid specification identifier");
   }
}

void BDSManager::RegisterListener(BDSManagerListener* pListener)
{
   PRECONDITION(pListener != nullptr);
   ms_Listeners.push_back( pListener );
   pListener->OnRegistered();
}

void BDSManager::UnregisterListener(BDSManagerListener* pListener)
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

IndexType BDSManager::ListenerCount()
{
   return ms_Listeners.size();
}

void BDSManager::NotifyAllListeners()
{
   if ( !IsDamaged() )
   {
      for (auto* listener : ms_Listeners)
      {
         listener->OnUpdate();
      }
   }
}
