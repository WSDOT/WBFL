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

// Core.cpp : Implementation of DLL Exports.


#include "stdafx.h"
#include "resource.h"
#include <initguid.h>

#include <WBFLTools_i.c>
#include "CLSID.h"

#include "SysAgent.h"

#include <EAF\ComponentModule.h>
WBFL::EAF::ComponentModule Module_;
EAF_BEGIN_OBJECT_MAP(ObjectMap)
   EAF_OBJECT_ENTRY(CLSID_SysAgent,CSysAgent)
EAF_END_OBJECT_MAP()

class CCoreApp : public CWinApp
{
public:

   // Overrides
   virtual BOOL InitInstance() override;
   virtual int ExitInstance() override;

   DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CCoreApp, CWinApp)
END_MESSAGE_MAP()

CCoreApp theApp;

BOOL CCoreApp::InitInstance()
{
   Module_.Init(ObjectMap);
   return CWinApp::InitInstance();
}

int CCoreApp::ExitInstance()
{
   Module_.Term();
   return CWinApp::ExitInstance();
}
