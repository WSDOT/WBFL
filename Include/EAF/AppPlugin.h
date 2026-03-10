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

#include <EAF\EAFTypes.h>

class CEAFPluginApp;

namespace WBFL
{
   namespace EAF
   {
      /// @brief This interface is for plugins to the main CEAFApp application
      class IAppPlugin
      {
      public:
         /// @brief Called for self-initialization
         virtual BOOL Init(CEAFPluginApp * pParent) = 0;

         /// @brief Called when the application is about to terminate
         virtual void Terminate() = 0;

         /// @brief Called to give this plugin the opportunity to integrate itself
         /// into the user interface. When bIntegrate is TRUE, add menus, commands, toolbars, etc
         /// when FALSE, remove what you added
         virtual void IntegrateWithUI(BOOL bIntegrate) = 0;

         /// @brief return the name of the plugin. This name is used throughout the user interface
         virtual CString GetName() = 0;
      };
   };
};
