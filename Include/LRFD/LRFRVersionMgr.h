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

#pragma once

#include <Lrfd\LrfdExp.h>
#include <list>

class lrfrVersionMgrListener;

/*****************************************************************************
CLASS 
   lrfrVersionMgr

   LRFR Specification version manager.


DESCRIPTION
   LRFR Specification version manager.  This class controls the version of
   the LRFR specification currently in use.

LOG
   rab : 12.07.2009 : Created file
*****************************************************************************/

class LRFDCLASS lrfrVersionMgr
{
public:
   enum Version { FirstEdition2008              = 1,
                  // no interims in 2009
                  FirstEditionWith2010Interims  = 2,
                  SecondEdition2011             = 3, // Is this 2010 or 2011... Original document says 2011, interims say 2010... very confusion
                  SecondEditionWith2011Interims = 4,
                  SecondEditionWith2013Interims = 5,
                  SecondEditionWith2014Interims = 6,
                  SecondEditionWith2015Interims = 7,
                  SecondEditionWith2016Interims = 8,
                  ThirdEdition2018              = 9,
                  ThirdEditionWith2020Interims = 10,
                  LastVersion
};

   ~lrfrVersionMgr();

   static void BeginDamage();
   static void EndDamage();
   static bool IsDamaged();

   static void RegisterListener(lrfrVersionMgrListener* pListener);

   static void UnregisterListener(lrfrVersionMgrListener* pListener);

   static CollectionIndexType ListenerCount();

   //------------------------------------------------------------------------
   // Sets the current version of the LRFR specification.  Returns the prevous
   // version.
   static Version SetVersion(Version version);

   //------------------------------------------------------------------------
   // Returns the current version of the specification.
   static Version GetVersion();

   //------------------------------------------------------------------------
   // Returns "The Manual for Bridge Evaluation"
   static LPCTSTR GetCodeString();

   //------------------------------------------------------------------------
   // Returns the current version of the specification as a string.
   static LPCTSTR GetVersionString(bool bAbbreviated=false);

   //------------------------------------------------------------------------
   // Returns the current version of the specification as a string.
   static LPCTSTR GetVersionString(lrfrVersionMgr::Version version,bool bAbbreviated=false);

   //------------------------------------------------------------------------
   // returns the version enum value from the abbreviated version string
   static Version GetVersion(LPCTSTR strAbbrev);

   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   static bool AssertValid();

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   static void Dump(WBFL::Debug::LogContext& os);
#endif // _DEBUG
#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(WBFL::Debug::Log& rlog);
#endif // _UNITTEST

protected:

   //------------------------------------------------------------------------
   static void NotifyAllListeners();

private:
   // GROUP: DATA MEMBERS
   static Version ms_Version;
   static bool    ms_IsDamaged;

public:
   using Listeners = std::list<lrfrVersionMgrListener*,std::allocator<lrfrVersionMgrListener*>>;

private:
   static Listeners ms_Listeners;

   // Default constructor
   lrfrVersionMgr();

   // Prevent accidental copying and assignment
   lrfrVersionMgr(const lrfrVersionMgr&);
   lrfrVersionMgr& operator=(const lrfrVersionMgr&) = delete;
};
