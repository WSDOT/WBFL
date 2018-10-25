///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2015  Washington State Department of Transportation
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


lrfrVersionMgr::Version lrfrVersionMgr::ms_Version = lrfrVersionMgr::FirstEdition2008;
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

std::_tstring lrfrVersionMgr::GetCodeString()
{
   return _T("The Manual for Bridge Evaluation");
}

std::_tstring lrfrVersionMgr::GetVersionString()
{
   return GetVersionString(ms_Version);
}

std::_tstring lrfrVersionMgr::GetVersionString(lrfrVersionMgr::Version version)
{
   std::_tstring strVersion;
   switch( version )
   {
   case FirstEdition2008:
      strVersion = _T("First Edition 2008");
      break;

   case FirstEditionWith2010Interims:
      strVersion = _T("First Edition 2008, with 2010 interim provisions");
      break;

   case SecondEdition2011:
      strVersion = _T("Second Edition 2011");
      break;
      
   case SecondEditionWith2011Interims:
      strVersion = _T("Second Edition 2011, with 2011 interim provisions");
      break;

   case SecondEditionWith2013Interims:
      strVersion = _T("Second Edition 2011, with 2011-2013 interim provisions");
      break;

   case SecondEditionWith2014Interims:
      strVersion = _T("Second Edition 2011, with 2011-2014 interim provisions");
      break;

   case SecondEditionWith2015Interims:
      strVersion = _T("Second Edition 2011, with 2011-2015 interim provisions");
      break;

   case SecondEditionWith2016Interims:
      strVersion = _T("Second Edition 2011, with 2011-2016 interim provisions");
      break;

   default:
      strVersion = _T("Unknown");
      ASSERT(false);
   }

   return strVersion;
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
   os << GetVersionString().c_str() << endl;
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
