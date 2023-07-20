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
      class LRFRVersionMgrListener;

      /// @brief LRFR specification manager. This class is a global manager of the
      /// LRFR specification currently in use. LRFRVersionMgrListener objects may
      /// be registered and will receive notifications when the specification changes
      class LRFDCLASS LRFRVersionMgr
      {
      public:
         /// @brief Identifies the specification edition
         enum class Version { FirstEdition2008              = 1,
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

         LRFRVersionMgr() = delete;
         LRFRVersionMgr(const LRFRVersionMgr&) = delete;
         LRFRVersionMgr& operator=(const LRFRVersionMgr&) = delete;
         ~LRFRVersionMgr() = delete;

         /// @brief Sets the version manager into damage state. In damage state listeners are not notified of 
         /// changes until EndDamage is called
         static void BeginDamage();

         /// @brief Ends teh damaged state and notifies listeners of changes
         static void EndDamage();

         /// @brief Returns true if in the damaged stage
         static bool IsDamaged();

         /// @brief Registers a callback listener.
         static void RegisterListener(LRFRVersionMgrListener* pListener);

         /// @brief Unregisters a callback listener.
         static void UnregisterListener(LRFRVersionMgrListener* pListener);

         /// @brief Returns the listener count
         static IndexType ListenerCount();

         /// @brief Sets the current version of the LRFR specification.  Returns the previous version.
         static Version SetVersion(Version version);

         /// @brief Returns the current version of the specification.
         static Version GetVersion();

         /// @brief Returns the must recent version
         static Version GetLatestVersion();

         /// @brief Returns the name of the specification - "The Manual for Bridge Evaluation"
         static LPCTSTR GetCodeString();

         /// @brief Returns the current version of the specification as a string.
         /// @param bAbbreviated If true, an abbreviated version is returned. The abbreviated version
         /// is a single word useful as a key
         static LPCTSTR GetVersionString(bool bAbbreviated=false);

         /// @brief Returns the specified version of the specification as a string.
         /// @param version The version for which a string is returned
         /// @param bAbbreviated If true, an abbreviated version is returned. The abbreviated version
         /// is a single word useful as a key
         static LPCTSTR GetVersionString(LRFRVersionMgr::Version version,bool bAbbreviated=false);

         /// @brief Returns the version from the abbreviated version string
         static Version GetVersion(LPCTSTR strAbbrev);

      private:
         static Version ms_Version;
         static bool    ms_IsDamaged;
         using Listeners = std::list<LRFRVersionMgrListener*,std::allocator<LRFRVersionMgrListener*>>;
         static Listeners ms_Listeners;

         static void NotifyAllListeners();
      };
   };
};
