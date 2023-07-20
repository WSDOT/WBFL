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

namespace WBFL
{
   namespace LRFD
   {
      class LRFDVersionMgrListener;

      /// @brief LRFD specification manager. This class is a global manager of the
      /// LRFD specification currently in use. LRFDVersionMgrListener objects may
      /// be registered and will receive notifications when the specification changes
      class LRFDCLASS LRFDVersionMgr
      {
      public:
         /// @brief Identifies the specification edition
         enum class Version { FirstEdition1994              = 1,
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

         /// @brief Identifies the unit system of the specification. 
         /// AASHTO published dual US and SI LRFD specifications until 4th Edition 2007
         enum class Units { SI, US };

         LRFDVersionMgr() = delete;
         LRFDVersionMgr(const LRFDVersionMgr&) = delete;
         LRFDVersionMgr& operator=(const LRFDVersionMgr&) = delete;
         ~LRFDVersionMgr() = delete;

         /// @brief Sets the version manager into damage state. In damage state listeners are not notified of 
         /// changes until EndDamage is called
         static void BeginDamage();

         /// @brief Ends teh damaged state and notifies listeners of changes
         static void EndDamage();

         /// @brief Returns true if in the damaged stage
         static bool IsDamaged();

         /// @brief Registers a callback listener.
         static void RegisterListener(LRFDVersionMgrListener* pListener);

         /// @brief Unregisters a callback listener.
         static void UnregisterListener(LRFDVersionMgrListener* pListener);

         /// @brief Returns the listener count
         static IndexType ListenerCount();

         /// @brief Sets the current version of the LRFD specification.  Returns the previous version.
         /// If the specification units are SI and version is set to 4th Edition 2007 or later, the
         /// units well be automatically set to US
         static Version SetVersion(Version version);

         /// @brief Returns the current version of the specification.
         static Version GetVersion();

         /// @brief Returns the must recent version
         static Version GetLatestVersion();

         /// @brief Sets the units of the specification.
         /// If the specification version is 4th Edition 2007 or later, the units will automatically be set to US
         static Units SetUnits(Units units);

         /// @brief Returns the units of the specification.
         static Units GetUnits();

         /// @brief Returns the name of the specification - "AASHTO LRFD Bridge Design Specification"
         static LPCTSTR GetCodeString();

         /// @brief Returns the current version of the specification as a string.
         /// @param bAbbreviated If true, an abbreviated version is returned. The abbreviated version
         /// is a single word useful as a key
         static LPCTSTR GetVersionString(bool bAbbreviated=false);

         /// @brief Returns the specified version of the specification as a string.
         /// @param version The version for which a string is returned
         /// @param bAbbreviated If true, an abbreviated version is returned. The abbreviated version
         /// is a single word useful as a key
         static LPCTSTR GetVersionString(LRFDVersionMgr::Version version,bool bAbbreviated=false);

         /// @brief Returns the name of the specification unit system as a string.
         static LPCTSTR GetUnitString();

         /// @brief Returns the version from the abbreviated version string
         static Version GetVersion(LPCTSTR strAbbrev);

      private:
         static Version ms_Version;
         static Units   ms_Units;
         static bool    ms_IsDamaged;

         using Listeners = std::list<LRFDVersionMgrListener*, std::allocator<LRFDVersionMgrListener*>>;
         static Listeners ms_Listeners;

         static void NotifyAllListeners();
      };

      /// Function to support the 8th Edition, 2017 reorganization of chapter 5 of the Specifications
      // The mapping document for this endeavor by AASHTO T10 was called "Crosswalk", hence the function name


      /// @brief Updates a specification reference number to the 8th Edition 2007 specification. 
      /// Chapter 5 of the 8th Edition 2017 specification was reorganized and the reference number for
      /// many of the specification articles changed. The changes are document in a "Crosswalk" appendix
      /// to Chapter 5.
      /// @param oldArticleNumber The pre-8th Edition reference number 
      /// @param newArticleNumber The 8th Edition (and later) reference number
      /// @param version The version of the specification in use
      /// @return The reference number after applying the crosswalk
      inline LPCTSTR LrfdCw8th(LPCTSTR oldArticleNumber, LPCTSTR newArticleNumber,LRFDVersionMgr::Version version=LRFDVersionMgr::GetVersion())
      {
         return (version < LRFDVersionMgr::Version::EighthEdition2017) ? oldArticleNumber : newArticleNumber;
      }
   };
};
