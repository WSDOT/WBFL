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

// EAFMenu.h: interface for the CEAFMenu class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <EAF\EAFExp.h>
#include <vector>
#include <memory>

namespace WBFL
{
   namespace EAF
   {
	  class PluginCommandManager;
	  class ICommandCallback;

	  /// @brief Wrapper class for a Windows accelerator table. Plug-ins cannot access the accelerator table directly because of the 
	  /// need to map plug-in command ID's, which are not guaranteed to be unique, into application
	  /// command IDs that must be unique. This class provides an object wrapper on the accelerator table
	  /// and handles command ID mapping and routing
	  class EAFCLASS AcceleratorTable
	  {
	  public:
		 AcceleratorTable() = default;
   	     virtual ~AcceleratorTable();

		 void Init(std::shared_ptr<WBFL::EAF::PluginCommandManager> pCmdMgr);

		 BOOL AddAccelTable(HACCEL hAccelTable, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);

		 BOOL AddAccelKey(BYTE fVirt, WORD key, WORD cmd, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);
		 BOOL RemoveAccelKey(WORD cmd, std::shared_ptr<WBFL::EAF::ICommandCallback> pCallback);
		 BOOL RemoveAccelKey(BYTE fVirt,WORD key);

		 BOOL TranslateMessage(CWnd* pWnd,MSG* pMsg);

	  private:

		 std::shared_ptr<WBFL::EAF::PluginCommandManager> m_pCmdMgr;
		 HACCEL m_hAccelTable = 0;
	  };
   };
};
