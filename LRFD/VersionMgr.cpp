///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2021  Washington State Department of Transportation
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfdVersionMgr
****************************************************************************/


// Make the default, the most current version
lrfdVersionMgr::Version lrfdVersionMgr::ms_Version = (lrfdVersionMgr::Version)((int)lrfdVersionMgr::LastVersion-1);
lrfdVersionMgr::Units   lrfdVersionMgr::ms_Units   = lrfdVersionMgr::US;
bool lrfdVersionMgr::ms_IsDamaged = false;

typedef std::list<lrfdVersionMgrListener*,std::allocator<lrfdVersionMgrListener*> > Listeners;
Listeners lrfdVersionMgr::ms_Listeners;

void notify_listeners(Listeners& rList)
{
   Listeners::iterator iter;
   for ( iter = rList.begin(); iter != rList.end(); iter++ )
   {
      (*iter)->OnUpdate();
   }
}

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================

lrfdVersionMgr::~lrfdVersionMgr()
{
}

//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdVersionMgr::BeginDamage()
{
   ms_IsDamaged = true;
}

void lrfdVersionMgr::EndDamage()
{
   ms_IsDamaged = false;
   NotifyAllListeners();
}

bool lrfdVersionMgr::IsDamaged()
{
   return ms_IsDamaged;
}

//======================== ACCESS     =======================================
lrfdVersionMgr::Version lrfdVersionMgr::SetVersion(Version version)
{
   if ( version == ms_Version )
      return ms_Version;

   Version temp = ms_Version;
   ms_Version = version;

   if ( lrfdVersionMgr::FourthEdition2007 <= ms_Version && ms_Units == lrfdVersionMgr::SI )
   {
      // SI units were dropped from LRFD starting with 4th Edition 2007
      ms_Units = lrfdVersionMgr::US;
   }


   NotifyAllListeners();
   return temp;
}

lrfdVersionMgr::Version lrfdVersionMgr::GetVersion()
{
   return ms_Version;
}

lrfdVersionMgr::Units lrfdVersionMgr::SetUnits(Units units)
{
   if ( units == ms_Units )
      return ms_Units;

   Units temp = ms_Units;
   ms_Units = units;


   if ( lrfdVersionMgr::FourthEdition2007 <= ms_Version && ms_Units == lrfdVersionMgr::SI )
   {
      // SI units were dropped from LRFD starting with 4th Edition 2007
      ASSERT( false );
      ms_Units = lrfdVersionMgr::US;
   }

   NotifyAllListeners();
   return temp;
}

lrfdVersionMgr::Units lrfdVersionMgr::GetUnits()
{
   return ms_Units;
}

LPCTSTR lrfdVersionMgr::GetCodeString()
{
   return _T("AASHTO LRFD Bridge Design Specification");
}

LPCTSTR lrfdVersionMgr::GetVersionString(bool bAbbreviated)
{
   return lrfdVersionMgr::GetVersionString(ms_Version,bAbbreviated);
}

LPCTSTR lrfdVersionMgr::GetVersionString(lrfdVersionMgr::Version version,bool bAbbreviated)
{
   switch( version )
   {
   case FirstEdition1994:
      return (bAbbreviated ? _T("AashtoLrfd1994") : _T("First Edition 1994"));

   case FirstEditionWith1996Interims:
      return (bAbbreviated ? _T("AashtoLrfd1996") : _T("First Edition 1994 with 1996 interim provisions"));

   case FirstEditionWith1997Interims:
      return (bAbbreviated ? _T("AashtoLrfd1997") : _T("First Edition 1994 with 1996 - 1997 interim provisions"));

   case SecondEdition1998:
      return (bAbbreviated ? _T("AashtoLrfd1998") : _T("Second Edition 1998"));

   case SecondEditionWith1999Interims:
      return (bAbbreviated ? _T("AashtoLrfd1999") : _T("Second Edition 1998 with 1999 interim provisions"));

   case SecondEditionWith2000Interims:
      return (bAbbreviated ? _T("AashtoLrfd2000") : _T("Second Edition 1998 with 1999 - 2000 interim provisions"));

   case SecondEditionWith2001Interims:
      return (bAbbreviated ? _T("AashtoLrfd2001") : _T("Second Edition 1998 with 1999 - 2001 interim provisions"));

   case SecondEditionWith2002Interims:
      return (bAbbreviated ? _T("AashtoLrfd2002") : _T("Second Edition 1998 with 1999 - 2002 interim provisions"));

   case SecondEditionWith2003Interims:
      return (bAbbreviated ? _T("AashtoLrfd2003") : _T("Second Edition 1998 with 1999 - 2003 interim provisions"));

   case ThirdEdition2004:
      return (bAbbreviated ? _T("AashtoLrfd2004") : _T("Third Edition 2004"));

   case ThirdEditionWith2005Interims:
      return (bAbbreviated ? _T("AashtoLrfd2005") : _T("Third Edition 2004 with 2005 interim provisions"));

   case ThirdEditionWith2006Interims:
      return (bAbbreviated ? _T("AashtoLrfd2006") : _T("Third Edition 2004 with 2005 - 2006 interim provisions"));

      // NOTE: 4th is not spelled out in the official name of the 4th edition, but
      // it is spelled out in all other editions. That is why 4th is used here
      // instead of fourth
   case FourthEdition2007:
      return (bAbbreviated ? _T("AashtoLrfd2007") : _T("4th Edition 2007"));

   case FourthEditionWith2008Interims:
      return (bAbbreviated ? _T("AashtoLrfd2008") : _T("4th Edition 2007 with 2008 interim provisions"));

   case FourthEditionWith2009Interims:
      return (bAbbreviated ? _T("AashtoLrfd2009") : _T("4th Edition 2007 with 2008 - 2009 interim provisions"));

   case FifthEdition2010:
      return (bAbbreviated ? _T("AashtoLrfd2010") : _T("Fifth Edition 2010"));

   case SixthEdition2012:
      return (bAbbreviated ? _T("AashtoLrfd2012") : _T("Sixth Edition 2012"));

   case SixthEditionWith2013Interims:
      return (bAbbreviated ? _T("AashtoLrfd2013") : _T("Sixth Edition 2012 with 2013 interim provisions"));

   case SeventhEdition2014:
      return (bAbbreviated ? _T("AashtoLrfd2014") : _T("Seventh Edition 2014"));

   case SeventhEditionWith2015Interims:
      return (bAbbreviated ? _T("AashtoLrfd2015") : _T("Seventh Edition 2014 with 2015 interim provisions"));

   case SeventhEditionWith2016Interims:
      return (bAbbreviated ? _T("AashtoLrfd2016") : _T("Seventh Edition 2014 with 2016 interim provisions"));

   case EighthEdition2017:
      return (bAbbreviated ? _T("AashtoLrfd2017") : _T("8th Edition 2017"));

   case NinthEdition2020:
      return (bAbbreviated ? _T("AashtoLrfd2020") : _T("9th Edition 2020"));

   default:
      ASSERT(false);
      return _T("Unknown");
   }
}

LPCTSTR lrfdVersionMgr::GetUnitString()
{
   return ( ms_Units == SI ? _T("SI Units") : _T("Customary U.S. Units")) ;
}

lrfdVersionMgr::Version lrfdVersionMgr::GetVersion(LPCTSTR strAbbrev)
{
   std::_tstring tmp(strAbbrev);
   if (tmp == _T("AashtoLrfd2020"))
   {
      return lrfdVersionMgr::NinthEdition2020;
   }
   else if(tmp==_T("AashtoLrfd2017"))
   {
      return lrfdVersionMgr::EighthEdition2017;
   }
   else if(tmp==_T("AashtoLrfd2016"))
   {
      return lrfdVersionMgr::SeventhEditionWith2016Interims;
   }
   else if(tmp==_T("AashtoLrfd2015"))
   {
      return lrfdVersionMgr::SeventhEditionWith2015Interims;
   }
   else if(tmp==_T("AashtoLrfd2014"))
   {
      return lrfdVersionMgr::SeventhEdition2014;
   }
   else if(tmp==_T("AashtoLrfd2013"))
   {
      return lrfdVersionMgr::SixthEditionWith2013Interims;
   }
   else if(tmp==_T("AashtoLrfd2012"))
   {
      return lrfdVersionMgr::SixthEdition2012;
   }
   else if(tmp==_T("AashtoLrfd2010"))
   {
      return lrfdVersionMgr::FifthEdition2010;
   }
   else if(tmp==_T("AashtoLrfd2009"))
   {
      return lrfdVersionMgr::FourthEditionWith2009Interims;
   }
   else if(tmp==_T("AashtoLrfd2008"))
   {
      return lrfdVersionMgr::FourthEditionWith2008Interims;
   }
   else if(tmp==_T("AashtoLrfd2007"))
   {
      return lrfdVersionMgr::FourthEdition2007;
   }
   else if(tmp==_T("AashtoLrfd2006"))
   {
      return lrfdVersionMgr::ThirdEditionWith2006Interims;
   }
   else if(tmp==_T("AashtoLrfd2005"))
   {
      return lrfdVersionMgr::ThirdEditionWith2005Interims;
   }
   else if(tmp==_T("AashtoLrfd2004"))
   {
      return lrfdVersionMgr::ThirdEdition2004;
   }
   else if(tmp==_T("AashtoLrfd2003"))
   {
      return lrfdVersionMgr::SecondEditionWith2003Interims;
   }
   else if(tmp==_T("AashtoLrfd2002"))
   {
      return lrfdVersionMgr::SecondEditionWith2002Interims;
   }
   else if(tmp==_T("AashtoLrfd2001"))
   {
      return lrfdVersionMgr::SecondEditionWith2001Interims;
   }
   else if(tmp==_T("AashtoLrfd2000"))
   {
      return lrfdVersionMgr::SecondEditionWith2000Interims;
   }
   else if(tmp==_T("AashtoLrfd1999"))
   {
      return lrfdVersionMgr::SecondEditionWith1999Interims;
   }
   else if(tmp==_T("AashtoLrfd1998"))
   {
      return lrfdVersionMgr::SecondEdition1998;
   }
   else if(tmp==_T("AashtoLrfd1997"))
   {
      return lrfdVersionMgr::FirstEditionWith1997Interims;
   }
   else if(tmp==_T("AashtoLrfd1996"))
   {
      return lrfdVersionMgr::FirstEditionWith1996Interims;
   }
   else if (tmp==_T("AashtoLrfd1994"))
   {
      return lrfdVersionMgr::FirstEdition1994;
   }
   else
   {
      ATLASSERT(false);
      throw 0;
   }
}

void lrfdVersionMgr::RegisterListener(lrfdVersionMgrListener* pListener)
{
   ms_Listeners.push_back( pListener );
   pListener->OnRegistered();
}

void lrfdVersionMgr::UnregisterListener(lrfdVersionMgrListener* pListener)
{
   Listeners::iterator found;
   found = std::find( ms_Listeners.begin(), ms_Listeners.end(), pListener );
   if ( found != ms_Listeners.end() )
   {
      pListener->OnUnregistered();
      ms_Listeners.erase( found );
   }
}

CollectionIndexType lrfdVersionMgr::ListenerCount()
{
   return ms_Listeners.size();
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool lrfdVersionMgr::AssertValid()
{
   return true;
}

void lrfdVersionMgr::Dump(dbgDumpContext& os)
{
   os << GetVersionString(false) << endl;
}
#endif // _DEBUG
#if defined _UNITTEST
bool lrfdVersionMgr::TestMe(dbgLog& rlog)
{
   return true;
}
#endif // _UNITTEST


////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void lrfdVersionMgr::NotifyAllListeners()
{
   if ( !IsDamaged() )
   {
      notify_listeners( ms_Listeners );
   }
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


