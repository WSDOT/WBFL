///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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
   // Reserves the total range of command IDs that may be used for plug-in commands.
   // This also defines the maximum number of plug-in commands that an application can support
   // Each plug-in manager must call ReserveCommandIDRange(nCommands) to reserve command IDs for
   // its plug-ins
   static void ReserveTotalCommandIDRange(UINT nMinID,UINT nMaxID);
   static UINT GetCommandTotal();

	CEAFPluginCommandManager();
	virtual ~CEAFPluginCommandManager();

   // Reserves a range of commands for this command manager
   // Returns the actual size of the range created or -1 if the range could not be reserved.
   // This method clears all callbacks previously added
   UINT ReserveCommandIDRange(UINT nCommands);

   // returns the number of reserved commands
   UINT GetReservedCommandIDCount() const;

   // returns the first and last command command
   void GetReservedCommandIDRange(UINT* pFirst,UINT* pLast) const;

   // Adds a new commnad and the object to call when it is executed. Returns a unique
   // command id to be assigned to menu items, toolbar buttons, etc through the pMappedID
   // parameter. Returns FALSE if the plugin command cannot be mapped
   BOOL AddCommandCallback(UINT nPluginCmdID,IEAFCommandCallback* pCallback,UINT* pMappedID);

   // Transates the unique ID back into the original command ID gets the callback object
   // associated with the command
   BOOL GetCommandCallback(UINT nMappedID,UINT* pPluginCmdID,IEAFCommandCallback** ppCallback);

   // Removes a callback based on the mapped command id
   void RemoveCommandCallback(UINT nMappedID);

   // returns all the mapped command ids of this callback
   std::vector<UINT> GetMappedCommandIDs(IEAFCommandCallback* pCallback);

   // Given an original command ID and a callback, retreives the mapped (unique) command id
   BOOL GetMappedCommandID(UINT nPluginCmdID,IEAFCommandCallback* pCallback,UINT* pMappedCmdID);

   // clears out all command ID mapping
   void Clear();

private:
   static UINT ms_MinID; // minimum command ID
   static UINT ms_MaxID; // maximum command ID
   static UINT ms_NextID; // start of the next available command ID

   UINT m_nBaseID; // ID of first unique mapped id
   UINT m_nCommands; // number of commands reserved for this command manager
   UINT m_nNextID;

   // returns true if the command id supplied by a plugin is in the
   // range of the standard command IDs handled by the application.
   // If this method returns true, the command ID is not mapped and
   // it will be handled by standard processing
   bool IsInStandardRange(UINT nPluginCmdID);

   struct CCallbackItem 
   {
      UINT nPluginCmdID;
      CComPtr<IEAFCommandCallback> pCallback;
   };

   typedef std::map<UINT,CCallbackItem> CallbackContainer;
   typedef std::pair<UINT,CCallbackItem> CallbackEntry;
   CallbackContainer m_Callbacks;
};
