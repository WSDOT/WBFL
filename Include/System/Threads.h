///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#include <System\SysExp.h>

namespace WBFL
{
   namespace System
   {
      /// Utility functions for threading and concurrency
      class SYSCLASS Threads
      {
      public:
         Threads() = delete;
         Threads(const Threads&) = delete;
         ~Threads() = delete;

         Threads& operator=(const Threads&) = delete;

         /// Set the minimum number of items per thread. Threading has overhread so if there
         /// aren't enough items, it may not be worthwhile to use multiple threads.
         /// This allows you to optimize threading by defining the minimum number of items for
         /// using multiple threads
         static void SetMinItemsPerThread(IndexType minItemsPerThread);
         static IndexType GetMinItemsPerThread();

         /// Returns the number of worker threads and number of items to be processed per thread.
         static void GetThreadParameters(IndexType nItems, IndexType& nWorkerThreads, IndexType& nItemsPerThread);

       private:
          static IndexType m_nMinItemsPerThread;
      };
   };
};
