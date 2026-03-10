///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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
#include <DManip/DManipExp.h>

namespace WBFL
{
   namespace DManip
   {
      /// @brief Interface defining a tool that may be placed in a CToolPalette
      class DMANIPCLASS iTool
      {
      public:
         /// @brief Sets the identifier of the tool. 
         /// Must be the same as the resource identifier as the dialog bar control
         virtual void SetID(UINT id) = 0;
         virtual UINT GetID() const = 0; 

         /// @brief Sets the tooltip text for the tool
         virtual void SetToolTipText(LPCTSTR lpszText) = 0;
         virtual std::_tstring GetToolTipText() const = 0;
      };

      /// @brief Interface defining the icon resource associated with a tool
      class DMANIPCLASS iToolIcon
      {
      public:
         /// @brief Sets the icon resource
         /// @param hInstance Instance handle for the instance owning the icon resource
         /// @param IconResId Identifier of the icon resource
         /// @return 
         virtual HRESULT SetIcon(HINSTANCE hInstance, WORD IconResId) = 0;
      };
   };
};
