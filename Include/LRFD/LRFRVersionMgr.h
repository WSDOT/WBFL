///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2010  Washington State Department of Transportation
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

COPYRIGHT
   Copyright (c) 2009
   Washington State Department Of Transportation
   All Rights Reserved

LOG
   rab : 12.07.2009 : Created file
*****************************************************************************/

class LRFDCLASS lrfrVersionMgr
{
public:
   enum Version { FirstEdition2008              = 1
   };

   ~lrfrVersionMgr();

   static void BeginDamage();
   static void EndDamage();
   static bool IsDamaged();

   static void RegisterListener(lrfrVersionMgrListener* pListener);

   static void UnregisterListener(lrfrVersionMgrListener* pListener);

   static Int32 ListenerCount();

   //------------------------------------------------------------------------
   // Sets the current version of the LRFR specification.  Returns the prevous
   // version.
   static Version SetVersion(Version version);

   //------------------------------------------------------------------------
   // Returns the current version of the specification.
   static Version GetVersion();

   //------------------------------------------------------------------------
   // Returns "The Manual for Bridge Evaluation"
   static std::string GetCodeString();

   //------------------------------------------------------------------------
   // Returns the current version of the specification as a string.
   static std::string GetVersionString();


   // GROUP: INQUIRY
   // GROUP: DEBUG
#if defined _DEBUG
   //------------------------------------------------------------------------
   // Returns <b>true</b> if the class is in a valid state, otherwise returns
   // <b>false</b>.
   static bool AssertValid();

   //------------------------------------------------------------------------
   // Dumps the contents of the class to the given stream.
   static void Dump(dbgDumpContext& os);
#endif // _DEBUG
#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:

   //------------------------------------------------------------------------
   static void NotifyAllListeners();

private:
   // GROUP: DATA MEMBERS
   static Version ms_Version;
   static bool    ms_IsDamaged;

public:
   typedef std::list<lrfrVersionMgrListener*,std::allocator<lrfrVersionMgrListener*>> Listeners;
private:
   static Listeners ms_Listeners;

   // Default constructor
   lrfrVersionMgr();

   // Prevent accidental copying and assignment
   lrfrVersionMgr(const lrfrVersionMgr&);
   lrfrVersionMgr& operator=(const lrfrVersionMgr&);
};
