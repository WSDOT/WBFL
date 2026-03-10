///////////////////////////////////////////////////////////////////////
// CORE - Core elements of the Agent-Broker Architecture
// Copyright © 1999-2025  Washington State Department of Transportation
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

#include <EAF/Agent.h>
#include <EAF/EAFProgress.h>
#include <EAF/EAFCommandLineInfo.h>
#include "ProgressThread.h"

class CSysAgent : public WBFL::EAF::Agent,
   public IEAFProgress
{
public:
	CSysAgent() = default;
	virtual ~CSysAgent() = default;

// Agent
public:
   std::_tstring GetName() const override { return _T("SysAgent"); }
   bool RegisterInterfaces() override;
   bool Init() override;
   bool ShutDown() override;
   CLSID GetCLSID() const override;

   // IEAFProgress
public:
   HRESULT CreateProgressWindow(DWORD dwMask, UINT nDelay) override;
   HRESULT Init(short begin, short end, short inc) override;
   HRESULT Increment() override;
   HRESULT UpdateMessage(LPCTSTR msg) override;
   HRESULT Continue() override;
   HRESULT DestroyProgressWindow() override;

private:
   EAF_DECLARE_AGENT_DATA;

   CProgressThread* m_pThread = nullptr;
   Int16 m_cProgressRef = 0; // progress thread ref count
                                            // a progress window instance begins

   HRESULT ValidateThread();

   std::vector<std::_tstring> m_MessageStack;
   std::_tstring m_LastMessage; // most recent message

   CEAFCommandLineInfo::CommandLineDisplayMode m_CommandLineDisplayMode;  // display mode if in command line mode
};
