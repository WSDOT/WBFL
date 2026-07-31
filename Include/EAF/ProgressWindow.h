///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright � 1999-2026  Washington State Department of Transportation
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
   WBFL::EAF::ProgressWindow

   Stand-alone progress window. Unlike IEAFProgress, this class has no
   dependency on an Agent-Broker/document context - it can be constructed
   and used from anywhere in an EAF-hosted application, including places
   that run before a project document (and therefore a broker) exists.

   The constructor creates and shows the window; the destructor tears it
   down. CEAFDocProxyAgent's IEAFProgress implementation is itself just a
   broker-aware wrapper around an instance of this class.
*****************************************************************************/

class CProgressThread;

namespace WBFL
{
   namespace EAF
   {
      class EAFCLASS ProgressWindow
      {
      public:
         ProgressWindow(CWnd* pParentWnd = nullptr, DWORD dwMask = PW_ALL, UINT nDelay = 500);
         ~ProgressWindow();

         ProgressWindow(const ProgressWindow&) = delete;
         ProgressWindow& operator=(const ProgressWindow&) = delete;

         void Init(short begin, short end, short inc);
         void Increment();
         void UpdateMessage(LPCTSTR msg);
         bool Continue(); // returns false if the user cancelled

      private:
         CProgressThread* m_pThread;
      };
   };
};
