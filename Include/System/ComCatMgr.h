///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysExp.h>
#include <ComCat.h>

namespace WBFL
{
   namespace System
   {
      /// Wrapper class for the COM Component Category Manager
      class SYSCLASS ComCatMgr
      {
      public:
         ComCatMgr() = delete;
         ComCatMgr(const ComCatMgr&) = delete;
         ~ComCatMgr() = delete;
         ComCatMgr& operator=(const ComCatMgr&) = delete;

         /// Creates a component category
         static HRESULT CreateCategory(
            OLECHAR* lpszDesc, ///< Component category description
            const CATID& catid ///< Category ID
         );

         /// Removes a component category
         static HRESULT RemoveCategory(
            const CATID& catid,///< Category ID
            bool bLeaveIfUsed ///< True causes component category to be removed, even if it is in use. False retains the component category if it is in use.
         );

         /// Registers or unregisters a class with a component category
         static HRESULT RegWithCategory(
            const CLSID& clsid, ///< Class ID to get registered with the category
            const CATID& catid, ///< The Category ID
            bool bReg ///< True registers the class, false unregisters
         );
      };
   };
};
