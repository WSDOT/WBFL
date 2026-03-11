///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2026  Washington State Department of Transportation
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

#include <EAF\EAFExp.h>
#include <EAF\EAFProgress.h>

/*****************************************************************************
CLASS 
   WBFL::EAF::AutoProgress

   Auto-pointer like class for the IProgress interface.


DESCRIPTION
   Auto-pointer like class for the IProgress interface.
   Code that creates progress windows must destroy them.  When exceptions
   are throw, the destroy code is often never called.  This class encapsulates
   the destroy code and is automatically called as the stack unwinds.

EXAMPLE
   EAFAutoProgress ap(pProgress);
   // Don't call CreateWindow or DestroyWindow on the IProgress interface
*****************************************************************************/

namespace WBFL
{
   namespace EAF
   {
      /// @brief Auto-pointer like class for the IEAFProgress interface.
      /// Code that creates progress windows must destroy them. When exceptions
      /// are thrown, the destroy code is often never called. This class encapsulates
      /// the destroy code and is automatically called as the stack unwinds.
      class EAFCLASS AutoProgress
      {
      public:
         AutoProgress(const AutoProgress&) = delete;
         AutoProgress(std::shared_ptr<IEAFProgress> pProgress,UINT nDelay = 500,DWORD dwMask = PW_ALL | PW_NOGAUGE | PW_NOCANCEL);
         ~AutoProgress();

         AutoProgress& operator=(const AutoProgress&) = delete;

         HRESULT Continue();

      private:
         std::shared_ptr<IEAFProgress> m_pProgress;
         bool m_bCreated;

         HRESULT CreateProgressWindow(DWORD dwMask,UINT nDelay);
      };
   };
};
