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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   lrfrVersionMgr
****************************************************************************/

// Make the default, the most current version
lrfrVersionMgr::Version lrfrVersionMgr::ms_Version = (lrfrVersionMgr::Version)((int)lrfrVersionMgr::LastVersion-1);
bool lrfrVersionMgr::ms_IsDamaged = false;

lrfrVersionMgr::Listeners lrfrVersionMgr::ms_Listeners;

void notify_listeners(lrfrVersionMgr::Listeners& rList)
{
   lrfrVersionMgr::Listeners::iterator iter;
   for ( iter = rList.begin(); iter != rList.end(); iter++ )
   {
      (*iter)->OnUpdate();
   }
}


lrfrVersionMgr::~lrfrVersionMgr()
{
}

void lrfrVersionMgr::BeginDamage()
{
   ms_IsDamaged = true;
}

void lrfrVersionMgr::EndDamage()
{
   ms_IsDamaged = false;
   NotifyAllListeners();
}

bool lrfrVersionMgr::IsDamaged()
{
   return ms_IsDamaged;
}

//======================== ACCESS     =======================================
lrfrVersionMgr::Version lrfrVersionMgr::SetVersion(Version version)
{
   if ( version == ms_Version )
      return ms_Version;

   Version temp = ms_Version;
   ms_Version = version;
   NotifyAllListeners();
   return temp;
}

lrfrVersionMgr::Version lrfrVersionMgr::GetVersion()
{
   return ms_Version;
}

LPCTSTR lrfrVersionMgr::GetCodeString()
{
   return _T("The Manual for Bridge Evaluation");
}

LPCTSTR lrfrVersionMgr::GetVersionString(bool bAbbreviated)
{
   return GetVersionString(ms_Version,bAbbreviated);
}

LPCTSTR lrfrVersionMgr::GetVersionString(lrfrVersionMgr::Version version,bool bAbbreviated)
{
   switch( version )
   {
   case FirstEdition2008:
      return (bAbbreviated ? _T("LRFR2008") : _T("First Edition 2008"));

   case FirstEditionWith2010Interims:
      return (bAbbreviated ? _T("LRFR2010") : _T("First Edition 2008, with 2010 interim provisions"));

   case SecondEdition2011:
      return (bAbbreviated ? _T("LRFR2011") : _T("Second Edition 2011"));
      
   case SecondEditionWith2011Interims:
      return (bAbbreviated ? _T("LRFR2011i") : _T("Second Edition 2011, with 2011 interim provisions"));

   case SecondEditionWith2013Interims:
      return (bAbbreviated ? _T("LRFR2013") : _T("Second Edition 2011, with 2011-2013 interim provisions"));

   case SecondEditionWith2014Interims:
      return (bAbbreviated ? _T("LRFR2015") : _T("Second Edition 2011, with 2011-2014 interim provisions"));

   case SecondEditionWith2015Interims:
      return (bAbbreviated ? _T("LRFR2015") : _T("Second Edition 2011, with 2011-2015 interim provisions"));
   
   case SecondEditionWith2016Interims:
      return (bAbbreviated ? _T("LRFR2016") : _T("Second Edition 2011, with 2011-2016 interim provisions"));

   case ThirdEdition2018:
      return (bAbbreviated ? _T("LRFR2018") : _T("Third Edition 2018"));

   case ThirdEditionWith2020Interims:
      return (bAbbreviated ? _T("LRFR2020") : _T("Third Edition 2018, with 2020 interim provisions"));

   default:
      ASSERT(false);
      return _T("LRFR2008");
   }
}

lrfrVersionMgr::Version lrfrVersionMgr::GetVersion(LPCTSTR strAbbrev)
{
   std::_tstring strSpecVersion(strAbbrev);
   if(strSpecVersion == _T("LRFR2008"))
   {
      return lrfrVersionMgr::FirstEdition2008;
   }
   else if(strSpecVersion == _T("LRFR2010"))
   {
      return lrfrVersionMgr::FirstEditionWith2010Interims;
   }
   else if (strSpecVersion == _T("LRFR2011"))
   {
      return lrfrVersionMgr::SecondEdition2011;
   }
   else if (strSpecVersion == _T("LRFR2011i"))
   {
      return lrfrVersionMgr::SecondEditionWith2011Interims;
   }
   else if (strSpecVersion == _T("LRFR2013"))
   {
      return lrfrVersionMgr::SecondEditionWith2013Interims;
   }
   else if (strSpecVersion == _T("LRFR2014"))
   {
      return lrfrVersionMgr::SecondEditionWith2014Interims;
   }
   else if (strSpecVersion == _T("LRFR2015"))
   {
      return lrfrVersionMgr::SecondEditionWith2015Interims;
   }
   else if (strSpecVersion == _T("LRFR2016"))
   {
      return lrfrVersionMgr::SecondEditionWith2016Interims;
   }
   else if (strSpecVersion == _T("LRFR2018"))
   {
      return lrfrVersionMgr::ThirdEdition2018;
   }
   else if (strSpecVersion == _T("LRFR2020"))
   {
      return lrfrVersionMgr::ThirdEditionWith2020Interims;
   }
   else
   {
      ATLASSERT(false);
      throw 0;
   }
}

void lrfrVersionMgr::RegisterListener(lrfrVersionMgrListener* pListener)
{
   ms_Listeners.push_back( pListener );
   pListener->OnRegistered();
}

void lrfrVersionMgr::UnregisterListener(lrfrVersionMgrListener* pListener)
{
   Listeners::iterator found;
   found = std::find( ms_Listeners.begin(), ms_Listeners.end(), pListener );
   if ( found != ms_Listeners.end() )
   {
      pListener->OnUnregistered();
      ms_Listeners.erase( found );
   }
}

CollectionIndexType lrfrVersionMgr::ListenerCount()
{
   return ms_Listeners.size();
}

#if defined _DEBUG
bool lrfrVersionMgr::AssertValid()
{
   return true;
}

void lrfrVersionMgr::Dump(dbgDumpContext& os)
{
   os << GetVersionString(false) << endl;
}
#endif // _DEBUG
#if defined _UNITTEST
bool lrfrVersionMgr::TestMe(dbgLog& rlog)
{
   return true;
}
#endif // _UNITTEST

void lrfrVersionMgr::NotifyAllListeners()
{
   if ( !IsDamaged() )
   {
      notify_listeners( ms_Listeners );
   }
}
