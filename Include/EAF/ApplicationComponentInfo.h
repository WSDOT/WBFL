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

#include <EAF/ComponentObject.h>

class CEAFApp;

namespace WBFL
{
   namespace EAF
   {
      /// @brief Objects that implement this interface provide information about an EAF application 
      /// component. An application component is an abstract idea that represents
      /// an installable piece of the overall application. A component could be an EAFAppPlugin object
      /// or it could be a collection of 3rd party Extension Agent objects that extend the capabilities
      /// of an application.
      class ApplicationComponentInfo : public ComponentObject
      {
      public:
         /// @brief Called by the application framework to initialize this object
         /// This is a good place to validate license keys for 3rd party components
         virtual BOOL Init(CEAFApp* pApp) = 0;

         /// @brief Called by the application framework to do any clean up while terminating
         virtual void Terminate() = 0;

         /// @brief Return the name of your component
         virtual CString GetName() = 0;

         /// @brief Return a description of the component
         virtual CString GetDescription() = 0;

         /// @brief The icon returned goes in the About dialog
         virtual HICON GetIcon() = 0;

         /// @brief Return true if there is additional information to be displayed about the component
         virtual bool HasMoreInfo() = 0;

         /// @brief When this function is called, display more detailed information
         /// about your component
         virtual void OnMoreInfo() = 0;
      };
   };
};
