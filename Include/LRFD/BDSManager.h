///////////////////////////////////////////////////////////////////////
// LRFD - Utility library to support equations, methods, and procedures
//        from the AASHTO LRFD Bridge Design Specification
// Copyright © 1999-2024  Washington State Department of Transportation
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
      class BDSManagerListener;

      /// @brief LRFD Bridge Design Specification (BDS) manager. This class is a global manager of the
      /// LRFD specification currently in use. BDSManagerListener objects may
      /// be registered and will receive notifications when the specification changes
      class LRFDCLASS BDSManager
      {
      public:
         /// @brief Identifies the specification edition
         enum class Edition { FirstEdition1994              = 1,
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
                        // Covid stretched out the 1st 3 year publication cycle to 4 years.
                        TenthEdition2024,
                        LastEdition
         };

         /// @brief Identifies the unit system of the specification. 
         /// AASHTO published dual US and SI LRFD specifications until 4th Edition 2007
         enum class Units { SI, US };

         BDSManager() = delete;
         BDSManager(const BDSManager&) = delete;
         BDSManager& operator=(const BDSManager&) = delete;
         ~BDSManager() = delete;

         /// @brief Sets the version manager into damage state. In damage state listeners are not notified of 
         /// changes until EndDamage is called
         static void BeginDamage();

         /// @brief Ends teh damaged state and notifies listeners of changes
         static void EndDamage();

         /// @brief Returns true if in the damaged stage
         static bool IsDamaged();

         /// @brief Registers a callback listener.
         static void RegisterListener(BDSManagerListener* pListener);

         /// @brief Unregisters a callback listener.
         static void UnregisterListener(BDSManagerListener* pListener);

         /// @brief Returns the listener count
         static IndexType ListenerCount();

         /// @brief Sets the edition of the LRFD specification.  Returns the previous edition.
         /// If the specification units are SI and edition is set to 4th Edition 2007 or later, the
         /// units well be automatically set to US
         static Edition SetEdition(Edition version);

         /// @brief Returns the selected edition of the specification.
         static Edition GetEdition();

         /// @brief Returns the must recent edition
         static Edition GetLatestEdition();

         /// @brief Sets the units of the specification.
         /// If the specification edition is 4th Edition 2007 or later, the units will automatically be set to US
         static Units SetUnits(Units units);

         /// @brief Returns the units of the specification.
         static Units GetUnits();

         /// @brief Returns the name of the specification - "AASHTO LRFD Bridge Design Specification"
         static LPCTSTR GetSpecificationName();

         /// @brief Returns the current edition of the specification as a string.
         /// @param bAbbreviated If true, an abbreviated version is returned. The abbreviated edition
         /// is a single word useful as a key
         static LPCTSTR GetEditionAsString(bool bAbbreviated=false);

         /// @brief Returns the specified edition of the specification as a string.
         /// @param edition The edition for which a string is returned
         /// @param bAbbreviated If true, an abbreviated edition is returned. The abbreviated edition
         /// is a single word useful as a key
         static LPCTSTR GetEditionAsString(BDSManager::Edition edition,bool bAbbreviated=false);

         /// @brief Returns the name of the specification unit system as a string.
         static LPCTSTR GetUnitAsString();

         /// @brief Returns the version from the abbreviated version string
         static Edition GetEdition(LPCTSTR strAbbrev);

      private:
         static Edition ms_Edition;
         static Units   ms_Units;
         static bool    ms_bIsDamaged;

         using Listeners = std::list<BDSManagerListener*, std::allocator<BDSManagerListener*>>;
         static Listeners ms_Listeners;

         static void NotifyAllListeners();
      };

      /// @brief Updates a specification reference number to the 8th Edition 2007 specification. 
      /// Chapter 5 of the 8th Edition 2017 specification was reorganized and the reference number for
      /// many of the specification articles changed. The changes are document in a "Crosswalk" appendix
      /// to Chapter 5.
      /// @param oldArticleNumber The pre-8th Edition reference number 
      /// @param newArticleNumber The 8th Edition (and later) reference number
      /// @param version The version of the specification in use
      /// @return The reference number after applying the crosswalk
      inline LPCTSTR LrfdCw8th(LPCTSTR oldArticleNumber, LPCTSTR newArticleNumber,BDSManager::Edition edition =BDSManager::GetEdition())
      {
         return (edition < BDSManager::Edition::EighthEdition2017) ? oldArticleNumber : newArticleNumber;
      }
   };
};
