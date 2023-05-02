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

#include <System\SysLib.h>
#include <System\Threads.h>
#include <thread>

using namespace WBFL::System;

static IndexType gs_hardware_threads = std::thread::hardware_concurrency();
IndexType Threads::m_nMinItemsPerThread = 10000;

void Threads::SetMinItemsPerThread(IndexType minItemsPerThread)
{
   m_nMinItemsPerThread = minItemsPerThread;
}

IndexType Threads::GetMinItemsPerThread() {
   return m_nMinItemsPerThread;
}

void Threads::GetThreadParameters(IndexType nItems, IndexType& nWorkerThreads, IndexType& nItemsPerThread) {
   IndexType max_threads = (nItems + m_nMinItemsPerThread - 1) / m_nMinItemsPerThread;
   IndexType nThreads = min(gs_hardware_threads != 0 ? gs_hardware_threads : 2, max_threads);
   nWorkerThreads = nThreads - 1;
   nItemsPerThread = nItems / nThreads;

   // this makes everything run in the main thread
   //nWorkerThreads = 0;
   //nItemsPerThread = nItems;
}