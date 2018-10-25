///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

// EAFPluginCommandManager.h: interface for the CEAFPluginCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <EAF\EAFExp.h>
#include <EAF\EAFUIIntegration.h>
#include <map>

// All of the commands on the menus, toolbars, views, etc must have a unique command identifier. This is how
// Windows and MFC figures out which method to route the command to. However, with multiple extension agents
// and plug-ins developed by different parties, there is no way their extension commands will have unique IDs.
// Consider plugin A and plugin B that both add commands with ID=100. The developer of neither A nor B owns
// this command ID value and some third developer could create plugin C that also uses command ID=100
//
// The CEAFPluginCommandManager object keeps track of the commands added by the plug-ins. It creates unique
// command IDs that are assigned to the various menu items, tool bar buttons, etc. It also translates
// these unique IDs back to the original ID given by a plugin.

class EAFCLASS CEAFPluginCommandManager  
{
public:
	CEAFPluginCommandManager();
	virtual ~CEAFPluginCommandManager();

   void SetBaseCommandID(UINT nBaseID);

   // Adds a new commnad and the object to call when it is executed. Returns a unique
   // command id to be assigned to menu items, toolbar buttons, etc
   UINT AddCommandCallback(UINT nPluginCmdID,ICommandCallback* pCallback);

   // Transates the unique ID back into the original command ID gets the callback object
   // associated with the command
   BOOL GetCommandCallback(UINT nMappedID,UINT* pPluginCmdID,ICommandCallback** ppCallback);

   // Removes a callback based on the mapped command id
   void RemoveCommandCallback(UINT nMappedID);

   // returns all the mapped command ids of this callback
   std::vector<UINT> GetMappedCommandIDs(ICommandCallback* pCallback);

   // Given an original command ID and a callback, retreives the mapped (unique) command id
   BOOL GetMappedCommandID(UINT nPluginCmdID,ICommandCallback* pCallback,UINT* pMappedCmdID);

private:
   UINT m_nBaseID; // ID of first unique mapped id

   struct CCallbackItem 
   {
      UINT nPluginCmdID;
      CComPtr<ICommandCallback> pCallback;
   };

   typedef std::map<UINT,CCallbackItem> CallbackContainer;
   CallbackContainer m_Callbacks;
};
