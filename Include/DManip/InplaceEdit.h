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
      /// @brief Interface implemented by display objects that present an in-place editing interface such as a text edit box.
      class DMANIPCLASS iInplaceEditable
      {
      public:
         /// @brief Call to start the Inplace Editing process
         virtual void DoInplaceEdit() = 0;

         virtual void EndInplaceEdit() = 0;

         /// @brief Called when it is time to create an edit control on the screen
         virtual void CreateEditControl() = 0;

         /// @brief Called when it is time to destroy the edit control
         virtual void DestroyEditControl() = 0;

         /// @brief Called when the data in the control needs to be validated
         /// @return Return true if the data is valid
         virtual bool ValidateData() = 0;

         /// @brief Called by the framework when the edited data has changed
         virtual void OnDataChanged() = 0;
      };
   };
};
