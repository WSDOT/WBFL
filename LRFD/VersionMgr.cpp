///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2012  Washington State Department of Transportation
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


lrfdVersionMgr::Version lrfdVersionMgr::ms_Version = lrfdVersionMgr::SecondEditionWith2002Interims;
lrfdVersionMgr::Units   lrfdVersionMgr::ms_Units   = lrfdVersionMgr::SI;
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

std::_tstring lrfdVersionMgr::GetCodeString()
{
   return _T("AASHTO LRFD Bridge Design Specification");
}

std::_tstring lrfdVersionMgr::GetVersionString()
{
   return lrfdVersionMgr::GetVersionString(ms_Version);
}

std::_tstring lrfdVersionMgr::GetVersionString(lrfdVersionMgr::Version version)
{
   std::_tstring strVersion;
   switch( version )
   {
   case FirstEdition1994:
      strVersion = _T("First Edition 1994");
      break;

   case FirstEditionWith1996Interims:
      strVersion = _T("First Edition with 1996 interim provisions");
      break;

   case FirstEditionWith1997Interims:
      strVersion = _T("First Edition with 1996 - 1997 interim provisions");
      break;

   case SecondEdition1998:
      strVersion = _T("Second Edition 1998");
      break;

   case SecondEditionWith1999Interims:
      strVersion = _T("Second Edition with 1999 interim provisions");
      break;

   case SecondEditionWith2000Interims:
      strVersion = _T("Second Edition with 1999 - 2000 interim provisions");
      break;

   case SecondEditionWith2001Interims:
      strVersion = _T("Second Edition with 1999 - 2001 interim provisions");
      break;

   case SecondEditionWith2002Interims:
      strVersion = _T("Second Edition with 1999 - 2002 interim provisions");
      break;

   case SecondEditionWith2003Interims:
      strVersion = _T("2nd Edition, 1998 with 1999 - 2003 interim provisions");
      break;

   case ThirdEdition2004:
      strVersion = _T("3rd Edition, 2004");
      break;

   case ThirdEditionWith2005Interims:
      strVersion = _T("3rd Edition, 2004 with 2005 interim provisions");
      break;

   case ThirdEditionWith2006Interims:
      strVersion = _T("3rd Edition, 2004 with 2005 - 2006 interim provisions");
      break;

   case FourthEdition2007:
      strVersion = _T("4th Edition, 2007");
      break;

   case FourthEditionWith2008Interims:
      strVersion = _T("4th Edition, 2007 with 2008 interim provisions");
      break;

   case FourthEditionWith2009Interims:
      strVersion = _T("4th Edition, 2007 with 2008 - 2009 interim provisions");
      break;

   case FifthEdition2010:
      strVersion = _T("5th Edition, 2010");
      break;

   case SixthEdition2012:
      strVersion = _T("6th Edition, 2012");
      break;

   default:
      CHECK(false);
   }

   return strVersion;
}

std::_tstring lrfdVersionMgr::GetUnitString()
{
   return ( ms_Units == SI ? _T("SI Units") : _T("Customary U.S. Units")) ;
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
   os << GetVersionString().c_str() << endl;
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


