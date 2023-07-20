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
#include <Lrfd\VersionMgr.h>
#include <LRFD\LRFRVersionMgr.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Automatic object used to reset LRFD specification version settings.
      class LRFDCLASS LRFDAutoVersion
      {
      public:
         /// @brief Sets version and units to the current version and units returned from LRFDVersionMgr.
         LRFDAutoVersion();

         LRFDAutoVersion(const LRFDAutoVersion&) = delete;

         ~LRFDAutoVersion();

         LRFDAutoVersion& operator=(const LRFDAutoVersion&) = delete;

      private:
         LRFDVersionMgr::Version m_Version;
         LRFDVersionMgr::Units m_Units;
      };

      /// @brief Automatic object used to reset LRFR specification version settings.
      class LRFDCLASS LRFRAutoVersion
      {
      public:
         LRFRAutoVersion();
         LRFRAutoVersion(const LRFRAutoVersion&) = delete;
         ~LRFRAutoVersion();

         LRFRAutoVersion& operator=(const LRFRAutoVersion& rOther) = delete;

      private:
         LRFRVersionMgr::Version m_Version;
      };
   };
};
