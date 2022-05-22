///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
// Copyright © 1999-2022  Washington State Department of Transportation
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
#include <memory>

namespace WBFL
{
   namespace System
   {
      /// Template class for singleton killers.  Deletes a singleton after it goes out of scope.
      ///
      /// See: http://www.sigs.com/publications/docs/cppr/9606/cppr9606.c.vlissides.html
      template <class T>
      class SingletonKiller
      {
      public:
         SingletonKiller(T* pSingleton = nullptr):
         m_pSingleton(pSingleton)
         {
         }

         SingletonKiller(const SingletonKiller&) = delete;
         SingletonKiller& operator=(const SingletonKiller&) = delete;

         ~SingletonKiller()
         {
	         delete m_pSingleton;
         }

         /// Replaces the pointer to the singleton, returning the pointer to the previous singleton
         T* SetSingleton(T* pSingleton)
         {
            T* pOldSingleton = m_pSingleton;
            m_pSingleton = pSingleton;
            return pOldSingleton;
         }

      private:
         T* m_pSingleton;
      };
   };
};
