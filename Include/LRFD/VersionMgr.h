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

#ifndef INCLUDED_LRFD_VERSIONMGR_H_
#define INCLUDED_LRFD_VERSIONMGR_H_
#pragma once

// SYSTEM INCLUDES
//
#include <Lrfd\LrfdExp.h>
#include <list>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//
class lrfdVersionMgrListener;

// MISCELLANEOUS
//

/*****************************************************************************
CLASS 
   lrfdVersionMgr

   LRFD Specification version manager.


DESCRIPTION
   LRFD Specification version manager.  This class controls the version of
   the LRFD specification currently in use.

LOG
   rab : 11.14.1997 : Created file

*****************************************************************************/

class LRFDCLASS lrfdVersionMgr
{
public:
   // GROUP: ENUMERATIONS
   enum Version { FirstEdition1994              = 1,
                  // no interims in 1995
                  FirstEditionWith1996Interims  = 2,
                  FirstEditionWith1997Interims  = 3,
                  SecondEdition1998             = 4,
                  SecondEditionWith1999Interims = 5,
                  SecondEditionWith2000Interims = 6,
                  SecondEditionWith2001Interims = 7,
                  SecondEditionWith2002Interims = 8,
                  SecondEditionWith2003Interims = 9,
                  ThirdEdition2004              = 10,
                  ThirdEditionWith2005Interims  = 11,
                  ThirdEditionWith2006Interims  = 12,
                  FourthEdition2007             = 13,
                  FourthEditionWith2008Interims = 14,
                  FourthEditionWith2009Interims = 15,
                  FifthEdition2010              = 16,
                  // no interims in 2011
                  SixthEdition2012              = 17,
                  SixthEditionWith2013Interims  = 18,
                  SeventhEdition2014            = 19,
                  SeventhEditionWith2015Interims = 20,
                  SeventhEditionWith2016Interims = 21,
                  EighthEdition2017              = 22,
                  // AASHTO changed to a 3 year publication cycle, no interims
                  NinthEdition2020               = 23,
                  LastVersion
   };

   enum Units { SI, US };

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Destructor
   ~lrfdVersionMgr();

   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   static void BeginDamage();
   //------------------------------------------------------------------------
   static void EndDamage();
   //------------------------------------------------------------------------
   static bool IsDamaged();

   //------------------------------------------------------------------------
   static void RegisterListener(lrfdVersionMgrListener* pListener);

   //------------------------------------------------------------------------
   static void UnregisterListener(lrfdVersionMgrListener* pListener);

   //------------------------------------------------------------------------
   static CollectionIndexType ListenerCount();

   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Sets the current version of the LRFD specification.  Returns the prevous
   // version.
   static Version SetVersion(Version version);

   //------------------------------------------------------------------------
   // Returns the current version of the specification.
   static Version GetVersion();

   //------------------------------------------------------------------------
   // Sets the units of the specification.
   static Units SetUnits(Units units);

   //------------------------------------------------------------------------
   // Sets the units of the specification.
   static Units GetUnits();

   //------------------------------------------------------------------------
   // Returns "AASHTO LRFD Bridge Design Specification"
   static LPCTSTR GetCodeString();

   //------------------------------------------------------------------------
   // Returns the current version of the specification as a string.
   static LPCTSTR GetVersionString(bool bAbbreviated=false);

   //------------------------------------------------------------------------
   // Returns the current version of the specification as a string. 
   // If bAbbreviated is true, the appreviated string is returned
   static LPCTSTR GetVersionString(lrfdVersionMgr::Version version,bool bAbbreviated=false);

   //------------------------------------------------------------------------
   // Returns the current unit of the specification as a string.
   static LPCTSTR GetUnitString();

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
   static void Dump(dbgDumpContext& os);
#endif // _DEBUG
#if defined _UNITTEST
   //------------------------------------------------------------------------
   // Self-diagnostic test function.  Returns <b>true</b> if the test passes,
   // otherwise return <b>false</b>.
   static bool TestMe(dbgLog& rlog);
#endif // _UNITTEST

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS

   //------------------------------------------------------------------------
   static void NotifyAllListeners();

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   static Version ms_Version;
   static Units   ms_Units;
   static bool    ms_IsDamaged;

   static std::list<lrfdVersionMgrListener*, std::allocator<lrfdVersionMgrListener*> > ms_Listeners;

   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor
   lrfdVersionMgr();

   // Prevent accidental copying and assignment
   lrfdVersionMgr(const lrfdVersionMgr&);
   lrfdVersionMgr& operator=(const lrfdVersionMgr&) = delete;

   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//
// Function to support the 8th Edition, 2017 reorganization of chapter 5 of the Specifications
// The mapping document for this endeavor by AASHTO T10 was called "Crosswalk", hence the function name
inline LPCTSTR LrfdCw8th(LPCTSTR oldStr, LPCTSTR newStr)
{
   // Map to the current version of the spec
   if (lrfdVersionMgr::GetVersion() < lrfdVersionMgr::EighthEdition2017)
   {
      return oldStr;
   }
   else
   {
      return newStr;
   }
}

// EXTERNAL REFERENCES
//

#endif // INCLUDED_LRFD_VERSIONMGR_H_
