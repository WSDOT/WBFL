///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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
#include <EAF\EAFExp.h>
#include <EAF\EAFTypes.h>
#include <EAF\StatusItem.h>

/*****************************************************************************
INTERFACE
   IEAFStatusCenter

   Interface for the status center.

DESCRIPTION
   Interface for the status center. The status center maintains current application
   status information.
*****************************************************************************/
// {77977E9B-B074-401f-8994-73A418FC4FFF}
DEFINE_GUID(IID_IEAFStatusCenter,
0x77977e9b, 0xb074, 0x401f, 0x89, 0x94, 0x73, 0xa4, 0x18, 0xfc, 0x4f, 0xff);
class EAFCLASS IEAFStatusCenter
{
public:
   virtual StatusGroupIDType CreateStatusGroupID() = 0;
   virtual StatusItemIDType Add(std::shared_ptr<WBFL::EAF::StatusItem> pItem) = 0;
   virtual bool RemoveByID(StatusItemIDType id) = 0;
   virtual bool RemoveByIndex(IndexType index) = 0;
   virtual bool RemoveByStatusGroupID(StatusGroupIDType statusGroupID) = 0;
   virtual std::shared_ptr<WBFL::EAF::StatusItem> GetByID(StatusItemIDType id) = 0;
   virtual std::shared_ptr<WBFL::EAF::StatusItem> GetByIndex(IndexType index) = 0;
   virtual WBFL::EAF::StatusSeverityType GetSeverity(std::shared_ptr<const WBFL::EAF::StatusItem> pItem) = 0;
   virtual WBFL::EAF::StatusSeverityType GetSeverity() = 0;
   virtual IndexType Count() = 0;
   virtual StatusCallbackIDType RegisterCallback(std::shared_ptr<WBFL::EAF::StatusCallback> pCallback) = 0;
};
