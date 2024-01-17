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
#include <Lrfd/BDSManager.h>
#include <Lrfd/MBEManager.h>

namespace WBFL
{
   namespace LRFD
   {
      /// @brief Automatic object used to reset LRFD specification edition settings.
      class LRFDCLASS BDSAutoVersion
      {
      public:
         /// @brief Sets edition and units to the current edition and units returned from BDSManager.
         BDSAutoVersion();

         BDSAutoVersion(const BDSAutoVersion&) = delete;

         ~BDSAutoVersion();

         BDSAutoVersion& operator=(const BDSAutoVersion&) = delete;

      private:
         BDSManager::Edition m_Edition;
         BDSManager::Units m_Units;
      };

      /// @brief Automatic object used to reset LRFR specification edition settings.
      class LRFDCLASS MBEAutoVersion
      {
      public:
         MBEAutoVersion();
         MBEAutoVersion(const MBEAutoVersion&) = delete;
         ~MBEAutoVersion();

         MBEAutoVersion& operator=(const MBEAutoVersion& rOther) = delete;

      private:
         MBEManager::Edition m_Edition;
      };
   };
};
